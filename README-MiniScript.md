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
| <span style="color: lightgray">getVariable($variable: String): Mixed</span>                                                 |
| Set Variable                                                                                     |
| <span style="color: lightgray">setVariable($variable: String, $value: Mixed): Mixed</span>                                  |
| Unset Variable                                                                                   |
| <span style="color: lightgray">unsetVariable($variable: String): Void</span>                                                |
| Add                                                                                              |
| <span style="color: lightgray">add($a: Mixed, $b: Mixed): Mixed</span>                                                      |
| Logical And                                                                                      |
| <span style="color: lightgray">and($a: Boolean, $b: Boolean): Boolean</span>                                                |
| Bitwise And                                                                                      |
| <span style="color: lightgray">bitwiseAnd($a: Integer, $b: Integer): Integer</span>                                         |
| Bitwise Not                                                                                      |
| <span style="color: lightgray">bitwiseNot($value: Integer): Integer</span>                                                  |
| Bitwise Or                                                                                       |
| <span style="color: lightgray">bitwiseOr($a: Integer, $b: Integer): Integer</span>                                          |
| Bitwise Xor                                                                                      |
| <span style="color: lightgray">bitwiseXor($a: Integer, $b: Integer): Integer</span>                                         |
| Create Bool                                                                                      |
| <span style="color: lightgray">bool($bool: Boolean): Boolean</span>                                                         |
| Divide                                                                                           |
| <span style="color: lightgray">div($a: Mixed, $b: Mixed): Mixed</span>                                                      |
| Else                                                                                             |
| <span style="color: lightgray">else(): Void</span>                                                                          |
| Else If                                                                                          |
| <span style="color: lightgray">elseif($condition: Boolean): Void</span>                                                     |
| End                                                                                              |
| <span style="color: lightgray">end(): Void</span>                                                                           |
| Equals                                                                                           |
| <span style="color: lightgray">equals($a: Mixed, $b: Mixed): Boolean</span>                                                 |
| Create Float                                                                                     |
| <span style="color: lightgray">float($float: Float): Float</span>                                                           |
| For Condition                                                                                    |
| <span style="color: lightgray">forCondition($condition: Boolean): Void</span>                                               |
| For Time                                                                                         |
| <span style="color: lightgray">forTime($time: Integer): Void</span>                                                         |
| Greater                                                                                          |
| <span style="color: lightgray">greater($a: Mixed, $b: Mixed): Boolean</span>                                                |
| Greater Equals                                                                                   |
| <span style="color: lightgray">greaterEquals($a: Mixed, $b: Mixed): Boolean</span>                                          |
| If                                                                                               |
| <span style="color: lightgray">if($condition: Boolean): Void</span>                                                         |
| Create Integer                                                                                   |
| <span style="color: lightgray">int($int: Integer): Integer</span>                                                           |
| Lesser                                                                                           |
| <span style="color: lightgray">lesser($a: Mixed, $b: Mixed): Boolean</span>                                                 |
| Lesser Equals                                                                                    |
| <span style="color: lightgray">lesserEquals($a: Mixed, $b: Mixed): Boolean</span>                                           |
| Compute Modulo                                                                                   |
| <span style="color: lightgray">mod($value: Number, $range: Number): Number</span>                                           |
| Multiply                                                                                         |
| <span style="color: lightgray">mul($a: Mixed, $b: Mixed): Mixed</span>                                                      |
| Logical Not                                                                                      |
| <span style="color: lightgray">not($bool: Boolean): Boolean</span>                                                          |
| Logical Not Equal                                                                                |
| <span style="color: lightgray">notEqual($a: Mixed, $b: Mixed): Boolean</span>                                               |
| Logical Or                                                                                       |
| <span style="color: lightgray">or($a: Boolean, $b: Boolean): Boolean</span>                                                 |
| Prefix Decrement                                                                                 |
| <span style="color: lightgray">prefixDecrement(=$variable: Integer): Integer</span>                                         |
| Prefix Increment                                                                                 |
| <span style="color: lightgray">prefixIncrement(=$variable: Integer): Integer</span>                                         |
| Return from Function with optional Return Value                                                  |
| <span style="color: lightgray">return([$value: Mixed]): Void</span>                                                         |
| Subtract                                                                                         |
| <span style="color: lightgray">sub($a: Mixed, $b: Mixed): Mixed</span>                                                      |

## 6.2 Array Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Array                                                                                     |
| <span style="color: lightgray">array(...): Array</span>                                                                     |
| Get Array Entry                                                                                  |
| <span style="color: lightgray">array.get($array: Array, $index: Integer): Mixed</span>                                      |
| Set Array Entry                                                                                  |
| <span style="color: lightgray">array.set(=$array: Array, $index: Integer, $value: Mixed): Void</span>                       |
| Get Array Index by Value                                                                         |
| <span style="color: lightgray">array.indexOf($array: Array, $value: String[, $beginIndex: Integer]): Integer</span>         |
| Get Array Length                                                                                 |
| <span style="color: lightgray">array.length($array: Array): Integer</span>                                                  |
| Add to Array                                                                                     |
| <span style="color: lightgray">array.push(=$array: Array, ...): Void</span>                                                 |
| Remove Array by Index                                                                            |
| <span style="color: lightgray">array.remove(=$array: Array, $index: Integer): Void</span>                                   |
| Remove Array Entry by Value                                                                      |
| <span style="color: lightgray">array.removeOf(=$array: Array, $value: String[, $beginIndex: Integer]): Void</span>          |
| Reverse Array                                                                                    |
| <span style="color: lightgray">array.reverse(=$array: Array): Void</span>                                                   |
| Sort Array                                                                                       |
| <span style="color: lightgray">array.sort(=$array: Array, $function: String): Void</span>                                   |

## 6.3 Console Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Print to Console                                                                                 |
| <span style="color: lightgray">console.log(...): Void</span>                                                                |

## 6.4 JSON Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Deserialize JSON                                                                                 |
| <span style="color: lightgray">json.deserialize($json: String): Mixed</span>                                                |
| Serialize JSON                                                                                   |
| <span style="color: lightgray">json.serialize($value: Mixed): String</span>                                                 |

## 6.5 Map Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Map                                                                                       |
| <span style="color: lightgray">map(): Map</span>                                                                            |
| Has Entry by Key                                                                                 |
| <span style="color: lightgray">map.has($map: Map, $key: String): Boolean</span>                                             |
| Get Map Value by Key                                                                             |
| <span style="color: lightgray">map.get($map: Map, $key: String): Mixed</span>                                               |
| Set Map Entry                                                                                    |
| <span style="color: lightgray">map.set(=$map: Map, $key: String, $value: Mixed): Void</span>                                |
| Get Map Keys                                                                                     |
| <span style="color: lightgray">map.getKeys($map: Map): Array</span>                                                         |
| Get Map Values                                                                                   |
| <span style="color: lightgray">map.getValues($map: Map): Array</span>                                                       |
| Remove Map Entry                                                                                 |
| <span style="color: lightgray">map.remove(=$map: Map, $key: String): Void</span>                                            |

