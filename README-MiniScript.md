![LOGO](https://raw.githubusercontent.com/andreasdr/tdme2/master/resources/github/tdme2-logo.png)

This is the documentation of MiniScript language. This document is WIP.

# 1. Methods

| Methods                                                                                          |
|--------------------------------------------------------------------------------------------------|
| add(...): Mixed                                                                                  |
| and(...): Boolean                                                                                |
| array(...): Array                                                                                |
| array.get($array: Array, $index: Integer): Mixed                                                 |
| array.indexOf($array: Array, $value: String, $beginIndex: Integer(OPTIONAL), ...): Integer       |
| array.length($array: Array): Integer                                                             |
| array.push($array: Array, ...): Array                                                            |
| array.remove($array: Array, $index: Integer): Array                                              |
| array.removeOf($array: Array, $value: String): Array                                             |
| array.set($array: Array, $index: Integer, ...): Array                                            |
| bool($bool: Boolean): Boolean                                                                    |
| concatenate(...): String                                                                         |
| console.log(...): Void                                                                           |
| div(...): Mixed                                                                                  |
| else(): Void                                                                                     |
| elseif($condition: Boolean): Void                                                                |
| end(): Void                                                                                      |
| equals(...): Boolean                                                                             |
| float($float: Float): Float                                                                      |
| forCondition($condition: Boolean): Void                                                          |
| forTime($time: Integer): Void                                                                    |
| getVariable($variable: String): Mixed                                                            |
| greater($a: Float, $b: Float): Boolean                                                           |
| greaterequals($a: Float, $b: Float): Boolean                                                     |
| if($condition: Boolean): Void                                                                    |
| int($int: Integer): Integer                                                                      |
| lesser($a: Float, $b: Float): Boolean                                                            |
| lesserequals($a: Float, $b: Float): Boolean                                                      |
| map(): Map                                                                                       |
| map.get($map: Map, $key: String): Mixed                                                          |
| map.getKeys($map: Map): Array                                                                    |
| map.getValues($map: Map): Array                                                                  |
| map.has($map: Map, $key: String): Boolean                                                        |
| map.remove($map: Map, $key: String): Map                                                         |
| map.set($map: Map, $key: String, ...): Map                                                       |
| mat4.computeEulerAngles($mat4: Matrix4x4): Vector3                                               |
| mat4.identity(): Matrix4x4                                                                       |
| mat4.invert($mat4: Matrix4x4): Matrix4x4                                                         |
| mat4.multiply($mat4: Matrix4x4, ...): Mixed                                                      |
| mat4.rotate($axis: Vector3, $angle: Float): Matrix4x4                                            |
| mat4.scale(...): Matrix4x4                                                                       |
| mat4.translate($translation: Vector3): Matrix4x4                                                 |
| mul(...): Mixed                                                                                  |
| not($bool: Boolean): Boolean                                                                     |
| notequal(...): Boolean                                                                           |
| or(...): Boolean                                                                                 |
| quaternion.computeMatrix($quaternion: Quaternion): Matrix4x4                                     |
| quaternion.identity(): Quaternion                                                                |
| quaternion.invert($quaternion: Vector4): Quaternion                                              |
| quaternion.multiply($quaternion: Quaternion, ...): Mixed                                         |
| quaternion.normalize($quaternion: Quaternion): Quaternion                                        |
| quaternion.rotate($axis: Vector3, $angle: Float): Quaternion                                     |
| script.disableNamedCondition($name: String): Void                                                |
| script.emit($condition: String): Void                                                            |
| script.enableNamedCondition($name: String): Void                                                 |
| script.evaluate(...): Mixed                                                                      |
| script.getNamedConditions(): String                                                              |
| script.getVariables(): Map                                                                       |
| script.stop(): Void                                                                              |
| script.wait($time: Integer): Void                                                                |
| script.waitForCondition(): Void                                                                  |
| setVariable(...): Mixed                                                                          |
| space($spaces: Integer(OPTIONAL)): String                                                        |
| string($string: String): String                                                                  |
| sub(...): Mixed                                                                                  |
| time.getCurrentMillis(): Integer                                                                 |
| toLowerCase($string: String): String                                                             |
| toUpperCase($string: String): String                                                             |
| transform($translation: Vector3(OPTIONAL), $scale: Vector3(OPTIONAL), ...): Transform            |
| transform.getRotationAngle($transform: Transform, $idx: Integer): Float                          |
| transform.getRotationAxis($transform: Transform, $idx: Integer): Vector3                         |
| transform.getScale($transform: Transform): Vector3                                               |
| transform.getTranslation($transform: Transform): Vector3                                         |
| transform.multiply($transform: Transform, $vec3: Vector3): Vector3                               |
| transform.rotate($transform: Transform, $vec3: Vector3): Vector3                                 |
| transform.setRotationAngle($transform: Transform, $idx: Integer, $angle: Float): Transform       |
| transform.setScale($transform: Transform, $scale: Vector3): Transform                            |
| transform.setTranslation($transform: Transform, $translation: Vector3): Transform                |
| unsetVariable($variable: String): Void                                                           |
| vec2($x: Float, $y: Float): Vector2                                                              |
| vec2.computeDotProduct($a: Vector2, $b: Vector2): Float                                          |
| vec2.computeLength($vec2: Vector2): Float                                                        |
| vec2.computeLengthSquared($vec2: Vector2): Float                                                 |
| vec2.getX($vec2: Vector2): Float                                                                 |
| vec2.getY($vec2: Vector2): Float                                                                 |
| vec2.normalize($vec2: Vector2): Vector2                                                          |
| vec3($x: Float, $y: Float, $z: Float): Vector3                                                   |
| vec3.computeAngle($a: Vector3, $b: Vector3, $n: Vector3): Float                                  |
| vec3.computeCrossProduct($a: Vector3, $b: Vector3): Vector3                                      |
| vec3.computeDotProduct($a: Vector3, $b: Vector3): Float                                          |
| vec3.computeLength($vec3: Vector3): Float                                                        |
| vec3.computeLengthSquared($vec3: Vector3): Float                                                 |
| vec3.getX($vec3: Vector3): Float                                                                 |
| vec3.getY($vec3: Vector3): Float                                                                 |
| vec3.getZ($vec3: Vector3): Float                                                                 |
| vec3.normalize($vec3: Vector3): Vector3                                                          |
| vec4($x: Float, $y: Float, $z: Float, $w: Float): Vector4                                        |
| vec4.computeDotProduct($a: Vector4, $b: Vector4): Float                                          |
| vec4.computeLength($vec4: Vector4): Float                                                        |
| vec4.computeLengthSquared($vec4: Vector4): Float                                                 |
| vec4.getW($vec4: Vector4): Float                                                                 |
| vec4.getX($vec4: Vector4): Float                                                                 |
| vec4.getY($vec4: Vector4): Float                                                                 |
| vec4.getZ($vec4: Vector4): Float                                                                 |
| vec4.normalize($vec4: Vector4): Vector4                                                          |


# 2. Operators

| Op | Method                                                                                      |
|----|---------------------------------------------------------------------------------------------|
| !  | not($bool: Boolean): Boolean                                                                |
| != | notequal(...): Boolean                                                                      |
| && | and(...): Boolean                                                                           |
| *  | mul(...): Mixed                                                                             |
| +  | add(...): Mixed                                                                             |
| -  | sub(...): Mixed                                                                             |
| /  | div(...): Mixed                                                                             |
| <  | lesser($a: Float, $b: Float): Boolean                                                       |
| <= | lesserequals($a: Float, $b: Float): Boolean                                                 |
| =  | setVariable(...): Mixed                                                                     |
| == | equals(...): Boolean                                                                        |
| >  | greater($a: Float, $b: Float): Boolean                                                      |
| >= | greaterequals($a: Float, $b: Float): Boolean                                                |
| \|\|| or(...): Boolean                                                                           |
