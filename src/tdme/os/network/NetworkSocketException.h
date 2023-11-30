#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/NetworkException.h>

using tdme::os::network::NetworkException;

/**
 * Socket exception class
 * @author Andreas Drewke
 */
class tdme::os::network::NetworkSocketException: public NetworkException {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkSocketException(const string &message) throw();
};