## 6.6 Matrix3x3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Identity 3x3 Matrix                                                                       |
| <span style="color: lightgray">mat3.identity(): Matrix3x3</span>                                                            |
| Multiply 3x3 Matrix with 3x3 Matrix or Vector2                                                   |
| <span style="color: lightgray">mat3.multiply($mat3: Matrix3x3, ...): Mixed</span>                                           |
| Create Rotation 3x3 Matrix                                                                       |
| <span style="color: lightgray">mat3.rotate($angle: Float): Matrix3x3</span>                                                 |
| Create 3x3 Matrix which rotates around Point                                                     |
| <span style="color: lightgray">mat3.rotateAroundPoint($point: Vector2, $angle: Float): Matrix3x3</span>                     |
| Create 3x3 Matrix which rotates around Texture Center                                            |
| <span style="color: lightgray">mat3.rotateAroundTextureCenter($angle: Float): Matrix3x3</span>                              |
| Create Scale 3x3 Matrix                                                                          |
| <span style="color: lightgray">mat3.scale(...): Matrix3x3</span>                                                            |
| Create Translation 3x3 Matrix                                                                    |
| <span style="color: lightgray">mat3.translate($translation: Vector2): Matrix3x3</span>                                      |

## 6.7 Matrix4x4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from 4x4 Matrix                                                             |
| <span style="color: lightgray">mat4.computeEulerAngles($mat4: Matrix4x4): Vector3</span>                                    |
| Create Identity 4x4 Matrix                                                                       |
| <span style="color: lightgray">mat4.identity(): Matrix4x4</span>                                                            |
| Create 4x4 Matrix Inverse                                                                        |
| <span style="color: lightgray">mat4.invert($mat4: Matrix4x4): Matrix4x4</span>                                              |
| Multiply 4x4 Matrix with 4x4 Matrix or Vector3 or Vector4                                        |
| <span style="color: lightgray">mat4.multiply($mat4: Matrix4x4, ...): Mixed</span>                                           |
| Create Rotation 4x4 Matrix                                                                       |
| <span style="color: lightgray">mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4</span>                                 |
| Create Scale 4x4 Matrix                                                                          |
| <span style="color: lightgray">mat4.scale(...): Matrix4x4</span>                                                            |
| Create Translation 4x4 Matrix                                                                    |
| <span style="color: lightgray">mat4.translate($translation: Vector3): Matrix4x4</span>                                      |

## 6.8 Math Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Degree to Radian Factor                                                                          |
| <span style="color: lightgray">math.DEG2RAD(): Float</span>                                                                 |
| Epsilon                                                                                          |
| <span style="color: lightgray">math.EPSILON(): Float</span>                                                                 |
| G                                                                                                |
| <span style="color: lightgray">math.G(): Float</span>                                                                       |
| PI                                                                                               |
| <span style="color: lightgray">math.PI(): Float</span>                                                                      |
| Return Number as Positive Number                                                                 |
| <span style="color: lightgray">math.abs($value: Number): Number</span>                                                      |
| Return Number to be Positive within given Range                                                  |
| <span style="color: lightgray">math.absmod($value: Number, $range: Number): Number</span>                                   |
| Compute acos                                                                                     |
| <span style="color: lightgray">math.acos($value: Float): Float</span>                                                       |
| Compute asin                                                                                     |
| <span style="color: lightgray">math.asin($value: Float): Float</span>                                                       |
| Compute atan                                                                                     |
| <span style="color: lightgray">math.atan($value: Float): Float</span>                                                       |
| Compute atan2                                                                                    |
| <span style="color: lightgray">math.atan2($y: Float, $x: Float): Float</span>                                               |
| Round Float up to next higher Integer                                                            |
| <span style="color: lightgray">math.ceil($value: Float): Float</span>                                                       |
| Return Number clamped to be in given Range                                                       |
| <span style="color: lightgray">math.clamp($value: Number, $min: Number, $max: Number): Number</span>                        |
| Compute acos                                                                                     |
| <span style="color: lightgray">math.cos($value: Float): Float</span>                                                        |
| Compute exp                                                                                      |
| <span style="color: lightgray">math.exp($value: Float): Float</span>                                                        |
| Round Float down to next lower Integer                                                           |
| <span style="color: lightgray">math.floor($value: Float): Float</span>                                                      |
| Compute log                                                                                      |
| <span style="color: lightgray">math.log($value: Float): Float</span>                                                        |
| Return maximum Number of given Values                                                            |
| <span style="color: lightgray">math.max($a: Number, $b: Number): Number</span>                                              |
| Return minimum Number of given Values                                                            |
| <span style="color: lightgray">math.min($a: Number, $b: Number): Number</span>                                              |
| Compute Modulo/Remainder                                                                         |
| <span style="color: lightgray">math.mod($value: Number, $range: Number): Number</span>                                      |
| Compute pow                                                                                      |
| <span style="color: lightgray">math.pow($a: Number, $b: Number): Number</span>                                              |
| Create a random Number between 0.0 and 1.0                                                       |
| <span style="color: lightgray">math.random(): Float</span>                                                                  |
| Round Float Up or Down to Integer                                                                |
| <span style="color: lightgray">math.round($value: Float): Float</span>                                                      |
| Return Sign of given Number                                                                      |
| <span style="color: lightgray">math.sign($value: Number): Number</span>                                                     |
| Compute sin                                                                                      |
| <span style="color: lightgray">math.sin($value: Float): Float</span>                                                        |
| Compute Square Root                                                                              |
| <span style="color: lightgray">math.sqrt($value: Float): Float</span>                                                       |
| Compute Square Product                                                                           |
| <span style="color: lightgray">math.square($value: Number): Number</span>                                                   |
| Compute tan                                                                                      |
| <span style="color: lightgray">math.tan($value: Float): Float</span>                                                        |

## 6.9 Quaternion Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Compute Euler Angles from Quaternion                                                             |
| <span style="color: lightgray">quaternion.computeEulerAngles($quaternion: Quaternion): Vector3</span>                       |
| Compute 4x4 Rotation Matrix from Quaternion                                                      |
| <span style="color: lightgray">quaternion.computeMatrix($quaternion: Quaternion): Matrix4x4</span>                          |
| Create Identity Quaternion                                                                       |
| <span style="color: lightgray">quaternion.identity(): Quaternion</span>                                                     |
| Create Quaternion Inverse                                                                        |
| <span style="color: lightgray">quaternion.invert($quaternion: Quaternion): Quaternion</span>                                |
| Multiply Quaternion with Quaternion or Vector3                                                   |
| <span style="color: lightgray">quaternion.multiply($quaternion: Quaternion, ...): Mixed</span>                              |
| Normalize Quaternion                                                                             |
| <span style="color: lightgray">quaternion.normalize($quaternion: Quaternion): Quaternion</span>                             |
| Create Rotation Quaternion                                                                       |
| <span style="color: lightgray">quaternion.rotate($axis: Vector3, $angle: Float): Quaternion</span>                          |

