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
				auto& scriptContext = *static_cast<HTTPDownloadClientClass::ScriptContext*>(miniScript->getDataTypeScriptContext(MiniScript::TYPE_HTTPDOWNLOADCLIENT));
				//
				auto httpDownloadClient = make_shared<_HTTPDownloadClient>();
				scriptContext.instances.push_back(httpDownloadClient);
				//
				returnValue.setType(MiniScript::TYPE_HTTPDOWNLOADCLIENT);
				returnValue.setValue(&httpDownloadClient);
			}
		};
		miniScript->registerMethod(new MethodHTTPDownloadClient(miniScript));
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
		class MethodHTTPDownloadClientExecute: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodHTTPDownloadClientExecute(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_HTTPDOWNLOADCLIENT, .name = "httpdownloadclient", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "HTTPDownloadClient::execute";
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
		miniScript->registerMethod(new MethodHTTPDownloadClientExecute(miniScript));
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

void* HTTPDownloadClientClass::createScriptContext() const {
	return new ScriptContext();
}

void HTTPDownloadClientClass::deleteScriptContext(void* context) const {
	delete static_cast<ScriptContext*>(context);
}

void HTTPDownloadClientClass::garbageCollection(void* context) const {
	auto& scriptContext = *static_cast<ScriptContext*>(context);
	for (auto i = 0; i < scriptContext.instances.size(); i++) {
		auto& instance = scriptContext.instances[i];
		if (instance.use_count() == 1 && instance->isFinished() == true) {
			instance->join();
			scriptContext.instances.erase(scriptContext.instances.begin() + i);
			i--;
		}
	}
}
