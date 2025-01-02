![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Lambda functions

Lambda functions are anonymous functions, means they have no name, and are defined inline. You can use lambda functions with array, set, maps and more MinitScript API, if a argument takes a Function.

As a statement lambda functions are written like 

```
  ($arg0, ..., $argN) -> { console.printLine($arg0); ... }
```

If there are no lambda function arguments, you can write the lambda function also like this:

```
  () -> { console.printLine("Test"); ... }
```

or
```
  -> { console.printLine("Test"); ... }
```

See some examples:

## 1.1. Arrays

Log array values to console using array.forEach.

```
  $array = [1, 2, 3, 4, 5, 6]
  $array->forEach(($element) -> { console.printLine($element) })
```

Log array values to console using array.forRange.

```
  $array = [1, 2, 3, 4, 5, 6]
  $array->forRange(($element) -> { console.printLine($element) }, 1, 3, 2)
```

Sum array values using array.forEach.

```
  $array = [1, 2, 3, 4, 5, 6]
  $sum = 0
  $array->forEach(($element, &$sum) -> { $sum = $sum + $element }, $sum)
```

Sort array values descending.

```
  $array = [1, 2, 3, 4, 5, 6]
  $array->sort(($a, $b) -> { return($a > $b) })
```

## 1.2. Sets

Log set keys to console using set.forEach.

```
  $set = {a, b, c}
  $set->forEach(($key) -> { console.printLine($key) })
```

## 1.3. Maps

Log map key, value pairs to console using set.forEach.
```
  $map = {a: 1, b: 2, c: 3}
  $map->forEach(($key, $value) -> { console.printLine($key + " = " + $value) })
```

Sum map values using map.forEach.

```
  $map = {a: 1, b: 2, c: 3}
  $sum = 0
  $map->forEach(($key, $value, &$sum) -> { $sum = $sum + $value }, $sum)
```

## 1.4. Additional examples

Using lambda functions in arrays.

```
  $functions = [
    ($value) -> { console.printLine("function 1: " + $value) },
    ($value) -> { console.printLine("function 2: " + $value) },
    ($value) -> { console.printLine("function 3: " + $value) }
  ]
  $value = 1
  forEach($function in $functions)
    script.callFunction($function, $value)
    $value++
  end
```

Using a lambda function with forCondition.

```
  $i = 0
  forCondition($i < 5, -> { $i++ })
    console.printLine("$i = " + $i)
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
