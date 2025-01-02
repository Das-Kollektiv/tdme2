#include <yannet/network/udpserver/UDPServer.h>

#include <exception>
#include <memory>
#include <string>
#include <string_view>
#include <typeinfo>

#include <yannet/yannet.h>
#include <yannet/math/Math.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServerClient.h>
#include <yannet/network/udpserver/UDPServerIOThread.h>
#include <yannet/os/threading/AtomicOperations.h>
#include <yannet/os/threading/Barrier.h>
#include <yannet/os/threading/ReadWriteLock.h>
#include <yannet/os/threading/Thread.h>
#include <yannet/utilities/Console.h>
#include <yannet/utilities/Integer.h>
#include <yannet/utilities/RTTI.h>
#include <yannet/utilities/Time.h>

using std::ios_base;
using std::make_unique;
using std::string;
using std::string_view;
using std::to_string;
using std::unique_ptr;

using yannet::math::Math;
using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::UDPServer;
using yannet::network::udpserver::UDPServerClient;
using yannet::network::udpserver::UDPServerIOThread;
using yannet::os::threading::AtomicOperations;
using yannet::os::threading::Barrier;
using yannet::os::threading::ReadWriteLock;
using yannet::os::threading::Thread;
using yannet::utilities::Console;
using yannet::utilities::Integer;
using yannet::utilities::RTTI;
using yannet::utilities::Time;

UDPServer::UDPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU) :
	Server<UDPServerClient, UDPServerGroup>(name, host, port, maxCCU),
	Thread("nioudpserver"),
	clientIdMapReadWriteLock("nioudpserver_clientidmap"),
	clientIpMapReadWriteLock("nioudpserver_clientipmap"),
	workerThreadPool(nullptr),
	clientCount(0),
	messageCount(0) {
	//
}

UDPServer::~UDPServer() {
}

void UDPServer::run() {
	Console::printLine("UDPServer::run(): start");

	{
		// create start up barrier for io threads
		auto startUpBarrier = make_unique<Barrier>("nioudpserver_startup_workers", workerThreadPoolCount + 1);

		// setup worker thread pool
		workerThreadPool = make_unique<ServerWorkerThreadPool>(workerThreadPoolCount, workerThreadPoolMaxElements, startUpBarrier.get());
		workerThreadPool->start();

		// wait on startup barrier and delete it
		startUpBarrier->wait();
	}

	{
		// create start up barrier for IO threads
		auto startUpBarrier = make_unique<Barrier>("nioudpserver_startup_iothreads", ioThreadCount + 1);

		// create and start IO threads
		ioThreads.resize(ioThreadCount);
		for(auto i = 0; i < ioThreadCount; i++) {
			ioThreads[i] = make_unique<UDPServerIOThread>(i, this, (int)Math::ceil((float)maxCCU / (float)ioThreadCount), startUpBarrier.get());
			ioThreads[i] ->start();
		}

		// wait on startup barrier and delete it
		startUpBarrier->wait();
	}

	// init worker thread pool
	//
	Console::printLine("UDPServer::run(): ready");

	// do main event loop, waiting until stop requested
	auto lastCleanUpClientsTime = Time::getCurrentMillis();
	auto lastCleanUpClientsSafeMessagesTime = Time::getCurrentMillis();
	while (isStopRequested() == false) {
		// start time
		auto now = Time::getCurrentMillis();

		// clean up clients
		if (now >= lastCleanUpClientsTime + 100L) {
			cleanUpClients();
			lastCleanUpClientsTime = now;
		}

		//	iterate over clients and clean up safe messages
		if (now >= lastCleanUpClientsSafeMessagesTime + 100L) {
			auto _clientKeySet = getClientKeySet();
			for (const auto& clientKey: _clientKeySet) {
				auto client = getClientByKey(clientKey);

				// skip on clients that have been gone
				if (client == nullptr) continue;

				// clean up safe messages
				client->cleanUpSafeMessages();

				// never forget to release ;)
				client->releaseReference();
			}
			lastCleanUpClientsSafeMessagesTime = now;
		}

		// duration
		auto duration = Time::getCurrentMillis() - now;

		// wait total of 100ms seconds before repeat
		if (duration < 100L) {
			sleep(100L - duration);
		}
	}

	// we stopped accept, now iterate over clients and close them
	auto _clientKeySet = getClientKeySet();
	for (const auto& clientKey: _clientKeySet) {
		auto client = getClientByKey(clientKey);
		// continue if gone already
		if (client == nullptr) continue;
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}

	// now stop io threads
	for(const auto& ioThread: ioThreads) {
		ioThread->stop();
		ioThread->join();
	}
	ioThreads.clear();

	// stop thread pool
	workerThreadPool->stop();
	workerThreadPool = nullptr;

	//
	Console::printLine("UDPServer::run(): done");
}

