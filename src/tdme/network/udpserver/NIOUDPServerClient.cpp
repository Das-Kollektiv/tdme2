#include <stdio.h>

#include <map>
#include <string>
#include <sstream>
#include <typeinfo>

#include <tdme/utils/Console.h>
#include <tdme/utils/IntEncDec.h>
#include <tdme/utils/RTTI.h>
#include <tdme/utils/StringConverter.h>
#include <tdme/utils/Time.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>

using std::ios_base;
using std::map;
using std::pair;
using std::string;
using std::stringstream;

using tdme::utils::Console;
using tdme::utils::IntEncDec;
using tdme::utils::RTTI;
using tdme::utils::StringConverter;
using tdme::utils::Time;
using tdme::network::udpserver::NIOUDPServerClient;

NIOUDPServerClient::NIOUDPServerClient(const uint32_t clientId, const string& ip, const unsigned int port) :
	server(NULL),
	ioThread(NULL),
	clientId(clientId),
	ip(ip),
	port(port),
	shutdownRequested(false),
	messageMapSafeMutex(L"nioudpserverclient_messagemapsafe") {
	// key
	ostringstream tmp;
	tmp << KEY_PREFIX_UNNAMED;
	tmp << clientId;
	key = tmp.str();
}

NIOUDPServerClient::~NIOUDPServerClient() {
}

NIOUDPServer* NIOUDPServerClient::getServer() {
	return server;
}

const uint32_t NIOUDPServerClient::getClientId() {
	return clientId;
}

const string& NIOUDPServerClient::getIp() const {
	return ip;
}

const unsigned int NIOUDPServerClient::getPort() const {
	return port;
}

const string& NIOUDPServerClient::getKey() const {
	return key;
}

const bool NIOUDPServerClient::setKey(const string &key) {
	if (server->setClientKey(this, key) == true) {
		this->key = key;
		return true;
	} else {
		return false;
	}
}

stringstream* NIOUDPServerClient::createFrame() {
	stringstream* frame = new stringstream();
	server->writeHeader(frame);
	return frame;
}

void NIOUDPServerClient::send(stringstream* frame, bool safe) {
	try {
		// seek writing to end of stream
		frame->seekp(0, ios_base::end);

		// check size
		if (frame->tellp() > 512) {
			delete frame;
			throw NIONetworkServerException("message too big");
		}

		server->sendMessage(this, frame, safe, NIOUDPServer::MESSAGETYPE_MESSAGE);
	} catch (NIONetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::println(
			L"NIOUDPServerClient::send(): send failed for client '" +
			StringConverter::toWideString(ip) +
			L"': " +
			StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
			L": " +
			StringConverter::toWideString(exception.what())
		);
	}
}

bool NIOUDPServerClient::processSafeMessage(const uint32_t messageId) {
	bool messageProcessed = false;
	MessageMapSafe::iterator it;

	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	it = messageMapSafe.find(messageId);
	if (it != messageMapSafe.end()) {
		// yep, we did
		messageProcessed = true;
		Message* message = &it->second;
		message->receptions++;
	} else {
		// nope, just remember message
		Message message;
		message.messageId = messageId;
		message.receptions = 1;
		message.time = Time::getCurrentMillis();
		// TODO: check for overflow
		messageMapSafe.insert(it, pair<uint32_t, Message>(messageId, message));
	}

	//
	messageMapSafeMutex.unlock();

	// always send acknowlegdement to client
	stringstream* frame = createFrame();
	try {
		server->sendMessage(this, frame, false, NIOUDPServer::MESSAGETYPE_ACKNOWLEDGEMENT, messageId);
	} catch (NIONetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::println(
			L"NIOUDPServerClient::sendAcknowledgement(): send failed for client '" +
			StringConverter::toWideString(ip) +
			L"': " +
			StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
			L": " +
			StringConverter::toWideString(exception.what())
		);
	}

	// return if message should be processed
	return messageProcessed == true?false:true;
}

void NIOUDPServerClient::sendConnected() {
	stringstream* frame = createFrame();
	try {
		server->sendMessage(this, frame, true, NIOUDPServer::MESSAGETYPE_CONNECT);
	} catch (NIONetworkServerException &exception) {
		// shut down client
		shutdown();

		// log
		Console::println(
			L"NIOUDPServerClient::sendConnected(): send failed for client '" +
			StringConverter::toWideString(ip) +
			L"': " +
			StringConverter::toWideString(RTTI::demangle(typeid(exception).name())) +
			L": " +
			StringConverter::toWideString(exception.what())
		);
	}
}

void NIOUDPServerClient::shutdown() {
	shutdownRequested = true;
}

void NIOUDPServerClient::onFrameReceived(stringstream* frame, const uint32_t messageId, const uint8_t retries) {
	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_REQUEST,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		frame,
		messageId,
		retries
	);
	// delegate it to thread pool, but make it declinable
	if (server->workerThreadPool->addElement(request, true) == false) {
		// element was declined
		Console::println(L"NIOUDPServerClient::onFrameReceived(): client request declined from '" + StringConverter::toWideString(ip) + L"'. Shutting down client");
		// 	release client reference
		releaseReference();
		// 	delete frame
		delete frame;
		// 	delete request
		delete request;
		// 	shutdown client
		shutdown();
	}
}

void NIOUDPServerClient::close() {
	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_CLOSE,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
	// server call back
	server->closeClient(this);
}

void NIOUDPServerClient::init() {
	// acquire reference for worker
	acquireReference();

	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_INIT,
		this,
		NIOServerRequest::EVENT_CUSTOM_NONE,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);
	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}

void NIOUDPServerClient::fireEvent(const string &type) {
	// acquire reference for worker
	acquireReference();

	// create request
	NIOServerRequest* request = new NIOServerRequest(
		NIOServerRequest::REQUESTTYPE_CLIENT_CUSTOM,
		this,
		type,
		NULL,
		NIOServerRequest::MESSAGE_ID_UNSUPPORTED,
		NIOServerRequest::MESSAGE_RETRIES_NONE
	);

	// delegate it to thread pool, but make close request not declinable
	server->workerThreadPool->addElement(request, false);
}


void NIOUDPServerClient::cleanUpSafeMessages() {
	//
	messageMapSafeMutex.lock();

	// check if message has been already processed
	uint64_t now = Time::getCurrentMillis();
	MessageMapSafe::iterator it = messageMapSafe.begin();
	while (it != messageMapSafe.end()) {
		Message* message = &it->second;
		if (message->time < now - MESSAGESSAFE_KEEPTIME) {
			messageMapSafe.erase(it++);
			continue;
		}
		++it;
	}

	//
	messageMapSafeMutex.unlock();
}

uint64_t NIOUDPServerClient::getRetryTime(const uint8_t retries) {
	if (retries == 0) return 0L;
	if (retries > NIOUDPServerIOThread::MESSAGEACK_RESENDTIMES_TRIES) return 0L;
	return NIOUDPServerIOThread::MESSAGEACK_RESENDTIMES[retries - 1];
}

