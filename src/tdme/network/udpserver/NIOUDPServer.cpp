/**
 * @version $Id: baf35fe106f82d8bd3b13366cbf9d28daba32aed $
 */
#if defined(_WIN32) && defined(_MSC_VER)
	#include <windows.h>
#endif

#include <math.h>

#include <sstream>
#include <string>
#include <typeinfo>
#include <exception>

#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerIOThread.h>
#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/IntEncDec.h>
#include <tdme/utils/RTTI.h>
#include <tdme/utils/Time.h>

using std::ios_base;
using std::string;
using std::stringstream;
using std::to_string;

using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerIOThread;
using tdme::os::threading::Thread;
using tdme::os::threading::Barrier;
using tdme::os::threading::ReadWriteLock;
using tdme::utils::Console;
using tdme::utils::IntEncDec;
using tdme::utils::RTTI;
using tdme::utils::Time;

NIOUDPServer::NIOUDPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU) :
	NIOServer<NIOUDPServerClient, NIOUDPServerGroup>(name, host, port, maxCCU),
	Thread("nioudpserver"),
	clientIdMapReadWriteLock("nioudpserver_clientidmap"),
	clientIpMapReadWriteLock("nioudpserver_clientipmap"),
	ioThreadCurrent(0),
	ioThreads(NULL),
	workerThreadPool(NULL),
	clientCount(0),
	messageCount(0) {
	//
}

NIOUDPServer::~NIOUDPServer() {
}

void NIOUDPServer::run() {
	Console::println("NIOUDPServer::run(): start");

	// create start up barrier for io threads
	startUpBarrier = new Barrier("nioudpserver_startup_iothreads", ioThreadCount + 1);

	// create and start IO threads
	ioThreads = new NIOUDPServerIOThread*[ioThreadCount];
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i] = new NIOUDPServerIOThread(i, this, (int)ceil((float)maxCCU / (float)ioThreadCount));
		ioThreads[i] ->start();
	}

	// wait on startup barrier and delete it
	startUpBarrier->wait();
	delete startUpBarrier;
	startUpBarrier = NULL;

	// init worker thread pool
	startUpBarrier = new Barrier("nioudpserver_startup_workers", workerThreadPoolCount + 1);

	// setup worker thread pool
	workerThreadPool = new NIOServerWorkerThreadPool(startUpBarrier, workerThreadPoolCount, workerThreadPoolMaxElements);
	workerThreadPool->start();

	// wait on startup barrier and delete it
	startUpBarrier->wait();
	delete startUpBarrier;
	startUpBarrier = NULL;

	//
	Console::println("NIOUDPServer::run(): ready");

	// do main event loop, waiting until stop requested
	uint64_t lastCleanUpClientsTime = Time::getCurrentMillis();
	uint64_t lastCleanUpClientsSafeMessagesTime = Time::getCurrentMillis();
	while(isStopRequested() == false) {
		// start time
		uint64_t now = Time::getCurrentMillis();

		// clean up clients
		if (now >= lastCleanUpClientsTime + 100L) {
			cleanUpClients();
			lastCleanUpClientsTime = now;
		}

		//	iterate over clients and clean up safe messages
		if (now >= lastCleanUpClientsSafeMessagesTime + 100L) {
			ClientKeySet _clientKeySet = getClientKeySet();
			for (ClientKeySet::iterator i = _clientKeySet.begin(); i != _clientKeySet.end(); ++i) {
				NIOUDPServerClient* client = getClientByKey(*i);

				// skip on clients that have been gone
				if (client == NULL) continue;

				// clean up safe messages
				client->cleanUpSafeMessages();

				// never forget to release ;)
				client->releaseReference();
			}
			lastCleanUpClientsSafeMessagesTime = now;
		}

		// duration
		uint64_t duration = Time::getCurrentMillis() - now;

		// wait total of 100ms seconds before repeat
		if (duration < 100L) {
			sleep(100L - duration);
		}
	}

	// we stopped accept, now stop io threads, but leave them intact
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		ioThreads[i]->stop();
		ioThreads[i]->join();
	}

	//	iterate over clients and close them
	ClientKeySet _clientKeySet = getClientKeySet();
	for (ClientKeySet::iterator i = _clientKeySet.begin(); i != _clientKeySet.end(); ++i) {
		NIOUDPServerClient* client = getClientByKey(*i);
		// continue if gone already
		if (client == NULL) continue;
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}

	// stop thread pool
	workerThreadPool->stop();
	delete workerThreadPool;
	workerThreadPool = NULL;

	// delete io threads
	for(unsigned int i = 0; i < ioThreadCount; i++) {
		delete ioThreads[i];
	}
	delete [] ioThreads;
	ioThreads = NULL;

	//
	Console::println("NIOUDPServer::run(): done");
}

