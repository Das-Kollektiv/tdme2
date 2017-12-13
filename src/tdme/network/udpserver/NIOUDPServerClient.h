#pragma once

#include <stdint.h>

#include <exception>
#include <string>
#include <sstream>
#include <map>

#include <tdme/utils/Exception.h>
#include <tdme/utils/ReferenceCounter.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/network/NIOException.h>
#include <tdme/network/udpserver/NIOServerClient.h>
#include <tdme/network/udpserver/NIONetworkServerException.h>
#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerIOThread.h>

using std::map;

using tdme::utils::Exception;
using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerIOThread;

/**
 * Base class for NIO tcp server clients
 * @author Andreas Drewke
 */
class tdme::network::udpserver::NIOUDPServerClient : public NIOServerClient {
	friend class NIOUDPServer;
	friend class NIOUDPServerIOThread;

public:
	/**
	 * @brief public constructor should be called in any subclass of NIOUDPNetworkServer
	 * @param client id
	 * @param ip
	 * @param port
	 */
	NIOUDPServerClient(const uint32_t clientId, const std::string& ip, const unsigned int port);

	/**
	 * @brief Returns server
	 * @return server
	 */
	NIOUDPServer* getServer();

	/**
	 * @brief Get client id
	 * @return client id
	 */
	const uint32_t getClientId();

	/**
	 * @brief returns client's ip
	 * @return client ip
	 */
	const string& getIp() const;

	/**
	 * @brief returns client port
	 * @return client port
	 */
	const unsigned int getPort() const;

	/**
	 * @brief Client identification key
	 * @return client key
	 */
	const string& getKey() const;

	/**
	 * @brief sets the clients identification key
	 * @param client identification key
	 * @return if setting the key was succesful
	 */
	const bool setKey(const string &key);

	/**
	 * @brief Creates a frame to be used with send
	 * @return frame to be send
	 */
	static stringstream* createFrame();

	/**
	 * @brief Sends a frame to client, takes over ownership of frame
	 * @param frame data
	 * @param safe, requires ack and retransmission
	 * @param delete frame
	 */
	void send(stringstream* frame, bool safe = true, bool deleteFrame = true);

	/**
	 * @brief Checks if message has already been processed and sends an acknowlegdement to client / safe client messages
	 * @param message id
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
	 * @brief public destructor, should only be called implicitly by ReferenceCounter::releaseReference()
	 */
	virtual ~NIOUDPServerClient();

	/**
	 * @brief To be overwritten with a request handler, will be called from worker
	 * @param frame
	 * @param message id
	 * @param retries
	 */
	virtual void onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (Exception) = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() throw (Exception) = 0;

	/**
	 * @brief Event, which will be called if frame has been received, defaults to worker thread pool
	 * @param frame
	 * @param message id (upd server only)
	 * @param retries (udp server only)
	 */
	virtual void onFrameReceived(stringstream* frame, const uint32_t messageId = 0, const uint8_t retries = 0);

	/**
	 * @brief Shuts down this network client
	 */
	void close();

	/**
	 * @brief initiates this network client
	 */
	void init();

	//
	NIOUDPServer* server;
	NIOUDPServerIOThread* ioThread;
	uint32_t clientId;
	std::string ip;
	unsigned int port;

private:
	static const uint64_t MESSAGESSAFE_KEEPTIME = 5000L;
	struct Message {
		uint32_t messageId;
		uint64_t time;
		uint8_t receptions;
	};
	typedef map<uint32_t, Message> MessageMapSafe;

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
