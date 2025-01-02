#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/NetworkException.h>

using std::string;

/**
 * Kernel event mechanism exception class
 * @author Andreas Drewke
 */
class yannet::os::network::NetworkKEMException: public yannet::os::network::NetworkException {
public:
	/**
	 * Constructor
	 * @param &message message exception message
	 */
	NetworkKEMException(const string &message) throw();
};
