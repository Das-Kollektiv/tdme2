#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/os/network/fwd-minitscript.h>
#include <minitscript/utilities/fwd-minitscript.h>
#include <minitscript/utilities/ExceptionBase.h>

/**
 * Base exception class for network exceptions
 * @author Andreas Drewke
 */
class minitscript::os::network::NetworkException: public minitscript::utilities::ExceptionBase {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkException(const string &message) throw();
};
