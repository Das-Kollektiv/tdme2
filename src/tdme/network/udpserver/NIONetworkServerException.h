#pragma once

#include <string>

#include <tdme/network/udpserver/fwd-tdme.h>

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOException;

/**
 * Base exception class for NIO network server exceptions
 * @author Andreas Drewke
 */
class tdme::network::udpserver::NIONetworkServerException: public NIOException {
public:
	/**
	 * @brief public constructor
	 * @param message exception message
	 */
	NIONetworkServerException(const string &message) throw();
};
