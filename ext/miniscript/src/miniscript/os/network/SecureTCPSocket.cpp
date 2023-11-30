#include <miniscript/os/network/SecureTCPSocket.h>

#include <openssl/x509.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/ocsp.h>
#include <openssl/bn.h>
#include <openssl/trace.h>
#include <openssl/async.h>
#ifndef OPENSSL_NO_CT
#include <openssl/ct.h>
#endif

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/Network.h>
#include <miniscript/os/network/NetworkIOException.h>
#include <miniscript/os/network/NetworkSocket.h>
#include <miniscript/os/network/NetworkSocketClosedException.h>
#include <miniscript/os/network/NetworkSocketException.h>
#include <miniscript/os/threading/Mutex.h>
#include <miniscript/utilities/Console.h>

using miniscript::os::network::SecureTCPSocket;

using std::string;
using std::to_string;

using miniscript::os::network::Network;
using miniscript::os::network::NetworkIOException;
using miniscript::os::network::NetworkSocket;
using miniscript::os::network::NetworkSocketClosedException;
using miniscript::os::network::NetworkSocketException;
using miniscript::os::threading::Mutex;
using miniscript::utilities::Console;

// see: https://wiki.openssl.org/index.php/SSL/TLS_Client

SecureTCPSocket::SecureTCPSocket() {
}

SecureTCPSocket::~SecureTCPSocket() {
}

size_t SecureTCPSocket::read(void* buf, const size_t bytes) {
	auto bytesRead = BIO_read(bio, buf, bytes);
	if (bytesRead == -1) {
		throw NetworkIOException("Error while reading from socket: " + openSSLGetErrors());
	} else
	if (bytesRead == 0) {
		throw NetworkSocketClosedException("end of stream");
	}
	//
	return (size_t)bytesRead;
}

size_t SecureTCPSocket::write(void* buf, const size_t bytes) {
	auto bytesWritten = BIO_write(bio, buf, bytes);
	if (bytesWritten == -1) {
		throw NetworkIOException("Error while writing to socket: " + openSSLGetErrors());
	}
	//
	return (size_t)bytesWritten;
}

void SecureTCPSocket::connect(const string& hostname, const unsigned int port) {
	// set address
	this->ip = Network::getIpByHostname(hostname);
	this->port = port;
	//
	const SSL_METHOD* method = SSLv23_method();
	if (!(nullptr != method))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	ctx = SSL_CTX_new(method);
	if (!(ctx != nullptr))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	/* Cannot fail ??? */
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, openSSLVerifyCallback);

	/* Cannot fail ??? */
	SSL_CTX_set_verify_depth(ctx, 4);

	/* Cannot fail ??? */
	const long flags = SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3 | SSL_OP_NO_COMPRESSION;
	SSL_CTX_set_options(ctx, flags);

	//
	long result = 1;
	// see: https://stackoverflow.com/questions/59017890/where-is-the-certificate-file-for-ssl-ctx-load-verify-locations-in-openssl-locat
	result = SSL_CTX_load_verify_locations(ctx, "resources/certs/cacert-2023-08-22.pem" /* truststore */, "resources/certs");
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	bio = BIO_new_ssl_connect(ctx);
	if (!(bio != nullptr))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	result = BIO_set_conn_hostname(bio, string(hostname + ":" + to_string(port)).c_str());
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	BIO_get_ssl(bio, &ssl);
	if (!(ssl != nullptr))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	const char PREFERRED_CIPHERS[] = "HIGH:!aNULL:!kRSA:!PSK:!SRP:!MD5:!RC4";
	result = SSL_set_cipher_list(ssl, PREFERRED_CIPHERS);
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	result = SSL_set_tlsext_host_name(ssl, hostname.c_str());
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	out = BIO_new_fp(stdout, BIO_NOCLOSE);
	if (!(nullptr != out))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	result = BIO_do_connect(bio);
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	result = BIO_do_handshake(bio);
	if (!(1 == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	/* Step 1: verify a server certificate was presented during the negotiation */
	X509* cert = SSL_get_peer_certificate(ssl);
	if (cert) {
		X509_free(cert);
	} /* Free immediately */
	if (nullptr == cert)
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());

	/* Step 2: verify the result of chain verification */
	/* Verification performed according to RFC 4158    */
	result = SSL_get_verify_result(ssl);
	if (!(X509_V_OK == result))
		throw NetworkSocketException("Could not connect socket: " + openSSLGetErrors());
}

void SecureTCPSocket::createServerSocket(SecureTCPSocket& socket, const string& ip, const unsigned int port, const int backlog) {
	throw new NetworkSocketException("Could not create secure server socket: not implemented");
}

bool SecureTCPSocket::accept(SecureTCPSocket &_socket) {
	throw new NetworkSocketException("Could not accept: not implemented");
}

void SecureTCPSocket::shutdown() {
	if (bio != nullptr) BIO_free_all(bio);
	if (ctx != nullptr) SSL_CTX_free(ctx);
	bio = nullptr;
	ctx = nullptr;
}

void SecureTCPSocket::close() {
	if (bio != nullptr) BIO_free_all(bio);
	if (ctx != nullptr) SSL_CTX_free(ctx);
	bio = nullptr;
	ctx = nullptr;
}

int SecureTCPSocket::openSSLVerifyCallback(int preverify, X509_STORE_CTX *x509_ctx) {
	int depth = X509_STORE_CTX_get_error_depth(x509_ctx);
	int err = X509_STORE_CTX_get_error(x509_ctx);
	X509 *cert = X509_STORE_CTX_get_current_cert(x509_ctx);
	X509_NAME *iname = cert ? X509_get_issuer_name(cert) : nullptr;
	X509_NAME *sname = cert ? X509_get_subject_name(cert) : nullptr;
	/*
	 print_cn_name("Issuer (cn)", iname);
	 print_cn_name("Subject (cn)", sname);
	 */
	if (depth == 0) {
		/* If depth is 0, its the server's certificate. Print the SANs too */
		/*
		 print_san_name("Subject (san)", cert);
		 */
	}
	return preverify;
}

const string SecureTCPSocket::openSSLGetErrors() {
	string result;
	int err;
	while (err = ERR_get_error()) {
		auto errorMessage = ERR_error_string(err, 0);
		if (errorMessage == nullptr) return result;
		result+= string(errorMessage) + "\n";
	}
	return result;
}
