#pragma once

#include <tdme/os/network/NetworkIOException.h>

#include <tdme/tdme.h>

/**
 * Socket closes exception
 * @author Andreas Drewke
 */
class tdme::os::network::SocketClosedException: public NetworkIOException {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		SocketClosedException(const string &message) throw();
};

