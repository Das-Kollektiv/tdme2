#include <tdme/os/network/NIOIOException.h>

#include <string>

#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOException;
using tdme::os::network::NIOIOException;
using std::string;

NIOIOException::NIOIOException(const string &message) throw() : NIOException(message) {
}

