#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkException.h>

using std::string;

/**
 * Base exception class for network IO exceptions
 * @author Andreas Drewke
 */
class yannet::os::network::NetworkIOException: public ::yannet::os::network::NetworkException {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkIOException(const string &message) throw();
};
