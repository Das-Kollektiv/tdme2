![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Flow control - forTime, forCondition, for and forEach

## 1.1. forTime

forTime and "forCondition" are loops and belong to flow control also:

forTime takes a single argument "time" - it repeats the loop until "time" in milliseconds has passed since the initialization of the loop. See an example of forTime() below: 

```
...
	$i = 0
	forTime(2000)
		console.printLine($i, ": Hello World")
		script.wait(500)
		++$i
	end
...
```

## 1.2. forCondition

forCondition takes a single boolean value as argument. The loop will be executed as long as the argument is true. In this case "$i < 5" translates to "lesser($i, 5)" which results in a boolean value, which is used as the forCondition argument. See example of forCondition() below.

```
...
	$i = 0
	forCondition($i < 5)
		console.printLine("$ = ", $i)
		++$i
	end
...
```

## 1.3. for

for takes 3 arguments, a initializer statement, a continuing condition and an iteration statement. See an example below.   

```
	for ($i = 0, $i < 5, $i++)
		console.printLine("$i = " + $i)
	end
```

Also see the usage of continue and break in a advanced for example.

If a break is executed within a for loop, the script execution jumps to the corresponding for end statement.
If a continue is executed, the script jumps to the for statement for next iteration.  

```
	for ($i = 0, $i < 5, $i++)
		if ($i == 3)
			continue
		end
		console.printLine("$i = " + $i)
		if ($i == 4)
			break
		end
	end
```

## 1.4. forEach

forEach exists for iteration and processing of entries in arrays, maps and sets.

See a simple forEach example with an array.

```
	$array = [1,2,3]
	forEach($entry in $array)
		console.printLine($entry)
	end
```

See the same example, except that we are using a reference &$entry, to be able to manipulate our array entries.

```
	$array = [1,2,3]
	forEach(&$entry in $array)
		$entry++
		console.printLine($entry)
	end
```

The same usage applies when operating with sets. Just see an adjusted example.

```
	$set = {1,2,3}
	forEach($entry in $set)
		console.printLine($entry)
	end
```

forEach also works with maps. See an example below.

```
	$map = {a: 1, b: 2, c: 3}
	forEach($key, $value in $map)
		console.printLine("$key = " + $key + ", $value = " + $value)
	end
```

If you want to manipulate the value, you can also use references here.

```
	$map = {a: 1, b: 2, c: 3}
	forEach($key, &$value in $map)
		$value++
		console.printLine("$key = " + $key + ", $value = " + $value)
	end
```

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
