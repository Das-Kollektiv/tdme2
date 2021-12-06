#include <tdme/os/network/NetworkException.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/utilities/ExceptionBase.h>

using tdme::os::network::NetworkException;

using std::string;

using tdme::utilities::ExceptionBase;

NetworkException::NetworkException(const string &message) throw() : ExceptionBase(message) {
}

