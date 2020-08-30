#include <tdme/network/udpclient/ClientException.h>

using tdme::network::udpclient::ClientException;

ClientException::ClientException(const string &message) throw() : NetworkException(message) {
}