## 6.10 Script Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Named Conditions                                                                             |
| <span style="color: lightgray">script.getNamedConditions(): String</span>                                                   |
| Get Script Variables                                                                             |
| <span style="color: lightgray">script.getVariables(): Map</span>                                                            |
| Call Script Function                                                                             |
| <span style="color: lightgray">script.call($function: String, ...): Mixed</span>                                            |
| Disable a specific Named Condition                                                               |
| <span style="color: lightgray">script.disableNamedCondition($name: String): Void</span>                                     |
| Emit a Condition                                                                                 |
| <span style="color: lightgray">script.emit($condition: String): Void</span>                                                 |
| Enable a specific Named Condition                                                                |
| <span style="color: lightgray">script.enableNamedCondition($name: String): Void</span>                                      |
| Evaluate a Script Statement                                                                      |
| <span style="color: lightgray">script.evaluate($statement: String): Mixed</span>                                            |
| Stop Script                                                                                      |
| <span style="color: lightgray">script.stop(): Void</span>                                                                   |
| Wait for given Milliseconds                                                                      |
| <span style="color: lightgray">script.wait($time: Integer): Void</span>                                                     |
| Wait for Condition to happen                                                                     |
| <span style="color: lightgray">script.waitForCondition(): Void</span>                                                       |

## 6.11 Set Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Set                                                                                       |
| <span style="color: lightgray">set(): Set</span>                                                                            |
| Has Key in Set                                                                                   |
| <span style="color: lightgray">set.has($set: Set, $key: String): Boolean</span>                                             |
| Get Set Keys                                                                                     |
| <span style="color: lightgray">set.getKeys($set: Set): Array</span>                                                         |
| Insert Key into Set                                                                              |
| <span style="color: lightgray">set.insert(=$set: Set, $key: String): Void</span>                                            |
| Remove Key from Set                                                                              |
| <span style="color: lightgray">set.remove(=$set: Set, $key: String): Void</span>                                            |

## 6.12 String Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create String                                                                                    |
| <span style="color: lightgray">string($string: String): String</span>                                                       |
| Test if String Value is Empty                                                                    |
| <span style="color: lightgray">string.isEmpty($string: String): Boolean</span>                                              |
| Test if String Value is a Float Number                                                           |
| <span style="color: lightgray">string.isFloat($string: String): Boolean</span>                                              |
| Test if String Value is a Integer Number                                                         |
| <span style="color: lightgray">string.isInteger($string: String): Boolean</span>                                            |
| Return Character of String at given Position                                                     |
| <span style="color: lightgray">string.charAt($string: String, $index: Integer): String</span>                               |
| Concatenate Strings                                                                              |
| <span style="color: lightgray">string.concatenate(...): String</span>                                                       |
| Test if String ends with specific String                                                         |
| <span style="color: lightgray">string.endsWith($string: String, $suffix: String): Boolean</span>                            |
| Test if 2 Strings matches ignoring Case Sensitivity                                              |
| <span style="color: lightgray">string.equalsIgnoreCase($string1: String, $string2: String): Boolean</span>                  |
| Return First Index of specific String in String                                                  |
| <span style="color: lightgray">string.firstIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</span>  |
| Return Index of specific String in String                                                        |
| <span style="color: lightgray">string.indexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</span>       |
| Return Last Index of specific String in String                                                   |
| <span style="color: lightgray">string.lastIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer</span>   |
| Return String Length                                                                             |
| <span style="color: lightgray">string.length($string: String): Integer</span>                                               |
| Pad String Left                                                                                  |
| <span style="color: lightgray">string.padLeft($src: String, $by: String, $toSize: Integer): String</span>                   |
| Pad String Right                                                                                 |
| <span style="color: lightgray">string.padRight($src: String, $by: String, $toSize: Integer): String</span>                  |
| RegEx Match                                                                                      |
| <span style="color: lightgray">string.regexMatch($string: String, $pattern: String): Boolean</span>                         |
| RegEx Replace                                                                                    |
| <span style="color: lightgray">string.regexReplace($string: String, $pattern: String, $by: String): String</span>           |
| Replace specific String in String with given String                                              |
| <span style="color: lightgray">string.replace($string: String, $what: String, $by: String[, $beginIndex: Integer]): String</span>|
| Create Spaces as String                                                                          |
| <span style="color: lightgray">string.space([$spaces: Integer]): String</span>                                              |
| Test if given String starts with specific String                                                 |
| <span style="color: lightgray">string.startsWith($string: String, $prefix: String): Boolean</span>                          |
| Return Substring of String                                                                       |
| <span style="color: lightgray">string.substring($string: String, $beginIndex: Integer[, $endIndex: Integer]): String</span> |
| Compute Lower Case String of String                                                              |
| <span style="color: lightgray">string.toLowerCase($string: String): String</span>                                           |
| Compute Upper Case String of String                                                              |
| <span style="color: lightgray">string.toUpperCase($string: String): String</span>                                           |
| Tokenize String                                                                                  |
| <span style="color: lightgray">string.tokenize($string: String, $delimiters: String): Array</span>                          |
| Trim String                                                                                      |
| <span style="color: lightgray">string.trim($string: String): String</span>                                                  |

## 6.13 Time Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Time as String                                                                               |
| <span style="color: lightgray">time.getAsString([$format: String]): String</span>                                           |
| Get Current Time in Milliseconds                                                                 |
| <span style="color: lightgray">time.getCurrentMillis(): Integer</span>                                                      |

## 6.14 Transform Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Transform                                                                                 |
| <span style="color: lightgray">transform([$translation: Vector3[, $scale: Vector3[, $rotationZ: Float[, $rotationY: Float[, $rotationX: Float]]]]]): Transform</span>|
| X Axis as Vector3                                                                                |
| <span style="color: lightgray">transform.AXIS_X(): Vector3</span>                                                           |
| Y Axis as Vector3                                                                                |
| <span style="color: lightgray">transform.AXIS_Y(): Vector3</span>                                                           |
| Z Axis as Vector3                                                                                |
| <span style="color: lightgray">transform.AXIS_Z(): Vector3</span>                                                           |
| Get Rotation Angle of specific Rotation of Transform                                             |
| <span style="color: lightgray">transform.getRotationAngle($transform: Transform, $idx: Integer): Float</span>               |
| Set Rotation Angle of specific Rotation of Transform                                             |
| <span style="color: lightgray">transform.setRotationAngle(=$transform: Transform, $idx: Integer, $angle: Float): Void</span>|
| Set Rotation Axis of specific Rotation of Transform                                              |
| <span style="color: lightgray">transform.getRotationAxis($transform: Transform, $idx: Integer): Vector3</span>              |
| Compute Transform Rotations Quaternion                                                           |
| <span style="color: lightgray">transform.getRotationsQuaternion($transform: Transform): Quaternion</span>                   |
| Get Transfrom Scale                                                                              |
| <span style="color: lightgray">transform.getScale($transform: Transform): Vector3</span>                                    |
| Set Transfrom Scale                                                                              |
| <span style="color: lightgray">transform.setScale(=$transform: Transform, $scale: Vector3): Void</span>                     |
| Get 4x4 Transform Matrix                                                                         |
| <span style="color: lightgray">transform.getTransformMatrix($transform: Transform): Matrix4x4</span>                        |
| Get Transform Translation                                                                        |
| <span style="color: lightgray">transform.getTranslation($transform: Transform): Vector3</span>                              |
| Set Transform Translation                                                                        |
| <span style="color: lightgray">transform.setTranslation(=$transform: Transform, $translation: Vector3): Void</span>         |
| Apply a Rotation to Transform                                                                    |
| <span style="color: lightgray">transform.applyRotation(=$transform: Transform, $axis: Vector3, $angle: Float): Void</span>  |
| Create Transform from 4x4 Matrix                                                                 |
| <span style="color: lightgray">transform.fromMatrix($transformMatrix: Matrix4x4): Transform</span>                          |
| Interpolate Rotation                                                                             |
| <span style="color: lightgray">transform.interpolateRotation($currentAngle: Float, $targetAngle: Float, $timePassedSeconds: Float, $degreesPerSeconds: Float, =$interpolatedAngle: Float): Boolean</span>|
| Multiply Transform with Vector3                                                                  |
| <span style="color: lightgray">transform.multiply($transform: Transform, $vec3: Vector3): Vector3</span>                    |
| Rotate Vector3 using Transform                                                                   |
| <span style="color: lightgray">transform.rotate($transform: Transform, $vec3: Vector3): Vector3</span>                      |

