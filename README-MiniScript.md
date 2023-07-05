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
| <small>getVariable($variable: String): Mixed</small>                                                 |
| Set Variable                                                                                     |
| <small>setVariable($variable: String, $value: Mixed): Mixed</small>                                  |
| Unset Variable                                                                                   |
| <small>unsetVariable($variable: String): Void</small>                                                |
| Add                                                                                              |
| <small>add($a: Mixed, $b: Mixed): Mixed</small>                                                      |
| Logical And                                                                                      |
| <small>and($a: Boolean, $b: Boolean): Boolean</small>                                                |
| Bitwise And                                                                                      |
| <small>bitwiseAnd($a: Integer, $b: Integer): Integer</small>                                         |
| Bitwise Not                                                                                      |
| <small>bitwiseNot($value: Integer): Integer</small>                                                  |
| Bitwise Or                                                                                       |
| <small>bitwiseOr($a: Integer, $b: Integer): Integer</small>                                          |
| Bitwise Xor                                                                                      |
| <small>bitwiseXor($a: Integer, $b: Integer): Integer</small>                                         |
| Create Bool                                                                                      |
| <small>bool($bool: Boolean): Boolean</small>                                                         |
| Divide                                                                                           |
| <small>div($a: Mixed, $b: Mixed): Mixed</small>                                                      |
| Else                                                                                             |
| <small>else(): Void</small>                                                                          |
| Else If                                                                                          |
| <small>elseif($condition: Boolean): Void</small>                                                     |
| End                                                                                              |
| <small>end(): Void</small>                                                                           |
| Equals                                                                                           |
| <small>equals($a: Mixed, $b: Mixed): Boolean</small>                                                 |
| Create Float                                                                                     |
| <small>float($float: Float): Float</small>                                                           |
| For Condition                                                                                    |
| <small>forCondition($condition: Boolean): Void</small>                                               |
| For Time                                                                                         |
| <small>forTime($time: Integer): Void</small>                                                         |
| Greater                                                                                          |
| <small>greater($a: Mixed, $b: Mixed): Boolean</small>                                                |
| Greater Equals                                                                                   |
| <small>greaterEquals($a: Mixed, $b: Mixed): Boolean</small>                                          |
| If                                                                                               |
| <small>if($condition: Boolean): Void</small>                                                         |
| Create Integer                                                                                   |
| <small>int($int: Integer): Integer</small>                                                           |
| Lesser                                                                                           |
| <small>lesser($a: Mixed, $b: Mixed): Boolean</small>                                                 |
| Lesser Equals                                                                                    |
| <small>lesserEquals($a: Mixed, $b: Mixed): Boolean</small>                                           |
| Compute Modulo                                                                                   |
| <small>mod($value: Number, $range: Number): Number</small>                                           |
| Multiply                                                                                         |
| <small>mul($a: Mixed, $b: Mixed): Mixed</small>                                                      |
| Logical Not                                                                                      |
| <small>not($bool: Boolean): Boolean</small>                                                          |
| Logical Not Equal                                                                                |
| <small>notEqual($a: Mixed, $b: Mixed): Boolean</small>                                               |
| Logical Or                                                                                       |
| <small>or($a: Boolean, $b: Boolean): Boolean</small>                                                 |
| Prefix Decrement                                                                                 |
| <small>prefixDecrement(=$variable: Integer): Integer</small>                                         |
| Prefix Increment                                                                                 |
| <small>prefixIncrement(=$variable: Integer): Integer</small>                                         |
| Return from Function with optional Return Value                                                  |
| <small>return([$value: Mixed]): Void</small>                                                         |
| Subtract                                                                                         |
| <small>sub($a: Mixed, $b: Mixed): Mixed</small>                                                      |

## 6.2 Array Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Array                                                                                     |
| <small>array(...): Array</small>                                                                     |
| Get Array Entry                                                                                  |
| <small>array.get($array: Array, $index: Integer): Mixed</small>                                      |
| Set Array Entry                                                                                  |
| <small>array.set(=$array: Array, $index: Integer, $value: Mixed): Void</small>                       |
| Get Array Index by Value                                                                         |
| <small>array.indexOf($array: Array, $value: String[, $beginIndex: Integer]): Integer</small>         |
| Get Array Length                                                                                 |
| <small>array.length($array: Array): Integer</small>                                                  |
| Add to Array                                                                                     |
| <small>array.push(=$array: Array, ...): Void</small>                                                 |
| Remove Array by Index                                                                            |
| <small>array.remove(=$array: Array, $index: Integer): Void</small>                                   |
| Remove Array Entry by Value                                                                      |
| <small>array.removeOf(=$array: Array, $value: String[, $beginIndex: Integer]): Void</small>          |
| Reverse Array                                                                                    |
| <small>array.reverse(=$array: Array): Void</small>                                                   |
| Sort Array                                                                                       |
| <small>array.sort(=$array: Array, $function: String): Void</small>                                   |

## 6.3 Console Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Print to Console                                                                                 |
| <small>console.log(...): Void</small>                                                                |

## 6.4 JSON Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Deserialize JSON                                                                                 |
| <small>json.deserialize($json: String): Mixed</small>                                                |
| Serialize JSON                                                                                   |
| <small>json.serialize($value: Mixed): String</small>                                                 |

## 6.5 Map Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Map                                                                                       |
| <small>map(): Map</small>                                                                            |
| Has Entry by Key                                                                                 |
| <small>map.has($map: Map, $key: String): Boolean</small>                                             |
| Get Map Value by Key                                                                             |
| <small>map.get($map: Map, $key: String): Mixed</small>                                               |
| Set Map Entry                                                                                    |
| <small>map.set(=$map: Map, $key: String, $value: Mixed): Void</small>                                |
| Get Map Keys                                                                                     |
| <small>map.getKeys($map: Map): Array</small>                                                         |
| Get Map Values                                                                                   |
| <small>map.getValues($map: Map): Array</small>                                                       |
| Remove Map Entry                                                                                 |
| <small>map.remove(=$map: Map, $key: String): Void</small>                                            |

