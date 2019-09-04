#pragma once

#include <string>

#include <tdme/os/network/fwd-tdme.h>
#include <tdme/os/network/NIOIOException.h>
#include <tdme/os/network/NIONetworkSocket.h>
#include <tdme/os/network/NIOSocketException.h>

/**
 * Class representing a NIO TCP socket
 * @author Andreas Drewke
 */
class tdme::os::network::NIOTCPSocket : public NIONetworkSocket {
	public:
		/**
		 * @brief Public destructor
		 */
		virtual ~NIOTCPSocket();

		/**
		 * @brief Reads up to "bytes" bytes from socket
		 * @param buf buffer to write to
		 * @param bytes bytes to receive
		 * @throws tdme::os::network::NIOIOException
		 * @return bytes read
		 */
		size_t read(void* buf, const size_t bytes);

		/**
		 * @brief Writes up to "bytes" bytes to socket
		 * @param buf buffer to read from
		 * @param bytes bytes to send
		 * @throws tdme::os::network::NIOIOException
		 * @return bytes written
		 */
		size_t write(void* buf, const size_t bytes);

		/**
		 * @brief Creates a TCP socket
		 * @param socket socket
		 * @param ipVersion IP version
		 * @throws tdme::os::network::NIOSocketException
		 */
		static void create(NIOTCPSocket& socket, IpVersion ipVersion);

		/**
		 * Connects a socket to given IP and port
		 * @param ip ip
		 * @param port port
		 * @throws tdme::os::network::NIOSocketException
		 */
		void connect(const string& ip, const unsigned int port);

		/**
		 * @brief Creates a TCP server socket
		 * @param socket socket
		 * @param ip ip
		 * @param port port
		 * @param backlog backlog
		 * @throws tdme::os::network::NIOSocketException
		 * @return socket
		 */
		static void createServerSocket(NIOTCPSocket& socket, const std::string& ip, const unsigned int port, const int backlog);

		/**
		 * @brief Disables nagle's algorithm
		 * @throws tdme::os::network::NIOSocketException
		 */
		void setTCPNoDelay();

		/**
		 * @brief Accepts a socket from a server socket
		 * @param _socket socket
		 * @throws tdme::os::network::NIOSocketException
		 * @return if socket was accepted
		 */
		bool accept(NIOTCPSocket& _socket);
};