## 6.15 Vector2 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector2                                                                                   |
| <span style="color: lightgray">vec2($x: Float, $y: Float): Vector2</span>                                                   |
| Compute Vector2 Dot Product                                                                      |
| <span style="color: lightgray">vec2.computeDotProduct($a: Vector2, $b: Vector2): Float</span>                               |
| Compute Vector2 Length                                                                           |
| <span style="color: lightgray">vec2.computeLength($vec2: Vector2): Float</span>                                             |
| Compute Vector2 Squared Length                                                                   |
| <span style="color: lightgray">vec2.computeLengthSquared($vec2: Vector2): Float</span>                                      |
| Return Vector2 X Component                                                                       |
| <span style="color: lightgray">vec2.getX($vec2: Vector2): Float</span>                                                      |
| Return Vector2 Y Component                                                                       |
| <span style="color: lightgray">vec2.getY($vec2: Vector2): Float</span>                                                      |
| Normalize Vector2                                                                                |
| <span style="color: lightgray">vec2.normalize($vec2: Vector2): Vector2</span>                                               |

## 6.16 Vector3 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector3                                                                                   |
| <span style="color: lightgray">vec3($x: Float, $y: Float, $z: Float): Vector3</span>                                        |
| Compute Angle between two Vector3                                                                |
| <span style="color: lightgray">vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float</span>                       |
| Compute Vector3 Cross Product                                                                    |
| <span style="color: lightgray">vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3</span>                           |
| Compute Vector3 Dot Product                                                                      |
| <span style="color: lightgray">vec3.computeDotProduct($a: Vector3, $b: Vector3): Float</span>                               |
| Compute Vector3 Length                                                                           |
| <span style="color: lightgray">vec3.computeLength($vec3: Vector3): Float</span>                                             |
| Compute Vector3 Squared Length                                                                   |
| <span style="color: lightgray">vec3.computeLengthSquared($vec3: Vector3): Float</span>                                      |
| Return Vector3 X Component                                                                       |
| <span style="color: lightgray">vec3.getX($vec3: Vector3): Float</span>                                                      |
| Return Vector3 Y Component                                                                       |
| <span style="color: lightgray">vec3.getY($vec3: Vector3): Float</span>                                                      |
| Return Vector3 Z Component                                                                       |
| <span style="color: lightgray">vec3.getZ($vec3: Vector3): Float</span>                                                      |
| Normalize Vector3                                                                                |
| <span style="color: lightgray">vec3.normalize($vec3: Vector3): Vector3</span>                                               |

## 6.17 Vector4 Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create Vector4                                                                                   |
| <span style="color: lightgray">vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4</span>                             |
| Compute Vector4 Dot Product                                                                      |
| <span style="color: lightgray">vec4.computeDotProduct($a: Vector4, $b: Vector4): Float</span>                               |
| Compute Vector4 Length                                                                           |
| <span style="color: lightgray">vec4.computeLength($vec4: Vector4): Float</span>                                             |
| Compute Vector4 Squared Length                                                                   |
| <span style="color: lightgray">vec4.computeLengthSquared($vec4: Vector4): Float</span>                                      |
| Return Vector4 W Component                                                                       |
| <span style="color: lightgray">vec4.getW($vec4: Vector4): Float</span>                                                      |
| Return Vector4 X Component                                                                       |
| <span style="color: lightgray">vec4.getX($vec4: Vector4): Float</span>                                                      |
| Return Vector4 Y Component                                                                       |
| <span style="color: lightgray">vec4.getY($vec4: Vector4): Float</span>                                                      |
| Return Vector4 Z Component                                                                       |
| <span style="color: lightgray">vec4.getZ($vec4: Vector4): Float</span>                                                      |
| Normalize Vector4                                                                                |
| <span style="color: lightgray">vec4.normalize($vec4: Vector4): Vector4</span>                                               |

## 6.18 XML Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Create XML Tag                                                                                   |
| <span style="color: lightgray">xml.createTag($name: String[, $attributes: Map[, $innerXML: String]]): String</span>         |

# 7. MiniScript Logic Methods

## 7.1 Audio Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Listener Orientation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>            |
| <span style="color: lightgray">audio.getListenerOrientationAt(): Vector3</span>                                             |
| Set Listener Orientation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>            |
| <span style="color: lightgray">audio.setListenerOrientationAt($position: Vector3): Void</span>                              |
| Get Listener Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>               |
| <span style="color: lightgray">audio.getListenerPosition(): Vector3</span>                                                  |
| Set Listener Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>               |
| <span style="color: lightgray">audio.setListenerPosition($position: Vector3): Void</span>                                   |
| Play Audio at Engine Entity Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">audio.play($id: String[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</span>|
| Play Audio at Custom Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>       |
| <span style="color: lightgray">audio.playAtPosition($id: String, $position: Vector3[, $delay: Integer[, $gain: Integer[, $pitch: Integer[, $ignoreIfPlaying: Integer]]]]): String</span>|

## 7.2 Engine Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Id by Mouse Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.getEntityIdByMousePosition($mouseX: Integer, $mouseY: Integer): String</span>         |
| Get Engine Height <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                   |
| <span style="color: lightgray">engine.getHeight(): Integer</span>                                                           |
| Compute Engine Screen Coordinate by World Coordinate <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.computeScreenCoordinateByWorldCoordinate($worldCoodinate: Vector3, =$screenCoordinate: Vector2): Boolean</span>|
| Get Engine Width <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                    |
| <span style="color: lightgray">engine.getWidth(): Integer</span>                                                            |
| Compute Engine World Coordinate by Mouse Position <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.computeWorldCoordinateByMousePosition($mouseX: Integer, $mouseY: Integer): Vector3</span>|
| Dump Engine Entities <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                |
| <span style="color: lightgray">engine.dumpEntities(): Void</span>                                                           |
| Dump Engine Shaders <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                 |
| <span style="color: lightgray">engine.dumpShaders(): Void</span>                                                            |

