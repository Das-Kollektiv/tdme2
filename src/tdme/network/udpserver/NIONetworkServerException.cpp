#include <tdme/network/udpserver/NIONetworkServerException.h>

using tdme::network::udpserver::NIONetworkServerException;

NIONetworkServerException::NIONetworkServerException(const string &message) throw() : NIOException(message) {
}

