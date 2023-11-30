#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkException.h>

using std::string;

using miniscript::os::network::NetworkException;

/**
 * Base exception class for network IO exceptions
 * @author Andreas Drewke
 */
class miniscript::os::network::NetworkIOException: public NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NetworkIOException(const string &message) throw();
};
