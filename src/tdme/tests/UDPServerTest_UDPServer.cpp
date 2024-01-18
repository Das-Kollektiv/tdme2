#include "UDPServerTest_UDPServer.h"

#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

using std::string;
using std::to_string;

using tdme::utilities::Console;
using tdme::utilities::Exception;

CRHShutdown::CRHShutdown() : ServerClientRequestHandler<UDPServerClient,string>("/shutdown") {}

CRHShutdown::~CRHShutdown() {
}

void CRHShutdown::handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise request shutdown
	Console::printLine("received /shutdown, shutting down client");
	client->shutdown();
}

CRHDefault::CRHDefault() : ServerClientRequestHandler<UDPServerClient,string>("/default") {}

CRHDefault::~CRHDefault() {
}

void CRHDefault::handleRequest(UDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise echo the input
	auto outPacket = client->createPacket();
	outPacket->putString(data);
	client->send(outPacket, true);
}

EchoUDPServer::EchoUDPServer(const string& host, const unsigned int port, const unsigned int maxCCU) : UDPServer("echo", host, port, maxCCU) {
	Console::printLine("Starting echo udp server @ " + (host) + ":" + to_string(port));
	Console::printLine();
	setIOThreadCount(2);
	setWorkerThreadCount(8);
	requestHandlerHub.addHandler(new CRHShutdown());
	requestHandlerHub.setDefaultHandler(new CRHDefault());
}

EchoUDPServer::~EchoUDPServer() {
}

UDPServerClient* EchoUDPServer::accept(const uint32_t clientId, const string& ip, const uint16_t port) {
	Console::printLine("accepting client connection with '" + (ip) + ":" + to_string(port) + "'");

	// create client
	return new EchoUDPServerClient(clientId, ip, port);
}
