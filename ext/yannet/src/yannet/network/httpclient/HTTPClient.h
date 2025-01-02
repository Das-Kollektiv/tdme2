#pragma once

#include <sstream>
#include <unordered_map>
#include <vector>

#include <yannet/yannet.h>
#include <yannet/network/httpclient/fwd-yannet.h>
#include <yannet/network/httpclient/HTTPClientException.h>
#include <yannet/os/network/NetworkException.h>

using std::string;
using std::stringstream;
using std::unordered_map;
using std::vector;

// name spaces
namespace yannet {
namespace network {
namespace httpclient {
	using yannet::network::httpclient::HTTPClientException;
	using yannet::os::network::NetworkException;
}
}
}

/**
 * Basic HTTP client
 * @author Andreas Drewke
 */
class yannet::network::httpclient::HTTPClient {
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
	 */
	void parseHTTPResponseHeaders(stringstream& rawResponse);

public:
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_GET;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_HEAD;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_POST;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_PUT;
	STATIC_DLL_IMPEXT static const string HTTP_METHOD_DELETE;

	//
	enum HttpStatusCode {
		// https://github.com/j-ulrich/http-status-codes-cpp
		HTTP_STATUS_CONTINUE                        = 100,
		HTTP_STATUS_SWITCHINGPROTOCOLS              = 101,
		HTTP_STATUS_PROCESSING                      = 102,
		HTTP_STATUS_EARLYHINTS                      = 103,
		HTTP_STATUS_OK                              = 200,
		HTTP_STATUS_CREATED                         = 201,
		HTTP_STATUS_ACCEPTED                        = 202,
		HTTP_STATUS_NONAUTHORITATIVEINFORMATION     = 203,
		HTTP_STATUS_NOCONTENT                       = 204,
		HTTP_STATUS_RESETCONTENT                    = 205,
		HTTP_STATUS_PARTIALCONTENT                  = 206,
		HTTP_STATUS_MULTISTATUS                     = 207,
		HTTP_STATUS_ALREADYREPORTED                 = 208,
		HTTP_STATUS_IMUSED                          = 226,
		HTTP_STATUS_MULTIPLECHOICES                 = 300,
		HTTP_STATUS_MOVEDPERMANENTLY                = 301,
		HTTP_STATUS_FOUND                           = 302,
		HTTP_STATUS_SEEOTHER                        = 303,
		HTTP_STATUS_NOTMODIFIED                     = 304,
		HTTP_STATUS_USEPROXY                        = 305,
		HTTP_STATUS_TEMPORARYREDIRECT               = 307,
		HTTP_STATUS_PERMANENTREDIRECT               = 308,
		HTTP_STATUS_BADREQUEST                      = 400,
		HTTP_STATUS_UNAUTHORIZED                    = 401,
		HTTP_STATUS_PAYMENTREQUIRED                 = 402,
		HTTP_STATUS_FORBIDDEN                       = 403,
		HTTP_STATUS_NOTFOUND                        = 404,
		HTTP_STATUS_METHODNOTALLOWED                = 405,
		HTTP_STATUS_NOTACCEPTABLE                   = 406,
		HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED     = 407,
		HTTP_STATUS_REQUESTTIMEOUT                  = 408,
		HTTP_STATUS_CONFLICT                        = 409,
		HTTP_STATUS_GONE                            = 410,
		HTTP_STATUS_LENGTHREQUIRED                  = 411,
		HTTP_STATUS_PRECONDITIONFAILED              = 412,
		HTTP_STATUS_CONTENTTOOLARGE                 = 413,
		HTTP_STATUS_PAYLOADTOOLARGE                 = 413,
		HTTP_STATUS_URITOOLONG                      = 414,
		HTTP_STATUS_UNSUPPORTEDMEDIATYPE            = 415,
		HTTP_STATUS_RANGENOTSATISFIABLE             = 416,
		HTTP_STATUS_EXPECTATIONFAILED               = 417,
		HTTP_STATUS_IMATEAPOT                       = 418,
		HTTP_STATUS_MISDIRECTEDREQUEST              = 421,
		HTTP_STATUS_UNPROCESSABLECONTENT            = 422,
		HTTP_STATUS_UNPROCESSABLEENTITY             = 422,
		HTTP_STATUS_LOCKED                          = 423,
		HTTP_STATUS_FAILEDDEPENDENCY                = 424,
		HTTP_STATUS_TOOEARLY                        = 425,
		HTTP_STATUS_UPGRADEREQUIRED                 = 426,
		HTTP_STATUS_PRECONDITIONREQUIRED            = 428,
		HTTP_STATUS_TOOMANYREQUESTS                 = 429,
		HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE     = 431,
		HTTP_STATUS_UNAVAILABLEFORLEGALREASONS      = 451,
		HTTP_STATUS_INTERNALSERVERERROR             = 500,
		HTTP_STATUS_NOTIMPLEMENTED                  = 501,
		HTTP_STATUS_BADGATEWAY                      = 502,
		HTTP_STATUS_SERVICEUNAVAILABLE              = 503,
		HTTP_STATUS_GATEWAYTIMEOUT                  = 504,
		HTTP_STATUS_HTTPVERSIONNOTSUPPORTED         = 505,
		HTTP_STATUS_VARIANTALSONEGOTIATES           = 506,
		HTTP_STATUS_INSUFFICIENTSTORAGE             = 507,
		HTTP_STATUS_LOOPDETECTED                    = 508,
		HTTP_STATUS_NOTEXTENDED                     = 510,
		HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED   = 511,
		HTTP_STATUS_MAX                             = 1023
	};

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
