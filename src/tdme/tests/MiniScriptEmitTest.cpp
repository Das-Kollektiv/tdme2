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
	setNativeHash("55374f9dfd26193c0dda390e00be7f8b49458329ab3986507cfcd442463e14b3");
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
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
						-1
					),
					ScriptStatement(
						4,
						1,
						"console.log(\"emit-test: Initialize\")",
						"console.log(\"emit-test: Initialize\")",
						-1
					),
					ScriptStatement(
						5,
						2,
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
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
						"console.log(\"--------------------\")",
						"console.log(\"--------------------\")",
						-1
					),
					ScriptStatement(
						12,
						1,
						"console.log(\"emit-test: Nothing\")",
						"console.log(\"emit-test: Nothing\")",
						-1
					),
					ScriptStatement(
						13,
						2,
						"console.log(\"--------------------\")",
						"console.log(\"--------------------\")",
						-1
					),
					ScriptStatement(
						14,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						15,
						4,
						"console.log(\"--------------------------------------------------\")",
						"console.log(\"--------------------------------------------------\")",
						-1
					),
					ScriptStatement(
						16,
						5,
						"console.log(\"Test if enabled naming condition will be emitted\")",
						"console.log(\"Test if enabled naming condition will be emitted\")",
						-1
					),
					ScriptStatement(
						17,
						6,
						"console.log(\"--------------------------------------------------\")",
						"console.log(\"--------------------------------------------------\")",
						-1
					),
					ScriptStatement(
						18,
						7,
						"script.enableNamedCondition(\"named_condition_1\")",
						"script.enableNamedCondition(\"named_condition_1\")",
						-1
					),
					ScriptStatement(
						19,
						8,
						"script.wait(2000)",
						"script.wait(2000)",
						-1
					),
					ScriptStatement(
						20,
						9,
						"script.disableNamedCondition(\"named_condition_1\")",
						"script.disableNamedCondition(\"named_condition_1\")",
						-1
					),
					ScriptStatement(
						21,
						10,
						"console.log(\"---------------------------------------\")",
						"console.log(\"---------------------------------------\")",
						-1
					),
					ScriptStatement(
						22,
						11,
						"console.log(\"Naming condition has not been emitted\")",
						"console.log(\"Naming condition has not been emitted\")",
						-1
					),
					ScriptStatement(
						23,
						12,
						"console.log(\"---------------------------------------\")",
						"console.log(\"---------------------------------------\")",
						-1
					),
					ScriptStatement(
						24,
						13,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						25,
						14,
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
				28,
				"error",
				"error",
				ScriptStatement(
					28,
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
						29,
						0,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						30,
						1,
						"console.log(\"emit-test: Error\")",
						"console.log(\"emit-test: Error\")",
						-1
					),
					ScriptStatement(
						31,
						2,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						32,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						33,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						34,
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
			),
			Script(
				Script::SCRIPTTYPE_ON,
				37,
				"emittest",
				"emittest",
				ScriptStatement(
					37,
					0,
					"emittest",
					"emittest",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						38,
						0,
						"console.log(\"---------------------------------\")",
						"console.log(\"---------------------------------\")",
						-1
					),
					ScriptStatement(
						39,
						1,
						"console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						"console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						-1
					),
					ScriptStatement(
						40,
						2,
						"console.log(\"---------------------------------\")",
						"console.log(\"---------------------------------\")",
						-1
					),
					ScriptStatement(
						41,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						42,
						4,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						43,
						5,
						"console.log(\"Benchmark \")",
						"console.log(\"Benchmark \")",
						-1
					),
					ScriptStatement(
						44,
						6,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						45,
						7,
						"$startTime = time.getCurrentMillis()",
						"setVariable(\"$startTime\", time.getCurrentMillis())",
						-1
					),
					ScriptStatement(
						46,
						8,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						47,
						9,
						"$j = 0",
						"setVariable(\"$j\", 0)",
						-1
					),
					ScriptStatement(
						48,
						10,
						"$k = 0",
						"setVariable(\"$k\", 0)",
						-1
					),
					ScriptStatement(
						49,
						11,
						"forCondition($i < 500000)",
						"forCondition(lesser($i, 500000))",
						22
					),
					ScriptStatement(
						50,
						12,
						"$a = 123 + 456 * (25 / 12) + (7.5 * 12.25) - 8",
						"setVariable(\"$a\",sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))",
						-1
					),
					ScriptStatement(
						51,
						13,
						"if ($j == 0)",
						"if (equals($j, 0))",
						15
					),
					ScriptStatement(
						52,
						14,
						"++$k",
						"prefixIncrement($k)",
						-1
					),
					ScriptStatement(
						53,
						15,
						"end",
						"end",
						-1
					),
					ScriptStatement(
						54,
						16,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						55,
						17,
						"++$j",
						"prefixIncrement($j)",
						-1
					),
					ScriptStatement(
						56,
						18,
						"if ($j == 2)",
						"if (equals($j, 2))",
						20
					),
					ScriptStatement(
						57,
						19,
						"$j = 0",
						"setVariable(\"$j\", 0)",
						-1
					),
					ScriptStatement(
						58,
						20,
						"end",
						"end",
						-1
					),
					ScriptStatement(
						59,
						21,
						"end",
						"end",
						11
					),
					ScriptStatement(
						60,
						22,
						"$endTime = time.getCurrentMillis()",
						"setVariable(\"$endTime\", time.getCurrentMillis())",
						-1
					),
					ScriptStatement(
						61,
						23,
						"console.log(\"Finished. Time: \" + ($endTime - $startTime))",
						"console.log(add(\"Finished. Time: \", sub($endTime, $startTime)))",
						-1
					),
					ScriptStatement(
						62,
						24,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						63,
						25,
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
				Script::SCRIPTTYPE_ONENABLED,
				66,
				"true == true",
				"equals(true, true)",
				ScriptStatement(
					66,
					0,
					"true == true",
					"equals(true, true)",
					-1
				),
				{},
				"named_condition_1",
				false,
				{
					ScriptStatement(
						67,
						0,
						"script.disableNamedCondition(\"named_condition_1\")",
						"script.disableNamedCondition(\"named_condition_1\")",
						-1
					),
					ScriptStatement(
						68,
						1,
						"console.log(\"------------------------------------\")",
						"console.log(\"------------------------------------\")",
						-1
					),
					ScriptStatement(
						69,
						2,
						"console.log(\"named_condition_1 has been emitted\")",
						"console.log(\"named_condition_1 has been emitted\")",
						-1
					),
					ScriptStatement(
						70,
						3,
						"console.log(\"------------------------------------\")",
						"console.log(\"------------------------------------\")",
						-1
					),
					ScriptStatement(
						71,
						4,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						72,
						5,
						"console.log(\"-----------\")",
						"console.log(\"-----------\")",
						-1
					),
					ScriptStatement(
						73,
						6,
						"console.log(\"Test emit\")",
						"console.log(\"Test emit\")",
						-1
					),
					ScriptStatement(
						74,
						7,
						"console.log(\"-----------\")",
						"console.log(\"-----------\")",
						-1
					),
					ScriptStatement(
						75,
						8,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						76,
						9,
						"script.emit(emittest)",
						"script.emit(emittest)",
						-1
					),
					ScriptStatement(
						77,
						10,
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
void MiniScriptEmitTest::registerMethods() {
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

int MiniScriptEmitTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptEmitTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (const auto& enabledNamedCondition: enabledNamedConditions) {

		// next statements belong to tested enabled named condition with name "named_condition_1"
		if (enabledNamedCondition == "named_condition_1")
			// equals(1, 1)
			{
				// statement setup
				const ScriptStatement& statement = scripts[4].conditionStatement;
				getScriptState().statementIdx = statement.statementIdx;
				// required method code arguments
				ScriptVariable returnValue;
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(true),
					ScriptVariable(true)
				};
				array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
				// method code: equals
				if (argumentValues.size() != 2) {
					Console::println(string("equals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("equals")));
					miniScript->startErrorScript(); return -1;
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueAsString() != argumentValues[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
				bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return 4;
			}
	
	}

	//
	return SCRIPTIDX_NONE;
}

void MiniScriptEmitTest::emit(const string& condition) {
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
	if (condition == "emittest") {
		on_emittest(STATEMENTIDX_FIRST);
	} else
	{
		Console::println("MiniScriptEmitTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptEmitTest::on_initialize(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("emit-test: Initialize")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("emit-test: Initialize"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------------------"))
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

void MiniScriptEmitTest::on_nothing(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 9) goto miniscript_statement_9; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("--------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("--------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("emit-test: Nothing")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("emit-test: Nothing"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("--------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("--------------------"))
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
		const ScriptStatement& statement = scripts[1].statements[3];
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
	// console.log("--------------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("--------------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 5
	// console.log("Test if enabled naming condition will be emitted")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Test if enabled naming condition will be emitted"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 6
	// console.log("--------------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("--------------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 7
	// script.enableNamedCondition("named_condition_1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("named_condition_1"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
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
			Console::println(string("script.enableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.enableNamedCondition")));
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
	// statement: 8
	// script.wait(2000)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(2000ll))
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

	// enabled named conditions
	{
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != getScriptState().scriptIdx) {
		resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
		timeEnabledConditionsCheckLast = Time::getCurrentMillis();
		return;
		}
	}
	// statement: 9
	miniscript_statement_9:
	// script.disableNamedCondition("named_condition_1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("named_condition_1"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
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
			Console::println(string("script.disableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.disableNamedCondition")));
			miniScript->startErrorScript(); return;
		}
	}
	// statement: 10
	// console.log("---------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 11
	// console.log("Naming condition has not been emitted")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Naming condition has not been emitted"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 12
	// console.log("---------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 13
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[13];
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
	// statement: 14
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[14];
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

void MiniScriptEmitTest::on_error(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("emit-test: Error")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("emit-test: Error"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------"))
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

void MiniScriptEmitTest::on_emittest(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 12) goto miniscript_statement_12; else
	if (miniScriptGotoStatementIdx == 14) goto miniscript_statement_14; else
	if (miniScriptGotoStatementIdx == 16) goto miniscript_statement_16; else
	if (miniScriptGotoStatementIdx == 19) goto miniscript_statement_19; else
	if (miniScriptGotoStatementIdx == 21) goto miniscript_statement_21; else
	if (miniScriptGotoStatementIdx == 22) goto miniscript_statement_22; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_emittest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("---------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("SCRIPT JUST EMITTED A CONDITION")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("SCRIPT JUST EMITTED A CONDITION"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("---------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------"))
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
		const ScriptStatement& statement = scripts[3].statements[3];
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
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[4];
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
	// statement: 5
	// console.log("Benchmark ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Benchmark "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 6
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[6];
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
	// statement: 7
	// setVariable("$startTime", time.getCurrentMillis())
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$startTime")),
			ScriptVariable() // argumentValues[1] --> returnValue of time.getCurrentMillis()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: time.getCurrentMillis()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: time.getCurrentMillis
			returnValue.setValue(Time::getCurrentMillis());
		}
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
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[8];
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
	// statement: 9
	// setVariable("$j", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$j")),
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
	// statement: 10
	// setVariable("$k", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$k")),
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
	// statement: 11
	miniscript_statement_11:
	// forCondition(lesser(getVariable("$i"), 500000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$i"), 500000)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$i"), 500000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(500000ll))
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
	// statement: 12
	miniscript_statement_12:
	// setVariable("$a", sub(add(123, add(mul(456, div(25, 12)), mul(7.500000, 12.250000))), 8))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$a")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(add(123, add(mul(456, div(25, 12)), mul(7.500000, 12.250000))), 8)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(add(123, add(mul(456, div(25, 12)), mul(7.500000, 12.250000))), 8)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of add(123, add(mul(456, div(25, 12)), mul(7.500000, 12.250000)))
				ScriptVariable(static_cast<int64_t>(8ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: add(123, add(mul(456, div(25, 12)), mul(7.500000, 12.250000)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(123ll)),
					ScriptVariable() // argumentValues[1] --> returnValue of add(mul(456, div(25, 12)), mul(7.500000, 12.250000))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 1: add(mul(456, div(25, 12)), mul(7.500000, 12.250000))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(), // argumentValues[0] --> returnValue of mul(456, div(25, 12))
						ScriptVariable() // argumentValues[1] --> returnValue of mul(7.500000, 12.250000)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 0: mul(456, div(25, 12))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(static_cast<int64_t>(456ll)),
							ScriptVariable() // argumentValues[1] --> returnValue of div(25, 12)
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX0 = argumentValues;
						// depth = 5 / argument index = 1: div(25, 12)
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX0[1];
							array<ScriptVariable, 2> argumentValues {
								ScriptVariable(static_cast<int64_t>(25ll)),
								ScriptVariable(static_cast<int64_t>(12ll))
							};
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							// method code: div
							MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
						}
						// method code: mul
						MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
					}
					// depth = 4 / argument index = 1: mul(7.500000, 12.250000)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(7.500000f),
							ScriptVariable(12.250000f)
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
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
			Console::println(string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("setVariable")));
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}
	// statement: 13
	// if(equals(getVariable("$j"), 0))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$j"), 0)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$j"), 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$j")
				ScriptVariable(static_cast<int64_t>(0ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$j")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$j"))
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
				goto miniscript_statement_15;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 14
	miniscript_statement_14:
	// prefixIncrement(getVariable("$k"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$k")
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$k")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$k"))
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
			setVariable("$k", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		} else {
			++value;
			argumentValues[0] = value;
			returnValue.setValue(value);
		}
		// assign back
		setVariable("$k", argumentValues[0], &statement);
		//
	}
	// statement: 15
	miniscript_statement_15:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[15];
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
	// statement: 16
	miniscript_statement_16:
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[16];
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
	// statement: 17
	// prefixIncrement(getVariable("$j"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$j")
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$j")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$j"))
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
			setVariable("$j", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		} else {
			++value;
			argumentValues[0] = value;
			returnValue.setValue(value);
		}
		// assign back
		setVariable("$j", argumentValues[0], &statement);
		//
	}
	// statement: 18
	// if(equals(getVariable("$j"), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[18];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$j"), 2)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$j"), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$j")
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$j")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$j"))
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
				goto miniscript_statement_20;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 19
	miniscript_statement_19:
	// setVariable("$j", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$j")),
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
	// statement: 20
	miniscript_statement_20:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[20];
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
	// statement: 21
	miniscript_statement_21:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[21];
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
	// statement: 22
	miniscript_statement_22:
	// setVariable("$endTime", time.getCurrentMillis())
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[22];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$endTime")),
			ScriptVariable() // argumentValues[1] --> returnValue of time.getCurrentMillis()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: time.getCurrentMillis()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: time.getCurrentMillis
			returnValue.setValue(Time::getCurrentMillis());
		}
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
	// statement: 23
	// console.log(add("Finished. Time: ", sub(getVariable("$endTime"), getVariable("$startTime"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[23];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("Finished. Time: ", sub(getVariable("$endTime"), getVariable("$startTime")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("Finished. Time: ", sub(getVariable("$endTime"), getVariable("$startTime")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("Finished. Time: ")),
				ScriptVariable() // argumentValues[1] --> returnValue of sub(getVariable("$endTime"), getVariable("$startTime"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: sub(getVariable("$endTime"), getVariable("$startTime"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$endTime")
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$startTime")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$endTime")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$endTime"))
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
				// depth = 3 / argument index = 1: getVariable("$startTime")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$startTime"))
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
				// method code: sub
				MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
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
	// statement: 24
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[24];
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
	// statement: 25
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[25];
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

void MiniScriptEmitTest::on_enabled_named_condition_1(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_enabled_named_condition_1(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// script.disableNamedCondition("named_condition_1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("named_condition_1"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
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
			Console::println(string("script.disableNamedCondition") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.disableNamedCondition")));
			miniScript->startErrorScript(); return;
		}
	}
	// statement: 1
	// console.log("------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("named_condition_1 has been emitted")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("named_condition_1 has been emitted"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 3
	// console.log("------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[3];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 4
	// console.log()
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[4];
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
	// statement: 5
	// console.log("-----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 6
	// console.log("Test emit")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[6];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Test emit"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 7
	// console.log("-----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 8
	// console.log()
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[8];
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
	// statement: 9
	// script.emit("emittest")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("emittest"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: script.emit
		string condition;
		if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
			miniScript->emit(condition); return;
		} else {
			Console::println(string("script.emit") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("script.emit")));
			miniScript->startErrorScript(); return;
		}
	}
	// statement: 10
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[10];
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
