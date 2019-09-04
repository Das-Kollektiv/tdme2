#include "UDPServerTest_UDPServer.h"

#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;
using std::to_string;
using std::string;

using tdme::utils::Console;
using tdme::utils::Exception;

CRHShutdown::CRHShutdown() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/shutdown") {}

CRHShutdown::~CRHShutdown() {
}

void CRHShutdown::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise request shutdown
	Console::println("received /shutdown, shutting down client");
	client->shutdown();
}

CRHDefault::CRHDefault() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/default") {}

CRHDefault::~CRHDefault() {
}

void CRHDefault::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise echo the input
	stringstream* outFrame = client->createFrame();
	*outFrame << data;
	client->send(outFrame, true);
}

EchoUDPServer::EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU) : NIOUDPServer("echo", host, port, maxCCU) {
	Console::println("Starting echo udp server @ " + (host) + ":" + to_string(port));
	Console::println();
	setIOThreadCount(2);
	setWorkerThreadCount(8);
	requestHandlerHub.addHandler(new CRHShutdown());
	requestHandlerHub.setDefaultHandler(new CRHDefault());
}

EchoUDPServer::~EchoUDPServer() {
}

NIOUDPServerClient* EchoUDPServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	Console::println("accepting client connection with '" + (ip) + ":" + to_string(port) + "'");

	// create client
	EchoUDPServerClient* client = new EchoUDPServerClient(clientId, ip, port);

	//
	return client;
}