NIOUDPServerClient* NIOUDPServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	return NULL;
}

void NIOUDPServer::identify(stringstream* frame, MessageType& messageType, uint32_t& connectionId, uint32_t& messageId, uint8_t& retries) throw (NIONetworkServerException) {
	// format 1char_message_type,6_char_connection_id,6_char_message_id,1_char_retries
	char inMessageType;
	char inConnectionId[6];
	char inMessageId[6];
	char inRetries[1];

	// check if enough data available
	if ((unsigned int)frame->tellp() - (unsigned int)frame->tellg() <
		sizeof(inMessageType) +
		sizeof(inConnectionId) +
		sizeof(inMessageId) +
		sizeof(inRetries)) {
		throw NIONetworkServerException("Invalid message header size");
	}

	// check message type
	frame->read((char*)&inMessageType, sizeof(inMessageType));
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
			throw NIONetworkServerException("Invalid message type");
	}

	// connection id
	string strConnectionId;
	frame->read((char*)&inConnectionId, sizeof(inConnectionId));
	strConnectionId.append(inConnectionId, sizeof(inConnectionId));
	if (IntEncDec::decodeInt(strConnectionId, connectionId) == false) {
		throw NIONetworkServerException("Invalid connection id");
	}

	// decode message id
	string strMessageId;
	frame->read((char*)&inMessageId, sizeof(inMessageId));
	strMessageId.append(inMessageId, sizeof(inMessageId));
	if (IntEncDec::decodeInt(strMessageId, messageId) == false) {
		throw NIONetworkServerException("Invalid message id");
	}

	// decode retries
	string strRetries;
	frame->read((char*)&inRetries, sizeof(inRetries));
	strRetries.append(inRetries, sizeof(inRetries));
	uint32_t _retries;
	if (IntEncDec::decodeInt(strRetries, _retries) == false) {
		throw NIONetworkServerException("Invalid retries");
	}
	retries = _retries;
}

void NIOUDPServer::validate(stringstream* frame) throw (NIONetworkServerException) {
}

void NIOUDPServer::initializeHeader(stringstream* frame) throw (NIONetworkServerException) {
	// 14(messagetype, clientid, messageid, retries)
	char emptyHeader[14] =
		"\0\0\0\0\0\0\0\0\0\0"
		"\0\0\0";

	frame->write(emptyHeader, sizeof(emptyHeader));

	// seek to end of stream
	frame->seekp(0, ios_base::end);
}

void NIOUDPServer::writeHeader(stringstream* frame, MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries) throw (NIONetworkServerException) {
	// seek writing to beginning of header
	frame->seekp(0, ios_base::beg);

	// message type
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
			*frame << "C";
			break;
		case(MESSAGETYPE_MESSAGE):
			*frame << "M";
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			*frame << "A";
			break;
		default:
			delete frame;
			throw NIONetworkServerException("Invalid message type");
	}

	// client id
	string strClientId;
	IntEncDec::encodeInt(clientId, strClientId);
	*frame << strClientId;

	// message id
	string strMessageId;
	IntEncDec::encodeInt(messageId, strMessageId);
	*frame << strMessageId;

	// retries
	string strRetriesId;
	IntEncDec::encodeInt((uint32_t)retries, strRetriesId);
	*frame << strRetriesId[strRetriesId.size() - 1];

	// seek writing to end of stream
	frame->seekp(0, ios_base::end);
}

