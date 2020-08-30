#include <tdme/os/network/KEMException.h>

#include <string>

#include <tdme/os/network/NetworkException.h>

using tdme::os::network::NetworkException;
using tdme::os::network::KEMException;
using std::string;

KEMException::KEMException(const string &message) throw() : NetworkException(message) {
}

