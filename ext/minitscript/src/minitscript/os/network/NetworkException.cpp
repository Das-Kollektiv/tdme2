#include <minitscript/os/network/NetworkException.h>

#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/ExceptionBase.h>

using minitscript::os::network::NetworkException;

using std::string;

using minitscript::utilities::ExceptionBase;

NetworkException::NetworkException(const string &message) throw() : ExceptionBase(message) {
}