void NIOUDPServer::addClient(NIOUDPServerClient* client) throw (NIONetworkServerException) {
	uint32_t clientId = client->clientId;

	// prepare client struct for map
	Client _client;
	_client.clientId = clientId;
	_client.client = client;
	_client.time = Time::getCurrentMillis();

	//
	clientIdMapReadWriteLock.writeLock();

	if (clientIdMap.size() >= maxCCU) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("too many clients");
	}

	// check if client id was mapped already?
	ClientIdMap::iterator clientIdMapIt = clientIdMap.find(clientId);
	if (clientIdMapIt != clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client id is already mapped");
	}

	// put to map
	clientIdMap[clientId] = _client;

	// put to client ip set
	clientIpMapReadWriteLock.writeLock();

	// check if ip exists already?
	string clientIp = client->getIp() + ":" + to_string(client->getPort());
	ClientIpMap::iterator clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt != clientIpMap.end()) {
		// should actually never happen
		clientIpMapReadWriteLock.unlock();
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client ip is already registered");
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

void NIOUDPServer::removeClient(NIOUDPServerClient* client) throw (NIONetworkServerException) {
	uint32_t clientId = client->clientId;

	//
	clientIdMapReadWriteLock.writeLock();

	// check if client id was mapped already?
	ClientIdMap::iterator clientIdMapit = clientIdMap.find(clientId);
	if (clientIdMapit == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client id is not mapped");
	}

	// remove from map
	clientIdMap.erase(clientIdMapit);

	// remove from client ip set
	clientIpMapReadWriteLock.writeLock();

	// check if ip exists already?
	string clientIp = client->getIp() + ":" + to_string(client->getPort());
	ClientIpMap::iterator clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt == clientIpMap.end()) {
		// should actually never happen
		clientIpMapReadWriteLock.unlock();
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client ip is not registered");
	}

	// put to map
	clientIpMap.erase(clientIpMapIt);

	//
	clientIpMapReadWriteLock.unlock();

	// reference counter -1
	client->releaseReference();

	// unlock
	clientIdMapReadWriteLock.unlock();
}

NIOUDPServerClient* NIOUDPServer::lookupClient(const uint32_t clientId) throw (NIONetworkServerException) {
	NIOUDPServerClient* client = NULL;
	ClientIdMap::iterator it;

	//
	clientIdMapReadWriteLock.readLock();

	// check if client id was mapped already?
	it = clientIdMap.find(clientId);
	if (it == clientIdMap.end()) {
		// should actually never happen
		clientIdMapReadWriteLock.unlock();

		// failure
		throw NIONetworkServerException("client does not exist");
	}

	// get client
	Client* _client = &it->second;
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

NIOUDPServerClient* NIOUDPServer::getClientByIp(const string& ip, const unsigned int port) {
	NIOUDPServerClient* client = NULL;
	clientIpMapReadWriteLock.readLock();
	string clientIp = ip + ":" + to_string(port);
	ClientIpMap::iterator clientIpMapIt = clientIpMap.find(clientIp);
	if (clientIpMapIt != clientIpMap.end()) {
		client = clientIpMapIt->second;
		client->acquireReference();
	}
	clientIpMapReadWriteLock.unlock();
	return client;
}

void NIOUDPServer::cleanUpClients() {
	ClientSet clientCloseList;

	// determine clients that are idle or beeing flagged to be shut down
	clientIdMapReadWriteLock.readLock();

	uint64_t now = Time::getCurrentMillis();
	for(ClientIdMap::iterator it = clientIdMap.begin(); it != clientIdMap.end(); ++it) {
		Client *client = &it->second;
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
	for (ClientSet::iterator it = clientCloseList.begin(); it != clientCloseList.end(); ++it) {
		NIOUDPServerClient* client = *it;
		// client close logic
		client->close();
		// remove from udp client list
		removeClient(client);
	}
}

void NIOUDPServer::sendMessage(const NIOUDPServerClient* client, stringstream* frame, const bool safe, const bool deleteFrame, const MessageType messageType, const uint32_t messageId) throw (NIONetworkServerException) {
	// determine message id by message type
	uint32_t _messageId;
	switch(messageType) {
		case(MESSAGETYPE_CONNECT):
		case(MESSAGETYPE_MESSAGE):
			#if defined(_WIN32) && defined(_MSC_VER)
				_messageId = InterlockedIncrement(&messageCount);
			#else
				_messageId = __sync_add_and_fetch(&messageCount, 1);
			#endif
			break;
		case(MESSAGETYPE_ACKNOWLEDGEMENT):
			_messageId = messageId;
			break;
		default:
			delete frame;
			throw NIONetworkServerException("Invalid message type");
	}

	unsigned int threadIdx = _messageId % ioThreadCount;
	writeHeader(frame, messageType, client->clientId, _messageId, 0);
	ioThreads[threadIdx]->sendMessage(client, (uint8_t)messageType, _messageId, frame, safe, deleteFrame);
}

void NIOUDPServer::processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException) {
	unsigned int threadIdx = messageId % ioThreadCount;
	ioThreads[threadIdx]->processAckReceived(client, messageId);
}

const uint32_t NIOUDPServer::allocateClientId() {
	#if defined(_WIN32) && defined(_MSC_VER)
		uint32_t clientId = InterlockedIncrement(&clientCount);
	#else
		uint32_t clientId = __sync_add_and_fetch(&clientCount, 1);
	#endif
	return clientId;
}
