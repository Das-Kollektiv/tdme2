#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NetworkException.h>

using std::string;

/**
 * Kernel event mechanism exception class
 * @author Andreas Drewke
 */
class tdme::os::network::KEMException: public NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	KEMException(const string &message) throw();
};
