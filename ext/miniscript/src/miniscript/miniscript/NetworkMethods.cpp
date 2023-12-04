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
		class ScriptMethodNetworkHTTPClientHEAD: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNetworkHTTPClientHEAD(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string url;
				if (argumentValues.size() <= 3 &&
					MiniScript::getStringValue(argumentValues, 0, url, false) == true &&
					(argumentValues.size() <= 1 || argumentValues[1].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 2 || argumentValues[2].getType() == MiniScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (argumentValues.size() >= 2) {
						auto getParameterMapPtr = argumentValues[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (argumentValues.size() >= 3) {
						auto headersMapPtr = argumentValues[2].getMapPointer();
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
						MiniScript::ScriptVariable responseHeaders;
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
		miniScript->registerMethod(new ScriptMethodNetworkHTTPClientHEAD(miniScript));
	}
	{
		//
		class ScriptMethodNetworkHTTPClientGET: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNetworkHTTPClientGET(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string url;
				if (argumentValues.size() <= 3 &&
					MiniScript::getStringValue(argumentValues, 0, url, false) == true &&
					(argumentValues.size() <= 1 || argumentValues[1].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 2 || argumentValues[2].getType() == MiniScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (argumentValues.size() >= 2) {
						auto getParameterMapPtr = argumentValues[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}

					}
					// headers
					unordered_map<string, string> headers;
					if (argumentValues.size() >= 3) {
						auto headersMapPtr = argumentValues[2].getMapPointer();
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
						MiniScript::ScriptVariable responseHeaders;
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
		miniScript->registerMethod(new ScriptMethodNetworkHTTPClientGET(miniScript));
	}
	{
		//
		class ScriptMethodNetworkHTTPClientPOST: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNetworkHTTPClientPOST(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string url;
				string dataString;
				if (argumentValues.size() >= 2 && argumentValues.size() <= 4 &&
					MiniScript::getStringValue(argumentValues, 0, url, false) == true &&
					(MiniScript::getStringValue(argumentValues, 1, dataString, true) == true || argumentValues[2].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 2 || argumentValues[2].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 3 || argumentValues[3].getType() == MiniScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (argumentValues.size() >= 2) {
						if (argumentValues[1].getType() == MiniScript::TYPE_MAP) {
							auto postParameterMapPtr = argumentValues[1].getMapPointer();
							if (postParameterMapPtr != nullptr) {
								for (const auto& [key, value]: *postParameterMapPtr) {
									postParameters[key] = value->getValueAsString();
								}
							}
						}
					}
					// GET parameters
					unordered_map<string, string> getParameters;
					if (argumentValues.size() >= 3) {
						auto getParameterMapPtr = argumentValues[2].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (argumentValues.size() >= 4) {
						auto headersMapPtr = argumentValues[3].getMapPointer();
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
						MiniScript::ScriptVariable responseHeaders;
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
		miniScript->registerMethod(new ScriptMethodNetworkHTTPClientPOST(miniScript));
	}
	{
		//
		class ScriptMethodNetworkHTTPClientPUT: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNetworkHTTPClientPUT(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string url;
				string dataString;
				if (argumentValues.size() >= 2 && argumentValues.size() <= 4 &&
					MiniScript::getStringValue(argumentValues, 0, url, false) == true &&
					(MiniScript::getStringValue(argumentValues, 1, dataString, true) == true || argumentValues[2].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 2 || argumentValues[2].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 3 || argumentValues[3].getType() == MiniScript::TYPE_MAP)) {
					// post parameters
					unordered_map<string, string> postParameters;
					if (argumentValues.size() >= 2) {
						if (argumentValues[1].getType() == MiniScript::TYPE_MAP) {
							auto postParameterMapPtr = argumentValues[1].getMapPointer();
							if (postParameterMapPtr != nullptr) {
								for (const auto& [key, value]: *postParameterMapPtr) {
									postParameters[key] = value->getValueAsString();
								}
							}
						}
					}
					// GET parameters
					unordered_map<string, string> getParameters;
					if (argumentValues.size() >= 3) {
						auto getParameterMapPtr = argumentValues[2].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (argumentValues.size() >= 4) {
						auto headersMapPtr = argumentValues[3].getMapPointer();
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
						MiniScript::ScriptVariable responseHeaders;
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
		miniScript->registerMethod(new ScriptMethodNetworkHTTPClientPUT(miniScript));
	}
	{
		//
		class ScriptMethodNetworkHTTPClientDELETE: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNetworkHTTPClientDELETE(MiniScript* miniScript):
				MiniScript::ScriptMethod(
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
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string url;
				if (argumentValues.size() <= 3 &&
					MiniScript::getStringValue(argumentValues, 0, url, false) == true &&
					(argumentValues.size() <= 1 || argumentValues[1].getType() == MiniScript::TYPE_MAP) &&
					(argumentValues.size() <= 2 || argumentValues[2].getType() == MiniScript::TYPE_MAP)) {
					// GET parameters
					unordered_map<string, string> getParameters;
					if (argumentValues.size() >= 2) {
						auto getParameterMapPtr = argumentValues[1].getMapPointer();
						if (getParameterMapPtr != nullptr) {
							for (const auto& [key, value]: *getParameterMapPtr) {
								getParameters[key] = value->getValueAsString();
							}
						}
					}
					// headers
					unordered_map<string, string> headers;
					if (argumentValues.size() >= 3) {
						auto headersMapPtr = argumentValues[2].getMapPointer();
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
						MiniScript::ScriptVariable responseHeaders;
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
		miniScript->registerMethod(new ScriptMethodNetworkHTTPClientDELETE(miniScript));
	}
}
