#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Exception.h>

#include <yannet/network/udp/UDPPacket.h>
#include <yannet/network/udpserver/ServerClientRequestHandler.h>
#include <yannet/network/udpserver/ServerClientRequestHandlerHub.h>
#include <yannet/network/udpserver/UDPServer.h>
#include <yannet/network/udpserver/UDPServerClient.h>

#include "UDPServerTest_UDPServerClient.h"

using std::string;

using tdme::utilities::Exception;

using yannet::network::udp::UDPPacket;
using yannet::network::udpserver::ServerClientRequestHandler;
using yannet::network::udpserver::ServerClientRequestHandlerHub;
using yannet::network::udpserver::UDPServer;
using yannet::network::udpserver::UDPServerClient;

class CRHShutdown final: public ServerClientRequestHandler<UDPServerClient,string> {
public:
	// forbid class copy
	FORBID_CLASS_COPY(CRHShutdown)

	//
	CRHShutdown();

	virtual ~CRHShutdown();

	void handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class CRHDefault final: public ServerClientRequestHandler<UDPServerClient,string> {
public:
	// forbid class copy
	FORBID_CLASS_COPY(CRHDefault)

	//
	CRHDefault();

	virtual ~CRHDefault();

	void handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class EchoUDPServer final: public UDPServer {
	friend class EchoUDPServerClient;
public:
	// forbid class copy
	FORBID_CLASS_COPY(EchoUDPServer)

	//
	EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU);

	virtual ~EchoUDPServer();
protected:
	UDPServerClient* accept(const uint32_t clientId, const string& ip, const uint16_t port);

	ServerClientRequestHandlerHub<UDPServerClient,string> requestHandlerHub;
};
