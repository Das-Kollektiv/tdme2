#pragma once

#include <miniscript/os/network/NetworkIOException.h>

#include <miniscript/miniscript.h>

/**
 * Network socket closed exception
 * @author Andreas Drewke
 */
class miniscript::os::network::NetworkSocketClosedException: public NetworkIOException {
	public:
		/**
		 * @brief public constructor
		 * @param message exception message
		 */
		NetworkSocketClosedException(const string &message) throw();
};

