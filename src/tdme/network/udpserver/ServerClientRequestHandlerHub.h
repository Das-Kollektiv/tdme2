#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/network/udpserver/ServerClientRequestHandler.h>
#include <tdme/network/udpserver/ServerClientRequestHandlerHubException.h>

using std::string;
using std::unordered_map;

using tdme::network::udpserver::ServerClientRequestHandler;
using tdme::network::udpserver::ServerClientRequestHandlerHubException;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * @brief Network server client request handler hub
 * @author Andreas Drewke
 */
template <class CLIENT, class REQUEST>
class ServerClientRequestHandlerHub final {
public:
	/**
	 * @brief Public constructor
	 */
	ServerClientRequestHandlerHub() : defaultHandler(nullptr) {
	}

	/**
	 * @brief Public destructor
	 */
	virtual ~ServerClientRequestHandlerHub() {
		// delete handler
		for (auto& it: requestHandlerMap) {
			ServerClientRequestHandler<CLIENT,REQUEST>* handler = it.second;
			// delete reference
			delete handler;
		}
	}

	/**
	 * @brief Adds a client request handler
	 * @param handler request handler
	 * @throws TCPServerClientRequestHandlerHubException
	 */
	void addHandler(ServerClientRequestHandler<CLIENT,REQUEST>* handler) {
		auto it = requestHandlerMap.find(handler->getCommand());
		if (it == requestHandlerMap.end()) {
			requestHandlerMap[handler->getCommand()] = handler;
		} else {
			throw ServerClientRequestHandlerHubException("Handler for given command already exists");
		}
	}

	/**
	 * @brief Sets the client request default handler, will be used if command not found in request handler map
	 * @param handler request handler
	 */
	inline void setDefaultHandler(ServerClientRequestHandler<CLIENT,REQUEST>* handler) {
		defaultHandler = handler;
	}

	/**
	 * Handles a client request
	 * @param client client
	 * @param command command
	 * @param request request
	 * @param messageId message id (udp server only)
	 * @param retries retries (udp server only)
	 */
	void handleRequest(CLIENT* client, const string& command, REQUEST& request, const uint32_t messageId, const uint8_t retries) {
		auto it = requestHandlerMap.find(command);
		// handler not identified?
		if (it == requestHandlerMap.end()) {
			// use default / fall back if exists
			if (defaultHandler != nullptr) {
				defaultHandler->handleRequest(client, request, messageId, retries);
			} else {
				// otherwise report an exception
				throw ServerClientRequestHandlerHubException("Handler for given command not found");
			}
		} else {
			// found handler
			auto handler = it->second;
			handler->handleRequest(client, request, messageId, retries);
		}
	}
private:
	typedef unordered_map<string, ServerClientRequestHandler<CLIENT,REQUEST>*> RequestHandlerMap;
	RequestHandlerMap requestHandlerMap;
	ServerClientRequestHandler<CLIENT,REQUEST>* defaultHandler;
};

};
};
};
