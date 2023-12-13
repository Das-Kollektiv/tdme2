#include <miniscript/network/httpclient/HTTPDownloadClient.h>

#include <iomanip>
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/network/httpclient/HTTPClientException.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/os/network/Network.h>
#include <miniscript/os/network/NetworkSocketClosedException.h>
#include <miniscript/os/network/SecureTCPSocket.h>
#include <miniscript/os/network/TCPSocket.h>
#include <miniscript/os/threading/Mutex.h>
#include <miniscript/os/threading/Thread.h>
#include <miniscript/utilities/Base64.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/StringTokenizer.h>
#include <miniscript/utilities/StringTools.h>

using std::hex;
using std::make_unique;
using std::nouppercase;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::ostringstream;
using std::setw;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::uppercase;
using std::vector;

using miniscript::math::Math;
using miniscript::network::httpclient::HTTPClientException;
using miniscript::os::filesystem::FileSystem;
using miniscript::os::network::Network;
using miniscript::os::network::NetworkSocketClosedException;
using miniscript::os::network::SecureTCPSocket;
using miniscript::os::network::TCPSocket;
using miniscript::os::threading::Mutex;
using miniscript::os::threading::Thread;
using miniscript::utilities::Base64;
using miniscript::utilities::Character;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::Integer;
using miniscript::utilities::StringTokenizer;
using miniscript::utilities::StringTools;

using miniscript::network::httpclient::HTTPDownloadClient;

HTTPDownloadClient::HTTPDownloadClient(): downloadThreadMutex("downloadthread-mutex") {
}

