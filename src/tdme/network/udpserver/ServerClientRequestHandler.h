#pragma once

#include <tdme/tdme.h>

#include <string>

using std::string;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * @brief Network client request handler base class
 * @author Andreas Drewke
 */
template <class CLIENT, class REQUEST>
class ServerClientRequestHandler {
public:
	// forbid class copy
	FORBID_CLASS_COPY(ServerClientRequestHandler)

	/**
	 * @brief Public constructor
	 */
	ServerClientRequestHandler(const std::string& command) {
		this->command = command;
	}

	/**
	 * @brief Public destructor
	 */
	virtual ~ServerClientRequestHandler() {
	}

	/**
	 * @brief Returns this requests handler command name
	 */
	inline const string& getCommand() {
		return command;
	}

	/**
	 * @brief Request handler implementation
	 * @param client client
	 * @param request request data
	 * @param messageId message id (udp server only)
	 * @param retries retries (udp server only)
	 */
	virtual void handleRequest(CLIENT* client, REQUEST& request, const uint32_t messageId, const uint8_t retries) = 0;
private:
	string command;
};

};
};
};
