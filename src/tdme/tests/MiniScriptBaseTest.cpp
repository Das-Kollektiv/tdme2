#include "MiniScriptBaseTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptBaseTest::MiniScriptBaseTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/

#define __MINISCRIPT_TRANSPILATION__

void MiniScriptBaseTest::initializeNative() {
	setNative(true);
	setNativeHash("f1486e34cc1e491d9d53c8d650820a51cc13b5eb5d27e2fab80f0c7505729495");
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
						"console.log(\"base-test: Initialize\")",
						"console.log(\"base-test: Initialize\")",
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
						"console.log(\"base-test: Nothing\")",
						"console.log(\"base-test: Nothing\")",
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
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
						-1
					),
					ScriptStatement(
						16,
						5,
						"console.log(\"Check bool operations\")",
						"console.log(\"Check bool operations\")",
						-1
					),
					ScriptStatement(
						17,
						6,
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
						-1
					),
					ScriptStatement(
						18,
						7,
						"console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						"console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						-1
					),
					ScriptStatement(
						19,
						8,
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
						-1
					),
					ScriptStatement(
						20,
						9,
						"console.log(\"Check int computation\")",
						"console.log(\"Check int computation\")",
						-1
					),
					ScriptStatement(
						21,
						10,
						"console.log(\"-----------------------\")",
						"console.log(\"-----------------------\")",
						-1
					),
					ScriptStatement(
						22,
						11,
						"console.log(\"1 + 2 + 3 - 1: \", 1 + 2 + 3 - 1)",
						"console.log(\"1 + 2 + 3 - 1: \",sub(add(1,add(2, 3)), 1))",
						-1
					),
					ScriptStatement(
						23,
						12,
						"console.log(\"20 / 2: \", 20 / 2)",
						"console.log(\"20 / 2: \",div(20, 2))",
						-1
					),
					ScriptStatement(
						24,
						13,
						"console.log(\"11 * 10: \", 11 * 10)",
						"console.log(\"11 * 10: \",mul(11, 10))",
						-1
					),
					ScriptStatement(
						25,
						14,
						"console.log(\"2 > 1: \", 2 > 1)",
						"console.log(\"2 > 1: \",greater(2, 1))",
						-1
					),
					ScriptStatement(
						26,
						15,
						"console.log(\"2 < 1: \", 2 < 1)",
						"console.log(\"2 < 1: \",lesser(2, 1))",
						-1
					),
					ScriptStatement(
						27,
						16,
						"console.log(\"7 % 4: \", 7 % 4)",
						"console.log(\"7 % 4: \",mod(7, 4))",
						-1
					),
					ScriptStatement(
						28,
						17,
						"$i = 2",
						"setVariable(\"$i\", 2)",
						-1
					),
					ScriptStatement(
						29,
						18,
						"console.log(\"$i = 2 && ++$i: \", ++$i)",
						"console.log(\"$i = 2 && ++$i: \", prefixIncrement($i))",
						-1
					),
					ScriptStatement(
						30,
						19,
						"$i = 2",
						"setVariable(\"$i\", 2)",
						-1
					),
					ScriptStatement(
						31,
						20,
						"console.log(\"$i = 2 && --$i: \", --$i)",
						"console.log(\"$i = 2 && --$i: \", prefixDecrement($i))",
						-1
					),
					ScriptStatement(
						32,
						21,
						"console.log(\"--------------------------\")",
						"console.log(\"--------------------------\")",
						-1
					),
					ScriptStatement(
						33,
						22,
						"console.log(\"Check int bit operations\")",
						"console.log(\"Check int bit operations\")",
						-1
					),
					ScriptStatement(
						34,
						23,
						"console.log(\"--------------------------\")",
						"console.log(\"--------------------------\")",
						-1
					),
					ScriptStatement(
						35,
						24,
						"console.log(\"~1 & 255: \", ~1 & 255)",
						"console.log(\"~1 & 255: \",bitwiseAnd(bitwiseNot(1), 255))",
						-1
					),
					ScriptStatement(
						36,
						25,
						"console.log(\"~0 & 255: \", ~0 & 255)",
						"console.log(\"~0 & 255: \",bitwiseAnd(bitwiseNot(0), 255))",
						-1
					),
					ScriptStatement(
						37,
						26,
						"console.log(\"128 | 64: \", 128 | 64)",
						"console.log(\"128 | 64: \",bitwiseOr(128, 64))",
						-1
					),
					ScriptStatement(
						38,
						27,
						"console.log(\"128 ^ 64: \", 128 ^ 64)",
						"console.log(\"128 ^ 64: \",bitwiseXor(128, 64))",
						-1
					),
					ScriptStatement(
						39,
						28,
						"console.log(\"64 ^ 64: \", 64 ^ 64)",
						"console.log(\"64 ^ 64: \",bitwiseXor(64, 64))",
						-1
					),
					ScriptStatement(
						40,
						29,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						41,
						30,
						"console.log(\"Check float computation\")",
						"console.log(\"Check float computation\")",
						-1
					),
					ScriptStatement(
						42,
						31,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						43,
						32,
						"console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \", (1.1 + 2.2 + 3.3) - 1.2)",
						"console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \",sub(add(1.1,add(2.2, 3.3)), 1.2))",
						-1
					),
					ScriptStatement(
						44,
						33,
						"console.log(\"20 / 1.5: \", 20 / 1.5)",
						"console.log(\"20 / 1.5: \",div(20, 1.5))",
						-1
					),
					ScriptStatement(
						45,
						34,
						"console.log(\"11.5 * 10.5: \", 11.5 * 10.5)",
						"console.log(\"11.5 * 10.5: \",mul(11.5, 10.5))",
						-1
					),
					ScriptStatement(
						46,
						35,
						"console.log(\"2.2 > 1.3: \", 2.2 > 1.3)",
						"console.log(\"2.2 > 1.3: \",greater(2.2, 1.3))",
						-1
					),
					ScriptStatement(
						47,
						36,
						"console.log(\"2.5 < 1.2: \", 2.5 < 1.2)",
						"console.log(\"2.5 < 1.2: \",lesser(2.5, 1.2))",
						-1
					),
					ScriptStatement(
						48,
						37,
						"console.log(\"7.1 % 4.0: \", 7.1 % 4.0)",
						"console.log(\"7.1 % 4.0: \",mod(7.1, 4.0))",
						-1
					),
					ScriptStatement(
						49,
						38,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						50,
						39,
						"console.log(\"Check vector2 math\")",
						"console.log(\"Check vector2 math\")",
						-1
					),
					ScriptStatement(
						51,
						40,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						52,
						41,
						"console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						"console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						-1
					),
					ScriptStatement(
						53,
						42,
						"console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						"console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						-1
					),
					ScriptStatement(
						54,
						43,
						"console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						"console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						-1
					),
					ScriptStatement(
						55,
						44,
						"console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						"console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						-1
					),
					ScriptStatement(
						56,
						45,
						"console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						"console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						-1
					),
					ScriptStatement(
						57,
						46,
						"console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						"console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						-1
					),
					ScriptStatement(
						58,
						47,
						"console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \", vec2(1.1, 2.2) - vec2(1.2, 1.0))",
						"console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \",sub(vec2(1.1, 2.2), vec2(1.2, 1.0)))",
						-1
					),
					ScriptStatement(
						59,
						48,
						"console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \", vec2(20, 10) / vec2(1.5, 2.5))",
						"console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \",div(vec2(20, 10), vec2(1.5, 2.5)))",
						-1
					),
					ScriptStatement(
						60,
						49,
						"console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \", vec2(20, 10) * vec2(1.5, 2.5))",
						"console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \",mul(vec2(20, 10), vec2(1.5, 2.5)))",
						-1
					),
					ScriptStatement(
						61,
						50,
						"console.log(\"vec2(20, 10) / 2): \", vec2(20, 10) / 2)",
						"console.log(\"vec2(20, 10) / 2): \",div(vec2(20, 10), 2))",
						-1
					),
					ScriptStatement(
						62,
						51,
						"console.log(\"vec2(20, 10) * 2): \", vec2(20, 10) * 2)",
						"console.log(\"vec2(20, 10) * 2): \",mul(vec2(20, 10), 2))",
						-1
					),
					ScriptStatement(
						63,
						52,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						64,
						53,
						"console.log(\"Check vector3 math\")",
						"console.log(\"Check vector3 math\")",
						-1
					),
					ScriptStatement(
						65,
						54,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						66,
						55,
						"console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						"console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						-1
					),
					ScriptStatement(
						67,
						56,
						"console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						"console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						-1
					),
					ScriptStatement(
						68,
						57,
						"console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						"console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						-1
					),
					ScriptStatement(
						69,
						58,
						"console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						"console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						-1
					),
					ScriptStatement(
						70,
						59,
						"console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						"console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						-1
					),
					ScriptStatement(
						71,
						60,
						"console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						"console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						-1
					),
					ScriptStatement(
						72,
						61,
						"console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						"console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						-1
					),
					ScriptStatement(
						73,
						62,
						"console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						"console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						-1
					),
					ScriptStatement(
						74,
						63,
						"console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						"console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						-1
					),
					ScriptStatement(
						75,
						64,
						"console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \", vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0))",
						"console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \",sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))",
						-1
					),
					ScriptStatement(
						76,
						65,
						"console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \", vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5))",
						"console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \",div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						-1
					),
					ScriptStatement(
						77,
						66,
						"console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \", vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5))",
						"console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \",mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						-1
					),
					ScriptStatement(
						78,
						67,
						"console.log(\"vec3(20, 10, 5) / 2): \", vec3(20, 10, 5) / 2)",
						"console.log(\"vec3(20, 10, 5) / 2): \",div(vec3(20, 10, 5), 2))",
						-1
					),
					ScriptStatement(
						79,
						68,
						"console.log(\"vec3(20, 10, 5) * 2): \", vec3(20, 10, 5) * 2)",
						"console.log(\"vec3(20, 10, 5) * 2): \",mul(vec3(20, 10, 5), 2))",
						-1
					),
					ScriptStatement(
						80,
						69,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						81,
						70,
						"console.log(\"Check vector4 math\")",
						"console.log(\"Check vector4 math\")",
						-1
					),
					ScriptStatement(
						82,
						71,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						83,
						72,
						"console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						"console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						-1
					),
					ScriptStatement(
						84,
						73,
						"console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						"console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						-1
					),
					ScriptStatement(
						85,
						74,
						"console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						"console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						-1
					),
					ScriptStatement(
						86,
						75,
						"console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						"console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						-1
					),
					ScriptStatement(
						87,
						76,
						"console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						"console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						-1
					),
					ScriptStatement(
						88,
						77,
						"console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						"console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						-1
					),
					ScriptStatement(
						89,
						78,
						"console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						"console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						-1
					),
					ScriptStatement(
						90,
						79,
						"console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						"console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						-1
					),
					ScriptStatement(
						91,
						80,
						"console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \", vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0))",
						"console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \",sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0)))",
						-1
					),
					ScriptStatement(
						92,
						81,
						"console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \", vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1))",
						"console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \",div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						-1
					),
					ScriptStatement(
						93,
						82,
						"console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \", vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1))",
						"console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \",mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						-1
					),
					ScriptStatement(
						94,
						83,
						"console.log(\"vec4(20, 10, 5, 1) / 2): \", vec4(20, 10, 5, 1) / 2)",
						"console.log(\"vec4(20, 10, 5, 1) / 2): \",div(vec4(20, 10, 5, 1), 2))",
						-1
					),
					ScriptStatement(
						95,
						84,
						"console.log(\"vec4(20, 10, 5, 1) * 2): \", vec4(20, 10, 5, 1) * 2)",
						"console.log(\"vec4(20, 10, 5, 1) * 2): \",mul(vec4(20, 10, 5, 1), 2))",
						-1
					),
					ScriptStatement(
						96,
						85,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						97,
						86,
						"console.log(\"Check quaternion math\")",
						"console.log(\"Check quaternion math\")",
						-1
					),
					ScriptStatement(
						98,
						87,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						99,
						88,
						"console.log(\"quaternion.identity(): \", quaternion.identity())",
						"console.log(\"quaternion.identity(): \", quaternion.identity())",
						-1
					),
					ScriptStatement(
						100,
						89,
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						-1
					),
					ScriptStatement(
						101,
						90,
						"console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						"console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						-1
					),
					ScriptStatement(
						102,
						91,
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0))",
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0): \",mul(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						-1
					),
					ScriptStatement(
						103,
						92,
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0)): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0))",
						"console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0)): \",mul(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						-1
					),
					ScriptStatement(
						104,
						93,
						"console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						"console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						-1
					),
					ScriptStatement(
						105,
						94,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						106,
						95,
						"console.log(\"Check matrix4x4 math\")",
						"console.log(\"Check matrix4x4 math\")",
						-1
					),
					ScriptStatement(
						107,
						96,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						108,
						97,
						"console.log(\"mat4.identity(): \", mat4.identity())",
						"console.log(\"mat4.identity(): \", mat4.identity())",
						-1
					),
					ScriptStatement(
						109,
						98,
						"console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						"console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						-1
					),
					ScriptStatement(
						110,
						99,
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						-1
					),
					ScriptStatement(
						111,
						100,
						"console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						"console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						-1
					),
					ScriptStatement(
						112,
						101,
						"console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						"console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						-1
					),
					ScriptStatement(
						113,
						102,
						"console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						"console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						-1
					),
					ScriptStatement(
						114,
						103,
						"console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						"console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						-1
					),
					ScriptStatement(
						115,
						104,
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0))",
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0): \",mul(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						-1
					),
					ScriptStatement(
						116,
						105,
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0))",
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0): \",mul(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						-1
					),
					ScriptStatement(
						117,
						106,
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.translate(vec3(1.0, 2.0, 3.0)) *  vec4(0.0, 0.0, 1.0, 0.0)): \", (mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.translate(vec3(1.0, 2.0, 3.0))) * vec4(0.0, 0.0, 1.0, 0.0))",
						"console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.translate(vec3(1.0, 2.0, 3.0)) *  vec4(0.0, 0.0, 1.0, 0.0)): \",mul(mul(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))",
						-1
					),
					ScriptStatement(
						118,
						107,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						119,
						108,
						"console.log(\"Check matrix3x3 math\")",
						"console.log(\"Check matrix3x3 math\")",
						-1
					),
					ScriptStatement(
						120,
						109,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						121,
						110,
						"console.log(\"mat3.identity(): \", mat3.identity())",
						"console.log(\"mat3.identity(): \", mat3.identity())",
						-1
					),
					ScriptStatement(
						122,
						111,
						"console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						"console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						-1
					),
					ScriptStatement(
						123,
						112,
						"console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						"console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						-1
					),
					ScriptStatement(
						124,
						113,
						"console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						"console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						-1
					),
					ScriptStatement(
						125,
						114,
						"console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						"console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						-1
					),
					ScriptStatement(
						126,
						115,
						"console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						"console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						-1
					),
					ScriptStatement(
						127,
						116,
						"console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						"console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						-1
					),
					ScriptStatement(
						128,
						117,
						"console.log(\"mat3.rotate(90.0) * mat3.translate(vec2(1.0, 2.0)): \", mat3.rotate(90.0) * mat3.translate(vec2(1.0, 2.0)))",
						"console.log(\"mat3.rotate(90.0) * mat3.translate(vec2(1.0, 2.0)): \",mul(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))",
						-1
					),
					ScriptStatement(
						129,
						118,
						"console.log(\"mat3.rotate(90.0) * vec2(1.0, 2.0): \", mat3.rotate(90.0) * vec2(1.0, 2.0))",
						"console.log(\"mat3.rotate(90.0) * vec2(1.0, 2.0): \",mul(mat3.rotate(90.0), vec2(1.0, 2.0)))",
						-1
					),
					ScriptStatement(
						130,
						119,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						131,
						120,
						"console.log(\"Check additional math\")",
						"console.log(\"Check additional math\")",
						-1
					),
					ScriptStatement(
						132,
						121,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						133,
						122,
						"console.log(\"math.PI(): \", math.PI())",
						"console.log(\"math.PI(): \", math.PI())",
						-1
					),
					ScriptStatement(
						134,
						123,
						"console.log(\"math.EPSILON(): \", math.EPSILON())",
						"console.log(\"math.EPSILON(): \", math.EPSILON())",
						-1
					),
					ScriptStatement(
						135,
						124,
						"console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						"console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						-1
					),
					ScriptStatement(
						136,
						125,
						"console.log(\"math.G(): \", math.G())",
						"console.log(\"math.G(): \", math.G())",
						-1
					),
					ScriptStatement(
						137,
						126,
						"console.log(\"math.acos(0.0): \", math.acos(0.0))",
						"console.log(\"math.acos(0.0): \", math.acos(0.0))",
						-1
					),
					ScriptStatement(
						138,
						127,
						"console.log(\"math.asin(1.0): \", math.asin(1.0))",
						"console.log(\"math.asin(1.0): \", math.asin(1.0))",
						-1
					),
					ScriptStatement(
						139,
						128,
						"console.log(\"math.atan(1.0): \", math.atan(1.0))",
						"console.log(\"math.atan(1.0): \", math.atan(1.0))",
						-1
					),
					ScriptStatement(
						140,
						129,
						"console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						"console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						-1
					),
					ScriptStatement(
						141,
						130,
						"console.log(\"math.floor(2.87): \", math.floor(2.87))",
						"console.log(\"math.floor(2.87): \", math.floor(2.87))",
						-1
					),
					ScriptStatement(
						142,
						131,
						"console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						"console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						-1
					),
					ScriptStatement(
						143,
						132,
						"console.log(\"math.round(2.37): \", math.round(2.37))",
						"console.log(\"math.round(2.37): \", math.round(2.37))",
						-1
					),
					ScriptStatement(
						144,
						133,
						"console.log(\"math.round(2.87): \", math.round(2.87))",
						"console.log(\"math.round(2.87): \", math.round(2.87))",
						-1
					),
					ScriptStatement(
						145,
						134,
						"console.log(\"math.cos(0.0): \", math.cos(0.0))",
						"console.log(\"math.cos(0.0): \", math.cos(0.0))",
						-1
					),
					ScriptStatement(
						146,
						135,
						"console.log(\"math.sin(0.0): \", math.sin(0.0))",
						"console.log(\"math.sin(0.0): \", math.sin(0.0))",
						-1
					),
					ScriptStatement(
						147,
						136,
						"console.log(\"math.tan(1.0): \", math.tan(1.0))",
						"console.log(\"math.tan(1.0): \", math.tan(1.0))",
						-1
					),
					ScriptStatement(
						148,
						137,
						"console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						"console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						-1
					),
					ScriptStatement(
						149,
						138,
						"console.log(\"math.random(): \", math.random())",
						"console.log(\"math.random(): \", math.random())",
						-1
					),
					ScriptStatement(
						150,
						139,
						"console.log(\"math.random(): \", math.random())",
						"console.log(\"math.random(): \", math.random())",
						-1
					),
					ScriptStatement(
						151,
						140,
						"console.log(\"math.random(): \", math.random())",
						"console.log(\"math.random(): \", math.random())",
						-1
					),
					ScriptStatement(
						152,
						141,
						"console.log(\"math.exp(1.0): \", math.exp(1.0))",
						"console.log(\"math.exp(1.0): \", math.exp(1.0))",
						-1
					),
					ScriptStatement(
						153,
						142,
						"console.log(\"math.log(2.0): \", math.log(2.0))",
						"console.log(\"math.log(2.0): \", math.log(2.0))",
						-1
					),
					ScriptStatement(
						154,
						143,
						"console.log(\"math.sign(-2): \", math.sign(-2))",
						"console.log(\"math.sign(-2): \", math.sign(-2))",
						-1
					),
					ScriptStatement(
						155,
						144,
						"console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						"console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						-1
					),
					ScriptStatement(
						156,
						145,
						"console.log(\"math.square(3): \", math.square(3))",
						"console.log(\"math.square(3): \", math.square(3))",
						-1
					),
					ScriptStatement(
						157,
						146,
						"console.log(\"math.square(3.0): \", math.square(3.0))",
						"console.log(\"math.square(3.0): \", math.square(3.0))",
						-1
					),
					ScriptStatement(
						158,
						147,
						"console.log(\"math.min(4, 9): \", math.min(4, 9))",
						"console.log(\"math.min(4, 9): \", math.min(4, 9))",
						-1
					),
					ScriptStatement(
						159,
						148,
						"console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						"console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						-1
					),
					ScriptStatement(
						160,
						149,
						"console.log(\"math.max(4, 9): \", math.max(4, 9))",
						"console.log(\"math.max(4, 9): \", math.max(4, 9))",
						-1
					),
					ScriptStatement(
						161,
						150,
						"console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						"console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						-1
					),
					ScriptStatement(
						162,
						151,
						"console.log(\"math.abs(-9): \", math.abs(-9))",
						"console.log(\"math.abs(-9): \", math.abs(-9))",
						-1
					),
					ScriptStatement(
						163,
						152,
						"console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						"console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						-1
					),
					ScriptStatement(
						164,
						153,
						"console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						"console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						-1
					),
					ScriptStatement(
						165,
						154,
						"console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						"console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						-1
					),
					ScriptStatement(
						166,
						155,
						"console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						"console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						-1
					),
					ScriptStatement(
						167,
						156,
						"console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						"console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						-1
					),
					ScriptStatement(
						168,
						157,
						"console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						"console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						-1
					),
					ScriptStatement(
						169,
						158,
						"console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						"console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						-1
					),
					ScriptStatement(
						170,
						159,
						"console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						"console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						-1
					),
					ScriptStatement(
						171,
						160,
						"console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						"console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						-1
					),
					ScriptStatement(
						172,
						161,
						"console.log(\"-----------------------------------\")",
						"console.log(\"-----------------------------------\")",
						-1
					),
					ScriptStatement(
						173,
						162,
						"console.log(\"Check transform\")",
						"console.log(\"Check transform\")",
						-1
					),
					ScriptStatement(
						174,
						163,
						"console.log(\"-----------------------------------\")",
						"console.log(\"-----------------------------------\")",
						-1
					),
					ScriptStatement(
						175,
						164,
						"console.log(\"$transform = transform(vec3(1,2,3), vec3(2, 3, 4)\")",
						"console.log(\"$transform = transform(vec3(1,2,3), vec3(2, 3, 4)\")",
						-1
					),
					ScriptStatement(
						176,
						165,
						"$transform = transform(vec3(1,2,3), vec3(2, 3, 4))",
						"setVariable(\"$transform\", transform(vec3(1,2,3), vec3(2, 3, 4)))",
						-1
					),
					ScriptStatement(
						177,
						166,
						"console.log(\"$transform: \", $transform)",
						"console.log(\"$transform: \", $transform)",
						-1
					),
					ScriptStatement(
						178,
						167,
						"console.log(\"transform.setRotationAngle($transform, 1, 90)\")",
						"console.log(\"transform.setRotationAngle($transform, 1, 90)\")",
						-1
					),
					ScriptStatement(
						179,
						168,
						"transform.setRotationAngle($transform, 1, 90)",
						"transform.setRotationAngle($transform, 1, 90)",
						-1
					),
					ScriptStatement(
						180,
						169,
						"console.log(\"transform.getRotationAngle($transform, 1): \", transform.getRotationAngle($transform, 1))",
						"console.log(\"transform.getRotationAngle($transform, 1): \", transform.getRotationAngle($transform, 1))",
						-1
					),
					ScriptStatement(
						181,
						170,
						"console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						"console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						-1
					),
					ScriptStatement(
						182,
						171,
						"console.log(\"transform.setTranslation($transform, vec3(-1,-2,-3))\")",
						"console.log(\"transform.setTranslation($transform, vec3(-1,-2,-3))\")",
						-1
					),
					ScriptStatement(
						183,
						172,
						"transform.setTranslation($transform, vec3(-1,-2,-3))",
						"transform.setTranslation($transform, vec3(-1,-2,-3))",
						-1
					),
					ScriptStatement(
						184,
						173,
						"console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						"console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						-1
					),
					ScriptStatement(
						185,
						174,
						"console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						"console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						-1
					),
					ScriptStatement(
						186,
						175,
						"console.log(\"transform.setScale($transform, vec3(-2,-3,-4))\")",
						"console.log(\"transform.setScale($transform, vec3(-2,-3,-4))\")",
						-1
					),
					ScriptStatement(
						187,
						176,
						"transform.setScale($transform, vec3(-2,-3,-4))",
						"transform.setScale($transform, vec3(-2,-3,-4))",
						-1
					),
					ScriptStatement(
						188,
						177,
						"console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						"console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						-1
					),
					ScriptStatement(
						189,
						178,
						"console.log(\"transform.getRotationAxis($transform, 0): \", transform.getRotationAxis($transform, 0))",
						"console.log(\"transform.getRotationAxis($transform, 0): \", transform.getRotationAxis($transform, 0))",
						-1
					),
					ScriptStatement(
						190,
						179,
						"console.log(\"$transform * vec3(0,0,0): \", $transform * vec3(0,0,0))",
						"console.log(\"$transform * vec3(0,0,0): \",mul($transform, vec3(0,0,0)))",
						-1
					),
					ScriptStatement(
						191,
						180,
						"console.log(\"transform.rotate($transform, vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						"console.log(\"transform.rotate($transform, vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						-1
					),
					ScriptStatement(
						192,
						181,
						"console.log(\"transform.getTransformMatrix($transform): \", $transform->getTransformMatrix())",
						"console.log(\"transform.getTransformMatrix($transform): \", $transform->getTransformMatrix())",
						-1
					),
					ScriptStatement(
						193,
						182,
						"console.log(\"transform.getRotationsQuaternion($transform): \", $transform->getRotationsQuaternion())",
						"console.log(\"transform.getRotationsQuaternion($transform): \", $transform->getRotationsQuaternion())",
						-1
					),
					ScriptStatement(
						194,
						183,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						195,
						184,
						"console.log(\"Check string methods\")",
						"console.log(\"Check string methods\")",
						-1
					),
					ScriptStatement(
						196,
						185,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						197,
						186,
						"console.log(\"string.isInteger(1234): \" + string.isInteger(1234))",
						"console.log(add(\"string.isInteger(1234): \", string.isInteger(1234)))",
						-1
					),
					ScriptStatement(
						198,
						187,
						"console.log(\"string.isInteger(abcd): \" + string.isInteger(abcd))",
						"console.log(add(\"string.isInteger(abcd): \", string.isInteger(abcd)))",
						-1
					),
					ScriptStatement(
						199,
						188,
						"console.log(\"string.isFloat(1234.1234): \" + string.isFloat(1234.1234))",
						"console.log(add(\"string.isFloat(1234.1234): \", string.isFloat(1234.1234)))",
						-1
					),
					ScriptStatement(
						200,
						189,
						"console.log(\"string.isFloat(abcd.abcd): \" + string.isFloat(abcd.abcd))",
						"console.log(add(\"string.isFloat(abcd.abcd): \", string.isFloat(abcd.abcd)))",
						-1
					),
					ScriptStatement(
						201,
						190,
						"console.log(\"string.space(0): \" + string.space(0), \"1\")",
						"console.log(add(\"string.space(0): \", string.space(0)), \"1\")",
						-1
					),
					ScriptStatement(
						202,
						191,
						"console.log(\"string.space(2): \" + string.space(2), \"1.1\")",
						"console.log(add(\"string.space(2): \", string.space(2)), \"1.1\")",
						-1
					),
					ScriptStatement(
						203,
						192,
						"console.log(\"string.space(2): \" + string.space(2), \"1.2\")",
						"console.log(add(\"string.space(2): \", string.space(2)), \"1.2\")",
						-1
					),
					ScriptStatement(
						204,
						193,
						"console.log(\"string.space(4): \" + string.space(4), \"1.2.1\")",
						"console.log(add(\"string.space(4): \", string.space(4)), \"1.2.1\")",
						-1
					),
					ScriptStatement(
						205,
						194,
						"console.log(\"string.toUpperCase('xxxyyyzzz'): \", string.toUpperCase(\"xxxyyyzzz\"))",
						"console.log(\"string.toUpperCase('xxxyyyzzz'): \", string.toUpperCase(\"xxxyyyzzz\"))",
						-1
					),
					ScriptStatement(
						206,
						195,
						"console.log(\"string.toLowerCase('XXXYYYZZZ'): \", string.toLowerCase(\"XXXYYYZZZ\"))",
						"console.log(\"string.toLowerCase('XXXYYYZZZ'): \", string.toLowerCase(\"XXXYYYZZZ\"))",
						-1
					),
					ScriptStatement(
						207,
						196,
						"console.log(\"string.concatenate('abc', 'def', 'ghi'): \" + string.concatenate(\"abc\", \"def\", \"ghi\"))",
						"console.log(add(\"string.concatenate('abc', 'def', 'ghi'): \", string.concatenate(\"abc\", \"def\", \"ghi\")))",
						-1
					),
					ScriptStatement(
						208,
						197,
						"console.log(\"string.startsWith('abcdef', 'abc'): \" + string.startsWith(\"abcdef\", \"abc\"))",
						"console.log(add(\"string.startsWith('abcdef', 'abc'): \", string.startsWith(\"abcdef\", \"abc\")))",
						-1
					),
					ScriptStatement(
						209,
						198,
						"console.log(\"string.startsWith('abcdef', 'def'): \" + string.startsWith(\"abcdef\", \"def\"))",
						"console.log(add(\"string.startsWith('abcdef', 'def'): \", string.startsWith(\"abcdef\", \"def\")))",
						-1
					),
					ScriptStatement(
						210,
						199,
						"console.log(\"string.endsWith('abcdef', 'abc'): \" + string.endsWith(\"abcdef\", \"abc\"))",
						"console.log(add(\"string.endsWith('abcdef', 'abc'): \", string.endsWith(\"abcdef\", \"abc\")))",
						-1
					),
					ScriptStatement(
						211,
						200,
						"console.log(\"string.endsWith('abcdef', 'def'): \" + string.endsWith(\"abcdef\", \"def\"))",
						"console.log(add(\"string.endsWith('abcdef', 'def'): \", string.endsWith(\"abcdef\", \"def\")))",
						-1
					),
					ScriptStatement(
						212,
						201,
						"console.log(\"string.replace('abcdef', 'def', 'DEF'): \" + string.replace(\"abcdef\", \"def\", \"DEF\"))",
						"console.log(add(\"string.replace('abcdef', 'def', 'DEF'): \", string.replace(\"abcdef\", \"def\", \"DEF\")))",
						-1
					),
					ScriptStatement(
						213,
						202,
						"console.log(\"string.indexOf('abcdef', 'def'): \" + string.indexOf(\"abcdef\", \"def\"))",
						"console.log(add(\"string.indexOf('abcdef', 'def'): \", string.indexOf(\"abcdef\", \"def\")))",
						-1
					),
					ScriptStatement(
						214,
						203,
						"console.log(\"string.firstIndexOf('abcdef', 'def'): \" + string.firstIndexOf(\"abcdef\", \"def\"))",
						"console.log(add(\"string.firstIndexOf('abcdef', 'def'): \", string.firstIndexOf(\"abcdef\", \"def\")))",
						-1
					),
					ScriptStatement(
						215,
						204,
						"console.log(\"string.lastIndexOf('abcdef', 'def'): \" + string.lastIndexOf(\"abcdef\", \"def\"))",
						"console.log(add(\"string.lastIndexOf('abcdef', 'def'): \", string.lastIndexOf(\"abcdef\", \"def\")))",
						-1
					),
					ScriptStatement(
						216,
						205,
						"console.log(\"string.substring('abcdef', 3): \" + string.substring(\"abcdef\", 3))",
						"console.log(add(\"string.substring('abcdef', 3): \", string.substring(\"abcdef\", 3)))",
						-1
					),
					ScriptStatement(
						217,
						206,
						"console.log(\"string.substring('abcdef', 1, 5): \" + string.substring(\"abcdef\", 1, 5))",
						"console.log(add(\"string.substring('abcdef', 1, 5): \", string.substring(\"abcdef\", 1, 5)))",
						-1
					),
					ScriptStatement(
						218,
						207,
						"console.log(\"string.equalsIgnoreCase('abcdef', 'ABCDEF'): \" + string.equalsIgnoreCase('abcdef', 'ABCDEF'))",
						"console.log(add(\"string.equalsIgnoreCase('abcdef', 'ABCDEF'): \", string.equalsIgnoreCase('abcdef', 'ABCDEF')))",
						-1
					),
					ScriptStatement(
						219,
						208,
						"console.log(\"string.trim('   abcdef   '): \" + \"'\" + string.trim(\"   abcdef   \") + \"'\")",
						"console.log(add(\"string.trim('   abcdef   '): \",add(\"'\",add(string.trim(\"   abcdef   \"), \"'\"))))",
						-1
					),
					ScriptStatement(
						220,
						209,
						"console.log(\"string.regexMatch('abcdef', '[a-z]*'): \" + string.regexMatch(\"abcdef\", \"[a-z]*\"))",
						"console.log(add(\"string.regexMatch('abcdef', '[a-z]*'): \", string.regexMatch(\"abcdef\", \"[a-z]*\")))",
						-1
					),
					ScriptStatement(
						221,
						210,
						"console.log(\"string.regexMatch('abcdef', '[0-9]*'): \" + string.regexMatch(\"abcdef\", \"[0-9]*\"))",
						"console.log(add(\"string.regexMatch('abcdef', '[0-9]*'): \", string.regexMatch(\"abcdef\", \"[0-9]*\")))",
						-1
					),
					ScriptStatement(
						222,
						211,
						"console.log(\"string.regexReplace('abcdef', '[bcde]', '-'): \" + string.regexReplace(\"abcdef\", \"[bcde]\", \"-\"))",
						"console.log(add(\"string.regexReplace('abcdef', '[bcde]', '-'): \", string.regexReplace(\"abcdef\", \"[bcde]\", \"-\")))",
						-1
					),
					ScriptStatement(
						223,
						212,
						"console.log(\"string.tokenize('Andreas is a very good boy', ' '): \" + string.tokenize(\"Andreas is a very good boy <3\", \" \"))",
						"console.log(add(\"string.tokenize('Andreas is a very good boy', ' '): \", string.tokenize(\"Andreas is a very good boy <3\", \" \")))",
						-1
					),
					ScriptStatement(
						224,
						213,
						"console.log(\"string.length('abcdef'): \" + string.length(\"abcdef\"))",
						"console.log(add(\"string.length('abcdef'): \", string.length(\"abcdef\")))",
						-1
					),
					ScriptStatement(
						225,
						214,
						"console.log(\"string.charAt('abcdef', 0): \" + string.charAt(\"abcdef\", 0))",
						"console.log(add(\"string.charAt('abcdef', 0): \", string.charAt(\"abcdef\", 0)))",
						-1
					),
					ScriptStatement(
						226,
						215,
						"console.log(\"string.charAt('abcdef', 1): \" + string.charAt(\"abcdef\", 1))",
						"console.log(add(\"string.charAt('abcdef', 1): \", string.charAt(\"abcdef\", 1)))",
						-1
					),
					ScriptStatement(
						227,
						216,
						"console.log(\"string.charAt('abcdef', 2): \" + string.charAt(\"abcdef\", 2))",
						"console.log(add(\"string.charAt('abcdef', 2): \", string.charAt(\"abcdef\", 2)))",
						-1
					),
					ScriptStatement(
						228,
						217,
						"console.log(\"string.charAt('abcdef', 3): \" + string.charAt(\"abcdef\", 3))",
						"console.log(add(\"string.charAt('abcdef', 3): \", string.charAt(\"abcdef\", 3)))",
						-1
					),
					ScriptStatement(
						229,
						218,
						"console.log(\"string.charAt('abcdef', 4): \" + string.charAt(\"abcdef\", 4))",
						"console.log(add(\"string.charAt('abcdef', 4): \", string.charAt(\"abcdef\", 4)))",
						-1
					),
					ScriptStatement(
						230,
						219,
						"console.log(\"string.charAt('abcdef', 5): \" + string.charAt(\"abcdef\", 5))",
						"console.log(add(\"string.charAt('abcdef', 5): \", string.charAt(\"abcdef\", 5)))",
						-1
					),
					ScriptStatement(
						231,
						220,
						"console.log(\"string.charAt('abcdef', 6): \" + string.charAt(\"abcdef\", 6))",
						"console.log(add(\"string.charAt('abcdef', 6): \", string.charAt(\"abcdef\", 6)))",
						-1
					),
					ScriptStatement(
						232,
						221,
						"console.log(\"string.padLeft('1011', '0', 8): \" + string.padLeft(\"1011\", \"0\", 8))",
						"console.log(add(\"string.padLeft('1011', '0', 8): \", string.padLeft(\"1011\", \"0\", 8)))",
						-1
					),
					ScriptStatement(
						233,
						222,
						"console.log(\"string.padRight('1011', '0', 8): \" + string.padRight(\"1011\", \"0\", 8))",
						"console.log(add(\"string.padRight('1011', '0', 8): \", string.padRight(\"1011\", \"0\", 8)))",
						-1
					),
					ScriptStatement(
						234,
						223,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						235,
						224,
						"console.log(\"Check string operator (Operators)\")",
						"console.log(\"Check string operator (Operators)\")",
						-1
					),
					ScriptStatement(
						236,
						225,
						"console.log(\"'abc' + 'def' + 'ghi': \", \"abc\" + \"def\" + \"ghi\")",
						"console.log(\"'abc' + 'def' + 'ghi': \",add(\"abc\",add(\"def\", \"ghi\")))",
						-1
					),
					ScriptStatement(
						237,
						226,
						"console.log(\"abc == abc: \", \"abc\" == \"abc\")",
						"console.log(\"abc == abc: \",equals(\"abc\", \"abc\"))",
						-1
					),
					ScriptStatement(
						238,
						227,
						"console.log(\"abc == def: \", \"abc\" == \"def\")",
						"console.log(\"abc == def: \",equals(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						239,
						228,
						"console.log(\"abc != abc: \", \"abc\" != \"abc\")",
						"console.log(\"abc != abc: \",notEqual(\"abc\", \"abc\"))",
						-1
					),
					ScriptStatement(
						240,
						229,
						"console.log(\"abc != def: \", \"abc\" != \"def\")",
						"console.log(\"abc != def: \",notEqual(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						241,
						230,
						"console.log(\"abc < def: \", \"abc\" < \"def\")",
						"console.log(\"abc < def: \",lesser(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						242,
						231,
						"console.log(\"def < abc: \", \"def\" < \"abc\")",
						"console.log(\"def < abc: \",lesser(\"def\", \"abc\"))",
						-1
					),
					ScriptStatement(
						243,
						232,
						"console.log(\"abc <= abc: \", \"abc\" <= \"abc\")",
						"console.log(\"abc <= abc: \",lesserEquals(\"abc\", \"abc\"))",
						-1
					),
					ScriptStatement(
						244,
						233,
						"console.log(\"abc <= def: \", \"abc\" <= \"def\")",
						"console.log(\"abc <= def: \",lesserEquals(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						245,
						234,
						"console.log(\"def <= abc: \", \"def\" <= \"abc\")",
						"console.log(\"def <= abc: \",lesserEquals(\"def\", \"abc\"))",
						-1
					),
					ScriptStatement(
						246,
						235,
						"console.log(\"abc > def: \", \"abc\" > \"def\")",
						"console.log(\"abc > def: \",greater(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						247,
						236,
						"console.log(\"def > abc: \", \"def\" > \"abc\")",
						"console.log(\"def > abc: \",greater(\"def\", \"abc\"))",
						-1
					),
					ScriptStatement(
						248,
						237,
						"console.log(\"abc >= abc: \", \"abc\" >= \"abc\")",
						"console.log(\"abc >= abc: \",greaterEquals(\"abc\", \"abc\"))",
						-1
					),
					ScriptStatement(
						249,
						238,
						"console.log(\"abc >= def: \", \"abc\" >= \"def\")",
						"console.log(\"abc >= def: \",greaterEquals(\"abc\", \"def\"))",
						-1
					),
					ScriptStatement(
						250,
						239,
						"console.log(\"def >= abc: \", \"def\" >= \"abc\")",
						"console.log(\"def >= abc: \",greaterEquals(\"def\", \"abc\"))",
						-1
					),
					ScriptStatement(
						251,
						240,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						252,
						241,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						253,
						242,
						"console.log(\"Variable\")",
						"console.log(\"Variable\")",
						-1
					),
					ScriptStatement(
						254,
						243,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						255,
						244,
						"$variable = string(\"1234\")",
						"setVariable(\"$variable\", string(\"1234\"))",
						-1
					),
					ScriptStatement(
						256,
						245,
						"console.log(getVariable(\"$variable\"))",
						"console.log(getVariable(\"$variable\"))",
						-1
					),
					ScriptStatement(
						257,
						246,
						"console.log(\"--------------------\")",
						"console.log(\"--------------------\")",
						-1
					),
					ScriptStatement(
						258,
						247,
						"console.log(\"Lets check forTime\")",
						"console.log(\"Lets check forTime\")",
						-1
					),
					ScriptStatement(
						259,
						248,
						"console.log(\"--------------------\")",
						"console.log(\"--------------------\")",
						-1
					),
					ScriptStatement(
						260,
						249,
						"$i = 1",
						"setVariable(\"$i\", 1)",
						-1
					),
					ScriptStatement(
						261,
						250,
						"forTime(2000)",
						"forTime(2000)",
						255
					),
					ScriptStatement(
						262,
						251,
						"console.log($i, \": Hello World\")",
						"console.log($i, \": Hello World\")",
						-1
					),
					ScriptStatement(
						263,
						252,
						"script.wait(500)",
						"script.wait(500)",
						-1
					),
					ScriptStatement(
						264,
						253,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						265,
						254,
						"end",
						"end",
						250
					),
					ScriptStatement(
						266,
						255,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						267,
						256,
						"console.log(\"Lets check forCondition\")",
						"console.log(\"Lets check forCondition\")",
						-1
					),
					ScriptStatement(
						268,
						257,
						"console.log(\"-------------------------\")",
						"console.log(\"-------------------------\")",
						-1
					),
					ScriptStatement(
						269,
						258,
						"$i = 1",
						"setVariable(\"$i\", 1)",
						-1
					),
					ScriptStatement(
						270,
						259,
						"forCondition($i != 6)",
						"forCondition(notEqual($i, 6))",
						264
					),
					ScriptStatement(
						271,
						260,
						"console.log($i, \": Hello World\")",
						"console.log($i, \": Hello World\")",
						-1
					),
					ScriptStatement(
						272,
						261,
						"script.wait(500)",
						"script.wait(500)",
						-1
					),
					ScriptStatement(
						273,
						262,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						274,
						263,
						"end",
						"end",
						259
					),
					ScriptStatement(
						275,
						264,
						"console.log(\"i -> \", $i)",
						"console.log(\"i -> \", $i)",
						-1
					),
					ScriptStatement(
						276,
						265,
						"console.log(\"---------------------------------------------\")",
						"console.log(\"---------------------------------------------\")",
						-1
					),
					ScriptStatement(
						277,
						266,
						"console.log(\"Lets check forCondition with if/elseif/else\")",
						"console.log(\"Lets check forCondition with if/elseif/else\")",
						-1
					),
					ScriptStatement(
						278,
						267,
						"console.log(\"---------------------------------------------\")",
						"console.log(\"---------------------------------------------\")",
						-1
					),
					ScriptStatement(
						279,
						268,
						"$i = 1",
						"setVariable(\"$i\", 1)",
						-1
					),
					ScriptStatement(
						280,
						269,
						"forCondition($i < 5)",
						"forCondition(lesser($i, 5))",
						284
					),
					ScriptStatement(
						281,
						270,
						"console.log($i, \":\")",
						"console.log($i, \":\")",
						-1
					),
					ScriptStatement(
						282,
						271,
						"if ($i == 0)",
						"if (equals($i, 0))",
						273
					),
					ScriptStatement(
						283,
						272,
						"console.log(\"i -> 0\")",
						"console.log(\"i -> 0\")",
						-1
					),
					ScriptStatement(
						284,
						273,
						"elseif ($i == 1)",
						"elseif (equals($i, 1))",
						275
					),
					ScriptStatement(
						285,
						274,
						"console.log(\"i -> 1\")",
						"console.log(\"i -> 1\")",
						-1
					),
					ScriptStatement(
						286,
						275,
						"elseif ($i == 2)",
						"elseif (equals($i, 2))",
						277
					),
					ScriptStatement(
						287,
						276,
						"console.log(\"i -> 2\")",
						"console.log(\"i -> 2\")",
						-1
					),
					ScriptStatement(
						288,
						277,
						"elseif ($i == 3)",
						"elseif (equals($i, 3))",
						279
					),
					ScriptStatement(
						289,
						278,
						"console.log(\"i -> 3\")",
						"console.log(\"i -> 3\")",
						-1
					),
					ScriptStatement(
						290,
						279,
						"else",
						"else",
						281
					),
					ScriptStatement(
						291,
						280,
						"console.log(\"else: \", $i)",
						"console.log(\"else: \", $i)",
						-1
					),
					ScriptStatement(
						292,
						281,
						"end",
						"end",
						-1
					),
					ScriptStatement(
						293,
						282,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						294,
						283,
						"end",
						"end",
						269
					),
					ScriptStatement(
						295,
						284,
						"$i = 1",
						"setVariable(\"$i\", 1)",
						-1
					),
					ScriptStatement(
						296,
						285,
						"$j = 2",
						"setVariable(\"$j\", 2)",
						-1
					),
					ScriptStatement(
						297,
						286,
						"$k = 3",
						"setVariable(\"$k\", 3)",
						-1
					),
					ScriptStatement(
						298,
						287,
						"if (getVariable(\"$i\") == $j || getVariable(\"$i\") == $k)",
						"if (or(equals(getVariable(\"$i\"), $j),equals(getVariable(\"$i\"), $k)))",
						289
					),
					ScriptStatement(
						299,
						288,
						"console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						"console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						-1
					),
					ScriptStatement(
						300,
						289,
						"end",
						"end",
						-1
					),
					ScriptStatement(
						301,
						290,
						"console.log(\"-------------------------------------------------------------------------------------\")",
						"console.log(\"-------------------------------------------------------------------------------------\")",
						-1
					),
					ScriptStatement(
						302,
						291,
						"console.log(\"Test: string concatenation with brackets in string literals: \" + $i + \"(\" + $j + \")\")",
						"console.log(add(\"Test: string concatenation with brackets in string literals: \",add($i,add(\"(\",add($j, \")\")))))",
						-1
					),
					ScriptStatement(
						303,
						292,
						"console.log(\"-------------------------------------------------------------------------------------\")",
						"console.log(\"-------------------------------------------------------------------------------------\")",
						-1
					),
					ScriptStatement(
						304,
						293,
						"console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \", (4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)), \" = 17\")",
						"console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \",add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), \" = 17\")",
						-1
					),
					ScriptStatement(
						305,
						294,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						306,
						295,
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
				309,
				"error",
				"error",
				ScriptStatement(
					309,
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
						310,
						0,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						311,
						1,
						"console.log(\"base-test: Error\")",
						"console.log(\"base-test: Error\")",
						-1
					),
					ScriptStatement(
						312,
						2,
						"console.log(\"------------------\")",
						"console.log(\"------------------\")",
						-1
					),
					ScriptStatement(
						313,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						314,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						315,
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
void MiniScriptBaseTest::registerMethods() {
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

int MiniScriptBaseTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptBaseTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (const auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return SCRIPTIDX_NONE;
}

void MiniScriptBaseTest::emit(const string& condition) {
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
		Console::println("MiniScriptBaseTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptBaseTest::on_initialize(int miniScriptGotoStatementIdx) {
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
	// console.log("base-test: Initialize")
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("base-test: Initialize"))
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

void MiniScriptBaseTest::on_nothing(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 251) goto miniscript_statement_251; else
	if (miniScriptGotoStatementIdx == 253) goto miniscript_statement_253; else
	if (miniScriptGotoStatementIdx == 255) goto miniscript_statement_255; else
	if (miniScriptGotoStatementIdx == 260) goto miniscript_statement_260; else
	if (miniScriptGotoStatementIdx == 262) goto miniscript_statement_262; else
	if (miniScriptGotoStatementIdx == 264) goto miniscript_statement_264; else
	if (miniScriptGotoStatementIdx == 270) goto miniscript_statement_270; else
	if (miniScriptGotoStatementIdx == 272) goto miniscript_statement_272; else
	if (miniScriptGotoStatementIdx == 274) goto miniscript_statement_274; else
	if (miniScriptGotoStatementIdx == 276) goto miniscript_statement_276; else
	if (miniScriptGotoStatementIdx == 278) goto miniscript_statement_278; else
	if (miniScriptGotoStatementIdx == 280) goto miniscript_statement_280; else
	if (miniScriptGotoStatementIdx == 282) goto miniscript_statement_282; else
	if (miniScriptGotoStatementIdx == 284) goto miniscript_statement_284; else
	if (miniScriptGotoStatementIdx == 288) goto miniscript_statement_288; else
	if (miniScriptGotoStatementIdx == 290) goto miniscript_statement_290; else
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
	// console.log("base-test: Nothing")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("base-test: Nothing"))
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
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[4];
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
	// statement: 5
	// console.log("Check bool operations")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check bool operations"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 6
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[6];
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
	// statement: 7
	// console.log("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ", and(or(equals("MiniScript will do the job", "MiniScript will not do the job"), equals("it will", "it will")), 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of and(or(equals("MiniScript will do the job", "MiniScript will not do the job"), equals("it will", "it will")), 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: and(or(equals("MiniScript will do the job", "MiniScript will not do the job"), equals("it will", "it will")), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of or(equals("MiniScript will do the job", "MiniScript will not do the job"), equals("it will", "it will"))
				ScriptVariable(true)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: or(equals("MiniScript will do the job", "MiniScript will not do the job"), equals("it will", "it will"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of equals("MiniScript will do the job", "MiniScript will not do the job")
					ScriptVariable() // argumentValues[1] --> returnValue of equals("it will", "it will")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: equals("MiniScript will do the job", "MiniScript will not do the job")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string("MiniScript will do the job")),
						ScriptVariable(string("MiniScript will not do the job"))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
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
				// depth = 3 / argument index = 1: equals("it will", "it will")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string("it will")),
						ScriptVariable(string("it will"))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
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
				// method code: or
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println(string("or") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("or")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(false);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println(string("or") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("or")));
							miniScript->startErrorScript(); return;
						} else
						if (booleanValue == true) {
							returnValue.setValue(true);
							break;
						}
					}
				}
			}
			// method code: and
			if (argumentValues.size() != 2) {
				returnValue.setValue(false);
				Console::println(string("and") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("and")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println(string("and") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("and")));
						miniScript->startErrorScript(); return;
					} else
					if (booleanValue == false) {
						returnValue.setValue(false);
						break;
					}
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 8
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[8];
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
	// statement: 9
	// console.log("Check int computation")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check int computation"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 10
	// console.log("-----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[10];
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
	// statement: 11
	// console.log("1 + 2 + 3 - 1: ", sub(add(1, add(2, 3)), 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("1 + 2 + 3 - 1: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(add(1, add(2, 3)), 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(add(1, add(2, 3)), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of add(1, add(2, 3))
				ScriptVariable(static_cast<int64_t>(1ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: add(1, add(2, 3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable() // argumentValues[1] --> returnValue of add(2, 3)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 1: add(2, 3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(static_cast<int64_t>(2ll)),
						ScriptVariable(static_cast<int64_t>(3ll))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 12
	// console.log("20 / 2: ", div(20, 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("20 / 2: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(20, 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(20, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(20ll)),
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 13
	// console.log("11 * 10: ", mul(11, 10))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("11 * 10: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(11, 10)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(11, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(11ll)),
				ScriptVariable(static_cast<int64_t>(10ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 14
	// console.log("2 > 1: ", greater(2, 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("2 > 1: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greater(2, 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greater(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(1ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greater
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA > stringValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA > floatValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 15
	// console.log("2 < 1: ", lesser(2, 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("2 < 1: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesser(2, 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesser(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(1ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 16
	// console.log("7 % 4: ", mod(7, 4))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[16];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("7 % 4: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mod(7, 4)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mod(7, 4)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(7ll)),
				ScriptVariable(static_cast<int64_t>(4ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 17
	// setVariable("$i", 2)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(2ll))
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
	// statement: 18
	// console.log("$i = 2 && ++$i: ", prefixIncrement(getVariable("$i")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[18];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i = 2 && ++$i: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of prefixIncrement(getVariable("$i"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: prefixIncrement(getVariable("$i"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$i")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 19
	// setVariable("$i", 2)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(2ll))
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
	// console.log("$i = 2 && --$i: ", prefixDecrement(getVariable("$i")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[20];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i = 2 && --$i: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of prefixDecrement(getVariable("$i"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: prefixDecrement(getVariable("$i"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$i")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
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
			// method code: prefixDecrement
			int64_t value;
			if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
				Console::println(string("prefixDecrement") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("prefixDecrement")));
				// assign back
				setVariable("$i", argumentValues[0], &statement);
				//
				miniScript->startErrorScript(); return;
			} else {
				--value;
				argumentValues[0] = value;
				returnValue.setValue(value);
			}
			// assign back
			setVariable("$i", argumentValues[0], &statement);
			//
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 21
	// console.log("--------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[21];
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
	// statement: 22
	// console.log("Check int bit operations")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[22];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check int bit operations"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 23
	// console.log("--------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[23];
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
	// statement: 24
	// console.log("~1 & 255: ", bitwiseAnd(bitwiseNot(1), 255))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[24];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("~1 & 255: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of bitwiseAnd(bitwiseNot(1), 255)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: bitwiseAnd(bitwiseNot(1), 255)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of bitwiseNot(1)
				ScriptVariable(static_cast<int64_t>(255ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: bitwiseNot(1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: bitwiseNot
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(string("bitwiseNot") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseNot")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(~value);
				}
			}
			// method code: bitwiseAnd
			int64_t valueA;
			int64_t valueB;
			if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
				Console::println(string("bitwiseAnd") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseAnd")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(valueA & valueB);
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 25
	// console.log("~0 & 255: ", bitwiseAnd(bitwiseNot(0), 255))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[25];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("~0 & 255: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of bitwiseAnd(bitwiseNot(0), 255)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: bitwiseAnd(bitwiseNot(0), 255)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of bitwiseNot(0)
				ScriptVariable(static_cast<int64_t>(255ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: bitwiseNot(0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: bitwiseNot
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(string("bitwiseNot") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseNot")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(~value);
				}
			}
			// method code: bitwiseAnd
			int64_t valueA;
			int64_t valueB;
			if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
				Console::println(string("bitwiseAnd") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseAnd")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(valueA & valueB);
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 26
	// console.log("128 | 64: ", bitwiseOr(128, 64))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[26];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("128 | 64: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of bitwiseOr(128, 64)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: bitwiseOr(128, 64)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(128ll)),
				ScriptVariable(static_cast<int64_t>(64ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: bitwiseOr
			int64_t valueA;
			int64_t valueB;
			if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
				Console::println(string("bitwiseOr") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseOr")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(valueA | valueB);
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 27
	// console.log("128 ^ 64: ", bitwiseXor(128, 64))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[27];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("128 ^ 64: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of bitwiseXor(128, 64)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: bitwiseXor(128, 64)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(128ll)),
				ScriptVariable(static_cast<int64_t>(64ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: bitwiseXor
			int64_t valueA;
			int64_t valueB;
			if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
				Console::println(string("bitwiseXor") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseXor")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(valueA ^ valueB);
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 28
	// console.log("64 ^ 64: ", bitwiseXor(64, 64))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[28];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("64 ^ 64: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of bitwiseXor(64, 64)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: bitwiseXor(64, 64)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(64ll)),
				ScriptVariable(static_cast<int64_t>(64ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: bitwiseXor
			int64_t valueA;
			int64_t valueB;
			if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
				Console::println(string("bitwiseXor") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("bitwiseXor")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(valueA ^ valueB);
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 29
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[29];
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
	// statement: 30
	// console.log("Check float computation")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[30];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check float computation"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 31
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[31];
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
	// statement: 32
	// console.log("(1.1 + 2.2 + 3.3) - 1.2: ", sub(add(1.100000, add(2.200000, 3.300000)), 1.200000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[32];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("(1.1 + 2.2 + 3.3) - 1.2: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(add(1.100000, add(2.200000, 3.300000)), 1.200000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(add(1.100000, add(2.200000, 3.300000)), 1.200000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of add(1.100000, add(2.200000, 3.300000))
				ScriptVariable(1.200000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: add(1.100000, add(2.200000, 3.300000))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.100000f),
					ScriptVariable() // argumentValues[1] --> returnValue of add(2.200000, 3.300000)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 1: add(2.200000, 3.300000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(2.200000f),
						ScriptVariable(3.300000f)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: add
				MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 33
	// console.log("20 / 1.5: ", div(20, 1.500000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[33];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("20 / 1.5: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(20, 1.500000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(20, 1.500000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(20ll)),
				ScriptVariable(1.500000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 34
	// console.log("11.5 * 10.5: ", mul(11.500000, 10.500000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[34];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("11.5 * 10.5: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(11.500000, 10.500000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(11.500000, 10.500000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(11.500000f),
				ScriptVariable(10.500000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 35
	// console.log("2.2 > 1.3: ", greater(2.200000, 1.300000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[35];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("2.2 > 1.3: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greater(2.200000, 1.300000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greater(2.200000, 1.300000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(2.200000f),
				ScriptVariable(1.300000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greater
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA > stringValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA > floatValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 36
	// console.log("2.5 < 1.2: ", lesser(2.500000, 1.200000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[36];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("2.5 < 1.2: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesser(2.500000, 1.200000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesser(2.500000, 1.200000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(2.500000f),
				ScriptVariable(1.200000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 37
	// console.log("7.1 % 4.0: ", mod(7.100000, 4.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[37];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("7.1 % 4.0: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mod(7.100000, 4.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mod(7.100000, 4.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(7.100000f),
				ScriptVariable(4.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 38
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[38];
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
	// statement: 39
	// console.log("Check vector2 math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[39];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check vector2 math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 40
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[40];
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
	// statement: 41
	// console.log("vec2.computeLength(vec2(20, 10)): ", vec2.computeLength(vec2(20, 10)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[41];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.computeLength(vec2(20, 10)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.computeLength(vec2(20, 10))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.computeLength(vec2(20, 10))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(20, 10)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLength
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				auto length = vec2.computeLength();
				returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
			} else {
				Console::println(string("vec2.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.computeLength")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 42
	// console.log("vec2.computeLengthSquared(vec2(20, 10)): ", vec2.computeLengthSquared(vec2(20, 10)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[42];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.computeLengthSquared(vec2(20, 10)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.computeLengthSquared(vec2(20, 10))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.computeLengthSquared(vec2(20, 10))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(20, 10)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLengthSquared
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.computeLengthSquared());
			} else {
				Console::println(string("vec2.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.computeLengthSquared")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 43
	// console.log("vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): ", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[43];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.computeDotProduct(vec2(0, 1), vec2(0, -1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.computeDotProduct(vec2(0, 1), vec2(0, -1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(0, 1)
				ScriptVariable() // argumentValues[1] --> returnValue of vec2(0, -1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(0, -1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(-1ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeDotProduct
			Vector2 a;
			Vector2 b;
			if (MiniScript::getVector2Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector2Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector2::computeDotProduct(a, b));
			} else {
				Console::println(string("vec2.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.computeDotProduct")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 44
	// console.log("vec2.normalize(vec2(1, 2)): ", vec2.normalize(vec2(1, 2)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[44];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.normalize(vec2(1, 2)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.normalize(vec2(1, 2))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.normalize(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(1, 2)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.normalize
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				auto length = vec2.computeLength();
				returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector2(0.0f, 0.0f):vec2.normalize());
			} else {
				Console::println(string("vec2.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.normalize")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 45
	// console.log("vec2.getX(vec2(1, 2)): ", vec2.getX(vec2(1, 2)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[45];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.getX(vec2(1, 2)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.getX(vec2(1, 2))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.getX(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(1, 2)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getX
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getX());
			} else {
				Console::println(string("vec2.getX") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.getX")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 46
	// console.log("vec2.getY(vec2(1, 2)): ", vec2.getY(vec2(1, 2)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[46];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2.getY(vec2(1, 2)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec2.getY(vec2(1, 2))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec2.getY(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(1, 2)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getY
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getY());
			} else {
				Console::println(string("vec2.getY") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2.getY")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 47
	// console.log("vec2(1.1, 2.2) - vec2(1.2, 1.0): ", sub(vec2(1.100000, 2.200000), vec2(1.200000, 1.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[47];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2(1.1, 2.2) - vec2(1.2, 1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(vec2(1.100000, 2.200000), vec2(1.200000, 1.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(vec2(1.100000, 2.200000), vec2(1.200000, 1.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(1.100000, 2.200000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec2(1.200000, 1.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1.100000, 2.200000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.100000f),
					ScriptVariable(2.200000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.200000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.200000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 48
	// console.log("vec2(20, 10) / vec2(1.5, 2.5): ", div(vec2(20, 10), vec2(1.500000, 2.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[48];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2(20, 10) / vec2(1.5, 2.5): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec2(20, 10), vec2(1.500000, 2.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec2(20, 10), vec2(1.500000, 2.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(20, 10)
				ScriptVariable() // argumentValues[1] --> returnValue of vec2(1.500000, 2.500000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.500000, 2.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 49
	// console.log("vec2(20, 10) * vec2(1.5, 2.5)): ", mul(vec2(20, 10), vec2(1.500000, 2.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[49];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2(20, 10) * vec2(1.5, 2.5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec2(20, 10), vec2(1.500000, 2.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec2(20, 10), vec2(1.500000, 2.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(20, 10)
				ScriptVariable() // argumentValues[1] --> returnValue of vec2(1.500000, 2.500000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.500000, 2.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 50
	// console.log("vec2(20, 10) / 2): ", div(vec2(20, 10), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[50];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2(20, 10) / 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec2(20, 10), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec2(20, 10), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(20, 10)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 51
	// console.log("vec2(20, 10) * 2): ", mul(vec2(20, 10), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[51];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec2(20, 10) * 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec2(20, 10), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec2(20, 10), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(20, 10)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 52
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[52];
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
	// statement: 53
	// console.log("Check vector3 math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[53];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check vector3 math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 54
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[54];
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
	// statement: 55
	// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[55];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.computeLength(vec3(20, 10, 5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.computeLength(vec3(20, 10, 5))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.computeLength(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(20, 10, 5)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLength
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				auto length = vec3.computeLength();
				returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
			} else {
				Console::println(string("vec3.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.computeLength")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 56
	// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[56];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.computeLengthSquared(vec3(20, 10, 5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.computeLengthSquared(vec3(20, 10, 5))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.computeLengthSquared(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(20, 10, 5)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLengthSquared
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLengthSquared());
			} else {
				Console::println(string("vec3.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.computeLengthSquared")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 57
	// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[57];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0, 0, 1)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0, 0, -1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, -1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(-1ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeDotProduct
			Vector3 a;
			Vector3 b;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector3::computeDotProduct(a, b));
			} else {
				Console::println(string("vec3.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.computeDotProduct")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 58
	// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[58];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(1, 0, 0)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0, 1, 0)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeCrossProduct
			Vector3 a;
			Vector3 b;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector3::computeCrossProduct(a, b));
			} else {
				Console::println(string("vec3.computeCrossProduct") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.computeCrossProduct")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 59
	// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[59];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.normalize(vec3(1, 2, 3)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.normalize(vec3(1, 2, 3))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.normalize(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1, 2, 3)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.normalize
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				auto length = vec3.computeLength();
				returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector3(0.0f, 0.0f, 0.0f):vec3.normalize());
			} else {
				Console::println(string("vec3.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.normalize")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 60
	// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[60];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0, 0, 1)
				ScriptVariable(), // argumentValues[1] --> returnValue of vec3(1, 0, 0)
				ScriptVariable() // argumentValues[2] --> returnValue of vec3(0, 1, 0)
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 2: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX2 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeAngle
			Vector3 a;
			Vector3 b;
			Vector3 n;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true &&
				MiniScript::getVector3Value(argumentValues, 2, n, false) == true) {
				returnValue.setValue(Vector3::computeAngle(a, b, n));
			} else {
				Console::println(string("vec3.computeAngle") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.computeAngle")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 61
	// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[61];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.getX(vec3(1, 2, 3)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.getX(vec3(1, 2, 3))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.getX(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1, 2, 3)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getX
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getX());
			} else {
				Console::println(string("vec3.getX") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.getX")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 62
	// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[62];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.getY(vec3(1, 2, 3)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.getY(vec3(1, 2, 3))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.getY(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1, 2, 3)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getY
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getY());
			} else {
				Console::println(string("vec3.getY") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.getY")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 63
	// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[63];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3.getZ(vec3(1, 2, 3)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec3.getZ(vec3(1, 2, 3))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec3.getZ(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1, 2, 3)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getZ
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getZ());
			} else {
				Console::println(string("vec3.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3.getZ")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 64
	// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.100000, 2.200000, 3.300000), vec3(1.200000, 1.000000, 1.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[64];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(vec3(1.100000, 2.200000, 3.300000), vec3(1.200000, 1.000000, 1.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(vec3(1.100000, 2.200000, 3.300000), vec3(1.200000, 1.000000, 1.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(1.100000, 2.200000, 3.300000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(1.200000, 1.000000, 1.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1.100000, 2.200000, 3.300000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.100000f),
					ScriptVariable(2.200000f),
					ScriptVariable(3.300000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.200000, 1.000000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.200000f),
					ScriptVariable(1.000000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 65
	// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[65];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(20, 10, 5)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(1.500000, 2.500000, 3.500000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.500000, 2.500000, 3.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f),
					ScriptVariable(3.500000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 66
	// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[66];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.500000, 2.500000, 3.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(20, 10, 5)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(1.500000, 2.500000, 3.500000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.500000, 2.500000, 3.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f),
					ScriptVariable(3.500000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 67
	// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[67];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3(20, 10, 5) / 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec3(20, 10, 5), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(20, 10, 5)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 68
	// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[68];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec3(20, 10, 5) * 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(20, 10, 5)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 69
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[69];
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
	// statement: 70
	// console.log("Check vector4 math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[70];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check vector4 math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 71
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[71];
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
	// statement: 72
	// console.log("vec4.computeLength(vec4(20, 10, 5, 2.5)): ", vec4.computeLength(vec4(20, 10, 5, 2.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[72];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.computeLength(vec4(20, 10, 5, 2.5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.computeLength(vec4(20, 10, 5, 2.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.computeLength(vec4(20, 10, 5, 2.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(20, 10, 5, 2.500000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 2.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(2.500000f)
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLength
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				auto length = vec4.computeLength();
				returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
			} else {
				Console::println(string("vec4.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.computeLength")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 73
	// console.log("vec4.computeLengthSquared(vec3(20, 10, 5)): ", vec4.computeLengthSquared(vec4(20, 10, 5, 2.500000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[73];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.computeLengthSquared(vec3(20, 10, 5)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.computeLengthSquared(vec4(20, 10, 5, 2.500000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.computeLengthSquared(vec4(20, 10, 5, 2.500000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(20, 10, 5, 2.500000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 2.500000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(2.500000f)
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLengthSquared
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.computeLengthSquared());
			} else {
				Console::println(string("vec4.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.computeLengthSquared")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 74
	// console.log("vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): ", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[74];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(0, 0, 1, 1)
				ScriptVariable() // argumentValues[1] --> returnValue of vec4(0, 0, -1, 1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(0, 0, 1, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(0, 0, -1, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(-1ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeDotProduct
			Vector4 a;
			Vector4 b;
			if (MiniScript::getVector4Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector4Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector4::computeDotProduct(a, b));
			} else {
				Console::println(string("vec4.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.computeDotProduct")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 75
	// console.log("vec4.normalize(vec4(1, 2, 3, 4)): ", vec4.normalize(vec4(1, 2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[75];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.normalize(vec4(1, 2, 3, 4)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.normalize(vec4(1, 2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.normalize(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.normalize
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				auto length = vec4.computeLength();
				returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector4(0.0f, 0.0f, 0.0f, 0.0f):vec4.normalize());
			} else {
				Console::println(string("vec4.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.normalize")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 76
	// console.log("vec4.getX(vec4(1, 2, 3, 4)): ", vec4.getX(vec4(1, 2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[76];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.getX(vec4(1, 2, 3, 4)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.getX(vec4(1, 2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.getX(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getX
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getX());
			} else {
				Console::println(string("vec4.getX") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.getX")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 77
	// console.log("vec4.getY(vec4(1, 2, 3, 4)): ", vec4.getY(vec4(1, 2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[77];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.getY(vec4(1, 2, 3, 4)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.getY(vec4(1, 2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.getY(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getY
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getY());
			} else {
				Console::println(string("vec4.getY") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.getY")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 78
	// console.log("vec4.getZ(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[78];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.getZ(vec4(1, 2, 3, 4)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.getZ(vec4(1, 2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.getZ(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println(string("vec4.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.getZ")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 79
	// console.log("vec4.getW(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[79];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4.getW(vec4(1, 2, 3, 4)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of vec4.getZ(vec4(1, 2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: vec4.getZ(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println(string("vec4.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4.getZ")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 80
	// console.log("vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): ", sub(vec4(1.100000, 2.200000, 3.300000, 1.000000), vec4(1.200000, 1.000000, 1.000000, 1.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[80];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of sub(vec4(1.100000, 2.200000, 3.300000, 1.000000), vec4(1.200000, 1.000000, 1.000000, 1.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: sub(vec4(1.100000, 2.200000, 3.300000, 1.000000), vec4(1.200000, 1.000000, 1.000000, 1.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(1.100000, 2.200000, 3.300000, 1.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec4(1.200000, 1.000000, 1.000000, 1.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(1.100000, 2.200000, 3.300000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(1.100000f),
					ScriptVariable(2.200000f),
					ScriptVariable(3.300000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.200000, 1.000000, 1.000000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(1.200000f),
					ScriptVariable(1.000000f),
					ScriptVariable(1.000000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 81
	// console.log("vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): ", div(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[81];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
				ScriptVariable() // argumentValues[1] --> returnValue of vec4(1.500000, 2.500000, 3.500000, 1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.500000, 2.500000, 3.500000, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f),
					ScriptVariable(3.500000f),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 82
	// console.log("vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): ", mul(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[82];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec4(20, 10, 5, 1), vec4(1.500000, 2.500000, 3.500000, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
				ScriptVariable() // argumentValues[1] --> returnValue of vec4(1.500000, 2.500000, 3.500000, 1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.500000, 2.500000, 3.500000, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(1.500000f),
					ScriptVariable(2.500000f),
					ScriptVariable(3.500000f),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 83
	// console.log("vec4(20, 10, 5, 1) / 2): ", div(vec4(20, 10, 5, 1), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[83];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4(20, 10, 5, 1) / 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of div(vec4(20, 10, 5, 1), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: div(vec4(20, 10, 5, 1), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 84
	// console.log("vec4(20, 10, 5, 1) * 2): ", mul(vec4(20, 10, 5, 1), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[84];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("vec4(20, 10, 5, 1) * 2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(vec4(20, 10, 5, 1), 2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(vec4(20, 10, 5, 1), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
				ScriptVariable(static_cast<int64_t>(2ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(static_cast<int64_t>(20ll)),
					ScriptVariable(static_cast<int64_t>(10ll)),
					ScriptVariable(static_cast<int64_t>(5ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 85
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[85];
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
	// statement: 86
	// console.log("Check quaternion math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[86];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check quaternion math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 87
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[87];
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
	// statement: 88
	// console.log("quaternion.identity(): ", quaternion.identity())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[88];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.identity(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of quaternion.identity()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: quaternion.identity()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: quaternion.identity
			returnValue.setValue(Quaternion().identity());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 89
	// console.log("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[89];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
				ScriptVariable(90.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(0.000000f),
					ScriptVariable(1.000000f),
					ScriptVariable(0.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.rotate
			Vector3 axis;
			float angle;
			if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
				returnValue.setValue(Quaternion().rotate(axis, angle));
			} else {
				Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 90
	// console.log("quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.normalize(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[90];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of quaternion.normalize(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: quaternion.normalize(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: quaternion.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.normalize
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.normalize());
			} else {
				Console::println(string("quaternion.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.normalize")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 91
	// console.log("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0): ", mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), quaternion.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[91];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), quaternion.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), quaternion.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of quaternion.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: quaternion.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: quaternion.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(1.000000, 0.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: vec3(1.000000, 0.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: quaternion.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 92
	// console.log("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0)): ", mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[92];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0.000000, 0.000000, 1.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: quaternion.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0.000000, 0.000000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(0.000000f),
					ScriptVariable(0.000000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 93
	// console.log("quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.computeMatrix(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[93];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of quaternion.computeMatrix(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: quaternion.computeMatrix(quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: quaternion.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.computeMatrix
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.computeMatrix());
			} else {
				Console::println(string("quaternion.computeMatrix") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("quaternion.computeMatrix")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 94
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[94];
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
	// statement: 95
	// console.log("Check matrix4x4 math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[95];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check matrix4x4 math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 96
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[96];
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
	// statement: 97
	// console.log("mat4.identity(): ", mat4.identity())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[97];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.identity(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.identity()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.identity()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat4.identity
			returnValue.setValue(Matrix4x4().identity());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 98
	// console.log("mat4.translate(vec3(1.0, 2.0, 3.0)): ", mat4.translate(vec3(1.000000, 2.000000, 3.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[98];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.translate(vec3(1.0, 2.0, 3.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.translate(vec3(1.000000, 2.000000, 3.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.translate(vec3(1.000000, 2.000000, 3.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1.000000, 2.000000, 3.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1.000000, 2.000000, 3.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.000000f),
					ScriptVariable(2.000000f),
					ScriptVariable(3.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.translate
			Vector3 translation;
			if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix4x4().identity().setTranslation(translation));
			} else {
				Console::println(string("mat4.translate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.translate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 99
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[99];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
				ScriptVariable(90.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(0.000000f),
					ScriptVariable(1.000000f),
					ScriptVariable(0.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.rotate
			Vector3 axis;
			float angle;
			if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
				returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
			} else {
				Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 100
	// console.log("mat4.scale(vec3(1.0, 2.0, 3.0)): ", mat4.scale(vec3(1.000000, 2.000000, 3.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[100];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.scale(vec3(1.0, 2.0, 3.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.scale(vec3(1.000000, 2.000000, 3.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.scale(vec3(1.000000, 2.000000, 3.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec3(1.000000, 2.000000, 3.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1.000000, 2.000000, 3.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(1.000000f),
					ScriptVariable(2.000000f),
					ScriptVariable(3.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.scale
			Vector3 vec3Value;
			float floatValue;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(floatValue));
			} else {
				Console::println(string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.scale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 101
	// console.log("mat4.scale(3.0): ", mat4.scale(3.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[101];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.scale(3.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.scale(3.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.scale(3.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(3.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat4.scale
			Vector3 vec3Value;
			float floatValue;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(floatValue));
			} else {
				Console::println(string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.scale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 102
	// console.log("mat4.invert(mat4.scale(3.0)): ", mat4.invert(mat4.scale(3.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[102];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.invert(mat4.scale(3.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.invert(mat4.scale(3.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.invert(mat4.scale(3.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of mat4.scale(3.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat4.scale(3.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(3.000000f)
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: mat4.scale
				Vector3 vec3Value;
				float floatValue;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
				} else
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(floatValue));
				} else {
					Console::println(string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.scale")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.invert
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.invert());
			} else {
				Console::println(string("mat4.invert") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.invert")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 103
	// console.log("mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", mat4.computeEulerAngles(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[103];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat4.computeEulerAngles(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat4.computeEulerAngles(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
				} else {
					Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.computeEulerAngles
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.computeEulerAngles());
			} else {
				Console::println(string("mat4.computeEulerAngles") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.computeEulerAngles")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 104
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0): ", mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[104];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of mat4.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
				} else {
					Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: mat4.rotate(vec3(1.000000, 0.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(1.000000, 0.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: vec3(1.000000, 0.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
				} else {
					Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 105
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0): ", mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[105];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * vec3(0.0, 0.0, 1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), vec3(0.000000, 0.000000, 1.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0.000000, 0.000000, 1.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(0.000000f),
						ScriptVariable(1.000000f),
						ScriptVariable(0.000000f)
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
				} else {
					Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0.000000, 0.000000, 1.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(0.000000f),
					ScriptVariable(0.000000f),
					ScriptVariable(1.000000f)
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 106
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.translate(vec3(1.0, 2.0, 3.0)) *  vec4(0.0, 0.0, 1.0, 0.0)): ", mul(mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.translate(vec3(1.000000, 2.000000, 3.000000))), vec4(0.000000, 0.000000, 1.000000, 0.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[106];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0) * mat4.translate(vec3(1.0, 2.0, 3.0)) *  vec4(0.0, 0.0, 1.0, 0.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.translate(vec3(1.000000, 2.000000, 3.000000))), vec4(0.000000, 0.000000, 1.000000, 0.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.translate(vec3(1.000000, 2.000000, 3.000000))), vec4(0.000000, 0.000000, 1.000000, 0.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.translate(vec3(1.000000, 2.000000, 3.000000)))
				ScriptVariable() // argumentValues[1] --> returnValue of vec4(0.000000, 0.000000, 1.000000, 0.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mul(mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000), mat4.translate(vec3(1.000000, 2.000000, 3.000000)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
					ScriptVariable() // argumentValues[1] --> returnValue of mat4.translate(vec3(1.000000, 2.000000, 3.000000))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: mat4.rotate(vec3(0.000000, 1.000000, 0.000000), 90.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(), // argumentValues[0] --> returnValue of vec3(0.000000, 1.000000, 0.000000)
						ScriptVariable(90.000000f)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// depth = 4 / argument index = 0: vec3(0.000000, 1.000000, 0.000000)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[0];
						array<ScriptVariable, 3> argumentValues {
							ScriptVariable(0.000000f),
							ScriptVariable(1.000000f),
							ScriptVariable(0.000000f)
						};
						array<ScriptVariable, 3>& argumentValuesD4AIDX0 = argumentValues;
						// method code: vec3
						Vector3 result;
						float xValue;
						float yValue;
						float zValue;
						if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
							MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
							returnValue.setValue(Vector3(xValue, yValue, zValue));
						} else {
							Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
							miniScript->startErrorScript(); return;
						}
					}
					// method code: mat4.rotate
					Vector3 axis;
					float angle;
					if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
						returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
					} else {
						Console::println(string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.rotate")));
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: mat4.translate(vec3(1.000000, 2.000000, 3.000000))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable() // argumentValues[0] --> returnValue of vec3(1.000000, 2.000000, 3.000000)
					};
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 0: vec3(1.000000, 2.000000, 3.000000)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 3> argumentValues {
							ScriptVariable(1.000000f),
							ScriptVariable(2.000000f),
							ScriptVariable(3.000000f)
						};
						array<ScriptVariable, 3>& argumentValuesD4AIDX0 = argumentValues;
						// method code: vec3
						Vector3 result;
						float xValue;
						float yValue;
						float zValue;
						if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
							MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
							MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
							returnValue.setValue(Vector3(xValue, yValue, zValue));
						} else {
							Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
							miniScript->startErrorScript(); return;
						}
					}
					// method code: mat4.translate
					Vector3 translation;
					if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
						returnValue.setValue(Matrix4x4().identity().setTranslation(translation));
					} else {
						Console::println(string("mat4.translate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat4.translate")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mul
				MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
			}
			// depth = 2 / argument index = 1: vec4(0.000000, 0.000000, 1.000000, 0.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues {
					ScriptVariable(0.000000f),
					ScriptVariable(0.000000f),
					ScriptVariable(1.000000f),
					ScriptVariable(0.000000f)
				};
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec4
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec4")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 107
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[107];
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
	// statement: 108
	// console.log("Check matrix3x3 math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[108];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check matrix3x3 math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 109
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[109];
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
	// statement: 110
	// console.log("mat3.identity(): ", mat3.identity())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[110];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.identity(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.identity()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.identity()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat3.identity
			returnValue.setValue(Matrix3x3().identity());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 111
	// console.log("mat3.translate(vec2(1.0, 2.0)): ", mat3.translate(vec2(1.000000, 2.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[111];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.translate(vec2(1.0, 2.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.translate(vec2(1.000000, 2.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.translate(vec2(1.000000, 2.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(1.000000, 2.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1.000000, 2.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.000000f),
					ScriptVariable(2.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.translate
			Vector2 translation;
			if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix3x3().identity().setTranslation(translation));
			} else {
				Console::println(string("mat3.translate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.translate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 112
	// console.log("mat3.rotate(90.0): ", mat3.rotate(90.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[112];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.rotate(90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.rotate(90.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.rotate(90.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(90.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat3.rotate
			float angle;
			if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
				returnValue.setValue(Matrix3x3().identity().setAxes(angle));
			} else {
				Console::println(string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.rotate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 113
	// console.log("mat3.rotateAroundTextureCenter(90.0): ", mat3.rotateAroundTextureCenter(90.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[113];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.rotateAroundTextureCenter(90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.rotateAroundTextureCenter(90.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.rotateAroundTextureCenter(90.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(90.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat3.rotateAroundTextureCenter
			float angle;
			if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
				returnValue.setValue(Matrix3x3::rotateAroundTextureCenter(angle));
			} else {
				Console::println(string("mat3.rotateAroundTextureCenter") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.rotateAroundTextureCenter")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 114
	// console.log("mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): ", mat3.rotateAroundPoint(vec2(0.500000, 0.400000), 90.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[114];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.rotateAroundPoint(vec2(0.500000, 0.400000), 90.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.rotateAroundPoint(vec2(0.500000, 0.400000), 90.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec2(0.500000, 0.400000)
				ScriptVariable(90.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(0.500000, 0.400000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(0.500000f),
					ScriptVariable(0.400000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.rotateAroundPoint
			Vector2 point;
			float angle;
			if (MiniScript::getVector2Value(argumentValues, 0, point, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
				returnValue.setValue(Matrix3x3().rotateAroundPoint(point, angle));
			} else {
				Console::println(string("mat3.rotateAroundPoint") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.rotateAroundPoint")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 115
	// console.log("mat3.scale(vec2(1.0, 2.0)): ", mat3.scale(vec2(1.000000, 2.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[115];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.scale(vec2(1.0, 2.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.scale(vec2(1.000000, 2.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.scale(vec2(1.000000, 2.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of vec2(1.000000, 2.000000)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec2(1.000000, 2.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.000000f),
					ScriptVariable(2.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.scale
			Vector2 vec2Value;
			float floatValue;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
				returnValue.setValue(Matrix3x3().identity().scale(vec2Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix3x3().identity().scale(floatValue));
			} else {
				Console::println(string("mat3.scale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.scale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 116
	// console.log("mat3.scale(3.0): ", mat3.scale(3.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[116];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.scale(3.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mat3.scale(3.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mat3.scale(3.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(3.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat3.scale
			Vector2 vec2Value;
			float floatValue;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
				returnValue.setValue(Matrix3x3().identity().scale(vec2Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix3x3().identity().scale(floatValue));
			} else {
				Console::println(string("mat3.scale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.scale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 117
	// console.log("mat3.rotate(90.0) * mat3.translate(vec2(1.0, 2.0)): ", mul(mat3.rotate(90.000000), mat3.translate(vec2(1.000000, 2.000000))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[117];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.rotate(90.0) * mat3.translate(vec2(1.0, 2.0)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(mat3.rotate(90.000000), mat3.translate(vec2(1.000000, 2.000000)))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(mat3.rotate(90.000000), mat3.translate(vec2(1.000000, 2.000000)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of mat3.rotate(90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of mat3.translate(vec2(1.000000, 2.000000))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat3.rotate(90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: mat3.rotate
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix3x3().identity().setAxes(angle));
				} else {
					Console::println(string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: mat3.translate(vec2(1.000000, 2.000000))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable() // argumentValues[0] --> returnValue of vec2(1.000000, 2.000000)
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: vec2(1.000000, 2.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(1.000000f),
						ScriptVariable(2.000000f)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// method code: vec2
					Vector3 result;
					float xValue;
					float yValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
						returnValue.setValue(Vector2(xValue, yValue));
					} else {
						Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat3.translate
				Vector2 translation;
				if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
					returnValue.setValue(Matrix3x3().identity().setTranslation(translation));
				} else {
					Console::println(string("mat3.translate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.translate")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 118
	// console.log("mat3.rotate(90.0) * vec2(1.0, 2.0): ", mul(mat3.rotate(90.000000), vec2(1.000000, 2.000000)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[118];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("mat3.rotate(90.0) * vec2(1.0, 2.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(mat3.rotate(90.000000), vec2(1.000000, 2.000000))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(mat3.rotate(90.000000), vec2(1.000000, 2.000000))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of mat3.rotate(90.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of vec2(1.000000, 2.000000)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: mat3.rotate(90.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(90.000000f)
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// method code: mat3.rotate
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix3x3().identity().setAxes(angle));
				} else {
					Console::println(string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("mat3.rotate")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.000000, 2.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(1.000000f),
					ScriptVariable(2.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec2")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 119
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[119];
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
	// statement: 120
	// console.log("Check additional math")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[120];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check additional math"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 121
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[121];
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
	// statement: 122
	// console.log("math.PI(): ", math.PI())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[122];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.PI(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.PI()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.PI()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.PI
			returnValue.setValue(Math::PI);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 123
	// console.log("math.EPSILON(): ", math.EPSILON())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[123];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.EPSILON(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.EPSILON()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.EPSILON()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.EPSILON
			returnValue.setValue(Math::EPSILON);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 124
	// console.log("math.DEG2RAD(): ", math.DEG2RAD())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[124];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.DEG2RAD(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.DEG2RAD()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.DEG2RAD()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.DEG2RAD
			returnValue.setValue(Math::DEG2RAD);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 125
	// console.log("math.G(): ", math.G())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[125];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.G(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.G()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.G()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.G
			returnValue.setValue(Math::G);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 126
	// console.log("math.acos(0.0): ", math.acos(0.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[126];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.acos(0.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.acos(0.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.acos(0.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(0.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.acos
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::acos(x));
			} else {
				Console::println(string("math.acos") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.acos")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 127
	// console.log("math.asin(1.0): ", math.asin(1.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[127];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.asin(1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.asin(1.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.asin(1.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(1.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.asin
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::asin(x));
			} else {
				Console::println(string("math.asin") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.asin")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 128
	// console.log("math.atan(1.0): ", math.atan(1.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[128];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.atan(1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.atan(1.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.atan(1.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(1.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.atan
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::atan(x));
			} else {
				Console::println(string("math.atan") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.atan")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 129
	// console.log("math.atan2(-1.0, -1.0): ", math.atan2(-1.000000, -1.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[129];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.atan2(-1.0, -1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.atan2(-1.000000, -1.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.atan2(-1.000000, -1.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(-1.000000f),
				ScriptVariable(-1.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.atan2
			float y;
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, y, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, x, false) == true) {
				returnValue.setValue(Math::atan2(y, x));
			} else {
				Console::println(string("math.atan2") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.atan2")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 130
	// console.log("math.floor(2.87): ", math.floor(2.870000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[130];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.floor(2.87): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.floor(2.870000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.floor(2.870000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(2.870000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.floor
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::floor(value));
			} else {
				Console::println(string("math.floor") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.floor")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 131
	// console.log("math.ceil(2.87): ", math.ceil(2.870000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[131];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.ceil(2.87): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.ceil(2.870000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.ceil(2.870000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(2.870000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.ceil
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::ceil(value));
			} else {
				Console::println(string("math.ceil") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.ceil")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 132
	// console.log("math.round(2.37): ", math.round(2.370000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[132];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.round(2.37): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.round(2.370000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.round(2.370000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(2.370000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.round
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::round(value));
			} else {
				Console::println(string("math.round") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.round")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 133
	// console.log("math.round(2.87): ", math.round(2.870000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[133];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.round(2.87): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.round(2.870000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.round(2.870000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(2.870000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.round
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::round(value));
			} else {
				Console::println(string("math.round") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.round")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 134
	// console.log("math.cos(0.0): ", math.cos(0.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[134];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.cos(0.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.cos(0.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.cos(0.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(0.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.cos
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::cos(x));
			} else {
				Console::println(string("math.cos") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.cos")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 135
	// console.log("math.sin(0.0): ", math.sin(0.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[135];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.sin(0.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.sin(0.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.sin(0.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(0.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.sin
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::sin(x));
			} else {
				Console::println(string("math.sin") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.sin")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 136
	// console.log("math.tan(1.0): ", math.tan(1.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[136];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.tan(1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.tan(1.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.tan(1.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(1.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.tan
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, x, false) == true) {
				returnValue.setValue(Math::tan(x));
			} else {
				Console::println(string("math.tan") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.tan")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 137
	// console.log("math.sqrt(9.0): ", math.sqrt(9))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[137];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.sqrt(9.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.sqrt(9)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.sqrt(9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(static_cast<int64_t>(9ll))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.sqrt
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::sqrt(value));
			} else {
				Console::println(string("math.sqrt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.sqrt")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 138
	// console.log("math.random(): ", math.random())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[138];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.random(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.random()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.random()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 139
	// console.log("math.random(): ", math.random())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[139];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.random(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.random()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.random()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 140
	// console.log("math.random(): ", math.random())
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[140];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.random(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.random()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.random()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 141
	// console.log("math.exp(1.0): ", math.exp(1.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[141];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.exp(1.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.exp(1.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.exp(1.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(1.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.exp
			float power;
			if (MiniScript::getFloatValue(argumentValues, 0, power, false) == true) {
				returnValue.setValue(Math::exp(power));
			} else {
				Console::println(string("math.exp") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.exp")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 142
	// console.log("math.log(2.0): ", math.log(2.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[142];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.log(2.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.log(2.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.log(2.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(2.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.log
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::log(value));
			} else {
				Console::println(string("math.log") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.log")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 143
	// console.log("math.sign(-2): ", math.sign(-2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[143];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.sign(-2): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.sign(-2)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.sign(-2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(static_cast<int64_t>(-2ll))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.sign
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::sign(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::sign(intValue));
			} else {
				Console::println(string("math.sign") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.sign")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 144
	// console.log("math.sign(-2.0): ", math.sign(-2.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[144];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.sign(-2.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.sign(-2.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.sign(-2.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(-2.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.sign
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::sign(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::sign(intValue));
			} else {
				Console::println(string("math.sign") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.sign")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 145
	// console.log("math.square(3): ", math.square(3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[145];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.square(3): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.square(3)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.square(3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(static_cast<int64_t>(3ll))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.square
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::square(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::square(intValue));
			} else {
				Console::println(string("math.square") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.square")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 146
	// console.log("math.square(3.0): ", math.square(3.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[146];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.square(3.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.square(3.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.square(3.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(3.000000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.square
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::square(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::square(intValue));
			} else {
				Console::println(string("math.square") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.square")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 147
	// console.log("math.min(4, 9): ", math.min(4, 9))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[147];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.min(4, 9): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.min(4, 9)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.min(4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(4ll)),
				ScriptVariable(static_cast<int64_t>(9ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.min
			int64_t intValue1;
			int64_t intValue2;
			float floatValue1;
			float floatValue2;
			if (argumentValues.size() != 2) {
				Console::println(string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.min")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValue1, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValue2, false) == true) {
				returnValue.setValue(Math::min(floatValue1, floatValue2));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue1, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValue2, false) == true) {
				returnValue.setValue(Math::min(intValue1, intValue2));
			} else {
				Console::println(string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.min")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 148
	// console.log("math.min(4.1, 9.3): ", math.min(4.100000, 9.300000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[148];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.min(4.1, 9.3): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.min(4.100000, 9.300000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.min(4.100000, 9.300000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(4.100000f),
				ScriptVariable(9.300000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.min
			int64_t intValue1;
			int64_t intValue2;
			float floatValue1;
			float floatValue2;
			if (argumentValues.size() != 2) {
				Console::println(string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.min")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValue1, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValue2, false) == true) {
				returnValue.setValue(Math::min(floatValue1, floatValue2));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue1, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValue2, false) == true) {
				returnValue.setValue(Math::min(intValue1, intValue2));
			} else {
				Console::println(string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.min")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 149
	// console.log("math.max(4, 9): ", math.max(4, 9))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[149];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.max(4, 9): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.max(4, 9)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.max(4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(4ll)),
				ScriptVariable(static_cast<int64_t>(9ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.max
			int64_t intValue1;
			int64_t intValue2;
			float floatValue1;
			float floatValue2;
			if (argumentValues.size() != 2) {
				Console::println(string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.max")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValue1, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValue2, false) == true) {
				returnValue.setValue(Math::max(floatValue1, floatValue2));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue1, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValue2, false) == true) {
				returnValue.setValue(Math::max(intValue1, intValue2));
			} else {
				Console::println(string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.max")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 150
	// console.log("math.max(4.1, 9.3): ", math.max(4.100000, 9.300000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[150];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.max(4.1, 9.3): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.max(4.100000, 9.300000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.max(4.100000, 9.300000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(4.100000f),
				ScriptVariable(9.300000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.max
			int64_t intValue1;
			int64_t intValue2;
			float floatValue1;
			float floatValue2;
			if (argumentValues.size() != 2) {
				Console::println(string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.max")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValue1, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValue2, false) == true) {
				returnValue.setValue(Math::max(floatValue1, floatValue2));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue1, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValue2, false) == true) {
				returnValue.setValue(Math::max(intValue1, intValue2));
			} else {
				Console::println(string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.max")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 151
	// console.log("math.abs(-9): ", math.abs(-9))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[151];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.abs(-9): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.abs(-9)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.abs(-9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(static_cast<int64_t>(-9ll))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.abs
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::abs(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::abs(intValue));
			} else {
				Console::println(string("math.abs") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.abs")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 152
	// console.log("math.abs(-9.3): ", math.abs(-9.300000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[152];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.abs(-9.3): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.abs(-9.300000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.abs(-9.300000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(-9.300000f)
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.abs
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::abs(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::abs(intValue));
			} else {
				Console::println(string("math.abs") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.abs")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 153
	// console.log("math.clamp(-1, 4, 9): ", math.clamp(-1, 4, 9))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[153];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.clamp(-1, 4, 9): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.clamp(-1, 4, 9)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.clamp(-1, 4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(-1ll)),
				ScriptVariable(static_cast<int64_t>(4ll)),
				ScriptVariable(static_cast<int64_t>(9ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.clamp
			int64_t intValueA;
			int64_t intValueB;
			int64_t intValueC;
			float floatValueA;
			float floatValueB;
			float floatValueC;
			if (argumentValues.size() != 3) {
				Console::println(string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.clamp")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, floatValueC, false) == true) {
				returnValue.setValue(Math::clamp(floatValueA, floatValueB, floatValueC));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 2, intValueC, false) == true) {
				returnValue.setValue(Math::clamp(intValueA, intValueB, intValueC));
			} else {
				Console::println(string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.clamp")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 154
	// console.log("math.clamp(10.0, 4.1, 9.3): ", math.clamp(10.000000, 4.100000, 9.300000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[154];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.clamp(10.0, 4.1, 9.3): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.clamp(10.000000, 4.100000, 9.300000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.clamp(10.000000, 4.100000, 9.300000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(10.000000f),
				ScriptVariable(4.100000f),
				ScriptVariable(9.300000f)
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.clamp
			int64_t intValueA;
			int64_t intValueB;
			int64_t intValueC;
			float floatValueA;
			float floatValueB;
			float floatValueC;
			if (argumentValues.size() != 3) {
				Console::println(string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.clamp")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, floatValueC, false) == true) {
				returnValue.setValue(Math::clamp(floatValueA, floatValueB, floatValueC));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 2, intValueC, false) == true) {
				returnValue.setValue(Math::clamp(intValueA, intValueB, intValueC));
			} else {
				Console::println(string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.clamp")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 155
	// console.log("math.pow(2, 16): ", math.pow(2, 16))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[155];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.pow(2, 16): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.pow(2, 16)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.pow(2, 16)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(16ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.pow
			int64_t intValueBase;
			int64_t intValuePower;
			float floatValueBase;
			float floatValuePower;
			if (argumentValues.size() != 2) {
				Console::println(string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.pow")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueBase, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValuePower, false) == true) {
				returnValue.setValue(Math::pow(floatValueBase, floatValuePower));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueBase, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValuePower, false) == true) {
				returnValue.setValue(static_cast<int64_t>(Math::pow(intValueBase, intValuePower)));
			} else {
				Console::println(string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.pow")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 156
	// console.log("math.pow(2.0, 16.0): ", math.pow(2.000000, 16.000000))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[156];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.pow(2.0, 16.0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.pow(2.000000, 16.000000)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.pow(2.000000, 16.000000)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(2.000000f),
				ScriptVariable(16.000000f)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.pow
			int64_t intValueBase;
			int64_t intValuePower;
			float floatValueBase;
			float floatValuePower;
			if (argumentValues.size() != 2) {
				Console::println(string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.pow")));
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueBase, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValuePower, false) == true) {
				returnValue.setValue(Math::pow(floatValueBase, floatValuePower));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueBase, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValuePower, false) == true) {
				returnValue.setValue(static_cast<int64_t>(Math::pow(intValueBase, intValuePower)));
			} else {
				Console::println(string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.pow")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 157
	// console.log("math.mod(187, 180): ", math.mod(187, 180))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[157];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.mod(187, 180): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.mod(187, 180)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.mod(187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(187ll)),
				ScriptVariable(static_cast<int64_t>(180ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.mod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.mod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.mod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 158
	// console.log("math.mod(-187, 180): ", math.mod(-187, 180))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[158];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.mod(-187, 180): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.mod(-187, 180)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.mod(-187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(-187ll)),
				ScriptVariable(static_cast<int64_t>(180ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.mod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.mod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::mod(value, range));
				} else {
					Console::println(string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.mod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 159
	// console.log("math.absmod(187, 180): ", math.absmod(187, 180))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[159];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.absmod(187, 180): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.absmod(187, 180)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.absmod(187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(187ll)),
				ScriptVariable(static_cast<int64_t>(180ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.absmod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::absmod(value, range));
				} else {
					Console::println(string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.absmod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::absmod(value, range));
				} else {
					Console::println(string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.absmod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 160
	// console.log("math.absmod(-187, 180): ", math.absmod(-187, 180))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[160];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("math.absmod(-187, 180): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of math.absmod(-187, 180)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: math.absmod(-187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(static_cast<int64_t>(-187ll)),
				ScriptVariable(static_cast<int64_t>(180ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.absmod
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_INTEGER) == true) {
				int64_t value;
				int64_t range;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::absmod(value, range));
				} else {
					Console::println(string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.absmod")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float value;
				float range;
				if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
					returnValue.setValue(Math::absmod(value, range));
				} else {
					Console::println(string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("math.absmod")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 161
	// console.log("-----------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[161];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 162
	// console.log("Check transform")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[162];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check transform"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 163
	// console.log("-----------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[163];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-----------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 164
	// console.log("$transform = transform(vec3(1,2,3), vec3(2, 3, 4)")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[164];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("$transform = transform(vec3(1,2,3), vec3(2, 3, 4)"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 165
	// setVariable("$transform", transform(vec3(1, 2, 3), vec3(2, 3, 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[165];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$transform")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform(vec3(1, 2, 3), vec3(2, 3, 4))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform(vec3(1, 2, 3), vec3(2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of vec3(1, 2, 3)
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(2, 3, 4)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(2ll)),
					ScriptVariable(static_cast<int64_t>(3ll)),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform
			Transform transform;
			Vector3 vec3Value;
			float floatValue;
			// translation
			if (argumentValues.size() >= 1) {
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
					transform.setTranslation(vec3Value);
				} else {
					Console::println(string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform")));
					miniScript->startErrorScript(); return;
				}
			}
			// scale
			if (argumentValues.size() >= 2) {
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
					transform.setScale(vec3Value);
				} else {
					Console::println(string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform")));
					miniScript->startErrorScript(); return;
				}
			}
			// rotations: we always use euler angles here
			transform.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
			transform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
			transform.addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
			//
			for (auto i = 2; i < argumentValues.size() && i < 5; i++) {
				if (MiniScript::getFloatValue(argumentValues, i, floatValue, true) == true) {
					transform.setRotationAngle(i - 2, floatValue);
				} else {
					Console::println(string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform")));
					miniScript->startErrorScript(); return;
				}
			}
			transform.update();
			returnValue.setValue(transform);
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
	// statement: 166
	// console.log("$transform: ", getVariable("$transform"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[166];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$transform: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$transform")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$transform"))
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 167
	// console.log("transform.setRotationAngle($transform, 1, 90)")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[167];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("transform.setRotationAngle($transform, 1, 90)"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 168
	// transform.setRotationAngle(getVariable("$transform"), 1, 90)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[168];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
			ScriptVariable(static_cast<int64_t>(1ll)),
			ScriptVariable(static_cast<int64_t>(90ll))
		};
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$transform"))
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
		// method code: transform.setRotationAngle
		int64_t idx;
		Transform transform;
		float angle;
		if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
			MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
			MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
			if (idx < transform.getRotationCount()) {
				transform.setRotationAngle(idx, angle);
				transform.update();
				argumentValues[0].setValue(transform);
			} else {
				Console::println(string("transform.setRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
				// assign back
				setVariable("$transform", argumentValues[0], &statement);
				//
				miniScript->startErrorScript(); return;
			}
		} else {
			Console::println(string("transform.setRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.setRotationAngle")));
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}
	// statement: 169
	// console.log("transform.getRotationAngle($transform, 1): ", transform.getRotationAngle(getVariable("$transform"), 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[169];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getRotationAngle($transform, 1): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getRotationAngle(getVariable("$transform"), 1)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getRotationAngle(getVariable("$transform"), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
				ScriptVariable(static_cast<int64_t>(1ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getRotationAngle
			int64_t idx;
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
				if (idx < transform.getRotationCount()) {
					returnValue.setValue(transform.getRotationAngle(idx));
				} else {
					Console::println(string("transform.getRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println(string("transform.getRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getRotationAngle")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 170
	// console.log("transform.getTranslation($transform): ", transform.getTranslation(getVariable("$transform")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[170];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getTranslation($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getTranslation(getVariable("$transform"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getTranslation(getVariable("$transform"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$transform")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getTranslation
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTranslation());
			} else {
				Console::println(string("transform.getTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getTranslation")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 171
	// console.log("transform.setTranslation($transform, vec3(-1,-2,-3))")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[171];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("transform.setTranslation($transform, vec3(-1,-2,-3))"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 172
	// transform.setTranslation(getVariable("$transform"), vec3(-1, -2, -3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[172];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
			ScriptVariable() // argumentValues[1] --> returnValue of vec3(-1, -2, -3)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$transform"))
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
		// depth = 1 / argument index = 1: vec3(-1, -2, -3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(-1ll)),
				ScriptVariable(static_cast<int64_t>(-2ll)),
				ScriptVariable(static_cast<int64_t>(-3ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: vec3
			Vector3 result;
			float xValue;
			float yValue;
			float zValue;
			if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
				returnValue.setValue(Vector3(xValue, yValue, zValue));
			} else {
				Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: transform.setTranslation
		Transform transform;
		Vector3 translation;
		if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
			MiniScript::getVector3Value(argumentValues, 1, translation, false) == true) {
			transform.setTranslation(translation);
			transform.update();
			argumentValues[0].setValue(transform);
		} else {
			Console::println(string("transform.setTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.setTranslation")));
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}
	// statement: 173
	// console.log("transform.getTranslation($transform): ", transform.getTranslation(getVariable("$transform")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[173];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getTranslation($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getTranslation(getVariable("$transform"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getTranslation(getVariable("$transform"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$transform")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getTranslation
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTranslation());
			} else {
				Console::println(string("transform.getTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getTranslation")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 174
	// console.log("transform.getScale($transform): ", transform.getScale(getVariable("$transform")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[174];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getScale($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getScale(getVariable("$transform"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getScale(getVariable("$transform"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$transform")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getScale
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getScale());
			} else {
				Console::println(string("transform.getScale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getScale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 175
	// console.log("transform.setScale($transform, vec3(-2,-3,-4))")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[175];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("transform.setScale($transform, vec3(-2,-3,-4))"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 176
	// transform.setScale(getVariable("$transform"), vec3(-2, -3, -4))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[176];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
			ScriptVariable() // argumentValues[1] --> returnValue of vec3(-2, -3, -4)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$transform"))
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
		// depth = 1 / argument index = 1: vec3(-2, -3, -4)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(-2ll)),
				ScriptVariable(static_cast<int64_t>(-3ll)),
				ScriptVariable(static_cast<int64_t>(-4ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: vec3
			Vector3 result;
			float xValue;
			float yValue;
			float zValue;
			if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
				returnValue.setValue(Vector3(xValue, yValue, zValue));
			} else {
				Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: transform.setScale
		Transform transform;
		Vector3 scale;
		if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
			MiniScript::getVector3Value(argumentValues, 1, scale, false) == true) {
			transform.setScale(scale);
			transform.update();
			argumentValues[0].setValue(transform);
		} else {
			Console::println(string("transform.setScale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.setScale")));
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}
	// statement: 177
	// console.log("transform.getScale($transform): ", transform.getScale(getVariable("$transform")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[177];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getScale($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getScale(getVariable("$transform"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getScale(getVariable("$transform"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$transform")
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getScale
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getScale());
			} else {
				Console::println(string("transform.getScale") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getScale")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 178
	// console.log("transform.getRotationAxis($transform, 0): ", transform.getRotationAxis(getVariable("$transform"), 0))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[178];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getRotationAxis($transform, 0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.getRotationAxis(getVariable("$transform"), 0)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.getRotationAxis(getVariable("$transform"), 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
				ScriptVariable(static_cast<int64_t>(0ll))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// method code: transform.getRotationAxis
			int64_t idx;
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
				if (idx < transform.getRotationCount()) {
					returnValue.setValue(transform.getRotationAxis(idx));
				} else {
					Console::println(string("transform.getRotationAxis") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println(string("transform.getRotationAxis") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.getRotationAxis")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 179
	// console.log("$transform * vec3(0,0,0): ", mul(getVariable("$transform"), vec3(0, 0, 0)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[179];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$transform * vec3(0,0,0): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of mul(getVariable("$transform"), vec3(0, 0, 0))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: mul(getVariable("$transform"), vec3(0, 0, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0, 0, 0)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// depth = 2 / argument index = 1: vec3(0, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 180
	// console.log("transform.rotate($transform, vec3(0,0,1)): ", transform.rotate(getVariable("$transform"), vec3(0, 0, 1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[180];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.rotate($transform, vec3(0,0,1)): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of transform.rotate(getVariable("$transform"), vec3(0, 0, 1))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: transform.rotate(getVariable("$transform"), vec3(0, 0, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$transform")
				ScriptVariable() // argumentValues[1] --> returnValue of vec3(0, 0, 1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			// depth = 2 / argument index = 1: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(0ll)),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("vec3")));
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.rotate
			Transform transform;
			Vector3 vec3;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
				returnValue.setValue(transform.getRotationsQuaternion() * vec3);
			} else {
				Console::println(string("transform.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("transform.rotate")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 181
	// console.log("transform.getTransformMatrix($transform): ", internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getTransformMatrix"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[181];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getTransformMatrix($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getTransformMatrix")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getTransformMatrix")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$transform")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$transform")
				ScriptVariable(string("getTransformMatrix"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETTRANSFORMMATRIX;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 182
	// console.log("transform.getRotationsQuaternion($transform): ", internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getRotationsQuaternion"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[182];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("transform.getRotationsQuaternion($transform): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getRotationsQuaternion")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$transform", getVariable("$transform"), "getRotationsQuaternion")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$transform")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$transform")
				ScriptVariable(string("getRotationsQuaternion"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$transform"))
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONSQUATERNION;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 183
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[183];
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
	// statement: 184
	// console.log("Check string methods")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[184];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check string methods"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 185
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[185];
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
	// statement: 186
	// console.log(add("string.isInteger(1234): ", string.isInteger(1234)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[186];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.isInteger(1234): ", string.isInteger(1234))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.isInteger(1234): ", string.isInteger(1234))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.isInteger(1234): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.isInteger(1234)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.isInteger(1234)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(1234ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.isInteger
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Integer::is(stringValue));
				} else {
					Console::println(string("string.isInteger") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.isInteger")));
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
	// statement: 187
	// console.log(add("string.isInteger(abcd): ", string.isInteger("abcd")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[187];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.isInteger(abcd): ", string.isInteger("abcd"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.isInteger(abcd): ", string.isInteger("abcd"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.isInteger(abcd): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.isInteger("abcd")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.isInteger("abcd")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("abcd"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.isInteger
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Integer::is(stringValue));
				} else {
					Console::println(string("string.isInteger") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.isInteger")));
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
	// statement: 188
	// console.log(add("string.isFloat(1234.1234): ", string.isFloat(1234.123413)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[188];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.isFloat(1234.1234): ", string.isFloat(1234.123413))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.isFloat(1234.1234): ", string.isFloat(1234.123413))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.isFloat(1234.1234): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.isFloat(1234.123413)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.isFloat(1234.123413)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(1234.123413f)
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.isFloat
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Float::is(stringValue));
				} else {
					Console::println(string("string.isFloat") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.isFloat")));
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
	// statement: 189
	// console.log(add("string.isFloat(abcd.abcd): ", string.isFloat("abcd.abcd")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[189];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.isFloat(abcd.abcd): ", string.isFloat("abcd.abcd"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.isFloat(abcd.abcd): ", string.isFloat("abcd.abcd"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.isFloat(abcd.abcd): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.isFloat("abcd.abcd")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.isFloat("abcd.abcd")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("abcd.abcd"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.isFloat
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Float::is(stringValue));
				} else {
					Console::println(string("string.isFloat") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.isFloat")));
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
	// statement: 190
	// console.log(add("string.space(0): ", string.space(0)), "1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[190];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of add("string.space(0): ", string.space(0))
			ScriptVariable(string("1"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.space(0): ", string.space(0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.space(0): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.space(0)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.space(0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.space
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(string("string.space") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.space")));
					miniScript->startErrorScript(); return;
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
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
	// statement: 191
	// console.log(add("string.space(2): ", string.space(2)), "1.1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[191];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of add("string.space(2): ", string.space(2))
			ScriptVariable(string("1.1"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.space(2): ", string.space(2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.space(2): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.space(2)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.space(2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.space
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(string("string.space") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.space")));
					miniScript->startErrorScript(); return;
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
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
	// statement: 192
	// console.log(add("string.space(2): ", string.space(2)), "1.2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[192];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of add("string.space(2): ", string.space(2))
			ScriptVariable(string("1.2"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.space(2): ", string.space(2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.space(2): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.space(2)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.space(2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.space
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(string("string.space") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.space")));
					miniScript->startErrorScript(); return;
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
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
	// statement: 193
	// console.log(add("string.space(4): ", string.space(4)), "1.2.1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[193];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of add("string.space(4): ", string.space(4))
			ScriptVariable(string("1.2.1"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.space(4): ", string.space(4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.space(4): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.space(4)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.space(4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.space
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(string("string.space") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.space")));
					miniScript->startErrorScript(); return;
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
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
	// statement: 194
	// console.log("string.toUpperCase('xxxyyyzzz'): ", string.toUpperCase("xxxyyyzzz"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[194];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("string.toUpperCase('xxxyyyzzz'): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of string.toUpperCase("xxxyyyzzz")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: string.toUpperCase("xxxyyyzzz")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("xxxyyyzzz"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: string.toUpperCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toUpperCase(stringValue));
			} else {
				Console::println(string("string.toUpperCase") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.toUpperCase")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 195
	// console.log("string.toLowerCase('XXXYYYZZZ'): ", string.toLowerCase("XXXYYYZZZ"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[195];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("string.toLowerCase('XXXYYYZZZ'): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of string.toLowerCase("XXXYYYZZZ")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: string.toLowerCase("XXXYYYZZZ")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("XXXYYYZZZ"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: string.toLowerCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toLowerCase(stringValue));
			} else {
				Console::println(string("string.toLowerCase") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.toLowerCase")));
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 196
	// console.log(add("string.concatenate('abc', 'def', 'ghi'): ", string.concatenate("abc", "def", "ghi")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[196];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.concatenate('abc', 'def', 'ghi'): ", string.concatenate("abc", "def", "ghi"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.concatenate('abc', 'def', 'ghi'): ", string.concatenate("abc", "def", "ghi"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.concatenate('abc', 'def', 'ghi'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.concatenate("abc", "def", "ghi")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.concatenate("abc", "def", "ghi")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("abc")),
					ScriptVariable(string("def")),
					ScriptVariable(string("ghi"))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.concatenate
				string result;
				for (const auto& argumentValue: argumentValues) {
					result+= argumentValue.getValueAsString();
				}
				returnValue.setValue(result);
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
	// statement: 197
	// console.log(add("string.startsWith('abcdef', 'abc'): ", string.startsWith("abcdef", "abc")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[197];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.startsWith('abcdef', 'abc'): ", string.startsWith("abcdef", "abc"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.startsWith('abcdef', 'abc'): ", string.startsWith("abcdef", "abc"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.startsWith('abcdef', 'abc'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.startsWith("abcdef", "abc")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.startsWith("abcdef", "abc")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("abc"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.startsWith
				string stringValue;
				string prefix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, prefix, false) == false) {
					Console::println(string("string.startsWith") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.startsWith")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::startsWith(stringValue, prefix));
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
	// statement: 198
	// console.log(add("string.startsWith('abcdef', 'def'): ", string.startsWith("abcdef", "def")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[198];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.startsWith('abcdef', 'def'): ", string.startsWith("abcdef", "def"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.startsWith('abcdef', 'def'): ", string.startsWith("abcdef", "def"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.startsWith('abcdef', 'def'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.startsWith("abcdef", "def")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.startsWith("abcdef", "def")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.startsWith
				string stringValue;
				string prefix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, prefix, false) == false) {
					Console::println(string("string.startsWith") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.startsWith")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::startsWith(stringValue, prefix));
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
	// statement: 199
	// console.log(add("string.endsWith('abcdef', 'abc'): ", string.endsWith("abcdef", "abc")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[199];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.endsWith('abcdef', 'abc'): ", string.endsWith("abcdef", "abc"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.endsWith('abcdef', 'abc'): ", string.endsWith("abcdef", "abc"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.endsWith('abcdef', 'abc'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.endsWith("abcdef", "abc")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.endsWith("abcdef", "abc")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("abc"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.endsWith
				string stringValue;
				string suffix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, suffix, false) == false) {
					Console::println(string("string.endsWith") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.endsWith")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::endsWith(stringValue, suffix));
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
	// statement: 200
	// console.log(add("string.endsWith('abcdef', 'def'): ", string.endsWith("abcdef", "def")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[200];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.endsWith('abcdef', 'def'): ", string.endsWith("abcdef", "def"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.endsWith('abcdef', 'def'): ", string.endsWith("abcdef", "def"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.endsWith('abcdef', 'def'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.endsWith("abcdef", "def")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.endsWith("abcdef", "def")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.endsWith
				string stringValue;
				string suffix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, suffix, false) == false) {
					Console::println(string("string.endsWith") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.endsWith")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::endsWith(stringValue, suffix));
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
	// statement: 201
	// console.log(add("string.replace('abcdef', 'def', 'DEF'): ", string.replace("abcdef", "def", "DEF")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[201];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.replace('abcdef', 'def', 'DEF'): ", string.replace("abcdef", "def", "DEF"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.replace('abcdef', 'def', 'DEF'): ", string.replace("abcdef", "def", "DEF"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.replace('abcdef', 'def', 'DEF'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.replace("abcdef", "def", "DEF")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.replace("abcdef", "def", "DEF")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def")),
					ScriptVariable(string("DEF"))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.replace
				string stringValue;
				string what;
				string by;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 3, beginIndex, true) == false) {
					Console::println(string("string.replace") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.replace")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::replace(stringValue, what, by, beginIndex));
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
	// statement: 202
	// console.log(add("string.indexOf('abcdef', 'def'): ", string.indexOf("abcdef", "def")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[202];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.indexOf('abcdef', 'def'): ", string.indexOf("abcdef", "def"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.indexOf('abcdef', 'def'): ", string.indexOf("abcdef", "def"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.indexOf('abcdef', 'def'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.indexOf("abcdef", "def")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.indexOf("abcdef", "def")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.indexOf
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(string("string.indexOf") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.indexOf")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::indexOf(stringValue, what, beginIndex)));
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
	// statement: 203
	// console.log(add("string.firstIndexOf('abcdef', 'def'): ", string.firstIndexOf("abcdef", "def")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[203];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.firstIndexOf('abcdef', 'def'): ", string.firstIndexOf("abcdef", "def"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.firstIndexOf('abcdef', 'def'): ", string.firstIndexOf("abcdef", "def"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.firstIndexOf('abcdef', 'def'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.firstIndexOf("abcdef", "def")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.firstIndexOf("abcdef", "def")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.firstIndexOf
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(string("string.firstIndexOf") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.firstIndexOf")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::firstIndexOf(stringValue, what, beginIndex)));
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
	// statement: 204
	// console.log(add("string.lastIndexOf('abcdef', 'def'): ", string.lastIndexOf("abcdef", "def")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[204];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.lastIndexOf('abcdef', 'def'): ", string.lastIndexOf("abcdef", "def"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.lastIndexOf('abcdef', 'def'): ", string.lastIndexOf("abcdef", "def"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.lastIndexOf('abcdef', 'def'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.lastIndexOf("abcdef", "def")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.lastIndexOf("abcdef", "def")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("def"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.lastIndexOf
				string stringValue;
				string what;
				int64_t beginIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(string("string.lastIndexOf") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.lastIndexOf")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::lastIndexOf(stringValue, what, beginIndex)));
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
	// statement: 205
	// console.log(add("string.substring('abcdef', 3): ", string.substring("abcdef", 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[205];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.substring('abcdef', 3): ", string.substring("abcdef", 3))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.substring('abcdef', 3): ", string.substring("abcdef", 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.substring('abcdef', 3): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.substring("abcdef", 3)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.substring("abcdef", 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.substring
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, beginIndex, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, endIndex, true) == false) {
					Console::println(string("string.substring") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.substring")));
					miniScript->startErrorScript(); return;
				} else {
					if (endIndex == -1) {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex));
					} else {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex, endIndex));
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
	// statement: 206
	// console.log(add("string.substring('abcdef', 1, 5): ", string.substring("abcdef", 1, 5)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[206];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.substring('abcdef', 1, 5): ", string.substring("abcdef", 1, 5))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.substring('abcdef', 1, 5): ", string.substring("abcdef", 1, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.substring('abcdef', 1, 5): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.substring("abcdef", 1, 5)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.substring("abcdef", 1, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(1ll)),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.substring
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, beginIndex, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, endIndex, true) == false) {
					Console::println(string("string.substring") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.substring")));
					miniScript->startErrorScript(); return;
				} else {
					if (endIndex == -1) {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex));
					} else {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex, endIndex));
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
	// statement: 207
	// console.log(add("string.equalsIgnoreCase('abcdef', 'ABCDEF'): ", string.equalsIgnoreCase("'abcdef'", "'ABCDEF'")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[207];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.equalsIgnoreCase('abcdef', 'ABCDEF'): ", string.equalsIgnoreCase("'abcdef'", "'ABCDEF'"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.equalsIgnoreCase('abcdef', 'ABCDEF'): ", string.equalsIgnoreCase("'abcdef'", "'ABCDEF'"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.equalsIgnoreCase('abcdef', 'ABCDEF'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.equalsIgnoreCase("'abcdef'", "'ABCDEF'")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.equalsIgnoreCase("'abcdef'", "'ABCDEF'")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("'abcdef'")),
					ScriptVariable(string("'ABCDEF'"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.equalsIgnoreCase
				string stringValue;
				string other;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, other, false) == false) {
					Console::println(string("string.equalsIgnoreCase") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.equalsIgnoreCase")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::equalsIgnoreCase(stringValue, other));
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
	// statement: 208
	// console.log(add("string.trim('   abcdef   '): ", add("'", add(string.trim("   abcdef   "), "'"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[208];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.trim('   abcdef   '): ", add("'", add(string.trim("   abcdef   "), "'")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.trim('   abcdef   '): ", add("'", add(string.trim("   abcdef   "), "'")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.trim('   abcdef   '): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add("'", add(string.trim("   abcdef   "), "'"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add("'", add(string.trim("   abcdef   "), "'"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("'")),
					ScriptVariable() // argumentValues[1] --> returnValue of add(string.trim("   abcdef   "), "'")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: add(string.trim("   abcdef   "), "'")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(), // argumentValues[0] --> returnValue of string.trim("   abcdef   ")
						ScriptVariable(string("'"))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 0: string.trim("   abcdef   ")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("   abcdef   "))
						};
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						// method code: string.trim
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false) {
							Console::println(string("string.trim") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.trim")));
							miniScript->startErrorScript(); return;
						} else {
							returnValue.setValue(StringTools::trim(stringValue));
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
	// statement: 209
	// console.log(add("string.regexMatch('abcdef', '[a-z]*'): ", string.regexMatch("abcdef", "[a-z]*")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[209];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.regexMatch('abcdef', '[a-z]*'): ", string.regexMatch("abcdef", "[a-z]*"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.regexMatch('abcdef', '[a-z]*'): ", string.regexMatch("abcdef", "[a-z]*"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.regexMatch('abcdef', '[a-z]*'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.regexMatch("abcdef", "[a-z]*")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.regexMatch("abcdef", "[a-z]*")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("[a-z]*"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.regexMatch
				string stringValue;
				string pattern;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false) {
					Console::println(string("string.regexMatch") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.regexMatch")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::regexMatch(stringValue, pattern));
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
	// statement: 210
	// console.log(add("string.regexMatch('abcdef', '[0-9]*'): ", string.regexMatch("abcdef", "[0-9]*")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[210];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.regexMatch('abcdef', '[0-9]*'): ", string.regexMatch("abcdef", "[0-9]*"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.regexMatch('abcdef', '[0-9]*'): ", string.regexMatch("abcdef", "[0-9]*"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.regexMatch('abcdef', '[0-9]*'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.regexMatch("abcdef", "[0-9]*")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.regexMatch("abcdef", "[0-9]*")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("[0-9]*"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.regexMatch
				string stringValue;
				string pattern;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false) {
					Console::println(string("string.regexMatch") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.regexMatch")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::regexMatch(stringValue, pattern));
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
	// statement: 211
	// console.log(add("string.regexReplace('abcdef', '[bcde]', '-'): ", string.regexReplace("abcdef", "[bcde]", "-")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[211];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.regexReplace('abcdef', '[bcde]', '-'): ", string.regexReplace("abcdef", "[bcde]", "-"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.regexReplace('abcdef', '[bcde]', '-'): ", string.regexReplace("abcdef", "[bcde]", "-"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.regexReplace('abcdef', '[bcde]', '-'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.regexReplace("abcdef", "[bcde]", "-")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.regexReplace("abcdef", "[bcde]", "-")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(string("[bcde]")),
					ScriptVariable(string("-"))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.regexReplace
				string stringValue;
				string pattern;
				string by;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false) {
					Console::println(string("string.regexReplace") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.regexReplace")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::regexReplace(stringValue, pattern, by));
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
	// statement: 212
	// console.log(add("string.tokenize('Andreas is a very good boy', ' '): ", string.tokenize("Andreas is a very good boy <3", " ")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[212];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.tokenize('Andreas is a very good boy', ' '): ", string.tokenize("Andreas is a very good boy <3", " "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.tokenize('Andreas is a very good boy', ' '): ", string.tokenize("Andreas is a very good boy <3", " "))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.tokenize('Andreas is a very good boy', ' '): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.tokenize("Andreas is a very good boy <3", " ")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.tokenize("Andreas is a very good boy <3", " ")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("Andreas is a very good boy <3")),
					ScriptVariable(string(" "))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.tokenize
				string stringValue;
				string delimiters;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, delimiters, false) == false) {
					Console::println(string("string.tokenize") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.tokenize")));
					miniScript->startErrorScript(); return;
				} else {
					auto tokenizedStringVector = StringTools::tokenize(stringValue, delimiters);
					//
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& tokenizedString: tokenizedStringVector) {
						returnValue.pushArrayValue(tokenizedString);
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
	// statement: 213
	// console.log(add("string.length('abcdef'): ", string.length("abcdef")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[213];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.length('abcdef'): ", string.length("abcdef"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.length('abcdef'): ", string.length("abcdef"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.length('abcdef'): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.length("abcdef")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.length("abcdef")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("abcdef"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.length
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(static_cast<int64_t>(stringValue.size()));
				} else {
					Console::println(string("string.length") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.length")));
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
	// statement: 214
	// console.log(add("string.charAt('abcdef', 0): ", string.charAt("abcdef", 0)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[214];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 0): ", string.charAt("abcdef", 0))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 0): ", string.charAt("abcdef", 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 0): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 0)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(0ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 215
	// console.log(add("string.charAt('abcdef', 1): ", string.charAt("abcdef", 1)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[215];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 1): ", string.charAt("abcdef", 1))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 1): ", string.charAt("abcdef", 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 1): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 1)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(1ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 216
	// console.log(add("string.charAt('abcdef', 2): ", string.charAt("abcdef", 2)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[216];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 2): ", string.charAt("abcdef", 2))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 2): ", string.charAt("abcdef", 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 2): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 2)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 217
	// console.log(add("string.charAt('abcdef', 3): ", string.charAt("abcdef", 3)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[217];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 3): ", string.charAt("abcdef", 3))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 3): ", string.charAt("abcdef", 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 3): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 3)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(3ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 218
	// console.log(add("string.charAt('abcdef', 4): ", string.charAt("abcdef", 4)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[218];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 4): ", string.charAt("abcdef", 4))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 4): ", string.charAt("abcdef", 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 4): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 4)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(4ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 219
	// console.log(add("string.charAt('abcdef', 5): ", string.charAt("abcdef", 5)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[219];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 5): ", string.charAt("abcdef", 5))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 5): ", string.charAt("abcdef", 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 5): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 5)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(5ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 220
	// console.log(add("string.charAt('abcdef', 6): ", string.charAt("abcdef", 6)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[220];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.charAt('abcdef', 6): ", string.charAt("abcdef", 6))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.charAt('abcdef', 6): ", string.charAt("abcdef", 6))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.charAt('abcdef', 6): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.charAt("abcdef", 6)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.charAt("abcdef", 6)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("abcdef")),
					ScriptVariable(static_cast<int64_t>(6ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.charAt
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(string("string.charAt") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.charAt")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
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
	// statement: 221
	// console.log(add("string.padLeft('1011', '0', 8): ", string.padLeft("1011", "0", 8)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[221];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.padLeft('1011', '0', 8): ", string.padLeft("1011", "0", 8))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.padLeft('1011', '0', 8): ", string.padLeft("1011", "0", 8))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.padLeft('1011', '0', 8): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.padLeft("1011", "0", 8)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.padLeft("1011", "0", 8)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("1011")),
					ScriptVariable(string("0")),
					ScriptVariable(static_cast<int64_t>(8ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.padLeft
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(string("string.padLeft") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.padLeft")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::padLeft(stringValue, by, toSize));
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
	// statement: 222
	// console.log(add("string.padRight('1011', '0', 8): ", string.padRight("1011", "0", 8)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[222];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("string.padRight('1011', '0', 8): ", string.padRight("1011", "0", 8))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("string.padRight('1011', '0', 8): ", string.padRight("1011", "0", 8))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("string.padRight('1011', '0', 8): ")),
				ScriptVariable() // argumentValues[1] --> returnValue of string.padRight("1011", "0", 8)
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: string.padRight("1011", "0", 8)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("1011")),
					ScriptVariable(string("0")),
					ScriptVariable(static_cast<int64_t>(8ll))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// method code: string.padRight
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(string("string.padRight") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string.padRight")));
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(StringTools::padRight(stringValue, by, toSize));
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
	// statement: 223
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[223];
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
	// statement: 224
	// console.log("Check string operator (Operators)")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[224];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Check string operator (Operators)"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 225
	// console.log("'abc' + 'def' + 'ghi': ", add("abc", add("def", "ghi")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[225];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("'abc' + 'def' + 'ghi': ")),
			ScriptVariable() // argumentValues[1] --> returnValue of add("abc", add("def", "ghi"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: add("abc", add("def", "ghi"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable() // argumentValues[1] --> returnValue of add("def", "ghi")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: add("def", "ghi")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("def")),
					ScriptVariable(string("ghi"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
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
	// statement: 226
	// console.log("abc == abc: ", equals("abc", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[226];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc == abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of equals("abc", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: equals("abc", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 227
	// console.log("abc == def: ", equals("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[227];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc == def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of equals("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: equals("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 228
	// console.log("abc != abc: ", notEqual("abc", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[228];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc != abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of notEqual("abc", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: notEqual("abc", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: notEqual
			if (argumentValues.size() != 2) {
				Console::println(string("notEqual") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("notEqual")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueAsString() == argumentValues[i].getValueAsString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 229
	// console.log("abc != def: ", notEqual("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[229];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc != def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of notEqual("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: notEqual("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: notEqual
			if (argumentValues.size() != 2) {
				Console::println(string("notEqual") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("notEqual")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueAsString() == argumentValues[i].getValueAsString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 230
	// console.log("abc < def: ", lesser("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[230];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc < def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesser("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesser("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 231
	// console.log("def < abc: ", lesser("def", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[231];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("def < abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesser("def", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesser("def", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("def")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 232
	// console.log("abc <= abc: ", lesserEquals("abc", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[232];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc <= abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesserEquals("abc", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesserEquals("abc", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: lesserEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA <= stringValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA <= floatValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 233
	// console.log("abc <= def: ", lesserEquals("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[233];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc <= def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesserEquals("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesserEquals("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: lesserEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA <= stringValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA <= floatValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 234
	// console.log("def <= abc: ", lesserEquals("def", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[234];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("def <= abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of lesserEquals("def", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: lesserEquals("def", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("def")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: lesserEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA <= stringValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA <= floatValueB);
				} else {
					Console::println(string("lesserEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("lesserEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 235
	// console.log("abc > def: ", greater("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[235];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc > def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greater("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greater("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greater
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA > stringValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA > floatValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 236
	// console.log("def > abc: ", greater("def", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[236];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("def > abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greater("def", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greater("def", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("def")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greater
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA > stringValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA > floatValueB);
				} else {
					Console::println(string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greater")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 237
	// console.log("abc >= abc: ", greaterEquals("abc", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[237];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc >= abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greaterEquals("abc", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greaterEquals("abc", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greaterEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA >= stringValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA >= floatValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 238
	// console.log("abc >= def: ", greaterEquals("abc", "def"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[238];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("abc >= def: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greaterEquals("abc", "def")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greaterEquals("abc", "def")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("abc")),
				ScriptVariable(string("def"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greaterEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA >= stringValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA >= floatValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 239
	// console.log("def >= abc: ", greaterEquals("def", "abc"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[239];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("def >= abc: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of greaterEquals("def", "abc")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: greaterEquals("def", "abc")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("def")),
				ScriptVariable(string("abc"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// method code: greaterEquals
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string stringValueA;
				string stringValueB;
				if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
					MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
					returnValue.setValue(stringValueA >= stringValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			} else {
				float floatValueA;
				float floatValueB;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
					returnValue.setValue(floatValueA >= floatValueB);
				} else {
					Console::println(string("greaterEquals") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("greaterEquals")));
					miniScript->startErrorScript(); return;
				}
			}
		}
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 240
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[240];
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
	// statement: 241
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[241];
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
	// statement: 242
	// console.log("Variable")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[242];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Variable"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 243
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[243];
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
	// statement: 244
	// setVariable("$variable", string("1234"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[244];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$variable")),
			ScriptVariable() // argumentValues[1] --> returnValue of string("1234")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: string("1234")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("1234"))
			};
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// method code: string
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(stringValue);
			} else {
				Console::println(string("string") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("string")));
				miniScript->startErrorScript(); return;
			}
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
	// statement: 245
	// console.log(getVariable("$variable"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[245];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of getVariable("$variable")
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: getVariable("$variable")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$variable"))
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 246
	// console.log("--------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[246];
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
	// statement: 247
	// console.log("Lets check forTime")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[247];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Lets check forTime"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 248
	// console.log("--------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[248];
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
	// statement: 249
	// setVariable("$i", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[249];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(1ll))
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
	// statement: 250
	miniscript_statement_250:
	// forTime(2000)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[250];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(2000ll))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: forTime
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
			Console::println(string("forTime") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("forTime")));
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			auto timeWaitStarted = now;
			auto forTimeStartedIt = miniScript->getScriptState().forTimeStarted.find(statement.line);
			if (forTimeStartedIt == miniScript->getScriptState().forTimeStarted.end()) {
				miniScript->getScriptState().forTimeStarted[statement.line] = timeWaitStarted;
			} else {
				timeWaitStarted = forTimeStartedIt->second;
			}
			//
			if (Time::getCurrentMillis() > timeWaitStarted + time) {
				miniScript->getScriptState().forTimeStarted.erase(statement.line);
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_255;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 251
	miniscript_statement_251:
	// console.log(getVariable("$i"), ": Hello World")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[251];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
			ScriptVariable(string(": Hello World"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 252
	// script.wait(500)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[252];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(500ll))
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
	// statement: 253
	miniscript_statement_253:
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[253];
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
	// statement: 254
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[254];
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
				goto miniscript_statement_250;
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
	// statement: 255
	miniscript_statement_255:
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[255];
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
	// statement: 256
	// console.log("Lets check forCondition")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[256];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Lets check forCondition"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 257
	// console.log("-------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[257];
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
	// statement: 258
	// setVariable("$i", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[258];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(1ll))
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
	// statement: 259
	miniscript_statement_259:
	// forCondition(notEqual(getVariable("$i"), 6))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[259];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of notEqual(getVariable("$i"), 6)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: notEqual(getVariable("$i"), 6)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(6ll))
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
			// method code: notEqual
			if (argumentValues.size() != 2) {
				Console::println(string("notEqual") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("notEqual")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueAsString() == argumentValues[i].getValueAsString()) {
						returnValue.setValue(false);
						break;
					}
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
				goto miniscript_statement_264;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 260
	miniscript_statement_260:
	// console.log(getVariable("$i"), ": Hello World")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[260];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
			ScriptVariable(string(": Hello World"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 261
	// script.wait(500)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[261];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(static_cast<int64_t>(500ll))
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
	// statement: 262
	miniscript_statement_262:
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[262];
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
	// statement: 263
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[263];
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
				goto miniscript_statement_259;
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
	// statement: 264
	miniscript_statement_264:
	// console.log("i -> ", getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[264];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("i -> ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$i")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$i"))
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 265
	// console.log("---------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[265];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 266
	// console.log("Lets check forCondition with if/elseif/else")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[266];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("Lets check forCondition with if/elseif/else"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 267
	// console.log("---------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[267];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("---------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 268
	// setVariable("$i", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[268];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(1ll))
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
	// statement: 269
	miniscript_statement_269:
	// forCondition(lesser(getVariable("$i"), 5))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[269];
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
				goto miniscript_statement_284;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 270
	miniscript_statement_270:
	// console.log(getVariable("$i"), ":")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[270];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
			ScriptVariable(string(":"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 271
	// if(equals(getVariable("$i"), 0))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[271];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$i"), 0)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$i"), 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(0ll))
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
				goto miniscript_statement_273;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 272
	miniscript_statement_272:
	// console.log("i -> 0")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[272];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("i -> 0"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 273
	miniscript_statement_273:
	// elseif(equals(getVariable("$i"), 1))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[273];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$i"), 1)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$i"), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(1ll))
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println(string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("elseif")));
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->getScriptState().conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->getScriptState().conditionStack.pop();
				miniScript->getScriptState().conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_275;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 274
	miniscript_statement_274:
	// console.log("i -> 1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[274];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("i -> 1"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 275
	miniscript_statement_275:
	// elseif(equals(getVariable("$i"), 2))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[275];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$i"), 2)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$i"), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(2ll))
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println(string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("elseif")));
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->getScriptState().conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->getScriptState().conditionStack.pop();
				miniScript->getScriptState().conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_277;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 276
	miniscript_statement_276:
	// console.log("i -> 2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[276];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("i -> 2"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 277
	miniscript_statement_277:
	// elseif(equals(getVariable("$i"), 3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[277];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of equals(getVariable("$i"), 3)
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: equals(getVariable("$i"), 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable(static_cast<int64_t>(3ll))
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println(string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("elseif")));
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->getScriptState().conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->getScriptState().conditionStack.pop();
				miniScript->getScriptState().conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_279;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 278
	miniscript_statement_278:
	// console.log("i -> 3")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[278];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("i -> 3"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 279
	miniscript_statement_279:
	// else()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[279];
		getScriptState().statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues {
		};
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: else
		if (miniScript->getScriptState().conditionStack.empty() == true) {
			Console::println("ScriptMethodElse::executeMethod(): else without if");
			miniScript->startErrorScript(); return;
		} else {
			auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
			if (conditionStackElement == true) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_281;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 280
	miniscript_statement_280:
	// console.log("else: ", getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[280];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("else: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$i")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$i"))
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 281
	miniscript_statement_281:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[281];
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
	// statement: 282
	miniscript_statement_282:
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[282];
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
	// statement: 283
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[283];
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
				goto miniscript_statement_269;
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
	// statement: 284
	miniscript_statement_284:
	// setVariable("$i", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[284];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$i")),
			ScriptVariable(static_cast<int64_t>(1ll))
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
	// statement: 285
	// setVariable("$j", 2)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[285];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$j")),
			ScriptVariable(static_cast<int64_t>(2ll))
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
	// statement: 286
	// setVariable("$k", 3)
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[286];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$k")),
			ScriptVariable(static_cast<int64_t>(3ll))
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
	// statement: 287
	// if(or(equals(getVariable("$i"), getVariable("$j")), equals(getVariable("$i"), getVariable("$k"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[287];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of or(equals(getVariable("$i"), getVariable("$j")), equals(getVariable("$i"), getVariable("$k")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: or(equals(getVariable("$i"), getVariable("$j")), equals(getVariable("$i"), getVariable("$k")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of equals(getVariable("$i"), getVariable("$j"))
				ScriptVariable() // argumentValues[1] --> returnValue of equals(getVariable("$i"), getVariable("$k"))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: equals(getVariable("$i"), getVariable("$j"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$j")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$i"))
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
				// depth = 3 / argument index = 1: getVariable("$j")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$j"))
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
			// depth = 2 / argument index = 1: equals(getVariable("$i"), getVariable("$k"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$k")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$i"))
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
				// depth = 3 / argument index = 1: getVariable("$k")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$k"))
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
			// method code: or
			if (argumentValues.size() != 2) {
				returnValue.setValue(false);
				Console::println(string("or") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("or")));
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(false);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println(string("or") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("or")));
						miniScript->startErrorScript(); return;
					} else
					if (booleanValue == true) {
						returnValue.setValue(true);
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
				goto miniscript_statement_289;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 288
	miniscript_statement_288:
	// console.log("This should not happen, but look ok in preprocessor processed output")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[288];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("This should not happen, but look ok in preprocessor processed output"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 289
	miniscript_statement_289:
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[289];
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
	// statement: 290
	miniscript_statement_290:
	// console.log("-------------------------------------------------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[290];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-------------------------------------------------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 291
	// console.log(add("Test: string concatenation with brackets in string literals: ", add(getVariable("$i"), add("(", add(getVariable("$j"), ")")))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[291];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("Test: string concatenation with brackets in string literals: ", add(getVariable("$i"), add("(", add(getVariable("$j"), ")"))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("Test: string concatenation with brackets in string literals: ", add(getVariable("$i"), add("(", add(getVariable("$j"), ")"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("Test: string concatenation with brackets in string literals: ")),
				ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$i"), add("(", add(getVariable("$j"), ")")))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: add(getVariable("$i"), add("(", add(getVariable("$j"), ")")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
					ScriptVariable() // argumentValues[1] --> returnValue of add("(", add(getVariable("$j"), ")"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$i"))
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
				// depth = 3 / argument index = 1: add("(", add(getVariable("$j"), ")"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(string("(")),
						ScriptVariable() // argumentValues[1] --> returnValue of add(getVariable("$j"), ")")
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: add(getVariable("$j"), ")")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues {
							ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$j")
							ScriptVariable(string(")"))
						};
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// depth = 5 / argument index = 0: getVariable("$j")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues {
								ScriptVariable(string("$j"))
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
	// statement: 292
	// console.log("-------------------------------------------------------------------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[292];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("-------------------------------------------------------------------------------------"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 293
	// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.000000, 2.000000), 2.000000), mul(div(20.000000, 10.000000), add(2.000000, 5))), " = 17")
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[293];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues {
			ScriptVariable(string("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ")),
			ScriptVariable(), // argumentValues[1] --> returnValue of add(div(add(4.000000, 2.000000), 2.000000), mul(div(20.000000, 10.000000), add(2.000000, 5)))
			ScriptVariable(string(" = 17"))
		};
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: add(div(add(4.000000, 2.000000), 2.000000), mul(div(20.000000, 10.000000), add(2.000000, 5)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of div(add(4.000000, 2.000000), 2.000000)
				ScriptVariable() // argumentValues[1] --> returnValue of mul(div(20.000000, 10.000000), add(2.000000, 5))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 0: div(add(4.000000, 2.000000), 2.000000)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of add(4.000000, 2.000000)
					ScriptVariable(2.000000f)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// depth = 3 / argument index = 0: add(4.000000, 2.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(4.000000f),
						ScriptVariable(2.000000f)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: div
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			// depth = 2 / argument index = 1: mul(div(20.000000, 10.000000), add(2.000000, 5))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of div(20.000000, 10.000000)
					ScriptVariable() // argumentValues[1] --> returnValue of add(2.000000, 5)
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: div(20.000000, 10.000000)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(20.000000f),
						ScriptVariable(10.000000f)
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// method code: div
					MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
				}
				// depth = 3 / argument index = 1: add(2.000000, 5)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues {
						ScriptVariable(2.000000f),
						ScriptVariable(static_cast<int64_t>(5ll))
					};
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: mul
				MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
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
	// statement: 294
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[294];
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
	// statement: 295
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[295];
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

void MiniScriptBaseTest::on_error(int miniScriptGotoStatementIdx) {
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
	// console.log("base-test: Error")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("base-test: Error"))
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


/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
