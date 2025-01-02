#pragma once

#include <openssl/x509.h>

#include <string>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/os/network/fwd-yannet.h>
#include <yannet/os/network/TCPSocket.h>
#include <yannet/os/threading/Mutex.h>

using std::string;
using std::vector;

namespace yannet {
namespace os {
namespace network {
	using yannet::os::network::TCPSocket;
	using yannet::os::threading::Mutex;
}
}
}

/**
 * Class representing a secure TCP socket
 * @author Andreas Drewke
 */
class yannet::os::network::SecureTCPSocket : public TCPSocket {
public:
	// forbid class copy
	FORBID_CLASS_COPY(SecureTCPSocket)

	/**
	 * Public Constructor
	 */
	SecureTCPSocket();

	/**
	 * Public destructor
	 */
	virtual ~SecureTCPSocket();

	/**
	 * Connects a socket to given remote IP and port
	 * @param hostname hostname
	 * @param port port
	 * @throws tdme::os::network::NetworkSocketException
	 */
	void connect(const string& hostname, const unsigned int port);

	/**
	 * Reads up to "bytes" bytes from socket
	 * @param buf buffer to write to
	 * @param bytes bytes to receive
	 * @throws tdme::os::network::NetworkIOException
	 * @return bytes read
	 */
	size_t read(void* buf, const size_t bytes);

	/**
	 * Writes up to "bytes" bytes to socket
	 * @param buf buffer to read from
	 * @param bytes bytes to send
	 * @throws tdme::os::network::NetworkIOException
	 * @return bytes written
	 */
	size_t write(void* buf, const size_t bytes);

	/**
	 * shuts socket down for reading and writing
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

