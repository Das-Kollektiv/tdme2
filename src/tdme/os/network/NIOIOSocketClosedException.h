#pragma once

#include <tdme/os/network/NIOIOException.h>

/**
 * Socket closes exception
 * @author Andreas Drewke
 */
class tdme::os::network::NIOIOSocketClosedException: public NIOIOException {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		NIOIOSocketClosedException(const string &message) throw();
};

