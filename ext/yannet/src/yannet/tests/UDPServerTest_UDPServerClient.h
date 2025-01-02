#pragma once

#include <sstream>

#include <yannet/yannet.h>
#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>
#include <yannet/utilities/Exception.h>

#include "UDPServerTest_UDPServer.h"

using std::stringstream;

using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::UDPServer;
using yannet::network::udpserver::UDPServerClient;
using yannet::utilities::Exception;

class EchoUDPServerClient final: public UDPServerClient {
	friend class EchoUDPServer;

public:
	// forbid class copy
	FORBID_CLASS_COPY(EchoUDPServerClient)

	//
	EchoUDPServerClient(const uint32_t clientId, const std::string& ip, const uint16_t port);

protected:
	virtual ~EchoUDPServerClient();

	virtual void onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries);

	void onInit();
	void onClose();
	void onCustom(const string& type);
};
