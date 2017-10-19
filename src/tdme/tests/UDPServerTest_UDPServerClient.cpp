#include "UDPServerTest_UDPServerClient.h"

#include <string>

#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/StringConverter.h>

using std::string;
using std::to_wstring;
using std::wstring;
using std::endl;

using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::StringConverter;

EchoUDPServerClient::EchoUDPServerClient(const uint32_t clientId, const string& ip, const unsigned int port) :
	NIOUDPServerClient(clientId, ip, port) {
}

EchoUDPServerClient::~EchoUDPServerClient() {
	Console::println(L"EchoUDPServerClient::~EchoUDPServerClient()");
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
	Console::println(L"initiated connection with '" + StringConverter::toWideString(getIp()) + L":" + to_wstring(getPort()) + L"'");
}

void EchoUDPServerClient::onClose() throw (Exception) {
	Console::println(L"closed connection with '" + StringConverter::toWideString(getIp()) + L":" + to_wstring(getPort()) + L"'");
}

void EchoUDPServerClient::onCustom(const string& type) throw (Exception) {
	Console::println(L"custom event '" + StringConverter::toWideString(type) + L"' with '" + StringConverter::toWideString(getIp()) + L":" + to_wstring(getPort()) + L"'");
}
