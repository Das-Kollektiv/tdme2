#include <span>

#include <memory>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/ScriptMethods.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Time.h>

using std::span;
using std::make_unique;

using miniscript::miniscript::ScriptMethods;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::Console;
using miniscript::utilities::Time;

void ScriptMethods::registerMethods(MiniScript* miniScript) {
	// script methods
	{
		//
		class ScriptMethodScriptWaitForCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWaitForCondition(MiniScript* miniScript): miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.waitForCondition";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				// script bindings
				miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
				miniScript->getScriptState().timeWaitTime = 100LL;
				miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_WAIT_FOR_CONDITION);
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptWaitForCondition(miniScript));
	}
	{
		//
		class ScriptMethodScriptWait: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWait(MiniScript* miniScript):
				MiniScript::ScriptMethod({
					{ .type = MiniScript::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.wait";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
					miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
					miniScript->getScriptState().timeWaitTime = time;
					miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_WAIT);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptWait(miniScript));
	}
	{
		//
		class ScriptMethodScriptEmit: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEmit(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.emit";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
					miniScript->emit(condition);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptEmit(miniScript));
	}
	{
		//
		class ScriptMethodScriptEnableNamedCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEnableNamedCondition(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.enableNamedCondition"; // METHOD_ENABLENAMEDCONDITION;
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->enabledNamedConditions.erase(
						remove(
							miniScript->enabledNamedConditions.begin(),
							miniScript->enabledNamedConditions.end(),
							name
						),
						miniScript->enabledNamedConditions.end()
					);
					miniScript->enabledNamedConditions.push_back(name);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptEnableNamedCondition(miniScript));
	}
	{
		//
		class ScriptMethodScriptDisableNamedCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptDisableNamedCondition(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.disableNamedCondition"; // METHOD_DISABLENAMEDCONDITION;
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->enabledNamedConditions.erase(
						remove(
							miniScript->enabledNamedConditions.begin(),
							miniScript->enabledNamedConditions.end(),
							name
						),
						miniScript->enabledNamedConditions.end()
					);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptDisableNamedCondition(miniScript));
	}
	{
		//
		class ScriptMethodScriptGetNamedConditions: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptGetNamedConditions(MiniScript* miniScript):
				MiniScript::ScriptMethod({}, MiniScript::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getNamedConditions";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string result;
				for (const auto& namedCondition: miniScript->enabledNamedConditions) {
					result+= result.empty() == false?",":namedCondition;
				}
				returnValue.setValue(result);
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptGetNamedConditions(miniScript));
	}
	{
		//
		class ScriptMethodScriptEvaluate: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEvaluate(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.evaluate";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string statementString;
				if (miniScript->getStringValue(argumentValues, 0, statementString, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (miniScript->evaluate(statementString, returnValue) == false) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": '" + statementString + "': An error occurred");
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptEvaluate(miniScript));
	}
	{
		//
		class ScriptMethodScriptCall: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptCall(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.call"; // METHOD_SCRIPTCALL;
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == MiniScript::SCRIPTIDX_NONE) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
						miniScript->startErrorScript();
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							vector<MiniScript::ScriptVariable> callArgumentValues(argumentValues.size() - 1);
							for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues[i - 1] = move(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < argumentValues.size(); i++) argumentValues[i] = move(callArgumentValues[i - 1]);
						#else
							span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#endif
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptCall(miniScript));
	}
	{
		//
		class ScriptMethodScriptStop: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptStop(MiniScript* miniScript): MiniScript::ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.stop";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				//
				miniScript->stopScriptExecution();
				miniScript->stopRunning();
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptStop(miniScript));
	}
	{
		//
		class ScriptMethodScriptGetVariables: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptGetVariables(MiniScript* miniScript): MiniScript::ScriptMethod({}, MiniScript::TYPE_MAP), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getVariables";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_MAP);
				for (const auto& [variableName, variableValue]: miniScript->getScriptState().variables) {
					returnValue.setMapEntry(variableName, *variableValue);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodScriptGetVariables(miniScript));
	}
}
