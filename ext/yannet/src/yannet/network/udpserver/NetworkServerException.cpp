#include <yannet/yannet.h>
#include <yannet/network/udpserver/NetworkServerException.h>

using yannet::network::udpserver::NetworkServerException;

NetworkServerException::NetworkServerException(const string &message) throw() : NetworkException(message) {
}

