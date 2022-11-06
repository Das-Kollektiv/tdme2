#include "MiniScriptAdvancedTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptMath.h>

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
	setNativeHash("7c68c27f8921dfd5fbaae5e78189bf4a60e7fc7a4b42a9658e64fe907434463d");
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
						.statement = "console.log(\"---------------------------\")",
						.executableStatement = "console.log(\"---------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 4,
						.statementIdx = 1,
						.statement = "console.log(\"advanced-test: Initialize\")",
						.executableStatement = "console.log(\"advanced-test: Initialize\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 5,
						.statementIdx = 2,
						.statement = "console.log(\"--------------------------\")",
						.executableStatement = "console.log(\"--------------------------\")",
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
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 12,
						.statementIdx = 1,
						.statement = "console.log(\"advanced-test: Nothing\")",
						.executableStatement = "console.log(\"advanced-test: Nothing\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 13,
						.statementIdx = 2,
						.statement = "console.log(\"------------------------\")",
						.executableStatement = "console.log(\"------------------------\")",
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
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 16,
						.statementIdx = 5,
						.statement = "console.log(\"Arrays\")",
						.executableStatement = "console.log(\"Arrays\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 17,
						.statementIdx = 6,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 18,
						.statementIdx = 7,
						.statement = "$array = array(1,2,3)",
						.executableStatement = "setVariable(\"$array\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 19,
						.statementIdx = 8,
						.statement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.executableStatement = "console.log(\"array initialized with: $array = array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 20,
						.statementIdx = 9,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 21,
						.statementIdx = 10,
						.statement = "array.push($array, 8, 9, 10, 99, 10)",
						.executableStatement = "array.push($array, 8, 9, 10, 99, 10)",
						.gotoStatementIdx = -1
					},
					{
						.line = 22,
						.statementIdx = 11,
						.statement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10, 99, 10)\")",
						.executableStatement = "console.log(\"array pushed values with: array.push($array, 8, 9, 10, 99, 10)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 23,
						.statementIdx = 12,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 24,
						.statementIdx = 13,
						.statement = "$array[] = 123",
						.executableStatement = "setVariable(\"$array[]\", 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 25,
						.statementIdx = 14,
						.statement = "$array[] = 1234",
						.executableStatement = "setVariable(\"$array[]\", 1234)",
						.gotoStatementIdx = -1
					},
					{
						.line = 26,
						.statementIdx = 15,
						.statement = "$array[] = 12345",
						.executableStatement = "setVariable(\"$array[]\", 12345)",
						.gotoStatementIdx = -1
					},
					{
						.line = 27,
						.statementIdx = 16,
						.statement = "$array[] = array(1,2,3)",
						.executableStatement = "setVariable(\"$array[]\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 28,
						.statementIdx = 17,
						.statement = "console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						.executableStatement = "console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 29,
						.statementIdx = 18,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 30,
						.statementIdx = 19,
						.statement = "console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						.executableStatement = "console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 31,
						.statementIdx = 20,
						.statement = "$array[11][] = 50",
						.executableStatement = "setVariable(\"$array[11][]\", 50)",
						.gotoStatementIdx = -1
					},
					{
						.line = 32,
						.statementIdx = 21,
						.statement = "$array[11][] = 60",
						.executableStatement = "setVariable(\"$array[11][]\", 60)",
						.gotoStatementIdx = -1
					},
					{
						.line = 33,
						.statementIdx = 22,
						.statement = "$array[11][array.length($array[11]) - 1] = 61",
						.executableStatement = "setVariable(\"$array[11][sub(array.length($array[11]), 1)]\", 61)",
						.gotoStatementIdx = -1
					},
					{
						.line = 34,
						.statementIdx = 23,
						.statement = "console.log(\"array length: \", array.length($array))",
						.executableStatement = "console.log(\"array length: \", array.length($array))",
						.gotoStatementIdx = -1
					},
					{
						.line = 35,
						.statementIdx = 24,
						.statement = "console.log(\"array iteration with array.get(): \")",
						.executableStatement = "console.log(\"array iteration with array.get(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 36,
						.statementIdx = 25,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 37,
						.statementIdx = 26,
						.statement = "forCondition($i < array.length($array))",
						.executableStatement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 30
					},
					{
						.line = 38,
						.statementIdx = 27,
						.statement = "console.log($i + \": \" + array.get($array, $i))",
						.executableStatement = "console.log(add($i,add(\": \", array.get($array, $i))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 39,
						.statementIdx = 28,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 40,
						.statementIdx = 29,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 26
					},
					{
						.line = 41,
						.statementIdx = 30,
						.statement = "console.log(\"array iteration with [] operator: \")",
						.executableStatement = "console.log(\"array iteration with [] operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 42,
						.statementIdx = 31,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 43,
						.statementIdx = 32,
						.statement = "forCondition($i < array.length($array))",
						.executableStatement = "forCondition(lesser($i, array.length($array)))",
						.gotoStatementIdx = 36
					},
					{
						.line = 44,
						.statementIdx = 33,
						.statement = "console.log($i + \": \" + $array[$i])",
						.executableStatement = "console.log(add($i,add(\": \", $array[$i])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 45,
						.statementIdx = 34,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 46,
						.statementIdx = 35,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 32
					},
					{
						.line = 47,
						.statementIdx = 36,
						.statement = "console.log(\"array iteration with [] opertator and some index math: \")",
						.executableStatement = "console.log(\"array iteration with [] opertator and some index math: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 48,
						.statementIdx = 37,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 49,
						.statementIdx = 38,
						.statement = "forCondition($i < array.length($array) / 2)",
						.executableStatement = "forCondition(lesser($i,div(array.length($array), 2)))",
						.gotoStatementIdx = 43
					},
					{
						.line = 50,
						.statementIdx = 39,
						.statement = "console.log($i + \"-a: \" + $array[$i * 2 + 0])",
						.executableStatement = "console.log(add($i,add(\"-a: \", $array[add(mul($i, 2), 0)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 51,
						.statementIdx = 40,
						.statement = "console.log($i + \"-b: \" + $array[$i * 2 + 1])",
						.executableStatement = "console.log(add($i,add(\"-b: \", $array[add(mul($i, 2), 1)])))",
						.gotoStatementIdx = -1
					},
					{
						.line = 52,
						.statementIdx = 41,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 53,
						.statementIdx = 42,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 38
					},
					{
						.line = 54,
						.statementIdx = 43,
						.statement = "console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						.executableStatement = "console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 55,
						.statementIdx = 44,
						.statement = "array.removeOf($array, 123)",
						.executableStatement = "array.removeOf($array, 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 56,
						.statementIdx = 45,
						.statement = "array.removeOf($array, 1234)",
						.executableStatement = "array.removeOf($array, 1234)",
						.gotoStatementIdx = -1
					},
					{
						.line = 57,
						.statementIdx = 46,
						.statement = "array.removeOf($array, 12345)",
						.executableStatement = "array.removeOf($array, 12345)",
						.gotoStatementIdx = -1
					},
					{
						.line = 58,
						.statementIdx = 47,
						.statement = "console.log(\"array now looks like: \", $array)",
						.executableStatement = "console.log(\"array now looks like: \", $array)",
						.gotoStatementIdx = -1
					},
					{
						.line = 59,
						.statementIdx = 48,
						.statement = "console.log(\"array indexOf 10: \", array.indexOf($array, 10))",
						.executableStatement = "console.log(\"array indexOf 10: \", array.indexOf($array, 10))",
						.gotoStatementIdx = -1
					},
					{
						.line = 60,
						.statementIdx = 49,
						.statement = "console.log(\"array indexOf 10 beginning to search from 6: \", array.indexOf($array, 10, 6))",
						.executableStatement = "console.log(\"array indexOf 10 beginning to search from 6: \", array.indexOf($array, 10, 6))",
						.gotoStatementIdx = -1
					},
					{
						.line = 61,
						.statementIdx = 50,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 62,
						.statementIdx = 51,
						.statement = "console.log(\"Maps\")",
						.executableStatement = "console.log(\"Maps\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 63,
						.statementIdx = 52,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 64,
						.statementIdx = 53,
						.statement = "$map = map()",
						.executableStatement = "setVariable(\"$map\", map())",
						.gotoStatementIdx = -1
					},
					{
						.line = 65,
						.statementIdx = 54,
						.statement = "console.log(\"map initialized with: $map = map()\")",
						.executableStatement = "console.log(\"map initialized with: $map = map()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 66,
						.statementIdx = 55,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 67,
						.statementIdx = 56,
						.statement = "console.log(\"put some key value pairs into map: map.set()\")",
						.executableStatement = "console.log(\"put some key value pairs into map: map.set()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 68,
						.statementIdx = 57,
						.statement = "map.set($map, \"test1\", 123)",
						.executableStatement = "map.set($map, \"test1\", 123)",
						.gotoStatementIdx = -1
					},
					{
						.line = 69,
						.statementIdx = 58,
						.statement = "map.set($map, \"test2\", 456)",
						.executableStatement = "map.set($map, \"test2\", 456)",
						.gotoStatementIdx = -1
					},
					{
						.line = 70,
						.statementIdx = 59,
						.statement = "map.set($map, \"test3\", 789)",
						.executableStatement = "map.set($map, \"test3\", 789)",
						.gotoStatementIdx = -1
					},
					{
						.line = 71,
						.statementIdx = 60,
						.statement = "map.set($map, \"test4\", array(1,2,3))",
						.executableStatement = "map.set($map, \"test4\", array(1,2,3))",
						.gotoStatementIdx = -1
					},
					{
						.line = 72,
						.statementIdx = 61,
						.statement = "map.set($map, \"test5\", \"Yaaaa\")",
						.executableStatement = "map.set($map, \"test5\", \"Yaaaa\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 73,
						.statementIdx = 62,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 74,
						.statementIdx = 63,
						.statement = "console.log(\"remove test2 via map.remove: \")",
						.executableStatement = "console.log(\"remove test2 via map.remove: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 75,
						.statementIdx = 64,
						.statement = "map.remove($map, \"test2\")",
						.executableStatement = "map.remove($map, \"test2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 76,
						.statementIdx = 65,
						.statement = "console.log(\"map now looks like: \", $map)",
						.executableStatement = "console.log(\"map now looks like: \", $map)",
						.gotoStatementIdx = -1
					},
					{
						.line = 77,
						.statementIdx = 66,
						.statement = "map.set($map, \"test2\", 456)",
						.executableStatement = "map.set($map, \"test2\", 456)",
						.gotoStatementIdx = -1
					},
					{
						.line = 78,
						.statementIdx = 67,
						.statement = "console.log(\"readding test2: \")",
						.executableStatement = "console.log(\"readding test2: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 79,
						.statementIdx = 68,
						.statement = "console.log(\"map does have test2 key using map.has(): \", map.has($map, \"test2\"))",
						.executableStatement = "console.log(\"map does have test2 key using map.has(): \", map.has($map, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 80,
						.statementIdx = 69,
						.statement = "console.log(\"map does have test8 key using map.has(): \", map.has($map, \"test8\"))",
						.executableStatement = "console.log(\"map does have test8 key using map.has(): \", map.has($map, \"test8\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 81,
						.statementIdx = 70,
						.statement = "console.log(\"map value for test1 key using map.get(): \", map.get($map, \"test1\"))",
						.executableStatement = "console.log(\"map value for test1 key using map.get(): \", map.get($map, \"test1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 82,
						.statementIdx = 71,
						.statement = "console.log(\"map value for test2 key using map.get(): \", map.get($map, \"test2\"))",
						.executableStatement = "console.log(\"map value for test2 key using map.get(): \", map.get($map, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 83,
						.statementIdx = 72,
						.statement = "console.log(\"map value for test3 key using map.get(): \", map.get($map, \"test3\"))",
						.executableStatement = "console.log(\"map value for test3 key using map.get(): \", map.get($map, \"test3\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 84,
						.statementIdx = 73,
						.statement = "console.log(\"map value for test4 key using map.get(): \", map.get($map, \"test4\"))",
						.executableStatement = "console.log(\"map value for test4 key using map.get(): \", map.get($map, \"test4\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 85,
						.statementIdx = 74,
						.statement = "console.log(\"map value for test5 key using map.get(): \", map.get($map, \"test5\"))",
						.executableStatement = "console.log(\"map value for test5 key using map.get(): \", map.get($map, \"test5\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 86,
						.statementIdx = 75,
						.statement = "console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						.executableStatement = "console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 87,
						.statementIdx = 76,
						.statement = "console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						.executableStatement = "console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 88,
						.statementIdx = 77,
						.statement = "console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						.executableStatement = "console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 89,
						.statementIdx = 78,
						.statement = "console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						.executableStatement = "console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						.gotoStatementIdx = -1
					},
					{
						.line = 90,
						.statementIdx = 79,
						.statement = "console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						.executableStatement = "console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						.gotoStatementIdx = -1
					},
					{
						.line = 91,
						.statementIdx = 80,
						.statement = "console.log(\"adding map values using map dot operator: \")",
						.executableStatement = "console.log(\"adding map values using map dot operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 92,
						.statementIdx = 81,
						.statement = "$map.test6 = 666",
						.executableStatement = "setVariable(\"$map.test6\", 666)",
						.gotoStatementIdx = -1
					},
					{
						.line = 93,
						.statementIdx = 82,
						.statement = "$map.test7 = 770",
						.executableStatement = "setVariable(\"$map.test7\", 770)",
						.gotoStatementIdx = -1
					},
					{
						.line = 94,
						.statementIdx = 83,
						.statement = "$map.test8 = 890",
						.executableStatement = "setVariable(\"$map.test8\", 890)",
						.gotoStatementIdx = -1
					},
					{
						.line = 95,
						.statementIdx = 84,
						.statement = "console.log(\"map keys: \", map.getKeys($map))",
						.executableStatement = "console.log(\"map keys: \", map.getKeys($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 96,
						.statementIdx = 85,
						.statement = "console.log(\"map values: \", map.getValues($map))",
						.executableStatement = "console.log(\"map values: \", map.getValues($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 97,
						.statementIdx = 86,
						.statement = "console.log(\"iterating keys and values using map.getKeys(): \")",
						.executableStatement = "console.log(\"iterating keys and values using map.getKeys(): \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 98,
						.statementIdx = 87,
						.statement = "$mapKeys = map.getKeys($map)",
						.executableStatement = "setVariable(\"$mapKeys\", map.getKeys($map))",
						.gotoStatementIdx = -1
					},
					{
						.line = 99,
						.statementIdx = 88,
						.statement = "$i = 0",
						.executableStatement = "setVariable(\"$i\", 0)",
						.gotoStatementIdx = -1
					},
					{
						.line = 100,
						.statementIdx = 89,
						.statement = "forCondition($i < array.length($mapKeys))",
						.executableStatement = "forCondition(lesser($i, array.length($mapKeys)))",
						.gotoStatementIdx = 93
					},
					{
						.line = 101,
						.statementIdx = 90,
						.statement = "console.log($mapKeys[$i] + \" = \" + map.get($map, $mapKeys[$i]))",
						.executableStatement = "console.log(add($mapKeys[$i],add(\" = \", map.get($map, $mapKeys[$i]))))",
						.gotoStatementIdx = -1
					},
					{
						.line = 102,
						.statementIdx = 91,
						.statement = "$i = $i + 1",
						.executableStatement = "setVariable(\"$i\",add($i, 1))",
						.gotoStatementIdx = -1
					},
					{
						.line = 103,
						.statementIdx = 92,
						.statement = "end",
						.executableStatement = "end",
						.gotoStatementIdx = 89
					},
					{
						.line = 104,
						.statementIdx = 93,
						.statement = "console.log(\"---------\")",
						.executableStatement = "console.log(\"---------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 105,
						.statementIdx = 94,
						.statement = "console.log(\"Sets\")",
						.executableStatement = "console.log(\"Sets\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 106,
						.statementIdx = 95,
						.statement = "console.log(\"----------\")",
						.executableStatement = "console.log(\"----------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 107,
						.statementIdx = 96,
						.statement = "$set = set()",
						.executableStatement = "setVariable(\"$set\", set())",
						.gotoStatementIdx = -1
					},
					{
						.line = 108,
						.statementIdx = 97,
						.statement = "console.log(\"set initialized with: $set = set()\")",
						.executableStatement = "console.log(\"set initialized with: $set = set()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 109,
						.statementIdx = 98,
						.statement = "console.log(\"set now looks like: \", $set)",
						.executableStatement = "console.log(\"set now looks like: \", $set)",
						.gotoStatementIdx = -1
					},
					{
						.line = 110,
						.statementIdx = 99,
						.statement = "console.log(\"put some keys into set: set.insert()\")",
						.executableStatement = "console.log(\"put some keys into set: set.insert()\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 111,
						.statementIdx = 100,
						.statement = "set.insert($set, \"test1\")",
						.executableStatement = "set.insert($set, \"test1\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 112,
						.statementIdx = 101,
						.statement = "set.insert($set, \"test2\")",
						.executableStatement = "set.insert($set, \"test2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 113,
						.statementIdx = 102,
						.statement = "set.insert($set, \"test3\")",
						.executableStatement = "set.insert($set, \"test3\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 114,
						.statementIdx = 103,
						.statement = "set.insert($set, \"test4\")",
						.executableStatement = "set.insert($set, \"test4\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 115,
						.statementIdx = 104,
						.statement = "set.insert($set, \"test5\")",
						.executableStatement = "set.insert($set, \"test5\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 116,
						.statementIdx = 105,
						.statement = "console.log(\"set now looks like: \", $set)",
						.executableStatement = "console.log(\"set now looks like: \", $set)",
						.gotoStatementIdx = -1
					},
					{
						.line = 117,
						.statementIdx = 106,
						.statement = "console.log(\"remove test2 via set.remove: \")",
						.executableStatement = "console.log(\"remove test2 via set.remove: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 118,
						.statementIdx = 107,
						.statement = "set.remove($set, \"test2\")",
						.executableStatement = "set.remove($set, \"test2\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 119,
						.statementIdx = 108,
						.statement = "console.log(\"set now looks like: \", $set)",
						.executableStatement = "console.log(\"set now looks like: \", $set)",
						.gotoStatementIdx = -1
					},
					{
						.line = 120,
						.statementIdx = 109,
						.statement = "console.log(\"set does have test1 key using set.has(): \", set.has($set, \"test1\"))",
						.executableStatement = "console.log(\"set does have test1 key using set.has(): \", set.has($set, \"test1\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 121,
						.statementIdx = 110,
						.statement = "console.log(\"set does have test2 key using set.has(): \", set.has($set, \"test2\"))",
						.executableStatement = "console.log(\"set does have test2 key using set.has(): \", set.has($set, \"test2\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 122,
						.statementIdx = 111,
						.statement = "console.log(\"set does have test3 key using set.has(): \", set.has($set, \"test3\"))",
						.executableStatement = "console.log(\"set does have test3 key using set.has(): \", set.has($set, \"test3\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 123,
						.statementIdx = 112,
						.statement = "console.log(\"set does have test4 key using set.has(): \", set.has($set, \"test4\"))",
						.executableStatement = "console.log(\"set does have test4 key using set.has(): \", set.has($set, \"test4\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 124,
						.statementIdx = 113,
						.statement = "console.log(\"set does have test5 key using set.has(): \", set.has($set, \"test5\"))",
						.executableStatement = "console.log(\"set does have test5 key using set.has(): \", set.has($set, \"test5\"))",
						.gotoStatementIdx = -1
					},
					{
						.line = 125,
						.statementIdx = 114,
						.statement = "console.log(\"set key for test1 using set dot operator: \", $set.test1)",
						.executableStatement = "console.log(\"set key for test1 using set dot operator: \", $set.test1)",
						.gotoStatementIdx = -1
					},
					{
						.line = 126,
						.statementIdx = 115,
						.statement = "console.log(\"set key for test2 using set dot operator: \", $set.test2)",
						.executableStatement = "console.log(\"set key for test2 using set dot operator: \", $set.test2)",
						.gotoStatementIdx = -1
					},
					{
						.line = 127,
						.statementIdx = 116,
						.statement = "console.log(\"set key for test3 using set dot operator: \", $set.test3)",
						.executableStatement = "console.log(\"set key for test3 using set dot operator: \", $set.test3)",
						.gotoStatementIdx = -1
					},
					{
						.line = 128,
						.statementIdx = 117,
						.statement = "console.log(\"set key for test4 using set dot operator: \", $set.test4)",
						.executableStatement = "console.log(\"set key for test4 using set dot operator: \", $set.test4)",
						.gotoStatementIdx = -1
					},
					{
						.line = 129,
						.statementIdx = 118,
						.statement = "console.log(\"set key for test5 using set dot operator: \", $set.test5)",
						.executableStatement = "console.log(\"set key for test5 using set dot operator: \", $set.test5)",
						.gotoStatementIdx = -1
					},
					{
						.line = 130,
						.statementIdx = 119,
						.statement = "console.log(\"inserting set values using set dot operator: \")",
						.executableStatement = "console.log(\"inserting set values using set dot operator: \")",
						.gotoStatementIdx = -1
					},
					{
						.line = 131,
						.statementIdx = 120,
						.statement = "$set.test6 = true",
						.executableStatement = "setVariable(\"$set.test6\", true)",
						.gotoStatementIdx = -1
					},
					{
						.line = 132,
						.statementIdx = 121,
						.statement = "$set.test7 = true",
						.executableStatement = "setVariable(\"$set.test7\", true)",
						.gotoStatementIdx = -1
					},
					{
						.line = 133,
						.statementIdx = 122,
						.statement = "$set.test8 = false",
						.executableStatement = "setVariable(\"$set.test8\", false)",
						.gotoStatementIdx = -1
					},
					{
						.line = 134,
						.statementIdx = 123,
						.statement = "$set.test9 = true",
						.executableStatement = "setVariable(\"$set.test9\", true)",
						.gotoStatementIdx = -1
					},
					{
						.line = 135,
						.statementIdx = 124,
						.statement = "console.log(\"set keys: \", set.getKeys($set))",
						.executableStatement = "console.log(\"set keys: \", set.getKeys($set))",
						.gotoStatementIdx = -1
					},
					{
						.line = 136,
						.statementIdx = 125,
						.statement = "script.stop()",
						.executableStatement = "script.stop()",
						.gotoStatementIdx = -1
					},
					{
						.line = 137,
						.statementIdx = 126,
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
				.line = 140,
				.condition = "error",
				.executableCondition = "error",
				.name = "",
				.emitCondition = true,
				.statements = {
					{
						.line = 141,
						.statementIdx = 0,
						.statement = "console.log(\"----------------------\")",
						.executableStatement = "console.log(\"----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 142,
						.statementIdx = 1,
						.statement = "console.log(\"advanced-test: Error\")",
						.executableStatement = "console.log(\"advanced-test: Error\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 143,
						.statementIdx = 2,
						.statement = "console.log(\"----------------------\")",
						.executableStatement = "console.log(\"----------------------\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 144,
						.statementIdx = 3,
						.statement = "console.log(\"An error occurred\")",
						.executableStatement = "console.log(\"An error occurred\")",
						.gotoStatementIdx = -1
					},
					{
						.line = 145,
						.statementIdx = 4,
						.statement = "script.wait(1000)",
						.executableStatement = "script.wait(1000)",
						.gotoStatementIdx = -1
					},
					{
						.line = 146,
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

int MiniScriptAdvancedTest::determineScriptIdxToStart() {
	if (native == false) return MiniScript::determineScriptIdxToStart();
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptAdvancedTest::determineNamedScriptIdxToStart() {
	if (native == false) return MiniScript::determineNamedScriptIdxToStart();
	auto miniScript = this;
	for (auto& enabledNamedCondition: enabledNamedConditions) {
	}

	//
	return -1;
}

void MiniScriptAdvancedTest::emit(const string& condition) {
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
		Console::println("MiniScriptAdvancedTest::emit(): no condition with name: '" + condition + "'");
	}
}

void MiniScriptAdvancedTest::on_initialize(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("---------------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 1
	// console.log("advanced-test: Initialize")
	{
		const ScriptStatement& statement = scripts[0].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("advanced-test: Initialize"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("--------------------------")
	{
		const ScriptStatement& statement = scripts[0].statements[2];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------------"));
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

void MiniScriptAdvancedTest::on_nothing(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 27) goto miniscript_statement_27; else
	if (miniScriptGotoStatementIdx == 30) goto miniscript_statement_30; else
	if (miniScriptGotoStatementIdx == 33) goto miniscript_statement_33; else
	if (miniScriptGotoStatementIdx == 36) goto miniscript_statement_36; else
	if (miniScriptGotoStatementIdx == 39) goto miniscript_statement_39; else
	if (miniScriptGotoStatementIdx == 43) goto miniscript_statement_43; else
	if (miniScriptGotoStatementIdx == 90) goto miniscript_statement_90; else
	if (miniScriptGotoStatementIdx == 93) goto miniscript_statement_93; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[0];
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

	// Statement: 1
	// console.log("advanced-test: Nothing")
	{
		const ScriptStatement& statement = scripts[1].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("advanced-test: Nothing"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("------------------------")
	{
		const ScriptStatement& statement = scripts[1].statements[2];
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
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[4];
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

	// Statement: 5
	// console.log("Arrays")
	{
		const ScriptStatement& statement = scripts[1].statements[5];
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

	// Statement: 6
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[6];
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

	// Statement: 7
	// setVariable("$array", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[7];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 8
	// console.log("array initialized with: $array = array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[1].statements[8];
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

	// Statement: 9
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[9];
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

	// Statement: 10
	// array.push($array, 8, 9, 10, 99, 10)
	{
		const ScriptStatement& statement = scripts[1].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 6> argumentValues;
		array<ScriptVariable, 6>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$array")
		argumentValues[1].setValue(static_cast<int64_t>(8));
		argumentValues[2].setValue(static_cast<int64_t>(9));
		argumentValues[3].setValue(static_cast<int64_t>(10));
		argumentValues[4].setValue(static_cast<int64_t>(99));
		argumentValues[5].setValue(static_cast<int64_t>(10));
		// depth = 1 / argument index = 0: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: array.push
		//
		if (argumentValues.size() < 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
			Console::println("ScriptMethodArrayPush::executeMethod(): " + string("array.push") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
		} else {
			for (auto i = 1; i < argumentValues.size(); i++) {
				argumentValues[0].pushArrayValue(argumentValues[i]);
			}
		}
		// assign back
		setVariable("$array", argumentValues[0], &statement);
		//
	}

	// Statement: 11
	// console.log("array pushed values with: array.push($array, 8, 9, 10, 99, 10)")
	{
		const ScriptStatement& statement = scripts[1].statements[11];
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

	// Statement: 12
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[12];
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

	// Statement: 13
	// setVariable("$array[]", 123)
	{
		const ScriptStatement& statement = scripts[1].statements[13];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 14
	// setVariable("$array[]", 1234)
	{
		const ScriptStatement& statement = scripts[1].statements[14];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 15
	// setVariable("$array[]", 12345)
	{
		const ScriptStatement& statement = scripts[1].statements[15];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 16
	// setVariable("$array[]", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[16];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 17
	// console.log("array values added with [] operator: 123, 1234, 12345, array(1,2,3)")
	{
		const ScriptStatement& statement = scripts[1].statements[17];
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

	// Statement: 18
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[18];
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

	// Statement: 19
	// console.log("array values added with [] operator to push to array of array: 50, 60")
	{
		const ScriptStatement& statement = scripts[1].statements[19];
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

	// Statement: 20
	// setVariable("$array[11][]", 50)
	{
		const ScriptStatement& statement = scripts[1].statements[20];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 21
	// setVariable("$array[11][]", 60)
	{
		const ScriptStatement& statement = scripts[1].statements[21];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 22
	// setVariable("$array[11][sub(array.length($array[11]), 1)]", 61)
	{
		const ScriptStatement& statement = scripts[1].statements[22];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 23
	// console.log("array length: ", array.length($array))
	{
		const ScriptStatement& statement = scripts[1].statements[23];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: array.length
			if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
				Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
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

	// Statement: 24
	// console.log("array iteration with array.get(): ")
	{
		const ScriptStatement& statement = scripts[1].statements[24];
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

	// Statement: 25
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[25];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 26
	miniscript_statement_26:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[1].statements[26];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: array.length
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
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
				goto miniscript_statement_30;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 27
	miniscript_statement_27:
	// console.log(add($i,add(": ", array.get($array, $i))))
	{
		const ScriptStatement& statement = scripts[1].statements[27];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: array.get
					int64_t index;
					if ((argumentValues.size() <= 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
						MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
						Console::println("ScriptMethodArrayGet::executeMethod(): " + string("array.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: integer expected");
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

	// Statement: 28
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[28];
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

	// Statement: 29
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[29];
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
				goto miniscript_statement_26;
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

	// Statement: 30
	miniscript_statement_30:
	// console.log("array iteration with [] operator: ")
	{
		const ScriptStatement& statement = scripts[1].statements[30];
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

	// Statement: 31
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[31];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 32
	miniscript_statement_32:
	// forCondition(lesser($i, array.length($array)))
	{
		const ScriptStatement& statement = scripts[1].statements[32];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: array.length
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
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
				goto miniscript_statement_36;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 33
	miniscript_statement_33:
	// console.log(add($i,add(": ", $array[$i])))
	{
		const ScriptStatement& statement = scripts[1].statements[33];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 34
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[34];
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

	// Statement: 35
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[35];
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
				goto miniscript_statement_32;
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

	// Statement: 36
	miniscript_statement_36:
	// console.log("array iteration with [] opertator and some index math: ")
	{
		const ScriptStatement& statement = scripts[1].statements[36];
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

	// Statement: 37
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[37];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 38
	miniscript_statement_38:
	// forCondition(lesser($i,div(array.length($array), 2)))
	{
		const ScriptStatement& statement = scripts[1].statements[38];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: array.length
					if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
						Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
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
				goto miniscript_statement_43;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 39
	miniscript_statement_39:
	// console.log(add($i,add("-a: ", $array[add(mul($i, 2), 0)])))
	{
		const ScriptStatement& statement = scripts[1].statements[39];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 40
	// console.log(add($i,add("-b: ", $array[add(mul($i, 2), 1)])))
	{
		const ScriptStatement& statement = scripts[1].statements[40];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 41
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[41];
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

	// Statement: 42
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[42];
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
				goto miniscript_statement_38;
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

	// Statement: 43
	miniscript_statement_43:
	// console.log("array removal of 123, 1234, 12345 using array.removeOf")
	{
		const ScriptStatement& statement = scripts[1].statements[43];
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

	// Statement: 44
	// array.removeOf($array, 123)
	{
		const ScriptStatement& statement = scripts[1].statements[44];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$array")
		argumentValues[1].setValue(static_cast<int64_t>(123));
		// depth = 1 / argument index = 0: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: array.removeOf
		string stringValue;
		int64_t index;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
			MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
			Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
		} else {
			auto& array = argumentValues[0];
			for (auto i = 0; i < array.getArraySize(); i++) {
				auto arrayValue = array.getArrayValue(i);
				if (arrayValue.getValueString() == stringValue) {
					array.removeArrayValue(i);
					i--;
				}
			}
		}
		// assign back
		setVariable("$array", argumentValues[0], &statement);
		//
	}

	// Statement: 45
	// array.removeOf($array, 1234)
	{
		const ScriptStatement& statement = scripts[1].statements[45];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$array")
		argumentValues[1].setValue(static_cast<int64_t>(1234));
		// depth = 1 / argument index = 0: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: array.removeOf
		string stringValue;
		int64_t index;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
			MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
			Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
		} else {
			auto& array = argumentValues[0];
			for (auto i = 0; i < array.getArraySize(); i++) {
				auto arrayValue = array.getArrayValue(i);
				if (arrayValue.getValueString() == stringValue) {
					array.removeArrayValue(i);
					i--;
				}
			}
		}
		// assign back
		setVariable("$array", argumentValues[0], &statement);
		//
	}

	// Statement: 46
	// array.removeOf($array, 12345)
	{
		const ScriptStatement& statement = scripts[1].statements[46];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$array")
		argumentValues[1].setValue(static_cast<int64_t>(12345));
		// depth = 1 / argument index = 0: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$array"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: array.removeOf
		string stringValue;
		int64_t index;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
			MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false) {
			Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.removeOf") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
		} else {
			auto& array = argumentValues[0];
			for (auto i = 0; i < array.getArraySize(); i++) {
				auto arrayValue = array.getArrayValue(i);
				if (arrayValue.getValueString() == stringValue) {
					array.removeArrayValue(i);
					i--;
				}
			}
		}
		// assign back
		setVariable("$array", argumentValues[0], &statement);
		//
	}

	// Statement: 47
	// console.log("array now looks like: ", $array)
	{
		const ScriptStatement& statement = scripts[1].statements[47];
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

	// Statement: 48
	// console.log("array indexOf 10: ", array.indexOf($array, 10))
	{
		const ScriptStatement& statement = scripts[1].statements[48];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.indexOf") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
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

	// Statement: 49
	// console.log("array indexOf 10 beginning to search from 6: ", array.indexOf($array, 10, 6))
	{
		const ScriptStatement& statement = scripts[1].statements[49];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
				Console::println("ScriptMethodArraySet::executeMethod(): " + string("array.indexOf") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected, @argument 1: mixed expected");
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

	// Statement: 50
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[50];
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

	// Statement: 51
	// console.log("Maps")
	{
		const ScriptStatement& statement = scripts[1].statements[51];
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

	// Statement: 52
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[1].statements[52];
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

	// Statement: 53
	// setVariable("$map", map())
	{
		const ScriptStatement& statement = scripts[1].statements[53];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 54
	// console.log("map initialized with: $map = map()")
	{
		const ScriptStatement& statement = scripts[1].statements[54];
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

	// Statement: 55
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[1].statements[55];
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

	// Statement: 56
	// console.log("put some key value pairs into map: map.set()")
	{
		const ScriptStatement& statement = scripts[1].statements[56];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("put some key value pairs into map: map.set()"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 57
	// map.set($map, "test1", 123)
	{
		const ScriptStatement& statement = scripts[1].statements[57];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test1"));
		argumentValues[2].setValue(static_cast<int64_t>(123));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.set
		//
		string key;
		if (argumentValues.size() < 3 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 58
	// map.set($map, "test2", 456)
	{
		const ScriptStatement& statement = scripts[1].statements[58];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test2"));
		argumentValues[2].setValue(static_cast<int64_t>(456));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.set
		//
		string key;
		if (argumentValues.size() < 3 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 59
	// map.set($map, "test3", 789)
	{
		const ScriptStatement& statement = scripts[1].statements[59];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test3"));
		argumentValues[2].setValue(static_cast<int64_t>(789));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.set
		//
		string key;
		if (argumentValues.size() < 3 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 60
	// map.set($map, "test4", array(1,2,3))
	{
		const ScriptStatement& statement = scripts[1].statements[60];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test4"));
		// argumentValues[2] --> returnValue of array(1,2,3)
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// depth = 1 / argument index = 2: array(1, 2, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[2];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX2 = argumentValues;
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
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 61
	// map.set($map, "test5", "Yaaaa")
	{
		const ScriptStatement& statement = scripts[1].statements[61];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test5"));
		argumentValues[2].setValue(string("Yaaaa"));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.set
		//
		string key;
		if (argumentValues.size() < 3 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 62
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[1].statements[62];
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

	// Statement: 63
	// console.log("remove test2 via map.remove: ")
	{
		const ScriptStatement& statement = scripts[1].statements[63];
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

	// Statement: 64
	// map.remove($map, "test2")
	{
		const ScriptStatement& statement = scripts[1].statements[64];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test2"));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.remove
		//
		string key;
		if (argumentValues.size() < 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapRemove::executeMethod(): " + string("map.remove") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
		} else {
			argumentValues[0].removeMapValue(key);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 65
	// console.log("map now looks like: ", $map)
	{
		const ScriptStatement& statement = scripts[1].statements[65];
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

	// Statement: 66
	// map.set($map, "test2", 456)
	{
		const ScriptStatement& statement = scripts[1].statements[66];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$map")
		argumentValues[1].setValue(string("test2"));
		argumentValues[2].setValue(static_cast<int64_t>(456));
		// depth = 1 / argument index = 0: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$map"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: map.set
		//
		string key;
		if (argumentValues.size() < 3 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodMapSet::executeMethod(): " + string("map.set") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string, @ argument 2: mixed expected");
		} else {
			argumentValues[0].setMapValue(key, argumentValues[2]);
		}
		// assign back
		setVariable("$map", argumentValues[0], &statement);
		//
	}

	// Statement: 67
	// console.log("readding test2: ")
	{
		const ScriptStatement& statement = scripts[1].statements[67];
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

	// Statement: 68
	// console.log("map does have test2 key using map.has(): ", map.has($map, "test2"))
	{
		const ScriptStatement& statement = scripts[1].statements[68];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapHas::executeMethod(): " + string("map.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 69
	// console.log("map does have test8 key using map.has(): ", map.has($map, "test8"))
	{
		const ScriptStatement& statement = scripts[1].statements[69];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapHas::executeMethod(): " + string("map.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 70
	// console.log("map value for test1 key using map.get(): ", map.get($map, "test1"))
	{
		const ScriptStatement& statement = scripts[1].statements[70];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 71
	// console.log("map value for test2 key using map.get(): ", map.get($map, "test2"))
	{
		const ScriptStatement& statement = scripts[1].statements[71];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 72
	// console.log("map value for test3 key using map.get(): ", map.get($map, "test3"))
	{
		const ScriptStatement& statement = scripts[1].statements[72];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 73
	// console.log("map value for test4 key using map.get(): ", map.get($map, "test4"))
	{
		const ScriptStatement& statement = scripts[1].statements[73];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 74
	// console.log("map value for test5 key using map.get(): ", map.get($map, "test5"))
	{
		const ScriptStatement& statement = scripts[1].statements[74];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.get
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 75
	// console.log("map value for test1 using map dot operator: ", $map.test1)
	{
		const ScriptStatement& statement = scripts[1].statements[75];
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

	// Statement: 76
	// console.log("map value for test2 using map dot operator: ", $map.test2)
	{
		const ScriptStatement& statement = scripts[1].statements[76];
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

	// Statement: 77
	// console.log("map value for test3 using map dot operator: ", $map.test3)
	{
		const ScriptStatement& statement = scripts[1].statements[77];
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

	// Statement: 78
	// console.log("map value for test4 using map dot operator: ", $map.test4)
	{
		const ScriptStatement& statement = scripts[1].statements[78];
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

	// Statement: 79
	// console.log("map value for test5 using map dot operator: ", $map.test5)
	{
		const ScriptStatement& statement = scripts[1].statements[79];
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

	// Statement: 80
	// console.log("adding map values using map dot operator: ")
	{
		const ScriptStatement& statement = scripts[1].statements[80];
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

	// Statement: 81
	// setVariable("$map.test6", 666)
	{
		const ScriptStatement& statement = scripts[1].statements[81];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 82
	// setVariable("$map.test7", 770)
	{
		const ScriptStatement& statement = scripts[1].statements[82];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 83
	// setVariable("$map.test8", 890)
	{
		const ScriptStatement& statement = scripts[1].statements[83];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 84
	// console.log("map keys: ", map.getKeys($map))
	{
		const ScriptStatement& statement = scripts[1].statements[84];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getKeys
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetKeys::executeMethod(): " + string("map.getKeys") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected");
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

	// Statement: 85
	// console.log("map values: ", map.getValues($map))
	{
		const ScriptStatement& statement = scripts[1].statements[85];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getValues
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetValues::executeMethod(): " + string("map.getValues") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected");
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

	// Statement: 86
	// console.log("iterating keys and values using map.getKeys(): ")
	{
		const ScriptStatement& statement = scripts[1].statements[86];
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

	// Statement: 87
	// setVariable("$mapKeys", map.getKeys($map))
	{
		const ScriptStatement& statement = scripts[1].statements[87];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: map.getKeys
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
				Console::println("ScriptMethodMapGetKeys::executeMethod(): " + string("map.getKeys") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected");
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 88
	// setVariable("$i", 0)
	{
		const ScriptStatement& statement = scripts[1].statements[88];
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
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1], &statement);
			returnValue = argumentValues[1];
		}
	}

	// Statement: 89
	miniscript_statement_89:
	// forCondition(lesser($i, array.length($mapKeys)))
	{
		const ScriptStatement& statement = scripts[1].statements[89];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: array.length
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println("ScriptMethodArrayLength::executeMethod(): " + string("array.length") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: array expected");
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
				goto miniscript_statement_93;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}

	// Statement: 90
	miniscript_statement_90:
	// console.log(add($mapKeys[$i],add(" = ", map.get($map, $mapKeys[$i]))))
	{
		const ScriptStatement& statement = scripts[1].statements[90];
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
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
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
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
							miniScript->startErrorScript(); return;
						}
					}
					// method code: map.get
					//
					string key;
					if (argumentValues.size() < 2 ||
						argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
						MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
						Console::println("ScriptMethodMapGet::executeMethod(): " + string("map.get") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected, @ argument 1: string");
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

	// Statement: 91
	// setVariable("$i", add($i, 1))
	{
		const ScriptStatement& statement = scripts[1].statements[91];
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

	// Statement: 92
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[92];
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
				goto miniscript_statement_89;
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

	// Statement: 93
	miniscript_statement_93:
	// console.log("---------")
	{
		const ScriptStatement& statement = scripts[1].statements[93];
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

	// Statement: 94
	// console.log("Sets")
	{
		const ScriptStatement& statement = scripts[1].statements[94];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Sets"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 95
	// console.log("----------")
	{
		const ScriptStatement& statement = scripts[1].statements[95];
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

	// Statement: 96
	// setVariable("$set", set())
	{
		const ScriptStatement& statement = scripts[1].statements[96];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$set"));
		// argumentValues[1] --> returnValue of set()
		// depth = 1 / argument index = 1: set()
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues;
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: set
			returnValue.setType(MiniScript::TYPE_SET);
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

	// Statement: 97
	// console.log("set initialized with: $set = set()")
	{
		const ScriptStatement& statement = scripts[1].statements[97];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set initialized with: $set = set()"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 98
	// console.log("set now looks like: ", $set)
	{
		const ScriptStatement& statement = scripts[1].statements[98];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$set")
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set"));
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

	// Statement: 99
	// console.log("put some keys into set: set.insert()")
	{
		const ScriptStatement& statement = scripts[1].statements[99];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("put some keys into set: set.insert()"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 100
	// set.insert($set, "test1")
	{
		const ScriptStatement& statement = scripts[1].statements[100];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test1"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.insert
		//
		string key;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetInsert::executeMethod(): " + string("set.insert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string expected");
		} else {
			argumentValues[0].insertSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 101
	// set.insert($set, "test2")
	{
		const ScriptStatement& statement = scripts[1].statements[101];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test2"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.insert
		//
		string key;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetInsert::executeMethod(): " + string("set.insert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string expected");
		} else {
			argumentValues[0].insertSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 102
	// set.insert($set, "test3")
	{
		const ScriptStatement& statement = scripts[1].statements[102];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test3"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.insert
		//
		string key;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetInsert::executeMethod(): " + string("set.insert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string expected");
		} else {
			argumentValues[0].insertSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 103
	// set.insert($set, "test4")
	{
		const ScriptStatement& statement = scripts[1].statements[103];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test4"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.insert
		//
		string key;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetInsert::executeMethod(): " + string("set.insert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string expected");
		} else {
			argumentValues[0].insertSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 104
	// set.insert($set, "test5")
	{
		const ScriptStatement& statement = scripts[1].statements[104];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test5"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.insert
		//
		string key;
		if (argumentValues.size() != 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetInsert::executeMethod(): " + string("set.insert") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string expected");
		} else {
			argumentValues[0].insertSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 105
	// console.log("set now looks like: ", $set)
	{
		const ScriptStatement& statement = scripts[1].statements[105];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$set")
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set"));
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

	// Statement: 106
	// console.log("remove test2 via set.remove: ")
	{
		const ScriptStatement& statement = scripts[1].statements[106];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("remove test2 via set.remove: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 107
	// set.remove($set, "test2")
	{
		const ScriptStatement& statement = scripts[1].statements[107];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$set")
		argumentValues[1].setValue(string("test2"));
		// depth = 1 / argument index = 0: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$set"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				returnValue = miniScript->getVariable(variable);
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: set.remove
		//
		string key;
		if (argumentValues.size() < 2 ||
			argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
			MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
			Console::println("ScriptMethodSetRemove::executeMethod(): " + string("set.remove") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
		} else {
			argumentValues[0].removeSetKey(key);
		}
		// assign back
		setVariable("$set", argumentValues[0], &statement);
		//
	}

	// Statement: 108
	// console.log("set now looks like: ", $set)
	{
		const ScriptStatement& statement = scripts[1].statements[108];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set now looks like: "));
		// argumentValues[1] --> returnValue of getVariable("$set")
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set"));
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

	// Statement: 109
	// console.log("set does have test1 key using set.has(): ", set.has($set, "test1"))
	{
		const ScriptStatement& statement = scripts[1].statements[109];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set does have test1 key using set.has(): "));
		// argumentValues[1] --> returnValue of set.has($set, "test1")
		// depth = 1 / argument index = 1: set.has($set, "test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			argumentValues[1].setValue(string("test1"));
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodSetHas::executeMethod(): " + string("set.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasSetKey(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 110
	// console.log("set does have test2 key using set.has(): ", set.has($set, "test2"))
	{
		const ScriptStatement& statement = scripts[1].statements[110];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set does have test2 key using set.has(): "));
		// argumentValues[1] --> returnValue of set.has($set, "test2")
		// depth = 1 / argument index = 1: set.has($set, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			argumentValues[1].setValue(string("test2"));
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodSetHas::executeMethod(): " + string("set.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasSetKey(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 111
	// console.log("set does have test3 key using set.has(): ", set.has($set, "test3"))
	{
		const ScriptStatement& statement = scripts[1].statements[111];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set does have test3 key using set.has(): "));
		// argumentValues[1] --> returnValue of set.has($set, "test3")
		// depth = 1 / argument index = 1: set.has($set, "test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			argumentValues[1].setValue(string("test3"));
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodSetHas::executeMethod(): " + string("set.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasSetKey(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 112
	// console.log("set does have test4 key using set.has(): ", set.has($set, "test4"))
	{
		const ScriptStatement& statement = scripts[1].statements[112];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set does have test4 key using set.has(): "));
		// argumentValues[1] --> returnValue of set.has($set, "test4")
		// depth = 1 / argument index = 1: set.has($set, "test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			argumentValues[1].setValue(string("test4"));
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodSetHas::executeMethod(): " + string("set.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasSetKey(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 113
	// console.log("set does have test5 key using set.has(): ", set.has($set, "test5"))
	{
		const ScriptStatement& statement = scripts[1].statements[113];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set does have test5 key using set.has(): "));
		// argumentValues[1] --> returnValue of set.has($set, "test5")
		// depth = 1 / argument index = 1: set.has($set, "test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			argumentValues[1].setValue(string("test5"));
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.has
			//
			string key;
			if (argumentValues.size() < 2 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
				MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
				Console::println("ScriptMethodSetHas::executeMethod(): " + string("set.has") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: set expected, @ argument 1: string");
			} else {
				returnValue.setValue(argumentValues[0].hasSetKey(key));
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 114
	// console.log("set key for test1 using set dot operator: ", $set.test1)
	{
		const ScriptStatement& statement = scripts[1].statements[114];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set key for test1 using set dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$set.test1")
		// depth = 1 / argument index = 1: getVariable("$set.test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set.test1"));
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

	// Statement: 115
	// console.log("set key for test2 using set dot operator: ", $set.test2)
	{
		const ScriptStatement& statement = scripts[1].statements[115];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set key for test2 using set dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$set.test2")
		// depth = 1 / argument index = 1: getVariable("$set.test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set.test2"));
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

	// Statement: 116
	// console.log("set key for test3 using set dot operator: ", $set.test3)
	{
		const ScriptStatement& statement = scripts[1].statements[116];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set key for test3 using set dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$set.test3")
		// depth = 1 / argument index = 1: getVariable("$set.test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set.test3"));
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

	// Statement: 117
	// console.log("set key for test4 using set dot operator: ", $set.test4)
	{
		const ScriptStatement& statement = scripts[1].statements[117];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set key for test4 using set dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$set.test4")
		// depth = 1 / argument index = 1: getVariable("$set.test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set.test4"));
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

	// Statement: 118
	// console.log("set key for test5 using set dot operator: ", $set.test5)
	{
		const ScriptStatement& statement = scripts[1].statements[118];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set key for test5 using set dot operator: "));
		// argumentValues[1] --> returnValue of getVariable("$set.test5")
		// depth = 1 / argument index = 1: getVariable("$set.test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$set.test5"));
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

	// Statement: 119
	// console.log("inserting set values using set dot operator: ")
	{
		const ScriptStatement& statement = scripts[1].statements[119];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("inserting set values using set dot operator: "));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 120
	// setVariable("$set.test6", true)
	{
		const ScriptStatement& statement = scripts[1].statements[120];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$set.test6"));
		argumentValues[1].setValue(true);
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

	// Statement: 121
	// setVariable("$set.test7", true)
	{
		const ScriptStatement& statement = scripts[1].statements[121];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$set.test7"));
		argumentValues[1].setValue(true);
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

	// Statement: 122
	// setVariable("$set.test8", false)
	{
		const ScriptStatement& statement = scripts[1].statements[122];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$set.test8"));
		argumentValues[1].setValue(false);
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

	// Statement: 123
	// setVariable("$set.test9", true)
	{
		const ScriptStatement& statement = scripts[1].statements[123];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$set.test9"));
		argumentValues[1].setValue(true);
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

	// Statement: 124
	// console.log("set keys: ", set.getKeys($set))
	{
		const ScriptStatement& statement = scripts[1].statements[124];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("set keys: "));
		// argumentValues[1] --> returnValue of set.getKeys($set)
		// depth = 1 / argument index = 1: set.getKeys($set)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$set")
			// depth = 2 / argument index = 0: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$set"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable);
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: set.getKeys
			//
			if (argumentValues.size() != 1 ||
				argumentValues[0].getType() != ScriptVariableType::TYPE_SET) {
				Console::println("ScriptMethodSetGetKeys::executeMethod(): " + string("set.getKeys") + "(): " + miniScript->getStatementInformation(statement) + ": parameter type mismatch @ argument 0: map expected");
			} else {
				auto keys = argumentValues[0].getSetKeys();
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

	// Statement: 125
	// script.stop()
	{
		const ScriptStatement& statement = scripts[1].statements[125];
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

	// Statement: 126
	// end()
	{
		const ScriptStatement& statement = scripts[1].statements[126];
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

void MiniScriptAdvancedTest::on_error(int miniScriptGotoStatementIdx) {
	// -1 means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_NONE) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// Statement: 0
	// console.log("----------------------")
	{
		const ScriptStatement& statement = scripts[2].statements[0];
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
	// console.log("advanced-test: Error")
	{
		const ScriptStatement& statement = scripts[2].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("advanced-test: Error"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}

	// Statement: 2
	// console.log("----------------------")
	{
		const ScriptStatement& statement = scripts[2].statements[2];
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
