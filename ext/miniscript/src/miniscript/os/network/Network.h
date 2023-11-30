#pragma once

#include <miniscript/miniscript.h>
#include <miniscript/os/network/fwd-miniscript.h>

#include <string>

using std::string;

/**
 * Network class
 * @author Andreas Drewke
 */
class miniscript::os::network::Network {
public:

	/**
	 * Initialize
	 * @return success
	 */
	static bool initialize();

	/**
	 * Get IP by hostname
	 * @param hostname hostname
	 * @throws miniscript::os::network::NetworkException
	 * @return ip address of given host
	 */
	static const string getIpByHostname(const string &hostname);

};
