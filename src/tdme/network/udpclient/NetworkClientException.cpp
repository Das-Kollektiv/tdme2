#include <string>

#include <tdme/tdme.h>
#include <tdme/network/udpclient/NetworkClientException.h>

using std::string;

using tdme::network::udpclient::NetworkClientException;

NetworkClientException::NetworkClientException(const string &message) throw() : NetworkException(message) {
}

