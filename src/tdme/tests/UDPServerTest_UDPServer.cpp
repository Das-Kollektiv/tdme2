#include "UDPServerTest_UDPServer.h"

#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/StringConverter.h>

using std::string;
using std::to_wstring;
using std::wstring;

using tdme::utils::Console;
using tdme::utils::Exception;

CRHShutdown::CRHShutdown() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/shutdown") {}

CRHShutdown::~CRHShutdown() {
}

void CRHShutdown::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (Exception) {
	// exit here if already processed
	if (client->processSafeMessage(messageId) == false) {
		return;
	}

	// otherwise request shutdown
	Console::println(L"received /shutdown, shutting down client");
	client->shutdown();
}

CRHDefault::CRHDefault() : NIOServerClientRequestHandler<NIOUDPServerClient,string>("/default") {}

CRHDefault::~CRHDefault() {
}

void CRHDefault::handleRequest(NIOUDPServerClient *client, string& data, const uint32_t messageId, const uint8_t retries) throw (Exception) {
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
	Console::println(L"Starting echo udp server @ " + StringConverter::toWideString(host) + L":" + to_wstring(port));
	Console::println();
	setIOThreadCount(2);
	setWorkerThreadCount(8);
	requestHandlerHub.addHandler(new CRHShutdown());
	requestHandlerHub.setDefaultHandler(new CRHDefault());
}

EchoUDPServer::~EchoUDPServer() {
}

NIOUDPServerClient* EchoUDPServer::accept(const uint32_t clientId, const std::string& ip, const unsigned int port) {
	Console::println(L"accepting client connection with '" + StringConverter::toWideString(ip) + L":" + to_wstring(port) + L"'");

	// create client
	EchoUDPServerClient* client = new EchoUDPServerClient(clientId, ip, port);

	//
	return client;
}
