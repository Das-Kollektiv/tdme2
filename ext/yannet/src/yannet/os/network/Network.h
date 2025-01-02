#pragma once

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>

#include <string>

using std::string;

/**
 * Network class
 * @author Andreas Drewke
 */
class yannet::os::network::Network {
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
