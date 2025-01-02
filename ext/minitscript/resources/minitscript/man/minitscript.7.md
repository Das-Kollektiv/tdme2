This is the home of MinitScript - The mini C++ transpileable scripting language.

This document and repository is WIP. Expect a BETA release around 2025-03-01.\
See section 1.3. for 1.0 BETA release TODO list.

# 1. Introduction

MinitScript is developed as part of our [TDME2 3D Engine](https://github.com/andreasdr/tdme2) to match
the requirements for high performance script execution, as well as straight forward game logic scripting.

MinitScript might borrow some ideas from JavaScript, Kotlin, PHP and even Pascal, C# and C++, which you might like and find familier.
Also note the focus on easy integration into other products and easy customizability and extendability.

## 1.1. Open source

- MinitScript is open source
  - please check the [license](https://github.com/andreasdr/minitscript/blob/main/LICENSE)
  - you find the source code at [https://github.com/andreasdr/minitscript](https://github.com/andreasdr/minitscript) 
  - here you find developer [documentation including collaboration graphs and API](https://www.mindty.com/products/minitscript/documentation/)

## 1.2. Language features

- Introduction to MinitScript language features:
  - very small implementation of a scripting language
  - runs on every CPU, OS, ... due to its simplicity, so its highly portable
  - can be easily extended by writing state machine machine states and script methods in C++ as well as custom data types
  - built-in data types: null, boolean, integer, float, string, byte array, array, map and set, ...
  - when calling script C++ methods or script functions with arguments it does optionally use references or value by copy
  - supports functions/stacklets and recursion
  - supports lamda functions and inline stacklets
  - supports operators by operator to method mapping by a preprocessor run
  - supports loops, conditions and switch/case/default blocks
  - supports programming with classes style programming
    - for built-in datatypes: string, byte array, array, map and set, ...
    - for script classes/objects
    - for custom data types
  - supports event like programming
  - unicode support via UTF8
  - can be transpiled to C++

## 1.3. 1.0 BETA release TODO list

- Whats left to do for 1.0 BETA release
  - some adjustments
    - modules
    - exceptions
    - array sub type optimization
    - passing method arguments with vector of pointer of MinitScript variables
    - have a more sophisticated parser
    - have interfaces
    - optional: make event system optional??? what about error emits/errors in functions/stacklets??? 
    - build system: check executable output directories
  - parser
    - improve error messages even more
  - documentation
    - detailed documentation for specific sections and maybe methods
    - README.md: resolve TODOs
    - README-BuildingHowTo.md: resolve TODOs
    - README-Syntax.md: TODO
    - README-Extension.md: TODO
    - README-Integration.md: TODO
    - ...
  - installer for Windows
  - installer for MacOSX