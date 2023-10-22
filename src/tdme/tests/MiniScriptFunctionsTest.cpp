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
	setNativeHash("a46fe56564df8b7888c49ee7a251bfae26f731ef135898ffa2e43fc939f7378e");
	setNativeScripts(
		{
			Script(
				Script::SCRIPTTYPE_ON,
				2,
				"initialize",
				"initialize",
				ScriptStatement(
					2,
					0,
					"initialize",
					"initialize",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						3,
						0,
						"console.log(\"----------------------------\")",
						"console.log(\"----------------------------\")",
						-1
					),
					ScriptStatement(
						4,
						1,
						"console.log(\"functions-test: Initialize\")",
						"console.log(\"functions-test: Initialize\")",
						-1
					),
					ScriptStatement(
						5,
						2,
						"console.log(\"----------------------------\")",
						"console.log(\"----------------------------\")",
						-1
					),
					ScriptStatement(
						6,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						7,
						4,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
				}
			),
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				10,
				"factorial",
				"factorial",
				ScriptStatement(
					10,
					0,
					"factorial",
					"factorial",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						11,
						0,
						"console.log(\"factorial(): $arguments = \" + $arguments + \" / $value = \" + $value)",
						"console.log(add(\"factorial(): $arguments = \",add($arguments,add(\" / $value = \", $value))))",
						-1
					),
					ScriptStatement(
						12,
						1,
						"if ($value == 0)",
						"if (equals($value, 0))",
						3
					),
					ScriptStatement(
						13,
						2,
						"return(1)",
						"return(1)",
						-1
					),
					ScriptStatement(
						14,
						3,
						"end",
						"end",
						-1
					),
					ScriptStatement(
						15,
						4,
						"return($value * factorial($value - 1))",
						"return(mul($value, factorial(sub($value, 1))))",
						-1
					),
					ScriptStatement(
						16,
						5,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
					Script::ScriptArgument(
						"$value",
						false
					)
				}
			),
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				19,
				"helloWorldFunction",
				"helloWorldFunction",
				ScriptStatement(
					19,
					0,
					"helloWorldFunction",
					"helloWorldFunction",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						20,
						0,
						"console.log(\"helloWorldFunction(): Hello world\")",
						"console.log(\"helloWorldFunction(): Hello world\")",
						-1
					),
					ScriptStatement(
						21,
						1,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
				}
			),
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				24,
				"assignTest",
				"assignTest",
				ScriptStatement(
					24,
					0,
					"assignTest",
					"assignTest",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						25,
						0,
						"$a = \"a\"",
						"setVariable(\"$a\", \"a\")",
						-1
					),
					ScriptStatement(
						26,
						1,
						"$b = \"b\"",
						"setVariable(\"$b\", \"b\")",
						-1
					),
					ScriptStatement(
						27,
						2,
						"$c = \"c\"",
						"setVariable(\"$c\", \"c\")",
						-1
					),
					ScriptStatement(
						28,
						3,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
					Script::ScriptArgument(
						"$a",
						false
					),
					Script::ScriptArgument(
						"$b",
						true
					),
					Script::ScriptArgument(
						"$c",
						true
					)
				}
			),
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				31,
				"globalVariableTest",
				"globalVariableTest",
				ScriptStatement(
					31,
					0,
					"globalVariableTest",
					"globalVariableTest",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						32,
						0,
						"console.log(\"globalVariableTest(): $GLOBAL.globalTest = \" + $GLOBAL.globalTest)",
						"console.log(add(\"globalVariableTest(): $GLOBAL.globalTest = \", $GLOBAL.globalTest))",
						-1
					),
					ScriptStatement(
						33,
						1,
						"$GLOBAL.globalTest = \"Been there, done that, got the t-shirt\"",
						"setVariable(\"$GLOBAL.globalTest\", \"Been there, done that, got the t-shirt\")",
						-1
					),
					ScriptStatement(
						34,
						2,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
				}
			),
			Script(
				Script::SCRIPTTYPE_ON,
				37,
				"nothing",
				"nothing",
				ScriptStatement(
					37,
					0,
					"nothing",
					"nothing",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						38,
						0,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						39,
						1,
						"console.log(\"functions-test: Nothing\")",
						"console.log(\"functions-test: Nothing\")",
						-1
					),
					ScriptStatement(
						40,
						2,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						41,
						3,
						"helloWorldFunction()",
						"helloWorldFunction()",
						-1
					),
					ScriptStatement(
						42,
						4,
						"console.log(\"factorial(5) = \" + factorial(5))",
						"console.log(add(\"factorial(5) = \", factorial(5)))",
						-1
					),
					ScriptStatement(
						43,
						5,
						"$a = \"0\"",
						"setVariable(\"$a\", \"0\")",
						-1
					),
					ScriptStatement(
						44,
						6,
						"$b = \"1\"",
						"setVariable(\"$b\", \"1\")",
						-1
					),
					ScriptStatement(
						45,
						7,
						"$c = \"2\"",
						"setVariable(\"$c\", \"2\")",
						-1
					),
					ScriptStatement(
						46,
						8,
						"console.log(\"assignTest(): pre: $a = \" + $a + \", $b = \" + $b + \", $c = \" + $c)",
						"console.log(add(\"assignTest(): pre: $a = \",add($a,add(\", $b = \",add($b,add(\", $c = \", $c))))))",
						-1
					),
					ScriptStatement(
						47,
						9,
						"assignTest($a, $b, $c)",
						"assignTest($a, $b, $c)",
						-1
					),
					ScriptStatement(
						48,
						10,
						"console.log(\"assignTest(): post: $a = \" + $a + \", $b = \" + $b + \", $c = \" + $c)",
						"console.log(add(\"assignTest(): post: $a = \",add($a,add(\", $b = \",add($b,add(\", $c = \", $c))))))",
						-1
					),
					ScriptStatement(
						49,
						11,
						"$globalTest = \"Global Test Variable\"",
						"setVariable(\"$globalTest\", \"Global Test Variable\")",
						-1
					),
					ScriptStatement(
						50,
						12,
						"console.log(\"globalVariableTest(): pre: $globalTest = \" + $globalTest)",
						"console.log(add(\"globalVariableTest(): pre: $globalTest = \", $globalTest))",
						-1
					),
					ScriptStatement(
						51,
						13,
						"globalVariableTest()",
						"globalVariableTest()",
						-1
					),
					ScriptStatement(
						52,
						14,
						"console.log(\"globalVariableTest(): post: $globalTest = \" + $globalTest)",
						"console.log(add(\"globalVariableTest(): post: $globalTest = \", $globalTest))",
						-1
					),
					ScriptStatement(
						53,
						15,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						54,
						16,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
				}
			),
			Script(
				Script::SCRIPTTYPE_ON,
				57,
				"error",
				"error",
				ScriptStatement(
					57,
					0,
					"error",
					"error",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						58,
						0,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						59,
						1,
						"console.log(\"functions-test: Error\")",
						"console.log(\"functions-test: Error\")",
						-1
					),
					ScriptStatement(
						60,
						2,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						61,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						62,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						63,
						5,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
				}
			)
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
void MiniScriptFunctionsTest::registerMethods() {
	MiniScript::registerMethods();
	if (native == false) return;
	evaluateMemberAccessArrays = {};
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_CHARAT] = getMethod("string.charAt");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_ENDSWITH] = getMethod("string.endsWith");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_EQUALSIGNORECASE] = getMethod("string.equalsIgnoreCase");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_FIRSTINDEXOF] = getMethod("string.firstIndexOf");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_INDEXOF] = getMethod("string.indexOf");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_ISEMPTY] = getMethod("string.isEmpty");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_ISFLOAT] = getMethod("string.isFloat");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_ISINTEGER] = getMethod("string.isInteger");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_LASTINDEXOF] = getMethod("string.lastIndexOf");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_LENGTH] = getMethod("string.length");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_PADLEFT] = getMethod("string.padLeft");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_PADRIGHT] = getMethod("string.padRight");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_REGEXMATCH] = getMethod("string.regexMatch");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_REGEXREPLACE] = getMethod("string.regexReplace");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_REPLACE] = getMethod("string.replace");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_STARTSWITH] = getMethod("string.startsWith");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_SUBSTRING] = getMethod("string.substring");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_TOLOWERCASE] = getMethod("string.toLowerCase");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_TOUPPERCASE] = getMethod("string.toUpperCase");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_TOKENIZE] = getMethod("string.tokenize");
	evaluateMemberAccessArrays[0][EVALUATEMEMBERACCESSARRAYIDX_TRIM] = getMethod("string.trim");
	evaluateMemberAccessArrays[1][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTH] = getMethod("vec2.computeLength");
	evaluateMemberAccessArrays[1][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTHSQUARED] = getMethod("vec2.computeLengthSquared");
	evaluateMemberAccessArrays[1][EVALUATEMEMBERACCESSARRAYIDX_GETX] = getMethod("vec2.getX");
	evaluateMemberAccessArrays[1][EVALUATEMEMBERACCESSARRAYIDX_GETY] = getMethod("vec2.getY");
	evaluateMemberAccessArrays[1][EVALUATEMEMBERACCESSARRAYIDX_NORMALIZE] = getMethod("vec2.normalize");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTH] = getMethod("vec3.computeLength");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTHSQUARED] = getMethod("vec3.computeLengthSquared");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_GETX] = getMethod("vec3.getX");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_GETY] = getMethod("vec3.getY");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_GETZ] = getMethod("vec3.getZ");
	evaluateMemberAccessArrays[2][EVALUATEMEMBERACCESSARRAYIDX_NORMALIZE] = getMethod("vec3.normalize");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTH] = getMethod("vec4.computeLength");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTHSQUARED] = getMethod("vec4.computeLengthSquared");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_GETW] = getMethod("vec4.getW");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_GETX] = getMethod("vec4.getX");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_GETY] = getMethod("vec4.getY");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_GETZ] = getMethod("vec4.getZ");
	evaluateMemberAccessArrays[3][EVALUATEMEMBERACCESSARRAYIDX_NORMALIZE] = getMethod("vec4.normalize");
	evaluateMemberAccessArrays[4][EVALUATEMEMBERACCESSARRAYIDX_COMPUTEEULERANGLES] = getMethod("quaternion.computeEulerAngles");
	evaluateMemberAccessArrays[4][EVALUATEMEMBERACCESSARRAYIDX_COMPUTEMATRIX] = getMethod("quaternion.computeMatrix");
	evaluateMemberAccessArrays[4][EVALUATEMEMBERACCESSARRAYIDX_INVERT] = getMethod("quaternion.invert");
	evaluateMemberAccessArrays[4][EVALUATEMEMBERACCESSARRAYIDX_NORMALIZE] = getMethod("quaternion.normalize");
	evaluateMemberAccessArrays[6][EVALUATEMEMBERACCESSARRAYIDX_COMPUTEEULERANGLES] = getMethod("mat4.computeEulerAngles");
	evaluateMemberAccessArrays[6][EVALUATEMEMBERACCESSARRAYIDX_INVERT] = getMethod("mat4.invert");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_APPLYROTATION] = getMethod("transform.applyRotation");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONANGLE] = getMethod("transform.getRotationAngle");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONAXIS] = getMethod("transform.getRotationAxis");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONSQUATERNION] = getMethod("transform.getRotationsQuaternion");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETSCALE] = getMethod("transform.getScale");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETTRANSFORMMATRIX] = getMethod("transform.getTransformMatrix");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_GETTRANSLATION] = getMethod("transform.getTranslation");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_ROTATE] = getMethod("transform.rotate");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_SETROTATIONANGLE] = getMethod("transform.setRotationAngle");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_SETSCALE] = getMethod("transform.setScale");
	evaluateMemberAccessArrays[7][EVALUATEMEMBERACCESSARRAYIDX_SETTRANSLATION] = getMethod("transform.setTranslation");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_GET] = getMethod("array.get");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_INDEXOF] = getMethod("array.indexOf");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_LENGTH] = getMethod("array.length");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_PUSH] = getMethod("array.push");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_REMOVE] = getMethod("array.remove");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_REMOVEOF] = getMethod("array.removeOf");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_REVERSE] = getMethod("array.reverse");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_SET] = getMethod("array.set");
	evaluateMemberAccessArrays[8][EVALUATEMEMBERACCESSARRAYIDX_SORT] = getMethod("array.sort");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_GET] = getMethod("map.get");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_GETKEYS] = getMethod("map.getKeys");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_GETVALUES] = getMethod("map.getValues");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_HAS] = getMethod("map.has");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_REMOVE] = getMethod("map.remove");
	evaluateMemberAccessArrays[9][EVALUATEMEMBERACCESSARRAYIDX_SET] = getMethod("map.set");
	evaluateMemberAccessArrays[10][EVALUATEMEMBERACCESSARRAYIDX_GETKEYS] = getMethod("set.getKeys");
	evaluateMemberAccessArrays[10][EVALUATEMEMBERACCESSARRAYIDX_HAS] = getMethod("set.has");
	evaluateMemberAccessArrays[10][EVALUATEMEMBERACCESSARRAYIDX_INSERT] = getMethod("set.insert");
	evaluateMemberAccessArrays[10][EVALUATEMEMBERACCESSARRAYIDX_REMOVE] = getMethod("set.remove");
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
	for (const auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return SCRIPTIDX_NONE;
}

