/**
 * @version $Id: 195918a6413fa6c4091868423121684636669354 $
 */

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>

#include <tdme/os/network/NIOUDPSocket.h>

using std::string;

using tdme::os::network::NIOUDPSocket;

// determine which SO_REUSE option to use
#if defined(__linux__)
	// on linux < 3.9 we need to to use "addr". it behaves like "port" on BSD for UDP sockets
	#define SO_REUSEOPTION	SO_REUSEADDR
#else
	// standard is "port" as it exactly does what we want
	#define SO_REUSEOPTION	SO_REUSEPORT
#endif

NIOUDPSocket::~NIOUDPSocket() {
}

ssize_t NIOUDPSocket::read(string& from, unsigned int& port, void* buf, const size_t bytes) throw (NIOIOException) {
	// read from socket
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);
	ssize_t bytesRead = ::recvfrom(descriptor, buf, bytes, 0, (struct sockaddr *)&sin, &sin_len);
	if (bytesRead == -1) {
		// nope throw an exception
		if (errno == EAGAIN) {
			return -1;
		} else {
			string msg = "error while reading from socket: ";
			msg+= strerror(errno);
			throw NIOIOException(msg);
		}
	}

	// set up senders ip + port
	from = inet_ntoa(sin.sin_addr);
	port = ntohs(sin.sin_port);

	// return bytes read
	return bytesRead;
}

ssize_t NIOUDPSocket::write(const string& to, const unsigned int port, void* buf, const size_t bytes) throw (NIOIOException) {
	// set up receiver
	struct sockaddr_in sin;
	socklen_t sin_len = sizeof(sin);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(to.c_str());
	sin.sin_port = htons(port);

	// go
	#ifdef __APPLE__
		ssize_t bytesWritten = ::sendto(descriptor, buf, bytes, 0, (const struct sockaddr*)&sin, sin_len);
	#else
		ssize_t bytesWritten = ::sendto(descriptor, buf, bytes, MSG_NOSIGNAL, (const struct sockaddr*)&sin, sin_len);
	#endif

	// send successful?
	if (bytesWritten == -1) {
		// nope throw an exception
		if (errno == EAGAIN) {
			return -1;
		} else {
			string msg = "error while writing to socket: ";
			msg+= strerror(errno);
			throw NIOIOException(msg);
		}
	}

	// return bytes written
	return bytesWritten;
}

void NIOUDPSocket::create(NIOUDPSocket& socket) throw (NIOSocketException) {
	socket.descriptor = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (socket.descriptor == -1) {
		string msg = "Could not create socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}
	#ifdef __APPLE__
		int flag = 1;
		if (setsockopt(socket.descriptor, SOL_SOCKET, SO_NOSIGPIPE, (void*)&flag, sizeof(flag)) == -1) {
			string msg = "Could not set no sig pipe on socket: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	#endif
}

void NIOUDPSocket::createServerSocket(NIOUDPSocket& socket, const string& ip, const unsigned int port) throw (NIOSocketException) {
	// create socket
	NIOUDPSocket::create(socket);

	try {
		// set non blocked
		socket.setNonBlocked();

		// enable socket reuse port
		int flag = 1;
		if (setsockopt(socket.descriptor, SOL_SOCKET, SO_REUSEOPTION, (void*)&flag, sizeof(flag)) == -1) {
			string msg = "Could not set reuse port on socket: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}

		// bind socket to host
		socket.bind(ip, port);

	} catch (NIOSocketException &exception) {
		socket.close();
		throw;
	}
}
