#include <tdme/os/network/NIOSocketException.h>

#include <string>

#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOSocketException;

using std::string;

using tdme::os::network::NIOException;

NIOSocketException::NIOSocketException(const string &message) throw() : NIOException(message) {
}

