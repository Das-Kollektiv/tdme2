#include <yannet/os/network/NetworkIOException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkException.h>

using std::string;
using yannet::os::network::NetworkException;
using yannet::os::network::NetworkIOException;

NetworkIOException::NetworkIOException(const string &message) throw() : NetworkException(message) {
}

