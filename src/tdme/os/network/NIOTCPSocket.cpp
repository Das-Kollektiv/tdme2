#include <tdme/os/network/NIOTCPSocket.h>

#include <string>

#include <tdme/os/network/NIOIOException.h>
#include <tdme/os/network/NIONetworkSocket.h>
#include <tdme/os/network/NIOSocketException.h>
#include <tdme/os/network/NIOIOSocketClosedException.h>

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

using tdme::os::network::NIOTCPSocket;

using std::to_string;

using tdme::os::network::NIOIOException;
using tdme::os::network::NIONetworkSocket;
using tdme::os::network::NIOSocketException;
using tdme::os::network::NIOIOSocketClosedException;

/**
 * @brief public destructor
 */
NIOTCPSocket::~NIOTCPSocket() {
}

size_t NIOTCPSocket::read(void* buf, const size_t bytes) throw (NIOIOException) {
	ssize_t bytesRead = ::recv(descriptor, BUF_CAST(buf), bytes, 0);
	if (bytesRead == -1) {
		std::string msg = "error while reading from socket: ";
		msg+= strerror(errno);
		throw NIOIOException(msg);
	} else
	if (bytesRead == 0) {
		throw NIOIOSocketClosedException("end of stream");
	}
	//
	return (size_t)bytesRead;
}

size_t NIOTCPSocket::write(void* buf, const size_t bytes) throw (NIOIOException) {
	#if defined(__APPLE__) || defined(_WIN32)
		ssize_t bytesWritten = ::send(descriptor, BUF_CAST(buf), bytes, 0);
	#else
		ssize_t bytesWritten = ::send(descriptor, BUF_CAST(buf), bytes, MSG_NOSIGNAL);
	#endif
	if (bytesWritten == -1) {
		if (errno == ECONNRESET || errno == EPIPE) {
			std::string msg = "end of stream: ";
			msg+= strerror(errno);
			throw NIOIOSocketClosedException(msg);
		} else {
			std::string msg = "error while writing to socket: ";
			msg+= strerror(errno);
			throw NIOIOException(msg);
		}
	}
	//
	return (size_t)bytesWritten;
}

void NIOTCPSocket::create(NIOTCPSocket& socket, IpVersion ipVersion) throw (NIOSocketException) {
	socket.ipVersion = ipVersion;
	socket.descriptor = ::socket(ipVersion == IPV6?PF_INET6:PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (socket.descriptor == -1) {
		std::string msg = "Could not create socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}
	#if defined(__APPLE__)
		int flag = 1;
		if (setsockopt(socket.descriptor, SOL_SOCKET, SO_NOSIGPIPE, (void*)&flag, sizeof(flag)) == -1) {
			std::string msg = "Could not set no sig pipe on socket: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	#endif
}

void NIOTCPSocket::connect(const std::string& ip, const unsigned int port) throw (NIOSocketException) {
	// determine IP version
	ipVersion = determineIpVersion(ip);

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
		std::string msg = "Could not connect socket: ";
		#if defined(_WIN32)
			msg+= to_string(WSAGetLastError());
		#else
			msg+= strerror(errno);
		#endif
		throw NIOSocketException(msg);
	}

	// set address
	this->ip = ip;
	this->port = port;
}
void NIOTCPSocket::createServerSocket(NIOTCPSocket& socket, const std::string& ip, const unsigned int port, const int backlog) throw (NIOSocketException) {
	// create socket
	NIOTCPSocket::create(socket, determineIpVersion(ip));

	try {
		// set non blocked
		socket.setNonBlocked();

		// bind
		socket.bind(ip, port);

		// make socket listen, backlog is 10% of max CCU
		if (listen(socket.descriptor, backlog) == -1) {
			std::string msg = "Could not set socket to listen: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	} catch (NIOSocketException &exception) {
		socket.close();
		throw;
	}
}

void NIOTCPSocket::setTCPNoDelay() throw (NIOSocketException) {
	int flag = 1;
	#if defined(_WIN32)
		if (setsockopt(descriptor, IPPROTO_TCP, TCP_NODELAY, (const char*)&flag, sizeof(flag)) == -1) {
	#else
		if (setsockopt(descriptor, IPPROTO_TCP, TCP_NODELAY, (void*)&flag, sizeof(flag)) == -1) {
	#endif
		std::string msg = "Could not set tcp no delay: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}
}

bool NIOTCPSocket::accept(NIOTCPSocket &_socket) throw (NIOSocketException) {
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
		std::string msg = "Could not accept socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}

	// create client socket, return it
	_socket.descriptor = _descriptor;
	_socket.ip = inet_ntoa(_sin.sin_addr);
	_socket.port = ntohs(_sin.sin_port);
	_socket.setNonBlocked();
	_socket.setTCPNoDelay();

	// success
	return true;
}
