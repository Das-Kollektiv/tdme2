![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Flow control - if, elseif and else

If, elseif and else are flow control methods. Please see the usage below.

## 1.1. If

See an example of if:
```
...
	$i = 1
	if ($i == 1)
		console.printLine("i -> 1")
	end
...
```

## 1.2. If and else

See an example of if and else:
```
...
	$i = 2
	if ($i == 1)
		console.printLine("i -> 1")
	else
		console.printLine("else: ", $i)
	end
...
```

## 1.3. If, elseif and else

See an example of if, elseif and else:

```
...
	$i = 2
	console.printLine($i, ":")
	if ($i == 0)
		console.printLine("i -> 0")
	elseif ($i == 1)
		console.printLine("i -> 1")
	elseif ($i == 2)
		console.printLine("i -> 2")
	elseif ($i == 3)
		console.printLine("i -> 3")
	else
		console.printLine("else: ", $i)
	end
...
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