UDPServerClient* UDPServer::accept(const uint32_t clientId, const std::string& ip, const uint16_t port) {
	return nullptr;
}

void UDPServer::identify(const UDPPacket* packet, MessageType& messageType, uint32_t& connectionId, uint32_t& messageId, uint8_t& retries) {
	// format 1char_message_type,6_char_connection_id,6_char_message_id,1_char_retries
	char inMessageType;
	char inConnectionId[6];
	char inMessageId[6];
	char inRetries[1];

	// check if enough data available
	if (packet->getSize() <
		sizeof(inMessageType) +
		sizeof(inConnectionId) +
		sizeof(inMessageId) +
		sizeof(inRetries)) {
		throw NetworkServerException("Invalid message header size");
	}

	// check message type
	inMessageType = packet->getByte();
	switch(inMessageType) {
		case('C'):
			messageType = MESSAGETYPE_CONNECT;
			break;
		case('M'):
			messageType = MESSAGETYPE_MESSAGE;
			break;
		case('A'):
			messageType = MESSAGETYPE_ACKNOWLEDGEMENT;
			break;
		default:
			throw NetworkServerException("Invalid message type");
	}

	// connection id
	packet->getBytes((uint8_t*)&inConnectionId, sizeof(inConnectionId));
	if (Integer::viewDecode(string_view(inConnectionId, sizeof(inConnectionId)), connectionId) == false) {
		throw NetworkServerException("Invalid connection id");
	}

	// decode message id
	packet->getBytes((uint8_t*)&inMessageId, sizeof(inMessageId));
	if (Integer::viewDecode(string_view(inMessageId, sizeof(inMessageId)), messageId) == false) {
		throw NetworkServerException("Invalid message id");
	}

	// decode retries
	packet->getBytes((uint8_t*)&inRetries, sizeof(inRetries));
	uint32_t _retries;
	if (Integer::viewDecode(string_view(inRetries, sizeof(inRetries)), _retries) == false) {
		throw NetworkServerException("Invalid retries");
	}
	retries = _retries;
}

void UDPServer::validate(const UDPPacket* packet) {
}

void UDPServer::initializeHeader(UDPPacket* packet) {
	// 14(messagetype, clientid, messageid, retries)
	uint8_t emptyHeader[14] =
		"\0\0\0\0\0\0\0\0\0\0"
		"\0\0\0";

	packet->putBytes(emptyHeader, sizeof(emptyHeader));
}

void UDPServer::writeHeader(UDPPacket* packet, MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries) {
	// store current position which should be end of packet
	auto position = packet->getPosition();
	// reset position to be able to write header
	packet->reset();

	// message type
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
			packet->putByte('C');
			break;
		case(MESSAGETYPE_MESSAGE):
			packet->putByte('M');
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			packet->putByte('A');
			break;
		default:
			delete packet;
			throw NetworkServerException("Invalid message type");
	}

	// client id
	string clientIdEncoded;
	Integer::encode(clientId, clientIdEncoded);

	// message id
	string messageIdEncoded;
	Integer::encode(messageId, messageIdEncoded);

	// retries
	string retriesEncoded;
	Integer::encode((uint32_t)retries, retriesEncoded);

	// put to packet
	packet->putBytes((const uint8_t*)clientIdEncoded.data(), clientIdEncoded.size());
	packet->putBytes((const uint8_t*)messageIdEncoded.data(), messageIdEncoded.size());
	packet->putByte(retriesEncoded[retriesEncoded.size() - 1]);

	// restore position to end of stream
	packet->setPosition(position);
}

void UDPServer::addClient(UDPServerClient* client) {
	auto clientId = client->clientId;

	//
	clientIdMapReadWriteLock.writeLock();

	if (clientIdMap.size() >= maxCCU) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("too many clients");
	}

	// check if client id was mapped already?
	auto clientIdMapIt = clientIdMap.find(clientId);
	if (clientIdMapIt != clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("client id is already mapped");
	}

	// prepare client struct for map
	auto _clientId = new ClientId();
	_clientId->clientId = clientId;
	_clientId->client = client;
	_clientId->time = Time::getCurrentMillis();

	// put to map
	clientIdMap[clientId] = _clientId;

	// put to client ip set
	clientIpMapReadWriteLock.writeLock();

	// check if ip exists already?
	string clientIp = client->getIp() + ":" + to_string(client->getPort());
	auto clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt != clientIpMap.end()) {
		// should actually never happen
		clientIpMapReadWriteLock.unlock();
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("client ip is already registered");
	}

	// put to map
	clientIpMap[clientIp] = client;

	///
	clientIpMapReadWriteLock.unlock();

	// reference counter +1
	client->acquireReference();

	// unlock
	clientIdMapReadWriteLock.unlock();
}

