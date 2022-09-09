#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;

MiniScriptTest::MiniScriptTest(): MiniScript() {
	initializeNative();
}

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/
void MiniScriptTest::initializeNative() {
	setNative(true);
	setHash("fc2d9de551deb52ee2c47c602b2a11ccde9f1ba52315269896ce7fd7b9ebd90c");
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
						.statement = "console.log(\"------------\")",
						.executableStatement = "console.log(\"------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 4,
						.statementIdx = 1,
						.statement = "console.log(\"Initialize\")",
						.executableStatement = "console.log(\"Initialize\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 5,
						.statementIdx = 2,
						.statement = "console.log(\"------------\")",
						.executableStatement = "console.log(\"------------\")",
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
				.argumentNames = {
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
				.argumentNames = {
					"$value"
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
				.argumentNames = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 24,
				.condition = "nothing",
				.executableCondition = "nothing",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 25,
						.statementIdx = 0,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 1,
						.statement = "console.log(\"Nothing\")",
						.executableStatement = "console.log(\"Nothing\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 2,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 3,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 29,
						.statementIdx = 4,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 30,
						.statementIdx = 5,
						.statement = "console.log(\"Check bool operations\")",
						.executableStatement = "console.log(\"Check bool operations\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 6,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 7,
						.statement = "console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						.executableStatement = "console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 8,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 9,
						.statement = "console.log(\"Check int computation\")",
						.executableStatement = "console.log(\"Check int computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 35,
						.statementIdx = 10,
						.statement = "console.log(\"-----------------------\")",
						.executableStatement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 36,
						.statementIdx = 11,
						.statement = "console.log(\"sub(add(1, 2, 3), 1)): \", sub(add(1, 2, 3), 1)))",
						.executableStatement = "console.log(\"sub(add(1, 2, 3), 1)): \", sub(add(1, 2, 3), 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 37,
						.statementIdx = 12,
						.statement = "console.log(\"div(20, 2): \", div(20, 2))",
						.executableStatement = "console.log(\"div(20, 2): \", div(20, 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 38,
						.statementIdx = 13,
						.statement = "console.log(\"mul(11, 10): \", mul(11, 10))",
						.executableStatement = "console.log(\"mul(11, 10): \", mul(11, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 14,
						.statement = "console.log(\"greater(2, 1): \", greater(2, 1))",
						.executableStatement = "console.log(\"greater(2, 1): \", greater(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 15,
						.statement = "console.log(\"lesser(2, 1): \", lesser(2, 1))",
						.executableStatement = "console.log(\"lesser(2, 1): \", lesser(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 41,
						.statementIdx = 16,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 17,
						.statement = "console.log(\"Check int computation (Operators)\")",
						.executableStatement = "console.log(\"Check int computation (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 18,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 19,
						.statement = "console.log(\"1 + 2 + 3 - 1: \", 1 + 2 + 3 - 1)",
						.executableStatement = "console.log(\"1 + 2 + 3 - 1: \",sub(add(1,add(2, 3)), 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 20,
						.statement = "console.log(\"20 / 2: \", 20 / 2)",
						.executableStatement = "console.log(\"20 / 2: \",div(20, 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 21,
						.statement = "console.log(\"11 * 10: \", 11 * 10)",
						.executableStatement = "console.log(\"11 * 10: \",mul(11, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 47,
						.statementIdx = 22,
						.statement = "console.log(\"2 > 1: \", 2 > 1)",
						.executableStatement = "console.log(\"2 > 1: \",greater(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 23,
						.statement = "console.log(\"2 < 1: \", 2 < 1)",
						.executableStatement = "console.log(\"2 < 1: \",lesser(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 24,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 50,
						.statementIdx = 25,
						.statement = "console.log(\"Check float computation\")",
						.executableStatement = "console.log(\"Check float computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 26,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 27,
						.statement = "console.log(\"sub(add(1.1, 2.2, 3.3), 1.2)): \", sub(add(1.1, 2.2, 3.3), 1.2)))",
						.executableStatement = "console.log(\"sub(add(1.1, 2.2, 3.3), 1.2)): \", sub(add(1.1, 2.2, 3.3), 1.2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 28,
						.statement = "console.log(\"div(20, 1.5): \", div(20, 1.5))",
						.executableStatement = "console.log(\"div(20, 1.5): \", div(20, 1.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 29,
						.statement = "console.log(\"mul(11.5, 10.5): \", mul(11.5, 10.5))",
						.executableStatement = "console.log(\"mul(11.5, 10.5): \", mul(11.5, 10.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 30,
						.statement = "console.log(\"greater(2.2, 1.3): \", greater(2.2, 1.3))",
						.executableStatement = "console.log(\"greater(2.2, 1.3): \", greater(2.2, 1.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 31,
						.statement = "console.log(\"lesser(2.5, 1.2): \", lesser(2.5, 1.2))",
						.executableStatement = "console.log(\"lesser(2.5, 1.2): \", lesser(2.5, 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 57,
						.statementIdx = 32,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 33,
						.statement = "console.log(\"Check float computation (Operators)\")",
						.executableStatement = "console.log(\"Check float computation (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 34,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 60,
						.statementIdx = 35,
						.statement = "console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \", (1.1 + 2.2 + 3.3) - 1.2)",
						.executableStatement = "console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \",sub(add(1.1,add(2.2, 3.3)), 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 36,
						.statement = "console.log(\"20 / 1.5: \", 20 / 1.5)",
						.executableStatement = "console.log(\"20 / 1.5: \",div(20, 1.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 37,
						.statement = "console.log(\"11.5 * 10.5: \", 11.5 * 10.5)",
						.executableStatement = "console.log(\"11.5 * 10.5: \",mul(11.5, 10.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 38,
						.statement = "console.log(\"2.2 > 1.3: \", 2.2 > 1.3)",
						.executableStatement = "console.log(\"2.2 > 1.3: \",greater(2.2, 1.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 64,
						.statementIdx = 39,
						.statement = "console.log(\"2.5 < 1.2: \", 2.5 < 1.2)",
						.executableStatement = "console.log(\"2.5 < 1.2: \",lesser(2.5, 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 65,
						.statementIdx = 40,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 66,
						.statementIdx = 41,
						.statement = "console.log(\"Check vector2 math\")",
						.executableStatement = "console.log(\"Check vector2 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 67,
						.statementIdx = 42,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 43,
						.statement = "console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						.executableStatement = "console.log(\"vec2.computeLength(vec2(20, 10)): \", vec2.computeLength(vec2(20, 10)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 44,
						.statement = "console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						.executableStatement = "console.log(\"vec2.computeLengthSquared(vec2(20, 10)): \", vec2.computeLengthSquared(vec2(20, 10)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 70,
						.statementIdx = 45,
						.statement = "console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						.executableStatement = "console.log(\"vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): \", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 46,
						.statement = "console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.normalize(vec2(1, 2)): \", vec2.normalize(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 47,
						.statement = "console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.getX(vec2(1, 2)): \", vec2.getX(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 48,
						.statement = "console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						.executableStatement = "console.log(\"vec2.getY(vec2(1, 2)): \", vec2.getY(vec2(1, 2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 74,
						.statementIdx = 49,
						.statement = "console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \", vec2(1.1, 2.2) - vec2(1.2, 1.0))",
						.executableStatement = "console.log(\"vec2(1.1, 2.2) - vec2(1.2, 1.0): \",sub(vec2(1.1, 2.2), vec2(1.2, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 75,
						.statementIdx = 50,
						.statement = "console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \", vec2(20, 10) / vec2(1.5, 2.5))",
						.executableStatement = "console.log(\"vec2(20, 10) / vec2(1.5, 2.5): \",div(vec2(20, 10), vec2(1.5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 76,
						.statementIdx = 51,
						.statement = "console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \", vec2(20, 10) * vec2(1.5, 2.5))",
						.executableStatement = "console.log(\"vec2(20, 10) * vec2(1.5, 2.5)): \",mul(vec2(20, 10), vec2(1.5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 52,
						.statement = "console.log(\"vec2(20, 10) / 2): \", vec2(20, 10) / 2)",
						.executableStatement = "console.log(\"vec2(20, 10) / 2): \",div(vec2(20, 10), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 78,
						.statementIdx = 53,
						.statement = "console.log(\"vec2(20, 10) * 2): \", vec2(20, 10) * 2)",
						.executableStatement = "console.log(\"vec2(20, 10) * 2): \",mul(vec2(20, 10), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 79,
						.statementIdx = 54,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 80,
						.statementIdx = 55,
						.statement = "console.log(\"Check vector3 math\")",
						.executableStatement = "console.log(\"Check vector3 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 81,
						.statementIdx = 56,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 82,
						.statementIdx = 57,
						.statement = "console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						.executableStatement = "console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 83,
						.statementIdx = 58,
						.statement = "console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						.executableStatement = "console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 84,
						.statementIdx = 59,
						.statement = "console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						.executableStatement = "console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 85,
						.statementIdx = 60,
						.statement = "console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						.executableStatement = "console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 86,
						.statementIdx = 61,
						.statement = "console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 87,
						.statementIdx = 62,
						.statement = "console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						.executableStatement = "console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 88,
						.statementIdx = 63,
						.statement = "console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 89,
						.statementIdx = 64,
						.statement = "console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 90,
						.statementIdx = 65,
						.statement = "console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						.executableStatement = "console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 91,
						.statementIdx = 66,
						.statement = "console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \", vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0))",
						.executableStatement = "console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \",sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 92,
						.statementIdx = 67,
						.statement = "console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \", vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5))",
						.executableStatement = "console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \",div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 93,
						.statementIdx = 68,
						.statement = "console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \", vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5))",
						.executableStatement = "console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \",mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 94,
						.statementIdx = 69,
						.statement = "console.log(\"vec3(20, 10, 5) / 2): \", vec3(20, 10, 5) / 2)",
						.executableStatement = "console.log(\"vec3(20, 10, 5) / 2): \",div(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 95,
						.statementIdx = 70,
						.statement = "console.log(\"vec3(20, 10, 5) * 2): \", vec3(20, 10, 5) * 2)",
						.executableStatement = "console.log(\"vec3(20, 10, 5) * 2): \",mul(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 96,
						.statementIdx = 71,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 97,
						.statementIdx = 72,
						.statement = "console.log(\"Check vector4 math\")",
						.executableStatement = "console.log(\"Check vector4 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 98,
						.statementIdx = 73,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 99,
						.statementIdx = 74,
						.statement = "console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						.executableStatement = "console.log(\"vec4.computeLength(vec4(20, 10, 5, 2.5)): \", vec4.computeLength(vec4(20, 10, 5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 100,
						.statementIdx = 75,
						.statement = "console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						.executableStatement = "console.log(\"vec4.computeLengthSquared(vec3(20, 10, 5)): \", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 101,
						.statementIdx = 76,
						.statement = "console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						.executableStatement = "console.log(\"vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): \", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 102,
						.statementIdx = 77,
						.statement = "console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.normalize(vec4(1, 2, 3, 4)): \", vec4.normalize(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 103,
						.statementIdx = 78,
						.statement = "console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getX(vec4(1, 2, 3, 4)): \", vec4.getX(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 104,
						.statementIdx = 79,
						.statement = "console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getY(vec4(1, 2, 3, 4)): \", vec4.getY(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 105,
						.statementIdx = 80,
						.statement = "console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getZ(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 106,
						.statementIdx = 81,
						.statement = "console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.executableStatement = "console.log(\"vec4.getW(vec4(1, 2, 3, 4)): \", vec4.getZ(vec4(1, 2, 3, 4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 107,
						.statementIdx = 82,
						.statement = "console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \", vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0))",
						.executableStatement = "console.log(\"vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): \",sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 108,
						.statementIdx = 83,
						.statement = "console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \", vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1))",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): \",div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 109,
						.statementIdx = 84,
						.statement = "console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \", vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1))",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): \",mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 110,
						.statementIdx = 85,
						.statement = "console.log(\"vec4(20, 10, 5, 1) / 2): \", vec4(20, 10, 5, 1) / 2)",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) / 2): \",div(vec4(20, 10, 5, 1), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 111,
						.statementIdx = 86,
						.statement = "console.log(\"vec4(20, 10, 5, 1) * 2): \", vec4(20, 10, 5, 1) * 2)",
						.executableStatement = "console.log(\"vec4(20, 10, 5, 1) * 2): \",mul(vec4(20, 10, 5, 1), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 112,
						.statementIdx = 87,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 113,
						.statementIdx = 88,
						.statement = "console.log(\"Check quaternion math\")",
						.executableStatement = "console.log(\"Check quaternion math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 114,
						.statementIdx = 89,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 115,
						.statementIdx = 90,
						.statement = "console.log(\"quaternion.identity(): \", quaternion.identity())",
						.executableStatement = "console.log(\"quaternion.identity(): \", quaternion.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 116,
						.statementIdx = 91,
						.statement = "console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.executableStatement = "console.log(\"quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 117,
						.statementIdx = 92,
						.statement = "console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 118,
						.statementIdx = 93,
						.statement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 119,
						.statementIdx = 94,
						.statement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.executableStatement = "console.log(\"quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 120,
						.statementIdx = 95,
						.statement = "console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 121,
						.statementIdx = 96,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 122,
						.statementIdx = 97,
						.statement = "console.log(\"Check matrix4x4 math\")",
						.executableStatement = "console.log(\"Check matrix4x4 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 123,
						.statementIdx = 98,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 124,
						.statementIdx = 99,
						.statement = "console.log(\"mat4.identity(): \", mat4.identity())",
						.executableStatement = "console.log(\"mat4.identity(): \", mat4.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 125,
						.statementIdx = 100,
						.statement = "console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						.executableStatement = "console.log(\"mat4.translate(vec3(1.0, 2.0, 3.0)): \", mat4.translate(vec3(1.0, 2.0, 3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 126,
						.statementIdx = 101,
						.statement = "console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.executableStatement = "console.log(\"mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): \", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 127,
						.statementIdx = 102,
						.statement = "console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						.executableStatement = "console.log(\"mat4.scale(vec3(1.0, 2.0, 3.0)): \", mat4.scale(vec3(1.0, 2.0, 3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 128,
						.statementIdx = 103,
						.statement = "console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						.executableStatement = "console.log(\"mat4.scale(3.0): \", mat4.scale(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 129,
						.statementIdx = 104,
						.statement = "console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						.executableStatement = "console.log(\"mat4.invert(mat4.scale(3.0)): \", mat4.invert(mat4.scale(3.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 130,
						.statementIdx = 105,
						.statement = "console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): \", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 131,
						.statementIdx = 106,
						.statement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 132,
						.statementIdx = 107,
						.statement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): \", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 133,
						.statementIdx = 108,
						.statement = "console.log(\"mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): \", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))",
						.executableStatement = "console.log(\"mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): \", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 134,
						.statementIdx = 109,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 135,
						.statementIdx = 110,
						.statement = "console.log(\"Check matrix3x3 math\")",
						.executableStatement = "console.log(\"Check matrix3x3 math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 136,
						.statementIdx = 111,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 137,
						.statementIdx = 112,
						.statement = "console.log(\"mat3.identity(): \", mat3.identity())",
						.executableStatement = "console.log(\"mat3.identity(): \", mat3.identity())",
						.gotoStatementIdx = -1
					},
					{
						.line = 138,
						.statementIdx = 113,
						.statement = "console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.translate(vec2(1.0, 2.0)): \", mat3.translate(vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 139,
						.statementIdx = 114,
						.statement = "console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						.executableStatement = "console.log(\"mat3.rotate(90.0): \", mat3.rotate(90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 140,
						.statementIdx = 115,
						.statement = "console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						.executableStatement = "console.log(\"mat3.rotateAroundTextureCenter(90.0): \", mat3.rotateAroundTextureCenter(90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 141,
						.statementIdx = 116,
						.statement = "console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						.executableStatement = "console.log(\"mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): \", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 142,
						.statementIdx = 117,
						.statement = "console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.scale(vec2(1.0, 2.0)): \", mat3.scale(vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 143,
						.statementIdx = 118,
						.statement = "console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						.executableStatement = "console.log(\"mat3.scale(3.0): \", mat3.scale(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 144,
						.statementIdx = 119,
						.statement = "console.log(\"mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): \", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))",
						.executableStatement = "console.log(\"mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): \", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 145,
						.statementIdx = 120,
						.statement = "console.log(\"mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): \", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))",
						.executableStatement = "console.log(\"mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): \", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 146,
						.statementIdx = 121,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 147,
						.statementIdx = 122,
						.statement = "console.log(\"Check additional math\")",
						.executableStatement = "console.log(\"Check additional math\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 148,
						.statementIdx = 123,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 149,
						.statementIdx = 124,
						.statement = "console.log(\"math.PI(): \", math.PI())",
						.executableStatement = "console.log(\"math.PI(): \", math.PI())",
						.gotoStatementIdx = -1
					},
					{
						.line = 150,
						.statementIdx = 125,
						.statement = "console.log(\"math.EPSILON(): \", math.EPSILON())",
						.executableStatement = "console.log(\"math.EPSILON(): \", math.EPSILON())",
						.gotoStatementIdx = -1
					},
					{
						.line = 151,
						.statementIdx = 126,
						.statement = "console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						.executableStatement = "console.log(\"math.DEG2RAD(): \", math.DEG2RAD())",
						.gotoStatementIdx = -1
					},
					{
						.line = 152,
						.statementIdx = 127,
						.statement = "console.log(\"math.G(): \", math.G())",
						.executableStatement = "console.log(\"math.G(): \", math.G())",
						.gotoStatementIdx = -1
					},
					{
						.line = 153,
						.statementIdx = 128,
						.statement = "console.log(\"math.acos(0.0): \", math.acos(0.0))",
						.executableStatement = "console.log(\"math.acos(0.0): \", math.acos(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 154,
						.statementIdx = 129,
						.statement = "console.log(\"math.asin(1.0): \", math.asin(1.0))",
						.executableStatement = "console.log(\"math.asin(1.0): \", math.asin(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 155,
						.statementIdx = 130,
						.statement = "console.log(\"math.atan(1.0): \", math.atan(1.0))",
						.executableStatement = "console.log(\"math.atan(1.0): \", math.atan(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 156,
						.statementIdx = 131,
						.statement = "console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						.executableStatement = "console.log(\"math.atan2(-1.0, -1.0): \", math.atan2(-1.0, -1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 157,
						.statementIdx = 132,
						.statement = "console.log(\"math.floor(2.87): \", math.floor(2.87))",
						.executableStatement = "console.log(\"math.floor(2.87): \", math.floor(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 158,
						.statementIdx = 133,
						.statement = "console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						.executableStatement = "console.log(\"math.ceil(2.87): \", math.ceil(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 159,
						.statementIdx = 134,
						.statement = "console.log(\"math.round(2.37): \", math.round(2.37))",
						.executableStatement = "console.log(\"math.round(2.37): \", math.round(2.37))",
						.gotoStatementIdx = -1
					},
					{
						.line = 160,
						.statementIdx = 135,
						.statement = "console.log(\"math.round(2.87): \", math.round(2.87))",
						.executableStatement = "console.log(\"math.round(2.87): \", math.round(2.87))",
						.gotoStatementIdx = -1
					},
					{
						.line = 161,
						.statementIdx = 136,
						.statement = "console.log(\"math.cos(0.0): \", math.cos(0.0))",
						.executableStatement = "console.log(\"math.cos(0.0): \", math.cos(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 162,
						.statementIdx = 137,
						.statement = "console.log(\"math.sin(0.0): \", math.sin(0.0))",
						.executableStatement = "console.log(\"math.sin(0.0): \", math.sin(0.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 163,
						.statementIdx = 138,
						.statement = "console.log(\"math.tan(1.0): \", math.tan(1.0))",
						.executableStatement = "console.log(\"math.tan(1.0): \", math.tan(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 164,
						.statementIdx = 139,
						.statement = "console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						.executableStatement = "console.log(\"math.sqrt(9.0): \", math.sqrt(9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 165,
						.statementIdx = 140,
						.statement = "console.log(\"math.random(): \", math.random())",
						.executableStatement = "console.log(\"math.random(): \", math.random())",
						.gotoStatementIdx = -1
					},
					{
						.line = 166,
						.statementIdx = 141,
						.statement = "console.log(\"math.exp(1.0): \", math.exp(1.0))",
						.executableStatement = "console.log(\"math.exp(1.0): \", math.exp(1.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 167,
						.statementIdx = 142,
						.statement = "console.log(\"math.log(2.0): \", math.log(2.0))",
						.executableStatement = "console.log(\"math.log(2.0): \", math.log(2.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 168,
						.statementIdx = 143,
						.statement = "console.log(\"math.sign(-2): \", math.sign(-2))",
						.executableStatement = "console.log(\"math.sign(-2): \", math.sign(-2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 169,
						.statementIdx = 144,
						.statement = "console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						.executableStatement = "console.log(\"math.sign(-2.0): \", math.sign(-2.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 170,
						.statementIdx = 145,
						.statement = "console.log(\"math.square(3): \", math.square(3))",
						.executableStatement = "console.log(\"math.square(3): \", math.square(3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 171,
						.statementIdx = 146,
						.statement = "console.log(\"math.square(3.0): \", math.square(3.0))",
						.executableStatement = "console.log(\"math.square(3.0): \", math.square(3.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 172,
						.statementIdx = 147,
						.statement = "console.log(\"math.min(4, 9): \", math.min(4, 9))",
						.executableStatement = "console.log(\"math.min(4, 9): \", math.min(4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 173,
						.statementIdx = 148,
						.statement = "console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						.executableStatement = "console.log(\"math.min(4.1, 9.3): \", math.min(4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 174,
						.statementIdx = 149,
						.statement = "console.log(\"math.max(4, 9): \", math.max(4, 9))",
						.executableStatement = "console.log(\"math.max(4, 9): \", math.max(4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 175,
						.statementIdx = 150,
						.statement = "console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						.executableStatement = "console.log(\"math.max(4.1, 9.3): \", math.max(4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 176,
						.statementIdx = 151,
						.statement = "console.log(\"math.abs(-9): \", math.abs(-9))",
						.executableStatement = "console.log(\"math.abs(-9): \", math.abs(-9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 177,
						.statementIdx = 152,
						.statement = "console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						.executableStatement = "console.log(\"math.abs(-9.3): \", math.abs(-9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 178,
						.statementIdx = 153,
						.statement = "console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						.executableStatement = "console.log(\"math.clamp(-1, 4, 9): \", math.clamp(-1, 4, 9))",
						.gotoStatementIdx = -1
					},
					{
						.line = 179,
						.statementIdx = 154,
						.statement = "console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						.executableStatement = "console.log(\"math.clamp(10.0, 4.1, 9.3): \", math.clamp(10.0, 4.1, 9.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 180,
						.statementIdx = 155,
						.statement = "console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						.executableStatement = "console.log(\"math.pow(2, 16): \", math.pow(2, 16))",
						.gotoStatementIdx = -1
					},
					{
						.line = 181,
						.statementIdx = 156,
						.statement = "console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						.executableStatement = "console.log(\"math.pow(2.0, 16.0): \", math.pow(2.0, 16.0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 182,
						.statementIdx = 157,
						.statement = "console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						.executableStatement = "console.log(\"math.mod(187, 180): \", math.mod(187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 183,
						.statementIdx = 158,
						.statement = "console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						.executableStatement = "console.log(\"math.mod(-187, 180): \", math.mod(-187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 184,
						.statementIdx = 159,
						.statement = "console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						.executableStatement = "console.log(\"math.absmod(187, 180): \", math.absmod(187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 185,
						.statementIdx = 160,
						.statement = "console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						.executableStatement = "console.log(\"math.absmod(-187, 180): \", math.absmod(-187, 180))",
						.gotoStatementIdx = -1
					},
					{
						.line = 186,
						.statementIdx = 161,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 187,
						.statementIdx = 162,
						.statement = "console.log(\"Check transform\")",
						.executableStatement = "console.log(\"Check transform\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 188,
						.statementIdx = 163,
						.statement = "console.log(\"-----------------------------------\")",
						.executableStatement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 189,
						.statementIdx = 164,
						.statement = "$transform = transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))",
						.executableStatement = "setVariable(\"$transform\", transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 190,
						.statementIdx = 165,
						.statement = "$transform = transform.setRotationAngle($transform, 0, 90));",
						.executableStatement = "setVariable(\"$transform\", transform.setRotationAngle($transform, 0, 90)));",
						.gotoStatementIdx = -1
					},
					{
						.line = 191,
						.statementIdx = 166,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): \", $transform)",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): \", $transform)",
						.gotoStatementIdx = -1
					},
					{
						.line = 192,
						.statementIdx = 167,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): \", transform.getTranslation($transform))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): \", transform.getTranslation($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 193,
						.statementIdx = 168,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): \", transform.setTranslation($transform, vec3(-1,-2,-3)))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): \", transform.setTranslation($transform, vec3(-1,-2,-3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 194,
						.statementIdx = 169,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): \", transform.getScale($transform))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): \", transform.getScale($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 195,
						.statementIdx = 170,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): \", transform.setScale($transform, vec3(-2,-3,-4)))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): \", transform.setScale($transform, vec3(-2,-3,-4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 196,
						.statementIdx = 171,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): \", transform.getRotationAxis($transform, 0))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): \", transform.getRotationAxis($transform, 0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 197,
						.statementIdx = 172,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): \", transform.getRotationAngle($transform, 0))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): \", transform.getRotationAngle($transform, 0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 198,
						.statementIdx = 173,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): \", transform.setRotationAngle($transform, 0, 90))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): \", transform.setRotationAngle($transform, 0, 90))",
						.gotoStatementIdx = -1
					},
					{
						.line = 199,
						.statementIdx = 174,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): \", transform.multiply($transform, vec3(0,0,0)))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): \", transform.multiply($transform, vec3(0,0,0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 200,
						.statementIdx = 175,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						.executableStatement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 201,
						.statementIdx = 176,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 202,
						.statementIdx = 177,
						.statement = "console.log(\"Check string functions\")",
						.executableStatement = "console.log(\"Check string functions\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 203,
						.statementIdx = 178,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 204,
						.statementIdx = 179,
						.statement = "console.log(space(0), \"1\"))",
						.executableStatement = "console.log(space(0), \"1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 205,
						.statementIdx = 180,
						.statement = "console.log(space(2), \"1.1\"))",
						.executableStatement = "console.log(space(2), \"1.1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 206,
						.statementIdx = 181,
						.statement = "console.log(space(2), \"1.2\"))",
						.executableStatement = "console.log(space(2), \"1.2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 207,
						.statementIdx = 182,
						.statement = "console.log(toUpperCase(\"xxxyyyzzz\"))",
						.executableStatement = "console.log(toUpperCase(\"xxxyyyzzz\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 208,
						.statementIdx = 183,
						.statement = "console.log(toLowerCase(\"XXXYYYZZZ\"))",
						.executableStatement = "console.log(toLowerCase(\"XXXYYYZZZ\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 209,
						.statementIdx = 184,
						.statement = "console.log(concatenate(\"abc\", \"def\", \"ghi\"))",
						.executableStatement = "console.log(concatenate(\"abc\", \"def\", \"ghi\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 210,
						.statementIdx = 185,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 211,
						.statementIdx = 186,
						.statement = "console.log(\"Check string functions (Operators)\")",
						.executableStatement = "console.log(\"Check string functions (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 212,
						.statementIdx = 187,
						.statement = "console.log(\"abc\" + \"def\" + \"ghi\")",
						.executableStatement = "console.log(add(\"abc\",add(\"def\", \"ghi\")))",
						.gotoStatementIdx = -1
					},
					{
						.line = 213,
						.statementIdx = 188,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 214,
						.statementIdx = 189,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 215,
						.statementIdx = 190,
						.statement = "console.log(\"Variable\")",
						.executableStatement = "console.log(\"Variable\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 216,
						.statementIdx = 191,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 217,
						.statementIdx = 192,
						.statement = "$variable = string(\"1234\")",
						.executableStatement = "setVariable(\"$variable\", string(\"1234\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 218,
						.statementIdx = 193,
						.statement = "console.log(getVariable(\"$variable\"))",
						.executableStatement = "console.log(getVariable(\"$variable\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 219,
						.statementIdx = 194,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 220,
						.statementIdx = 195,
						.statement = "console.log(\"Lets check forTime\")",
						.executableStatement = "console.log(\"Lets check forTime\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 221,
						.statementIdx = 196,
						.statement = "console.log(\"--------------------\")",
						.executableStatement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 222,
						.statementIdx = 197,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 223,
						.statementIdx = 198,
						.statement = "forTime(2000)",
						.executableStatement = "forTime(2000)",
						.gotoStatementIdx = 203
					},
					{
						.line = 224,
						.statementIdx = 199,
						.statement = "console.log($i, \": Hello World\")",
						.executableStatement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 225,
						.statementIdx = 200,
						.statement = "script.wait(500)",
						.executableStatement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 226,
						.statementIdx = 201,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 227,
						.statementIdx = 202,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 198
					},
					{
						.line = 228,
						.statementIdx = 203,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 229,
						.statementIdx = 204,
						.statement = "console.log(\"Lets check forCondition\")",
						.executableStatement = "console.log(\"Lets check forCondition\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 230,
						.statementIdx = 205,
						.statement = "console.log(\"-------------------------\")",
						.executableStatement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 231,
						.statementIdx = 206,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 232,
						.statementIdx = 207,
						.statement = "forCondition($i != 6)",
						.executableStatement = "forCondition(notequal($i, 6))",
						.gotoStatementIdx = 212
					},
					{
						.line = 233,
						.statementIdx = 208,
						.statement = "console.log($i, \": Hello World\")",
						.executableStatement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 234,
						.statementIdx = 209,
						.statement = "script.wait(500)",
						.executableStatement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 235,
						.statementIdx = 210,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 236,
						.statementIdx = 211,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 207
					},
					{
						.line = 237,
						.statementIdx = 212,
						.statement = "console.log(\"i -> \", $i)",
						.executableStatement = "console.log(\"i -> \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 238,
						.statementIdx = 213,
						.statement = "console.log(\"---------------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 239,
						.statementIdx = 214,
						.statement = "console.log(\"Lets check forCondition with if/elseif/else\")",
						.executableStatement = "console.log(\"Lets check forCondition with if/elseif/else\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 240,
						.statementIdx = 215,
						.statement = "console.log(\"---------------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 241,
						.statementIdx = 216,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 242,
						.statementIdx = 217,
						.statement = "forCondition($i < 5)",
						.executableStatement = "forCondition(lesser($i, 5))",
						.gotoStatementIdx = 232
					},
					{
						.line = 243,
						.statementIdx = 218,
						.statement = "console.log($i, \":\")",
						.executableStatement = "console.log($i, \":\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 244,
						.statementIdx = 219,
						.statement = "if ($i == 0)",
						.executableStatement = "if (equals($i, 0))",
						.gotoStatementIdx = 221
					},
					{
						.line = 245,
						.statementIdx = 220,
						.statement = "console.log(\"i -> 0\")",
						.executableStatement = "console.log(\"i -> 0\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 246,
						.statementIdx = 221,
						.statement = "elseif ($i == 1)",
						.executableStatement = "elseif (equals($i, 1))",
						.gotoStatementIdx = 223
					},
					{
						.line = 247,
						.statementIdx = 222,
						.statement = "console.log(\"i -> 1\")",
						.executableStatement = "console.log(\"i -> 1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 248,
						.statementIdx = 223,
						.statement = "elseif ($i == 2)",
						.executableStatement = "elseif (equals($i, 2))",
						.gotoStatementIdx = 225
					},
					{
						.line = 249,
						.statementIdx = 224,
						.statement = "console.log(\"i -> 2\")",
						.executableStatement = "console.log(\"i -> 2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 250,
						.statementIdx = 225,
						.statement = "elseif ($i == 3)",
						.executableStatement = "elseif (equals($i, 3))",
						.gotoStatementIdx = 227
					},
					{
						.line = 251,
						.statementIdx = 226,
						.statement = "console.log(\"i -> 3\")",
						.executableStatement = "console.log(\"i -> 3\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 252,
						.statementIdx = 227,
						.statement = "else",
						.executableStatement = "else",
						.gotoStatementIdx = 229
					},
					{
						.line = 253,
						.statementIdx = 228,
						.statement = "console.log(\"else: \", $i)",
						.executableStatement = "console.log(\"else: \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 254,
						.statementIdx = 229,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 255,
						.statementIdx = 230,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 256,
						.statementIdx = 231,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 217
					},
					{
						.line = 257,
						.statementIdx = 232,
						.statement = "$i = 1",
						.executableStatement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 258,
						.statementIdx = 233,
						.statement = "$j = 2",
						.executableStatement = "setVariable(\"$j\", 2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 259,
						.statementIdx = 234,
						.statement = "$k = 3",
						.executableStatement = "setVariable(\"$k\", 3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 260,
						.statementIdx = 235,
						.statement = "if (getVariable(\"$i\") == $j || getVariable(\"$i\") == $k)",
						.executableStatement = "if (or(equals(getVariable(\"$i\"), $j),equals(getVariable(\"$i\"), $k)))",
						.gotoStatementIdx = 237
					},
					{
						.line = 261,
						.statementIdx = 236,
						.statement = "console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						.executableStatement = "console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 262,
						.statementIdx = 237,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 263,
						.statementIdx = 238,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.executableStatement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 264,
						.statementIdx = 239,
						.statement = "console.log(\"Test: string concatenation with brackets in string literals: \" + $i + \"(\" + $j + \")\")",
						.executableStatement = "console.log(add(\"Test: string concatenation with brackets in string literals: \",add($i,add(\"(\",add($j, \")\")))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 265,
						.statementIdx = 240,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.executableStatement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 266,
						.statementIdx = 241,
						.statement = "console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \", (4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)), \" = 17\")",
						.executableStatement = "console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \",add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), \" = 17\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 267,
						.statementIdx = 242,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 268,
						.statementIdx = 243,
						.statement = "console.log(\"Arrays\")",
						.executableStatement = "console.log(\"Arrays\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 269,
						.statementIdx = 244,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 270,
						.statementIdx = 245,
						.statement = "$array = array(1,2,3)",
						.executableStatement = "setVariable(\"$array\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 271,
						.statementIdx = 246,
						.statement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.executableStatement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 272,
						.statementIdx = 247,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 273,
						.statementIdx = 248,
						.statement = "$array = array.push($array, 8, 9, 10, 99, 10)",
						.executableStatement = "setVariable(\"$array\", array.push($array, 8, 9, 10, 99, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 274,
						.statementIdx = 249,
						.statement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10, 99, 10)\")",
						.executableStatement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10, 99, 10)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 275,
						.statementIdx = 250,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 276,
						.statementIdx = 251,
						.statement = "$array[] = 123",
						.executableStatement = "setVariable(\"$array[]\", 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 277,
						.statementIdx = 252,
						.statement = "$array[] = 1234",
						.executableStatement = "setVariable(\"$array[]\", 1234)",
						.gotoStatementIdx = -1
					},
					{
						.line = 278,
						.statementIdx = 253,
						.statement = "$array[] = 12345",
						.executableStatement = "setVariable(\"$array[]\", 12345)",
						.gotoStatementIdx = -1
					},
					{
						.line = 279,
						.statementIdx = 254,
						.statement = "$array[] = array(1,2,3)",
						.executableStatement = "setVariable(\"$array[]\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 280,
						.statementIdx = 255,
						.statement = "console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						.executableStatement = "console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 281,
						.statementIdx = 256,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 282,
						.statementIdx = 257,
						.statement = "console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						.executableStatement = "console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 283,
						.statementIdx = 258,
						.statement = "$array[11][] = 50",
						.executableStatement = "setVariable(\"$array[11][]\", 50)",
						.gotoStatementIdx = -1
					},
					{
						.line = 284,
						.statementIdx = 259,
						.statement = "$array[11][] = 60",
						.executableStatement = "setVariable(\"$array[11][]\", 60)",
						.gotoStatementIdx = -1
					},
					{
						.line = 285,
						.statementIdx = 260,
						.statement = "$array[11][array.length($array[11]) - 1] = 61",
						.executableStatement = "setVariable(\"$array[11][sub(array.length($array[11]), 1)]\", 61)",
						.gotoStatementIdx = -1
					},
					{
						.line = 286,
						.statementIdx = 261,
						.statement = "console.log(\"array length: \", array.length($array))",
						.executableStatement = "console.log(\"array length: \", array.length($array))",
						.gotoStatementIdx = -1
					},
					{
						.line = 287,
						.statementIdx = 262,
						.statement = "console.log(\"array iteration with array.get(): \")",
						.executableStatement = "console.log(\"array iteration with array.get(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 288,
						.statementIdx = 263,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 289,
						.statementIdx = 264,
						.statement = "forCondition($i < array.length($array))",
						.executableStatement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 268
					},
					{
						.line = 290,
						.statementIdx = 265,
						.statement = "console.log($i + \": \" + array.get($array, $i))",
						.executableStatement = "console.log(add($i,add(\": \", array.get($array, $i))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 291,
						.statementIdx = 266,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 292,
						.statementIdx = 267,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 264
					},
					{
						.line = 293,
						.statementIdx = 268,
						.statement = "console.log(\"array iteration with [] operator: \")",
						.executableStatement = "console.log(\"array iteration with [] operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 294,
						.statementIdx = 269,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 295,
						.statementIdx = 270,
						.statement = "forCondition($i < array.length($array))",
						.executableStatement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 274
					},
					{
						.line = 296,
						.statementIdx = 271,
						.statement = "console.log($i + \": \" + $array[$i])",
						.executableStatement = "console.log(add($i,add(\": \", $array[$i])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 297,
						.statementIdx = 272,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 298,
						.statementIdx = 273,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 270
					},
					{
						.line = 299,
						.statementIdx = 274,
						.statement = "console.log(\"array iteration with [] opertator and some index math: \")",
						.executableStatement = "console.log(\"array iteration with [] opertator and some index math: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 300,
						.statementIdx = 275,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 301,
						.statementIdx = 276,
						.statement = "forCondition($i < array.length($array) / 2)",
						.executableStatement = "forCondition(lesser($i,div(array.length($array), 2)))",
						.gotoStatementIdx = 281
					},
					{
						.line = 302,
						.statementIdx = 277,
						.statement = "console.log($i + \"-a: \" + $array[$i * 2 + 0])",
						.executableStatement = "console.log(add($i,add(\"-a: \", $array[add(mul($i, 2), 0)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 303,
						.statementIdx = 278,
						.statement = "console.log($i + \"-b: \" + $array[$i * 2 + 1])",
						.executableStatement = "console.log(add($i,add(\"-b: \", $array[add(mul($i, 2), 1)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 304,
						.statementIdx = 279,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 305,
						.statementIdx = 280,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 276
					},
					{
						.line = 306,
						.statementIdx = 281,
						.statement = "console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						.executableStatement = "console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 307,
						.statementIdx = 282,
						.statement = "$array = array.removeOf($array, 123)",
						.executableStatement = "setVariable(\"$array\", array.removeOf($array, 123))",
						.gotoStatementIdx = -1
					},
					{
						.line = 308,
						.statementIdx = 283,
						.statement = "$array = array.removeOf($array, 1234)",
						.executableStatement = "setVariable(\"$array\", array.removeOf($array, 1234))",
						.gotoStatementIdx = -1
					},
					{
						.line = 309,
						.statementIdx = 284,
						.statement = "$array = array.removeOf($array, 12345)",
						.executableStatement = "setVariable(\"$array\", array.removeOf($array, 12345))",
						.gotoStatementIdx = -1
					},
					{
						.line = 310,
						.statementIdx = 285,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 311,
						.statementIdx = 286,
						.statement = "console.log(\"array indexOf 10: \", array.indexOf($array, 10))",
						.executableStatement = "console.log(\"array indexOf 10: \", array.indexOf($array, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 312,
						.statementIdx = 287,
						.statement = "console.log(\"array indexOf 10 beginning to search from 6: \", array.indexOf($array, 10, 6))",
						.executableStatement = "console.log(\"array indexOf 10 beginning to search from 6: \", array.indexOf($array, 10, 6))",
						.gotoStatementIdx = -1
					},
					{
						.line = 313,
						.statementIdx = 288,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 314,
						.statementIdx = 289,
						.statement = "console.log(\"Maps\")",
						.executableStatement = "console.log(\"Maps\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 315,
						.statementIdx = 290,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 316,
						.statementIdx = 291,
						.statement = "$map = map()",
						.executableStatement = "setVariable(\"$map\", map())",
						.gotoStatementIdx = -1
					},
					{
						.line = 317,
						.statementIdx = 292,
						.statement = "console.log(\"map initialized with: $map = map()\")",
						.executableStatement = "console.log(\"map initialized with: $map = map()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 318,
						.statementIdx = 293,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 319,
						.statementIdx = 294,
						.statement = "console.log(\"put some key value pairs into map: $map = map.set()\")",
						.executableStatement = "console.log(\"put some key value pairs into map: $map = map.set()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 320,
						.statementIdx = 295,
						.statement = "$map = map.set($map, \"test1\", 123)",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test1\", 123))",
						.gotoStatementIdx = -1
					},
					{
						.line = 321,
						.statementIdx = 296,
						.statement = "$map = map.set($map, \"test2\", 456)",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test2\", 456))",
						.gotoStatementIdx = -1
					},
					{
						.line = 322,
						.statementIdx = 297,
						.statement = "$map = map.set($map, \"test3\", 789)",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test3\", 789))",
						.gotoStatementIdx = -1
					},
					{
						.line = 323,
						.statementIdx = 298,
						.statement = "$map = map.set($map, \"test4\", array(1,2,3))",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test4\", array(1,2,3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 324,
						.statementIdx = 299,
						.statement = "$map = map.set($map, \"test5\", \"Yaaaa\")",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test5\", \"Yaaaa\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 325,
						.statementIdx = 300,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 326,
						.statementIdx = 301,
						.statement = "console.log(\"remove test2 via map.remove: \")",
						.executableStatement = "console.log(\"remove test2 via map.remove: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 327,
						.statementIdx = 302,
						.statement = "$map = map.remove($map, \"test2\")",
						.executableStatement = "setVariable(\"$map\", map.remove($map, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 328,
						.statementIdx = 303,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 329,
						.statementIdx = 304,
						.statement = "$map = map.set($map, \"test2\", 456)",
						.executableStatement = "setVariable(\"$map\", map.set($map, \"test2\", 456))",
						.gotoStatementIdx = -1
					},
					{
						.line = 330,
						.statementIdx = 305,
						.statement = "console.log(\"readding test2: \")",
						.executableStatement = "console.log(\"readding test2: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 331,
						.statementIdx = 306,
						.statement = "console.log(\"map does have test2 key using map.has(): \", map.has($map, \"test2\"))",
						.executableStatement = "console.log(\"map does have test2 key using map.has(): \", map.has($map, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 332,
						.statementIdx = 307,
						.statement = "console.log(\"map does have test8 key using map.has(): \", map.has($map, \"test8\"))",
						.executableStatement = "console.log(\"map does have test8 key using map.has(): \", map.has($map, \"test8\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 333,
						.statementIdx = 308,
						.statement = "console.log(\"map value for test1 key using map.get(): \", map.get($map, \"test1\"))",
						.executableStatement = "console.log(\"map value for test1 key using map.get(): \", map.get($map, \"test1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 334,
						.statementIdx = 309,
						.statement = "console.log(\"map value for test2 key using map.get(): \", map.get($map, \"test2\"))",
						.executableStatement = "console.log(\"map value for test2 key using map.get(): \", map.get($map, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 335,
						.statementIdx = 310,
						.statement = "console.log(\"map value for test3 key using map.get(): \", map.get($map, \"test3\"))",
						.executableStatement = "console.log(\"map value for test3 key using map.get(): \", map.get($map, \"test3\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 336,
						.statementIdx = 311,
						.statement = "console.log(\"map value for test4 key using map.get(): \", map.get($map, \"test4\"))",
						.executableStatement = "console.log(\"map value for test4 key using map.get(): \", map.get($map, \"test4\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 337,
						.statementIdx = 312,
						.statement = "console.log(\"map value for test5 key using map.get(): \", map.get($map, \"test5\"))",
						.executableStatement = "console.log(\"map value for test5 key using map.get(): \", map.get($map, \"test5\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 338,
						.statementIdx = 313,
						.statement = "console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						.executableStatement = "console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 339,
						.statementIdx = 314,
						.statement = "console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						.executableStatement = "console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 340,
						.statementIdx = 315,
						.statement = "console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						.executableStatement = "console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 341,
						.statementIdx = 316,
						.statement = "console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						.executableStatement = "console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						.gotoStatementIdx = -1
					},
					{
						.line = 342,
						.statementIdx = 317,
						.statement = "console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						.executableStatement = "console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						.gotoStatementIdx = -1
					},
					{
						.line = 343,
						.statementIdx = 318,
						.statement = "console.log(\"adding map values using map dot operator: \")",
						.executableStatement = "console.log(\"adding map values using map dot operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 344,
						.statementIdx = 319,
						.statement = "$map.test6 = 666",
						.executableStatement = "setVariable(\"$map.test6\", 666)",
						.gotoStatementIdx = -1
					},
					{
						.line = 345,
						.statementIdx = 320,
						.statement = "$map.test7 = 770",
						.executableStatement = "setVariable(\"$map.test7\", 770)",
						.gotoStatementIdx = -1
					},
					{
						.line = 346,
						.statementIdx = 321,
						.statement = "$map.test8 = 890",
						.executableStatement = "setVariable(\"$map.test8\", 890)",
						.gotoStatementIdx = -1
					},
					{
						.line = 347,
						.statementIdx = 322,
						.statement = "console.log(\"map keys: \", map.getKeys($map))",
						.executableStatement = "console.log(\"map keys: \", map.getKeys($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 348,
						.statementIdx = 323,
						.statement = "console.log(\"map values: \", map.getValues($map))",
						.executableStatement = "console.log(\"map values: \", map.getValues($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 349,
						.statementIdx = 324,
						.statement = "console.log(\"iterating keys and values using map.getKeys(): \")",
						.executableStatement = "console.log(\"iterating keys and values using map.getKeys(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 350,
						.statementIdx = 325,
						.statement = "$mapKeys = map.getKeys($map)",
						.executableStatement = "setVariable(\"$mapKeys\", map.getKeys($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 351,
						.statementIdx = 326,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 352,
						.statementIdx = 327,
						.statement = "forCondition($i < array.length($mapKeys))",
						.executableStatement = "forCondition(lesser($i, array.length($mapKeys)))",
						.gotoStatementIdx = 331
					},
					{
						.line = 353,
						.statementIdx = 328,
						.statement = "console.log($mapKeys[$i] + \" = \" + map.get($map, $mapKeys[$i]))",
						.executableStatement = "console.log(add($mapKeys[$i],add(\" = \", map.get($map, $mapKeys[$i]))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 354,
						.statementIdx = 329,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 355,
						.statementIdx = 330,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 327
					},
					{
						.line = 356,
						.statementIdx = 331,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 357,
						.statementIdx = 332,
						.statement = "console.log(\"Functions\")",
						.executableStatement = "console.log(\"Functions\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 358,
						.statementIdx = 333,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 359,
						.statementIdx = 334,
						.statement = "helloWorldFunction()",
						.executableStatement = "helloWorldFunction()",
						.gotoStatementIdx = -1
					},
					{
						.line = 360,
						.statementIdx = 335,
						.statement = "console.log(\"factorial(5) = \" + factorial(5))",
						.executableStatement = "console.log(add(\"factorial(5) = \", factorial(5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 361,
						.statementIdx = 336,
						.statement = "console.log(\"--------------------------------------------------\")",
						.executableStatement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 362,
						.statementIdx = 337,
						.statement = "console.log(\"Test if enabled naming condition will be emitted\")",
						.executableStatement = "console.log(\"Test if enabled naming condition will be emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 363,
						.statementIdx = 338,
						.statement = "console.log(\"--------------------------------------------------\")",
						.executableStatement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 364,
						.statementIdx = 339,
						.statement = "script.enableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.enableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 365,
						.statementIdx = 340,
						.statement = "script.wait(2000)",
						.executableStatement = "script.wait(2000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 366,
						.statementIdx = 341,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 367,
						.statementIdx = 342,
						.statement = "console.log(\"---------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 368,
						.statementIdx = 343,
						.statement = "console.log(\"Naming condition has not been emitted\")",
						.executableStatement = "console.log(\"Naming condition has not been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 369,
						.statementIdx = 344,
						.statement = "console.log(\"---------------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 370,
						.statementIdx = 345,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 371,
						.statementIdx = 346,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.argumentNames = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 373,
				.condition = "error",
				.executableCondition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 374,
						.statementIdx = 0,
						.statement = "console.log(\"An error occurred\")",
						.executableStatement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 375,
						.statementIdx = 1,
						.statement = "script.wait(1000)",
						.executableStatement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 376,
						.statementIdx = 2,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.argumentNames = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ON,
				.line = 378,
				.condition = "emittest",
				.executableCondition = "emittest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 379,
						.statementIdx = 0,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 380,
						.statementIdx = 1,
						.statement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.executableStatement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 381,
						.statementIdx = 2,
						.statement = "console.log(\"---------------------------------\")",
						.executableStatement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 382,
						.statementIdx = 3,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 383,
						.statementIdx = 4,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 384,
						.statementIdx = 5,
						.statement = "console.log(\"Benchmark \")",
						.executableStatement = "console.log(\"Benchmark \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 385,
						.statementIdx = 6,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 386,
						.statementIdx = 7,
						.statement = "$startTime = time.getCurrentMillis()",
						.executableStatement = "setVariable(\"$startTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 387,
						.statementIdx = 8,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 388,
						.statementIdx = 9,
						.statement = "$j = 0",
						.executableStatement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 389,
						.statementIdx = 10,
						.statement = "$k = 0",
						.executableStatement = "setVariable(\"$k\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 390,
						.statementIdx = 11,
						.statement = "forCondition($i < 500000)",
						.executableStatement = "forCondition(lesser($i, 500000))",
						.gotoStatementIdx = 22
					},
					{
						.line = 391,
						.statementIdx = 12,
						.statement = "$a = 123 + 456 * (25 / 12) + (7.5 * 12.25) - 8",
						.executableStatement = "setVariable(\"$a\",sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))",
						.gotoStatementIdx = -1
					},
					{
						.line = 392,
						.statementIdx = 13,
						.statement = "if ($j == 0)",
						.executableStatement = "if (equals($j, 0))",
						.gotoStatementIdx = 15
					},
					{
						.line = 393,
						.statementIdx = 14,
						.statement = "$k = $k + 1",
						.executableStatement = "setVariable(\"$k\",add($k, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 394,
						.statementIdx = 15,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 395,
						.statementIdx = 16,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 396,
						.statementIdx = 17,
						.statement = "$j = $j + 1",
						.executableStatement = "setVariable(\"$j\",add($j, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 397,
						.statementIdx = 18,
						.statement = "if ($j == 2)",
						.executableStatement = "if (equals($j, 2))",
						.gotoStatementIdx = 20
					},
					{
						.line = 398,
						.statementIdx = 19,
						.statement = "$j = 0",
						.executableStatement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 399,
						.statementIdx = 20,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 400,
						.statementIdx = 21,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 11
					},
					{
						.line = 401,
						.statementIdx = 22,
						.statement = "$endTime = time.getCurrentMillis()",
						.executableStatement = "setVariable(\"$endTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 402,
						.statementIdx = 23,
						.statement = "console.log(\"Finished. Time: \" + ($endTime - $startTime))",
						.executableStatement = "console.log(add(\"Finished. Time: \", sub($endTime, $startTime)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 403,
						.statementIdx = 24,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 404,
						.statementIdx = 25,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.argumentNames = {
				}
			},
			{
				.scriptType = Script::SCRIPTTYPE_ONENABLED,
				.line = 406,
				.condition = "true == true",
				.executableCondition = "equals(true, true)",
				.name = "named_condition_1",
				.emitCondition = false,
				.statements = {
					{
						.line = 407,
						.statementIdx = 0,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.executableStatement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 408,
						.statementIdx = 1,
						.statement = "console.log(\"------------------------------------\")",
						.executableStatement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 409,
						.statementIdx = 2,
						.statement = "console.log(\"named_condition_1 has been emitted\")",
						.executableStatement = "console.log(\"named_condition_1 has been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 410,
						.statementIdx = 3,
						.statement = "console.log(\"------------------------------------\")",
						.executableStatement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 411,
						.statementIdx = 4,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 412,
						.statementIdx = 5,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 413,
						.statementIdx = 6,
						.statement = "console.log(\"Test emit\")",
						.executableStatement = "console.log(\"Test emit\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 414,
						.statementIdx = 7,
						.statement = "console.log(\"-----------\")",
						.executableStatement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 415,
						.statementIdx = 8,
						.statement = "console.log()",
						.executableStatement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 416,
						.statementIdx = 9,
						.statement = "script.emit(emittest)",
						.executableStatement = "script.emit(emittest)",
						.gotoStatementIdx = -1
					},
					{
						.line = 417,
						.statementIdx = 10,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = -1
					}
				},
				.argumentNames = {
				}
			}
		}
	);
	setNativeScriptFunctions(
		{
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

int MiniScriptTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 3;
}

int MiniScriptTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (auto& enabledNamedCondition: enabledNamedConditions) {

		// next statements belong to tested enabled named condition with name "named_condition_1"
		if (enabledNamedCondition == "named_condition_1")
			// equals(true, true)
			{
				const ScriptStatement statement = {
					.line = 406,
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
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
				bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return 6;
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
		Console::println("MiniScriptTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptTest::on_initialize(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("------------")
	{
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
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
		getScriptState().statementIdx = statement.statementIdx;
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
		getScriptState().statementIdx = statement.statementIdx;
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

void MiniScriptTest::factorial(int miniScriptGotoStatementIdx) {
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
	// console.log(add("factorial(): $arguments = ",add($arguments,add(" / $value = ", $value))))
	{
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("factorial(): $arguments = ",add($arguments,add(" / $value = ", $value)))
		// depth = 1 / argument index = 0: add("factorial(): $arguments = ", add($arguments,add(" / $value = ", $value)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("factorial(): $arguments = "));
			// argumentValues[1] --> returnValue of add($arguments,add(" / $value = ", $value))
			// depth = 2 / argument index = 1: add($arguments, add(" / $value = ", $value))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$arguments")
				// argumentValues[1] --> returnValue of add(" / $value = ", $value)
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add(" / $value = ", $value)
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
	// if(equals($value, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($value, 0)
		// depth = 1 / argument index = 0: equals($value, 0)
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
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): no function is being executed, return($value) has no effect");
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): parameter type mismatch @ argument 0: mixed expected");
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
	// return(mul($value, factorial(sub($value, 1))))
	{
		const ScriptStatement& statement = scripts[1].statements[4];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of mul($value, factorial(sub($value, 1)))
		// depth = 1 / argument index = 0: mul($value, factorial(sub($value, 1)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$value")
			// argumentValues[1] --> returnValue of factorial(sub($value, 1))
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: script.call(factorial, sub($value, 1))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("factorial"));
				// argumentValues[1] --> returnValue of sub($value, 1)
				// depth = 3 / argument index = 1: sub($value, 1)
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: sub
					MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
				}
				// method code: script.call
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): parameter type mismatch @ argument 0: string expected");
				} else {
					miniScript->call(function, span(argumentValues.begin() + 1, argumentValues.end()), returnValue);
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: return
		if (miniScript->isFunctionRunning() == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): no function is being executed, return($value) has no effect");
		} else
		if (argumentValues.size() == 1) {
			auto& scriptState = miniScript->getScriptState();
			scriptState.returnValue = argumentValues[0];
			miniScript->stopRunning();
		} else {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("return") + "(): parameter type mismatch @ argument 0: mixed expected");
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

void MiniScriptTest::helloWorldFunction(int miniScriptGotoStatementIdx) {
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

void MiniScriptTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 199) goto miniscript_statement_199; else
	if (miniScriptGotoStatementIdx == 201) goto miniscript_statement_201; else
	if (miniScriptGotoStatementIdx == 203) goto miniscript_statement_203; else
	if (miniScriptGotoStatementIdx == 208) goto miniscript_statement_208; else
	if (miniScriptGotoStatementIdx == 210) goto miniscript_statement_210; else
	if (miniScriptGotoStatementIdx == 212) goto miniscript_statement_212; else
	if (miniScriptGotoStatementIdx == 218) goto miniscript_statement_218; else
	if (miniScriptGotoStatementIdx == 220) goto miniscript_statement_220; else
	if (miniScriptGotoStatementIdx == 222) goto miniscript_statement_222; else
	if (miniScriptGotoStatementIdx == 224) goto miniscript_statement_224; else
	if (miniScriptGotoStatementIdx == 226) goto miniscript_statement_226; else
	if (miniScriptGotoStatementIdx == 228) goto miniscript_statement_228; else
	if (miniScriptGotoStatementIdx == 230) goto miniscript_statement_230; else
	if (miniScriptGotoStatementIdx == 232) goto miniscript_statement_232; else
	if (miniScriptGotoStatementIdx == 236) goto miniscript_statement_236; else
	if (miniScriptGotoStatementIdx == 238) goto miniscript_statement_238; else
	if (miniScriptGotoStatementIdx == 265) goto miniscript_statement_265; else
	if (miniScriptGotoStatementIdx == 268) goto miniscript_statement_268; else
	if (miniScriptGotoStatementIdx == 271) goto miniscript_statement_271; else
	if (miniScriptGotoStatementIdx == 274) goto miniscript_statement_274; else
	if (miniScriptGotoStatementIdx == 277) goto miniscript_statement_277; else
	if (miniScriptGotoStatementIdx == 281) goto miniscript_statement_281; else
	if (miniScriptGotoStatementIdx == 328) goto miniscript_statement_328; else
	if (miniScriptGotoStatementIdx == 331) goto miniscript_statement_331; else
	if (miniScriptGotoStatementIdx == 341) goto miniscript_statement_341; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[3].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
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
	// console.log("Nothing")
	{
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Nothing"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[3].statements[2];
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
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[4];
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
		const ScriptStatement& statement = scripts[3].statements[5];
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
		const ScriptStatement& statement = scripts[3].statements[6];
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
		const ScriptStatement& statement = scripts[3].statements[7];
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
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("it will"));
					argumentValues[1].setValue(string("it will"));
					// method code: equals
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
				// method code: or
				returnValue.setValue(false);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
						miniScript->startErrorScript(); return;
					} else
					if (booleanValue == true) {
						returnValue.setValue(true);
						break;
					}
				}
			}
			// method code: and
			returnValue.setValue(true);
			for (auto i = 0; i < argumentValues.size(); i++) {
				bool booleanValue;
				if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
					Console::println("ScriptMethodAnd::executeMethod(): " + string("and") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
					miniScript->startErrorScript(); return;
				} else
				if (booleanValue == false) {
					returnValue.setValue(false);
					break;
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
		const ScriptStatement& statement = scripts[3].statements[8];
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
		const ScriptStatement& statement = scripts[3].statements[9];
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
		const ScriptStatement& statement = scripts[3].statements[10];
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
	// console.log("sub(add(1, 2, 3), 1)): ", sub(add(1, 2, 3), 1))
	{
		const ScriptStatement& statement = scripts[3].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(1, 2, 3), 1)): "));
		// argumentValues[1] --> returnValue of sub(add(1, 2, 3), 1)
		// depth = 1 / argument index = 1: sub(add(1, 2, 3), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1, 2, 3)
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: add(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
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
	// console.log("div(20, 2): ", div(20, 2))
	{
		const ScriptStatement& statement = scripts[3].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(20, 2): "));
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
	// console.log("mul(11, 10): ", mul(11, 10))
	{
		const ScriptStatement& statement = scripts[3].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(11, 10): "));
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
	// console.log("greater(2, 1): ", greater(2, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("greater(2, 1): "));
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
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("lesser(2, 1): ", lesser(2, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("lesser(2, 1): "));
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("---------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[16];
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

	// Statement: 17
	// console.log("Check int computation (Operators)")
	{
		const ScriptStatement& statement = scripts[3].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check int computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 18
	// console.log("---------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[18];
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

	// Statement: 19
	// console.log("1 + 2 + 3 - 1: ", sub(add(1,add(2, 3)), 1))
	{
		const ScriptStatement& statement = scripts[3].statements[19];
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

	// Statement: 20
	// console.log("20 / 2: ", div(20, 2))
	{
		const ScriptStatement& statement = scripts[3].statements[20];
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

	// Statement: 21
	// console.log("11 * 10: ", mul(11, 10))
	{
		const ScriptStatement& statement = scripts[3].statements[21];
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

	// Statement: 22
	// console.log("2 > 1: ", greater(2, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[22];
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
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("2 < 1: ", lesser(2, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[23];
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
		const ScriptStatement& statement = scripts[3].statements[24];
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
	// console.log("Check float computation")
	{
		const ScriptStatement& statement = scripts[3].statements[25];
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

	// Statement: 26
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[26];
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
	// console.log("sub(add(1.1, 2.2, 3.3), 1.2)): ", sub(add(1.1, 2.2, 3.3), 1.2))
	{
		const ScriptStatement& statement = scripts[3].statements[27];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(1.1, 2.2, 3.3), 1.2)): "));
		// argumentValues[1] --> returnValue of sub(add(1.1, 2.2, 3.3), 1.2)
		// depth = 1 / argument index = 1: sub(add(1.1, 2.2, 3.3), 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1.1, 2.2, 3.3)
			argumentValues[1].setValue(1.200000f);
			// depth = 2 / argument index = 0: add(1.1, 2.2, 3.3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				argumentValues[2].setValue(3.300000f);
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

	// Statement: 28
	// console.log("div(20, 1.5): ", div(20, 1.5))
	{
		const ScriptStatement& statement = scripts[3].statements[28];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(20, 1.5): "));
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

	// Statement: 29
	// console.log("mul(11.5, 10.5): ", mul(11.5, 10.5))
	{
		const ScriptStatement& statement = scripts[3].statements[29];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(11.5, 10.5): "));
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

	// Statement: 30
	// console.log("greater(2.2, 1.3): ", greater(2.2, 1.3))
	{
		const ScriptStatement& statement = scripts[3].statements[30];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("greater(2.2, 1.3): "));
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
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("lesser(2.5, 1.2): ", lesser(2.5, 1.2))
	{
		const ScriptStatement& statement = scripts[3].statements[31];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("lesser(2.5, 1.2): "));
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[32];
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

	// Statement: 33
	// console.log("Check float computation (Operators)")
	{
		const ScriptStatement& statement = scripts[3].statements[33];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check float computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 34
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[34];
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

	// Statement: 35
	// console.log("(1.1 + 2.2 + 3.3) - 1.2: ", sub(add(1.1,add(2.2, 3.3)), 1.2))
	{
		const ScriptStatement& statement = scripts[3].statements[35];
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

	// Statement: 36
	// console.log("20 / 1.5: ", div(20, 1.5))
	{
		const ScriptStatement& statement = scripts[3].statements[36];
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

	// Statement: 37
	// console.log("11.5 * 10.5: ", mul(11.5, 10.5))
	{
		const ScriptStatement& statement = scripts[3].statements[37];
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

	// Statement: 38
	// console.log("2.2 > 1.3: ", greater(2.2, 1.3))
	{
		const ScriptStatement& statement = scripts[3].statements[38];
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
				Console::println("ScriptMethodGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 39
	// console.log("2.5 < 1.2: ", lesser(2.5, 1.2))
	{
		const ScriptStatement& statement = scripts[3].statements[39];
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 40
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[40];
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
	// console.log("Check vector2 math")
	{
		const ScriptStatement& statement = scripts[3].statements[41];
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

	// Statement: 42
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[42];
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

	// Statement: 43
	// console.log("vec2.computeLength(vec2(20, 10)): ", vec2.computeLength(vec2(20, 10)))
	{
		const ScriptStatement& statement = scripts[3].statements[43];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLength
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.computeLength());
			} else {
				Console::println("ScriptMethodVec2ComputeLength::executeMethod(): " + string("vec2.computeLength") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("vec2.computeLengthSquared(vec2(20, 10)): ", vec2.computeLengthSquared(vec2(20, 10)))
	{
		const ScriptStatement& statement = scripts[3].statements[44];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.computeLengthSquared
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec2ComputeLengthSquared::executeMethod(): " + string("vec2.computeLengthSquared") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)): ", vec2.computeDotProduct(vec2(0, 1), vec2(0, -1)))
	{
		const ScriptStatement& statement = scripts[3].statements[45];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				Console::println("ScriptMethodVec2ComputeDotProduct::executeMethod(): " + string("vec2.computeDotProduct") + "(): parameter type mismatch @ argument 0: vector2 expected, @ argument 1: vector2 expected");
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
	// console.log("vec2.normalize(vec2(1, 2)): ", vec2.normalize(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[3].statements[46];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.normalize
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.normalize());
			} else {
				Console::println("ScriptMethodVec2Normalize::executeMethod(): " + string("vec2.normalize") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("vec2.getX(vec2(1, 2)): ", vec2.getX(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[3].statements[47];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getX
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getX());
			} else {
				Console::println("ScriptMethodVec2GetX::executeMethod(): " + string("vec2.getX") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("vec2.getY(vec2(1, 2)): ", vec2.getY(vec2(1, 2)))
	{
		const ScriptStatement& statement = scripts[3].statements[48];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec2.getY
			Vector2 vec2;
			if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
				returnValue.setValue(vec2.getY());
			} else {
				Console::println("ScriptMethodVec2GetY::executeMethod(): " + string("vec2.getY") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("vec2(1.1, 2.2) - vec2(1.2, 1.0): ", sub(vec2(1.1, 2.2), vec2(1.2, 1.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[49];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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

	// Statement: 50
	// console.log("vec2(20, 10) / vec2(1.5, 2.5): ", div(vec2(20, 10), vec2(1.5, 2.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[50];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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

	// Statement: 51
	// console.log("vec2(20, 10) * vec2(1.5, 2.5)): ", mul(vec2(20, 10), vec2(1.5, 2.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[51];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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

	// Statement: 52
	// console.log("vec2(20, 10) / 2): ", div(vec2(20, 10), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[52];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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

	// Statement: 53
	// console.log("vec2(20, 10) * 2): ", mul(vec2(20, 10), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[53];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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

	// Statement: 54
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[54];
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

	// Statement: 55
	// console.log("Check vector3 math")
	{
		const ScriptStatement& statement = scripts[3].statements[55];
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

	// Statement: 56
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[56];
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

	// Statement: 57
	// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[3].statements[57];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLength
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLength());
			} else {
				Console::println("ScriptMethodVec3ComputeLength::executeMethod(): " + string("vec3.computeLength") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 58
	// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[3].statements[58];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLengthSquared
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec3ComputeLengthSquared::executeMethod(): " + string("vec3.computeLengthSquared") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
	{
		const ScriptStatement& statement = scripts[3].statements[59];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeDotProduct::executeMethod(): " + string("vec3.computeDotProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
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
	// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[3].statements[60];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeCrossProduct::executeMethod(): " + string("vec3.computeCrossProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
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
	// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[3].statements[61];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.normalize
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.normalize());
			} else {
				Console::println("ScriptMethodVec3Normalize::executeMethod(): " + string("vec3.normalize") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[3].statements[62];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodVec3ComputeAngle::executeMethod(): " + string("vec3.computeAngle") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected @ argument 2: vector3 expected");
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
	// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[3].statements[63];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getX
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getX());
			} else {
				Console::println("ScriptMethodVec3GetX::executeMethod(): " + string("vec3.getX") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[3].statements[64];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getY
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getY());
			} else {
				Console::println("ScriptMethodVec3GetY::executeMethod(): " + string("vec3.getY") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[3].statements[65];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getZ
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getZ());
			} else {
				Console::println("ScriptMethodVec3GetZ::executeMethod(): " + string("vec3.getZ") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[66];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
	// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[67];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
	// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[68];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
	// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[69];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
	// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[70];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
		const ScriptStatement& statement = scripts[3].statements[71];
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
	// console.log("Check vector4 math")
	{
		const ScriptStatement& statement = scripts[3].statements[72];
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

	// Statement: 73
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[73];
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
	// console.log("vec4.computeLength(vec4(20, 10, 5, 2.5)): ", vec4.computeLength(vec4(20, 10, 5, 2.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[74];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLength
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.computeLength());
			} else {
				Console::println("ScriptMethodVec4ComputeLength::executeMethod(): " + string("vec4.computeLength") + "(): parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 75
	// console.log("vec4.computeLengthSquared(vec3(20, 10, 5)): ", vec4.computeLengthSquared(vec4(20, 10, 5, 2.5)))
	{
		const ScriptStatement& statement = scripts[3].statements[75];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.computeLengthSquared
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec4ComputeLengthSquared::executeMethod(): " + string("vec4.computeLengthSquared") + "(): parameter type mismatch @ argument 0: vector4 expected");
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
	// console.log("vec4.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1, 1)): ", vec4.computeDotProduct(vec4(0, 0, 1, 1), vec4(0, 0, -1, 1)))
	{
		const ScriptStatement& statement = scripts[3].statements[76];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
				Console::println("ScriptMethodVec4ComputeDotProduct::executeMethod(): " + string("vec4.computeDotProduct") + "(): parameter type mismatch @ argument 0: vector4 expected, @ argument 1: vector4 expected");
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
	// console.log("vec4.normalize(vec4(1, 2, 3, 4)): ", vec4.normalize(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[3].statements[77];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.normalize
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.normalize());
			} else {
				Console::println("ScriptMethodVec4Normalize::executeMethod(): " + string("vec4.normalize") + "(): parameter type mismatch @ argument 0: vector4 expected");
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
	// console.log("vec4.getX(vec4(1, 2, 3, 4)): ", vec4.getX(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[3].statements[78];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getX
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getX());
			} else {
				Console::println("ScriptMethodVec4GetX::executeMethod(): " + string("vec4.getX") + "(): parameter type mismatch @ argument 0: vector4 expected");
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
	// console.log("vec4.getY(vec4(1, 2, 3, 4)): ", vec4.getY(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[3].statements[79];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getY
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getY());
			} else {
				Console::println("ScriptMethodVec4GetY::executeMethod(): " + string("vec4.getY") + "(): parameter type mismatch @ argument 0: vector4 expected");
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
	// console.log("vec4.getZ(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[3].statements[80];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println("ScriptMethodVec4GetZ::executeMethod(): " + string("vec4.getZ") + "(): parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 81
	// console.log("vec4.getW(vec4(1, 2, 3, 4)): ", vec4.getZ(vec4(1, 2, 3, 4)))
	{
		const ScriptStatement& statement = scripts[3].statements[81];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec4.getZ
			Vector4 vec4;
			if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
				returnValue.setValue(vec4.getZ());
			} else {
				Console::println("ScriptMethodVec4GetZ::executeMethod(): " + string("vec4.getZ") + "(): parameter type mismatch @ argument 0: vector4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 82
	// console.log("vec4(1.1, 2.2, 3.3, 1.0) - vec4(1.2, 1.0, 1.0, 1.0): ", sub(vec4(1.1, 2.2, 3.3, 1.0), vec4(1.2, 1.0, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[82];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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

	// Statement: 83
	// console.log("vec4(20, 10, 5, 1) / vec4(1.5, 2.5, 3.5, 1): ", div(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))
	{
		const ScriptStatement& statement = scripts[3].statements[83];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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

	// Statement: 84
	// console.log("vec4(20, 10, 5, 1) * vec4(1.5, 2.5, 3.5, 1)): ", mul(vec4(20, 10, 5, 1), vec4(1.5, 2.5, 3.5, 1)))
	{
		const ScriptStatement& statement = scripts[3].statements[84];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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

	// Statement: 85
	// console.log("vec4(20, 10, 5, 1) / 2): ", div(vec4(20, 10, 5, 1), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[85];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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

	// Statement: 86
	// console.log("vec4(20, 10, 5, 1) * 2): ", mul(vec4(20, 10, 5, 1), 2))
	{
		const ScriptStatement& statement = scripts[3].statements[86];
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
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

	// Statement: 87
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[87];
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

	// Statement: 88
	// console.log("Check quaternion math")
	{
		const ScriptStatement& statement = scripts[3].statements[88];
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

	// Statement: 89
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[89];
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

	// Statement: 90
	// console.log("quaternion.identity(): ", quaternion.identity())
	{
		const ScriptStatement& statement = scripts[3].statements[90];
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

	// Statement: 91
	// console.log("quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0))
	{
		const ScriptStatement& statement = scripts[3].statements[91];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
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
	// console.log("quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.normalize(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[92];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.normalize
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.normalize());
			} else {
				Console::println("ScriptMethodQuaternionNormalize::executeMethod(): " + string("quaternion.normalize") + "(): parameter type mismatch @ argument 0: quaternion expected");
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
	// console.log("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)): ", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), quaternion.rotate(vec3(1.0, 0.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[93];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.multiply
			Quaternion quaternion;
			Quaternion quaternionValue;
			Vector3 vec3Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				if (MiniScript::getQuaternionValue(argumentValues, 1, quaternionValue, false) == true) {
					returnValue.setValue(quaternion.multiply(quaternionValue));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(quaternion.multiply(vec3Value));
				} else {
					Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 94
	// console.log("quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): ", quaternion.multiply(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[94];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.multiply
			Quaternion quaternion;
			Quaternion quaternionValue;
			Vector3 vec3Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				if (MiniScript::getQuaternionValue(argumentValues, 1, quaternionValue, false) == true) {
					returnValue.setValue(quaternion.multiply(quaternionValue));
				} else
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
					returnValue.setValue(quaternion.multiply(vec3Value));
				} else {
					Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodQuaternionMultiply::executeMethod(): " + string("quaternion.multiply") + "(): parameter type mismatch @ argument 0: quaternion expected, @ argument 1: quaternion or vec3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 95
	// console.log("quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", quaternion.computeMatrix(quaternion.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[95];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodQuaternionRotate::executeMethod(): " + string("quaternion.rotate") + "(): parameter type mismatch @ argument 0: vec3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: quaternion.computeMatrix
			Quaternion quaternion;
			if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
				returnValue.setValue(quaternion.computeMatrix());
			} else {
				Console::println("ScriptMethodQuaternionComputeMatrix::executeMethod(): " + string("quaternion.computeMatrix") + "(): parameter type mismatch @ argument 0: quaternion expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 96
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[96];
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

	// Statement: 97
	// console.log("Check matrix4x4 math")
	{
		const ScriptStatement& statement = scripts[3].statements[97];
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

	// Statement: 98
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[98];
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

	// Statement: 99
	// console.log("mat4.identity(): ", mat4.identity())
	{
		const ScriptStatement& statement = scripts[3].statements[99];
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

	// Statement: 100
	// console.log("mat4.translate(vec3(1.0, 2.0, 3.0)): ", mat4.translate(vec3(1.0, 2.0, 3.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[100];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.translate
			Vector3 translation;
			if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix4x4().identity().translate(translation));
			} else {
				Console::println("ScriptMethodMatrix4x4Translate::executeMethod(): " + string("mat4.translate") + "(): parameter type mismatch @ argument 0: vector3 expected");
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
	// console.log("mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0): ", mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0))
	{
		const ScriptStatement& statement = scripts[3].statements[101];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
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
	// console.log("mat4.scale(vec3(1.0, 2.0, 3.0)): ", mat4.scale(vec3(1.0, 2.0, 3.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[102];
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): parameter type mismatch @ argument 0: vector3 or float expected");
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
	// console.log("mat4.scale(3.0): ", mat4.scale(3.0))
	{
		const ScriptStatement& statement = scripts[3].statements[103];
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
				Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): parameter type mismatch @ argument 0: vector3 or float expected");
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
	// console.log("mat4.invert(mat4.scale(3.0)): ", mat4.invert(mat4.scale(3.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[104];
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
					Console::println("ScriptMethodMatrix4x4Scale::executeMethod(): " + string("mat4.scale") + "(): parameter type mismatch @ argument 0: vector3 or float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.invert
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.invert());
			} else {
				Console::println("ScriptMethodMatrix4x4Invert::executeMethod(): " + string("mat4.invert") + "(): parameter type mismatch @ argument 0: matrix4x4 expected");
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
	// console.log("mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)): ", mat4.computeEulerAngles(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[105];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.computeEulerAngles
			Matrix4x4 mat4;
			if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
				returnValue.setValue(mat4.computeEulerAngles());
			} else {
				Console::println("ScriptMethodMatrix4x4EulerAngles::executeMethod(): " + string("mat4.computeEulerAngles") + "(): parameter type mismatch @ argument 0: matrix4x4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 106
	// console.log("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)): ", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.rotate(vec3(1.0, 0.0, 0.0), 90.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[106];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
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
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 107
	// console.log("mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)): ", mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), vec3(0.0, 0.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[107];
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
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
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
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 108
	// console.log("mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)): ", mat4.multiply(mat4.multiply(mat4.rotate(vec3(0.0, 1.0, 0.0), 90.0), mat4.translate(vec3(1.0, 2.0, 3.0))), vec4(0.0, 0.0, 1.0, 0.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[108];
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
							Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
						Console::println("ScriptMethodMatrix4x4Rotate::executeMethod(): " + string("mat4.rotate") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: float expected");
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
							Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: mat4.translate
					Vector3 translation;
					if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
						returnValue.setValue(Matrix4x4().identity().translate(translation));
					} else {
						Console::println("ScriptMethodMatrix4x4Translate::executeMethod(): " + string("mat4.translate") + "(): parameter type mismatch @ argument 0: vector3 expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat4.multiply
				Matrix4x4 mat4;
				Matrix4x4 mat4Value;
				Vector3 vec3Value;
				Vector4 vec4Value;
				if (argumentValues.size() != 2) {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
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
						Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
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
					Console::println("ScriptMethodVec4::executeMethod(): " + string("vec4") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected, @ argument 3: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat4.multiply
			Matrix4x4 mat4;
			Matrix4x4 mat4Value;
			Vector3 vec3Value;
			Vector4 vec4Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
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
					Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix4x4Multiply::executeMethod(): " + string("mat4.multiply") + "(): parameter type mismatch @ argument 0: matrix4x4 expected, @ argument 1: vec3 or vec4 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 109
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[109];
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

	// Statement: 110
	// console.log("Check matrix3x3 math")
	{
		const ScriptStatement& statement = scripts[3].statements[110];
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

	// Statement: 111
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[111];
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

	// Statement: 112
	// console.log("mat3.identity(): ", mat3.identity())
	{
		const ScriptStatement& statement = scripts[3].statements[112];
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

	// Statement: 113
	// console.log("mat3.translate(vec2(1.0, 2.0)): ", mat3.translate(vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[113];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.translate
			Vector2 translation;
			if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
				returnValue.setValue(Matrix2D3x3().identity().translate(translation));
			} else {
				Console::println("ScriptMethodMatrix3x3Translate::executeMethod(): " + string("mat3.translate") + "(): parameter type mismatch @ argument 0: vector2 expected");
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
	// console.log("mat3.rotate(90.0): ", mat3.rotate(90.0))
	{
		const ScriptStatement& statement = scripts[3].statements[114];
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
				Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("mat3.rotateAroundTextureCenter(90.0): ", mat3.rotateAroundTextureCenter(90.0))
	{
		const ScriptStatement& statement = scripts[3].statements[115];
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
				Console::println("ScriptMethodMatrix3x3RotateAroundCenter::executeMethod(): " + string("mat3.rotateAroundTextureCenter") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("mat3.rotateAroundPoint(vec2(0.5, 0.5), 90.0): ", mat3.rotateAroundPoint(vec2(0.5, 0.4), 90.0))
	{
		const ScriptStatement& statement = scripts[3].statements[116];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				Console::println("ScriptMethodMatrix3x3RotateAroundPoint::executeMethod(): " + string("mat3.rotateAroundPoint") + "(): parameter type mismatch @ argument 0: vector2 expected, @ argument 1: float expected");
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
	// console.log("mat3.scale(vec2(1.0, 2.0)): ", mat3.scale(vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[117];
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				Console::println("ScriptMethodMatrix3x3Scale::executeMethod(): " + string("mat3.scale") + "(): parameter type mismatch @ argument 0: vector2 or float expected");
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
	// console.log("mat3.scale(3.0): ", mat3.scale(3.0))
	{
		const ScriptStatement& statement = scripts[3].statements[118];
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
				Console::println("ScriptMethodMatrix3x3Scale::executeMethod(): " + string("mat3.scale") + "(): parameter type mismatch @ argument 0: vector2 or float expected");
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
	// console.log("mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))): ", mat3.multiply(mat3.rotate(90.0), mat3.translate(vec2(1.0, 2.0))))
	{
		const ScriptStatement& statement = scripts[3].statements[119];
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
					Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): parameter type mismatch @ argument 0: float expected");
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
						Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: mat3.translate
				Vector2 translation;
				if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
					returnValue.setValue(Matrix2D3x3().identity().translate(translation));
				} else {
					Console::println("ScriptMethodMatrix3x3Translate::executeMethod(): " + string("mat3.translate") + "(): parameter type mismatch @ argument 0: vector2 expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.multiply
			Matrix2D3x3 mat3;
			Matrix2D3x3 mat3Value;
			Vector2 vec2Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix3x3Value(argumentValues, 0, mat3, false) == true) {
				if (MiniScript::getMatrix3x3Value(argumentValues, 1, mat3Value, false) == true) {
					returnValue.setValue(mat3.multiply(mat3Value));
				} else
				if (MiniScript::getVector2Value(argumentValues, 1, vec2Value, false) == true) {
					returnValue.setValue(mat3.multiply(vec2Value));
				} else {
					Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
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
	// console.log("mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)): ", mat3.multiply(mat3.rotate(90.0), vec2(1.0, 2.0)))
	{
		const ScriptStatement& statement = scripts[3].statements[120];
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
					Console::println("ScriptMethodMatrix3x3Rotate::executeMethod(): " + string("mat3.rotate") + "(): parameter type mismatch @ argument 0: float expected");
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
					Console::println("ScriptMethodVec2::executeMethod(): " + string("vec2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mat3.multiply
			Matrix2D3x3 mat3;
			Matrix2D3x3 mat3Value;
			Vector2 vec2Value;
			if (argumentValues.size() != 2) {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
				miniScript->startErrorScript(); return;
			} else
			if (MiniScript::getMatrix3x3Value(argumentValues, 0, mat3, false) == true) {
				if (MiniScript::getMatrix3x3Value(argumentValues, 1, mat3Value, false) == true) {
					returnValue.setValue(mat3.multiply(mat3Value));
				} else
				if (MiniScript::getVector2Value(argumentValues, 1, vec2Value, false) == true) {
					returnValue.setValue(mat3.multiply(vec2Value));
				} else {
					Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodMatrix3x3Multiply::executeMethod(): " + string("mat3.multiply") + "(): parameter type mismatch @ argument 0: matrix3x3 expected, @ argument 1: vec2 expected");
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
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[121];
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

	// Statement: 122
	// console.log("Check additional math")
	{
		const ScriptStatement& statement = scripts[3].statements[122];
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

	// Statement: 123
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[123];
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

	// Statement: 124
	// console.log("math.PI(): ", math.PI())
	{
		const ScriptStatement& statement = scripts[3].statements[124];
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

	// Statement: 125
	// console.log("math.EPSILON(): ", math.EPSILON())
	{
		const ScriptStatement& statement = scripts[3].statements[125];
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

	// Statement: 126
	// console.log("math.DEG2RAD(): ", math.DEG2RAD())
	{
		const ScriptStatement& statement = scripts[3].statements[126];
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

	// Statement: 127
	// console.log("math.G(): ", math.G())
	{
		const ScriptStatement& statement = scripts[3].statements[127];
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

	// Statement: 128
	// console.log("math.acos(0.0): ", math.acos(0.0))
	{
		const ScriptStatement& statement = scripts[3].statements[128];
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
				Console::println("ScriptMethodAcos::executeMethod(): " + string("math.acos") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.asin(1.0): ", math.asin(1.0))
	{
		const ScriptStatement& statement = scripts[3].statements[129];
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
				Console::println("ScriptMethodAsin::executeMethod(): " + string("math.asin") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.atan(1.0): ", math.atan(1.0))
	{
		const ScriptStatement& statement = scripts[3].statements[130];
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
				Console::println("ScriptMethodAtan::executeMethod(): " + string("math.atan") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.atan2(-1.0, -1.0): ", math.atan2(-1.0, -1.0))
	{
		const ScriptStatement& statement = scripts[3].statements[131];
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
				Console::println("ScriptMethodAtan2::executeMethod(): " + string("math.atan2") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("math.floor(2.87): ", math.floor(2.87))
	{
		const ScriptStatement& statement = scripts[3].statements[132];
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
				Console::println("ScriptMethodCeil::executeMethod(): " + string("math.floor") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.ceil(2.87): ", math.ceil(2.87))
	{
		const ScriptStatement& statement = scripts[3].statements[133];
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
				Console::println("ScriptMethodCeil::executeMethod(): " + string("math.ceil") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.round(2.37): ", math.round(2.37))
	{
		const ScriptStatement& statement = scripts[3].statements[134];
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
				Console::println("ScriptMethodRound::executeMethod(): " + string("math.round") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.round(2.87): ", math.round(2.87))
	{
		const ScriptStatement& statement = scripts[3].statements[135];
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
				Console::println("ScriptMethodRound::executeMethod(): " + string("math.round") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.cos(0.0): ", math.cos(0.0))
	{
		const ScriptStatement& statement = scripts[3].statements[136];
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
				Console::println("ScriptMethodCos::executeMethod(): " + string("math.cos") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.sin(0.0): ", math.sin(0.0))
	{
		const ScriptStatement& statement = scripts[3].statements[137];
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
				Console::println("ScriptMethodSin::executeMethod(): " + string("math.sin") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.tan(1.0): ", math.tan(1.0))
	{
		const ScriptStatement& statement = scripts[3].statements[138];
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
				Console::println("ScriptMethodTan::executeMethod(): " + string("math.tan") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.sqrt(9.0): ", math.sqrt(9))
	{
		const ScriptStatement& statement = scripts[3].statements[139];
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
				Console::println("ScriptMethodSqrt::executeMethod(): " + string("math.sqrt") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.random(): ", math.random())
	{
		const ScriptStatement& statement = scripts[3].statements[140];
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

	// Statement: 141
	// console.log("math.exp(1.0): ", math.exp(1.0))
	{
		const ScriptStatement& statement = scripts[3].statements[141];
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
				Console::println("ScriptMethodExp::executeMethod(): " + string("math.exp") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.log(2.0): ", math.log(2.0))
	{
		const ScriptStatement& statement = scripts[3].statements[142];
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
				Console::println("ScriptMethodLog::executeMethod(): " + string("math.log") + "(): parameter type mismatch @ argument 0: float expected");
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
	// console.log("math.sign(-2): ", math.sign(-2))
	{
		const ScriptStatement& statement = scripts[3].statements[143];
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
				Console::println("ScriptMethodSign::executeMethod(): " + string("math.sign") + "(): parameter type mismatch @ argument 0: float or integer expected");
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
	// console.log("math.sign(-2.0): ", math.sign(-2.0))
	{
		const ScriptStatement& statement = scripts[3].statements[144];
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
				Console::println("ScriptMethodSign::executeMethod(): " + string("math.sign") + "(): parameter type mismatch @ argument 0: float or integer expected");
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
	// console.log("math.square(3): ", math.square(3))
	{
		const ScriptStatement& statement = scripts[3].statements[145];
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
				Console::println("ScriptMethodSquare::executeMethod(): " + string("math.square") + "(): parameter type mismatch @ argument 0: float or integer expected");
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
	// console.log("math.square(3.0): ", math.square(3.0))
	{
		const ScriptStatement& statement = scripts[3].statements[146];
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
				Console::println("ScriptMethodSquare::executeMethod(): " + string("math.square") + "(): parameter type mismatch @ argument 0: float or integer expected");
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
	// console.log("math.min(4, 9): ", math.min(4, 9))
	{
		const ScriptStatement& statement = scripts[3].statements[147];
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
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 148
	// console.log("math.min(4.1, 9.3): ", math.min(4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[3].statements[148];
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
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodMin::executeMethod(): " + string("math.min") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 149
	// console.log("math.max(4, 9): ", math.max(4, 9))
	{
		const ScriptStatement& statement = scripts[3].statements[149];
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
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 150
	// console.log("math.max(4.1, 9.3): ", math.max(4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[3].statements[150];
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
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodMax::executeMethod(): " + string("math.max") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 151
	// console.log("math.abs(-9): ", math.abs(-9))
	{
		const ScriptStatement& statement = scripts[3].statements[151];
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
				Console::println("ScriptMethodAbs::executeMethod(): " + string("math.abs") + "(): parameter type mismatch @ argument 0: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 152
	// console.log("math.abs(-9.3): ", math.abs(-9.3))
	{
		const ScriptStatement& statement = scripts[3].statements[152];
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
				Console::println("ScriptMethodAbs::executeMethod(): " + string("math.abs") + "(): parameter type mismatch @ argument 0: float or integer expected");
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
	// console.log("math.clamp(-1, 4, 9): ", math.clamp(-1, 4, 9))
	{
		const ScriptStatement& statement = scripts[3].statements[153];
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 154
	// console.log("math.clamp(10.0, 4.1, 9.3): ", math.clamp(10.0, 4.1, 9.3))
	{
		const ScriptStatement& statement = scripts[3].statements[154];
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
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
				Console::println("ScriptMethodClamp::executeMethod(): " + string("math.clamp") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected, @ argument 2: float or integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 155
	// console.log("math.pow(2, 16): ", math.pow(2, 16))
	{
		const ScriptStatement& statement = scripts[3].statements[155];
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
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
	// console.log("math.pow(2.0, 16.0): ", math.pow(2.0, 16.0))
	{
		const ScriptStatement& statement = scripts[3].statements[156];
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
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
				Console::println("ScriptMethodPow::executeMethod(): " + string("math.pow") + "(): parameter type mismatch @ argument 0: float or integer expected, @ argument 1: float or integer expected");
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
	// console.log("math.mod(187, 180): ", math.mod(187, 180))
	{
		const ScriptStatement& statement = scripts[3].statements[157];
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
				Console::println("ScriptMethodMod::executeMethod(): " + string("math.mod") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 158
	// console.log("math.mod(-187, 180): ", math.mod(-187, 180))
	{
		const ScriptStatement& statement = scripts[3].statements[158];
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
				Console::println("ScriptMethodMod::executeMethod(): " + string("math.mod") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 159
	// console.log("math.absmod(187, 180): ", math.absmod(187, 180))
	{
		const ScriptStatement& statement = scripts[3].statements[159];
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
				Console::println("ScriptMethodAbsMod::executeMethod(): " + string("math.absmod") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("math.absmod(-187, 180): ", math.absmod(-187, 180))
	{
		const ScriptStatement& statement = scripts[3].statements[160];
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
				Console::println("ScriptMethodAbsMod::executeMethod(): " + string("math.absmod") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[161];
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

	// Statement: 162
	// console.log("Check transform")
	{
		const ScriptStatement& statement = scripts[3].statements[162];
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

	// Statement: 163
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[163];
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

	// Statement: 164
	// setVariable("$transform", transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[3].statements[164];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transform"));
		// argumentValues[1] --> returnValue of transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1,2,3)
			// argumentValues[1] --> returnValue of vec3(2, 3, 4)
			// argumentValues[2] --> returnValue of vec3(0, 1, 0)
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform
			Transform transform;
			Vector3 vec3Value;
			if (argumentValues.size() >= 1) {
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
					transform.setTranslation(vec3Value);
				} else {
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			if (argumentValues.size() >= 2) {
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
					transform.setScale(vec3Value);
				} else {
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): parameter type mismatch @ argument 1: vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			for (auto i = 2; i < argumentValues.size(); i++) {
				if (MiniScript::getVector3Value(argumentValues, i, vec3Value, true) == true) {
					transform.addRotation(vec3Value, 0.0f);
				} else {
					Console::println("ScriptMethodTransform::executeMethod(): " + string("transform") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 165
	// setVariable("$transform", transform.setRotationAngle($transform, 0, 90))
	{
		const ScriptStatement& statement = scripts[3].statements[165];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transform"));
		// argumentValues[1] --> returnValue of transform.setRotationAngle($transform, 0, 90)
		// depth = 1 / argument index = 1: transform.setRotationAngle($transform, 0, 90)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			argumentValues[2].setValue(static_cast<int64_t>(90));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					returnValue.setValue(transform);
				} else {
					Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected, @ argument 2: float expected");
				miniScript->startErrorScript(); return;
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

	// Statement: 166
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): ", $transform)
	{
		const ScriptStatement& statement = scripts[3].statements[166];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): "));
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

	// Statement: 167
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): ", transform.getTranslation($transform))
	{
		const ScriptStatement& statement = scripts[3].statements[167];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): "));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getTranslation
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getTranslation());
			} else {
				Console::println("ScriptMethodTransformGetTranslation::executeMethod(): " + string("transform.getTranslation") + "(): parameter type mismatch @ argument 0: transform expected");
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
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): ", transform.setTranslation($transform, vec3(-1,-2,-3)))
	{
		const ScriptStatement& statement = scripts[3].statements[168];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): "));
		// argumentValues[1] --> returnValue of transform.setTranslation($transform, vec3(-1,-2,-3))
		// depth = 1 / argument index = 1: transform.setTranslation($transform, vec3(-1,-2,-3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// argumentValues[1] --> returnValue of vec3(-1,-2,-3)
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(-1, -2, -3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				returnValue.setValue(transform);
			} else {
				Console::println("ScriptMethodTransformSetTranslation::executeMethod(): " + string("transform.setTranslation") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
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
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): ", transform.getScale($transform))
	{
		const ScriptStatement& statement = scripts[3].statements[169];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): "));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transform.getScale
			Transform transform;
			if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
				returnValue.setValue(transform.getScale());
			} else {
				Console::println("ScriptMethodTransformGetScale::executeMethod(): " + string("transform.getScale") + "(): parameter type mismatch @ argument 0: transform expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 170
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): ", transform.setScale($transform, vec3(-2,-3,-4)))
	{
		const ScriptStatement& statement = scripts[3].statements[170];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): "));
		// argumentValues[1] --> returnValue of transform.setScale($transform, vec3(-2,-3,-4))
		// depth = 1 / argument index = 1: transform.setScale($transform, vec3(-2,-3,-4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			// argumentValues[1] --> returnValue of vec3(-2,-3,-4)
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(-2, -3, -4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				returnValue.setValue(transform);
			} else {
				Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.setScale") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 171
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): ", transform.getRotationAxis($transform, 0))
	{
		const ScriptStatement& statement = scripts[3].statements[171];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): "));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodTransformGetRotationAxis::executeMethod(): " + string("transform.getRotationAxis") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformGetRotationAxis::executeMethod(): " + string("transform.getRotationAxis") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 172
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): ", transform.getRotationAngle($transform, 0))
	{
		const ScriptStatement& statement = scripts[3].statements[172];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): "));
		// argumentValues[1] --> returnValue of transform.getRotationAngle($transform, 0)
		// depth = 1 / argument index = 1: transform.getRotationAngle($transform, 0)
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodTransformGetRotationAngle::executeMethod(): " + string("transform.getRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformGetRotationAngle::executeMethod(): " + string("transform.getRotationAngle") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 173
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): ", transform.setRotationAngle($transform, 0, 90))
	{
		const ScriptStatement& statement = scripts[3].statements[173];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): "));
		// argumentValues[1] --> returnValue of transform.setRotationAngle($transform, 0, 90)
		// depth = 1 / argument index = 1: transform.setRotationAngle($transform, 0, 90)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transform")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			argumentValues[2].setValue(static_cast<int64_t>(90));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					returnValue.setValue(transform);
				} else {
					Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformSetRotationAngle::executeMethod(): " + string("transform.setRotationAngle") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: integer expected, @ argument 2: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 174
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): ", transform.multiply($transform, vec3(0,0,0)))
	{
		const ScriptStatement& statement = scripts[3].statements[174];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): "));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.multiply") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 175
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): ", transform.rotate($transform, vec3(0,0,1)))
	{
		const ScriptStatement& statement = scripts[3].statements[175];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): "));
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
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
				Console::println("ScriptMethodTransformSetScale::executeMethod(): " + string("transform.rotate") + "(): parameter type mismatch @ argument 0: transform expected, @ argument 1: vector3 expected");
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
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[176];
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

	// Statement: 177
	// console.log("Check string functions")
	{
		const ScriptStatement& statement = scripts[3].statements[177];
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

	// Statement: 178
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[178];
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
	// console.log(space(0), "1")
	{
		const ScriptStatement& statement = scripts[3].statements[179];
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
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
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

	// Statement: 180
	// console.log(space(2), "1.1")
	{
		const ScriptStatement& statement = scripts[3].statements[180];
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
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
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

	// Statement: 181
	// console.log(space(2), "1.2")
	{
		const ScriptStatement& statement = scripts[3].statements[181];
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
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
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

	// Statement: 182
	// console.log(toUpperCase("xxxyyyzzz"))
	{
		const ScriptStatement& statement = scripts[3].statements[182];
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
				Console::println("ScriptMethodToUpperCase::executeMethod(): " + string("toUpperCase") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 183
	// console.log(toLowerCase("XXXYYYZZZ"))
	{
		const ScriptStatement& statement = scripts[3].statements[183];
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
				Console::println("ScriptMethodToLowerCase::executeMethod(): " + string("toLowerCase") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 184
	// console.log(concatenate("abc", "def", "ghi"))
	{
		const ScriptStatement& statement = scripts[3].statements[184];
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

	// Statement: 185
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[185];
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

	// Statement: 186
	// console.log("Check string functions (Operators)")
	{
		const ScriptStatement& statement = scripts[3].statements[186];
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

	// Statement: 187
	// console.log(add("abc",add("def", "ghi")))
	{
		const ScriptStatement& statement = scripts[3].statements[187];
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

	// Statement: 188
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[188];
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

	// Statement: 189
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[189];
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

	// Statement: 190
	// console.log("Variable")
	{
		const ScriptStatement& statement = scripts[3].statements[190];
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

	// Statement: 191
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[191];
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

	// Statement: 192
	// setVariable("$variable", string("1234"))
	{
		const ScriptStatement& statement = scripts[3].statements[192];
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
				Console::println("ScriptMethodString::executeMethod(): " + string("string") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
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

	// Statement: 193
	// console.log(getVariable("$variable"))
	{
		const ScriptStatement& statement = scripts[3].statements[193];
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

	// Statement: 194
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[194];
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

	// Statement: 195
	// console.log("Lets check forTime")
	{
		const ScriptStatement& statement = scripts[3].statements[195];
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

	// Statement: 196
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[196];
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

	// Statement: 197
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[3].statements[197];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 198
	miniscript_statement_198:
	// forTime(2000)
	{
		const ScriptStatement& statement = scripts[3].statements[198];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
		// method code: forTime
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
			Console::println("ScriptMethodForTime::executeMethod(): " + string("forTime") + "(): parameter type mismatch @ argument 0: integer expected");
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
				goto miniscript_statement_203;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 199
	miniscript_statement_199:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[3].statements[199];
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

	// Statement: 200
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[3].statements[200];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 201
	miniscript_statement_201:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[201];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 202
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[202];
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
				goto miniscript_statement_198;
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

	// Statement: 203
	miniscript_statement_203:
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[203];
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

	// Statement: 204
	// console.log("Lets check forCondition")
	{
		const ScriptStatement& statement = scripts[3].statements[204];
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

	// Statement: 205
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[205];
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

	// Statement: 206
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[3].statements[206];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 207
	miniscript_statement_207:
	// forCondition(notequal($i, 6))
	{
		const ScriptStatement& statement = scripts[3].statements[207];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: notequal
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_212;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 208
	miniscript_statement_208:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[3].statements[208];
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

	// Statement: 209
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[3].statements[209];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 210
	miniscript_statement_210:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[210];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 211
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[211];
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
				goto miniscript_statement_207;
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

	// Statement: 212
	miniscript_statement_212:
	// console.log("i -> ", $i)
	{
		const ScriptStatement& statement = scripts[3].statements[212];
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

	// Statement: 213
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[213];
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

	// Statement: 214
	// console.log("Lets check forCondition with if/elseif/else")
	{
		const ScriptStatement& statement = scripts[3].statements[214];
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

	// Statement: 215
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[215];
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

	// Statement: 216
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[3].statements[216];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 217
	miniscript_statement_217:
	// forCondition(lesser($i, 5))
	{
		const ScriptStatement& statement = scripts[3].statements[217];
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_232;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 218
	miniscript_statement_218:
	// console.log($i, ":")
	{
		const ScriptStatement& statement = scripts[3].statements[218];
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

	// Statement: 219
	// if(equals($i, 0))
	{
		const ScriptStatement& statement = scripts[3].statements[219];
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
			miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->getScriptState().conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_221;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 220
	miniscript_statement_220:
	// console.log("i -> 0")
	{
		const ScriptStatement& statement = scripts[3].statements[220];
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

	// Statement: 221
	miniscript_statement_221:
	// elseif(equals($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[221];
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_223;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 222
	miniscript_statement_222:
	// console.log("i -> 1")
	{
		const ScriptStatement& statement = scripts[3].statements[222];
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

	// Statement: 223
	miniscript_statement_223:
	// elseif(equals($i, 2))
	{
		const ScriptStatement& statement = scripts[3].statements[223];
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_225;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 224
	miniscript_statement_224:
	// console.log("i -> 2")
	{
		const ScriptStatement& statement = scripts[3].statements[224];
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

	// Statement: 225
	miniscript_statement_225:
	// elseif(equals($i, 3))
	{
		const ScriptStatement& statement = scripts[3].statements[225];
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
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
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
				goto miniscript_statement_227;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 226
	miniscript_statement_226:
	// console.log("i -> 3")
	{
		const ScriptStatement& statement = scripts[3].statements[226];
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

	// Statement: 227
	miniscript_statement_227:
	// else()
	{
		const ScriptStatement& statement = scripts[3].statements[227];
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
				goto miniscript_statement_229;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 228
	miniscript_statement_228:
	// console.log("else: ", $i)
	{
		const ScriptStatement& statement = scripts[3].statements[228];
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

	// Statement: 229
	miniscript_statement_229:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[229];
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

	// Statement: 230
	miniscript_statement_230:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[230];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 231
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[231];
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
				goto miniscript_statement_217;
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

	// Statement: 232
	miniscript_statement_232:
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[3].statements[232];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 233
	// setVariable("$j", 2)
	{
		const ScriptStatement& statement = scripts[3].statements[233];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 234
	// setVariable("$k", 3)
	{
		const ScriptStatement& statement = scripts[3].statements[234];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 235
	// if(or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k)))
	{
		const ScriptStatement& statement = scripts[3].statements[235];
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			// method code: or
			returnValue.setValue(false);
			for (auto i = 0; i < argumentValues.size(); i++) {
				bool booleanValue;
				if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
					Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
					miniScript->startErrorScript(); return;
				} else
				if (booleanValue == true) {
					returnValue.setValue(true);
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
			miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->getScriptState().conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_237;
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 236
	miniscript_statement_236:
	// console.log("This should not happen, but look ok in preprocessor processed output")
	{
		const ScriptStatement& statement = scripts[3].statements[236];
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

	// Statement: 237
	miniscript_statement_237:
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[237];
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

	// Statement: 238
	miniscript_statement_238:
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[238];
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

	// Statement: 239
	// console.log(add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")")))))
	{
		const ScriptStatement& statement = scripts[3].statements[239];
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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

	// Statement: 240
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[240];
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

	// Statement: 241
	// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), " = 17")
	{
		const ScriptStatement& statement = scripts[3].statements[241];
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

	// Statement: 242
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[3].statements[242];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 243
	// console.log("Arrays")
	{
		const ScriptStatement& statement = scripts[3].statements[243];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 244
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[3].statements[244];
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

	// Statement: 245
	// setVariable("$array", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[3].statements[245];
		getScriptState().statementIdx = statement.statementIdx;
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
			returnValue.setType(MiniScript::TYPE_ARRAY);
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

	// Statement: 246
	// console.log("array initialized with: $array = array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[3].statements[246];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 247
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[3].statements[247];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 248
	// setVariable("$array", array.push($array, 8, 9, 10, 99, 10))
	{
		const ScriptStatement& statement = scripts[3].statements[248];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array.push($array, 8, 9, 10, 99, 10)
		// depth = 1 / argument index = 1: array.push($array, 8, 9, 10, 99, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 6> argumentValues;
			array<ScriptVariable, 6>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(8));
			argumentValues[2].setValue(static_cast<int64_t>(9));
			argumentValues[3].setValue(static_cast<int64_t>(10));
			argumentValues[4].setValue(static_cast<int64_t>(99));
			argumentValues[5].setValue(static_cast<int64_t>(10));
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

	// Statement: 249
	// console.log("array pushed values with: array.push($array, 8, 9, 10, 99, 10)")
	{
		const ScriptStatement& statement = scripts[3].statements[249];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array pushed values with: array.push($array, 8, 9, 10, 99, 10)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 250
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[3].statements[250];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 251
	// setVariable("$array[]", 123)
	{
		const ScriptStatement& statement = scripts[3].statements[251];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 252
	// setVariable("$array[]", 1234)
	{
		const ScriptStatement& statement = scripts[3].statements[252];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 253
	// setVariable("$array[]", 12345)
	{
		const ScriptStatement& statement = scripts[3].statements[253];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 254
	// setVariable("$array[]", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[3].statements[254];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[]"));
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
			returnValue.setType(MiniScript::TYPE_ARRAY);
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

	// Statement: 255
	// console.log("array values added with [] operator: 123, 1234, 12345, array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[3].statements[255];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array values added with [] operator: 123, 1234, 12345, array(1,2,3)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 256
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[3].statements[256];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 257
	// console.log("array values added with [] operator to push to array of array: 50, 60")
	{
		const ScriptStatement& statement = scripts[3].statements[257];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array values added with [] operator to push to array of array: 50, 60"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 258
	// setVariable("$array[11][]", 50)
	{
		const ScriptStatement& statement = scripts[3].statements[258];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[11][]"));
		argumentValues[1].setValue(static_cast<int64_t>(50));
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

	// Statement: 259
	// setVariable("$array[11][]", 60)
	{
		const ScriptStatement& statement = scripts[3].statements[259];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[11][]"));
		argumentValues[1].setValue(static_cast<int64_t>(60));
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

	// Statement: 260
	// setVariable("$array[11][sub(array.length($array[11]), 1)]", 61)
	{
		const ScriptStatement& statement = scripts[3].statements[260];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array[11][sub(array.length($array[11]), 1)]"));
		argumentValues[1].setValue(static_cast<int64_t>(61));
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

	// Statement: 261
	// console.log("array length: ", array.length($array))
	{
		const ScriptStatement& statement = scripts[3].statements[261];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 262
	// console.log("array iteration with array.get(): ")
	{
		const ScriptStatement& statement = scripts[3].statements[262];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 263
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[263];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 264
	miniscript_statement_264:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[3].statements[264];
		getScriptState().statementIdx = statement.statementIdx;
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_268;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 265
	miniscript_statement_265:
	// console.log(add($i,add(": ", array.get($array, $i))))
	{
		const ScriptStatement& statement = scripts[3].statements[265];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 266
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[266];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 267
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[267];
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
				goto miniscript_statement_264;
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

	// Statement: 268
	miniscript_statement_268:
	// console.log("array iteration with [] operator: ")
	{
		const ScriptStatement& statement = scripts[3].statements[268];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 269
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[269];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 270
	miniscript_statement_270:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[3].statements[270];
		getScriptState().statementIdx = statement.statementIdx;
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_274;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 271
	miniscript_statement_271:
	// console.log(add($i,add(": ", $array[$i])))
	{
		const ScriptStatement& statement = scripts[3].statements[271];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($i,add(": ", $array[$i]))
		// depth = 1 / argument index = 0: add($i, add(": ", $array[$i]))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of add(": ", $array[$i])
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
			// depth = 2 / argument index = 1: add(": ", $array[$i])
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(": "));
				// argumentValues[1] --> returnValue of getVariable("$array[$i]")
				// depth = 3 / argument index = 1: getVariable("$array[$i]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$array[$i]"));
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

	// Statement: 272
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[272];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 273
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[273];
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
				goto miniscript_statement_270;
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

	// Statement: 274
	miniscript_statement_274:
	// console.log("array iteration with [] opertator and some index math: ")
	{
		const ScriptStatement& statement = scripts[3].statements[274];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array iteration with [] opertator and some index math: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 275
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[275];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 276
	miniscript_statement_276:
	// forCondition(lesser($i,div(array.length($array), 2)))
	{
		const ScriptStatement& statement = scripts[3].statements[276];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i,div(array.length($array), 2))
		// depth = 1 / argument index = 0: lesser($i, div(array.length($array), 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of div(array.length($array), 2)
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
			// depth = 2 / argument index = 1: div(array.length($array), 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of array.length($array)
				argumentValues[1].setValue(static_cast<int64_t>(2));
				// depth = 3 / argument index = 0: array.length($array)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$array")
					// depth = 4 / argument index = 0: getVariable("$array")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[0];
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
					// method code: array.length
					if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
						Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): parameter type mismatch @ argument 0: array expected");
					} else {
						returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
					}
				}
				// method code: div
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
			}
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_281;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 277
	miniscript_statement_277:
	// console.log(add($i,add("-a: ", $array[add(mul($i, 2), 0)])))
	{
		const ScriptStatement& statement = scripts[3].statements[277];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($i,add("-a: ", $array[add(mul($i, 2), 0)]))
		// depth = 1 / argument index = 0: add($i, add("-a: ", $array[add(mul($i, 2), 0)]))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of add("-a: ", $array[add(mul($i, 2), 0)])
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
			// depth = 2 / argument index = 1: add("-a: ", $array[add(mul($i, 2), 0)])
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("-a: "));
				// argumentValues[1] --> returnValue of getVariable("$array[add(mul($i, 2), 0)]")
				// depth = 3 / argument index = 1: getVariable("$array[add(mul($i, 2), 0)]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$array[add(mul($i, 2), 0)]"));
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

	// Statement: 278
	// console.log(add($i,add("-b: ", $array[add(mul($i, 2), 1)])))
	{
		const ScriptStatement& statement = scripts[3].statements[278];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($i,add("-b: ", $array[add(mul($i, 2), 1)]))
		// depth = 1 / argument index = 0: add($i, add("-b: ", $array[add(mul($i, 2), 1)]))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of add("-b: ", $array[add(mul($i, 2), 1)])
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
			// depth = 2 / argument index = 1: add("-b: ", $array[add(mul($i, 2), 1)])
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("-b: "));
				// argumentValues[1] --> returnValue of getVariable("$array[add(mul($i, 2), 1)]")
				// depth = 3 / argument index = 1: getVariable("$array[add(mul($i, 2), 1)]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$array[add(mul($i, 2), 1)]"));
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

	// Statement: 279
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[279];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 280
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[280];
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
				goto miniscript_statement_276;
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

	// Statement: 281
	miniscript_statement_281:
	// console.log("array removal of 123, 1234, 12345 using array.removeOf")
	{
		const ScriptStatement& statement = scripts[3].statements[281];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array removal of 123, 1234, 12345 using array.removeOf"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 282
	// setVariable("$array", array.removeOf($array, 123))
	{
		const ScriptStatement& statement = scripts[3].statements[282];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array.removeOf($array, 123)
		// depth = 1 / argument index = 1: array.removeOf($array, 123)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(123));
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
			// method code: array.removeOf
			string stringValue;
			int64_t index;
			if (argumentValues.size() != 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
				MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
			} else {
				auto& array = argumentValues[0];
				returnValue.setType(ScriptVariableType::TYPE_ARRAY);
				for (auto i = 0; i < array.getArraySize(); i++) {
					auto arrayValue = array.getArrayValue(i);
					if (arrayValue.getValueString() == stringValue) continue;
					returnValue.pushArrayValue(arrayValue);
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

	// Statement: 283
	// setVariable("$array", array.removeOf($array, 1234))
	{
		const ScriptStatement& statement = scripts[3].statements[283];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array.removeOf($array, 1234)
		// depth = 1 / argument index = 1: array.removeOf($array, 1234)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(1234));
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
			// method code: array.removeOf
			string stringValue;
			int64_t index;
			if (argumentValues.size() != 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
				MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
			} else {
				auto& array = argumentValues[0];
				returnValue.setType(ScriptVariableType::TYPE_ARRAY);
				for (auto i = 0; i < array.getArraySize(); i++) {
					auto arrayValue = array.getArrayValue(i);
					if (arrayValue.getValueString() == stringValue) continue;
					returnValue.pushArrayValue(arrayValue);
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

	// Statement: 284
	// setVariable("$array", array.removeOf($array, 12345))
	{
		const ScriptStatement& statement = scripts[3].statements[284];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$array"));
		// argumentValues[1] --> returnValue of array.removeOf($array, 12345)
		// depth = 1 / argument index = 1: array.removeOf($array, 12345)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(12345));
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
			// method code: array.removeOf
			string stringValue;
			int64_t index;
			if (argumentValues.size() != 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
				MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
			} else {
				auto& array = argumentValues[0];
				returnValue.setType(ScriptVariableType::TYPE_ARRAY);
				for (auto i = 0; i < array.getArraySize(); i++) {
					auto arrayValue = array.getArrayValue(i);
					if (arrayValue.getValueString() == stringValue) continue;
					returnValue.pushArrayValue(arrayValue);
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

	// Statement: 285
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[3].statements[285];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 286
	// console.log("array indexOf 10: ", array.indexOf($array, 10))
	{
		const ScriptStatement& statement = scripts[3].statements[286];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array indexOf 10: "));
		// argumentValues[1] --> returnValue of array.indexOf($array, 10)
		// depth = 1 / argument index = 1: array.indexOf($array, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(10));
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
			// method code: array.indexOf
			string stringValue;
			int64_t beginIndex = 0;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
				MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.indexOf") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
			} else {
				auto& array = argumentValues[0];
				returnValue.setValue(static_cast<int64_t>(-1));
				for (auto i = beginIndex; i < array.getArraySize(); i++) {
					auto arrayValue = array.getArrayValue(i);
					if (arrayValue.getValueString() == stringValue) {
						returnValue.setValue(static_cast<int64_t>(i));
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

	// Statement: 287
	// console.log("array indexOf 10 beginning to search from 6: ", array.indexOf($array, 10, 6))
	{
		const ScriptStatement& statement = scripts[3].statements[287];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("array indexOf 10 beginning to search from 6: "));
		// argumentValues[1] --> returnValue of array.indexOf($array, 10, 6)
		// depth = 1 / argument index = 1: array.indexOf($array, 10, 6)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$array")
			argumentValues[1].setValue(static_cast<int64_t>(10));
			argumentValues[2].setValue(static_cast<int64_t>(6));
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
			// method code: array.indexOf
			string stringValue;
			int64_t beginIndex = 0;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
				MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
				MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.indexOf") + "(): parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
			} else {
				auto& array = argumentValues[0];
				returnValue.setValue(static_cast<int64_t>(-1));
				for (auto i = beginIndex; i < array.getArraySize(); i++) {
					auto arrayValue = array.getArrayValue(i);
					if (arrayValue.getValueString() == stringValue) {
						returnValue.setValue(static_cast<int64_t>(i));
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

	// Statement: 288
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[3].statements[288];
		getScriptState().statementIdx = statement.statementIdx;
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

	// Statement: 289
	// console.log("Maps")
	{
		const ScriptStatement& statement = scripts[3].statements[289];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Maps"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 290
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[3].statements[290];
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

	// Statement: 291
	// setVariable("$map", map())
	{
		const ScriptStatement& statement = scripts[3].statements[291];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map()
		// depth = 1 / argument index = 1: map()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: map
			returnValue.setType(MiniScript::TYPE_MAP);
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

	// Statement: 292
	// console.log("map initialized with: $map = map()")
	{
		const ScriptStatement& statement = scripts[3].statements[292];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map initialized with: $map = map()"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 293
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[3].statements[293];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$map")
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map"));
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

	// Statement: 294
	// console.log("put some key value pairs into map: $map = map.set()")
	{
		const ScriptStatement& statement = scripts[3].statements[294];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("put some key value pairs into map: $map = map.set()"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 295
	// setVariable("$map", map.set($map, "test1", 123))
	{
		const ScriptStatement& statement = scripts[3].statements[295];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test1", 123)
		// depth = 1 / argument index = 1: map.set($map, "test1", 123)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test1"));
			argumentValues[2].setValue(static_cast<int64_t>(123));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 296
	// setVariable("$map", map.set($map, "test2", 456))
	{
		const ScriptStatement& statement = scripts[3].statements[296];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test2", 456)
		// depth = 1 / argument index = 1: map.set($map, "test2", 456)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test2"));
			argumentValues[2].setValue(static_cast<int64_t>(456));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 297
	// setVariable("$map", map.set($map, "test3", 789))
	{
		const ScriptStatement& statement = scripts[3].statements[297];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test3", 789)
		// depth = 1 / argument index = 1: map.set($map, "test3", 789)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test3"));
			argumentValues[2].setValue(static_cast<int64_t>(789));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 298
	// setVariable("$map", map.set($map, "test4", array(1,2,3)))
	{
		const ScriptStatement& statement = scripts[3].statements[298];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test4", array(1,2,3))
		// depth = 1 / argument index = 1: map.set($map, "test4", array(1,2,3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test4"));
			// argumentValues[2] --> returnValue of array(1,2,3)
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 2: array(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX2 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: array
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (auto& argumentValue: argumentValues) {
					returnValue.pushArrayValue(argumentValue);
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 299
	// setVariable("$map", map.set($map, "test5", "Yaaaa"))
	{
		const ScriptStatement& statement = scripts[3].statements[299];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test5", "Yaaaa")
		// depth = 1 / argument index = 1: map.set($map, "test5", "Yaaaa")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test5"));
			argumentValues[2].setValue(string("Yaaaa"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 300
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[3].statements[300];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$map")
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map"));
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

	// Statement: 301
	// console.log("remove test2 via map.remove: ")
	{
		const ScriptStatement& statement = scripts[3].statements[301];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("remove test2 via map.remove: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 302
	// setVariable("$map", map.remove($map, "test2"))
	{
		const ScriptStatement& statement = scripts[3].statements[302];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.remove($map, "test2")
		// depth = 1 / argument index = 1: map.remove($map, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test2"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.remove
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapHas::executeMethod(): " + string("map.remove") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0];
				returnValue.removeMapValue(key);
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

	// Statement: 303
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[3].statements[303];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$map")
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map"));
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

	// Statement: 304
	// setVariable("$map", map.set($map, "test2", 456))
	{
		const ScriptStatement& statement = scripts[3].statements[304];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map"));
		// argumentValues[1] --> returnValue of map.set($map, "test2", 456)
		// depth = 1 / argument index = 1: map.set($map, "test2", 456)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test2"));
			argumentValues[2].setValue(static_cast<int64_t>(456));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.set
			//
			string key;
			if (argumentValues.size() < 3 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
			} else {
				returnValue = argumentValues[0];
				returnValue.setMapValue(key, argumentValues[2]);
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

	// Statement: 305
	// console.log("readding test2: ")
	{
		const ScriptStatement& statement = scripts[3].statements[305];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("readding test2: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 306
	// console.log("map does have test2 key using map.has(): ", map.has($map, "test2"))
	{
		const ScriptStatement& statement = scripts[3].statements[306];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map does have test2 key using map.has(): "));
		// argumentValues[1] --> returnValue of map.has($map, "test2")
		// depth = 1 / argument index = 1: map.has($map, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test2"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapHas::executeMethod(): " + string("map.has") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasMapValue(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 307
	// console.log("map does have test8 key using map.has(): ", map.has($map, "test8"))
	{
		const ScriptStatement& statement = scripts[3].statements[307];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map does have test8 key using map.has(): "));
		// argumentValues[1] --> returnValue of map.has($map, "test8")
		// depth = 1 / argument index = 1: map.has($map, "test8")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test8"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapHas::executeMethod(): " + string("map.has") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasMapValue(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 308
	// console.log("map value for test1 key using map.get(): ", map.get($map, "test1"))
	{
		const ScriptStatement& statement = scripts[3].statements[308];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test1 key using map.get(): "));
		// argumentValues[1] --> returnValue of map.get($map, "test1")
		// depth = 1 / argument index = 1: map.get($map, "test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test1"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0].getMapValue(key);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 309
	// console.log("map value for test2 key using map.get(): ", map.get($map, "test2"))
	{
		const ScriptStatement& statement = scripts[3].statements[309];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test2 key using map.get(): "));
		// argumentValues[1] --> returnValue of map.get($map, "test2")
		// depth = 1 / argument index = 1: map.get($map, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test2"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0].getMapValue(key);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 310
	// console.log("map value for test3 key using map.get(): ", map.get($map, "test3"))
	{
		const ScriptStatement& statement = scripts[3].statements[310];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test3 key using map.get(): "));
		// argumentValues[1] --> returnValue of map.get($map, "test3")
		// depth = 1 / argument index = 1: map.get($map, "test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test3"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0].getMapValue(key);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 311
	// console.log("map value for test4 key using map.get(): ", map.get($map, "test4"))
	{
		const ScriptStatement& statement = scripts[3].statements[311];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test4 key using map.get(): "));
		// argumentValues[1] --> returnValue of map.get($map, "test4")
		// depth = 1 / argument index = 1: map.get($map, "test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test4"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0].getMapValue(key);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 312
	// console.log("map value for test5 key using map.get(): ", map.get($map, "test5"))
	{
		const ScriptStatement& statement = scripts[3].statements[312];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test5 key using map.get(): "));
		// argumentValues[1] --> returnValue of map.get($map, "test5")
		// depth = 1 / argument index = 1: map.get($map, "test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			argumentValues[1].setValue(string("test5"));
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
			} else {
				returnValue = argumentValues[0].getMapValue(key);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 313
	// console.log("map value for test1 using map dot operator: ", $map.test1)
	{
		const ScriptStatement& statement = scripts[3].statements[313];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test1 using map dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$map.test1")
		// depth = 1 / argument index = 1: getVariable("$map.test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map.test1"));
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

	// Statement: 314
	// console.log("map value for test2 using map dot operator: ", $map.test2)
	{
		const ScriptStatement& statement = scripts[3].statements[314];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test2 using map dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$map.test2")
		// depth = 1 / argument index = 1: getVariable("$map.test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map.test2"));
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

	// Statement: 315
	// console.log("map value for test3 using map dot operator: ", $map.test3)
	{
		const ScriptStatement& statement = scripts[3].statements[315];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test3 using map dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$map.test3")
		// depth = 1 / argument index = 1: getVariable("$map.test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map.test3"));
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

	// Statement: 316
	// console.log("map value for test4 using map dot operator: ", $map.test4)
	{
		const ScriptStatement& statement = scripts[3].statements[316];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test4 using map dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$map.test4")
		// depth = 1 / argument index = 1: getVariable("$map.test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map.test4"));
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

	// Statement: 317
	// console.log("map value for test5 using map dot operator: ", $map.test5)
	{
		const ScriptStatement& statement = scripts[3].statements[317];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map value for test5 using map dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$map.test5")
		// depth = 1 / argument index = 1: getVariable("$map.test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$map.test5"));
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

	// Statement: 318
	// console.log("adding map values using map dot operator: ")
	{
		const ScriptStatement& statement = scripts[3].statements[318];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("adding map values using map dot operator: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 319
	// setVariable("$map.test6", 666)
	{
		const ScriptStatement& statement = scripts[3].statements[319];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map.test6"));
		argumentValues[1].setValue(static_cast<int64_t>(666));
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

	// Statement: 320
	// setVariable("$map.test7", 770)
	{
		const ScriptStatement& statement = scripts[3].statements[320];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map.test7"));
		argumentValues[1].setValue(static_cast<int64_t>(770));
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

	// Statement: 321
	// setVariable("$map.test8", 890)
	{
		const ScriptStatement& statement = scripts[3].statements[321];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$map.test8"));
		argumentValues[1].setValue(static_cast<int64_t>(890));
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

	// Statement: 322
	// console.log("map keys: ", map.getKeys($map))
	{
		const ScriptStatement& statement = scripts[3].statements[322];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map keys: "));
		// argumentValues[1] --> returnValue of map.getKeys($map)
		// depth = 1 / argument index = 1: map.getKeys($map)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getKeys
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetKeys::executeMethod(): " + string("map.getKeys") + "(): parameter type mismatch @ argument 0: map expected");
			} else {
				auto keys = argumentValues[0].getMapKeys();
				returnValue.setType(TYPE_ARRAY);
				for (auto& key: keys) {
					returnValue.pushArrayValue(key);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 323
	// console.log("map values: ", map.getValues($map))
	{
		const ScriptStatement& statement = scripts[3].statements[323];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("map values: "));
		// argumentValues[1] --> returnValue of map.getValues($map)
		// depth = 1 / argument index = 1: map.getValues($map)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getValues
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetValues::executeMethod(): " + string("map.getValues") + "(): parameter type mismatch @ argument 0: map expected");
			} else {
				auto values = argumentValues[0].getMapValues();
				returnValue.setType(TYPE_ARRAY);
				for (auto& value: values) {
					returnValue.pushArrayValue(value);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 324
	// console.log("iterating keys and values using map.getKeys(): ")
	{
		const ScriptStatement& statement = scripts[3].statements[324];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("iterating keys and values using map.getKeys(): "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 325
	// setVariable("$mapKeys", map.getKeys($map))
	{
		const ScriptStatement& statement = scripts[3].statements[325];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$mapKeys"));
		// argumentValues[1] --> returnValue of map.getKeys($map)
		// depth = 1 / argument index = 1: map.getKeys($map)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$map")
			// depth = 2 / argument index = 0: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$map"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getKeys
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetKeys::executeMethod(): " + string("map.getKeys") + "(): parameter type mismatch @ argument 0: map expected");
			} else {
				auto keys = argumentValues[0].getMapKeys();
				returnValue.setType(TYPE_ARRAY);
				for (auto& key: keys) {
					returnValue.pushArrayValue(key);
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

	// Statement: 326
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[3].statements[326];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 327
	miniscript_statement_327:
	// forCondition(lesser($i, array.length($mapKeys)))
	{
		const ScriptStatement& statement = scripts[3].statements[327];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, array.length($mapKeys))
		// depth = 1 / argument index = 0: lesser($i, array.length($mapKeys))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			// argumentValues[1] --> returnValue of array.length($mapKeys)
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
			// depth = 2 / argument index = 1: array.length($mapKeys)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$mapKeys")
				// depth = 3 / argument index = 0: getVariable("$mapKeys")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$mapKeys"));
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
				miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				goto miniscript_statement_331;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 328
	miniscript_statement_328:
	// console.log(add($mapKeys[$i],add(" = ", map.get($map, $mapKeys[$i]))))
	{
		const ScriptStatement& statement = scripts[3].statements[328];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add($mapKeys[$i],add(" = ", map.get($map, $mapKeys[$i])))
		// depth = 1 / argument index = 0: add($mapKeys[$i], add(" = ", map.get($map, $mapKeys[$i])))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$mapKeys[$i]")
			// argumentValues[1] --> returnValue of add(" = ", map.get($map, $mapKeys[$i]))
			// depth = 2 / argument index = 0: getVariable("$mapKeys[$i]")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$mapKeys[$i]"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: add(" = ", map.get($map, $mapKeys[$i]))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(" = "));
				// argumentValues[1] --> returnValue of map.get($map, $mapKeys[$i])
				// depth = 3 / argument index = 1: map.get($map, $mapKeys[$i])
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$map")
					// argumentValues[1] --> returnValue of getVariable("$mapKeys[$i]")
					// depth = 4 / argument index = 0: getVariable("$map")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
						argumentValues[0].setValue(string("$map"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// depth = 4 / argument index = 1: getVariable("$mapKeys[$i]")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX1 = argumentValues;
						argumentValues[0].setValue(string("$mapKeys[$i]"));
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable);
						} else {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: map.get
					//
					string key;
					if (argumentValues.size() < 2 ||
						argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
						MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
						Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): parameter type mismatch @ argument 0: map expected, @ argument 1: string");
					} else {
						returnValue = argumentValues[0].getMapValue(key);
					}
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

	// Statement: 329
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[3].statements[329];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 330
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[330];
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
				goto miniscript_statement_327;
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

	// Statement: 331
	miniscript_statement_331:
	// console.log("-----------")
	{
		const ScriptStatement& statement = scripts[3].statements[331];
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

	// Statement: 332
	// console.log("Functions")
	{
		const ScriptStatement& statement = scripts[3].statements[332];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Functions"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 333
	// console.log("-----------")
	{
		const ScriptStatement& statement = scripts[3].statements[333];
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

	// Statement: 334
	// script.call(helloWorldFunction)
	{
		const ScriptStatement& statement = scripts[3].statements[334];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("helloWorldFunction"));
		// method code: script.call
		string function;
		if (miniScript->getStringValue(argumentValues, 0, function) == false) {
			Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): parameter type mismatch @ argument 0: string expected");
		} else {
			miniScript->call(function, span(argumentValues.begin() + 1, argumentValues.end()), returnValue);
		}
	}

	// Statement: 335
	// console.log(add("factorial(5) = ", factorial(5)))
	{
		const ScriptStatement& statement = scripts[3].statements[335];
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
			// depth = 2 / argument index = 1: script.call(factorial, 5)
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
					Console::println("ScriptMethodReturn::executeMethod(): " + string("script.call") + "(): parameter type mismatch @ argument 0: string expected");
				} else {
					miniScript->call(function, span(argumentValues.begin() + 1, argumentValues.end()), returnValue);
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

	// Statement: 336
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[336];
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

	// Statement: 337
	// console.log("Test if enabled naming condition will be emitted")
	{
		const ScriptStatement& statement = scripts[3].statements[337];
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

	// Statement: 338
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[338];
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

	// Statement: 339
	// script.enableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[3].statements[339];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.enableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
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

	// Statement: 340
	// script.wait(2000)
	{
		const ScriptStatement& statement = scripts[3].statements[340];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
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

	// Statement: 341
	miniscript_statement_341:
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[3].statements[341];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 342
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[342];
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

	// Statement: 343
	// console.log("Naming condition has not been emitted")
	{
		const ScriptStatement& statement = scripts[3].statements[343];
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

	// Statement: 344
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[3].statements[344];
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

	// Statement: 345
	// script.stop()
	{
		const ScriptStatement& statement = scripts[3].statements[345];
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

	// Statement: 346
	// end()
	{
		const ScriptStatement& statement = scripts[3].statements[346];
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

void MiniScriptTest::on_error(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx == 2) goto miniscript_statement_2; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("An error occurred")
	{
		const ScriptStatement& statement = scripts[4].statements[0];
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

	// Statement: 1
	// script.wait(1000)
	{
		const ScriptStatement& statement = scripts[4].statements[1];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 2
	miniscript_statement_2:
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

void MiniScriptTest::on_emittest(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(5, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 5;
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
		const ScriptStatement& statement = scripts[5].statements[0];
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
		const ScriptStatement& statement = scripts[5].statements[1];
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
		const ScriptStatement& statement = scripts[5].statements[2];
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
		const ScriptStatement& statement = scripts[5].statements[3];
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
		const ScriptStatement& statement = scripts[5].statements[4];
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
		const ScriptStatement& statement = scripts[5].statements[5];
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
		const ScriptStatement& statement = scripts[5].statements[6];
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
		const ScriptStatement& statement = scripts[5].statements[7];
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
		const ScriptStatement& statement = scripts[5].statements[8];
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
		const ScriptStatement& statement = scripts[5].statements[9];
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
		const ScriptStatement& statement = scripts[5].statements[10];
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
		const ScriptStatement& statement = scripts[5].statements[11];
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
				Console::println("ScriptMethodLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
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
		const ScriptStatement& statement = scripts[5].statements[12];
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
		const ScriptStatement& statement = scripts[5].statements[13];
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
		const ScriptStatement& statement = scripts[5].statements[14];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
		const ScriptStatement& statement = scripts[5].statements[15];
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
		const ScriptStatement& statement = scripts[5].statements[16];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
		const ScriptStatement& statement = scripts[5].statements[17];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
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
		const ScriptStatement& statement = scripts[5].statements[18];
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
		const ScriptStatement& statement = scripts[5].statements[19];
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
		const ScriptStatement& statement = scripts[5].statements[20];
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
		const ScriptStatement& statement = scripts[5].statements[21];
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
		const ScriptStatement& statement = scripts[5].statements[22];
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
		const ScriptStatement& statement = scripts[5].statements[23];
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
		const ScriptStatement& statement = scripts[5].statements[24];
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
		const ScriptStatement& statement = scripts[5].statements[25];
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

void MiniScriptTest::on_enabled_named_condition_1(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(6, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 6;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_enabled_named_condition_1(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[6].statements[0];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 1
	// console.log("------------------------------------")
	{
		const ScriptStatement& statement = scripts[6].statements[1];
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
		const ScriptStatement& statement = scripts[6].statements[2];
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
		const ScriptStatement& statement = scripts[6].statements[3];
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
		const ScriptStatement& statement = scripts[6].statements[4];
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
		const ScriptStatement& statement = scripts[6].statements[5];
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
		const ScriptStatement& statement = scripts[6].statements[6];
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
		const ScriptStatement& statement = scripts[6].statements[7];
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
		const ScriptStatement& statement = scripts[6].statements[8];
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
		const ScriptStatement& statement = scripts[6].statements[9];
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
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.emit") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// Statement: 10
	// end()
	{
		const ScriptStatement& statement = scripts[6].statements[10];
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
