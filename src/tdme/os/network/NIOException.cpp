#include <tdme/os/network/NIOException.h>

#include <string>

#include <tdme/utils/ExceptionBase.h>

using tdme::os::network::NIOException;

using std::string;

using tdme::utils::ExceptionBase;

NIOException::NIOException(const string &message) throw() : ExceptionBase(message) {
}

