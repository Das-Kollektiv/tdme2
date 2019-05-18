#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/os/network/NIOException.h>

using std::string;

using tdme::os::network::NIOException;

/**
 * Base exception class for NIO IO exceptions
 * @author Andreas Drewke
 */
class tdme::os::network::NIOIOException: public NIOException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOIOException(const string &message) throw();
};
