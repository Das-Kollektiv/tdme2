#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>
#include <tdme/network/udpserver/NIOServerClientRequestHandler.h>
#include <tdme/network/udpserver/NIOServerClientRequestHandlerHub.h>
#include <tdme/utilities/Exception.h>

#include "UDPServerTest_UDPServerClient.h"

using std::string;

using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerClient;
using tdme::network::udpserver::NIOServerClientRequestHandler;
using tdme::network::udpserver::NIOServerClientRequestHandlerHub;
using tdme::utilities::Exception;

class CRHShutdown : public NIOServerClientRequestHandler<NIOUDPServerClient,string> {
public:
	CRHShutdown();

	virtual ~CRHShutdown();

	void handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class CRHDefault : public NIOServerClientRequestHandler<NIOUDPServerClient,string> {
public:
	CRHDefault();

	virtual ~CRHDefault();

	void handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries);
};

class EchoUDPServer : public NIOUDPServer {
	friend class EchoUDPServerClient;
public:
	EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU);

	virtual ~EchoUDPServer();
protected:
	NIOUDPServerClient* accept(const uint32_t clientId, const string& ip, const unsigned int port);

	NIOServerClientRequestHandlerHub<NIOUDPServerClient,string> requestHandlerHub;
};
