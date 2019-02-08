#include <tdme/os/network/Network.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/network/httpclient/HTTPClient.h>

using std::string;
using std::stringstream;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::network::httpclient::HTTPClient;
using tdme::os::network::Network;
using tdme::utils::Console;
using tdme::utils::Exception;

int main(int argc, char *argv[]) {
	Network::initialize();

	try {
		HTTPClient httpClient;
		httpClient.setMethod(HTTPClient::HTTP_METHOD_GET);
		httpClient.setURL("http://www.drewke.net/tdme2/");
		httpClient.execute();
		Console::println("HTTP status code: " + to_string(httpClient.getStatusCode()));
		for (auto header: httpClient.getResponseHeaders()) {
			Console::println("Header: " + header);
		}
		Console::println("Response: ");
		char c;
		while (httpClient.getResponse().eof() == false) {
			httpClient.getResponse().get(c);
			Console::print(string() + c);
		}
		Console::println();
	} catch (Exception& exception) {
		Console::println(string("Fail: ") + exception.what());
	}
}

