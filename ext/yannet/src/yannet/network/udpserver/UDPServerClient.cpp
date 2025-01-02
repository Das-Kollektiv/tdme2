#include <stdio.h>

#include <string>
#include <typeinfo>
#include <unordered_map>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServerClient.h>
#include <yannet/network/udpserver/NetworkServerException.h>
#include <yannet/utilities/Console.h>
#include <yannet/utilities/RTTI.h>
#include <yannet/utilities/Time.h>

using std::string;
using std::unordered_map;

using yannet::network::udpserver::UDPServerClient;

using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::NetworkServerException;
using yannet::utilities::Console;
using yannet::utilities::RTTI;
using yannet::utilities::Time;

UDPServerClient::UDPServerClient(const uint32_t clientId, const string& ip, const uint16_t port) :
	server(nullptr),
	ioThread(nullptr),
	clientId(clientId),
	ip(ip),
	port(port),
	shutdownRequested(false),
	messageMapSafeMutex("nioudpserverclient_messagemapsafe") {
	// key
	key = KEY_PREFIX_UNNAMED + to_string(clientId);
}

UDPServerClient::~UDPServerClient() {
	for (const auto& [messageId, message]: messageMapSafe) delete message;
}

const bool UDPServerClient::setKey(const string &key) {
	if (key.size() > 0 &&
		key.size() < 256 &&
		server->setClientKey(this, key) == true) {
		this->key = key;
		return true;
	} else {
		return false;
	}
}

UDPPacket* UDPServerClient::createPacket() {
	auto packet = new UDPPacket();
	UDPServer::initializeHeader(packet);
	return packet;
}

void UDPServerClient::send(UDPPacket* packet, bool safe, bool deleteFrame) {
	try {
		server->sendMessage(this, packet, safe, deleteFrame, UDPServer::MESSAGETYPE_MESSAGE);
	} catch (NetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::printLine(
			"UDPServerClient::send(): send failed for client '" +
			ip +
			"': " +
			RTTI::demangle(typeid(exception).name()) +
			": " +
			string(exception.what())
		);
	}
}

bool UDPServerClient::processSafeMessage(const uint32_t messageId) {
	bool messageProcessed = false;

	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	auto it = messageMapSafe.find(messageId);
	if (it != messageMapSafe.end()) {
		// yep, we did
		messageProcessed = true;
		auto message = it->second;
		message->receptions++;
	} else {
		// nope, just remember message
		auto message = new Message();
		message->messageId = messageId;
		message->receptions = 1;
		message->time = Time::getCurrentMillis();
		// TODO: check for overflow
		messageMapSafe[messageId] = message;
	}

	//
	messageMapSafeMutex.unlock();

	// always send acknowlegdement to client
	auto packet = createPacket();
	try {
		server->sendMessage(this, packet, false, true, UDPServer::MESSAGETYPE_ACKNOWLEDGEMENT, messageId);
	} catch (NetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::printLine(
			"UDPServerClient::processSafeMessage(): send failed for client '" +
			ip +
			"': " +
			RTTI::demangle(typeid(exception).name()) +
			": " +
			string(exception.what())
		);
	}

	// return if message should be processed
	return messageProcessed == true?false:true;
}

void UDPServerClient::sendConnected() {
	auto packet = createPacket();
	try {
		packet->putString(key);
		server->sendMessage(this, packet, true, true, UDPServer::MESSAGETYPE_CONNECT);
	} catch (NetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::printLine(
			"UDPServerClient::sendConnected(): send failed for client '" +
			ip +
			"': " +
			RTTI::demangle(typeid(exception).name()) +
			": " +
			string(exception.what())
		);
	}
}

void UDPServerClient::shutdown() {
	shutdownRequested = true;
}

void UDPServerClient::onPacketReceived(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries) {
	// create request
	auto request = new ServerRequest(
		ServerRequest::REQUESTTYPE_CLIENT_REQUEST,
		this,
		ServerRequest::EVENT_CUSTOM_NONE,
		packet,
		messageId,
		retries
	);
	// delegate it to thread pool, but make it declinable
	if (server->workerThreadPool->addElement(request, true) == false) {
		// element was declined
		Console::printLine("UDPServerClient::onPacketReceived(): client request declined from '" + (ip) + "'. Shutting down client");
		// 	release client reference
		releaseReference();
		// 	delete packet
		delete packet;
		// 	delete request
		delete request;
		// 	shutdown client
		shutdown();
	}
}

void UDPServerClient::close() {
	// create request
	auto request = new ServerRequest(
		ServerRequest::REQUESTTYPE_CLIENT_CLOSE,
		this,
		ServerRequest::EVENT_CUSTOM_NONE,
		nullptr,
		ServerRequest::MESSAGE_ID_UNSUPPORTED,
		ServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
	// server call back
	server->closeClient(this);
}

void UDPServerClient::init() {
	// acquire reference for worker
	acquireReference();

	// create request
	auto request = new ServerRequest(
		ServerRequest::REQUESTTYPE_CLIENT_INIT,
		this,
		ServerRequest::EVENT_CUSTOM_NONE,
		nullptr,
		ServerRequest::MESSAGE_ID_UNSUPPORTED,
		ServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}

void UDPServerClient::fireEvent(const string &type) {
	// acquire reference for worker
	acquireReference();

	// create request
	auto request = new ServerRequest(
		ServerRequest::REQUESTTYPE_CLIENT_CUSTOM,
		this,
		type,
		nullptr,
		ServerRequest::MESSAGE_ID_UNSUPPORTED,
		ServerRequest::MESSAGE_RETRIES_NONE
	);

	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}


void UDPServerClient::cleanUpSafeMessages() {
	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	auto now = Time::getCurrentMillis();
	auto it = messageMapSafe.begin();
	while (it != messageMapSafe.end()) {
		auto message = it->second;
		if (message->time < now - MESSAGESSAFE_KEEPTIME) {
			delete it->second;
			messageMapSafe.erase(it++);
			continue;
		}
		++it;
	}

	//
	messageMapSafeMutex.unlock();
}

uint64_t UDPServerClient::getRetryTime(const uint8_t retries) {
	if (retries == 0) return 0L;
	if (retries > UDPServerIOThread::MESSAGEACK_RESENDTIMES_TRIES) return 0L;
	return UDPServerIOThread::MESSAGEACK_RESENDTIMES[retries - 1];
}

