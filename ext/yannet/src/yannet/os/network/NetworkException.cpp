#include <yannet/os/network/NetworkException.h>

#include <string>

#include <yannet/yannet.h>
#include <yannet/utilities/ExceptionBase.h>

using yannet::os::network::NetworkException;

using std::string;

using yannet::utilities::ExceptionBase;

NetworkException::NetworkException(const string &message) throw() : ExceptionBase(message) {
}

