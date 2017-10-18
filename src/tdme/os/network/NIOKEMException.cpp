#include <tdme/os/network/NIOKEMException.h>

#include <string>

#include <tdme/os/network/NIOException.h>

using tdme::os::network::NIOException;
using tdme::os::network::NIOKEMException;
using std::string;

NIOKEMException::NIOKEMException(const string &message) throw() : NIOException(message) {
}

