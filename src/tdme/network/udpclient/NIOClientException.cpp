#include <tdme/network/udpclient/NIOClientException.h>

using tdme::network::udpclient::NIOClientException;

NIOClientException::NIOClientException(const string &message) throw() : NIOException(message) {
}

