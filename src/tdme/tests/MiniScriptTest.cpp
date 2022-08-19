#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

MiniScriptTest::MiniScriptTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/
void MiniScriptTest::initializeNative() {
	setNative(true);
	setHash("b56fb2ced490fe799dbb288252b3416941fd0072b7f78d76fb84369306c39383");
	setNativeScripts(
		{
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 2,
				.condition = "initialize",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 3,
						.statementIdx = 0,
						.statement = "console.log(\"------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 4,
						.statementIdx = 1,
						.statement = "console.log(\"Initialize\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 5,
						.statementIdx = 2,
						.statement = "console.log(\"------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 6,
						.statementIdx = 3,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 7,
						.statementIdx = 4,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 10,
				.condition = "nothing",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 11,
						.statementIdx = 0,
						.statement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 12,
						.statementIdx = 1,
						.statement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 13,
						.statementIdx = 2,
						.statement = "console.log(\"Arrays\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 14,
						.statementIdx = 3,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 15,
						.statementIdx = 4,
						.statement = "setVariable(\"$array\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 17,
						.statementIdx = 6,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 18,
						.statementIdx = 7,
						.statement = "setVariable(\"$array\", array.push($array, 8, 9, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 19,
						.statementIdx = 8,
						.statement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 20,
						.statementIdx = 9,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 10,
						.statement = "setVariable(\"$array[]\", 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 22,
						.statementIdx = 11,
						.statement = "setVariable(\"$array[]\", 1234)",
						.gotoStatementIdx = -1
					},
					{
						.line = 23,
						.statementIdx = 12,
						.statement = "setVariable(\"$array[]\", 12345)",
						.gotoStatementIdx = -1
					},
					{
						.line = 24,
						.statementIdx = 13,
						.statement = "console.log(\"array values added with [] operator: 123, 1234, 12345\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 25,
						.statementIdx = 14,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 15,
						.statement = "console.log(\"array length: \", array.length($array))",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 16,
						.statement = "console.log(\"array iteration with array.get(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 17,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 29,
						.statementIdx = 18,
						.statement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 22
					},
					{
						.line = 30,
						.statementIdx = 19,
						.statement = "console.log(add($i,add(\": \", array.get($array, $i))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 20,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 21,
						.statement = "end",
						.gotoStatementIdx = 18
					},
					{
						.line = 33,
						.statementIdx = 22,
						.statement = "console.log(\"array iteration with [] operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 23,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 35,
						.statementIdx = 24,
						.statement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 28
					},
					{
						.line = 36,
						.statementIdx = 25,
						.statement = "console.log(add($i,add(\": \", array.get($array, $i))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 37,
						.statementIdx = 26,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 38,
						.statementIdx = 27,
						.statement = "end",
						.gotoStatementIdx = 24
					},
					{
						.line = 39,
						.statementIdx = 28,
						.statement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 29,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 42,
				.condition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 43,
						.statementIdx = 0,
						.statement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 1,
						.statement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 2,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 47,
				.condition = "emittest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 48,
						.statementIdx = 0,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 1,
						.statement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 50,
						.statementIdx = 2,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 3,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 4,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 5,
						.statement = "console.log(\"Benchmark \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 6,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 7,
						.statement = "setVariable(\"$startTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 8,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 57,
						.statementIdx = 9,
						.statement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 10,
						.statement = "setVariable(\"$k\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 11,
						.statement = "forCondition(lesser($i, 500000))",
						.gotoStatementIdx = 22
					},
					{
						.line = 60,
						.statementIdx = 12,
						.statement = "setVariable(\"$a\",sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 13,
						.statement = "if (equals($j, 0))",
						.gotoStatementIdx = 15
					},
					{
						.line = 62,
						.statementIdx = 14,
						.statement = "setVariable(\"$k\",add($k, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 15,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 64,
						.statementIdx = 16,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 65,
						.statementIdx = 17,
						.statement = "setVariable(\"$j\",add($j, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 66,
						.statementIdx = 18,
						.statement = "if (equals($j, 2))",
						.gotoStatementIdx = 20
					},
					{
						.line = 67,
						.statementIdx = 19,
						.statement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 20,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 21,
						.statement = "end",
						.gotoStatementIdx = 11
					},
					{
						.line = 70,
						.statementIdx = 22,
						.statement = "setVariable(\"$endTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 23,
						.statement = "console.log(add(\"Finished. Time: \", sub($endTime, $startTime)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 24,
						.statement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 25,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ONENABLED,
				.line = 75,
				.condition = "equals(1,1)",
				.name = "named_condition_1",
				.emitCondition = false,
				.statements = {
					{
						.line = 76,
						.statementIdx = 0,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 1,
						.statement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 78,
						.statementIdx = 2,
						.statement = "console.log(\"named_condition_1 has been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 79,
						.statementIdx = 3,
						.statement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 80,
						.statementIdx = 4,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 81,
						.statementIdx = 5,
						.statement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 82,
						.statementIdx = 6,
						.statement = "console.log(\"Test emit\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 83,
						.statementIdx = 7,
						.statement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 84,
						.statementIdx = 8,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 85,
						.statementIdx = 9,
						.statement = "script.emit(emittest)",
						.gotoStatementIdx = -1
					},
					{
						.line = 86,
						.statementIdx = 10,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			}
		}
	);
}

int MiniScriptTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (auto& enabledNamedCondition: scriptState.enabledNamedConditions) {

		// next statements belong to tested enabled named condition with name "named_condition_1"
		if (enabledNamedCondition == "named_condition_1")
			// equals(1, 1)
			{
				const ScriptStatement statement = {
					.line = 75,
					.statementIdx = 0,
					.statement = "<unavailable>",
					.gotoStatementIdx = -1
				};
				miniScript->scriptState.statementIdx = statement.statementIdx;
				// required method code arguments
				ScriptVariable returnValue;
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				// method code: equals
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
				bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return 4;
			}
	
	}

	//
	return -1;
}

