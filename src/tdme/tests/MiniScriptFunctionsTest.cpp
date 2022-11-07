#include "MiniScriptFunctionsTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptFunctionsTest::MiniScriptFunctionsTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/

#define __MINISCRIPT_TRANSPILATION__

void MiniScriptFunctionsTest::initializeNative() {
	setNative(true);
	setNativeHash("b35432b960ca4756754ad71d27db32ff22dc77d9c8d43a81ed8d6699466a2684");
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
						.statement = "console.log(\"----------------------------\")",
						.executableStatement = "console.log(\"----------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 4,
						.statementIdx = 1,
						.statement = "console.log(\"functions-test: Initialize\")",
						.executableStatement = "console.log(\"functions-test: Initialize\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 5,
						.statementIdx = 2,
						.statement = "console.log(\"----------------------------\")",
						.executableStatement = "console.log(\"----------------------------\")",
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
				.scriptType = Script::SCRIPTTYPE_FUNCTION,
				.line = 10,
				.condition = "factorial",
				.executableCondition = "factorial",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 11,
						.statementIdx = 0,
						.statement = "console.log(\"factorial(): $arguments = \" + $arguments + \" / $value = \" + $value)",
						.executableStatement = "console.log(add(\"factorial(): $arguments = \",add($arguments,add(\" / $value = \", $value))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 12,
						.statementIdx = 1,
						.statement = "if ($value == 0)",
						.executableStatement = "if (equals($value, 0))",
						.gotoStatementIdx = 3
					},
					{
						.line = 13,
						.statementIdx = 2,
						.statement = "return(1)",
						.executableStatement = "return(1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 14,
						.statementIdx = 3,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 15,
						.statementIdx = 4,
						.statement = "return($value * factorial($value - 1))",
						.executableStatement = "return(mul($value, factorial(sub($value, 1))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
					{
						.name = "$value",
						.assignBack = false
					}
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_FUNCTION,
				.line = 19,
				.condition = "helloWorldFunction",
				.executableCondition = "helloWorldFunction",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 20,
						.statementIdx = 0,
						.statement = "console.log(\"helloWorldFunction(): Hello world\")",
						.executableStatement = "console.log(\"helloWorldFunction(): Hello world\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 1,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_FUNCTION,
				.line = 24,
				.condition = "assignTest",
				.executableCondition = "assignTest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 25,
						.statementIdx = 0,
						.statement = "$a = \"a\"",
						.executableStatement = "setVariable(\"$a\", \"a\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 1,
						.statement = "$b = \"b\"",
						.executableStatement = "setVariable(\"$b\", \"b\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 2,
						.statement = "$c = \"c\"",
						.executableStatement = "setVariable(\"$c\", \"c\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 3,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.arguments = {
					{
						.name = "$a",
						.assignBack = false
					},
					{
						.name = "$b",
						.assignBack = true
					},
					{
						.name = "$c",
						.assignBack = true
					}
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_FUNCTION,
				.line = 31,
				.condition = "globalVariableTest",
				.executableCondition = "globalVariableTest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 32,
						.statementIdx = 0,
						.statement = "console.log(\"globalVariableTest(): $GLOBAL.globalTest = \" + $GLOBAL.globalTest)",
						.executableStatement = "console.log(add(\"globalVariableTest(): $GLOBAL.globalTest = \", $GLOBAL.globalTest))",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 1,
						.statement = "$GLOBAL.globalTest = \"Been there, done that, got the t-shirt\"",
						.executableStatement = "setVariable(\"$GLOBAL.globalTest\", \"Been there, done that, got the t-shirt\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 2,
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
				.condition = "nothing",
				.executableCondition = "nothing",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 38,
						.statementIdx = 0,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 1,
						.statement = "console.log(\"functions-test: Nothing\")",
						.executableStatement = "console.log(\"functions-test: Nothing\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 2,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 41,
						.statementIdx = 3,
						.statement = "helloWorldFunction()",
						.executableStatement = "helloWorldFunction()",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 4,
						.statement = "console.log(\"factorial(5) = \" + factorial(5))",
						.executableStatement = "console.log(add(\"factorial(5) = \", factorial(5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 5,
						.statement = "$a = \"0\"",
						.executableStatement = "setVariable(\"$a\", \"0\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 6,
						.statement = "$b = \"1\"",
						.executableStatement = "setVariable(\"$b\", \"1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 7,
						.statement = "$c = \"2\"",
						.executableStatement = "setVariable(\"$c\", \"2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 8,
						.statement = "console.log(\"assignTest(): pre: $a = \" + $a + \", $b = \" + $b + \", $c = \" + $c)",
						.executableStatement = "console.log(add(\"assignTest(): pre: $a = \",add($a,add(\", $b = \",add($b,add(\", $c = \", $c))))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 47,
						.statementIdx = 9,
						.statement = "assignTest($a, $b, $c)",
						.executableStatement = "assignTest($a, $b, $c)",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 10,
						.statement = "console.log(\"assignTest(): post: $a = \" + $a + \", $b = \" + $b + \", $c = \" + $c)",
						.executableStatement = "console.log(add(\"assignTest(): post: $a = \",add($a,add(\", $b = \",add($b,add(\", $c = \", $c))))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 11,
						.statement = "$globalTest = \"Global Test Variable\"",
						.executableStatement = "setVariable(\"$globalTest\", \"Global Test Variable\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 50,
						.statementIdx = 12,
						.statement = "console.log(\"globalVariableTest(): pre: $globalTest = \" + $globalTest)",
						.executableStatement = "console.log(add(\"globalVariableTest(): pre: $globalTest = \", $globalTest))",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 13,
						.statement = "globalVariableTest()",
						.executableStatement = "globalVariableTest()",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 14,
						.statement = "console.log(\"globalVariableTest(): post: $globalTest = \" + $globalTest)",
						.executableStatement = "console.log(add(\"globalVariableTest(): post: $globalTest = \", $globalTest))",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 15,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 16,
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
				.line = 57,
				.condition = "error",
				.executableCondition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 58,
						.statementIdx = 0,
						.statement = "console.log(\"----------------------\")",
						.executableStatement = "console.log(\"----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 1,
						.statement = "console.log(\"functions-test: Error\")",
						.executableStatement = "console.log(\"functions-test: Error\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 60,
						.statementIdx = 2,
						.statement = "console.log(\"----------------------\")",
						.executableStatement = "console.log(\"----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 3,
						.statement = "console.log(\"An error occurred\")",
						.executableStatement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 4,
						.statement = "script.wait(1000)",
						.executableStatement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 5,
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
			{
				"globalVariableTest",
				4
			},
			{
				"assignTest",
				3
			},
			{
				"helloWorldFunction",
				2
			},
			{
				"factorial",
				1
			}
		}
	);
}

int MiniScriptFunctionsTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 5;
}

int MiniScriptFunctionsTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return -1;
}

void MiniScriptFunctionsTest::emit(const string& condition) {
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
	{
		Console::println("MiniScriptFunctionsTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptFunctionsTest::on_initialize(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("----------------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("functions-test: Initialize")
	{
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("functions-test: Initialize"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("----------------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------------------------"));
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

void MiniScriptFunctionsTest::factorial(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 2) goto miniscript_statement_2; else
	if (miniScriptGotoStatementIdx == 4) goto miniscript_statement_4; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::factorial(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log(add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))))
	{
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value"))))
		// depth = 1 / argument index = 0: add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("factorial(): $arguments = "));
			// argumentValues[1] --> returnValue of add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))
			// depth = 2 / argument index = 1: add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$arguments")
				// argumentValues[1] --> returnValue of add(" / $value = ", getVariable("$value"))
				// depth = 3 / argument index = 0: getVariable("$arguments")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$arguments"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(" / $value = ", getVariable("$value"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string(" / $value = "));
					// argumentValues[1] --> returnValue of getVariable("$value")
					// depth = 4 / argument index = 1: getVariable("$value")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX1 = argumentValues;
						argumentValues[0].setValue(string("$value"));
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
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
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

	// Statement: 1
	// if(equals(getVariable("$value"), 0))
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals(getVariable("$value"), 0)
		// depth = 1 / argument index = 0: equals(getVariable("$value"), 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$value")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$value")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$value"));
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
				goto miniscript_statement_3;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 2
	miniscript_statement_2:
	// return(1)
	{
		const ScriptStatement& statement = scripts[1].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(1));
		// method code: return
		if (miniScript->isFunctionRunning() == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected");
		}
	}
	if (getScriptState().running == false) {
		return;
	}

	// Statement: 3
	miniscript_statement_3:
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[3];
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

	// Statement: 4
	miniscript_statement_4:
	// return(mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1))))
	{
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1)))
		// depth = 1 / argument index = 0: mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$value")
			// argumentValues[1] --> returnValue of factorial(sub(getVariable("$value"), 1))
			// depth = 2 / argument index = 0: getVariable("$value")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$value"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: script.call("factorial", sub(getVariable("$value"), 1))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("factorial"));
				// argumentValues[1] --> returnValue of sub(getVariable("$value"), 1)
				// depth = 3 / argument index = 1: sub(getVariable("$value"), 1)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$value")
					argumentValues[1].setValue(static_cast<int64_t>(1));
					// depth = 4 / argument index = 0: getVariable("$value")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(string("$value"));
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
				// method code: script.call
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							// so we need to make a copy of argumentValues beginning from second element
							vector<ScriptVariable> callArgumentValues;
							for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#else
							span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#endif
					}
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: return
		if (miniScript->isFunctionRunning() == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected");
		}
	}
	if (getScriptState().running == false) {
		return;
	}

	// Statement: 5
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[5];
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

