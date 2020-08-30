/**
 * @version $Id: 4e34499120297e23dd0002a1f2f70a59cbfdfe7d $
 */

#include <tdme/os/network/SocketClosedException.h>

using tdme::os::network::SocketClosedException;

SocketClosedException::SocketClosedException(const string &message) throw() : NetworkIOException(message) {
}

