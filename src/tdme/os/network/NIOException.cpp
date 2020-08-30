#include <tdme/os/network/NIOException.h>

#include <string>

#include <tdme/utilities/ExceptionBase.h>

using tdme::os::network::NIOException;

using std::string;

using tdme::utilities::ExceptionBase;

NIOException::NIOException(const string &message) throw() : ExceptionBase(message) {
}

