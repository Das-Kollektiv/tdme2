#include <minitscript/os/network/NetworkSocketException.h>

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/os/network/NetworkException.h>

using minitscript::os::network::NetworkSocketException;

using std::string;

using minitscript::os::network::NetworkException;

NetworkSocketException::NetworkSocketException(const string &message) throw() : NetworkException(message) {
}

