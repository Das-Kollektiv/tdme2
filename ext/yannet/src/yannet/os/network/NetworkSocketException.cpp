#include <yannet/os/network/NetworkSocketException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkException.h>

using yannet::os::network::NetworkSocketException;

using std::string;

using yannet::os::network::NetworkException;

NetworkSocketException::NetworkSocketException(const string &message) throw() : NetworkException(message) {
}