void UDPServer::removeClient(UDPServerClient* client) {
	uint32_t clientId = client->clientId;

	//
	clientIdMapReadWriteLock.writeLock();

	// check if client id was mapped already?
	auto clientIdMapit = clientIdMap.find(clientId);
	if (clientIdMapit == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("client id is not mapped");
	}

	// remove from client id map
	delete clientIdMapit->second;
	clientIdMap.erase(clientIdMapit);

	// remove from client ip set
	clientIpMapReadWriteLock.writeLock();

	// check if ip exists already?
	auto clientIp = client->getIp() + ":" + to_string(client->getPort());
	auto clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt == clientIpMap.end()) {
		// should actually never happen
		clientIpMapReadWriteLock.unlock();
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("client ip is not registered");
	}

	// remove from ip map
	clientIpMap.erase(clientIpMapIt);

	//
	clientIpMapReadWriteLock.unlock();

	// reference counter -1
	client->releaseReference();

	// unlock
	clientIdMapReadWriteLock.unlock();
}

UDPServerClient* UDPServer::lookupClient(const uint32_t clientId) {
	UDPServerClient* client = nullptr;

	//
	clientIdMapReadWriteLock.readLock();

	// check if client id was mapped already?
	auto it = clientIdMap.find(clientId);
	if (it == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NetworkServerException("client does not exist");
	}

	// get client
	auto _client = it->second;
	//	update last access time
	_client->time = Time::getCurrentMillis();
	//	get client
	client = _client->client;

	//
	client->acquireReference();

	// unlock
	clientIdMapReadWriteLock.unlock();

	//
	return client;
}

UDPServerClient* UDPServer::getClientByIp(const string& ip, const uint16_t port) {
	UDPServerClient* client = nullptr;
	clientIpMapReadWriteLock.readLock();
	auto clientIp = ip + ":" + to_string(port);
	auto clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt != clientIpMap.end()) {
		client = clientIpMapIt->second;
		client->acquireReference();
	}
	clientIpMapReadWriteLock.unlock();
	return client;
}

void UDPServer::cleanUpClients() {
	ClientSet clientCloseList;

	// determine clients that are idle or beeing flagged to be shut down
	clientIdMapReadWriteLock.readLock();

	auto now = Time::getCurrentMillis();
	for (const auto& [clientId, client]: clientIdMap) {
		if (client->client->shutdownRequested == true ||
			client->time < now - CLIENT_CLEANUP_IDLETIME) {

			// acquire reference for worker
			client->client->acquireReference();

			// mark for beeing closed
			clientCloseList.insert(client->client);
		}
	}

	//
	clientIdMapReadWriteLock.unlock();

	// erase clients
	for (auto client: clientCloseList) {
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}
}

void UDPServer::sendMessage(const UDPServerClient* client, UDPPacket* packet, const bool safe, const bool deleteFrame, const MessageType messageType, const uint32_t messageId) {
	// determine message id by message type
	uint32_t _messageId;
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
		case(MESSAGETYPE_MESSAGE):
			_messageId = AtomicOperations::increment(messageCount);
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			_messageId = messageId;
			break;
		default:
			delete packet;
			throw NetworkServerException("Invalid message type");
	}

	unsigned int threadIdx = _messageId % ioThreads.size();
	writeHeader(packet, messageType, client->clientId, _messageId, 0);
	ioThreads[threadIdx]->sendMessage(client, (uint8_t)messageType, _messageId, packet, safe, deleteFrame);
}

void UDPServer::processAckReceived(UDPServerClient* client, const uint32_t messageId) {
	unsigned int threadIdx = messageId % ioThreads.size();
	ioThreads[threadIdx]->processAckReceived(client, messageId);
}

const uint32_t UDPServer::allocateClientId() {
	return AtomicOperations::increment(clientCount);
}

const UDPServer::UDPServer_Statistics UDPServer::getStatistics() {
	auto stats = statistics;
	statistics.time = Time::getCurrentMillis();
	statistics.received = 0;
	statistics.sent = 0;
	statistics.accepts = 0;
	statistics.errors = 0;
	// determine clients that are idle or beeing flagged to be shut down
	clientIdMapReadWriteLock.readLock();
	stats.clients = clientIdMap.size();
	clientIdMapReadWriteLock.unlock();
	return stats;
}
