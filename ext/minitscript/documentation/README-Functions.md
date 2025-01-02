![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Functions/Stacklets/Callables

## 1.1. Functions

See this example that shows functions and recursion.

Argument variables, parsed in function declarations are populated in function context with corresponding values.
```
...
# function of recursive factorial computation
function: factorial($value)
	console.printLine("factorial(): $value = " + $value)
	if ($value == 0) 
		return(1)
	end
	return($value * factorial($value - 1))
end
...
	console.printLine("factorial(5) = " + factorial(5))
...
```

If a argument(variable) is prefixed with a & operator in the function declaration, the variable will not be copied into the function arguments, 
but a reference will be created, means if this variable changes within the function it will also change in the parent variable scope.
See &$b and &$c.

Be aware that value by copy variables usually require more instantiation time due to the copy that needs to be made of the variable from parent variable scope to function variable scope. 
```
...
# function to test references in user functions
function: assignTest($a, &$b, &$c)
	$a = "a"
	$b = "b"
	$c = "c"
end
...
	$a = "0"
	$b = "1"
	$c = "2"
	console.printLine("assignTest(): pre: $a = " + $a + ", $b = " + $b + ", $c = " + $c)
	assignTest($a, $b, $c)
	console.printLine("assignTest(): post: $a = " + $a + ", $b = " + $b + ", $c = " + $c)
...
``` 

By default, variables are read from current (variable) context. The default context is the global context. 
Functions and callables have their own contexts. In this case global variables must be accessed by using the "$$." or "$GLOBAL." accessor.
```
...
# function to test global variable access
function: globalVariableTest()
	console.printLine("globalVariableTest(): $GLOBAL.globalTest = " + $GLOBAL.globalTest)
	$GLOBAL.globalTest = "Been there, done that, got the t-shirt"
end
...
	$globalTest = "Global Test Variable"
	console.printLine("globalVariableTest(): pre: $globalTest = " + $globalTest)
	globalVariableTest()
	console.printLine("globalVariableTest(): post: $globalTest = " + $globalTest)
...
```

## 1.2. Stacklets

Stacklets are basically functions without a own stack(or scope), that e.g. holds variables. 
But stacklets are able to read/write variables of root scope or of a defined scope function scope. 
Stacklets take no argument if used in root scope. It can take a single argument that names the function the stacklet is bound too, to use its scope.

```
...
stacklet: stackletTest(main)
	# we can read from current script scope as stacklets do not create their own script scope
	console.printLine("stackletTest(): " + $works)
end

# main
function: main()
	$works = "Works!"
	stackletTest()
	script.stop()
end
...

```  

## 1.3. Callables

A special type of functions are callables. Callables are functions that are used to interact between MinitScript scripts.
 
Despite the fact that a callable function of a script can be called from another script, 
they have the limitation that they must not contain MinitScript C++ method calls that require a context function.

Context functions are functions that require a special context. You can ignore this fow now. 
Default MinitScript does not provide script methods by C++ that require a context. 

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
