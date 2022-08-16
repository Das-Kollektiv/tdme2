![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is the documentation of MiniScript language. This document is WIP.

# 1. Methods

| Methods                                                                                          |
|--------------------------------------------------------------------------------------------------|
| add(...): Mixed                                                                                  |
| and(...): Boolean                                                                                |
| array(...): Array                                                                                |
| array.get(array: Array, index: Integer): Mixed                                                   |
| array.length(array: Array): Integer                                                              |
| array.push(...): Array                                                                           |
| array.remove(array: Array, index: Integer): Array                                                |
| array.set(...): Array                                                                            |
| bool(bool: Boolean): Boolean                                                                     |
| concatenate(...): String                                                                         |
| console.log(...): Void                                                                           |
| div(...): Mixed                                                                                  |
| else(): Void                                                                                     |
| elseif(condition: Boolean): Void                                                                 |
| end(): Void                                                                                      |
| equals(...): Boolean                                                                             |
| float(float: Float): Float                                                                       |
| forCondition(condition: Boolean): Void                                                           |
| forTime(time: Integer): Void                                                                     |
| getVariable(variable: String): Mixed                                                             |
| greater(a: Float, b: Float): Boolean                                                             |
| greaterequals(a: Float, b: Float): Boolean                                                       |
| if(condition: Boolean): Void                                                                     |
| int(int: Integer): Integer                                                                       |
| lesser(a: Float, b: Float): Boolean                                                              |
| lesserequals(a: Float, b: Float): Boolean                                                        |
| mul(...): Mixed                                                                                  |
| not(bool: Boolean): Boolean                                                                      |
| notequal(...): Boolean                                                                           |
| or(...): Boolean                                                                                 |
| script.disableNamedCondition(name: String): Void                                                 |
| script.emit(condition: String): Void                                                             |
| script.enableNamedCondition(name: String): Void                                                  |
| script.getNamedConditions(): String                                                              |
| script.stop(): Void                                                                              |
| script.wait(time: Integer): Void                                                                 |
| script.waitForCondition(): Void                                                                  |
| setVariable(...): Mixed                                                                          |
| space(spaces: Integer(OPTIONAL)): String                                                         |
| string(string: String): String                                                                   |
| sub(...): Mixed                                                                                  |
| time.getCurrentMillis(): Integer                                                                 |
| toLowerCase(string: String): String                                                              |
| toUpperCase(string: String): String                                                              |
| transform(...): Transform                                                                        |
| transform.getRotationAngle(transform: Transform, idx: Integer): Float                            |
| transform.getRotationAxis(transform: Transform, idx: Integer): Vector3                           |
| transform.getScale(transform: Transform): Vector3                                                |
| transform.getTranslation(transform: Transform): Vector3                                          |
| transform.multiply(transform: Transform, vec3: Vector3): Vector3                                 |
| transform.rotate(transform: Transform, vec3: Vector3): Vector3                                   |
| transform.setRotationAngle(transform: Transform, idx: Integer, angle: Float): Transform          |
| transform.setScale(transform: Transform, scale: Vector3): Transform                              |
| transform.setTranslation(transform: Transform, translation: Vector3): Transform                  |
| vec3(x: Float, y: Float, z: Float): Vector3                                                      |
| vec3.computeAngle(a: Vector3, b: Vector3, n: Vector3): Float                                     |
| vec3.computeCrossProduct(a: Vector3, b: Vector3): Vector3                                        |
| vec3.computeDotProduct(a: Vector3, b: Vector3): Float                                            |
| vec3.computeLength(vec3: Vector3): Float                                                         |
| vec3.computeLengthSquared(vec3: Vector3): Float                                                  |
| vec3.getX(vec3: Vector3): Float                                                                  |
| vec3.getY(vec3: Vector3): Float                                                                  |
| vec3.getZ(vec3: Vector3): Float                                                                  |
| vec3.normalize(vec3: Vector3): Vector3                                                           |

# 2. Operators

| Op | Method                                                                                      |
|----|---------------------------------------------------------------------------------------------|
| !  | not(bool: Boolean): Boolean                                                                 |
| != | notequal(...): Boolean                                                                      |
| && | and(...): Boolean                                                                           |
| *  | mul(...): Mixed                                                                             |
| +  | add(...): Mixed                                                                             |
| -  | sub(...): Mixed                                                                             |
| /  | div(...): Mixed                                                                             |
| <  | lesser(a: Float, b: Float): Boolean                                                         |
| <= | lesserequals(a: Float, b: Float): Boolean                                                   |
| =  | setVariable(...): Mixed                                                                     |
| == | equals(...): Boolean                                                                        |
| >  | greater(a: Float, b: Float): Boolean                                                        |
| >= | greaterequals(a: Float, b: Float): Boolean                                                  |
| \|\|| or(...): Boolean                                                                           |
