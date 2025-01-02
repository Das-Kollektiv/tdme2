#include <string>

#include <yannet/yannet.h>
#include <yannet/network/udpclient/NetworkClientException.h>

using std::string;

using yannet::network::udpclient::NetworkClientException;

NetworkClientException::NetworkClientException(const string &message) throw() : NetworkException(message) {
}

