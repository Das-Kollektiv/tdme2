![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Data types, variables and constants

Default MinitScript works with the following data types:
- boolean
- integer
- float
- string
- array
- map
- set
- ...

Variable and constant identifiers always start with a "$".
You can manually set variables with the setVariable("$variableName", ...) or constants with setConstant("$CONSTANT", ...) methods.

## 1.1. Primitive data types

The following primitive data types are available: boolean, integer, float.

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

The primitive data types can also be assigned by using initialization methods that return explicitly those primitive data types:

```
...
	$boolean = boolean(true)
	$boolean = boolean(false)
...
```

```
...
	$integer = integer(123)
...
```

```
...
	$float = float(456.789)
...
```

## 1.2. Additional data types

Additionally we have string, array, set and map datatypes.

### 1.2.1. String

See how to initialize a string.

```
...
	$string = "This is my mighty string"
...
```

For further usage see [String class](./README-BuiltIn-Classes.md#11-string-class) documentation.

### 1.2.2. Array

An array is a sequence of values which can be accessed by indices.

Initializing an array by array initializer:

```
...
	$array = [1, 2, 3]
...
```

Initializing an array by constructor:

```
...
	$array = Array()
...
```

... or initialize and push values to it:

```
...
	$array = Array(1, 2, 3)
...
```

Pushing values using Array::push():

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

Removing values from arrays using Array::removeOf():

```
...
	$array->removeOf(6)
	$array->removeOf(7)
...
```

Removing from arrays using a index with Array::remove():

```
...
	$array->remove(2)
...
```

Iterating arrays using Array::length() and Array::get():

```
...
	$i = 0
	forCondition($i < $array->length())
		console.printLine($i + ": " + $array->get($i))
		++$i
	end
...
```

Iterating arrays using Array::length() and [] operator:

```
...
	$i = 0
	forCondition($i < $array->length())
		console.printLine($i + ": " + $array[$i])
		++$i
	end
...
```

Iterating arrays using Array::forEach() and a lamda function

```
...
	$array->forEach(($value) -> { console.printLine($value) })
...
```

Iterating arrays using forEach

```
...
	forEach ($value in $array) 
		console.printLine($value)
	end
...
```

For further usage see [Array class](./README-BuiltIn-Classes.md#13-array-class) documentation.

### 1.2.3. Map

A map is key, value pair storage using a underlying hash map. Keys can only exist once in a map.

Initializing a map by map initializer

```
...
	$map = {"test1": 123, "test2": 456, "test3": [1, 2, 3], "test4": "Yaaaa"}
...
```

Initializing a map by map constructor:

```
...
	$map = Map()
...
```

Setting map key, value pairs using Map::set():

```
...
	$map->set("test1", 123)
	$map->set("test2", 456)
	$map->set("test3", array(1, 2, 3))
	$map->set("test4", "Yaaaa")
...
```

Removing from map using Map::remove() and a given key:

```
...
	$map->remove("test2")
...
```

Reading values from map using Map::get() and given keys:

```
...
	console.printLine("map value for test1 key using map.get(): ", $map->get("test1"))
	console.printLine("map value for test2 key using map.get(): ", $map->get("test2"))
	console.printLine("map value for test3 key using map.get(): ", $map->get("test3"))
	console.printLine("map value for test4 key using map.get(): ", $map->get("test4"))
...
```

Reading values from map using dot operator:

```
...
	console.printLine("map value for test1 using map dot operator: ", $map.test1)
	console.printLine("map value for test2 using map dot operator: ", $map.test2)
	console.printLine("map value for test3 using map dot operator: ", $map.test3)
	console.printLine("map value for test4 using map dot operator: ", $map.test4)
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
	console.printLine("map keys: ", $map->getKeys())
...
```

Reading map values:

```
...
	console.printLine("map values: ", $map->getValues())
...
```

Reading all keys and values from map using Map::get() and Map::getKeys()

```
...
	$keys = $map->getKeys()
	forEach($key in $keys)
		console.printLine($key + " = " + $map->get($key))
	end
...
```

Iterating maps using Map::forEach() and a lamda function

```
...
	$map->forEach(($key, $value) -> { console.printLine($key + " = " + $value) })
...
```

Iterating maps using forEach

```
...
	forEach($key, $value in $map)
		console.printLine($key + " = " + $value)
	end
...
```

For further usage see [Map class](./README-BuiltIn-Classes.md#14-map-class) documentation.

### 1.2.4. Set

A set is key storage using a underlying hash set. Keys can only exist once in a set.

Initializing a set by set initializer
```
...
	$set = {"test1", "test2", "test3"}
...
```

Initializing a set by set constructor
```
...
	$set = Set()
...
```

Inserting keys into set using Set::insert():
```
...
	$set->insert("test1")
	$set->insert("test2")
	$set->insert("test3")
...
```

Removing keys from set using Set::remove():
```
...
	$set->remove("test2")
...
```

Checking if keys exist in set using Set::has() and given keys:
```
...
	console.printLine("set does have test1 key using set.has(): ", $set->has("test1"))
	console.printLine("set does have test2 key using set.has(): ", $set->has("test2"))
	console.printLine("set does have test3 key using set.has(): ", $set->has("test3"))
	console.printLine("set does have test4 key using set.has(): ", $set->has("test4"))
	console.printLine("set does have test5 key using set.has(): ", $set->has("test5"))
...
```

Reading all keys as array from set:
```
...
	console.printLine("set keys: ", $set->getKeys())
...
```

Iterating sets using Set::forEach() and a lamda function
```
...
	$set->forEach(($key) -> { console.printLine($key) })
...
```

Iterating sets using forEach

```
...
	forEach ($key in $set) 
		console.printLine($key)
	end
...
```

For further usage see [Set class](./README-BuiltIn-Classes.md#15-set-class) documentation.

### 1.2.5. More ...

For more information about how to work with data types and classes, see [Built-in classes](./README-BuiltIn-Classes.md) section.

# 2. Links

## 2.1. Language documentation
- [Syntax](./README-Syntax.md)
- [Data types, variables and constants](./README-DataTypes.md)
- [Flow control - if, elseif and else](./README-FlowControl-Conditions.md)
- [Flow control - switch, case and default](./README-FlowControl-Conditions2.md)
- [Flow control - forTime, forCondition, for and forEach](./README-FlowControl-Loops.md)
- [Flow control - exceptions](./README-FlowControl-Exceptions.md)
- [Functions](./README-Functions.md)
- [Lambda functions](./README-Lambda-Functions.md)
- [Classes](./README-Classes.md)
- [Modules](./README-Modules.md)
- [Built-in functions](./README-BuiltIn-Functions.md)
- [Built-in classes](./README-BuiltIn-Classes.md)
- [Operators](./README-Operators.md)
- [Constants](./README-Constants.md)

## 2.2. Other links

- MinitScript, see [README.md](../README.md)
- MinitScript - How to build, see [README-BuildingHowTo.md](../README-BuildingHowTo.md)
- MinitScript - How to use, see [README-Tools.md](../README-Tools.md)
- The Mindty Kollektiv [Discord Server](https://discord.gg/Na4ACaFD)