## 7.3 Engine Camera Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Camera horizontal Field Of View <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span> |
| <span style="color: lightgray">engine.camera.getFovX(): Float</span>                                                        |
| Set Camera horizontal Field Of View <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span> |
| <span style="color: lightgray">engine.camera.setFovX($fovX: Float): Void</span>                                             |
| Get Camera Look At <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                  |
| <span style="color: lightgray">engine.camera.getLookAt(): Vector3</span>                                                    |
| Set Camera Look At <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                  |
| <span style="color: lightgray">engine.camera.setLookAt($lookAt: Vector3): Void</span>                                       |
| Get Camera Look From <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                |
| <span style="color: lightgray">engine.camera.getLookFrom(): Vector3</span>                                                  |
| Set Camera Look From <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                |
| <span style="color: lightgray">engine.camera.setLookFrom($lookFrom: Vector3): Void</span>                                   |
| Get Camera Up Vector <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                |
| <span style="color: lightgray">engine.camera.getUpVector(): Vector3</span>                                                  |
| Set Camera Up Vector <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>                |
| <span style="color: lightgray">engine.camera.setUpVector($upVector: Vector3): Void</span>                                   |
| Compute Camera Up Vector <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>            |
| <span style="color: lightgray">engine.camera.computeUpVector($lookFrom: Vector3, $lookAt: Vector3): Vector3</span>          |

## 7.4 Engine Entity Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Entity Animation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>         |
| <span style="color: lightgray">engine.entity.getAnimation($entityId: String[, $childEntityId: String]): String</span>       |
| Set Engine Entity Animation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>         |
| <span style="color: lightgray">engine.entity.setAnimation($entityId: String, $animation: String[, $speed: Float[, $childEntityId: String]]): Void</span>|
| Get Engine Entity Animation Speed <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>   |
| <span style="color: lightgray">engine.entity.setAnimationSpeed($entityId: String, $speed: Float[, $childEntityId: String]): Void</span>|
| Set Engine Entity Animation Speed <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>   |
| <span style="color: lightgray">engine.entity.getAnimationTime($entityId: String[, $childEntityId: String]): Float</span>    |
| Get Engine Entity Additive Effect Color <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.getEffectColorAdd($entityId: String[, $childEntityId: String]): Vector4</span> |
| Set Engine Entity Additive Effect Color <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.setEffectColorAdd($entityId: String, $effectColorAdd: Vector4[, $childEntityId: String]): Void</span>|
| Get Engine Entity Multiplicative Effect Color <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.getEffectColorMul($entityId: String[, $childEntityId: String]): Vector4</span> |
| Set Engine Entity Multiplicative Effect Color <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.setEffectColorMul($entityId: String, $effectColorMul: Vector4[, $childEntityId: String]): Void</span>|
| Return if Engine Entity is enabled <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>  |
| <span style="color: lightgray">engine.entity.isEnabled($entityId: String[, $childEntityId: String]): Boolean</span>         |
| Set Engine Entity enabled/disabled <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>  |
| <span style="color: lightgray">engine.entity.setEnabled($entityId: String, $enabled: Boolean[, $childEntityId: String]): Void</span>|
| Get Engine Entity Node Transform <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>    |
| <span style="color: lightgray">engine.entity.getNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Transform</span>|
| Set Engine Entity Node Transform <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>    |
| <span style="color: lightgray">engine.entity.setNodeTransform($entityId: String, $nodeId: String, $transform: Transform[, $childEntityId: String]): Void</span>|
| Unset Engine Entity Node Transform <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>  |
| <span style="color: lightgray">engine.entity.unsetNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Void</span>|
| Get Engine Entity Node Transform Matrix <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.getNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Matrix4x4</span>|
| Set Engine Entity Node Transform Matrix <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.setNodeTransformMatrix($entityId: String, $nodeId: String, $matrix: Matrix4x4[, $childEntityId: String]): Void</span>|
| Unset Engine Entity Node Transform Matrix <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.unsetNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Void</span>|
| Return if Engine Entity has specific Overlay Animation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.hasOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Boolean</span>|
| Return Engine Entity Overlay Animation Playback Time from 0.0 until 1.0 <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.entity.getOverlayAnimationTime($entityId: String, $animation: String[, $childEntityId: String]): Float</span>|
| Return if Engine Entity is Pickable <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span> |
| <span style="color: lightgray">engine.entity.isPickable($entityId: String[, $childEntityId: String]): Boolean</span>        |
| Set Engine Entity Pickable <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>          |
| <span style="color: lightgray">engine.entity.setPickable($entityId: String, $pickable: Boolean[, $childEntityId: String]): Void</span>|
| Get Engine Entity Transform <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>         |
| <span style="color: lightgray">engine.entity.getTransform($entityId: String[, $childEntityId: String]): Transform</span>    |
| Set Engine Entity Transform <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>         |
| <span style="color: lightgray">engine.entity.setTransform($entityId: String, $transform: Transform[, $childEntityId: String]): Void</span>|
| Add Engine Entity Overlay Animation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span> |
| <span style="color: lightgray">engine.entity.addOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</span>|
| Emit Engine Entity Particles <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>        |
| <span style="color: lightgray">engine.entity.emitParticles($entityId: String[, $childEntityId: String]): Integer</span>     |
| Remove finished Overlay Animations <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>  |
| <span style="color: lightgray">engine.entity.removeFinishedOverlayAnimations($entityId: String[, $childEntityId: String]): Void</span>|
| Remove specific Overlay Animation <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>   |
| <span style="color: lightgray">engine.entity.removeOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void</span>|
| Remove Overlay Animations <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>           |
| <span style="color: lightgray">engine.entity.removeOverlayAnimations($entityId: String[, $childEntityId: String]): Void</span>|

## 7.5 Engine Timing Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Engine Timing Avarage FPS <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>       |
| <span style="color: lightgray">engine.timing.getAvarageFPS(): Float</span>                                                  |
| Get Engine Timing Frame Delta Time in Milliseconds <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.timing.getDeltaTime(): Integer</span>                                                 |
| Get Engine Timing Frame Delta Time in Seconds <span style="color: lightgray">(available in initializeEngine(), updateEngine())</span>|
| <span style="color: lightgray">engine.timing.getDeltaTimeSeconds(): Float</span>                                            |

