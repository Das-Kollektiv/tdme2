#pragma once

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/fwd-miniscript.h>
#include <miniscript/os/network/NetworkSocket.h>

using std::string;

/**
 * Class representing a TCP socket
 * @author Andreas Drewke
 */
class miniscript::os::network::TCPSocket: public NetworkSocket {
	public:
		/**
		 * Creates a TCP server socket
		 * @param ip ip
		 * @param port port
		 * @param backlog backlog
		 * @throws miniscript::os::network::NetworkSocketException
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
		 * @throws miniscript::os::network::NetworkSocketException
		 */
		void setTCPNoDelay();

		/**
		 * Connects a socket to given remote IP and port
		 * @param ip ip
		 * @param port port
		 * @throws miniscript::os::network::NetworkSocketException
		 */
		virtual void connect(const string& ip, const unsigned int port);

		/**
		 * Accepts a socket from a server socket
		 * @param _socket socket
		 * @throws miniscript::os::network::NetworkSocketException
		 * @return if socket was accepted
		 */
		virtual bool accept(TCPSocket* _socket);

		/**
		 * Reads up to "bytes" bytes from socket
		 * @param buf buffer to write to
		 * @param bytes bytes to receive
		 * @throws miniscript::os::network::NetworkIOException
		 * @return bytes read
		 */
		virtual size_t read(void* buf, const size_t bytes);

		/**
		 * Writes up to "bytes" bytes to socket
		 * @param buf buffer to read from
		 * @param bytes bytes to send
		 * @throws miniscript::os::network::NetworkIOException
		 * @return bytes written
		 */
		virtual size_t write(void* buf, const size_t bytes);

};

