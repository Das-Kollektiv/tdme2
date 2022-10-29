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
	setNativeHash("8901584602e47754fe3b3b9744e0767937ab71303439baa29fe4813f622d4e3f");
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
						.statement = "console.log(\"base-test: Initialize\")",
						.executableStatement = "console.log(\"base-test: Initialize\")",
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
						.statement = "console.log(\"base-test: Nothing\")",
						.executableStatement = "console.log(\"base-test: Nothing\")",
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
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "console.log(\"Check bool operations\")",
						.executableStatement = "console.log(\"Check bool operations\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 17,
						.statementIdx = 6,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 18,
						.statementIdx = 7,
						.statement = "console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						.executableStatement = "console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						.gotoStatementIdx = -1
					},
					{
						.line = 19,
						.statementIdx = 8,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 20,
						.statementIdx = 9,
						.statement = "console.log(\"Check int computation\")",
						.executableStatement = "console.log(\"Check int computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 10,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 22,
						.statementIdx = 11,
						.statement = "console.log(\"1 + 2 + 3 - 1: \", 1 + 2 + 3 - 1)",
						.executableStatement = "console.log(\"1 + 2 + 3 - 1: \",sub(add(1,add(2, 3)), 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 23,
						.statementIdx = 12,
						.statement = "console.log(\"20 / 2: \", 20 / 2)",
						.executableStatement = "console.log(\"20 / 2: \",div(20, 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 24,
						.statementIdx = 13,
						.statement = "console.log(\"11 * 10: \", 11 * 10)",
						.executableStatement = "console.log(\"11 * 10: \",mul(11, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 25,
						.statementIdx = 14,
						.statement = "console.log(\"2 > 1: \", 2 > 1)",
						.executableStatement = "console.log(\"2 > 1: \",greater(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 15,
						.statement = "console.log(\"2 < 1: \", 2 < 1)",
						.executableStatement = "console.log(\"2 < 1: \",lesser(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 16,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 17,
						.statement = "console.log(\"Check float computation\")",
						.executableStatement = "console.log(\"Check float computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 29,
						.statementIdx = 18,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 30,
						.statementIdx = 19,
						.statement = "console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \", (1.1 + 2.2 + 3.3) - 1.2)",
						.executableStatement = "console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \",sub(add(1.1,add(2.2, 3.3)), 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 20,
						.statement = "console.log(\"20 / 1.5: \", 20 / 1.5)",
						.executableStatement = "console.log(\"20 / 1.5: \",div(20, 1.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 21,
						.statement = "console.log(\"11.5 * 10.5: \", 11.5 * 10.5)",
						.executableStatement = "console.log(\"11.5 * 10.5: \",mul(11.5, 10.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 22,
						.statement = "console.log(\"2.2 > 1.3: \", 2.2 > 1.3)",
						.executableStatement = "console.log(\"2.2 > 1.3: \",greater(2.2, 1.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 23,
						.statement = "console.log(\"2.5 < 1.2: \", 2.5 < 1.2)",
						.executableStatement = "console.log(\"2.5 < 1.2: \",lesser(2.5, 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 35,
						.statementIdx = 24,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 36,
						.statementIdx = 25,
						.statement = "console.log(\"Check vector2 math\")",
						.executableStatement = "console.log(\"Check vector2 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 37,
						.statementIdx = 26,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 38,
						.statementIdx = 27,
						.statement = "console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						.executableStatement = "console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 28,
						.statement = "console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						.executableStatement = "console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 29,
						.statement = "console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						.executableStatement = "console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 41,
						.statementIdx = 30,
						.statement = "console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 31,
						.statement = "console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 32,
						.statement = "console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 33,
						.statement = "console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \", vec2(1.1, 2.2) - vec2(1.2, 1.0))",
						.executableStatement = "console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \",sub(vec2(1.1, 2.2), vec2(1.2, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 34,
						.statement = "console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \", vec2(20, 10) / vec2(1.5, 2.5))",
						.executableStatement = "console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \",div(vec2(20, 10), vec2(1.5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 35,
						.statement = "console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \", vec2(20, 10) * vec2(1.5, 2.5))",
						.executableStatement = "console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \",mul(vec2(20, 10), vec2(1.5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 47,
						.statementIdx = 36,
						.statement = "console.log(\"vec2(20, 10) / 2): \", vec2(20, 10) / 2)",
						.executableStatement = "console.log(\"vec2(20, 10) / 2): \",div(vec2(20, 10), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 37,
						.statement = "console.log(\"vec2(20, 10) * 2): \", vec2(20, 10) * 2)",
						.executableStatement = "console.log(\"vec2(20, 10) * 2): \",mul(vec2(20, 10), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 38,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 50,
						.statementIdx = 39,
						.statement = "console.log(\"Check vector3 math\")",
						.executableStatement = "console.log(\"Check vector3 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 40,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 41,
						.statement = "console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						.executableStatement = "console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 42,
						.statement = "console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						.executableStatement = "console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 43,
						.statement = "console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						.executableStatement = "console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 44,
						.statement = "console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						.executableStatement = "console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 45,
						.statement = "console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 57,
						.statementIdx = 46,
						.statement = "console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						.executableStatement = "console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 47,
						.statement = "console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 48,
						.statement = "console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 60,
						.statementIdx = 49,
						.statement = "console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 50,
						.statement = "console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \", vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0))",
						.executableStatement = "console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \",sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 51,
						.statement = "console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \", vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5))",
						.executableStatement = "console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \",div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 52,
						.statement = "console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \", vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5))",
						.executableStatement = "console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \",mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 64,
						.statementIdx = 53,
						.statement = "console.log(\"vec3(20, 10, 5) / 2): \", vec3(20, 10, 5) / 2)",
						.executableStatement = "console.log(\"vec3(20, 10, 5) / 2): \",div(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 65,
						.statementIdx = 54,
						.statement = "console.log(\"vec3(20, 10, 5) * 2): \", vec3(20, 10, 5) * 2)",
						.executableStatement = "console.log(\"vec3(20, 10, 5) * 2): \",mul(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 66,
						.statementIdx = 55,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 67,
						.statementIdx = 56,
						.statement = "console.log(\"Check vector4 math\")",
						.executableStatement = "console.log(\"Check vector4 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 57,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 58,
						.statement = "console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						.executableStatement = "console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 70,
						.statementIdx = 59,
						.statement = "console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						.executableStatement = "console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 60,
						.statement = "console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						.executableStatement = "console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 61,
						.statement = "console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 62,
						.statement = "console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 74,
						.statementIdx = 63,
						.statement = "console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 75,
						.statementIdx = 64,
						.statement = "console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 76,
						.statementIdx = 65,
						.statement = "console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 66,
						.statement = "console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \", vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0))",
						.executableStatement = "console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \",sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 78,
						.statementIdx = 67,
						.statement = "console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \", vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1))",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \",div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 79,
						.statementIdx = 68,
						.statement = "console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \", vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1))",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \",mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 80,
						.statementIdx = 69,
						.statement = "console.log(\"vec4(20, 10, 5, 1) / 2): \", vec4(20, 10, 5, 1) / 2)",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) / 2): \",div(vec4(20, 10, 5, 1), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 81,
						.statementIdx = 70,
						.statement = "console.log(\"vec4(20, 10, 5, 1) * 2): \", vec4(20, 10, 5, 1) * 2)",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) * 2): \",mul(vec4(20, 10, 5, 1), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 82,
						.statementIdx = 71,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 83,
						.statementIdx = 72,
						.statement = "console.log(\"Check quaternion math\")",
						.executableStatement = "console.log(\"Check quaternion math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 84,
						.statementIdx = 73,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 85,
						.statementIdx = 74,
						.statement = "console.log(\"quaternion.identity(): \", quaternion.identity())",
						.executableStatement = "console.log(\"quaternion.identity(): \", quaternion.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 86,
						.statementIdx = 75,
						.statement = "console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.executableStatement = "console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 87,
						.statementIdx = 76,
						.statement = "console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 88,
						.statementIdx = 77,
						.statement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 89,
						.statementIdx = 78,
						.statement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.executableStatement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 90,
						.statementIdx = 79,
						.statement = "console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 91,
						.statementIdx = 80,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 92,
						.statementIdx = 81,
						.statement = "console.log(\"Check matrix4x4 math\")",
						.executableStatement = "console.log(\"Check matrix4x4 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 93,
						.statementIdx = 82,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 94,
						.statementIdx = 83,
						.statement = "console.log(\"mat4.identity(): \", mat4.identity())",
						.executableStatement = "console.log(\"mat4.identity(): \", mat4.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 95,
						.statementIdx = 84,
						.statement = "console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						.executableStatement = "console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 96,
						.statementIdx = 85,
						.statement = "console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.executableStatement = "console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 97,
						.statementIdx = 86,
						.statement = "console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						.executableStatement = "console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 98,
						.statementIdx = 87,
						.statement = "console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						.executableStatement = "console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 99,
						.statementIdx = 88,
						.statement = "console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						.executableStatement = "console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 100,
						.statementIdx = 89,
						.statement = "console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 101,
						.statementIdx = 90,
						.statement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 102,
						.statementIdx = 91,
						.statement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 103,
						.statementIdx = 92,
						.statement = "console.log(\"mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): \", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): \", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 104,
						.statementIdx = 93,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 105,
						.statementIdx = 94,
						.statement = "console.log(\"Check matrix3x3 math\")",
						.executableStatement = "console.log(\"Check matrix3x3 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 106,
						.statementIdx = 95,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 107,
						.statementIdx = 96,
						.statement = "console.log(\"mat3.identity(): \", mat3.identity())",
						.executableStatement = "console.log(\"mat3.identity(): \", mat3.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 108,
						.statementIdx = 97,
						.statement = "console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 109,
						.statementIdx = 98,
						.statement = "console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						.executableStatement = "console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 110,
						.statementIdx = 99,
						.statement = "console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						.executableStatement = "console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 111,
						.statementIdx = 100,
						.statement = "console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						.executableStatement = "console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 112,
						.statementIdx = 101,
						.statement = "console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 113,
						.statementIdx = 102,
						.statement = "console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						.executableStatement = "console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 114,
						.statementIdx = 103,
						.statement = "console.log(\"mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): \", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))",
						.executableStatement = "console.log(\"mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): \", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 115,
						.statementIdx = 104,
						.statement = "console.log(\"mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): \", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): \", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 116,
						.statementIdx = 105,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 117,
						.statementIdx = 106,
						.statement = "console.log(\"Check additional math\")",
						.executableStatement = "console.log(\"Check additional math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 118,
						.statementIdx = 107,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 119,
						.statementIdx = 108,
						.statement = "console.log(\"math.PI(): \", math.PI())",
						.executableStatement = "console.log(\"math.PI(): \", math.PI())",
						.gotoStatementIdx = -1
					},
					{
						.line = 120,
						.statementIdx = 109,
						.statement = "console.log(\"math.EPSILON(): \", math.EPSILON())",
						.executableStatement = "console.log(\"math.EPSILON(): \", math.EPSILON())",
						.gotoStatementIdx = -1
					},
					{
						.line = 121,
						.statementIdx = 110,
						.statement = "console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						.executableStatement = "console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						.gotoStatementIdx = -1
					},
					{
						.line = 122,
						.statementIdx = 111,
						.statement = "console.log(\"math.G(): \", math.G())",
						.executableStatement = "console.log(\"math.G(): \", math.G())",
						.gotoStatementIdx = -1
					},
					{
						.line = 123,
						.statementIdx = 112,
						.statement = "console.log(\"math.acos(0.0): \", math.acos(0.0))",
						.executableStatement = "console.log(\"math.acos(0.0): \", math.acos(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 124,
						.statementIdx = 113,
						.statement = "console.log(\"math.asin(1.0): \", math.asin(1.0))",
						.executableStatement = "console.log(\"math.asin(1.0): \", math.asin(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 125,
						.statementIdx = 114,
						.statement = "console.log(\"math.atan(1.0): \", math.atan(1.0))",
						.executableStatement = "console.log(\"math.atan(1.0): \", math.atan(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 126,
						.statementIdx = 115,
						.statement = "console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						.executableStatement = "console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 127,
						.statementIdx = 116,
						.statement = "console.log(\"math.floor(2.87): \", math.floor(2.87))",
						.executableStatement = "console.log(\"math.floor(2.87): \", math.floor(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 128,
						.statementIdx = 117,
						.statement = "console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						.executableStatement = "console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 129,
						.statementIdx = 118,
						.statement = "console.log(\"math.round(2.37): \", math.round(2.37))",
						.executableStatement = "console.log(\"math.round(2.37): \", math.round(2.37))",
						.gotoStatementIdx = -1
					},
					{
						.line = 130,
						.statementIdx = 119,
						.statement = "console.log(\"math.round(2.87): \", math.round(2.87))",
						.executableStatement = "console.log(\"math.round(2.87): \", math.round(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 131,
						.statementIdx = 120,
						.statement = "console.log(\"math.cos(0.0): \", math.cos(0.0))",
						.executableStatement = "console.log(\"math.cos(0.0): \", math.cos(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 132,
						.statementIdx = 121,
						.statement = "console.log(\"math.sin(0.0): \", math.sin(0.0))",
						.executableStatement = "console.log(\"math.sin(0.0): \", math.sin(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 133,
						.statementIdx = 122,
						.statement = "console.log(\"math.tan(1.0): \", math.tan(1.0))",
						.executableStatement = "console.log(\"math.tan(1.0): \", math.tan(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 134,
						.statementIdx = 123,
						.statement = "console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						.executableStatement = "console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 135,
						.statementIdx = 124,
						.statement = "console.log(\"math.random(): \", math.random())",
						.executableStatement = "console.log(\"math.random(): \", math.random())",
						.gotoStatementIdx = -1
					},
					{
						.line = 136,
						.statementIdx = 125,
						.statement = "console.log(\"math.random(): \", math.random())",
						.executableStatement = "console.log(\"math.random(): \", math.random())",
						.gotoStatementIdx = -1
					},
					{
						.line = 137,
						.statementIdx = 126,
						.statement = "console.log(\"math.random(): \", math.random())",
						.executableStatement = "console.log(\"math.random(): \", math.random())",
						.gotoStatementIdx = -1
					},
					{
						.line = 138,
						.statementIdx = 127,
						.statement = "console.log(\"math.exp(1.0): \", math.exp(1.0))",
						.executableStatement = "console.log(\"math.exp(1.0): \", math.exp(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 139,
						.statementIdx = 128,
						.statement = "console.log(\"math.log(2.0): \", math.log(2.0))",
						.executableStatement = "console.log(\"math.log(2.0): \", math.log(2.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 140,
						.statementIdx = 129,
						.statement = "console.log(\"math.sign(-2): \", math.sign(-2))",
						.executableStatement = "console.log(\"math.sign(-2): \", math.sign(-2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 141,
						.statementIdx = 130,
						.statement = "console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						.executableStatement = "console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 142,
						.statementIdx = 131,
						.statement = "console.log(\"math.square(3): \", math.square(3))",
						.executableStatement = "console.log(\"math.square(3): \", math.square(3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 143,
						.statementIdx = 132,
						.statement = "console.log(\"math.square(3.0): \", math.square(3.0))",
						.executableStatement = "console.log(\"math.square(3.0): \", math.square(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 144,
						.statementIdx = 133,
						.statement = "console.log(\"math.min(4, 9): \", math.min(4, 9))",
						.executableStatement = "console.log(\"math.min(4, 9): \", math.min(4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 145,
						.statementIdx = 134,
						.statement = "console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						.executableStatement = "console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 146,
						.statementIdx = 135,
						.statement = "console.log(\"math.max(4, 9): \", math.max(4, 9))",
						.executableStatement = "console.log(\"math.max(4, 9): \", math.max(4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 147,
						.statementIdx = 136,
						.statement = "console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						.executableStatement = "console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 148,
						.statementIdx = 137,
						.statement = "console.log(\"math.abs(-9): \", math.abs(-9))",
						.executableStatement = "console.log(\"math.abs(-9): \", math.abs(-9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 149,
						.statementIdx = 138,
						.statement = "console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						.executableStatement = "console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 150,
						.statementIdx = 139,
						.statement = "console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						.executableStatement = "console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 151,
						.statementIdx = 140,
						.statement = "console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						.executableStatement = "console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 152,
						.statementIdx = 141,
						.statement = "console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						.executableStatement = "console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						.gotoStatementIdx = -1
					},
					{
						.line = 153,
						.statementIdx = 142,
						.statement = "console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						.executableStatement = "console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 154,
						.statementIdx = 143,
						.statement = "console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						.executableStatement = "console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 155,
						.statementIdx = 144,
						.statement = "console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						.executableStatement = "console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 156,
						.statementIdx = 145,
						.statement = "console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						.executableStatement = "console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 157,
						.statementIdx = 146,
						.statement = "console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						.executableStatement = "console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 158,
						.statementIdx = 147,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 159,
						.statementIdx = 148,
						.statement = "console.log(\"Check transform\")",
						.executableStatement = "console.log(\"Check transform\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 160,
						.statementIdx = 149,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 161,
						.statementIdx = 150,
						.statement = "console.log(\"$transform = transform(vec3(1,2,3), vec3(2, 3, 4)\")",
						.executableStatement = "console.log(\"$transform = transform(vec3(1,2,3), vec3(2, 3, 4)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 162,
						.statementIdx = 151,
						.statement = "$transform = transform(vec3(1,2,3), vec3(2, 3, 4))",
						.executableStatement = "setVariable(\"$transform\", transform(vec3(1,2,3), vec3(2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 163,
						.statementIdx = 152,
						.statement = "console.log(\"$transform: \", $transform)",
						.executableStatement = "console.log(\"$transform: \", $transform)",
						.gotoStatementIdx = -1
					},
					{
						.line = 164,
						.statementIdx = 153,
						.statement = "console.log(\"transform.setRotationAngle($transform, 1, 90)\")",
						.executableStatement = "console.log(\"transform.setRotationAngle($transform, 1, 90)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 165,
						.statementIdx = 154,
						.statement = "transform.setRotationAngle($transform, 1, 90)",
						.executableStatement = "transform.setRotationAngle($transform, 1, 90)",
						.gotoStatementIdx = -1
					},
					{
						.line = 166,
						.statementIdx = 155,
						.statement = "console.log(\"transform.getRotationAngle($transform, 1): \", transform.getRotationAngle($transform, 1))",
						.executableStatement = "console.log(\"transform.getRotationAngle($transform, 1): \", transform.getRotationAngle($transform, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 167,
						.statementIdx = 156,
						.statement = "console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						.executableStatement = "console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 168,
						.statementIdx = 157,
						.statement = "console.log(\"transform.setTranslation($transform, vec3(-1,-2,-3))\")",
						.executableStatement = "console.log(\"transform.setTranslation($transform, vec3(-1,-2,-3))\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 169,
						.statementIdx = 158,
						.statement = "transform.setTranslation($transform, vec3(-1,-2,-3))",
						.executableStatement = "transform.setTranslation($transform, vec3(-1,-2,-3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 170,
						.statementIdx = 159,
						.statement = "console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						.executableStatement = "console.log(\"transform.getTranslation($transform): \", transform.getTranslation($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 171,
						.statementIdx = 160,
						.statement = "console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						.executableStatement = "console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 172,
						.statementIdx = 161,
						.statement = "console.log(\"transform.setScale($transform, vec3(-2,-3,-4))\")",
						.executableStatement = "console.log(\"transform.setScale($transform, vec3(-2,-3,-4))\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 173,
						.statementIdx = 162,
						.statement = "transform.setScale($transform, vec3(-2,-3,-4))",
						.executableStatement = "transform.setScale($transform, vec3(-2,-3,-4))",
						.gotoStatementIdx = -1
					},
					{
						.line = 174,
						.statementIdx = 163,
						.statement = "console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						.executableStatement = "console.log(\"transform.getScale($transform): \", transform.getScale($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 175,
						.statementIdx = 164,
						.statement = "console.log(\"transform.getRotationAxis($transform, 0): \", transform.getRotationAxis($transform, 0))",
						.executableStatement = "console.log(\"transform.getRotationAxis($transform, 0): \", transform.getRotationAxis($transform, 0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 176,
						.statementIdx = 165,
						.statement = "console.log(\"transform.multiply($transform, vec3(0,0,0)): \", transform.multiply($transform, vec3(0,0,0)))",
						.executableStatement = "console.log(\"transform.multiply($transform, vec3(0,0,0)): \", transform.multiply($transform, vec3(0,0,0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 177,
						.statementIdx = 166,
						.statement = "console.log(\"transform.rotate($transform, vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						.executableStatement = "console.log(\"transform.rotate($transform, vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 178,
						.statementIdx = 167,
						.statement = "console.log(\"transform.getTransformMatrix($transform): \", transform.getTransformMatrix($transform))",
						.executableStatement = "console.log(\"transform.getTransformMatrix($transform): \", transform.getTransformMatrix($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 179,
						.statementIdx = 168,
						.statement = "console.log(\"transform.getRotationsQuaternion($transform): \", transform.getRotationsQuaternion($transform))",
						.executableStatement = "console.log(\"transform.getRotationsQuaternion($transform): \", transform.getRotationsQuaternion($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 180,
						.statementIdx = 169,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 181,
						.statementIdx = 170,
						.statement = "console.log(\"Check string functions\")",
						.executableStatement = "console.log(\"Check string functions\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 182,
						.statementIdx = 171,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 183,
						.statementIdx = 172,
						.statement = "console.log(space(0), \"1\"))",
						.executableStatement = "console.log(space(0), \"1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 184,
						.statementIdx = 173,
						.statement = "console.log(space(2), \"1.1\"))",
						.executableStatement = "console.log(space(2), \"1.1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 185,
						.statementIdx = 174,
						.statement = "console.log(space(2), \"1.2\"))",
						.executableStatement = "console.log(space(2), \"1.2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 186,
						.statementIdx = 175,
						.statement = "console.log(toUpperCase(\"xxxyyyzzz\"))",
						.executableStatement = "console.log(toUpperCase(\"xxxyyyzzz\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 187,
						.statementIdx = 176,
						.statement = "console.log(toLowerCase(\"XXXYYYZZZ\"))",
						.executableStatement = "console.log(toLowerCase(\"XXXYYYZZZ\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 188,
						.statementIdx = 177,
						.statement = "console.log(concatenate(\"abc\", \"def\", \"ghi\"))",
						.executableStatement = "console.log(concatenate(\"abc\", \"def\", \"ghi\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 189,
						.statementIdx = 178,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 190,
						.statementIdx = 179,
						.statement = "console.log(\"Check string functions (Operators)\")",
						.executableStatement = "console.log(\"Check string functions (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 191,
						.statementIdx = 180,
						.statement = "console.log(\"abc\" + \"def\" + \"ghi\")",
						.executableStatement = "console.log(add(\"abc\",add(\"def\", \"ghi\")))",
						.gotoStatementIdx = -1
					},
					{
						.line = 192,
						.statementIdx = 181,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 193,
						.statementIdx = 182,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 194,
						.statementIdx = 183,
						.statement = "console.log(\"Variable\")",
						.executableStatement = "console.log(\"Variable\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 195,
						.statementIdx = 184,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 196,
						.statementIdx = 185,
						.statement = "$variable = string(\"1234\")",
						.executableStatement = "setVariable(\"$variable\", string(\"1234\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 197,
						.statementIdx = 186,
						.statement = "console.log(getVariable(\"$variable\"))",
						.executableStatement = "console.log(getVariable(\"$variable\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 198,
						.statementIdx = 187,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 199,
						.statementIdx = 188,
						.statement = "console.log(\"Lets check forTime\")",
						.executableStatement = "console.log(\"Lets check forTime\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 200,
						.statementIdx = 189,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 201,
						.statementIdx = 190,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 202,
						.statementIdx = 191,
						.statement = "forTime(2000)",
						.executableStatement = "forTime(2000)",
						.gotoStatementIdx = 196
					},
					{
						.line = 203,
						.statementIdx = 192,
						.statement = "console.log($i, \": Hello World\")",
						.executableStatement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 204,
						.statementIdx = 193,
						.statement = "script.wait(500)",
						.executableStatement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 205,
						.statementIdx = 194,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 206,
						.statementIdx = 195,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 191
					},
					{
						.line = 207,
						.statementIdx = 196,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 208,
						.statementIdx = 197,
						.statement = "console.log(\"Lets check forCondition\")",
						.executableStatement = "console.log(\"Lets check forCondition\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 209,
						.statementIdx = 198,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 210,
						.statementIdx = 199,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 211,
						.statementIdx = 200,
						.statement = "forCondition($i != 6)",
						.executableStatement = "forCondition(notequal($i, 6))",
						.gotoStatementIdx = 205
					},
					{
						.line = 212,
						.statementIdx = 201,
						.statement = "console.log($i, \": Hello World\")",
						.executableStatement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 213,
						.statementIdx = 202,
						.statement = "script.wait(500)",
						.executableStatement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 214,
						.statementIdx = 203,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 215,
						.statementIdx = 204,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 200
					},
					{
						.line = 216,
						.statementIdx = 205,
						.statement = "console.log(\"i -> \", $i)",
						.executableStatement = "console.log(\"i -> \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 217,
						.statementIdx = 206,
						.statement = "console.log(\"---------------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 218,
						.statementIdx = 207,
						.statement = "console.log(\"Lets check forCondition with if/elseif/else\")",
						.executableStatement = "console.log(\"Lets check forCondition with if/elseif/else\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 219,
						.statementIdx = 208,
						.statement = "console.log(\"---------------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 220,
						.statementIdx = 209,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 221,
						.statementIdx = 210,
						.statement = "forCondition($i < 5)",
						.executableStatement = "forCondition(lesser($i, 5))",
						.gotoStatementIdx = 225
					},
					{
						.line = 222,
						.statementIdx = 211,
						.statement = "console.log($i, \":\")",
						.executableStatement = "console.log($i, \":\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 223,
						.statementIdx = 212,
						.statement = "if ($i == 0)",
						.executableStatement = "if (equals($i, 0))",
						.gotoStatementIdx = 214
					},
					{
						.line = 224,
						.statementIdx = 213,
						.statement = "console.log(\"i -> 0\")",
						.executableStatement = "console.log(\"i -> 0\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 225,
						.statementIdx = 214,
						.statement = "elseif ($i == 1)",
						.executableStatement = "elseif (equals($i, 1))",
						.gotoStatementIdx = 216
					},
					{
						.line = 226,
						.statementIdx = 215,
						.statement = "console.log(\"i -> 1\")",
						.executableStatement = "console.log(\"i -> 1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 227,
						.statementIdx = 216,
						.statement = "elseif ($i == 2)",
						.executableStatement = "elseif (equals($i, 2))",
						.gotoStatementIdx = 218
					},
					{
						.line = 228,
						.statementIdx = 217,
						.statement = "console.log(\"i -> 2\")",
						.executableStatement = "console.log(\"i -> 2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 229,
						.statementIdx = 218,
						.statement = "elseif ($i == 3)",
						.executableStatement = "elseif (equals($i, 3))",
						.gotoStatementIdx = 220
					},
					{
						.line = 230,
						.statementIdx = 219,
						.statement = "console.log(\"i -> 3\")",
						.executableStatement = "console.log(\"i -> 3\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 231,
						.statementIdx = 220,
						.statement = "else",
						.executableStatement = "else",
						.gotoStatementIdx = 222
					},
					{
						.line = 232,
						.statementIdx = 221,
						.statement = "console.log(\"else: \", $i)",
						.executableStatement = "console.log(\"else: \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 233,
						.statementIdx = 222,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 234,
						.statementIdx = 223,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 235,
						.statementIdx = 224,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 210
					},
					{
						.line = 236,
						.statementIdx = 225,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 237,
						.statementIdx = 226,
						.statement = "$j = 2",
						.executableStatement = "setVariable(\"$j\", 2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 238,
						.statementIdx = 227,
						.statement = "$k = 3",
						.executableStatement = "setVariable(\"$k\", 3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 239,
						.statementIdx = 228,
						.statement = "if (getVariable(\"$i\") == $j || getVariable(\"$i\") == $k)",
						.executableStatement = "if (or(equals(getVariable(\"$i\"), $j),equals(getVariable(\"$i\"), $k)))",
						.gotoStatementIdx = 230
					},
					{
						.line = 240,
						.statementIdx = 229,
						.statement = "console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						.executableStatement = "console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 241,
						.statementIdx = 230,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 242,
						.statementIdx = 231,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.executableStatement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 243,
						.statementIdx = 232,
						.statement = "console.log(\"Test: string concatenation with brackets in string literals: \" + $i + \"(\" + $j + \")\")",
						.executableStatement = "console.log(add(\"Test: string concatenation with brackets in string literals: \",add($i,add(\"(\",add($j, \")\")))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 244,
						.statementIdx = 233,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.executableStatement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 245,
						.statementIdx = 234,
						.statement = "console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \", (4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)), \" = 17\")",
						.executableStatement = "console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \",add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), \" = 17\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 246,
						.statementIdx = 235,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 247,
						.statementIdx = 236,
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
				.line = 250,
				.condition = "error",
				.executableCondition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 251,
						.statementIdx = 0,
						.statement = "console.log(\"------------------\")",
						.executableStatement = "console.log(\"------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 252,
						.statementIdx = 1,
						.statement = "console.log(\"base-test: Error\")",
						.executableStatement = "console.log(\"base-test: Error\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 253,
						.statementIdx = 2,
						.statement = "console.log(\"------------------\")",
						.executableStatement = "console.log(\"------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 254,
						.statementIdx = 3,
						.statement = "console.log(\"An error occurred\")",
						.executableStatement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 255,
						.statementIdx = 4,
						.statement = "script.wait(1000)",
						.executableStatement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 256,
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
		}
	);
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
	for (auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return -1;
}

void MiniScriptBaseTest::emit(const string& condition) {
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
		Console::println("MiniScriptBaseTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptBaseTest::on_initialize(int miniScriptGotoStatementIdx) {
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
	// console.log("base-test: Initialize")
	{
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("base-test: Initialize"));
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

void MiniScriptBaseTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 192) goto miniscript_statement_192; else
	if (miniScriptGotoStatementIdx == 194) goto miniscript_statement_194; else
	if (miniScriptGotoStatementIdx == 196) goto miniscript_statement_196; else
	if (miniScriptGotoStatementIdx == 201) goto miniscript_statement_201; else
	if (miniScriptGotoStatementIdx == 203) goto miniscript_statement_203; else
	if (miniScriptGotoStatementIdx == 205) goto miniscript_statement_205; else
	if (miniScriptGotoStatementIdx == 211) goto miniscript_statement_211; else
	if (miniScriptGotoStatementIdx == 213) goto miniscript_statement_213; else
	if (miniScriptGotoStatementIdx == 215) goto miniscript_statement_215; else
	if (miniScriptGotoStatementIdx == 217) goto miniscript_statement_217; else
	if (miniScriptGotoStatementIdx == 219) goto miniscript_statement_219; else
	if (miniScriptGotoStatementIdx == 221) goto miniscript_statement_221; else
	if (miniScriptGotoStatementIdx == 223) goto miniscript_statement_223; else
	if (miniScriptGotoStatementIdx == 225) goto miniscript_statement_225; else
	if (miniScriptGotoStatementIdx == 229) goto miniscript_statement_229; else
	if (miniScriptGotoStatementIdx == 231) goto miniscript_statement_231; else
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
	// console.log("base-test: Nothing")
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("base-test: Nothing"));
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
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[4];
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

	// Statement: 5
	// console.log("Check bool operations")
	{
		const ScriptStatement& statement = scripts[1].statements[5];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check bool operations"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 6
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[6];
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

	// Statement: 7
	// console.log("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))
	{
		const ScriptStatement& statement = scripts[1].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): "));
		// argumentValues[1] --> returnValue of and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
		// depth = 1 / argument index = 1: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
			argumentValues[1].setValue(true);
			// depth = 2 / argument index = 0: or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of equals(MiniScript will do the job, MiniScript will not do the job)
				// argumentValues[1] --> returnValue of equals(it will, it will)
				// depth = 3 / argument index = 0: equals(MiniScript will do the job, MiniScript will not do the job)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("MiniScript will do the job"));
					argumentValues[1].setValue(string("MiniScript will not do the job"));
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
				// depth = 3 / argument index = 1: equals(it will, it will)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("it will"));
					argumentValues[1].setValue(string("it will"));
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
				// method code: or
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected, @ argument 1: boolean expected");
					miniScript->startErrorScript(); return;
				} else {
					returnValue.setValue(false);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
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
				Console::println("ScriptMethodOr::executeMethod(): " + string("and") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected, @ argument 1: boolean expected");
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodAnd::executeMethod(): " + string("and") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
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
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 8
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[8];
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

	// Statement: 9
	// console.log("Check int computation")
	{
		const ScriptStatement& statement = scripts[1].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check int computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 10
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[10];
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

	// Statement: 11
	// console.log("1 + 2 + 3 - 1: ", sub(add(1,add(2, 3)), 1))
	{
		const ScriptStatement& statement = scripts[1].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("1 + 2 + 3 - 1: "));
		// argumentValues[1] --> returnValue of sub(add(1,add(2, 3)), 1)
		// depth = 1 / argument index = 1: sub(add(1,add(2, 3)), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1,add(2, 3))
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: add(1, add(2, 3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				// argumentValues[1] --> returnValue of add(2, 3)
				// depth = 3 / argument index = 1: add(2, 3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(static_cast<int64_t>(2));
					argumentValues[1].setValue(static_cast<int64_t>(3));
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
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 12
	// console.log("20 / 2: ", div(20, 2))
	{
		const ScriptStatement& statement = scripts[1].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("20 / 2: "));
		// argumentValues[1] --> returnValue of div(20, 2)
		// depth = 1 / argument index = 1: div(20, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 13
	// console.log("11 * 10: ", mul(11, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("11 * 10: "));
		// argumentValues[1] --> returnValue of mul(11, 10)
		// depth = 1 / argument index = 1: mul(11, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(11));
			argumentValues[1].setValue(static_cast<int64_t>(10));
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 14
	// console.log("2 > 1: ", greater(2, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2 > 1: "));
		// argumentValues[1] --> returnValue of greater(2, 1)
		// depth = 1 / argument index = 1: greater(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("2 < 1: ", lesser(2, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2 < 1: "));
		// argumentValues[1] --> returnValue of lesser(2, 1)
		// depth = 1 / argument index = 1: lesser(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 16
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[16];
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

	// Statement: 17
	// console.log("Check float computation")
	{
		const ScriptStatement& statement = scripts[1].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check float computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 18
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[18];
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

	// Statement: 19
	// console.log("(1.1 + 2.2 + 3.3) - 1.2: ", sub(add(1.1,add(2.2, 3.3)), 1.2))
	{
		const ScriptStatement& statement = scripts[1].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("(1.1 + 2.2 + 3.3) - 1.2: "));
		// argumentValues[1] --> returnValue of sub(add(1.1,add(2.2, 3.3)), 1.2)
		// depth = 1 / argument index = 1: sub(add(1.1,add(2.2, 3.3)), 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1.1,add(2.2, 3.3))
			argumentValues[1].setValue(1.200000f);
			// depth = 2 / argument index = 0: add(1.1, add(2.2, 3.3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				// argumentValues[1] --> returnValue of add(2.2, 3.3)
				// depth = 3 / argument index = 1: add(2.2, 3.3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(2.200000f);
					argumentValues[1].setValue(3.300000f);
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
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 20
	// console.log("20 / 1.5: ", div(20, 1.5))
	{
		const ScriptStatement& statement = scripts[1].statements[20];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("20 / 1.5: "));
		// argumentValues[1] --> returnValue of div(20, 1.5)
		// depth = 1 / argument index = 1: div(20, 1.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(1.500000f);
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 21
	// console.log("11.5 * 10.5: ", mul(11.5, 10.5))
	{
		const ScriptStatement& statement = scripts[1].statements[21];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("11.5 * 10.5: "));
		// argumentValues[1] --> returnValue of mul(11.5, 10.5)
		// depth = 1 / argument index = 1: mul(11.5, 10.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(11.500000f);
			argumentValues[1].setValue(10.500000f);
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 22
	// console.log("2.2 > 1.3: ", greater(2.2, 1.3))
	{
		const ScriptStatement& statement = scripts[1].statements[22];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2.2 > 1.3: "));
		// argumentValues[1] --> returnValue of greater(2.2, 1.3)
		// depth = 1 / argument index = 1: greater(2.2, 1.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.200000f);
			argumentValues[1].setValue(1.300000f);
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 23
	// console.log("2.5 < 1.2: ", lesser(2.5, 1.2))
	{
		const ScriptStatement& statement = scripts[1].statements[23];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2.5 < 1.2: "));
		// argumentValues[1] --> returnValue of lesser(2.5, 1.2)
		// depth = 1 / argument index = 1: lesser(2.5, 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.500000f);
			argumentValues[1].setValue(1.200000f);
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 24
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[24];
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

	// Statement: 25
	// console.log("Check vector2 math")
	{
		const ScriptStatement& statement = scripts[1].statements[25];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector2 math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 26
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[26];
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

	// Statement: 27
	// console.log("vec2.computeLength(vec2(20, 10)): ", vec2.computeLength(vec2(20, 10)))
	{
		const ScriptStatement& statement = scripts[1].statements[27];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.computeLength(vec2(20, 10)): "));
		// argumentValues[1] --> returnValue of vec2.computeLength(vec2(20, 10))
		// depth = 1 / argument index = 1: vec2.computeLength(vec2(20, 10))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLength
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.computeLength());
			} else {
				Console::println("ScriptMethodVec2ComputeLength::executeMethod(): " + string("vec2.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 28
	// console.log("vec2.computeLengthSquared(vec2(20, 10)): ", vec2.computeLengthSquared(vec2(20, 10)))
	{
		const ScriptStatement& statement = scripts[1].statements[28];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.computeLengthSquared(vec2(20, 10)): "));
		// argumentValues[1] --> returnValue of vec2.computeLengthSquared(vec2(20, 10))
		// depth = 1 / argument index = 1: vec2.computeLengthSquared(vec2(20, 10))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLengthSquared
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec2ComputeLengthSquared::executeMethod(): " + string("vec2.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 29
	// console.log("vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): ", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))
	{
		const ScriptStatement& statement = scripts[1].statements[29];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): "));
		// argumentValues[1] --> returnValue of vec2.computeDotProduct(vec2(0, 1), vec2(0, -1))
		// depth = 1 / argument index = 1: vec2.computeDotProduct(vec2(0, 1), vec2(0, -1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(0, 1)
			// argumentValues[1] --> returnValue of vec2(0, -1)
			// depth = 2 / argument index = 0: vec2(0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(0, -1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(-1));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				Console::println("ScriptMethodVec2ComputeDotProduct::executeMethod(): " + string("vec2.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected, @ argument 1: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 30
	// console.log("vec2.normalize(vec2(1, 2)): ", vec2.normalize(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[30];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.normalize(vec2(1, 2)): "));
		// argumentValues[1] --> returnValue of vec2.normalize(vec2(1, 2))
		// depth = 1 / argument index = 1: vec2.normalize(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1, 2)
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.normalize
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.normalize());
			} else {
				Console::println("ScriptMethodVec2Normalize::executeMethod(): " + string("vec2.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 31
	// console.log("vec2.getX(vec2(1, 2)): ", vec2.getX(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[31];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.getX(vec2(1, 2)): "));
		// argumentValues[1] --> returnValue of vec2.getX(vec2(1, 2))
		// depth = 1 / argument index = 1: vec2.getX(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1, 2)
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getX
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getX());
			} else {
				Console::println("ScriptMethodVec2GetX::executeMethod(): " + string("vec2.getX") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 32
	// console.log("vec2.getY(vec2(1, 2)): ", vec2.getY(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[32];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2.getY(vec2(1, 2)): "));
		// argumentValues[1] --> returnValue of vec2.getY(vec2(1, 2))
		// depth = 1 / argument index = 1: vec2.getY(vec2(1, 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1, 2)
			// depth = 2 / argument index = 0: vec2(1, 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getY
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getY());
			} else {
				Console::println("ScriptMethodVec2GetY::executeMethod(): " + string("vec2.getY") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 33
	// console.log("vec2(1.1, 2.2) - vec2(1.2, 1.0): ", sub(vec2(1.1, 2.2), vec2(1.2, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[33];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2(1.1, 2.2) - vec2(1.2, 1.0): "));
		// argumentValues[1] --> returnValue of sub(vec2(1.1, 2.2), vec2(1.2, 1.0))
		// depth = 1 / argument index = 1: sub(vec2(1.1, 2.2), vec2(1.2, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1.1, 2.2)
			// argumentValues[1] --> returnValue of vec2(1.2, 1.0)
			// depth = 2 / argument index = 0: vec2(1.1, 2.2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.2, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.200000f);
				argumentValues[1].setValue(1.000000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 34
	// console.log("vec2(20, 10) / vec2(1.5, 2.5): ", div(vec2(20, 10), vec2(1.5, 2.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[34];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2(20, 10) / vec2(1.5, 2.5): "));
		// argumentValues[1] --> returnValue of div(vec2(20, 10), vec2(1.5, 2.5))
		// depth = 1 / argument index = 1: div(vec2(20, 10), vec2(1.5, 2.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			// argumentValues[1] --> returnValue of vec2(1.5, 2.5)
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.5, 2.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 35
	// console.log("vec2(20, 10) * vec2(1.5, 2.5)): ", mul(vec2(20, 10), vec2(1.5, 2.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[35];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2(20, 10) * vec2(1.5, 2.5)): "));
		// argumentValues[1] --> returnValue of mul(vec2(20, 10), vec2(1.5, 2.5))
		// depth = 1 / argument index = 1: mul(vec2(20, 10), vec2(1.5, 2.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			// argumentValues[1] --> returnValue of vec2(1.5, 2.5)
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.5, 2.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 36
	// console.log("vec2(20, 10) / 2): ", div(vec2(20, 10), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[36];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2(20, 10) / 2): "));
		// argumentValues[1] --> returnValue of div(vec2(20, 10), 2)
		// depth = 1 / argument index = 1: div(vec2(20, 10), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 37
	// console.log("vec2(20, 10) * 2): ", mul(vec2(20, 10), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[37];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec2(20, 10) * 2): "));
		// argumentValues[1] --> returnValue of mul(vec2(20, 10), 2)
		// depth = 1 / argument index = 1: mul(vec2(20, 10), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(20, 10)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec2(20, 10)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 38
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[38];
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

	// Statement: 39
	// console.log("Check vector3 math")
	{
		const ScriptStatement& statement = scripts[1].statements[39];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector3 math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 40
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[40];
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

	// Statement: 41
	// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[1].statements[41];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeLength(vec3(20, 10, 5)): "));
		// argumentValues[1] --> returnValue of vec3.computeLength(vec3(20, 10, 5))
		// depth = 1 / argument index = 1: vec3.computeLength(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLength
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLength());
			} else {
				Console::println("ScriptMethodVec3ComputeLength::executeMethod(): " + string("vec3.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 42
	// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[1].statements[42];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeLengthSquared(vec3(20, 10, 5)): "));
		// argumentValues[1] --> returnValue of vec3.computeLengthSquared(vec3(20, 10, 5))
		// depth = 1 / argument index = 1: vec3.computeLengthSquared(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLengthSquared
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec3ComputeLengthSquared::executeMethod(): " + string("vec3.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 43
	// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
	{
		const ScriptStatement& statement = scripts[1].statements[43];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): "));
		// argumentValues[1] --> returnValue of vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		// depth = 1 / argument index = 1: vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0, 0, 1)
			// argumentValues[1] --> returnValue of vec3(0, 0, -1)
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, -1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(-1));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeDotProduct::executeMethod(): " + string("vec3.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 44
	// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[1].statements[44];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): "));
		// argumentValues[1] --> returnValue of vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 0, 0)
			// argumentValues[1] --> returnValue of vec3(0, 1, 0)
			// depth = 2 / argument index = 0: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				argumentValues[2].setValue(static_cast<int64_t>(0));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeCrossProduct::executeMethod(): " + string("vec3.computeCrossProduct") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 45
	// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[45];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.normalize(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.normalize(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.normalize(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.normalize
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.normalize());
			} else {
				Console::println("ScriptMethodVec3Normalize::executeMethod(): " + string("vec3.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 46
	// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[1].statements[46];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): "));
		// argumentValues[1] --> returnValue of vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0, 0, 1)
			// argumentValues[1] --> returnValue of vec3(1, 0, 0)
			// argumentValues[2] --> returnValue of vec3(0, 1, 0)
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 2: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX2 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				argumentValues[2].setValue(static_cast<int64_t>(0));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeAngle::executeMethod(): " + string("vec3.computeAngle") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected @ argument 2: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 47
	// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[47];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getX(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getX(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getX(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getX
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getX());
			} else {
				Console::println("ScriptMethodVec3GetX::executeMethod(): " + string("vec3.getX") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 48
	// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[48];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getY(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getY(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getY(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getY
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getY());
			} else {
				Console::println("ScriptMethodVec3GetY::executeMethod(): " + string("vec3.getY") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 49
	// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[49];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getZ(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getZ(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getZ(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getZ
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getZ());
			} else {
				Console::println("ScriptMethodVec3GetZ::executeMethod(): " + string("vec3.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 50
	// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[50];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): "));
		// argumentValues[1] --> returnValue of sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
		// depth = 1 / argument index = 1: sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1.1, 2.2, 3.3)
			// argumentValues[1] --> returnValue of vec3(1.2, 1.0, 1.0)
			// depth = 2 / argument index = 0: vec3(1.1, 2.2, 3.3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				argumentValues[2].setValue(3.300000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.2, 1.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.200000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(1.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 51
	// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[51];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 52
	// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[52];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 53
	// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[53];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) / 2): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 54
	// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[54];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) * 2): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 55
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[55];
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

	// Statement: 56
	// console.log("Check vector4 math")
	{
		const ScriptStatement& statement = scripts[1].statements[56];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector4 math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 57
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[57];
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

	// Statement: 58
	// console.log("vec4.computeLength(vec4(20, 10, 5, 2.5)): ", vec4.computeLength(vec4(20, 10, 5, 2.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[58];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.computeLength(vec4(20, 10, 5, 2.5)): "));
		// argumentValues[1] --> returnValue of vec4.computeLength(vec4(20, 10, 5, 2.5))
		// depth = 1 / argument index = 1: vec4.computeLength(vec4(20, 10, 5, 2.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 2.5)
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 2.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(2.500000f);
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLength
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.computeLength());
			} else {
				Console::println("ScriptMethodVec4ComputeLength::executeMethod(): " + string("vec4.computeLength") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 59
	// console.log("vec4.computeLengthSquared(vec3(20, 10, 5)): ", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[59];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.computeLengthSquared(vec3(20, 10, 5)): "));
		// argumentValues[1] --> returnValue of vec4.computeLengthSquared(vec4(20, 10, 5, 2.5))
		// depth = 1 / argument index = 1: vec4.computeLengthSquared(vec4(20, 10, 5, 2.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 2.5)
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 2.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(2.500000f);
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLengthSquared
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec4ComputeLengthSquared::executeMethod(): " + string("vec4.computeLengthSquared") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 60
	// console.log("vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): ", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))
	{
		const ScriptStatement& statement = scripts[1].statements[60];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): "));
		// argumentValues[1] --> returnValue of vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1))
		// depth = 1 / argument index = 1: vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(0, 0, 1, 1)
			// argumentValues[1] --> returnValue of vec4(0, 0, -1, 1)
			// depth = 2 / argument index = 0: vec4(0, 0, 1, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(0, 0, -1, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(-1));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
				Console::println("ScriptMethodVec4ComputeDotProduct::executeMethod(): " + string("vec4.computeDotProduct") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected, @ argument 1: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 61
	// console.log("vec4.normalize(vec4(1, 2, 3, 4)): ", vec4.normalize(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[61];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.normalize(vec4(1, 2, 3, 4)): "));
		// argumentValues[1] --> returnValue of vec4.normalize(vec4(1, 2, 3, 4))
		// depth = 1 / argument index = 1: vec4.normalize(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				argumentValues[3].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.normalize
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.normalize());
			} else {
				Console::println("ScriptMethodVec4Normalize::executeMethod(): " + string("vec4.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 62
	// console.log("vec4.getX(vec4(1, 2, 3, 4)): ", vec4.getX(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[62];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.getX(vec4(1, 2, 3, 4)): "));
		// argumentValues[1] --> returnValue of vec4.getX(vec4(1, 2, 3, 4))
		// depth = 1 / argument index = 1: vec4.getX(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				argumentValues[3].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getX
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getX());
			} else {
				Console::println("ScriptMethodVec4GetX::executeMethod(): " + string("vec4.getX") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 63
	// console.log("vec4.getY(vec4(1, 2, 3, 4)): ", vec4.getY(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[63];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.getY(vec4(1, 2, 3, 4)): "));
		// argumentValues[1] --> returnValue of vec4.getY(vec4(1, 2, 3, 4))
		// depth = 1 / argument index = 1: vec4.getY(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				argumentValues[3].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getY
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getY());
			} else {
				Console::println("ScriptMethodVec4GetY::executeMethod(): " + string("vec4.getY") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 64
	// console.log("vec4.getZ(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[64];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.getZ(vec4(1, 2, 3, 4)): "));
		// argumentValues[1] --> returnValue of vec4.getZ(vec4(1, 2, 3, 4))
		// depth = 1 / argument index = 1: vec4.getZ(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				argumentValues[3].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println("ScriptMethodVec4GetZ::executeMethod(): " + string("vec4.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 65
	// console.log("vec4.getW(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[65];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4.getW(vec4(1, 2, 3, 4)): "));
		// argumentValues[1] --> returnValue of vec4.getZ(vec4(1, 2, 3, 4))
		// depth = 1 / argument index = 1: vec4.getZ(vec4(1, 2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1, 2, 3, 4)
			// depth = 2 / argument index = 0: vec4(1, 2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				argumentValues[3].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println("ScriptMethodVec4GetZ::executeMethod(): " + string("vec4.getZ") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 66
	// console.log("vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): ", sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[66];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): "));
		// argumentValues[1] --> returnValue of sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0))
		// depth = 1 / argument index = 1: sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(1.1, 2.2, 3.3, 1.0)
			// argumentValues[1] --> returnValue of vec4(1.2, 1.0, 1.0, 1.0)
			// depth = 2 / argument index = 0: vec4(1.1, 2.2, 3.3, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				argumentValues[2].setValue(3.300000f);
				argumentValues[3].setValue(1.000000f);
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.2, 1.0, 1.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.200000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(1.000000f);
				argumentValues[3].setValue(1.000000f);
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 67
	// console.log("vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): ", div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))
	{
		const ScriptStatement& statement = scripts[1].statements[67];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): "));
		// argumentValues[1] --> returnValue of div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1))
		// depth = 1 / argument index = 1: div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
			// argumentValues[1] --> returnValue of vec4(1.5, 2.5, 3.5, 1)
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.5, 2.5, 3.5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 68
	// console.log("vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): ", mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))
	{
		const ScriptStatement& statement = scripts[1].statements[68];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): "));
		// argumentValues[1] --> returnValue of mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1))
		// depth = 1 / argument index = 1: mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
			// argumentValues[1] --> returnValue of vec4(1.5, 2.5, 3.5, 1)
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(1.5, 2.5, 3.5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 69
	// console.log("vec4(20, 10, 5, 1) / 2): ", div(vec4(20, 10, 5, 1), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[69];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4(20, 10, 5, 1) / 2): "));
		// argumentValues[1] --> returnValue of div(vec4(20, 10, 5, 1), 2)
		// depth = 1 / argument index = 1: div(vec4(20, 10, 5, 1), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 70
	// console.log("vec4(20, 10, 5, 1) * 2): ", mul(vec4(20, 10, 5, 1), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[70];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec4(20, 10, 5, 1) * 2): "));
		// argumentValues[1] --> returnValue of mul(vec4(20, 10, 5, 1), 2)
		// depth = 1 / argument index = 1: mul(vec4(20, 10, 5, 1), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec4(20, 10, 5, 1)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec4(20, 10, 5, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				argumentValues[3].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 71
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[71];
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

	// Statement: 72
	// console.log("Check quaternion math")
	{
		const ScriptStatement& statement = scripts[1].statements[72];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check quaternion math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 73
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[73];
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

	// Statement: 74
	// console.log("quaternion.identity(): ", quaternion.identity())
	{
		const ScriptStatement& statement = scripts[1].statements[74];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.identity(): "));
		// argumentValues[1] --> returnValue of quaternion.identity()
		// depth = 1 / argument index = 1: quaternion.identity()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: quaternion.identity
			returnValue.setValue(Quaternion().identity());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 75
	// console.log("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
	{
		const ScriptStatement& statement = scripts[1].statements[75];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): "));
		// argumentValues[1] --> returnValue of quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
		// depth = 1 / argument index = 1: quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
			argumentValues[1].setValue(90.000000f);
			// depth = 2 / argument index = 0: vec3(0.0, 1.0, 0.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(0.000000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(0.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 76
	// console.log("quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[76];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): "));
		// argumentValues[1] --> returnValue of quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		// depth = 1 / argument index = 1: quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.normalize
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.normalize());
			} else {
				Console::println("ScriptMethodQuaternionNormalize::executeMethod(): " + string("quaternion.normalize") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 77
	// console.log("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): ", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[77];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): "));
		// argumentValues[1] --> returnValue of quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0))
		// depth = 1 / argument index = 1: quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// argumentValues[1] --> returnValue of quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(1.0, 0.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(1.0, 0.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(1.000000f);
					argumentValues[1].setValue(0.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.multiply
			Quaternion quaternion;
			Quaternion quaternionValue;
			Vector3 vec3Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				if (MiniScript::getQuaternionValue(argumentValues, 1, quaternionValue, false) == true) {
					returnValue.setValue(quaternion.multiply(quaternionValue));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(quaternion.multiply(vec3Value));
				} else {
					Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 78
	// console.log("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): ", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[78];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): "));
		// argumentValues[1] --> returnValue of quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0))
		// depth = 1 / argument index = 1: quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// argumentValues[1] --> returnValue of vec3(0.0, 0.0, 1.0)
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0.0, 0.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(0.000000f);
				argumentValues[1].setValue(0.000000f);
				argumentValues[2].setValue(1.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.multiply
			Quaternion quaternion;
			Quaternion quaternionValue;
			Vector3 vec3Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				if (MiniScript::getQuaternionValue(argumentValues, 1, quaternionValue, false) == true) {
					returnValue.setValue(quaternion.multiply(quaternionValue));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(quaternion.multiply(vec3Value));
				} else {
					Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 79
	// console.log("quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[79];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): "));
		// argumentValues[1] --> returnValue of quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		// depth = 1 / argument index = 1: quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// depth = 2 / argument index = 0: quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.computeMatrix
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.computeMatrix());
			} else {
				Console::println("ScriptMethodQuaternionComputeMatrix::executeMethod(): " + string("quaternion.computeMatrix") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: quaternion expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 80
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[80];
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

	// Statement: 81
	// console.log("Check matrix4x4 math")
	{
		const ScriptStatement& statement = scripts[1].statements[81];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check matrix4x4 math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 82
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[82];
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

	// Statement: 83
	// console.log("mat4.identity(): ", mat4.identity())
	{
		const ScriptStatement& statement = scripts[1].statements[83];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.identity(): "));
		// argumentValues[1] --> returnValue of mat4.identity()
		// depth = 1 / argument index = 1: mat4.identity()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat4.identity
			returnValue.setValue(Matrix4x4().identity());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 84
	// console.log("mat4.translate(vec3(1.0, 2.0, 3.0)): ", mat4.translate(vec3(1.0, 2.0, 3.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[84];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.translate(vec3(1.0, 2.0, 3.0)): "));
		// argumentValues[1] --> returnValue of mat4.translate(vec3(1.0, 2.0, 3.0))
		// depth = 1 / argument index = 1: mat4.translate(vec3(1.0, 2.0, 3.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1.0, 2.0, 3.0)
			// depth = 2 / argument index = 0: vec3(1.0, 2.0, 3.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.000000f);
				argumentValues[1].setValue(2.000000f);
				argumentValues[2].setValue(3.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.translate
			Vector3 translation;
			if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix4x4().identity().translate(translation));
			} else {
				Console::println("ScriptMethodMatrix4x4Translate::executeMethod(): " + string("mat4.translate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 85
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))
	{
		const ScriptStatement& statement = scripts[1].statements[85];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): "));
		// argumentValues[1] --> returnValue of mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
		// depth = 1 / argument index = 1: mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
			argumentValues[1].setValue(90.000000f);
			// depth = 2 / argument index = 0: vec3(0.0, 1.0, 0.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(0.000000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(0.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.rotate
			Vector3 axis;
			float angle;
			if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
				returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
			} else {
				Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 86
	// console.log("mat4.scale(vec3(1.0, 2.0, 3.0)): ", mat4.scale(vec3(1.0, 2.0, 3.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[86];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.scale(vec3(1.0, 2.0, 3.0)): "));
		// argumentValues[1] --> returnValue of mat4.scale(vec3(1.0, 2.0, 3.0))
		// depth = 1 / argument index = 1: mat4.scale(vec3(1.0, 2.0, 3.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1.0, 2.0, 3.0)
			// depth = 2 / argument index = 0: vec3(1.0, 2.0, 3.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.000000f);
				argumentValues[1].setValue(2.000000f);
				argumentValues[2].setValue(3.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 or float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 87
	// console.log("mat4.scale(3.0): ", mat4.scale(3.0))
	{
		const ScriptStatement& statement = scripts[1].statements[87];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.scale(3.0): "));
		// argumentValues[1] --> returnValue of mat4.scale(3.0)
		// depth = 1 / argument index = 1: mat4.scale(3.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(3.000000f);
			// method code: mat4.scale
			Vector3 vec3Value;
			float floatValue;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix4x4().identity().scale(floatValue));
			} else {
				Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 or float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 88
	// console.log("mat4.invert(mat4.scale(3.0)): ", mat4.invert(mat4.scale(3.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[88];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.invert(mat4.scale(3.0)): "));
		// argumentValues[1] --> returnValue of mat4.invert(mat4.scale(3.0))
		// depth = 1 / argument index = 1: mat4.invert(mat4.scale(3.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat4.scale(3.0)
			// depth = 2 / argument index = 0: mat4.scale(3.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(3.000000f);
				// method code: mat4.scale
				Vector3 vec3Value;
				float floatValue;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
				} else
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(floatValue));
				} else {
					Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 or float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.invert
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.invert());
			} else {
				Console::println("ScriptMethodMatrix4x4Invert::executeMethod(): " + string("mat4.invert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 89
	// console.log("mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[89];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): "));
		// argumentValues[1] --> returnValue of mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		// depth = 1 / argument index = 1: mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
				} else {
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.computeEulerAngles
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.computeEulerAngles());
			} else {
				Console::println("ScriptMethodMatrix4x4EulerAngles::executeMethod(): " + string("mat4.computeEulerAngles") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 90
	// console.log("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): ", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[90];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): "));
		// argumentValues[1] --> returnValue of mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0))
		// depth = 1 / argument index = 1: mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// argumentValues[1] --> returnValue of mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
				} else {
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(1.0, 0.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(1.0, 0.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(1.000000f);
					argumentValues[1].setValue(0.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
				} else {
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				if (MiniScript::getMatrix4x4Value(argumentValues, 1, mat4Value, false) == true) {
					returnValue.setValue(mat4.multiply(mat4Value));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec3Value));
				} else
				if (MiniScript::getVector4Value(argumentValues, 1, vec4Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec4Value));
				} else {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 91
	// console.log("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): ", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[91];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): "));
		// argumentValues[1] --> returnValue of mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0))
		// depth = 1 / argument index = 1: mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			// argumentValues[1] --> returnValue of vec3(0.0, 0.0, 1.0)
			// depth = 2 / argument index = 0: mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
				argumentValues[1].setValue(90.000000f);
				// depth = 3 / argument index = 0: vec3(0.0, 1.0, 0.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(0.000000f);
					argumentValues[1].setValue(1.000000f);
					argumentValues[2].setValue(0.000000f);
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.rotate
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
				} else {
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0.0, 0.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(0.000000f);
				argumentValues[1].setValue(0.000000f);
				argumentValues[2].setValue(1.000000f);
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				if (MiniScript::getMatrix4x4Value(argumentValues, 1, mat4Value, false) == true) {
					returnValue.setValue(mat4.multiply(mat4Value));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec3Value));
				} else
				if (MiniScript::getVector4Value(argumentValues, 1, vec4Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec4Value));
				} else {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 92
	// console.log("mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): ", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[92];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): "));
		// argumentValues[1] --> returnValue of mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0))
		// depth = 1 / argument index = 1: mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0)))
			// argumentValues[1] --> returnValue of vec4(0.0, 0.0, 1.0, 0.0)
			// depth = 2 / argument index = 0: mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
				// argumentValues[1] --> returnValue of mat4.translate(vec3(1.0, 2.0, 3.0))
				// depth = 3 / argument index = 0: mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// argumentValues[0] --> returnValue of vec3(0.0, 1.0, 0.0)
					argumentValues[1].setValue(90.000000f);
					// depth = 4 / argument index = 0: vec3(0.0, 1.0, 0.0)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[0];
						array<ScriptVariable, 3> argumentValues;
						array<ScriptVariable, 3>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(0.000000f);
						argumentValues[1].setValue(1.000000f);
						argumentValues[2].setValue(0.000000f);
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
							Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: mat4.rotate
					Vector3 axis;
					float angle;
					if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
						returnValue.setValue(Matrix4x4().identity().rotate(axis, angle));
					} else {
						Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: mat4.translate(vec3(1.0, 2.0, 3.0))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of vec3(1.0, 2.0, 3.0)
					// depth = 4 / argument index = 0: vec3(1.0, 2.0, 3.0)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 3> argumentValues;
						array<ScriptVariable, 3>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(1.000000f);
						argumentValues[1].setValue(2.000000f);
						argumentValues[2].setValue(3.000000f);
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
							Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: mat4.translate
					Vector3 translation;
					if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
						returnValue.setValue(Matrix4x4().identity().translate(translation));
					} else {
						Console::println("ScriptMethodMatrix4x4Translate::executeMethod(): " + string("mat4.translate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.multiply
				Matrix4x4 mat4;
				Matrix4x4 mat4Value;
				Vector3 vec3Value;
				Vector4 vec4Value;
				if (argumentValues.size() != 2) {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				} else
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
					if (MiniScript::getMatrix4x4Value(argumentValues, 1, mat4Value, false) == true) {
						returnValue.setValue(mat4.multiply(mat4Value));
					} else
					if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
						returnValue.setValue(mat4.multiply(vec3Value));
					} else
					if (MiniScript::getVector4Value(argumentValues, 1, vec4Value, false) == true) {
						returnValue.setValue(mat4.multiply(vec4Value));
					} else {
						Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec4(0.0, 0.0, 1.0, 0.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 4> argumentValues;
				array<ScriptVariable, 4>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(0.000000f);
				argumentValues[1].setValue(0.000000f);
				argumentValues[2].setValue(1.000000f);
				argumentValues[3].setValue(0.000000f);
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				if (MiniScript::getMatrix4x4Value(argumentValues, 1, mat4Value, false) == true) {
					returnValue.setValue(mat4.multiply(mat4Value));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec3Value));
				} else
				if (MiniScript::getVector4Value(argumentValues, 1, vec4Value, false) == true) {
					returnValue.setValue(mat4.multiply(vec4Value));
				} else {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 93
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[93];
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

	// Statement: 94
	// console.log("Check matrix3x3 math")
	{
		const ScriptStatement& statement = scripts[1].statements[94];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check matrix3x3 math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 95
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[95];
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

	// Statement: 96
	// console.log("mat3.identity(): ", mat3.identity())
	{
		const ScriptStatement& statement = scripts[1].statements[96];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.identity(): "));
		// argumentValues[1] --> returnValue of mat3.identity()
		// depth = 1 / argument index = 1: mat3.identity()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: mat3.identity
			returnValue.setValue(Matrix2D3x3().identity());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 97
	// console.log("mat3.translate(vec2(1.0, 2.0)): ", mat3.translate(vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[97];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.translate(vec2(1.0, 2.0)): "));
		// argumentValues[1] --> returnValue of mat3.translate(vec2(1.0, 2.0))
		// depth = 1 / argument index = 1: mat3.translate(vec2(1.0, 2.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1.0, 2.0)
			// depth = 2 / argument index = 0: vec2(1.0, 2.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.000000f);
				argumentValues[1].setValue(2.000000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.translate
			Vector2 translation;
			if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().translate(translation));
			} else {
				Console::println("ScriptMethodMatrix3x3Translate::executeMethod(): " + string("mat3.translate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 98
	// console.log("mat3.rotate(90.0): ", mat3.rotate(90.0))
	{
		const ScriptStatement& statement = scripts[1].statements[98];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.rotate(90.0): "));
		// argumentValues[1] --> returnValue of mat3.rotate(90.0)
		// depth = 1 / argument index = 1: mat3.rotate(90.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(90.000000f);
			// method code: mat3.rotate
			float angle;
			if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().rotate(angle));
			} else {
				Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 99
	// console.log("mat3.rotateAroundTextureCenter(90.0): ", mat3.rotateAroundTextureCenter(90.0))
	{
		const ScriptStatement& statement = scripts[1].statements[99];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.rotateAroundTextureCenter(90.0): "));
		// argumentValues[1] --> returnValue of mat3.rotateAroundTextureCenter(90.0)
		// depth = 1 / argument index = 1: mat3.rotateAroundTextureCenter(90.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(90.000000f);
			// method code: mat3.rotateAroundTextureCenter
			float angle;
			if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
				returnValue.setValue(Matrix2D3x3::rotateAroundTextureCenter(angle));
			} else {
				Console::println("ScriptMethodMatrix3x3RotateAroundCenter::executeMethod(): " + string("mat3.rotateAroundTextureCenter") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 100
	// console.log("mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): ", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))
	{
		const ScriptStatement& statement = scripts[1].statements[100];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): "));
		// argumentValues[1] --> returnValue of mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0)
		// depth = 1 / argument index = 1: mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(0.5, 0.4)
			argumentValues[1].setValue(90.000000f);
			// depth = 2 / argument index = 0: vec2(0.5, 0.4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(0.500000f);
				argumentValues[1].setValue(0.400000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.rotateAroundPoint
			Vector2 point;
			float angle;
			if (MiniScript::getVector2Value(argumentValues, 0, point, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
				returnValue.setValue(Matrix2D3x3().rotateAroundPoint(point, angle));
			} else {
				Console::println("ScriptMethodMatrix3x3RotateAroundPoint::executeMethod(): " + string("mat3.rotateAroundPoint") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 101
	// console.log("mat3.scale(vec2(1.0, 2.0)): ", mat3.scale(vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[101];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.scale(vec2(1.0, 2.0)): "));
		// argumentValues[1] --> returnValue of mat3.scale(vec2(1.0, 2.0))
		// depth = 1 / argument index = 1: mat3.scale(vec2(1.0, 2.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec2(1.0, 2.0)
			// depth = 2 / argument index = 0: vec2(1.0, 2.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.000000f);
				argumentValues[1].setValue(2.000000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.scale
			Vector2 vec2Value;
			float floatValue;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().scale(vec2Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().scale(floatValue));
			} else {
				Console::println("ScriptMethodMatrix3x3Scale::executeMethod(): " + string("mat3.scale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 or float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 102
	// console.log("mat3.scale(3.0): ", mat3.scale(3.0))
	{
		const ScriptStatement& statement = scripts[1].statements[102];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.scale(3.0): "));
		// argumentValues[1] --> returnValue of mat3.scale(3.0)
		// depth = 1 / argument index = 1: mat3.scale(3.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(3.000000f);
			// method code: mat3.scale
			Vector2 vec2Value;
			float floatValue;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().scale(vec2Value));
			} else
			if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().scale(floatValue));
			} else {
				Console::println("ScriptMethodMatrix3x3Scale::executeMethod(): " + string("mat3.scale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 or float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 103
	// console.log("mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): ", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))
	{
		const ScriptStatement& statement = scripts[1].statements[103];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): "));
		// argumentValues[1] --> returnValue of mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0)))
		// depth = 1 / argument index = 1: mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat3.rotate(90.0)
			// argumentValues[1] --> returnValue of mat3.translate(vec2(1.0, 2.0))
			// depth = 2 / argument index = 0: mat3.rotate(90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(90.000000f);
				// method code: mat3.rotate
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix2D3x3().identity().rotate(angle));
				} else {
					Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: mat3.translate(vec2(1.0, 2.0))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of vec2(1.0, 2.0)
				// depth = 3 / argument index = 0: vec2(1.0, 2.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(1.000000f);
					argumentValues[1].setValue(2.000000f);
					// method code: vec2
					Vector3 result;
					float xValue;
					float yValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
						returnValue.setValue(Vector2(xValue, yValue));
					} else {
						Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat3.translate
				Vector2 translation;
				if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
					returnValue.setValue(Matrix2D3x3().identity().translate(translation));
				} else {
					Console::println("ScriptMethodMatrix3x3Translate::executeMethod(): " + string("mat3.translate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector2 expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.multiply
			Matrix2D3x3 mat3;
			Matrix2D3x3 mat3Value;
			Vector2 vec2Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix3x3Value(argumentValues, 0, mat3, false) == true) {
				if (MiniScript::getMatrix3x3Value(argumentValues, 1, mat3Value, false) == true) {
					returnValue.setValue(mat3.multiply(mat3Value));
				} else
				if (MiniScript::getVector2Value(argumentValues, 1, vec2Value, false) == true) {
					returnValue.setValue(mat3.multiply(vec2Value));
				} else {
					Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 104
	// console.log("mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): ", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[104];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): "));
		// argumentValues[1] --> returnValue of mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0))
		// depth = 1 / argument index = 1: mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of mat3.rotate(90.0)
			// argumentValues[1] --> returnValue of vec2(1.0, 2.0)
			// depth = 2 / argument index = 0: mat3.rotate(90.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(90.000000f);
				// method code: mat3.rotate
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix2D3x3().identity().rotate(angle));
				} else {
					Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec2(1.0, 2.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.000000f);
				argumentValues[1].setValue(2.000000f);
				// method code: vec2
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.multiply
			Matrix2D3x3 mat3;
			Matrix2D3x3 mat3Value;
			Vector2 vec2Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix3x3Value(argumentValues, 0, mat3, false) == true) {
				if (MiniScript::getMatrix3x3Value(argumentValues, 1, mat3Value, false) == true) {
					returnValue.setValue(mat3.multiply(mat3Value));
				} else
				if (MiniScript::getVector2Value(argumentValues, 1, vec2Value, false) == true) {
					returnValue.setValue(mat3.multiply(vec2Value));
				} else {
					Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 105
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[105];
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

	// Statement: 106
	// console.log("Check additional math")
	{
		const ScriptStatement& statement = scripts[1].statements[106];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check additional math"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 107
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[107];
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

	// Statement: 108
	// console.log("math.PI(): ", math.PI())
	{
		const ScriptStatement& statement = scripts[1].statements[108];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.PI(): "));
		// argumentValues[1] --> returnValue of math.PI()
		// depth = 1 / argument index = 1: math.PI()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.PI
			returnValue.setValue(Math::PI);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 109
	// console.log("math.EPSILON(): ", math.EPSILON())
	{
		const ScriptStatement& statement = scripts[1].statements[109];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.EPSILON(): "));
		// argumentValues[1] --> returnValue of math.EPSILON()
		// depth = 1 / argument index = 1: math.EPSILON()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.EPSILON
			returnValue.setValue(Math::EPSILON);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 110
	// console.log("math.DEG2RAD(): ", math.DEG2RAD())
	{
		const ScriptStatement& statement = scripts[1].statements[110];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.DEG2RAD(): "));
		// argumentValues[1] --> returnValue of math.DEG2RAD()
		// depth = 1 / argument index = 1: math.DEG2RAD()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.DEG2RAD
			returnValue.setValue(Math::DEG2RAD);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 111
	// console.log("math.G(): ", math.G())
	{
		const ScriptStatement& statement = scripts[1].statements[111];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.G(): "));
		// argumentValues[1] --> returnValue of math.G()
		// depth = 1 / argument index = 1: math.G()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.G
			returnValue.setValue(Math::G);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 112
	// console.log("math.acos(0.0): ", math.acos(0.0))
	{
		const ScriptStatement& statement = scripts[1].statements[112];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.acos(0.0): "));
		// argumentValues[1] --> returnValue of math.acos(0.0)
		// depth = 1 / argument index = 1: math.acos(0.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(0.000000f);
			// method code: math.acos
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::acos(value));
			} else {
				Console::println("ScriptMethodAcos::executeMethod(): " + string("math.acos") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 113
	// console.log("math.asin(1.0): ", math.asin(1.0))
	{
		const ScriptStatement& statement = scripts[1].statements[113];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.asin(1.0): "));
		// argumentValues[1] --> returnValue of math.asin(1.0)
		// depth = 1 / argument index = 1: math.asin(1.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(1.000000f);
			// method code: math.asin
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::asin(value));
			} else {
				Console::println("ScriptMethodAsin::executeMethod(): " + string("math.asin") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 114
	// console.log("math.atan(1.0): ", math.atan(1.0))
	{
		const ScriptStatement& statement = scripts[1].statements[114];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.atan(1.0): "));
		// argumentValues[1] --> returnValue of math.atan(1.0)
		// depth = 1 / argument index = 1: math.atan(1.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(1.000000f);
			// method code: math.atan
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::atan(value));
			} else {
				Console::println("ScriptMethodAtan::executeMethod(): " + string("math.atan") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 115
	// console.log("math.atan2(-1.0, -1.0): ", math.atan2(-1.0, -1.0))
	{
		const ScriptStatement& statement = scripts[1].statements[115];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.atan2(-1.0, -1.0): "));
		// argumentValues[1] --> returnValue of math.atan2(-1.0, -1.0)
		// depth = 1 / argument index = 1: math.atan2(-1.0, -1.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(-1.000000f);
			argumentValues[1].setValue(-1.000000f);
			// method code: math.atan2
			float y;
			float x;
			if (MiniScript::getFloatValue(argumentValues, 0, y, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, x, false) == true) {
				returnValue.setValue(Math::atan2(y, x));
			} else {
				Console::println("ScriptMethodAtan2::executeMethod(): " + string("math.atan2") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 116
	// console.log("math.floor(2.87): ", math.floor(2.87))
	{
		const ScriptStatement& statement = scripts[1].statements[116];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.floor(2.87): "));
		// argumentValues[1] --> returnValue of math.floor(2.87)
		// depth = 1 / argument index = 1: math.floor(2.87)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.870000f);
			// method code: math.floor
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::floor(value));
			} else {
				Console::println("ScriptMethodCeil::executeMethod(): " + string("math.floor") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 117
	// console.log("math.ceil(2.87): ", math.ceil(2.87))
	{
		const ScriptStatement& statement = scripts[1].statements[117];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.ceil(2.87): "));
		// argumentValues[1] --> returnValue of math.ceil(2.87)
		// depth = 1 / argument index = 1: math.ceil(2.87)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.870000f);
			// method code: math.ceil
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::ceil(value));
			} else {
				Console::println("ScriptMethodCeil::executeMethod(): " + string("math.ceil") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 118
	// console.log("math.round(2.37): ", math.round(2.37))
	{
		const ScriptStatement& statement = scripts[1].statements[118];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.round(2.37): "));
		// argumentValues[1] --> returnValue of math.round(2.37)
		// depth = 1 / argument index = 1: math.round(2.37)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.370000f);
			// method code: math.round
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::round(value));
			} else {
				Console::println("ScriptMethodRound::executeMethod(): " + string("math.round") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 119
	// console.log("math.round(2.87): ", math.round(2.87))
	{
		const ScriptStatement& statement = scripts[1].statements[119];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.round(2.87): "));
		// argumentValues[1] --> returnValue of math.round(2.87)
		// depth = 1 / argument index = 1: math.round(2.87)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.870000f);
			// method code: math.round
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::round(value));
			} else {
				Console::println("ScriptMethodRound::executeMethod(): " + string("math.round") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 120
	// console.log("math.cos(0.0): ", math.cos(0.0))
	{
		const ScriptStatement& statement = scripts[1].statements[120];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.cos(0.0): "));
		// argumentValues[1] --> returnValue of math.cos(0.0)
		// depth = 1 / argument index = 1: math.cos(0.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(0.000000f);
			// method code: math.cos
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::cos(value));
			} else {
				Console::println("ScriptMethodCos::executeMethod(): " + string("math.cos") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 121
	// console.log("math.sin(0.0): ", math.sin(0.0))
	{
		const ScriptStatement& statement = scripts[1].statements[121];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.sin(0.0): "));
		// argumentValues[1] --> returnValue of math.sin(0.0)
		// depth = 1 / argument index = 1: math.sin(0.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(0.000000f);
			// method code: math.sin
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::sin(value));
			} else {
				Console::println("ScriptMethodSin::executeMethod(): " + string("math.sin") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 122
	// console.log("math.tan(1.0): ", math.tan(1.0))
	{
		const ScriptStatement& statement = scripts[1].statements[122];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.tan(1.0): "));
		// argumentValues[1] --> returnValue of math.tan(1.0)
		// depth = 1 / argument index = 1: math.tan(1.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(1.000000f);
			// method code: math.tan
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::tan(value));
			} else {
				Console::println("ScriptMethodTan::executeMethod(): " + string("math.tan") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 123
	// console.log("math.sqrt(9.0): ", math.sqrt(9))
	{
		const ScriptStatement& statement = scripts[1].statements[123];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.sqrt(9.0): "));
		// argumentValues[1] --> returnValue of math.sqrt(9)
		// depth = 1 / argument index = 1: math.sqrt(9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(9));
			// method code: math.sqrt
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::sqrt(value));
			} else {
				Console::println("ScriptMethodSqrt::executeMethod(): " + string("math.sqrt") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 124
	// console.log("math.random(): ", math.random())
	{
		const ScriptStatement& statement = scripts[1].statements[124];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.random(): "));
		// argumentValues[1] --> returnValue of math.random()
		// depth = 1 / argument index = 1: math.random()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 125
	// console.log("math.random(): ", math.random())
	{
		const ScriptStatement& statement = scripts[1].statements[125];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.random(): "));
		// argumentValues[1] --> returnValue of math.random()
		// depth = 1 / argument index = 1: math.random()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 126
	// console.log("math.random(): ", math.random())
	{
		const ScriptStatement& statement = scripts[1].statements[126];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.random(): "));
		// argumentValues[1] --> returnValue of math.random()
		// depth = 1 / argument index = 1: math.random()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: math.random
			returnValue.setValue(Math::random());
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 127
	// console.log("math.exp(1.0): ", math.exp(1.0))
	{
		const ScriptStatement& statement = scripts[1].statements[127];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.exp(1.0): "));
		// argumentValues[1] --> returnValue of math.exp(1.0)
		// depth = 1 / argument index = 1: math.exp(1.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(1.000000f);
			// method code: math.exp
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::exp(value));
			} else {
				Console::println("ScriptMethodExp::executeMethod(): " + string("math.exp") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 128
	// console.log("math.log(2.0): ", math.log(2.0))
	{
		const ScriptStatement& statement = scripts[1].statements[128];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.log(2.0): "));
		// argumentValues[1] --> returnValue of math.log(2.0)
		// depth = 1 / argument index = 1: math.log(2.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.000000f);
			// method code: math.log
			float value;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true) {
				returnValue.setValue(Math::log(value));
			} else {
				Console::println("ScriptMethodLog::executeMethod(): " + string("math.log") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 129
	// console.log("math.sign(-2): ", math.sign(-2))
	{
		const ScriptStatement& statement = scripts[1].statements[129];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.sign(-2): "));
		// argumentValues[1] --> returnValue of math.sign(-2)
		// depth = 1 / argument index = 1: math.sign(-2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-2));
			// method code: math.sign
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::sign(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::sign(intValue));
			} else {
				Console::println("ScriptMethodSign::executeMethod(): " + string("math.sign") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 130
	// console.log("math.sign(-2.0): ", math.sign(-2.0))
	{
		const ScriptStatement& statement = scripts[1].statements[130];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.sign(-2.0): "));
		// argumentValues[1] --> returnValue of math.sign(-2.0)
		// depth = 1 / argument index = 1: math.sign(-2.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(-2.000000f);
			// method code: math.sign
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::sign(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::sign(intValue));
			} else {
				Console::println("ScriptMethodSign::executeMethod(): " + string("math.sign") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 131
	// console.log("math.square(3): ", math.square(3))
	{
		const ScriptStatement& statement = scripts[1].statements[131];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.square(3): "));
		// argumentValues[1] --> returnValue of math.square(3)
		// depth = 1 / argument index = 1: math.square(3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(3));
			// method code: math.square
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::square(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::square(intValue));
			} else {
				Console::println("ScriptMethodSquare::executeMethod(): " + string("math.square") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 132
	// console.log("math.square(3.0): ", math.square(3.0))
	{
		const ScriptStatement& statement = scripts[1].statements[132];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.square(3.0): "));
		// argumentValues[1] --> returnValue of math.square(3.0)
		// depth = 1 / argument index = 1: math.square(3.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(3.000000f);
			// method code: math.square
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::square(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::square(intValue));
			} else {
				Console::println("ScriptMethodSquare::executeMethod(): " + string("math.square") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 133
	// console.log("math.min(4, 9): ", math.min(4, 9))
	{
		const ScriptStatement& statement = scripts[1].statements[133];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.min(4, 9): "));
		// argumentValues[1] --> returnValue of math.min(4, 9)
		// depth = 1 / argument index = 1: math.min(4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(4));
			argumentValues[1].setValue(static_cast<int64_t>(9));
			// method code: math.min
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::min(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::min(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 134
	// console.log("math.min(4.1, 9.3): ", math.min(4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[1].statements[134];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.min(4.1, 9.3): "));
		// argumentValues[1] --> returnValue of math.min(4.1, 9.3)
		// depth = 1 / argument index = 1: math.min(4.1, 9.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(4.100000f);
			argumentValues[1].setValue(9.300000f);
			// method code: math.min
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::min(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::min(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 135
	// console.log("math.max(4, 9): ", math.max(4, 9))
	{
		const ScriptStatement& statement = scripts[1].statements[135];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.max(4, 9): "));
		// argumentValues[1] --> returnValue of math.max(4, 9)
		// depth = 1 / argument index = 1: math.max(4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(4));
			argumentValues[1].setValue(static_cast<int64_t>(9));
			// method code: math.max
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::max(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::max(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 136
	// console.log("math.max(4.1, 9.3): ", math.max(4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[1].statements[136];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.max(4.1, 9.3): "));
		// argumentValues[1] --> returnValue of math.max(4.1, 9.3)
		// depth = 1 / argument index = 1: math.max(4.1, 9.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(4.100000f);
			argumentValues[1].setValue(9.300000f);
			// method code: math.max
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::max(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::max(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 137
	// console.log("math.abs(-9): ", math.abs(-9))
	{
		const ScriptStatement& statement = scripts[1].statements[137];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.abs(-9): "));
		// argumentValues[1] --> returnValue of math.abs(-9)
		// depth = 1 / argument index = 1: math.abs(-9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-9));
			// method code: math.abs
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::abs(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::abs(intValue));
			} else {
				Console::println("ScriptMethodAbs::executeMethod(): " + string("math.abs") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 138
	// console.log("math.abs(-9.3): ", math.abs(-9.3))
	{
		const ScriptStatement& statement = scripts[1].statements[138];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.abs(-9.3): "));
		// argumentValues[1] --> returnValue of math.abs(-9.3)
		// depth = 1 / argument index = 1: math.abs(-9.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(-9.300000f);
			// method code: math.abs
			int64_t intValue;
			float floatValue;
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true && MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
				returnValue.setValue(Math::abs(floatValue));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
				returnValue.setValue(Math::abs(intValue));
			} else {
				Console::println("ScriptMethodAbs::executeMethod(): " + string("math.abs") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 139
	// console.log("math.clamp(-1, 4, 9): ", math.clamp(-1, 4, 9))
	{
		const ScriptStatement& statement = scripts[1].statements[139];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.clamp(-1, 4, 9): "));
		// argumentValues[1] --> returnValue of math.clamp(-1, 4, 9)
		// depth = 1 / argument index = 1: math.clamp(-1, 4, 9)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-1));
			argumentValues[1].setValue(static_cast<int64_t>(4));
			argumentValues[2].setValue(static_cast<int64_t>(9));
			// method code: math.clamp
			int64_t intValueA;
			int64_t intValueB;
			int64_t intValueC;
			float floatValueA;
			float floatValueB;
			float floatValueC;
			if (argumentValues.size() != 3) {
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 140
	// console.log("math.clamp(10.0, 4.1, 9.3): ", math.clamp(10.0, 4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[1].statements[140];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.clamp(10.0, 4.1, 9.3): "));
		// argumentValues[1] --> returnValue of math.clamp(10.0, 4.1, 9.3)
		// depth = 1 / argument index = 1: math.clamp(10.0, 4.1, 9.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(10.000000f);
			argumentValues[1].setValue(4.100000f);
			argumentValues[2].setValue(9.300000f);
			// method code: math.clamp
			int64_t intValueA;
			int64_t intValueB;
			int64_t intValueC;
			float floatValueA;
			float floatValueB;
			float floatValueC;
			if (argumentValues.size() != 3) {
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 141
	// console.log("math.pow(2, 16): ", math.pow(2, 16))
	{
		const ScriptStatement& statement = scripts[1].statements[141];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.pow(2, 16): "));
		// argumentValues[1] --> returnValue of math.pow(2, 16)
		// depth = 1 / argument index = 1: math.pow(2, 16)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(16));
			// method code: math.pow
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::pow(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::pow(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 142
	// console.log("math.pow(2.0, 16.0): ", math.pow(2.0, 16.0))
	{
		const ScriptStatement& statement = scripts[1].statements[142];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.pow(2.0, 16.0): "));
		// argumentValues[1] --> returnValue of math.pow(2.0, 16.0)
		// depth = 1 / argument index = 1: math.pow(2.0, 16.0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.000000f);
			argumentValues[1].setValue(16.000000f);
			// method code: math.pow
			int64_t intValueA;
			int64_t intValueB;
			float floatValueA;
			float floatValueB;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true &&
				MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(Math::pow(floatValueA, floatValueB));
			} else
			if (MiniScript::getIntegerValue(argumentValues, 0, intValueA, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, intValueB, false) == true) {
				returnValue.setValue(Math::pow(intValueA, intValueB));
			} else {
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 143
	// console.log("math.mod(187, 180): ", math.mod(187, 180))
	{
		const ScriptStatement& statement = scripts[1].statements[143];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.mod(187, 180): "));
		// argumentValues[1] --> returnValue of math.mod(187, 180)
		// depth = 1 / argument index = 1: math.mod(187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(187));
			argumentValues[1].setValue(static_cast<int64_t>(180));
			// method code: math.mod
			float value;
			float range;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
				returnValue.setValue(Math::mod(value, range));
			} else {
				Console::println("ScriptMethodMod::executeMethod(): " + string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 144
	// console.log("math.mod(-187, 180): ", math.mod(-187, 180))
	{
		const ScriptStatement& statement = scripts[1].statements[144];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.mod(-187, 180): "));
		// argumentValues[1] --> returnValue of math.mod(-187, 180)
		// depth = 1 / argument index = 1: math.mod(-187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-187));
			argumentValues[1].setValue(static_cast<int64_t>(180));
			// method code: math.mod
			float value;
			float range;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
				returnValue.setValue(Math::mod(value, range));
			} else {
				Console::println("ScriptMethodMod::executeMethod(): " + string("math.mod") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 145
	// console.log("math.absmod(187, 180): ", math.absmod(187, 180))
	{
		const ScriptStatement& statement = scripts[1].statements[145];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.absmod(187, 180): "));
		// argumentValues[1] --> returnValue of math.absmod(187, 180)
		// depth = 1 / argument index = 1: math.absmod(187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(187));
			argumentValues[1].setValue(static_cast<int64_t>(180));
			// method code: math.absmod
			float value;
			float range;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
				returnValue.setValue(Math::absmod(value, range));
			} else {
				Console::println("ScriptMethodAbsMod::executeMethod(): " + string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 146
	// console.log("math.absmod(-187, 180): ", math.absmod(-187, 180))
	{
		const ScriptStatement& statement = scripts[1].statements[146];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("math.absmod(-187, 180): "));
		// argumentValues[1] --> returnValue of math.absmod(-187, 180)
		// depth = 1 / argument index = 1: math.absmod(-187, 180)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-187));
			argumentValues[1].setValue(static_cast<int64_t>(180));
			// method code: math.absmod
			float value;
			float range;
			if (MiniScript::getFloatValue(argumentValues, 0, value, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, range, false) == true) {
				returnValue.setValue(Math::absmod(value, range));
			} else {
				Console::println("ScriptMethodAbsMod::executeMethod(): " + string("math.absmod") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 147
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[147];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 148
	// console.log("Check transform")
	{
		const ScriptStatement& statement = scripts[1].statements[148];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check transform"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 149
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[149];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 150
	// console.log("$transform = transform(vec3(1,2,3), vec3(2, 3, 4)")
	{
		const ScriptStatement& statement = scripts[1].statements[150];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transform = transform(vec3(1,2,3), vec3(2, 3, 4)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 151
	// setVariable("$transform", transform(vec3(1,2,3), vec3(2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[1].statements[151];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transform"));
		// argumentValues[1] --> returnValue of transform(vec3(1,2,3), vec3(2, 3, 4))
		// depth = 1 / argument index = 1: transform(vec3(1,2,3), vec3(2, 3, 4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1,2,3)
			// argumentValues[1] --> returnValue of vec3(2, 3, 4)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(2));
				argumentValues[1].setValue(static_cast<int64_t>(3));
				argumentValues[2].setValue(static_cast<int64_t>(4));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			// scale
			if (argumentValues.size() >= 2) {
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
					transform.setScale(vec3Value);
				} else {
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 1: vector3 expected");
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
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument " + to_string(i) + ": float expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 152
	// console.log("$transform: ", $transform)
	{
		const ScriptStatement& statement = scripts[1].statements[152];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transform: "));
		// argumentValues[1] --> returnValue of getVariable("$transform")
		// depth = 1 / argument index = 1: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$transform"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 153
	// console.log("transform.setRotationAngle($transform, 1, 90)")
	{
		const ScriptStatement& statement = scripts[1].statements[153];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.setRotationAngle($transform, 1, 90)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 154
	// transform.setRotationAngle($transform, 1, 90)
	{
		const ScriptStatement& statement = scripts[1].statements[154];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$transform")
		argumentValues[1].setValue(static_cast<int64_t>(1));
		argumentValues[2].setValue(static_cast<int64_t>(90));
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$transform"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
				Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
				// assign back
				setVariable("$transform", argumentValues[0], &statement);
				//
				miniScript->startErrorScript(); return;
			}
		} else {
			Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected, @ argument 2: float expected");
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}

	// Statement: 155
	// console.log("transform.getRotationAngle($transform, 1): ", transform.getRotationAngle($transform, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[155];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getRotationAngle($transform, 1): "));
		// argumentValues[1] --> returnValue of transform.getRotationAngle($transform, 1)
		// depth = 1 / argument index = 1: transform.getRotationAngle($transform, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodTransformGetRotationAngle::executeMethod(): " + string("transform.getRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformGetRotationAngle::executeMethod(): " + string("transform.getRotationAngle") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 156
	// console.log("transform.getTranslation($transform): ", transform.getTranslation($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[156];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getTranslation($transform): "));
		// argumentValues[1] --> returnValue of transform.getTranslation($transform)
		// depth = 1 / argument index = 1: transform.getTranslation($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getTranslation
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTranslation());
			} else {
				Console::println("ScriptMethodTransformGetTranslation::executeMethod(): " + string("transform.getTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 157
	// console.log("transform.setTranslation($transform, vec3(-1,-2,-3))")
	{
		const ScriptStatement& statement = scripts[1].statements[157];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.setTranslation($transform, vec3(-1,-2,-3))"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 158
	// transform.setTranslation($transform, vec3(-1,-2,-3))
	{
		const ScriptStatement& statement = scripts[1].statements[158];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$transform")
		// argumentValues[1] --> returnValue of vec3(-1,-2,-3)
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$transform"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 1: vec3(-1, -2, -3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-1));
			argumentValues[1].setValue(static_cast<int64_t>(-2));
			argumentValues[2].setValue(static_cast<int64_t>(-3));
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
				Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
			Console::println("ScriptMethodTransformSetTranslation::executeMethod(): " + string("transform.setTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}

	// Statement: 159
	// console.log("transform.getTranslation($transform): ", transform.getTranslation($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[159];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getTranslation($transform): "));
		// argumentValues[1] --> returnValue of transform.getTranslation($transform)
		// depth = 1 / argument index = 1: transform.getTranslation($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getTranslation
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTranslation());
			} else {
				Console::println("ScriptMethodTransformGetTranslation::executeMethod(): " + string("transform.getTranslation") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 160
	// console.log("transform.getScale($transform): ", transform.getScale($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[160];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getScale($transform): "));
		// argumentValues[1] --> returnValue of transform.getScale($transform)
		// depth = 1 / argument index = 1: transform.getScale($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getScale
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getScale());
			} else {
				Console::println("ScriptMethodTransformGetScale::executeMethod(): " + string("transform.getScale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 161
	// console.log("transform.setScale($transform, vec3(-2,-3,-4))")
	{
		const ScriptStatement& statement = scripts[1].statements[161];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.setScale($transform, vec3(-2,-3,-4))"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 162
	// transform.setScale($transform, vec3(-2,-3,-4))
	{
		const ScriptStatement& statement = scripts[1].statements[162];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$transform")
		// argumentValues[1] --> returnValue of vec3(-2,-3,-4)
		// depth = 1 / argument index = 0: getVariable("$transform")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$transform"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 1: vec3(-2, -3, -4)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(-2));
			argumentValues[1].setValue(static_cast<int64_t>(-3));
			argumentValues[2].setValue(static_cast<int64_t>(-4));
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
				Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
			Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.setScale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
			// assign back
			setVariable("$transform", argumentValues[0], &statement);
			//
			miniScript->startErrorScript(); return;
		}
		// assign back
		setVariable("$transform", argumentValues[0], &statement);
		//
	}

	// Statement: 163
	// console.log("transform.getScale($transform): ", transform.getScale($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[163];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getScale($transform): "));
		// argumentValues[1] --> returnValue of transform.getScale($transform)
		// depth = 1 / argument index = 1: transform.getScale($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getScale
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getScale());
			} else {
				Console::println("ScriptMethodTransformGetScale::executeMethod(): " + string("transform.getScale") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 164
	// console.log("transform.getRotationAxis($transform, 0): ", transform.getRotationAxis($transform, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[164];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getRotationAxis($transform, 0): "));
		// argumentValues[1] --> returnValue of transform.getRotationAxis($transform, 0)
		// depth = 1 / argument index = 1: transform.getRotationAxis($transform, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodTransformGetRotationAxis::executeMethod(): " + string("transform.getRotationAxis") + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformGetRotationAxis::executeMethod(): " + string("transform.getRotationAxis") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 165
	// console.log("transform.multiply($transform, vec3(0,0,0)): ", transform.multiply($transform, vec3(0,0,0)))
	{
		const ScriptStatement& statement = scripts[1].statements[165];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.multiply($transform, vec3(0,0,0)): "));
		// argumentValues[1] --> returnValue of transform.multiply($transform, vec3(0,0,0))
		// depth = 1 / argument index = 1: transform.multiply($transform, vec3(0,0,0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// argumentValues[1] --> returnValue of vec3(0,0,0)
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.multiply
			Transform transform;
			Vector3 vec3;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
				returnValue.setValue(transform.getTransformMatrix() * vec3);
			} else {
				Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.multiply") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 166
	// console.log("transform.rotate($transform, vec3(0,0,1)): ", transform.rotate($transform, vec3(0,0,1)))
	{
		const ScriptStatement& statement = scripts[1].statements[166];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.rotate($transform, vec3(0,0,1)): "));
		// argumentValues[1] --> returnValue of transform.rotate($transform, vec3(0,0,1))
		// depth = 1 / argument index = 1: transform.rotate($transform, vec3(0,0,1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// argumentValues[1] --> returnValue of vec3(0,0,1)
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.rotate") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 167
	// console.log("transform.getTransformMatrix($transform): ", transform.getTransformMatrix($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[167];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getTransformMatrix($transform): "));
		// argumentValues[1] --> returnValue of transform.getTransformMatrix($transform)
		// depth = 1 / argument index = 1: transform.getTransformMatrix($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getTransformMatrix
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTransformMatrix());
			} else {
				Console::println("ScriptMethodTransformGetTransformMatrix::executeMethod(): " + string("transform.getTransformMatrix") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 168
	// console.log("transform.getRotationsQuaternion($transform): ", transform.getRotationsQuaternion($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[168];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform.getRotationsQuaternion($transform): "));
		// argumentValues[1] --> returnValue of transform.getRotationsQuaternion($transform)
		// depth = 1 / argument index = 1: transform.getRotationsQuaternion($transform)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// depth = 2 / argument index = 0: getVariable("$transform")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transform"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getRotationsQuaternion
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getRotationsQuaternion());
			} else {
				Console::println("ScriptMethodTransformGetRotationsQuaternion::executeMethod(): " + string("transform.getRotationsQuaternion") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 169
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[169];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 170
	// console.log("Check string functions")
	{
		const ScriptStatement& statement = scripts[1].statements[170];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check string functions"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 171
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[171];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 172
	// console.log(space(0), "1")
	{
		const ScriptStatement& statement = scripts[1].statements[172];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(0)
		argumentValues[1].setValue(string("1"));
		// depth = 1 / argument index = 0: space(0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(0));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 173
	// console.log(space(2), "1.1")
	{
		const ScriptStatement& statement = scripts[1].statements[173];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(2)
		argumentValues[1].setValue(string("1.1"));
		// depth = 1 / argument index = 0: space(2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 174
	// console.log(space(2), "1.2")
	{
		const ScriptStatement& statement = scripts[1].statements[174];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(2)
		argumentValues[1].setValue(string("1.2"));
		// depth = 1 / argument index = 0: space(2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 175
	// console.log(toUpperCase("xxxyyyzzz"))
	{
		const ScriptStatement& statement = scripts[1].statements[175];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of toUpperCase("xxxyyyzzz")
		// depth = 1 / argument index = 0: toUpperCase("xxxyyyzzz")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("xxxyyyzzz"));
			// method code: toUpperCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toUpperCase(stringValue));
			} else {
				Console::println("ScriptMethodToUpperCase::executeMethod(): " + string("toUpperCase") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 176
	// console.log(toLowerCase("XXXYYYZZZ"))
	{
		const ScriptStatement& statement = scripts[1].statements[176];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of toLowerCase("XXXYYYZZZ")
		// depth = 1 / argument index = 0: toLowerCase("XXXYYYZZZ")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("XXXYYYZZZ"));
			// method code: toLowerCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toLowerCase(stringValue));
			} else {
				Console::println("ScriptMethodToLowerCase::executeMethod(): " + string("toLowerCase") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 177
	// console.log(concatenate("abc", "def", "ghi"))
	{
		const ScriptStatement& statement = scripts[1].statements[177];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of concatenate("abc", "def", "ghi")
		// depth = 1 / argument index = 0: concatenate("abc", "def", "ghi")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("abc"));
			argumentValues[1].setValue(string("def"));
			argumentValues[2].setValue(string("ghi"));
			// method code: concatenate
			string result;
			for (auto& argumentValue: argumentValues) {
				result+= argumentValue.getValueString();
			}
			returnValue.setValue(result);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 178
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[178];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 179
	// console.log("Check string functions (Operators)")
	{
		const ScriptStatement& statement = scripts[1].statements[179];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check string functions (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 180
	// console.log(add("abc",add("def", "ghi")))
	{
		const ScriptStatement& statement = scripts[1].statements[180];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("abc",add("def", "ghi"))
		// depth = 1 / argument index = 0: add("abc", add("def", "ghi"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("abc"));
			// argumentValues[1] --> returnValue of add("def", "ghi")
			// depth = 2 / argument index = 1: add("def", "ghi")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("def"));
				argumentValues[1].setValue(string("ghi"));
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

	// Statement: 181
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[181];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 182
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[182];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 183
	// console.log("Variable")
	{
		const ScriptStatement& statement = scripts[1].statements[183];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Variable"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 184
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[184];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 185
	// setVariable("$variable", string("1234"))
	{
		const ScriptStatement& statement = scripts[1].statements[185];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$variable"));
		// argumentValues[1] --> returnValue of string("1234")
		// depth = 1 / argument index = 1: string("1234")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("1234"));
			// method code: string
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(stringValue);
			} else {
				Console::println("ScriptMethodString::executeMethod(): " + string("string") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
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

	// Statement: 186
	// console.log(getVariable("$variable"))
	{
		const ScriptStatement& statement = scripts[1].statements[186];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$variable")
		// depth = 1 / argument index = 0: getVariable("$variable")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$variable"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 187
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[187];
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

	// Statement: 188
	// console.log("Lets check forTime")
	{
		const ScriptStatement& statement = scripts[1].statements[188];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forTime"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 189
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[189];
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

	// Statement: 190
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[190];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
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

	// Statement: 191
	miniscript_statement_191:
	// forTime(2000)
	{
		const ScriptStatement& statement = scripts[1].statements[191];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
		// method code: forTime
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
			Console::println("ScriptMethodForTime::executeMethod(): " + string("forTime") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: integer expected");
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
				goto miniscript_statement_196;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 192
	miniscript_statement_192:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[1].statements[192];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(": Hello World"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 193
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[1].statements[193];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
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

	// Statement: 194
	miniscript_statement_194:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[194];
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

	// Statement: 195
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[195];
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
				goto miniscript_statement_191;
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

	// Statement: 196
	miniscript_statement_196:
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[196];
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

	// Statement: 197
	// console.log("Lets check forCondition")
	{
		const ScriptStatement& statement = scripts[1].statements[197];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forCondition"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 198
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[198];
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

	// Statement: 199
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[199];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
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

	// Statement: 200
	miniscript_statement_200:
	// forCondition(notequal($i, 6))
	{
		const ScriptStatement& statement = scripts[1].statements[200];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of notequal($i, 6)
		// depth = 1 / argument index = 0: notequal($i, 6)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(6));
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
			// method code: notequal
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodNotEqual::executeMethod(): " + string("notequal") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: mixed expected, @ argument 1: mixed expected");
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
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
				goto miniscript_statement_205;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 201
	miniscript_statement_201:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[1].statements[201];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(": Hello World"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 202
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[1].statements[202];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
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

	// Statement: 203
	miniscript_statement_203:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[203];
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

	// Statement: 204
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[204];
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
				goto miniscript_statement_200;
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

	// Statement: 205
	miniscript_statement_205:
	// console.log("i -> ", $i)
	{
		const ScriptStatement& statement = scripts[1].statements[205];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> "));
		// argumentValues[1] --> returnValue of getVariable("$i")
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 206
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[206];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 207
	// console.log("Lets check forCondition with if/elseif/else")
	{
		const ScriptStatement& statement = scripts[1].statements[207];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forCondition with if/elseif/else"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 208
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[208];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 209
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[209];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
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

	// Statement: 210
	miniscript_statement_210:
	// forCondition(lesser($i, 5))
	{
		const ScriptStatement& statement = scripts[1].statements[210];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, 5)
		// depth = 1 / argument index = 0: lesser($i, 5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(5));
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
				goto miniscript_statement_225;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 211
	miniscript_statement_211:
	// console.log($i, ":")
	{
		const ScriptStatement& statement = scripts[1].statements[211];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(":"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 212
	// if(equals($i, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[212];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 0)
		// depth = 1 / argument index = 0: equals($i, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(0));
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
				goto miniscript_statement_214;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 213
	miniscript_statement_213:
	// console.log("i -> 0")
	{
		const ScriptStatement& statement = scripts[1].statements[213];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 0"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 214
	miniscript_statement_214:
	// elseif(equals($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[214];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 1)
		// depth = 1 / argument index = 0: equals($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_216;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 215
	miniscript_statement_215:
	// console.log("i -> 1")
	{
		const ScriptStatement& statement = scripts[1].statements[215];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 1"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 216
	miniscript_statement_216:
	// elseif(equals($i, 2))
	{
		const ScriptStatement& statement = scripts[1].statements[216];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 2)
		// depth = 1 / argument index = 0: equals($i, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(2));
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_218;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 217
	miniscript_statement_217:
	// console.log("i -> 2")
	{
		const ScriptStatement& statement = scripts[1].statements[217];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 2"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 218
	miniscript_statement_218:
	// elseif(equals($i, 3))
	{
		const ScriptStatement& statement = scripts[1].statements[218];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 3)
		// depth = 1 / argument index = 0: equals($i, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(3));
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_220;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 219
	miniscript_statement_219:
	// console.log("i -> 3")
	{
		const ScriptStatement& statement = scripts[1].statements[219];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 3"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 220
	miniscript_statement_220:
	// else()
	{
		const ScriptStatement& statement = scripts[1].statements[220];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: else
		if (miniScript->getScriptState().conditionStack.empty() == true) {
			Console::println("ScriptMethodElse::executeMethod(): else without if");
			miniScript->startErrorScript(); return;
		} else {
			auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
			if (conditionStackElement == true) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_222;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 221
	miniscript_statement_221:
	// console.log("else: ", $i)
	{
		const ScriptStatement& statement = scripts[1].statements[221];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("else: "));
		// argumentValues[1] --> returnValue of getVariable("$i")
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 222
	miniscript_statement_222:
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[222];
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

	// Statement: 223
	miniscript_statement_223:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[223];
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

	// Statement: 224
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[224];
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
				goto miniscript_statement_210;
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

	// Statement: 225
	miniscript_statement_225:
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[225];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
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

	// Statement: 226
	// setVariable("$j", 2)
	{
		const ScriptStatement& statement = scripts[1].statements[226];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$j"));
		argumentValues[1].setValue(static_cast<int64_t>(2));
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

	// Statement: 227
	// setVariable("$k", 3)
	{
		const ScriptStatement& statement = scripts[1].statements[227];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$k"));
		argumentValues[1].setValue(static_cast<int64_t>(3));
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

	// Statement: 228
	// if(or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k)))
	{
		const ScriptStatement& statement = scripts[1].statements[228];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k))
		// depth = 1 / argument index = 0: or(equals(getVariable("$i"), $j), equals(getVariable("$i"), $k))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of equals(getVariable("$i"), $j)
			// argumentValues[1] --> returnValue of equals(getVariable("$i"), $k)
			// depth = 2 / argument index = 0: equals(getVariable("$i"), $j)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of getVariable("$j")
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
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
				// depth = 3 / argument index = 1: getVariable("$j")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
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
			// depth = 2 / argument index = 1: equals(getVariable("$i"), $k)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of getVariable("$k")
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
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
				// depth = 3 / argument index = 1: getVariable("$k")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
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
			// method code: or
			if (argumentValues.size() != 2) {
				returnValue.setValue(false);
				Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected, @ argument 1: boolean expected");
				miniScript->startErrorScript(); return;
			} else {
				returnValue.setValue(false);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
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
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->getScriptState().conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_230;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 229
	miniscript_statement_229:
	// console.log("This should not happen, but look ok in preprocessor processed output")
	{
		const ScriptStatement& statement = scripts[1].statements[229];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("This should not happen, but look ok in preprocessor processed output"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 230
	miniscript_statement_230:
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[230];
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

	// Statement: 231
	miniscript_statement_231:
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[231];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 232
	// console.log(add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")")))))
	{
		const ScriptStatement& statement = scripts[1].statements[232];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")"))))
		// depth = 1 / argument index = 0: add("Test: string concatenation with brackets in string literals: ", add($i,add("(",add($j, ")"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("Test: string concatenation with brackets in string literals: "));
			// argumentValues[1] --> returnValue of add($i,add("(",add($j, ")")))
			// depth = 2 / argument index = 1: add($i, add("(",add($j, ")")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of add("(",add($j, ")"))
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
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
				// depth = 3 / argument index = 1: add("(", add($j, ")"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("("));
					// argumentValues[1] --> returnValue of add($j, ")")
					// depth = 4 / argument index = 1: add($j, ")")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of getVariable("$j")
						argumentValues[1].setValue(string(")"));
						// depth = 5 / argument index = 0: getVariable("$j")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues;
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
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

	// Statement: 233
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[233];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 234
	// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), " = 17")
	{
		const ScriptStatement& statement = scripts[1].statements[234];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): "));
		// argumentValues[1] --> returnValue of add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5)))
		argumentValues[2].setValue(string(" = 17"));
		// depth = 1 / argument index = 1: add(div(add(4.0, 2.0), 2.0), mul(div(20.0, 10.0), add(2.0, 5)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of div(add(4.0, 2.0), 2.0)
			// argumentValues[1] --> returnValue of mul(div(20.0, 10.0), add(2.0, 5))
			// depth = 2 / argument index = 0: div(add(4.0, 2.0), 2.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of add(4.0, 2.0)
				argumentValues[1].setValue(2.000000f);
				// depth = 3 / argument index = 0: add(4.0, 2.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(4.000000f);
					argumentValues[1].setValue(2.000000f);
					// method code: add
					MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
				}
				// method code: div
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			// depth = 2 / argument index = 1: mul(div(20.0, 10.0), add(2.0, 5))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of div(20.0, 10.0)
				// argumentValues[1] --> returnValue of add(2.0, 5)
				// depth = 3 / argument index = 0: div(20.0, 10.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(20.000000f);
					argumentValues[1].setValue(10.000000f);
					// method code: div
					MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
				}
				// depth = 3 / argument index = 1: add(2.0, 5)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(2.000000f);
					argumentValues[1].setValue(static_cast<int64_t>(5));
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
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 235
	// script.stop()
	{
		const ScriptStatement& statement = scripts[1].statements[235];
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

	// Statement: 236
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[236];
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

void MiniScriptBaseTest::on_error(int miniScriptGotoStatementIdx) {
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
	// console.log("base-test: Error")
	{
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("base-test: Error"));
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


/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
