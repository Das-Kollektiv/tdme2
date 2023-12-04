/**
 */

#include <miniscript/miniscript.h>
#include <miniscript/os/network/NetworkSocketClosedException.h>

using miniscript::os::network::NetworkSocketClosedException;

NetworkSocketClosedException::NetworkSocketClosedException(const string &message) throw() : NetworkIOException(message) {
}