void MiniScriptFunctionsTest::emit(const string& condition) {
	if (native == false) {
		MiniScript::emit(condition);
		return;
	}
	if (condition == "initialize") {
		on_initialize(STATEMENTIDX_FIRST);
	} else
	if (condition == "nothing") {
		on_nothing(STATEMENTIDX_FIRST);
	} else
	if (condition == "error") {
		on_error(STATEMENTIDX_FIRST);
	} else
	{
		Console::println("MiniScriptFunctionsTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptFunctionsTest::on_initialize(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("----------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("functions-test: Initialize")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("functions-test: Initialize"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("----------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 3
	// console.log()
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 4
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 2) goto miniscript_statement_2; else
	if (miniScriptGotoStatementIdx == 4) goto miniscript_statement_4; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::factorial(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log(add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value"))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("factorial(): $arguments = ", add(getVariable("$arguments"), add(" / $value = ", getVariable("$value"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("factorial(): $arguments = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add(getVariable("$arguments"), add(" / $value = ", getVariable("$value")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$arguments")
					ScriptVariable() // argumentValues[1] --> returnValue of add(" / $value = ", getVariable("$value"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$arguments")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$arguments"))
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable, &statement);
					} else {
						Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(" / $value = ", getVariable("$value"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string(" / $value = ")),
						ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$value")
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: getVariable("$value")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$value"))
						};
						array<ScriptVariable, 1>& argumentValuesD4AIDX1 = argumentValues;
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable, &statement);
						} else {
							Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
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
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// if(equals(getVariable("$value"), 0))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$value"), 0)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$value"), 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$value")
				ScriptVariable(static_cast<int64_t>(0ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$value")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$value"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			if (argumentValues.size() != 2) {
				Console::println(string("equals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("equals")));
				miniScript->startErrorScript(); return;
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
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println(string("if") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("if")));
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
	// statement: 2
	miniscript_statement_2:
	// return(1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(1ll))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: return
		if (miniScript->isFunctionRunning() == false) {
			Console::println(string("return") + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
			miniScript->startErrorScript(); return;
		} else
		if (argumentValues.size() == 0) {
			miniScript->stopRunning();
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println(string("return") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("return")));
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	// statement: 3
	miniscript_statement_3:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// statement: 4
	miniscript_statement_4:
	// return(mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1)))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: mul(getVariable("$value"), factorial(sub(getVariable("$value"), 1)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$value")
				ScriptVariable() // argumentValues[1] --> returnValue of factorial(sub(getVariable("$value"), 1))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$value")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$value"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: script.call("factorial", sub(getVariable("$value"), 1))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("factorial")),
					ScriptVariable() // argumentValues[1] --> returnValue of sub(getVariable("$value"), 1)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: sub(getVariable("$value"), 1)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$value")
						ScriptVariable(static_cast<int64_t>(1ll))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 0: getVariable("$value")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$value"))
						};
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable, &statement);
						} else {
							Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
							miniScript->startErrorScript(); return;
						}
					}
					// method code: sub
					MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
				}
				// method code: script.call
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.call")));
					miniScript->startErrorScript(); return;
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
						miniScript->startErrorScript(); return;
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
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
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: return
		if (miniScript->isFunctionRunning() == false) {
			Console::println(string("return") + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
			miniScript->startErrorScript(); return;
		} else
		if (argumentValues.size() == 0) {
			miniScript->stopRunning();
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println(string("return") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("return")));
		}
	}
	if (getScriptState().running == false) {
		return;
	}
	// statement: 5
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::helloWorldFunction(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("helloWorldFunction(): Hello world")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("helloWorldFunction(): Hello world"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::assignTest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// setVariable("$a", "a")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$a")),
			ScriptVariable(string("a"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 1
	// setVariable("$b", "b")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$b")),
			ScriptVariable(string("b"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 2
	// setVariable("$c", "c")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$c")),
			ScriptVariable(string("c"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 3
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::globalVariableTest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log(add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("globalVariableTest(): $GLOBAL.globalTest = ", getVariable("$GLOBAL.globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("globalVariableTest(): $GLOBAL.globalTest = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$GLOBAL.globalTest")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$GLOBAL.globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$GLOBAL.globalTest"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// setVariable("$GLOBAL.globalTest", "Been there, done that, got the t-shirt")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$GLOBAL.globalTest")),
			ScriptVariable(string("Been there, done that, got the t-shirt"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 2
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(5, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 5;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("functions-test: Nothing")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("functions-test: Nothing"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 3
	// script.call("helloWorldFunction")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("helloWorldFunction"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.call")));
			miniScript->startErrorScript(); return;
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
				miniScript->startErrorScript(); return;
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
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
	// statement: 4
	// console.log(add("factorial(5) = ", factorial(5)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("factorial(5) = ", factorial(5))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("factorial(5) = ", factorial(5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("factorial(5) = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of factorial(5)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: script.call("factorial", 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("factorial")),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: script.call
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.call")));
					miniScript->startErrorScript(); return;
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
						miniScript->startErrorScript(); return;
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
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
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 5
	// setVariable("$a", "0")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$a")),
			ScriptVariable(string("0"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 6
	// setVariable("$b", "1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$b")),
			ScriptVariable(string("1"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 7
	// setVariable("$c", "2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$c")),
			ScriptVariable(string("2"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 8
	// console.log(add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("assignTest(): pre: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("assignTest(): pre: $a = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$a")
					ScriptVariable() // argumentValues[1] --> returnValue of add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$a")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$a"))
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable, &statement);
					} else {
						Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string(", $b = ")),
						ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$b")
							ScriptVariable() // argumentValues[1] --> returnValue of add(", $c = ", getVariable("$c"))
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// depth = 5 / argument index = 0: getVariable("$b")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues {
								ScriptVariable(string("$b"))
							};
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
							// method code: getVariable
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								returnValue = miniScript->getVariable(variable, &statement);
							} else {
								Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
								miniScript->startErrorScript(); return;
							}
						}
						// depth = 5 / argument index = 1: add(", $c = ", getVariable("$c"))
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[1];
							array<ScriptVariable, 2> argumentValues {
								ScriptVariable(string(", $c = ")),
								ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$c")
							};
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							// depth = 6 / argument index = 1: getVariable("$c")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX1[1];
								array<ScriptVariable, 1> argumentValues {
									ScriptVariable(string("$c"))
								};
								array<ScriptVariable, 1>& argumentValuesD6AIDX1 = argumentValues;
								// method code: getVariable
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									returnValue = miniScript->getVariable(variable, &statement);
								} else {
									Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
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
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 9
	// script.call("assignTest", getVariable("$a"), getVariable("$b"), getVariable("$c"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 4> argumentValues {
			ScriptVariable(string("assignTest")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$a")
			ScriptVariable(), // argumentValues[2] --> returnValue of getVariable("$b")
			ScriptVariable() // argumentValues[3] --> returnValue of getVariable("$c")
		};
		array<ScriptVariable, 4>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$a")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$a"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable, &statement);
			} else {
				Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 2: getVariable("$b")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[2];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$b"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX2 = argumentValues;
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable, &statement);
			} else {
				Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 3: getVariable("$c")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[3];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$c"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX3 = argumentValues;
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable, &statement);
			} else {
				Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.call")));
			// assign back
			setVariable("$b", argumentValues[2], &statement);
			setVariable("$c", argumentValues[3], &statement);
			//
			miniScript->startErrorScript(); return;
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
				// assign back
				setVariable("$b", argumentValues[2], &statement);
				setVariable("$c", argumentValues[3], &statement);
				//
				miniScript->startErrorScript(); return;
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
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
		// assign back
		setVariable("$b", argumentValues[2], &statement);
		setVariable("$c", argumentValues[3], &statement);
		//
	}
	// statement: 10
	// console.log(add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("assignTest(): post: $a = ", add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("assignTest(): post: $a = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add(getVariable("$a"), add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c")))))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$a")
					ScriptVariable() // argumentValues[1] --> returnValue of add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$a")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$a"))
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable, &statement);
					} else {
						Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(", $b = ", add(getVariable("$b"), add(", $c = ", getVariable("$c"))))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string(", $b = ")),
						ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: add(getVariable("$b"), add(", $c = ", getVariable("$c")))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$b")
							ScriptVariable() // argumentValues[1] --> returnValue of add(", $c = ", getVariable("$c"))
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// depth = 5 / argument index = 0: getVariable("$b")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues {
								ScriptVariable(string("$b"))
							};
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
							// method code: getVariable
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								returnValue = miniScript->getVariable(variable, &statement);
							} else {
								Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
								miniScript->startErrorScript(); return;
							}
						}
						// depth = 5 / argument index = 1: add(", $c = ", getVariable("$c"))
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[1];
							array<ScriptVariable, 2> argumentValues {
								ScriptVariable(string(", $c = ")),
								ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$c")
							};
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							// depth = 6 / argument index = 1: getVariable("$c")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX1[1];
								array<ScriptVariable, 1> argumentValues {
									ScriptVariable(string("$c"))
								};
								array<ScriptVariable, 1>& argumentValuesD6AIDX1 = argumentValues;
								// method code: getVariable
								string variable;
								if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
									returnValue = miniScript->getVariable(variable, &statement);
								} else {
									Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
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
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 11
	// setVariable("$globalTest", "Global Test Variable")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$globalTest")),
			ScriptVariable(string("Global Test Variable"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 12
	// console.log(add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("globalVariableTest(): pre: $globalTest = ", getVariable("$globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("globalVariableTest(): pre: $globalTest = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$globalTest")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$globalTest"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 13
	// script.call("globalVariableTest")
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("globalVariableTest"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.call")));
			miniScript->startErrorScript(); return;
		} else {
			auto scriptIdx = miniScript->getFunctionScriptIdx(function);
			if (scriptIdx == SCRIPTIDX_NONE) {
				Console::println(string("script.call") + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
				miniScript->startErrorScript(); return;
			} else {
				#if defined (__APPLE__)
					// MACOSX currently does not support initializing span using begin and end iterators,
					vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
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
	// statement: 14
	// console.log(add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("globalVariableTest(): post: $globalTest = ", getVariable("$globalTest"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("globalVariableTest(): post: $globalTest = ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$globalTest")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$globalTest")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$globalTest"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 15
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->stopScriptExecution();
		miniScript->stopRunning();
	}
	if (getScriptState().running == false) {
		return;
	}
	// statement: 16
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[5].statements[16];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(6, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 6;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("functions-test: Error")
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("functions-test: Error"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 3
	// console.log("An error occurred")
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("An error occurred"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 4
	// script.wait(1000)
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(1000ll))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
			miniScript->getScriptState().timeWaitTime = time;
			miniScript->setScriptStateState(STATEMACHINESTATE_WAIT);
		} else {
			Console::println(string("script.wait") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.wait")));
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 5
	miniscript_statement_5:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[6].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->getScriptState().endTypeStack.empty() == true) {
			Console::println(string("end") + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
			miniScript->startErrorScript(); return;
		} else {
			auto endType = miniScript->getScriptState().endTypeStack.top();
			miniScript->getScriptState().endTypeStack.pop();
			switch(endType) {
				case ScriptState::ENDTYPE_BLOCK:
					if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
						miniScript->stopRunning();
					}
					break;
				case ScriptState::ENDTYPE_FOR:
					// no op
					break;
				case ScriptState::ENDTYPE_IF:
					miniScript->getScriptState().conditionStack.pop();
					break;
			}
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
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
