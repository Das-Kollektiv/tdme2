#pragma once

#include <string>

#include <tdme/network/udpclient/fwd-tdme.h>

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NetworkException.h>

using tdme::os::network::NetworkException;

/**
 * Base exception class for network client exceptions
 * @author Andreas Drewke
 */
class tdme::network::udpclient::ClientException: public NetworkException {
public:
	/**
	 * @brief public constructor
	 * @param &message message exception message
	 */
	ClientException(const string &message) throw();
};
