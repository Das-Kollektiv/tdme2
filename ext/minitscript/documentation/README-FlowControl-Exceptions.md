![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. What are exceptions

MinitScript supports exceptions, which are categorized as flow control.

Exceptions are about 3 things. Trying to do some work, that can issue a exception, which means a failure in logic, and catching the exception. 
Third is also how to throw exceptions.

Exceptions do not need to be catched at the level of the throw statement, it can also be catched a level higher from a calling function. 

## 1.1. Trying and catching

```
module

function: module1Init()
	console.printLine("-----------------")
	console.printLine("init")
	console.printLine("-----------------")
	# initialize our array
	$array = []
	try
		# reading data.txt into an array
		$array = filesystem.getContentAsStringArray(".", "data.txt")	
		# filesystem.getContentAsStringArray() would throw an exception if data.txt does not exist
		# in this case the following functions would not be executed anymore
		# the script would jump into catch block
		# and we would not see this message
		console.printLine("data.txt: read file into memory");
	catch ($exception)
		console.printLine("An error occurred: " + $exception)
		# print the stack trace
		console.printLine(stackTrace())
	end
end
```

## 1.2. Throwing an exception

```
module;

function: module1Init()
	# this throws an exception with the string argument "not implemented"
	# the exception can be catched at a higher level
	throw("not implemented")
end
```

## 1.3. Initialization example

```
use: module_1.tscript
use: module_2.tscript
use: module_3.tscript

# main
function: main()
	console.printLine("---------")
	console.printLine("Nothing")
	console.printLine("---------")
	console.printLine()
	# initialize modules, which can load data from files or databases, or computing some values, ...
	try
		# if any of the module initializations throw an unhandled exception, the exception will be handled here in catch block. then the script will stop.
		module1Init()
		module2Init()
		module3Init()
	catch ($exception)
		# ahhhhh! one initialization failed!
		console.printLine("An error occurred: " + $exception)
		# print the stack trace
		console.printLine(stackTrace())
	end
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