## 7.6 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <span style="color: lightgray">input.keyboard.isAltDown(): Boolean</span>                                                   |
| Returns if specific Character is currently pressed                                               |
| <span style="color: lightgray">input.keyboard.isCharDown($charAsString: String): Boolean</span>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <span style="color: lightgray">input.keyboard.isControlDown(): Boolean</span>                                               |
| Backspace Key Keycode                                                                            |
| <span style="color: lightgray">input.keyboard.KEYCODE_BACKSPACE(): Integer</span>                                           |
| Delete Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_DELETE(): Integer</span>                                              |
| Down Key Keycode                                                                                 |
| <span style="color: lightgray">input.keyboard.KEYCODE_DOWN(): Integer</span>                                                |
| End Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_END(): Integer</span>                                                 |
| Escape Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_ESCAPE(): Integer</span>                                              |
| F1 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F1(): Integer</span>                                                  |
| F10 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F10(): Integer</span>                                                 |
| F11 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F11(): Integer</span>                                                 |
| F12 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F12(): Integer</span>                                                 |
| F2 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F2(): Integer</span>                                                  |
| F3 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F3(): Integer</span>                                                  |
| F4 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F4(): Integer</span>                                                  |
| F5 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F5(): Integer</span>                                                  |
| F6 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F6(): Integer</span>                                                  |
| F7 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F7(): Integer</span>                                                  |
| F8 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F8(): Integer</span>                                                  |
| F9 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F9(): Integer</span>                                                  |
| Left Key Keycode                                                                                 |
| <span style="color: lightgray">input.keyboard.KEYCODE_LEFT(): Integer</span>                                                |
| Page Down Key Keycode                                                                            |
| <span style="color: lightgray">input.keyboard.KEYCODE_PAGEDOWN(): Integer</span>                                            |
| Page Up Key Keycode                                                                              |
| <span style="color: lightgray">input.keyboard.KEYCODE_PAGEUP(): Integer</span>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <span style="color: lightgray">input.keyboard.KEYCODE_POS1(): Integer</span>                                                |
| Return Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_RETURN(): Integer</span>                                              |
| Right Key Keycode                                                                                |
| <span style="color: lightgray">input.keyboard.KEYCODE_RIGHT(): Integer</span>                                               |
| Space Key Keycode                                                                                |
| <span style="color: lightgray">input.keyboard.KEYCODE_SPACE(): Integer</span>                                               |
| Up Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_UP(): Integer</span>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <span style="color: lightgray">input.keyboard.isKeyDown($keyCode: Integer): Boolean</span>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <span style="color: lightgray">input.keyboard.isMetaDown(): Boolean</span>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <span style="color: lightgray">input.keyboard.isShiftDown(): Boolean</span>                                                 |
| Returns last typed String                                                                        |
| <span style="color: lightgray">input.keyboard.getTypedString(): String</span>                                               |

## 7.7 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <span style="color: lightgray">input.mouse.BUTTON_LEFT(): Integer</span>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <span style="color: lightgray">input.mouse.BUTTON_MIDDLE(): Integer</span>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <span style="color: lightgray">input.mouse.BUTTON_RIGHT(): Integer</span>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <span style="color: lightgray">input.mouse.isButtonDown($button: Integer): Boolean</span>                                   |
| Returns if specific Mouse Button has been released                                               |
| <span style="color: lightgray">input.mouse.isButtonUp($button: Integer): Boolean</span>                                     |
| Returns if Mouse is dragging currently                                                           |
| <span style="color: lightgray">input.mouse.isDragging($button: Integer): Boolean</span>                                     |
| Returns if Mouse has been moved                                                                  |
| <span style="color: lightgray">input.mouse.hasMoved(): Boolean</span>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelX(): Float</span>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelY(): Float</span>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelZ(): Float</span>                                                        |
| Get X Mouse Position                                                                             |
| <span style="color: lightgray">input.mouse.getX(): Integer</span>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <span style="color: lightgray">input.mouse.getXUnscaled(): Integer</span>                                                   |
| Get Y Mouse Position                                                                             |
| <span style="color: lightgray">input.mouse.getY(): Integer</span>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <span style="color: lightgray">input.mouse.getYUnscaled(): Integer</span>                                                   |

