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
	ipVersion = socket.ipVersion;
	return *this;
}

NIONetworkSocket::NIONetworkSocket() : descriptor(-1), ip("0.0.0.0"), port(0), ipVersion(IpVersion::IPV4) {
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
				memset(&sinIPV4, 0, sizeof(sinIPV4));
				sinIPV4.sin_family = AF_INET;
				sinIPV4.sin_port = htons(port);
				sinIPV4.sin_addr.s_addr = inet_addr(ip.c_str());
				sin = &sinIPV4;
				sinLen = sizeof(sockaddr_in);
			}
			break;
		case IPV6:
			{

				memset(&sinIPV6, 0, sizeof(sinIPV6));
				sinIPV6.sin6_family = AF_INET6;
				sinIPV6.sin6_port = htons(port);
				inet_pton(AF_INET6, ip.c_str(), &sinIPV6.sin6_addr);
				sin = &sinIPV6;
				sinLen = sizeof(sockaddr_in6);
			}
	}

	// bind
	if (::bind(descriptor, (const struct sockaddr*)sin, sinLen) == -1) {
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
		unsigned int mode = 1;
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
	#if defined(_WIN32)
		::closesocket(descriptor);
	#else
		::close(descriptor);
	#endif
	descriptor = -1;
}

NIONetworkSocket::IpVersion NIONetworkSocket::determineIpVersion(const string& ip) {
	return ip.find(':') != std::string::npos?IpVersion::IPV6:IpVersion::IPV4;
}
