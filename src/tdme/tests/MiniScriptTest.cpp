#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

void MiniScriptTest::nothing(int miniScriptGotoStatementIdx) {
	// this can be transpiled using: ./bin/tdme/tools/cli/miniscripttranspiler.exe resources/tests/scripts/test.tscript src/tdme/tests/MiniScriptTest.cpp
	// the __MINISCRIPT_TRANSPILED_NOTHING_START__ and __MINISCRIPT_TRANSPILED_NOTHING_END__ are required markers where transpiled code will be placed

	/*__MINISCRIPT_TRANSPILED_NOTHING_START__*/
auto miniScript = this;
miniScript->scriptState.scriptIdx = 1;
if (miniScriptGotoStatementIdx == 103) goto statement_103; else
if (miniScriptGotoStatementIdx == 105) goto statement_105; else
if (miniScriptGotoStatementIdx == 107) goto statement_107; else
if (miniScriptGotoStatementIdx == 112) goto statement_112; else
if (miniScriptGotoStatementIdx == 114) goto statement_114; else
if (miniScriptGotoStatementIdx == 116) goto statement_116; else
if (miniScriptGotoStatementIdx == 122) goto statement_122; else
if (miniScriptGotoStatementIdx == 124) goto statement_124; else
if (miniScriptGotoStatementIdx == 126) goto statement_126; else
if (miniScriptGotoStatementIdx == 128) goto statement_128; else
if (miniScriptGotoStatementIdx == 130) goto statement_130; else
if (miniScriptGotoStatementIdx == 132) goto statement_132; else
if (miniScriptGotoStatementIdx == 134) goto statement_134; else
if (miniScriptGotoStatementIdx == 136) goto statement_136; else
if (miniScriptGotoStatementIdx == 140) goto statement_140; else
if (miniScriptGotoStatementIdx == 142) goto statement_142; else
if (miniScriptGotoStatementIdx == 151) goto statement_151; else
if (miniScriptGotoStatementIdx != 0) Console::println("MiniScript::nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
statement_0:
				// console.log("---------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 10, 
						.statementIdx = 0, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_1:
				// console.log("Nothing")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 11, 
						.statementIdx = 1, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Nothing")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_2:
				// console.log("----------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 12, 
						.statementIdx = 2, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("----------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_3:
				// console.log()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 13, 
						.statementIdx = 3, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_4:
				// console.log("-----------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 14, 
						.statementIdx = 4, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_5:
				// console.log("Check bool operations")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 15, 
						.statementIdx = 5, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check bool operations")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_6:
				// console.log("-----------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 16, 
						.statementIdx = 6, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_7:
				// console.log("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 17, 
						.statementIdx = 7, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
					// depth = 1 / argument index = 1: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
						argumentValues.push_back(MiniScript::ScriptVariable(true));
						// depth = 2 / argument index = 0: or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals(MiniScript will do the job, MiniScript will not do the job)
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals(it will, it will)
							// depth = 3 / argument index = 0: equals(MiniScript will do the job, MiniScript will not do the job)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("MiniScript will do the job")));
								argumentValues.push_back(MiniScript::ScriptVariable(string("MiniScript will not do the job")));
								returnValue.setValue(true);
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
										returnValue.setValue(false);
										break;
									}
								}
							}
							// depth = 3 / argument index = 1: equals(it will, it will)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("it will")));
								argumentValues.push_back(MiniScript::ScriptVariable(string("it will")));
								returnValue.setValue(true);
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
										returnValue.setValue(false);
										break;
									}
								}
							}
							returnValue.setValue(false);
							for (auto i = 0; i < argumentValues.size(); i++) {
								bool booleanValue;
								if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
									Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
									miniScript->startErrorScript();
								} else
								if (booleanValue == true) {
									returnValue.setValue(true);
									break;
								}
							}
						}
						returnValue.setValue(true);
						for (auto i = 0; i < argumentValues.size(); i++) {
							bool booleanValue;
							if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
								Console::println("ScriptMethodAnd::executeMethod(): " + string("and") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
								miniScript->startErrorScript();
							} else
							if (booleanValue == false) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_8:
				// console.log("-----------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 18, 
						.statementIdx = 8, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_9:
				// console.log("Check int computation")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 19, 
						.statementIdx = 9, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check int computation")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_10:
				// console.log("-----------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 20, 
						.statementIdx = 10, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_11:
				// console.log("sub(add(1, 2, 3), 1)): ", sub(add(1, 2, 3), 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 21, 
						.statementIdx = 11, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("sub(add(1, 2, 3), 1)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(add(1, 2, 3), 1)
					// depth = 1 / argument index = 1: sub(add(1, 2, 3), 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(1, 2, 3)
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: add(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_12:
				// console.log("div(20, 2): ", div(20, 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 22, 
						.statementIdx = 12, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("div(20, 2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(20, 2)
					// depth = 1 / argument index = 1: div(20, 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_13:
				// console.log("mul(11, 10): ", mul(11, 10))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 23, 
						.statementIdx = 13, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("mul(11, 10): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(11, 10)
					// depth = 1 / argument index = 1: mul(11, 10)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(11)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_14:
				// console.log("greater(2, 1): ", greater(2, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 24, 
						.statementIdx = 14, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("greater(2, 1): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of greater(2, 1)
					// depth = 1 / argument index = 1: greater(2, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA > floatValueB);
						} else {
							Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_15:
				// console.log("lesser(2, 1): ", lesser(2, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 25, 
						.statementIdx = 15, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("lesser(2, 1): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of lesser(2, 1)
					// depth = 1 / argument index = 1: lesser(2, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_16:
				// console.log("---------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 26, 
						.statementIdx = 16, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_17:
				// console.log("Check int computation (Operators)")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 27, 
						.statementIdx = 17, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check int computation (Operators)")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_18:
				// console.log("---------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 28, 
						.statementIdx = 18, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_19:
				// console.log("1 + 2 + 3 - 1: ", sub(add(1,add(2, 3)), 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 29, 
						.statementIdx = 19, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("1 + 2 + 3 - 1: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(add(1,add(2, 3)), 1)
					// depth = 1 / argument index = 1: sub(add(1,add(2, 3)), 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(1,add(2, 3))
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: add(1, add(2, 3))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(2, 3)
							// depth = 3 / argument index = 1: add(2, 3)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
								argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
									string result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										string stringValue;
										if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
											result+= stringValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									Vector3 result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result+= vec3Value;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									float result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= floatValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else {
									int64_t result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result+= intValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_20:
				// console.log("20 / 2: ", div(20, 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 30, 
						.statementIdx = 20, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("20 / 2: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(20, 2)
					// depth = 1 / argument index = 1: div(20, 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_21:
				// console.log("11 * 10: ", mul(11, 10))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 31, 
						.statementIdx = 21, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("11 * 10: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(11, 10)
					// depth = 1 / argument index = 1: mul(11, 10)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(11)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_22:
				// console.log("2 > 1: ", greater(2, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 32, 
						.statementIdx = 22, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("2 > 1: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of greater(2, 1)
					// depth = 1 / argument index = 1: greater(2, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA > floatValueB);
						} else {
							Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_23:
				// console.log("2 < 1: ", lesser(2, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 33, 
						.statementIdx = 23, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("2 < 1: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of lesser(2, 1)
					// depth = 1 / argument index = 1: lesser(2, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_24:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 34, 
						.statementIdx = 24, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_25:
				// console.log("Check float computation")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 35, 
						.statementIdx = 25, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check float computation")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_26:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 36, 
						.statementIdx = 26, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_27:
				// console.log("sub(add(1.1, 2.2, 3.3), 1.2)): ", sub(add(1.1, 2.2, 3.3), 1.2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 37, 
						.statementIdx = 27, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("sub(add(1.1, 2.2, 3.3), 1.2)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(add(1.1, 2.2, 3.3), 1.2)
					// depth = 1 / argument index = 1: sub(add(1.1, 2.2, 3.3), 1.2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(1.1, 2.2, 3.3)
						argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
						// depth = 2 / argument index = 0: add(1.1, 2.2, 3.3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.100000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.300000f));
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_28:
				// console.log("div(20, 1.5): ", div(20, 1.5))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 38, 
						.statementIdx = 28, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("div(20, 1.5): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(20, 1.5)
					// depth = 1 / argument index = 1: div(20, 1.5)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
						argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_29:
				// console.log("mul(11.5, 10.5): ", mul(11.5, 10.5))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 39, 
						.statementIdx = 29, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("mul(11.5, 10.5): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(11.5, 10.5)
					// depth = 1 / argument index = 1: mul(11.5, 10.5)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(11.500000f));
						argumentValues.push_back(MiniScript::ScriptVariable(10.500000f));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_30:
				// console.log("greater(2.2, 1.3): ", greater(2.2, 1.3))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 40, 
						.statementIdx = 30, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("greater(2.2, 1.3): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of greater(2.2, 1.3)
					// depth = 1 / argument index = 1: greater(2.2, 1.3)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
						argumentValues.push_back(MiniScript::ScriptVariable(1.300000f));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA > floatValueB);
						} else {
							Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_31:
				// console.log("lesser(2.5, 1.2): ", lesser(2.5, 1.2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 41, 
						.statementIdx = 31, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("lesser(2.5, 1.2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of lesser(2.5, 1.2)
					// depth = 1 / argument index = 1: lesser(2.5, 1.2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
						argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_32:
				// console.log("-----------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 42, 
						.statementIdx = 32, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_33:
				// console.log("Check float computation (Operators)")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 43, 
						.statementIdx = 33, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check float computation (Operators)")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_34:
				// console.log("-----------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 44, 
						.statementIdx = 34, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_35:
				// console.log("(1.1 + 2.2 + 3.3) - 1.2: ", sub(add(1.1,add(2.2, 3.3)), 1.2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 45, 
						.statementIdx = 35, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("(1.1 + 2.2 + 3.3) - 1.2: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(add(1.1,add(2.2, 3.3)), 1.2)
					// depth = 1 / argument index = 1: sub(add(1.1,add(2.2, 3.3)), 1.2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(1.1,add(2.2, 3.3))
						argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
						// depth = 2 / argument index = 0: add(1.1, add(2.2, 3.3))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.100000f));
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(2.2, 3.3)
							// depth = 3 / argument index = 1: add(2.2, 3.3)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
								argumentValues.push_back(MiniScript::ScriptVariable(3.300000f));
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
									string result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										string stringValue;
										if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
											result+= stringValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									Vector3 result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result+= vec3Value;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									float result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= floatValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else {
									int64_t result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result+= intValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_36:
				// console.log("20 / 1.5: ", div(20, 1.5))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 46, 
						.statementIdx = 36, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("20 / 1.5: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(20, 1.5)
					// depth = 1 / argument index = 1: div(20, 1.5)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
						argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_37:
				// console.log("11.5 * 10.5: ", mul(11.5, 10.5))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 47, 
						.statementIdx = 37, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("11.5 * 10.5: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(11.5, 10.5)
					// depth = 1 / argument index = 1: mul(11.5, 10.5)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(11.500000f));
						argumentValues.push_back(MiniScript::ScriptVariable(10.500000f));
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_38:
				// console.log("2.2 > 1.3: ", greater(2.2, 1.3))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 48, 
						.statementIdx = 38, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("2.2 > 1.3: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of greater(2.2, 1.3)
					// depth = 1 / argument index = 1: greater(2.2, 1.3)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
						argumentValues.push_back(MiniScript::ScriptVariable(1.300000f));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA > floatValueB);
						} else {
							Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_39:
				// console.log("2.5 < 1.2: ", lesser(2.5, 1.2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 49, 
						.statementIdx = 39, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("2.5 < 1.2: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of lesser(2.5, 1.2)
					// depth = 1 / argument index = 1: lesser(2.5, 1.2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
						argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_40:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 50, 
						.statementIdx = 40, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_41:
				// console.log("Check vector3 computation")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 51, 
						.statementIdx = 41, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check vector3 computation")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_42:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 52, 
						.statementIdx = 42, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_43:
				// console.log("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): ", sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 53, 
						.statementIdx = 43, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
					// depth = 1 / argument index = 1: sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(vec3(1.1, 2.2, 3.3))
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.2, 1.0, 1.0)
						// depth = 2 / argument index = 0: add(vec3(1.1, 2.2, 3.3))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.1, 2.2, 3.3)
							// depth = 3 / argument index = 0: vec3(1.1, 2.2, 3.3)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(1.100000f));
								argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
								argumentValues.push_back(MiniScript::ScriptVariable(3.300000f));
								Vector3 result;
								float xValue;
								float yValue;
								float zValue;
								if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
									MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
									MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
									returnValue.setValue(Vector3(xValue, yValue, zValue));
								} else {
									Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
									miniScript->startErrorScript();
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						// depth = 2 / argument index = 1: vec3(1.2, 1.0, 1.0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
							argumentValues.push_back(MiniScript::ScriptVariable(1.000000f));
							argumentValues.push_back(MiniScript::ScriptVariable(1.000000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_44:
				// console.log("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 54, 
						.statementIdx = 44, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.5, 2.5, 3.5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.500000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_45:
				// console.log("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 55, 
						.statementIdx = 45, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.5, 2.5, 3.5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.500000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_46:
				// console.log("div(vec3(20, 10, 5), 2): ", div(vec3(20, 10, 5), 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 56, 
						.statementIdx = 46, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("div(vec3(20, 10, 5), 2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(vec3(20, 10, 5), 2)
					// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_47:
				// console.log("mul(vec3(20, 10, 5), 2): ", mul(vec3(20, 10, 5), 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 57, 
						.statementIdx = 47, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("mul(vec3(20, 10, 5), 2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(vec3(20, 10, 5), 2)
					// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_48:
				// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 58, 
						.statementIdx = 48, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.computeLength(vec3(20, 10, 5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.computeLength(vec3(20, 10, 5))
					// depth = 1 / argument index = 1: vec3.computeLength(vec3(20, 10, 5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.computeLength());
						} else {
							Console::println("ScriptMethodVec3ComputeLength::executeMethod(): " + string("vec3.computeLength") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_49:
				// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 59, 
						.statementIdx = 49, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.computeLengthSquared(vec3(20, 10, 5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.computeLengthSquared(vec3(20, 10, 5))
					// depth = 1 / argument index = 1: vec3.computeLengthSquared(vec3(20, 10, 5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.computeLengthSquared());
						} else {
							Console::println("ScriptMethodVec3ComputeLengthSquared::executeMethod(): " + string("vec3.computeLengthSquared") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_50:
				// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 60, 
						.statementIdx = 50, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
					// depth = 1 / argument index = 1: vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 0, 1)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 0, -1)
						// depth = 2 / argument index = 0: vec3(0, 0, 1)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(0, 0, -1)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-1)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 a;
						Vector3 b;
						if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
							returnValue.setValue(Vector3::computeDotProduct(a, b));
						} else {
							Console::println("ScriptMethodVec3ComputeDotProduct::executeMethod(): " + string("vec3.computeDotProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_51:
				// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 61, 
						.statementIdx = 51, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
					// depth = 1 / argument index = 1: vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 0, 0)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 1, 0)
						// depth = 2 / argument index = 0: vec3(1, 0, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(0, 1, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 a;
						Vector3 b;
						if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
							returnValue.setValue(Vector3::computeCrossProduct(a, b));
						} else {
							Console::println("ScriptMethodVec3ComputeCrossProduct::executeMethod(): " + string("vec3.computeCrossProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_52:
				// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 62, 
						.statementIdx = 52, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.normalize(vec3(1, 2, 3)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.normalize(vec3(1, 2, 3))
					// depth = 1 / argument index = 1: vec3.normalize(vec3(1, 2, 3))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 2, 3)
						// depth = 2 / argument index = 0: vec3(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.normalize());
						} else {
							Console::println("ScriptMethodVec3Normalize::executeMethod(): " + string("vec3.normalize") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_53:
				// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 63, 
						.statementIdx = 53, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
					// depth = 1 / argument index = 1: vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 0, 1)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 0, 0)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 1, 0)
						// depth = 2 / argument index = 0: vec3(0, 0, 1)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1, 0, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 2: vec3(0, 1, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX2 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 a;
						Vector3 b;
						Vector3 n;
						if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, b, false) == true &&
							MiniScript::getVector3Value(argumentValues, 2, n, false) == true) {
							returnValue.setValue(Vector3::computeAngle(a, b, n));
						} else {
							Console::println("ScriptMethodVec3ComputeAngle::executeMethod(): " + string("vec3.computeAngle") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected @ argument 2: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_54:
				// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 64, 
						.statementIdx = 54, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.getX(vec3(1, 2, 3)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.getX(vec3(1, 2, 3))
					// depth = 1 / argument index = 1: vec3.getX(vec3(1, 2, 3))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 2, 3)
						// depth = 2 / argument index = 0: vec3(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.getX());
						} else {
							Console::println("ScriptMethodVec3GetX::executeMethod(): " + string("vec3.getX") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_55:
				// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 65, 
						.statementIdx = 55, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.getY(vec3(1, 2, 3)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.getY(vec3(1, 2, 3))
					// depth = 1 / argument index = 1: vec3.getY(vec3(1, 2, 3))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 2, 3)
						// depth = 2 / argument index = 0: vec3(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.getY());
						} else {
							Console::println("ScriptMethodVec3GetY::executeMethod(): " + string("vec3.getY") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_56:
				// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 66, 
						.statementIdx = 56, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3.getZ(vec3(1, 2, 3)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3.getZ(vec3(1, 2, 3))
					// depth = 1 / argument index = 1: vec3.getZ(vec3(1, 2, 3))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1, 2, 3)
						// depth = 2 / argument index = 0: vec3(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Vector3 vec3;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
							returnValue.setValue(vec3.getZ());
						} else {
							Console::println("ScriptMethodVec3GetZ::executeMethod(): " + string("vec3.getZ") + "(): parameter type mismatch @ argument 0: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_57:
				// console.log("-------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 67, 
						.statementIdx = 57, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_58:
				// console.log("Check vector3 computation (Operators)")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 68, 
						.statementIdx = 58, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check vector3 computation (Operators)")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_59:
				// console.log("-------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 69, 
						.statementIdx = 59, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_60:
				// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 70, 
						.statementIdx = 60, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
					// depth = 1 / argument index = 1: sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.1, 2.2, 3.3)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.2, 1.0, 1.0)
						// depth = 2 / argument index = 0: vec3(1.1, 2.2, 3.3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.100000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.200000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.300000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1.2, 1.0, 1.0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.200000f));
							argumentValues.push_back(MiniScript::ScriptVariable(1.000000f));
							argumentValues.push_back(MiniScript::ScriptVariable(1.000000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result-= vec3Value;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							bool valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result-= floatValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							bool valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result-= intValue;
									} else {
										Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_61:
				// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 71, 
						.statementIdx = 61, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.5, 2.5, 3.5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.500000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_62:
				// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 72, 
						.statementIdx = 62, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1.5, 2.5, 3.5)
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(1.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(2.500000f));
							argumentValues.push_back(MiniScript::ScriptVariable(3.500000f));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_63:
				// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 73, 
						.statementIdx = 63, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3(20, 10, 5) / 2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(vec3(20, 10, 5), 2)
					// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result/= vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result/= intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_64:
				// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 74, 
						.statementIdx = 64, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("vec3(20, 10, 5) * 2): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(vec3(20, 10, 5), 2)
					// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(20, 10, 5)
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						// depth = 2 / argument index = 0: vec3(20, 10, 5)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(20)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(10)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript();
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result*= vec3Value;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
								}
								returnValue.setValue(result);
							}
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							auto valid = true;
							float result = 0.0f;
							{
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = floatValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result*= floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						} else {
							auto valid = true;
							int64_t result = 0LL;
							{
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
									result = intValue;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
									miniScript->startErrorScript();
									valid = false;
								}
							}
							if (valid == true) {
								for (auto i = 1; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result*= intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_65:
				// console.log("-----------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 75, 
						.statementIdx = 65, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_66:
				// console.log("Check transformations computation")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 76, 
						.statementIdx = 66, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check transformations computation")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_67:
				// console.log("-----------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 77, 
						.statementIdx = 67, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-----------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_68:
				// setVariable("$transformations", transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 78, 
						.statementIdx = 68, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
					// depth = 1 / argument index = 1: transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(1,2,3)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(2, 3, 4)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0, 1, 0)
						// depth = 2 / argument index = 0: vec3(1, 2, 3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(2, 3, 4)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(4)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 2: vec3(0, 1, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX2 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						Vector3 vec3Value;
						if (argumentValues.size() >= 1) {
							if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
								transformations.setTranslation(vec3Value);
							} else {
								Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument 0: vector3 expected");
								miniScript->startErrorScript();
							}
						}
						if (argumentValues.size() >= 2) {
							if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
								transformations.setScale(vec3Value);
							} else {
								Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument 1: vector3 expected");
								miniScript->startErrorScript();
							}
						}
						for (auto i = 2; i < argumentValues.size(); i++) {
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, true) == true) {
								transformations.addRotation(vec3Value, 0.0f);
							} else {
								Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript();
							}
						}
						transformations.update();
						returnValue.setValue(transformations);
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_69:
				// setVariable("$transformations", transformations.setRotationAngle($transformations, 0, 90))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 79, 
						.statementIdx = 69, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.setRotationAngle($transformations, 0, 90)
					// depth = 1 / argument index = 1: transformations.setRotationAngle($transformations, 0, 90)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(90)));
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						int64_t idx;
						Transformations transformations;
						float angle;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
							MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
							if (idx < transformations.getRotationCount()) {
								transformations.setRotationAngle(idx, angle);
								transformations.update();
								returnValue.setValue(transformations);
							} else {
								Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
								miniScript->startErrorScript();
							}
						} else {
							Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected, @ argument 2: float expected");
							miniScript->startErrorScript();
						}
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_70:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): ", $transformations)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 80, 
						.statementIdx = 70, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
					// depth = 1 / argument index = 1: getVariable("$transformations")
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_71:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): ", transformations.getTranslation($transformations))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 81, 
						.statementIdx = 71, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.getTranslation($transformations)
					// depth = 1 / argument index = 1: transformations.getTranslation($transformations)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
							returnValue.setValue(transformations.getTranslation());
						} else {
							Console::println("ScriptMethodTransformationsGetTranslation::executeMethod(): " + string("transformations.getTranslation") + "(): parameter type mismatch @ argument 0: transformations expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_72:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): ", transformations.setTranslation($transformations, vec3(-1,-2,-3)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 82, 
						.statementIdx = 72, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.setTranslation($transformations, vec3(-1,-2,-3))
					// depth = 1 / argument index = 1: transformations.setTranslation($transformations, vec3(-1,-2,-3))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(-1,-2,-3)
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(-1, -2, -3)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-1)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-3)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						Vector3 translation;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, translation, false) == true) {
							transformations.setTranslation(translation);
							transformations.update();
							returnValue.setValue(transformations);
						} else {
							Console::println("ScriptMethodTransformationsSetTranslation::executeMethod(): " + string("transformations.setTranslation") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_73:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): ", transformations.getScale($transformations))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 83, 
						.statementIdx = 73, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.getScale($transformations)
					// depth = 1 / argument index = 1: transformations.getScale($transformations)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
							returnValue.setValue(transformations.getScale());
						} else {
							Console::println("ScriptMethodTransformationsGetScale::executeMethod(): " + string("transformations.getScale") + "(): parameter type mismatch @ argument 0: transformations expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_74:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): ", transformations.setScale($transformations, vec3(-2,-3,-4)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 84, 
						.statementIdx = 74, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.setScale($transformations, vec3(-2,-3,-4))
					// depth = 1 / argument index = 1: transformations.setScale($transformations, vec3(-2,-3,-4))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(-2,-3,-4)
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(-2, -3, -4)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-2)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-3)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(-4)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						Vector3 scale;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, scale, false) == true) {
							transformations.setScale(scale);
							transformations.update();
							returnValue.setValue(transformations);
						} else {
							Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.setScale") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_75:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): ", transformations.getRotationAxis($transformations, 0))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 85, 
						.statementIdx = 75, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.getRotationAxis($transformations, 0)
					// depth = 1 / argument index = 1: transformations.getRotationAxis($transformations, 0)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						int64_t idx;
						Transformations transformations;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
							if (idx < transformations.getRotationCount()) {
								returnValue.setValue(transformations.getRotationAxis(idx));
							} else {
								Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + string("transformations.getRotationAxis") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
								miniScript->startErrorScript();
							}
						} else {
							Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + string("transformations.getRotationAxis") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_76:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): ", transformations.getRotationAngle($transformations, 0))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 86, 
						.statementIdx = 76, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.getRotationAngle($transformations, 0)
					// depth = 1 / argument index = 1: transformations.getRotationAngle($transformations, 0)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						int64_t idx;
						Transformations transformations;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
							if (idx < transformations.getRotationCount()) {
								returnValue.setValue(transformations.getRotationAngle(idx));
							} else {
								Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + string("transformations.getRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
								miniScript->startErrorScript();
							}
						} else {
							Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + string("transformations.getRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_77:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): ", transformations.setRotationAngle($transformations, 0, 90))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 87, 
						.statementIdx = 77, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.setRotationAngle($transformations, 0, 90)
					// depth = 1 / argument index = 1: transformations.setRotationAngle($transformations, 0, 90)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(90)));
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						int64_t idx;
						Transformations transformations;
						float angle;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
							MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
							if (idx < transformations.getRotationCount()) {
								transformations.setRotationAngle(idx, angle);
								transformations.update();
								returnValue.setValue(transformations);
							} else {
								Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
								miniScript->startErrorScript();
							}
						} else {
							Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected, @ argument 2: float expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_78:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): ", transformations.multiply($transformations, vec3(0,0,0)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 88, 
						.statementIdx = 78, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.multiply($transformations, vec3(0,0,0))
					// depth = 1 / argument index = 1: transformations.multiply($transformations, vec3(0,0,0))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0,0,0)
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(0, 0, 0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						Vector3 vec3;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
							returnValue.setValue(transformations.getTransformationsMatrix() * vec3);
						} else {
							Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.multiply") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_79:
				// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): ", transformations.rotate($transformations, vec3(0,0,1)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 89, 
						.statementIdx = 79, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of transformations.rotate($transformations, vec3(0,0,1))
					// depth = 1 / argument index = 1: transformations.rotate($transformations, vec3(0,0,1))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$transformations")
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of vec3(0,0,1)
						// depth = 2 / argument index = 0: getVariable("$transformations")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$transformations")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						// depth = 2 / argument index = 1: vec3(0, 0, 1)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
							argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
							Vector3 result;
							float xValue;
							float yValue;
							float zValue;
							if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
								MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
								returnValue.setValue(Vector3(xValue, yValue, zValue));
							} else {
								Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
								miniScript->startErrorScript();
							}
						}
						Transformations transformations;
						Vector3 vec3;
						if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
							MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
							returnValue.setValue(transformations.getRotationsQuaternion() * vec3);
						} else {
							Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.rotate") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_80:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 90, 
						.statementIdx = 80, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_81:
				// console.log("Check string functions")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 91, 
						.statementIdx = 81, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check string functions")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_82:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 92, 
						.statementIdx = 82, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_83:
				// console.log(space(0), "1")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 93, 
						.statementIdx = 83, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of space(0)
					argumentValues.push_back(MiniScript::ScriptVariable(string("1")));
					// depth = 1 / argument index = 0: space(0)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						int64_t spaces = 1;
						if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
							Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
							miniScript->startErrorScript();
						} else {
							string spacesString;
							for (auto i = 0; i < spaces; i++) spacesString+= " ";
							returnValue.setValue(spacesString);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_84:
				// console.log(space(2), "1.1")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 94, 
						.statementIdx = 84, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of space(2)
					argumentValues.push_back(MiniScript::ScriptVariable(string("1.1")));
					// depth = 1 / argument index = 0: space(2)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						int64_t spaces = 1;
						if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
							Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
							miniScript->startErrorScript();
						} else {
							string spacesString;
							for (auto i = 0; i < spaces; i++) spacesString+= " ";
							returnValue.setValue(spacesString);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_85:
				// console.log(space(2), "1.2")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 95, 
						.statementIdx = 85, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of space(2)
					argumentValues.push_back(MiniScript::ScriptVariable(string("1.2")));
					// depth = 1 / argument index = 0: space(2)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						int64_t spaces = 1;
						if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
							Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
							miniScript->startErrorScript();
						} else {
							string spacesString;
							for (auto i = 0; i < spaces; i++) spacesString+= " ";
							returnValue.setValue(spacesString);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_86:
				// console.log(toUpperCase("xxxyyyzzz"))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 96, 
						.statementIdx = 86, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of toUpperCase("xxxyyyzzz")
					// depth = 1 / argument index = 0: toUpperCase("xxxyyyzzz")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("xxxyyyzzz")));
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
							returnValue.setValue(StringTools::toUpperCase(stringValue));
						} else {
							Console::println("ScriptMethodToUpperCase::executeMethod(): " + string("toUpperCase") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_87:
				// console.log(toLowerCase("XXXYYYZZZ"))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 97, 
						.statementIdx = 87, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of toLowerCase("XXXYYYZZZ")
					// depth = 1 / argument index = 0: toLowerCase("XXXYYYZZZ")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("XXXYYYZZZ")));
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
							returnValue.setValue(StringTools::toLowerCase(stringValue));
						} else {
							Console::println("ScriptMethodToLowerCase::executeMethod(): " + string("toLowerCase") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_88:
				// console.log(concatenate("abc", "def", "ghi"))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 98, 
						.statementIdx = 88, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of concatenate("abc", "def", "ghi")
					// depth = 1 / argument index = 0: concatenate("abc", "def", "ghi")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("abc")));
						argumentValues.push_back(MiniScript::ScriptVariable(string("def")));
						argumentValues.push_back(MiniScript::ScriptVariable(string("ghi")));
						string result;
						for (auto& argumentValue: argumentValues) {
							result+= argumentValue.getValueString();
						}
						returnValue.setValue(result);
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_89:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 99, 
						.statementIdx = 89, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_90:
				// console.log("Check string functions (Operators)")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 100, 
						.statementIdx = 90, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Check string functions (Operators)")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_91:
				// console.log(add("abc",add("def", "ghi")))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 101, 
						.statementIdx = 91, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add("abc",add("def", "ghi"))
					// depth = 1 / argument index = 0: add("abc", add("def", "ghi"))
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("abc")));
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add("def", "ghi")
						// depth = 2 / argument index = 1: add("def", "ghi")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("def")));
							argumentValues.push_back(MiniScript::ScriptVariable(string("ghi")));
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_92:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 102, 
						.statementIdx = 92, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_93:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 103, 
						.statementIdx = 93, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_94:
				// console.log("Variable")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 104, 
						.statementIdx = 94, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Variable")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_95:
				// console.log("------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 105, 
						.statementIdx = 95, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_96:
				// setVariable("$variable", string("1234"))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 106, 
						.statementIdx = 96, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$variable")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of string("1234")
					// depth = 1 / argument index = 1: string("1234")
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("1234")));
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
							returnValue.setValue(stringValue);
						} else {
							Console::println("ScriptMethodString::executeMethod(): " + string("string") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_97:
				// console.log(getVariable("$variable"))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 107, 
						.statementIdx = 97, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$variable")
					// depth = 1 / argument index = 0: getVariable("$variable")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$variable")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_98:
				// console.log("--------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 108, 
						.statementIdx = 98, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("--------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_99:
				// console.log("Lets check forTime")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 109, 
						.statementIdx = 99, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Lets check forTime")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_100:
				// console.log("--------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 110, 
						.statementIdx = 100, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("--------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_101:
				// setVariable("$i", 1)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 111, 
						.statementIdx = 101, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_102:
				// forTime(2000)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 112, 
						.statementIdx = 102, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 107
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2000)));
					int64_t time;
					if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
						Console::println("ScriptMethodForTime::executeMethod(): " + string("forTime") + "(): parameter type mismatch @ argument 0: integer expected");
						miniScript->startErrorScript();
					} else {
						//
						auto now = Time::getCurrentMillis();
						auto timeWaitStarted = now;
						auto forTimeStartedIt = miniScript->scriptState.forTimeStarted.find(statement.line);
						if (forTimeStartedIt == miniScript->scriptState.forTimeStarted.end()) {
							miniScript->scriptState.forTimeStarted[statement.line] = timeWaitStarted;
						} else {
							timeWaitStarted = forTimeStartedIt->second;
						}
						//
						if (Time::getCurrentMillis() > timeWaitStarted + time) {
							miniScript->scriptState.forTimeStarted.erase(statement.line);
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_107;
						} else {
							miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_103:
				// console.log($i, ": Hello World")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 113, 
						.statementIdx = 103, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
					argumentValues.push_back(MiniScript::ScriptVariable(string(": Hello World")));
					// depth = 1 / argument index = 0: getVariable("$i")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_104:
				// script.wait(500)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 114, 
						.statementIdx = 104, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(500)));
					int64_t time;
					if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
						miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
						miniScript->scriptState.timeWaitTime = time;
						miniScript->setScriptState(STATE_WAIT);
					} else {
						Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_105:
				// setVariable("$i", add($i, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 115, 
						.statementIdx = 105, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add($i, 1)
					// depth = 1 / argument index = 1: add($i, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_106:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 116, 
						.statementIdx = 106, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 102
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_102;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_107:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 117, 
						.statementIdx = 107, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_108:
				// console.log("Lets check forCondition")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 118, 
						.statementIdx = 108, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Lets check forCondition")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_109:
				// console.log("-------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 119, 
						.statementIdx = 109, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_110:
				// setVariable("$i", 1)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 120, 
						.statementIdx = 110, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_111:
				// forCondition(notequal($i, 6))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 121, 
						.statementIdx = 111, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 116
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of notequal($i, 6)
					// depth = 1 / argument index = 0: notequal($i, 6)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(6)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						returnValue.setValue(true);
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else {
						//
						auto now = Time::getCurrentMillis();
						if (booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_116;
						} else {
							miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_112:
				// console.log($i, ": Hello World")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 122, 
						.statementIdx = 112, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
					argumentValues.push_back(MiniScript::ScriptVariable(string(": Hello World")));
					// depth = 1 / argument index = 0: getVariable("$i")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_113:
				// script.wait(500)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 123, 
						.statementIdx = 113, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(500)));
					int64_t time;
					if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
						miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
						miniScript->scriptState.timeWaitTime = time;
						miniScript->setScriptState(STATE_WAIT);
					} else {
						Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_114:
				// setVariable("$i", add($i, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 124, 
						.statementIdx = 114, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add($i, 1)
					// depth = 1 / argument index = 1: add($i, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_115:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 125, 
						.statementIdx = 115, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 111
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_111;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_116:
				// console.log("i -> ", $i)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 126, 
						.statementIdx = 116, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("i -> ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
					// depth = 1 / argument index = 1: getVariable("$i")
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_117:
				// console.log("---------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 127, 
						.statementIdx = 117, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_118:
				// console.log("Lets check forCondition with if/elseif/else")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 128, 
						.statementIdx = 118, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Lets check forCondition with if/elseif/else")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_119:
				// console.log("---------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 129, 
						.statementIdx = 119, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_120:
				// setVariable("$i", 1)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 130, 
						.statementIdx = 120, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_121:
				// forCondition(lesser($i, 5))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 131, 
						.statementIdx = 121, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 136
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of lesser($i, 5)
					// depth = 1 / argument index = 0: lesser($i, 5)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						float floatValueA;
						float floatValueB;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
							returnValue.setValue(floatValueA < floatValueB);
						} else {
							Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
							miniScript->startErrorScript();
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else {
						//
						auto now = Time::getCurrentMillis();
						if (booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_136;
						} else {
							miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_122:
				// console.log($i, ":")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 132, 
						.statementIdx = 122, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
					argumentValues.push_back(MiniScript::ScriptVariable(string(":")));
					// depth = 1 / argument index = 0: getVariable("$i")
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_123:
				// if(equals($i, 0))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 133, 
						.statementIdx = 123, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 125
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals($i, 0)
					// depth = 1 / argument index = 0: equals($i, 0)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(0)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						returnValue.setValue(true);
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else {
						//
						miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
						//
						miniScript->scriptState.conditionStack.push(booleanValue);
						if (booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_125;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_124:
				// console.log("i -> 0")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 134, 
						.statementIdx = 124, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("i -> 0")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_125:
				// elseif(equals($i, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 135, 
						.statementIdx = 125, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 127
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals($i, 1)
					// depth = 1 / argument index = 0: equals($i, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						returnValue.setValue(true);
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else
					if (miniScript->scriptState.conditionStack.empty() == true) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
						miniScript->startErrorScript();
					} else {
						//
						auto conditionStackElement = miniScript->scriptState.conditionStack.top();
						if (conditionStackElement == false) {
							miniScript->scriptState.conditionStack.pop();
							miniScript->scriptState.conditionStack.push(booleanValue);
						}
						if (conditionStackElement == true || booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_127;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_126:
				// console.log("i -> 1")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 136, 
						.statementIdx = 126, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("i -> 1")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_127:
				// elseif(equals($i, 2))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 137, 
						.statementIdx = 127, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 129
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals($i, 2)
					// depth = 1 / argument index = 0: equals($i, 2)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						returnValue.setValue(true);
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else
					if (miniScript->scriptState.conditionStack.empty() == true) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
						miniScript->startErrorScript();
					} else {
						//
						auto conditionStackElement = miniScript->scriptState.conditionStack.top();
						if (conditionStackElement == false) {
							miniScript->scriptState.conditionStack.pop();
							miniScript->scriptState.conditionStack.push(booleanValue);
						}
						if (conditionStackElement == true || booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_129;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_128:
				// console.log("i -> 2")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 138, 
						.statementIdx = 128, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("i -> 2")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_129:
				// elseif(equals($i, 3))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 139, 
						.statementIdx = 129, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 131
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals($i, 3)
					// depth = 1 / argument index = 0: equals($i, 3)
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						returnValue.setValue(true);
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
								returnValue.setValue(false);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else
					if (miniScript->scriptState.conditionStack.empty() == true) {
						Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
						miniScript->startErrorScript();
					} else {
						//
						auto conditionStackElement = miniScript->scriptState.conditionStack.top();
						if (conditionStackElement == false) {
							miniScript->scriptState.conditionStack.pop();
							miniScript->scriptState.conditionStack.push(booleanValue);
						}
						if (conditionStackElement == true || booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_131;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_130:
				// console.log("i -> 3")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 140, 
						.statementIdx = 130, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("i -> 3")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_131:
				// else()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 141, 
						.statementIdx = 131, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 133
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.conditionStack.empty() == true) {
						Console::println("ScriptMethodElse::executeMethod(): else without if");
						miniScript->startErrorScript();
					} else {
						auto conditionStackElement = miniScript->scriptState.conditionStack.top();
						if (conditionStackElement == true) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_133;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_132:
				// console.log("else: ", $i)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 142, 
						.statementIdx = 132, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("else: ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
					// depth = 1 / argument index = 1: getVariable("$i")
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							auto variableIt = miniScript->scriptState.variables.find(variable);
							if (variableIt == miniScript->scriptState.variables.end()) {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
							} else {
								returnValue = variableIt->second;
							}
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript();
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_133:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 143, 
						.statementIdx = 133, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_134:
				// setVariable("$i", add($i, 1))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 144, 
						.statementIdx = 134, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add($i, 1)
					// depth = 1 / argument index = 1: add($i, 1)
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
						argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
						// depth = 2 / argument index = 0: getVariable("$i")
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript();
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_135:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 145, 
						.statementIdx = 135, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 121
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_121;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_136:
				// setVariable("$i", 1)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 146, 
						.statementIdx = 136, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(1)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_137:
				// setVariable("$j", 2)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 147, 
						.statementIdx = 137, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$j")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_138:
				// setVariable("$k", 3)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 148, 
						.statementIdx = 138, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("$k")));
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(3)));
					string variable;
					if (argumentValues.size() != 2 ||
						MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
						Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
						miniScript->startErrorScript();
					} else {
						miniScript->setVariable(variable, argumentValues[1]);
						returnValue = argumentValues[1];
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_139:
				// if(or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k)))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 149, 
						.statementIdx = 139, 
						.statement = "<unavailable>",
						.gotoStatementIdx = 141
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k))
					// depth = 1 / argument index = 0: or(equals(getVariable("$i"), $j), equals(getVariable("$i"), $k))
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals(getVariable("$i"), $j)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of equals(getVariable("$i"), $k)
						// depth = 2 / argument index = 0: equals(getVariable("$i"), $j)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$j")
							// depth = 3 / argument index = 0: getVariable("$i")
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									auto variableIt = miniScript->scriptState.variables.find(variable);
									if (variableIt == miniScript->scriptState.variables.end()) {
										Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
									} else {
										returnValue = variableIt->second;
									}
								} else {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
									miniScript->startErrorScript();
								}
							}
							// depth = 3 / argument index = 1: getVariable("$j")
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("$j")));
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									auto variableIt = miniScript->scriptState.variables.find(variable);
									if (variableIt == miniScript->scriptState.variables.end()) {
										Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
									} else {
										returnValue = variableIt->second;
									}
								} else {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(true);
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
									returnValue.setValue(false);
									break;
								}
							}
						}
						// depth = 2 / argument index = 1: equals(getVariable("$i"), $k)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$k")
							// depth = 3 / argument index = 0: getVariable("$i")
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									auto variableIt = miniScript->scriptState.variables.find(variable);
									if (variableIt == miniScript->scriptState.variables.end()) {
										Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
									} else {
										returnValue = variableIt->second;
									}
								} else {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
									miniScript->startErrorScript();
								}
							}
							// depth = 3 / argument index = 1: getVariable("$k")
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("$k")));
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									auto variableIt = miniScript->scriptState.variables.find(variable);
									if (variableIt == miniScript->scriptState.variables.end()) {
										Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
									} else {
										returnValue = variableIt->second;
									}
								} else {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(true);
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
									returnValue.setValue(false);
									break;
								}
							}
						}
						returnValue.setValue(false);
						for (auto i = 0; i < argumentValues.size(); i++) {
							bool booleanValue;
							if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
								Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
								miniScript->startErrorScript();
							} else
							if (booleanValue == true) {
								returnValue.setValue(true);
								break;
							}
						}
					}
					bool booleanValue;
					if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
						Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
						miniScript->startErrorScript();
					} else {
						//
						miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
						//
						miniScript->scriptState.conditionStack.push(booleanValue);
						if (booleanValue == false) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
							goto statement_141;
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_140:
				// console.log("This should not happen, but look ok in preprocessor processed output")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 150, 
						.statementIdx = 140, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("This should not happen, but look ok in preprocessor processed output")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_141:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 151, 
						.statementIdx = 141, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_142:
				// console.log("-------------------------------------------------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 152, 
						.statementIdx = 142, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------------------------------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_143:
				// console.log(add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")")))))
				{
					const MiniScript::ScriptStatement statement = {
						.line = 153, 
						.statementIdx = 143, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")"))))
					// depth = 1 / argument index = 0: add("Test: string concatenation with brackets in string literals: ", add($i,add("(",add($j, ")"))))
					{
						ScriptVariable& returnValue = argumentValuesD0[0];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX0 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable(string("Test: string concatenation with brackets in string literals: ")));
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add($i,add("(",add($j, ")")))
						// depth = 2 / argument index = 1: add($i, add("(",add($j, ")")))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$i")
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add("(",add($j, ")"))
							// depth = 3 / argument index = 0: getVariable("$i")
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("$i")));
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									auto variableIt = miniScript->scriptState.variables.find(variable);
									if (variableIt == miniScript->scriptState.variables.end()) {
										Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
									} else {
										returnValue = variableIt->second;
									}
								} else {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
									miniScript->startErrorScript();
								}
							}
							// depth = 3 / argument index = 1: add("(", add($j, ")"))
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(string("(")));
								argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add($j, ")")
								// depth = 4 / argument index = 1: add($j, ")")
								{
									ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
									vector<ScriptVariable> argumentValues;
									vector<ScriptVariable>& argumentValuesD4AIDX1 = argumentValues;
									argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of getVariable("$j")
									argumentValues.push_back(MiniScript::ScriptVariable(string(")")));
									// depth = 5 / argument index = 0: getVariable("$j")
									{
										ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
										vector<ScriptVariable> argumentValues;
										vector<ScriptVariable>& argumentValuesD5AIDX0 = argumentValues;
										argumentValues.push_back(MiniScript::ScriptVariable(string("$j")));
										string variable;
										if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
											auto variableIt = miniScript->scriptState.variables.find(variable);
											if (variableIt == miniScript->scriptState.variables.end()) {
												Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
											} else {
												returnValue = variableIt->second;
											}
										} else {
											Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
											miniScript->startErrorScript();
										}
									}
									if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
										string result;
										for (auto i = 0; i < argumentValues.size(); i++) {
											string stringValue;
											if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
												result+= stringValue;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
												miniScript->startErrorScript();
											}
										}
										returnValue.setValue(result);
									} else
									if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
										Vector3 result;
										for (auto i = 0; i < argumentValues.size(); i++) {
											if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
												Vector3 vec3Value;
												if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
													result+= vec3Value;
												} else {
													Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
													miniScript->startErrorScript();
												}
											} else {
												float floatValue;
												if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
													result+= Vector3(floatValue, floatValue, floatValue);
												} else {
													Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
													miniScript->startErrorScript();
												}
											}
										}
										returnValue.setValue(result);
									} else
									if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
										float result = 0.0f;
										for (auto i = 0; i < argumentValues.size(); i++) {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= floatValue;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
										returnValue.setValue(result);
									} else {
										int64_t result = 0.0f;
										for (auto i = 0; i < argumentValues.size(); i++) {
											int64_t intValue;
											if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
												result+= intValue;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
												miniScript->startErrorScript();
											}
										}
										returnValue.setValue(result);
									}
								}
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
									string result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										string stringValue;
										if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
											result+= stringValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									Vector3 result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result+= vec3Value;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									float result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= floatValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else {
									int64_t result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result+= intValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
								string result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									string stringValue;
									if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
										result+= stringValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								Vector3 result;
								for (auto i = 0; i < argumentValues.size(); i++) {
									if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
											result+= vec3Value;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
											miniScript->startErrorScript();
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
								}
								returnValue.setValue(result);
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								float result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= floatValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							} else {
								int64_t result = 0.0f;
								for (auto i = 0; i < argumentValues.size(); i++) {
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
										result+= intValue;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
										miniScript->startErrorScript();
									}
								}
								returnValue.setValue(result);
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_144:
				// console.log("-------------------------------------------------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 154, 
						.statementIdx = 144, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("-------------------------------------------------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_145:
				// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), " = 17")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 155, 
						.statementIdx = 145, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ")));
					argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5)))
					argumentValues.push_back(MiniScript::ScriptVariable(string(" = 17")));
					// depth = 1 / argument index = 1: add(div(add(4.0, 2.0), 2.0), mul(div(20.0, 10.0), add(2.0, 5)))
					{
						ScriptVariable& returnValue = argumentValuesD0[1];
						vector<ScriptVariable> argumentValues;
						vector<ScriptVariable>& argumentValuesD1AIDX1 = argumentValues;
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(add(4.0, 2.0), 2.0)
						argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of mul(div(20.0, 10.0), add(2.0, 5))
						// depth = 2 / argument index = 0: div(add(4.0, 2.0), 2.0)
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX0 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(4.0, 2.0)
							argumentValues.push_back(MiniScript::ScriptVariable(2.000000f));
							// depth = 3 / argument index = 0: add(4.0, 2.0)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(4.000000f));
								argumentValues.push_back(MiniScript::ScriptVariable(2.000000f));
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
									string result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										string stringValue;
										if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
											result+= stringValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									Vector3 result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result+= vec3Value;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									float result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= floatValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else {
									int64_t result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result+= intValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								auto valid = true;
								Vector3 result;
								if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
										result = vec3Value;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
										miniScript->startErrorScript();
										valid = false;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
										result = Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result/= vec3Value;
											} else {
												Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
												break;
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result/= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
												break;
											}
										}
									}
									returnValue.setValue(result);
								}
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								auto valid = true;
								float result = 0.0f;
								{
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
										result = floatValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result/= floatValue;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
									returnValue.setValue(result);
								}
							} else {
								auto valid = true;
								int64_t result = 0LL;
								{
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
										result = intValue;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result/= intValue;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
											break;
										}
									}
									returnValue.setValue(result);
								}
							}
						}
						// depth = 2 / argument index = 1: mul(div(20.0, 10.0), add(2.0, 5))
						{
							ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
							vector<ScriptVariable> argumentValues;
							vector<ScriptVariable>& argumentValuesD2AIDX1 = argumentValues;
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of div(20.0, 10.0)
							argumentValues.push_back(MiniScript::ScriptVariable()); // returnValue of add(2.0, 5)
							// depth = 3 / argument index = 0: div(20.0, 10.0)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX0 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(20.000000f));
								argumentValues.push_back(MiniScript::ScriptVariable(10.000000f));
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									auto valid = true;
									Vector3 result;
									if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
										Vector3 vec3Value;
										if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
											result = vec3Value;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
											miniScript->startErrorScript();
											valid = false;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
											result = Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
											miniScript->startErrorScript();
											valid = false;
										}
									}
									if (valid == true) {
										for (auto i = 1; i < argumentValues.size(); i++) {
											if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
												Vector3 vec3Value;
												if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
													result/= vec3Value;
												} else {
													Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
													miniScript->startErrorScript();
													break;
												}
											} else {
												float floatValue;
												if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
													result/= Vector3(floatValue, floatValue, floatValue);
												} else {
													Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
													miniScript->startErrorScript();
													break;
												}
											}
										}
										returnValue.setValue(result);
									}
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									auto valid = true;
									float result = 0.0f;
									{
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
											result = floatValue;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
											miniScript->startErrorScript();
											valid = false;
										}
									}
									if (valid == true) {
										for (auto i = 1; i < argumentValues.size(); i++) {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result/= floatValue;
											} else {
												Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
												break;
											}
										}
										returnValue.setValue(result);
									}
								} else {
									auto valid = true;
									int64_t result = 0LL;
									{
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
											result = intValue;
										} else {
											Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
											miniScript->startErrorScript();
											valid = false;
										}
									}
									if (valid == true) {
										for (auto i = 1; i < argumentValues.size(); i++) {
											int64_t intValue;
											if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
												result/= intValue;
											} else {
												Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
												miniScript->startErrorScript();
												break;
											}
										}
										returnValue.setValue(result);
									}
								}
							}
							// depth = 3 / argument index = 1: add(2.0, 5)
							{
								ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
								vector<ScriptVariable> argumentValues;
								vector<ScriptVariable>& argumentValuesD3AIDX1 = argumentValues;
								argumentValues.push_back(MiniScript::ScriptVariable(2.000000f));
								argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(5)));
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
									string result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										string stringValue;
										if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
											result+= stringValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
									Vector3 result;
									for (auto i = 0; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result+= vec3Value;
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result+= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
											}
										}
									}
									returnValue.setValue(result);
								} else
								if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
									float result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result+= floatValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								} else {
									int64_t result = 0.0f;
									for (auto i = 0; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result+= intValue;
										} else {
											Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
										}
									}
									returnValue.setValue(result);
								}
							}
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								auto valid = true;
								Vector3 result;
								if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
										result = vec3Value;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
										miniScript->startErrorScript();
										valid = false;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
										result = Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
											Vector3 vec3Value;
											if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
												result*= vec3Value;
											} else {
												Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
												miniScript->startErrorScript();
												break;
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result*= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript();
												break;
											}
										}
									}
									returnValue.setValue(result);
								}
							} else
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
								auto valid = true;
								float result = 0.0f;
								{
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
										result = floatValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= floatValue;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript();
											break;
										}
									}
									returnValue.setValue(result);
								}
							} else {
								auto valid = true;
								int64_t result = 0LL;
								{
									int64_t intValue;
									if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
										result = intValue;
									} else {
										Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
										miniScript->startErrorScript();
										valid = false;
									}
								}
								if (valid == true) {
									for (auto i = 1; i < argumentValues.size(); i++) {
										int64_t intValue;
										if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
											result*= intValue;
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
											miniScript->startErrorScript();
											break;
										}
									}
									returnValue.setValue(result);
								}
							}
						}
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript();
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript();
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript();
								}
							}
							returnValue.setValue(result);
						}
					}
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_146:
				// console.log("--------------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 156, 
						.statementIdx = 146, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("--------------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_147:
				// console.log("Test if enabled naming condition will be emitted")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 157, 
						.statementIdx = 147, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Test if enabled naming condition will be emitted")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_148:
				// console.log("--------------------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 158, 
						.statementIdx = 148, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("--------------------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_149:
				// script.enableNamedCondition("named_condition_1")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 159, 
						.statementIdx = 149, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("named_condition_1")));
					string name;
					if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
						miniScript->scriptState.enabledConditionNames.erase(
							remove(
								miniScript->scriptState.enabledConditionNames.begin(),
								miniScript->scriptState.enabledConditionNames.end(),
								name
							),
							miniScript->scriptState.enabledConditionNames.end()
						);
						miniScript->scriptState.enabledConditionNames.push_back(name);
					} else {
						Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.enableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript();
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_150:
				// script.wait(2000)
				{
					const MiniScript::ScriptStatement statement = {
						.line = 160, 
						.statementIdx = 150, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(static_cast<int64_t>(2000)));
					int64_t time;
					if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
						miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
						miniScript->scriptState.timeWaitTime = time;
						miniScript->setScriptState(STATE_WAIT);
					} else {
						Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_151:
				// script.disableNamedCondition("named_condition_1")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 161, 
						.statementIdx = 151, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("named_condition_1")));
					string name;
					if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
						miniScript->scriptState.enabledConditionNames.erase(
							remove(
								miniScript->scriptState.enabledConditionNames.begin(),
								miniScript->scriptState.enabledConditionNames.end(),
								name
							),
							miniScript->scriptState.enabledConditionNames.end()
						);
					} else {
						Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript();
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_152:
				// console.log("---------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 162, 
						.statementIdx = 152, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_153:
				// console.log("Naming condition has not been emitted")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 163, 
						.statementIdx = 153, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("Naming condition has not been emitted")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_154:
				// console.log("---------------------------------------")
				{
					const MiniScript::ScriptStatement statement = {
						.line = 164, 
						.statementIdx = 154, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					argumentValues.push_back(MiniScript::ScriptVariable(string("---------------------------------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
statement_155:
				// end()
				{
					const MiniScript::ScriptStatement statement = {
						.line = 165, 
						.statementIdx = 155, 
						.statement = "<unavailable>",
						.gotoStatementIdx = -1
					};
					miniScript->scriptState.statementIdx = statement.statementIdx;
					ScriptVariable returnValue;
					vector<ScriptVariable> argumentValues;
					vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
						}
					}
				}
while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();

	/*__MINISCRIPT_TRANSPILED_NOTHING_END__*/
}
