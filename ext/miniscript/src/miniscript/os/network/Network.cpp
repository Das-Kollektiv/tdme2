#include <miniscript/os/network/Network.h>

#include <string.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#if defined(_WIN32)
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	#include <netdb.h>
	#include <arpa/inet.h>
	#include <netinet/in.h>
	#include <sys/socket.h>
#endif

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkException.h>
#include <miniscript/os/network/NetworkSocket.h>
#include <miniscript/utilities/Console.h>

using miniscript::os::network::Network;

using std::string;
using std::to_string;

using miniscript::os::network::NetworkException;
using miniscript::os::network::NetworkSocket;
using miniscript::utilities::Console;

bool Network::initialize() {
	// https support
	SSL_library_init();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	//
	#if defined(_WIN32)
		WSADATA wsaData;
		auto result = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (result != 0) {
			Console::println("WinSock2 initialization failed: " + to_string(result));
			return false;
		}
	#endif
	return true;
}

const string Network::getIpByHostname(const string& hostname) {
	auto hostEnt = gethostbyname(hostname.c_str());

	if (hostEnt == nullptr) {
		throw NetworkException("Could not resolve hostname");
	}

	switch (hostEnt->h_addrtype) {
	case AF_INET:
		if (hostEnt->h_addr_list[0] != nullptr) {
			struct in_addr addr;
			addr.s_addr = *(uint32_t*)hostEnt->h_addr_list[0];
			return string(inet_ntoa(addr));
		}
		break;
	case AF_INET6:
		if (hostEnt->h_addr_list[0] != nullptr) {
			char ipv6AddressString[46];
			return string(inet_ntop(AF_INET6, (in6_addr*)hostEnt->h_addr_list[0], ipv6AddressString, INET6_ADDRSTRLEN) == NULL?"":ipv6AddressString);
		}
		break;
	}

	throw NetworkException("Could not resolve hostname");
}