## 7.8 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.has($logicId: String, $function: String): Boolean</span>                               |
| Get Hierarchy Id <span style="color: lightgray">(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.getHierarchyId(): String</span>                                                        |
| Get Hierarchy Parent Id <span style="color: lightgray">(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.getHierarchyParentId(): String</span>                                                  |
| Get Logic Id <span style="color: lightgray">(available in initializeEngine(), updateEngine(), initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.getId(): String</span>                                                                 |
| Call specific Logic Function <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.call($logicId: String, $function: String, ...): Mixed</span>                           |

## 7.9 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Signal has been sent                                                                  |
| <span style="color: lightgray">logic.signal.has(): Boolean</span>                                                           |
| Get Signal Argument                                                                              |
| <span style="color: lightgray">logic.signal.getArgument($argumentIndex: Integer): Mixed</span>                              |
| Get Signal Name                                                                                  |
| <span style="color: lightgray">logic.signal.getName(): String</span>                                                        |
| Advance to next Signal                                                                           |
| <span style="color: lightgray">logic.signal.next(): Void</span>                                                             |
| Send Signal <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">logic.signal.send($logicId: String, $signal: String, ...): Void</span>                       |

## 7.10 PathFinding Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Pathfinding Idle State Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_IDLE(): Integer</span>                                                     |
| Pathfinding Computing State Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_PATHFINDING(): Integer</span>                                              |
| Pathfinding Failed State Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_PATHFINDING_FAILED(): Integer</span>                                       |
| Pathfinding Computing Other Pathfinding Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_PATHFINDING_OTHER(): Integer</span>                                        |
| Pathfinding Success State Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_PATHFINDING_SUCCESS(): Integer</span>                                      |
| Pathfinding Try/Lock Failed Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.STATE_TRYLOCK_FAILED(): Integer</span>                                           |
| Issue Pathfinding <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">pathfinding.findPath($logicId: String, $startPosition: Vector3, $endPosition: Vector3, =$path: Array): Integer</span>|

## 7.11 Scene Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Scene Depth                                                                                  |
| <span style="color: lightgray">scene.getDepth(): Float</span>                                                               |
| Get Scene Height                                                                                 |
| <span style="color: lightgray">scene.getHeight(): Float</span>                                                              |
| Get Scene Width                                                                                  |
| <span style="color: lightgray">scene.getWidth(): Float</span>                                                               |

## 7.12 SceneConnector Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Attach Prototype to the Logic Hierarchy <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">sceneconnector.attachPrototype($pathName: String, $fileName: String, $id: String, $attachNodeId: String, $transform: Transform[, $parentId: String]): Void</span>|
| Spawn Prototype in Scene <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">sceneconnector.spawnPrototype($pathName: String, $fileName: String, $id: String, $transform: Transform[, $hierarchyId: String[, $hierarchyParentId: String]]): Void</span>|

## 7.13 Physics World Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Determine Height at specific Position in Physics World <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.determineHeight($collisionTypeIds: Integer, $stepUpMax: Float, $point: Vector3, =$heightPoint: Vector3[, =$bodyId: String[, $minHeight: Float[, $maxHeight: Float]]]): Boolean</span>|
| Determine Collision of Two Specific Bodies in Physics World <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.doCollide($bodyId1: String, $bodyId2: String): Boolean</span>                          |
| Compute Ray Casting in Physics World <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.doRayCasting($collisionTypeIds: Integer, $start: Vector3, $end: Vector3, =$hitPoint: Vector3[, =$bodyId: String[, $actorId: String]]): Boolean</span>|
| Determine Collision of Specific Body in Physics World <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.doesCollideWith($collisionTypeIds: Integer, $bodyId: String): Array</span>             |

## 7.14 Physics World Body Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Physics World Entity Angular Damping <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getAngularDamping($bodyId: String): Float</span>                                  |
| Set Physics World Entity Angular Damping <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setAngularDamping($bodyId: String, $angularDamping: Float): Void</span>           |
| Get Physics World Entity Angular Velocity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getAngularVelocity($bodyId: String): Vector3</span>                               |
| Set Physics World Entity Angular Velocity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setAngularVelocity($bodyId: String, $angularVelocity: Vector3): Void</span>       |
| Returns Physics World Collision Type Id 10 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_10(): Integer</span>                                             |
| Returns Physics World Collision Type Id 11 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_11(): Integer</span>                                             |
| Returns Physics World Collision Type Id 12 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_12(): Integer</span>                                             |
| Returns Physics World Collision Type Id 13 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_13(): Integer</span>                                             |
| Returns Physics World Collision Type Id 14 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_14(): Integer</span>                                             |
| Returns Physics World Collision Type Id 15 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_15(): Integer</span>                                             |
| Returns Physics World Collision Type Id 16 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_16(): Integer</span>                                             |
| Returns Physics World Collision Type Id 3 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_3(): Integer</span>                                              |
| Returns Physics World Collision Type Id 4 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_4(): Integer</span>                                              |
| Returns Physics World Collision Type Id 5 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_5(): Integer</span>                                              |
| Returns Physics World Collision Type Id 6 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_6(): Integer</span>                                              |
| Returns Physics World Collision Type Id 7 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_7(): Integer</span>                                              |
| Returns Physics World Collision Type Id 8 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_8(): Integer</span>                                              |
| Returns Physics World Collision Type Id 9 <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_9(): Integer</span>                                              |
| Returns All Physics World Collision Type Ids <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_ALL(): Integer</span>                                            |
| Returns Dynamic Physics World Collision Type Id <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_DYNAMIC(): Integer</span>                                        |
| Returns Static Physics World Collision Type Id <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.COLLISION_TYPEID_STATIC(): Integer</span>                                         |
| Get Physics World Entity own Collision Type Id <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getCollisionTypeId($bodyId: String): Integer</span>                               |
| Set Physics World Entity own Collision Type Id <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setCollisionTypeId($bodyId: String, $collisionTypeId: Integer): Void</span>       |
| Get Physics World Entity enabled Collision Type Ids <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getCollisionTypeIds($bodyId: String): Integer</span>                              |
| Set Physics World Entity enabled Collision Type Ids <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setCollisionTypeIds($bodyId: String, $collisionTypeIds: Integer): Void</span>     |
| Returns if Physics World Entity is enabled <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.isEnabled($bodyId: String): Boolean</span>                                        |
| Set Physics World Entity enabled/disabled <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setEnabled($bodyId: String, $enabled: Boolean): Void</span>                       |
| Get Physics World Entity Linear Damping <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getLinearDamping($bodyId: String): Float</span>                                   |
| Set Physics World Entity Linear Damping <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setLinearDamping($bodyId: String, $linearDamping: Float): Void</span>             |
| Get Physics World Entity Linear Velocity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getLinearVelocity($bodyId: String): Vector3</span>                                |
| Set Physics World Entity Linear Velocity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setLinearVelocity($bodyId: String, $linearVelocity: Vector3): Void</span>         |
| Returns Physics World Dynamic Collision Body Type Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.TYPE_COLLISION_DYNAMIC(): Integer</span>                                          |
| Returns Physics World Static Collision Body Type Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.TYPE_COLLISION_STATIC(): Integer</span>                                           |
| Returns Physics World Dynamic Rigid Body Type Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.TYPE_DYNAMIC(): Integer</span>                                                    |
| Returns Physics World Static Rigid Body Type Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.TYPE_STATIC(): Integer</span>                                                     |
| Get Physics World Entity Transform <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getTransform($bodyId: String): Transform</span>                                   |
| Set Physics World Entity Transform <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.setTransform($bodyId: String, $transform: Transform): Void</span>                 |
| Get Physics World Entity Body Type Integer Code <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.getType($bodyId: String): Integer</span>                                          |
| Add Force to Physics World Entity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.addForce($bodyId: String, $force: Vector3[, $origin: Vector3]): Void</span>       |
| Add Torque to Physics World Entity <span style="color: lightgray">(available in initializeLogic(), updateLogic(), onLogicAdded(), onLogicsProcessed())</span>|
| <span style="color: lightgray">world.body.addTorque($bodyId: String, $torque: Vector3): Void</span>                         |

# 8. MiniScript GUI Methods

## 8.1 Element Node Condition Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if GUI Element Node has a specific Condition enabled                                     |
| <span style="color: lightgray">gui.elementnode.conditions.has($elementNodeId: String, $condition: String): Boolean</span>   |
| Get enabled GUI Element Node Conditions                                                          |
| <span style="color: lightgray">gui.elementnode.conditions.get($elementNodeId: String): Array</span>                         |
| Set enabled GUI Element Node Condition                                                           |
| <span style="color: lightgray">gui.elementnode.conditions.set($elementNodeId: String, $condition: String): Void</span>      |
| Set Array of enabled GUI Element Node Conditions                                                 |
| <span style="color: lightgray">gui.elementnode.conditions.setAll($elementNodeId: String, $conditions: Array): Void</span>   |
| Add enabled GUI Element Node Condition                                                           |
| <span style="color: lightgray">gui.elementnode.conditions.add($elementNodeId: String, $condition: String): Void</span>      |
| Remove enabled GUI Element Node Condition                                                        |
| <span style="color: lightgray">gui.elementnode.conditions.remove($elementNodeId: String, $condition: String): Void</span>   |
| Remove All enabled GUI Element Node Conditions                                                   |
| <span style="color: lightgray">gui.elementnode.conditions.removeAll($elementNodeId: String): Void</span>                    |

## 8.2 Event Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns GUI Event Performed Action Type Integer Code                                             |
| <span style="color: lightgray">gui.event.ACTIONTYPE_PERFORMED(): Integer</span>                                             |
| Returns GUI Event Performing Action Type Integer Code                                            |
| <span style="color: lightgray">gui.event.ACTIONTYPE_PERFORMING(): Integer</span>                                            |

## 8.3 Image Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Image Source of GUI Image Node                                                               |
| <span style="color: lightgray">gui.imagenode.getSource($imageNodeId: String): String</span>                                 |
| Set Image Source of GUI Image Node                                                               |
| <span style="color: lightgray">gui.imagenode.setSource($imageNodeId: String, $source: String): Void</span>                  |

## 8.4 Node Controller Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get GUI Node Controller Value                                                                    |
| <span style="color: lightgray">gui.node.controller.getValue($nodeId: String): String</span>                                 |
| Set GUI Node Controller Value                                                                    |
| <span style="color: lightgray">gui.node.controller.setValue($nodeId: String, $value: String): Void</span>                   |

## 8.5 Parent Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Add Sub Nodes using XML to GUI Parent Node                                                       |
| <span style="color: lightgray">gui.parentnode.addSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</span>|
| Clear Sub Nodes of GUI Parent Node                                                               |
| <span style="color: lightgray">gui.parentnode.clearSubNodes($parentNodeId: String): Void</span>                             |
| Replace Sub Nodes using XML of GUI Parent Node                                                   |
| <span style="color: lightgray">gui.parentnode.replaceSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void</span>|

## 8.6 Screen Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Return if GUI Screen is enabled                                                                  |
| <span style="color: lightgray">gui.screen.isEnabled($screenId: String): Boolean</span>                                      |
| Set GUI Screen enabled/disabled                                                                  |
| <span style="color: lightgray">gui.screen.setEnabled($screenId: String, $enabled: Boolean): Void</span>                     |
| Call specific Screen Logic Function                                                              |
| <span style="color: lightgray">gui.screen.call($screenId: String, $function: String, ...): Mixed</span>                     |
| Goto current Screen to specific Screen                                                           |
| <span style="color: lightgray">gui.screen.goto($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</span>      |
| Pop current Screen from Screen Stack                                                             |
| <span style="color: lightgray">gui.screen.pop(): Void</span>                                                                |
| Push Screen to current Screen Stack                                                              |
| <span style="color: lightgray">gui.screen.push($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void</span>      |

## 8.7 Screen Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Current Screen Node Id                                                                       |
| <span style="color: lightgray">gui.screennode.getId(): String</span>                                                        |

## 8.8 Text Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Text of GUI Text Node                                                                        |
| <span style="color: lightgray">gui.textnode.getText($textNodeId: String): String</span>                                     |
| Set Text of GUI Text Node                                                                        |
| <span style="color: lightgray">gui.textnode.setText($textNodeId: String, $text: String): Void</span>                        |

## 8.9 Video Node Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Get Video Source of GUI Video Node                                                               |
| <span style="color: lightgray">gui.videonode.getSource($videoNodeId: String): String</span>                                 |
| Set Video Source of GUI Video Node                                                               |
| <span style="color: lightgray">gui.videonode.setSource($videoNodeId: String, $source: String): Void</span>                  |

## 8.10 Keyboard Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if ALT Key is currently pressed                                                          |
| <span style="color: lightgray">input.keyboard.isAltDown(): Boolean</span>                                                   |
| Returns if specific Character is currently pressed                                               |
| <span style="color: lightgray">input.keyboard.isCharDown($charAsString: String): Boolean</span>                             |
| Returns if CONTROL Key is currently pressed                                                      |
| <span style="color: lightgray">input.keyboard.isControlDown(): Boolean</span>                                               |
| Backspace Key Keycode                                                                            |
| <span style="color: lightgray">input.keyboard.KEYCODE_BACKSPACE(): Integer</span>                                           |
| Delete Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_DELETE(): Integer</span>                                              |
| Down Key Keycode                                                                                 |
| <span style="color: lightgray">input.keyboard.KEYCODE_DOWN(): Integer</span>                                                |
| End Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_END(): Integer</span>                                                 |
| Escape Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_ESCAPE(): Integer</span>                                              |
| F1 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F1(): Integer</span>                                                  |
| F10 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F10(): Integer</span>                                                 |
| F11 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F11(): Integer</span>                                                 |
| F12 Key Keycode                                                                                  |
| <span style="color: lightgray">input.keyboard.KEYCODE_F12(): Integer</span>                                                 |
| F2 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F2(): Integer</span>                                                  |
| F3 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F3(): Integer</span>                                                  |
| F4 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F4(): Integer</span>                                                  |
| F5 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F5(): Integer</span>                                                  |
| F6 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F6(): Integer</span>                                                  |
| F7 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F7(): Integer</span>                                                  |
| F8 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F8(): Integer</span>                                                  |
| F9 Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_F9(): Integer</span>                                                  |
| Left Key Keycode                                                                                 |
| <span style="color: lightgray">input.keyboard.KEYCODE_LEFT(): Integer</span>                                                |
| Page Down Key Keycode                                                                            |
| <span style="color: lightgray">input.keyboard.KEYCODE_PAGEDOWN(): Integer</span>                                            |
| Page Up Key Keycode                                                                              |
| <span style="color: lightgray">input.keyboard.KEYCODE_PAGEUP(): Integer</span>                                              |
| Home/Position 1 Key Keycode                                                                      |
| <span style="color: lightgray">input.keyboard.KEYCODE_POS1(): Integer</span>                                                |
| Return Key Keycode                                                                               |
| <span style="color: lightgray">input.keyboard.KEYCODE_RETURN(): Integer</span>                                              |
| Right Key Keycode                                                                                |
| <span style="color: lightgray">input.keyboard.KEYCODE_RIGHT(): Integer</span>                                               |
| Space Key Keycode                                                                                |
| <span style="color: lightgray">input.keyboard.KEYCODE_SPACE(): Integer</span>                                               |
| Up Key Keycode                                                                                   |
| <span style="color: lightgray">input.keyboard.KEYCODE_UP(): Integer</span>                                                  |
| Returns if specific Key is currently pressed                                                     |
| <span style="color: lightgray">input.keyboard.isKeyDown($keyCode: Integer): Boolean</span>                                  |
| Returns if Meta Key is currently pressed                                                         |
| <span style="color: lightgray">input.keyboard.isMetaDown(): Boolean</span>                                                  |
| Returns if Shift Key is currently pressed                                                        |
| <span style="color: lightgray">input.keyboard.isShiftDown(): Boolean</span>                                                 |
| Returns last typed String                                                                        |
| <span style="color: lightgray">input.keyboard.getTypedString(): String</span>                                               |

## 8.11 Mouse Input Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Left Mouse Button Integer Code                                                                   |
| <span style="color: lightgray">input.mouse.BUTTON_LEFT(): Integer</span>                                                    |
| Middle Mouse Button Integer Code                                                                 |
| <span style="color: lightgray">input.mouse.BUTTON_MIDDLE(): Integer</span>                                                  |
| Right Mouse Button Integer Code                                                                  |
| <span style="color: lightgray">input.mouse.BUTTON_RIGHT(): Integer</span>                                                   |
| Returns if specific Mouse Button is currently pressed                                            |
| <span style="color: lightgray">input.mouse.isButtonDown($button: Integer): Boolean</span>                                   |
| Returns if specific Mouse Button has been released                                               |
| <span style="color: lightgray">input.mouse.isButtonUp($button: Integer): Boolean</span>                                     |
| Returns if Mouse is dragging currently                                                           |
| <span style="color: lightgray">input.mouse.isDragging($button: Integer): Boolean</span>                                     |
| Returns if Mouse has been moved                                                                  |
| <span style="color: lightgray">input.mouse.hasMoved(): Boolean</span>                                                       |
| Returns current Value of X Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelX(): Float</span>                                                        |
| Returns current Value of Y Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelY(): Float</span>                                                        |
| Returns current Value of Z Axis Mouse Wheel                                                      |
| <span style="color: lightgray">input.mouse.getWheelZ(): Float</span>                                                        |
| Get X Mouse Position                                                                             |
| <span style="color: lightgray">input.mouse.getX(): Integer</span>                                                           |
| Get Unscaled X Mouse Position                                                                    |
| <span style="color: lightgray">input.mouse.getXUnscaled(): Integer</span>                                                   |
| Get Y Mouse Position                                                                             |
| <span style="color: lightgray">input.mouse.getY(): Integer</span>                                                           |
| Get Unscaled Y Mouse Position                                                                    |
| <span style="color: lightgray">input.mouse.getYUnscaled(): Integer</span>                                                   |

## 8.12 Logic Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Returns if Logic has Function                                                                    |
| <span style="color: lightgray">logic.has($logicId: String, $function: String): Boolean</span>                               |
| Call specific Logic Function                                                                     |
| <span style="color: lightgray">logic.call($logicId: String, $function: String, ...): Mixed</span>                           |

## 8.13 Logic Signal Methods

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Send Signal                                                                                      |
| <span style="color: lightgray">logic.signal.send($logicId: String, $signal: String, ...): Void</span>                       |

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
