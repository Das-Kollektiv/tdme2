#include <span>
#include <unordered_map>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/BaseMethods.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/os/threading/Thread.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Hex.h>
#include <minitscript/utilities/Time.h>

using std::span;
using std::unordered_map;
using std::vector;

using minitscript::minitscript::BaseMethods;

using minitscript::minitscript::MinitScript;

using _Thread = minitscript::os::threading::Thread;
using _Console = minitscript::utilities::Console;
using _Hex = minitscript::utilities::Hex;
using _Time = minitscript::utilities::Time;

void BaseMethods::registerConstants(MinitScript* minitScript) {
	minitScript->setConstant("$___NULL", MinitScript::Variable());
	minitScript->setConstant("$___ARRAY", MinitScript::Variable(vector<MinitScript::Variable*>()));
	minitScript->setConstant("$___MAP", MinitScript::Variable(unordered_map<string, MinitScript::Variable*>()));
}

void BaseMethods::registerMethods(MinitScript* minitScript) {
	// script internal base methods
	{
		//
		class MethodInternalScriptEvaluate: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodInternalScriptEvaluate(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "internal.script.evaluate";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() != 1) {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				} else
				if (arguments.size() == 1) {
					returnValue.setValue(arguments[0]);
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodInternalScriptEvaluate(minitScript));
	}
	{
		//
		class MethodInternalEvaluateMemberAccess: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodInternalEvaluateMemberAccess(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "this", .optional = false, .reference = false, .nullable = true },
						{ .type = MinitScript::TYPE_STRING, .name = "member", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED,
					true
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "internal.script.evaluateMemberAccess";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				// Current layout:
				//	0: variable name of object, 1: variable content of object
				//	2: object method to call
				//	3: variable name of argument 0; 4: variable content of argument 0
				//	5: variable name of argument 1; 6: variable content of argument 1
				//	..
				//
				string variable;
				string member;
				//
				if (arguments.size() < 3 ||
					minitScript->getStringValue(arguments, 2, member, false) == false) {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				} else {
					// complain?
					auto complain = true;
					// do we have a this variable name?
					string thisVariableName;
					{
						if (arguments[0].getType() != MinitScript::TYPE_NULL && arguments[0].getStringValue(thisVariableName) == true) {
							// yep, looks like that, we always use a reference here
							#if defined(__MINITSCRIPT_TRANSPILATION__)
								arguments[1] = MinitScript::Variable::createReferenceVariable(&EVALUATEMEMBERACCESS_ARGUMENT0);
							#else
								arguments[1] = minitScript->getVariable(thisVariableName, &subStatement, true);
							#endif
						}
					}
					// check if map, if so fetch function assignment of member property
					auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
					if (arguments[1].getType() == MinitScript::TYPE_MAP) {
						string function;
						auto mapValue = arguments[1].getMapEntry(member);
						if (mapValue.getType() == MinitScript::TYPE_FUNCTION_ASSIGNMENT && mapValue.getFunctionValue(function, functionScriptIdx) == true) {
							// check if private and private scope
							if (mapValue.isPrivate() == true && arguments[1].isPrivateScope() == false) {
								complain = false;
								functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
								_Console::printLine(minitScript->getSubStatementInformation(subStatement) + ": Private variable: " + thisVariableName + ": access not allowed from outside of object");
							} else
							// no function idx, so get it
							if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) functionScriptIdx = minitScript->getFunctionScriptIdx(function);
						}
					}
					//
					const auto& className = arguments[1].getTypeAsString();
					//
					if (className.empty() == false || functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
						//
						MinitScript::Method* method { nullptr };
						if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							#if defined(__MINITSCRIPT_TRANSPILATION__)
								method = evaluateMemberAccessArrays[static_cast<int>(arguments[1].getType()) - static_cast<int>(MinitScript::TYPE_STRING)][EVALUATEMEMBERACCESS_MEMBER];
							#else
								method = minitScript->getMethod(className + "::" + member);
							#endif
						}
						if (method != nullptr || functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
							// create method call arguments
							vector<MinitScript::Variable> callArguments(1 + (arguments.size() - 3) / 2);
							//	this
							callArguments[0] = std::move(arguments[1]);
							//	additional method call arguments
							{
								auto callArgumentIdx = 1;
								for (auto argumentIdx = 3; argumentIdx < arguments.size(); argumentIdx+=2) {
									// do we have a this variable name?
									string argumentVariableName;
									if (arguments[argumentIdx].getType() != MinitScript::TYPE_NULL && arguments[argumentIdx].getStringValue(argumentVariableName) == true) {
										#if defined(__MINITSCRIPT_TRANSPILATION__)
											if (method != nullptr) {
												arguments[argumentIdx + 1] =
													callArgumentIdx >= method->getArgumentTypes().size() || method->getArgumentTypes()[callArgumentIdx].reference == false?
														MinitScript::Variable::createNonReferenceVariable(&EVALUATEMEMBERACCESS_ARGUMENTS[callArgumentIdx - 1]):
														EVALUATEMEMBERACCESS_ARGUMENTS[callArgumentIdx - 1];
											} else
											if (functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
												arguments[argumentIdx + 1] =
													callArgumentIdx >= minitScript->getScripts()[functionScriptIdx].arguments.size() || minitScript->getScripts()[functionScriptIdx].arguments[callArgumentIdx].reference == false?
														MinitScript::Variable::createNonReferenceVariable(&EVALUATEMEMBERACCESS_ARGUMENTS[callArgumentIdx - 1]):
														EVALUATEMEMBERACCESS_ARGUMENTS[callArgumentIdx - 1];
											}
										#else
											// yep, looks like that
											if (method != nullptr) {
												arguments[argumentIdx + 1] = minitScript->getVariable(argumentVariableName, &subStatement, callArgumentIdx >= method->getArgumentTypes().size()?false:method->getArgumentTypes()[callArgumentIdx].reference);
											} else
											if (functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
												arguments[argumentIdx + 1] = minitScript->getVariable(argumentVariableName, &subStatement, callArgumentIdx >= minitScript->getScripts()[functionScriptIdx].arguments.size()?false:minitScript->getScripts()[functionScriptIdx].arguments[callArgumentIdx].reference);
											}
										#endif
									}
									//
									callArguments[callArgumentIdx] = std::move(arguments[argumentIdx + 1]);
									callArgumentIdx++;
								}
							}
							//
							span callArgumentsSpan(callArguments);
							//
							if (method != nullptr) {
								method->executeMethod(callArgumentsSpan, returnValue, subStatement);
							} else
							if (functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
								minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
							}
							// write back arguments from call arguments
							//	this
							arguments[1] = std::move(callArgumentsSpan[0]);
							//	additional arguments
							{
								auto callArgumentIdx = 1;
								for (auto argumentIdx = 3; argumentIdx < arguments.size(); argumentIdx+=2) {
									arguments[argumentIdx] = std::move(callArgumentsSpan[callArgumentIdx]);
									callArgumentIdx++;
								}
							}
						} else {
							if (complain == true) {
								MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Class/object member not found: " + member + "()");
							}
						}
					} else {
						if (complain == true) {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodInternalEvaluateMemberAccess(minitScript));
	}
	{
		//
		class MethodInternalScriptCallStacklet: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodInternalScriptCallStacklet(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STACKLET_ASSIGNMENT, .name = "stacklet", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "internal.script.callStacklet";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string stacklet;
				auto stackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
				if (arguments.size() == 1 &&
					minitScript->getStackletValue(arguments, 0, stacklet, stackletScriptIdx) == true) {
					if (stackletScriptIdx == MinitScript::SCRIPTIDX_NONE) {
						stackletScriptIdx = minitScript->getFunctionScriptIdx(stacklet);
					}
					if (stackletScriptIdx == MinitScript::SCRIPTIDX_NONE || minitScript->getScripts()[stackletScriptIdx].type != MinitScript::Script::TYPE_STACKLET) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Stacklet not found: " + stacklet);
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
		minitScript->registerMethod(new MethodInternalScriptCallStacklet(minitScript));
	}
	// base methods
	{
		//
		class MethodReturn: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodReturn(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_NULL
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "return";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0 || arguments.size() == 1) {
					if (minitScript->isFunctionRunning() == false) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "No function is being executed, return($value) has no effect");
					} else
					if (arguments.size() == 1) minitScript->getScriptState().returnValue.setValue(arguments[0]);
					//
					auto& scriptState = minitScript->getScriptState();
					auto& blockStack = scriptState.blockStack;
					// jump to end of current script
					const auto& scripts = minitScript->getScripts();
					const auto& statements = scripts[scriptState.scriptIdx].getStatements();
					//
					blockStack.erase(blockStack.begin() + 1, blockStack.end());
					//
					minitScript->gotoStatement(statements[statements.size() - 1]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodReturn(minitScript));
	}
	{
		//
		class MethodBreak: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBreak(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "levels", .optional = true, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "break";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t levels = 1;
				if ((arguments.size() == 0 || arguments.size() == 1) &&
					MinitScript::getIntegerValue(arguments, 0, levels, true) == true) {
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "break without forCondition/forTime");
					} else {
						int64_t level = 0;
						auto& blockStack = minitScript->getScriptState().blockStack;
						MinitScript::ScriptState::Block* endType = nullptr;
						vector<int> blockStacksToRemove;
						for (int i = blockStack.size() - 1; i >= 0; i--) {
							if (blockStack[i].type == MinitScript::ScriptState::Block::TYPE_FOR) {
								endType = &blockStack[i];
								level++;
								blockStacksToRemove.push_back(i);
								if (level == levels) break;
							} else
							if (level < levels) {
								blockStacksToRemove.push_back(i);
							}
						}
						if (endType == nullptr) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "break without forCondition, forTime");
						} else
						if (levels != level) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "break(" + to_string(levels) + ") + without " + to_string(levels) + " levels of forCondition, forTime");
						} else
						if (endType->breakStatement != nullptr) {
							auto breakStatement = endType->breakStatement;
							for (auto i: blockStacksToRemove) blockStack.erase(blockStack.begin() + i);
							minitScript->gotoStatement(*breakStatement);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "No break statement");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodBreak(minitScript));
	}
	{
		//
		class MethodContinue: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodContinue(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "levels", .optional = true, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "continue";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t levels = 1;
				if ((arguments.size() == 0 || arguments.size() == 1) &&
					MinitScript::getIntegerValue(arguments, 0, levels, true) == true) {
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "continue without forCondition, forTime");
					} else {
						int64_t level = 0;
						auto& blockStack = minitScript->getScriptState().blockStack;
						MinitScript::ScriptState::Block* endType = nullptr;
						vector<int> blockStacksToRemove;
						for (int i = blockStack.size() - 1; i >= 0; i--) {
							if (blockStack[i].type == MinitScript::ScriptState::Block::TYPE_FOR) {
								endType = &blockStack[i];
								level++;
								if (level == levels) {
									break;
								} else {
									blockStacksToRemove.push_back(i);
								}
							} else
							if (level < levels) {
								blockStacksToRemove.push_back(i);
							}
						}
						if (endType == nullptr) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "continue without forCondition, forTime");
						} else
						if (levels != level) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "continue(" + to_string(levels) + ") + without " + to_string(levels) + " levels of forCondition, forTime");
						} else
						if (endType->continueStatement != nullptr) {
							auto continueStatement = endType->continueStatement;
							for (auto i: blockStacksToRemove) blockStack.erase(blockStack.begin() + i);
							minitScript->gotoStatement(*continueStatement);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "No continue statement");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodContinue(minitScript));
	}
	{
		//
		class MethodEnd: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodEnd(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "end";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "end without if/elseif/else/switch/case/default/forCondition/forTime/catch");
					} else {
						auto& blockStack = minitScript->getScriptState().blockStack;
						auto& block = blockStack.back();
						if (block.type == MinitScript::ScriptState::Block::TYPE_FUNCTION || block.type == MinitScript::ScriptState::Block::TYPE_STACKLET) {
							minitScript->stopRunning();
						} else
						if (block.type ==  MinitScript::ScriptState::Block::TYPE_FOR && block.parameter.getType() == MinitScript::TYPE_INTEGER) {
							vector<MinitScript::Variable> arguments {};
							span argumentsSpan(arguments);
							MinitScript::Variable returnValue;
							int64_t iterationStackletScriptIdx;
							if (block.parameter.getIntegerValue(iterationStackletScriptIdx) == true &&
								iterationStackletScriptIdx != MinitScript::SCRIPTIDX_NONE) {
								minitScript->callStacklet(iterationStackletScriptIdx, argumentsSpan, returnValue);
							} else {
								MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "end with for: iteration stacklet: invalid stacklet");
							}
						}
						blockStack.erase(blockStack.begin() + blockStack.size() - 1);
						//
						if (
							#if defined(MINITSCRIPT_EVENTS)
								minitScript->hasEmitted() == false &&
							#endif
							subStatement.statement->gotoStatementIdx != MinitScript::STATEMENTIDX_NONE) {
							minitScript->gotoStatementGoto(*subStatement.statement);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodEnd(minitScript));
	}
	{
		//
		class MethodForTime: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodForTime(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "forTime";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t time;
				if (arguments.size() == 1 &&
					minitScript->getIntegerValue(arguments, 0, time) == true) {
					auto& scriptState = minitScript->getScriptState();
					auto now = _Time::getCurrentMillis();
					auto timeWaitStarted = now;
					auto forTimeStartedIt = scriptState.forTimeStarted.find(subStatement.statement->line);
					if (forTimeStartedIt == scriptState.forTimeStarted.end()) {
						minitScript->getScriptState().forTimeStarted[subStatement.statement->line] = timeWaitStarted;
					} else {
						timeWaitStarted = forTimeStartedIt->second;
					}
					//
					if (_Time::getCurrentMillis() > timeWaitStarted + time) {
						scriptState.forTimeStarted.erase(subStatement.statement->line);
						minitScript->gotoStatementGoto(*subStatement.statement);
					} else {
						scriptState.blockStack.emplace_back(
							MinitScript::ScriptState::Block::TYPE_FORTIME,
							false,
							&minitScript->rootScript->getScripts()[scriptState.scriptIdx].getStatements()[subStatement.statement->gotoStatementIdx - 1],
							&minitScript->rootScript->getScripts()[scriptState.scriptIdx].getStatements()[subStatement.statement->gotoStatementIdx],
							nullptr,
							MinitScript::Variable()
						);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodForTime(minitScript));
	}
	{
		//
		class MethodForCondition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodForCondition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_STACKLET_ASSIGNMENT, .name = "iterationStacklet", .optional = true, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "forCondition";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValue;
				string iterationStacklet;
				auto iterationStackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					minitScript->getBooleanValue(arguments, 0, booleanValue) == true &&
					minitScript->getStackletValue(arguments, 1, iterationStacklet, iterationStackletScriptIdx, true) == true) {
					if (booleanValue == false) {
						minitScript->gotoStatementGoto(*subStatement.statement);
					} else {
						if (iterationStacklet.empty() == false && iterationStackletScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							iterationStackletScriptIdx = minitScript->getFunctionScriptIdx(iterationStacklet);
						}
						// check if valid
						if (iterationStacklet.empty() == false && iterationStackletScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Stacklet not found: " + iterationStacklet);
						} else {
							auto& scriptState = minitScript->getScriptState();
							scriptState.blockStack.emplace_back(
								MinitScript::ScriptState::Block::TYPE_FOR,
								false,
								&minitScript->rootScript->getScripts()[scriptState.scriptIdx].getStatements()[subStatement.statement->gotoStatementIdx - 1],
								&minitScript->rootScript->getScripts()[scriptState.scriptIdx].getStatements()[subStatement.statement->gotoStatementIdx],
								nullptr,
								iterationStacklet.empty() == true?MinitScript::Variable():MinitScript::Variable(static_cast<int64_t>(iterationStackletScriptIdx))
							);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodForCondition(minitScript));
	}
	{
		//
		class MethodIfCondition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodIfCondition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "if";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValue;
				if (arguments.size() == 1 &&
					minitScript->getBooleanValue(arguments, 0, booleanValue) == true) {
					minitScript->getScriptState().blockStack.emplace_back(
						MinitScript::ScriptState::Block::TYPE_IF,
						booleanValue,
						nullptr,
						nullptr,
						nullptr,
						MinitScript::Variable()
					);
					if (booleanValue == false) {
						minitScript->gotoStatementGoto(*subStatement.statement);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodIfCondition(minitScript));
	}
	{
		//
		class MethodElseIfCondition: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodElseIfCondition(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "elseif";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValue;
				if (arguments.size() == 1 &&
					minitScript->getBooleanValue(arguments, 0, booleanValue) == true) {
					auto& scriptState = minitScript->getScriptState();
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "elseif without if");
					} else {
						auto& block = scriptState.blockStack.back();
						if (block.type != MinitScript::ScriptState::Block::TYPE_IF) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "elseif without if");
						} else
						if (block.match == true || booleanValue == false) {
							minitScript->gotoStatementGoto(*subStatement.statement);
						} else {
							block.match = booleanValue;
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodElseIfCondition(minitScript));
	}
	{
		//
		class MethodElse: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodElse(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "else";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					auto& scriptState = minitScript->getScriptState();
					auto& block = scriptState.blockStack.back();
					if (block.type != MinitScript::ScriptState::Block::TYPE_IF) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "else without if");
					} else
					if (block.match == true) {
						minitScript->gotoStatementGoto(*subStatement.statement);
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodElse(minitScript));
	}
	// switch
	{
		//
		class MethodSwitch: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSwitch(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "switch";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					auto& scriptState = minitScript->getScriptState();
					scriptState.blockStack.emplace_back(
						MinitScript::ScriptState::Block::TYPE_SWITCH,
						false,
						nullptr,
						nullptr,
						nullptr,
						arguments[0]
					);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSwitch(minitScript));
	}
	{
		//
		class MethodCase: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCase(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "case";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					auto& scriptState = minitScript->getScriptState();
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "case without switch");
					} else {
						auto& block = scriptState.blockStack.back();
						if (block.type != MinitScript::ScriptState::Block::TYPE_SWITCH) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "case without switch");
						} else {
							auto match = arguments[0].getValueAsString() == block.parameter.getValueAsString();
							if (block.match == true || match == false) {
								minitScript->gotoStatementGoto(*subStatement.statement);
							} else {
								block.match = match;
								scriptState.blockStack.emplace_back(
									MinitScript::ScriptState::Block::TYPE_CASE,
									false,
									nullptr,
									nullptr,
									nullptr,
									MinitScript::Variable()
								);
							}
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodCase(minitScript));
	}
	{
		//
		class MethodDefault: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodDefault(MinitScript* minitScript): MinitScript::Method(), minitScript(minitScript) {}
			const string getMethodName() override {
				return "default";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 0) {
					auto& scriptState = minitScript->getScriptState();
					if (minitScript->getScriptState().blockStack.empty() == true) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "default without switch");
					} else {
						auto& block = scriptState.blockStack.back();
						if (block.type != MinitScript::ScriptState::Block::TYPE_SWITCH) {
							MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "default without switch");
						} else
						if (block.match == true) {
							minitScript->gotoStatementGoto(*subStatement.statement);
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodDefault(minitScript));
	}
	// try, catch and throw
	{
		//
		class MethodTry: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodTry(MinitScript* minitScript):
				MinitScript::Method(),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "try";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto& scriptState = minitScript->getScriptState();
				scriptState.blockStack.emplace_back(
					MinitScript::ScriptState::Block::TYPE_TRY,
					false,
					nullptr,
					nullptr,
					&minitScript->rootScript->getScripts()[scriptState.scriptIdx].getStatements()[subStatement.statement->gotoStatementIdx],
					MinitScript::Variable()
				);
			}
		};
		minitScript->registerMethod(new MethodTry(minitScript));
	}
	{
		//
		class MethodCatch: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodCatch(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "exception", .optional = false, .reference = true, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "catch";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto& blockStack = minitScript->getScriptState().blockStack;
				auto& block = blockStack.back();
				//
				auto hadException = false;
				// did we had an exception?
				if (block.type == MinitScript::ScriptState::Block::TYPE_CATCH) {
					// set exception in arguments
					if (arguments.empty() == false) arguments[0].setValue(block.parameter);
					// delete our TYPE_CATCH block
					blockStack.erase(blockStack.begin() + blockStack.size() - 1);
					block = blockStack.back();
					// we had an exception
					hadException = true;
				}
				//
				if (block.type == MinitScript::ScriptState::Block::TYPE_TRY) {
					// delete our TYPE_TRY block
					blockStack.erase(blockStack.begin() + blockStack.size() - 1);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "catch without try");
				}
				// did we had an exception?
				if (hadException == true) {
					// we had a exception, hence are in catch block, we need this for "end"
					minitScript->getScriptState().blockStack.emplace_back(
						MinitScript::ScriptState::Block::TYPE_CATCH,
						false,
						nullptr,
						nullptr,
						nullptr,
						MinitScript::Variable()
					);
				} else {
					// no exception, so jump after it
					minitScript->gotoStatementGoto(*subStatement.statement);
				}
			}
		};
		minitScript->registerMethod(new MethodCatch(minitScript));
	}
	{
		//
		class MethodThrow: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodThrow(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "exception", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "throw";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				auto& scriptState = minitScript->getScriptState();
				auto& blockStack = scriptState.blockStack;
				auto& block = blockStack.back();
				//
				auto tryBlockIdx = -1;
				for (int i = blockStack.size() - 1; i >= 0; i--) {
					if (blockStack[i].type == MinitScript::ScriptState::Block::TYPE_TRY) {
						tryBlockIdx = i;
						break;
					}
				}
				if (tryBlockIdx == -1) {
					// set exception and jump to end of script
					minitScript->setException(
						scriptState.scriptIdx,
						subStatement,
						arguments.empty() == false?arguments[0]:MinitScript::Variable()
					);
					// jump to end of current script
					const auto& scripts = minitScript->rootScript->getScripts();
					const auto& statements = scripts[scriptState.scriptIdx].getStatements();
					//
					blockStack.erase(blockStack.begin() + 1, blockStack.end());
					// unhandled global exception
					if (minitScript->getScriptStateStackSize() == 1) {
						MINITSCRIPT_METHODUSAGE_COMPLAINM(getMethodName(), "Unhandled exception!");
					} else {
						// somewhere else in a function
						minitScript->gotoStatement(statements[statements.size() - 1]);
					}
				} else {
					auto catchStatement = blockStack[tryBlockIdx].catchStatement;
					//
					blockStack.erase(blockStack.begin() + tryBlockIdx + 1, blockStack.end());
					//
					blockStack.emplace_back(
						MinitScript::ScriptState::Block::TYPE_CATCH,
						false,
						nullptr,
						nullptr,
						nullptr,
						arguments.empty() == false?arguments[0]:MinitScript::Variable()
					);
					//
					minitScript->gotoStatement(*catchStatement);
				}
			}
		};
		minitScript->registerMethod(new MethodThrow(minitScript));
	}
	// equality
	{
		//
		class MethodEquals: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodEquals(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					returnValue.setValue(true);
					for (auto i = 1; i < 2; i++) {
						if (arguments[0].getValueAsString() != arguments[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_EQUALS;
			}
		};
		minitScript->registerMethod(new MethodEquals(minitScript));
	}
	{
		//
		class MethodNotEqual: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNotEqual(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "notEqual";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					returnValue.setValue(true);
					for (auto i = 1; i < 2; i++) {
						if (arguments[0].getValueAsString() == arguments[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_NOTEQUAL;
			}
		};
		minitScript->registerMethod(new MethodNotEqual(minitScript));
	}
	// int methods
	{
		//
		class MethodInt: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodInt(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "integer", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "integer";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t integerValue;
				if (arguments.size() == 1 &&
					MinitScript::getIntegerValue(arguments, 0, integerValue) == true) {
					returnValue.setValue(integerValue);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodInt(minitScript));
	}
	// float methods
	//	TODO: move me into FloatMethods
	{
		//
		class MethodFloat: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodFloat(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "float";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float floatValue;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, floatValue) == true) {
					returnValue.setValue(floatValue);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodFloat(minitScript));
	}
	{
		//
		class MethodFloatToIntValue: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodFloatToIntValue(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "float.toIntegerValue";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				float floatValue;
				if (arguments.size() == 1 &&
					MinitScript::getFloatValue(arguments, 0, floatValue) == true) {
					returnValue.setValue(static_cast<int64_t>(*((uint32_t*)&floatValue)));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodFloatToIntValue(minitScript));
	}
	{
		//
		class MethodFloatfromIntValue: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodFloatfromIntValue(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "integer", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_FLOAT
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "float.fromIntegerValue";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t intValue;
				if (arguments.size() == 1 &&
					MinitScript::getIntegerValue(arguments, 0, intValue) == true) {
					returnValue.setValue(*((float*)&intValue));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodFloatfromIntValue(minitScript));
	}
	//
	{
		//
		class MethodGreater: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGreater(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "greater";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_STRING) == true) {
						string stringValueA;
						string stringValueB;
						if (MinitScript::getStringValue(arguments, 0, stringValueA, false) == true &&
							MinitScript::getStringValue(arguments, 1, stringValueB, false) == true) {
							returnValue.setValue(stringValueA > stringValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					} else {
						float floatValueA;
						float floatValueB;
						if (MinitScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
							MinitScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA > floatValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_GREATER;
			}
		};
		minitScript->registerMethod(new MethodGreater(minitScript));
	}
	{
		//
		class MethodGreaterEquals: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGreaterEquals(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "greaterEquals";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_STRING) == true) {
						string stringValueA;
						string stringValueB;
						if (MinitScript::getStringValue(arguments, 0, stringValueA, false) == true &&
							MinitScript::getStringValue(arguments, 1, stringValueB, false) == true) {
							returnValue.setValue(stringValueA >= stringValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					} else {
						float floatValueA;
						float floatValueB;
						if (MinitScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
							MinitScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA >= floatValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_GREATEREQUALS;
			}
		};
		minitScript->registerMethod(new MethodGreaterEquals(minitScript));
	}
	{
		//
		class MethodLesser: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodLesser(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "lesser";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_STRING) == true) {
						string stringValueA;
						string stringValueB;
						if (MinitScript::getStringValue(arguments, 0, stringValueA, false) == true &&
							MinitScript::getStringValue(arguments, 1, stringValueB, false) == true) {
							returnValue.setValue(stringValueA < stringValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					} else {
						float floatValueA;
						float floatValueB;
						if (MinitScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
							MinitScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_LESSER;
			}
		};
		minitScript->registerMethod(new MethodLesser(minitScript));
	}
	{
		//
		class MethodLesserEquals: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodLesserEquals(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "lesserEquals";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 2 || arguments.size() == 3) {
					if (MinitScript::hasTypeForOperatorArguments(arguments, MinitScript::TYPE_STRING) == true) {
						string stringValueA;
						string stringValueB;
						if (MinitScript::getStringValue(arguments, 0, stringValueA, false) == true &&
							MinitScript::getStringValue(arguments, 1, stringValueB, false) == true) {
							returnValue.setValue(stringValueA <= stringValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					} else {
						float floatValueA;
						float floatValueB;
						if (MinitScript::getFloatValue(arguments, 0, floatValueA, false) == true &&
							MinitScript::getFloatValue(arguments, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA <= floatValueB);
						} else {
							MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Can not compare '" + arguments[0].getValueAsString() + "' with '" + arguments[1].getValueAsString() + "'");
						}
					}
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_LESSEREQUALS;
			}
		};
		minitScript->registerMethod(new MethodLesserEquals(minitScript));
	}
	// bool methods
	{
		//
		class MethodBool: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBool(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "boolean", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "boolean";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValue;
				if (arguments.size() == 1 &&
					MinitScript::getBooleanValue(arguments, 0, booleanValue) == true) {
					returnValue.setValue(booleanValue);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodBool(minitScript));
	}
	{
		//
		class MethodNot: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodNot(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "boolean", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN), minitScript(minitScript) {}
			const string getMethodName() override {
				return "not";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValue = false;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getBooleanValue(arguments, 0, booleanValue) == true) {
					returnValue.setValue(!booleanValue);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a boolean value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_NOT;
			}
		};
		minitScript->registerMethod(new MethodNot(minitScript));
	}
	{
		//
		class MethodAnd: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodAnd(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "and";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValueA;
				bool booleanValueB;
				auto isBooleanValueA = MinitScript::getBooleanValue(arguments, 0, booleanValueA);
				auto isBooleanValueB = MinitScript::getBooleanValue(arguments, 1, booleanValueB);
				//
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					isBooleanValueA == true &&
					isBooleanValueB == true) {
					returnValue.setValue(booleanValueA && booleanValueB);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), string(isBooleanValueA == false?"Left argument '" + arguments[0].getValueAsString() + "' is not a boolean value":"") + string(isBooleanValueB == false?string(isBooleanValueA == false?" and right argument":"Right argument") + " '" + arguments[1].getValueAsString() + "' is not a boolean value":""));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_AND;
			}
		};
		minitScript->registerMethod(new MethodAnd(minitScript));
	}
	{
		//
		class MethodOr: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodOr(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				bool booleanValueA;
				bool booleanValueB;
				auto isBooleanValueA = MinitScript::getBooleanValue(arguments, 0, booleanValueA);
				auto isBooleanValueB = MinitScript::getBooleanValue(arguments, 1, booleanValueB);
				//
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					isBooleanValueA == true &&
					isBooleanValueB == true) {
					returnValue.setValue(booleanValueA || booleanValueB);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), string(isBooleanValueA == false?"Left argument '" + arguments[0].getValueAsString() + "' is not a boolean value":"") + string(isBooleanValueB == false?string(isBooleanValueA == false?" and right argument":"Right argument") + " '" + arguments[1].getValueAsString() + "' is not a boolean value":""));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_OR;
			}
		};
		minitScript->registerMethod(new MethodOr(minitScript));
	}
	// get type
	{
		//
		class MethodGetType: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGetType(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "getType";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					returnValue.setValue(arguments[0].getTypeAsString());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodGetType(minitScript));
	}
	// is constant
	{
		//
		class MethodIsConstant: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodIsConstant(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "isConstant";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					returnValue.setValue(arguments[0].isConstant());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodIsConstant(minitScript));
	}
	// is reference
	{
		//
		class MethodIsReference: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodIsReference(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "isReference";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.size() == 1) {
					returnValue.setValue(arguments[0].isReference());
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodIsReference(minitScript));
	}
	// has variable
	{
		//
		class MethodHasVariable: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHasVariable(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_BOOLEAN
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "hasVariable";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					returnValue.setValue(minitScript->hasVariable(variable, &subStatement));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHasVariable(minitScript));
	}
	// get variable
	{
		//
		class MethodGetVariable: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGetVariable(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "getVariable";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					returnValue = minitScript->getVariable(variable, &subStatement);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodGetVariable(minitScript));
	}
	// get variable for method arguments
	{
		//
		class MethodGetMethodArgumentVariable: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGetMethodArgumentVariable(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "getMethodArgumentVariable";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					returnValue = minitScript->getMethodArgumentVariable(variable, &subStatement);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodGetMethodArgumentVariable(minitScript));
	}
	// get variable reference
	{
		//
		class MethodGetVariableReference: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodGetVariableReference(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "getVariableReference";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					returnValue = minitScript->getVariable(variable, &subStatement, true);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodGetVariableReference(minitScript));
	}
	// set variable
	{
		//
		class MethodSetVariable: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetVariable(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "setVariable";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					minitScript->setVariable(variable, arguments[1].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[1]):arguments[1], &subStatement);
					returnValue.setValue(arguments[1]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_SET;
			}
		};
		minitScript->registerMethod(new MethodSetVariable(minitScript));
	}
	// set variable reference
	{
		//
		class MethodSetVariableReference: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetVariableReference(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = true, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "setVariableReference";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					minitScript->setVariable(variable, arguments[1], &subStatement, true);
					returnValue.setValue(arguments[1]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodSetVariableReference(minitScript));
	}
	// Unset variable reference
	{
		//
		class MethodUnsetVariableReference: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodUnsetVariableReference(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "unsetVariableReference";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string variable;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, variable) == true) {
					minitScript->unsetVariable(variable, &subStatement);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		minitScript->registerMethod(new MethodUnsetVariableReference(minitScript));
	}
	// set constant
	{
		//
		class MethodSetConstant: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSetConstant(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "constant", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {
				//
			}
			const string getMethodName() override {
				return "setConstant";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string constant;
				if (arguments.size() == 2 &&
					MinitScript::getStringValue(arguments, 0, constant) == true) {
					MinitScript::setConstant(arguments[1]);
					minitScript->setVariable(constant, arguments[1], &subStatement);
					returnValue.setValue(arguments[1]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodSetConstant(minitScript));
	}
	{
		//
		class MethodPostfixIncrement: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodPostfixIncrement(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "postfixIncrement";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					arguments[0].setValue(value + 1);
					returnValue.setValue(value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a integer value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_POSTFIX_INCREMENT;
			}
		};
		minitScript->registerMethod(new MethodPostfixIncrement(minitScript));
	}
	{
		//
		class MethodPostfixDecrement: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodPostfixDecrement(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "postfixDecrement";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					arguments[0].setValue(value - 1);
					returnValue.setValue(value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a integer value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_POSTFIX_DECREMENT;
			}
		};
		minitScript->registerMethod(new MethodPostfixDecrement(minitScript));
	}
	{
		//
		class MethodPrefixIncrement: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodPrefixIncrement(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "prefixIncrement";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					++value;
					arguments[0].setValue(value);
					returnValue.setValue(value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a integer value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_PREFIX_INCREMENT;
			}
		};
		minitScript->registerMethod(new MethodPrefixIncrement(minitScript));
	}
	{
		//
		class MethodPrefixDecrement: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodPrefixDecrement(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "prefixDecrement";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					--value;
					arguments[0].setValue(value);
					returnValue.setValue(value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a integer value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_PREFIX_DECREMENT;
			}
		};
		minitScript->registerMethod(new MethodPrefixDecrement(minitScript));
	}
	//
	{
		//
		class MethodBitwiseNot: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBitwiseNot(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "bitwiseNot";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if ((arguments.size() == 1 || arguments.size() == 2) &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					returnValue.setValue(~value);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 1, getMethodName()), "'" + arguments[0].getValueAsString() + "' is not a integer value");
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_BITWISENOT;
			}
		};
		minitScript->registerMethod(new MethodBitwiseNot(minitScript));
	}
	//
	{
		class MethodBitwiseAnd: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBitwiseAnd(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "bitwiseAnd";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t valueA;
				int64_t valueB;
				auto isValueAInteger = MinitScript::getIntegerValue(arguments, 0, valueA);
				auto isValueBInteger = MinitScript::getIntegerValue(arguments, 1, valueB);
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					isValueAInteger == true &&
					isValueBInteger == true) {
					//
					returnValue.setValue(valueA & valueB);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), string(isValueAInteger == false?"Left argument '" + arguments[0].getValueAsString() + "' is not a integer value":"") + string(isValueBInteger == false?string(isValueAInteger == false?" and right argument":"Right argument") + " '" + arguments[1].getValueAsString() + "' is not a integer value":""));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_BITWISEAND;
			}
		};
		minitScript->registerMethod(new MethodBitwiseAnd(minitScript));
	}
	//
	{
		class MethodBitwiseOr: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBitwiseOr(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "bitwiseOr";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t valueA;
				int64_t valueB;
				auto isValueAInteger = MinitScript::getIntegerValue(arguments, 0, valueA);
				auto isValueBInteger = MinitScript::getIntegerValue(arguments, 1, valueB);
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					isValueAInteger == true &&
					isValueBInteger == true) {
					//
					returnValue.setValue(valueA | valueB);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), string(isValueAInteger == false?"Left argument '" + arguments[0].getValueAsString() + "' is not a integer value":"") + string(isValueBInteger == false?string(isValueAInteger == false?" and right argument":"Right argument") + " '" + arguments[1].getValueAsString() + "' is not a integer value":""));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_BITWISEOR;
			}
		};
		minitScript->registerMethod(new MethodBitwiseOr(minitScript));
	}
	//
	{
		class MethodBitwiseXor: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodBitwiseXor(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER),
					minitScript(minitScript) {}
			const string getMethodName() override {
				return "bitwiseXor";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t valueA;
				int64_t valueB;
				auto isValueAInteger = MinitScript::getIntegerValue(arguments, 0, valueA);
				auto isValueBInteger = MinitScript::getIntegerValue(arguments, 1, valueB);
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					isValueAInteger == true &&
					isValueBInteger == true) {
					//
					returnValue.setValue(valueA ^ valueB);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), string(isValueAInteger == false?"Left argument '" + arguments[0].getValueAsString() + "' is not a integer value":"") + string(isValueBInteger == false?string(isValueAInteger == false?" and right argument":"Right argument") + " '" + arguments[1].getValueAsString() + "' is not a integer value":""));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_BITWISEXOR;
			}
		};
		minitScript->registerMethod(new MethodBitwiseXor(minitScript));
	}
	// hex: move me into HexMethods
	{
		//
		class MethodHexEncode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHexEncode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "hex.encode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t value;
				if (arguments.size() == 1 &&
					MinitScript::getIntegerValue(arguments, 0, value) == true) {
					returnValue.setValue(_Hex::encodeInt(value));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHexEncode(minitScript));
	}
	{
		//
		class MethodHexDecode: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodHexDecode(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "hex.decode";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string value;
				if (arguments.size() == 1 &&
					MinitScript::getStringValue(arguments, 0, value) == true) {
					returnValue.setValue(static_cast<int64_t>(_Hex::decodeInt(value)));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new MethodHexDecode(minitScript));
	}
	// swap
	{
		//
		class SwapMethod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			SwapMethod(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = true, .nullable = false }
					}
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "swap";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				//
				if (arguments.size() == 2) {
					MinitScript::Variable::swap(arguments[0], arguments[1]);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new SwapMethod(minitScript));
	}
	// threading ...
	{
		//
		class ConcurrencyGetHardwareThreadCountMethod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ConcurrencyGetHardwareThreadCountMethod(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_INTEGER
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "concurrency.getHardwareThreadCount";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				if (arguments.empty() == true) {
					returnValue.setValue(static_cast<int64_t>(_Thread::getHardwareThreadCount()));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new ConcurrencyGetHardwareThreadCountMethod(minitScript));
	}
	// stacktrace
	{
		//
		class StackTraceMethod: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			StackTraceMethod(MinitScript* minitScript):
				MinitScript::Method(
					{},
					MinitScript::TYPE_STRING
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "stackTrace";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				//
				if (arguments.empty() == true) {
					returnValue.setValue(minitScript->stackTrace(arguments, subStatement));
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
				}
			}
		};
		minitScript->registerMethod(new StackTraceMethod(minitScript));
	}
	// subscript operator
	{
		//
		class MethodSubScript: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodSubScript(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "subscript";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				int64_t index;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_ARRAY &&
					MinitScript::getIntegerValue(arguments, 1, index) == true) {
					auto arrayEntryPtr = arguments[0].getArrayEntryPtr(index);
					if (arrayEntryPtr != nullptr) returnValue.setReference(arrayEntryPtr);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINO(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_SUBSCRIPT;
			}
		};
		minitScript->registerMethod(new MethodSubScript(minitScript));
	}
	// property operator
	{
		//
		class MethodMemberProperty: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMemberProperty(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_MAP, .name = "object", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "property", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = true, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "memberProperty";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string key;
				if ((arguments.size() == 2 || arguments.size() == 3) &&
					arguments[0].getType() == MinitScript::TYPE_MAP &&
					MinitScript::getStringValue(arguments, 1, key) == true) {
					auto mapEntryPtr = arguments[0].getMapEntryPtr(key);
					if (mapEntryPtr != nullptr) returnValue.setReference(mapEntryPtr);
				} else {
					MINITSCRIPT_METHODUSAGE_COMPLAINO(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()));
				}
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_MEMBERACCESS_PROPERTY;
			}
		};
		minitScript->registerMethod(new MethodMemberProperty(minitScript));
	}
	// execute operator
	{
		//
		class MethodMemberExecute: public MinitScript::Method {
		private:
			MinitScript* minitScript { nullptr };
		public:
			MethodMemberExecute(MinitScript* minitScript):
				MinitScript::Method(
					{
						{ .type = MinitScript::TYPE_PSEUDO_MIXED, .name = "object", .optional = false, .reference = true, .nullable = false },
						{ .type = MinitScript::TYPE_STRING, .name = "method", .optional = false, .reference = false, .nullable = false },
						{ .type = MinitScript::TYPE_INTEGER, .name = "operator", .optional = false, .reference = false, .nullable = false }
					},
					MinitScript::TYPE_PSEUDO_MIXED
				),
				minitScript(minitScript) {}
			const string getMethodName() override {
				return "memberExecute";
			}
			void executeMethod(span<MinitScript::Variable>& arguments, MinitScript::Variable& returnValue, const MinitScript::SubStatement& subStatement) override {
				string methodName;
				//
				if (arguments.size() < 3 ||
					minitScript->getStringValue(arguments, 1, methodName, false) == false) {
					MINITSCRIPT_METHODUSAGE_COMPLAINO(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()));
				} else {
					// complain?
					auto complain = true;
					// check if map, if so fetch function assignment of member property
					auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
					if (arguments[0].getType() == MinitScript::TYPE_MAP) {
						string function;
						auto mapValue = arguments[0].getMapEntry(methodName);
						if (mapValue.getType() == MinitScript::TYPE_FUNCTION_ASSIGNMENT && mapValue.getFunctionValue(function, functionScriptIdx) == true) {
							// check if private and private scope
							if (mapValue.isPrivate() == true && arguments[0].isPrivateScope() == false) {
								complain = false;
								functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
								_Console::printLine(minitScript->getSubStatementInformation(subStatement) + ": Private variable: " + /*thisVariableName*/ + "No variable name: access not allowed from outside of object");
							} else
							// no function idx, so get it
							if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) functionScriptIdx = minitScript->getFunctionScriptIdx(function);
						}
					}
					//
					const auto& className = arguments[0].getTypeAsString();
					//
					if (className.empty() == false || functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
						//
						MinitScript::Method* method { nullptr };
						if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							#if defined(__MINITSCRIPT_TRANSPILATION__)
								method = evaluateMemberAccessArrays[static_cast<int>(arguments[0].getType()) - static_cast<int>(MinitScript::TYPE_STRING)][EVALUATEMEMBERACCESS_MEMBER];
							#else
								method = minitScript->getMethod(className + "::" + methodName);
							#endif
						}
						if (method != nullptr || functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
							// create method call arguments
							vector<MinitScript::Variable> callArguments(arguments.size() - 2);
							//	this
							callArguments[0] = std::move(arguments[0]);
							//
							for (auto argumentIdx = 3; argumentIdx < arguments.size(); argumentIdx++) {
								callArguments[argumentIdx - 2] = std::move(arguments[argumentIdx]);
							}
							//
							span callArgumentsSpan(callArguments);
							//
							if (method != nullptr) {
								method->executeMethod(callArgumentsSpan, returnValue, subStatement);
							} else
							if (functionScriptIdx != MinitScript::SCRIPTIDX_NONE) {
								minitScript->call(functionScriptIdx, callArgumentsSpan, returnValue);
							}
							//
							// write back arguments from call arguments
							//	this
							arguments[0] = std::move(callArguments[0]);
							//	additional arguments
							{
								for (auto argumentIdx = 3; argumentIdx < arguments.size(); argumentIdx++) {
									arguments[argumentIdx] = std::move(callArguments[argumentIdx - 2]);
								}
							}
						} else {
							if (complain == true) {
								MINITSCRIPT_METHODUSAGE_COMPLAINOM(getMethodName(), MinitScript::decodeOperator(arguments, 2, getMethodName()), "Class/object member not found: " + methodName + "()");
							}
						}
					} else {
						if (complain == true) {
							MINITSCRIPT_METHODUSAGE_COMPLAIN(getMethodName());
						}
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
			MinitScript::Operator getOperator() const override {
				return MinitScript::OPERATOR_MEMBERACCESS_EXECUTE;
			}
		};
		minitScript->registerMethod(new MethodMemberExecute(minitScript));
	}
}