void MiniScriptFunctionsTest::helloWorldFunction(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::helloWorldFunction(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("helloWorldFunction(): Hello world")
	{
		const ScriptStatement& statement = scripts[2].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("helloWorldFunction(): Hello world"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// end()
	{
		const ScriptStatement& statement = scripts[2].statements[1];
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

void MiniScriptFunctionsTest::assignTest(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::assignTest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// setVariable("$a", "a")
	{
		const ScriptStatement& statement = scripts[3].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$a"));
		argumentValues[1].setValue(string("a"));
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

	// Statement: 1
	// setVariable("$b", "b")
	{
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$b"));
		argumentValues[1].setValue(string("b"));
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

	// Statement: 2
	// setVariable("$c", "c")
	{
		const ScriptStatement& statement = scripts[3].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$c"));
		argumentValues[1].setValue(string("c"));
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

	// Statement: 3
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[3];
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

void MiniScriptFunctionsTest::globalVariableTest(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::globalVariableTest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log(add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest")))
	{
		const ScriptStatement& statement = scripts[4].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest"))
		// depth = 1 / argument index = 0: add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("globalVariableTest(): $GLOBAL.globalTest = "));
			// argumentValues[1] --> returnValue of getVariable("$GLOBAL.globalTest")
			// depth = 2 / argument index = 1: getVariable("$GLOBAL.globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("$GLOBAL.globalTest"));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// setVariable("$GLOBAL.globalTest", "Been there, done that, got the t-shirt")
	{
		const ScriptStatement& statement = scripts[4].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$GLOBAL.globalTest"));
		argumentValues[1].setValue(string("Been there, done that, got the t-shirt"));
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

	// Statement: 2
	// end()
	{
		const ScriptStatement& statement = scripts[4].statements[2];
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

void MiniScriptFunctionsTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(5, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 5;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[5].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("functions-test: Nothing")
	{
		const ScriptStatement& statement = scripts[5].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("functions-test: Nothing"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[5].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// script.call("helloWorldFunction")
	{
		const ScriptStatement& statement = scripts[5].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("helloWorldFunction"));
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					// so we need to make a copy of argumentValues beginning from second element
					vector<ScriptVariable> callArgumentValues;
					for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
					// call
					span callArgumentValuesSpan(callArgumentValues);
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#else
					span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#endif
			}
		}
	}

	// Statement: 4
	// console.log(add("factorial(5) = ", factorial(5)))
	{
		const ScriptStatement& statement = scripts[5].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("factorial(5) = ", factorial(5))
		// depth = 1 / argument index = 0: add("factorial(5) = ", factorial(5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("factorial(5) = "));
			// argumentValues[1] --> returnValue of factorial(5)
			// depth = 2 / argument index = 1: script.call("factorial", 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("factorial"));
				argumentValues[1].setValue(static_cast<int64_t>(5));
				// method code: script.call
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							// so we need to make a copy of argumentValues beginning from second element
							vector<ScriptVariable> callArgumentValues;
							for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#else
							span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#endif
					}
				}
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

	// Statement: 5
	// setVariable("$a", "0")
	{
		const ScriptStatement& statement = scripts[5].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$a"));
		argumentValues[1].setValue(string("0"));
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

	// Statement: 6
	// setVariable("$b", "1")
	{
		const ScriptStatement& statement = scripts[5].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$b"));
		argumentValues[1].setValue(string("1"));
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

	// Statement: 7
	// setVariable("$c", "2")
	{
		const ScriptStatement& statement = scripts[5].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$c"));
		argumentValues[1].setValue(string("2"));
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
	// console.log(add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))))
	{
		const ScriptStatement& statement = scripts[5].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		// depth = 1 / argument index = 0: add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("assignTest(): pre: $a = "));
			// argumentValues[1] --> returnValue of add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			// depth = 2 / argument index = 1: add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$a")
				// argumentValues[1] --> returnValue of add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				// depth = 3 / argument index = 0: getVariable("$a")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$a"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string(", $b = "));
					// argumentValues[1] --> returnValue of add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					// depth = 4 / argument index = 1: add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of getVariable("$b")
						// argumentValues[1] --> returnValue of add(", $c = ", getVariable("$c"))
						// depth = 5 / argument index = 0: getVariable("$b")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues;
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
							argumentValues[0].setValue(string("$b"));
							// method code: getVariable
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								returnValue = miniScript->getVariable(variable);
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript(); return;
							}
						}
						// depth = 5 / argument index = 1: add(", $c = ", getVariable("$c"))
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[1];
							array<ScriptVariable, 2> argumentValues;
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							argumentValues[0].setValue(string(", $c = "));
							// argumentValues[1] --> returnValue of getVariable("$c")
							// depth = 6 / argument index = 1: getVariable("$c")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX1[1];
								array<ScriptVariable, 1> argumentValues;
								array<ScriptVariable, 1>& argumentValuesD6AIDX1 = argumentValues;
								argumentValues[0].setValue(string("$c"));
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
						// method code: add
						MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
					}
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
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

	// Statement: 9
	// script.call("assignTest", getVariable("$a"), getVariable("$b"), getVariable("$c"))
	{
		const ScriptStatement& statement = scripts[5].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 4> argumentValues;
		array<ScriptVariable, 4>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("assignTest"));
		// argumentValues[1] --> returnValue of getVariable("$a")
		// argumentValues[2] --> returnValue of getVariable("$b")
		// argumentValues[3] --> returnValue of getVariable("$c")
		// depth = 1 / argument index = 1: getVariable("$a")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$a"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 2: getVariable("$b")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[2];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX2 = argumentValues;
			argumentValues[0].setValue(string("$b"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 3: getVariable("$c")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[3];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX3 = argumentValues;
			argumentValues[0].setValue(string("$c"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					// so we need to make a copy of argumentValues beginning from second element
					vector<ScriptVariable> callArgumentValues;
					for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
					// call
					span callArgumentValuesSpan(callArgumentValues);
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#else
					span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#endif
			}
		}
		// assign back
		setVariable("$b", argumentValues[2], &statement);
		setVariable("$c", argumentValues[3], &statement);
		//
	}

	// Statement: 10
	// console.log(add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))))
	{
		const ScriptStatement& statement = scripts[5].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		// depth = 1 / argument index = 0: add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("assignTest(): post: $a = "));
			// argumentValues[1] --> returnValue of add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			// depth = 2 / argument index = 1: add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$a")
				// argumentValues[1] --> returnValue of add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				// depth = 3 / argument index = 0: getVariable("$a")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$a"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable);
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string(", $b = "));
					// argumentValues[1] --> returnValue of add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					// depth = 4 / argument index = 1: add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of getVariable("$b")
						// argumentValues[1] --> returnValue of add(", $c = ", getVariable("$c"))
						// depth = 5 / argument index = 0: getVariable("$b")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues;
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
							argumentValues[0].setValue(string("$b"));
							// method code: getVariable
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								returnValue = miniScript->getVariable(variable);
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript(); return;
							}
						}
						// depth = 5 / argument index = 1: add(", $c = ", getVariable("$c"))
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[1];
							array<ScriptVariable, 2> argumentValues;
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							argumentValues[0].setValue(string(", $c = "));
							// argumentValues[1] --> returnValue of getVariable("$c")
							// depth = 6 / argument index = 1: getVariable("$c")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX1[1];
								array<ScriptVariable, 1> argumentValues;
								array<ScriptVariable, 1>& argumentValuesD6AIDX1 = argumentValues;
								argumentValues[0].setValue(string("$c"));
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
						// method code: add
						MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
					}
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
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

	// Statement: 11
	// setVariable("$globalTest", "Global Test Variable")
	{
		const ScriptStatement& statement = scripts[5].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$globalTest"));
		argumentValues[1].setValue(string("Global Test Variable"));
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

	// Statement: 12
	// console.log(add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest")))
	{
		const ScriptStatement& statement = scripts[5].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest"))
		// depth = 1 / argument index = 0: add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("globalVariableTest(): pre: $globalTest = "));
			// argumentValues[1] --> returnValue of getVariable("$globalTest")
			// depth = 2 / argument index = 1: getVariable("$globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("$globalTest"));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 13
	// script.call("globalVariableTest")
	{
		const ScriptStatement& statement = scripts[5].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("globalVariableTest"));
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					// so we need to make a copy of argumentValues beginning from second element
					vector<ScriptVariable> callArgumentValues;
					for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
					// call
					span callArgumentValuesSpan(callArgumentValues);
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#else
					span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
					miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
				#endif
			}
		}
	}

	// Statement: 14
	// console.log(add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest")))
	{
		const ScriptStatement& statement = scripts[5].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest"))
		// depth = 1 / argument index = 0: add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("globalVariableTest(): post: $globalTest = "));
			// argumentValues[1] --> returnValue of getVariable("$globalTest")
			// depth = 2 / argument index = 1: getVariable("$globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("$globalTest"));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 15
	// script.stop()
	{
		const ScriptStatement& statement = scripts[5].statements[15];
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

	// Statement: 16
	// end()
	{
		const ScriptStatement& statement = scripts[5].statements[16];
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

void MiniScriptFunctionsTest::on_error(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(6, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 6;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("----------------------")
	{
		const ScriptStatement& statement = scripts[6].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("functions-test: Error")
	{
		const ScriptStatement& statement = scripts[6].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("functions-test: Error"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("----------------------")
	{
		const ScriptStatement& statement = scripts[6].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 3
	// console.log("An error occurred")
	{
		const ScriptStatement& statement = scripts[6].statements[3];
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
		const ScriptStatement& statement = scripts[6].statements[4];
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
		const ScriptStatement& statement = scripts[6].statements[5];
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
