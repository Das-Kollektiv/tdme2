/**
 */

#include <tdme/tdme.h>
#include <tdme/os/network/NetworkSocketClosedException.h>

using tdme::os::network::NetworkSocketClosedException;

NetworkSocketClosedException::NetworkSocketClosedException(const string &message) throw() : NetworkIOException(message) {
}

