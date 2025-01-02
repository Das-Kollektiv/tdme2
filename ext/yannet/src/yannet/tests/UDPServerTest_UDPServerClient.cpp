#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <yannet/yannet.h>
#include <yannet/utilities/Console.h>
#include <yannet/utilities/Exception.h>

using std::endl;
using std::string;
using std::to_string;

using yannet::utilities::Console;
using yannet::utilities::Exception;

EchoUDPServerClient::EchoUDPServerClient(const uint32_t clientId, const string& ip, const uint16_t port) :
	UDPServerClient(clientId, ip, port) {
}

EchoUDPServerClient::~EchoUDPServerClient() {
}

void EchoUDPServerClient::onRequest(const UDPPacket* packet, const uint32_t messageId, const uint8_t retries) {
	auto command = packet->getString();

	// do the handler logic
	static_cast<EchoUDPServer*>(server)->requestHandlerHub.handleRequest(
		this,
		command,
		command,
		messageId,
		retries
	);
}

void EchoUDPServerClient::onInit() {
	Console::printLine("initiated connection with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}

void EchoUDPServerClient::onClose() {
	Console::printLine("closed connection with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}

void EchoUDPServerClient::onCustom(const string& type) {
	Console::printLine("custom event '" + (type) + "' with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}
