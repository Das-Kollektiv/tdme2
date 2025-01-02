#include <span>

#include <memory>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/ScriptMethods.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Time.h>

using std::span;
using std::make_unique;

using minitscript::minitscript::ScriptMethods;

using minitscript::minitscript::MinitScript;

using _Console = minitscript::utilities::Console;
using _Time = minitscript::utilities::Time;

void ScriptMethods::registerConstants(MinitScript* minitScript) {
}

void ScriptMethods::registerMethods(MinitScript* minitScript) {
	// script methods
	{
		//
		class MethodScriptWaitForCondition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptWaitForCondition(MinitScript* minitScript): minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.waitForCondition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					minitScript->getScriptState().timeWaitStarted = _Time::getCurrentMillis();
					minitScript->getScriptState().timeWaitTime = 100LL;
					minitScript->setScriptStateState(MinitScript::STATEMACHINESTATE_WAIT_FOR_CONDITION);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptWaitForCondition(minitScript));
	}
	{
		//
		class MethodScriptWait: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptWait(MinitScript* minitScript):
				MinitScript::Method({
					{ .type = MinitScript::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
				}),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.wait";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t time;
				if (arguments.size() == 1 &&
					minitScript->getIntegerValue(arguments, 0, time) == true) {
					minitScript->getScriptState().timeWaitStarted = _Time::getCurrentMillis();
					minitScript->getScriptState().timeWaitTime = time;
					minitScript->setScriptStateState(MinitScript::STATEMACHINESTATE_WAIT);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptWait(minitScript));
	}
	#if defined(MINITSCRIPT_EVENTS)
		// events
		{
			//
			class MethodScriptEmit: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodScriptEmit(MinitScript* minitScript):
					MinitScript::Method(
						{
							{ .type = MinitScript::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false }
						}
					),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "script.emit";
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					string condition;
					if (arguments.size() == 1 &&
						MinitScript::getStringValue(arguments, 0, condition) == true) {
						minitScript->emit(condition);
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodScriptEmit(minitScript));
		}
	#endif
	#if defined(MINITSCRIPT_EVENTS)
		// events
		{
			//
			class MethodScriptEnableNamedCondition: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodScriptEnableNamedCondition(MinitScript* minitScript):
					MinitScript::Method(
						{
							{ .type = MinitScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
						}
					),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "script.enableNamedCondition"; // METHOD_ENABLENAMEDCONDITION;
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					string name;
					if (arguments.size() == 1 &&
						MinitScript::getStringValue(arguments, 0, name) == true) {
						minitScript->enabledNamedConditions.erase(
							remove(
								minitScript->enabledNamedConditions.begin(),
								minitScript->enabledNamedConditions.end(),
								name
							),
							minitScript->enabledNamedConditions.end()
						);
						minitScript->enabledNamedConditions.push_back(name);
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodScriptEnableNamedCondition(minitScript));
		}
		{
			//
			class MethodScriptDisableNamedCondition: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodScriptDisableNamedCondition(MinitScript* minitScript):
					MinitScript::Method(
						{
							{ .type = MinitScript::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
						}
					),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "script.disableNamedCondition"; // METHOD_DISABLENAMEDCONDITION;
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					string name;
					if (arguments.size() == 1 &&
						MinitScript::getStringValue(arguments, 0, name) == true) {
						minitScript->enabledNamedConditions.erase(
							remove(
								minitScript->enabledNamedConditions.begin(),
								minitScript->enabledNamedConditions.end(),
								name
							),
							minitScript->enabledNamedConditions.end()
						);
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodScriptDisableNamedCondition(minitScript));
		}
		{
			//
			class MethodScriptGetNamedConditions: public MinitScript::Method {
			private:
				MinitScript* minitScript { nullptr };
			public:
				MethodScriptGetNamedConditions(MinitScript* minitScript):
					MinitScript::Method({}, MinitScript::TYPE_STRING),
					minitScript(minitScript) {}
				const string getMethodName() override {
					return "script.getNamedConditions";
				}
				void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
					if (arguments.size() == 0) {
						string result;
						for (const auto& namedCondition: minitScript->enabledNamedConditions) {
							result+= result.empty() == false?",":namedCondition;
						}
						returnValue.setValue(result);
					} else {
						MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
					}
				}
			};
			minitScript->registerMethod(new MethodScriptGetNamedConditions(minitScript));
		}
	#endif
	{
		//
		class MethodScriptEvaluate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptEvaluate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.evaluate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string statementString;
				if (arguments.size() == 1 &&
					minitScript->getStringValue(arguments, 0, statementString) == true) {
					if (minitScript->evaluate(statementString, returnValue) == false) {
						_Console::printLine(getMethodName() + "(): " + minitScript->getSubStatementInformation(subStatement) + ": '" + statementString + "': An error occurred");
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptEvaluate(minitScript));
	}
	{
		//
		class MethodScriptCall: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptCall(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.call"; // METHOD_SCRIPTCALL;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string function;
				if (arguments.size() >= 1 &&
					minitScript->getStringValue(arguments, 0, function) == true) {
					auto scriptIdx = minitScript->getFunctionScriptIdx(function);
					if (scriptIdx == MinitScript::SCRIPTIDX_NONE || minitScript->getScripts()[scriptIdx].type != MinitScript::Script::TYPE_FUNCTION) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + function);
					} else {
						#if defined (__clang__)
							// Clang currently does not support initializing span using begin and end iterators,
							vector<MinitScript::Variable> callArguments(arguments.size() - 1);
							for (auto i = 1; i < arguments.size(); i++) callArguments[i - 1] = move(arguments[i]);
							// call
							span callArgumentsSpan(callArguments);
							minitScript->call(scriptIdx, callArgumentsSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 1]);
						#else
							span callArgumentsSpan(arguments.begin() + 1, arguments.end());
							minitScript->call(scriptIdx, callArgumentsSpan, returnValue);
						#endif
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodScriptCall(minitScript));
	}
	{
		//
		class MethodScriptCallByIndex: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptCallByIndex(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "functionScriptIdx", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.callByIndex"; // METHOD_SCRIPTCALLBYINDEX;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t functionScriptIdx;
				if (arguments.size() >= 1 &&
					minitScript->getIntegerValue(arguments, 0, functionScriptIdx) == true) {
					if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE ||
						functionScriptIdx < 0 ||
						functionScriptIdx >= minitScript->getScripts().size() ||
						minitScript->getScripts()[functionScriptIdx].type != MinitScript::Script::TYPE_FUNCTION) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function script index invalid: " + to_string(functionScriptIdx));
					} else {
						#if defined (__clang__)
							// Clang currently does not support initializing span using begin and end iterators,
							vector<MinitScript::Variable> callArguments(arguments.size() - 1);
							for (auto i = 1; i < arguments.size(); i++) callArguments[i - 1] = move(arguments[i]);
							// call
							span callArgumentsSpan(callArguments);
							minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 1]);
						#else
							span callArgumentsSpan(arguments.begin() + 1, arguments.end());
							minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
						#endif
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isVariadic() const override {
				return true;
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodScriptCallByIndex(minitScript));
	}
	{
		//
		class MethodScriptCallFunction: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptCallFunction(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_FUNCTION_ASSIGNMENT, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.callFunction";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string function;
				auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
				if (arguments.size() >= 1 &&
					minitScript->getFunctionValue(arguments, 0, function, functionScriptIdx) == true) {
					if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
						functionScriptIdx = minitScript->getFunctionScriptIdx(function);
					}
					if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE || minitScript->getScripts()[functionScriptIdx].type != MinitScript::Script::TYPE_FUNCTION) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Function not found: " + function);
					} else {
						#if defined (__clang__)
							// Clang currently does not support initializing span using begin and end iterators,
							vector<MinitScript::Variable> callArguments(arguments.size() - 1);
							for (auto i = 1; i < arguments.size(); i++) callArguments[i - 1] = move(arguments[i]);
							// call
							span callArgumentsSpan(callArguments);
							minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < arguments.size(); i++) arguments[i] = move(callArguments[i - 1]);
						#else
							span callArgumentsSpan(arguments.begin() + 1, arguments.end());
							minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
						#endif
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodScriptCallFunction(minitScript));
	}
	{
		//
		class MethodScriptCallStacklet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptCallStacklet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "stacklet", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.callStacklet"; // METHOD_SCRIPTCALLSTACKLET;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stacklet;
				if (arguments.size() >= 1 &&
					minitScript->getStringValue(arguments, 0, stacklet) == true) {
					auto scriptIdx = minitScript->getFunctionScriptIdx(stacklet);
					if (scriptIdx == MinitScript::SCRIPTIDX_NONE || minitScript->getScripts()[scriptIdx].type != MinitScript::Script::TYPE_STACKLET) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Stacklet not found: " + stacklet);
					} else {
						vector<MinitScript::Variable> callArguments(0);
						span callArgumentsSpan(callArguments);
						minitScript->callStacklet(scriptIdx, callArgumentsSpan, returnValue);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptCallStacklet(minitScript));
	}
	{
		//
		class MethodScriptCallStackletByIndex: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptCallStackletByIndex(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "stackletScriptIndex", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.callStackletByIndex"; // METHOD_SCRIPTCALLSTACKLETBYINDEX;
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t stackletScriptIdx;
				if (arguments.size() == 1 &&
					minitScript->getIntegerValue(arguments, 0, stackletScriptIdx) == true) {
					if (stackletScriptIdx == MinitScript::SCRIPTIDX_NONE ||
						stackletScriptIdx < 0 ||
						stackletScriptIdx >= minitScript->getScripts().size() ||
						minitScript->getScripts()[stackletScriptIdx].type != MinitScript::Script::TYPE_STACKLET) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Stacklet script index invalid: " + to_string(stackletScriptIdx));
					} else {
						vector<MinitScript::Variable> callArguments(0);
						span callArgumentsSpan(callArguments);
						minitScript->callStacklet(stackletScriptIdx, callArgumentsSpan, returnValue);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodScriptCallStackletByIndex(minitScript));
	}
	{
		//
		class MethodScriptStop: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptStop(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.stop";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					minitScript->stopScriptExecution();
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptStop(minitScript));
	}
	{
		//
		class MethodScriptGetVariables: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptGetVariables(MinitScript* minitScript): MinitScript::Method({}, MinitScript::TYPE_MAP), minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.getVariables";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setType(MinitScript::TYPE_MAP);
					for (const auto& [variableName, variableValue]: minitScript->getScriptState().variables) {
						returnValue.setMapEntry(variableName, *variableValue);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptGetVariables(minitScript));
	}
	{
		//
		class MethodScriptIsNative: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptIsNative(MinitScript* minitScript): MinitScript::Method({}, MinitScript::TYPE_BOOLEAN),
			minitScript(minitScript) {}

			const string getMethodName() override {
				return "script.isNative";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					returnValue.setValue(minitScript->isNative());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptIsNative(minitScript));
	}
	{
		//
		class MethodScriptErrorGetMessage: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptErrorGetMessage(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_STRING, true),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.error.getMessage";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					const auto& errorSubStatement = minitScript->getErrorSubStatement();
					if (errorSubStatement.statement != nullptr) {
						returnValue.setValue(minitScript->getErrorMessage());
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptErrorGetMessage(minitScript));
	}
	{
		//
		class MethodScriptErrorGetStatement: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodScriptErrorGetStatement(MinitScript* minitScript):
				MinitScript::Method({}, MinitScript::TYPE_MAP, true),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "script.error.getStatement";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					const auto& errorSubStatement = minitScript->getErrorSubStatement();
					if (errorSubStatement.statement != nullptr) {
						returnValue.setType(MinitScript::TYPE_MAP);
						returnValue.setMapEntry("script", MinitScript::Variable(minitScript->getScriptPathName() + "/" + minitScript->getScriptFileName()));
						returnValue.setMapEntry("line", MinitScript::Variable(static_cast<int64_t>(errorSubStatement.statement->line + errorSubStatement.subLineIdx)));
						returnValue.setMapEntry("statementIndex", MinitScript::Variable(static_cast<int64_t>(errorSubStatement.statement->statementIdx)));
						returnValue.setMapEntry("statement", MinitScript::Variable(errorSubStatement.statement->statement));
						returnValue.setMapEntry("executableStatement", MinitScript::Variable(errorSubStatement.statement->executableStatement));
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodScriptErrorGetStatement(minitScript));
	}
}
