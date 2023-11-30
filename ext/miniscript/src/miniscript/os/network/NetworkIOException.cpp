#include <miniscript/os/network/NetworkIOException.h>

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkException.h>

using std::string;
using miniscript::os::network::NetworkException;
using miniscript::os::network::NetworkIOException;

NetworkIOException::NetworkIOException(const string &message) throw() : NetworkException(message) {
}

