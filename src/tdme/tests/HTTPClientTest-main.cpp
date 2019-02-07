#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/utils/Character.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/Integer.h>
#include <tdme/utils/StringTokenizer.h>

#include <tdme/os/network/Network.h>
#include <tdme/os/network/NIOTCPSocket.h>

using std::hex;
using std::nouppercase;
using std::ostringstream;
using std::setw;
using std::string;
using std::stringstream;
using std::to_string;
using std::unordered_map;
using std::uppercase;
using std::vector;

using tdme::os::network::Network;
using tdme::os::network::NIOTCPSocket;
using tdme::utils::Character;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::Integer;
using tdme::utils::StringTokenizer;

string urlEncode(const string &value) {
	// see: https://stackoverflow.com/questions/154536/encode-decode-urls-in-c
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (Character::isAlphaNumeric(c) == true || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

static const int16_t HTTP_STATUSCODE_OK = 200;

static const string HTTP_METHOD_GET = "GET";
static const string HTTP_METHOD_HEAD = "HEAD";
static const string HTTP_METHOD_POST = "POST";
static const string HTTP_METHOD_PUT = "PUT";
static const string HTTP_METHOD_DELETE = "DELETE";


string createHTTPRequestHeaders(const string& hostName, const string& method, const string& relativeUrl, const unordered_map<string, string>& getParameters, const unordered_map<string, string>& postParameters, const string& body) {
	string query;
	for (auto getParameterIt: getParameters) {
		if (query.size() == 0) query+= "?"; else query+="&amp;";
		query+= urlEncode(getParameterIt.first) + "=" + urlEncode(getParameterIt.second);
	}
	auto request =
		string(method + " " + relativeUrl + query + " HTTP/1.1\r\n") +
		string("User-Agent: tdme2-httpclient\r\n") +
		string("Host: " + hostName + "\r\n") +
		string("Connection: close\r\n");
	if (method == HTTP_METHOD_POST || method == HTTP_METHOD_PUT) {
		string _body;
		if (postParameters.size() > 0) {
			for (auto postParameterIt: postParameters) {
				if (_body.size() >= 0) _body+="&amp;";
				_body+= urlEncode(postParameterIt.first) + "=" + urlEncode(postParameterIt.second);
			}
		} else {
			_body = body;
		}
		request+= "Content-Length: " + to_string(_body.size()) + "\r\n\r\n";
		request+= _body;
	} else {
		request+= "\r\n";
	}
	return request;
}

void parseHttpResponseHeaders(stringstream& rawResponse, int16_t& httpStatusCode, vector<string>& httpHeader) {
	string lastLine;
	string line;
	char lastChar = -1;
	char currentChar;
	while (rawResponse.eof() == false) {
		rawResponse.get(currentChar);
		if (lastChar == '\r' && currentChar == '\n') {
			if (line.size() != 0) {
				httpHeader.push_back(line);
			}
			lastLine = line;
			if (line.size() == 0 && lastLine.size() == 0) break;
			line.clear();
		} else
		if (currentChar != '\r' && currentChar != '\n') {
			line+= currentChar;
		}
		lastChar = currentChar;
	}
	if (httpHeader.size() > 0) {
		StringTokenizer t;
		t.tokenize(httpHeader[0], " ");
		for (auto i = 0; i < 3 && t.hasMoreTokens(); i++) {
			auto token = t.nextToken();
			if (i == 1) {
				httpStatusCode = Integer::parseInt(token);
			}
		}
	}
}

int main(int argc, char *argv[]) {
	try {
		Network::initialize();
		Console::println(Network::getIpByHostName("www.drewke.net"));
		NIOTCPSocket socket;
		NIOTCPSocket::create(socket, NIOTCPSocket::determineIpVersion("172.217.17.110"));
		socket.connect("172.217.17.110", 80);
		auto request = createHTTPRequestHeaders("www.google.com", HTTP_METHOD_GET, "/", {{"q", "tdme2"}}, {}, string());
		Console::println("Request: ");
		Console::println(request);
		socket.write((void*)request.data(), request.length());
		stringstream rawResponse;
		char rawResponseBuf[16384];
		auto rawResponseBytesRead = 0;
		do {
			auto rawResponseBytesRead = socket.read(rawResponseBuf, sizeof(rawResponseBuf));
			rawResponse.write(rawResponseBuf, rawResponseBytesRead);
		} while (rawResponseBytesRead == sizeof(rawResponseBuf));
		int16_t httpStatusCode;
		vector<string> httpHeader;
		parseHttpResponseHeaders(rawResponse, httpStatusCode, httpHeader);
		Console::println("HTTP status code: " + to_string(httpStatusCode));
		for (auto header: httpHeader) {
			Console::println("Header: " + header);
		}
		string response;
		Console::println("Response: ");
		char c;
		while (rawResponse.eof() == false) {
			rawResponse.get(c);
			Console::print(string() + c);
		}
		Console::println();
		socket.shutdown();
	} catch (Exception& exception) {
		Console::println(string("Fail: ") + exception.what());
	}
}