string HTTPDownloadClient::urlEncode(const string &value) {
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

string HTTPDownloadClient::createHTTPRequestHeaders(const string& hostName, const string& relativeUrl) {
	string query;
	for (const auto& [parameterName, parameterValue]: getParameters) {
		if (query.empty() == true) query+= "?"; else query+="&";
		query+= urlEncode(parameterName) + "=" + urlEncode(parameterValue);
	}
	auto request =
		string("GET " + relativeUrl + query + " HTTP/1.1\r\n") +
		string("User-Agent: tdme2-httpdownloadclient\r\n") +
		string("Host: " + hostName + "\r\n") +
		string("Connection: close\r\n");
	if (username.empty() == false || password.empty() == false) {
		string base64Pass;
		Base64::encode(username + ":" + password, base64Pass);
		request+= "Authorization: Basic " + base64Pass + "\r\n";
	}
	for (const auto& [headerName, headerValue]: headers) {
		request+= headerName + ": " + headerValue + "\r\n";
	}
	request+=
		string("\r\n");
	return request;
}

uint64_t HTTPDownloadClient::parseHTTPResponseHeaders(ifstream& rawResponse) {
	responseHeaders.clear();
	auto headerSize = 0ll;
	auto returnHeaderSize = 0ll;
	int headerIdx = 0;
	string statusHeader;
	string line;
	char lastChar = -1;
	char currentChar;
	while (rawResponse.eof() == false) {
		rawResponse.get(currentChar);
		headerSize++;
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
				returnHeaderSize = headerSize;
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
	//
	return returnHeaderSize;
}

void HTTPDownloadClient::reset() {
	url.clear();
	file.clear();
	headers.clear();
	getParameters.clear();
	statusCode = -1;
	responseHeaders.clear();
	//
	haveHeaders = false;
	haveContentSize = false;
	headerSize = 0LL;
	contentSize = 0LL;
	finished = true;
	progress = 0.0f;
}

void HTTPDownloadClient::start() {
	class DownloadThread: public Thread {
		public:
			DownloadThread(HTTPDownloadClient* downloadClient): Thread("download-thread"), downloadClient(downloadClient) {
			}
		private:
			void run() {
				downloadClient->finished = false;
				downloadClient->progress = 0.0f;
				unique_ptr<TCPSocket> socket;
				try {
					// TODO: we might need a class to determine protocol, hostname and port, yaaar
					auto protocolSeparatorIdx = StringTools::indexOf(downloadClient->url, string("://"));
					if (protocolSeparatorIdx == -1) throw HTTPClientException("Invalid URL");
					auto relativeUrl = StringTools::substring(downloadClient->url, protocolSeparatorIdx + 3);
					if (relativeUrl.empty() == true) throw HTTPClientException("No URL given");
					auto slashIdx = relativeUrl.find('/');
					auto hostname = relativeUrl;
					if (slashIdx != -1) hostname = StringTools::substring(relativeUrl, 0, slashIdx);
					relativeUrl = StringTools::substring(relativeUrl, hostname.size());
					// socket
					if (StringTools::startsWith(downloadClient->url, "http://") == true) {
						//
						auto ip = Network::getIpByHostname(hostname);
						if (ip.empty() == true) {
							Console::println("HTTPDownloadClient::execute(): failed");
							throw HTTPClientException("Could not resolve host IP by hostname");
						}
						//
						socket = make_unique<TCPSocket>();
						socket->connect(ip, 80);
					} else
					if (StringTools::startsWith(downloadClient->url, "https://") == true) {
						socket = make_unique<SecureTCPSocket>();
						socket->connect(hostname, 443);
					} else {
						throw HTTPClientException("Invalid protocol");
					}
					//
					auto request = downloadClient->createHTTPRequestHeaders(hostname, relativeUrl);
					socket->write((void*)request.data(), request.length());

					{
						// output file stream
						ofstream ofs(std::filesystem::u8path(downloadClient->file + ".download"), ofstream::binary);
						if (ofs.is_open() == false) {
							throw HTTPClientException("Unable to open file for writing(" + to_string(errno) + "): " + (downloadClient->file + ".download"));
						}

						// download
						char rawResponseBuf[16384];
						auto rawResponseBytesRead = 0;
						uint64_t bytesRead = 0;
						try {
							for (;isStopRequested() == false;) {
								auto rawResponseBytesRead = socket->read(rawResponseBuf, sizeof(rawResponseBuf));
								ofs.write(rawResponseBuf, rawResponseBytesRead);
								if (downloadClient->haveHeaders == false) {
									// flush download file to disk
									ofs.flush();
									// input file stream
									ifstream ifs(std::filesystem::u8path(downloadClient->file + ".download"), ofstream::binary);
									if (ifs.is_open() == false) {
										throw HTTPClientException("Unable to open file for reading(" + to_string(errno) + "): " + (downloadClient->file + ".download"));
									}
									// try to read headers
									downloadClient->responseHeaders.clear();
									if ((downloadClient->headerSize = downloadClient->parseHTTPResponseHeaders(ifs)) > 0) {
										downloadClient->haveHeaders = true;
										auto contentLengthHeaderIt = downloadClient->responseHeaders.find("Content-Length");
										if (contentLengthHeaderIt != downloadClient->responseHeaders.end()) {
											const auto& contentLengthHeader = contentLengthHeaderIt->second;
											downloadClient->haveContentSize = true;
											downloadClient->contentSize = Integer::parse(contentLengthHeader);
										}
									}
									ifs.close();
								}
								bytesRead+= rawResponseBytesRead;
								if (downloadClient->haveHeaders == true && downloadClient->haveContentSize == true) {
									downloadClient->progress = static_cast<float>(bytesRead - downloadClient->headerSize) / static_cast<float>(downloadClient->contentSize);
								}
							};
						} catch (NetworkSocketClosedException& sce) {
							// end of stream
						}

						// close download file
						ofs.close();
					}

					// transfer to real file
					if (downloadClient->statusCode == 200 && isStopRequested() == false) {
						// input file stream
						ifstream ifs(std::filesystem::u8path(downloadClient->file + ".download"), ofstream::binary);
						if (ifs.is_open() == false) {
							throw HTTPClientException("Unable to open file for reading(" + to_string(errno) + "): " + (downloadClient->file + ".download"));
						}

						ifs.seekg(downloadClient->headerSize, ios::beg);
						auto ifsHeaderSize = ifs.tellg();
						ifs.seekg(0, ios::end);
						auto ifsSizeTotal = ifs.tellg();
						auto ifsSize = ifsSizeTotal - ifsHeaderSize;
						ifs.seekg(ifsHeaderSize, ios::beg);

						// output file stream
						ofstream ofs(std::filesystem::u8path(downloadClient->file), ofstream::binary);
						if (ofs.is_open() == false) {
							throw HTTPClientException("Unable to open file for writing(" + to_string(errno) + "): " + downloadClient->file);
						}

						//
						char buf[16384];
						auto ifsBytesToRead = 0;
						auto ifsBytesRead = 0;
						do {
							auto ifsBytesToRead = Math::min(static_cast<int64_t>(ifsSize - ifsBytesRead), sizeof(buf));
							ifs.read(buf, ifsBytesToRead);
							ofs.write(buf, ifsBytesToRead);
							ifsBytesRead+= ifsBytesToRead;
						} while (ifsBytesRead < ifsSize);

						// close target file
						ofs.close();

						// close download file
						ifs.close();
					}

					//
					FileSystem::removeFile(".", downloadClient->file + ".download");

					//
					socket->shutdown();

					//
					downloadClient->finished = true;
					downloadClient->progress = 1.0f;
				} catch (Exception& exception) {
					if (socket != nullptr) socket->shutdown();
					downloadClient->finished = true;
					Console::println(string("HTTPDownloadClient::execute(): performed HTTP request: FAILED: ") + exception.what());
				}
			}
		private:
			HTTPDownloadClient* downloadClient;
	};
	downloadThreadMutex.lock();
	finished = false;
	this->downloadThread = make_unique<DownloadThread>(this);
	this->downloadThread->start();
	downloadThreadMutex.unlock();
}

void HTTPDownloadClient::cancel() {
	downloadThreadMutex.lock();
	if (downloadThread != nullptr) downloadThread->stop();
	downloadThreadMutex.unlock();
}

void HTTPDownloadClient::join() {
	downloadThreadMutex.lock();
	if (downloadThread != nullptr) {
		downloadThread->join();
		this->downloadThread = nullptr;
	}
	downloadThreadMutex.unlock();
}
