![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Operators

| Op | Method                                                                                      |
|----|---------------------------------------------------------------------------------------------|
| !  | not($boolean: Boolean[, $operator: Integer]): Boolean                                       |
| != | notEqual($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                               |
| %  | mod($value: Number, $range: Number[, $operator: Integer]): Number                           |
| &  | bitwiseAnd($a: Integer, $b: Integer[, $operator: Integer]): Integer                         |
| && | and($a: Boolean, $b: Boolean[, $operator: Integer]): Boolean                                |
| *  | mul($a: Mixed, $b: Mixed[, $operator: Integer]): Mixed                                      |
| +  | add($a: Mixed, $b: Mixed[, $operator: Integer]): Mixed                                      |
| ++ | postfixIncrement(&$variable: Integer[, $operator: Integer]): Integer                        |
| ++ | prefixIncrement(&$variable: Integer[, $operator: Integer]): Integer                         |
| -  | sub($a: Mixed, $b: Mixed[, $operator: Integer]): Mixed                                      |
| -- | postfixDecrement(&$variable: Integer[, $operator: Integer]): Integer                        |
| -- | prefixDecrement(&$variable: Integer[, $operator: Integer]): Integer                         |
| -> | memberExecute(&$object: Mixed, $method: String, $operator: Integer, ...): Mixed             |
| .  | memberProperty(&$object: Map, $property: String[, $operator: Integer]): Mixed               |
| /  | div($a: Mixed, $b: Mixed[, $operator: Integer]): Mixed                                      |
| <  | lesser($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                                 |
| <= | lesserEquals($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                           |
| =  | setVariable($variable: String, $value: Mixed[, $operator: Integer]): Mixed                  |
| == | equals($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                                 |
| >  | greater($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                                |
| >= | greaterEquals($a: Mixed, $b: Mixed[, $operator: Integer]): Boolean                          |
| [] | subscript(&$array: Array, $index: Integer[, $operator: Integer]): Mixed                     |
| \| | bitwiseOr($a: Integer, $b: Integer[, $operator: Integer]): Integer                          |
| \|\|| or($a: Boolean, $b: Boolean[, $operator: Integer]): Boolean                                |
| ^  | bitwiseXor($a: Integer, $b: Integer[, $operator: Integer]): Integer                         |
| ~  | bitwiseNot($value: Integer[, $operator: Integer]): Integer                                  |

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
