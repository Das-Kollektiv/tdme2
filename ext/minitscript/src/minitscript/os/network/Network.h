#pragma once

#include <minitscript/minitscript.h>
#include <minitscript/os/network/fwd-minitscript.h>

#include <string>

using std::string;

/**
 * Network class
 * @author Andreas Drewke
 */
class minitscript::os::network::Network {
public:

	/**
	 * Initialize
	 * @return success
	 */
	static bool initialize();

	/**
	 * Get IP by hostname
	 * @param hostname hostname
	 * @throws minitscript::os::network::NetworkException
	 * @return ip address of given host
	 */
	static const string getIpByHostname(const string &hostname);

};
