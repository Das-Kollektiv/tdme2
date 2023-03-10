![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is the documentation of MiniScript language. This document is WIP.

# 1. Introduction

Introduction to MiniScript language features:
- very small implementation of a scripting language
- runs on every CPU, OS, ... due to its simplicity, so its highly portable just like TDME2 is
- can be easily extended by writing state machine machine states and script methods in C++
- works with the following data types: boolean, integer, float, string, vector2, vector3, vector4, quaternion, matrix3x3, matrix4x4, transform, array, map and set
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
		$i = $i + 1
	end
...
```

forCondition takes a single boolean value as argument. The loop will be executed as long as the argument is true. In this case "$i < 5" translates to "lesser($i, 5)" which results in a boolean value, which is used as the forCondition argument. See example of forCondition() below.
```
...
	$i = 0
	forCondition($i < 5)
		console.log("$ = ", $i)
		$i = $i + 1
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
		$i = $i + 1
	end
...
```

Iterating arrays using array.length() and [] operator:
```
...
	$i = 0
	forCondition($i < array.length($array))
		console.log($i + ": " + $array[$i])
		$i = $i + 1
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
		$i = $i + 1
	end
...
```

## 4.5. Sets

A set is value storage using a underlying hash set. Keys can only exist once in a set.

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

# 6. MiniScript methods

| Methods                                                                                          |
|--------------------------------------------------------------------------------------------------|
| getVariable($variable: String): Mixed                                                            |
| setVariable($variable: String, $value: Mixed): Mixed                                             |
| unsetVariable($variable: String): Void                                                           |
| add($a: Mixed, $b: Mixed): Mixed                                                                 |
| and($a: Boolean, $b: Boolean): Boolean                                                           |
| array(...): Array                                                                                |
| array.get($array: Array, $index: Integer): Mixed                                                 |
| array.set(=$array: Array, $index: Integer, ...): Void                                            |
| array.indexOf($array: Array, $value: String[, $beginIndex: Integer, ...]): Integer               |
| array.length($array: Array): Integer                                                             |
| array.push(=$array: Array, ...): Void                                                            |
| array.remove(=$array: Array, $index: Integer): Void                                              |
| array.removeOf(=$array: Array, $value: String[, $beginIndex: Integer]): Void                     |
| array.reverse(=$array: Array): Void                                                              |
| array.sort(=$array: Array, $function: String): Void                                              |
| bool($bool: Boolean): Boolean                                                                    |
| console.log(...): Void                                                                           |
| div($a: Mixed, $b: Mixed): Mixed                                                                 |
| else(): Void                                                                                     |
| elseif($condition: Boolean): Void                                                                |
| end(): Void                                                                                      |
| equals($a: Mixed, $b: Mixed): Boolean                                                            |
| float($float: Float): Float                                                                      |
| forCondition($condition: Boolean): Void                                                          |
| forTime($time: Integer): Void                                                                    |
| greater($a: Mixed, $b: Mixed): Boolean                                                           |
| greaterequals($a: Mixed, $b: Mixed): Boolean                                                     |
| if($condition: Boolean): Void                                                                    |
| int($int: Integer): Integer                                                                      |
| json.deserialize($json: String): Mixed                                                           |
| json.serialize($value: Mixed): String                                                            |
| lesser($a: Mixed, $b: Mixed): Boolean                                                            |
| lesserequals($a: Mixed, $b: Mixed): Boolean                                                      |
| map(): Map                                                                                       |
| map.has($map: Map, $key: String): Boolean                                                        |
| map.get($map: Map, $key: String): Mixed                                                          |
| map.set(=$map: Map, $key: String, ...): Void                                                     |
| map.getKeys($map: Map): Array                                                                    |
| map.getValues($map: Map): Array                                                                  |
| map.remove(=$map: Map, $key: String): Void                                                       |
| mat3.identity(): Matrix3x3                                                                       |
| mat3.multiply($mat3: Matrix3x3, ...): Mixed                                                      |
| mat3.rotate($angle: Float): Matrix3x3                                                            |
| mat3.rotateAroundPoint($point: Vector2, $angle: Float): Matrix3x3                                |
| mat3.rotateAroundTextureCenter($angle: Float): Matrix3x3                                         |
| mat3.scale(...): Matrix3x3                                                                       |
| mat3.translate($translation: Vector2): Matrix3x3                                                 |
| mat4.computeEulerAngles($mat4: Matrix4x4): Vector3                                               |
| mat4.identity(): Matrix4x4                                                                       |
| mat4.invert($mat4: Matrix4x4): Matrix4x4                                                         |
| mat4.multiply($mat4: Matrix4x4, ...): Mixed                                                      |
| mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4                                            |
| mat4.scale(...): Matrix4x4                                                                       |
| mat4.translate($translation: Vector3): Matrix4x4                                                 |
| math.DEG2RAD(): Float                                                                            |
| math.EPSILON(): Float                                                                            |
| math.G(): Float                                                                                  |
| math.PI(): Float                                                                                 |
| math.abs($value: Number): Number                                                                 |
| math.absmod($value: Float, $range: Float): Float                                                 |
| math.acos($value: Float): Float                                                                  |
| math.asin($value: Float): Float                                                                  |
| math.atan($value: Float): Float                                                                  |
| math.atan2($y: Float, $x: Float): Float                                                          |
| math.ceil($value: Float): Float                                                                  |
| math.clamp($value: Number, $min: Number, $max: Number): Number                                   |
| math.cos($value: Float): Float                                                                   |
| math.exp($value: Float): Float                                                                   |
| math.floor($value: Float): Float                                                                 |
| math.log($value: Float): Float                                                                   |
| math.max($a: Number, $b: Number): Number                                                         |
| math.min($a: Number, $b: Number): Number                                                         |
| math.mod($value: Float, $range: Float): Float                                                    |
| math.pow($a: Number, $b: Number): Number                                                         |
| math.random(): Float                                                                             |
| math.round($value: Float): Float                                                                 |
| math.sign($value: Number): Number                                                                |
| math.sin($value: Float): Float                                                                   |
| math.sqrt($value: Float): Float                                                                  |
| math.square($value: Number): Number                                                              |
| math.tan($value: Float): Float                                                                   |
| mul($a: Mixed, $b: Mixed): Mixed                                                                 |
| not($bool: Boolean): Boolean                                                                     |
| notequal($a: Mixed, $b: Mixed): Boolean                                                          |
| or($a: Boolean, $b: Boolean): Boolean                                                            |
| quaternion.computeMatrix($quaternion: Quaternion): Matrix4x4                                     |
| quaternion.identity(): Quaternion                                                                |
| quaternion.invert($quaternion: Vector4): Quaternion                                              |
| quaternion.multiply($quaternion: Quaternion, ...): Mixed                                         |
| quaternion.normalize($quaternion: Quaternion): Quaternion                                        |
| quaternion.rotate($axis: Vector3, $angle: Float): Quaternion                                     |
| return([$value: Mixed]): Void                                                                    |
| script.getNamedConditions(): String                                                              |
| script.getVariables(): Map                                                                       |
| script.call($function: String, ...): Mixed                                                       |
| script.disableNamedCondition($name: String): Void                                                |
| script.emit($condition: String): Void                                                            |
| script.enableNamedCondition($name: String): Void                                                 |
| script.evaluate($statement: String): Mixed                                                       |
| script.stop(): Void                                                                              |
| script.wait($time: Integer): Void                                                                |
| script.waitForCondition(): Void                                                                  |
| set(): Set                                                                                       |
| set.has($set: Set, $key: String): Boolean                                                        |
| set.getKeys($set: Set): Array                                                                    |
| set.insert(=$set: Set, $key: String): Void                                                       |
| set.remove(=$set: Set, $key: String): Void                                                       |
| string($string: String): String                                                                  |
| string.isFloat($string: String): Boolean                                                         |
| string.isInteger($string: String): Boolean                                                       |
| string.charAt($string: String, $index: Integer): String                                          |
| string.concatenate(...): String                                                                  |
| string.endsWith($string: String, $suffix: String): Boolean                                       |
| string.equalsIgnoreCase($string1: String, $string2: String): Boolean                             |
| string.firstIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer             |
| string.indexOf($string: String, $what: String[, $beginIndex: Integer]): Integer                  |
| string.lastIndexOf($string: String, $what: String[, $beginIndex: Integer]): Integer              |
| string.length($string: String): Integer                                                          |
| string.regexMatch($string: String, $pattern: String): Boolean                                    |
| string.regexReplace($string: String, $pattern: String, $by: String): String                      |
| string.replace($string: String, $what: String, $by: String[, $beginIndex: Integer]): String      |
| string.space([$spaces: Integer]): String                                                         |
| string.startsWith($string: String, $prefix: String): Boolean                                     |
| string.substring($string: String, $beginIndex: Integer[, $endIndex: Integer]): String            |
| string.toLowerCase($string: String): String                                                      |
| string.toUpperCase($string: String): String                                                      |
| string.tokenize($string: String, $delimiters: String): Array                                     |
| string.trim($string: String): String                                                             |
| sub($a: Mixed, $b: Mixed): Mixed                                                                 |
| time.getAsString([$format: String]): String                                                      |
| time.getCurrentMillis(): Integer                                                                 |
| transform([$translation: Vector3[, $scale: Vector3[, $rotationZ: Float[, $rotationY: Float[, $rotationX: Float]]]]]): Transform|
| transform.AXIS_X(): Vector3                                                                      |
| transform.AXIS_Y(): Vector3                                                                      |
| transform.AXIS_Z(): Vector3                                                                      |
| transform.getRotationAngle($transform: Transform, $idx: Integer): Float                          |
| transform.setRotationAngle(=$transform: Transform, $idx: Integer, $angle: Float): Void           |
| transform.getRotationAxis($transform: Transform, $idx: Integer): Vector3                         |
| transform.getRotationsQuaternion($transform: Transform): Quaternion                              |
| transform.getScale($transform: Transform): Vector3                                               |
| transform.setScale(=$transform: Transform, $scale: Vector3): Void                                |
| transform.getTransformMatrix($transform: Transform): Matrix4x4                                   |
| transform.getTranslation($transform: Transform): Vector3                                         |
| transform.setTranslation(=$transform: Transform, $translation: Vector3): Void                    |
| transform.applyRotation(=$transform: Transform, $axis: Vector3, $angle: Float): Void             |
| transform.fromMatrix($transformMatrix: Matrix4x4): Transform                                     |
| transform.interpolateRotation($currentAngle: Float, $targetAngle: Float, $timePassedSeconds: Float, $degreesPerSeconds: Float, =$interpolatedAngle: Float): Boolean|
| transform.multiply($transform: Transform, $vec3: Vector3): Vector3                               |
| transform.rotate($transform: Transform, $vec3: Vector3): Vector3                                 |
| vec2($x: Float, $y: Float): Vector2                                                              |
| vec2.computeDotProduct($a: Vector2, $b: Vector2): Float                                          |
| vec2.computeLength($vec2: Vector2): Float                                                        |
| vec2.computeLengthSquared($vec2: Vector2): Float                                                 |
| vec2.getX($vec2: Vector2): Float                                                                 |
| vec2.getY($vec2: Vector2): Float                                                                 |
| vec2.normalize($vec2: Vector2): Vector2                                                          |
| vec3($x: Float, $y: Float, $z: Float): Vector3                                                   |
| vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float                                  |
| vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3                                      |
| vec3.computeDotProduct($a: Vector3, $b: Vector3): Float                                          |
| vec3.computeLength($vec3: Vector3): Float                                                        |
| vec3.computeLengthSquared($vec3: Vector3): Float                                                 |
| vec3.getX($vec3: Vector3): Float                                                                 |
| vec3.getY($vec3: Vector3): Float                                                                 |
| vec3.getZ($vec3: Vector3): Float                                                                 |
| vec3.normalize($vec3: Vector3): Vector3                                                          |
| vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4                                        |
| vec4.computeDotProduct($a: Vector4, $b: Vector4): Float                                          |
| vec4.computeLength($vec4: Vector4): Float                                                        |
| vec4.computeLengthSquared($vec4: Vector4): Float                                                 |
| vec4.getW($vec4: Vector4): Float                                                                 |
| vec4.getX($vec4: Vector4): Float                                                                 |
| vec4.getY($vec4: Vector4): Float                                                                 |
| vec4.getZ($vec4: Vector4): Float                                                                 |
| vec4.normalize($vec4: Vector4): Vector4                                                          |
| xml.createTag($name: String[, $attributes: Map[, $innerXML: String]]): String                    |

# 7. MiniScript logic methods

| MiniScript logic methods                                                                         |
|--------------------------------------------------------------------------------------------------|
| engine.getEntityIdByMousePosition($mouseX: Integer, $mouseY: Integer): String                    |
| engine.getHeight(): Integer                                                                      |
| engine.computeScreenCoordinateByWorldCoordinate($worldCoodinate: Vector3, =$screenCoordinate: Vector2): Boolean|
| engine.getWidth(): Integer                                                                       |
| engine.computeWorldCoordinateByMousePosition($mouseX: Integer, $mouseY: Integer): Vector3        |
| engine.camera.getFovX(): Float                                                                   |
| engine.camera.setFovX($fovX: Float): Void                                                        |
| engine.camera.getLookAt(): Vector3                                                               |
| engine.camera.setLookAt($lookAt: Vector3): Void                                                  |
| engine.camera.getLookFrom(): Vector3                                                             |
| engine.camera.setLookFrom($lookFrom: Vector3): Void                                              |
| engine.camera.getUpVector(): Vector3                                                             |
| engine.camera.setUpVector($upVector: Vector3): Void                                              |
| engine.camera.computeUpVector($lookFrom: Vector3, $lookAt: Vector3): Vector3                     |
| engine.entity.getAnimation($entityId: String[, $childEntityId: String]): String                  |
| engine.entity.setAnimation($entityId: String, $animation: String[, $speed: Float[, $childEntityId: String]]): Void|
| engine.entity.setAnimationSpeed($entityId: String, $speed: Float[, $childEntityId: String]): Void|
| engine.entity.getAnimationTime($entityId: String[, $childEntityId: String]): Float               |
| engine.entity.getEffectColorAdd($entityId: String[, $childEntityId: String]): Vector4            |
| engine.entity.setEffectColorAdd($entityId: String, $effectColorAdd: Vector4[, $childEntityId: String]): Void|
| engine.entity.getEffectColorMul($entityId: String[, $childEntityId: String]): Vector4            |
| engine.entity.setEffectColorMul($entityId: String, $effectColorMul: Vector4[, $childEntityId: String]): Void|
| engine.entity.isEnabled($entityId: String[, $childEntityId: String]): Boolean                    |
| engine.entity.setEnabled($entityId: String, $enabled: Boolean[, $childEntityId: String]): Void   |
| engine.entity.getNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Transform|
| engine.entity.setNodeTransform($entityId: String, $nodeId: String, $transform: Transform[, $childEntityId: String]): Void|
| engine.entity.unsetNodeTransform($entityId: String, $nodeId: String[, $childEntityId: String]): Void|
| engine.entity.getNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Matrix4x4|
| engine.entity.setNodeTransformMatrix($entityId: String, $nodeId: String, $matrix: Matrix4x4[, $childEntityId: String]): Void|
| engine.entity.unsetNodeTransformMatrix($entityId: String, $nodeId: String[, $childEntityId: String]): Void|
| engine.entity.hasOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Boolean|
| engine.entity.getOverlayAnimationTime($entityId: String, $animation: String[, $childEntityId: String]): Float|
| engine.entity.isPickable($entityId: String[, $childEntityId: String]): Boolean                   |
| engine.entity.setPickable($entityId: String, $pickable: Boolean[, $childEntityId: String]): Void |
| engine.entity.getTransform($entityId: String[, $childEntityId: String]): Transform               |
| engine.entity.setTransform($entityId: String, $transform: Transform[, $childEntityId: String]): Void|
| engine.entity.addOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void|
| engine.entity.emitParticles($entityId: String[, $childEntityId: String]): Integer                |
| engine.entity.removeFinishedOverlayAnimations($entityId: String[, $childEntityId: String]): Void |
| engine.entity.removeOverlayAnimation($entityId: String, $animation: String[, $childEntityId: String]): Void|
| engine.entity.removeOverlayAnimations($entityId: String[, $childEntityId: String]): Void         |
| engine.timing.getAvarageFPS(): Float                                                             |
| engine.timing.getDeltaTime(): Integer                                                            |
| engine.timing.getDeltaTimeSeconds(): Float                                                       |
| input.keyboard.isAltDown(): Boolean                                                              |
| input.keyboard.isCharDown($charAsString: String): Boolean                                        |
| input.keyboard.isControlDown(): Boolean                                                          |
| input.keyboard.KEYCODE_BACKSPACE(): Integer                                                      |
| input.keyboard.KEYCODE_DELETE(): Integer                                                         |
| input.keyboard.KEYCODE_DOWN(): Integer                                                           |
| input.keyboard.KEYCODE_END(): Integer                                                            |
| input.keyboard.KEYCODE_ESCAPE(): Integer                                                         |
| input.keyboard.KEYCODE_F1(): Integer                                                             |
| input.keyboard.KEYCODE_F10(): Integer                                                            |
| input.keyboard.KEYCODE_F11(): Integer                                                            |
| input.keyboard.KEYCODE_F12(): Integer                                                            |
| input.keyboard.KEYCODE_F2(): Integer                                                             |
| input.keyboard.KEYCODE_F3(): Integer                                                             |
| input.keyboard.KEYCODE_F4(): Integer                                                             |
| input.keyboard.KEYCODE_F5(): Integer                                                             |
| input.keyboard.KEYCODE_F6(): Integer                                                             |
| input.keyboard.KEYCODE_F7(): Integer                                                             |
| input.keyboard.KEYCODE_F8(): Integer                                                             |
| input.keyboard.KEYCODE_F9(): Integer                                                             |
| input.keyboard.KEYCODE_LEFT(): Integer                                                           |
| input.keyboard.KEYCODE_PAGEDOWN(): Integer                                                       |
| input.keyboard.KEYCODE_PAGEUP(): Integer                                                         |
| input.keyboard.KEYCODE_POS1(): Integer                                                           |
| input.keyboard.KEYCODE_RETURN(): Integer                                                         |
| input.keyboard.KEYCODE_RIGHT(): Integer                                                          |
| input.keyboard.KEYCODE_SPACE(): Integer                                                          |
| input.keyboard.KEYCODE_UP(): Integer                                                             |
| input.keyboard.isKeyDown($keyCode: Integer): Boolean                                             |
| input.keyboard.isMetaDown(): Boolean                                                             |
| input.keyboard.isShiftDown(): Boolean                                                            |
| input.keyboard.getTypedString(): String                                                          |
| input.mouse.BUTTON_LEFT(): Integer                                                               |
| input.mouse.BUTTON_MIDDLE(): Integer                                                             |
| input.mouse.BUTTON_RIGHT(): Integer                                                              |
| input.mouse.isButtonDown($button: Integer): Boolean                                              |
| input.mouse.isButtonUp($button: Integer): Boolean                                                |
| input.mouse.isDragging($button: Integer): Boolean                                                |
| input.mouse.hasMoved(): Boolean                                                                  |
| input.mouse.getWheelX(): Float                                                                   |
| input.mouse.getWheelY(): Float                                                                   |
| input.mouse.getWheelZ(): Float                                                                   |
| input.mouse.getX(): Integer                                                                      |
| input.mouse.getXUnscaled(): Integer                                                              |
| input.mouse.getY(): Integer                                                                      |
| input.mouse.getYUnscaled(): Integer                                                              |
| logic.getId(): String                                                                            |
| logic.call($logicId: String, $function: String, ...): Mixed                                      |
| logic.signal.has(): Boolean                                                                      |
| logic.signal.getArgument($argumentIndex: Integer): Mixed                                         |
| logic.signal.getName(): String                                                                   |
| logic.signal.next(): Void                                                                        |
| logic.signal.send($logicId: String, $signal: String, ...): Void                                  |
| pathfinding.STATE_IDLE(): Integer                                                                |
| pathfinding.STATE_PATHFINDING(): Integer                                                         |
| pathfinding.STATE_PATHFINDING_FAILED(): Integer                                                  |
| pathfinding.STATE_PATHFINDING_OTHER(): Integer                                                   |
| pathfinding.STATE_PATHFINDING_SUCCESS(): Integer                                                 |
| pathfinding.STATE_TRYLOCK_FAILED(): Integer                                                      |
| pathfinding.findPath($logicId: String, $startPosition: Vector3, $endPosition: Vector3, =$path: Array): Integer|
| sceneconnector.addPrototype($pathName: String, $fileName: String, $id: String, $transform: Transform[, $entityHierarchyId: String[, $entityHierarchyParentId: String]]): Void|
| world.body.getAngularDamping($bodyId: String): Float                                             |
| world.body.setAngularDamping($bodyId: String, $angularDamping: Float): Void                      |
| world.body.getAngularVelocity($bodyId: String): Vector3                                          |
| world.body.setAngularVelocity($bodyId: String, $angularVelocity: Vector3): Void                  |
| world.body.COLLISION_TYPEID_10(): Integer                                                        |
| world.body.COLLISION_TYPEID_11(): Integer                                                        |
| world.body.COLLISION_TYPEID_12(): Integer                                                        |
| world.body.COLLISION_TYPEID_13(): Integer                                                        |
| world.body.COLLISION_TYPEID_14(): Integer                                                        |
| world.body.COLLISION_TYPEID_15(): Integer                                                        |
| world.body.COLLISION_TYPEID_16(): Integer                                                        |
| world.body.COLLISION_TYPEID_3(): Integer                                                         |
| world.body.COLLISION_TYPEID_4(): Integer                                                         |
| world.body.COLLISION_TYPEID_5(): Integer                                                         |
| world.body.COLLISION_TYPEID_6(): Integer                                                         |
| world.body.COLLISION_TYPEID_7(): Integer                                                         |
| world.body.COLLISION_TYPEID_8(): Integer                                                         |
| world.body.COLLISION_TYPEID_9(): Integer                                                         |
| world.body.COLLISION_TYPEID_ALL(): Integer                                                       |
| world.body.COLLISION_TYPEID_DYNAMIC(): Integer                                                   |
| world.body.COLLISION_TYPEID_STATIC(): Integer                                                    |
| world.body.getCollisionTypeId($bodyId: String): Integer                                          |
| world.body.setCollisionTypeId($bodyId: String, $collisionTypeId: Integer): Void                  |
| world.body.getCollisionTypeIds($bodyId: String): Integer                                         |
| world.body.setCollisionTypeIds($bodyId: String, $collisionTypeIds: Integer): Void                |
| world.body.isEnabled($bodyId: String): Boolean                                                   |
| world.body.setEnabled($bodyId: String, $enabled: Boolean): Void                                  |
| world.body.getLinearDamping($bodyId: String): Float                                              |
| world.body.setLinearDamping($bodyId: String, $linearDamping: Float): Void                        |
| world.body.getLinearVelocity($bodyId: String): Vector3                                           |
| world.body.setLinearVelocity($bodyId: String, $linearVelocity: Vector3): Void                    |
| world.body.TYPE_COLLISION(): Integer                                                             |
| world.body.TYPE_DYNAMIC(): Integer                                                               |
| world.body.TYPE_STATIC(): Integer                                                                |
| world.body.getTransform($bodyId: String): Transform                                              |
| world.body.setTransform($bodyId: String, $transform: Transform): Void                            |
| world.body.getType($bodyId: String): Integer                                                     |
| world.body.addForce($bodyId: String, $force: Vector3[, $origin: Vector3]): Void                  |
| world.body.addTorque($bodyId: String, $torque: Vector3): Void                                    |
| world.determineHeight($collisionTypeIds: Integer, $stepUpMax: Float, $point: Vector3, =$heightPoint: Vector3[, =$bodyId: String[, $minHeight: Float[, $maxHeight: Float]]]): Boolean|
| world.doCollide($bodyId1: String, $bodyId2: String): Boolean                                     |
| world.doRayCasting($collisionTypeIds: Integer, $start: Vector3, $end: Vector3, =$hitPoint: Vector3, =$bodyId: String[, $actorId: String]): Boolean|
| world.doesCollideWith($collisionTypeIds: Integer, $bodyId: String): Array                        |

# 8. MiniScript GUI methods

| MiniScript GUI methods                                                                           |
|--------------------------------------------------------------------------------------------------|
| gui.elementnode.conditions.has($elementNodeId: String, $condition: String): Boolean              |
| gui.elementnode.conditions.get($elementNodeId: String): Array                                    |
| gui.elementnode.conditions.set($elementNodeId: String, $condition: String): Void                 |
| gui.elementnode.conditions.setAll($elementNodeId: String, $conditions: Array): Void              |
| gui.elementnode.conditions.add($elementNodeId: String, $condition: String): Void                 |
| gui.elementnode.conditions.remove($elementNodeId: String, $condition: String): Void              |
| gui.elementnode.conditions.removeAll($elementNodeId: String): Void                               |
| gui.event.ACTIONTYPE_PERFORMED(): Integer                                                        |
| gui.event.ACTIONTYPE_PERFORMING(): Integer                                                       |
| gui.imagenode.getSource($imageNodeId: String): String                                            |
| gui.imagenode.setSource($imageNodeId: String, $source: String): Void                             |
| gui.node.controller.getValue($nodeId: String): String                                            |
| gui.node.controller.setValue($nodeId: String, $value: String): Void                              |
| gui.parentnode.addSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void|
| gui.parentnode.clearSubNodes($parentNodeId: String): Void                                        |
| gui.parentnode.replaceSubNodes($parentNodeId: String, $xml: String[, $resetScrollOffsets: Boolean]): Void|
| gui.screen.isEnabled($screenId: String): Boolean                                                 |
| gui.screen.setEnabled($screenId: String, $enabled: Boolean): Void                                |
| gui.screen.call($screenId: String, $function: String, ...): Mixed                                |
| gui.screen.goto($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void                 |
| gui.screen.pop(): Void                                                                           |
| gui.screen.push($fileName: String[, $variables: Map[, $arguments: Mixed]]): Void                 |
| gui.screennode.getId(): String                                                                   |
| gui.textnode.getText($textNodeId: String): String                                                |
| gui.textnode.setText($textNodeId: String, $text: String): Void                                   |
| gui.videonode.getSource($videoNodeId: String): String                                            |
| gui.videonode.setSource($videoNodeId: String, $source: String): Void                             |
| input.keyboard.isAltDown(): Boolean                                                              |
| input.keyboard.isCharDown($charAsString: String): Boolean                                        |
| input.keyboard.isControlDown(): Boolean                                                          |
| input.keyboard.KEYCODE_BACKSPACE(): Integer                                                      |
| input.keyboard.KEYCODE_DELETE(): Integer                                                         |
| input.keyboard.KEYCODE_DOWN(): Integer                                                           |
| input.keyboard.KEYCODE_END(): Integer                                                            |
| input.keyboard.KEYCODE_ESCAPE(): Integer                                                         |
| input.keyboard.KEYCODE_F1(): Integer                                                             |
| input.keyboard.KEYCODE_F10(): Integer                                                            |
| input.keyboard.KEYCODE_F11(): Integer                                                            |
| input.keyboard.KEYCODE_F12(): Integer                                                            |
| input.keyboard.KEYCODE_F2(): Integer                                                             |
| input.keyboard.KEYCODE_F3(): Integer                                                             |
| input.keyboard.KEYCODE_F4(): Integer                                                             |
| input.keyboard.KEYCODE_F5(): Integer                                                             |
| input.keyboard.KEYCODE_F6(): Integer                                                             |
| input.keyboard.KEYCODE_F7(): Integer                                                             |
| input.keyboard.KEYCODE_F8(): Integer                                                             |
| input.keyboard.KEYCODE_F9(): Integer                                                             |
| input.keyboard.KEYCODE_LEFT(): Integer                                                           |
| input.keyboard.KEYCODE_PAGEDOWN(): Integer                                                       |
| input.keyboard.KEYCODE_PAGEUP(): Integer                                                         |
| input.keyboard.KEYCODE_POS1(): Integer                                                           |
| input.keyboard.KEYCODE_RETURN(): Integer                                                         |
| input.keyboard.KEYCODE_RIGHT(): Integer                                                          |
| input.keyboard.KEYCODE_SPACE(): Integer                                                          |
| input.keyboard.KEYCODE_UP(): Integer                                                             |
| input.keyboard.isKeyDown($keyCode: Integer): Boolean                                             |
| input.keyboard.isMetaDown(): Boolean                                                             |
| input.keyboard.isShiftDown(): Boolean                                                            |
| input.keyboard.getTypedString(): String                                                          |
| input.mouse.BUTTON_LEFT(): Integer                                                               |
| input.mouse.BUTTON_MIDDLE(): Integer                                                             |
| input.mouse.BUTTON_RIGHT(): Integer                                                              |
| input.mouse.isButtonDown($button: Integer): Boolean                                              |
| input.mouse.isButtonUp($button: Integer): Boolean                                                |
| input.mouse.isDragging($button: Integer): Boolean                                                |
| input.mouse.hasMoved(): Boolean                                                                  |
| input.mouse.getWheelX(): Float                                                                   |
| input.mouse.getWheelY(): Float                                                                   |
| input.mouse.getWheelZ(): Float                                                                   |
| input.mouse.getX(): Integer                                                                      |
| input.mouse.getXUnscaled(): Integer                                                              |
| input.mouse.getY(): Integer                                                                      |
| input.mouse.getYUnscaled(): Integer                                                              |
| logic.call($logicId: String, $function: String, ...): Mixed                                      |
| logic.signal.send($logicId: String, $signal: String, ...): Void                                  |

# 9. Operators

| Op | Method                                                                                      |
|----|---------------------------------------------------------------------------------------------|
| !  | not($bool: Boolean): Boolean                                                                |
| != | notequal($a: Mixed, $b: Mixed): Boolean                                                     |
| && | and($a: Boolean, $b: Boolean): Boolean                                                      |
| *  | mul($a: Mixed, $b: Mixed): Mixed                                                            |
| +  | add($a: Mixed, $b: Mixed): Mixed                                                            |
| -  | sub($a: Mixed, $b: Mixed): Mixed                                                            |
| /  | div($a: Mixed, $b: Mixed): Mixed                                                            |
| <  | lesser($a: Mixed, $b: Mixed): Boolean                                                       |
| <= | lesserequals($a: Mixed, $b: Mixed): Boolean                                                 |
| =  | setVariable($variable: String, $value: Mixed): Mixed                                        |
| == | equals($a: Mixed, $b: Mixed): Boolean                                                       |
| >  | greater($a: Mixed, $b: Mixed): Boolean                                                      |
| >= | greaterequals($a: Mixed, $b: Mixed): Boolean                                                |
| \|\|| or($a: Boolean, $b: Boolean): Boolean                                                      |
