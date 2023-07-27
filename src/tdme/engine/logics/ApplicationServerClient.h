#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/ApplicationServer.h>
#include <tdme/engine/logics/LogicNetworkPacket.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpserver/UDPServer.h>
#include <tdme/network/udpserver/UDPServerClient.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::vector;

using tdme::engine::logics::ApplicationServer;
using tdme::engine::logics::LogicNetworkPacket;
using tdme::network::udp::UDPPacket;
using tdme::network::udpserver::UDPServer;
using tdme::network::udpserver::UDPServerClient;
using tdme::os::threading::Mutex;
using tdme::utilities::Exception;

/**
 * Application server client
 */
class tdme::engine::logics::ApplicationServerClient: public UDPServerClient {
	friend class WSServer;

public:
	// forbid class copy
	CLASS_FORBID_COPY(ApplicationServerClient)

	/**
	 * Public constructor
	 * @param clientId client id
	 * @param ip ip
	 * @param port port
	 */
	ApplicationServerClient(const uint32_t clientId, const string& ip, const unsigned int port);

	/**
	 * @return incoming network packets mutex
	 */
	Mutex& getNetworkPacketsMutex();

	/**
	 * @return incoming network packets
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