void MiniScriptTest::emit(const string& condition) {
	if (native == false) {
		MiniScript::emit(condition);
		return;
	}
	if (condition == "initialize") {
		on_initialize(-1);
		return;
	}
	if (condition == "nothing") {
		on_nothing(-1);
		return;
	}
	if (condition == "error") {
		on_error(-1);
		return;
	}
	if (condition == "emittest") {
		on_emittest(-1);
		return;
	}
}

void MiniScriptTest::on_initialize(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(0, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 0;
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("------------")
	{
		const ScriptStatement& statement = scripts[0].statements[0];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("Initialize")
	{
		const ScriptStatement& statement = scripts[0].statements[1];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Initialize"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("------------")
	{
		const ScriptStatement& statement = scripts[0].statements[2];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------"));
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(1, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 19) goto miniscript_statement_19; else
	if (miniScriptGotoStatementIdx == 22) goto miniscript_statement_22; else
	if (miniScriptGotoStatementIdx == 25) goto miniscript_statement_25; else
	if (miniScriptGotoStatementIdx == 28) goto miniscript_statement_28; else
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[0];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("Arrays")
	{
		const ScriptStatement& statement = scripts[1].statements[2];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Arrays"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[1].statements[3];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 4
	// setVariable("$array", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[4];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array(1,2,3)
		// depth = 1 / argument index = 1: array(1, 2, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(1));
			argumentValues[1].setValue(static_cast<int64_t>(2));
			argumentValues[2].setValue(static_cast<int64_t>(3));
			// method code: array
			for (auto& argumentValue: argumentValues) {
				returnValue.pushArrayValue(argumentValue);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 5
	// console.log("array initialized with: $array = array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[1].statements[5];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array initialized with: $array = array(1,2,3)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 6
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[6];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$array")
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 7
	// setVariable("$array", array.push($array, 8, 9, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[7];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array.push($array, 8, 9, 10)
		// depth = 1 / argument index = 1: array.push($array, 8, 9, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 4> argumentValues;
			array<ScriptVariable, 4>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(8));
			argumentValues[2].setValue(static_cast<int64_t>(9));
			argumentValues[3].setValue(static_cast<int64_t>(10));
			// depth = 2 / argument index = 0: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$array"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: array.push
			//
			if (argumentValues.size() < 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
				Console::println("ScriptMethodArrayPush::executeMethod(): " + string("array.push") + "(): parameter type mismatch @ argument 0: array expected");
			} else {
				returnValue = argumentValues[0];
				for (auto i = 1; i < argumentValues.size(); i++) {
					returnValue.pushArrayValue(argumentValues[i]);
				}
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 8
	// console.log("array pushed values with: array.push($array, 8, 9, 10)")
	{
		const ScriptStatement& statement = scripts[1].statements[8];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array pushed values with: array.push($array, 8, 9, 10)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 9
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[9];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$array")
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 10
	// setVariable("$array[]", 123)
	{
		const ScriptStatement& statement = scripts[1].statements[10];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[]"));
		argumentValues[1].setValue(static_cast<int64_t>(123));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 11
	// setVariable("$array[]", 1234)
	{
		const ScriptStatement& statement = scripts[1].statements[11];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[]"));
		argumentValues[1].setValue(static_cast<int64_t>(1234));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 12
	// setVariable("$array[]", 12345)
	{
		const ScriptStatement& statement = scripts[1].statements[12];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[]"));
		argumentValues[1].setValue(static_cast<int64_t>(12345));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 13
	// console.log("array values added with [] operator: 123, 1234, 12345")
	{
		const ScriptStatement& statement = scripts[1].statements[13];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array values added with [] operator: 123, 1234, 12345"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 14
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[14];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$array")
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 15
	// console.log("array length: ", array.length($array))
	{
		const ScriptStatement& statement = scripts[1].statements[15];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array length: "));
		// argumentValues[1] --> returnValue of array.length($array)
		// depth = 1 / argument index = 1: array.length($array)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			// depth = 2 / argument index = 0: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$array"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: array.length
			if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
				Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): parameter type mismatch @ argument 0: array expected");
			} else {
				returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 16
	// console.log("array iteration with array.get(): ")
	{
		const ScriptStatement& statement = scripts[1].statements[16];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array iteration with array.get(): "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 17
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[17];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 18
	miniscript_statement_18:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[1].statements[18];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, array.length($array))
		// depth = 1 / argument index = 0: lesser($i, array.length($array))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of array.length($array)
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: array.length($array)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$array")
				// depth = 3 / argument index = 0: getVariable("$array")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$array"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: array.length
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): parameter type mismatch @ argument 0: array expected");
				} else {
					returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
				}
			}
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_22;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 19
	miniscript_statement_19:
	// console.log(add($i,add(": ", array.get($array, $i))))
	{
		const ScriptStatement& statement = scripts[1].statements[19];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($i,add(": ", array.get($array, $i)))
		// depth = 1 / argument index = 0: add($i, add(": ", array.get($array, $i)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of add(": ", array.get($array, $i))
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: add(": ", array.get($array, $i))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(": "));
				// argumentValues[1] --> returnValue of array.get($array, $i)
				// depth = 3 / argument index = 1: array.get($array, $i)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$array")
					// argumentValues[1] --> returnValue of getVariable("$i")
					// depth = 4 / argument index = 0: getVariable("$array")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(string("$array"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// depth = 4 / argument index = 1: getVariable("$i")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX1 = argumentValues;
						argumentValues[0].setValue(string("$i"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: array.get
					int64_t index;
					if ((argumentValues.size() <= 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
						MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
						Console::println("ScriptMethodArrayGet::executeMethod(): " + string("array.get") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: integer expected");
					} else {
						returnValue = argumentValues[0].getArrayValue(index);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 20
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[20];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 21
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[21];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_18;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 22
	miniscript_statement_22:
	// console.log("array iteration with [] operator: ")
	{
		const ScriptStatement& statement = scripts[1].statements[22];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array iteration with [] operator: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 23
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[23];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 24
	miniscript_statement_24:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[1].statements[24];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, array.length($array))
		// depth = 1 / argument index = 0: lesser($i, array.length($array))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of array.length($array)
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: array.length($array)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$array")
				// depth = 3 / argument index = 0: getVariable("$array")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$array"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: array.length
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): parameter type mismatch @ argument 0: array expected");
				} else {
					returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
				}
			}
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_28;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 25
	miniscript_statement_25:
	// console.log(add($i,add(": ", array.get($array, $i))))
	{
		const ScriptStatement& statement = scripts[1].statements[25];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($i,add(": ", array.get($array, $i)))
		// depth = 1 / argument index = 0: add($i, add(": ", array.get($array, $i)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of add(": ", array.get($array, $i))
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: add(": ", array.get($array, $i))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(": "));
				// argumentValues[1] --> returnValue of array.get($array, $i)
				// depth = 3 / argument index = 1: array.get($array, $i)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$array")
					// argumentValues[1] --> returnValue of getVariable("$i")
					// depth = 4 / argument index = 0: getVariable("$array")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(string("$array"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// depth = 4 / argument index = 1: getVariable("$i")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX1 = argumentValues;
						argumentValues[0].setValue(string("$i"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: array.get
					int64_t index;
					if ((argumentValues.size() <= 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
						MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
						Console::println("ScriptMethodArrayGet::executeMethod(): " + string("array.get") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: integer expected");
					} else {
						returnValue = argumentValues[0].getArrayValue(index);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 26
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[26];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 27
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[27];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_24;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 28
	miniscript_statement_28:
	// script.stop()
	{
		const ScriptStatement& statement = scripts[1].statements[28];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->stopScriptExecutation();
	}
	if (scriptState.running == false) {
		return;
	}

	// Statement: 29
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[29];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_error(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(2, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 2) goto miniscript_statement_2; else
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("An error occurred")
	{
		const ScriptStatement& statement = scripts[2].statements[0];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 1
	// script.wait(1000)
	{
		const ScriptStatement& statement = scripts[2].statements[1];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(1000));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
			miniScript->scriptState.timeWaitTime = time;
			miniScript->setScriptState(STATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 2
	miniscript_statement_2:
	// end()
	{
		const ScriptStatement& statement = scripts[2].statements[2];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_emittest(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(3, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 12) goto miniscript_statement_12; else
	if (miniScriptGotoStatementIdx == 14) goto miniscript_statement_14; else
	if (miniScriptGotoStatementIdx == 16) goto miniscript_statement_16; else
	if (miniScriptGotoStatementIdx == 19) goto miniscript_statement_19; else
	if (miniScriptGotoStatementIdx == 21) goto miniscript_statement_21; else
	if (miniScriptGotoStatementIdx == 22) goto miniscript_statement_22; else
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_emittest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("---------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[0];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_22;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 12
	miniscript_statement_12:
	// setVariable("$a", sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))
	{
		const ScriptStatement& statement = scripts[3].statements[12];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
							if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
								auto valid = true;
								Vector3 result;
								if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
										result = vec3Value;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
										miniScript->startErrorScript(); return;
										valid = false;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
										result = Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
										miniScript->startErrorScript(); return;
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
												miniScript->startErrorScript(); return;
												break;
											}
										} else {
											float floatValue;
											if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
												result/= Vector3(floatValue, floatValue, floatValue);
											} else {
												Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
												miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
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
											miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
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
											miniScript->startErrorScript(); return;
											break;
										}
									}
									returnValue.setValue(result);
								}
							}
						}
						// method code: mul
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript(); return;
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript(); return;
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
											miniScript->startErrorScript(); return;
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript(); return;
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
									miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
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
									miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
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
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							auto valid = true;
							Vector3 result;
							if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
									result = vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
									miniScript->startErrorScript(); return;
									valid = false;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
									result = Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
									miniScript->startErrorScript(); return;
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
											miniScript->startErrorScript(); return;
											break;
										}
									} else {
										float floatValue;
										if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
											result*= Vector3(floatValue, floatValue, floatValue);
										} else {
											Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
											miniScript->startErrorScript(); return;
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
									miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
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
									miniScript->startErrorScript(); return;
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
										miniScript->startErrorScript(); return;
										break;
									}
								}
								returnValue.setValue(result);
							}
						}
					}
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
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
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_15;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 14
	miniscript_statement_14:
	// setVariable("$k", add($k, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[14];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 16
	miniscript_statement_16:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[16];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_20;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 19
	miniscript_statement_19:
	// setVariable("$j", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[19];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 21
	miniscript_statement_21:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[21];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_11;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 22
	miniscript_statement_22:
	// setVariable("$endTime", time.getCurrentMillis())
	{
		const ScriptStatement& statement = scripts[3].statements[22];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: sub
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result-= vec3Value;
							} else {
								Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result-= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
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
								miniScript->startErrorScript(); return;
								break;
							}
						}
						returnValue.setValue(result);
					}
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
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
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
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
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->stopScriptExecutation();
	}
	if (scriptState.running == false) {
		return;
	}

	// Statement: 25
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[25];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_enabled_named_condition_1(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(4, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 4;
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_enabled_named_condition_1(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[4].statements[0];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.disableNamedCondition
		string name;
		if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
			miniScript->scriptState.enabledNamedConditions.erase(
				remove(
					miniScript->scriptState.enabledNamedConditions.begin(),
					miniScript->scriptState.enabledNamedConditions.end(),
					name
				),
				miniScript->scriptState.enabledNamedConditions.end()
			);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 1
	// console.log("------------------------------------")
	{
		const ScriptStatement& statement = scripts[4].statements[1];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.emit") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 10
	// end()
	{
		const ScriptStatement& statement = scripts[4].statements[10];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}


/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
