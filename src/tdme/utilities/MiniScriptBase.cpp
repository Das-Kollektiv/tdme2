#include <span>

#include <tdme/tdme.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptBase.h>

using std::span;

using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptBase;

void MiniScriptBase::registerMethods(MiniScript* miniScript) {
	// base methods
	{
		//
		class ScriptMethodReturn: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodReturn(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "return";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (miniScript->isFunctionRunning() == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
					miniScript->startErrorScript();
				} else
				if (argumentValues.size() == 0) {
					miniScript->stopRunning();
				} else
				if (argumentValues.size() == 1) {
					auto& scriptState = miniScript->getScriptState();
					scriptState.returnValue = argumentValues[0];
					miniScript->stopRunning();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodReturn(miniScript));
	}
	{
		//
		class ScriptMethodEnd: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEnd(MiniScript* miniScript): MiniScript::ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "end";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (miniScript->getScriptState().endTypeStack.empty() == true) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
					miniScript->startErrorScript();
				} else {
					auto endType = miniScript->getScriptState().endTypeStack.top();
					miniScript->getScriptState().endTypeStack.pop();
					switch(endType) {
						case MiniScript::ScriptState::ENDTYPE_BLOCK:
							if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
								miniScript->stopRunning();
							}
							break;
						case MiniScript::ScriptState::ENDTYPE_FOR:
							// no op
							break;
						case MiniScript::ScriptState::ENDTYPE_IF:
							miniScript->getScriptState().conditionStack.pop();
							break;
					}
					if (statement.gotoStatementIdx != MiniScript::STATEMENTIDX_NONE) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodEnd(miniScript));
	}
	{
		//
		class ScriptMethodForTime: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForTime(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forTime";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto now = Time::getCurrentMillis();
					auto timeWaitStarted = now;
					auto forTimeStartedIt = miniScript->getScriptState().forTimeStarted.find(statement.line);
					if (forTimeStartedIt == miniScript->getScriptState().forTimeStarted.end()) {
						miniScript->getScriptState().forTimeStarted[statement.line] = timeWaitStarted;
					} else {
						timeWaitStarted = forTimeStartedIt->second;
					}
					//
					if (Time::getCurrentMillis() > timeWaitStarted + time) {
						miniScript->getScriptState().forTimeStarted.erase(statement.line);
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						miniScript->getScriptState().endTypeStack.push(MiniScript::ScriptState::ENDTYPE_FOR);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodForTime(miniScript));
	}
	{
		//
		class ScriptMethodForCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForCondition(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forCondition";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto now = Time::getCurrentMillis();
					if (booleanValue == false) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						miniScript->getScriptState().endTypeStack.push(MiniScript::ScriptState::ENDTYPE_FOR);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodForCondition(miniScript));
	}
	{
		//
		class ScriptMethodIfCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodIfCondition(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "if";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					miniScript->getScriptState().endTypeStack.push(MiniScript::ScriptState::ENDTYPE_IF);
					//
					miniScript->getScriptState().conditionStack.push(booleanValue);
					if (booleanValue == false) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodIfCondition(miniScript));
	}
	{
		//
		class ScriptMethodElseIfCondition: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElseIfCondition(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "elseif";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
					miniScript->startErrorScript();
				} else {
					//
					auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
					if (conditionStackElement == false) {
						miniScript->getScriptState().conditionStack.pop();
						miniScript->getScriptState().conditionStack.push(booleanValue);
					}
					if (conditionStackElement == true || booleanValue == false) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodElseIfCondition(miniScript));
	}
	{
		//
		class ScriptMethodElse: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElse(MiniScript* miniScript): MiniScript::ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "else";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					Console::println("ScriptMethodElse::executeMethod(): else without if");
					miniScript->startErrorScript();
				} else {
					auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
					if (conditionStackElement == true) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodElse(miniScript));
	}
	// equality
	{
		//
		class ScriptMethodEquals: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEquals(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueAsString() != argumentValues[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_EQUALS;
			}
		};
		miniScript->registerMethod(new ScriptMethodEquals(miniScript));
	}
	{
		//
		class ScriptMethodNotEqual: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNotEqual(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "notEqual";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueAsString() == argumentValues[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_NOTEQUAL;
			}
		};
		miniScript->registerMethod(new ScriptMethodNotEqual(miniScript));
	}
	// int methods
	{
		//
		class ScriptMethodInt: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodInt(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "int", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "int";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t integerValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, integerValue, false) == true) {
					returnValue.setValue(integerValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodInt(miniScript));
	}
	// float methods
	{
		//
		class ScriptMethodFloat: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodFloat(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(floatValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodFloat(miniScript));
	}
	//
	{
		//
		class ScriptMethodGreater: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreater(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greater";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA > stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA > floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_GREATER;
			}
		};
		miniScript->registerMethod(new ScriptMethodGreater(miniScript));
	}
	{
		//
		class ScriptMethodGreaterEquals: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreaterEquals(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greaterEquals";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA >= stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA >= floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_GREATEREQUALS;
			}
		};
		miniScript->registerMethod(new ScriptMethodGreaterEquals(miniScript));
	}
	{
		//
		class ScriptMethodLesser: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesser(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesser";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA < stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA < floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_LESSER;
			}
		};
		miniScript->registerMethod(new ScriptMethodLesser(miniScript));
	}
	{
		//
		class ScriptMethodLesserEquals: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesserEquals(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesserEquals";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA <= stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA <= floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_LESSEREQUALS;
			}
		};
		miniScript->registerMethod(new ScriptMethodLesserEquals(miniScript));
	}
	// bool methods
	{
		//
		class ScriptMethodBool: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBool(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "bool";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				bool boolValue;
				if (MiniScript::getBooleanValue(argumentValues, 0, boolValue, false) == true) {
					returnValue.setValue(boolValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodBool(miniScript));
	}
	{
		//
		class ScriptMethodNot: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNot(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "not";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				bool booleanValue = false;
				if (MiniScript::getBooleanValue(argumentValues, 0, booleanValue, false) == true) {
					returnValue.setValue(!booleanValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_NOT;
			}
		};
		miniScript->registerMethod(new ScriptMethodNot(miniScript));
	}
	{
		//
		class ScriptMethodAnd: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAnd(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "and";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == false) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_AND;
			}
		};
		miniScript->registerMethod(new ScriptMethodAnd(miniScript));
	}
	{
		//
		class ScriptMethodOr: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodOr(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(false);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == true) {
							returnValue.setValue(true);
							break;
						}
					}
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_OR;
			}
		};
		miniScript->registerMethod(new ScriptMethodOr(miniScript));
	}
	// get variable
	{
		//
		class ScriptMethodGetVariable: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetVariable(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariable";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}

		};
		miniScript->registerMethod(new ScriptMethodGetVariable(miniScript));
	}
	// get variable reference
	{
		//
		class ScriptMethodGetVariableReference: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetVariableReference(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariableReference";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement, true);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		miniScript->registerMethod(new ScriptMethodGetVariableReference(miniScript));
	}
	// set variable
	{
		//
		class ScriptMethodSetVariable: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetVariable(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "setVariable";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string variable;
				if (argumentValues.size() != 2 ||
					MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->setVariable(variable, argumentValues[1], &statement);
					returnValue = argumentValues[1];
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_SET;
			}
		};
		miniScript->registerMethod(new ScriptMethodSetVariable(miniScript));
	}
	// unset variable
	{
		//
		class ScriptMethodUnsetVariable: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodUnsetVariable(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "unsetVariable";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				string variable;
				if (argumentValues.size() != 1 ||
					MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->unsetVariable(variable, &statement);
				}
			}
		};
		miniScript->registerMethod(new ScriptMethodUnsetVariable(miniScript));
	}
	{
		//
		class ScriptMethodIncrement: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodIncrement(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixIncrement";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					++value;
					argumentValues[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_INCREMENT;
			}
		};
		miniScript->registerMethod(new ScriptMethodIncrement(miniScript));
	}
	{
		//
		class ScriptMethodDecrement: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodDecrement(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixDecrement";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					--value;
					argumentValues[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_DECREMENT;
			}
		};
		miniScript->registerMethod(new ScriptMethodDecrement(miniScript));
	}
	//
	{
		//
		class ScriptMethodBitwiseNot: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseNot(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseNot";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(~value);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_BITWISENOT;
			}
		};
		miniScript->registerMethod(new ScriptMethodBitwiseNot(miniScript));
	}
	//
	{
		class ScriptMethodBitwiseAnd: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseAnd(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseAnd";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA & valueB);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEAND;
			}
		};
		miniScript->registerMethod(new ScriptMethodBitwiseAnd(miniScript));
	}
	//
	{
		class ScriptMethodBitwiseOr: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseOr(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseOr";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA | valueB);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEOR;
			}
		};
		miniScript->registerMethod(new ScriptMethodBitwiseOr(miniScript));
	}
	//
	{
		class ScriptMethodBitwiseXor: public MiniScript::ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseXor(MiniScript* miniScript):
				MiniScript::ScriptMethod(
					{
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseXor";
			}
			void executeMethod(span<MiniScript::ScriptVariable>& argumentValues, MiniScript::ScriptVariable& returnValue, const MiniScript::ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA ^ valueB);
				}
			}
			MiniScript::ScriptOperator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEXOR;
			}
		};
		miniScript->registerMethod(new ScriptMethodBitwiseXor(miniScript));
	}

}
