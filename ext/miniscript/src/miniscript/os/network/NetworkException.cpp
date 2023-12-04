#include <miniscript/os/network/NetworkException.h>

#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/ExceptionBase.h>

using miniscript::os::network::NetworkException;

using std::string;

using miniscript::utilities::ExceptionBase;

NetworkException::NetworkException(const string &message) throw() : ExceptionBase(message) {
}

