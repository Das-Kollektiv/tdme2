#pragma once

#include <tdme/tdme.h>
#include <tdme/os/network/fwd-tdme.h>

#include <string>

using std::string;

/**
 * Network class
 * @author Andreas Drewke
 */
class tdme::os::network::Network {
public:

	/**
	 * Initialize
	 * @return success
	 */
	static bool initialize();

	/**
	 * Get IP by hostname
	 * @param hostname hostname
	 * @throws tdme::os::network::NetworkException
	 * @return ip address of given host
	 */
	static const string getIpByHostname(const string &hostname);

};
