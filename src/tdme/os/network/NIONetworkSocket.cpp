#include <string.h>

#if defined(_WIN32)
	#include <winsock2.h>
	#define SHUT_RDWR SD_BOTH	
#else
	#include <errno.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
#endif

#include <tdme/os/network/NIONetworkSocket.h>

using tdme::os::network::NIONetworkSocket;

NIONetworkSocket& NIONetworkSocket::operator=(NIONetworkSocket& socket) {
	descriptor = socket.descriptor;
	ip = socket.ip;
	return *this;
}

NIONetworkSocket::NIONetworkSocket() : descriptor(-1), ip("0.0.0.0"), port(0) {
}

NIONetworkSocket::~NIONetworkSocket() {
}

const std::string& NIONetworkSocket::getAddress() {
	return ip;
}

const unsigned int NIONetworkSocket::getPort() {
	return port;
}

void NIONetworkSocket::shutdown() {
	::shutdown(descriptor, SHUT_RDWR);
}

void NIONetworkSocket::bind(const std::string& ip, const unsigned int port) throw (NIOSocketException) {
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(ip.c_str());
	sin.sin_port = htons(port);
	if (::bind(descriptor, (const struct sockaddr*)&sin, sizeof(sin)) == -1) {
		std::string msg = "Could not bind socket: ";
		msg+= strerror(errno);
		throw NIOSocketException(msg);
	}

	// set address
	this->ip = ip;
	this->port = port;
}

void NIONetworkSocket::setNonBlocked() throw (NIOSocketException) {
	#if defined(_WIN32)
		u_long mode = 1;
		ioctlsocket(descriptor, FIONBIO, &mode);
	#else
		// get the server socket file descriptor control settings
		int fdc = fcntl(descriptor, F_GETFL, 0);
		if (fdc == -1) {
			std::string msg = "Could not get socket file descriptor settings: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}

		// make the socket non blocked
		if (fcntl(descriptor, F_SETFL, fdc | O_NONBLOCK) == -1) {
			std::string msg = "Could not set socket non blocked: ";
			msg+= strerror(errno);
			throw NIOSocketException(msg);
		}
	#endif
}

void NIONetworkSocket::close() {
	::closesocket(descriptor);
	descriptor = -1;
}
