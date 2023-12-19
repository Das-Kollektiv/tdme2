#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/fwd-miniscript.h>
#include <miniscript/utilities/fwd-miniscript.h>
#include <miniscript/utilities/ExceptionBase.h>

using _ExceptionBase = miniscript::utilities::ExceptionBase;

/**
 * Base exception class for network exceptions
 * @author Andreas Drewke
 */
class miniscript::os::network::NetworkException: public _ExceptionBase {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkException(const string &message) throw();
};
