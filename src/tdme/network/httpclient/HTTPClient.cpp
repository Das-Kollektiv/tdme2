#include <tdme/network/httpclient/HTTPClient.h>

#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/httpclient/HTTPClientException.h>
#include <tdme/os/network/Network.h>
#include <tdme/os/network/NetworkSocketClosedException.h>
#include <tdme/os/network/SecureTCPSocket.h>
#include <tdme/os/network/TCPSocket.h>
#include <tdme/utilities/Base64.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::hex;
using std::make_unique;
using std::nouppercase;
using std::ostringstream;
using std::setw;
using std::string;
using std::stringstream;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::uppercase;
using std::vector;

using tdme::network::httpclient::HTTPClientException;
using tdme::os::network::Network;
using tdme::os::network::NetworkSocketClosedException;
using tdme::os::network::SecureTCPSocket;
using tdme::os::network::TCPSocket;
using tdme::utilities::Base64;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

using tdme::network::httpclient::HTTPClient;

const string HTTPClient::HTTP_METHOD_GET = "GET";
const string HTTPClient::HTTP_METHOD_HEAD = "HEAD";
const string HTTPClient::HTTP_METHOD_POST = "POST";
const string HTTPClient::HTTP_METHOD_PUT = "PUT";
const string HTTPClient::HTTP_METHOD_DELETE = "DELETE";

string HTTPClient::urlEncode(const string &value) {
	// TODO: put me into utilities
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

string HTTPClient::createHTTPRequestHeaders(const string& hostname, const string& relativeUrl, const string& body) {
	string query;
	for (const auto& [parameterName, parameterValue]: getParameters) {
		if (query.empty() == true) query+= "?"; else query+="&";
		query+= urlEncode(parameterName) + "=" + urlEncode(parameterValue);
	}
	auto request =
		string(method + " " + relativeUrl + query + " HTTP/1.1\r\n") +
		string("User-Agent: tdme2-httpclient\r\n") +
		string("Accept-Charset: UTF-8\r\n") +
		string("Host: " + hostname + "\r\n") +
		string("Connection: close\r\n");
	if (username.empty() == false || password.empty() == false) {
		string base64Pass;
		Base64::encode(username + ":" + password, base64Pass);
		request+= "Authorization: Basic " + base64Pass + "\r\n";
	}
	if (contentType.size() > 0) {
		request+=
			string("Content-Type: " + contentType + "\r\n");
	}
	for (const auto& [headerName, headerValue]: headers) {
		request+= headerName + ": " + headerValue + "\r\n";
	}
	if (method == HTTP_METHOD_POST || method == HTTP_METHOD_PUT) {
		string _body;
		if (postParameters.size() > 0) {
			for (const auto& [parameterName, parameterValue]: postParameters) {
				if (_body.size() >= 0) _body+="&";
				_body+= urlEncode(parameterName) + "=" + urlEncode(parameterValue);
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

void HTTPClient::parseHTTPResponseHeaders(stringstream& rawResponse) {
	int headerIdx = 0;
	string statusHeader;
	string line;
	char lastChar = -1;
	char currentChar;
	while (rawResponse.eof() == false) {
		rawResponse.get(currentChar);
		if (lastChar == '\r' && currentChar == '\n') {
			if (line.empty() == false) {
				if (headerIdx == 0) {
					statusHeader = line;
					headerIdx++;
				} else {
					auto headerNameValueSeparator = StringTools::indexOf(line, ':');
					responseHeaders[StringTools::trim(StringTools::substring(line, 0, headerNameValueSeparator))] =
						StringTools::trim(StringTools::substring(line, headerNameValueSeparator + 1));
				}
			} else {
				break;
			}
			line.clear();
		} else
		if (currentChar != '\r' && currentChar != '\n') {
			line+= currentChar;
		}
		lastChar = currentChar;
	}
	if (statusHeader.empty() == false) {
		StringTokenizer t;
		t.tokenize(statusHeader, " ");
		for (auto i = 0; i < 3 && t.hasMoreTokens(); i++) {
			auto token = t.nextToken();
			if (i == 1) {
				statusCode = Integer::parse(token);
			}
		}
	}
}

void HTTPClient::reset() {
	url.clear();
	method.clear();
	headers.clear();
	getParameters.clear();
	postParameters.clear();
	body.clear();
	contentType.clear();

	rawResponse.clear();
	statusCode = -1;
	responseHeaders.clear();
}

void HTTPClient::execute() {
	//
	unique_ptr<TCPSocket> socket;
	try {
		// TODO: we might need a class to determine protocol, hostname and port, yaaar
		auto protocolSeparatorIdx = StringTools::indexOf(url, string("://"));
		if (protocolSeparatorIdx == -1) throw HTTPClientException("Invalid URL");
		auto relativeUrl = StringTools::substring(url, protocolSeparatorIdx + 3);
		if (relativeUrl.empty() == true) throw HTTPClientException("No URL given");
		auto slashIdx = relativeUrl.find('/');
		auto hostname = relativeUrl;
		if (slashIdx != -1) hostname = StringTools::substring(relativeUrl, 0, slashIdx);
		relativeUrl = StringTools::substring(relativeUrl, hostname.size());
		//
		if (StringTools::startsWith(url, "http://") == true) {
			auto ip = Network::getIpByHostname(hostname);
			if (ip.empty() == true) {
				Console::println("HTTPClient::execute(): failed");
				throw HTTPClientException("Could not resolve host IP by hostname");
			}
			//
			socket = make_unique<TCPSocket>();
			socket->connect(ip, 80);
		} else
		if (StringTools::startsWith(url, "https://") == true) {
			socket = make_unique<SecureTCPSocket>();
			socket->connect(hostname, 443);
		} else {
			throw HTTPClientException("Invalid protocol");
		}
		//
		auto request = createHTTPRequestHeaders(hostname, relativeUrl, body);
		socket->write((void*)request.data(), request.length());

		char rawResponseBuf[16384];
		auto rawResponseBytesRead = 0;
		try {
			for (;true;) {
				auto rawResponseBytesRead = socket->read(rawResponseBuf, sizeof(rawResponseBuf));
				rawResponse.write(rawResponseBuf, rawResponseBytesRead);
			};
		} catch (NetworkSocketClosedException& sce) {
			// end of stream
		}

		//
		parseHTTPResponseHeaders(rawResponse);

		//
		socket->shutdown();
	} catch (Exception& exception) {
		if (socket != nullptr) socket->shutdown();
		//
		Console::println(string("HTTPClient::execute(): performed HTTP request: FAILED: ") + exception.what());
		// rethrow
		throw;
	}

}
