#pragma once

#include <string>

#include <stddef.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#define ssize_t int
#endif

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/NetworkIOException.h>
#include <yannet/os/network/NetworkSocket.h>
#include <yannet/os/network/NetworkSocketException.h>

using std::string;

// namespaces
namespace yannet {
namespace os {
namespace network {
	using ::yannet::os::network::NetworkIOException;
	using ::yannet::os::network::NetworkSocket;
	using ::yannet::os::network::NetworkSocketException;
}
}
}

/**
 * Class representing a UDP socket
 * @author Andreas Drewke
 */
class yannet::os::network::UDPSocket : public ::yannet::os::network::NetworkSocket {
public:
	// forbid class copy
	FORBID_CLASS_COPY(UDPSocket)

	/**
	 * Creates a UDP server socket
	 * @param ip ip
	 * @param port port
	 * @return UDP socket
	 * @throws tdme::os::network::NetworkSocketException
	 */
	static UDPSocket* createServerSocket(const string& ip, const unsigned int port);

	/**
	 * Creates a UDP client socket
	 * @param ipVersion IP version
	 * @return UDP socket
	 * @throws tdme::os::network::NetworkSocketException
	 */
	static UDPSocket* createClientSocket(IpVersion ipVersion);

	/**
	 * Constructor
	 */
	UDPSocket(IpVersion ipVersion);

	/**
	 * Destructor
	 */
	virtual ~UDPSocket();

	/**
	 * Reads a datagram from socket
	 * @param from from host
	 * @param port from port
	 * @param buf buf
	 * @param bytes buf size
	 * @throws tdme::os::network::NetworkIOException
	 * @return datagram size or -1 if read would block
	 */
	ssize_t read(string& from, unsigned int& port, void* buf, const size_t bytes);

	/**
	 * Writes a datagram to socket
	 * @throws tdme::os::network::NetworkIOException
	 * @param to to host
	 * @param port to port
	 * @param buf buf
	 * @param bytes buf size
	 * @throws tdme::os::network::NetworkIOException
	 * @return datagram bytes written or -1 if write would block
	 */
	ssize_t write(const string& to, const unsigned int port, void* buf, const size_t bytes);

private:
	IpVersion ipVersion;

	/**
	 * Creates a UDP socket
	 * @param ipVersion IP version
	 * @return UDP socket
	 * @throws tdme::os::network::NetworkSocketException
	 */
	static UDPSocket* create(IpVersion ipVersion);
};