## 6.6 Matrix3x3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Identity 3x3 Matrix                                                                       |
| <small>mat3.identity(): Matrix3x3</small>                                                            |
| Multiply 3x3 Matrix with 3x3 Matrix or Vector2                                                   |
| <small>mat3.multiply($mat3: Matrix3x3, ...): Mixed</small>                                           |
| Create Rotation 3x3 Matrix                                                                       |
| <small>mat3.rotate($angle: Float): Matrix3x3</small>                                                 |
| Create 3x3 Matrix which rotates around Point                                                     |
| <small>mat3.rotateAroundPoint($point: Vector2, $angle: Float): Matrix3x3</small>                     |
| Create 3x3 Matrix which rotates around Texture Center                                            |
| <small>mat3.rotateAroundTextureCenter($angle: Float): Matrix3x3</small>                              |
| Create Scale 3x3 Matrix                                                                          |
| <small>mat3.scale(...): Matrix3x3</small>                                                            |
| Create Translation 3x3 Matrix                                                                    |
| <small>mat3.translate($translation: Vector2): Matrix3x3</small>                                      |

## 6.7 Matrix4x4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from 4x4 Matrix                                                             |
| <small>mat4.computeEulerAngles($mat4: Matrix4x4): Vector3</small>                                    |
| Create Identity 4x4 Matrix                                                                       |
| <small>mat4.identity(): Matrix4x4</small>                                                            |
| Create 4x4 Matrix Inverse                                                                        |
| <small>mat4.invert($mat4: Matrix4x4): Matrix4x4</small>                                              |
| Multiply 4x4 Matrix with 4x4 Matrix or Vector3 or Vector4                                        |
| <small>mat4.multiply($mat4: Matrix4x4, ...): Mixed</small>                                           |
| Create Rotation 4x4 Matrix                                                                       |
| <small>mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4</small>                                 |
| Create Scale 4x4 Matrix                                                                          |
| <small>mat4.scale(...): Matrix4x4</small>                                                            |
| Create Translation 4x4 Matrix                                                                    |
| <small>mat4.translate($translation: Vector3): Matrix4x4</small>                                      |

## 6.8 Math Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Degree to Radian Factor                                                                          |
| <small>math.DEG2RAD(): Float</small>                                                                 |
| Epsilon                                                                                          |
| <small>math.EPSILON(): Float</small>                                                                 |
| G                                                                                                |
| <small>math.G(): Float</small>                                                                       |
| PI                                                                                               |
| <small>math.PI(): Float</small>                                                                      |
| Return Number as Positive Number                                                                 |
| <small>math.abs($value: Number): Number</small>                                                      |
| Return Number to be Positive within given Range                                                  |
| <small>math.absmod($value: Number, $range: Number): Number</small>                                   |
| Compute acos                                                                                     |
| <small>math.acos($value: Float): Float</small>                                                       |
| Compute asin                                                                                     |
| <small>math.asin($value: Float): Float</small>                                                       |
| Compute atan                                                                                     |
| <small>math.atan($value: Float): Float</small>                                                       |
| Compute atan2                                                                                    |
| <small>math.atan2($y: Float, $x: Float): Float</small>                                               |
| Round Float up to next higher Integer                                                            |
| <small>math.ceil($value: Float): Float</small>                                                       |
| Return Number clamped to be in given Range                                                       |
| <small>math.clamp($value: Number, $min: Number, $max: Number): Number</small>                        |
| Compute acos                                                                                     |
| <small>math.cos($value: Float): Float</small>                                                        |
| Compute exp                                                                                      |
| <small>math.exp($value: Float): Float</small>                                                        |
| Round Float down to next lower Integer                                                           |
| <small>math.floor($value: Float): Float</small>                                                      |
| Compute log                                                                                      |
| <small>math.log($value: Float): Float</small>                                                        |
| Return maximum Number of given Values                                                            |
| <small>math.max($a: Number, $b: Number): Number</small>                                              |
| Return minimum Number of given Values                                                            |
| <small>math.min($a: Number, $b: Number): Number</small>                                              |
| Compute Modulo/Remainder                                                                         |
| <small>math.mod($value: Number, $range: Number): Number</small>                                      |
| Compute pow                                                                                      |
| <small>math.pow($a: Number, $b: Number): Number</small>                                              |
| Create a random Number between 0.0 and 1.0                                                       |
| <small>math.random(): Float</small>                                                                  |
| Round Float Up or Down to Integer                                                                |
| <small>math.round($value: Float): Float</small>                                                      |
| Return Sign of given Number                                                                      |
| <small>math.sign($value: Number): Number</small>                                                     |
| Compute sin                                                                                      |
| <small>math.sin($value: Float): Float</small>                                                        |
| Compute Square Root                                                                              |
| <small>math.sqrt($value: Float): Float</small>                                                       |
| Compute Square Product                                                                           |
| <small>math.square($value: Number): Number</small>                                                   |
| Compute tan                                                                                      |
| <small>math.tan($value: Float): Float</small>                                                        |

## 6.9 Quaternion Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from Quaternion                                                             |
| <small>quaternion.computeEulerAngles($quaternion: Quaternion): Vector3</small>                       |
| Compute 4x4 Rotation Matrix from Quaternion                                                      |
| <small>quaternion.computeMatrix($quaternion: Quaternion): Matrix4x4</small>                          |
| Create Identity Quaternion                                                                       |
| <small>quaternion.identity(): Quaternion</small>                                                     |
| Create Quaternion Inverse                                                                        |
| <small>quaternion.invert($quaternion: Quaternion): Quaternion</small>                                |
| Multiply Quaternion with Quaternion or Vector3                                                   |
| <small>quaternion.multiply($quaternion: Quaternion, ...): Mixed</small>                              |
| Normalize Quaternion                                                                             |
| <small>quaternion.normalize($quaternion: Quaternion): Quaternion</small>                             |
| Create Rotation Quaternion                                                                       |
| <small>quaternion.rotate($axis: Vector3, $angle: Float): Quaternion</small>                          |

## 6.10 Script Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Named Conditions                                                                             |
| <small>script.getNamedConditions(): String</small>                                                   |
| Get Script Variables                                                                             |
| <small>script.getVariables(): Map</small>                                                            |
| Call Script Function                                                                             |
| <small>script.call($function: String, ...): Mixed</small>                                            |
| Disable a specific Named Condition                                                               |
| <small>script.disableNamedCondition($name: String): Void</small>                                     |
| Emit a Condition                                                                                 |
| <small>script.emit($condition: String): Void</small>                                                 |
| Enable a specific Named Condition                                                                |
| <small>script.enableNamedCondition($name: String): Void</small>                                      |
| Evaluate a Script Statement                                                                      |
| <small>script.evaluate($statement: String): Mixed</small>                                            |
| Stop Script                                                                                      |
| <small>script.stop(): Void</small>                                                                   |
| Wait for given Milliseconds                                                                      |
| <small>script.wait($time: Integer): Void</small>                                                     |
| Wait for Condition to happen                                                                     |
| <small>script.waitForCondition(): Void</small>                                                       |

