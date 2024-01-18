#include <span>

#include <unordered_map>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/NetworkMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/network/httpclient/HTTPClient.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>

using std::span;
using std::unordered_map;

using miniscript::miniscript::NetworkMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _Exception = miniscript::utilities::Exception;
using _HTTPClient = miniscript::network::httpclient::HTTPClient;

void NetworkMethods::registerConstants(MiniScript* miniScript) {
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_CONTINUE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONTINUE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_SWITCHINGPROTOCOLS", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SWITCHINGPROTOCOLS));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PROCESSING", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PROCESSING));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_EARLYHINTS", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_EARLYHINTS));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_OK", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_OK));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_CREATED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CREATED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_ACCEPTED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_ACCEPTED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NONAUTHORITATIVEINFORMATION", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NONAUTHORITATIVEINFORMATION));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOCONTENT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOCONTENT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_RESETCONTENT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_RESETCONTENT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PARTIALCONTENT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PARTIALCONTENT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_MULTISTATUS", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MULTISTATUS));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_ALREADYREPORTED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_ALREADYREPORTED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_IMUSED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_IMUSED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_MULTIPLECHOICES", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MULTIPLECHOICES));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_MOVEDPERMANENTLY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MOVEDPERMANENTLY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_FOUND", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FOUND));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_SEEOTHER", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SEEOTHER));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOTMODIFIED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTMODIFIED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_USEPROXY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_USEPROXY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_TEMPORARYREDIRECT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TEMPORARYREDIRECT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PERMANENTREDIRECT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PERMANENTREDIRECT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_BADREQUEST", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_BADREQUEST));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UNAUTHORIZED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNAUTHORIZED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PAYMENTREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PAYMENTREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_FORBIDDEN", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FORBIDDEN));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOTFOUND", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTFOUND));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_METHODNOTALLOWED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_METHODNOTALLOWED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOTACCEPTABLE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTACCEPTABLE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_REQUESTTIMEOUT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_REQUESTTIMEOUT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_CONFLICT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONFLICT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_GONE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_GONE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_LENGTHREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LENGTHREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PRECONDITIONFAILED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PRECONDITIONFAILED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_CONTENTTOOLARGE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_CONTENTTOOLARGE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PAYLOADTOOLARGE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PAYLOADTOOLARGE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_URITOOLONG", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_URITOOLONG));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UNSUPPORTEDMEDIATYPE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNSUPPORTEDMEDIATYPE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_RANGENOTSATISFIABLE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_RANGENOTSATISFIABLE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_EXPECTATIONFAILED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_EXPECTATIONFAILED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_IMATEAPOT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_IMATEAPOT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_MISDIRECTEDREQUEST", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MISDIRECTEDREQUEST));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UNPROCESSABLECONTENT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNPROCESSABLECONTENT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UNPROCESSABLEENTITY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNPROCESSABLEENTITY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_LOCKED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LOCKED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_FAILEDDEPENDENCY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_FAILEDDEPENDENCY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_TOOEARLY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TOOEARLY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UPGRADEREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UPGRADEREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_PRECONDITIONREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_PRECONDITIONREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_TOOMANYREQUESTS", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_TOOMANYREQUESTS));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_UNAVAILABLEFORLEGALREASONS", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_UNAVAILABLEFORLEGALREASONS));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_INTERNALSERVERERROR", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_INTERNALSERVERERROR));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOTIMPLEMENTED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTIMPLEMENTED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_BADGATEWAY", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_BADGATEWAY));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_SERVICEUNAVAILABLE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_SERVICEUNAVAILABLE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_GATEWAYTIMEOUT", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_GATEWAYTIMEOUT));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_HTTPVERSIONNOTSUPPORTED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_HTTPVERSIONNOTSUPPORTED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_VARIANTALSONEGOTIATES", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_VARIANTALSONEGOTIATES));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_INSUFFICIENTSTORAGE", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_INSUFFICIENTSTORAGE));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_LOOPDETECTED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_LOOPDETECTED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NOTEXTENDED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NOTEXTENDED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED));
	miniScript->setConstant("$HTTPClient::HTTP_STATUS_MAX", static_cast<int64_t>(_HTTPClient::HTTP_STATUS_MAX));
}

