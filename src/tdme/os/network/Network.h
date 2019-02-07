#pragma once

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
	 * Get IP by host name
	 * @param hostName host name
	 * @return ip of given host
	 */
	static const string getIpByHostName(const string &hostName);

};