## 6.11 Set Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Set                                                                                       |
| <small>set(): Set</small>                                                                            |
| Has Key in Set                                                                                   |
| <small>set.has($set: Set, $key: String): Boolean</small>                                             |
| Get Set Keys                                                                                     |
| <small>set.getKeys($set: Set): Array</small>                                                         |
| Insert Key into Set                                                                              |
| <small>set.insert(=$set: Set, $key: String): Void</small>                                            |
| Remove Key from Set                                                                              |
| <small>set.remove(=$set: Set, $key: String): Void</small>                                            |

## 6.12 String Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create String                                                                                    |
| <small>string($string: String): String</small>                                                       |
| Test if String Value is Empty                                                                    |
| <small>string.isEmpty($string: String): Boolean</small>                                              |
| Test if String Value is a Float Number                                                           |
| <small>string.isFloat($string: String): Boolean</small>                                              |
| Test if String Value is a Integer Number                                                         |
| <small>string.isInteger($string: String): Boolean</small>                                            |
| Return Character of String at given Position                                                     |
| <small>string.charAt($string: String, $index: Integer): String</small>                               |
| Concatenate Strings                                                                              |
| <small>string.concatenate(...): String</small>                                                       |
| Test if String ends with specific String                                                         |
| <small>string.endsWith($string: String, $suffix: String): Boolean</small>                            |
| Test if 2 Strings matches ignoring Case Sensitivity                                              |
| <small>string.equalsIgnoreCase($string1: String, $string2: String): Boolean</small>                  |
| Return First Index of specific String in String                                                  |
| <small>string.firstIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</small>  |
| Return Index of specific String in String                                                        |
| <small>string.indexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</small>       |
| Return Last Index of specific String in String                                                   |
| <small>string.lastIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</small>   |
| Return String Length                                                                             |
| <small>string.length($string: String): Integer</small>                                               |
| Pad String Left                                                                                  |
| <small>string.padLeft($src: String, $by: String, $toSize: Integer): String</small>                   |
| Pad String Right                                                                                 |
| <small>string.padRight($src: String, $by: String, $toSize: Integer): String</small>                  |
| RegEx Match                                                                                      |
| <small>string.regexMatch($string: String, $pattern: String): Boolean</small>                         |
| RegEx Replace                                                                                    |
| <small>string.regexReplace($string: String, $pattern: String, $by: String): String</small>           |
| Replace specific String in String with given String                                              |
| <small>string.replace($string: String, $what: String, $by: String[, $beginIndex: Integer]): String</small>|
| Create Spaces as String                                                                          |
| <small>string.space([$spaces: Integer]): String</small>                                              |
| Test if given String starts with specific String                                                 |
| <small>string.startsWith($string: String, $prefix: String): Boolean</small>                          |
| Return Substring of String                                                                       |
| <small>string.substring($string: String, $beginIndex: Integer[, $endIndex: Integer]): String</small> |
| Compute Lower Case String of String                                                              |
| <small>string.toLowerCase($string: String): String</small>                                           |
| Compute Upper Case String of String                                                              |
| <small>string.toUpperCase($string: String): String</small>                                           |
| Tokenize String                                                                                  |
| <small>string.tokenize($string: String, $delimiters: String): Array</small>                          |
| Trim String                                                                                      |
| <small>string.trim($string: String): String</small>                                                  |

## 6.13 Time Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Time as String                                                                               |
| <small>time.getAsString([$format: String]): String</small>                                           |
| Get Current Time in Milliseconds                                                                 |
| <small>time.getCurrentMillis(): Integer</small>                                                      |

## 6.14 Transform Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Transform                                                                                 |
| <small>transform([$translation: Vector3[, $scale: Vector3[, $rotationZ: Float[, $rotationY: Float[, $rotationX: Float]]]]]): Transform</small>|
| X Axis as Vector3                                                                                |
| <small>transform.AXIS_X(): Vector3</small>                                                           |
| Y Axis as Vector3                                                                                |
| <small>transform.AXIS_Y(): Vector3</small>                                                           |
| Z Axis as Vector3                                                                                |
| <small>transform.AXIS_Z(): Vector3</small>                                                           |
| Get Rotation Angle of specific Rotation of Transform                                             |
| <small>transform.getRotationAngle($transform: Transform, $idx: Integer): Float</small>               |
| Set Rotation Angle of specific Rotation of Transform                                             |
| <small>transform.setRotationAngle(=$transform: Transform, $idx: Integer, $angle: Float): Void</small>|
| Set Rotation Axis of specific Rotation of Transform                                              |
| <small>transform.getRotationAxis($transform: Transform, $idx: Integer): Vector3</small>              |
| Compute Transform Rotations Quaternion                                                           |
| <small>transform.getRotationsQuaternion($transform: Transform): Quaternion</small>                   |
| Get Transfrom Scale                                                                              |
| <small>transform.getScale($transform: Transform): Vector3</small>                                    |
| Set Transfrom Scale                                                                              |
| <small>transform.setScale(=$transform: Transform, $scale: Vector3): Void</small>                     |
| Get 4x4 Transform Matrix                                                                         |
| <small>transform.getTransformMatrix($transform: Transform): Matrix4x4</small>                        |
| Get Transform Translation                                                                        |
| <small>transform.getTranslation($transform: Transform): Vector3</small>                              |
| Set Transform Translation                                                                        |
| <small>transform.setTranslation(=$transform: Transform, $translation: Vector3): Void</small>         |
| Apply a Rotation to Transform                                                                    |
| <small>transform.applyRotation(=$transform: Transform, $axis: Vector3, $angle: Float): Void</small>  |
| Create Transform from 4x4 Matrix                                                                 |
| <small>transform.fromMatrix($transformMatrix: Matrix4x4): Transform</small>                          |
| Interpolate Rotation                                                                             |
| <small>transform.interpolateRotation($currentAngle: Float, $targetAngle: Float, $timePassedSeconds: Float, $degreesPerSeconds: Float, =$interpolatedAngle: Float): Boolean</small>|
| Multiply Transform with Vector3                                                                  |
| <small>transform.multiply($transform: Transform, $vec3: Vector3): Vector3</small>                    |
| Rotate Vector3 using Transform                                                                   |
| <small>transform.rotate($transform: Transform, $vec3: Vector3): Vector3</small>                      |

