#pragma once

#include <string>


#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/UDPServerClient.h>

#include "UDPServerTest_UDPServer.h"

using std::string;

using yannet::network::udpserver::UDPPacket;
using yannet::network::udpserver::UDPServerClient;

class EchoUDPServerClient final: public UDPServerClient {
	friend class EchoUDPServer;

public:
	// forbid class copy
	FORBID_CLASS_COPY(EchoUDPServerClient)

	//
	EchoUDPServerClient(const uint32_t clientId, const string& ip, const uint16_t port);

protected:
	virtual ~EchoUDPServerClient();

	virtual void onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries);

	void onInit();
	void onClose();
	void onCustom(const string& type);
};
