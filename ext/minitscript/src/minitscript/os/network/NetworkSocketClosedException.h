#pragma once

#include <minitscript/os/network/NetworkIOException.h>

#include <minitscript/minitscript.h>

/**
 * Network socket closed exception
 * @author Andreas Drewke
 */
class minitscript::os::network::NetworkSocketClosedException: public ::minitscript::os::network::NetworkIOException {
	public:
		/**
		 * Constructor
		 * @param message exception message
		 */
		NetworkSocketClosedException(const string &message) throw();
};

