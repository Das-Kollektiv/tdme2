#include <minitscript/os/network/NetworkIOException.h>

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/os/network/NetworkException.h>

using std::string;
using minitscript::os::network::NetworkException;
using minitscript::os::network::NetworkIOException;

NetworkIOException::NetworkIOException(const string &message) throw() : NetworkException(message) {
}

