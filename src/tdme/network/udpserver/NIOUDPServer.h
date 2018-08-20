#pragma once

#include <stdint.h>

#include <sstream>
#include <string>
#include <map>
#include <set>

#include <tdme/network/udpserver/fwd-tdme.h>

#include <tdme/os/threading/Thread.h>
#include <tdme/os/threading/Barrier.h>
#include <tdme/os/threading/ReadWriteLock.h>
#include <tdme/network/udpserver/NIONetworkServerException.h>
#include <tdme/network/udpserver/NIOUDPServerIOThread.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>
#include <tdme/network/udpserver/NIOUDPServerGroup.h>
#include <tdme/network/udpserver/NIOServer.h>
#include <tdme/network/udpserver/NIOServerWorkerThreadPool.h>

using std::stringstream;

using tdme::os::threading::Thread;
using tdme::os::threading::Barrier;
using tdme::os::threading::ReadWriteLock;
using tdme::network::udpserver::NIONetworkServerException;
using tdme::network::udpserver::NIOUDPServerIOThread;
using tdme::network::udpserver::NIOUDPServerClient;
using tdme::network::udpserver::NIOUDPServerGroup;
using tdme::network::udpserver::NIOServer;
using tdme::network::udpserver::NIOServerWorkerThreadPool;

/**
 * Base class for NIO udp servers
 * @author Andreas Drewke
 */
class tdme::network::udpserver::NIOUDPServer: public NIOServer<NIOUDPServerClient, NIOUDPServerGroup>, public Thread {
	friend class NIOUDPServerClient;
	friend class NIOUDPServerIOThread;
	friend class NIOServerGroup<NIOUDPServer, NIOUDPServerClient, NIOUDPServerGroup>;

public:
	/**
	 * @brief Public constructor
	 * @param name server name
	 * @param host host where to bind the server socket
	 * @param port port to listen on
	 * @param maxCCU max ccu
	 */
	NIOUDPServer(const std::string& name, const std::string& host, const unsigned int port, const unsigned int maxCCU);

	/**
	 * @brief destructor
	 */
	virtual ~NIOUDPServer();

	/**
	 * main event loop
	 */
	virtual void run();

protected:
	enum MessageType {MESSAGETYPE_CONNECT = 0, MESSAGETYPE_MESSAGE = 1, MESSAGETYPE_ACKNOWLEDGEMENT = 2};

	/**
	 * @brief method to implement for accepting clients
	 * @param clientId client id
	 * @param ip ip
	 * @param port port
	 * @return server client class
	 */
	virtual NIOUDPServerClient* accept(const uint32_t clientId, const std::string& ip, const unsigned int port);

	/**
	 * Identifies a client message
	 * @param frame frame
	 * @param messageType message type (see NIOUDPServer::MessageType)
	 * @param connectionId connection id
	 * @param messageId message id
	 * @param retries retries
	 * @throws NIONetworkServerException
	 * @return client or NULL
	 */
	virtual void identify(stringstream* frame, MessageType& messageType, uint32_t& connectionId, uint32_t& messageId, uint8_t& retries) throw (NIONetworkServerException);

	/**
	 * Validates a client message
	 * @param frame frame
	 * @throws NIONetworkServerException
	 */
	virtual void validate(stringstream* frame) throw (NIONetworkServerException);

	/**
	 * Writes a empty header to message
	 * @param frame frame
	 * @throws NIONetworkServerException
	 */
	static void writeHeader(stringstream* frame) throw (NIONetworkServerException);

	/**
	 * Writes a message header to message
	 * @param frame frame
	 * @param messageType message type
	 * @param clientId client id
	 * @param messageId message id
	 * @param retries retries
	 * @throws NIONetworkServerException
	 */
	virtual void writeHeader(stringstream* frame, MessageType messageType, const uint32_t clientId, const uint32_t messageId, const uint8_t retries) throw (NIONetworkServerException);
private:
	static const uint64_t CLIENT_CLEANUP_IDLETIME = 120000L;
	struct Client {
		uint32_t clientId;
		NIOUDPServerClient* client;
		uint64_t time;
	};
	typedef std::map<uint32_t, Client> ClientIdMap;
	typedef std::map<string, NIOUDPServerClient*> ClientIpMap;
	typedef std::set<NIOUDPServerClient*> ClientSet;
	static const uint32_t MESSAGE_ID_NONE = 0;

	/**
	 * @brief maps a new client to a given client id
	 * @param client client
	 * @throws NIONetworkServerException if id is already in use
	 */
	void addClient(NIOUDPServerClient* client) throw (NIONetworkServerException);

	/**
	 * @brief removes a client
	 * @param client client
	 * @throws NIONetworkServerException if id is not in use
	 */
	void removeClient(NIOUDPServerClient* client) throw (NIONetworkServerException);

	/**
	 * @brief Look ups a client by client id
	 * @param clientId client id
	 * @throws NIONetworkServerException if client does not exist
	 * @return client
	 */
	NIOUDPServerClient* lookupClient(const uint32_t clientId) throw (NIONetworkServerException);

	/**
	 * @brief Returns client by host name and port
	 * @param ip ip
	 * @param port port
	 * @return client
	 */
	NIOUDPServerClient* getClientByIp(const string& ip, const unsigned int port);

	/**
	 * @brief Clean up clients that have been idle for some time or are flagged to be shut down
	 */
	void cleanUpClients();

	/**
	 * @brief pushes a message to be send, takes over ownership of frame
	 * @param client client
	 * @param frame frame to be send
	 * @param safe safe, requires ack and retransmission
	 * @param deleteFrame delete frame
	 * @param messageType message type
	 * @param messageId message id (only for MESSAGETYPE_MESSAGE)
	 * @throws NIONetworkServerException
	 */
	void sendMessage(const NIOUDPServerClient* client, stringstream* frame, const bool safe, const bool deleteFrame, const MessageType messageType, const uint32_t messageId = MESSAGE_ID_NONE) throw (NIONetworkServerException);

	/**
	 * @brief Processes an acknowlegdement reception
	 * @param client client
	 * @param messageId message id
	 */
	void processAckReceived(NIOUDPServerClient* client, const uint32_t messageId) throw (NIONetworkServerException);

	/**
	 * @brief Allocates a client id for a new client
	 * @return client id
	 */
	const uint32_t allocateClientId();

	//
	ClientIdMap clientIdMap;
	ReadWriteLock clientIdMapReadWriteLock;

	ClientIpMap clientIpMap;
	ReadWriteLock clientIpMapReadWriteLock;

	unsigned int ioThreadCurrent;
	NIOUDPServerIOThread** ioThreads;
	NIOServerWorkerThreadPool* workerThreadPool;

	uint32_t clientCount;
	uint32_t messageCount;
};

