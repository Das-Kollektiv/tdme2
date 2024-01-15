#include <memory>
#include <span>
#include <string>

#include <miniscript/miniscript/MiniScript.h>

#include <miniscript/miniscript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/miniscript/HTTPDownloadClientClass.h>
#include <miniscript/network/httpclient/HTTPDownloadClient.h>

using std::make_shared;
using std::shared_ptr;
using std::span;
using std::string;

using miniscript::miniscript::HTTPDownloadClientClass;

using miniscript::miniscript::MiniScript;
using _Console = miniscript::utilities::Console;
using _HTTPDownloadClient = miniscript::network::httpclient::HTTPDownloadClient;

const string HTTPDownloadClientClass::TYPE_NAME = "HTTPDownloadClient";

void HTTPDownloadClientClass::initialize() {
}

void HTTPDownloadClientClass::registerConstants(MiniScript* miniScript) const {
}

void HTTPDownloadClientClass::registerMethods(MiniScript* miniScript) const {
	//
	{
		//
		class MethodHTTPDownloadClient: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClient(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_HTTPDOWNLOADCLIENT),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				auto& scriptContext = *static_cast<HTTPDownloadClientClass::HTTPDownloadClientClassScriptContext*>(miniScript->getDataTypeScriptContext(MiniScript::TYPE_HTTPDOWNLOADCLIENT));
				//
				auto httpDownloadClient = make_shared<_HTTPDownloadClient>();
				scriptContext.getInstances().push_back(httpDownloadClient);
				scriptContext.setRequiresGarbageCollection();
				//
				returnValue.setType(MiniScript::TYPE_HTTPDOWNLOADCLIENT);
				returnValue.setValue(&httpDownloadClient);
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClient(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetUserName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetUserName(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getUserName";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->getUsername());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetUserName(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetUserName: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetUserName(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "userName", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setUserName";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string userName;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					MiniScript::getStringValue(arguments, 1, userName, false) == true) {
					httpDownloadClient->setUsername(userName);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetUserName(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetPassword: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetPassword(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getPassword";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->getPassword());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetPassword(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetPassword: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetPassword(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "password", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setPassword";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string password;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					MiniScript::getStringValue(arguments, 1, password, false) == true) {
					httpDownloadClient->setPassword(password);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetPassword(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetURL: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetURL(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getURL";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->getURL());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetURL(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetURL: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetURL(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setURL";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string url;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					MiniScript::getStringValue(arguments, 1, url, false) == true) {
					httpDownloadClient->setURL(url);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetURL(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetFile: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetFile(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getFile";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->getFile());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetFile(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetFile: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetFile(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "url", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setFile";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				string file;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					MiniScript::getStringValue(arguments, 1, file, false) == true) {
					httpDownloadClient->setFile(file);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetFile(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientReset: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientReset(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::reset";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					httpDownloadClient->reset();
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientReset(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientStart: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientStart(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::start";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					httpDownloadClient->start();
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientStart(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientCancel: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientCancel(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::cancel";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					httpDownloadClient->cancel();
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientCancel(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientJoin: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientJoin(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::join";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					httpDownloadClient->join();
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientJoin(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetProgress: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetProgress(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getProgress";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->getProgress());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetProgress(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientIsFinished: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientIsFinished(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::isFinished";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(httpDownloadClient->isFinished());
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientIsFinished(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetStatusCode: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetStatusCode(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getStatusCode";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setValue(static_cast<int64_t>(httpDownloadClient->getStatusCode()));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetStatusCode(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetResponseHeaders: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetResponseHeaders(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getResponseHeaders";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setType(MiniScript::TYPE_MAP);
					for (const auto& [headerName, headerValue]: httpDownloadClient->getResponseHeaders()) {
						returnValue.setMapEntry(headerName, MiniScript::Variable(string(headerValue)));
					}
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetResponseHeaders(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetGETParameters: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetGETParameters(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getGETParameters";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setType(MiniScript::TYPE_MAP);
					for (const auto& [parameterName, parameterValue]: httpDownloadClient->getGETParameters()) {
						returnValue.setMapEntry(parameterName, MiniScript::Variable(string(parameterValue)));
					}
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetGETParameters(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetGETParameters: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetGETParameters(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "getParameters", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setGETParameters";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					arguments[1].getType() == MiniScript::TYPE_MAP) {
					//
					unordered_map<string, string> getParameters;
					for (const auto& [parameterName, parameterValue]: *arguments[1].getMapPointer()) {
						getParameters[parameterName] = parameterValue->getValueAsString();
					}
					httpDownloadClient->setGETParameters(getParameters);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetGETParameters(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientGetHeaders: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientGetHeaders(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::getHeaders";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true) {
					returnValue.setType(MiniScript::TYPE_MAP);
					for (const auto& [headerName, headerValue]: httpDownloadClient->getHeaders()) {
						returnValue.setMapEntry(headerName, MiniScript::Variable(string(headerValue)));
					}
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientGetHeaders(miniScript));
	}
	{
		//
		class MethodHTTPDownloadClientSetHeaders: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientSetHeaders(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_MAP, .name = "headers", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::setHeaders";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				shared_ptr<_HTTPDownloadClient> httpDownloadClient;
				if (arguments.size() == 2 &&
					HTTPDownloadClientClass::getHTTPDownloadClientValue(arguments, 0, httpDownloadClient, false) == true &&
					arguments[1].getType() == MiniScript::TYPE_MAP) {
					//
					unordered_map<string, string> headers;
					for (const auto& [mapEntryName, mapEntryValue]: *arguments[1].getMapPointer()) {
						headers[mapEntryName] = mapEntryValue->getValueAsString();
					}
					httpDownloadClient->setHeaders(headers);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClientSetHeaders(miniScript));
	}
}

void HTTPDownloadClientClass::unsetVariableValue(MiniScript::Variable& variable) const {
	delete static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr());
}

void HTTPDownloadClientClass::setVariableValue(MiniScript::Variable& variable) const {
	variable.setValuePtr(new shared_ptr<_HTTPDownloadClient>(nullptr));
}

void HTTPDownloadClientClass::setVariableValue(MiniScript::Variable& variable, const void* value) const {
	*static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr()) = *static_cast<const shared_ptr<_HTTPDownloadClient>*>(value);
}

void HTTPDownloadClientClass::copyVariable(MiniScript::Variable& to, const MiniScript::Variable& from) const {
	to.setType(MiniScript::TYPE_HTTPDOWNLOADCLIENT);
	*static_cast<shared_ptr<_HTTPDownloadClient>*>(to.getValuePtr()) = *static_cast<shared_ptr<_HTTPDownloadClient>*>(from.getValuePtr());
}

bool HTTPDownloadClientClass::mul(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool HTTPDownloadClientClass::div(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool HTTPDownloadClientClass::add(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

bool HTTPDownloadClientClass::sub(MiniScript* miniScript, const span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) const {
	return false;
}

const string& HTTPDownloadClientClass::getTypeAsString() const {
	return TYPE_NAME;
}

const string HTTPDownloadClientClass::getValueAsString(const MiniScript::Variable& variable) const {
	const auto& httpDownloadClient = *static_cast<shared_ptr<_HTTPDownloadClient>*>(variable.getValuePtr());
	return "HTTPDownloadClientClass(url: " + httpDownloadClient->getURL() + ", file: " + httpDownloadClient->getFile() + ")";
}

MiniScript::DataType::ScriptContext* HTTPDownloadClientClass::createScriptContext() const {
	return new HTTPDownloadClientClassScriptContext();
}

void HTTPDownloadClientClass::deleteScriptContext(MiniScript::DataType::ScriptContext* context) const {
	delete static_cast<HTTPDownloadClientClassScriptContext*>(context);
}

void HTTPDownloadClientClass::garbageCollection(MiniScript::DataType::ScriptContext* context) const {
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
