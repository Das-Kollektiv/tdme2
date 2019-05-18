#pragma once

#include <string>

#include <tdme/network/udpclient/fwd-tdme.h>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOException;

/**
 * Base exception class for NIO client exceptions
 * @author Andreas Drewke
 */
class tdme::network::udpclient::NIOClientException: public NIOException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NIOClientException(const string &message) throw();
};
