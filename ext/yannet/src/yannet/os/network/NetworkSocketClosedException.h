#pragma once

#include <yannet/os/network/NetworkIOException.h>

#include <yannet/yannet.h>

/**
 * Network socket closed exception
 * @author Andreas Drewke
 */
class yannet::os::network::NetworkSocketClosedException: public yannet::os::network::NetworkIOException {
	public:
		/**
		 * Constructor
		 * @param message exception message
		 */
		NetworkSocketClosedException(const string &message) throw();
};

