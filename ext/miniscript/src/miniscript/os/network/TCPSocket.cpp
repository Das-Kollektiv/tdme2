#include <miniscript/os/network/TCPSocket.h>

#include <memory>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkIOException.h>
#include <miniscript/os/network/NetworkSocket.h>
#include <miniscript/os/network/NetworkSocketClosedException.h>
#include <miniscript/os/network/NetworkSocketException.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#if defined(_WIN32)
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define socklen_t int
	#define BUF_CAST(buf) ((char*)buf)
	#if defined(_MSC_VER)
		#define ssize_t int
	#endif
#else
	#include <arpa/inet.h>
	#include <netinet/tcp.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#define BUF_CAST(buf) ((void*)buf)
#endif

using miniscript::os::network::TCPSocket;

using std::make_unique;
using std::string;
using std::to_string;

using miniscript::os::network::NetworkIOException;
using miniscript::os::network::NetworkSocket;
using miniscript::os::network::NetworkSocketClosedException;
using miniscript::os::network::NetworkSocketException;

TCPSocket* TCPSocket::createServerSocket(const string& ip, const unsigned int port, const int backlog) {
	// create socket
	auto socket = make_unique<TCPSocket>();
	auto ipVersion = determineIpVersion(ip);
	socket->descriptor = ::socket(ipVersion == IPV6?PF_INET6:PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket->descriptor == -1) {
		throw NetworkSocketException("Could not create socket: " + string(strerror(errno)));
	}
	#if defined(__APPLE__)
		int flag = 1;
		if (setsockopt(socket->descriptor, SOL_SOCKET, SO_NOSIGPIPE, (void*)&flag, sizeof(flag)) == -1) {
			throw NetworkSocketException("Could not set no sig pipe on socket: " + string(strerror(errno)));
		}
	#endif

	//
	try {
		// set non blocked
		socket->setNonBlocked();

		// bind
		socket->bind(ip, port);

		// make socket listen, backlog is 10% of max CCU
		if (listen(socket->descriptor, backlog) == -1) {
			throw NetworkSocketException("Could not set socket to listen: " + string(strerror(errno)));
		}
		//
	} catch (NetworkSocketException &exception) {
		socket->close();
		throw;
	}
	//
	return socket.release();
}

TCPSocket::TCPSocket(): NetworkSocket() {
}

TCPSocket::~TCPSocket() {
}

void TCPSocket::setTCPNoDelay() {
	int flag = 1;
	#if defined(_WIN32)
		if (setsockopt(descriptor, IPPROTO_TCP, TCP_NODELAY, (const char*)&flag, sizeof(flag)) == -1) {
	#else
		if (setsockopt(descriptor, IPPROTO_TCP, TCP_NODELAY, (void*)&flag, sizeof(flag)) == -1) {
	#endif
		throw NetworkSocketException("Could not set tcp no delay: " + string(strerror(errno)));
	}
}

void TCPSocket::connect(const string& ip, const unsigned int port) {
	// determine IP version
	auto ipVersion = determineIpVersion(ip);

	//
	descriptor = ::socket(ipVersion == IPV6?PF_INET6:PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (descriptor == -1) {
		throw NetworkSocketException("Could not create socket: " + string(strerror(errno)));
	}
	#if defined(__APPLE__)
		int flag = 1;
		if (setsockopt(descriptor, SOL_SOCKET, SO_NOSIGPIPE, (void*)&flag, sizeof(flag)) == -1) {
			throw NetworkSocketException("Could not set no sig pipe on socket: " + string(strerror(errno)));
		}
	#endif

	// socket address in setup
	socklen_t sinLen = 0;
	void* sin;
	sockaddr_in sinIPV4;
	sockaddr_in6 sinIPV6;
	switch(ipVersion) {
		case IPV4:
			{
				sinLen = sizeof(sinIPV4);
				memset(&sinIPV4, 0, sinLen);
				sinIPV4.sin_family = AF_INET;
				sinIPV4.sin_port = htons(port);
				sinIPV4.sin_addr.s_addr = inet_addr(ip.c_str());
				sin = &sinIPV4;
			}
			break;
		case IPV6:
			{
				sinLen = sizeof(sinIPV6);
				memset(&sinIPV6, 0, sinLen);
				sinIPV6.sin6_family = AF_INET6;
				sinIPV6.sin6_port = htons(port);
				inet_pton(AF_INET6, ip.c_str(), &sinIPV6.sin6_addr);
				sin = &sinIPV6;
			}
			break;
	}

	// bind
	if (::connect(descriptor, (const struct sockaddr*)sin, sinLen) == -1) {
		#if defined(_WIN32)
			throw NetworkSocketException("Could not connect socket: " + to_string(WSAGetLastError()));
		#else
			throw NetworkSocketException("Could not connect socket: " + string(strerror(errno)));
		#endif
	}

	// set address
	this->ip = ip;
	this->port = port;
}

bool TCPSocket::accept(TCPSocket *_socket) {
	struct sockaddr_in _sin;
	socklen_t _sinSize = sizeof(_sin);

	// accept socket
	int _descriptor = ::accept(descriptor, (struct sockaddr *)&_sin, &_sinSize);
	if (_descriptor == -1) {
		// no more connections are present
		if (errno == EAGAIN ||
			errno == EWOULDBLOCK) {
			return false;
		}
		throw NetworkSocketException("Could not accept socket: " + string(strerror(errno)));
	}

	// create client socket, return it
	_socket->descriptor = _descriptor;
	_socket->ip = inet_ntoa(_sin.sin_addr);
	_socket->port = ntohs(_sin.sin_port);
	_socket->setNonBlocked();
	_socket->setTCPNoDelay();

	// success
	return true;
}

size_t TCPSocket::read(void* buf, const size_t bytes) {
	ssize_t bytesRead = ::recv(descriptor, BUF_CAST(buf), bytes, 0);
	if (bytesRead == -1) {
		throw NetworkIOException("Error while reading from socket: " + string(strerror(errno)));
	} else
	if (bytesRead == 0) {
		throw NetworkSocketClosedException("End of stream");
	}
	//
	return (size_t)bytesRead;
}

size_t TCPSocket::write(void* buf, const size_t bytes) {
	#if defined(__APPLE__) || defined(_WIN32)
		ssize_t bytesWritten = ::send(descriptor, BUF_CAST(buf), bytes, 0);
	#else
		ssize_t bytesWritten = ::send(descriptor, BUF_CAST(buf), bytes, MSG_NOSIGNAL);
	#endif
	if (bytesWritten == -1) {
		if (errno == ECONNRESET || errno == EPIPE) {
			throw NetworkSocketClosedException("End of stream: " + string(strerror(errno)));
		} else {
			throw NetworkIOException("Error while writing to socket: " + string(strerror(errno)));
		}
	}
	//
	return (size_t)bytesWritten;
}

