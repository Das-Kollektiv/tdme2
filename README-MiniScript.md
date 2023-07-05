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

# 3. Functions

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

Variable identifiers always start with a "$", not because we love money and/or PHP, but because its the cheapest way to determine if e.g. a argument is a literal or a variable.
Constants need also be prefixed with a "$" and should be named with uppercase letters like "$PI = 3.14". (No real constant support yet, but it is planned)

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
	array.push($array, 5, 6, 7)
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
	forCondition($i < array.length($array))
		console.log($i + ": " + array.get($array, $i))
		++$i
	end
...
```

Iterating arrays using array.length() and [] operator:
```
...
	$i = 0
	forCondition($i < array.length($array))
		console.log($i + ": " + $array[$i])
		++$i
	end
...
```

Removing values from arrays using array.removeOf():
```
...
	array.removeOf($array, 6)
	array.removeOf($array, 7)
...
```

Removing from arrays using a index with array.remove():
```
...
	array.remove($array, 2)
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
	map.set($map, "test1", 123)
	map.set($map, "test2", 456)
	map.set($map, "test3", array(1, 2, 3))
	map.set($map, "test4", "Yaaaa")
...
```

Removing from map using map.remove() and a given key:
```
...
	map.remove($map, "test2")
...
```

Reading values from map using map.get() and given keys:
```
...
	console.log("map value for test1 key using map.get(): ", map.get($map, "test1"))
	console.log("map value for test2 key using map.get(): ", map.get($map, "test2"))
	console.log("map value for test3 key using map.get(): ", map.get($map, "test3"))
	console.log("map value for test4 key using map.get(): ", map.get($map, "test4"))
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
	console.log("map keys: ", map.getKeys($map))
...
```

Reading map values:
```
...
	console.log("map values: ", map.getValues($map))
...
```

Reading all keys and values from map using map.get() and map.getKeys()
```
...
	$mapKeys = map.getKeys($map)
	$i = 0
	forCondition($i < array.length($mapKeys))
		console.log($mapKeys[$i] + " = " + map.get($map, $mapKeys[$i]))
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
	set.insert($set, "test1")
	set.insert($set, "test2")
	set.insert($set, "test3")
...
```

Removing keys from set using set.remove():
```
...
	set.remove($set, "test2")
...
```

Checking if keys exist in map using map.has() and given keys:
```
...
	console.log("set does have test1 key using set.has(): ", set.has($set, "test1"))
	console.log("set does have test2 key using set.has(): ", set.has($set, "test2"))
	console.log("set does have test3 key using set.has(): ", set.has($set, "test3"))
	console.log("set does have test4 key using set.has(): ", set.has($set, "test4"))
	console.log("set does have test5 key using set.has(): ", set.has($set, "test5"))
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
	console.log("set keys: ", set.getKeys($set))
