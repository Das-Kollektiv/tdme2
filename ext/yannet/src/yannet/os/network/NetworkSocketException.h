#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkException.h>

/**
 * Socket exception class
 * @author Andreas Drewke
 */
class yannet::os::network::NetworkSocketException: public yannet::os::network::NetworkException {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkSocketException(const string &message) throw();
};
