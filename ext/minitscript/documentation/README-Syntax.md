![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Syntax

## 1.1. Introduction

MinitScript takes a simple approach regarding its syntax. There are no syntax keywords or similar. 
Everything, despite variables, constants and operators, is build around the idea of methods, functions and callables, 
which are identified by a name, including some namespace information, and arguments surrounded by brackets like:

E.g. namespace.functionName($arg0, ..., $argN)

## 1.2. Statements

You can simply list statements line by line.

```
	console.printLine("Hi there. Who has some serious interest in MinitScripting?")
	console.printLine("Me!")
	console.printLine("Me not!")
```

You can also separate statements using the semicolon.

```
	# one line, one statement
	console.printLine("Hi there. Who has some serious interest in MinitScripting?")
	# see line below with multiple statements
	console.printLine("Me!"); console.printLine("Me not!"); console.printLine("Never ever!")
```

This can also be used like:

```
	$array = [1,2,3]
	forEach($entry in $array); console.printLine($entry); end
```

## 1.3. Methods, functions and callables.

A method is provided by a C++ class and its member method, hence the name. 
In the documentation you find them in [Built-in functions](./README-BuiltIn-Functions.md) section.
This sounds a bit confusing, but makes sense.

Methods (and possibly a custom data type) can also be used to generate a classes like API, just look in the [Built-in classes](./README-BuiltIn-Classes.md) section.

Function and callables are defined by the scripts itself. Callables are basically public functions for script interoperability with some more safety checks.
See [Functions](./README-Functions.md) section.

In combination with map datatype, you can also generate classes like objects in MinitScript language. See [Classes](./README-Classes.md) section.

## 1.4. Top level script syntax

At top level MinitScript can take the following syntax:
- function: ...
- callable: ...
- stacklet: ...

### 1.4.1 Functions and callables

At top level script scope we still can define functions like:

```
function: factorial($value)
	if ($value == 0)
		return(1)
	end
	return($value * factorial($value - 1))
end
```

and callables like:

```
callable: helloWorldFunction()
	console.printLine("helloWorldFunction(): Hello world")
end
```

For more information see [Functions](./README-Functions.md) section.

### 1.4.2 Main function

The entry point for MinitScript scripts is the main function, if events are disabled, e.g. in stock MinitScript distribution.
Means the first thing that is called in stock MinitScript is the script's main function.

```
# main
function: main()
	console.printLine("Hello world")
end
```


## 1.6. Additional documentation

To have more information, I would suggest you to read the following sections next or on demand.
- [Data types, variables and constants](./README-DataTypes.md)
- [Flow control - if, elseif and else](./README-FlowControl-Conditions.md)
- [Flow control - switch, case and default](./README-FlowControl-Conditions2.md)
- [Flow control - forTime, forCondition, for and forEach](./README-FlowControl-Loops.md)
- [Flow control - exceptions](./README-FlowControl-Exceptions.md)
- [Functions](./README-Functions.md)
- [Lambda Functions](./README-Lambda-Functions.md)
- [Classes](./README-Classes.md)
- [Modules](./README-Modules.md)

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
