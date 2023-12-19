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

using _Console = miniscript::utilities::Console;
using _Time = miniscript::utilities::Time;

void ScriptMethods::registerMethods(MiniScript* miniScript) {
	// script methods
	{
		//
		class MethodScriptWaitForCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptWaitForCondition(MiniScript* miniScript): miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.waitForCondition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				// script bindings
				miniScript->getScriptState().timeWaitStarted = _Time::getCurrentMillis();
				miniScript->getScriptState().timeWaitTime = 100LL;
				miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_WAIT_FOR_CONDITION);
			}
		};
		miniScript->registerMethod(new MethodScriptWaitForCondition(miniScript));
	}
	{
		//
		class MethodScriptWait: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptWait(MiniScript* miniScript):
				MiniScript::Method({
					{ .type = MiniScript::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.wait";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(arguments, 0, time) == true) {
					miniScript->getScriptState().timeWaitStarted = _Time::getCurrentMillis();
					miniScript->getScriptState().timeWaitTime = time;
					miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_WAIT);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		miniScript->registerMethod(new MethodScriptWait(miniScript));
	}
	{
		//
		class MethodScriptEmit: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptEmit(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.emit";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string condition;
				if (MiniScript::getStringValue(arguments, 0, condition, false) == true) {
					miniScript->emit(condition);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodScriptEmit(miniScript));
	}
	{
		//
		class MethodScriptEnableNamedCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptEnableNamedCondition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.enableNamedCondition"; // METHOD_ENABLENAMEDCONDITION;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string name;
				if (MiniScript::getStringValue(arguments, 0, name, false) == true) {
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
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodScriptEnableNamedCondition(miniScript));
	}
	{
		//
		class MethodScriptDisableNamedCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptDisableNamedCondition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.disableNamedCondition"; // METHOD_DISABLENAMEDCONDITION;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string name;
				if (MiniScript::getStringValue(arguments, 0, name, false) == true) {
					miniScript->enabledNamedConditions.erase(
						remove(
							miniScript->enabledNamedConditions.begin(),
							miniScript->enabledNamedConditions.end(),
							name
						),
						miniScript->enabledNamedConditions.end()
					);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodScriptDisableNamedCondition(miniScript));
	}
	{
		//
		class MethodScriptGetNamedConditions: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptGetNamedConditions(MiniScript* miniScript):
				MiniScript::Method({}, MiniScript::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getNamedConditions";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string result;
				for (const auto& namedCondition: miniScript->enabledNamedConditions) {
					result+= result.empty() == false?",":namedCondition;
				}
				returnValue.setValue(result);
			}
		};
		miniScript->registerMethod(new MethodScriptGetNamedConditions(miniScript));
	}
	{
		//
		class MethodScriptEvaluate: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptEvaluate(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.evaluate";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string statementString;
				if (miniScript->getStringValue(arguments, 0, statementString, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (miniScript->evaluate(statementString, returnValue) == false) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": '" + statementString + "': An error occurred");
					}
				}
			}
		};
		miniScript->registerMethod(new MethodScriptEvaluate(miniScript));
	}
	{
		//
		class MethodScriptCall: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptCall(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.call"; // METHOD_SCRIPTCALL;
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string function;
				if (miniScript->getStringValue(arguments, 0, function) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == MiniScript::SCRIPTIDX_NONE) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
						miniScript->startErrorScript();
					} else {
						#if defined (__clang__)
							// Clang currently does not support initializing span using begin and end iterators,
							vector<MiniScript::Variable> callArguments(arguments.size() - 1);
							for (auto i = 1; i < arguments.size(); i++) callArguments[i - 1] = move(arguments[i]);
							// call
							span callArgumentsSpan(callArguments);
							miniScript->call(scriptIdx, callArgumentsSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 1]);
						#else
							span callArgumentsSpan(arguments.begin() + 1, arguments.end());
							miniScript->call(scriptIdx, callArgumentsSpan, returnValue);
						#endif
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodScriptCall(miniScript));
	}
	{
		//
		class MethodScriptStop: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptStop(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.stop";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				//
				miniScript->stopScriptExecution();
				miniScript->stopRunning();
			}
		};
		miniScript->registerMethod(new MethodScriptStop(miniScript));
	}
	{
		//
		class MethodScriptGetVariables: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptGetVariables(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_MAP), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getVariables";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setType(MiniScript::TYPE_MAP);
				for (const auto& [variableName, variableValue]: miniScript->getScriptState().variables) {
					returnValue.setMapEntry(variableName, *variableValue);
				}
			}
		};
		miniScript->registerMethod(new MethodScriptGetVariables(miniScript));
	}
	{
		//
		class MethodScriptIsNative: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodScriptIsNative(MiniScript* miniScript): MiniScript::Method({}, MiniScript::TYPE_BOOLEAN),
			miniScript(miniScript) {}

			const string getMethodName() override {
				return "script.isNative";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				returnValue.setValue(miniScript->isNative());
			}
		};
		miniScript->registerMethod(new MethodScriptIsNative(miniScript));
	}
}
