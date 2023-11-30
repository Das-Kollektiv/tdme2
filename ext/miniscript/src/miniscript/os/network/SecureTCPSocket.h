#pragma once

#include <openssl/types.h>
#include <openssl/x509.h>

#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/fwd-miniscript.h>
#include <miniscript/os/network/TCPSocket.h>
#include <miniscript/os/threading/Mutex.h>

using std::string;
using std::vector;

using miniscript::os::network::TCPSocket;
using miniscript::os::threading::Mutex;

/**
 * Class representing a secure TCP socket
 * @author Andreas Drewke
 */
class miniscript::os::network::SecureTCPSocket : public TCPSocket {
	public:
		// forbid class copy
		FORBID_CLASS_COPY(SecureTCPSocket)

		/**
		 * @brief Public Constructor
		 */
		SecureTCPSocket();

		/**
		 * @brief Public destructor
		 */
		virtual ~SecureTCPSocket();

		/**
		 * @brief Reads up to "bytes" bytes from socket
		 * @param buf buffer to write to
		 * @param bytes bytes to receive
		 * @throws miniscript::os::network::NetworkIOException
		 * @return bytes read
		 */
		size_t read(void* buf, const size_t bytes);

		/**
		 * @brief Writes up to "bytes" bytes to socket
		 * @param buf buffer to read from
		 * @param bytes bytes to send
		 * @throws miniscript::os::network::NetworkIOException
		 * @return bytes written
		 */
		size_t write(void* buf, const size_t bytes);

		/**
		 * Connects a socket to given IP and port
		 * @param hostname hostname
		 * @param port port
		 * @throws miniscript::os::network::NetworkSocketException
		 */
		void connect(const string& hostname, const unsigned int port);

		/**
		 * @brief Creates a TCP server socket
		 * @param socket socket
		 * @param hostname hostname
		 * @param port port
		 * @param backlog backlog
		 * @throws miniscript::os::network::NetworkSocketException
		 * @return socket
		 */
		static void createServerSocket(SecureTCPSocket& socket, const string& hostname, const unsigned int port, const int backlog);

		/**
		 * @brief Accepts a socket from a server socket
		 * @param _socket socket
		 * @throws miniscript::os::network::NetworkSocketException
		 * @return if socket was accepted
		 */
		bool accept(SecureTCPSocket& _socket);

		/**
		 * @brief shuts socket down for reading and writing
		 */
		virtual void shutdown();

		/**
		 * Closes the socket
		 */
		virtual void close();

	private:
		/**
		 * OpenSSL verify callback
		 * @param preverify preverify
		 * @param x509_ctx x509_ctx
		 */
		static int openSSLVerifyCallback(int preverify, X509_STORE_CTX* x509_ctx);

		/**
		 * @return OpenSSL get errors
		 */
		const string openSSLGetErrors();

		//
		SSL* ssl = nullptr;
		SSL_CTX* ctx = nullptr;
		BIO* bio = nullptr, *out = nullptr;
};

