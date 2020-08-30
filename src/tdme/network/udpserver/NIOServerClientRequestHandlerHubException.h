#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::utilities::ExceptionBase;

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

