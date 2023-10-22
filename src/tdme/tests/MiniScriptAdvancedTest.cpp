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
	setNativeHash("2c8e7f67417b803c3160a2a0c3b1dc8150eed1865766f282ea214c906001d605");
	setNativeScripts(
		{
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				2,
				"sortFunctionDesc",
				"sortFunctionDesc",
				ScriptStatement(
					2,
					0,
					"sortFunctionDesc",
					"sortFunctionDesc",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						3,
						0,
						"return($a > $b)",
						"return(greater($a, $b))",
						-1
					),
					ScriptStatement(
						4,
						1,
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
						false
					)
				}
			),
			Script(
				Script::SCRIPTTYPE_FUNCTION,
				7,
				"sortFunctionAsc",
				"sortFunctionAsc",
				ScriptStatement(
					7,
					0,
					"sortFunctionAsc",
					"sortFunctionAsc",
					-1
				),
				{},
				"",
				true,
				{
					ScriptStatement(
						8,
						0,
						"return($a < $b)",
						"return(lesser($a, $b))",
						-1
					),
					ScriptStatement(
						9,
						1,
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
						false
					)
				}
			),
			Script(
				Script::SCRIPTTYPE_ON,
				12,
				"initialize",
				"initialize",
				ScriptStatement(
					12,
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
						13,
						0,
						"console.log(\"---------------------------\")",
						"console.log(\"---------------------------\")",
						-1
					),
					ScriptStatement(
						14,
						1,
						"console.log(\"advanced-test: Initialize\")",
						"console.log(\"advanced-test: Initialize\")",
						-1
					),
					ScriptStatement(
						15,
						2,
						"console.log(\"--------------------------\")",
						"console.log(\"--------------------------\")",
						-1
					),
					ScriptStatement(
						16,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						17,
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
				20,
				"nothing",
				"nothing",
				ScriptStatement(
					20,
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
						21,
						0,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						22,
						1,
						"console.log(\"advanced-test: Nothing\")",
						"console.log(\"advanced-test: Nothing\")",
						-1
					),
					ScriptStatement(
						23,
						2,
						"console.log(\"------------------------\")",
						"console.log(\"------------------------\")",
						-1
					),
					ScriptStatement(
						24,
						3,
						"console.log()",
						"console.log()",
						-1
					),
					ScriptStatement(
						25,
						4,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						26,
						5,
						"console.log(\"Arrays\")",
						"console.log(\"Arrays\")",
						-1
					),
					ScriptStatement(
						27,
						6,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						28,
						7,
						"$array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]",
						"setVariable(\"$array\", [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}])",
						-1
					),
					ScriptStatement(
						29,
						8,
						"console.log(\"array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: \" + $array)",
						"console.log(add(\"array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: \", $array))",
						-1
					),
					ScriptStatement(
						30,
						9,
						"$array = array(1, 2, 3)",
						"setVariable(\"$array\", array(1, 2, 3))",
						-1
					),
					ScriptStatement(
						31,
						10,
						"console.log(\"array initialized with: $array = array(1, 2, 3): \" + $array)",
						"console.log(add(\"array initialized with: $array = array(1, 2, 3): \", $array))",
						-1
					),
					ScriptStatement(
						32,
						11,
						"$array->push(8, 9, 10, 99, 10)",
						"$array->push(8, 9, 10, 99, 10)",
						-1
					),
					ScriptStatement(
						33,
						12,
						"console.log(\"array pushed values with: $array->push(8, 9, 10, 99, 10)\")",
						"console.log(\"array pushed values with: $array->push(8, 9, 10, 99, 10)\")",
						-1
					),
					ScriptStatement(
						34,
						13,
						"console.log(\"array now looks like: \", $array)",
						"console.log(\"array now looks like: \", $array)",
						-1
					),
					ScriptStatement(
						35,
						14,
						"$array[] = 123",
						"setVariable(\"$array[]\", 123)",
						-1
					),
					ScriptStatement(
						36,
						15,
						"$array[] = 1234",
						"setVariable(\"$array[]\", 1234)",
						-1
					),
					ScriptStatement(
						37,
						16,
						"$array[] = 12345",
						"setVariable(\"$array[]\", 12345)",
						-1
					),
					ScriptStatement(
						38,
						17,
						"$array[] = array(1,2,3)",
						"setVariable(\"$array[]\", array(1,2,3))",
						-1
					),
					ScriptStatement(
						39,
						18,
						"console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						"console.log(\"array values added with [] operator: 123, 1234, 12345, array(1,2,3)\")",
						-1
					),
					ScriptStatement(
						40,
						19,
						"console.log(\"array now looks like: \", $array)",
						"console.log(\"array now looks like: \", $array)",
						-1
					),
					ScriptStatement(
						41,
						20,
						"console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						"console.log(\"array values added with [] operator to push to array of array: 50, 60\")",
						-1
					),
					ScriptStatement(
						42,
						21,
						"$array[11][] = 50",
						"setVariable(\"$array[11][]\", 50)",
						-1
					),
					ScriptStatement(
						43,
						22,
						"$array[11][] = 60",
						"setVariable(\"$array[11][]\", 60)",
						-1
					),
					ScriptStatement(
						44,
						23,
						"$array[11][$array[11]->length() - 1] = 61",
						"setVariable(\"$array[11][sub($array[11]->length(), 1)]\", 61)",
						-1
					),
					ScriptStatement(
						45,
						24,
						"console.log(\"array length: \", $array->length())",
						"console.log(\"array length: \", $array->length())",
						-1
					),
					ScriptStatement(
						46,
						25,
						"console.log(\"array iteration with $array->get(): \")",
						"console.log(\"array iteration with $array->get(): \")",
						-1
					),
					ScriptStatement(
						47,
						26,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						48,
						27,
						"forCondition($i < $array->length())",
						"forCondition(lesser($i, $array->length()))",
						31
					),
					ScriptStatement(
						49,
						28,
						"console.log($i + \": \" + $array->get($i))",
						"console.log(add($i,add(\": \", $array->get($i))))",
						-1
					),
					ScriptStatement(
						50,
						29,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						51,
						30,
						"end",
						"end",
						27
					),
					ScriptStatement(
						52,
						31,
						"console.log(\"array iteration with [] operator: \")",
						"console.log(\"array iteration with [] operator: \")",
						-1
					),
					ScriptStatement(
						53,
						32,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						54,
						33,
						"forCondition($i < $array->length())",
						"forCondition(lesser($i, $array->length()))",
						37
					),
					ScriptStatement(
						55,
						34,
						"console.log($i + \": \" + $array[$i])",
						"console.log(add($i,add(\": \", $array[$i])))",
						-1
					),
					ScriptStatement(
						56,
						35,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						57,
						36,
						"end",
						"end",
						33
					),
					ScriptStatement(
						58,
						37,
						"console.log(\"array iteration with [] opertator and some index math: \")",
						"console.log(\"array iteration with [] opertator and some index math: \")",
						-1
					),
					ScriptStatement(
						59,
						38,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						60,
						39,
						"forCondition($i < $array->length() / 2)",
						"forCondition(lesser($i,div($array->length(), 2)))",
						44
					),
					ScriptStatement(
						61,
						40,
						"console.log($i + \"-a: \" + $array[$i * 2 + 0])",
						"console.log(add($i,add(\"-a: \", $array[add(mul($i, 2), 0)])))",
						-1
					),
					ScriptStatement(
						62,
						41,
						"console.log($i + \"-b: \" + $array[$i * 2 + 1])",
						"console.log(add($i,add(\"-b: \", $array[add(mul($i, 2), 1)])))",
						-1
					),
					ScriptStatement(
						63,
						42,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						64,
						43,
						"end",
						"end",
						39
					),
					ScriptStatement(
						65,
						44,
						"console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						"console.log(\"array removal of 123, 1234, 12345 using array.removeOf\")",
						-1
					),
					ScriptStatement(
						66,
						45,
						"$array->removeOf(123)",
						"$array->removeOf(123)",
						-1
					),
					ScriptStatement(
						67,
						46,
						"$array->removeOf(1234)",
						"$array->removeOf(1234)",
						-1
					),
					ScriptStatement(
						68,
						47,
						"$array->removeOf(12345)",
						"$array->removeOf(12345)",
						-1
					),
					ScriptStatement(
						69,
						48,
						"console.log(\"array now looks like: \", $array)",
						"console.log(\"array now looks like: \", $array)",
						-1
					),
					ScriptStatement(
						70,
						49,
						"console.log(\"array indexOf 10: \", $array->indexOf(10))",
						"console.log(\"array indexOf 10: \", $array->indexOf(10))",
						-1
					),
					ScriptStatement(
						71,
						50,
						"console.log(\"array indexOf 10 beginning to search from 6: \", $array->indexOf(10, 6))",
						"console.log(\"array indexOf 10 beginning to search from 6: \", $array->indexOf(10, 6))",
						-1
					),
					ScriptStatement(
						72,
						51,
						"console.log(\"sorting of array('abc', 'def', 'ghi', 'jkl', 'mno'): \", $array = array(\"abc\", \"def\", \"ghi\", \"jkl\", \"mno\"))",
						"console.log(\"sorting of array('abc', 'def', 'ghi', 'jkl', 'mno'): \",setVariable(\"$array\", array(\"abc\", \"def\", \"ghi\", \"jkl\", \"mno\")))",
						-1
					),
					ScriptStatement(
						73,
						52,
						"$array->sort(\"sortFunctionDesc\")",
						"$array->sort(\"sortFunctionDesc\")",
						-1
					),
					ScriptStatement(
						74,
						53,
						"console.log(\"$array->sort('sortFunctionDesc'): \", $array)",
						"console.log(\"$array->sort('sortFunctionDesc'): \", $array)",
						-1
					),
					ScriptStatement(
						75,
						54,
						"$array->sort(\"sortFunctionAsc\")",
						"$array->sort(\"sortFunctionAsc\")",
						-1
					),
					ScriptStatement(
						76,
						55,
						"console.log(\"$array->sort('sortFunctionAsc'): \", $array)",
						"console.log(\"$array->sort('sortFunctionAsc'): \", $array)",
						-1
					),
					ScriptStatement(
						77,
						56,
						"$array->reverse()",
						"$array->reverse()",
						-1
					),
					ScriptStatement(
						78,
						57,
						"console.log(\"array reverse: \", $array)",
						"console.log(\"array reverse: \", $array)",
						-1
					),
					ScriptStatement(
						79,
						58,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						80,
						59,
						"console.log(\"Maps\")",
						"console.log(\"Maps\")",
						-1
					),
					ScriptStatement(
						81,
						60,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						82,
						61,
						"$map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}",
						"setVariable(\"$map\", {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}})",
						-1
					),
					ScriptStatement(
						83,
						62,
						"console.log(\"map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: \" + $map)",
						"console.log(add(\"map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: \", $map))",
						-1
					),
					ScriptStatement(
						84,
						63,
						"$map = map()",
						"setVariable(\"$map\", map())",
						-1
					),
					ScriptStatement(
						85,
						64,
						"console.log(\"map initialized with: $map = map(): \" + $map)",
						"console.log(add(\"map initialized with: $map = map(): \", $map))",
						-1
					),
					ScriptStatement(
						86,
						65,
						"console.log(\"put some key value pairs into map: map->set()\")",
						"console.log(\"put some key value pairs into map: map->set()\")",
						-1
					),
					ScriptStatement(
						87,
						66,
						"$map->set(\"test1\", 123)",
						"$map->set(\"test1\", 123)",
						-1
					),
					ScriptStatement(
						88,
						67,
						"$map->set(\"test2\", 456)",
						"$map->set(\"test2\", 456)",
						-1
					),
					ScriptStatement(
						89,
						68,
						"$map->set(\"test3\", 789)",
						"$map->set(\"test3\", 789)",
						-1
					),
					ScriptStatement(
						90,
						69,
						"$map->set(\"test4\", array(1,2,3))",
						"$map->set(\"test4\", array(1,2,3))",
						-1
					),
					ScriptStatement(
						91,
						70,
						"$map->set(\"test5\", \"Yaaaa\")",
						"$map->set(\"test5\", \"Yaaaa\")",
						-1
					),
					ScriptStatement(
						92,
						71,
						"console.log(\"map now looks like: \", $map)",
						"console.log(\"map now looks like: \", $map)",
						-1
					),
					ScriptStatement(
						93,
						72,
						"console.log(\"remove test2 via $map->remove: \")",
						"console.log(\"remove test2 via $map->remove: \")",
						-1
					),
					ScriptStatement(
						94,
						73,
						"$map->remove(\"test2\")",
						"$map->remove(\"test2\")",
						-1
					),
					ScriptStatement(
						95,
						74,
						"console.log(\"map now looks like: \", $map)",
						"console.log(\"map now looks like: \", $map)",
						-1
					),
					ScriptStatement(
						96,
						75,
						"$map->set(\"test2\", 456)",
						"$map->set(\"test2\", 456)",
						-1
					),
					ScriptStatement(
						97,
						76,
						"console.log(\"reading map key(+value) pairs: \")",
						"console.log(\"reading map key(+value) pairs: \")",
						-1
					),
					ScriptStatement(
						98,
						77,
						"console.log(\"map does have test2 key using $map->has(): \", $map->has(\"test2\"))",
						"console.log(\"map does have test2 key using $map->has(): \", $map->has(\"test2\"))",
						-1
					),
					ScriptStatement(
						99,
						78,
						"console.log(\"map does have test8 key using $map->has(): \", $map->has(\"test8\"))",
						"console.log(\"map does have test8 key using $map->has(): \", $map->has(\"test8\"))",
						-1
					),
					ScriptStatement(
						100,
						79,
						"console.log(\"map value for test1 key using $map->get(): \", $map->get(\"test1\"))",
						"console.log(\"map value for test1 key using $map->get(): \", $map->get(\"test1\"))",
						-1
					),
					ScriptStatement(
						101,
						80,
						"console.log(\"map value for test2 key using $map->get(): \", $map->get(\"test2\"))",
						"console.log(\"map value for test2 key using $map->get(): \", $map->get(\"test2\"))",
						-1
					),
					ScriptStatement(
						102,
						81,
						"console.log(\"map value for test3 key using $map->get(): \", $map->get(\"test3\"))",
						"console.log(\"map value for test3 key using $map->get(): \", $map->get(\"test3\"))",
						-1
					),
					ScriptStatement(
						103,
						82,
						"console.log(\"map value for test4 key using $map->get(): \", $map->get(\"test4\"))",
						"console.log(\"map value for test4 key using $map->get(): \", $map->get(\"test4\"))",
						-1
					),
					ScriptStatement(
						104,
						83,
						"console.log(\"map value for test5 key using $map->get(): \", $map->get(\"test5\"))",
						"console.log(\"map value for test5 key using $map->get(): \", $map->get(\"test5\"))",
						-1
					),
					ScriptStatement(
						105,
						84,
						"console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						"console.log(\"map value for test1 using map dot operator: \", $map.test1)",
						-1
					),
					ScriptStatement(
						106,
						85,
						"console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						"console.log(\"map value for test2 using map dot operator: \", $map.test2)",
						-1
					),
					ScriptStatement(
						107,
						86,
						"console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						"console.log(\"map value for test3 using map dot operator: \", $map.test3)",
						-1
					),
					ScriptStatement(
						108,
						87,
						"console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						"console.log(\"map value for test4 using map dot operator: \", $map.test4)",
						-1
					),
					ScriptStatement(
						109,
						88,
						"console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						"console.log(\"map value for test5 using map dot operator: \", $map.test5)",
						-1
					),
					ScriptStatement(
						110,
						89,
						"console.log(\"adding map values using map dot operator: \")",
						"console.log(\"adding map values using map dot operator: \")",
						-1
					),
					ScriptStatement(
						111,
						90,
						"$map.test6 = 666",
						"setVariable(\"$map.test6\", 666)",
						-1
					),
					ScriptStatement(
						112,
						91,
						"$map.test7 = 770",
						"setVariable(\"$map.test7\", 770)",
						-1
					),
					ScriptStatement(
						113,
						92,
						"$map.test8 = 890",
						"setVariable(\"$map.test8\", 890)",
						-1
					),
					ScriptStatement(
						114,
						93,
						"console.log(\"map keys: \", $map->getKeys())",
						"console.log(\"map keys: \", $map->getKeys())",
						-1
					),
					ScriptStatement(
						115,
						94,
						"console.log(\"map values: \", $map->getValues())",
						"console.log(\"map values: \", $map->getValues())",
						-1
					),
					ScriptStatement(
						116,
						95,
						"console.log(\"iterating keys and values using $map->getKeys(): \")",
						"console.log(\"iterating keys and values using $map->getKeys(): \")",
						-1
					),
					ScriptStatement(
						117,
						96,
						"$mapKeys = $map->getKeys()",
						"setVariable(\"$mapKeys\", $map->getKeys())",
						-1
					),
					ScriptStatement(
						118,
						97,
						"$i = 0",
						"setVariable(\"$i\", 0)",
						-1
					),
					ScriptStatement(
						119,
						98,
						"forCondition($i < $mapKeys->length())",
						"forCondition(lesser($i, $mapKeys->length()))",
						102
					),
					ScriptStatement(
						120,
						99,
						"console.log($mapKeys[$i] + \" = \" + $map->get($mapKeys[$i]))",
						"console.log(add($mapKeys[$i],add(\" = \", $map->get($mapKeys[$i]))))",
						-1
					),
					ScriptStatement(
						121,
						100,
						"++$i",
						"prefixIncrement($i)",
						-1
					),
					ScriptStatement(
						122,
						101,
						"end",
						"end",
						98
					),
					ScriptStatement(
						123,
						102,
						"console.log(\"---------\")",
						"console.log(\"---------\")",
						-1
					),
					ScriptStatement(
						124,
						103,
						"console.log(\"Sets\")",
						"console.log(\"Sets\")",
						-1
					),
					ScriptStatement(
						125,
						104,
						"console.log(\"----------\")",
						"console.log(\"----------\")",
						-1
					),
					ScriptStatement(
						126,
						105,
						"$set = {test1, test2, test3, test4, test5}",
						"setVariable(\"$set\", {test1, test2, test3, test4, test5})",
						-1
					),
					ScriptStatement(
						127,
						106,
						"console.log(\"set initialized with: $set = {test1, test2, test3, test4, test5}: \" + $set)",
						"console.log(add(\"set initialized with: $set = {test1, test2, test3, test4, test5}: \", $set))",
						-1
					),
					ScriptStatement(
						128,
						107,
						"$set = set()",
						"setVariable(\"$set\", set())",
						-1
					),
					ScriptStatement(
						129,
						108,
						"console.log(\"set initialized with: $set = set(): \" + $set)",
						"console.log(add(\"set initialized with: $set = set(): \", $set))",
						-1
					),
					ScriptStatement(
						130,
						109,
						"console.log(\"put some keys into set: $set->insert()\")",
						"console.log(\"put some keys into set: $set->insert()\")",
						-1
					),
					ScriptStatement(
						131,
						110,
						"$set->insert(\"test1\")",
						"$set->insert(\"test1\")",
						-1
					),
					ScriptStatement(
						132,
						111,
						"$set->insert(\"test2\")",
						"$set->insert(\"test2\")",
						-1
					),
					ScriptStatement(
						133,
						112,
						"$set->insert(\"test3\")",
						"$set->insert(\"test3\")",
						-1
					),
					ScriptStatement(
						134,
						113,
						"$set->insert(\"test4\")",
						"$set->insert(\"test4\")",
						-1
					),
					ScriptStatement(
						135,
						114,
						"$set->insert(\"test5\")",
						"$set->insert(\"test5\")",
						-1
					),
					ScriptStatement(
						136,
						115,
						"console.log(\"set now looks like: \", $set)",
						"console.log(\"set now looks like: \", $set)",
						-1
					),
					ScriptStatement(
						137,
						116,
						"console.log(\"remove test2 via $set->remove: \")",
						"console.log(\"remove test2 via $set->remove: \")",
						-1
					),
					ScriptStatement(
						138,
						117,
						"$set->remove(\"test2\")",
						"$set->remove(\"test2\")",
						-1
					),
					ScriptStatement(
						139,
						118,
						"console.log(\"set now looks like: \", $set)",
						"console.log(\"set now looks like: \", $set)",
						-1
					),
					ScriptStatement(
						140,
						119,
						"console.log(\"set does have test1 key using $set->has(): \", $set->has(\"test1\"))",
						"console.log(\"set does have test1 key using $set->has(): \", $set->has(\"test1\"))",
						-1
					),
					ScriptStatement(
						141,
						120,
						"console.log(\"set does have test2 key using $set->has(): \", $set->has(\"test2\"))",
						"console.log(\"set does have test2 key using $set->has(): \", $set->has(\"test2\"))",
						-1
					),
					ScriptStatement(
						142,
						121,
						"console.log(\"set does have test3 key using $set->has(): \", $set->has(\"test3\"))",
						"console.log(\"set does have test3 key using $set->has(): \", $set->has(\"test3\"))",
						-1
					),
					ScriptStatement(
						143,
						122,
						"console.log(\"set does have test4 key using $set->has(): \", $set->has(\"test4\"))",
						"console.log(\"set does have test4 key using $set->has(): \", $set->has(\"test4\"))",
						-1
					),
					ScriptStatement(
						144,
						123,
						"console.log(\"set does have test5 key using $set->has(): \", $set->has(\"test5\"))",
						"console.log(\"set does have test5 key using $set->has(): \", $set->has(\"test5\"))",
						-1
					),
					ScriptStatement(
						145,
						124,
						"console.log(\"set key for test1 using set dot operator: \", $set.test1)",
						"console.log(\"set key for test1 using set dot operator: \", $set.test1)",
						-1
					),
					ScriptStatement(
						146,
						125,
						"console.log(\"set key for test2 using set dot operator: \", $set.test2)",
						"console.log(\"set key for test2 using set dot operator: \", $set.test2)",
						-1
					),
					ScriptStatement(
						147,
						126,
						"console.log(\"set key for test3 using set dot operator: \", $set.test3)",
						"console.log(\"set key for test3 using set dot operator: \", $set.test3)",
						-1
					),
					ScriptStatement(
						148,
						127,
						"console.log(\"set key for test4 using set dot operator: \", $set.test4)",
						"console.log(\"set key for test4 using set dot operator: \", $set.test4)",
						-1
					),
					ScriptStatement(
						149,
						128,
						"console.log(\"set key for test5 using set dot operator: \", $set.test5)",
						"console.log(\"set key for test5 using set dot operator: \", $set.test5)",
						-1
					),
					ScriptStatement(
						150,
						129,
						"console.log(\"inserting set values using set dot operator: \")",
						"console.log(\"inserting set values using set dot operator: \")",
						-1
					),
					ScriptStatement(
						151,
						130,
						"$set.test6 = true",
						"setVariable(\"$set.test6\", true)",
						-1
					),
					ScriptStatement(
						152,
						131,
						"$set.test7 = true",
						"setVariable(\"$set.test7\", true)",
						-1
					),
					ScriptStatement(
						153,
						132,
						"$set.test8 = false",
						"setVariable(\"$set.test8\", false)",
						-1
					),
					ScriptStatement(
						154,
						133,
						"$set.test9 = true",
						"setVariable(\"$set.test9\", true)",
						-1
					),
					ScriptStatement(
						155,
						134,
						"console.log(\"set keys: \", $set->getKeys())",
						"console.log(\"set keys: \", $set->getKeys())",
						-1
					),
					ScriptStatement(
						156,
						135,
						"script.stop()",
						"script.stop()",
						-1
					),
					ScriptStatement(
						157,
						136,
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
				160,
				"error",
				"error",
				ScriptStatement(
					160,
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
						161,
						0,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						162,
						1,
						"console.log(\"advanced-test: Error\")",
						"console.log(\"advanced-test: Error\")",
						-1
					),
					ScriptStatement(
						163,
						2,
						"console.log(\"----------------------\")",
						"console.log(\"----------------------\")",
						-1
					),
					ScriptStatement(
						164,
						3,
						"console.log(\"An error occurred\")",
						"console.log(\"An error occurred\")",
						-1
					),
					ScriptStatement(
						165,
						4,
						"script.wait(1000)",
						"script.wait(1000)",
						-1
					),
					ScriptStatement(
						166,
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
				"sortFunctionAsc",
				1
			},
			{
				"sortFunctionDesc",
				0
			}
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
	return 3;
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

void MiniScriptAdvancedTest::sortFunctionDesc(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 0;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::sortFunctionDesc(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// return(greater(getVariable("$a"), getVariable("$b")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of greater(getVariable("$a"), getVariable("$b"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: greater(getVariable("$a"), getVariable("$b"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$a")
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$b")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$a")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$a"))
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
			// depth = 2 / argument index = 1: getVariable("$b")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$b"))
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
	// statement: 1
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[0].statements[1];
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

void MiniScriptAdvancedTest::sortFunctionAsc(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(1, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 1;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::sortFunctionAsc(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// return(lesser(getVariable("$a"), getVariable("$b")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[0];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$a"), getVariable("$b"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$a"), getVariable("$b"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$a")
				ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$b")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 0: getVariable("$a")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$a"))
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
			// depth = 2 / argument index = 1: getVariable("$b")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$b"))
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
	// statement: 1
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[1].statements[1];
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

void MiniScriptAdvancedTest::on_initialize(int miniScriptGotoStatementIdx) {
	// STATEMENTIDX_FIRST means complete method call
	if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 2;
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("---------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[0];
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
		const ScriptStatement& statement = scripts[2].statements[1];
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
		const ScriptStatement& statement = scripts[2].statements[2];
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
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[2].statements[4];
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
		resetScriptExecutationState(3, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 3;
	if (miniScriptGotoStatementIdx == 28) goto miniscript_statement_28; else
	if (miniScriptGotoStatementIdx == 31) goto miniscript_statement_31; else
	if (miniScriptGotoStatementIdx == 34) goto miniscript_statement_34; else
	if (miniScriptGotoStatementIdx == 37) goto miniscript_statement_37; else
	if (miniScriptGotoStatementIdx == 40) goto miniscript_statement_40; else
	if (miniScriptGotoStatementIdx == 44) goto miniscript_statement_44; else
	if (miniScriptGotoStatementIdx == 99) goto miniscript_statement_99; else
	if (miniScriptGotoStatementIdx == 102) goto miniscript_statement_102; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("------------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[0];
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
	// console.log("advanced-test: Nothing")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[1];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("advanced-test: Nothing"))
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
		const ScriptStatement& statement = scripts[3].statements[2];
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
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[4];
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
	// statement: 5
	// console.log("Arrays")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[5];
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
	// statement: 6
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[6];
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
	// statement: 7
	// we will use on_nothing_array_access_statement_s_7_1_0() to determine array access index
	// setVariable("$array", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[7];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array")),
			on_nothing_initializer_s_7_1(statement)
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
	// console.log(add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: ", getVariable("$array")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[8];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: ", getVariable("$array"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: ", getVariable("$array"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("array initialized with: $array = [1, 2, 3, [1, 2, 3], {a: xxx, b: yyy, c: zzz}, {a, b, c}]: ")),
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
	// statement: 9
	// setVariable("$array", array(1, 2, 3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[9];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable() // argumentValues[1] --> returnValue of array(1, 2, 3)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: array(1, 2, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(1ll)),
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(3ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: array
			returnValue.setType(MiniScript::TYPE_ARRAY);
			for (const auto& argumentValue: argumentValues) {
				returnValue.pushArrayValue(argumentValue);
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
	// statement: 10
	// console.log(add("array initialized with: $array = array(1, 2, 3): ", getVariable("$array")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[10];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("array initialized with: $array = array(1, 2, 3): ", getVariable("$array"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("array initialized with: $array = array(1, 2, 3): ", getVariable("$array"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("array initialized with: $array = array(1, 2, 3): ")),
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
	// statement: 11
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "push", <VOID>, 8, <VOID>, 9, <VOID>, 10, <VOID>, 99, <VOID>, 10)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[11];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 13> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("push")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(8ll)),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(9ll)),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(10ll)),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(99ll)),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(10ll))
		};
		array<ScriptVariable, 13>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_PUSH;
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
	// statement: 12
	// console.log("array pushed values with: $array->push(8, 9, 10, 99, 10)")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[12];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array pushed values with: $array->push(8, 9, 10, 99, 10)"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 13
	// console.log("array now looks like: ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[13];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 14
	// setVariable("$array[]", 123)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[14];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[]")),
			ScriptVariable(static_cast<int64_t>(123ll))
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
	// statement: 15
	// setVariable("$array[]", 1234)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[15];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[]")),
			ScriptVariable(static_cast<int64_t>(1234ll))
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
	// statement: 16
	// setVariable("$array[]", 12345)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[16];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[]")),
			ScriptVariable(static_cast<int64_t>(12345ll))
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
	// statement: 17
	// setVariable("$array[]", array(1, 2, 3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[17];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[]")),
			ScriptVariable() // argumentValues[1] --> returnValue of array(1, 2, 3)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: array(1, 2, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(1ll)),
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(3ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// method code: array
			returnValue.setType(MiniScript::TYPE_ARRAY);
			for (const auto& argumentValue: argumentValues) {
				returnValue.pushArrayValue(argumentValue);
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
	// statement: 18
	// console.log("array values added with [] operator: 123, 1234, 12345, array(1,2,3)")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[18];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array values added with [] operator: 123, 1234, 12345, array(1,2,3)"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 19
	// console.log("array now looks like: ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[19];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 20
	// console.log("array values added with [] operator to push to array of array: 50, 60")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[20];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array values added with [] operator to push to array of array: 50, 60"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 21
	// we will use on_nothing_array_access_statement_s_21_0_0() to determine array access index
	// setVariable("$array[11][]", 50)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[21];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_21_0_0(statement).getValueAsString() + "][]")),
			ScriptVariable(static_cast<int64_t>(50ll))
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
	// statement: 22
	// we will use on_nothing_array_access_statement_s_22_0_0() to determine array access index
	// setVariable("$array[11][]", 60)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[22];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_22_0_0(statement).getValueAsString() + "][]")),
			ScriptVariable(static_cast<int64_t>(60ll))
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
	// statement: 23
	// we will use on_nothing_array_access_statement_s_23_0_0() to determine array access index
	// we will use on_nothing_array_access_statement_s_23_0_1() to determine array access index
	// setVariable("$array[11][sub($array[11]->length(), 1)]", 61)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[23];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_23_0_0(statement).getValueAsString() + "][" + on_nothing_array_access_statement_s_23_0_1(statement).getValueAsString() + "]")),
			ScriptVariable(static_cast<int64_t>(61ll))
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
	// statement: 24
	// console.log("array length: ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[24];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array length: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$array")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
				ScriptVariable(string("length"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
	// statement: 25
	// console.log("array iteration with $array->get(): ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[25];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array iteration with $array->get(): "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 26
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[26];
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
	// statement: 27
	miniscript_statement_27:
	// forCondition(lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[27];
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
				goto miniscript_statement_31;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 28
	miniscript_statement_28:
	// console.log(add(getVariable("$i"), add(": ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i")))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[28];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add(getVariable("$i"), add(": ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i"))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add(getVariable("$i"), add(": ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of add(": ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i")))
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
			// depth = 2 / argument index = 1: add(": ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string(": ")),
					ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "get", "$i", getVariable("$i"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 5> argumentValues {
						ScriptVariable(string("$array")),
						ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
						ScriptVariable(string("get")),
						ScriptVariable(string("$i")),
						ScriptVariable() // argumentValues[4] --> returnValue of getVariable("$i")
					};
					array<ScriptVariable, 5>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: getVariable("$array")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$array"))
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
					// depth = 4 / argument index = 4: getVariable("$i")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[4];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$i"))
						};
						array<ScriptVariable, 1>& argumentValuesD4AIDX4 = argumentValues;
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable, &statement);
						} else {
							Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
							miniScript->startErrorScript(); return;
						}
					}
					const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 29
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[29];
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
	// statement: 30
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[30];
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
				goto miniscript_statement_27;
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
	// statement: 31
	miniscript_statement_31:
	// console.log("array iteration with [] operator: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[31];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array iteration with [] operator: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 32
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[32];
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
	// statement: 33
	miniscript_statement_33:
	// forCondition(lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[33];
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
				goto miniscript_statement_37;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 34
	miniscript_statement_34:
	// console.log(add(getVariable("$i"), add(": ", getVariable("$array[$i]"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[34];
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
				// we will use on_nothing_array_access_statement_s_34_0_1_1_0_0() to determine array access index
				// depth = 3 / argument index = 1: getVariable("$array[$i]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_34_0_1_1_0_0(statement).getValueAsString() + "]"))
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
	// statement: 35
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[35];
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
	// statement: 36
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[36];
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
				goto miniscript_statement_33;
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
	// statement: 37
	miniscript_statement_37:
	// console.log("array iteration with [] opertator and some index math: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[37];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array iteration with [] opertator and some index math: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 38
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[38];
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
	// statement: 39
	miniscript_statement_39:
	// forCondition(lesser(getVariable("$i"), div(internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"), 2)))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[39];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$i"), div(internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"), 2))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$i"), div(internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"), 2))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of div(internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"), 2)
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
			// depth = 2 / argument index = 1: div(internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length"), 2)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(), // argumentValues[0] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
					ScriptVariable(static_cast<int64_t>(2ll))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 0: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "length")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 3> argumentValues {
						ScriptVariable(string("$array")),
						ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
						ScriptVariable(string("length"))
					};
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					// depth = 4 / argument index = 1: getVariable("$array")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX0[1];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$array"))
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
				// method code: div
				MiniScriptMath::div(miniScript, argumentValues, returnValue, statement);
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
				goto miniscript_statement_44;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 40
	miniscript_statement_40:
	// console.log(add(getVariable("$i"), add("-a: ", getVariable("$array[add(mul($i, 2), 0)]"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[40];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add(getVariable("$i"), add("-a: ", getVariable("$array[add(mul($i, 2), 0)]")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add(getVariable("$i"), add("-a: ", getVariable("$array[add(mul($i, 2), 0)]")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of add("-a: ", getVariable("$array[add(mul($i, 2), 0)]"))
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
			// depth = 2 / argument index = 1: add("-a: ", getVariable("$array[add(mul($i, 2), 0)]"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("-a: ")),
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array[add(mul($i, 2), 0)]")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// we will use on_nothing_array_access_statement_s_40_0_1_1_0_0() to determine array access index
				// depth = 3 / argument index = 1: getVariable("$array[add(mul($i, 2), 0)]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_40_0_1_1_0_0(statement).getValueAsString() + "]"))
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
	// statement: 41
	// console.log(add(getVariable("$i"), add("-b: ", getVariable("$array[add(mul($i, 2), 1)]"))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[41];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add(getVariable("$i"), add("-b: ", getVariable("$array[add(mul($i, 2), 1)]")))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add(getVariable("$i"), add("-b: ", getVariable("$array[add(mul($i, 2), 1)]")))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of add("-b: ", getVariable("$array[add(mul($i, 2), 1)]"))
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
			// depth = 2 / argument index = 1: add("-b: ", getVariable("$array[add(mul($i, 2), 1)]"))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string("-b: ")),
					ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array[add(mul($i, 2), 1)]")
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// we will use on_nothing_array_access_statement_s_41_0_1_1_0_0() to determine array access index
				// depth = 3 / argument index = 1: getVariable("$array[add(mul($i, 2), 1)]")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$array[" + on_nothing_array_access_statement_s_41_0_1_1_0_0(statement).getValueAsString() + "]"))
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
	// statement: 42
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[42];
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
	// statement: 43
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[43];
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
				goto miniscript_statement_39;
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
	// statement: 44
	miniscript_statement_44:
	// console.log("array removal of 123, 1234, 12345 using array.removeOf")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[44];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("array removal of 123, 1234, 12345 using array.removeOf"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 45
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "removeOf", <VOID>, 123)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[45];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("removeOf")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(123ll))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REMOVEOF;
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
	// statement: 46
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "removeOf", <VOID>, 1234)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[46];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("removeOf")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(1234ll))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REMOVEOF;
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
	// statement: 47
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "removeOf", <VOID>, 12345)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[47];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("removeOf")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(12345ll))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REMOVEOF;
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
	// statement: 48
	// console.log("array now looks like: ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[48];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 49
	// console.log("array indexOf 10: ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[49];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array indexOf 10: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$array")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
				ScriptVariable(string("indexOf")),
				ScriptVariable(),
				ScriptVariable(static_cast<int64_t>(10ll))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INDEXOF;
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
	// statement: 50
	// console.log("array indexOf 10 beginning to search from 6: ", internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10, <VOID>, 6))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[50];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array indexOf 10 beginning to search from 6: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10, <VOID>, 6)
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$array", getVariable("$array"), "indexOf", <VOID>, 10, <VOID>, 6)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 7> argumentValues {
				ScriptVariable(string("$array")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
				ScriptVariable(string("indexOf")),
				ScriptVariable(),
				ScriptVariable(static_cast<int64_t>(10ll)),
				ScriptVariable(),
				ScriptVariable(static_cast<int64_t>(6ll))
			};
			array<ScriptVariable, 7>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$array")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INDEXOF;
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
	// statement: 51
	// console.log("sorting of array('abc', 'def', 'ghi', 'jkl', 'mno'): ", setVariable("$array", array("abc", "def", "ghi", "jkl", "mno")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[51];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("sorting of array('abc', 'def', 'ghi', 'jkl', 'mno'): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of setVariable("$array", array("abc", "def", "ghi", "jkl", "mno"))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: setVariable("$array", array("abc", "def", "ghi", "jkl", "mno"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("$array")),
				ScriptVariable() // argumentValues[1] --> returnValue of array("abc", "def", "ghi", "jkl", "mno")
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: array("abc", "def", "ghi", "jkl", "mno")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 5> argumentValues {
					ScriptVariable(string("abc")),
					ScriptVariable(string("def")),
					ScriptVariable(string("ghi")),
					ScriptVariable(string("jkl")),
					ScriptVariable(string("mno"))
				};
				array<ScriptVariable, 5>& argumentValuesD2AIDX1 = argumentValues;
				// method code: array
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (const auto& argumentValue: argumentValues) {
					returnValue.pushArrayValue(argumentValue);
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
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 52
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "sort", <VOID>, "sortFunctionDesc")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[52];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("sort")),
			ScriptVariable(),
			ScriptVariable(string("sortFunctionDesc"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SORT;
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
	// statement: 53
	// console.log("$array->sort('sortFunctionDesc'): ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[53];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array->sort('sortFunctionDesc'): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 54
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "sort", <VOID>, "sortFunctionAsc")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[54];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("sort")),
			ScriptVariable(),
			ScriptVariable(string("sortFunctionAsc"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SORT;
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
	// statement: 55
	// console.log("$array->sort('sortFunctionAsc'): ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[55];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$array->sort('sortFunctionAsc'): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 56
	// internal.script.evaluateMemberAccess("$array", getVariable("$array"), "reverse")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[56];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues {
			ScriptVariable(string("$array")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array")
			ScriptVariable(string("reverse"))
		};
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REVERSE;
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
	// statement: 57
	// console.log("array reverse: ", getVariable("$array"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[57];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("array reverse: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$array")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$array")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$array"))
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
	// statement: 58
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[58];
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
	// statement: 59
	// console.log("Maps")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[59];
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
	// statement: 60
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[60];
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
	// statement: 61
	// we will use on_nothing_array_access_statement_s_61_1_0() to determine array access index
	// setVariable("$map", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[61];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map")),
			on_nothing_initializer_s_61_1(statement)
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
	// statement: 62
	// console.log(add("map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: ", getVariable("$map")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[62];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: ", getVariable("$map"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: ", getVariable("$map"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("map initialized with: $map = {test1: 123, test2: 456, test3: 789, test4: [1, 2, 3], test5: {a: xxx, b: yyy, c: zzz}, test6: {a, b, c}}: ")),
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
	// statement: 63
	// setVariable("$map", map())
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[63];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable() // argumentValues[1] --> returnValue of map()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: map()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: map
			returnValue.setType(MiniScript::TYPE_MAP);
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
	// statement: 64
	// console.log(add("map initialized with: $map = map(): ", getVariable("$map")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[64];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("map initialized with: $map = map(): ", getVariable("$map"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("map initialized with: $map = map(): ", getVariable("$map"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("map initialized with: $map = map(): ")),
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
	// statement: 65
	// console.log("put some key value pairs into map: map->set()")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[65];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("put some key value pairs into map: map->set()"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 66
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test1", <VOID>, 123)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[66];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test1")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(123ll))
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 67
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test2", <VOID>, 456)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[67];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test2")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(456ll))
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 68
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test3", <VOID>, 789)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[68];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test3")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(789ll))
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 69
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test4", <VOID>, array(1, 2, 3))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[69];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test4")),
			ScriptVariable(),
			ScriptVariable() // argumentValues[6] --> returnValue of array(1, 2, 3)
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		// depth = 1 / argument index = 6: array(1, 2, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[6];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(static_cast<int64_t>(1ll)),
				ScriptVariable(static_cast<int64_t>(2ll)),
				ScriptVariable(static_cast<int64_t>(3ll))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX6 = argumentValues;
			// method code: array
			returnValue.setType(MiniScript::TYPE_ARRAY);
			for (const auto& argumentValue: argumentValues) {
				returnValue.pushArrayValue(argumentValue);
			}
		}
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 70
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test5", <VOID>, "Yaaaa")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[70];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test5")),
			ScriptVariable(),
			ScriptVariable(string("Yaaaa"))
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 71
	// console.log("map now looks like: ", getVariable("$map"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[71];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
	// statement: 72
	// console.log("remove test2 via $map->remove: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[72];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("remove test2 via $map->remove: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 73
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "remove", <VOID>, "test2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[73];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("remove")),
			ScriptVariable(),
			ScriptVariable(string("test2"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REMOVE;
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
	// statement: 74
	// console.log("map now looks like: ", getVariable("$map"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[74];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
	// statement: 75
	// internal.script.evaluateMemberAccess("$map", getVariable("$map"), "set", <VOID>, "test2", <VOID>, 456)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[75];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 7> argumentValues {
			ScriptVariable(string("$map")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
			ScriptVariable(string("set")),
			ScriptVariable(),
			ScriptVariable(string("test2")),
			ScriptVariable(),
			ScriptVariable(static_cast<int64_t>(456ll))
		};
		array<ScriptVariable, 7>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_SET;
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
	// statement: 76
	// console.log("reading map key(+value) pairs: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[76];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("reading map key(+value) pairs: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 77
	// console.log("map does have test2 key using $map->has(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test2"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[77];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map does have test2 key using $map->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test2")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test2"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 78
	// console.log("map does have test8 key using $map->has(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test8"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[78];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map does have test8 key using $map->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test8")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "has", <VOID>, "test8")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test8"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 79
	// console.log("map value for test1 key using $map->get(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test1"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[79];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test1 key using $map->get(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test1")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("get")),
				ScriptVariable(),
				ScriptVariable(string("test1"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 80
	// console.log("map value for test2 key using $map->get(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test2"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[80];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test2 key using $map->get(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test2")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("get")),
				ScriptVariable(),
				ScriptVariable(string("test2"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 81
	// console.log("map value for test3 key using $map->get(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test3"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[81];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test3 key using $map->get(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test3")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("get")),
				ScriptVariable(),
				ScriptVariable(string("test3"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 82
	// console.log("map value for test4 key using $map->get(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test4"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[82];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test4 key using $map->get(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test4")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("get")),
				ScriptVariable(),
				ScriptVariable(string("test4"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 83
	// console.log("map value for test5 key using $map->get(): ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test5"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[83];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test5 key using $map->get(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test5")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", <VOID>, "test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("get")),
				ScriptVariable(),
				ScriptVariable(string("test5"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 84
	// console.log("map value for test1 using map dot operator: ", getVariable("$map.test1"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[84];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test1 using map dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map.test1")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map.test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map.test1"))
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
	// statement: 85
	// console.log("map value for test2 using map dot operator: ", getVariable("$map.test2"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[85];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test2 using map dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map.test2")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map.test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map.test2"))
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
	// statement: 86
	// console.log("map value for test3 using map dot operator: ", getVariable("$map.test3"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[86];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test3 using map dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map.test3")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map.test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map.test3"))
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
	// statement: 87
	// console.log("map value for test4 using map dot operator: ", getVariable("$map.test4"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[87];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test4 using map dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map.test4")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map.test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map.test4"))
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
	// statement: 88
	// console.log("map value for test5 using map dot operator: ", getVariable("$map.test5"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[88];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map value for test5 using map dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$map.test5")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$map.test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$map.test5"))
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
	// statement: 89
	// console.log("adding map values using map dot operator: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[89];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("adding map values using map dot operator: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 90
	// setVariable("$map.test6", 666)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[90];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map.test6")),
			ScriptVariable(static_cast<int64_t>(666ll))
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
	// statement: 91
	// setVariable("$map.test7", 770)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[91];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map.test7")),
			ScriptVariable(static_cast<int64_t>(770ll))
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
	// statement: 92
	// setVariable("$map.test8", 890)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[92];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$map.test8")),
			ScriptVariable(static_cast<int64_t>(890ll))
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
	// statement: 93
	// console.log("map keys: ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[93];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map keys: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("getKeys"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETKEYS;
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
	// statement: 94
	// console.log("map values: ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getValues"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[94];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("map values: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getValues")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getValues")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("getValues"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETVALUES;
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
	// statement: 95
	// console.log("iterating keys and values using $map->getKeys(): ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[95];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("iterating keys and values using $map->getKeys(): "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 96
	// setVariable("$mapKeys", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[96];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$mapKeys")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "getKeys")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$map")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
				ScriptVariable(string("getKeys"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$map")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETKEYS;
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
	// statement: 97
	// setVariable("$i", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[97];
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
	// statement: 98
	miniscript_statement_98:
	// forCondition(lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$mapKeys", getVariable("$mapKeys"), "length")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[98];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$mapKeys", getVariable("$mapKeys"), "length"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: lesser(getVariable("$i"), internal.script.evaluateMemberAccess("$mapKeys", getVariable("$mapKeys"), "length"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$i")
				ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$mapKeys", getVariable("$mapKeys"), "length")
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
			// depth = 2 / argument index = 1: internal.script.evaluateMemberAccess("$mapKeys", getVariable("$mapKeys"), "length")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 3> argumentValues {
					ScriptVariable(string("$mapKeys")),
					ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$mapKeys")
					ScriptVariable(string("length"))
				};
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: getVariable("$mapKeys")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues {
						ScriptVariable(string("$mapKeys"))
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
				goto miniscript_statement_102;
			} else {
				miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {
		getScriptState().statementIdx++;
		return;
	}
	// statement: 99
	miniscript_statement_99:
	// console.log(add(getVariable("$mapKeys[$i]"), add(" = ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]")))))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[99];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add(getVariable("$mapKeys[$i]"), add(" = ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]"))))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add(getVariable("$mapKeys[$i]"), add(" = ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(), // argumentValues[0] --> returnValue of getVariable("$mapKeys[$i]")
				ScriptVariable() // argumentValues[1] --> returnValue of add(" = ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]")))
			};
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// we will use on_nothing_array_access_statement_s_99_0_0_0_0() to determine array access index
			// depth = 2 / argument index = 0: getVariable("$mapKeys[$i]")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$mapKeys[" + on_nothing_array_access_statement_s_99_0_0_0_0(statement).getValueAsString() + "]"))
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
			// depth = 2 / argument index = 1: add(" = ", internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues {
					ScriptVariable(string(" = ")),
					ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]"))
				};
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// depth = 3 / argument index = 1: internal.script.evaluateMemberAccess("$map", getVariable("$map"), "get", "$mapKeys[$i]", getVariable("$mapKeys[$i]"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 5> argumentValues {
						ScriptVariable(string("$map")),
						ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$map")
						ScriptVariable(string("get")),
						ScriptVariable(string("$mapKeys[$i]")),
						ScriptVariable() // argumentValues[4] --> returnValue of getVariable("$mapKeys[$i]")
					};
					array<ScriptVariable, 5>& argumentValuesD3AIDX1 = argumentValues;
					// depth = 4 / argument index = 1: getVariable("$map")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$map"))
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
					// we will use on_nothing_array_access_statement_s_99_0_1_1_4_0_0() to determine array access index
					// depth = 4 / argument index = 4: getVariable("$mapKeys[$i]")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[4];
						array<ScriptVariable, 1> argumentValues {
							ScriptVariable(string("$mapKeys[" + on_nothing_array_access_statement_s_99_0_1_1_4_0_0(statement).getValueAsString() + "]"))
						};
						array<ScriptVariable, 1>& argumentValuesD4AIDX4 = argumentValues;
						// method code: getVariable
						string variable;
						if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
							returnValue = miniScript->getVariable(variable, &statement);
						} else {
							Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
							miniScript->startErrorScript(); return;
						}
					}
					const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GET;
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
	// statement: 100
	// prefixIncrement(getVariable("$i"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[100];
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
	// statement: 101
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[101];
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
				goto miniscript_statement_98;
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
	// statement: 102
	miniscript_statement_102:
	// console.log("---------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[102];
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
	// statement: 103
	// console.log("Sets")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[103];
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
	// statement: 104
	// console.log("----------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[104];
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
	// statement: 105
	// setVariable("$set", <COMPLEX DATATYPE>)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[105];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set")),
			on_nothing_initializer_s_105_1(statement)
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
	// statement: 106
	// console.log(add("set initialized with: $set = {test1, test2, test3, test4, test5}: ", getVariable("$set")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[106];
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
	// statement: 107
	// setVariable("$set", set())
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[107];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable() // argumentValues[1] --> returnValue of set()
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: set()
		{
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 0> argumentValues {
			};
			array<ScriptVariable, 0>& argumentValuesD1AIDX1 = argumentValues;
			// method code: set
			returnValue.setType(MiniScript::TYPE_SET);
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
	// statement: 108
	// console.log(add("set initialized with: $set = set(): ", getVariable("$set")))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[108];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable() // argumentValues[0] --> returnValue of add("set initialized with: $set = set(): ", getVariable("$set"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: add("set initialized with: $set = set(): ", getVariable("$set"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues {
				ScriptVariable(string("set initialized with: $set = set(): ")),
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
	// statement: 109
	// console.log("put some keys into set: $set->insert()")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[109];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("put some keys into set: $set->insert()"))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 110
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "insert", <VOID>, "test1")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[110];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("insert")),
			ScriptVariable(),
			ScriptVariable(string("test1"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INSERT;
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
	// statement: 111
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "insert", <VOID>, "test2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[111];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("insert")),
			ScriptVariable(),
			ScriptVariable(string("test2"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INSERT;
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
	// statement: 112
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "insert", <VOID>, "test3")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[112];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("insert")),
			ScriptVariable(),
			ScriptVariable(string("test3"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INSERT;
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
	// statement: 113
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "insert", <VOID>, "test4")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[113];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("insert")),
			ScriptVariable(),
			ScriptVariable(string("test4"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INSERT;
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
	// statement: 114
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "insert", <VOID>, "test5")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[114];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("insert")),
			ScriptVariable(),
			ScriptVariable(string("test5"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_INSERT;
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
	// statement: 115
	// console.log("set now looks like: ", getVariable("$set"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[115];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
	// statement: 116
	// console.log("remove test2 via $set->remove: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[116];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("remove test2 via $set->remove: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 117
	// internal.script.evaluateMemberAccess("$set", getVariable("$set"), "remove", <VOID>, "test2")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[117];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 5> argumentValues {
			ScriptVariable(string("$set")),
			ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
			ScriptVariable(string("remove")),
			ScriptVariable(),
			ScriptVariable(string("test2"))
		};
		array<ScriptVariable, 5>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
		const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_REMOVE;
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
	// statement: 118
	// console.log("set now looks like: ", getVariable("$set"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[118];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set now looks like: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set"))
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
	// statement: 119
	// console.log("set does have test1 key using $set->has(): ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test1"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[119];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set does have test1 key using $set->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test1")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test1"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 120
	// console.log("set does have test2 key using $set->has(): ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test2"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[120];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set does have test2 key using $set->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test2")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test2"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 121
	// console.log("set does have test3 key using $set->has(): ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test3"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[121];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set does have test3 key using $set->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test3")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test3"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 122
	// console.log("set does have test4 key using $set->has(): ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test4"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[122];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set does have test4 key using $set->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test4")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test4"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 123
	// console.log("set does have test5 key using $set->has(): ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test5"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[123];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set does have test5 key using $set->has(): ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test5")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "has", <VOID>, "test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 5> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("has")),
				ScriptVariable(),
				ScriptVariable(string("test5"))
			};
			array<ScriptVariable, 5>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_HAS;
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
	// statement: 124
	// console.log("set key for test1 using set dot operator: ", getVariable("$set.test1"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[124];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set key for test1 using set dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set.test1")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set.test1")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set.test1"))
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
	// statement: 125
	// console.log("set key for test2 using set dot operator: ", getVariable("$set.test2"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[125];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set key for test2 using set dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set.test2")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set.test2")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set.test2"))
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
	// statement: 126
	// console.log("set key for test3 using set dot operator: ", getVariable("$set.test3"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[126];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set key for test3 using set dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set.test3")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set.test3")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set.test3"))
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
	// statement: 127
	// console.log("set key for test4 using set dot operator: ", getVariable("$set.test4"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[127];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set key for test4 using set dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set.test4")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set.test4")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set.test4"))
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
	// statement: 128
	// console.log("set key for test5 using set dot operator: ", getVariable("$set.test5"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[128];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set key for test5 using set dot operator: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of getVariable("$set.test5")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: getVariable("$set.test5")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues {
				ScriptVariable(string("$set.test5"))
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
	// statement: 129
	// console.log("inserting set values using set dot operator: ")
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[129];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues {
			ScriptVariable(string("inserting set values using set dot operator: "))
		};
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (const auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueAsString());
		}
		Console::println();
	}
	// statement: 130
	// setVariable("$set.test6", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[130];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set.test6")),
			ScriptVariable(true)
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
	// statement: 131
	// setVariable("$set.test7", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[131];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set.test7")),
			ScriptVariable(true)
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
	// statement: 132
	// setVariable("$set.test8", 0)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[132];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set.test8")),
			ScriptVariable(false)
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
	// statement: 133
	// setVariable("$set.test9", 1)
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[133];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("$set.test9")),
			ScriptVariable(true)
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
	// statement: 134
	// console.log("set keys: ", internal.script.evaluateMemberAccess("$set", getVariable("$set"), "getKeys"))
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[134];
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(string("set keys: ")),
			ScriptVariable() // argumentValues[1] --> returnValue of internal.script.evaluateMemberAccess("$set", getVariable("$set"), "getKeys")
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 1: internal.script.evaluateMemberAccess("$set", getVariable("$set"), "getKeys")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$set")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$set")
				ScriptVariable(string("getKeys"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$set")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
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
			const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_GETKEYS;
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
	// statement: 135
	// script.stop()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[135];
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
	// statement: 136
	// end()
	{
		// statement setup
		const ScriptStatement& statement = scripts[3].statements[136];
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
		resetScriptExecutationState(4, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	// script setup
	auto miniScript = this;
	getScriptState().scriptIdx = 4;
	if (miniScriptGotoStatementIdx == 5) goto miniscript_statement_5; else
	if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println("MiniScriptTranspiler::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	// statement: 0
	// console.log("----------------------")
	{
		// statement setup
		const ScriptStatement& statement = scripts[4].statements[0];
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
		const ScriptStatement& statement = scripts[4].statements[1];
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
		const ScriptStatement& statement = scripts[4].statements[2];
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
		const ScriptStatement& statement = scripts[4].statements[3];
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
		const ScriptStatement& statement = scripts[4].statements[4];
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
		const ScriptStatement& statement = scripts[4].statements[5];
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

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_23_0_1(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	// sub(internal.script.evaluateMemberAccess("$array[11]", getVariable("$array[11]"), "length"), 1)
	{
		// statement setup
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of internal.script.evaluateMemberAccess("$array[11]", getVariable("$array[11]"), "length")
			ScriptVariable(static_cast<int64_t>(1ll))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: internal.script.evaluateMemberAccess("$array[11]", getVariable("$array[11]"), "length")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 3> argumentValues {
				ScriptVariable(string("$array[11]")),
				ScriptVariable(), // argumentValues[1] --> returnValue of getVariable("$array[11]")
				ScriptVariable(string("length"))
			};
			array<ScriptVariable, 3>& argumentValuesD1AIDX0 = argumentValues;
			// depth = 2 / argument index = 1: getVariable("$array[11]")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 1> argumentValues {
					ScriptVariable(string("$array[11]"))
				};
				array<ScriptVariable, 1>& argumentValuesD2AIDX1 = argumentValues;
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(string("getVariable") + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(string("getVariable")));
					miniScript->startErrorScript(); return ScriptVariable();
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
								miniScript->startErrorScript(); return ScriptVariable();
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
														miniScript->startErrorScript(); return ScriptVariable();
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
									miniScript->startErrorScript(); return ScriptVariable();
								}
							}
		}
		// method code: sub
		MiniScriptMath::sub(miniScript, argumentValues, returnValue, statement);
		return returnValue;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_34_0_1_1_0_0(const ScriptStatement& statement) {
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

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_40_0_1_1_0_0(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	// add(mul(getVariable("$i"), 2), 0)
	{
		// statement setup
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of mul(getVariable("$i"), 2)
			ScriptVariable(static_cast<int64_t>(0ll))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: mul(getVariable("$i"), 2)
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
					miniScript->startErrorScript(); return ScriptVariable();
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: add
		MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		return returnValue;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_41_0_1_1_0_0(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	// add(mul(getVariable("$i"), 2), 1)
	{
		// statement setup
		getScriptState().statementIdx = statement.statementIdx;
		// required method code arguments
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues {
			ScriptVariable(), // argumentValues[0] --> returnValue of mul(getVariable("$i"), 2)
			ScriptVariable(static_cast<int64_t>(1ll))
		};
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// depth = 1 / argument index = 0: mul(getVariable("$i"), 2)
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
					miniScript->startErrorScript(); return ScriptVariable();
				}
			}
			// method code: mul
			MiniScriptMath::mul(miniScript, argumentValues, returnValue, statement);
		}
		// method code: add
		MiniScriptMath::add(miniScript, argumentValues, returnValue, statement);
		return returnValue;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_99_0_0_0_0(const ScriptStatement& statement) {
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

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_array_access_statement_s_99_0_1_1_4_0_0(const ScriptStatement& statement) {
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


inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_7_1(const ScriptStatement& statement) {
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
		return variableD0;
	}
}

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_61_1(const ScriptStatement& statement) {
	// Miniscript setup
	auto miniScript = this;
	//
	{
		ScriptVariable variableD0;
		variableD0.setType(TYPE_MAP);
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

inline MiniScript::ScriptVariable MiniScriptAdvancedTest::on_nothing_initializer_s_105_1(const ScriptStatement& statement) {
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
