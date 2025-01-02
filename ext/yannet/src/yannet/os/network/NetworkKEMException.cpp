#include <yannet/os/network/NetworkKEMException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkException.h>

using std::string;
using yannet::os::network::NetworkException;
using yannet::os::network::NetworkKEMException;

NetworkKEMException::NetworkKEMException(const string &message) throw() : NetworkException(message) {
}

