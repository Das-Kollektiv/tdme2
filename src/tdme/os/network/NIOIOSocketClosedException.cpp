/**
 * @version $Id: 4e34499120297e23dd0002a1f2f70a59cbfdfe7d $
 */

#include <tdme/os/network/NIOIOSocketClosedException.h>

using tdme::os::network::NIOIOSocketClosedException;

NIOIOSocketClosedException::NIOIOSocketClosedException(const string &message) throw() : NIOIOException(message) {
}

