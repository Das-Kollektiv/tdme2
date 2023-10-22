#include "MiniScriptClassTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptClassTest::MiniScriptClassTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/

#define __MINISCRIPT_TRANSPILATION__

void MiniScriptClassTest::initializeNative() {
	setNative(true);
	setNativeHash("1c5f81bd83413beb183a547f8c0336831a86def9fb353c3d3a458f25d1a6f66d");
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
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						4,
						1,
						"console.log(\"class-test: Initialize\")",
						"console.log(\"class-test: Initialize\")",
						-1
					),
					ScriptStatement(
						5,
						2,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
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
				9,
				"printABC",
				"printABC",
				ScriptStatement(
					9,
					0,
					"printABC",
					"printABC",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						10,
						0,
						"console.log(\"printABC(): \" +\"a: \" + $this.a + \", \" +\"b: \" + $this.b + \", \" +\"c: \" + $this.c + \", \" +\"a*b*c: \" + ($this.a * $this.b * $this.c))",
						"console.log(add(\"printABC(): \",add(\"a: \",add($this.a,add(\", \",add(\"b: \",add($this.b,add(\", \",add(\"c: \",add($this.c,add(\", \",add(\"a*b*c: \",mul($this.a,mul($this.b, $this.c))))))))))))))",
						-1
					),
					ScriptStatement(
						17,
						1,
						"$this.c = $this.c + 1",
						"setVariable(\"$this.c\",add($this.c, 1))",
						-1
					),
					ScriptStatement(
						18,
						2,
						"end",
						"end",
						-1
					)
				},
				{},
				false,
				{
					Script::ScriptArgument(
						"$this",
						true
					)
				}
			),
			Script(
				Script::SCRIPTTYPE_ON,
				21,
				"nothing",
				"nothing",
				ScriptStatement(
					21,
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
						22,
						0,
						"console.log(\"---------------------\")",
						"console.log(\"---------------------\")",
						-1
					),
					ScriptStatement(
						23,
						1,
						"console.log(\"class-test: Nothing\")",
						"console.log(\"class-test: Nothing\")",
						-1
					),
					ScriptStatement(
						24,
						2,
						"console.log(\"---------------------\")",
						"console.log(\"---------------------\")",
						-1
					),
					ScriptStatement(
						25,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						27,
						4,
						"$class = {a: 1,b: 2,c: 3,printABC: () -> printABC}",
						"setVariable(\"$class\", {a: 1,b: 2,c: 3,printABC: () -> printABC})",
						-1
					),
					ScriptStatement(
						35,
						5,
						"console.dump($class)",
						"console.dump($class)",
						-1
					),
					ScriptStatement(
						37,
						6,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						38,
						7,
						"forCondition($i < 5)",
						"forCondition(lesser($i, 5))",
						11
					),
					ScriptStatement(
						39,
						8,
						"$class->printABC()",
						"$class->printABC()",
						-1
					),
					ScriptStatement(
						40,
						9,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						41,
						10,
						"end",
						"end",
						7
					),
					ScriptStatement(
						43,
						11,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						44,
						12,
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
				47,
				"error",
				"error",
				ScriptStatement(
					47,
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
						48,
						0,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						49,
						1,
						"console.log(\"class-test: Error\")",
						"console.log(\"class-test: Error\")",
						-1
					),
					ScriptStatement(
						50,
						2,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						51,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						52,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						53,
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
				"printABC",
				1
			}
		}
	);
}
void MiniScriptClassTest::registerMethods() {
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

int MiniScriptClassTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 2;
}

int MiniScriptClassTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (const auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return SCRIPTIDX_NONE;
}

