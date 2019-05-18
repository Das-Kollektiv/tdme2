#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOException;

/**
 * Kernel event mechanism exception class
 * @author Andreas Drewke
 */
class tdme::os::network::NIOSocketException: public NIOException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOSocketException(const string &message) throw();
};
