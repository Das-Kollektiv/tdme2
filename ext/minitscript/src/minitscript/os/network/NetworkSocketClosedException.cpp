/**
 */

#include <minitscript/minitscript.h>
#include <minitscript/os/network/NetworkSocketClosedException.h>

using minitscript::os::network::NetworkSocketClosedException;

NetworkSocketClosedException::NetworkSocketClosedException(const string &message) throw() : NetworkIOException(message) {
}

