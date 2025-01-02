![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Built-in classes

## 1.1. String class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| Create string                                                                                    |
| <sub><b>static</b> String($string: String): String</sub>                                         |
| Concatenate strings                                                                              |
| <sub><b>static</b> String::concatenate(...): String</sub>                                        |
| Create string from byte array                                                                    |
| <sub><b>static</b> String::fromByteArray($byteArray: ByteArray): String</sub>                    |
| Create string from unicode code point                                                            |
| <sub><b>static</b> String::fromCodePoint($codePoint: Integer): String</sub>                      |
| Generate string                                                                                  |
| <sub><b>static</b> String::generate($what: String[, $count: Integer]): String</sub>              |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Returns character of string at given position                                                    |
| <sub>charAt($index: Integer): String</sub>                                                       |
| Returns code point of string at given position                                                   |
| <sub>codePointAt($index: Integer): Integer</sub>                                                 |
| Test if string ends with specific string                                                         |
| <sub>endsWith($suffix: String): Boolean</sub>                                                    |
| Test if strings matches ignoring case sensitivity                                                |
| <sub>equalsIgnoreCase($other: String): Boolean</sub>                                             |
| Returns first index of specific string in string                                                 |
| <sub>firstIndexOf($what: String[, $beginIndex: Integer]): Integer</sub>                          |
| Returns first index of characters provided within given string in string                         |
| <sub>firstIndexOfChars($what: String[, $beginIndex: Integer]): Integer</sub>                     |
| Returns string size in bytes                                                                     |
| <sub>getSize(): Integer</sub>                                                                    |
| Indent string                                                                                    |
| <sub>indent($with: String, $count: Integer): String</sub>                                        |
| Returns index of specific string in string                                                       |
| <sub>indexOf($what: String[, $beginIndex: Integer]): Integer</sub>                               |
| Test if string value is empty                                                                    |
| <sub>isEmpty(): Boolean</sub>                                                                    |
| Test if string value is a float number                                                           |
| <sub>isFloat(): Boolean</sub>                                                                    |
| Test if string value is a integer number                                                         |
| <sub>isInteger(): Boolean</sub>                                                                  |
| Returns last index of specific string in string                                                  |
| <sub>lastIndexOf($what: String[, $beginIndex: Integer]): Integer</sub>                           |
| Returns last index of characters provided within given string in string                          |
| <sub>lastIndexOfChars($what: String[, $endIndex: Integer]): Integer</sub>                        |
| Pad string left                                                                                  |
| <sub>padLeft($by: String, $toLength: Integer): String</sub>                                      |
| Pad string right                                                                                 |
| <sub>padRight($by: String, $toLength: Integer): String</sub>                                     |
| RegEx match                                                                                      |
| <sub>regexMatch($pattern: String[, &$matches: ?Array]): Boolean</sub>                            |
| RegEx replace                                                                                    |
| <sub>regexReplace($pattern: String, $by: String): String</sub>                                   |
| RegEx search                                                                                     |
| <sub>regexSearch($pattern: String[, &$matches: ?Array]): Boolean</sub>                           |
| Replace specific string in string with given string                                              |
| <sub>replace($what: String, $by: String[, $beginIndex: Integer]): String</sub>                   |
| Test if given string starts with specific string                                                 |
| <sub>startsWith($prefix: String): Boolean</sub>                                                  |
| Returns substring of string                                                                      |
| <sub>substring($beginIndex: Integer[, $endIndex: Integer]): String</sub>                         |
| Convert string to byte array                                                                     |
| <sub>toByteArray(): ByteArray</sub>                                                              |
| Compute lower case string of string                                                              |
| <sub>toLowerCase(): String</sub>                                                                 |
| Compute upper case string of string                                                              |
| <sub>toUpperCase(): String</sub>                                                                 |
| Tokenize string                                                                                  |
| <sub>tokenize($delimiters: String): Array</sub>                                                  |
| Trim string                                                                                      |
| <sub>trim(): String</sub>                                                                        |

## 1.2. Byte array class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| Create byte array                                                                                |
| <sub><b>static</b> ByteArray(): ByteArray</sub>                                                  |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Clear byte array                                                                                 |
| <sub>clear(): Null</sub>                                                                         |
| Get read position                                                                                |
| <sub>getReadPosition(): Integer</sub>                                                            |
| Returns size of byte array in bytes                                                              |
| <sub>getSize(): Integer</sub>                                                                    |
| Get write position                                                                               |
| <sub>getWritePosition(): Integer</sub>                                                           |
| Read boolean value and advance read position by 1 byte                                           |
| <sub>readBool(): ?Boolean</sub>                                                                  |
| Read 32 bit float value and advance read position by 4 bytes                                     |
| <sub>readFloat(): ?Float</sub>                                                                   |
| Read 16 bit integer value and advance read position by 2 bytes                                   |
| <sub>readInt16(): ?Integer</sub>                                                                 |
| Read 16 bit integer value and advance read position by 4 bytes                                   |
| <sub>readInt32(): ?Integer</sub>                                                                 |
| Read 64 bit integer value and advance read position by 8 bytes                                   |
| <sub>readInt64(): ?Integer</sub>                                                                 |
| Read 8 bit integer value and advance read position by 1 byte                                     |
| <sub>readInt8(): ?Integer</sub>                                                                  |
| Read a string with maximum size of 255 bytes                                                     |
| <sub>readLargeString(): ?String</sub>                                                            |
| Read a string with maximum size of 65535 bytes                                                   |
| <sub>readMediumString(): ?String</sub>                                                           |
| Read a string with maximum size of 4294967295 bytes                                              |
| <sub>readSmallString(): ?String</sub>                                                            |
| Remove values from byte array                                                                    |
| <sub>remove($index: Integer, $size: Integer): Null</sub>                                         |
| Set read position                                                                                |
| <sub>setReadPosition($position: Integer): Null</sub>                                             |
| Set write position                                                                               |
| <sub>setWritePosition($position: Integer): Null</sub>                                            |
| Write boolean value and advance write position by 1 byte                                         |
| <sub>writeBool($value: Boolean): Null</sub>                                                      |
| Write 32 bit float value and advance write position by 4 bytes                                   |
| <sub>writeFloat($value: Integer): Null</sub>                                                     |
| Write 16 bit integer value and advance write position by 2 bytes                                 |
| <sub>writeInt16($value: Integer): Null</sub>                                                     |
| Write 32 bit integer value and advance write position by 4 bytes                                 |
| <sub>writeInt32($value: Integer): Null</sub>                                                     |
| Write 64 bit integer value and advance write position by 8 bytes                                 |
| <sub>writeInt64($value: Integer): Null</sub>                                                     |
| Write 8 bit integer value and advance write position by 1 byte                                   |
| <sub>writeInt8($value: Integer): Null</sub>                                                      |
| Write a string with maximum size of 255 bytes                                                    |
| <sub>writeLargeString($value: String): Null</sub>                                                |
| Write a string with maximum size of 65535 bytes                                                  |
| <sub>writeMediumString($value: String): Null</sub>                                               |
| Write a string with maximum size of 4294967295 bytes                                             |
| <sub>writeSmallString($value: String): Null</sub>                                                |

## 1.3. Array class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| Create array                                                                                     |
| <sub><b>static</b> Array(...): Array</sub>                                                       |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Clear array                                                                                      |
| <sub>clear(): Null</sub>                                                                         |
| Returns if array contains a specific value                                                       |
| <sub>contains($value: Mixed): Boolean</sub>                                                      |
| Iterate array values, by using a (Lamda) function                                                |
| <sub>forEach($callbackFunction: Function[, &$cookie: Mixed]): Null</sub>                         |
| Iterate range of array values, by using a (Lamda) function                                       |
| <sub>forRange($callbackFunction: Function, $beginIndex: Integer[, $count: Integer[, $step: Integer[, &$cookie: Mixed]]]): Null</sub>|
| Get array entry                                                                                  |
| <sub>get($index: Integer): Mixed</sub>                                                           |
| Returns number of elements in array                                                              |
| <sub>getSize(): Integer</sub>                                                                    |
| Get array index by value                                                                         |
| <sub>indexOf($value: String[, $beginIndex: Integer]): Integer</sub>                              |
| Returns if array is empty                                                                        |
| <sub>isEmpty(): Boolean</sub>                                                                    |
| Add entry to array                                                                               |
| <sub>push(...): Null</sub>                                                                       |
| Remove array entry by index                                                                      |
| <sub>remove($index: Integer): Null</sub>                                                         |
| Remove array entry by value                                                                      |
| <sub>removeOf($value: String[, $beginIndex: Integer]): Null</sub>                                |
| Reverse array                                                                                    |
| <sub>reverse(): Null</sub>                                                                       |
| Set array entry                                                                                  |
| <sub>set($index: Integer, $value: Mixed): Null</sub>                                             |
| Sort array                                                                                       |
| <sub>sort($sortFunction: Function): Null</sub>                                                   |
| Sort array ascending                                                                             |
| <sub>sortAscending(): Null</sub>                                                                 |
| Sort array descending                                                                            |
| <sub>sortDescending(): Null</sub>                                                                |

## 1.4. Map class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| Create map                                                                                       |
| <sub><b>static</b> Map(): Map</sub>                                                              |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Clear map                                                                                        |
| <sub>clear(): Null</sub>                                                                         |
| Returns if map contains specific key                                                             |
| <sub>contains($key: String): Boolean</sub>                                                       |
| Iterate map key and value pairs, by using a (Lamda) function                                     |
| <sub>forEach($callbackFunction: Function[, &$cookie: Mixed]): Null</sub>                         |
| Get map value by key                                                                             |
| <sub>get($key: String): Mixed</sub>                                                              |
| Get map keys                                                                                     |
| <sub>getKeys(): Array</sub>                                                                      |
| Returns number of elements in map                                                                |
| <sub>getSize(): Integer</sub>                                                                    |
| Get map values                                                                                   |
| <sub>getValues(): Array</sub>                                                                    |
| Returns if map is empty                                                                          |
| <sub>isEmpty(): Boolean</sub>                                                                    |
| Remove map entry                                                                                 |
| <sub>remove($key: String): Null</sub>                                                            |
| Set map entry                                                                                    |
| <sub>set($key: String, $value: Mixed): Null</sub>                                                |

## 1.5. Set class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| Create set                                                                                       |
| <sub><b>static</b> Set(): Set</sub>                                                              |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Clear set                                                                                        |
| <sub>clear(): Null</sub>                                                                         |
| Returns if set contains specific key                                                             |
| <sub>contains($key: String): Boolean</sub>                                                       |
| Iterate set keys, by using a (Lamda) function                                                    |
| <sub>forEach($callbackFunction: Function[, &$cookie: Mixed]): Null</sub>                         |
| Get set keys                                                                                     |
| <sub>getKeys(): Array</sub>                                                                      |
| Returns number of elements in set                                                                |
| <sub>getSize(): Integer</sub>                                                                    |
| Insert key into set                                                                              |
| <sub>insert($key: String): Null</sub>                                                            |
| Returns if set is empty                                                                          |
| <sub>isEmpty(): Boolean</sub>                                                                    |
| Remove key from set                                                                              |
| <sub>remove($key: String): Null</sub>                                                            |

## 1.6. HTTP download client class

| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |
|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| &nbsp;                                    |
| <b>STATIC METHODS</b>                     |
| HTTP Download Client                                                                             |
| <sub><b>static</b> HTTPDownloadClient(): HTTPDownloadClient</sub>                                |
| &nbsp;                                    |
| <b>NON STATIC METHODS</b>                 |
| Cancel download                                                                                  |
| <sub>cancel(): Null</sub>                                                                        |
| Get file URI                                                                                     |
| <sub>getFile(): String</sub>                                                                     |
| Get GET parameters                                                                               |
| <sub>getGETParameters(): Map</sub>                                                               |
| Get headers                                                                                      |
| <sub>getHeaders(): Map</sub>                                                                     |
| Get password                                                                                     |
| <sub>getPassword(): String</sub>                                                                 |
| Get progress                                                                                     |
| <sub>getProgress(): Float</sub>                                                                  |
| Get response headers                                                                             |
| <sub>getResponseHeaders(): Map</sub>                                                             |
| Get HTTP status code                                                                             |
| <sub>getStatusCode(): Integer</sub>                                                              |
| Get URL                                                                                          |
| <sub>getURL(): String</sub>                                                                      |
| Get username                                                                                     |
| <sub>getUserName(): String</sub>                                                                 |
| Returns if download has been finished                                                            |
| <sub>isFinished(): Boolean</sub>                                                                 |
| Wait until download thread has finished working                                                  |
| <sub>join(): Null</sub>                                                                          |
| Reset HTTP download client                                                                       |
| <sub>reset(): Null</sub>                                                                         |
| Set file to save file downloaded to                                                              |
| <sub>setFile($url: String): Null</sub>                                                           |
| Set GET parameters                                                                               |
| <sub>setGETParameters($getParameters: Map): Null</sub>                                           |
| Set headers                                                                                      |
| <sub>setHeaders($headers: Map): Null</sub>                                                       |
| Set password                                                                                     |
| <sub>setPassword($password: String): Null</sub>                                                  |
| Set URL                                                                                          |
| <sub>setURL($url: String): Null</sub>                                                            |
| Set user name                                                                                    |
| <sub>setUserName($userName: String): Null</sub>                                                  |
| Start download                                                                                   |
| <sub>start(): Null</sub>                                                                         |

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
