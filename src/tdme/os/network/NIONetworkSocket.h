#pragma once

#include <string>

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOSocketException.h>

using std::string;

using tdme::os::network::NIOSocketException;

/**
 * Class representing a nio socket
 * @author Andreas Drewke
 */
class tdme::os::network::NIONetworkSocket {
	friend class KernelEventMechanism;

public:
	enum IpVersion {IPV4, IPV6};

	/**
	 * @brief copy operator
	 */
	NIONetworkSocket& operator=(NIONetworkSocket& socket);

	/**
	 * Protected constructor
	 */
	NIONetworkSocket();

	/**
	 * @brief public destructor
	 */
	virtual ~NIONetworkSocket();

	/**
	 * @brief returns the end points ip address
	 * @return end point ip address
	 */
	const string& getAddress();

	/**
	 * @brief returns the end points port
	 * @return end point port
	 */
	const unsigned int getPort();

	/**
	 * @brief shuts socket down for reading and writing
	 */
	void shutdown();

	/**
	 * Binds a socket to local ip and port
	 * @param ip
	 * @param port
	 * @throws NIOSocketException
	 */
	void bind(const string& ip, const unsigned int port) throw (NIOSocketException);

	/**
	 * @brief sets the socket non blocked
	 * @throws NIOSocketException
	 */
	void setNonBlocked() throw (NIOSocketException);

	/**
	 * Closes the socket
	 */
	void close();

	/**
	 * Determine IP version
	 * @param ip
	 * @returns ip version
	 */
	static IpVersion determineIpVersion(const string& ip);

protected:
	IpVersion ipVersion;
	int descriptor;
	string ip;
	unsigned int port;
};
