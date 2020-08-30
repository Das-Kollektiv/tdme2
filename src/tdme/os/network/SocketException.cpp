#include <tdme/os/network/SocketException.h>

#include <string>

#include <tdme/os/network/NetworkException.h>

using tdme::os::network::SocketException;

using std::string;

using tdme::os::network::NetworkException;

SocketException::SocketException(const string &message) throw() : NetworkException(message) {
}

