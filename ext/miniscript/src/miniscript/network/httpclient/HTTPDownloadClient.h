#pragma once

#include <fstream>
#include <memory>
#include <unordered_map>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/network/httpclient/fwd-miniscript.h>
#include <miniscript/network/httpclient/HTTPClientException.h>
#include <miniscript/os/network/NetworkException.h>
#include <miniscript/os/threading/Mutex.h>
#include <miniscript/os/threading/Thread.h>

using std::ifstream;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::vector;

using _HTTPClientException = miniscript::network::httpclient::HTTPClientException;
using _NetworkException = miniscript::os::network::NetworkException;
using _Mutex = miniscript::os::threading::Mutex;
using _Thread = miniscript::os::threading::Thread;

/**
 * HTTP download client
 * @author Andreas Drewke
 */
class miniscript::network::httpclient::HTTPDownloadClient {

private:
	string url;
	string file;
	string username;
	string password;

	unordered_map<string, string> headers;
	unordered_map<string, string> getParameters;

	int16_t statusCode { -1 };
	unordered_map<string, string> responseHeaders;

	unique_ptr<_Thread> downloadThread;
	_Mutex downloadThreadMutex;
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