void NetworkMethods::registerMethods(MiniScript* miniScript) {
	// network
	{
		//
		class MethodNetworkHTTPClientHEAD: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNetworkHTTPClientHEAD(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MiniScript::TYPE_MAP,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "network.httpclient.head";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string url;
				if (arguments.size() <= 3 &&
					MiniScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MiniScript::TYPE_MAP)) {
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
						returnValue.setType(MiniScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						//
						MiniScript::Variable responseHeaders;
						responseHeaders.setType(MiniScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						_Console::printLine("An error occurred: " + string(exception.what()));
					}
				} else {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientHEAD(miniScript));
	}
	{
		//
		class MethodNetworkHTTPClientGET: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNetworkHTTPClientGET(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MiniScript::TYPE_MAP,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "network.httpclient.get";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string url;
				if (arguments.size() <= 3 &&
					MiniScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MiniScript::TYPE_MAP)) {
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
						returnValue.setType(MiniScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MiniScript::Variable responseHeaders;
						responseHeaders.setType(MiniScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						_Console::printLine("An error occurred: " + string(exception.what()));
					}
				} else {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientGET(miniScript));
	}
	{
		//
		class MethodNetworkHTTPClientPOST: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNetworkHTTPClientPOST(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "data", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MiniScript::TYPE_MAP,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "network.httpclient.post";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string url;
				string dataString;
				if (arguments.size() >= 2 && arguments.size() <= 4 &&
					MiniScript::getStringValue(arguments, 0, url, false) == true &&
					(MiniScript::getStringValue(arguments, 1, dataString, true) == true || arguments[2].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 3 || arguments[3].getType() == MiniScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (arguments.size() >= 2) {
						if (arguments[1].getType() == MiniScript::TYPE_MAP) {
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
						returnValue.setType(MiniScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MiniScript::Variable responseHeaders;
						responseHeaders.setType(MiniScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						_Console::printLine("An error occurred: " + string(exception.what()));
					}
				} else {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientPOST(miniScript));
	}
	{
		//
		class MethodNetworkHTTPClientPUT: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNetworkHTTPClientPUT(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "data", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MiniScript::TYPE_MAP,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "network.httpclient.put";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string url;
				string dataString;
				if (arguments.size() >= 2 && arguments.size() <= 4 &&
					MiniScript::getStringValue(arguments, 0, url, false) == true &&
					(MiniScript::getStringValue(arguments, 1, dataString, true) == true || arguments[2].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 3 || arguments[3].getType() == MiniScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (arguments.size() >= 2) {
						if (arguments[1].getType() == MiniScript::TYPE_MAP) {
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
						returnValue.setType(MiniScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						returnValue.setMapEntry("response", response);
						//
						MiniScript::Variable responseHeaders;
						responseHeaders.setType(MiniScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						_Console::printLine("An error occurred: " + string(exception.what()));
					}
				} else {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientPUT(miniScript));
	}
	{
		//
		class MethodNetworkHTTPClientDELETE: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNetworkHTTPClientDELETE(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "queryParameters", .optional = true, .reference = false, .nullable = true },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = true, .reference = false, .nullable = true },
					},
					MiniScript::TYPE_MAP,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "network.httpclient.delete";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string url;
				if (arguments.size() <= 3 &&
					MiniScript::getStringValue(arguments, 0, url, false) == true &&
					(arguments.size() <= 1 || arguments[1].getType() == MiniScript::TYPE_MAP) &&
					(arguments.size() <= 2 || arguments[2].getType() == MiniScript::TYPE_MAP)) {
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
						returnValue.setType(MiniScript::TYPE_MAP);
						returnValue.setMapEntry("status", static_cast<int64_t>(httpClient.getStatusCode()));
						//
						MiniScript::Variable responseHeaders;
						responseHeaders.setType(MiniScript::TYPE_MAP);
						for (const auto& [headerName, headerValue]: httpClient.getResponseHeaders()) {
							responseHeaders.setMapEntry(headerName, headerValue);
						}
						returnValue.setMapEntry("headers", responseHeaders);
					} catch (_Exception& exception) {
						_Console::printLine("An error occurred: " + string(exception.what()));
					}
				} else {
					_Console::printLine(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientDELETE(miniScript));
	}
}