## 6.15 Vector2 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector2                                                                                   |
| <small>vec2($x: Float, $y: Float): Vector2</small>                                                   |
| Compute Vector2 Dot Product                                                                      |
| <small>vec2.computeDotProduct($a: Vector2, $b: Vector2): Float</small>                               |
| Compute Vector2 Length                                                                           |
| <small>vec2.computeLength($vec2: Vector2): Float</small>                                             |
| Compute Vector2 Squared Length                                                                   |
| <small>vec2.computeLengthSquared($vec2: Vector2): Float</small>                                      |
| Return Vector2 X Component                                                                       |
| <small>vec2.getX($vec2: Vector2): Float</small>                                                      |
| Return Vector2 Y Component                                                                       |
| <small>vec2.getY($vec2: Vector2): Float</small>                                                      |
| Normalize Vector2                                                                                |
| <small>vec2.normalize($vec2: Vector2): Vector2</small>                                               |

## 6.16 Vector3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector3                                                                                   |
| <small>vec3($x: Float, $y: Float, $z: Float): Vector3</small>                                        |
| Compute Angle between two Vector3                                                                |
| <small>vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float</small>                       |
| Compute Vector3 Cross Product                                                                    |
| <small>vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3</small>                           |
| Compute Vector3 Dot Product                                                                      |
| <small>vec3.computeDotProduct($a: Vector3, $b: Vector3): Float</small>                               |
| Compute Vector3 Length                                                                           |
| <small>vec3.computeLength($vec3: Vector3): Float</small>                                             |
| Compute Vector3 Squared Length                                                                   |
| <small>vec3.computeLengthSquared($vec3: Vector3): Float</small>                                      |
| Return Vector3 X Component                                                                       |
| <small>vec3.getX($vec3: Vector3): Float</small>                                                      |
| Return Vector3 Y Component                                                                       |
| <small>vec3.getY($vec3: Vector3): Float</small>                                                      |
| Return Vector3 Z Component                                                                       |
| <small>vec3.getZ($vec3: Vector3): Float</small>                                                      |
| Normalize Vector3                                                                                |
| <small>vec3.normalize($vec3: Vector3): Vector3</small>                                               |

## 6.17 Vector4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector4                                                                                   |
| <small>vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4</small>                             |
| Compute Vector4 Dot Product                                                                      |
| <small>vec4.computeDotProduct($a: Vector4, $b: Vector4): Float</small>                               |
| Compute Vector4 Length                                                                           |
| <small>vec4.computeLength($vec4: Vector4): Float</small>                                             |
| Compute Vector4 Squared Length                                                                   |
| <small>vec4.computeLengthSquared($vec4: Vector4): Float</small>                                      |
| Return Vector4 W Component                                                                       |
| <small>vec4.getW($vec4: Vector4): Float</small>                                                      |
| Return Vector4 X Component                                                                       |
| <small>vec4.getX($vec4: Vector4): Float</small>                                                      |
| Return Vector4 Y Component                                                                       |
| <small>vec4.getY($vec4: Vector4): Float</small>                                                      |
| Return Vector4 Z Component                                                                       |
| <small>vec4.getZ($vec4: Vector4): Float</small>                                                      |
| Normalize Vector4                                                                                |
| <small>vec4.normalize($vec4: Vector4): Vector4</small>                                               |

## 6.18 XML Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create XML Tag                                                                                   |
| <small>xml.createTag($name: String[, $attributes: Map[, $innerXML: String]]): String</small>         |

# 7. MiniScript Logic Methods

