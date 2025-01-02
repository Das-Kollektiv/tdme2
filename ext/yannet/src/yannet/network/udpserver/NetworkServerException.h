#pragma once

#include <string>

#include <yannet/network/udpserver/fwd-yannet.h>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/NetworkException.h>

/**
 * Base exception class for network server exceptions
 * @author Andreas Drewke
 */
class yannet::network::udpserver::NetworkServerException: public yannet::os::network::NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	NetworkServerException(const string &message) throw();
};