void MiniScriptClassTest::emit(const string& condition) {
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
		Console::println("MiniScriptClassTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptClassTest::on_initialize(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("class-test: Initialize")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("class-test: Initialize"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("------------------------"))
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

void MiniScriptClassTest::printABC(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::printABC(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log(add("printABC(): ", add("a: ", add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))))))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("printABC(): ", add("a: ", add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("printABC(): ", add("a: ", add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("printABC(): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add("a: ", add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))))))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add("a: ", add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))))))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("a: ")),
					ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: add(getVariable("$this.a"), add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.a")
						ScriptVariable() // argumentValues[1] --> returnValue of add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 0: getVariable("$this.a")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$this.a"))
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
					// depth = 4 / argument index = 1: add(", ", add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))))
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(string(", ")),
							ScriptVariable() // argumentValues[1] --> returnValue of add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// depth = 5 / argument index = 1: add("b: ", add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))))
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[1];
							array<ScriptVariable, 2> argumentValues {
								ScriptVariable(string("b: ")),
								ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))
							};
							array<ScriptVariable, 2>& argumentValuesD5AIDX1 = argumentValues;
							// depth = 6 / argument index = 1: add(getVariable("$this.b"), add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))))
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX1[1];
								array<ScriptVariable, 2> argumentValues {
									ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.b")
									ScriptVariable() // argumentValues[1] --> returnValue of add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))
								};
								array<ScriptVariable, 2>& argumentValuesD6AIDX1 = argumentValues;
								// depth = 7 / argument index = 0: getVariable("$this.b")
								{
									// required method code arguments
									ScriptVariable& returnValue = argumentValuesD6AIDX1[0];
									array<ScriptVariable, 1> argumentValues {
										ScriptVariable(string("$this.b"))
									};
									array<ScriptVariable, 1>& argumentValuesD7AIDX0 = argumentValues;
									// method code: getVariable
									string variable;
									if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
										returnValue = miniScript->getVariable(variable, &statement);
									} else {
										Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
										miniScript->startErrorScript(); return;
									}
								}
								// depth = 7 / argument index = 1: add(", ", add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))))
								{
									// required method code arguments
									ScriptVariable& returnValue = argumentValuesD6AIDX1[1];
									array<ScriptVariable, 2> argumentValues {
										ScriptVariable(string(", ")),
										ScriptVariable() // argumentValues[1] --> returnValue of add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))
									};
									array<ScriptVariable, 2>& argumentValuesD7AIDX1 = argumentValues;
									// depth = 8 / argument index = 1: add("c: ", add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))))
									{
										// required method code arguments
										ScriptVariable& returnValue = argumentValuesD7AIDX1[1];
										array<ScriptVariable, 2> argumentValues {
											ScriptVariable(string("c: ")),
											ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))
										};
										array<ScriptVariable, 2>& argumentValuesD8AIDX1 = argumentValues;
										// depth = 9 / argument index = 1: add(getVariable("$this.c"), add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))))
										{
											// required method code arguments
											ScriptVariable& returnValue = argumentValuesD8AIDX1[1];
											array<ScriptVariable, 2> argumentValues {
												ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.c")
												ScriptVariable() // argumentValues[1] --> returnValue of add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))
											};
											array<ScriptVariable, 2>& argumentValuesD9AIDX1 = argumentValues;
											// depth = 10 / argument index = 0: getVariable("$this.c")
											{
												// required method code arguments
												ScriptVariable& returnValue = argumentValuesD9AIDX1[0];
												array<ScriptVariable, 1> argumentValues {
													ScriptVariable(string("$this.c"))
												};
												array<ScriptVariable, 1>& argumentValuesD10AIDX0 = argumentValues;
												// method code: getVariable
												string variable;
												if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
													returnValue = miniScript->getVariable(variable, &statement);
												} else {
													Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
													miniScript->startErrorScript(); return;
												}
											}
											// depth = 10 / argument index = 1: add(", ", add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))))
											{
												// required method code arguments
												ScriptVariable& returnValue = argumentValuesD9AIDX1[1];
												array<ScriptVariable, 2> argumentValues {
													ScriptVariable(string(", ")),
													ScriptVariable() // argumentValues[1] --> returnValue of add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))
												};
												array<ScriptVariable, 2>& argumentValuesD10AIDX1 = argumentValues;
												// depth = 11 / argument index = 1: add("a*b*c: ", mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c"))))
												{
													// required method code arguments
													ScriptVariable& returnValue = argumentValuesD10AIDX1[1];
													array<ScriptVariable, 2> argumentValues {
														ScriptVariable(string("a*b*c: ")),
														ScriptVariable() // argumentValues[1] --> returnValue of mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))
													};
													array<ScriptVariable, 2>& argumentValuesD11AIDX1 = argumentValues;
													// depth = 12 / argument index = 1: mul(getVariable("$this.a"), mul(getVariable("$this.b"), getVariable("$this.c")))
													{
														// required method code arguments
														ScriptVariable& returnValue = argumentValuesD11AIDX1[1];
														array<ScriptVariable, 2> argumentValues {
															ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.a")
															ScriptVariable() // argumentValues[1] --> returnValue of mul(getVariable("$this.b"), getVariable("$this.c"))
														};
														array<ScriptVariable, 2>& argumentValuesD12AIDX1 = argumentValues;
														// depth = 13 / argument index = 0: getVariable("$this.a")
														{
															// required method code arguments
															ScriptVariable& returnValue = argumentValuesD12AIDX1[0];
															array<ScriptVariable, 1> argumentValues {
																ScriptVariable(string("$this.a"))
															};
															array<ScriptVariable, 1>& argumentValuesD13AIDX0 = argumentValues;
															// method code: getVariable
															string variable;
															if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
																returnValue = miniScript->getVariable(variable, &statement);
															} else {
																Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
																miniScript->startErrorScript(); return;
															}
														}
														// depth = 13 / argument index = 1: mul(getVariable("$this.b"), getVariable("$this.c"))
														{
															// required method code arguments
															ScriptVariable& returnValue = argumentValuesD12AIDX1[1];
															array<ScriptVariable, 2> argumentValues {
																ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.b")
																ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$this.c")
															};
															array<ScriptVariable, 2>& argumentValuesD13AIDX1 = argumentValues;
															// depth = 14 / argument index = 0: getVariable("$this.b")
															{
																// required method code arguments
																ScriptVariable& returnValue = argumentValuesD13AIDX1[0];
																array<ScriptVariable, 1> argumentValues {
																	ScriptVariable(string("$this.b"))
																};
																array<ScriptVariable, 1>& argumentValuesD14AIDX0 = argumentValues;
																// method code: getVariable
																string variable;
																if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
																	returnValue = miniScript->getVariable(variable, &statement);
																} else {
																	Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
																	miniScript->startErrorScript(); return;
																}
															}
															// depth = 14 / argument index = 1: getVariable("$this.c")
															{
																// required method code arguments
																ScriptVariable& returnValue = argumentValuesD13AIDX1[1];
																array<ScriptVariable, 1> argumentValues {
																	ScriptVariable(string("$this.c"))
																};
																array<ScriptVariable, 1>& argumentValuesD14AIDX1 = argumentValues;
																// method code: getVariable
																string variable;
																if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
																	returnValue = miniScript->getVariable(variable, &statement);
																} else {
																	Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
																	miniScript->startErrorScript(); return;
																}
															}
															// method code: mul
															MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
														}
														// method code: mul
														MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
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
	// setVariable("$this.c", add(getVariable("$this.c"), 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$this.c")),
			ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$this.c"), 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: add(getVariable("$this.c"), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$this.c")
				ScriptVariable(static_cast<int64_t>(1ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$this.c")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$this.c"))
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
			// method code: add
			MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
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
	// statement: 2
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[2];
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

void MiniScriptClassTest::on_nothing(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 8) goto miniscript_statement_8; else
	if (miniScriptGotoStatementIdx == 11) goto miniscript_statement_11; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("---------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 1
	// console.log("class-test: Nothing")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("class-test: Nothing"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 2
	// console.log("---------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------"))
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
		const ScriptStatement& statement = scripts[2].statements[3];
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
	// setVariable("$class", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$class")),
			on_nothing_initializer_s_4_1(statement)
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
	// statement: 5
	// console.dump(getVariable("$class"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$class")
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$class")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$class"))
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
		// method code: console.dump
		if (argumentValues.size() != 1) {
			Console::println(string("console.dump") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("console.dump")));
			miniScript->startErrorScript(); return;
		} else {
			Console::println(argumentValues[0].getValueAsString(true));
		}
	}
	// statement: 6
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[6];
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
	// statement: 7
	miniscript_statement_7:
	// forCondition(lesser(getVariable("$i"), 5))
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$i"), 5)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$i"), 5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(5ll))
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
				goto miniscript_statement_11;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 8
	miniscript_statement_8:
	// internal.script.evaluateMemberAccess("$class", getVariable("$class"), "printABC")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues {
			ScriptVariable(string("$class")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$class")
			ScriptVariable(string("printABC"))
		};
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$class")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$class"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_NONE;
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
							// check if map, if so fetch function assignment of member property
							auto functionIdx = MiniScript::SCRIPTIDX_NONE;
							if (argumentValues[1].getType() == TYPE_MAP) {
								string function;
								auto mapValue = argumentValues[1].getMapValue(member);
								if (mapValue.getType() == MiniScript::TYPE_FUNCTION_ASSIGNMENT && mapValue.getStringValue(function) == true) {
									functionIdx = miniScript->getFunctionScriptIdx(function);
								}
							}
							//
							const auto& className = ScriptVariable::getClassName(argumentValues[1].getType());
							//
							if (className.empty() == false || functionIdx != MiniScript::SCRIPTIDX_NONE) {
								ScriptMethod* method { nullptr };
								if (functionIdx == MiniScript::SCRIPTIDX_NONE) {
									#if defined(__MINISCRIPT_TRANSPILATION__)
										method = evaluateMemberAccessArrays[static_cast<int>(argumentValues[1].getType()) - static_cast<int>(MiniScript::TYPE_STRING)][EVALUATEMEMBERACCESS_MEMBER];
									#else
										method = miniScript->getMethod(className + "." + member);
									#endif
								}
								if (method != nullptr || functionIdx != MiniScript::SCRIPTIDX_NONE) {
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
									if (method != nullptr) {
										method->executeMethod(callArgumentValuesSpan, returnValue, statement);
									} else
									if (functionIdx != MiniScript::SCRIPTIDX_NONE) {
										miniScript->call(functionIdx, callArgumentValuesSpan, returnValue);
									}
									// assign back variables
									{
										auto argumentIdx = 0;
		
										//
										auto assignBack = [&]() {
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
										};
		
										// method
										if (method != nullptr) {
											for (const auto& argument: method->getArgumentTypes()) {
												if (argument.assignBack == false) {
													argumentIdx++;
													continue;
												}
												//
												assignBack();
												//
												argumentIdx++;
											}
										} else
										if (functionIdx != MiniScript::SCRIPTIDX_NONE) {
											const auto& script = miniScript->getScripts()[functionIdx];
											for (const auto& argument: script.arguments) {
												if (argument.assignBack == false) {
													argumentIdx++;
													continue;
												}
												//
												assignBack();
												//
												argumentIdx++;
											}
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
	// statement: 9
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[9];
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
	// statement: 10
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[10];
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
				goto miniscript_statement_7;
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
	// statement: 11
	miniscript_statement_11:
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[11];
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
	// statement: 12
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[12];
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

void MiniScriptClassTest::on_error(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[0];
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
	// console.log("class-test: Error")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("class-test: Error"))
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
		const ScriptStatement& statement = scripts[3].statements[2];
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
		const ScriptStatement& statement = scripts[3].statements[3];
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
		const ScriptStatement& statement = scripts[3].statements[4];
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
		const ScriptStatement& statement = scripts[3].statements[5];
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


inline MiniScript::ScriptVariable MiniScriptClassTest::on_nothing_initializer_s_4_1(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	{
		ScriptVariable variableD0;
		variableD0.setType(TYPE_MAP);
		{
			ScriptVariable variableD1;
			variableD1.setFunctionAssignment("printABC");
			variableD0.setMapValue("printABC", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(3ll));
			variableD0.setMapValue("c", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(2ll));
			variableD0.setMapValue("b", variableD1);
		}
		{
			ScriptVariable variableD1(static_cast<int64_t>(1ll));
			variableD0.setMapValue("a", variableD1);
		}
		return variableD0;
	}
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
