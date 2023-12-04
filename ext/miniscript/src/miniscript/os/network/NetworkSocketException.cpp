#include <miniscript/os/network/NetworkSocketException.h>

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkException.h>

using miniscript::os::network::NetworkSocketException;

using std::string;

using miniscript::os::network::NetworkException;

NetworkSocketException::NetworkSocketException(const string &message) throw() : NetworkException(message) {
}

