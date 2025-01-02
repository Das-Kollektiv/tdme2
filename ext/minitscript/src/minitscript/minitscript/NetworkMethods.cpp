#include <span>

#include <unordered_map>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/NetworkMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/network/httpclient/HTTPClient.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>

using std::span;
using std::unordered_map;

using minitscript::minitscript::NetworkMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _Exception = minitscript::utilities::Exception;
using _HTTPClient = minitscript::network::httpclient::HTTPClient;

void NetworkMethods::registerConstants(MinitScript* minitScript) {
	minitScript->setConstant("$http::HTTP_STATUS_CONTINUE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONTINUE)));
	minitScript->setConstant("$http::HTTP_STATUS_SWITCHINGPROTOCOLS", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SWITCHINGPROTOCOLS)));
	minitScript->setConstant("$http::HTTP_STATUS_PROCESSING", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PROCESSING)));
	minitScript->setConstant("$http::HTTP_STATUS_EARLYHINTS", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_EARLYHINTS)));
	minitScript->setConstant("$http::HTTP_STATUS_OK", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_OK)));
	minitScript->setConstant("$http::HTTP_STATUS_CREATED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CREATED)));
	minitScript->setConstant("$http::HTTP_STATUS_ACCEPTED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_ACCEPTED)));
	minitScript->setConstant("$http::HTTP_STATUS_NONAUTHORITATIVEINFORMATION", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NONAUTHORITATIVEINFORMATION)));
	minitScript->setConstant("$http::HTTP_STATUS_NOCONTENT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOCONTENT)));
	minitScript->setConstant("$http::HTTP_STATUS_RESETCONTENT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_RESETCONTENT)));
	minitScript->setConstant("$http::HTTP_STATUS_PARTIALCONTENT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PARTIALCONTENT)));
	minitScript->setConstant("$http::HTTP_STATUS_MULTISTATUS", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MULTISTATUS)));
	minitScript->setConstant("$http::HTTP_STATUS_ALREADYREPORTED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_ALREADYREPORTED)));
	minitScript->setConstant("$http::HTTP_STATUS_IMUSED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_IMUSED)));
	minitScript->setConstant("$http::HTTP_STATUS_MULTIPLECHOICES", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MULTIPLECHOICES)));
	minitScript->setConstant("$http::HTTP_STATUS_MOVEDPERMANENTLY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MOVEDPERMANENTLY)));
	minitScript->setConstant("$http::HTTP_STATUS_FOUND", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FOUND)));
	minitScript->setConstant("$http::HTTP_STATUS_SEEOTHER", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SEEOTHER)));
	minitScript->setConstant("$http::HTTP_STATUS_NOTMODIFIED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTMODIFIED)));
	minitScript->setConstant("$http::HTTP_STATUS_USEPROXY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_USEPROXY)));
	minitScript->setConstant("$http::HTTP_STATUS_TEMPORARYREDIRECT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TEMPORARYREDIRECT)));
	minitScript->setConstant("$http::HTTP_STATUS_PERMANENTREDIRECT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PERMANENTREDIRECT)));
	minitScript->setConstant("$http::HTTP_STATUS_BADREQUEST", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_BADREQUEST)));
	minitScript->setConstant("$http::HTTP_STATUS_UNAUTHORIZED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNAUTHORIZED)));
	minitScript->setConstant("$http::HTTP_STATUS_PAYMENTREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PAYMENTREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_FORBIDDEN", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FORBIDDEN)));
	minitScript->setConstant("$http::HTTP_STATUS_NOTFOUND", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTFOUND)));
	minitScript->setConstant("$http::HTTP_STATUS_METHODNOTALLOWED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_METHODNOTALLOWED)));
	minitScript->setConstant("$http::HTTP_STATUS_NOTACCEPTABLE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTACCEPTABLE)));
	minitScript->setConstant("$http::HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_REQUESTTIMEOUT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_REQUESTTIMEOUT)));
	minitScript->setConstant("$http::HTTP_STATUS_CONFLICT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONFLICT)));
	minitScript->setConstant("$http::HTTP_STATUS_GONE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_GONE)));
	minitScript->setConstant("$http::HTTP_STATUS_LENGTHREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LENGTHREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_PRECONDITIONFAILED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PRECONDITIONFAILED)));
	minitScript->setConstant("$http::HTTP_STATUS_CONTENTTOOLARGE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONTENTTOOLARGE)));
	minitScript->setConstant("$http::HTTP_STATUS_PAYLOADTOOLARGE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PAYLOADTOOLARGE)));
	minitScript->setConstant("$http::HTTP_STATUS_URITOOLONG", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_URITOOLONG)));
	minitScript->setConstant("$http::HTTP_STATUS_UNSUPPORTEDMEDIATYPE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNSUPPORTEDMEDIATYPE)));
	minitScript->setConstant("$http::HTTP_STATUS_RANGENOTSATISFIABLE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_RANGENOTSATISFIABLE)));
	minitScript->setConstant("$http::HTTP_STATUS_EXPECTATIONFAILED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_EXPECTATIONFAILED)));
	minitScript->setConstant("$http::HTTP_STATUS_IMATEAPOT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_IMATEAPOT)));
	minitScript->setConstant("$http::HTTP_STATUS_MISDIRECTEDREQUEST", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MISDIRECTEDREQUEST)));
	minitScript->setConstant("$http::HTTP_STATUS_UNPROCESSABLECONTENT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNPROCESSABLECONTENT)));
	minitScript->setConstant("$http::HTTP_STATUS_UNPROCESSABLEENTITY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNPROCESSABLEENTITY)));
	minitScript->setConstant("$http::HTTP_STATUS_LOCKED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LOCKED)));
	minitScript->setConstant("$http::HTTP_STATUS_FAILEDDEPENDENCY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FAILEDDEPENDENCY)));
	minitScript->setConstant("$http::HTTP_STATUS_TOOEARLY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TOOEARLY)));
	minitScript->setConstant("$http::HTTP_STATUS_UPGRADEREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UPGRADEREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_PRECONDITIONREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PRECONDITIONREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_TOOMANYREQUESTS", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TOOMANYREQUESTS)));
	minitScript->setConstant("$http::HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE)));
	minitScript->setConstant("$http::HTTP_STATUS_UNAVAILABLEFORLEGALREASONS", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNAVAILABLEFORLEGALREASONS)));
	minitScript->setConstant("$http::HTTP_STATUS_INTERNALSERVERERROR", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_INTERNALSERVERERROR)));
	minitScript->setConstant("$http::HTTP_STATUS_NOTIMPLEMENTED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTIMPLEMENTED)));
	minitScript->setConstant("$http::HTTP_STATUS_BADGATEWAY", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_BADGATEWAY)));
	minitScript->setConstant("$http::HTTP_STATUS_SERVICEUNAVAILABLE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SERVICEUNAVAILABLE)));
	minitScript->setConstant("$http::HTTP_STATUS_GATEWAYTIMEOUT", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_GATEWAYTIMEOUT)));
	minitScript->setConstant("$http::HTTP_STATUS_HTTPVERSIONNOTSUPPORTED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_HTTPVERSIONNOTSUPPORTED)));
	minitScript->setConstant("$http::HTTP_STATUS_VARIANTALSONEGOTIATES", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_VARIANTALSONEGOTIATES)));
	minitScript->setConstant("$http::HTTP_STATUS_INSUFFICIENTSTORAGE", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_INSUFFICIENTSTORAGE)));
	minitScript->setConstant("$http::HTTP_STATUS_LOOPDETECTED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LOOPDETECTED)));
	minitScript->setConstant("$http::HTTP_STATUS_NOTEXTENDED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTEXTENDED)));
	minitScript->setConstant("$http::HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED)));
	minitScript->setConstant("$http::HTTP_STATUS_MAX", MinitScript::Variable(static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MAX)));
}

void NetworkMethods::registerMethods(MinitScript* minitScript) {
	// network
	{
		//
		class MethodNetworkHTTPClientHEAD: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNetworkHTTPClientHEAD(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MinitScript::TYPE_MAP,
					false,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "network.httpclient.head";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string url;
				if (arguments.size() <= 3 &&
					MinitScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MinitScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (arguments.size() >= 2) {
						auto getParameterMapPtr = arguments[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (arguments.size() >= 3) {
						auto headersMapPtr = arguments[2].getMapPointer();
						if (headersMapPtr != nullptr) {
							for (const auto& [key, value]: *headersMapPtr) {
								headers[key] = value->getValueAsString();
							}
						}
					}
					//
					try {
						_HTTPClient httpClient;
						httpClient.setMethod(_HTTPClient::HTTP_METHOD_HEAD);
						httpClient.setGETParameters(getParameters);
						httpClient.setHeaders(headers);
						httpClient.setURL(url);
						httpClient.execute();
						//
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						//
						MinitScript::Variable responseHeaders;
						responseHeaders.setType(MinitScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodNetworkHTTPClientHEAD(minitScript));
	}
	{
		//
		class MethodNetworkHTTPClientGET: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNetworkHTTPClientGET(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MinitScript::TYPE_MAP,
					false,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "network.httpclient.get";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string url;
				if (arguments.size() <= 3 &&
					MinitScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MinitScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (arguments.size() >= 2) {
						auto getParameterMapPtr = arguments[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}

					}
					// headers
					unordered_map<string, string> headers;
					if (arguments.size() >= 3) {
						auto headersMapPtr = arguments[2].getMapPointer();
						if (headersMapPtr != nullptr) {
							for (const auto& [key, value]: *headersMapPtr) {
								headers[key] = value->getValueAsString();
							}
						}
					}
					//
					try {
						_HTTPClient httpClient;
						httpClient.setMethod(_HTTPClient::HTTP_METHOD_GET);
						httpClient.setGETParameters(getParameters);
						httpClient.setHeaders(headers);
						httpClient.setURL(url);
						httpClient.execute();
						string response;
						char c;
						while (httpClient.getResponse().eof() == false) {
							httpClient.getResponse().get(c);
							response+= c;
						}
						//
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MinitScript::Variable responseHeaders;
						responseHeaders.setType(MinitScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodNetworkHTTPClientGET(minitScript));
	}
	{
		//
		class MethodNetworkHTTPClientPOST: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNetworkHTTPClientPOST(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "data", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MinitScript::TYPE_MAP,
					false,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "network.httpclient.post";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string url;
				string dataString;
				if (arguments.size() >= 2 && arguments.size() <= 4 &&
					MinitScript::getStringValue(arguments, 0, url, false) == true &&
					(MinitScript::getStringValue(arguments, 1, dataString, true) == true || arguments[2].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 3 || arguments[3].getType() == MinitScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (arguments.size() >= 2) {
						if (arguments[1].getType() == MinitScript::TYPE_MAP) {
							auto postParameterMapPtr = arguments[1].getMapPointer();
							if (postParameterMapPtr != nullptr) {
								for (const auto& [key, value]: *postParameterMapPtr) {
									postParameters[key] = value->getValueAsString();
								}
							}
						}
					}
					// GET parameters
					unordered_map<string, string> getParameters;
					if (arguments.size() >= 3) {
						auto getParameterMapPtr = arguments[2].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (arguments.size() >= 4) {
						auto headersMapPtr = arguments[3].getMapPointer();
						if (headersMapPtr != nullptr) {
							for (const auto& [key, value]: *headersMapPtr) {
								headers[key] = value->getValueAsString();
							}
						}
					}
					//
					try {
						_HTTPClient httpClient;
						httpClient.setMethod(_HTTPClient::HTTP_METHOD_POST);
						httpClient.setGETParameters(getParameters);
						httpClient.setHeaders(headers);
						if (postParameters.empty() == false) {
							httpClient.setPOSTParameters(postParameters);
						} else {
							httpClient.setBody("text/text", dataString);
						}
						httpClient.setURL(url);
						httpClient.execute();
						string response;
						char c;
						while (httpClient.getResponse().eof() == false) {
							httpClient.getResponse().get(c);
							response+= c;
						}
						//
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MinitScript::Variable responseHeaders;
						responseHeaders.setType(MinitScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodNetworkHTTPClientPOST(minitScript));
	}
	{
		//
		class MethodNetworkHTTPClientPUT: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNetworkHTTPClientPUT(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "data", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MinitScript::TYPE_MAP,
					false,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "network.httpclient.put";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string url;
				string dataString;
				if (arguments.size() >= 2 && arguments.size() <= 4 &&
					MinitScript::getStringValue(arguments, 0, url, false) == true &&
					(MinitScript::getStringValue(arguments, 1, dataString, true) == true || arguments[2].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 3 || arguments[3].getType() == MinitScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (arguments.size() >= 2) {
						if (arguments[1].getType() == MinitScript::TYPE_MAP) {
							auto postParameterMapPtr = arguments[1].getMapPointer();
							if (postParameterMapPtr != nullptr) {
								for (const auto& [key, value]: *postParameterMapPtr) {
									postParameters[key] = value->getValueAsString();
								}
							}
						}
					}
					// GET parameters
					unordered_map<string, string> getParameters;
					if (arguments.size() >= 3) {
						auto getParameterMapPtr = arguments[2].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (arguments.size() >= 4) {
						auto headersMapPtr = arguments[3].getMapPointer();
						if (headersMapPtr != nullptr) {
							for (const auto& [key, value]: *headersMapPtr) {
								headers[key] = value->getValueAsString();
							}
						}
					}
					//
					try {
						_HTTPClient httpClient;
						httpClient.setMethod(_HTTPClient::HTTP_METHOD_PUT);
						httpClient.setGETParameters(getParameters);
						httpClient.setHeaders(headers);
						if (postParameters.empty() == false) {
							httpClient.setPOSTParameters(postParameters);
						} else {
							httpClient.setBody("text/text", dataString);
						}
						httpClient.setURL(url);
						httpClient.execute();
						string response;
						char c;
						while (httpClient.getResponse().eof() == false) {
							httpClient.getResponse().get(c);
							response+= c;
						}
						//
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MinitScript::Variable responseHeaders;
						responseHeaders.setType(MinitScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodNetworkHTTPClientPUT(minitScript));
	}
	{
		//
		class MethodNetworkHTTPClientDELETE: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNetworkHTTPClientDELETE(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MinitScript::TYPE_MAP,
					false,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "network.httpclient.delete";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string url;
				if (arguments.size() <= 3 &&
					MinitScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MinitScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MinitScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (arguments.size() >= 2) {
						auto getParameterMapPtr = arguments[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (arguments.size() >= 3) {
						auto headersMapPtr = arguments[2].getMapPointer();
						if (headersMapPtr != nullptr) {
							for (const auto& [key, value]: *headersMapPtr) {
								headers[key] = value->getValueAsString();
							}
						}
					}
					//
					try {
						_HTTPClient httpClient;
						httpClient.setMethod(_HTTPClient::HTTP_METHOD_DELETE);
						httpClient.setGETParameters(getParameters);
						httpClient.setHeaders(headers);
						httpClient.setURL(url);
						httpClient.execute();
						//
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						//
						MinitScript::Variable responseHeaders;
						responseHeaders.setType(MinitScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						minitScript->_throw(string(exception.what()));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodNetworkHTTPClientDELETE(minitScript));
	}
}
