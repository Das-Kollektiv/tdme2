#include "MiniScriptEmitTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptEmitTest::MiniScriptEmitTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/

#define __MINISCRIPT_TRANSPILATION__

void MiniScriptEmitTest::initializeNative() {
	setNative(true);
	setNativeHash("baee5c30615e5d8deceb2ca92aa43525ecfe6056451ff54981e0bbff70909812");
	setNativeScripts(
		{
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 2,
				.condition = "initialize",
				.executableCondition = "initialize",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 3,
						.statementIdx = 0,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 4,
						.statementIdx = 1,
						.statement = "console.log(\"emit-test: Initialize\")",
						.executableStatement = "console.log(\"emit-test: Initialize\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 5,
						.statementIdx = 2,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 6,
						.statementIdx = 3,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 7,
						.statementIdx = 4,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 10,
				.condition = "nothing",
				.executableCondition = "nothing",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 11,
						.statementIdx = 0,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 12,
						.statementIdx = 1,
						.statement = "console.log(\"emit-test: Nothing\")",
						.executableStatement = "console.log(\"emit-test: Nothing\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 13,
						.statementIdx = 2,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 14,
						.statementIdx = 3,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 15,
						.statementIdx = 4,
						.statement = "console.log(\"--------------------------------------------------\")",
						.executableStatement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "console.log(\"Test if enabled naming condition will be emitted\")",
						.executableStatement = "console.log(\"Test if enabled naming condition will be emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 17,
						.statementIdx = 6,
						.statement = "console.log(\"--------------------------------------------------\")",
						.executableStatement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 18,
						.statementIdx = 7,
						.statement = "script.enableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.enableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 19,
						.statementIdx = 8,
						.statement = "script.wait(2000)",
						.executableStatement = "script.wait(2000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 20,
						.statementIdx = 9,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 10,
						.statement = "console.log(\"---------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 22,
						.statementIdx = 11,
						.statement = "console.log(\"Naming condition has not been emitted\")",
						.executableStatement = "console.log(\"Naming condition has not been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 23,
						.statementIdx = 12,
						.statement = "console.log(\"---------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 24,
						.statementIdx = 13,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 25,
						.statementIdx = 14,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 28,
				.condition = "error",
				.executableCondition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 29,
						.statementIdx = 0,
						.statement = "console.log(\"------------------\")",
						.executableStatement = "console.log(\"------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 30,
						.statementIdx = 1,
						.statement = "console.log(\"emit-test: Error\")",
						.executableStatement = "console.log(\"emit-test: Error\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 2,
						.statement = "console.log(\"------------------\")",
						.executableStatement = "console.log(\"------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 3,
						.statement = "console.log(\"An error occurred\")",
						.executableStatement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 4,
						.statement = "script.wait(1000)",
						.executableStatement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 5,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 37,
				.condition = "emittest",
				.executableCondition = "emittest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 38,
						.statementIdx = 0,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 1,
						.statement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.executableStatement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 2,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 41,
						.statementIdx = 3,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 4,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 5,
						.statement = "console.log(\"Benchmark \")",
						.executableStatement = "console.log(\"Benchmark \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 6,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 7,
						.statement = "$startTime = time.getCurrentMillis()",
						.executableStatement = "setVariable(\"$startTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 8,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 47,
						.statementIdx = 9,
						.statement = "$j = 0",
						.executableStatement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 10,
						.statement = "$k = 0",
						.executableStatement = "setVariable(\"$k\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 11,
						.statement = "forCondition($i < 500000)",
						.executableStatement = "forCondition(lesser($i, 500000))",
						.gotoStatementIdx = 22
					},
					{
						.line = 50,
						.statementIdx = 12,
						.statement = "$a = 123 + 456 * (25 / 12) + (7.5 * 12.25) - 8",
						.executableStatement = "setVariable(\"$a\",sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 13,
						.statement = "if ($j == 0)",
						.executableStatement = "if (equals($j, 0))",
						.gotoStatementIdx = 15
					},
					{
						.line = 52,
						.statementIdx = 14,
						.statement = "$k = $k + 1",
						.executableStatement = "setVariable(\"$k\",add($k, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 15,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 16,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 17,
						.statement = "$j = $j + 1",
						.executableStatement = "setVariable(\"$j\",add($j, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 18,
						.statement = "if ($j == 2)",
						.executableStatement = "if (equals($j, 2))",
						.gotoStatementIdx = 20
					},
					{
						.line = 57,
						.statementIdx = 19,
						.statement = "$j = 0",
						.executableStatement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 20,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 21,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 11
					},
					{
						.line = 60,
						.statementIdx = 22,
						.statement = "$endTime = time.getCurrentMillis()",
						.executableStatement = "setVariable(\"$endTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 23,
						.statement = "console.log(\"Finished. Time: \" + ($endTime - $startTime))",
						.executableStatement = "console.log(add(\"Finished. Time: \", sub($endTime, $startTime)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 24,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 25,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ONENABLED,
				.line = 66,
				.condition = "true == true",
				.executableCondition = "equals(true, true)",
				.name = "named_condition_1",
				.emitCondition = false,
				.statements = {
					{
						.line = 67,
						.statementIdx = 0,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 1,
						.statement = "console.log(\"------------------------------------\")",
						.executableStatement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 2,
						.statement = "console.log(\"named_condition_1 has been emitted\")",
						.executableStatement = "console.log(\"named_condition_1 has been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 70,
						.statementIdx = 3,
						.statement = "console.log(\"------------------------------------\")",
						.executableStatement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 4,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 5,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 6,
						.statement = "console.log(\"Test emit\")",
						.executableStatement = "console.log(\"Test emit\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 74,
						.statementIdx = 7,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 75,
						.statementIdx = 8,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 76,
						.statementIdx = 9,
						.statement = "script.emit(emittest)",
						.executableStatement = "script.emit(emittest)",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 10,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			}
		}
	);
	setNativeScriptFunctions(
		{
		}
	);
}

int MiniScriptEmitTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptEmitTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (auto& enabledNamedCondition: enabledNamedConditions) {

		// next statements belong to tested enabled named condition with name "named_condition_1"
		if (enabledNamedCondition == "named_condition_1")
			// equals(true, true)
			{
				const ScriptStatement statement = {
					.line = 66,
					.statementIdx = 0,
					.statement = "<unavailable>",
					.executableStatement = "<unavailable>",
					.gotoStatementIdx = -1
				};
				getScriptState().statementIdx = statement.statementIdx;
				// required method code arguments
				ScriptVariable returnValue;
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
				argumentValues[0].setValue(true);
				argumentValues[1].setValue(true);
				// method code: equals
				if (argumentValues.size() != 2) {
					Console::println("ScriptMethodEquals::executeMethod(): " + string("equals") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
					miniScript->startErrorScript(); return -1;
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
				bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return 4;
			}
	
	}

	//
	return -1;
}

void MiniScriptEmitTest::emit(const string& condition) {
	if (native == false) {
		MiniScript::emit(condition);
		return;
	}
	if (condition == "initialize") {
		on_initialize(-1);
	} else
	if (condition == "nothing") {
		on_nothing(-1);
	} else
	if (condition == "error") {
		on_error(-1);
	} else
	if (condition == "emittest") {
		on_emittest(-1);
	} else
	{
		Console::println("MiniScriptEmitTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptEmitTest::on_initialize(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("emit-test: Initialize")
	{
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("emit-test: Initialize"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log()
	{
		const ScriptStatement& statement = scripts[0].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 4
	// end()
	{
		const ScriptStatement& statement = scripts[0].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	getScriptState().scriptIdx = SCRIPTIDX_NONE;
	getScriptState().statementIdx = STATEMENTIDX_NONE;
	setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
}

void MiniScriptEmitTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 9) goto miniscript_statement_9; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("emit-test: Nothing")
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("emit-test: Nothing"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log()
	{
		const ScriptStatement& statement = scripts[1].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 4
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 5
	// console.log("Test if enabled naming condition will be emitted")
	{
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Test if enabled naming condition will be emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 6
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 7
	// script.enableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[1].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.enableNamedCondition
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.enableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// enabled named conditions
	{
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != getScriptState().scriptIdx) {
		resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
		timeEnabledConditionsCheckLast = Time::getCurrentMillis();
		return;
		}
	}

	// Statement: 8
	// script.wait(2000)
	{
		const ScriptStatement& statement = scripts[1].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
			miniScript->getScriptState().timeWaitTime = time;
			miniScript->setScriptStateState(STATEMACHINESTATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// enabled named conditions
	{
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != getScriptState().scriptIdx) {
		resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
		timeEnabledConditionsCheckLast = Time::getCurrentMillis();
		return;
		}
	}

	// Statement: 9
	miniscript_statement_9:
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[1].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.disableNamedCondition
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 10
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 11
	// console.log("Naming condition has not been emitted")
	{
		const ScriptStatement& statement = scripts[1].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Naming condition has not been emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 12
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 13
	// script.stop()
	{
		const ScriptStatement& statement = scripts[1].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->stopScriptExecutation();
	}
	if (getScriptState().running == false) {
		return;
	}

	// Statement: 14
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	getScriptState().scriptIdx = SCRIPTIDX_NONE;
	getScriptState().statementIdx = STATEMENTIDX_NONE;
	setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
}

void MiniScriptEmitTest::on_error(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("------------------")
	{
		const ScriptStatement& statement = scripts[2].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("emit-test: Error")
	{
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("emit-test: Error"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("------------------")
	{
		const ScriptStatement& statement = scripts[2].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log("An error occurred")
	{
		const ScriptStatement& statement = scripts[2].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("An error occurred"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 4
	// script.wait(1000)
	{
		const ScriptStatement& statement = scripts[2].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(1000));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
			miniScript->getScriptState().timeWaitTime = time;
			miniScript->setScriptStateState(STATEMACHINESTATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 5
	miniscript_statement_5:
	// end()
	{
		const ScriptStatement& statement = scripts[2].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	getScriptState().scriptIdx = SCRIPTIDX_NONE;
	getScriptState().statementIdx = STATEMENTIDX_NONE;
	setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
}

void MiniScriptEmitTest::on_emittest(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 12) goto miniscript_statement_12; else
	if (miniScriptGotoStatementIdx == 14) goto miniscript_statement_14; else
	if (miniScriptGotoStatementIdx == 16) goto miniscript_statement_16; else
	if (miniScriptGotoStatementIdx == 19) goto miniscript_statement_19; else
	if (miniScriptGotoStatementIdx == 21) goto miniscript_statement_21; else
	if (miniScriptGotoStatementIdx == 22) goto miniscript_statement_22; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_emittest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("---------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("SCRIPT JUST EMITTED A CONDITION")
	{
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("SCRIPT JUST EMITTED A CONDITION"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("---------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log()
	{
		const ScriptStatement& statement = scripts[3].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 4
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[3].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 5
	// console.log("Benchmark ")
	{
		const ScriptStatement& statement = scripts[3].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Benchmark "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 6
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[3].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 7
	// setVariable("$startTime", time.getCurrentMillis())
	{
		const ScriptStatement& statement = scripts[3].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$startTime"));
		// argumentValues[1] --> returnValue of time.getCurrentMillis()
		// depth = 1 / argument index = 1: time.getCurrentMillis()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: time.getCurrentMillis
			returnValue.setValue(Time::getCurrentMillis());
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 8
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(0));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 9
	// setVariable("$j", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$j"));
		argumentValues[1].setValue(static_cast<int64_t>(0));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 10
	// setVariable("$k", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$k"));
		argumentValues[1].setValue(static_cast<int64_t>(0));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 11
	miniscript_statement_11:
	// forCondition(lesser($i, 500000))
	{
		const ScriptStatement& statement = scripts[3].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, 500000)
		// depth = 1 / argument index = 0: lesser($i, 500000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(500000));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_22;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 12
	miniscript_statement_12:
	// setVariable("$a", sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))
	{
		const ScriptStatement& statement = scripts[3].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$a"));
		// argumentValues[1] --> returnValue of sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8)
		// depth = 1 / argument index = 1: sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25)))
			argumentValues[1].setValue(static_cast<int64_t>(8));
			// depth = 2 / argument index = 0: add(123, add(mul(456,div(25, 12)),mul(7.5, 12.25)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(123));
				// argumentValues[1] --> returnValue of add(mul(456,div(25, 12)),mul(7.5, 12.25))
				// depth = 3 / argument index = 1: add(mul(456,div(25, 12)), mul(7.5, 12.25))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of mul(456,div(25, 12))
					// argumentValues[1] --> returnValue of mul(7.5, 12.25)
					// depth = 4 / argument index = 0: mul(456, div(25, 12))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(static_cast<int64_t>(456));
						// argumentValues[1] --> returnValue of div(25, 12)
						// depth = 5 / argument index = 1: div(25, 12)
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX0[1];
							array<ScriptVariable, 2> argumentValues;
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							argumentValues[0].setValue(static_cast<int64_t>(25));
							argumentValues[1].setValue(static_cast<int64_t>(12));
							// method code: div
							MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
						}
						// method code: mul
						MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
					}
					// depth = 4 / argument index = 1: mul(7.5, 12.25)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						argumentValues[0].setValue(7.500000f);
						argumentValues[1].setValue(12.250000f);
						// method code: mul
						MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
					}
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 13
	// if(equals($j, 0))
	{
		const ScriptStatement& statement = scripts[3].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($j, 0)
		// depth = 1 / argument index = 0: equals($j, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$j")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$j")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$j"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodEquals::executeMethod(): " + string("equals") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->getScriptState().conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_15;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 14
	miniscript_statement_14:
	// setVariable("$k", add($k, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$k"));
		// argumentValues[1] --> returnValue of add($k, 1)
		// depth = 1 / argument index = 1: add($k, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$k")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$k")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$k"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 15
	miniscript_statement_15:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 16
	miniscript_statement_16:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[16];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		// argumentValues[1] --> returnValue of add($i, 1)
		// depth = 1 / argument index = 1: add($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 17
	// setVariable("$j", add($j, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$j"));
		// argumentValues[1] --> returnValue of add($j, 1)
		// depth = 1 / argument index = 1: add($j, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$j")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$j")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$j"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 18
	// if(equals($j, 2))
	{
		const ScriptStatement& statement = scripts[3].statements[18];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($j, 2)
		// depth = 1 / argument index = 0: equals($j, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$j")
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: getVariable("$j")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$j"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodEquals::executeMethod(): " + string("equals") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->getScriptState().conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_20;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 19
	miniscript_statement_19:
	// setVariable("$j", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$j"));
		argumentValues[1].setValue(static_cast<int64_t>(0));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 20
	miniscript_statement_20:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[20];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 21
	miniscript_statement_21:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[21];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_11;
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 22
	miniscript_statement_22:
	// setVariable("$endTime", time.getCurrentMillis())
	{
		const ScriptStatement& statement = scripts[3].statements[22];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$endTime"));
		// argumentValues[1] --> returnValue of time.getCurrentMillis()
		// depth = 1 / argument index = 1: time.getCurrentMillis()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: time.getCurrentMillis
			returnValue.setValue(Time::getCurrentMillis());
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 23
	// console.log(add("Finished. Time: ", sub($endTime, $startTime)))
	{
		const ScriptStatement& statement = scripts[3].statements[23];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("Finished. Time: ", sub($endTime, $startTime))
		// depth = 1 / argument index = 0: add("Finished. Time: ", sub($endTime, $startTime))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("Finished. Time: "));
			// argumentValues[1] --> returnValue of sub($endTime, $startTime)
			// depth = 2 / argument index = 1: sub($endTime, $startTime)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$endTime")
				// argumentValues[1] --> returnValue of getVariable("$startTime")
				// depth = 3 / argument index = 0: getVariable("$endTime")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$endTime"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: getVariable("$startTime")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$startTime"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: sub
				MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 24
	// script.stop()
	{
		const ScriptStatement& statement = scripts[3].statements[24];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->stopScriptExecutation();
	}
	if (getScriptState().running == false) {
		return;
	}

	// Statement: 25
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[25];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	getScriptState().scriptIdx = SCRIPTIDX_NONE;
	getScriptState().statementIdx = STATEMENTIDX_NONE;
	setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
}

void MiniScriptEmitTest::on_enabled_named_condition_1(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_enabled_named_condition_1(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[4].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.disableNamedCondition
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 1
	// console.log("------------------------------------")
	{
		const ScriptStatement& statement = scripts[4].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("named_condition_1 has been emitted")
	{
		const ScriptStatement& statement = scripts[4].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1 has been emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log("------------------------------------")
	{
		const ScriptStatement& statement = scripts[4].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 4
	// console.log()
	{
		const ScriptStatement& statement = scripts[4].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 5
	// console.log("-----------")
	{
		const ScriptStatement& statement = scripts[4].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 6
	// console.log("Test emit")
	{
		const ScriptStatement& statement = scripts[4].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Test emit"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 7
	// console.log("-----------")
	{
		const ScriptStatement& statement = scripts[4].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 8
	// console.log()
	{
		const ScriptStatement& statement = scripts[4].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 9
	// script.emit(emittest)
	{
		const ScriptStatement& statement = scripts[4].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("emittest"));
		// method code: script.emit
		string condition;
		if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
			miniScript->emit(condition); return;
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.emit") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 10
	// end()
	{
		const ScriptStatement& statement = scripts[4].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			if (miniScript->getScriptState().statementIdx < miniScript->scripts[miniScript->getScriptState().scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
			} else
			if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
				miniScript->stopRunning();
			}
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMACHINESTATE_NONE) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
			}
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	getScriptState().scriptIdx = SCRIPTIDX_NONE;
	getScriptState().statementIdx = STATEMENTIDX_NONE;
	setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
}


/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
