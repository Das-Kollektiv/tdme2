#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkException.h>

using miniscript::os::network::NetworkException;

/**
 * Socket exception class
 * @author Andreas Drewke
 */
class miniscript::os::network::NetworkSocketException: public NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NetworkSocketException(const string &message) throw();
};
