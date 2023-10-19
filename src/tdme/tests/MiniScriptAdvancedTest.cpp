#include "MiniScriptAdvancedTest.h"

#include <array>
#include <utility>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using std::array;
using std::move;

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptAdvancedTest::MiniScriptAdvancedTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/

#define __MINISCRIPT_TRANSPILATION__

void MiniScriptAdvancedTest::initializeNative() {
	setNative(true);
	setNativeHash("e50b03f12c453eee491bea0d4aa2df428612ac2efecb8a02250d6b420881429a");
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
						"console.log(\"---------------------------\")",
						"console.log(\"---------------------------\")",
						-1
					),
					ScriptStatement(
						4,
						1,
						"console.log(\"advanced-test: Initialize\")",
						"console.log(\"advanced-test: Initialize\")",
						-1
					),
					ScriptStatement(
						5,
						2,
						"console.log(\"--------------------------\")",
						"console.log(\"--------------------------\")",
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
				Script::SCRIPTTYPE_ON,
				10,
				"nothing",
				"nothing",
				ScriptStatement(
					10,
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
						11,
						0,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						12,
						1,
						"console.log(\"Arrays\")",
						"console.log(\"Arrays\")",
						-1
					),
					ScriptStatement(
						13,
						2,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						14,
						3,
						"$array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]",
						"setVariable(\"$array\", [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c},mul(20, 20)])",
						-1
					),
					ScriptStatement(
						15,
						4,
						"console.log(\"array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: \" + $array)",
						"console.log(add(\"array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: \", $array))",
						-1
					),
					ScriptStatement(
						17,
						5,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						18,
						6,
						"forCondition($i < $array->length())",
						"forCondition(lesser($i, $array->length()))",
						10
					),
					ScriptStatement(
						19,
						7,
						"console.log($i + \": \" + $array[$i])",
						"console.log(add($i,add(\": \", $array[$i])))",
						-1
					),
					ScriptStatement(
						20,
						8,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						21,
						9,
						"end",
						"end",
						6
					),
					ScriptStatement(
						23,
						10,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						24,
						11,
						"console.log(\"Maps\")",
						"console.log(\"Maps\")",
						-1
					),
					ScriptStatement(
						25,
						12,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						26,
						13,
						"$map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}",
						"setVariable(\"$map\", {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f:mul(20, 20)})",
						-1
					),
					ScriptStatement(
						27,
						14,
						"console.log(\"map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: \" + $map)",
						"console.log(add(\"map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: \", $map))",
						-1
					),
					ScriptStatement(
						28,
						15,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						29,
						16,
						"console.log(\"Sets\")",
						"console.log(\"Sets\")",
						-1
					),
					ScriptStatement(
						30,
						17,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						31,
						18,
						"$set = {test1, test2, test3, test4, test5}",
						"setVariable(\"$set\", {test1, test2, test3, test4, test5})",
						-1
					),
					ScriptStatement(
						32,
						19,
						"console.log(\"set initialized with: $set = {test1, test2, test3, test4, test5}: \" + $set)",
						"console.log(add(\"set initialized with: $set = {test1, test2, test3, test4, test5}: \", $set))",
						-1
					),
					ScriptStatement(
						33,
						20,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						34,
						21,
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
				"error",
				"error",
				ScriptStatement(
					37,
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
						38,
						0,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						39,
						1,
						"console.log(\"advanced-test: Error\")",
						"console.log(\"advanced-test: Error\")",
						-1
					),
					ScriptStatement(
						40,
						2,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						41,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						42,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						43,
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
		}
	);
}
void MiniScriptAdvancedTest::registerMethods() {
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

int MiniScriptAdvancedTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptAdvancedTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (const auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return SCRIPTIDX_NONE;
}

void MiniScriptAdvancedTest::emit(const string& condition) {
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
		Console::println("MiniScriptAdvancedTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptAdvancedTest::on_initialize(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("---------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("advanced-test: Initialize")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("advanced-test: Initialize"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("--------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("--------------------------"))
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

void MiniScriptAdvancedTest::on_nothing(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 7) goto miniscript_statement_7; else
	if (miniScriptGotoStatementIdx == 10) goto miniscript_statement_10; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("Arrays")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Arrays"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 3
	// we will use on_nothing_array_access_statement_s_3_1_0_0() to determine array access index
	// setVariable("$array", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array")),
			MiniScript::initializeArray("[1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c},mul(20, 20)]", this, statement)
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
	// statement: 4
	// console.log(add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: ", getVariable("$array")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: ", getVariable("$array"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: ", getVariable("$array"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}, 20 * 20]: ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$array"))
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
	// statement: 5
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(0ll))
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
	miniscript_statement_6:
	// forCondition(lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$i"))
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
			// depth = 2 / argument index = 1: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("$array")),
					ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
					ScriptVariable(string("length"))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: getVariable("$array")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$array"))
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						returnValue = miniScript->getVariable(variable, &statement);
					} else {
						Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
						miniScript->startErrorScript(); return;
					}
				}
				const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_LENGTH;
				// method code: internal.script.evaluateMemberAccess
				// Current layout:
				//	0: variable name of object
				//	1: variable content of object
				//	2: object method to call
				//	3: variable name of argument 0
				//	4: variable content of argument 0
				//	5: variable name of argument 1
				//	6: variable content of argument 1
				//	..
				string variable;
				string member;
				if (argumentValues.size() < 3 ||
					miniScript->getStringValue(argumentValues, 0, variable, false) == false ||
					miniScript->getStringValue(argumentValues, 2, member, false) == false) {
					Console::println(string("internal.script.evaluateMemberAccess") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("internal.script.evaluateMemberAccess")));
					miniScript->startErrorScript(); return;
				} else {
					const auto& className = ScriptVariable::getClassName(argumentValues[1].getType());
					if (className.empty() == false) {
						#if defined(__MINISCRIPT_TRANSPILATION__)
							auto method = evaluateMemberAccessArrays[static_cast<int>(argumentValues[1].getType()) - static_cast<int>(MiniScript::TYPE_STRING)][EVALUATEMEMBERACCESS_MEMBER];
						#else
							auto method = miniScript->getMethod(className + "." + member);
						#endif
						if (method != nullptr) {
							// create method call arguments
							vector<ScriptVariable> callArgumentValues(1 + (argumentValues.size() - 3) / 2);
							//	this
							callArgumentValues[0] = move(argumentValues[1]);
							//	additional method call arguments
							{
								auto callArgumentValueIdx = 1;
								for (auto argumentValueIdx = 3; argumentValueIdx < argumentValues.size(); argumentValueIdx+=2) {
									callArgumentValues[callArgumentValueIdx] = move(argumentValues[argumentValueIdx + 1]);
									callArgumentValueIdx++;
								}
							}
							span callArgumentValuesSpan(callArgumentValues);
							method->executeMethod(callArgumentValuesSpan, returnValue, statement);
							// assign back variables
							{
								auto argumentIdx = 0;
								for (const auto& argumentType: method->getArgumentTypes()) {
									if (argumentType.assignBack == false) {
										argumentIdx++;
										continue;
									}
									//
									if (argumentIdx == 0) {
										if (isVariableAccess(variable) == true) {
											miniScript->setVariable(variable, callArgumentValuesSpan[0], &statement);
										} else {
											Console::println(miniScript->getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variable + "'");
										}
									} else {
										auto variableNameArgumentIdx = (argumentIdx * 2) + 1;
										if (variableNameArgumentIdx >= argumentValues.size() || argumentIdx >= callArgumentValuesSpan.size()) {
											Console::println(string("internal.script.evaluateMemberAccess") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("internal.script.evaluateMemberAccess")) + ": invalid member call");
											miniScript->startErrorScript(); return;
										} else {
											auto argumentVariable = argumentValues[variableNameArgumentIdx].getValueAsString();
											if (isVariableAccess(argumentVariable) == true) {
												miniScript->setVariable(argumentVariable, callArgumentValuesSpan[argumentIdx], &statement);
											} else {
												Console::println(miniScript->getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + argumentVariable + "'");
											}
										}
									}
									//
									argumentIdx++;
								}
							}
							// write back arguments from call arguments
							//	this
							argumentValues[1] = move(callArgumentValuesSpan[0]);
							//	additional arguments
							{
								auto callArgumentValueIdx = 1;
								for (auto argumentValueIdx = 3; argumentValueIdx < argumentValues.size(); argumentValueIdx+=2) {
									argumentValues[argumentValueIdx] = move(callArgumentValuesSpan[callArgumentValueIdx].getValueAsString());
									callArgumentValueIdx++;
								}
							}
						}
					} else {
						Console::println(string("internal.script.evaluateMemberAccess") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("internal.script.evaluateMemberAccess")) + ": invalid variable type");
						miniScript->startErrorScript(); return;
					}
				}
			}
			// method code: lesser
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA < stringValueB);
				} else {
					Console::println(string("lesser") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesser")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA < floatValueB);
				} else {
					Console::println(string("lesser") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesser")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println(string("forCondition") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("forCondition")));
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_10;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 7
	miniscript_statement_7:
	// console.log(add(getVariable("$i"), add(": ", getVariable("$array[$i]"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add(getVariable("$i"), add(": ", getVariable("$array[$i]")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add(getVariable("$i"), add(": ", getVariable("$array[$i]")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of add(": ", getVariable("$array[$i]"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$i"))
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
			// depth = 2 / argument index = 1: add(": ", getVariable("$array[$i]"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string(": ")),
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array[$i]")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// we will use on_nothing_array_access_statement_s_7_0_0_3() to determine array access index
				// depth = 3 / argument index = 1: getVariable("$array[$i]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_7_0_0_3(statement).getValueAsString() + "]"))
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 8
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$i")
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$i"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable, &statement);
			} else {
				Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: prefixIncrement
		int64_t value;
		if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
			Console::println(string("prefixIncrement") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("prefixIncrement")));
			// assign back
			setVariable("$i", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		} else {
			++value;
			argumentValues[0] = value;
			returnValue.setValue(value);
		}
		// assign back
		setVariable("$i", argumentValues[0], &statement);
		//
	}
	// statement: 9
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[9];
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
				goto miniscript_statement_6;
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
	// statement: 10
	miniscript_statement_10:
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 11
	// console.log("Maps")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Maps"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 12
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 13
	// we will use on_nothing_array_access_statement_s_13_1_0_0() to determine array access index
	// setVariable("$map", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map")),
			MiniScript::initializeMapSet("{test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f:mul(20, 20)}", this, statement)
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
	// statement: 14
	// console.log(add("map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: ", getVariable("$map")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: ", getVariable("$map"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: ", getVariable("$map"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("map initialized with: {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}, f: 20 * 20}: ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$map"))
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
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 16
	// console.log("Sets")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[16];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Sets"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 17
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("----------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 18
	// setVariable("$set", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[18];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set")),
			MiniScript::initializeMapSet("{test1, test2, test3, test4, test5}", this, statement)
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
	// statement: 19
	// console.log(add("set initialized with: $set = {test1, test2, test3, test4, test5}: ", getVariable("$set")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("set initialized with: $set = {test1, test2, test3, test4, test5}: ", getVariable("$set"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("set initialized with: $set = {test1, test2, test3, test4, test5}: ", getVariable("$set"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("set initialized with: $set = {test1, test2, test3, test4, test5}: ")),
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$set"))
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
	// statement: 20
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[20];
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
	// statement: 21
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[21];
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

void MiniScriptAdvancedTest::on_error(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[0];
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
	// console.log("advanced-test: Error")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("advanced-test: Error"))
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
		const ScriptStatement& statement = scripts[2].statements[2];
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
		const ScriptStatement& statement = scripts[2].statements[3];
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
		const ScriptStatement& statement = scripts[2].statements[4];
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
		const ScriptStatement& statement = scripts[2].statements[5];
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

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_7_0_0_3(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	// getVariable("$i")
	{
		// statement setup
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("$i"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: getVariable
		string variable;
		if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
			returnValue = miniScript->getVariable(variable, &statement);
		} else {
			Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
			miniScript->startErrorScript(); return ScriptVariable();
		}
		return returnValue;
	}
}


inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_3_0(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	{
		ScriptVariable variableD0;
		variableD0.setType(TYPE_ARRAY);
		{
			ScriptVariable variableD1(static_cast<int64_t>(1ll));
			variableD0.pushArrayValue(variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(2ll));
			variableD0.pushArrayValue(variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(3ll));
			variableD0.pushArrayValue(variableD1);
		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_ARRAY);
			{
				ScriptVariable variableD2(static_cast<int64_t>(1ll));
				variableD1.pushArrayValue(variableD2);
			}
			{
				ScriptVariable variableD2(static_cast<int64_t>(2ll));
				variableD1.pushArrayValue(variableD2);
			}
			{
				ScriptVariable variableD2(static_cast<int64_t>(3ll));
				variableD1.pushArrayValue(variableD2);
			}
			variableD0.pushArrayValue(variableD1);
		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_MAP);
			{
				ScriptVariable variableD2(string("zzz"));
				variableD1.setMapValue("c", variableD2);
			}
			{
				ScriptVariable variableD2(string("yyy"));
				variableD1.setMapValue("b", variableD2);
			}
			{
				ScriptVariable variableD2(string("xxx"));
				variableD1.setMapValue("a", variableD2);
			}
			variableD0.pushArrayValue(variableD1);
		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_SET);
			variableD1.insertSetKey("a");
			variableD1.insertSetKey("b");
			variableD1.insertSetKey("c");
			variableD0.pushArrayValue(variableD1);
		}
		// mul(20, 20)
		{
			// statement setup
			getScriptState().statementIdx = statement.statementIdx;
			// required method code arguments
			ScriptVariable returnValue;
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(20ll)),
				ScriptVariable(static_cast<int64_t>(20ll))
			};
			array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			const auto& variableD1 = returnValue; variableD0.pushArrayValue(variableD1);

		}
		return variableD0;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_13_0(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	{
		ScriptVariable variableD0;
		variableD0.setType(TYPE_MAP);
		// mul(20, 20)
		{
			// statement setup
			getScriptState().statementIdx = statement.statementIdx;
			// required method code arguments
			ScriptVariable returnValue;
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(20ll)),
				ScriptVariable(static_cast<int64_t>(20ll))
			};
			array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			const auto& variableD1 = returnValue; variableD0.setMapValue("f", variableD1);

		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_SET);
			variableD1.insertSetKey("a");
			variableD1.insertSetKey("b");
			variableD1.insertSetKey("c");
			variableD0.setMapValue("test6", variableD1);
		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_MAP);
			{
				ScriptVariable variableD2(string("zzz"));
				variableD1.setMapValue("c", variableD2);
			}
			{
				ScriptVariable variableD2(string("yyy"));
				variableD1.setMapValue("b", variableD2);
			}
			{
				ScriptVariable variableD2(string("xxx"));
				variableD1.setMapValue("a", variableD2);
			}
			variableD0.setMapValue("test5", variableD1);
		}
		{
			ScriptVariable variableD1;
			variableD1.setType(TYPE_ARRAY);
			{
				ScriptVariable variableD2(static_cast<int64_t>(1ll));
				variableD1.pushArrayValue(variableD2);
			}
			{
				ScriptVariable variableD2(static_cast<int64_t>(2ll));
				variableD1.pushArrayValue(variableD2);
			}
			{
				ScriptVariable variableD2(static_cast<int64_t>(3ll));
				variableD1.pushArrayValue(variableD2);
			}
			variableD0.setMapValue("test4", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(789ll));
			variableD0.setMapValue("test3", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(456ll));
			variableD0.setMapValue("test2", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(123ll));
			variableD0.setMapValue("test1", variableD1);
		}
		return variableD0;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_18_0(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	{
		ScriptVariable variableD0;
		variableD0.setType(TYPE_SET);
		variableD0.insertSetKey("test1");
		variableD0.insertSetKey("test2");
		variableD0.insertSetKey("test3");
		variableD0.insertSetKey("test4");
		variableD0.insertSetKey("test5");
		return variableD0;
	}
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
