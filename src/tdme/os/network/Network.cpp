#include <tdme/os/network/Network.h>

#if defined(_WIN32)
	#include <winsock2.h>
#endif

#include <string>

#include <tdme/utils/Console.h>

using tdme::os::network::Network;

using std::to_wstring;

using tdme::utils::Console;

bool Network::initialize() {
	#if defined(_WIN32)
		WSADATA wsaData;
		int result;
		result = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (result != 0) {
			Console::println(L"WinSock2 initialization failed: " + to_wstring(result));
			return false;
		}
	#endif
	return true;
}

