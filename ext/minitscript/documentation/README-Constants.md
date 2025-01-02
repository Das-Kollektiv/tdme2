![LOGO](https://raw.githubusercontent.com/andreasdr/minitscript/master/resources/github/minitscript-logo.png)

# 1. Constants

| Name                                                        | Value                              |
|-------------------------------------------------------------|------------------------------------|
| $$.application::CPU                                           | e.g. X64                           |
| $$.application::EXITCODE_FAILURE                              | 1                                  |
| $$.application::EXITCODE_SUCCESS                              | 0                                  |
| $$.application::OS                                            | e.g. Linux                         |
| $$.http::HTTP_STATUS_ACCEPTED                                 | 202                                |
| $$.http::HTTP_STATUS_ALREADYREPORTED                          | 208                                |
| $$.http::HTTP_STATUS_BADGATEWAY                               | 502                                |
| $$.http::HTTP_STATUS_BADREQUEST                               | 400                                |
| $$.http::HTTP_STATUS_CONFLICT                                 | 409                                |
| $$.http::HTTP_STATUS_CONTENTTOOLARGE                          | 413                                |
| $$.http::HTTP_STATUS_CONTINUE                                 | 100                                |
| $$.http::HTTP_STATUS_CREATED                                  | 201                                |
| $$.http::HTTP_STATUS_EARLYHINTS                               | 103                                |
| $$.http::HTTP_STATUS_EXPECTATIONFAILED                        | 417                                |
| $$.http::HTTP_STATUS_FAILEDDEPENDENCY                         | 424                                |
| $$.http::HTTP_STATUS_FORBIDDEN                                | 403                                |
| $$.http::HTTP_STATUS_FOUND                                    | 302                                |
| $$.http::HTTP_STATUS_GATEWAYTIMEOUT                           | 504                                |
| $$.http::HTTP_STATUS_GONE                                     | 410                                |
| $$.http::HTTP_STATUS_HTTPVERSIONNOTSUPPORTED                  | 505                                |
| $$.http::HTTP_STATUS_IMATEAPOT                                | 418                                |
| $$.http::HTTP_STATUS_IMUSED                                   | 226                                |
| $$.http::HTTP_STATUS_INSUFFICIENTSTORAGE                      | 507                                |
| $$.http::HTTP_STATUS_INTERNALSERVERERROR                      | 500                                |
| $$.http::HTTP_STATUS_LENGTHREQUIRED                           | 411                                |
| $$.http::HTTP_STATUS_LOCKED                                   | 423                                |
| $$.http::HTTP_STATUS_LOOPDETECTED                             | 508                                |
| $$.http::HTTP_STATUS_MAX                                      | 1023                               |
| $$.http::HTTP_STATUS_METHODNOTALLOWED                         | 405                                |
| $$.http::HTTP_STATUS_MISDIRECTEDREQUEST                       | 421                                |
| $$.http::HTTP_STATUS_MOVEDPERMANENTLY                         | 301                                |
| $$.http::HTTP_STATUS_MULTIPLECHOICES                          | 300                                |
| $$.http::HTTP_STATUS_MULTISTATUS                              | 207                                |
| $$.http::HTTP_STATUS_NETWORKAUTHENTICATIONREQUIRED            | 511                                |
| $$.http::HTTP_STATUS_NOCONTENT                                | 204                                |
| $$.http::HTTP_STATUS_NONAUTHORITATIVEINFORMATION              | 203                                |
| $$.http::HTTP_STATUS_NOTACCEPTABLE                            | 406                                |
| $$.http::HTTP_STATUS_NOTEXTENDED                              | 510                                |
| $$.http::HTTP_STATUS_NOTFOUND                                 | 404                                |
| $$.http::HTTP_STATUS_NOTIMPLEMENTED                           | 501                                |
| $$.http::HTTP_STATUS_NOTMODIFIED                              | 304                                |
| $$.http::HTTP_STATUS_OK                                       | 200                                |
| $$.http::HTTP_STATUS_PARTIALCONTENT                           | 206                                |
| $$.http::HTTP_STATUS_PAYLOADTOOLARGE                          | 413                                |
| $$.http::HTTP_STATUS_PAYMENTREQUIRED                          | 402                                |
| $$.http::HTTP_STATUS_PERMANENTREDIRECT                        | 308                                |
| $$.http::HTTP_STATUS_PRECONDITIONFAILED                       | 412                                |
| $$.http::HTTP_STATUS_PRECONDITIONREQUIRED                     | 428                                |
| $$.http::HTTP_STATUS_PROCESSING                               | 102                                |
| $$.http::HTTP_STATUS_PROXYAUTHENTICATIONREQUIRED              | 407                                |
| $$.http::HTTP_STATUS_RANGENOTSATISFIABLE                      | 416                                |
| $$.http::HTTP_STATUS_REQUESTHEADERFIELDSTOOLARGE              | 431                                |
| $$.http::HTTP_STATUS_REQUESTTIMEOUT                           | 408                                |
| $$.http::HTTP_STATUS_RESETCONTENT                             | 205                                |
| $$.http::HTTP_STATUS_SEEOTHER                                 | 303                                |
| $$.http::HTTP_STATUS_SERVICEUNAVAILABLE                       | 503                                |
| $$.http::HTTP_STATUS_SWITCHINGPROTOCOLS                       | 101                                |
| $$.http::HTTP_STATUS_TEMPORARYREDIRECT                        | 307                                |
| $$.http::HTTP_STATUS_TOOEARLY                                 | 425                                |
| $$.http::HTTP_STATUS_TOOMANYREQUESTS                          | 429                                |
| $$.http::HTTP_STATUS_UNAUTHORIZED                             | 401                                |
| $$.http::HTTP_STATUS_UNAVAILABLEFORLEGALREASONS               | 451                                |
| $$.http::HTTP_STATUS_UNPROCESSABLECONTENT                     | 422                                |
| $$.http::HTTP_STATUS_UNPROCESSABLEENTITY                      | 422                                |
| $$.http::HTTP_STATUS_UNSUPPORTEDMEDIATYPE                     | 415                                |
| $$.http::HTTP_STATUS_UPGRADEREQUIRED                          | 426                                |
| $$.http::HTTP_STATUS_URITOOLONG                               | 414                                |
| $$.http::HTTP_STATUS_USEPROXY                                 | 305                                |
| $$.http::HTTP_STATUS_VARIANTALSONEGOTIATES                    | 506                                |
| $$.math::DEG2RAD                                              | 0.017453                           |
| $$.math::EPSILON                                              | 0.000000                           |
| $$.math::PI                                                   | 3.141593                           |

Please note:
- $$.application::CPU can have the following values: FreeBSD, Haiku, Linux, MacOSX, NetBSD, OpenBSD, Windows-MSC, Windows-MINGW, Unknown
- $$.application::OS can have the following values: X86, X64, IA64, ARM64, ARM, RISCV64, RISCV, PPC64, PPC, Unknown

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
