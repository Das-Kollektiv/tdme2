#pragma once

#include <string>

#include <stddef.h>

#if defined(_WIN32) && defined(_MSC_VER)
	#define ssize_t int
#endif

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOIOException.h>
#include <tdme/os/network/NIONetworkSocket.h>
#include <tdme/os/network/NIOSocketException.h>

using std::string;

using tdme::os::network::NIOIOException;
using tdme::os::network::NIONetworkSocket;
using tdme::os::network::NIOSocketException;

/**
 * Class representing a nio udp socket
 * @author Andreas Drewke
 */
class tdme::os::network::NIOUDPSocket : public NIONetworkSocket {
public:
	/**
	 * @brief public destructor
	 */
	virtual ~NIOUDPSocket();

	/**
	 * @brief reads a datagram from socket
	 * @param from from host
	 * @param port from port
	 * @param buf buf
	 * @param bytes buf size
	 * @return datagram size or -1 if read would block
	 */
	ssize_t read(string& from, unsigned int& port, void* buf, const size_t bytes) throw (NIOIOException);

	/**
	 * @brief writes up to "bytes" bytes to socket
	 * @throws NIOIOException
	 * @param to to host
	 * @param port to port
	 * @param buf buf
	 * @param bytes buf size
	 * @return datagram bytes written or -1 if write would block
	 */
	ssize_t write(const string& to, const unsigned int port, void* buf, const size_t bytes) throw (NIOIOException);

	/**
	 * @brief creates a udp socket
	 * @param socket socket
	 * @param ipVersion IP version
	 * @throws NIOSocketException
	 */
	static void create(NIOUDPSocket& socket, IpVersion ipVersion) throw (NIOSocketException);

	/**
	 * @brief creates a udp server socket
	 * @param socket socket
	 * @param ip ip
	 * @param port port
	 * @throws NIOSocketException
	 */
	static void createServerSocket(NIOUDPSocket& socket, const std::string& ip, const unsigned int port) throw (NIOSocketException);

	/**
	 * @brief creates a udp client socket
	 * @param socket socket
	 * @param ipVersion IP version
	 * @throws NIOSocketException
	 */
	static void createClientSocket(NIOUDPSocket& socket, IpVersion ipVersion) throw (NIOSocketException);
};