## 7.1 Audio Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Listener Orientation <small>(available in initializeEngine(), updateEngine())</small>            |
| <small>audio.getListenerOrientationAt(): Vector3</small>                                             |
| Set Listener Orientation <small>(available in initializeEngine(), updateEngine())</small>            |
| <small>audio.setListenerOrientationAt($position: Vector3): Void</small>                              |
| Get Listener Position <small>(available in initializeEngine(), updateEngine())</small>               |
| <small>audio.getListenerPosition(): Vector3</small>                                                  |
| Set Listener Position <small>(available in initializeEngine(), updateEngine())</small>               |
| <small>audio.setListenerPosition($position: Vector3): Void</small>                                   |
| Play Audio at Engine Entity Position <small>(available in initializeEngine(), updateEngine())</small>|
| <small>audio.play($id: String[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</small>|
| Play Audio at Custom Position <small>(available in initializeEngine(), updateEngine())</small>       |
| <small>audio.playAtPosition($id: String, $position: Vector3[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</small>|

## 7.2 Engine Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Id by Mouse Position <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.getEntityIdByMousePosition($mouseX: Integer, $mouseY: Integer): String</small>         |
| Get Engine Height <small>(available in initializeEngine(), updateEngine())</small>                   |
| <small>engine.getHeight(): Integer</small>                                                           |
| Compute Engine Screen Coordinate by World Coordinate <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.computeScreenCoordinateByWorldCoordinate($worldCoodinate: Vector3, =$screenCoordinate: Vector2): Boolean</small>|
| Get Engine Width <small>(available in initializeEngine(), updateEngine())</small>                    |
| <small>engine.getWidth(): Integer</small>                                                            |
| Compute Engine World Coordinate by Mouse Position <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.computeWorldCoordinateByMousePosition($mouseX: Integer, $mouseY: Integer): Vector3</small>|
| Dump Engine Entities <small>(available in initializeEngine(), updateEngine())</small>                |
| <small>engine.dumpEntities(): Void</small>                                                           |
| Dump Engine Shaders <small>(available in initializeEngine(), updateEngine())</small>                 |
| <small>engine.dumpShaders(): Void</small>                                                            |

## 7.3 Engine Camera Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Camera horizontal Field Of View <small>(available in initializeEngine(), updateEngine())</small> |
| <small>engine.camera.getFovX(): Float</small>                                                        |
| Set Camera horizontal Field Of View <small>(available in initializeEngine(), updateEngine())</small> |
| <small>engine.camera.setFovX($fovX: Float): Void</small>                                             |
| Get Camera Look At <small>(available in initializeEngine(), updateEngine())</small>                  |
| <small>engine.camera.getLookAt(): Vector3</small>                                                    |
| Set Camera Look At <small>(available in initializeEngine(), updateEngine())</small>                  |
| <small>engine.camera.setLookAt($lookAt: Vector3): Void</small>                                       |
| Get Camera Look From <small>(available in initializeEngine(), updateEngine())</small>                |
| <small>engine.camera.getLookFrom(): Vector3</small>                                                  |
| Set Camera Look From <small>(available in initializeEngine(), updateEngine())</small>                |
| <small>engine.camera.setLookFrom($lookFrom: Vector3): Void</small>                                   |
| Get Camera Up Vector <small>(available in initializeEngine(), updateEngine())</small>                |
| <small>engine.camera.getUpVector(): Vector3</small>                                                  |
| Set Camera Up Vector <small>(available in initializeEngine(), updateEngine())</small>                |
| <small>engine.camera.setUpVector($upVector: Vector3): Void</small>                                   |
| Compute Camera Up Vector <small>(available in initializeEngine(), updateEngine())</small>            |
| <small>engine.camera.computeUpVector($lookFrom: Vector3, $lookAt: Vector3): Vector3</small>          |

## 7.4 Engine Entity Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Animation <small>(available in initializeEngine(), updateEngine())</small>         |
| <small>engine.entity.getAnimation($entityId: String[, $childEntityId: String]): String</small>       |
| Set Engine Entity Animation <small>(available in initializeEngine(), updateEngine())</small>         |
| <small>engine.entity.setAnimation($entityId: String, $animation: String[, $speed: Float[, $childEntityId: String]]): Void</small>|
| Get Engine Entity Animation Speed <small>(available in initializeEngine(), updateEngine())</small>   |
| <small>engine.entity.setAnimationSpeed($entityId: String, $speed: Float[, $childEntityId: String]): Void</small>|
| Set Engine Entity Animation Speed <small>(available in initializeEngine(), updateEngine())</small>   |
| <small>engine.entity.getAnimationTime($entityId: String[, $childEntityId: String]): Float</small>    |
| Get Engine Entity Additive Effect Color <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.getEffectColorAdd($entityId: String[, $childEntityId: String]): Vector4</small> |
| Set Engine Entity Additive Effect Color <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.setEffectColorAdd($entityId: String, $effectColorAdd: Vector4[, $childEntityId: String]): Void</small>|
| Get Engine Entity Multiplicative Effect Color <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.getEffectColorMul($entityId: String[, $childEntityId: String]): Vector4</small> |
| Set Engine Entity Multiplicative Effect Color <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.setEffectColorMul($entityId: String, $effectColorMul: Vector4[, $childEntityId: String]): Void</small>|
| Return if Engine Entity is enabled <small>(available in initializeEngine(), updateEngine())</small>  |
| <small>engine.entity.isEnabled($entityId: String[, $childEntityId: String]): Boolean</small>         |
| Set Engine Entity enabled/disabled <small>(available in initializeEngine(), updateEngine())</small>  |
| <small>engine.entity.setEnabled($entityId: String, $enabled: Boolean[, $childEntityId: String]): Void</small>|
| Get Engine Entity Node Transform <small>(available in initializeEngine(), updateEngine())</small>    |
| <small>engine.entity.getNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Transform</small>|
| Set Engine Entity Node Transform <small>(available in initializeEngine(), updateEngine())</small>    |
| <small>engine.entity.setNodeTransform($entityId: String, $nodeId: String, $transform: Transform[, $childEntityId: String]): Void</small>|
| Unset Engine Entity Node Transform <small>(available in initializeEngine(), updateEngine())</small>  |
| <small>engine.entity.unsetNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Void</small>|
| Get Engine Entity Node Transform Matrix <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.getNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Matrix4x4</small>|
| Set Engine Entity Node Transform Matrix <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.setNodeTransformMatrix($entityId: String, $nodeId: String, $matrix: Matrix4x4[, $childEntityId: String]): Void</small>|
| Unset Engine Entity Node Transform Matrix <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.unsetNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Void</small>|
| Return if Engine Entity has specific Overlay Animation <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.hasOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Boolean</small>|
| Return Engine Entity Overlay Animation Playback Time from 0.0 until 1.0 <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.entity.getOverlayAnimationTime($entityId: String, $animation: String[, $childEntityId: String]): Float</small>|
| Return if Engine Entity is Pickable <small>(available in initializeEngine(), updateEngine())</small> |
| <small>engine.entity.isPickable($entityId: String[, $childEntityId: String]): Boolean</small>        |
| Set Engine Entity Pickable <small>(available in initializeEngine(), updateEngine())</small>          |
| <small>engine.entity.setPickable($entityId: String, $pickable: Boolean[, $childEntityId: String]): Void</small>|
| Get Engine Entity Transform <small>(available in initializeEngine(), updateEngine())</small>         |
| <small>engine.entity.getTransform($entityId: String[, $childEntityId: String]): Transform</small>    |
| Set Engine Entity Transform <small>(available in initializeEngine(), updateEngine())</small>         |
| <small>engine.entity.setTransform($entityId: String, $transform: Transform[, $childEntityId: String]): Void</small>|
| Add Engine Entity Overlay Animation <small>(available in initializeEngine(), updateEngine())</small> |
| <small>engine.entity.addOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</small>|
| Emit Engine Entity Particles <small>(available in initializeEngine(), updateEngine())</small>        |
| <small>engine.entity.emitParticles($entityId: String[, $childEntityId: String]): Integer</small>     |
| Remove finished Overlay Animations <small>(available in initializeEngine(), updateEngine())</small>  |
| <small>engine.entity.removeFinishedOverlayAnimations($entityId: String[, $childEntityId: String]): Void</small>|
| Remove specific Overlay Animation <small>(available in initializeEngine(), updateEngine())</small>   |
| <small>engine.entity.removeOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</small>|
| Remove Overlay Animations <small>(available in initializeEngine(), updateEngine())</small>           |
| <small>engine.entity.removeOverlayAnimations($entityId: String[, $childEntityId: String]): Void</small>|

## 7.5 Engine Timing Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Timing Avarage FPS <small>(available in initializeEngine(), updateEngine())</small>       |
| <small>engine.timing.getAvarageFPS(): Float</small>                                                  |
| Get Engine Timing Frame Delta Time in Milliseconds <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.timing.getDeltaTime(): Integer</small>                                                 |
| Get Engine Timing Frame Delta Time in Seconds <small>(available in initializeEngine(), updateEngine())</small>|
| <small>engine.timing.getDeltaTimeSeconds(): Float</small>                                            |

## 7.6 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <small>input.keyboard.isAltDown(): Boolean</small>                                                   |
| Returns if specific Character is currently pressed                                               |
| <small>input.keyboard.isCharDown($charAsString: String): Boolean</small>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <small>input.keyboard.isControlDown(): Boolean</small>                                               |
| Backspace Key Keycode                                                                            |
| <small>input.keyboard.KEYCODE_BACKSPACE(): Integer</small>                                           |
| Delete Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_DELETE(): Integer</small>                                              |
| Down Key Keycode                                                                                 |
| <small>input.keyboard.KEYCODE_DOWN(): Integer</small>                                                |
| End Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_END(): Integer</small>                                                 |
| Escape Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_ESCAPE(): Integer</small>                                              |
| F1 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F1(): Integer</small>                                                  |
| F10 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F10(): Integer</small>                                                 |
| F11 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F11(): Integer</small>                                                 |
| F12 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F12(): Integer</small>                                                 |
| F2 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F2(): Integer</small>                                                  |
| F3 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F3(): Integer</small>                                                  |
| F4 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F4(): Integer</small>                                                  |
| F5 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F5(): Integer</small>                                                  |
| F6 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F6(): Integer</small>                                                  |
| F7 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F7(): Integer</small>                                                  |
| F8 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F8(): Integer</small>                                                  |
| F9 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F9(): Integer</small>                                                  |
| Left Key Keycode                                                                                 |
| <small>input.keyboard.KEYCODE_LEFT(): Integer</small>                                                |
| Page Down Key Keycode                                                                            |
| <small>input.keyboard.KEYCODE_PAGEDOWN(): Integer</small>                                            |
| Page Up Key Keycode                                                                              |
| <small>input.keyboard.KEYCODE_PAGEUP(): Integer</small>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <small>input.keyboard.KEYCODE_POS1(): Integer</small>                                                |
| Return Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_RETURN(): Integer</small>                                              |
| Right Key Keycode                                                                                |
| <small>input.keyboard.KEYCODE_RIGHT(): Integer</small>                                               |
| Space Key Keycode                                                                                |
| <small>input.keyboard.KEYCODE_SPACE(): Integer</small>                                               |
| Up Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_UP(): Integer</small>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <small>input.keyboard.isKeyDown($keyCode: Integer): Boolean</small>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <small>input.keyboard.isMetaDown(): Boolean</small>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <small>input.keyboard.isShiftDown(): Boolean</small>                                                 |
| Returns last typed String                                                                        |
| <small>input.keyboard.getTypedString(): String</small>                                               |

## 7.7 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <small>input.mouse.BUTTON_LEFT(): Integer</small>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <small>input.mouse.BUTTON_MIDDLE(): Integer</small>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <small>input.mouse.BUTTON_RIGHT(): Integer</small>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <small>input.mouse.isButtonDown($button: Integer): Boolean</small>                                   |
| Returns if specific Mouse Button has been released                                               |
| <small>input.mouse.isButtonUp($button: Integer): Boolean</small>                                     |
| Returns if Mouse is dragging currently                                                           |
| <small>input.mouse.isDragging($button: Integer): Boolean</small>                                     |
| Returns if Mouse has been moved                                                                  |
| <small>input.mouse.hasMoved(): Boolean</small>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelX(): Float</small>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelY(): Float</small>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelZ(): Float</small>                                                        |
| Get X Mouse Position                                                                             |
| <small>input.mouse.getX(): Integer</small>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <small>input.mouse.getXUnscaled(): Integer</small>                                                   |
| Get Y Mouse Position                                                                             |
| <small>input.mouse.getY(): Integer</small>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <small>input.mouse.getYUnscaled(): Integer</small>                                                   |

## 7.8 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.has($logicId: String, $function: String): Boolean</small>                               |
| Get Hierarchy Id <small>(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.getHierarchyId(): String</small>                                                        |
| Get Hierarchy Parent Id <small>(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.getHierarchyParentId(): String</small>                                                  |
| Get Logic Id <small>(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.getId(): String</small>                                                                 |
| Call specific Logic Function <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.call($logicId: String, $function: String, ...): Mixed</small>                           |

## 7.9 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Signal has been sent                                                                  |
| <small>logic.signal.has(): Boolean</small>                                                           |
| Get Signal Argument                                                                              |
| <small>logic.signal.getArgument($argumentIndex: Integer): Mixed</small>                              |
| Get Signal Name                                                                                  |
| <small>logic.signal.getName(): String</small>                                                        |
| Advance to next Signal                                                                           |
| <small>logic.signal.next(): Void</small>                                                             |
| Send Signal <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>logic.signal.send($logicId: String, $signal: String, ...): Void</small>                       |

## 7.10 PathFinding Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Pathfinding Idle State Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_IDLE(): Integer</small>                                                     |
| Pathfinding Computing State Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_PATHFINDING(): Integer</small>                                              |
| Pathfinding Failed State Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_PATHFINDING_FAILED(): Integer</small>                                       |
| Pathfinding Computing Other Pathfinding Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_PATHFINDING_OTHER(): Integer</small>                                        |
| Pathfinding Success State Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_PATHFINDING_SUCCESS(): Integer</small>                                      |
| Pathfinding Try/Lock Failed Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.STATE_TRYLOCK_FAILED(): Integer</small>                                           |
| Issue Pathfinding <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>pathfinding.findPath($logicId: String, $startPosition: Vector3, $endPosition: Vector3, =$path: Array): Integer</small>|

## 7.11 Scene Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Scene Depth                                                                                  |
| <small>scene.getDepth(): Float</small>                                                               |
| Get Scene Height                                                                                 |
| <small>scene.getHeight(): Float</small>                                                              |
| Get Scene Width                                                                                  |
| <small>scene.getWidth(): Float</small>                                                               |

## 7.12 SceneConnector Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Attach Prototype to the Logic Hierarchy <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>sceneconnector.attachPrototype($pathName: String, $fileName: String, $id: String, $attachNodeId: String, $transform: Transform[, $parentId: String]): Void</small>|
| Spawn Prototype in Scene <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>sceneconnector.spawnPrototype($pathName: String, $fileName: String, $id: String, $transform: Transform[, $hierarchyId: String[, $hierarchyParentId: String]]): Void</small>|

## 7.13 Physics World Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Determine Height at specific Position in Physics World <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.determineHeight($collisionTypeIds: Integer, $stepUpMax: Float, $point: Vector3, =$heightPoint: Vector3[, =$bodyId: String[, $minHeight: Float[, $maxHeight: Float]]]): Boolean</small>|
| Determine Collision of Two Specific Bodies in Physics World <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.doCollide($bodyId1: String, $bodyId2: String): Boolean</small>                          |
| Compute Ray Casting in Physics World <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.doRayCasting($collisionTypeIds: Integer, $start: Vector3, $end: Vector3, =$hitPoint: Vector3[, =$bodyId: String[, $actorId: String]]): Boolean</small>|
| Determine Collision of Specific Body in Physics World <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.doesCollideWith($collisionTypeIds: Integer, $bodyId: String): Array</small>             |

## 7.14 Physics World Body Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Physics World Entity Angular Damping <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getAngularDamping($bodyId: String): Float</small>                                  |
| Set Physics World Entity Angular Damping <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setAngularDamping($bodyId: String, $angularDamping: Float): Void</small>           |
| Get Physics World Entity Angular Velocity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getAngularVelocity($bodyId: String): Vector3</small>                               |
| Set Physics World Entity Angular Velocity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setAngularVelocity($bodyId: String, $angularVelocity: Vector3): Void</small>       |
| Returns Physics World Collision Type Id 10 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_10(): Integer</small>                                             |
| Returns Physics World Collision Type Id 11 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_11(): Integer</small>                                             |
| Returns Physics World Collision Type Id 12 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_12(): Integer</small>                                             |
| Returns Physics World Collision Type Id 13 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_13(): Integer</small>                                             |
| Returns Physics World Collision Type Id 14 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_14(): Integer</small>                                             |
| Returns Physics World Collision Type Id 15 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_15(): Integer</small>                                             |
| Returns Physics World Collision Type Id 16 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_16(): Integer</small>                                             |
| Returns Physics World Collision Type Id 3 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_3(): Integer</small>                                              |
| Returns Physics World Collision Type Id 4 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_4(): Integer</small>                                              |
| Returns Physics World Collision Type Id 5 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_5(): Integer</small>                                              |
| Returns Physics World Collision Type Id 6 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_6(): Integer</small>                                              |
| Returns Physics World Collision Type Id 7 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_7(): Integer</small>                                              |
| Returns Physics World Collision Type Id 8 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_8(): Integer</small>                                              |
| Returns Physics World Collision Type Id 9 <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_9(): Integer</small>                                              |
| Returns All Physics World Collision Type Ids <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_ALL(): Integer</small>                                            |
| Returns Dynamic Physics World Collision Type Id <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_DYNAMIC(): Integer</small>                                        |
| Returns Static Physics World Collision Type Id <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.COLLISION_TYPEID_STATIC(): Integer</small>                                         |
| Get Physics World Entity own Collision Type Id <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getCollisionTypeId($bodyId: String): Integer</small>                               |
| Set Physics World Entity own Collision Type Id <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setCollisionTypeId($bodyId: String, $collisionTypeId: Integer): Void</small>       |
| Get Physics World Entity enabled Collision Type Ids <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getCollisionTypeIds($bodyId: String): Integer</small>                              |
| Set Physics World Entity enabled Collision Type Ids <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setCollisionTypeIds($bodyId: String, $collisionTypeIds: Integer): Void</small>     |
| Returns if Physics World Entity is enabled <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.isEnabled($bodyId: String): Boolean</small>                                        |
| Set Physics World Entity enabled/disabled <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setEnabled($bodyId: String, $enabled: Boolean): Void</small>                       |
| Get Physics World Entity Linear Damping <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getLinearDamping($bodyId: String): Float</small>                                   |
| Set Physics World Entity Linear Damping <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setLinearDamping($bodyId: String, $linearDamping: Float): Void</small>             |
| Get Physics World Entity Linear Velocity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getLinearVelocity($bodyId: String): Vector3</small>                                |
| Set Physics World Entity Linear Velocity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setLinearVelocity($bodyId: String, $linearVelocity: Vector3): Void</small>         |
| Returns Physics World Dynamic Collision Body Type Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.TYPE_COLLISION_DYNAMIC(): Integer</small>                                          |
| Returns Physics World Static Collision Body Type Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.TYPE_COLLISION_STATIC(): Integer</small>                                           |
| Returns Physics World Dynamic Rigid Body Type Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.TYPE_DYNAMIC(): Integer</small>                                                    |
| Returns Physics World Static Rigid Body Type Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.TYPE_STATIC(): Integer</small>                                                     |
| Get Physics World Entity Transform <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getTransform($bodyId: String): Transform</small>                                   |
| Set Physics World Entity Transform <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.setTransform($bodyId: String, $transform: Transform): Void</small>                 |
| Get Physics World Entity Body Type Integer Code <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.getType($bodyId: String): Integer</small>                                          |
| Add Force to Physics World Entity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.addForce($bodyId: String, $force: Vector3[, $origin: Vector3]): Void</small>       |
| Add Torque to Physics World Entity <small>(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</small>|
| <small>world.body.addTorque($bodyId: String, $torque: Vector3): Void</small>                         |

# 8. MiniScript GUI Methods

## 8.1 Element Node Condition Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if GUI Element Node has a specific Condition enabled                                     |
| <small>gui.elementnode.conditions.has($elementNodeId: String, $condition: String): Boolean</small>   |
| Get enabled GUI Element Node Conditions                                                          |
| <small>gui.elementnode.conditions.get($elementNodeId: String): Array</small>                         |
| Set enabled GUI Element Node Condition                                                           |
| <small>gui.elementnode.conditions.set($elementNodeId: String, $condition: String): Void</small>      |
| Set Array of enabled GUI Element Node Conditions                                                 |
| <small>gui.elementnode.conditions.setAll($elementNodeId: String, $conditions: Array): Void</small>   |
| Add enabled GUI Element Node Condition                                                           |
| <small>gui.elementnode.conditions.add($elementNodeId: String, $condition: String): Void</small>      |
| Remove enabled GUI Element Node Condition                                                        |
| <small>gui.elementnode.conditions.remove($elementNodeId: String, $condition: String): Void</small>   |
| Remove All enabled GUI Element Node Conditions                                                   |
| <small>gui.elementnode.conditions.removeAll($elementNodeId: String): Void</small>                    |

## 8.2 Event Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns GUI Event Performed Action Type Integer Code                                             |
| <small>gui.event.ACTIONTYPE_PERFORMED(): Integer</small>                                             |
| Returns GUI Event Performing Action Type Integer Code                                            |
| <small>gui.event.ACTIONTYPE_PERFORMING(): Integer</small>                                            |

## 8.3 Image Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Image Source of GUI Image Node                                                               |
| <small>gui.imagenode.getSource($imageNodeId: String): String</small>                                 |
| Set Image Source of GUI Image Node                                                               |
| <small>gui.imagenode.setSource($imageNodeId: String, $source: String): Void</small>                  |

## 8.4 Node Controller Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get GUI Node Controller Value                                                                    |
| <small>gui.node.controller.getValue($nodeId: String): String</small>                                 |
| Set GUI Node Controller Value                                                                    |
| <small>gui.node.controller.setValue($nodeId: String, $value: String): Void</small>                   |

## 8.5 Parent Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Add Sub Nodes using XML to GUI Parent Node                                                       |
| <small>gui.parentnode.addSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</small>|
| Clear Sub Nodes of GUI Parent Node                                                               |
| <small>gui.parentnode.clearSubNodes($parentNodeId: String): Void</small>                             |
| Replace Sub Nodes using XML of GUI Parent Node                                                   |
| <small>gui.parentnode.replaceSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</small>|

## 8.6 Screen Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Return if GUI Screen is enabled                                                                  |
| <small>gui.screen.isEnabled($screenId: String): Boolean</small>                                      |
| Set GUI Screen enabled/disabled                                                                  |
| <small>gui.screen.setEnabled($screenId: String, $enabled: Boolean): Void</small>                     |
| Call specific Screen Logic Function                                                              |
| <small>gui.screen.call($screenId: String, $function: String, ...): Mixed</small>                     |
| Goto current Screen to specific Screen                                                           |
| <small>gui.screen.goto($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</small>      |
| Pop current Screen from Screen Stack                                                             |
| <small>gui.screen.pop(): Void</small>                                                                |
| Push Screen to current Screen Stack                                                              |
| <small>gui.screen.push($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</small>      |

## 8.7 Screen Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Current Screen Node Id                                                                       |
| <small>gui.screennode.getId(): String</small>                                                        |

## 8.8 Text Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Text of GUI Text Node                                                                        |
| <small>gui.textnode.getText($textNodeId: String): String</small>                                     |
| Set Text of GUI Text Node                                                                        |
| <small>gui.textnode.setText($textNodeId: String, $text: String): Void</small>                        |

## 8.9 Video Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Video Source of GUI Video Node                                                               |
| <small>gui.videonode.getSource($videoNodeId: String): String</small>                                 |
| Set Video Source of GUI Video Node                                                               |
| <small>gui.videonode.setSource($videoNodeId: String, $source: String): Void</small>                  |

## 8.10 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <small>input.keyboard.isAltDown(): Boolean</small>                                                   |
| Returns if specific Character is currently pressed                                               |
| <small>input.keyboard.isCharDown($charAsString: String): Boolean</small>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <small>input.keyboard.isControlDown(): Boolean</small>                                               |
| Backspace Key Keycode                                                                            |
| <small>input.keyboard.KEYCODE_BACKSPACE(): Integer</small>                                           |
| Delete Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_DELETE(): Integer</small>                                              |
| Down Key Keycode                                                                                 |
| <small>input.keyboard.KEYCODE_DOWN(): Integer</small>                                                |
| End Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_END(): Integer</small>                                                 |
| Escape Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_ESCAPE(): Integer</small>                                              |
| F1 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F1(): Integer</small>                                                  |
| F10 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F10(): Integer</small>                                                 |
| F11 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F11(): Integer</small>                                                 |
| F12 Key Keycode                                                                                  |
| <small>input.keyboard.KEYCODE_F12(): Integer</small>                                                 |
| F2 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F2(): Integer</small>                                                  |
| F3 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F3(): Integer</small>                                                  |
| F4 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F4(): Integer</small>                                                  |
| F5 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F5(): Integer</small>                                                  |
| F6 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F6(): Integer</small>                                                  |
| F7 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F7(): Integer</small>                                                  |
| F8 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F8(): Integer</small>                                                  |
| F9 Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_F9(): Integer</small>                                                  |
| Left Key Keycode                                                                                 |
| <small>input.keyboard.KEYCODE_LEFT(): Integer</small>                                                |
| Page Down Key Keycode                                                                            |
| <small>input.keyboard.KEYCODE_PAGEDOWN(): Integer</small>                                            |
| Page Up Key Keycode                                                                              |
| <small>input.keyboard.KEYCODE_PAGEUP(): Integer</small>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <small>input.keyboard.KEYCODE_POS1(): Integer</small>                                                |
| Return Key Keycode                                                                               |
| <small>input.keyboard.KEYCODE_RETURN(): Integer</small>                                              |
| Right Key Keycode                                                                                |
| <small>input.keyboard.KEYCODE_RIGHT(): Integer</small>                                               |
| Space Key Keycode                                                                                |
| <small>input.keyboard.KEYCODE_SPACE(): Integer</small>                                               |
| Up Key Keycode                                                                                   |
| <small>input.keyboard.KEYCODE_UP(): Integer</small>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <small>input.keyboard.isKeyDown($keyCode: Integer): Boolean</small>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <small>input.keyboard.isMetaDown(): Boolean</small>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <small>input.keyboard.isShiftDown(): Boolean</small>                                                 |
| Returns last typed String                                                                        |
| <small>input.keyboard.getTypedString(): String</small>                                               |

## 8.11 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <small>input.mouse.BUTTON_LEFT(): Integer</small>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <small>input.mouse.BUTTON_MIDDLE(): Integer</small>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <small>input.mouse.BUTTON_RIGHT(): Integer</small>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <small>input.mouse.isButtonDown($button: Integer): Boolean</small>                                   |
| Returns if specific Mouse Button has been released                                               |
| <small>input.mouse.isButtonUp($button: Integer): Boolean</small>                                     |
| Returns if Mouse is dragging currently                                                           |
| <small>input.mouse.isDragging($button: Integer): Boolean</small>                                     |
| Returns if Mouse has been moved                                                                  |
| <small>input.mouse.hasMoved(): Boolean</small>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelX(): Float</small>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelY(): Float</small>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <small>input.mouse.getWheelZ(): Float</small>                                                        |
| Get X Mouse Position                                                                             |
| <small>input.mouse.getX(): Integer</small>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <small>input.mouse.getXUnscaled(): Integer</small>                                                   |
| Get Y Mouse Position                                                                             |
| <small>input.mouse.getY(): Integer</small>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <small>input.mouse.getYUnscaled(): Integer</small>                                                   |

## 8.12 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function                                                                    |
| <small>logic.has($logicId: String, $function: String): Boolean</small>                               |
| Call specific Logic Function                                                                     |
| <small>logic.call($logicId: String, $function: String, ...): Mixed</small>                           |

## 8.13 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Send Signal                                                                                      |
| <small>logic.signal.send($logicId: String, $signal: String, ...): Void</small>                       |

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
