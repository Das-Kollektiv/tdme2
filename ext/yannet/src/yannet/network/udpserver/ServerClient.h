#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/ServerRequest.h>
#include <yannet/utilities/Exception.h>
#include <yannet/utilities/Reference.h>

using std::string;

// namespaces
namespace yannet {
namespace network {
namespace udpserver {
	using ::yannet::network::udp::UDPPacket;
	using ::yannet::utilities::Exception;
	using ::yannet::utilities::Reference;

	class ServerRequest;
};
};
};

/**
 * Base class for network server clients
 * @author Andreas Drewke
 */
class yannet::network::udpserver::ServerClient : public ::yannet::utilities::Reference {
	friend class ServerWorkerThread;

public:
	YANNET_STATIC_DLL_IMPEXT static const char* KEY_PREFIX_UNNAMED;

	/**
	 * @brief returns client's ip
	 * @return client ip
	 */
	virtual const string& getIp() const = 0;

	/**
	 * @brief returns client port
	 * @return client port
	 */
	virtual const uint16_t getPort() const = 0;

	/**
	 * @brief Client identification key
	 * @return client key
	 */
	virtual const string& getKey() const = 0;

	/**
	 * @brief sets the clients identification key
	 * @param &key client identification key
	 * @return if setting the key was succesful
	 */
	virtual const bool setKey(const string &key) = 0;

	/**
	 * @brief Creates a packet to be used with send
	 * @return packet to be send
	 */
	inline UDPPacket* createPacket() {
		return new UDPPacket();
	}

	/**
	 * @brief Shuts down this network client
	 */
	virtual void shutdown() = 0;

protected:
	/**
	 * @brief To be overwritten with a request handler, will be called from worker
	 * @param packet packet
	 * @param messageId message id (udp server only)
	 * @param retries retries (udp server only)
	 */
	virtual void onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries) = 0;

	/*
	 * @brief event method called if client will be initiated, will be called from worker
	 */
	virtual void onInit() = 0;

	/*
	 * @brief event method called if client will be closed, will be called from worker
	 */
	virtual void onClose() = 0;

	/*
	 * @brief custom event method called if fired, will be called from worker
	 */
	virtual void onCustom(const string& type) = 0;

	/**
	 * @brief Event, which will be called if packet has been received, defaults to worker thread pool
	 * @param packet packet
	 * @param messageId message id (upd server only)
	 * @param retries retries (udp server only)
	 */
	virtual void onPacketReceived(const UDPPacket* packet, const uint32_t messageId = 0, const uint8_t retries = 0) = 0;

	/**
	 * @brief Shuts down this network client
	 */
	virtual void close() = 0;

	//
	string key;
};

