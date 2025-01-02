/**
 */

#include <yannet/yannet.h>
#include <yannet/os/network/NetworkSocketClosedException.h>

using yannet::os::network::NetworkSocketClosedException;

NetworkSocketClosedException::NetworkSocketClosedException(const string &message) throw() : NetworkIOException(message) {
}

