#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationServer.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Exception.h>

#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>

using std::string;
using std::vector;

using tdme::engine::logics::ApplicationServer;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::os::threading::Mutex;
using tdme::utilities::Exception;

using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::UDPServer;
using yannet::network::udpserver::UDPServerClient;

/**
 * Application server client
 */
class tdme::engine::logics::ApplicationServerClient: public UDPServerClient {
	friend class WSServer;

public:
	// forbid class copy
	FORBID_CLASS_COPY(ApplicationServerClient)

	/**
	 * Public constructor
	 * @param clientId client id
	 * @param ip ip
	 * @param port port
	 */
	ApplicationServerClient(const uint32_t clientId, const string& ip, const unsigned int port);

	/**
	 * @returns incoming network packets mutex
	 */
	Mutex& getNetworkPacketsMutex();

	/**
	 * @returns incoming network packets
	 */
	vector<LogicNetworkPacket>& getNetworkPackets();

protected:
	/**
	 * Destructor
	 */
	virtual ~ApplicationServerClient();

	/**
	 * On request
	 * @param packet packet
	 * @param messageId message id
	 * @param retries retries
	 * @throws Exception
	 */
	void onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries);

	/**
	 * On init
	 * @throws Exception
	 */
	virtual void onInit();

	/**
	 * On close
	 * @throws Exception
	 */
	virtual void onClose();

	/**
	 * On custom
	 * @throws Exception
	 */
	virtual void onCustom(const string& type);

private:
	Mutex networkPacketsMutex;
	vector<LogicNetworkPacket> networkPackets;
};
