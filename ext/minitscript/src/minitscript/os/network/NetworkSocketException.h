#pragma once

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/os/network/NetworkException.h>

/**
 * Socket exception class
 * @author Andreas Drewke
 */
class minitscript::os::network::NetworkSocketException: public ::minitscript::os::network::NetworkException {
public:
	/**
	 * Public constructor
	 * @param &message message exception message
	 */
	NetworkSocketException(const string &message) throw();
};
