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
using miniscript::network::httpclient::HTTPClient;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;

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
						HTTPClient httpClient;
						httpClient.setMethod(HTTPClient::HTTP_METHOD_HEAD);
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
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						HTTPClient httpClient;
						httpClient.setMethod(HTTPClient::HTTP_METHOD_GET);
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
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						HTTPClient httpClient;
						httpClient.setMethod(HTTPClient::HTTP_METHOD_POST);
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
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						HTTPClient httpClient;
						httpClient.setMethod(HTTPClient::HTTP_METHOD_PUT);
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
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
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
						HTTPClient httpClient;
						httpClient.setMethod(HTTPClient::HTTP_METHOD_DELETE);
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
					} catch (Exception& exception) {
						Console::println("An error occurred: " + string(exception.what()));
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodNetworkHTTPClientDELETE(miniScript));
	}
}
