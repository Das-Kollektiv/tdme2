#pragma once

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/NetworkSocket.h>

using std::string;

/**
 * Class representing a TCP socket
 * @author Andreas Drewke
 */
class yannet::os::network::TCPSocket: public ::yannet::os::network::NetworkSocket {
public:
	/**
	 * Creates a TCP server socket
	 * @param ip ip
	 * @param port port
	 * @param backlog backlog
	 * @throws tdme::os::network::NetworkSocketException
	 * @return socket
	 */
	static TCPSocket* createServerSocket(const string& ip, const unsigned int port, const int backlog);

	// forbid class copy
	FORBID_CLASS_COPY(TCPSocket)

	/**
	 * @brief Constructor
	 */
	TCPSocket();

	/**
	 * @brief Destructor
	 */
	virtual ~TCPSocket();


	/**
	 * Disables nagle's algorithm
	 * @throws tdme::os::network::NetworkSocketException
	 */
	void setTCPNoDelay();

	/**
	 * Connects a socket to given remote IP and port
	 * @param ip ip
	 * @param port port
	 * @throws tdme::os::network::NetworkSocketException
	 */
	virtual void connect(const string& ip, const unsigned int port);

	/**
	 * Accepts a socket from a server socket
	 * @param _socket socket
	 * @throws tdme::os::network::NetworkSocketException
	 * @return if socket was accepted
	 */
	virtual bool accept(TCPSocket* _socket);

	/**
	 * Reads up to "bytes" bytes from socket
	 * @param buf buffer to write to
	 * @param bytes bytes to receive
	 * @throws tdme::os::network::NetworkIOException
	 * @return bytes read
	 */
	virtual size_t read(void* buf, const size_t bytes);

	/**
	 * Writes up to "bytes" bytes to socket
	 * @param buf buffer to read from
	 * @param bytes bytes to send
	 * @throws tdme::os::network::NetworkIOException
	 * @return bytes written
	 */
	virtual size_t write(void* buf, const size_t bytes);

};

