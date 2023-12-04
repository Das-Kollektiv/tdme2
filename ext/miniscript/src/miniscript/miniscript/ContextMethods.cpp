#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/ContextMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>

using std::span;

using miniscript::miniscript::ContextMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;

void ContextMethods::registerMethods(MiniScript* miniScript) {
	if (miniScript->getContext() == nullptr) return;
	{
		//
		class ScriptMethodContextScriptHasCallable: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodContextScriptHasCallable(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "context.script.hasCallable";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string scriptId;
				string callable;
				if (MiniScript::getStringValue(argumentValues, 0, scriptId) == false ||
					MiniScript::getStringValue(argumentValues, 1, callable) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto script = miniScript->getContext()->getScript(scriptId);
					if (script == nullptr) {
						returnValue.setValue(false);
					} else {
						auto scriptIdx = script->getFunctionScriptIdx(callable);
						if (scriptIdx == MiniScript::SCRIPTIDX_NONE || script->getScripts()[scriptIdx].callable == false) {
							returnValue.setValue(false);
						} else {
							returnValue.setValue(true);
						}
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodContextScriptHasCallable(miniScript));
	}
	{
		//
		class ScriptMethodContextScriptCall: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodContextScriptCall(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "callable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "context.script.call";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string scriptId;
				string callable;
				if (MiniScript::getStringValue(argumentValues, 0, scriptId) == false ||
					MiniScript::getStringValue(argumentValues, 1, callable) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto script = dynamic_cast<MiniScript*>(miniScript->getContext()->getScript(scriptId));
					if (script == nullptr) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no script with given id: " + scriptId);
						miniScript->startErrorScript();
					} else {
						auto scriptIdx = script->getFunctionScriptIdx(callable);
						if (scriptIdx == MiniScript::SCRIPTIDX_NONE || script->getScripts()[scriptIdx].callable == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": callable not found: " + callable);
							miniScript->startErrorScript();
						} else {
							#if defined (__APPLE__)
								// MACOSX currently does not support initializing span using begin and end iterators,
								vector<MiniScript::ScriptVariable> callArgumentValues(argumentValues.size() - 2);
								for (auto i = 2; i < argumentValues.size(); i++) callArgumentValues[i - 2] = move(argumentValues[i]);
								// call
								span callArgumentValuesSpan(callArgumentValues);
								script->call(scriptIdx, callArgumentValuesSpan, returnValue);
								// move back arguments
								for (auto i = 2; i < argumentValues.size(); i++) argumentValues[i] = move(callArgumentValues[i - 2]);
							#else
								span callArgumentValuesSpan(argumentValues.begin() + 2, argumentValues.end());
								script->call(scriptIdx, callArgumentValuesSpan, returnValue);
							#endif
						}
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new ScriptMethodContextScriptCall(miniScript));
	}
	{
		//
		class ScriptMethodContextScriptLoadScript: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodContextScriptLoadScript(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "pathName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_STRING, .name = "fileName", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "verbose", .optional = true, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "context.script.loadScript";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string scriptId;
				string pathName;
				string fileName;
				bool verbose = false;
				if (MiniScript::getStringValue(argumentValues, 0, scriptId) == false ||
					MiniScript::getStringValue(argumentValues, 1, pathName) == false ||
					MiniScript::getStringValue(argumentValues, 2, fileName) == false ||
					MiniScript::getBooleanValue(argumentValues, 3, verbose, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto script = make_unique<MiniScript>();
					script->setContext(miniScript->getContext());
					script->parseScript(
						pathName,
						fileName
					);
					if (script != nullptr) {
						// verbose
						if (verbose == true) Console::println(script->getInformation());
						//
						if (script->isValid() == false) {
							Console::println("Script not valid.");
						} else {
							miniScript->getContext()->addScript(scriptId, script.release());
						}
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodContextScriptLoadScript(miniScript));
	}
	{
		//
		class ScriptMethodContextScriptRemoveScript: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodContextScriptRemoveScript(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "scriptId", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "context.script.removeScript";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string scriptId;
				if (MiniScript::getStringValue(argumentValues, 0, scriptId) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->getContext()->removeScript(scriptId);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodContextScriptRemoveScript(miniScript));
	}
	{
		//
		class ScriptMethodContextScriptGetScriptIds: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodContextScriptGetScriptIds(MiniScript* miniScript):
				MiniScript::ScriptMethod({}, MiniScript::TYPE_ARRAY),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "context.script.getScriptIds";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				auto scriptIds = miniScript->getContext()->getScriptIds();
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (const auto& scriptId: scriptIds) returnValue.pushArrayEntry(scriptId);
			}
		};
		miniScript->registerMethod(new ScriptMethodContextScriptGetScriptIds(miniScript));
	}
}
