#include <span>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/BaseMethods.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Time.h>

using std::span;

using miniscript::miniscript::BaseMethods;

using miniscript::miniscript::MiniScript;

using _Console = miniscript::utilities::Console;
using _Time = miniscript::utilities::Time;

void BaseMethods::registerConstants(MiniScript* miniScript) {
}

void BaseMethods::registerMethods(MiniScript* miniScript) {
	// base methods
	{
		//
		class MethodReturn: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodReturn(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = true, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "return";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (miniScript->isFunctionRunning() == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
					miniScript->startErrorScript();
				} else
				if (arguments.size() == 0) {
					miniScript->stopRunning();
				} else
				if (arguments.size() == 1) {
					auto& scriptState = miniScript->getScriptState();
					scriptState.returnValue = arguments[0];
					miniScript->stopRunning();
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		miniScript->registerMethod(new MethodReturn(miniScript));
	}
	{
		//
		class MethodBreak: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBreak(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "break";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (miniScript->getScriptState().blockStack.empty() == true) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": break without forXXX");
					miniScript->startErrorScript();
				} else {
					auto& blockStack = miniScript->getScriptState().blockStack;
					MiniScript::ScriptState::Block endType;
					for (auto i = blockStack.size() - 1; i >= 0; i--) {
						if (blockStack[i].type == MiniScript::ScriptState::BLOCKTYPE_FOR) {
							endType = blockStack[i];
							blockStack.erase(blockStack.begin() + i, blockStack.end());
							break;
						}
					}
					if (endType.type == MiniScript::ScriptState::BLOCKTYPE_NONE) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": break without forXXX");
					} else
					if (endType.continueStatement != nullptr) {
						miniScript->gotoStatement(*endType.breakStatement);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no break statement");
					}
				}
			}
		};
		miniScript->registerMethod(new MethodBreak(miniScript));
	}
	{
		//
		class MethodContinue: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodContinue(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "continue";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (miniScript->getScriptState().blockStack.empty() == true) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": continue without forXXX");
					miniScript->startErrorScript();
				} else {
					auto& blockStack = miniScript->getScriptState().blockStack;
					MiniScript::ScriptState::Block* endType = nullptr;
					for (auto i = blockStack.size() - 1; i >= 0; i--) {
						if (blockStack[i].type == MiniScript::ScriptState::BLOCKTYPE_FOR) {
							endType = &blockStack[i];
							blockStack.erase(blockStack.begin() + i + 1, blockStack.end());
							break;
						}
					}
					if (endType == nullptr) {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": continue without forXXX");
					} else
					if (endType->continueStatement != nullptr) {
						miniScript->gotoStatement(*endType->continueStatement);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no continue statement");
					}
				}
			}
		};
		miniScript->registerMethod(new MethodContinue(miniScript));
	}
	{
		//
		class MethodEnd: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodEnd(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "end";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (miniScript->getScriptState().blockStack.empty() == true) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
					miniScript->startErrorScript();
				} else {
					auto& blockStack = miniScript->getScriptState().blockStack;
					auto endType = blockStack[blockStack.size() - 1];
					blockStack.erase(blockStack.begin() + blockStack.size() - 1);
					switch(endType.type) {
						case MiniScript::ScriptState::BLOCKTYPE_BLOCK:
							if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
								miniScript->stopRunning();
							}
							break;
						case MiniScript::ScriptState::BLOCKTYPE_FOR:
							// no op
							break;
						case MiniScript::ScriptState::BLOCKTYPE_IF:
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
		miniScript->registerMethod(new MethodEnd(miniScript));
	}
	{
		//
		class MethodForTime: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodForTime(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forTime";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(arguments, 0, time) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto& scriptState = miniScript->getScriptState();
					auto now = _Time::getCurrentMillis();
					auto timeWaitStarted = now;
					auto forTimeStartedIt = scriptState.forTimeStarted.find(statement.line);
					if (forTimeStartedIt == scriptState.forTimeStarted.end()) {
						miniScript->getScriptState().forTimeStarted[statement.line] = timeWaitStarted;
					} else {
						timeWaitStarted = forTimeStartedIt->second;
					}
					//
					if (_Time::getCurrentMillis() > timeWaitStarted + time) {
						scriptState.forTimeStarted.erase(statement.line);
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						scriptState.blockStack.emplace_back(
							MiniScript::ScriptState::BLOCKTYPE_FOR,
							&miniScript->getScripts()[scriptState.scriptIdx].statements[statement.gotoStatementIdx - 1],
							&miniScript->getScripts()[scriptState.scriptIdx].statements[statement.gotoStatementIdx]
						);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodForTime(miniScript));
	}
	{
		//
		class MethodForCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodForCondition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forCondition";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(arguments, 0, booleanValue, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto now = _Time::getCurrentMillis();
					if (booleanValue == false) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						auto& scriptState = miniScript->getScriptState();
						scriptState.blockStack.emplace_back(
							MiniScript::ScriptState::BLOCKTYPE_FOR,
							&miniScript->getScripts()[scriptState.scriptIdx].statements[statement.gotoStatementIdx - 1],
							&miniScript->getScripts()[scriptState.scriptIdx].statements[statement.gotoStatementIdx]
						);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodForCondition(miniScript));
	}
	{
		//
		class MethodIfCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodIfCondition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "if";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(arguments, 0, booleanValue, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto& scriptState = miniScript->getScriptState();
					scriptState.blockStack.emplace_back(MiniScript::ScriptState::BLOCKTYPE_IF, nullptr, nullptr);
					scriptState.conditionStack.push(booleanValue);
					if (booleanValue == false) {
						miniScript->setScriptStateState(MiniScript::STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		miniScript->registerMethod(new MethodIfCondition(miniScript));
	}
	{
		//
		class MethodElseIfCondition: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodElseIfCondition(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "elseif";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(arguments, 0, booleanValue, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					_Console::println("MethodElseIfCondition::executeMethod(): elseif without if");
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
		miniScript->registerMethod(new MethodElseIfCondition(miniScript));
	}
	{
		//
		class MethodElse: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodElse(MiniScript* miniScript): MiniScript::Method(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "else";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					_Console::println("MethodElse::executeMethod(): else without if");
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
		miniScript->registerMethod(new MethodElse(miniScript));
	}
	// equality
	{
		//
		class MethodEquals: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodEquals(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 2) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < arguments.size(); i++) {
						if (arguments[0].getValueAsString() != arguments[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_EQUALS;
			}
		};
		miniScript->registerMethod(new MethodEquals(miniScript));
	}
	{
		//
		class MethodNotEqual: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNotEqual(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "notEqual";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 2) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < arguments.size(); i++) {
						if (arguments[0].getValueAsString() == arguments[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_NOTEQUAL;
			}
		};
		miniScript->registerMethod(new MethodNotEqual(miniScript));
	}
	// int methods
	{
		//
		class MethodInt: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodInt(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "int", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "int";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t integerValue;
				if (MiniScript::getIntegerValue(arguments, 0, integerValue, false) == true) {
					returnValue.setValue(integerValue);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodInt(miniScript));
	}
	// float methods
	{
		//
		class MethodFloat: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodFloat(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float floatValue;
				if (MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					returnValue.setValue(floatValue);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodFloat(miniScript));
	}
	{
		//
		class MethodFloatToIntValue: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodFloatToIntValue(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float.toIntValue";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				float floatValue;
				if (MiniScript::getFloatValue(arguments, 0, floatValue, false) == true) {
					returnValue.setValue(static_cast<int64_t>(*((uint32_t*)&floatValue)));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodFloatToIntValue(miniScript));
	}
	{
		//
		class MethodFloatfromIntValue: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodFloatfromIntValue(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "int", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float.fromIntValue";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t intValue;
				if (MiniScript::getIntegerValue(arguments, 0, intValue, false) == true) {
					returnValue.setValue(*((float*)&intValue));
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		miniScript->registerMethod(new MethodFloatfromIntValue(miniScript));
	}
	//
	{
		//
		class MethodGreater: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodGreater(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greater";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(arguments, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(arguments, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA > stringValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA > floatValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_GREATER;
			}
		};
		miniScript->registerMethod(new MethodGreater(miniScript));
	}
	{
		//
		class MethodGreaterEquals: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodGreaterEquals(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greaterEquals";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(arguments, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(arguments, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA >= stringValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA >= floatValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_GREATEREQUALS;
			}
		};
		miniScript->registerMethod(new MethodGreaterEquals(miniScript));
	}
	{
		//
		class MethodLesser: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodLesser(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesser";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(arguments, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(arguments, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA < stringValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA < floatValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_LESSER;
			}
		};
		miniScript->registerMethod(new MethodLesser(miniScript));
	}
	{
		//
		class MethodLesserEquals: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodLesserEquals(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesserEquals";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (MiniScript::hasType(arguments, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(arguments, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(arguments, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA <= stringValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA <= floatValueB);
					} else {
						_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_LESSEREQUALS;
			}
		};
		miniScript->registerMethod(new MethodLesserEquals(miniScript));
	}
	// bool methods
	{
		//
		class MethodBool: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBool(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "bool";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				bool boolValue;
				if (MiniScript::getBooleanValue(arguments, 0, boolValue, false) == true) {
					returnValue.setValue(boolValue);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
		};
		miniScript->registerMethod(new MethodBool(miniScript));
	}
	{
		//
		class MethodNot: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodNot(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "not";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				bool booleanValue = false;
				if (MiniScript::getBooleanValue(arguments, 0, booleanValue, false) == true) {
					returnValue.setValue(!booleanValue);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_NOT;
			}
		};
		miniScript->registerMethod(new MethodNot(miniScript));
	}
	{
		//
		class MethodAnd: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodAnd(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "and";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 2) {
					returnValue.setValue(false);
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 0; i < arguments.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(arguments, i, booleanValue, false) == false) {
							_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == false) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_AND;
			}
		};
		miniScript->registerMethod(new MethodAnd(miniScript));
	}
	{
		//
		class MethodOr: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodOr(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				if (arguments.size() != 2) {
					returnValue.setValue(false);
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(false);
					for (auto i = 0; i < arguments.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(arguments, i, booleanValue, false) == false) {
							_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == true) {
							returnValue.setValue(true);
							break;
						}
					}
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_OR;
			}
		};
		miniScript->registerMethod(new MethodOr(miniScript));
	}
	// get variable
	{
		//
		class MethodGetVariable: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodGetVariable(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariable";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string variable;
				if (MiniScript::getStringValue(arguments, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}

		};
		miniScript->registerMethod(new MethodGetVariable(miniScript));
	}
	// get variable reference
	{
		//
		class MethodGetVariableReference: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodGetVariableReference(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariableReference";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string variable;
				if (MiniScript::getStringValue(arguments, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement, true);
				} else {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		miniScript->registerMethod(new MethodGetVariableReference(miniScript));
	}
	// set variable
	{
		//
		class MethodSetVariable: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetVariable(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "setVariable";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string variable;
				if (arguments.size() != 2 ||
					MiniScript::getStringValue(arguments, 0, variable, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->setVariable(variable, arguments[1], &statement);
					returnValue = arguments[1];
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_SET;
			}
		};
		miniScript->registerMethod(new MethodSetVariable(miniScript));
	}
	// set constant
	{
		//
		class MethodSetConstant: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodSetConstant(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_STRING, .name = "constant", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "setConstant";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				string constant;
				if (arguments.size() != 2 ||
					MiniScript::getStringValue(arguments, 0, constant, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					MiniScript::setConstant(arguments[1]);
					miniScript->setVariable(constant, arguments[1], &statement);
					returnValue = arguments[1];
				}
			}
		};
		miniScript->registerMethod(new MethodSetConstant(miniScript));
	}
	{
		//
		class MethodPostfixIncrement: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPostfixIncrement(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "postfixIncrement";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(arguments, 0, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].setValue(value + 1);
					returnValue.setValue(value);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_POSTFIX_INCREMENT;
			}
		};
		miniScript->registerMethod(new MethodPostfixIncrement(miniScript));
	}
	{
		//
		class MethodPostfixDecrement: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPostfixDecrement(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "postfixDecrement";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(arguments, 0, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					arguments[0].setValue(value - 1);
					returnValue.setValue(value);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_POSTFIX_DECREMENT;
			}
		};
		miniScript->registerMethod(new MethodPostfixDecrement(miniScript));
	}
	{
		//
		class MethodPrefixIncrement: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPrefixIncrement(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixIncrement";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(arguments, 0, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					++value;
					arguments[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_PREFIX_INCREMENT;
			}
		};
		miniScript->registerMethod(new MethodPrefixIncrement(miniScript));
	}
	{
		//
		class MethodPrefixDecrement: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodPrefixDecrement(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					MiniScript::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixDecrement";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(arguments, 0, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					--value;
					arguments[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_PREFIX_DECREMENT;
			}
		};
		miniScript->registerMethod(new MethodPrefixDecrement(miniScript));
	}
	//
	{
		//
		class MethodBitwiseNot: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBitwiseNot(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					MiniScript::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseNot";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(arguments, 0, value, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(~value);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_BITWISENOT;
			}
		};
		miniScript->registerMethod(new MethodBitwiseNot(miniScript));
	}
	//
	{
		class MethodBitwiseAnd: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBitwiseAnd(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseAnd";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(arguments, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, valueB, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA & valueB);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEAND;
			}
		};
		miniScript->registerMethod(new MethodBitwiseAnd(miniScript));
	}
	//
	{
		class MethodBitwiseOr: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBitwiseOr(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseOr";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(arguments, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, valueB, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA | valueB);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEOR;
			}
		};
		miniScript->registerMethod(new MethodBitwiseOr(miniScript));
	}
	//
	{
		class MethodBitwiseXor: public MiniScript::Method {
		private:
			MiniScript* miniScript { nullptr };
		public:
			MethodBitwiseXor(MiniScript* miniScript):
				MiniScript::Method(
					{
						{ .type = MiniScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MiniScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					MiniScript::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseXor";
			}
			void executeMethod(span<MiniScript::Variable>& arguments, MiniScript::Variable& returnValue, const MiniScript::Statement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(arguments, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(arguments, 1, valueB, false) == false) {
					_Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA ^ valueB);
				}
			}
			MiniScript::Operator getOperator() const override {
				return MiniScript::OPERATOR_BITWISEXOR;
			}
		};
		miniScript->registerMethod(new MethodBitwiseXor(miniScript));
	}

}
