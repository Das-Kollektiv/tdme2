#pragma once

#include <map>
#include <string>

#include <tdme.h>
#include <tdme/network/udpserver/NIOServerClientRequestHandler.h>
#include <tdme/network/udpserver/NIOServerClientRequestHandlerHubException.h>

using std::map;
using std::string;

using tdme::network::udpserver::NIOServerClientRequestHandler;
using tdme::network::udpserver::NIOServerClientRequestHandlerHubException;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * @brief Server client request bean
 * @author Andreas Drewke
 */
template <class CLIENT, class REQUEST>
class NIOServerClientRequestHandlerHub {
	public:
		/**
		 * @brief Public constructor
		 */
		NIOServerClientRequestHandlerHub() : defaultHandler(NULL) {
		}

		/**
		 * @brief Public destructor
		 */
		virtual ~NIOServerClientRequestHandlerHub() {
			// delete handler
			for (typename RequestHandlerMap::iterator i = requestHandlerMap.begin(); i != requestHandlerMap.end(); ++i) {
				NIOServerClientRequestHandler<CLIENT,REQUEST>* handler = (*i).second;
				// delete reference
				delete handler;
			}
		}

		/**
		 * @brief Adds a client request handler
		 * @param request handler
		 * @throws TCPServerClientRequestHandlerHubException
		 */
		void addHandler(NIOServerClientRequestHandler<CLIENT,REQUEST>* handler) throw (NIOServerClientRequestHandlerHubException) {
			typename RequestHandlerMap::iterator it = requestHandlerMap.find(handler->getCommand());
			if (it == requestHandlerMap.end()) {
				requestHandlerMap[handler->getCommand()] = handler;
			} else {
				throw NIOServerClientRequestHandlerHubException("Handler for given command already exists");
			}
		}

		/**
		 * @brief Sets the client request default handler, will be used if command not found in request handler map
		 * @param request handler
		 */
		void setDefaultHandler(NIOServerClientRequestHandler<CLIENT,REQUEST>* handler) {
			defaultHandler = handler;
		}

		/**
		 * Handles a client request
		 * @param client
		 * @param command
		 * @param request
		 * @param message id (udp server only)
		 * @param retries (udp server only)
		 * @throws exception
		 */
		void handleRequest(CLIENT* client, const string& command, REQUEST& request, const uint32_t messageId, const uint8_t retries) throw (Exception) {
			typename RequestHandlerMap::iterator it = requestHandlerMap.find(command);
			// handler not identified?
			if (it == requestHandlerMap.end()) {
				// use default / fall back if exists
				if (defaultHandler != NULL) {
					defaultHandler->handleRequest(client, request, messageId, retries);
				} else {
					// otherwise report an exception
					throw NIOServerClientRequestHandlerHubException("Handler for given command not found");
				}
			} else {
				// found handler
				NIOServerClientRequestHandler<CLIENT,REQUEST>* handler = it->second;
				handler->handleRequest(client, request, messageId, retries);
			}
		}
	private:
		typedef map<string, NIOServerClientRequestHandler<CLIENT,REQUEST>*> RequestHandlerMap;
		RequestHandlerMap requestHandlerMap;
		NIOServerClientRequestHandler<CLIENT,REQUEST>* defaultHandler;
};

};
};
};