...
```

# 5. Program structure and flow

... TODO ...

# 6. MiniScript Base Methods

## 6.1 Base Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Variable                                                                                     |
| <sub>getVariable($variable: String): Mixed</sub>                                                 |
| Set Variable                                                                                     |
| <sub>setVariable($variable: String, $value: Mixed): Mixed</sub>                                  |
| Unset Variable                                                                                   |
| <sub>unsetVariable($variable: String): Void</sub>                                                |
| Add                                                                                              |
| <sub>add($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Logical And                                                                                      |
| <sub>and($a: Boolean, $b: Boolean): Boolean</sub>                                                |
| Bitwise And                                                                                      |
| <sub>bitwiseAnd($a: Integer, $b: Integer): Integer</sub>                                         |
| Bitwise Not                                                                                      |
| <sub>bitwiseNot($value: Integer): Integer</sub>                                                  |
| Bitwise Or                                                                                       |
| <sub>bitwiseOr($a: Integer, $b: Integer): Integer</sub>                                          |
| Bitwise Xor                                                                                      |
| <sub>bitwiseXor($a: Integer, $b: Integer): Integer</sub>                                         |
| Create Bool                                                                                      |
| <sub>bool($bool: Boolean): Boolean</sub>                                                         |
| Divide                                                                                           |
| <sub>div($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Else                                                                                             |
| <sub>else(): Void</sub>                                                                          |
| Else If                                                                                          |
| <sub>elseif($condition: Boolean): Void</sub>                                                     |
| End                                                                                              |
| <sub>end(): Void</sub>                                                                           |
| Equals                                                                                           |
| <sub>equals($a: Mixed, $b: Mixed): Boolean</sub>                                                 |
| Create Float                                                                                     |
| <sub>float($float: Float): Float</sub>                                                           |
| For Condition                                                                                    |
| <sub>forCondition($condition: Boolean): Void</sub>                                               |
| For Time                                                                                         |
| <sub>forTime($time: Integer): Void</sub>                                                         |
| Greater                                                                                          |
| <sub>greater($a: Mixed, $b: Mixed): Boolean</sub>                                                |
| Greater Equals                                                                                   |
| <sub>greaterEquals($a: Mixed, $b: Mixed): Boolean</sub>                                          |
| If                                                                                               |
| <sub>if($condition: Boolean): Void</sub>                                                         |
| Create Integer                                                                                   |
| <sub>int($int: Integer): Integer</sub>                                                           |
| Lesser                                                                                           |
| <sub>lesser($a: Mixed, $b: Mixed): Boolean</sub>                                                 |
| Lesser Equals                                                                                    |
| <sub>lesserEquals($a: Mixed, $b: Mixed): Boolean</sub>                                           |
| Compute Modulo                                                                                   |
| <sub>mod($value: Number, $range: Number): Number</sub>                                           |
| Multiply                                                                                         |
| <sub>mul($a: Mixed, $b: Mixed): Mixed</sub>                                                      |
| Logical Not                                                                                      |
| <sub>not($bool: Boolean): Boolean</sub>                                                          |
| Logical Not Equal                                                                                |
| <sub>notEqual($a: Mixed, $b: Mixed): Boolean</sub>                                               |
| Logical Or                                                                                       |
| <sub>or($a: Boolean, $b: Boolean): Boolean</sub>                                                 |
| Prefix Decrement                                                                                 |
| <sub>prefixDecrement(=$variable: Integer): Integer</sub>                                         |
| Prefix Increment                                                                                 |
| <sub>prefixIncrement(=$variable: Integer): Integer</sub>                                         |
| Return from Function with optional Return Value                                                  |
| <sub>return([$value: Mixed]): Void</sub>                                                         |
| Subtract                                                                                         |
| <sub>sub($a: Mixed, $b: Mixed): Mixed</sub>                                                      |

## 6.2 Array Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Array                                                                                     |
| <sub>array(...): Array</sub>                                                                     |
| Get Array Entry                                                                                  |
| <sub>array.get($array: Array, $index: Integer): Mixed</sub>                                      |
| Set Array Entry                                                                                  |
| <sub>array.set(=$array: Array, $index: Integer, $value: Mixed): Void</sub>                       |
| Get Array Index by Value                                                                         |
| <sub>array.indexOf($array: Array, $value: String[, $beginIndex: Integer]): Integer</sub>         |
| Get Array Length                                                                                 |
| <sub>array.length($array: Array): Integer</sub>                                                  |
| Add to Array                                                                                     |
| <sub>array.push(=$array: Array, ...): Void</sub>                                                 |
| Remove Array by Index                                                                            |
| <sub>array.remove(=$array: Array, $index: Integer): Void</sub>                                   |
| Remove Array Entry by Value                                                                      |
| <sub>array.removeOf(=$array: Array, $value: String[, $beginIndex: Integer]): Void</sub>          |
| Reverse Array                                                                                    |
| <sub>array.reverse(=$array: Array): Void</sub>                                                   |
| Sort Array                                                                                       |
| <sub>array.sort(=$array: Array, $function: String): Void</sub>                                   |

## 6.3 Console Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Print to Console                                                                                 |
| <sub>console.log(...): Void</sub>                                                                |

## 6.4 JSON Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Deserialize JSON                                                                                 |
| <sub>json.deserialize($json: String): Mixed</sub>                                                |
| Serialize JSON                                                                                   |
| <sub>json.serialize($value: Mixed): String</sub>                                                 |

## 6.5 Map Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Map                                                                                       |
| <sub>map(): Map</sub>                                                                            |
| Has Entry by Key                                                                                 |
| <sub>map.has($map: Map, $key: String): Boolean</sub>                                             |
| Get Map Value by Key                                                                             |
| <sub>map.get($map: Map, $key: String): Mixed</sub>                                               |
| Set Map Entry                                                                                    |
| <sub>map.set(=$map: Map, $key: String, $value: Mixed): Void</sub>                                |
| Get Map Keys                                                                                     |
| <sub>map.getKeys($map: Map): Array</sub>                                                         |
| Get Map Values                                                                                   |
| <sub>map.getValues($map: Map): Array</sub>                                                       |
| Remove Map Entry                                                                                 |
| <sub>map.remove(=$map: Map, $key: String): Void</sub>                                            |

## 6.6 Matrix3x3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Identity 3x3 Matrix                                                                       |
| <sub>mat3.identity(): Matrix3x3</sub>                                                            |
| Multiply 3x3 Matrix with 3x3 Matrix or Vector2                                                   |
| <sub>mat3.multiply($mat3: Matrix3x3, ...): Mixed</sub>                                           |
| Create Rotation 3x3 Matrix                                                                       |
| <sub>mat3.rotate($angle: Float): Matrix3x3</sub>                                                 |
| Create 3x3 Matrix which rotates around Point                                                     |
| <sub>mat3.rotateAroundPoint($point: Vector2, $angle: Float): Matrix3x3</sub>                     |
| Create 3x3 Matrix which rotates around Texture Center                                            |
| <sub>mat3.rotateAroundTextureCenter($angle: Float): Matrix3x3</sub>                              |
| Create Scale 3x3 Matrix                                                                          |
| <sub>mat3.scale(...): Matrix3x3</sub>                                                            |
| Create Translation 3x3 Matrix                                                                    |
| <sub>mat3.translate($translation: Vector2): Matrix3x3</sub>                                      |

## 6.7 Matrix4x4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from 4x4 Matrix                                                             |
| <sub>mat4.computeEulerAngles($mat4: Matrix4x4): Vector3</sub>                                    |
| Create Identity 4x4 Matrix                                                                       |
| <sub>mat4.identity(): Matrix4x4</sub>                                                            |
| Create 4x4 Matrix Inverse                                                                        |
| <sub>mat4.invert($mat4: Matrix4x4): Matrix4x4</sub>                                              |
| Multiply 4x4 Matrix with 4x4 Matrix or Vector3 or Vector4                                        |
| <sub>mat4.multiply($mat4: Matrix4x4, ...): Mixed</sub>                                           |
| Create Rotation 4x4 Matrix                                                                       |
| <sub>mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4</sub>                                 |
| Create Scale 4x4 Matrix                                                                          |
| <sub>mat4.scale(...): Matrix4x4</sub>                                                            |
| Create Translation 4x4 Matrix                                                                    |
| <sub>mat4.translate($translation: Vector3): Matrix4x4</sub>                                      |

## 6.8 Math Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Degree to Radian Factor                                                                          |
| <sub>math.DEG2RAD(): Float</sub>                                                                 |
| Epsilon                                                                                          |
| <sub>math.EPSILON(): Float</sub>                                                                 |
| G                                                                                                |
| <sub>math.G(): Float</sub>                                                                       |
| PI                                                                                               |
| <sub>math.PI(): Float</sub>                                                                      |
| Return Number as Positive Number                                                                 |
| <sub>math.abs($value: Number): Number</sub>                                                      |
| Return Number to be Positive within given Range                                                  |
| <sub>math.absmod($value: Number, $range: Number): Number</sub>                                   |
| Compute acos                                                                                     |
| <sub>math.acos($value: Float): Float</sub>                                                       |
| Compute asin                                                                                     |
| <sub>math.asin($value: Float): Float</sub>                                                       |
| Compute atan                                                                                     |
| <sub>math.atan($value: Float): Float</sub>                                                       |
| Compute atan2                                                                                    |
| <sub>math.atan2($y: Float, $x: Float): Float</sub>                                               |
| Round Float up to next higher Integer                                                            |
| <sub>math.ceil($value: Float): Float</sub>                                                       |
| Return Number clamped to be in given Range                                                       |
| <sub>math.clamp($value: Number, $min: Number, $max: Number): Number</sub>                        |
| Compute acos                                                                                     |
| <sub>math.cos($value: Float): Float</sub>                                                        |
| Compute exp                                                                                      |
| <sub>math.exp($value: Float): Float</sub>                                                        |
| Round Float down to next lower Integer                                                           |
| <sub>math.floor($value: Float): Float</sub>                                                      |
| Compute log                                                                                      |
| <sub>math.log($value: Float): Float</sub>                                                        |
| Return maximum Number of given Values                                                            |
| <sub>math.max($a: Number, $b: Number): Number</sub>                                              |
| Return minimum Number of given Values                                                            |
| <sub>math.min($a: Number, $b: Number): Number</sub>                                              |
| Compute Modulo/Remainder                                                                         |
| <sub>math.mod($value: Number, $range: Number): Number</sub>                                      |
| Compute pow                                                                                      |
| <sub>math.pow($a: Number, $b: Number): Number</sub>                                              |
| Create a random Number between 0.0 and 1.0                                                       |
| <sub>math.random(): Float</sub>                                                                  |
| Round Float Up or Down to Integer                                                                |
| <sub>math.round($value: Float): Float</sub>                                                      |
| Return Sign of given Number                                                                      |
| <sub>math.sign($value: Number): Number</sub>                                                     |
| Compute sin                                                                                      |
| <sub>math.sin($value: Float): Float</sub>                                                        |
| Compute Square Root                                                                              |
| <sub>math.sqrt($value: Float): Float</sub>                                                       |
| Compute Square Product                                                                           |
| <sub>math.square($value: Number): Number</sub>                                                   |
| Compute tan                                                                                      |
| <sub>math.tan($value: Float): Float</sub>                                                        |

## 6.9 Quaternion Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from Quaternion                                                             |
| <sub>quaternion.computeEulerAngles($quaternion: Quaternion): Vector3</sub>                       |
| Compute 4x4 Rotation Matrix from Quaternion                                                      |
| <sub>quaternion.computeMatrix($quaternion: Quaternion): Matrix4x4</sub>                          |
| Create Identity Quaternion                                                                       |
| <sub>quaternion.identity(): Quaternion</sub>                                                     |
| Create Quaternion Inverse                                                                        |
| <sub>quaternion.invert($quaternion: Quaternion): Quaternion</sub>                                |
| Multiply Quaternion with Quaternion or Vector3                                                   |
| <sub>quaternion.multiply($quaternion: Quaternion, ...): Mixed</sub>                              |
| Normalize Quaternion                                                                             |
| <sub>quaternion.normalize($quaternion: Quaternion): Quaternion</sub>                             |
| Create Rotation Quaternion                                                                       |
| <sub>quaternion.rotate($axis: Vector3, $angle: Float): Quaternion</sub>                          |

## 6.10 Script Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Named Conditions                                                                             |
| <sub>script.getNamedConditions(): String</sub>                                                   |
| Get Script Variables                                                                             |
| <sub>script.getVariables(): Map</sub>                                                            |
| Call Script Function                                                                             |
| <sub>script.call($function: String, ...): Mixed</sub>                                            |
| Disable a specific Named Condition                                                               |
| <sub>script.disableNamedCondition($name: String): Void</sub>                                     |
| Emit a Condition                                                                                 |
| <sub>script.emit($condition: String): Void</sub>                                                 |
| Enable a specific Named Condition                                                                |
| <sub>script.enableNamedCondition($name: String): Void</sub>                                      |
| Evaluate a Script Statement                                                                      |
| <sub>script.evaluate($statement: String): Mixed</sub>                                            |
| Stop Script                                                                                      |
| <sub>script.stop(): Void</sub>                                                                   |
| Wait for given Milliseconds                                                                      |
| <sub>script.wait($time: Integer): Void</sub>                                                     |
| Wait for Condition to happen                                                                     |
| <sub>script.waitForCondition(): Void</sub>                                                       |

## 6.11 Set Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Set                                                                                       |
| <sub>set(): Set</sub>                                                                            |
| Has Key in Set                                                                                   |
| <sub>set.has($set: Set, $key: String): Boolean</sub>                                             |
| Get Set Keys                                                                                     |
| <sub>set.getKeys($set: Set): Array</sub>                                                         |
| Insert Key into Set                                                                              |
| <sub>set.insert(=$set: Set, $key: String): Void</sub>                                            |
| Remove Key from Set                                                                              |
| <sub>set.remove(=$set: Set, $key: String): Void</sub>                                            |

## 6.12 String Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create String                                                                                    |
| <sub>string($string: String): String</sub>                                                       |
| Test if String Value is Empty                                                                    |
| <sub>string.isEmpty($string: String): Boolean</sub>                                              |
| Test if String Value is a Float Number                                                           |
| <sub>string.isFloat($string: String): Boolean</sub>                                              |
| Test if String Value is a Integer Number                                                         |
| <sub>string.isInteger($string: String): Boolean</sub>                                            |
| Return Character of String at given Position                                                     |
| <sub>string.charAt($string: String, $index: Integer): String</sub>                               |
| Concatenate Strings                                                                              |
| <sub>string.concatenate(...): String</sub>                                                       |
| Test if String ends with specific String                                                         |
| <sub>string.endsWith($string: String, $suffix: String): Boolean</sub>                            |
| Test if 2 Strings matches ignoring Case Sensitivity                                              |
| <sub>string.equalsIgnoreCase($string1: String, $string2: String): Boolean</sub>                  |
| Return First Index of specific String in String                                                  |
| <sub>string.firstIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</sub>  |
| Return Index of specific String in String                                                        |
| <sub>string.indexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</sub>       |
| Return Last Index of specific String in String                                                   |
| <sub>string.lastIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</sub>   |
| Return String Length                                                                             |
| <sub>string.length($string: String): Integer</sub>                                               |
| Pad String Left                                                                                  |
| <sub>string.padLeft($src: String, $by: String, $toSize: Integer): String</sub>                   |
| Pad String Right                                                                                 |
| <sub>string.padRight($src: String, $by: String, $toSize: Integer): String</sub>                  |
| RegEx Match                                                                                      |
| <sub>string.regexMatch($string: String, $pattern: String): Boolean</sub>                         |
| RegEx Replace                                                                                    |
| <sub>string.regexReplace($string: String, $pattern: String, $by: String): String</sub>           |
| Replace specific String in String with given String                                              |
| <sub>string.replace($string: String, $what: String, $by: String[, $beginIndex: Integer]): String</sub>|
| Create Spaces as String                                                                          |
| <sub>string.space([$spaces: Integer]): String</sub>                                              |
| Test if given String starts with specific String                                                 |
| <sub>string.startsWith($string: String, $prefix: String): Boolean</sub>                          |
| Return Substring of String                                                                       |
| <sub>string.substring($string: String, $beginIndex: Integer[, $endIndex: Integer]): String</sub> |
| Compute Lower Case String of String                                                              |
| <sub>string.toLowerCase($string: String): String</sub>                                           |
| Compute Upper Case String of String                                                              |
| <sub>string.toUpperCase($string: String): String</sub>                                           |
| Tokenize String                                                                                  |
| <sub>string.tokenize($string: String, $delimiters: String): Array</sub>                          |
| Trim String                                                                                      |
| <sub>string.trim($string: String): String</sub>                                                  |

## 6.13 Time Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Time as String                                                                               |
| <sub>time.getAsString([$format: String]): String</sub>                                           |
| Get Current Time in Milliseconds                                                                 |
| <sub>time.getCurrentMillis(): Integer</sub>                                                      |

## 6.14 Transform Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Transform                                                                                 |
| <sub>transform([$translation: Vector3[, $scale: Vector3[, $rotationZ: Float[, $rotationY: Float[, $rotationX: Float]]]]]): Transform</sub>|
| X Axis as Vector3                                                                                |
| <sub>transform.AXIS_X(): Vector3</sub>                                                           |
| Y Axis as Vector3                                                                                |
| <sub>transform.AXIS_Y(): Vector3</sub>                                                           |
| Z Axis as Vector3                                                                                |
| <sub>transform.AXIS_Z(): Vector3</sub>                                                           |
| Get Rotation Angle of specific Rotation of Transform                                             |
| <sub>transform.getRotationAngle($transform: Transform, $idx: Integer): Float</sub>               |
| Set Rotation Angle of specific Rotation of Transform                                             |
| <sub>transform.setRotationAngle(=$transform: Transform, $idx: Integer, $angle: Float): Void</sub>|
| Set Rotation Axis of specific Rotation of Transform                                              |
| <sub>transform.getRotationAxis($transform: Transform, $idx: Integer): Vector3</sub>              |
| Compute Transform Rotations Quaternion                                                           |
| <sub>transform.getRotationsQuaternion($transform: Transform): Quaternion</sub>                   |
| Get Transfrom Scale                                                                              |
| <sub>transform.getScale($transform: Transform): Vector3</sub>                                    |
| Set Transfrom Scale                                                                              |
| <sub>transform.setScale(=$transform: Transform, $scale: Vector3): Void</sub>                     |
| Get 4x4 Transform Matrix                                                                         |
| <sub>transform.getTransformMatrix($transform: Transform): Matrix4x4</sub>                        |
| Get Transform Translation                                                                        |
| <sub>transform.getTranslation($transform: Transform): Vector3</sub>                              |
| Set Transform Translation                                                                        |
| <sub>transform.setTranslation(=$transform: Transform, $translation: Vector3): Void</sub>         |
| Apply a Rotation to Transform                                                                    |
| <sub>transform.applyRotation(=$transform: Transform, $axis: Vector3, $angle: Float): Void</sub>  |
| Create Transform from 4x4 Matrix                                                                 |
| <sub>transform.fromMatrix($transformMatrix: Matrix4x4): Transform</sub>                          |
| Interpolate Rotation                                                                             |
| <sub>transform.interpolateRotation($currentAngle: Float, $targetAngle: Float, $timePassedSeconds: Float, $degreesPerSeconds: Float, =$interpolatedAngle: Float): Boolean</sub>|
| Multiply Transform with Vector3                                                                  |
| <sub>transform.multiply($transform: Transform, $vec3: Vector3): Vector3</sub>                    |
| Rotate Vector3 using Transform                                                                   |
| <sub>transform.rotate($transform: Transform, $vec3: Vector3): Vector3</sub>                      |

## 6.15 Vector2 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector2                                                                                   |
| <sub>vec2($x: Float, $y: Float): Vector2</sub>                                                   |
| Compute Vector2 Dot Product                                                                      |
| <sub>vec2.computeDotProduct($a: Vector2, $b: Vector2): Float</sub>                               |
| Compute Vector2 Length                                                                           |
| <sub>vec2.computeLength($vec2: Vector2): Float</sub>                                             |
| Compute Vector2 Squared Length                                                                   |
| <sub>vec2.computeLengthSquared($vec2: Vector2): Float</sub>                                      |
| Return Vector2 X Component                                                                       |
| <sub>vec2.getX($vec2: Vector2): Float</sub>                                                      |
| Return Vector2 Y Component                                                                       |
| <sub>vec2.getY($vec2: Vector2): Float</sub>                                                      |
| Normalize Vector2                                                                                |
| <sub>vec2.normalize($vec2: Vector2): Vector2</sub>                                               |

## 6.16 Vector3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector3                                                                                   |
| <sub>vec3($x: Float, $y: Float, $z: Float): Vector3</sub>                                        |
| Compute Angle between two Vector3                                                                |
| <sub>vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float</sub>                       |
| Compute Vector3 Cross Product                                                                    |
| <sub>vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3</sub>                           |
| Compute Vector3 Dot Product                                                                      |
| <sub>vec3.computeDotProduct($a: Vector3, $b: Vector3): Float</sub>                               |
| Compute Vector3 Length                                                                           |
| <sub>vec3.computeLength($vec3: Vector3): Float</sub>                                             |
| Compute Vector3 Squared Length                                                                   |
| <sub>vec3.computeLengthSquared($vec3: Vector3): Float</sub>                                      |
| Return Vector3 X Component                                                                       |
| <sub>vec3.getX($vec3: Vector3): Float</sub>                                                      |
| Return Vector3 Y Component                                                                       |
| <sub>vec3.getY($vec3: Vector3): Float</sub>                                                      |
| Return Vector3 Z Component                                                                       |
| <sub>vec3.getZ($vec3: Vector3): Float</sub>                                                      |
| Normalize Vector3                                                                                |
| <sub>vec3.normalize($vec3: Vector3): Vector3</sub>                                               |

## 6.17 Vector4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector4                                                                                   |
| <sub>vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4</sub>                             |
| Compute Vector4 Dot Product                                                                      |
| <sub>vec4.computeDotProduct($a: Vector4, $b: Vector4): Float</sub>                               |
| Compute Vector4 Length                                                                           |
| <sub>vec4.computeLength($vec4: Vector4): Float</sub>                                             |
| Compute Vector4 Squared Length                                                                   |
| <sub>vec4.computeLengthSquared($vec4: Vector4): Float</sub>                                      |
| Return Vector4 W Component                                                                       |
| <sub>vec4.getW($vec4: Vector4): Float</sub>                                                      |
| Return Vector4 X Component                                                                       |
| <sub>vec4.getX($vec4: Vector4): Float</sub>                                                      |
| Return Vector4 Y Component                                                                       |
| <sub>vec4.getY($vec4: Vector4): Float</sub>                                                      |
| Return Vector4 Z Component                                                                       |
| <sub>vec4.getZ($vec4: Vector4): Float</sub>                                                      |
| Normalize Vector4                                                                                |
| <sub>vec4.normalize($vec4: Vector4): Vector4</sub>                                               |

## 6.18 XML Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create XML Tag                                                                                   |
| <sub>xml.createTag($name: String[, $attributes: Map[, $innerXML: String]]): String</sub>         |

# 7. MiniScript Logic Methods

## 7.1 Audio Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Listener Orientation                                                                         |
| <sub>audio.getListenerOrientationAt(): Vector3</sub>                                             |
| Set Listener Orientation                                                                         |
| <sub>audio.setListenerOrientationAt($position: Vector3): Void</sub>                              |
| Get Listener Position                                                                            |
| <sub>audio.getListenerPosition(): Vector3</sub>                                                  |
| Set Listener Position                                                                            |
| <sub>audio.setListenerPosition($position: Vector3): Void</sub>                                   |
| Play Audio at Engine Entity Position                                                             |
| <sub>audio.play($id: String[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</sub>|
| Play Audio at Custom Position                                                                    |
| <sub>audio.playAtPosition($id: String, $position: Vector3[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</sub>|

## 7.2 Engine Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Id by Mouse Position                                                           |
| <sub>engine.getEntityIdByMousePosition($mouseX: Integer, $mouseY: Integer): String</sub>         |
| Get Engine Height                                                                                |
| <sub>engine.getHeight(): Integer</sub>                                                           |
| Compute Engine Screen Coordinate by World Coordinate                                             |
| <sub>engine.computeScreenCoordinateByWorldCoordinate($worldCoodinate: Vector3, =$screenCoordinate: Vector2): Boolean</sub>|
| Get Engine Width                                                                                 |
| <sub>engine.getWidth(): Integer</sub>                                                            |
| Compute Engine World Coordinate by Mouse Position                                                |
| <sub>engine.computeWorldCoordinateByMousePosition($mouseX: Integer, $mouseY: Integer): Vector3</sub>|
| Dump Engine Entities                                                                             |
| <sub>engine.dumpEntities(): Void</sub>                                                           |
| Dump Engine Shaders                                                                              |
| <sub>engine.dumpShaders(): Void</sub>                                                            |

## 7.3 Engine Camera Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Camera horizontal Field Of View                                                              |
| <sub>engine.camera.getFovX(): Float</sub>                                                        |
| Set Camera horizontal Field Of View                                                              |
| <sub>engine.camera.setFovX($fovX: Float): Void</sub>                                             |
| Get Camera Look At                                                                               |
| <sub>engine.camera.getLookAt(): Vector3</sub>                                                    |
| Set Camera Look At                                                                               |
| <sub>engine.camera.setLookAt($lookAt: Vector3): Void</sub>                                       |
| Get Camera Look From                                                                             |
| <sub>engine.camera.getLookFrom(): Vector3</sub>                                                  |
| Set Camera Look From                                                                             |
| <sub>engine.camera.setLookFrom($lookFrom: Vector3): Void</sub>                                   |
| Get Camera Up Vector                                                                             |
| <sub>engine.camera.getUpVector(): Vector3</sub>                                                  |
| Set Camera Up Vector                                                                             |
| <sub>engine.camera.setUpVector($upVector: Vector3): Void</sub>                                   |
| Compute Camera Up Vector                                                                         |
| <sub>engine.camera.computeUpVector($lookFrom: Vector3, $lookAt: Vector3): Vector3</sub>          |

## 7.4 Engine Entity Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Animation                                                                      |
| <sub>engine.entity.getAnimation($entityId: String[, $childEntityId: String]): String</sub>       |
| Set Engine Entity Animation                                                                      |
| <sub>engine.entity.setAnimation($entityId: String, $animation: String[, $speed: Float[, $childEntityId: String]]): Void</sub>|
| Get Engine Entity Animation Speed                                                                |
| <sub>engine.entity.setAnimationSpeed($entityId: String, $speed: Float[, $childEntityId: String]): Void</sub>|
| Set Engine Entity Animation Speed                                                                |
| <sub>engine.entity.getAnimationTime($entityId: String[, $childEntityId: String]): Float</sub>    |
| Get Engine Entity Additive Effect Color                                                          |
| <sub>engine.entity.getEffectColorAdd($entityId: String[, $childEntityId: String]): Vector4</sub> |
| Set Engine Entity Additive Effect Color                                                          |
| <sub>engine.entity.setEffectColorAdd($entityId: String, $effectColorAdd: Vector4[, $childEntityId: String]): Void</sub>|
| Get Engine Entity Multiplicative Effect Color                                                    |
| <sub>engine.entity.getEffectColorMul($entityId: String[, $childEntityId: String]): Vector4</sub> |
| Set Engine Entity Multiplicative Effect Color                                                    |
| <sub>engine.entity.setEffectColorMul($entityId: String, $effectColorMul: Vector4[, $childEntityId: String]): Void</sub>|
| Return if Engine Entity is enabled                                                               |
| <sub>engine.entity.isEnabled($entityId: String[, $childEntityId: String]): Boolean</sub>         |
| Set Engine Entity enabled/disabled                                                               |
| <sub>engine.entity.setEnabled($entityId: String, $enabled: Boolean[, $childEntityId: String]): Void</sub>|
| Get Engine Entity Node Transform                                                                 |
| <sub>engine.entity.getNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Transform</sub>|
| Set Engine Entity Node Transform                                                                 |
| <sub>engine.entity.setNodeTransform($entityId: String, $nodeId: String, $transform: Transform[, $childEntityId: String]): Void</sub>|
| Unset Engine Entity Node Transform                                                               |
| <sub>engine.entity.unsetNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Void</sub>|
| Get Engine Entity Node Transform Matrix                                                          |
| <sub>engine.entity.getNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Matrix4x4</sub>|
| Set Engine Entity Node Transform Matrix                                                          |
| <sub>engine.entity.setNodeTransformMatrix($entityId: String, $nodeId: String, $matrix: Matrix4x4[, $childEntityId: String]): Void</sub>|
| Unset Engine Entity Node Transform Matrix                                                        |
| <sub>engine.entity.unsetNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Void</sub>|
| Return if Engine Entity has specific Overlay Animation                                           |
| <sub>engine.entity.hasOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Boolean</sub>|
| Return Engine Entity Overlay Animation Playback Time from 0.0 until 1.0                          |
| <sub>engine.entity.getOverlayAnimationTime($entityId: String, $animation: String[, $childEntityId: String]): Float</sub>|
| Return if Engine Entity is Pickable                                                              |
| <sub>engine.entity.isPickable($entityId: String[, $childEntityId: String]): Boolean</sub>        |
| Set Engine Entity Pickable                                                                       |
| <sub>engine.entity.setPickable($entityId: String, $pickable: Boolean[, $childEntityId: String]): Void</sub>|
| Get Engine Entity Transform                                                                      |
| <sub>engine.entity.getTransform($entityId: String[, $childEntityId: String]): Transform</sub>    |
| Set Engine Entity Transform                                                                      |
| <sub>engine.entity.setTransform($entityId: String, $transform: Transform[, $childEntityId: String]): Void</sub>|
| Add Engine Entity Overlay Animation                                                              |
| <sub>engine.entity.addOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</sub>|
| Emit Engine Entity Particles                                                                     |
| <sub>engine.entity.emitParticles($entityId: String[, $childEntityId: String]): Integer</sub>     |
| Remove finished Overlay Animations                                                               |
| <sub>engine.entity.removeFinishedOverlayAnimations($entityId: String[, $childEntityId: String]): Void</sub>|
| Remove specific Overlay Animation                                                                |
| <sub>engine.entity.removeOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</sub>|
| Remove Overlay Animations                                                                        |
| <sub>engine.entity.removeOverlayAnimations($entityId: String[, $childEntityId: String]): Void</sub>|

## 7.5 Engine Timing Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Timing Avarage FPS                                                                    |
| <sub>engine.timing.getAvarageFPS(): Float</sub>                                                  |
| Get Engine Timing Frame Delta Time in Milliseconds                                               |
| <sub>engine.timing.getDeltaTime(): Integer</sub>                                                 |
| Get Engine Timing Frame Delta Time in Seconds                                                    |
| <sub>engine.timing.getDeltaTimeSeconds(): Float</sub>                                            |

## 7.6 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <sub>input.keyboard.isAltDown(): Boolean</sub>                                                   |
| Returns if specific Character is currently pressed                                               |
| <sub>input.keyboard.isCharDown($charAsString: String): Boolean</sub>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <sub>input.keyboard.isControlDown(): Boolean</sub>                                               |
| Backspace Key Keycode                                                                            |
| <sub>input.keyboard.KEYCODE_BACKSPACE(): Integer</sub>                                           |
| Delete Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_DELETE(): Integer</sub>                                              |
| Down Key Keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_DOWN(): Integer</sub>                                                |
| End Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_END(): Integer</sub>                                                 |
| Escape Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_ESCAPE(): Integer</sub>                                              |
| F1 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F1(): Integer</sub>                                                  |
| F10 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F10(): Integer</sub>                                                 |
| F11 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F11(): Integer</sub>                                                 |
| F12 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F12(): Integer</sub>                                                 |
| F2 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F2(): Integer</sub>                                                  |
| F3 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F3(): Integer</sub>                                                  |
| F4 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F4(): Integer</sub>                                                  |
| F5 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F5(): Integer</sub>                                                  |
| F6 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F6(): Integer</sub>                                                  |
| F7 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F7(): Integer</sub>                                                  |
| F8 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F8(): Integer</sub>                                                  |
| F9 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F9(): Integer</sub>                                                  |
| Left Key Keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_LEFT(): Integer</sub>                                                |
| Page Down Key Keycode                                                                            |
| <sub>input.keyboard.KEYCODE_PAGEDOWN(): Integer</sub>                                            |
| Page Up Key Keycode                                                                              |
| <sub>input.keyboard.KEYCODE_PAGEUP(): Integer</sub>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <sub>input.keyboard.KEYCODE_POS1(): Integer</sub>                                                |
| Return Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_RETURN(): Integer</sub>                                              |
| Right Key Keycode                                                                                |
| <sub>input.keyboard.KEYCODE_RIGHT(): Integer</sub>                                               |
| Space Key Keycode                                                                                |
| <sub>input.keyboard.KEYCODE_SPACE(): Integer</sub>                                               |
| Up Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_UP(): Integer</sub>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <sub>input.keyboard.isKeyDown($keyCode: Integer): Boolean</sub>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <sub>input.keyboard.isMetaDown(): Boolean</sub>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <sub>input.keyboard.isShiftDown(): Boolean</sub>                                                 |
| Returns last typed String                                                                        |
| <sub>input.keyboard.getTypedString(): String</sub>                                               |

## 7.7 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <sub>input.mouse.BUTTON_LEFT(): Integer</sub>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <sub>input.mouse.BUTTON_MIDDLE(): Integer</sub>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <sub>input.mouse.BUTTON_RIGHT(): Integer</sub>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <sub>input.mouse.isButtonDown($button: Integer): Boolean</sub>                                   |
| Returns if specific Mouse Button has been released                                               |
| <sub>input.mouse.isButtonUp($button: Integer): Boolean</sub>                                     |
| Returns if Mouse is dragging currently                                                           |
| <sub>input.mouse.isDragging($button: Integer): Boolean</sub>                                     |
| Returns if Mouse has been moved                                                                  |
| <sub>input.mouse.hasMoved(): Boolean</sub>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelX(): Float</sub>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelY(): Float</sub>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelZ(): Float</sub>                                                        |
| Get X Mouse Position                                                                             |
| <sub>input.mouse.getX(): Integer</sub>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <sub>input.mouse.getXUnscaled(): Integer</sub>                                                   |
| Get Y Mouse Position                                                                             |
| <sub>input.mouse.getY(): Integer</sub>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <sub>input.mouse.getYUnscaled(): Integer</sub>                                                   |

## 7.8 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function                                                                    |
| <sub>logic.has($logicId: String, $function: String): Boolean</sub>                               |
| Get Hierarchy Id                                                                                 |
| <sub>logic.getHierarchyId(): String</sub>                                                        |
| Get Hierarchy Parent Id                                                                          |
| <sub>logic.getHierarchyParentId(): String</sub>                                                  |
| Get Logic Id                                                                                     |
| <sub>logic.getId(): String</sub>                                                                 |
| Call specific Logic Function                                                                     |
| <sub>logic.call($logicId: String, $function: String, ...): Mixed</sub>                           |

## 7.9 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Signal has been sent                                                                  |
| <sub>logic.signal.has(): Boolean</sub>                                                           |
| Get Signal Argument                                                                              |
| <sub>logic.signal.getArgument($argumentIndex: Integer): Mixed</sub>                              |
| Get Signal Name                                                                                  |
| <sub>logic.signal.getName(): String</sub>                                                        |
| Advance to next Signal                                                                           |
| <sub>logic.signal.next(): Void</sub>                                                             |
| Send Signal                                                                                      |
| <sub>logic.signal.send($logicId: String, $signal: String, ...): Void</sub>                       |

## 7.10 PathFinding Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Pathfinding Idle State Integer Code                                                              |
| <sub>pathfinding.STATE_IDLE(): Integer</sub>                                                     |
| Pathfinding Computing State Integer Code                                                         |
| <sub>pathfinding.STATE_PATHFINDING(): Integer</sub>                                              |
| Pathfinding Failed State Integer Code                                                            |
| <sub>pathfinding.STATE_PATHFINDING_FAILED(): Integer</sub>                                       |
| Pathfinding Computing Other Pathfinding Integer Code                                             |
| <sub>pathfinding.STATE_PATHFINDING_OTHER(): Integer</sub>                                        |
| Pathfinding Success State Integer Code                                                           |
| <sub>pathfinding.STATE_PATHFINDING_SUCCESS(): Integer</sub>                                      |
| Pathfinding Try/Lock Failed Integer Code                                                         |
| <sub>pathfinding.STATE_TRYLOCK_FAILED(): Integer</sub>                                           |
| Issue Pathfinding                                                                                |
| <sub>pathfinding.findPath($logicId: String, $startPosition: Vector3, $endPosition: Vector3, =$path: Array): Integer</sub>|

## 7.11 Scene Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Scene Depth                                                                                  |
| <sub>scene.getDepth(): Float</sub>                                                               |
| Get Scene Height                                                                                 |
| <sub>scene.getHeight(): Float</sub>                                                              |
| Get Scene Width                                                                                  |
| <sub>scene.getWidth(): Float</sub>                                                               |

## 7.12 SceneConnector Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Attach Prototype to the Logic Hierarchy                                                          |
| <sub>sceneconnector.attachPrototype($pathName: String, $fileName: String, $id: String, $attachNodeId: String, $transform: Transform[, $parentId: String]): Void</sub>|
| Spawn Prototype in Scene                                                                         |
| <sub>sceneconnector.spawnPrototype($pathName: String, $fileName: String, $id: String, $transform: Transform[, $hierarchyId: String[, $hierarchyParentId: String]]): Void</sub>|

## 7.13 Physics World Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Determine Height at specific Position in Physics World                                           |
| <sub>world.determineHeight($collisionTypeIds: Integer, $stepUpMax: Float, $point: Vector3, =$heightPoint: Vector3[, =$bodyId: String[, $minHeight: Float[, $maxHeight: Float]]]): Boolean</sub>|
| Determine Collision of Two Specific Bodies in Physics World                                      |
| <sub>world.doCollide($bodyId1: String, $bodyId2: String): Boolean</sub>                          |
| Compute Ray Casting in Physics World                                                             |
| <sub>world.doRayCasting($collisionTypeIds: Integer, $start: Vector3, $end: Vector3, =$hitPoint: Vector3[, =$bodyId: String[, $actorId: String]]): Boolean</sub>|
| Determine Collision of Specific Body in Physics World                                            |
| <sub>world.doesCollideWith($collisionTypeIds: Integer, $bodyId: String): Array</sub>             |

## 7.14 Physics World Body Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Physics World Entity Angular Damping                                                         |
| <sub>world.body.getAngularDamping($bodyId: String): Float</sub>                                  |
| Set Physics World Entity Angular Damping                                                         |
| <sub>world.body.setAngularDamping($bodyId: String, $angularDamping: Float): Void</sub>           |
| Get Physics World Entity Angular Velocity                                                        |
| <sub>world.body.getAngularVelocity($bodyId: String): Vector3</sub>                               |
| Set Physics World Entity Angular Velocity                                                        |
| <sub>world.body.setAngularVelocity($bodyId: String, $angularVelocity: Vector3): Void</sub>       |
| Returns Physics World Collision Type Id 10                                                       |
| <sub>world.body.COLLISION_TYPEID_10(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 11                                                       |
| <sub>world.body.COLLISION_TYPEID_11(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 12                                                       |
| <sub>world.body.COLLISION_TYPEID_12(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 13                                                       |
| <sub>world.body.COLLISION_TYPEID_13(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 14                                                       |
| <sub>world.body.COLLISION_TYPEID_14(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 15                                                       |
| <sub>world.body.COLLISION_TYPEID_15(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 16                                                       |
| <sub>world.body.COLLISION_TYPEID_16(): Integer</sub>                                             |
| Returns Physics World Collision Type Id 3                                                        |
| <sub>world.body.COLLISION_TYPEID_3(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 4                                                        |
| <sub>world.body.COLLISION_TYPEID_4(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 5                                                        |
| <sub>world.body.COLLISION_TYPEID_5(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 6                                                        |
| <sub>world.body.COLLISION_TYPEID_6(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 7                                                        |
| <sub>world.body.COLLISION_TYPEID_7(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 8                                                        |
| <sub>world.body.COLLISION_TYPEID_8(): Integer</sub>                                              |
| Returns Physics World Collision Type Id 9                                                        |
| <sub>world.body.COLLISION_TYPEID_9(): Integer</sub>                                              |
| Returns All Physics World Collision Type Ids                                                     |
| <sub>world.body.COLLISION_TYPEID_ALL(): Integer</sub>                                            |
| Returns Dynamic Physics World Collision Type Id                                                  |
| <sub>world.body.COLLISION_TYPEID_DYNAMIC(): Integer</sub>                                        |
| Returns Static Physics World Collision Type Id                                                   |
| <sub>world.body.COLLISION_TYPEID_STATIC(): Integer</sub>                                         |
| Get Physics World Entity own Collision Type Id                                                   |
| <sub>world.body.getCollisionTypeId($bodyId: String): Integer</sub>                               |
| Set Physics World Entity own Collision Type Id                                                   |
| <sub>world.body.setCollisionTypeId($bodyId: String, $collisionTypeId: Integer): Void</sub>       |
| Get Physics World Entity enabled Collision Type Ids                                              |
| <sub>world.body.getCollisionTypeIds($bodyId: String): Integer</sub>                              |
| Set Physics World Entity enabled Collision Type Ids                                              |
| <sub>world.body.setCollisionTypeIds($bodyId: String, $collisionTypeIds: Integer): Void</sub>     |
| Returns if Physics World Entity is enabled                                                       |
| <sub>world.body.isEnabled($bodyId: String): Boolean</sub>                                        |
| Set Physics World Entity enabled/disabled                                                        |
| <sub>world.body.setEnabled($bodyId: String, $enabled: Boolean): Void</sub>                       |
| Get Physics World Entity Linear Damping                                                          |
| <sub>world.body.getLinearDamping($bodyId: String): Float</sub>                                   |
| Set Physics World Entity Linear Damping                                                          |
| <sub>world.body.setLinearDamping($bodyId: String, $linearDamping: Float): Void</sub>             |
| Get Physics World Entity Linear Velocity                                                         |
| <sub>world.body.getLinearVelocity($bodyId: String): Vector3</sub>                                |
| Set Physics World Entity Linear Velocity                                                         |
| <sub>world.body.setLinearVelocity($bodyId: String, $linearVelocity: Vector3): Void</sub>         |
| Returns Physics World Dynamic Collision Body Type Integer Code                                   |
| <sub>world.body.TYPE_COLLISION_DYNAMIC(): Integer</sub>                                          |
| Returns Physics World Static Collision Body Type Integer Code                                    |
| <sub>world.body.TYPE_COLLISION_STATIC(): Integer</sub>                                           |
| Returns Physics World Dynamic Rigid Body Type Integer Code                                       |
| <sub>world.body.TYPE_DYNAMIC(): Integer</sub>                                                    |
| Returns Physics World Static Rigid Body Type Integer Code                                        |
| <sub>world.body.TYPE_STATIC(): Integer</sub>                                                     |
| Get Physics World Entity Transform                                                               |
| <sub>world.body.getTransform($bodyId: String): Transform</sub>                                   |
| Set Physics World Entity Transform                                                               |
| <sub>world.body.setTransform($bodyId: String, $transform: Transform): Void</sub>                 |
| Get Physics World Entity Body Type Integer Code                                                  |
| <sub>world.body.getType($bodyId: String): Integer</sub>                                          |
| Add Force to Physics World Entity                                                                |
| <sub>world.body.addForce($bodyId: String, $force: Vector3[, $origin: Vector3]): Void</sub>       |
| Add Torque to Physics World Entity                                                               |
| <sub>world.body.addTorque($bodyId: String, $torque: Vector3): Void</sub>                         |

# 8. MiniScript GUI Methods

## 8.1 Element Node Condition Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if GUI Element Node has a specific Condition enabled                                     |
| <sub>gui.elementnode.conditions.has($elementNodeId: String, $condition: String): Boolean</sub>   |
| Get enabled GUI Element Node Conditions                                                          |
| <sub>gui.elementnode.conditions.get($elementNodeId: String): Array</sub>                         |
| Set enabled GUI Element Node Condition                                                           |
| <sub>gui.elementnode.conditions.set($elementNodeId: String, $condition: String): Void</sub>      |
| Set Array of enabled GUI Element Node Conditions                                                 |
| <sub>gui.elementnode.conditions.setAll($elementNodeId: String, $conditions: Array): Void</sub>   |
| Add enabled GUI Element Node Condition                                                           |
| <sub>gui.elementnode.conditions.add($elementNodeId: String, $condition: String): Void</sub>      |
| Remove enabled GUI Element Node Condition                                                        |
| <sub>gui.elementnode.conditions.remove($elementNodeId: String, $condition: String): Void</sub>   |
| Remove All enabled GUI Element Node Conditions                                                   |
| <sub>gui.elementnode.conditions.removeAll($elementNodeId: String): Void</sub>                    |

## 8.2 Event Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns GUI Event Performed Action Type Integer Code                                             |
| <sub>gui.event.ACTIONTYPE_PERFORMED(): Integer</sub>                                             |
| Returns GUI Event Performing Action Type Integer Code                                            |
| <sub>gui.event.ACTIONTYPE_PERFORMING(): Integer</sub>                                            |

## 8.3 Image Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Image Source of GUI Image Node                                                               |
| <sub>gui.imagenode.getSource($imageNodeId: String): String</sub>                                 |
| Set Image Source of GUI Image Node                                                               |
| <sub>gui.imagenode.setSource($imageNodeId: String, $source: String): Void</sub>                  |

## 8.4 Node Controller Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get GUI Node Controller Value                                                                    |
| <sub>gui.node.controller.getValue($nodeId: String): String</sub>                                 |
| Set GUI Node Controller Value                                                                    |
| <sub>gui.node.controller.setValue($nodeId: String, $value: String): Void</sub>                   |

## 8.5 Parent Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Add Sub Nodes using XML to GUI Parent Node                                                       |
| <sub>gui.parentnode.addSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</sub>|
| Clear Sub Nodes of GUI Parent Node                                                               |
| <sub>gui.parentnode.clearSubNodes($parentNodeId: String): Void</sub>                             |
| Replace Sub Nodes using XML of GUI Parent Node                                                   |
| <sub>gui.parentnode.replaceSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</sub>|

## 8.6 Screen Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Return if GUI Screen is enabled                                                                  |
| <sub>gui.screen.isEnabled($screenId: String): Boolean</sub>                                      |
| Set GUI Screen enabled/disabled                                                                  |
| <sub>gui.screen.setEnabled($screenId: String, $enabled: Boolean): Void</sub>                     |
| Call specific Screen Logic Function                                                              |
| <sub>gui.screen.call($screenId: String, $function: String, ...): Mixed</sub>                     |
| Goto current Screen to specific Screen                                                           |
| <sub>gui.screen.goto($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</sub>      |
| Pop current Screen from Screen Stack                                                             |
| <sub>gui.screen.pop(): Void</sub>                                                                |
| Push Screen to current Screen Stack                                                              |
| <sub>gui.screen.push($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</sub>      |

## 8.7 Screen Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Current Screen Node Id                                                                       |
| <sub>gui.screennode.getId(): String</sub>                                                        |

## 8.8 Text Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Text of GUI Text Node                                                                        |
| <sub>gui.textnode.getText($textNodeId: String): String</sub>                                     |
| Set Text of GUI Text Node                                                                        |
| <sub>gui.textnode.setText($textNodeId: String, $text: String): Void</sub>                        |

## 8.9 Video Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Video Source of GUI Video Node                                                               |
| <sub>gui.videonode.getSource($videoNodeId: String): String</sub>                                 |
| Set Video Source of GUI Video Node                                                               |
| <sub>gui.videonode.setSource($videoNodeId: String, $source: String): Void</sub>                  |

## 8.10 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <sub>input.keyboard.isAltDown(): Boolean</sub>                                                   |
| Returns if specific Character is currently pressed                                               |
| <sub>input.keyboard.isCharDown($charAsString: String): Boolean</sub>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <sub>input.keyboard.isControlDown(): Boolean</sub>                                               |
| Backspace Key Keycode                                                                            |
| <sub>input.keyboard.KEYCODE_BACKSPACE(): Integer</sub>                                           |
| Delete Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_DELETE(): Integer</sub>                                              |
| Down Key Keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_DOWN(): Integer</sub>                                                |
| End Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_END(): Integer</sub>                                                 |
| Escape Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_ESCAPE(): Integer</sub>                                              |
| F1 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F1(): Integer</sub>                                                  |
| F10 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F10(): Integer</sub>                                                 |
| F11 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F11(): Integer</sub>                                                 |
| F12 Key Keycode                                                                                  |
| <sub>input.keyboard.KEYCODE_F12(): Integer</sub>                                                 |
| F2 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F2(): Integer</sub>                                                  |
| F3 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F3(): Integer</sub>                                                  |
| F4 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F4(): Integer</sub>                                                  |
| F5 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F5(): Integer</sub>                                                  |
| F6 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F6(): Integer</sub>                                                  |
| F7 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F7(): Integer</sub>                                                  |
| F8 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F8(): Integer</sub>                                                  |
| F9 Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_F9(): Integer</sub>                                                  |
| Left Key Keycode                                                                                 |
| <sub>input.keyboard.KEYCODE_LEFT(): Integer</sub>                                                |
| Page Down Key Keycode                                                                            |
| <sub>input.keyboard.KEYCODE_PAGEDOWN(): Integer</sub>                                            |
| Page Up Key Keycode                                                                              |
| <sub>input.keyboard.KEYCODE_PAGEUP(): Integer</sub>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <sub>input.keyboard.KEYCODE_POS1(): Integer</sub>                                                |
| Return Key Keycode                                                                               |
| <sub>input.keyboard.KEYCODE_RETURN(): Integer</sub>                                              |
| Right Key Keycode                                                                                |
| <sub>input.keyboard.KEYCODE_RIGHT(): Integer</sub>                                               |
| Space Key Keycode                                                                                |
| <sub>input.keyboard.KEYCODE_SPACE(): Integer</sub>                                               |
| Up Key Keycode                                                                                   |
| <sub>input.keyboard.KEYCODE_UP(): Integer</sub>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <sub>input.keyboard.isKeyDown($keyCode: Integer): Boolean</sub>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <sub>input.keyboard.isMetaDown(): Boolean</sub>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <sub>input.keyboard.isShiftDown(): Boolean</sub>                                                 |
| Returns last typed String                                                                        |
| <sub>input.keyboard.getTypedString(): String</sub>                                               |

## 8.11 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <sub>input.mouse.BUTTON_LEFT(): Integer</sub>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <sub>input.mouse.BUTTON_MIDDLE(): Integer</sub>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <sub>input.mouse.BUTTON_RIGHT(): Integer</sub>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <sub>input.mouse.isButtonDown($button: Integer): Boolean</sub>                                   |
| Returns if specific Mouse Button has been released                                               |
| <sub>input.mouse.isButtonUp($button: Integer): Boolean</sub>                                     |
| Returns if Mouse is dragging currently                                                           |
| <sub>input.mouse.isDragging($button: Integer): Boolean</sub>                                     |
| Returns if Mouse has been moved                                                                  |
| <sub>input.mouse.hasMoved(): Boolean</sub>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelX(): Float</sub>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelY(): Float</sub>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <sub>input.mouse.getWheelZ(): Float</sub>                                                        |
| Get X Mouse Position                                                                             |
| <sub>input.mouse.getX(): Integer</sub>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <sub>input.mouse.getXUnscaled(): Integer</sub>                                                   |
| Get Y Mouse Position                                                                             |
| <sub>input.mouse.getY(): Integer</sub>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <sub>input.mouse.getYUnscaled(): Integer</sub>                                                   |

## 8.12 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function                                                                    |
| <sub>logic.has($logicId: String, $function: String): Boolean</sub>                               |
| Call specific Logic Function                                                                     |
| <sub>logic.call($logicId: String, $function: String, ...): Mixed</sub>                           |

## 8.13 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Send Signal                                                                                      |
| <sub>logic.signal.send($logicId: String, $signal: String, ...): Void</sub>                       |

# 9. Operators

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
