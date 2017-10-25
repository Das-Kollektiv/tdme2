#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>

using std::string;
using std::to_string;
using std::string;
using std::endl;

using tdme::utils::Console;
using tdme::utils::Exception;

EchoUDPServerClient::EchoUDPServerClient(const uint32_t clientId, const string& ip, const unsigned int port) :
	NIOUDPServerClient(clientId, ip, port) {
}

EchoUDPServerClient::~EchoUDPServerClient() {
	Console::println("EchoUDPServerClient::~EchoUDPServerClient()");
}

void EchoUDPServerClient::onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries) throw (Exception) {
	string command;
	char c;
	while(true) {
		// extract character from frame
		frame->get(c);

		// exit if eof
		if (frame->eof() == true) {
			break;
		}

		// no eof, add character to command
		command+= c;
	}

	// do the handler logic
	static_cast<EchoUDPServer*>(server)->requestHandlerHub.handleRequest(
		this,
		command,
		command,
		messageId,
		retries
	);
}

void EchoUDPServerClient::onInit() throw (Exception) {
	Console::println("initiated connection with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}

void EchoUDPServerClient::onClose() throw (Exception) {
	Console::println("closed connection with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}

void EchoUDPServerClient::onCustom(const string& type) throw (Exception) {
	Console::println("custom event '" + (type) + "' with '" + (getIp()) + ":" + to_string(getPort()) + "'");
}
