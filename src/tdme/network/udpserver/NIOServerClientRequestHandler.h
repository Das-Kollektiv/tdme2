#pragma once

#include <tdme/tdme.h>

#include <string>

#include <tdme/utils/Exception.h>

using std::string;

using tdme::utils::Exception;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * @brief Client request handler base class
 * @author Andreas Drewke
 */
template <class CLIENT, class REQUEST>
class NIOServerClientRequestHandler {
public:
	/**
	 * @brief Public constructor
	 */
	NIOServerClientRequestHandler(const std::string& command) {
		this->command = command;
	}

	/**
	 * @brief Public destructor
	 */
	virtual ~NIOServerClientRequestHandler() {
	}

	/**
	 * @brief Returns this requests handler command name
	 */
	const string& getCommand() {
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
