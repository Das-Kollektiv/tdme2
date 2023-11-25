#pragma once

#include <sstream>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/network/httpclient/fwd-tdme.h>
#include <tdme/network/httpclient/HTTPClientException.h>
#include <tdme/os/network/NetworkException.h>

using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

using tdme::network::httpclient::HTTPClientException;
using tdme::os::network::NetworkException;

/**
 * Basic HTTP client
 * @author Andreas Drewke
 */
class tdme::network::httpclient::HTTPClient {

private:
	string url;
	string method;
	unordered_map<string, string> headers;
	unordered_map<string, string> getParameters;
	unordered_map<string, string> postParameters;
	string body;
	string contentType;
	string username;
	string password;

	stringstream rawResponse;
	int16_t statusCode { -1 };
	unordered_map<string, string> responseHeaders;

	/**
	 * Returns a URL encoded representation of value
	 * @param value value
	 * @return URL encoded value
	 */
	static string urlEncode(const string& value);

	/**
	 * Create HTTP request headers
	 * @param hostname hostname
	 * @param relativeUrl url relative to server root
	 * @param body body
	 */
	string createHTTPRequestHeaders(const string& hostname, const string& relativeUrl, const string& body);

	/**
	 * Parse HTTP response headers
	 * @param rawResponse raw response
	 * @param statusCode HTTP status code
	 * @param responseHeaders HTTP response headers
	 */
	void parseHTTPResponseHeaders(stringstream& rawResponse, int16_t& statusCode, unordered_map<string, string>& responseHeaders);

public:
	static const constexpr int16_t HTTP_STATUSCODE_OK { 200 };

	STATIC_DLL_IMPEXT static const string HTTP_METHOD_GET;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_HEAD;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_POST;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_PUT;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_DELETE;

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
	 * Get method
	 * @return method
	 */
	inline const string& getMethod() {
		return method;
	}

	/**
	 * Set method
	 * @param method method
	 */
	inline void setMethod(const string& method) {
		this->method = method;
	}

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
	 * Get headers
	 * @return headers
	 */
	inline const unordered_map<string, string>& getHeaders() {
		return headers;
	}

	/**
	 * Set headers
	 * @param headers headers
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
	 * Get POST parameter
	 * @return POST parameter
	 */
	inline const unordered_map<string, string>& getPOSTParameters() {
		return postParameters;
	}

	/**
	 * Set POST parameter
	 * @param POST parameter
	 */
	inline void setPOSTParameters(const unordered_map<string, string>& parameters) {
		this->postParameters = parameters;
	}

	/**
	 * Get body
	 * @return body
	 */
	inline const string& getBody() {
		return body;
	}

	/**
	 * Set body
	 * @param contentType content type
	 * @param body body
	 */
	inline void setBody(const string& contentType, const string& body) {
		this->contentType = contentType;
		this->body = body;
	}

	/**
	 * Get content type
	 * @return content type
	 */
	inline const string& getContentType() {
		return contentType;
	}

	/**
	 * Set content type
	 * @param contentType content type
	 */
	inline void setContentType(const string& contentType) {
		this->contentType = contentType;
	}


	/**
	 * Reset this HTTP client
	 */
	void reset();

	/**
	 * Execute HTTP request
	 * @throws tdme::network::httpclient::HTTPClientException
	 * @throws tdme::os::network::NetworkException
	 */
	void execute();

	/**
	 * @return complete response stream
	 */
	inline stringstream& getResponse() {
		return rawResponse;
	}

	/**
	 * @return HTTP status code
	 */
	inline int16_t getStatusCode() {
		return statusCode;
	}

	/**
	 * @return response headers
	 */
	inline const unordered_map<string, string>& getResponseHeaders() {
		return responseHeaders;
	}

};
