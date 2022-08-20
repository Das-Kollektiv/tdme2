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
	setHash("f77f1bd00ef098f8f20c2b13b3cea95cde541ebbdab0c5075525ab0071e63826");
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
						.statement = "console.log(\"Nothing\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 13,
						.statementIdx = 2,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 14,
						.statementIdx = 3,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 15,
						.statementIdx = 4,
						.statement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "console.log(\"Check bool operations\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 17,
						.statementIdx = 6,
						.statement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 18,
						.statementIdx = 7,
						.statement = "console.log(\"MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): \", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))",
						.gotoStatementIdx = -1
					},
					{
						.line = 19,
						.statementIdx = 8,
						.statement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 20,
						.statementIdx = 9,
						.statement = "console.log(\"Check int computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 10,
						.statement = "console.log(\"-----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 22,
						.statementIdx = 11,
						.statement = "console.log(\"sub(add(1, 2, 3), 1)): \", sub(add(1, 2, 3), 1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 23,
						.statementIdx = 12,
						.statement = "console.log(\"div(20, 2): \", div(20, 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 24,
						.statementIdx = 13,
						.statement = "console.log(\"mul(11, 10): \", mul(11, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 25,
						.statementIdx = 14,
						.statement = "console.log(\"greater(2, 1): \", greater(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 15,
						.statement = "console.log(\"lesser(2, 1): \", lesser(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 16,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 17,
						.statement = "console.log(\"Check int computation (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 29,
						.statementIdx = 18,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 30,
						.statementIdx = 19,
						.statement = "console.log(\"1 + 2 + 3 - 1: \",sub(add(1,add(2, 3)), 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 20,
						.statement = "console.log(\"20 / 2: \",div(20, 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 21,
						.statement = "console.log(\"11 * 10: \",mul(11, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 22,
						.statement = "console.log(\"2 > 1: \",greater(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 23,
						.statement = "console.log(\"2 < 1: \",lesser(2, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 35,
						.statementIdx = 24,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 36,
						.statementIdx = 25,
						.statement = "console.log(\"Check float computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 37,
						.statementIdx = 26,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 38,
						.statementIdx = 27,
						.statement = "console.log(\"sub(add(1.1, 2.2, 3.3), 1.2)): \", sub(add(1.1, 2.2, 3.3), 1.2)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 28,
						.statement = "console.log(\"div(20, 1.5): \", div(20, 1.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 29,
						.statement = "console.log(\"mul(11.5, 10.5): \", mul(11.5, 10.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 41,
						.statementIdx = 30,
						.statement = "console.log(\"greater(2.2, 1.3): \", greater(2.2, 1.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 31,
						.statement = "console.log(\"lesser(2.5, 1.2): \", lesser(2.5, 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 32,
						.statement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 44,
						.statementIdx = 33,
						.statement = "console.log(\"Check float computation (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 34,
						.statement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 35,
						.statement = "console.log(\"(1.1 + 2.2 + 3.3) - 1.2: \",sub(add(1.1,add(2.2, 3.3)), 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 47,
						.statementIdx = 36,
						.statement = "console.log(\"20 / 1.5: \",div(20, 1.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 37,
						.statement = "console.log(\"11.5 * 10.5: \",mul(11.5, 10.5))",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 38,
						.statement = "console.log(\"2.2 > 1.3: \",greater(2.2, 1.3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 50,
						.statementIdx = 39,
						.statement = "console.log(\"2.5 < 1.2: \",lesser(2.5, 1.2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 40,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 41,
						.statement = "console.log(\"Check vector3 computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 42,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 54,
						.statementIdx = 43,
						.statement = "console.log(\"sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): \", sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 44,
						.statement = "console.log(\"div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): \", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 45,
						.statement = "console.log(\"mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): \", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 57,
						.statementIdx = 46,
						.statement = "console.log(\"div(vec3(20, 10, 5), 2): \", div(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 47,
						.statement = "console.log(\"mul(vec3(20, 10, 5), 2): \" ,mul(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 48,
						.statement = "console.log(\"vec3.computeLength(vec3(20, 10, 5)): \", vec3.computeLength(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 60,
						.statementIdx = 49,
						.statement = "console.log(\"vec3.computeLengthSquared(vec3(20, 10, 5)): \", vec3.computeLengthSquared(vec3(20, 10, 5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 50,
						.statement = "console.log(\"vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): \", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 51,
						.statement = "console.log(\"vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 52,
						.statement = "console.log(\"vec3.normalize(vec3(1, 2, 3)): \", vec3.normalize(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 64,
						.statementIdx = 53,
						.statement = "console.log(\"vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): \", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 65,
						.statementIdx = 54,
						.statement = "console.log(\"vec3.getX(vec3(1, 2, 3)): \", vec3.getX(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 66,
						.statementIdx = 55,
						.statement = "console.log(\"vec3.getY(vec3(1, 2, 3)): \", vec3.getY(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 67,
						.statementIdx = 56,
						.statement = "console.log(\"vec3.getZ(vec3(1, 2, 3)): \", vec3.getZ(vec3(1, 2, 3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 57,
						.statement = "console.log(\"-------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 58,
						.statement = "console.log(\"Check vector3 computation (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 70,
						.statementIdx = 59,
						.statement = "console.log(\"-------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 60,
						.statement = "console.log(\"vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): \",sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 61,
						.statement = "console.log(\"vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): \",div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 62,
						.statement = "console.log(\"vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): \",mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 74,
						.statementIdx = 63,
						.statement = "console.log(\"vec3(20, 10, 5) / 2): \",div(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 75,
						.statementIdx = 64,
						.statement = "console.log(\"vec3(20, 10, 5) * 2): \",mul(vec3(20, 10, 5), 2))",
						.gotoStatementIdx = -1
					},
					{
						.line = 76,
						.statementIdx = 65,
						.statement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 66,
						.statement = "console.log(\"Check transform computation\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 78,
						.statementIdx = 67,
						.statement = "console.log(\"-----------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 79,
						.statementIdx = 68,
						.statement = "setVariable(\"$transform\", transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 80,
						.statementIdx = 69,
						.statement = "setVariable(\"$transform\", transform.setRotationAngle($transform, 0, 90)));",
						.gotoStatementIdx = -1
					},
					{
						.line = 81,
						.statementIdx = 70,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): \", $transform)",
						.gotoStatementIdx = -1
					},
					{
						.line = 82,
						.statementIdx = 71,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): \", transform.getTranslation($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 83,
						.statementIdx = 72,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): \", transform.setTranslation($transform, vec3(-1,-2,-3)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 84,
						.statementIdx = 73,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): \", transform.getScale($transform))",
						.gotoStatementIdx = -1
					},
					{
						.line = 85,
						.statementIdx = 74,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): \", transform.setScale($transform, vec3(-2,-3,-4)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 86,
						.statementIdx = 75,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): \", transform.getRotationAxis($transform, 0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 87,
						.statementIdx = 76,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): \", transform.getRotationAngle($transform, 0))",
						.gotoStatementIdx = -1
					},
					{
						.line = 88,
						.statementIdx = 77,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): \", transform.setRotationAngle($transform, 0, 90))",
						.gotoStatementIdx = -1
					},
					{
						.line = 89,
						.statementIdx = 78,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): \", transform.multiply($transform, vec3(0,0,0)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 90,
						.statementIdx = 79,
						.statement = "console.log(\"transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): \", transform.rotate($transform, vec3(0,0,1)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 91,
						.statementIdx = 80,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 92,
						.statementIdx = 81,
						.statement = "console.log(\"Check string functions\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 93,
						.statementIdx = 82,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 94,
						.statementIdx = 83,
						.statement = "console.log(space(0), \"1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 95,
						.statementIdx = 84,
						.statement = "console.log(space(2), \"1.1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 96,
						.statementIdx = 85,
						.statement = "console.log(space(2), \"1.2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 97,
						.statementIdx = 86,
						.statement = "console.log(toUpperCase(\"xxxyyyzzz\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 98,
						.statementIdx = 87,
						.statement = "console.log(toLowerCase(\"XXXYYYZZZ\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 99,
						.statementIdx = 88,
						.statement = "console.log(concatenate(\"abc\", \"def\", \"ghi\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 100,
						.statementIdx = 89,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 101,
						.statementIdx = 90,
						.statement = "console.log(\"Check string functions (Operators)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 102,
						.statementIdx = 91,
						.statement = "console.log(add(\"abc\",add(\"def\", \"ghi\")))",
						.gotoStatementIdx = -1
					},
					{
						.line = 103,
						.statementIdx = 92,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 104,
						.statementIdx = 93,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 105,
						.statementIdx = 94,
						.statement = "console.log(\"Variable\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 106,
						.statementIdx = 95,
						.statement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 107,
						.statementIdx = 96,
						.statement = "setVariable(\"$variable\", string(\"1234\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 108,
						.statementIdx = 97,
						.statement = "console.log(getVariable(\"$variable\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 109,
						.statementIdx = 98,
						.statement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 110,
						.statementIdx = 99,
						.statement = "console.log(\"Lets check forTime\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 111,
						.statementIdx = 100,
						.statement = "console.log(\"--------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 112,
						.statementIdx = 101,
						.statement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 113,
						.statementIdx = 102,
						.statement = "forTime(2000)",
						.gotoStatementIdx = 107
					},
					{
						.line = 114,
						.statementIdx = 103,
						.statement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 115,
						.statementIdx = 104,
						.statement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 116,
						.statementIdx = 105,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 117,
						.statementIdx = 106,
						.statement = "end",
						.gotoStatementIdx = 102
					},
					{
						.line = 118,
						.statementIdx = 107,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 119,
						.statementIdx = 108,
						.statement = "console.log(\"Lets check forCondition\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 120,
						.statementIdx = 109,
						.statement = "console.log(\"-------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 121,
						.statementIdx = 110,
						.statement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 122,
						.statementIdx = 111,
						.statement = "forCondition(notequal($i, 6))",
						.gotoStatementIdx = 116
					},
					{
						.line = 123,
						.statementIdx = 112,
						.statement = "console.log($i, \": Hello World\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 124,
						.statementIdx = 113,
						.statement = "script.wait(500)",
						.gotoStatementIdx = -1
					},
					{
						.line = 125,
						.statementIdx = 114,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 126,
						.statementIdx = 115,
						.statement = "end",
						.gotoStatementIdx = 111
					},
					{
						.line = 127,
						.statementIdx = 116,
						.statement = "console.log(\"i -> \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 128,
						.statementIdx = 117,
						.statement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 129,
						.statementIdx = 118,
						.statement = "console.log(\"Lets check forCondition with if/elseif/else\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 130,
						.statementIdx = 119,
						.statement = "console.log(\"---------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 131,
						.statementIdx = 120,
						.statement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 132,
						.statementIdx = 121,
						.statement = "forCondition(lesser($i, 5))",
						.gotoStatementIdx = 136
					},
					{
						.line = 133,
						.statementIdx = 122,
						.statement = "console.log($i, \":\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 134,
						.statementIdx = 123,
						.statement = "if (equals($i, 0))",
						.gotoStatementIdx = 125
					},
					{
						.line = 135,
						.statementIdx = 124,
						.statement = "console.log(\"i -> 0\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 136,
						.statementIdx = 125,
						.statement = "elseif (equals($i, 1))",
						.gotoStatementIdx = 127
					},
					{
						.line = 137,
						.statementIdx = 126,
						.statement = "console.log(\"i -> 1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 138,
						.statementIdx = 127,
						.statement = "elseif (equals($i, 2))",
						.gotoStatementIdx = 129
					},
					{
						.line = 139,
						.statementIdx = 128,
						.statement = "console.log(\"i -> 2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 140,
						.statementIdx = 129,
						.statement = "elseif (equals($i, 3))",
						.gotoStatementIdx = 131
					},
					{
						.line = 141,
						.statementIdx = 130,
						.statement = "console.log(\"i -> 3\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 142,
						.statementIdx = 131,
						.statement = "else",
						.gotoStatementIdx = 133
					},
					{
						.line = 143,
						.statementIdx = 132,
						.statement = "console.log(\"else: \", $i)",
						.gotoStatementIdx = -1
					},
					{
						.line = 144,
						.statementIdx = 133,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 145,
						.statementIdx = 134,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 146,
						.statementIdx = 135,
						.statement = "end",
						.gotoStatementIdx = 121
					},
					{
						.line = 147,
						.statementIdx = 136,
						.statement = "setVariable(\"$i\", 1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 148,
						.statementIdx = 137,
						.statement = "setVariable(\"$j\", 2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 149,
						.statementIdx = 138,
						.statement = "setVariable(\"$k\", 3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 150,
						.statementIdx = 139,
						.statement = "if (or(equals(getVariable(\"$i\"), $j),equals(getVariable(\"$i\"), $k)))",
						.gotoStatementIdx = 141
					},
					{
						.line = 151,
						.statementIdx = 140,
						.statement = "console.log(\"This should not happen, but look ok in preprocessor processed output\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 152,
						.statementIdx = 141,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 153,
						.statementIdx = 142,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 154,
						.statementIdx = 143,
						.statement = "console.log(add(\"Test: string concatenation with brackets in string literals: \",add($i,add(\"(\",add($j, \")\")))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 155,
						.statementIdx = 144,
						.statement = "console.log(\"-------------------------------------------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 156,
						.statementIdx = 145,
						.statement = "console.log(\"(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): \",add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), \" = 17\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 157,
						.statementIdx = 146,
						.statement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 158,
						.statementIdx = 147,
						.statement = "console.log(\"Arrays\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 159,
						.statementIdx = 148,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 160,
						.statementIdx = 149,
						.statement = "setVariable(\"$array\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 161,
						.statementIdx = 150,
						.statement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 162,
						.statementIdx = 151,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 163,
						.statementIdx = 152,
						.statement = "setVariable(\"$array\", array.push($array, 8, 9, 10, 99, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 164,
						.statementIdx = 153,
						.statement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10, 99, 10)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 165,
						.statementIdx = 154,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 166,
						.statementIdx = 155,
						.statement = "setVariable(\"$array[]\", 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 167,
						.statementIdx = 156,
						.statement = "setVariable(\"$array[]\", 1234)",
						.gotoStatementIdx = -1
					},
					{
						.line = 168,
						.statementIdx = 157,
						.statement = "setVariable(\"$array[]\", 12345)",
						.gotoStatementIdx = -1
					},
					{
						.line = 169,
						.statementIdx = 158,
						.statement = "setVariable(\"$array[]\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 170,
						.statementIdx = 159,
						.statement = "console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 171,
						.statementIdx = 160,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 172,
						.statementIdx = 161,
						.statement = "console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 173,
						.statementIdx = 162,
						.statement = "setVariable(\"$array[11][]\", 50)",
						.gotoStatementIdx = -1
					},
					{
						.line = 174,
						.statementIdx = 163,
						.statement = "setVariable(\"$array[11][]\", 60)",
						.gotoStatementIdx = -1
					},
					{
						.line = 175,
						.statementIdx = 164,
						.statement = "console.log(\"array length: \", array.length($array))",
						.gotoStatementIdx = -1
					},
					{
						.line = 176,
						.statementIdx = 165,
						.statement = "console.log(\"array iteration with array.get(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 177,
						.statementIdx = 166,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 178,
						.statementIdx = 167,
						.statement = "forCondition(lesser($i,div(array.length($array), 2)))",
						.gotoStatementIdx = 172
					},
					{
						.line = 179,
						.statementIdx = 168,
						.statement = "console.log(add(add(mul($i, 2), 0),add(\": \", array.get($array,add(mul($i, 2), 0)))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 180,
						.statementIdx = 169,
						.statement = "console.log(add(add(mul($i, 2), 1),add(\": \", array.get($array,add(mul($i, 2), 1)))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 181,
						.statementIdx = 170,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 182,
						.statementIdx = 171,
						.statement = "end",
						.gotoStatementIdx = 167
					},
					{
						.line = 183,
						.statementIdx = 172,
						.statement = "console.log(\"array iteration with [] operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 184,
						.statementIdx = 173,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 185,
						.statementIdx = 174,
						.statement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 178
					},
					{
						.line = 186,
						.statementIdx = 175,
						.statement = "console.log(add($i,add(\": \", $array[$i])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 187,
						.statementIdx = 176,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 188,
						.statementIdx = 177,
						.statement = "end",
						.gotoStatementIdx = 174
					},
					{
						.line = 189,
						.statementIdx = 178,
						.statement = "console.log(\"array iteration with [] opertator and some index math: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 190,
						.statementIdx = 179,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 191,
						.statementIdx = 180,
						.statement = "forCondition(lesser($i,div(array.length($array), 2)))",
						.gotoStatementIdx = 185
					},
					{
						.line = 192,
						.statementIdx = 181,
						.statement = "console.log(add($i,add(\"-a: \", $array[add(mul($i, 2), 0)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 193,
						.statementIdx = 182,
						.statement = "console.log(add($i,add(\"-b: \", $array[add(mul($i, 2), 1)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 194,
						.statementIdx = 183,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 195,
						.statementIdx = 184,
						.statement = "end",
						.gotoStatementIdx = 180
					},
					{
						.line = 196,
						.statementIdx = 185,
						.statement = "console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 197,
						.statementIdx = 186,
						.statement = "setVariable(\"$array\", array.removeOf($array, 123))",
						.gotoStatementIdx = -1
					},
					{
						.line = 198,
						.statementIdx = 187,
						.statement = "setVariable(\"$array\", array.removeOf($array, 1234))",
						.gotoStatementIdx = -1
					},
					{
						.line = 199,
						.statementIdx = 188,
						.statement = "setVariable(\"$array\", array.removeOf($array, 12345))",
						.gotoStatementIdx = -1
					},
					{
						.line = 200,
						.statementIdx = 189,
						.statement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 201,
						.statementIdx = 190,
						.statement = "console.log(\"array indexOf 10: \", array.indexOf($array, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 202,
						.statementIdx = 191,
						.statement = "console.log(\"array indexOf 10 beginning to search from 6: \", array.indexOf($array, 10, 6))",
						.gotoStatementIdx = -1
					},
					{
						.line = 203,
						.statementIdx = 192,
						.statement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 204,
						.statementIdx = 193,
						.statement = "console.log(\"Test if enabled naming condition will be emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 205,
						.statementIdx = 194,
						.statement = "console.log(\"--------------------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 206,
						.statementIdx = 195,
						.statement = "script.enableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 207,
						.statementIdx = 196,
						.statement = "script.wait(2000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 208,
						.statementIdx = 197,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 209,
						.statementIdx = 198,
						.statement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 210,
						.statementIdx = 199,
						.statement = "console.log(\"Naming condition has not been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 211,
						.statementIdx = 200,
						.statement = "console.log(\"---------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 212,
						.statementIdx = 201,
						.statement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 213,
						.statementIdx = 202,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 215,
				.condition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 216,
						.statementIdx = 0,
						.statement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 217,
						.statementIdx = 1,
						.statement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 218,
						.statementIdx = 2,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ON,
				.line = 220,
				.condition = "emittest",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 221,
						.statementIdx = 0,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 222,
						.statementIdx = 1,
						.statement = "console.log(\"SCRIPT JUST EMITTED A CONDITION\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 223,
						.statementIdx = 2,
						.statement = "console.log(\"---------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 224,
						.statementIdx = 3,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 225,
						.statementIdx = 4,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 226,
						.statementIdx = 5,
						.statement = "console.log(\"Benchmark \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 227,
						.statementIdx = 6,
						.statement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 228,
						.statementIdx = 7,
						.statement = "setVariable(\"$startTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 229,
						.statementIdx = 8,
						.statement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 230,
						.statementIdx = 9,
						.statement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 231,
						.statementIdx = 10,
						.statement = "setVariable(\"$k\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 232,
						.statementIdx = 11,
						.statement = "forCondition(lesser($i, 500000))",
						.gotoStatementIdx = 22
					},
					{
						.line = 233,
						.statementIdx = 12,
						.statement = "setVariable(\"$a\",sub(add(123,add(mul(456,div(25, 12)),mul(7.5, 12.25))), 8))",
						.gotoStatementIdx = -1
					},
					{
						.line = 234,
						.statementIdx = 13,
						.statement = "if (equals($j, 0))",
						.gotoStatementIdx = 15
					},
					{
						.line = 235,
						.statementIdx = 14,
						.statement = "setVariable(\"$k\",add($k, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 236,
						.statementIdx = 15,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 237,
						.statementIdx = 16,
						.statement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 238,
						.statementIdx = 17,
						.statement = "setVariable(\"$j\",add($j, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 239,
						.statementIdx = 18,
						.statement = "if (equals($j, 2))",
						.gotoStatementIdx = 20
					},
					{
						.line = 240,
						.statementIdx = 19,
						.statement = "setVariable(\"$j\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 241,
						.statementIdx = 20,
						.statement = "end",
						.gotoStatementIdx = -1
					},
					{
						.line = 242,
						.statementIdx = 21,
						.statement = "end",
						.gotoStatementIdx = 11
					},
					{
						.line = 243,
						.statementIdx = 22,
						.statement = "setVariable(\"$endTime\", time.getCurrentMillis())",
						.gotoStatementIdx = -1
					},
					{
						.line = 244,
						.statementIdx = 23,
						.statement = "console.log(add(\"Finished. Time: \", sub($endTime, $startTime)))",
						.gotoStatementIdx = -1
					},
					{
						.line = 245,
						.statementIdx = 24,
						.statement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 246,
						.statementIdx = 25,
						.statement = "end",
						.gotoStatementIdx = -1
					}
				}
			},
			{
				.conditionType = Script::CONDITIONTYPE_ONENABLED,
				.line = 248,
				.condition = "equals(1,1)",
				.name = "named_condition_1",
				.emitCondition = false,
				.statements = {
					{
						.line = 249,
						.statementIdx = 0,
						.statement = "script.disableNamedCondition(\"named_condition_1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 250,
						.statementIdx = 1,
						.statement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 251,
						.statementIdx = 2,
						.statement = "console.log(\"named_condition_1 has been emitted\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 252,
						.statementIdx = 3,
						.statement = "console.log(\"------------------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 253,
						.statementIdx = 4,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 254,
						.statementIdx = 5,
						.statement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 255,
						.statementIdx = 6,
						.statement = "console.log(\"Test emit\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 256,
						.statementIdx = 7,
						.statement = "console.log(\"-----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 257,
						.statementIdx = 8,
						.statement = "console.log()",
						.gotoStatementIdx = -1
					},
					{
						.line = 258,
						.statementIdx = 9,
						.statement = "script.emit(emittest)",
						.gotoStatementIdx = -1
					},
					{
						.line = 259,
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
					.line = 248,
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
	if (miniScriptGotoStatementIdx == 103) goto miniscript_statement_103; else
	if (miniScriptGotoStatementIdx == 105) goto miniscript_statement_105; else
	if (miniScriptGotoStatementIdx == 107) goto miniscript_statement_107; else
	if (miniScriptGotoStatementIdx == 112) goto miniscript_statement_112; else
	if (miniScriptGotoStatementIdx == 114) goto miniscript_statement_114; else
	if (miniScriptGotoStatementIdx == 116) goto miniscript_statement_116; else
	if (miniScriptGotoStatementIdx == 122) goto miniscript_statement_122; else
	if (miniScriptGotoStatementIdx == 124) goto miniscript_statement_124; else
	if (miniScriptGotoStatementIdx == 126) goto miniscript_statement_126; else
	if (miniScriptGotoStatementIdx == 128) goto miniscript_statement_128; else
	if (miniScriptGotoStatementIdx == 130) goto miniscript_statement_130; else
	if (miniScriptGotoStatementIdx == 132) goto miniscript_statement_132; else
	if (miniScriptGotoStatementIdx == 134) goto miniscript_statement_134; else
	if (miniScriptGotoStatementIdx == 136) goto miniscript_statement_136; else
	if (miniScriptGotoStatementIdx == 140) goto miniscript_statement_140; else
	if (miniScriptGotoStatementIdx == 142) goto miniscript_statement_142; else
	if (miniScriptGotoStatementIdx == 168) goto miniscript_statement_168; else
	if (miniScriptGotoStatementIdx == 172) goto miniscript_statement_172; else
	if (miniScriptGotoStatementIdx == 175) goto miniscript_statement_175; else
	if (miniScriptGotoStatementIdx == 178) goto miniscript_statement_178; else
	if (miniScriptGotoStatementIdx == 181) goto miniscript_statement_181; else
	if (miniScriptGotoStatementIdx == 185) goto miniscript_statement_185; else
	if (miniScriptGotoStatementIdx == 197) goto miniscript_statement_197; else
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
	// console.log("Nothing")
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[2];
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

	// Statement: 3
	// console.log()
	{
		const ScriptStatement& statement = scripts[1].statements[3];
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
	// console.log("-----------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[4];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[8];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[11];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 12
	// console.log("div(20, 2): ", div(20, 2))
	{
		const ScriptStatement& statement = scripts[1].statements[12];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 13
	// console.log("mul(11, 10): ", mul(11, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[13];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 14
	// console.log("greater(2, 1): ", greater(2, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[14];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[15];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[16];
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

	// Statement: 17
	// console.log("Check int computation (Operators)")
	{
		const ScriptStatement& statement = scripts[1].statements[17];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[18];
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

	// Statement: 19
	// console.log("1 + 2 + 3 - 1: ", sub(add(1,add(2, 3)), 1))
	{
		const ScriptStatement& statement = scripts[1].statements[19];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 20
	// console.log("20 / 2: ", div(20, 2))
	{
		const ScriptStatement& statement = scripts[1].statements[20];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 21
	// console.log("11 * 10: ", mul(11, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[21];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 22
	// console.log("2 > 1: ", greater(2, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[22];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[23];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[24];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[25];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[26];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[27];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 28
	// console.log("div(20, 1.5): ", div(20, 1.5))
	{
		const ScriptStatement& statement = scripts[1].statements[28];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 29
	// console.log("mul(11.5, 10.5): ", mul(11.5, 10.5))
	{
		const ScriptStatement& statement = scripts[1].statements[29];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 30
	// console.log("greater(2.2, 1.3): ", greater(2.2, 1.3))
	{
		const ScriptStatement& statement = scripts[1].statements[30];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[31];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[32];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[33];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[34];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[35];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 36
	// console.log("20 / 1.5: ", div(20, 1.5))
	{
		const ScriptStatement& statement = scripts[1].statements[36];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 37
	// console.log("11.5 * 10.5: ", mul(11.5, 10.5))
	{
		const ScriptStatement& statement = scripts[1].statements[37];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 38
	// console.log("2.2 > 1.3: ", greater(2.2, 1.3))
	{
		const ScriptStatement& statement = scripts[1].statements[38];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[39];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		const ScriptStatement& statement = scripts[1].statements[40];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
	// console.log("Check vector3 computation")
	{
		const ScriptStatement& statement = scripts[1].statements[41];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector3 computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 42
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[42];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
	// console.log("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): ", sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[43];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): "));
		// argumentValues[1] --> returnValue of sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
		// depth = 1 / argument index = 1: sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(vec3(1.1, 2.2, 3.3))
			// argumentValues[1] --> returnValue of vec3(1.2, 1.0, 1.0)
			// depth = 2 / argument index = 0: add(vec3(1.1, 2.2, 3.3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(1.1, 2.2, 3.3)
				// depth = 3 / argument index = 0: vec3(1.1, 2.2, 3.3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
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
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 44
	// console.log("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[44];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): "));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 45
	// console.log("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[45];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): "));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 46
	// console.log("div(vec3(20, 10, 5), 2): ", div(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[46];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(vec3(20, 10, 5), 2): "));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 47
	// console.log("mul(vec3(20, 10, 5), 2): ", mul(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[47];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(vec3(20, 10, 5), 2): "));
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 48
	// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[1].statements[48];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 49
	// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
	{
		const ScriptStatement& statement = scripts[1].statements[49];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 50
	// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
	{
		const ScriptStatement& statement = scripts[1].statements[50];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 51
	// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[1].statements[51];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 52
	// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[52];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 53
	// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[1].statements[53];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 54
	// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[54];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 55
	// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[55];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 56
	// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
	{
		const ScriptStatement& statement = scripts[1].statements[56];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 57
	// console.log("-------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[57];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 58
	// console.log("Check vector3 computation (Operators)")
	{
		const ScriptStatement& statement = scripts[1].statements[58];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector3 computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 59
	// console.log("-------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[59];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 60
	// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))
	{
		const ScriptStatement& statement = scripts[1].statements[60];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 61
	// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[61];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 62
	// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		const ScriptStatement& statement = scripts[1].statements[62];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 63
	// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[63];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 64
	// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
	{
		const ScriptStatement& statement = scripts[1].statements[64];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 65
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[65];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 66
	// console.log("Check transform computation")
	{
		const ScriptStatement& statement = scripts[1].statements[66];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check transform computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 67
	// console.log("-----------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[67];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 68
	// setVariable("$transform", transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))
	{
		const ScriptStatement& statement = scripts[1].statements[68];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 69
	// setVariable("$transform", transform.setRotationAngle($transform, 0, 90))
	{
		const ScriptStatement& statement = scripts[1].statements[69];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 70
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): ", $transform)
	{
		const ScriptStatement& statement = scripts[1].statements[70];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 71
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): ", transform.getTranslation($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[71];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 72
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): ", transform.setTranslation($transform, vec3(-1,-2,-3)))
	{
		const ScriptStatement& statement = scripts[1].statements[72];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 73
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): ", transform.getScale($transform))
	{
		const ScriptStatement& statement = scripts[1].statements[73];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 74
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): ", transform.setScale($transform, vec3(-2,-3,-4)))
	{
		const ScriptStatement& statement = scripts[1].statements[74];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 75
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): ", transform.getRotationAxis($transform, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[75];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 76
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): ", transform.getRotationAngle($transform, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[76];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 77
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): ", transform.setRotationAngle($transform, 0, 90))
	{
		const ScriptStatement& statement = scripts[1].statements[77];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 78
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): ", transform.multiply($transform, vec3(0,0,0)))
	{
		const ScriptStatement& statement = scripts[1].statements[78];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 79
	// console.log("transform(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): ", transform.rotate($transform, vec3(0,0,1)))
	{
		const ScriptStatement& statement = scripts[1].statements[79];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 80
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[80];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 81
	// console.log("Check string functions")
	{
		const ScriptStatement& statement = scripts[1].statements[81];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 82
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[82];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 83
	// console.log(space(0), "1")
	{
		const ScriptStatement& statement = scripts[1].statements[83];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 84
	// console.log(space(2), "1.1")
	{
		const ScriptStatement& statement = scripts[1].statements[84];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 85
	// console.log(space(2), "1.2")
	{
		const ScriptStatement& statement = scripts[1].statements[85];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 86
	// console.log(toUpperCase("xxxyyyzzz"))
	{
		const ScriptStatement& statement = scripts[1].statements[86];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 87
	// console.log(toLowerCase("XXXYYYZZZ"))
	{
		const ScriptStatement& statement = scripts[1].statements[87];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 88
	// console.log(concatenate("abc", "def", "ghi"))
	{
		const ScriptStatement& statement = scripts[1].statements[88];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 89
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[89];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 90
	// console.log("Check string functions (Operators)")
	{
		const ScriptStatement& statement = scripts[1].statements[90];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 91
	// console.log(add("abc",add("def", "ghi")))
	{
		const ScriptStatement& statement = scripts[1].statements[91];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 92
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[92];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 93
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[93];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 94
	// console.log("Variable")
	{
		const ScriptStatement& statement = scripts[1].statements[94];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 95
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[95];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 96
	// setVariable("$variable", string("1234"))
	{
		const ScriptStatement& statement = scripts[1].statements[96];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 97
	// console.log(getVariable("$variable"))
	{
		const ScriptStatement& statement = scripts[1].statements[97];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 98
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[98];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 99
	// console.log("Lets check forTime")
	{
		const ScriptStatement& statement = scripts[1].statements[99];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 100
	// console.log("--------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[100];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 101
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[101];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 102
	miniscript_statement_102:
	// forTime(2000)
	{
		const ScriptStatement& statement = scripts[1].statements[102];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			auto forTimeStartedIt = miniScript->scriptState.forTimeStarted.find(statement.line);
			if (forTimeStartedIt == miniScript->scriptState.forTimeStarted.end()) {
				miniScript->scriptState.forTimeStarted[statement.line] = timeWaitStarted;
			} else {
				timeWaitStarted = forTimeStartedIt->second;
			}
			//
			if (Time::getCurrentMillis() > timeWaitStarted + time) {
				miniScript->scriptState.forTimeStarted.erase(statement.line);
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_107;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 103
	miniscript_statement_103:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[1].statements[103];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 104
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[1].statements[104];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
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

	// Statement: 105
	miniscript_statement_105:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[105];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 106
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[106];
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
				goto miniscript_statement_102;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 107
	miniscript_statement_107:
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[107];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
	// console.log("Lets check forCondition")
	{
		const ScriptStatement& statement = scripts[1].statements[108];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 109
	// console.log("-------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[109];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[110];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 111
	miniscript_statement_111:
	// forCondition(notequal($i, 6))
	{
		const ScriptStatement& statement = scripts[1].statements[111];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_116;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 112
	miniscript_statement_112:
	// console.log($i, ": Hello World")
	{
		const ScriptStatement& statement = scripts[1].statements[112];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 113
	// script.wait(500)
	{
		const ScriptStatement& statement = scripts[1].statements[113];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
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

	// Statement: 114
	miniscript_statement_114:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[114];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 115
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[115];
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
				goto miniscript_statement_111;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 116
	miniscript_statement_116:
	// console.log("i -> ", $i)
	{
		const ScriptStatement& statement = scripts[1].statements[116];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 117
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[117];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 118
	// console.log("Lets check forCondition with if/elseif/else")
	{
		const ScriptStatement& statement = scripts[1].statements[118];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 119
	// console.log("---------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[119];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 120
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[120];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 121
	miniscript_statement_121:
	// forCondition(lesser($i, 5))
	{
		const ScriptStatement& statement = scripts[1].statements[121];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_136;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 122
	miniscript_statement_122:
	// console.log($i, ":")
	{
		const ScriptStatement& statement = scripts[1].statements[122];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 123
	// if(equals($i, 0))
	{
		const ScriptStatement& statement = scripts[1].statements[123];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_125;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 124
	miniscript_statement_124:
	// console.log("i -> 0")
	{
		const ScriptStatement& statement = scripts[1].statements[124];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 125
	miniscript_statement_125:
	// elseif(equals($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[125];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_127;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 126
	miniscript_statement_126:
	// console.log("i -> 1")
	{
		const ScriptStatement& statement = scripts[1].statements[126];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 127
	miniscript_statement_127:
	// elseif(equals($i, 2))
	{
		const ScriptStatement& statement = scripts[1].statements[127];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_129;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 128
	miniscript_statement_128:
	// console.log("i -> 2")
	{
		const ScriptStatement& statement = scripts[1].statements[128];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 129
	miniscript_statement_129:
	// elseif(equals($i, 3))
	{
		const ScriptStatement& statement = scripts[1].statements[129];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_131;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 130
	miniscript_statement_130:
	// console.log("i -> 3")
	{
		const ScriptStatement& statement = scripts[1].statements[130];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 131
	miniscript_statement_131:
	// else()
	{
		const ScriptStatement& statement = scripts[1].statements[131];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: else
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElse::executeMethod(): else without if");
			miniScript->startErrorScript(); return;
		} else {
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == true) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_133;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 132
	miniscript_statement_132:
	// console.log("else: ", $i)
	{
		const ScriptStatement& statement = scripts[1].statements[132];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 133
	miniscript_statement_133:
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[133];
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

	// Statement: 134
	miniscript_statement_134:
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[134];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 135
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[135];
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
				goto miniscript_statement_121;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 136
	miniscript_statement_136:
	// setVariable("$i", 1)
	{
		const ScriptStatement& statement = scripts[1].statements[136];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 137
	// setVariable("$j", 2)
	{
		const ScriptStatement& statement = scripts[1].statements[137];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 138
	// setVariable("$k", 3)
	{
		const ScriptStatement& statement = scripts[1].statements[138];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 139
	// if(or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k)))
	{
		const ScriptStatement& statement = scripts[1].statements[139];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_141;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 140
	miniscript_statement_140:
	// console.log("This should not happen, but look ok in preprocessor processed output")
	{
		const ScriptStatement& statement = scripts[1].statements[140];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 141
	miniscript_statement_141:
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[141];
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

	// Statement: 142
	miniscript_statement_142:
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[142];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 143
	// console.log(add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")")))))
	{
		const ScriptStatement& statement = scripts[1].statements[143];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
									result+= argumentValues[i].getValueString();
								} else
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
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 144
	// console.log("-------------------------------------------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[144];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 145
	// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), " = 17")
	{
		const ScriptStatement& statement = scripts[1].statements[145];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
				// depth = 3 / argument index = 1: add(2.0, 5)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(2.000000f);
					argumentValues[1].setValue(static_cast<int64_t>(5));
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 146
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[146];
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

	// Statement: 147
	// console.log("Arrays")
	{
		const ScriptStatement& statement = scripts[1].statements[147];
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

	// Statement: 148
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[1].statements[148];
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

	// Statement: 149
	// setVariable("$array", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[149];
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

	// Statement: 150
	// console.log("array initialized with: $array = array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[1].statements[150];
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

	// Statement: 151
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[151];
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

	// Statement: 152
	// setVariable("$array", array.push($array, 8, 9, 10, 99, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[152];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 153
	// console.log("array pushed values with: array.push($array, 8, 9, 10, 99, 10)")
	{
		const ScriptStatement& statement = scripts[1].statements[153];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 154
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[154];
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

	// Statement: 155
	// setVariable("$array[]", 123)
	{
		const ScriptStatement& statement = scripts[1].statements[155];
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

	// Statement: 156
	// setVariable("$array[]", 1234)
	{
		const ScriptStatement& statement = scripts[1].statements[156];
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

	// Statement: 157
	// setVariable("$array[]", 12345)
	{
		const ScriptStatement& statement = scripts[1].statements[157];
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

	// Statement: 158
	// setVariable("$array[]", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[158];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 159
	// console.log("array values added with [] operator: 123, 1234, 12345, array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[1].statements[159];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 160
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[160];
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

	// Statement: 161
	// console.log("array values added with [] operator to push to array of array: 50, 60")
	{
		const ScriptStatement& statement = scripts[1].statements[161];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 162
	// setVariable("$array[11][]", 50)
	{
		const ScriptStatement& statement = scripts[1].statements[162];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 163
	// setVariable("$array[11][]", 60)
	{
		const ScriptStatement& statement = scripts[1].statements[163];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 164
	// console.log("array length: ", array.length($array))
	{
		const ScriptStatement& statement = scripts[1].statements[164];
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

	// Statement: 165
	// console.log("array iteration with array.get(): ")
	{
		const ScriptStatement& statement = scripts[1].statements[165];
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

	// Statement: 166
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[166];
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

	// Statement: 167
	miniscript_statement_167:
	// forCondition(lesser($i,div(array.length($array), 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[167];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_172;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 168
	miniscript_statement_168:
	// console.log(add(add(mul($i, 2), 0),add(": ", array.get($array,add(mul($i, 2), 0)))))
	{
		const ScriptStatement& statement = scripts[1].statements[168];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add(add(mul($i, 2), 0),add(": ", array.get($array,add(mul($i, 2), 0))))
		// depth = 1 / argument index = 0: add(add(mul($i, 2), 0), add(": ", array.get($array,add(mul($i, 2), 0))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of add(mul($i, 2), 0)
			// argumentValues[1] --> returnValue of add(": ", array.get($array,add(mul($i, 2), 0)))
			// depth = 2 / argument index = 0: add(mul($i, 2), 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of mul($i, 2)
				argumentValues[1].setValue(static_cast<int64_t>(0));
				// depth = 3 / argument index = 0: mul($i, 2)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$i")
					argumentValues[1].setValue(static_cast<int64_t>(2));
					// depth = 4 / argument index = 0: getVariable("$i")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
			// depth = 2 / argument index = 1: add(": ", array.get($array,add(mul($i, 2), 0)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(": "));
				// argumentValues[1] --> returnValue of array.get($array,add(mul($i, 2), 0))
				// depth = 3 / argument index = 1: array.get($array, add(mul($i, 2), 0))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$array")
					// argumentValues[1] --> returnValue of add(mul($i, 2), 0)
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
					// depth = 4 / argument index = 1: add(mul($i, 2), 0)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of mul($i, 2)
						argumentValues[1].setValue(static_cast<int64_t>(0));
						// depth = 5 / argument index = 0: mul($i, 2)
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 2> argumentValues;
							array<ScriptVariable, 2>& argumentValuesD5AIDX0 = argumentValues;
							// argumentValues[0] --> returnValue of getVariable("$i")
							argumentValues[1].setValue(static_cast<int64_t>(2));
							// depth = 6 / argument index = 0: getVariable("$i")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX0[0];
								array<ScriptVariable, 1> argumentValues;
								array<ScriptVariable, 1>& argumentValuesD6AIDX0 = argumentValues;
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
								if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
									result+= argumentValues[i].getValueString();
								} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 169
	// console.log(add(add(mul($i, 2), 1),add(": ", array.get($array,add(mul($i, 2), 1)))))
	{
		const ScriptStatement& statement = scripts[1].statements[169];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add(add(mul($i, 2), 1),add(": ", array.get($array,add(mul($i, 2), 1))))
		// depth = 1 / argument index = 0: add(add(mul($i, 2), 1), add(": ", array.get($array,add(mul($i, 2), 1))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of add(mul($i, 2), 1)
			// argumentValues[1] --> returnValue of add(": ", array.get($array,add(mul($i, 2), 1)))
			// depth = 2 / argument index = 0: add(mul($i, 2), 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of mul($i, 2)
				argumentValues[1].setValue(static_cast<int64_t>(1));
				// depth = 3 / argument index = 0: mul($i, 2)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$i")
					argumentValues[1].setValue(static_cast<int64_t>(2));
					// depth = 4 / argument index = 0: getVariable("$i")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[0];
						array<ScriptVariable, 1> argumentValues;
						array<ScriptVariable, 1>& argumentValuesD4AIDX0 = argumentValues;
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
			// depth = 2 / argument index = 1: add(": ", array.get($array,add(mul($i, 2), 1)))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string(": "));
				// argumentValues[1] --> returnValue of array.get($array,add(mul($i, 2), 1))
				// depth = 3 / argument index = 1: array.get($array, add(mul($i, 2), 1))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					// argumentValues[0] --> returnValue of getVariable("$array")
					// argumentValues[1] --> returnValue of add(mul($i, 2), 1)
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
					// depth = 4 / argument index = 1: add(mul($i, 2), 1)
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of mul($i, 2)
						argumentValues[1].setValue(static_cast<int64_t>(1));
						// depth = 5 / argument index = 0: mul($i, 2)
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 2> argumentValues;
							array<ScriptVariable, 2>& argumentValuesD5AIDX0 = argumentValues;
							// argumentValues[0] --> returnValue of getVariable("$i")
							argumentValues[1].setValue(static_cast<int64_t>(2));
							// depth = 6 / argument index = 0: getVariable("$i")
							{
								// required method code arguments
								ScriptVariable& returnValue = argumentValuesD5AIDX0[0];
								array<ScriptVariable, 1> argumentValues;
								array<ScriptVariable, 1>& argumentValuesD6AIDX0 = argumentValues;
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
								if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
									result+= argumentValues[i].getValueString();
								} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 170
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[170];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 171
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[171];
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
				goto miniscript_statement_167;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 172
	miniscript_statement_172:
	// console.log("array iteration with [] operator: ")
	{
		const ScriptStatement& statement = scripts[1].statements[172];
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

	// Statement: 173
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[173];
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

	// Statement: 174
	miniscript_statement_174:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[1].statements[174];
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
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_178;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 175
	miniscript_statement_175:
	// console.log(add($i,add(": ", $array[$i])))
	{
		const ScriptStatement& statement = scripts[1].statements[175];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 176
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[176];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 177
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[177];
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
				goto miniscript_statement_174;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 178
	miniscript_statement_178:
	// console.log("array iteration with [] opertator and some index math: ")
	{
		const ScriptStatement& statement = scripts[1].statements[178];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 179
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[179];
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

	// Statement: 180
	miniscript_statement_180:
	// forCondition(lesser($i,div(array.length($array), 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[180];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_185;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 181
	miniscript_statement_181:
	// console.log(add($i,add("-a: ", $array[add(mul($i, 2), 0)])))
	{
		const ScriptStatement& statement = scripts[1].statements[181];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 182
	// console.log(add($i,add("-b: ", $array[add(mul($i, 2), 1)])))
	{
		const ScriptStatement& statement = scripts[1].statements[182];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 183
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[183];
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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

	// Statement: 184
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[184];
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
				goto miniscript_statement_180;
			}
		}
	}
	if (scriptState.stateStack.top().state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// Statement: 185
	miniscript_statement_185:
	// console.log("array removal of 123, 1234, 12345 using array.removeOf")
	{
		const ScriptStatement& statement = scripts[1].statements[185];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 186
	// setVariable("$array", array.removeOf($array, 123))
	{
		const ScriptStatement& statement = scripts[1].statements[186];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 187
	// setVariable("$array", array.removeOf($array, 1234))
	{
		const ScriptStatement& statement = scripts[1].statements[187];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 188
	// setVariable("$array", array.removeOf($array, 12345))
	{
		const ScriptStatement& statement = scripts[1].statements[188];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 189
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[189];
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

	// Statement: 190
	// console.log("array indexOf 10: ", array.indexOf($array, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[190];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 191
	// console.log("array indexOf 10 beginning to search from 6: ", array.indexOf($array, 10, 6))
	{
		const ScriptStatement& statement = scripts[1].statements[191];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 192
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[192];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 193
	// console.log("Test if enabled naming condition will be emitted")
	{
		const ScriptStatement& statement = scripts[1].statements[193];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 194
	// console.log("--------------------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[194];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 195
	// script.enableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[1].statements[195];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.enableNamedCondition
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
			miniScript->scriptState.enabledNamedConditions.push_back(name);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.enableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}

	// enabled named conditions
	{
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
		resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
		scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
		return;
		}
	}

	// Statement: 196
	// script.wait(2000)
	{
		const ScriptStatement& statement = scripts[1].statements[196];
		miniScript->scriptState.statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
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

	// enabled named conditions
	{
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
		resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
		scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
		return;
		}
	}

	// Statement: 197
	miniscript_statement_197:
	// script.disableNamedCondition("named_condition_1")
	{
		const ScriptStatement& statement = scripts[1].statements[197];
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

	// Statement: 198
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[198];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 199
	// console.log("Naming condition has not been emitted")
	{
		const ScriptStatement& statement = scripts[1].statements[199];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 200
	// console.log("---------------------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[200];
		miniScript->scriptState.statementIdx = statement.statementIdx;
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

	// Statement: 201
	// script.stop()
	{
		const ScriptStatement& statement = scripts[1].statements[201];
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

	// Statement: 202
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[202];
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
							if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
								result+= argumentValues[i].getValueString();
							} else
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
						if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
							result+= argumentValues[i].getValueString();
						} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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
					if (argumentValues[i].getType() == MiniScript::TYPE_ARRAY) {
						result+= argumentValues[i].getValueString();
					} else
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
