#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/NetworkException.h>

using tdme::os::network::NetworkException;

/**
 * Kernel event mechanism exception class
 * @author Andreas Drewke
 */
class tdme::os::network::SocketException: public NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	SocketException(const string &message) throw();
};
