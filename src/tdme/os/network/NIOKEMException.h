#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOException.h>

using std::string;

/**
 * Kernel event mechanism exception class
 * @author Andreas Drewke
 */
class tdme::os::network::NIOKEMException: public NIOException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOKEMException(const string &message) throw();
};
