#pragma once

#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/httpclient/fwd-tdme.h>
#include <tdme/network/httpclient/HTTPClientException.h>
#include <tdme/os/network/NetworkException.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/os/threading/Thread.h>

using std::ifstream;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using tdme::network::httpclient::HTTPClientException;
using tdme::os::network::NetworkException;
using tdme::os::threading::Mutex;
using tdme::os::threading::Thread;

/**
 * HTTP download client
 * @author Andreas Drewke
 */
class tdme::network::httpclient::HTTPDownloadClient {

private:
	string url;
	string file;
	string username;
	string password;

	unordered_map<string, string> headers;
	unordered_map<string, string> getParameters;

	int16_t statusCode { -1 };
	unordered_map<string, string> responseHeaders;

	unique_ptr<Thread> downloadThread;
	Mutex downloadThreadMutex;
	bool haveHeaders { false };
	bool haveContentSize { false };
	uint64_t headerSize { 0LL };
	uint64_t contentSize { 0LL };
	volatile bool finished { true };
	volatile float progress { 0.0f };

	/**
	 * Returns a URL encoded representation of value
	 * @param value value
	 * @return URL encoded value
	 */
	static string urlEncode(const string& value);

	/**
	 * Create HTTP request headers
	 * @param hostName host name
	 * @param relativeUrl url relative to server root
	 */
	string createHTTPRequestHeaders(const string& hostName, const string& relativeUrl);

	/**
	 * Parse HTTP response headers
	 * @param rawResponse raw response
	 * @return http header size or 0 if not yet completely submitted
	 */
	uint64_t parseHTTPResponseHeaders(ifstream& rawResponse);

public:

	static const constexpr int16_t HTTP_STATUSCODE_OK { 200 };

	/**
	 * Public constructor
	 */
	HTTPDownloadClient();

	/**
	 * Get username
	 * @return username
	 */
	inline const string& getUsername() {
		return username;
	}

	/**
	 * Set username
	 * @param username user name
	 */
	inline void setUsername(const string& username) {
		this->username = username;
	}

	/**
	 * Get password
	 * @return password
	 */
	inline const string& getPassword() {
		return password;
	}

	/**
	 * Set password
	 * @param password password
	 */
	inline void setPassword(const string& password) {
		this->password = password;
	}

	/**
	 * Get request headers
	 * @return request headers
	 */
	inline const unordered_map<string, string>& getHeaders() {
		return headers;
	}

	/**
	 * Set request headers
	 * @param headers request headers
	 */
	inline void setHeaders(const unordered_map<string, string>& headers) {
		this->headers = headers;
	}

	/**
	 * Get GET parameter
	 * @return GET parameter
	 */
	inline const unordered_map<string, string>& getGETParameters() {
		return getParameters;
	}

	/**
	 * Set GET parameter
	 * @param GET parameter
	 */
	inline void setGETParameters(const unordered_map<string, string>& parameters) {
		this->getParameters = parameters;
	}

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
	 * Starts the HTTP download to file
	 */
	void start();

	/**
	 * @return HTTP status code
	 */
	inline int16_t getStatusCode() {
		return statusCode;
	}

	/**
	 * @return HTTP response headers
	 */
	inline const unordered_map<string, string>& getResponseHeaders() {
		return headers;
	}

	/**
	 * @return is finished
	 */
	inline bool isFinished() {
		return finished;
	}

	/**
	 * @return progress
	 */
	inline float getProgress() {
		return progress;
	}

	/**
	 * Cancel a started download
	 */
	void cancel();

	/**
	 * Wait until underlying thread has finished
	 */
	void join();

};
