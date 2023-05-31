#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/network/udp/UDPPacket.h>
#include <tdme/network/udpserver/ServerClientRequestHandler.h>
#include <tdme/network/udpserver/ServerClientRequestHandlerHub.h>
#include <tdme/network/udpserver/UDPServer.h>
#include <tdme/network/udpserver/UDPServerClient.h>
#include <tdme/utilities/Exception.h>

#include "UDPServerTest_UDPServerClient.h"

using std::string;

using tdme::network::udp::UDPPacket;
using tdme::network::udpserver::ServerClientRequestHandler;
using tdme::network::udpserver::ServerClientRequestHandlerHub;
using tdme::network::udpserver::UDPServer;
using tdme::network::udpserver::UDPServerClient;
using tdme::utilities::Exception;

class CRHShutdown final: public ServerClientRequestHandler<UDPServerClient,string> {
public:
	CRHShutdown();

	virtual ~CRHShutdown();

	void handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class CRHDefault final: public ServerClientRequestHandler<UDPServerClient,string> {
public:
	CRHDefault();

	virtual ~CRHDefault();

	void handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class EchoUDPServer final: public UDPServer {
	friend class EchoUDPServerClient;
public:
	EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU);

	virtual ~EchoUDPServer();
protected:
	UDPServerClient* accept(const uint32_t clientId, const string& ip, const uint16_t port);

	ServerClientRequestHandlerHub<UDPServerClient,string> requestHandlerHub;
};
