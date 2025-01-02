#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/utilities/ExceptionBase.h>

using std::string;

namespace yannet {
namespace network {
namespace udpserver {

/**
 * Network server client request handler hub exception
 * @author Andreas Drewke
 */
class ServerClientRequestHandlerHubException: public yannet::utilities::ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	ServerClientRequestHandlerHubException(const string& message) throw();
};

};
};
};

