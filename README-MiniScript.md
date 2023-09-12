![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is the documentation of MiniScript language. This document is WIP.

# 1. Introduction

Introduction to MiniScript language features:
- very small implementation of a scripting language
- runs on every CPU, OS, ... due to its simplicity, so its highly portable just like TDME2 is
- can be easily extended by writing state machine machine states and script methods in C++
- works with the following data types: null, boolean, integer, float, string, vector2, vector3, vector4, quaternion, matrix3x3, matrix4x4, transform, array, map and set
- when calling script methods/returning from methods it does not use references or pointers but only value by copy
- supports user script functions and recursion
- supports kind of references by optionally assigning back argument values to variables
- supports operators by operator to method mapping by a preprocessor run
- supports loops and conditions
- supports event like programming
- can be transpiled to C++

# 2. Flow control

## 2.1. If, elseif, else and end

If, elseif, else and end are flow control methods. Please see the usage below.

See an example of if and end:
```
...
	$i = 1
	if ($i == 1)
		console.log("i -> 1")
	end
...
```

See an example of if and else and end:
```
...
	$i = 2
	if ($i == 1)
		console.log("i -> 1")
	else
		console.log("else: ", $i)
	end
...
```

See an example of if, elseif, else and end:

```
...
	$i = 2
	console.log($i, ":")
	if ($i == 0)
		console.log("i -> 0")
	elseif ($i == 1)
		console.log("i -> 1")
	elseif ($i == 2)
		console.log("i -> 2")
	elseif ($i == 3)
		console.log("i -> 3")
	else
		console.log("else: ", $i)
	end
...
```

## 2.2. forTime, forCondition

forTime and forCondition are loops and belong to flow control also:

forTime takes a single argument "time" - it repeats the loop until "time" in milliseconds has passed since the initialization of the loop. See an example of forTime() below: 
```
...
	$i = 0
	forTime(2000)
		console.log($i, ": Hello World")
		script.wait(500)
		++$i
	end
...
```

forCondition takes a single boolean value as argument. The loop will be executed as long as the argument is true. In this case "$i < 5" translates to "lesser($i, 5)" which results in a boolean value, which is used as the forCondition argument. See example of forCondition() below.
```
...
	$i = 0
	forCondition($i < 5)
		console.log("$ = ", $i)
		++$i
	end
...
```

# 3. Functions/Callables

See this example that shows user script functions and recursion.

It also shows $arguments array variable, which is created in function context and allows access to all arguments that the function was called with.
Argument variable names in function declaration are also populated in function context with corresponding values.
```
...
# user script function of recursive factorial computation
function: factorial($value)
	console.log("factorial(): $arguments = " + $arguments + " / $value = " + $value)
	if ($value == 0) 
		return(1)
	end
	return($value * factorial($value - 1))
end
...
	console.log("factorial(5) = " + factorial(5))
...
```

If a argument variable is prefixed with a = operator in function declaration, this variable will be assigned back after the function returns. See =$b and =$c.
```
...
# user script function to test assign back in user functions
function: assignTest($a, =$b, =$c)
	$a = "a"
	$b = "b"
	$c = "c"
end
...
	$a = "0"
	$b = "1"
	$c = "2"
	console.log("assignTest(): pre: $a = " + $a + ", $b = " + $b + ", $c = " + $c)
	assignTest($a, $b, $c)
	console.log("assignTest(): post: $a = " + $a + ", $b = " + $b + ", $c = " + $c)
...
``` 

Global variables can always be accessed by using the "$GLOBAL." accessor.
By default variables are read from current context and if they have not been found from root context.
So to be sure to use a global variable in function scope, just use the "$GLOBAL." accessor.
```
...
# user script function to test global variable access
function: globalVariableTest()
	console.log("globalVariableTest(): $GLOBAL.globalTest = " + $GLOBAL.globalTest)
	$GLOBAL.globalTest = "Been there, done that, got the t-shirt"
end
...
	$globalTest = "Global Test Variable"
	console.log("globalVariableTest(): pre: $globalTest = " + $globalTest)
	globalVariableTest()
	console.log("globalVariableTest(): post: $globalTest = " + $globalTest)
...
```

A special type of functions are callables. Callables are functions that are used to interact between MiniScript logics.
Despite the fact that a callable function of a logic can be called from another logic, 
they have the limitation that they must only contain MiniScript C++ method calls that dont require a context function.

Context functions are functions that are called from TDME2 to e.g. update audio, engine or physics, 
like e.g. initializeEngine(), updateEngine() or initializeLogic(), updateLogic(), ...

```
...
# call this callable to select this unit 
callable: select()
	$GLOBAL.selectMode = "select"
end
...
# call this callable to unselect this unit 
callable: unselect()
	$GLOBAL.selectMode = "unselect"
end
...
# update engine (context) function
function: updateEngine()
	...
	# selection
	if ($GLOBAL.selectMode == "select")
		engine.entity.setEnabled(logic.getId(), true, "selection")
		$GLOBAL.selectMode = "none"
	elseif ($GLOBAL.selectMode == "unselect")
		engine.entity.setEnabled(logic.getId(), false, "selection")
		$GLOBAL.selectMode = "none"
	end
	...
end
...
```

# 4. Data types and variables

MiniScript works with the following data types:
- boolean
- integer
- float
- string
- vector2
- vector3
- vector4
- quaternion
- matrix3x3
- matrix4x4
- transform
- array
- map
- set  

Variable identifiers always start with a "$". Constants need also be prefixed with a "$" and should be named with uppercase letters like "$PI = 3.14". (No real constant support yet, but it is planned)

## 4.1. Primitive data types

The following primitive data types are available: boolean, integer, float, string.

Variables of those types can be assigned implicitly, which means the parser know about the data type by given value:

```
...
	$boolean = true
	$boolean = false
...
```

```
...
	$integer = 123
...
```

```
...
	$float = 456.789
...
```

```
...
	$string = "This is my mighty string"
...
```

The primitive data types can also be assigned by using initialization methods that return explicitly those primitive data types:

```
...
	$boolean = bool(true)
	$boolean = bool(false)
...
```

```
...
	$integer = int(123)
...
```

```
...
	$float = float(456.789)
...
```

```
...
	$string = string("This is my mighty string")
...
```

## 4.2. Compound math data types

MiniScript works with the following math specific data types:
- vector2
- vector3
- vector4
- quaternion
- matrix3x3
- matrix4x4
- transform

Those variables can be created the following ways:

```
...
	$vector2 = vec2(-1.0, 1.0)
...
```

```
...
	$vector3 = vec3(-1.0, 1.0, -2.0)
...
```

```
...
	$vector4 = vec4(-1.0, 1.0, -2.0, 1.0)
...
```

```
...
	$quaternion = quaternion.identity()
...
```

```
...
	$matrix3 = mat3.identity()
...
```

```
...
	$matrix4 = mat4.identity()
...
```

```
...
	$translation = vec3(-1.0, 1.0, -2.0)
	$scale = vec3(2.0, 2.0, 2.0)
	$rotationZ = 0.0
	$rotationY = 90.0
	$rotationX = 0.0
	$transform = transform($translation, $scale, $rotationZ, $rotationY, $rotationX)
	# or
	$transform = transform(vec3(-1.0, 1.0, -2.0), vec3(2.0, 2.0, 2.0), 0.0, 90.0, 0.0)
...
```

For more math related methods just look into "6. Methods" section. 

## 4.3. Arrays

An array is a collection/sequence of values which can be accessed by indices.

Initializing an array:

```
...
	$array = array()
...
```

... or initialize and push values to it:
```
...
	$array = array(1, 2, 3)
...
```

Pushing values using array.push():
```
...
	$array->push(5, 6, 7)
...
```

Pushing values using [] operator:
```
...
	$array[] = 8
	$array[] = 9
	$array[] = 10
...
```

Iterating arrays using array.length() and array.get():
```
...
	$i = 0
	forCondition($i < $array->length())
		console.log($i + ": " + $array->get($i))
		++$i
	end
...
```

Iterating arrays using array.length() and [] operator:
```
...
	$i = 0
	forCondition($i < $array->length())
		console.log($i + ": " + $array[$i])
		++$i
	end
...
```

Removing values from arrays using array.removeOf():
```
...
	$array->removeOf(6)
	$array->removeOf(7)
...
```

Removing from arrays using a index with array.remove():
```
...
	$array->remove(2)
...
```


## 4.4. Maps

A map is key, value pair storage using a underlying hash map. Keys can only exist once in a map.

Initializing maps using map() method:
```
...
	$map = map()
...
```

Setting map key, value pairs using map.set():
```
...
	$map->set("test1", 123)
	$map->set("test2", 456)
	$map->set("test3", array(1, 2, 3))
	$map->set("test4", "Yaaaa")
...
```

Removing from map using map.remove() and a given key:
```
...
	$map->remove("test2")
...
```

Reading values from map using map.get() and given keys:
```
...
	console.log("map value for test1 key using map.get(): ", $map->get("test1"))
	console.log("map value for test2 key using map.get(): ", $map->get("test2"))
	console.log("map value for test3 key using map.get(): ", $map->get("test3"))
	console.log("map value for test4 key using map.get(): ", $map->get("test4"))
...
```

Reading values from map using dot operator:
```
...
	console.log("map value for test1 using map dot operator: ", $map.test1)
	console.log("map value for test2 using map dot operator: ", $map.test2)
	console.log("map value for test3 using map dot operator: ", $map.test3)
	console.log("map value for test4 using map dot operator: ", $map.test4)
...
```

Setting key, value pairs to map using dot operator:
```
...
	$map.test6 = 666
	$map.test7 = 770
...
```

Reading map keys:
```
...
	console.log("map keys: ", $map->getKeys())
...
```

Reading map values:
```
...
	console.log("map values: ", $map->getValues())
...
```

Reading all keys and values from map using map.get() and map.getKeys()
```
...
	$mapKeys = $map->getKeys()
	$i = 0
	forCondition($i < $mapKeys->length())
		console.log($mapKeys[$i] + " = " + $map->get($mapKeys[$i]))
		++$i
	end
...
```

## 4.5. Sets

A set is key storage using a underlying hash set. Keys can only exist once in a set.

Initializing sets using set() method:
```
...
	$set = set()
...
```

Inserting keys into set using set.insert():
```
...
	$set->insert("test1")
	$set->insert("test2")
	$set->insert("test3")
...
```

Removing keys from set using set.remove():
```
...
	$set->remove("test2")
...
```

Checking if keys exist in map using map.has() and given keys:
```
...
	console.log("set does have test1 key using set.has(): ", $set->has("test1"))
	console.log("set does have test2 key using set.has(): ", $set->has("test2"))
	console.log("set does have test3 key using set.has(): ", $set->has("test3"))
	console.log("set does have test4 key using set.has(): ", $set->has("test4"))
	console.log("set does have test5 key using set.has(): ", $set->has("test5"))
...
```


Checking if keys exist in map using dot opertator and given keys:
```
...
	console.log("set key for test1 using set dot operator: ", $set.test1)
	console.log("set key for test2 using set dot operator: ", $set.test2)
	console.log("set key for test3 using set dot operator: ", $set.test3)
	console.log("set key for test4 using set dot operator: ", $set.test4)
	console.log("set key for test5 using set dot operator: ", $set.test5)
...
```

Inserting/Removing set keys by using dot operator and boolean assignment:
```
...
	$set.test6 = true
	$set.test7 = true
	$set.test8 = false
	$set.test9 = true
...
```

Reading all keys as array from set:
```
...
	console.log("set keys: ", $set->getKeys())
...
```

# 5. Program structure and flow

... TODO ...

# 6. MiniScript classes

## 6.1 String class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create string                                                                                    |
| <sub><b>STATIC</b> string($string: String): String</sub>                                         |
| Test if string value is empty                                                                    |
| <sub>isEmpty(): Boolean</sub>                                                                    |
| Test if string value is a float number                                                           |
| <sub>isFloat(): Boolean</sub>                                                                    |
| Test if string value is a integer number                                                         |
| <sub>isInteger(): Boolean</sub>                                                                  |
| Return character of string at given position                                                     |
| <sub>charAt($index: Integer): String</sub>                                                       |
| Concatenate strings                                                                              |
| <sub><b>STATIC</b> string.concatenate(...): String</sub>                                         |
| Test if string ends with specific string                                                         |
| <sub>endsWith($suffix: String): Boolean</sub>                                                    |
| Test if strings matches ignoring case sensitivity                                                |
| <sub><b>STATIC</b> string.equalsIgnoreCase($string1: String, $string2: String): Boolean</sub>    |
| Return first index of specific string in string                                                  |
| <sub>firstIndexOf($what: String[, $beginIndex: Integer]): Integer</sub>                          |
| Return index of specific string in string                                                        |
| <sub>indexOf($what: String[, $beginIndex: Integer]): Integer</sub>                               |
| Return last index of specific string in string                                                   |
| <sub>lastIndexOf($what: String[, $beginIndex: Integer]): Integer</sub>                           |
| Return string length                                                                             |
| <sub>length(): Integer</sub>                                                                     |
| Pad string left                                                                                  |
| <sub><b>STATIC</b> string.padLeft($src: String, $by: String, $toSize: Integer): String</sub>     |
| Pad string right                                                                                 |
| <sub><b>STATIC</b> string.padRight($src: String, $by: String, $toSize: Integer): String</sub>    |
| RegEx match                                                                                      |
| <sub>regexMatch($pattern: String): Boolean</sub>                                                 |
| RegEx replace                                                                                    |
| <sub>regexReplace($pattern: String, $by: String): String</sub>                                   |
| Replace specific string in string with given string                                              |
| <sub>replace($what: String, $by: String[, $beginIndex: Integer]): String</sub>                   |
| Create spaces as string                                                                          |
| <sub><b>STATIC</b> string.space([, $spaces: Integer]): String</sub>                              |
| Test if given string starts with specific string                                                 |
| <sub>startsWith($prefix: String): Boolean</sub>                                                  |
| Return substring of string                                                                       |
| <sub>substring($beginIndex: Integer[, $endIndex: Integer]): String</sub>                         |
| Compute lower case string of string                                                              |
| <sub>toLowerCase(): String</sub>                                                                 |
| Compute upper case string of string                                                              |
| <sub>toUpperCase(): String</sub>                                                                 |
| Tokenize string                                                                                  |
| <sub>tokenize($delimiters: String): Array</sub>                                                  |
| Trim string                                                                                      |
| <sub>trim(): String</sub>                                                                        |

## 6.2 Vector2 class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create vector2                                                                                   |
| <sub><b>STATIC</b> vec2($x: Float, $y: Float): Vector2</sub>                                     |
| Compute vector2 dot product                                                                      |
| <sub><b>STATIC</b> vec2.computeDotProduct($a: Vector2, $b: Vector2): Float</sub>                 |
| Compute vector2 length                                                                           |
| <sub>computeLength(): Float</sub>                                                                |
| Compute vector2 squared length                                                                   |
| <sub>computeLengthSquared(): Float</sub>                                                         |
| Return vector2 x component                                                                       |
| <sub>getX(): Float</sub>                                                                         |
| Return vector2 y component                                                                       |
| <sub>getY(): Float</sub>                                                                         |
| Normalize vector2                                                                                |
| <sub>normalize(): Vector2</sub>                                                                  |

## 6.3 Vector3 class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create vector3                                                                                   |
| <sub><b>STATIC</b> vec3($x: Float, $y: Float, $z: Float): Vector3</sub>                          |
| Compute angle between two vector3                                                                |
| <sub><b>STATIC</b> vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float</sub>         |
| Compute vector3 cross product                                                                    |
| <sub><b>STATIC</b> vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3</sub>             |
| Compute vector3 dot product                                                                      |
| <sub><b>STATIC</b> vec3.computeDotProduct($a: Vector3, $b: Vector3): Float</sub>                 |
| Compute vector3 length                                                                           |
| <sub>computeLength(): Float</sub>                                                                |
| Compute vector3 squared length                                                                   |
| <sub>computeLengthSquared(): Float</sub>                                                         |
| Return vector3 x component                                                                       |
| <sub>getX(): Float</sub>                                                                         |
| Return vector3 y component                                                                       |
| <sub>getY(): Float</sub>                                                                         |
| Return vector3 z component                                                                       |
| <sub>getZ(): Float</sub>                                                                         |
| Normalize vector3                                                                                |
| <sub>normalize(): Vector3</sub>                                                                  |

## 6.4 Vector4 class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create vector4                                                                                   |
| <sub><b>STATIC</b> vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4</sub>               |
| Compute vector4 dot product                                                                      |
| <sub><b>STATIC</b> vec4.computeDotProduct($a: Vector4, $b: Vector4): Float</sub>                 |
| Compute vector4 length                                                                           |
| <sub>computeLength(): Float</sub>                                                                |
| Compute vector4 squared length                                                                   |
| <sub>computeLengthSquared(): Float</sub>                                                         |
| Return vector4 w component                                                                       |
| <sub>getW(): Float</sub>                                                                         |
| Return vector4 x component                                                                       |
| <sub>getX(): Float</sub>                                                                         |
| Return vector4 y component                                                                       |
| <sub>getY(): Float</sub>                                                                         |
| Return vector4 z component                                                                       |
| <sub>getZ(): Float</sub>                                                                         |
| Normalize vector4                                                                                |
| <sub>normalize(): Vector4</sub>                                                                  |

## 6.5 Quaternion class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute euler angles from quaternion                                                             |
| <sub>computeEulerAngles(): Vector3</sub>                                                         |
| Compute 4x4 rotation matrix from quaternion                                                      |
| <sub>computeMatrix(): Matrix4x4</sub>                                                            |
| Create identity quaternion                                                                       |
| <sub><b>STATIC</b> quaternion.identity(): Quaternion</sub>                                       |
| Create quaternion inverse                                                                        |
| <sub>invert(): Quaternion</sub>                                                                  |
| Multiply quaternion with quaternion or vector3                                                   |
| <sub>multiply(, ...): Mixed</sub>                                                                |
| Normalize quaternion                                                                             |
| <sub>normalize(): Quaternion</sub>                                                               |
| Create rotation quaternion                                                                       |
| <sub><b>STATIC</b> quaternion.rotate($axis: Vector3, $angle: Float): Quaternion</sub>            |

## 6.6 Matrix3x3 class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create identity 3x3 matrix                                                                       |
| <sub><b>STATIC</b> mat3.identity(): Matrix3x3</sub>                                              |
| Multiply 3x3 matrix with 3x3 matrix or vector2                                                   |
| <sub>multiply(, ...): Mixed</sub>                                                                |
| Create rotation 3x3 matrix                                                                       |
| <sub><b>STATIC</b> mat3.rotate($angle: Float): Matrix3x3</sub>                                   |
| Create 3x3 matrix which rotates around point                                                     |
| <sub><b>STATIC</b> mat3.rotateAroundPoint($point: Vector2, $angle: Float): Matrix3x3</sub>       |
| Create 3x3 matrix which rotates around texture center                                            |
| <sub><b>STATIC</b> mat3.rotateAroundTextureCenter($angle: Float): Matrix3x3</sub>                |
| Create scale 3x3 matrix                                                                          |
| <sub><b>STATIC</b> mat3.scale(...): Matrix3x3</sub>                                              |
| Create translation 3x3 matrix                                                                    |
| <sub><b>STATIC</b> mat3.translate($translation: Vector2): Matrix3x3</sub>                        |

## 6.7 Matrix4x4 class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute euler angles from 4x4 matrix                                                             |
| <sub>computeEulerAngles(): Vector3</sub>                                                         |
| Create identity 4x4 matrix                                                                       |
| <sub><b>STATIC</b> mat4.identity(): Matrix4x4</sub>                                              |
| Create 4x4 matrix inverse                                                                        |
| <sub>invert(): Matrix4x4</sub>                                                                   |
| Multiply 4x4 matrix with 4x4 matrix or vector3 or vector4                                        |
| <sub>multiply(, ...): Mixed</sub>                                                                |
| Create rotation 4x4 matrix                                                                       |
| <sub><b>STATIC</b> mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4</sub>                   |
| Create scale 4x4 matrix                                                                          |
| <sub><b>STATIC</b> mat4.scale(...): Matrix4x4</sub>                                              |
| Create translation 4x4 matrix                                                                    |
| <sub><b>STATIC</b> mat4.translate($translation: Vector3): Matrix4x4</sub>                        |

## 6.8 Transform class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create transform                                                                                 |
| <sub><b>STATIC</b> transform([, $translation: Vector3[, $scale: Vector3[, $rotationZ: Float[, $rotationY: Float[, $rotationX: Float]]]]]): Transform</sub>|
| X axis as vector3                                                                                |
| <sub><b>STATIC</b> transform.AXIS_X(): Vector3</sub>                                             |
| Y axis as vector3                                                                                |
| <sub><b>STATIC</b> transform.AXIS_Y(): Vector3</sub>                                             |
| Z axis as vector3                                                                                |
| <sub><b>STATIC</b> transform.AXIS_Z(): Vector3</sub>                                             |
| Get rotation angle of specific rotation of transform                                             |
| <sub>getRotationAngle($idx: Integer): Float</sub>                                                |
| Set rotation angle of specific rotation of transform                                             |
| <sub>setRotationAngle($idx: Integer, $angle: Float): Void</sub>                                  |
| Set rotation axis of specific rotation of transform                                              |
| <sub>getRotationAxis($idx: Integer): Vector3</sub>                                               |
| Compute transform rotations quaternion                                                           |
| <sub>getRotationsQuaternion(): Quaternion</sub>                                                  |
| Get transfrom scale                                                                              |
| <sub>getScale(): Vector3</sub>                                                                   |
| Set transfrom scale                                                                              |
| <sub>setScale($scale: Vector3): Void</sub>                                                       |
| Get 4x4 transform matrix                                                                         |
| <sub>getTransformMatrix(): Matrix4x4</sub>                                                       |
| Get transform translation                                                                        |
| <sub>getTranslation(): Vector3</sub>                                                             |
| Set transform translation                                                                        |
| <sub>setTranslation($translation: Vector3): Void</sub>                                           |
| Apply a rotation to transform                                                                    |
| <sub>applyRotation($axis: Vector3, $angle: Float): Void</sub>                                    |
| Create transform from 4x4 matrix                                                                 |
| <sub><b>STATIC</b> transform.fromMatrix($transformMatrix: Matrix4x4): Transform</sub>            |
| Interpolate rotation                                                                             |
| <sub><b>STATIC</b> transform.interpolateRotation($currentAngle: Float, $targetAngle: Float, $timePassedSeconds: Float, $degreesPerSeconds: Float, =$interpolatedAngle: Float): Boolean</sub>|
| Multiply transform with vector3                                                                  |
| <sub>multiply($vec3: Vector3): Vector3</sub>                                                     |
| Rotate vector3 using transform                                                                   |
| <sub>rotate($vec3: Vector3): Vector3</sub>                                                       |

## 6.9 Array class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create array                                                                                     |
| <sub><b>STATIC</b> array(...): Array</sub>                                                       |
| Get array entry                                                                                  |
| <sub>get($index: Integer): Mixed</sub>                                                           |
| Set array entry                                                                                  |
| <sub>set($index: Integer, $value: Mixed): Void</sub>                                             |
| Get array index by value                                                                         |
| <sub>indexOf($value: String[, $beginIndex: Integer]): Integer</sub>                              |
| Get array length                                                                                 |
| <sub>length(): Integer</sub>                                                                     |
| Add entry to array                                                                               |
| <sub>push(, ...): Void</sub>                                                                     |
| Remove array entry by index                                                                      |
| <sub>remove($index: Integer): Void</sub>                                                         |
| Remove array entry by value                                                                      |
| <sub>removeOf($value: String[, $beginIndex: Integer]): Void</sub>                                |
| Reverse array                                                                                    |
| <sub>reverse(): Void</sub>                                                                       |
| Sort array                                                                                       |
| <sub>sort($function: String): Void</sub>                                                         |

## 6.10 Map class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create map                                                                                       |
| <sub><b>STATIC</b> map(): Map</sub>                                                              |
| Has entry by key                                                                                 |
| <sub>has($key: String): Boolean</sub>                                                            |
| Get map value by key                                                                             |
| <sub>get($key: String): Mixed</sub>                                                              |
| Set map entry                                                                                    |
| <sub>set($key: String, $value: Mixed): Void</sub>                                                |
| Get map keys                                                                                     |
| <sub>getKeys(): Array</sub>                                                                      |
| Get map values                                                                                   |
| <sub>getValues(): Array</sub>                                                                    |
| Remove map entry                                                                                 |
| <sub>remove($key: String): Void</sub>                                                            |

## 6.11 Set class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create set                                                                                       |
| <sub><b>STATIC</b> set(): Set</sub>                                                              |
| Has key in set                                                                                   |
| <sub>has($key: String): Boolean</sub>                                                            |
| Get set keys                                                                                     |
| <sub>getKeys(): Array</sub>                                                                      |
| Insert key into set                                                                              |
| <sub>insert($key: String): Void</sub>                                                            |
| Remove key from set                                                                              |
| <sub>remove($key: String): Void</sub>                                                            |

# 7. MiniScript base methods

## 7.1 Base methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get variable                                                                                     |
| <sub>getVariable($variable: String): Mixed</sub>                                                 |
| Set variable                                                                                     |
| <sub>setVariable($variable: String, $value: Mixed): Mixed</sub>                                  |
| Unset variable                                                                                   |
| <sub>unsetVariable($variable: String): Void</sub>                                                |
| Add                                                                                              |
| <sub>add($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Logical and                                                                                      |
| <sub>and($a: Boolean, $b: Boolean): Boolean</sub>                                                |
| Bitwise and                                                                                      |
| <sub>bitwiseAnd($a: Integer, $b: Integer): Integer</sub>                                         |
| Bitwise not                                                                                      |
| <sub>bitwiseNot($value: Integer): Integer</sub>                                                  |
| Bitwise or                                                                                       |
| <sub>bitwiseOr($a: Integer, $b: Integer): Integer</sub>                                          |
| Bitwise xor                                                                                      |
| <sub>bitwiseXor($a: Integer, $b: Integer): Integer</sub>                                         |
| Create bool                                                                                      |
| <sub>bool($bool: Boolean): Boolean</sub>                                                         |
| Divide                                                                                           |
| <sub>div($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Else                                                                                             |
| <sub>else(): Void</sub>                                                                          |
| Else if                                                                                          |
| <sub>elseif($condition: Boolean): Void</sub>                                                     |
| End                                                                                              |
| <sub>end(): Void</sub>                                                                           |
| Equals                                                                                           |
| <sub>equals($a: Mixed, $b: Mixed): Boolean</sub>                                                 |
| Create float                                                                                     |
| <sub>float($float: Float): Float</sub>                                                           |
| For condition                                                                                    |
| <sub>forCondition($condition: Boolean): Void</sub>                                               |
| For time                                                                                         |
| <sub>forTime($time: Integer): Void</sub>                                                         |
| Greater                                                                                          |
| <sub>greater($a: Mixed, $b: Mixed): Boolean</sub>                                                |
| Greater equals                                                                                   |
| <sub>greaterEquals($a: Mixed, $b: Mixed): Boolean</sub>                                          |
| If                                                                                               |
| <sub>if($condition: Boolean): Void</sub>                                                         |
| Create integer                                                                                   |
| <sub>int($int: Integer): Integer</sub>                                                           |
| Lesser                                                                                           |
| <sub>lesser($a: Mixed, $b: Mixed): Boolean</sub>                                                 |
| Lesser equals                                                                                    |
| <sub>lesserEquals($a: Mixed, $b: Mixed): Boolean</sub>                                           |
| Compute modulo                                                                                   |
| <sub>mod($value: Number, $range: Number): Number</sub>                                           |
| Multiply                                                                                         |
| <sub>mul($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Logical not                                                                                      |
| <sub>not($bool: Boolean): Boolean</sub>                                                          |
| Logical not equal                                                                                |
| <sub>notEqual($a: Mixed, $b: Mixed): Boolean</sub>                                               |
| Logical or                                                                                       |
| <sub>or($a: Boolean, $b: Boolean): Boolean</sub>                                                 |
| Prefix decrement                                                                                 |
| <sub>prefixDecrement(=$variable: Integer): Integer</sub>                                         |
| Prefix increment                                                                                 |
| <sub>prefixIncrement(=$variable: Integer): Integer</sub>                                         |
| Return from function with optional return value                                                  |
| <sub>return([, $value: Mixed]): Void</sub>                                                       |
| Subtract                                                                                         |
| <sub>sub($a: Mixed, $b: Mixed): Mixed</sub>                                                      |

# 8. MiniScript logic methods

The boilerplate template code for a MiniScript logic looks like: [logic_script_template.tscript](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/engine/templates/tscript/logic_script_template.tscript)

## 8.1 Application methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if application runs in full screen                                                       |
| <sub>application.isFullScreen(): Boolean</sub>                                                   |
| Returns if application runs inside TDME editor                                                   |
| <sub>application.runsInEditor(): Boolean</sub>                                                   |

## 8.2 Audio methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get listener orientation at - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>audio.getListenerOrientationAt(): Vector3</sub>                                             |
| Set listener orientation at - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>audio.setListenerOrientationAt($orientation: Vector3): Void</sub>                           |
| Get listener orientation up - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>audio.getListenerOrientationUp(): Vector3</sub>                                             |
| Set listener orientation up - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>audio.setListenerOrientationUp($orientation: Vector3): Void</sub>                           |
| Get listener position - <i>available in initializeEngine(), updateEngine()</i>                   |
| <sub>audio.getListenerPosition(): Vector3</sub>                                                  |
| Set listener position - <i>available in initializeEngine(), updateEngine()</i>                   |
| <sub>audio.setListenerPosition($position: Vector3): Void</sub>                                   |
| Play audio at engine entity position - <i>available in initializeEngine(), updateEngine()</i>    |
| <sub>audio.play($id: String[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): Void</sub>|
| Play audio at custom position - <i>available in initializeEngine(), updateEngine()</i>           |
| <sub>audio.playAtPosition($id: String, $position: Vector3[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): Void</sub>|

## 8.3 Engine methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get animation computation reduction 1 distance - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.getAnimationComputationReduction1Distance(): Float</sub>                             |
| Set animation computation reduction 1 distance - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.setAnimationComputationReduction1Distance($animationComputationReduction1Distance: Float): Void</sub>|
| Get animation computation reduction 2 distance - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.getAnimationComputationReduction2Distance(): Float</sub>                             |
| Set animation computation reduction 2 distance - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.setAnimationComputationReduction2Distance($animationComputationReduction2Distance: Float): Void</sub>|
| Get engine entity id by mouse position - <i>available in initializeEngine(), updateEngine()</i>  |
| <sub>engine.getEntityIdByMousePosition($mouseX: Integer, $mouseY: Integer): String</sub>         |
| Get engine height - <i>available in initializeEngine(), updateEngine()</i>                       |
| <sub>engine.getHeight(): Integer</sub>                                                           |
| Compute engine screen coordinate by world coordinate - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.computeScreenCoordinateByWorldCoordinate($worldCoodinate: Vector3, =$screenCoordinate: Vector2): Boolean</sub>|
| Get engine width - <i>available in initializeEngine(), updateEngine()</i>                        |
| <sub>engine.getWidth(): Integer</sub>                                                            |
| Compute engine world coordinate by mouse position - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.computeWorldCoordinateByMousePosition($mouseX: Integer, $mouseY: Integer): Vector3</sub>|
| Dump engine entities - <i>available in initializeEngine(), updateEngine()</i>                    |
| <sub>engine.dumpEntities(): Void</sub>                                                           |
| Dump engine shaders - <i>available in initializeEngine(), updateEngine()</i>                     |
| <sub>engine.dumpShaders(): Void</sub>                                                            |

## 8.4 Engine camera methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get camera horizontal field of view - <i>available in initializeEngine(), updateEngine()</i>     |
| <sub>engine.camera.getFovX(): Float</sub>                                                        |
| Set camera horizontal field of view - <i>available in initializeEngine(), updateEngine()</i>     |
| <sub>engine.camera.setFovX($fovX: Float): Void</sub>                                             |
| Get camera look at - <i>available in initializeEngine(), updateEngine()</i>                      |
| <sub>engine.camera.getLookAt(): Vector3</sub>                                                    |
| Set camera look at - <i>available in initializeEngine(), updateEngine()</i>                      |
| <sub>engine.camera.setLookAt($lookAt: Vector3): Void</sub>                                       |
| Get camera look from - <i>available in initializeEngine(), updateEngine()</i>                    |
| <sub>engine.camera.getLookFrom(): Vector3</sub>                                                  |
| Set camera look from - <i>available in initializeEngine(), updateEngine()</i>                    |
| <sub>engine.camera.setLookFrom($lookFrom: Vector3): Void</sub>                                   |
| Get camera up vector - <i>available in initializeEngine(), updateEngine()</i>                    |
| <sub>engine.camera.getUpVector(): Vector3</sub>                                                  |
| Set camera up vector - <i>available in initializeEngine(), updateEngine()</i>                    |
| <sub>engine.camera.setUpVector($upVector: Vector3): Void</sub>                                   |
| Compute camera up vector - <i>available in initializeEngine(), updateEngine()</i>                |
| <sub>engine.camera.computeUpVector($lookFrom: Vector3, $lookAt: Vector3): Vector3</sub>          |

## 8.5 Engine entity methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get engine entity animation - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>engine.entity.getAnimation($entityId: String[, $childEntityId: String]): String</sub>       |
| Set engine entity animation - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>engine.entity.setAnimation($entityId: String, $animation: String[, $speed: Float[, $childEntityId: String]]): Void</sub>|
| Get engine entity animation speed - <i>available in initializeEngine(), updateEngine()</i>       |
| <sub>engine.entity.setAnimationSpeed($entityId: String, $speed: Float[, $childEntityId: String]): Void</sub>|
| Set engine entity animation speed - <i>available in initializeEngine(), updateEngine()</i>       |
| <sub>engine.entity.getAnimationTime($entityId: String[, $childEntityId: String]): Float</sub>    |
| Get engine entity additive effect color - <i>available in initializeEngine(), updateEngine()</i> |
| <sub>engine.entity.getEffectColorAdd($entityId: String[, $childEntityId: String]): Vector4</sub> |
| Set engine entity additive effect color - <i>available in initializeEngine(), updateEngine()</i> |
| <sub>engine.entity.setEffectColorAdd($entityId: String, $effectColorAdd: Vector4[, $childEntityId: String]): Void</sub>|
| Get engine entity multiplicative effect color - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.entity.getEffectColorMul($entityId: String[, $childEntityId: String]): Vector4</sub> |
| Set engine entity multiplicative effect color - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.entity.setEffectColorMul($entityId: String, $effectColorMul: Vector4[, $childEntityId: String]): Void</sub>|
| Return if engine entity is enabled - <i>available in initializeEngine(), updateEngine()</i>      |
| <sub>engine.entity.isEnabled($entityId: String[, $childEntityId: String]): Boolean</sub>         |
| Set engine entity enabled/disabled - <i>available in initializeEngine(), updateEngine()</i>      |
| <sub>engine.entity.setEnabled($entityId: String, $enabled: Boolean[, $childEntityId: String]): Void</sub>|
| Get engine entity node transform - <i>available in initializeEngine(), updateEngine()</i>        |
| <sub>engine.entity.getNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Transform</sub>|
| Set engine entity node transform - <i>available in initializeEngine(), updateEngine()</i>        |
| <sub>engine.entity.setNodeTransform($entityId: String, $nodeId: String, $transform: Transform[, $childEntityId: String]): Void</sub>|
| Unset engine entity node transform - <i>available in initializeEngine(), updateEngine()</i>      |
| <sub>engine.entity.unsetNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Void</sub>|
| Get engine entity node transform matrix - <i>available in initializeEngine(), updateEngine()</i> |
| <sub>engine.entity.getNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Matrix4x4</sub>|
| Set engine entity node transform matrix - <i>available in initializeEngine(), updateEngine()</i> |
| <sub>engine.entity.setNodeTransformMatrix($entityId: String, $nodeId: String, $matrix: Matrix4x4[, $childEntityId: String]): Void</sub>|
| Unset engine entity node transform matrix - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.entity.unsetNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Void</sub>|
| Return if engine entity has specific overlay animation - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.entity.hasOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Boolean</sub>|
| Return engine entity overlay animation playback time from 0.0 until 1.0 - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.entity.getOverlayAnimationTime($entityId: String, $animation: String[, $childEntityId: String]): Float</sub>|
| Return if engine entity is pickable - <i>available in initializeEngine(), updateEngine()</i>     |
| <sub>engine.entity.isPickable($entityId: String[, $childEntityId: String]): Boolean</sub>        |
| Set engine entity pickable - <i>available in initializeEngine(), updateEngine()</i>              |
| <sub>engine.entity.setPickable($entityId: String, $pickable: Boolean[, $childEntityId: String]): Void</sub>|
| Get engine entity transform - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>engine.entity.getTransform($entityId: String[, $childEntityId: String]): Transform</sub>    |
| Set engine entity transform - <i>available in initializeEngine(), updateEngine()</i>             |
| <sub>engine.entity.setTransform($entityId: String, $transform: Transform[, $childEntityId: String]): Void</sub>|
| Add engine entity overlay animation - <i>available in initializeEngine(), updateEngine()</i>     |
| <sub>engine.entity.addOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</sub>|
| Emit engine entity particles - <i>available in initializeEngine(), updateEngine()</i>            |
| <sub>engine.entity.emitParticles($entityId: String[, $childEntityId: String]): Integer</sub>     |
| Remove finished overlay animations - <i>available in initializeEngine(), updateEngine()</i>      |
| <sub>engine.entity.removeFinishedOverlayAnimations($entityId: String[, $childEntityId: String]): Void</sub>|
| Remove specific overlay animation - <i>available in initializeEngine(), updateEngine()</i>       |
| <sub>engine.entity.removeOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</sub>|
| Remove overlay animations - <i>available in initializeEngine(), updateEngine()</i>               |
| <sub>engine.entity.removeOverlayAnimations($entityId: String[, $childEntityId: String]): Void</sub>|

## 8.6 Engine timing methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get engine timing avarage FPS - <i>available in initializeEngine(), updateEngine()</i>           |
| <sub>engine.timing.getAvarageFPS(): Float</sub>                                                  |
| Get engine timing frame delta time in milliseconds - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.timing.getDeltaTime(): Integer</sub>                                                 |
| Get engine timing frame delta time in seconds - <i>available in initializeEngine(), updateEngine()</i>|
| <sub>engine.timing.getDeltaTimeSeconds(): Float</sub>                                            |

## 8.7 Keyboard input methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT key is currently pressed                                                          |
| <sub>input.keyboard.isAltDown(): Boolean</sub>                                                   |
| Returns if specific character is currently pressed                                               |
| <sub>input.keyboard.isCharDown($charAsString: String): Boolean</sub>                             |
| Returns if CONTROL key is currently pressed                                                      |
| <sub>input.keyboard.isControlDown(): Boolean</sub>                                               |
| Backspace key keycode                                                                            |
| <sub>input.keyboard.KEYCODE_BACKSPACE(): Integer</sub>                                           |
| Delete key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_DELETE(): Integer</sub>                                              |
| Down key keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_DOWN(): Integer</sub>                                                |
| End key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_END(): Integer</sub>                                                 |
| Escape key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_ESCAPE(): Integer</sub>                                              |
| F1 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F1(): Integer</sub>                                                  |
| F10 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F10(): Integer</sub>                                                 |
| F11 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F11(): Integer</sub>                                                 |
| F12 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F12(): Integer</sub>                                                 |
| F2 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F2(): Integer</sub>                                                  |
| F3 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F3(): Integer</sub>                                                  |
| F4 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F4(): Integer</sub>                                                  |
| F5 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F5(): Integer</sub>                                                  |
| F6 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F6(): Integer</sub>                                                  |
| F7 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F7(): Integer</sub>                                                  |
| F8 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F8(): Integer</sub>                                                  |
| F9 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F9(): Integer</sub>                                                  |
| Left key keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_LEFT(): Integer</sub>                                                |
| Page down key keycode                                                                            |
| <sub>input.keyboard.KEYCODE_PAGEDOWN(): Integer</sub>                                            |
| Page up key keycode                                                                              |
| <sub>input.keyboard.KEYCODE_PAGEUP(): Integer</sub>                                              |
| Home/position key keycode                                                                        |
| <sub>input.keyboard.KEYCODE_POS1(): Integer</sub>                                                |
| Return key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_RETURN(): Integer</sub>                                              |
| Right key keycode                                                                                |
| <sub>input.keyboard.KEYCODE_RIGHT(): Integer</sub>                                               |
| Space key keycode                                                                                |
| <sub>input.keyboard.KEYCODE_SPACE(): Integer</sub>                                               |
| Up key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_UP(): Integer</sub>                                                  |
| Returns if specific key is currently pressed                                                     |
| <sub>input.keyboard.isKeyDown($keyCode: Integer): Boolean</sub>                                  |
| Returns if meta key is currently pressed                                                         |
| <sub>input.keyboard.isMetaDown(): Boolean</sub>                                                  |
| Returns if shift key is currently pressed                                                        |
| <sub>input.keyboard.isShiftDown(): Boolean</sub>                                                 |
| Returns last typed string                                                                        |
| <sub>input.keyboard.getTypedString(): String</sub>                                               |

## 8.8 Mouse input methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left mouse button integer code                                                                   |
| <sub>input.mouse.BUTTON_LEFT(): Integer</sub>                                                    |
| Middle mouse button integer code                                                                 |
| <sub>input.mouse.BUTTON_MIDDLE(): Integer</sub>                                                  |
| Right mouse button integer code                                                                  |
| <sub>input.mouse.BUTTON_RIGHT(): Integer</sub>                                                   |
| Returns if specific mouse button is currently pressed                                            |
| <sub>input.mouse.isButtonDown($button: Integer): Boolean</sub>                                   |
| Returns if specific mouse button has been released                                               |
| <sub>input.mouse.isButtonUp($button: Integer): Boolean</sub>                                     |
| Returns if mouse is dragging currently                                                           |
| <sub>input.mouse.isDragging($button: Integer): Boolean</sub>                                     |
| Returns if mouse has been moved                                                                  |
| <sub>input.mouse.hasMoved(): Boolean</sub>                                                       |
| Returns current value of x axis mouse wheel                                                      |
| <sub>input.mouse.getWheelX(): Float</sub>                                                        |
| Returns current value of y axis mouse wheel                                                      |
| <sub>input.mouse.getWheelY(): Float</sub>                                                        |
| Returns current value of z axis mouse wheel                                                      |
| <sub>input.mouse.getWheelZ(): Float</sub>                                                        |
| Get x mouse position                                                                             |
| <sub>input.mouse.getX(): Integer</sub>                                                           |
| Get unscaled x mouse position                                                                    |
| <sub>input.mouse.getXUnscaled(): Integer</sub>                                                   |
| Get y mouse position                                                                             |
| <sub>input.mouse.getY(): Integer</sub>                                                           |
| Get unscaled y mouse position                                                                    |
| <sub>input.mouse.getYUnscaled(): Integer</sub>                                                   |

## 8.9 Logic methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if logic has callable function                                                           |
| <sub>logic.has($logicId: String, $callable: String): Boolean</sub>                               |
| Get hierarchy id - <i>available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>logic.getHierarchyId(): String</sub>                                                        |
| Get hierarchy parent id - <i>available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>logic.getHierarchyParentId(): String</sub>                                                  |
| Get logic id - <i>available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>logic.getId(): String</sub>                                                                 |
| Get logic ids of all logics within application context - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>logic.getLogicIds(): Array</sub>                                                            |
| Call specific logic callable function                                                            |
| <sub>logic.call($logicId: String, $callable: String, ...): Mixed</sub>                           |

## 8.10 Logic signal methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if signal has been sent                                                                  |
| <sub>logic.signal.has(): Boolean</sub>                                                           |
| Get signal argument                                                                              |
| <sub>logic.signal.getArgument($argumentIndex: Integer): Mixed</sub>                              |
| Get signal name                                                                                  |
| <sub>logic.signal.getName(): String</sub>                                                        |
| Advance to next signal                                                                           |
| <sub>logic.signal.next(): Void</sub>                                                             |
| Send signal - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>logic.signal.send($logicId: String, $signal: String, ...): Void</sub>                       |

## 8.11 PathFinding methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Pathfinding idle state integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_IDLE(): Integer</sub>                                                     |
| Pathfinding computing state integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_PATHFINDING(): Integer</sub>                                              |
| Pathfinding failed state integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_PATHFINDING_FAILED(): Integer</sub>                                       |
| Pathfinding computing other pathfinding integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_PATHFINDING_OTHER(): Integer</sub>                                        |
| Pathfinding success state integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_PATHFINDING_SUCCESS(): Integer</sub>                                      |
| Pathfinding try/lock failed integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.STATE_TRYLOCK_FAILED(): Integer</sub>                                           |
| Issue pathfinding - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>pathfinding.findPath($logicId: String, $startPosition: Vector3, $endPosition: Vector3, =$path: Array): Integer</sub>|

## 8.12 Scene methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get scene depth                                                                                  |
| <sub>scene.getDepth(): Float</sub>                                                               |
| Get scene height                                                                                 |
| <sub>scene.getHeight(): Float</sub>                                                              |
| Get scene width                                                                                  |
| <sub>scene.getWidth(): Float</sub>                                                               |

## 8.13 SceneConnector methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Attach prototype to the logic hierarchy - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>sceneconnector.attachPrototype($pathName: String, $fileName: String, $id: String, $attachNodeId: String, $transform: Transform[, $parentId: String]): Void</sub>|
| Spawn prototype in scene - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>sceneconnector.spawnPrototype($pathName: String, $fileName: String, $id: String, $transform: Transform[, $hierarchyId: String[, $hierarchyParentId: String]]): Void</sub>|

## 8.14 Physics world methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Determine height at specific position in physics world - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.determineHeight($collisionTypeIds: Integer, $stepUpMax: Float, $point: Vector3, =$heightPoint: Vector3[, =$bodyId: String[, $minHeight: Float[, $maxHeight: Float]]]): Boolean</sub>|
| Determine collision of two specific bodies in physics world - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.doCollide($bodyId1: String, $bodyId2: String): Boolean</sub>                          |
| Compute ray casting in physics world - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.doRayCasting($collisionTypeIds: Integer, $start: Vector3, $end: Vector3, =$hitPoint: Vector3[, =$bodyId: String[, $actorId: String]]): Boolean</sub>|
| Determine collision of specific body in physics world - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.doesCollideWith($collisionTypeIds: Integer, $bodyId: String): Array</sub>             |

## 8.15 Physics world body methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get physics world entity angular damping - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getAngularDamping($bodyId: String): Float</sub>                                  |
| Set physics world entity angular damping - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setAngularDamping($bodyId: String, $angularDamping: Float): Void</sub>           |
| Get physics world entity angular velocity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getAngularVelocity($bodyId: String): Vector3</sub>                               |
| Set physics world entity angular velocity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setAngularVelocity($bodyId: String, $angularVelocity: Vector3): Void</sub>       |
| Returns physics world collision type id 10 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_10(): Integer</sub>                                             |
| Returns physics world collision type id 11 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_11(): Integer</sub>                                             |
| Returns physics world collision type id 12 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_12(): Integer</sub>                                             |
| Returns physics world collision type id 13 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_13(): Integer</sub>                                             |
| Returns physics world collision type id 14 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_14(): Integer</sub>                                             |
| Returns physics world collision type id 15 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_15(): Integer</sub>                                             |
| Returns physics world collision type id 16 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_16(): Integer</sub>                                             |
| Returns physics world collision type id 3 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_3(): Integer</sub>                                              |
| Returns physics world collision type id 4 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_4(): Integer</sub>                                              |
| Returns physics world collision type id 5 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_5(): Integer</sub>                                              |
| Returns physics world collision type id 6 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_6(): Integer</sub>                                              |
| Returns physics world collision type id 7 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_7(): Integer</sub>                                              |
| Returns physics world collision type id 8 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_8(): Integer</sub>                                              |
| Returns physics world collision type id 9 - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_9(): Integer</sub>                                              |
| Returns all physics world collision type ids - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_ALL(): Integer</sub>                                            |
| Returns dynamic physics world collision type id - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_DYNAMIC(): Integer</sub>                                        |
| Returns static physics world collision type id - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.COLLISION_TYPEID_STATIC(): Integer</sub>                                         |
| Get Physics world entity own collision type id - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getCollisionTypeId($bodyId: String): Integer</sub>                               |
| Set Physics world entity own collision type id - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setCollisionTypeId($bodyId: String, $collisionTypeId: Integer): Void</sub>       |
| Get Physics world entity enabled collision type ids - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getCollisionTypeIds($bodyId: String): Integer</sub>                              |
| Set Physics world entity enabled collision type ids - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setCollisionTypeIds($bodyId: String, $collisionTypeIds: Integer): Void</sub>     |
| Returns if physics world entity is enabled - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.isEnabled($bodyId: String): Boolean</sub>                                        |
| Set physics world entity enabled/disabled - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setEnabled($bodyId: String, $enabled: Boolean): Void</sub>                       |
| Get physics world entity linear damping - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getLinearDamping($bodyId: String): Float</sub>                                   |
| Set physics world entity linear damping - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setLinearDamping($bodyId: String, $linearDamping: Float): Void</sub>             |
| Get physics world entity linear velocity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getLinearVelocity($bodyId: String): Vector3</sub>                                |
| Set physics world entity linear velocity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setLinearVelocity($bodyId: String, $linearVelocity: Vector3): Void</sub>         |
| Returns physics world dynamic collision body type integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.TYPE_COLLISION_DYNAMIC(): Integer</sub>                                          |
| Returns physics world static collision body type integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.TYPE_COLLISION_STATIC(): Integer</sub>                                           |
| Returns physics world dynamic rigid body type integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.TYPE_DYNAMIC(): Integer</sub>                                                    |
| Returns physics world static rigid body type integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.TYPE_STATIC(): Integer</sub>                                                     |
| Get physics world entity transform - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getTransform($bodyId: String): Transform</sub>                                   |
| Set physics world entity transform - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.setTransform($bodyId: String, $transform: Transform): Void</sub>                 |
| Get physics world entity body type integer code - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.getType($bodyId: String): Integer</sub>                                          |
| Add force to physics world entity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.addForce($bodyId: String, $force: Vector3[, $origin: Vector3]): Void</sub>       |
| Add torque to physics world entity - <i>available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed()</i>|
| <sub>world.body.addTorque($bodyId: String, $torque: Vector3): Void</sub>                         |

# 9. MiniScript GUI methods

The boilerplate template code for a MiniScript GUI logic looks like: [gui_script_template.tscript](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/engine/templates/tscript/gui_script_template.tscript)

## 9.1 Element node condition methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if GUI element node has a specific condition enabled                                     |
| <sub>gui.elementnode.conditions.has($elementNodeId: String, $condition: String): Boolean</sub>   |
| Get enabled GUI element node conditions                                                          |
| <sub>gui.elementnode.conditions.get($elementNodeId: String): Array</sub>                         |
| Set enabled GUI element node condition                                                           |
| <sub>gui.elementnode.conditions.set($elementNodeId: String, $condition: String): Void</sub>      |
| Set array of enabled GUI element node conditions                                                 |
| <sub>gui.elementnode.conditions.setAll($elementNodeId: String, $conditions: Array): Void</sub>   |
| Add enabled GUI element node condition                                                           |
| <sub>gui.elementnode.conditions.add($elementNodeId: String, $condition: String): Void</sub>      |
| Remove enabled GUI element node condition                                                        |
| <sub>gui.elementnode.conditions.remove($elementNodeId: String, $condition: String): Void</sub>   |
| Remove all enabled GUI element node conditions                                                   |
| <sub>gui.elementnode.conditions.removeAll($elementNodeId: String): Void</sub>                    |

## 9.2 Event methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns GUI event performed action type integer code                                             |
| <sub>gui.event.ACTIONTYPE_PERFORMED(): Integer</sub>                                             |
| Returns GUI event performing action type integer code                                            |
| <sub>gui.event.ACTIONTYPE_PERFORMING(): Integer</sub>                                            |

## 9.3 Image node methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get image source of GUI image node                                                               |
| <sub>gui.imagenode.getSource($imageNodeId: String): String</sub>                                 |
| Set image source of GUI image node                                                               |
| <sub>gui.imagenode.setSource($imageNodeId: String, $source: String): Void</sub>                  |

## 9.4 Node controller methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get GUI node controller value                                                                    |
| <sub>gui.node.controller.getValue($nodeId: String): String</sub>                                 |
| Set GUI node controller value                                                                    |
| <sub>gui.node.controller.setValue($nodeId: String, $value: String): Void</sub>                   |

## 9.5 Parent node methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Add sub nodes using XML to GUI parent node                                                       |
| <sub>gui.parentnode.addSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</sub>|
| Clear sub nodes of GUI parent node                                                               |
| <sub>gui.parentnode.clearSubNodes($parentNodeId: String): Void</sub>                             |
| Replace sub nodes using XML of GUI parent node                                                   |
| <sub>gui.parentnode.replaceSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</sub>|

## 9.6 Screen methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Return if GUI screen is enabled                                                                  |
| <sub>gui.screen.isEnabled($screenId: String): Boolean</sub>                                      |
| Set GUI screen enabled/disabled                                                                  |
| <sub>gui.screen.setEnabled($screenId: String, $enabled: Boolean): Void</sub>                     |
| Call specific screen logic function                                                              |
| <sub>gui.screen.call($screenId: String, $function: String, ...): Mixed</sub>                     |
| Goto current screen to specific screen                                                           |
| <sub>gui.screen.goto($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</sub>      |
| Pop current screen from screen stack                                                             |
| <sub>gui.screen.pop(): Void</sub>                                                                |
| Push screen to current screen stack                                                              |
| <sub>gui.screen.push($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</sub>      |

## 9.7 Screen node methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get current screen node Id                                                                       |
| <sub>gui.screennode.getId(): String</sub>                                                        |

## 9.8 Text node methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get text of GUI text node                                                                        |
| <sub>gui.textnode.getText($textNodeId: String): String</sub>                                     |
| Set text of GUI text node                                                                        |
| <sub>gui.textnode.setText($textNodeId: String, $text: String): Void</sub>                        |

## 9.9 Video node methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get video source of GUI video node                                                               |
| <sub>gui.videonode.getSource($videoNodeId: String): String</sub>                                 |
| Set video source of GUI video node                                                               |
| <sub>gui.videonode.setSource($videoNodeId: String, $source: String): Void</sub>                  |

## 9.10 Keyboard input methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT key is currently pressed                                                          |
| <sub>input.keyboard.isAltDown(): Boolean</sub>                                                   |
| Returns if specific character is currently pressed                                               |
| <sub>input.keyboard.isCharDown($charAsString: String): Boolean</sub>                             |
| Returns if CONTROL key is currently pressed                                                      |
| <sub>input.keyboard.isControlDown(): Boolean</sub>                                               |
| Backspace key keycode                                                                            |
| <sub>input.keyboard.KEYCODE_BACKSPACE(): Integer</sub>                                           |
| Delete key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_DELETE(): Integer</sub>                                              |
| Down key keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_DOWN(): Integer</sub>                                                |
| End key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_END(): Integer</sub>                                                 |
| Escape key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_ESCAPE(): Integer</sub>                                              |
| F1 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F1(): Integer</sub>                                                  |
| F10 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F10(): Integer</sub>                                                 |
| F11 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F11(): Integer</sub>                                                 |
| F12 key keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F12(): Integer</sub>                                                 |
| F2 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F2(): Integer</sub>                                                  |
| F3 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F3(): Integer</sub>                                                  |
| F4 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F4(): Integer</sub>                                                  |
| F5 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F5(): Integer</sub>                                                  |
| F6 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F6(): Integer</sub>                                                  |
| F7 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F7(): Integer</sub>                                                  |
| F8 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F8(): Integer</sub>                                                  |
| F9 key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F9(): Integer</sub>                                                  |
| Left key keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_LEFT(): Integer</sub>                                                |
| Page down key keycode                                                                            |
| <sub>input.keyboard.KEYCODE_PAGEDOWN(): Integer</sub>                                            |
| Page up key keycode                                                                              |
| <sub>input.keyboard.KEYCODE_PAGEUP(): Integer</sub>                                              |
| Home/position key keycode                                                                        |
| <sub>input.keyboard.KEYCODE_POS1(): Integer</sub>                                                |
| Return key keycode                                                                               |
| <sub>input.keyboard.KEYCODE_RETURN(): Integer</sub>                                              |
| Right key keycode                                                                                |
| <sub>input.keyboard.KEYCODE_RIGHT(): Integer</sub>                                               |
| Space key keycode                                                                                |
| <sub>input.keyboard.KEYCODE_SPACE(): Integer</sub>                                               |
| Up key keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_UP(): Integer</sub>                                                  |
| Returns if specific key is currently pressed                                                     |
| <sub>input.keyboard.isKeyDown($keyCode: Integer): Boolean</sub>                                  |
| Returns if meta key is currently pressed                                                         |
| <sub>input.keyboard.isMetaDown(): Boolean</sub>                                                  |
| Returns if shift key is currently pressed                                                        |
| <sub>input.keyboard.isShiftDown(): Boolean</sub>                                                 |
| Returns last typed String                                                                        |
| <sub>input.keyboard.getTypedString(): String</sub>                                               |

## 9.11 Mouse input methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left mouse button integer code                                                                   |
| <sub>input.mouse.BUTTON_LEFT(): Integer</sub>                                                    |
| Middle mouse button integer code                                                                 |
| <sub>input.mouse.BUTTON_MIDDLE(): Integer</sub>                                                  |
| Right mouse button integer code                                                                  |
| <sub>input.mouse.BUTTON_RIGHT(): Integer</sub>                                                   |
| Returns if specific mouse button is currently pressed                                            |
| <sub>input.mouse.isButtonDown($button: Integer): Boolean</sub>                                   |
| Returns if specific mouse button has been released                                               |
| <sub>input.mouse.isButtonUp($button: Integer): Boolean</sub>                                     |
| Returns if mouse is dragging currently                                                           |
| <sub>input.mouse.isDragging($button: Integer): Boolean</sub>                                     |
| Returns if mouse has been moved                                                                  |
| <sub>input.mouse.hasMoved(): Boolean</sub>                                                       |
| Returns current value of x axis mouse wheel                                                      |
| <sub>input.mouse.getWheelX(): Float</sub>                                                        |
| Returns current value of y axis mouse wheel                                                      |
| <sub>input.mouse.getWheelY(): Float</sub>                                                        |
| Returns current value of z axis mouse wheel                                                      |
| <sub>input.mouse.getWheelZ(): Float</sub>                                                        |
| Get x mouse position                                                                             |
| <sub>input.mouse.getX(): Integer</sub>                                                           |
| Get unscaled x mouse position                                                                    |
| <sub>input.mouse.getXUnscaled(): Integer</sub>                                                   |
| Get y mouse position                                                                             |
| <sub>input.mouse.getY(): Integer</sub>                                                           |
| Get unscaled y mouse position                                                                    |
| <sub>input.mouse.getYUnscaled(): Integer</sub>                                                   |

## 9.12 Logic methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if logic has callable function                                                           |
| <sub>logic.has($logicId: String, $callable: String): Boolean</sub>                               |
| Call specific logic callable function                                                            |
| <sub>logic.call($logicId: String, $callable: String, ...): Mixed</sub>                           |

## 9.13 Logic signal methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Send signal                                                                                      |
| <sub>logic.signal.send($logicId: String, $signal: String, ...): Void</sub>                       |

# 10. Operators

# 10. Operators

| Op | Method                                                                                      |
|----|---------------------------------------------------------------------------------------------|
| !  | not($bool: Boolean): Boolean                                                                |
| != | notEqual($a: Mixed, $b: Mixed): Boolean                                                     |
| %  | mod($value: Number, $range: Number): Number                                                 |
| &  | bitwiseAnd($a: Integer, $b: Integer): Integer                                               |
| && | and($a: Boolean, $b: Boolean): Boolean                                                      |
| *  | mul($a: Mixed, $b: Mixed): Mixed                                                            |
| +  | add($a: Mixed, $b: Mixed): Mixed                                                            |
| ++ | prefixIncrement(=$variable: Integer): Integer                                               |
| -  | sub($a: Mixed, $b: Mixed): Mixed                                                            |
| -- | prefixDecrement(=$variable: Integer): Integer                                               |
| /  | div($a: Mixed, $b: Mixed): Mixed                                                            |
| <  | lesser($a: Mixed, $b: Mixed): Boolean                                                       |
| <= | lesserEquals($a: Mixed, $b: Mixed): Boolean                                                 |
| =  | setVariable($variable: String, $value: Mixed): Mixed                                        |
| == | equals($a: Mixed, $b: Mixed): Boolean                                                       |
| >  | greater($a: Mixed, $b: Mixed): Boolean                                                      |
| >= | greaterEquals($a: Mixed, $b: Mixed): Boolean                                                |
| \| | bitwiseOr($a: Integer, $b: Integer): Integer                                                |
| \|\|| or($a: Boolean, $b: Boolean): Boolean                                                      |
| ^  | bitwiseXor($a: Integer, $b: Integer): Integer                                               |
| ~  | bitwiseNot($value: Integer): Integer                                                        |
