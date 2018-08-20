#pragma once

#include <string>

#include <tdme/utils/ExceptionBase.h>

using tdme::utils::ExceptionBase;

namespace tdme {
namespace network {
namespace udpserver {

/**
 * Base exception class for NIO exceptions
 * @author Andreas Drewke
 */
class NIOServerClientRequestHandlerHubException: public ExceptionBase {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOServerClientRequestHandlerHubException(const string &message) throw();
};

};
};
};

