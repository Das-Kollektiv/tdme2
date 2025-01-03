#pragma once

#include <string>
#include <unordered_map>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/ServerClient.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerIOThread.h>
#include <yannet/os/threading/Mutex.h>
#include <yannet/utilities/Reference.h>

using std::string;
using std::unordered_map;

// namespaces
namespace yannet {
namespace network {
namespace udpserver {
	using ::yannet::network::udp::UDPPacket;
	using ::yannet::network::udpserver::UDPServer;
	using ::yannet::network::udpserver::UDPServerIOThread;
	using ::yannet::os::threading::Mutex;
	using ::yannet::utilities::Exception;
}
}
}

/**
 * Base class for network UDP server clients
 * @author Andreas Drewke
 */
class yannet::network::udpserver::UDPServerClient : public ServerClient {
	friend class UDPServer;
	friend class UDPServerIOThread;

public:
	// forbid class copy
	FORBID_CLASS_COPY(UDPServerClient)

	/**
	 * @brief public constructor should be called in any subclass of UDPNetworkServer
	 * @param clientId client id
	 * @param ip ip
	 * @param port port
	 */
	UDPServerClient(const uint32_t clientId, const std::string& ip, const uint16_t port);

	/**
	 * @brief Returns server
	 * @return server
	 */
	UDPServer* getServer();

	/**
	 * @brief Get client id
	 * @return client id
	 */
	inline const uint32_t getClientId() {
		return clientId;
	}

	/**
	 * @brief returns client's ip
	 * @return client ip
	 */
	inline const string& getIp() const {
		return ip;
	}

	/**
	 * @brief returns client port
	 * @return client port
	 */
	inline const uint16_t getPort() const {
		return port;
	}

	/**
	 * @brief Client identification key
	 * @return client key
	 */
	inline const string& getKey() const {
		return key;
	}

	/**
	 * @brief sets the clients identification key
	 * @param &key client identification key
	 * @return if setting the key was succesful
	 */
	const bool setKey(const string &key);

	/**
	 * @brief Creates a packet to be used with send
	 * @return frame to be send
	 */
	static UDPPacket* createPacket();

	/**
	 * @brief Sends a frame to client, takes over ownership of frame
	 * @param packet packet to be send
	 * @param safe safe, requires ack and retransmission
	 * @param deleteFrame delete frame
	 */
	void send(UDPPacket* packet, bool safe = true, bool deleteFrame = true);

	/**
	 * @brief Checks if message has already been processed and sends an acknowlegdement to client / safe client messages
	 * @param messageId message id
	 */
	bool processSafeMessage(const uint32_t messageId);

	/**
	 * @return time passed until a retry was acknowledged
	 */
	uint64_t getRetryTime(const uint8_t retries);

	/**
	 * @brief fires an custom event
	 */
	void fireEvent(const string &type);

	/**
	 * @brief Shuts down this network client
	 */
	void shutdown();

protected:
	/**
	 * @brief public destructor, should only be called implicitly by Reference::releaseReference()
	 */
	virtual ~UDPServerClient();

	/**
	 * @brief To be overwritten with a request handler, will be called from worker
	 * @param packet packet
	 * @param messageId message id
	 * @param retries retries
	 */
	virtual void onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries) = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() = 0;

	/**
	 * @brief Event, which will be called if packet has been received, defaults to worker thread pool
	 * @param packet packet
	 * @param messageId message id (upd server only)
	 * @param retries retries (udp server only)
	 */
	virtual void onPacketReceived(const UDPPacket* packet, const uint32_t messageId = 0, const uint8_t retries = 0);

	/**
	 * @brief Shuts down this network client
	 */
	void close();

	/**
	 * @brief initiates this network client
	 */
	void init();

	//
	UDPServer* server;
	UDPServerIOThread* ioThread;
	uint32_t clientId;
	string ip;
	uint16_t port;

private:
	static const uint64_t MESSAGESSAFE_KEEPTIME = 5000L;
	struct Message {
		uint32_t messageId;
		uint64_t time;
		uint8_t receptions;
	};
	typedef unordered_map<uint32_t, Message*> MessageMapSafe;

	/**
	 * @brief Sends an connect message to client
	 */
	void sendConnected();

	/**
	 * @brief Clean up safe messages
	 */
	void cleanUpSafeMessages();

	//
	volatile bool shutdownRequested;
	Mutex messageMapSafeMutex;
	MessageMapSafe messageMapSafe;
};
