#include <memory>
#include <span>
#include <string>

#include <minitscript/minitscript/MinitScript.h>

#include <minitscript/minitscript.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/minitscript/HTTPDownloadClientClass.h>
#include <minitscript/network/httpclient/HTTPDownloadClient.h>

using std::make_shared;
using std::shared_ptr;
using std::span;
using std::string;

using minitscript::minitscript::HTTPDownloadClientClass;

using minitscript::minitscript::MinitScript;
using _Console = minitscript::utilities::Console;
using _HTTPDownloadClient = minitscript::network::httpclient::HTTPDownloadClient;

const string HTTPDownloadClientClass::TYPE_NAME = "HTTPDownloadClient";

void HTTPDownloadClientClass::initialize() {
}

void HTTPDownloadClientClass::registerConstants(MinitScript* minitScript) const {
}

void HTTPDownloadClientClass::registerMethods(MinitScript* minitScript) const {
	//
	{
		//
		class MethodHTTPDownloadClient: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClient(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_HTTPDOWNLOADCLIENT),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					auto& scriptContext = *static_cast<HTTPDownloadClientClass::HTTPDownloadClientClassScriptContext*>(minitScript->getDataTypeScriptContext(MinitScript::TYPE_HTTPDOWNLOADCLIENT));
					//
					auto httpDownloadClient = make_shared<_HTTPDownloadClient>();
					scriptContext.getInstances().push_back(httpDownloadClient);
					scriptContext.setRequiresGarbageCollection();
					//
					returnValue.setType(MinitScript::TYPE_HTTPDOWNLOADCLIENT);
					returnValue.setValue(&httpDownloadClient);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClient(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetUserName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetUserName(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getUserName";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->getUsername());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetUserName(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetUserName: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetUserName(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "userName", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setUserName";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string userName;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					MinitScript::getStringValue(arguments, 1, userName) == true) {
					httpDownloadClient->setUsername(userName);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetUserName(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetPassword: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetPassword(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getPassword";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->getPassword());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetPassword(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetPassword: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetPassword(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "password", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setPassword";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string password;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					MinitScript::getStringValue(arguments, 1, password) == true) {
					httpDownloadClient->setPassword(password);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetPassword(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetURL: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetURL(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getURL";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->getURL());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetURL(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetURL: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetURL(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setURL";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string url;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					MinitScript::getStringValue(arguments, 1, url) == true) {
					httpDownloadClient->setURL(url);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetURL(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetFile: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetFile(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getFile";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->getFile());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetFile(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetFile: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetFile(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setFile";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string file;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					MinitScript::getStringValue(arguments, 1, file) == true) {
					httpDownloadClient->setFile(file);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetFile(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientReset: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientReset(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::reset";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					httpDownloadClient->reset();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientReset(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientStart: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientStart(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::start";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					httpDownloadClient->start();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientStart(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientCancel: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientCancel(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::cancel";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					httpDownloadClient->cancel();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientCancel(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientJoin: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientJoin(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::join";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					httpDownloadClient->join();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientJoin(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetProgress: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetProgress(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getProgress";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->getProgress());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetProgress(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientIsFinished: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientIsFinished(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::isFinished";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(httpDownloadClient->isFinished());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientIsFinished(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetStatusCode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetStatusCode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getStatusCode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setValue(static_cast<int64_t>(httpDownloadClient->getStatusCode()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetStatusCode(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetResponseHeaders: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetResponseHeaders(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_MAP
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getResponseHeaders";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setType(MinitScript::TYPE_MAP);
					for (const auto& [headerName, headerValue]: httpDownloadClient->getResponseHeaders()) {
						returnValue.setMapEntry(headerName, MinitScript::Variable(string(headerValue)));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetResponseHeaders(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetGETParameters: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetGETParameters(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_MAP
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getGETParameters";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setType(MinitScript::TYPE_MAP);
					for (const auto& [parameterName, parameterValue]: httpDownloadClient->getGETParameters()) {
						returnValue.setMapEntry(parameterName, MinitScript::Variable(string(parameterValue)));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetGETParameters(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetGETParameters: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetGETParameters(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "getParameters", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setGETParameters";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					arguments[1].getType() == MinitScript::TYPE_MAP) {
					//
					unordered_map<string, string> getParameters;
					for (const auto& [parameterName, parameterValue]: *arguments[1].getMapPointer()) {
						getParameters[parameterName] = parameterValue->getValueAsString();
					}
					httpDownloadClient->setGETParameters(getParameters);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetGETParameters(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetHeaders: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientGetHeaders(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_MAP
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getHeaders";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 1 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true) {
					returnValue.setType(MinitScript::TYPE_MAP);
					for (const auto& [headerName, headerValue]: httpDownloadClient->getHeaders()) {
						returnValue.setMapEntry(headerName, MinitScript::Variable(string(headerValue)));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientGetHeaders(minitScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetHeaders: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHTTPDownloadClientSetHeaders(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_MAP, .name = "headers", .optional = false, .reference = false, .nullable = false },
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setHeaders";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient) == true &&
					arguments[1].getType() == MinitScript::TYPE_MAP) {
					//
					unordered_map<string, string> headers;
					for (const auto& [mapEntryName, mapEntryValue]: *arguments[1].getMapPointer()) {
						headers[mapEntryName] = mapEntryValue->getValueAsString();
					}
					httpDownloadClient->setHeaders(headers);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHTTPDownloadClientSetHeaders(minitScript));
	}
}

void HTTPDownloadClientClass::unsetVariableValue(MinitScript::Variable& variable) const {
	delete static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr());
}

void HTTPDownloadClientClass::setVariableValue(MinitScript::Variable& variable) const {
	variable.setValuePtr(new shared_ptr<_HTTPDownloadClient>(nullptr));
}

void HTTPDownloadClientClass::setVariableValue(MinitScript::Variable& variable, const void* value) const {
	*static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr()) = *static_cast<const shared_ptr<_HTTPDownloadClient>*>(value);
}

void HTTPDownloadClientClass::copyVariable(MinitScript::Variable& to, const MinitScript::Variable& from) const {
	to.setType(MinitScript::TYPE_HTTPDOWNLOADCLIENT);
	*static_cast<shared_ptr<_HTTPDownloadClient>*>(to.getValuePtr()) = *static_cast<shared_ptr<_HTTPDownloadClient>*>(from.getValuePtr());
}

bool HTTPDownloadClientClass::mul(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool HTTPDownloadClientClass::div(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool HTTPDownloadClientClass::add(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

bool HTTPDownloadClientClass::sub(MinitScript* minitScript, const span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) const {
	return false;
}

const string& HTTPDownloadClientClass::getTypeAsString() const {
	return TYPE_NAME;
}

const string HTTPDownloadClientClass::getValueAsString(const MinitScript::Variable& variable) const {
	const auto& httpDownloadClient = *static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr());
	return "HTTPDownloadClientClass(url: " + httpDownloadClient->getURL() + ", file: " + httpDownloadClient->getFile() + ")";
}

MinitScript::DataType::ScriptContext* HTTPDownloadClientClass::createScriptContext() const {
	return new HTTPDownloadClientClassScriptContext();
}

void HTTPDownloadClientClass::deleteScriptContext(MinitScript::DataType::ScriptContext* context) const {
	delete static_cast<HTTPDownloadClientClassScriptContext*>(context);
}

void HTTPDownloadClientClass::garbageCollection(MinitScript::DataType::ScriptContext* context) const {
	auto& scriptContext = *static_cast<HTTPDownloadClientClassScriptContext*>(context);
	auto& instances = scriptContext.getInstances();
	for (auto i = 0; i < instances.size(); i++) {
		auto& instance = instances[i];
		if (instance.use_count() == 1 && instance->isFinished() == true) {
			instance->join();
			instances.erase(instances.begin() + i);
			i--;
		}
	}
	if (instances.empty() == true) {
		scriptContext.unsetRequiresGarbageCollection();
	}
}
