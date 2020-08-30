#pragma once

#include <sstream>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/NIOUDPServer.h>
#include <tdme/network/udpserver/NIOUDPServerClient.h>
#include <tdme/utilities/Exception.h>

#include "UDPServerTest_UDPServer.h"

using std::stringstream;

using tdme::network::udpserver::NIOUDPServer;
using tdme::network::udpserver::NIOUDPServerClient;
using tdme::utilities::Exception;

class EchoUDPServerClient : public NIOUDPServerClient {
	friend class EchoUDPServer;

public:
	EchoUDPServerClient(const uint32_t clientId, const std::string& ip, const unsigned int port);

protected:
	virtual ~EchoUDPServerClient();

	virtual void onRequest(stringstream* frame, const uint32_t messageId, const uint8_t retries);

	void onInit();
	void onClose();
	void onCustom(const string& type);
};
