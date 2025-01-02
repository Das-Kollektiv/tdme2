#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>

#include <yannet/network/httpclient/HTTPClient.h>
#include <yannet/os/network/Network.h>

using std::string;
using std::stringstream;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::utilities::Console;
using tdme::utilities::Exception;

using yannet::network::httpclient::HTTPClient;
using yannet::os::network::Network;

int main(int argc, char *argv[]) {
	Network::initialize();
	//
	try {
		HTTPClient httpClient;
		httpClient.setMethod(HTTPClient::HTTP_METHOD_GET);
		httpClient.setURL("http://www.drewke.net/tdme2/");
		httpClient.execute();
		Console::printLine("HTTP status code: " + to_string(httpClient.getStatusCode()));
		for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
			Console::printLine("Response Header: " + headerName + ": " + headerValue);
		}
		Console::printLine("Response: ");
		char c;
		while (httpClient.getResponse().eof() == false) {
			httpClient.getResponse().get(c);
			Console::print(string() + c);
		}
		Console::printLine();
	} catch (Exception& exception) {
		Console::printLine(string("Fail: ") + exception.what());
	}
	//
	Console::shutdown();
	return 0;
}

