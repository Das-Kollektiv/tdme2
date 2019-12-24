#pragma once

#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/httpclient/fwd-tdme.h>
#include <tdme/network/httpclient/HTTPClientException.h>
#include <tdme/os/network/NIOException.h>

using std::ifstream;
using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

using tdme::network::httpclient::HTTPClientException;
using tdme::os::network::NIOException;

/**
 * HTTP download client
 * @author Andreas Drewke
 */
class tdme::network::httpclient::HTTPDownloadClient {

private:
	string url;
	string file;

	int16_t httpStatusCode;
	vector<string> httpHeader;

	/**
	 * Create HTTP request headers
	 * @param hostName host name
	 * @param relativeUrl url relative to server root
	 */
	string createHTTPRequestHeaders(const string& hostName, const string& relativeUrl);

	/**
	 * Parse HTTP response headers
	 * @param rawResponse raw response
	 * @param httpStatusCode HTTP status code
	 * @param httpHeader HTTP header
	 */
	void parseHTTPResponseHeaders(ifstream& rawResponse, int16_t& httpStatusCode, vector<string>& httpHeader);

public:

	static const constexpr int16_t HTTP_STATUSCODE_OK { 200 };

	/**
	 * Get URL
	 * @return URL
	 */
	inline const string& getURL() {
		return url;
	}

	/**
	 * Set URL
	 * @param url URL
	 */
	inline void setURL(const string& url) {
		this->url = url;
	}

	/**
	 * Get file to download to
	 * @return file
	 */
	inline const string& getFile() {
		return file;
	}

	/**
	 * Set file to download to
	 * @param file file
	 */
	inline void setFile(const string& file) {
		this->file = file;
	}

	/**
	 * Reset this HTTP client
	 */
	void reset();

	/**
	 * Execute HTTP request
	 * @throws tdme::network::HTTPDownloadClient::HTTPDownloadClientException
	 * @throws tdme::os::network::NIOException
	 */
	void execute();

	/**
	 * @return HTTP status code
	 */
	inline int16_t getStatusCode() {
		return httpStatusCode;
	}

	/**
	 * @return HTTP response headers
	 */
	inline const vector<string>& getResponseHeaders() {
		return httpHeader;
	}

};
