#include <sstream>

#include <tdme/network/udpserver/NIOServerClient.h>

using std::stringstream;

using tdme::network::udpserver::NIOServerClient;

const char* NIOServerClient::KEY_PREFIX_UNNAMED = "unnamed.";

stringstream* NIOServerClient::createFrame() {
	return new stringstream();
}
