#include <tdme/utilities/MiniScript.h>

#include <algorithm>
#include <initializer_list>
#include <map>
#include <memory>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/model/RotationOrder.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemException.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScriptMath.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/SHA256.h>
#include <tdme/utilities/Time.h>

using std::find;
using std::initializer_list;
using std::make_unique;
using std::map;
using std::move;
using std::remove;
using std::reverse;
using std::sort;
using std::span;
using std::stack;
using std::string;
using std::string_view;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::logics::LogicMiniScript;
using tdme::engine::model::RotationOrder;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::gui::GUIParser;
using tdme::gui::scripting::GUIMiniScript;
using tdme::math::Math;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemException;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Character;
using tdme::utilities::Console;
using tdme::utilities::Float;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptMath;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;
using tdme::utilities::SHA256;
using tdme::utilities::Time;

const string MiniScript::OPERATOR_CHARS = "+-!~/%<>=&^|";
const string MiniScript::METHOD_SCRIPTCALL = "script.call";
const string MiniScript::METHOD_ENABLENAMEDCONDITION = "script.enableNamedCondition";
const string MiniScript::METHOD_DISABLENAMEDCONDITION = "script.disableNamedCondition";

const string MiniScript::ScriptVariable::CLASSNAME_NONE = "";
const string MiniScript::ScriptVariable::CLASSNAME_STRING = "string";
const string MiniScript::ScriptVariable::CLASSNAME_VEC2 = "vec2";
const string MiniScript::ScriptVariable::CLASSNAME_VEC3 = "vec3";
const string MiniScript::ScriptVariable::CLASSNAME_VEC4 = "vec4";
const string MiniScript::ScriptVariable::CLASSNAME_QUATERNION = "quaternion";
const string MiniScript::ScriptVariable::CLASSNAME_MAT3 = "mat3";
const string MiniScript::ScriptVariable::CLASSNAME_MAT4 = "mat4";
const string MiniScript::ScriptVariable::CLASSNAME_TRANSFORM = "transform";
const string MiniScript::ScriptVariable::CLASSNAME_ARRAY = "array";
const string MiniScript::ScriptVariable::CLASSNAME_MAP = "map";
const string MiniScript::ScriptVariable::CLASSNAME_SET = "set";

const vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ALL = {};
const vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ENGINE = { "initializeEngine", "updateEngine" };
const vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_LOGIC = { "initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed" };
const vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ENGINELOGIC = {
	// engine
	"initializeEngine", "updateEngine",
	// logic
	"initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed"
};
const vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTION_GUI = {};

MiniScript* MiniScript::loadScript(const string& pathName, const string& fileName) {
	// we need to detect MiniScript variant
	vector<string> scriptAsStringArray;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptAsStringArray);
	} catch (Exception& exception) {
		Console::println("MiniScript::loadScript(): An error occurred: " + string(exception.what()));
		return nullptr;
	}

	// detect MiniScript variant
	auto logicMiniScript = false;
	auto guiMiniScript = false;
	array<string, 2> logicMiniScriptFunctions {
		"updateEngine",
		"updateLogic"
	};
	array<string, 12> guiMiniScriptFunctions {
		"onAction",
		"onChange",
		"onMouseOver",
		"onContextMenuRequest",
		"onFocus",
		"onUnfocus",
		"onMove",
		"onMoveRelease",
		"onTooltipShowRequest",
		"onTooltipCloseRequest",
		"onDragRequest",
		"onTick"
	};
	for (const auto& scriptLine: scriptAsStringArray) {
		for (const auto& functionName: logicMiniScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				logicMiniScript = true;
				break;
			}
		}
		if (logicMiniScript == true) break;
		for (const auto& functionName: guiMiniScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				guiMiniScript = true;
				break;
			}
		}
		if (guiMiniScript == true) break;
	}

	// load specific MiniScript
	unique_ptr<MiniScript> scriptInstance;
	if (logicMiniScript == true) {
		scriptInstance = make_unique<LogicMiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	} else
	if (guiMiniScript == true) {
		scriptInstance = make_unique<GUIMiniScript>(nullptr);
		scriptInstance->parseScript(pathName, fileName);
	} else {
		scriptInstance = make_unique<MiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	}
	//
	return scriptInstance.release();
}

const string MiniScript::getBaseClass() {
	return "tdme::utilities::MiniScript";
}

const vector<string> MiniScript::getTranspilationUnits() {
	return {
		"src/tdme/utilities/MiniScript.cpp",
		"src/tdme/utilities/MiniScriptMath.cpp"
	};
}

MiniScript::MiniScript() {
	setNative(false);
	pushScriptState();
}

MiniScript::~MiniScript() {
	for (const auto& [scriptMethodId, scriptMethod]: scriptMethods) delete scriptMethod;
	for (const auto& [scriptStateMachineStateId, scriptStateMachineState]: scriptStateMachineStates) delete scriptStateMachineState;
	while (scriptStateStack.empty() == false) popScriptState();
}

void MiniScript::registerStateMachineState(ScriptStateMachineState* state) {
	auto scriptStateMachineStateIt = scriptStateMachineStates.find(state->getId());
	if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
		Console::println("MiniScript::registerStateMachineState(): '" + scriptFileName + "': state with id + " + to_string(state->getId()) + ", name '" + state->getName() + "' already registered.");
		return;
	}
	scriptStateMachineStates[state->getId()] = state;
}

void MiniScript::initializeNative() {
}

void MiniScript::registerMethod(ScriptMethod* scriptMethod) {
	auto scriptMethodsIt = scriptMethods.find(scriptMethod->getMethodName());
	if (scriptMethodsIt != scriptMethods.end()) {
		Console::println("MiniScript::registerMethod(): '" + scriptFileName + "': method with name '" + scriptMethod->getMethodName() + "' already registered.");
		return;
	}
	scriptMethods[scriptMethod->getMethodName()] = scriptMethod;
}

void MiniScript::executeScriptLine() {
	auto& scriptState = getScriptState();
	if (scriptState.scriptIdx == SCRIPTIDX_NONE || scriptState.statementIdx == STATEMENTIDX_NONE || scriptState.running == false) return;
	//
	const auto& script = scripts[scriptState.scriptIdx];
	if (script.statements.empty() == true) return;
	// take goto statement index into account
	if (scriptState.gotoStatementIdx != STATEMENTIDX_NONE) {
		scriptState.statementIdx = scriptState.gotoStatementIdx;
		scriptState.gotoStatementIdx = STATEMENTIDX_NONE;
	}
	//
	const auto& statement = script.statements[scriptState.statementIdx];
	const auto& syntaxTree = script.syntaxTree[scriptState.statementIdx];
	if (VERBOSE == true) Console::println("MiniScript::executeScriptLine(): " + getStatementInformation(statement));

	//
	auto returnValue = executeScriptStatement(syntaxTree, statement);

	//
	scriptState.statementIdx++;
	if (scriptState.statementIdx >= script.statements.size()) {
		scriptState.scriptIdx = SCRIPTIDX_NONE;
		scriptState.statementIdx = STATEMENTIDX_NONE;
		setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
	}
}

bool MiniScript::parseScriptStatement(const string_view& executableStatement, string_view& methodName, vector<string_view>& arguments, const ScriptStatement& statement, string& accessObjectMemberStatement) {
	// TODO: improve me!
	if (VERBOSE == true) Console::println("MiniScript::parseScriptStatement(): " + getStatementInformation(statement) + ": '" + string(executableStatement) + "'");
	string_view objectMemberAccessObject;
	string_view objectMemberAccessMethod;
	auto objectMemberAccess = getObjectMemberAccess(executableStatement, objectMemberAccessObject, objectMemberAccessMethod, statement);
	auto executableStatementStartIdx = objectMemberAccess == true?objectMemberAccessObject.size() + 2:0;
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto quote = '\0';
	auto methodStart = string::npos;
	auto methodEnd = string::npos;
	auto argumentStart = string::npos;
	auto argumentEnd = string::npos;
	auto quotedArgumentStart = string::npos;
	auto quotedArgumentEnd = string::npos;
	auto lc  = '\0';
	//
	for (auto i = executableStatementStartIdx; i < executableStatement.size(); i++) {
		auto c = executableStatement[i];
		if (squareBracketCount == 0 && curlyBracketCount == 0 && ((c == '"' || c == '\'') && lc != '\\')) {
			if (bracketCount == 1) {
				if (quote == '\0') {
					quotedArgumentStart = i;
					quote = c;
				} else
				if (quote == c) {
					quotedArgumentEnd = i;
					quote = '\0';
				}
			} else {
				if (quote == '\0') {
					if (argumentStart == string::npos) {
						argumentStart = i;
					}
					quote = c;
				} else
				if (quote == c) {
					argumentEnd = i;
					quote = '\0';
				}
			}
		} else
		if (quote != '\0') {
			if (bracketCount == 1) {
				quotedArgumentEnd = i;
			} else {
				if (argumentStart == string::npos) {
					argumentStart = i;
				} else {
					argumentEnd = i;
				}
			}
		} else {
			// TODO: guess I need to check here too for balance of [ and ] also
			if (c == '(') {
				bracketCount++;
				if (bracketCount > 1) {
					if (argumentStart == string::npos) {
						argumentStart = i + 1;
					} else {
						argumentEnd = i;
					}
				}
			} else
			if (c == ')') {
				bracketCount--;
				if (bracketCount == 0) {
					if (quotedArgumentStart != string::npos) {
						if (quotedArgumentEnd == string::npos) quotedArgumentEnd = i - 1;
						auto argumentLength = quotedArgumentEnd - quotedArgumentStart + 1;
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&executableStatement[quotedArgumentStart], argumentLength)));
						quotedArgumentStart = string::npos;
						quotedArgumentEnd = string::npos;
					} else
					if (argumentStart != string::npos) {
						if (argumentEnd == string::npos) argumentEnd = i - 1;
						auto argumentLength = argumentEnd - argumentStart + 1;
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&executableStatement[argumentStart], argumentLength)));
						argumentStart = string::npos;
						argumentEnd = string::npos;
					}
				} else {
					if (argumentStart == string::npos) {
						argumentStart = i + 1;
					} else {
						argumentEnd = i;
					}
				}
			} else
			if (c == '[' && curlyBracketCount == 0) {
				if (squareBracketCount == 0) {
					if (argumentStart == string::npos) {
						argumentStart = i;
					} else {
						argumentEnd = i;
					}
				}
				squareBracketCount++;
			} else
			if (c == ']' && curlyBracketCount == 0) {
				squareBracketCount--;
				if (squareBracketCount == 0) {
					if (argumentStart == string::npos) {
						argumentStart = i;
					} else {
						argumentEnd = i;
					}
				}
			} else
			if (c == '{') {
				if (curlyBracketCount == 0) {
					if (argumentStart == string::npos) {
						argumentStart = i;
					} else {
						argumentEnd = i;
					}
				}
				curlyBracketCount++;
			} else
			if (c == '}') {
				curlyBracketCount--;
				if (curlyBracketCount == 0) {
					if (argumentStart == string::npos) {
						argumentStart = i;
					} else {
						argumentEnd = i;
					}
				}
			} else
			if (squareBracketCount == 0 && curlyBracketCount == 0) {
				if (c == ',') {
					if (bracketCount == 1) {
						if (quotedArgumentStart != string::npos) {
							if (quotedArgumentEnd == string::npos) quotedArgumentEnd = i - 1;
							auto argumentLength = quotedArgumentEnd - quotedArgumentStart + 1;
							if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&executableStatement[quotedArgumentStart], argumentLength)));
							quotedArgumentStart = string::npos;
							quotedArgumentEnd = string::npos;
						} else
						if (argumentStart != string::npos) {
							if (argumentEnd == string::npos) argumentEnd = i - 1;
							auto argumentLength = argumentEnd - argumentStart + 1;
							if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&executableStatement[argumentStart], argumentEnd - argumentStart + 1)));
							argumentStart = string::npos;
							argumentEnd = string::npos;
						}
					} else {
						if (argumentStart == string::npos) {
							argumentStart = i + 1;
						} else {
							argumentEnd = i;
						}
					}
				} else
				if (bracketCount == 0) {
					if (methodStart == string::npos) methodStart = i; else methodEnd = i;
				} else {
					if (argumentStart == string::npos) {
						if (Character::isSpace(c) == false) {
							argumentStart = i;
						}
					} else {
						argumentEnd = i;
					}
				}
			}
		}
		//
		lc = c;
	}
	//
	if (methodStart != string::npos && methodEnd != string::npos) {
		methodName = StringTools::viewTrim(string_view(&executableStatement[methodStart], methodEnd - methodStart + 1));
	}
	//
	if (objectMemberAccess == true) {
		// construct executable statement and arguments
		string_view evaluateMemberAccessMethodName;
		vector<string_view> evaluateMemberAccessArguments;

		//
		auto objectMemberAccessObjectVariable = viewIsVariableAccess(objectMemberAccessObject);

		// construct new method name and argument string views
		accessObjectMemberStatement.reserve(16384); // TODO: check me later
		auto idx = accessObjectMemberStatement.size();
		accessObjectMemberStatement+= "internal.script.evaluateMemberAccess";
		evaluateMemberAccessMethodName = string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx);
		accessObjectMemberStatement+= "(";
		idx = accessObjectMemberStatement.size();
		accessObjectMemberStatement+= objectMemberAccessObjectVariable == true?"\"" + string(objectMemberAccessObject) + "\"":"null";
		evaluateMemberAccessArguments.push_back(string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx));
		idx = accessObjectMemberStatement.size();
		accessObjectMemberStatement+= ", ";
		idx = accessObjectMemberStatement.size();
		accessObjectMemberStatement+= objectMemberAccessObjectVariable == true?"null":string(objectMemberAccessObject);
		evaluateMemberAccessArguments.push_back(string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx));
		accessObjectMemberStatement+= ", ";
		idx = accessObjectMemberStatement.size();
		accessObjectMemberStatement+= "\"" + string(methodName) + "\"";
		evaluateMemberAccessArguments.push_back(string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx));
		for (const auto& argument: arguments) {
			auto argumentVariable = viewIsVariableAccess(argument);
			accessObjectMemberStatement+= ", ";
			idx = accessObjectMemberStatement.size();
			accessObjectMemberStatement+= argumentVariable == true?"\"" + string(argument) + "\"":"null";
			evaluateMemberAccessArguments.push_back(string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx));
			accessObjectMemberStatement+= ", ";
			idx = accessObjectMemberStatement.size();
			accessObjectMemberStatement+= argumentVariable == true?"null":string(argument);
			evaluateMemberAccessArguments.push_back(string_view(&accessObjectMemberStatement.data()[idx], accessObjectMemberStatement.size() - idx));
		}
		accessObjectMemberStatement+= ")";
		// set up new results
		methodName = evaluateMemberAccessMethodName;
		arguments = evaluateMemberAccessArguments;
	}

	//
	if (VERBOSE == true) {
		Console::print("MiniScript::parseScriptStatement(): " + getStatementInformation(statement) + ": method: '" + string(methodName) + "', arguments: ");
		int variableIdx = 0;
		for (const auto& argument: arguments) {
			if (variableIdx > 0) Console::print(", ");
			Console::print("'" + string(argument) + "'");
			variableIdx++;
		}
		Console::println();
	}

	// complain about bracket count
	if (bracketCount != 0) {
		Console::println(getStatementInformation(statement) + ": " + string(executableStatement) + "': unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(string(executableStatement) + ": unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}
	// complain about square bracket count
	if (squareBracketCount != 0) {
		Console::println(getStatementInformation(statement) + ": " + string(executableStatement) + "': unbalanced square bracket count: " + to_string(Math::abs(squareBracketCount)) + " " + (squareBracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(string(executableStatement) + ": unbalanced square bracket count: " + to_string(Math::abs(squareBracketCount)) + " " + (squareBracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}
	// complain about curly bracket count
	if (curlyBracketCount != 0) {
		Console::println(getStatementInformation(statement) + ": " + string(executableStatement) + "': unbalanced curly bracket count: " + to_string(Math::abs(curlyBracketCount)) + " " + (curlyBracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(string(executableStatement) + ": unbalanced curly bracket count: " + to_string(Math::abs(curlyBracketCount)) + " " + (curlyBracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}

	//
	return true;
}

MiniScript::ScriptVariable MiniScript::executeScriptStatement(const ScriptSyntaxTreeNode& syntaxTree, const ScriptStatement& statement) {
	if (VERBOSE == true) Console::println("MiniScript::executeScriptStatement(): " + getStatementInformation(statement) + "': " + syntaxTree.value.getValueAsString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	// return on literal or empty syntaxTree
	if (syntaxTree.type != ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && syntaxTree.type != ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION) {
		return initializeVariable(syntaxTree.value);
	}
	//
	vector<ScriptVariable> argumentValues;
	ScriptVariable returnValue;
	// construct argument values
	for (const auto& argument: syntaxTree.arguments) {
		switch (argument.type) {
			case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
				{
					argumentValues.push_back(initializeVariable(argument.value));
					break;
				}
			case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
				{
					argumentValues.push_back(executeScriptStatement(argument, statement));
					break;
				}
			default:
				break;
		}
	}
	//
	if (VERBOSE == true) {
		Console::println("MiniScript::executeScriptStatement(): '" + getStatementInformation(statement) + ": " + syntaxTree.value.getValueAsString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	}
	// try first user functions
	if (syntaxTree.method == nullptr) {
		auto method = syntaxTree.value.getValueAsString();
		auto scriptFunctionsIt = scriptFunctions.find(method);
		if (scriptFunctionsIt != scriptFunctions.end()) {
			auto scriptIdx = scriptFunctionsIt->second;
			// call
			span argumentValuesSpan(argumentValues);
			call(scriptIdx, argumentValuesSpan, returnValue);
			//
			return returnValue;
		} else {
			Console::println(getStatementInformation(statement) + ": unknown function '" + string(syntaxTree.value.getValueAsString()) + "'");
			startErrorScript();
		}
	} else {
		// try methods next
		auto scriptMethod = syntaxTree.method;
		// validate arguments
		{
			auto argumentIdx = 0;
			for (const auto& argumentType: scriptMethod->getArgumentTypes()) {
				auto argumentOk = true;
				// nullable and NULL argument
				if (argumentType.nullable == true &&
					argumentIdx >= 0 && argumentIdx < argumentValues.size() &&
					argumentValues[argumentIdx].getType() == TYPE_NULL) {
					argumentOk = true;
				} else {
					// otherwise check the argument
					switch(argumentType.type) {
						case TYPE_NULL:
							break;
						case TYPE_BOOLEAN:
							{
								bool booleanValue;
								argumentOk = getBooleanValue(argumentValues, argumentIdx, booleanValue, argumentType.optional);
							}
							break;
						case TYPE_INTEGER:
							{
								int64_t integerValue;
								argumentOk = getIntegerValue(argumentValues, argumentIdx, integerValue, argumentType.optional);
							}
							break;
						case TYPE_FLOAT:
							{
								float floatValue;
								argumentOk = getFloatValue(argumentValues, argumentIdx, floatValue, argumentType.optional);
							}
							break;
						case TYPE_STRING:
							{
								string stringValue;
								argumentOk = getStringValue(argumentValues, argumentIdx, stringValue, argumentType.optional);
							}
							break;
						case TYPE_VECTOR2:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_VECTOR2;
								break;
							}
						case TYPE_VECTOR3:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_VECTOR3;
								break;
							}
						case TYPE_VECTOR4:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_VECTOR4;
								break;
							}
						case TYPE_QUATERNION:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_QUATERNION;
								break;
							}
						case TYPE_MATRIX3x3:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_MATRIX3x3;
								break;
							}
						case TYPE_MATRIX4x4:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_MATRIX4x4;
								break;
							}
						case TYPE_TRANSFORM:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_TRANSFORM;
								break;
							}
						case TYPE_ARRAY:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_ARRAY;
								break;
							}
						case TYPE_MAP:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_MAP;
								break;
							}
						case TYPE_SET:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == TYPE_SET;
								break;
							}
						case TYPE_PSEUDO_NUMBER:
							{
								float floatValue;
								argumentOk = getFloatValue(argumentValues, argumentIdx, floatValue, argumentType.optional);
								break;
							}
					}
				}
				if (argumentOk == false) {
					Console::println(
						getStatementInformation(statement) +
						": method '" + string(syntaxTree.value.getValueAsString()) + "'" +
						": argument value @ " + to_string(argumentIdx) + ": expected " + ScriptVariable::getTypeAsString(argumentType.type) + ", but got: " + (argumentIdx < argumentValues.size()?argumentValues[argumentIdx].getAsString():"nothing"));
				}
				argumentIdx++;
			}
			if (scriptMethod->isVariadic() == false && argumentValues.size() > scriptMethod->getArgumentTypes().size()) {
				Console::println(
					getStatementInformation(statement) +
					": method '" + string(syntaxTree.value.getValueAsString()) + "'" +
					": too many arguments: expected: " + to_string(scriptMethod->getArgumentTypes().size()) + ", got " + to_string(argumentValues.size()));
			}
		}
		// execute method
		span argumentValuesSpan(argumentValues);
		scriptMethod->executeMethod(argumentValuesSpan, returnValue, statement);
		// check return type
		if (scriptMethod->isReturnValueNullable() == true && returnValue.getType() == TYPE_NULL) {
			// no op, this is a valid return value
		} else
		if (MiniScript::ScriptVariable::isExpectedType(returnValue.getType(), scriptMethod->getReturnValueType()) == false) {
			Console::println(
				getStatementInformation(statement) +
				": method '" + string(syntaxTree.value.getValueAsString()) + "'" +
				": return value: expected " + ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable()) + ", but got: " + ScriptVariable::getReturnTypeAsString(returnValue.getType(), false));
		}
		//
		return returnValue;
	}
	//
	return returnValue;
}

bool MiniScript::createScriptStatementSyntaxTree(const string_view& methodName, const vector<string_view>& arguments, const ScriptStatement& statement, ScriptSyntaxTreeNode& syntaxTree) {
	if (VERBOSE == true) Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": " + string(methodName) + "(" + getArgumentsAsString(arguments) + ")");
	// method/function
	auto scriptFunctionIdx = SCRIPTIDX_NONE;
	ScriptMethod* scriptMethod = nullptr;
	// try first user functions
	{
		auto scriptFunctionsIt = scriptFunctions.find(string(methodName));
		if (scriptFunctionsIt != scriptFunctions.end()) {
			scriptFunctionIdx = scriptFunctionsIt->second;
		}
	}
	// try methods next
	{
		auto scriptMethodsIt = scriptMethods.find(string(methodName));
		if (scriptMethodsIt != scriptMethods.end()) {
			scriptMethod = scriptMethodsIt->second;
		}
	}

	// arguments
	vector<bool> argumentReferences(0);
	if (scriptFunctionIdx != SCRIPTIDX_NONE) {
		argumentReferences.resize(scripts[scriptFunctionIdx].arguments.size());
		auto argumentIdx = 0;
		for (const auto& argument: scripts[scriptFunctionIdx].arguments) {
			argumentReferences[argumentIdx++] = argument.reference;
		}
	} else
	if (scriptMethod != nullptr) {
		argumentReferences.resize(scriptMethod->getArgumentTypes().size());
		auto argumentIdx = 0;
		for (const auto& argument: scriptMethod->getArgumentTypes()) {
			argumentReferences[argumentIdx++] = argument.reference;
		}
	}
	auto argumentIdx = 0;
	for (const auto& argument: arguments) {
		// object member access
		string_view accessObjectMemberObject;
		string_view accessObjectMemberMethod;
		if (getObjectMemberAccess(argument, accessObjectMemberObject, accessObjectMemberMethod, statement) == true) {
			// method call
			string_view subMethodName;
			vector<string_view> subArguments;
			string accessObjectMemberStatement;
			if (parseScriptStatement(argument, subMethodName, subArguments, statement, accessObjectMemberStatement) == true) {
				ScriptSyntaxTreeNode subSyntaxTree;
				if (createScriptStatementSyntaxTree(subMethodName, subArguments, statement, subSyntaxTree) == false) {
					return false;
				}
				syntaxTree.arguments.push_back(subSyntaxTree);
			} else {
				return false;
			}
		} else
		// plain variable
		if (viewIsVariableAccess(argument) == true) {
			//
			ScriptVariable value;
			value.setValue(string(argument));

			// look up getVariable method
			string methodName = argumentIdx >= argumentReferences.size() || argumentReferences[argumentIdx] == false?"getVariable":"getVariableReference";
			ScriptMethod* method = nullptr;
			{
				auto scriptMethodsIt = scriptMethods.find(methodName);
				if (scriptMethodsIt != scriptMethods.end()) {
					method = scriptMethodsIt->second;
				} else {
					Console::println(getStatementInformation(statement) + ": unknown method '" + methodName + "'");
					//
					parseErrors.push_back(getStatementInformation(statement) + ": unknown method '" + methodName + "'");
					//
					return false;
				}
			}

			syntaxTree.arguments.emplace_back(
				ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD,
				MiniScript::ScriptVariable(methodName),
				method,
				initializer_list<ScriptSyntaxTreeNode>
					{
						{
							ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
							value,
							nullptr,
							{}
						}
					}
			);
		} else
		// method call
		if (argument.empty() == false &&
			StringTools::viewStartsWith(argument, "\"") == false &&
			StringTools::viewEndsWith(argument, "\"") == false &&
			StringTools::viewStartsWith(argument, "[") == false &&
			StringTools::viewEndsWith(argument, "]") == false &&
			StringTools::viewStartsWith(argument, "}") == false &&
			StringTools::viewEndsWith(argument, "}") == false &&
			argument.find('(') != string::npos &&
			argument.find(')') != string::npos) {
			// method call
			string_view subMethodName;
			vector<string_view> subArguments;
			string accessObjectMemberStatement;
			if (parseScriptStatement(argument, subMethodName, subArguments, statement, accessObjectMemberStatement) == true) {
				ScriptSyntaxTreeNode subSyntaxTree;
				if (createScriptStatementSyntaxTree(subMethodName, subArguments, statement, subSyntaxTree) == false) {
					return false;
				}
				syntaxTree.arguments.push_back(subSyntaxTree);
			} else {
				//
				return false;
			}
		} else {
			// string literal
			ScriptVariable argumentValue;
			if (StringTools::viewStartsWith(argument, "\"") == true &&
				StringTools::viewEndsWith(argument, "\"") == true) {
				//
				ScriptVariable value;
				value.setValue(string(StringTools::viewSubstring(argument, 1, argument.size() - 1)));
				//
				syntaxTree.arguments.emplace_back(
					ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
					value,
					nullptr,
					initializer_list<ScriptSyntaxTreeNode>{}
				);
			} else {
				// implicitely literal
				ScriptVariable value;
				value.setImplicitTypedValueFromStringView(argument, this, statement);
				//
				syntaxTree.arguments.emplace_back(
					ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
					value,
					nullptr,
					initializer_list<ScriptSyntaxTreeNode>{}
				);
			}
		}
		//
		argumentIdx++;
	}
	// try first user functions
	if (scriptFunctionIdx != SCRIPTIDX_NONE) {
		syntaxTree.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION;
		syntaxTree.value = string(methodName);
		//
		return true;
	} else
	// try methods next
	if (scriptMethod != nullptr) {
		syntaxTree.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
		syntaxTree.value = string(methodName);
		syntaxTree.method = scriptMethod;
		//
		return true;
	} else {
		Console::println(getStatementInformation(statement) + ": unknown function/method: " + string(methodName) + "()");
		//
		parseErrors.push_back(getStatementInformation(statement) + ": unknown function/method: " + string(methodName) + "()");
		//
		return false;
	}
	//
	return false;
}

bool MiniScript::validateCallable(const string& function) {
	auto functionScriptIdx = getFunctionScriptIdx(function);
	if (functionScriptIdx == SCRIPTIDX_NONE) {
		Console::println("MiniScript::validateCallable(): function not found: " + function);
		return false;
	}
	//
	const auto& script = scripts[functionScriptIdx];
	auto statementIdx = STATEMENTIDX_FIRST;
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateCallable(syntaxTreeNode, statement) == false) {
			//
			return false;
		}
	}
	//
	return true;
}

bool MiniScript::validateCallable(const ScriptSyntaxTreeNode& syntaxTreeNode, const ScriptStatement& statement) {
	//
	switch (syntaxTreeNode.type) {
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				const auto& contextFunctions = syntaxTreeNode.method->getContextFunctions();
				if (contextFunctions.empty() == false) {
					//
					Console::println(
						"MiniScript::validateCallable(): '" +
						getStatementInformation(statement) +
						": method " +
						syntaxTreeNode.method->getMethodName() + "() can not be called within a callable function"
					);
					//
					parseErrors.push_back(
						getStatementInformation(statement) +
						": method " +
						syntaxTreeNode.method->getMethodName() + "() can not be called within a callable function"
					);
					//
					return false;
				}
			}
			break;
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateCallable(argument, statement) == false) return false;
				}
				//
				validateCallable(syntaxTreeNode.value.getValueAsString());
				//
				break;
			}
		default:
			break;
	}
	//
	return true;
}

bool MiniScript::validateContextFunctions(const string& function, vector<string>& functionStack) {
	auto functionScriptIdx = getFunctionScriptIdx(function);
	if (functionScriptIdx == SCRIPTIDX_NONE) {
		Console::println("MiniScript::validateContextFunctions(): function not found: " + function);
		return false;
	}
	//
	const auto& script = scripts[functionScriptIdx];
	auto statementIdx = STATEMENTIDX_FIRST;
	//
	functionStack.push_back(script.condition);
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateContextFunctions(syntaxTreeNode, functionStack, statement) == false) {
			//
			return false;
		}
	}
	//
	functionStack.erase(functionStack.begin() + functionStack.size() - 1);
	//
	return true;
}

bool MiniScript::validateContextFunctions(const ScriptSyntaxTreeNode& syntaxTreeNode, vector<string>& functionStack, const ScriptStatement& statement) {
	//
	switch (syntaxTreeNode.type) {
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				const auto& contextFunctions = syntaxTreeNode.method->getContextFunctions();
				if (contextFunctions.empty() == false) {
					//
					string contextFunctionsString;
					for (const auto &contextFunction: contextFunctions) {
						if (contextFunctionsString.empty() == false) contextFunctionsString+= ", ";
						contextFunctionsString+= contextFunction + "()";
					}
					//
					const auto& functionStackFunction = functionStack[0];
					if (find(contextFunctions.begin(), contextFunctions.end(), functionStackFunction) == contextFunctions.end()) {
						//
						string contextFunctionsString;
						for (const auto &contextFunction: contextFunctions) {
							if (contextFunctionsString.empty() == false) contextFunctionsString+= ", ";
							contextFunctionsString+= contextFunction + "()";
						}
						//
						Console::println(
							"MiniScript::validateContextFunctions(): '" +
							getStatementInformation(statement) +
							": method " +
							syntaxTreeNode.method->getMethodName() + "() can only be called within the following functions: " +
							contextFunctionsString +
							", but was called from " +
							functionStackFunction + "()"
						);
						//
						parseErrors.push_back(
							getStatementInformation(statement) +
							": method " +
							syntaxTreeNode.method->getMethodName() + "() can only be called within the following functions: " +
							contextFunctionsString +
							", but was called from " +
							functionStackFunction + "()"
						);
						//
						return false;
					}
				}
			}
			break;
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateContextFunctions(argument, functionStack, statement) == false) return false;
				}
				//
				validateContextFunctions(syntaxTreeNode.value.getValueAsString(), functionStack	);
				//
				break;
			}
		default:
			break;
	}
	//
	return true;
}

void MiniScript::emit(const string& condition) {
	if (VERBOSE == true) Console::println("MiniScript::emit(): '" + scriptFileName + "': " + condition);
	auto scriptIdxToStart = 0;
	for (const auto& script: scripts) {
		auto conditionMet = true;
		if (script.name.empty() == false && script.name == condition) {
			break;
		} else
		if (script.condition == condition) {
			break;
		} else {
			scriptIdxToStart++;
		}
	}
	if (scriptIdxToStart == scripts.size()) {
		scriptIdxToStart = SCRIPTIDX_NONE;
		startErrorScript();
		return;
	}
	//
	getScriptState().running = true;
	resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
}

void MiniScript::executeStateMachine() {
	while (true == true) {
		{
			auto& scriptState = getScriptState();
			// determine state machine state if it did change
			{
				if (scriptState.lastStateMachineState == nullptr || scriptState.state != scriptState.lastState) {
					scriptState.lastState = scriptState.state;
					scriptState.lastStateMachineState = nullptr;
					auto scriptStateMachineStateIt = scriptStateMachineStates.find(scriptState.state);
					if (scriptStateMachineStateIt != scriptStateMachineStates.end()) {
						scriptState.lastStateMachineState = scriptStateMachineStateIt->second;
					}
				}
			}

			// execute state machine
			if (scriptState.lastStateMachineState != nullptr) {
				if (native == true && scriptState.state == STATEMACHINESTATE_NEXT_STATEMENT) {
					// ignore STATEMACHINESTATE_NEXT_STATEMENT on native
				} else {
					scriptState.lastStateMachineState->execute();
				}
			} else {
				// we can ignore this here and break as our state machine is unset
				break;
			}
		}

		// native
		//	also do not run enabled conditions when beeing in (user script) function
		if (native == true && isFunctionRunning() == false) {
			const auto& scriptState = getScriptState();
			// check named conditions
			auto now = Time::getCurrentMillis();
			if (enabledNamedConditions.empty() == false &&
				(timeEnabledConditionsCheckLast == TIME_NONE || now >= timeEnabledConditionsCheckLast + 100LL)) {
				auto scriptIdxToStart = determineNamedScriptIdxToStart();
				if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != scriptState.scriptIdx) {
					//
					resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
				}
				timeEnabledConditionsCheckLast = now;
			}
			// stop here
			break;
		} else {
			// break if no next statement but other state machine state or not running
			const auto& scriptState = getScriptState();
			if (scriptState.state != STATEMACHINESTATE_NEXT_STATEMENT || scriptState.running == false) break;
		}
	}
}

void MiniScript::execute() {
	const auto& scriptState = getScriptState();

	//
	if (scriptState.running == false || scriptState.state == STATEMACHINESTATE_NONE) return;

	// check named conditions
	auto now = Time::getCurrentMillis();
	if (isFunctionRunning() == false &&
		enabledNamedConditions.empty() == false &&
		(timeEnabledConditionsCheckLast == TIME_NONE || now >= timeEnabledConditionsCheckLast + 100LL)) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != scriptState.scriptIdx) {
			//
			resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
		}
		timeEnabledConditionsCheckLast = now;
	}

	// execute while having statements to be processed
	executeStateMachine();
}

const string MiniScript::getNextStatement(const string& scriptCode, int& i, int& line) {
	string statementCode;
	vector<string> statementCodeLines;
	statementCodeLines.emplace_back();
	auto quote = '\0';
	auto expectBracket = false;
	auto inlineFunctionArguments = false;
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto hash = false;
	auto lc = '\0';
	for (; i < scriptCode.size(); i++) {
		auto c = scriptCode[i];
		auto nc = i + 1 < scriptCode.size()?scriptCode[i + 1]:'\0';
		// handle quotes
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				quote = '\0';
			}
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
			//
			inlineFunctionArguments = false;
		} else
		if (quote != '\0') {
			// no op
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		// brackets
		if (c == '(') {
			inlineFunctionArguments = false;
			//
			bracketCount++;
			expectBracket = false;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		if (c == ')') {
			//
			inlineFunctionArguments = false;
			//
			bracketCount--;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
			//
			inlineFunctionArguments = true;
		} else
		// square brackets
		if (c == '[') {
			//
			inlineFunctionArguments = false;
			//
			squareBracketCount++;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		if (c == ']') {
			//
			inlineFunctionArguments = false;
			//
			squareBracketCount--;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		// curly brackets
		if (c == '{') {
			//
			inlineFunctionArguments = false;
			//
			curlyBracketCount++;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		if (c == '}') {
			//
			inlineFunctionArguments = false;
			//
			curlyBracketCount--;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		// hash
		if (c == '#') {
			// hash
			hash = true;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		// new line
		if (c == '\r') {
			// ignore
		} else
		if (lc == '-' && c == '>') {
			// we expect a bracket now
			if (inlineFunctionArguments == false) expectBracket = true;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		} else
		if ((c == '\n' && ++line) || (hash == false && c == ';')) {
			// break here and process script line
			if (expectBracket == false && bracketCount == 0 && squareBracketCount == 0 && curlyBracketCount == 0) break;
			// unset hash after newline
			if (c == '\n') {
				//
				hash = false;
				//
				statementCodeLines.emplace_back();
			} else {
				//
				inlineFunctionArguments = false;
			}
		} else {
			if (Character::isSpace(c) == false && c != '-' && nc != '>') inlineFunctionArguments = false;
			// add char to script line
			statementCodeLines[statementCodeLines.size() - 1] += c;
		}
		//
		lc = c;
	}

	//
	auto lineIdx = 0;
	for (const auto& line: statementCodeLines) {
		auto trimmedLine = StringTools::trim(line);
		if (trimmedLine.empty() == true || StringTools::startsWith(trimmedLine, "#") == true) continue;
		statementCode+= trimmedLine;
		if (lineIdx != statementCodeLines.size() - 1) statementCode+= "\n";
		lineIdx++;
	}

	// add last line index
	if (i == scriptCode.size() && scriptCode[scriptCode.size() - 1] != '\n') ++line;

	//
	return statementCode;
}

bool MiniScript::parseScriptInternal(const string& scriptCode) {
	//
	auto scriptCount = scripts.size();
	auto haveScript = false;
	auto lineIdx = LINE_FIRST;
	auto currentLineIdx = 0;
	auto statementIdx = STATEMENTIDX_FIRST;
	enum GotoStatementType { GOTOSTATEMENTTYPE_FOR, GOTOSTATEMENTTYPE_IF, GOTOSTATEMENTTYPE_ELSE, GOTOSTATEMENTTYPE_ELSEIF };
	struct GotoStatementStruct {
		GotoStatementType type;
		int statementIdx;
	};
	stack<GotoStatementStruct> gotoStatementStack;
	//
	for (auto i = 0; i < scriptCode.size(); i++) {
		//
		currentLineIdx = lineIdx;

		// try to get next statement code
		auto statementCode = getNextStatement(scriptCode, i, lineIdx);

		// add last line index
		if (i == scriptCode.size() && scriptCode[scriptCode.size() - 1] != '\n') ++lineIdx;
		//
		if (statementCode.empty() == true) {
			continue;
		}

		// no script yet
		if (haveScript == false) {
			// check if we have to read additional info from code
			if (statementCode == "function:" ||
				statementCode == "on:" ||
				statementCode == "on-enabled:" ||
				statementCode == "callable:") {
				//
				i++;
				// we need the condition or name
				for (; i < scriptCode.size(); i++) {
					auto nextStatementCode = getNextStatement(scriptCode, i, lineIdx);
					if (nextStatementCode.empty() == false) {
						statementCode+= " " + nextStatementCode;
						break;
					}
				}
			}
			// check if we need to parse ":= name"
			//	applies to on: and on-enabled only
			if (StringTools::startsWith(statementCode, "on:") == true ||
				StringTools::startsWith(statementCode, "on-enabled:") == true) {
				//
				if (statementCode.rfind(":=") == string::npos) {
					//
					auto gotName = false;
					//
					auto _i = i;
					auto _lineIdx = lineIdx;
					auto _statementCode = statementCode;
					//
					auto endStack = 0;
					//
					i++;
					//
					for (; i < scriptCode.size(); i++) {
						auto nextStatementCode = getNextStatement(scriptCode, i, lineIdx);
						if (nextStatementCode.empty() == false) {
							//
							if (StringTools::startsWith(nextStatementCode, "function:") == true ||
								StringTools::startsWith(nextStatementCode, "on:") == true ||
								StringTools::startsWith(nextStatementCode, "on-enabled:") == true ||
								StringTools::startsWith(nextStatementCode, "callable:") == true) break;
							//
							statementCode+= " " + nextStatementCode;
							// break here if we got our := or reached next declaration
							auto lc = '\0';
							auto quote = '\0';
							for (auto j = 0; j < statementCode.size(); j++) {
								auto c = statementCode[j];
								// handle quotes
								if ((c == '"' || c == '\'') && lc != '\\') {
									if (quote == '\0') {
										quote = c;
									} else
									if (quote == c) {
										quote = '\0';
									}
								} else
								if (quote != '\0') {
									// no op
								} else
								if (lc == ':' && c == '=') {
									gotName = true;
									//
									break;
								}
								//
								lc = c;
							}
							//
							if (gotName == true) break;
						}
					}
					// did we got our ":= name", nope?
					if (gotName == false) {
						// reset
						i = _i;
						lineIdx = _lineIdx;
						statementCode = _statementCode;
					}
				}
				// we still need the name
				if (StringTools::endsWith(statementCode, ":=") == true) {
					//
					i++;
					//
					for (; i < scriptCode.size(); i++) {
						auto nextStatementCode = getNextStatement(scriptCode, i, lineIdx);
						if (nextStatementCode.empty() == false) {
							statementCode+= " " + nextStatementCode;
							break;
						}
					}
				}
			}
			// script type
			auto callable = false;
			auto scriptType = Script::SCRIPTTYPE_NONE;
			if (StringTools::startsWith(statementCode, "function:") == true) scriptType = Script::SCRIPTTYPE_FUNCTION; else
			if (StringTools::startsWith(statementCode, "on:") == true) scriptType = Script::SCRIPTTYPE_ON; else
			if (StringTools::startsWith(statementCode, "on-enabled:") == true) scriptType = Script::SCRIPTTYPE_ONENABLED; else
			if (StringTools::startsWith(statementCode, "callable:") == true) {
				callable = true;
				scriptType = Script::SCRIPTTYPE_FUNCTION;
			}
			// no, but did we got a new script?
			if (scriptType != Script::SCRIPTTYPE_NONE) {
				// yes
				haveScript = true;
				// functions: argument names
				vector<Script::ScriptArgument> arguments;
				// determine statement
				string statement;
				if (scriptType == Script::SCRIPTTYPE_FUNCTION) {
					statement = callable == true?
						StringTools::trim(StringTools::substring(statementCode, string("callable:").size())):
						StringTools::trim(StringTools::substring(statementCode, string("function:").size()));
				} else
				if (scriptType == Script::SCRIPTTYPE_ON)
					statement = StringTools::trim(StringTools::substring(statementCode, string("on:").size())); else
				if (scriptType == Script::SCRIPTTYPE_ONENABLED)
					statement = StringTools::trim(StringTools::substring(statementCode, string("on-enabled:").size()));
				// and name
				string name;
				auto scriptLineNameSeparatorIdx = scriptType == Script::SCRIPTTYPE_FUNCTION?statement.rfind("function:"):statement.rfind(":=");
				if (scriptLineNameSeparatorIdx != string::npos) {
					name = StringTools::trim(StringTools::substring(statement, scriptLineNameSeparatorIdx + (scriptType == Script::SCRIPTTYPE_FUNCTION?string("function").size():2)));
					statement = StringTools::trim(StringTools::substring(statement, 0, scriptLineNameSeparatorIdx));
				}
				if (scriptType == Script::SCRIPTTYPE_FUNCTION) {
					auto leftBracketIdx = statement.find('(');
					auto rightBracketIdx = statement.find(')');
					if (leftBracketIdx != string::npos || leftBracketIdx != string::npos) {
						if (leftBracketIdx == string::npos) {
							Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + "': @" + to_string(currentLineIdx) + ": 'function:': unbalanced bracket count");
							//
							parseErrors.push_back(to_string(currentLineIdx) + ": 'function:': unbalanced bracket count");
							//
							scriptValid = false;
						} else
						if (rightBracketIdx == string::npos) {
							Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + "': @" + to_string(currentLineIdx) + ": 'function:': unbalanced bracket count");
							//
							parseErrors.push_back(to_string(currentLineIdx) + ": 'function:': unbalanced bracket count");
							//
							scriptValid = false;
						} else {
							auto argumentNamesString = StringTools::trim(StringTools::substring(statement, leftBracketIdx + 1, rightBracketIdx));
							auto argumentNamesTokenized = StringTools::tokenize(argumentNamesString, ",");
							statement = StringTools::substring(statement, 0, leftBracketIdx);
							for (const auto& argumentName: argumentNamesTokenized) {
								auto argumentNameTrimmed = StringTools::trim(argumentName);
								auto reference = false;
								if (StringTools::startsWith(argumentNameTrimmed, "=") == true) {
									reference = true;
									argumentNameTrimmed = StringTools::trim(StringTools::substring(argumentNameTrimmed, 1));
								}
								if (StringTools::regexMatch(argumentNameTrimmed, "\\$[a-zA-Z0-9]+") == true) {
									arguments.emplace_back(
										argumentNameTrimmed,
										reference
									);
								} else {
									Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + "': @" + to_string(currentLineIdx) + ": 'function:': invalid argument name: '" + argumentNameTrimmed + "'");
									//
									parseErrors.push_back(to_string(currentLineIdx) + ": 'function:': invalid argument name: '" + argumentNameTrimmed + "'");
									//
									scriptValid = false;
								}
							}
						}

					}
				}
				auto trimmedStatement = StringTools::trim(statement);
				ScriptStatement scriptStatement(
					currentLineIdx,
					STATEMENTIDX_FIRST,
					"internal.script.evaluate(" + StringTools::replace(StringTools::replace(trimmedStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
					"internal.script.evaluate(" + StringTools::replace(StringTools::replace(trimmedStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
					STATEMENTIDX_NONE
				);
				auto conditionOrNameExecutable = doStatementPreProcessing(trimmedStatement, scriptStatement);
				auto conditionOrName = trimmedStatement;
				auto emitCondition = StringTools::regexMatch(conditionOrName, "[a-zA-Z0-9_]+");
				statementIdx = STATEMENTIDX_FIRST;
				// add to user functions
				if (scriptType == Script::SCRIPTTYPE_FUNCTION) {
					scriptFunctions[conditionOrName] = scripts.size();
				}

				// push to scripts
				scripts.emplace_back(
					scriptType,
					currentLineIdx,
					conditionOrName,
					conditionOrNameExecutable,
					ScriptStatement(currentLineIdx, statementIdx, conditionOrName, conditionOrNameExecutable, STATEMENTIDX_NONE),
					ScriptSyntaxTreeNode(),
					name,
					emitCondition,
					initializer_list<ScriptStatement>{},
					initializer_list<ScriptSyntaxTreeNode>{},
					callable,
					arguments
				);
			} else {
				Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + "': @" + to_string(currentLineIdx) + ": expecting 'on:', 'on-enabled:', 'on-function:' script condition");
				//
				parseErrors.push_back(to_string(currentLineIdx) + ": expecting 'on:', 'on-enabled:', 'on-function:' script condition");
				//
				scriptValid = false;
			}
		} else {
			if (StringTools::startsWith(statementCode, "function:") == true ||
				StringTools::startsWith(statementCode, "on:") == true ||
				StringTools::startsWith(statementCode, "on-enabled:") == true ||
				StringTools::startsWith(statementCode, "callable:") == true
			) {
				Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + "': @" + to_string(currentLineIdx) + ": unbalanced forXXX/if/elseif/else/end");
				//
				parseErrors.push_back(to_string(currentLineIdx) + ": unbalanced forXXX/if/elseif/else/end");
				//
				scriptValid = false;
			} else
			if (statementCode == "end") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_FOR:
							{
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, gotoStatementStackElement.statementIdx);
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
							}
							break;
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSE:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
							}
							break;
					}
				} else{
					scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
					haveScript = false;
				}
			} else
			if (statementCode == "else") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, statementCode, STATEMENTIDX_NONE);
							}
							break;
						default:
							Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + ": @" + to_string(currentLineIdx) + ": else without if/elseif");
							//
							parseErrors.push_back(to_string(currentLineIdx) + ": else without if/elseif");
							//
							scriptValid = false;
							break;
					}
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_ELSE,
							.statementIdx = statementIdx
						}
					);
				} else {
					Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + ": @" + to_string(currentLineIdx) + ": else without if");
					//
					parseErrors.push_back(to_string(currentLineIdx) + ": else without if");
					//
					scriptValid = false;
				}
			} else
			if (StringTools::regexMatch(statementCode, "^elseif[\\s]*\\(.*\\)$") == true) {
				ScriptStatement scriptStatement(
					currentLineIdx,
					STATEMENTIDX_FIRST,
					StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
					StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
					STATEMENTIDX_NONE
				);
				auto executableStatement = doStatementPreProcessing(statementCode, scriptStatement);
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, executableStatement, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, executableStatement, STATEMENTIDX_NONE);
							}
							break;
						default:
							Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + ": @" + to_string(currentLineIdx) + ": elseif without if");
							scriptValid = false;
							break;
					}
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_ELSEIF,
							.statementIdx = statementIdx
						}
					);
				} else {
					Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + ": @" + to_string(currentLineIdx) + ": elseif without if");
					//
					parseErrors.push_back(to_string(currentLineIdx) + ": elseif without if");
					//
					scriptValid = false;
				}
			} else {
				ScriptStatement scriptStatement(
					currentLineIdx,
					STATEMENTIDX_FIRST,
					StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
					StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
					STATEMENTIDX_NONE
				);
				auto executableStatement = doStatementPreProcessing(statementCode, scriptStatement);
				if (StringTools::regexMatch(executableStatement, "^forTime[\\s]*\\(.*\\)$") == true ||
					StringTools::regexMatch(executableStatement, "^forCondition[\\s]*\\(.*\\)$") == true) {
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_FOR,
							.statementIdx = statementIdx
						}
					);
				} else
				if (StringTools::regexMatch(executableStatement, "^if[\\s]*\\(.*\\)$") == true) {
					gotoStatementStack.push(
						{
							.type = GOTOSTATEMENTTYPE_IF,
							.statementIdx = statementIdx
						}
					);
				}
				scripts[scripts.size() - 1].statements.emplace_back(currentLineIdx, statementIdx, statementCode, executableStatement, STATEMENTIDX_NONE);
			}
			statementIdx++;
		}
	}

	// check for unbalanced forXXX/if/elseif/else/end
	if (scriptValid == true && gotoStatementStack.empty() == false) {
		Console::println("MiniScript::parseScriptInternal(): '" + scriptFileName + ": unbalanced forXXX/if/elseif/else/end");
		//
		parseErrors.push_back("Unbalanced forXXX/if/elseif/else/end");
		//
		scriptValid = false;
		//
		return false;
	}

	// create syntax tree
	for (auto i = scriptCount; i < scripts.size(); i++) {
		auto& script = scripts[i];
		// create syntax tree of executable condition if we have any
		if (script.emitCondition == false && script.executableCondition.empty() == false) {
			string_view method;
			vector<string_view> arguments;
			string accessObjectMemberStatement;
			if (parseScriptStatement(script.executableCondition, method, arguments, script.conditionStatement, accessObjectMemberStatement) == false) {
				//
				scriptValid = false;
			} else
			if (createScriptStatementSyntaxTree(method, arguments, script.conditionStatement, script.conditionSyntaxTree) == false) {
				//
				scriptValid = false;
			}
		}
		// create script syntax tree
		for (auto statementIdx = STATEMENTIDX_FIRST; statementIdx < script.statements.size(); statementIdx++) {
			const auto& statement = script.statements[statementIdx];
			script.syntaxTree.emplace_back();
			auto& syntaxTree = script.syntaxTree[script.syntaxTree.size() - 1];
			string_view methodName;
			vector<string_view> arguments;
			string accessObjectMemberStatement;
			if (parseScriptStatement(statement.executableStatement, methodName, arguments, statement, accessObjectMemberStatement) == false) {
				//
				scriptValid = false;
			} else
			if (createScriptStatementSyntaxTree(methodName, arguments, statement, syntaxTree) == false) {
				//
				scriptValid = false;
			}
		}
	}

	//
	return scriptValid;
}

void MiniScript::parseScript(const string& pathName, const string& fileName) {
	//
	scriptValid = true;
	scriptPathName = pathName;
	scriptFileName = fileName;

	//
	for (const auto& [scriptMethodId, scriptMethod]: scriptMethods) delete scriptMethod;
	for (const auto& [scriptStateMachineStateId, scriptStateMachineState]: scriptStateMachineStates) delete scriptStateMachineState;
	scriptMethods.clear();
	scriptStateMachineStates.clear();
	while (scriptStateStack.empty() == false) popScriptState();

	// shutdown script state
	pushScriptState();
	resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_WAIT_FOR_CONDITION);

	//
	registerVariables();

	//
	string scriptCode;
	try {
		scriptCode = FileSystem::getInstance()->getContentAsString(pathName, fileName);
	} catch (FileSystemException& fse)	{
		Console::println("MiniScript::parseScript(): " + pathName + "/" + fileName + ": an error occurred: " + fse.what());
		//
		scriptValid = true;
		//
		parseErrors.push_back("An error occurred: " + string(fse.what()));
		//
		return;
	}

	//
	{
		auto scriptHash = SHA256::encode(scriptCode);
		if (native == true) {
			if (scriptHash == nativeHash) {
				scripts = nativeScripts;
				registerStateMachineStates();
				registerMethods();
				startScript();
				return;
			} else {
				Console::println("MiniScript::parseScript(): " + pathName + "/" + fileName + ": Script has changed. Script will be run in interpreted mode. Retranspile and recompile your script if you want to run it natively.");
				native = false;
			}
		}
		nativeHash = scriptHash;
	}

	//
	registerStateMachineStates();
	registerMethods();

	//
	if (parseScriptInternal(scriptCode) == false) return;

	// validate method call context functions
	for (const auto& script: scripts) {
		//
		if (script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION) {
			//
			if (script.callable == true) {
				//
				if (validateCallable(script.condition) == false) {
					//
					scriptValid = false;
					//
					break;
				}
			} else {
				//
				vector<string> functionStack;
				//
				if (validateContextFunctions(script.condition, functionStack) == false) {
					//
					scriptValid = false;
					//
					break;
				}
			}
		}
	}

	// check for initialize and error condition
	auto haveErrorScript = false;
	for (const auto& script: scripts) {
		if (script.scriptType == Script::SCRIPTTYPE_ONENABLED) {
			// no op
		} else
		if (script.condition == "error") {
			haveErrorScript = true;
		}
	}
	if (haveErrorScript == false) {
		Console::println("MiniScript::parseScript(): '" + scriptFileName + ": script needs to define an error condition");
		//
		parseErrors.push_back("Script needs to define an error condition");
		//
		scriptValid = false;
		//
		return;

	}

	// parse deferred function script codes,
	//	which are created by parsing map initializers and possible map inline functions
	do {
		auto deferredFunctionScriptCodesCopy = deferredFunctionScriptCodes;
		deferredFunctionScriptCodes.clear();
		for (const auto& functionScriptCode: deferredFunctionScriptCodesCopy) {
			parseScriptInternal(functionScriptCode);
		}
	} while (deferredFunctionScriptCodes.empty() == false);

	//
	startScript();
}

void MiniScript::startScript() {
	if (VERBOSE == true) Console::println("MiniScript::startScript(): '" + scriptFileName + ": starting script.");
	if (scriptValid == false) {
		Console::println("MiniScript::startScript(): '" + scriptFileName + "': script not valid: not starting");
		return;
	}
	auto& scriptState = getScriptState();
	for (const auto& [variableName, variable]: scriptState.variables) delete variable;
	scriptState.variables.clear();
	scriptState.running = true;
	registerVariables();
	//
	if (hasCondition("initialze") == true) emit("initialize");
}

int MiniScript::determineScriptIdxToStart() {
	if (VERBOSE == true) Console::println("MiniScript::determineScriptIdxToStart()");
	auto nothingScriptIdx = SCRIPTIDX_NONE;
	auto scriptIdx = 0;
	for (const auto& script: scripts) {
		if (script.scriptType != Script::SCRIPTTYPE_ON) {
			// no op
		} else
		if (script.emitCondition == true && script.condition == "nothing") {
			nothingScriptIdx = scriptIdx;
			// no op
		} else
		if (script.emitCondition == true) {
			// emit condition
		} else {
			auto conditionMet = true;
			auto returnValue = ScriptVariable();
			if (evaluateInternal(script.condition, script.executableCondition, returnValue) == true) {
				auto returnValueBoolValue = false;
				if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
					Console::println("MiniScript::determineScriptIdxToStart(): '" + script.condition + "': expecting boolean return value, but got: " + returnValue.getAsString());
					conditionMet = false;
				} else
				if (returnValueBoolValue == false) {
					conditionMet = false;
				}
			} else {
				Console::println("MiniScript::determineScriptIdxToStart(): '" + scriptFileName + "': @" + to_string(script.line) + ": '" + script.condition + "': parse error");
			}
			if (conditionMet == false) {
				if (VERBOSE == true) {
					Console::print("MiniScript::determineScriptIdxToStart(): " + script.condition + ": FAILED");
				}	
			} else {
				if (VERBOSE == true) {
					Console::print("MiniScript::determineScriptIdxToStart(): " + script.condition + ": OK");
				}
				return scriptIdx;
			}
		}
		scriptIdx++;
	}
	return nothingScriptIdx;
}

int MiniScript::determineNamedScriptIdxToStart() {
	if (VERBOSE == true) Console::println("MiniScript::determineNamedScriptIdxToStart()");
	// TODO: we could have a hash map here to speed up enabledConditionName -> script lookup
	const auto& scriptState = getScriptState();
	for (const auto& enabledConditionName: enabledNamedConditions) {
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			if (script.scriptType != Script::SCRIPTTYPE_ONENABLED ||
				script.name != enabledConditionName) {
				// no op
			} else {
				auto conditionMet = true;
				ScriptVariable returnValue;
				if (evaluateInternal(script.condition, script.executableCondition, returnValue) == true) {
					auto returnValueBoolValue = false;
					if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
						Console::println("MiniScript::determineNamedScriptIdxToStart(): '" + script.condition + "': expecting boolean return value, but got: " + returnValue.getAsString());
						conditionMet = false;
					} else
					if (returnValueBoolValue == false) {
						conditionMet = false;
					}
				} else {
					Console::println("MiniScript::determineNamedScriptIdxToStart(): '" + scriptFileName + "': @" + to_string(script.line) + ": '" + script.condition + "': parse error");
				}
				if (conditionMet == false) {
					if (VERBOSE == true) {
						Console::print("MiniScript::determineNamedScriptIdxToStart(): " + script.condition + ": FAILED");
					}
				} else {
					if (VERBOSE == true) {
						Console::print("MiniScript::determineNamedScriptIdxToStart(): " + script.condition + ": OK");
					}
					return scriptIdx;
				}
			}
			scriptIdx++;
		}
	}
	return SCRIPTIDX_NONE;
}

bool MiniScript::getNextStatementOperator(const string& processedStatement, MiniScript::ScriptStatementOperator& nextOperator, const ScriptStatement& statement) {
	//
	auto curlyBracketCount = 0;
	auto bracketCount = 0;
	auto quote = '\0';
	auto lc = '\0';
	for (auto i = 0; i < processedStatement.size(); i++) {
		auto c = processedStatement[i];
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				quote = '\0';
			}
		} else
		if (quote == '\0') {
			if (c == '(') {
				bracketCount++;
			} else
			if (c == ')') {
				bracketCount--;
			} else
			if (c == '{') {
				curlyBracketCount++;
			} else
			if (c == '}') {
				curlyBracketCount--;
			} else
			if (curlyBracketCount == 0) {
				for (int j = OPERATOR_NONE + 1; j < OPERATOR_MAX; j++) {
					auto priorizedOperator = static_cast<ScriptOperator>(j);
					string operatorCandidate;
					auto operatorString = getOperatorAsString(priorizedOperator);
					if (operatorString.size() == 1) operatorCandidate+= processedStatement[i];
					if (operatorString.size() == 2 && i + 1 < processedStatement.size()) {
						operatorCandidate+= processedStatement[i];
						operatorCandidate+= processedStatement[i + 1];
					}
					if (operatorString == operatorCandidate && (nextOperator.idx == OPERATORIDX_NONE || priorizedOperator > nextOperator.scriptOperator)) {
						if (i > 0 && isOperatorChar(processedStatement[i - 1]) == true) {
							continue;
						}
						if (operatorString.size() == 2 && i + 2 < processedStatement.size() && isOperatorChar(processedStatement[i + 2]) == true) {
							continue;
						} else
						if (operatorString.size() == 1 && i + 1 < processedStatement.size() && isOperatorChar(processedStatement[i + 1]) == true) {
							continue;
						}
						if (priorizedOperator == OPERATOR_SUBTRACTION) {
							string leftArgumentBrackets;
							auto leftArgumentLeft = 0;
							auto leftArgument = findLeftArgument(processedStatement, i - 1, leftArgumentLeft, leftArgumentBrackets);
							if (leftArgument.length() == 0) continue;
						}
						nextOperator.idx = i;
						nextOperator.scriptOperator = priorizedOperator;
					}
				}
			}
		}
		lc = c;
	}

	//
	if (bracketCount > 0) {
		Console::println(getStatementInformation(statement) + ": unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(getStatementInformation(statement) + ": unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}
	//
	return nextOperator.idx != OPERATORIDX_NONE;
}

inline const string MiniScript::trimArgument(const string& argument) {
	auto processedArgument = StringTools::trim(argument);
	if (StringTools::startsWith(processedArgument, "(") == true && StringTools::endsWith(processedArgument, ")") == true) {
		processedArgument = StringTools::substring(processedArgument, 1, processedArgument.size() - 1);
	}
	return processedArgument;
}

inline const string MiniScript::findRightArgument(const string& statement, int position, int& length, string& brackets) {
	//
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto quote = '\0';
	auto lc = '\0';
	string argument;
	length = 0;
	for (auto i = position; i < statement.size(); i++) {
		auto c = statement[i];
		// quote?
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				quote = '\0';
			}
			argument+= c;
		} else
		// no quote
		if (quote == '\0') {
			if (c == '(') {
				bracketCount++;
				argument+= c;
			} else
			if (c == '[') {
				squareBracketCount++;
				argument+= c;
			} else
			if (c == '{') {
				curlyBracketCount++;
				argument+= c;
			} else
			if (c == ')') {
				bracketCount--;
				if (bracketCount < 0) {
					brackets = "()";
					return trimArgument(argument);
				}
				argument+= c;
			} else
			if (c == ']') {
				squareBracketCount--;
				// array initializer?
				if (StringTools::startsWith(argument, "[") == false) {
					// no
					if (squareBracketCount < 0) {
						brackets = "[]";
						return trimArgument(argument);
					}
				}
				argument+= c;
			} else
			if (c == '}') {
				curlyBracketCount--;
				if (curlyBracketCount < 0) {
					brackets = "{}";
					return trimArgument(argument);
				}
				argument+= c;
			} else
			if (squareBracketCount == 0 && curlyBracketCount == 0 && c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				//
				if (argument.empty() == true && (c == ' ' || c == '\t' || c == '\n')) {
					// no op
				} else {
					argument+= c;
				}
			} else {
				//
				if (argument.empty() == true && (c == ' ' || c == '\t' || c == '\n')) {
					// no op
				} else {
					argument+= c;
				}
			}
		} else
		if (quote != '\0') {
			argument+= c;
		}
		length++;
		//
		lc = c;
	}
	//
	return trimArgument(argument);
}

inline const string MiniScript::findLeftArgument(const string& statement, int position, int& length, string& brackets) {
	// adapt code similar to findRightArguument related to array and map/initializer
	//
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto quote = '\0';
	auto lc = '\0';
	string argument;
	length = 0;
	for (int i = position; i >= 0; i--) {
		auto c = statement[i];
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				quote = '\0';
			}
			argument = c + argument;
		} else
		if (quote == '\0') {
			if (c == ')') {
				bracketCount++;
				argument = c + argument;
			} else
			if (c == ']') {
				squareBracketCount++;
				argument = c + argument;
			} else
			if (c == '}') {
				curlyBracketCount++;
				argument = c + argument;
			} else
			if (c == '(') {
				bracketCount--;
				if (bracketCount < 0) {
					brackets = "()";
					return trimArgument(argument);
				}
				argument = c + argument;
			} else
			if (c == ':' &&
				bracketCount == 0 &&
				squareBracketCount == 0 &&
				curlyBracketCount == 0) {
				//
				brackets = "";
				return trimArgument(argument);
			} else
			if (c == '[') {
				squareBracketCount--;
				if (squareBracketCount < 0) {
					brackets = "[]";
					return trimArgument(argument);
				}
				argument = c + argument;
			} else
			if (c == '{') {
				curlyBracketCount--;
				if (curlyBracketCount < 0) {
					brackets = "{}";
					return trimArgument(argument);
				}
				argument = c + argument;
			} else
			if (squareBracketCount == 0 && curlyBracketCount == 0 && c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				argument = c + argument;
			} else {
				argument = c + argument;
			}
		} else
		if (quote != '\0') {
			argument = c + argument;
		}
		length++;
		//
		lc = c;
	}
	return trimArgument(argument);
}

const string MiniScript::doStatementPreProcessing(const string& processedStatement, const ScriptStatement& statement) {
	auto preprocessedStatement = processedStatement;
	//
	ScriptStatementOperator nextOperators;
	while (getNextStatementOperator(preprocessedStatement, nextOperators, statement) == true) {
		auto methodIt = scriptOperators.find(nextOperators.scriptOperator);
		if (methodIt == scriptOperators.end()) {
			Console::println(getStatementInformation(statement) + ": " + processedStatement + ": operator found in: '" + preprocessedStatement + "'@" + to_string(nextOperators.idx) + ": no method found");
			// TODO: error handling
			return preprocessedStatement;
		}
		auto method = methodIt->second;
		if (method->isVariadic() == false &&
			method->getArgumentTypes().size() == 1) {
			// find the single argument right
			auto operatorString = getOperatorAsString(nextOperators.scriptOperator);
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperators.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperators.idx) +
				method->getMethodName() + "(" + rightArgument + ")" +
				StringTools::substring(preprocessedStatement, nextOperators.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
		} else
		if (method->isVariadic() == true ||
			method->getArgumentTypes().size() == 2) {
			auto operatorString = getOperatorAsString(nextOperators.scriptOperator);
			// find the first argument left
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperators.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find the first argument right
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperators.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			//
			if (leftArgumentBrackets.empty() == false && rightArgumentBrackets.empty() == false && leftArgumentBrackets != rightArgumentBrackets) {
				Console::println(getStatementInformation(statement) + ": " + processedStatement + ": operator found in: '" + preprocessedStatement + "'@" + to_string(nextOperators.idx) + ": unbalanced bracket usage");
				return preprocessedStatement;
			}
			//
			if (nextOperators.scriptOperator == OPERATOR_SET) {
				leftArgument = "\"" + doStatementPreProcessing(leftArgument, statement) + "\"";
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperators.idx - leftArgumentLength) +
				method->getMethodName() + "(" + leftArgument + ", " + rightArgument + ")" +
				StringTools::substring(preprocessedStatement, nextOperators.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
		}
		nextOperators = ScriptStatementOperator();
	}
	//
	return preprocessedStatement;
}

bool MiniScript::getObjectMemberAccess(const string_view& executableStatement, string_view& object, string_view& method, const ScriptStatement& statement) {
	//
	auto objectMemberAccess = false;
	auto objectStartIdx = string::npos;
	auto objectEndIdx = string::npos;
	auto memberCallStartIdx = string::npos;
	auto memberCallEndIdx = string::npos;
	//
	auto quote = '\0';
	auto lc = '\0';
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	for (auto i = 0; i < executableStatement.size(); i++) {
		auto c = executableStatement[i];
		// handle quotes
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				quote = '\0';
			}
		} else
		if (quote != '\0') {
			// no op
		} else
		if (c == '(') {
			bracketCount++;
		} else
		if (c == ')') {
			bracketCount--;
		} else
		if (c == '[') {
			squareBracketCount++;
		} else
		if (c == ']') {
			squareBracketCount--;
		} else
		if (c == '{') {
			curlyBracketCount++;
		} else
		if (c == '}') {
			curlyBracketCount--;
		} else
		if (lc == '-' && c == '>' &&
			bracketCount == 0 &&
			squareBracketCount == 0 &&
			curlyBracketCount == 0) {
			//
			objectStartIdx = 0;
			objectEndIdx = i - 1;
			memberCallStartIdx = i + 1;
			memberCallEndIdx = executableStatement.size();
			//
			object = string_view(&executableStatement[objectStartIdx], objectEndIdx - objectStartIdx);
			method = string_view(&executableStatement[memberCallStartIdx], memberCallEndIdx - memberCallStartIdx);
			//
			objectMemberAccess = true;
			// dont break here, we can have multiple member access operators here, but we want the last one in this step
		}
		//
		lc = c;
	}

	//
	return objectMemberAccess;
}

bool MiniScript::call(int scriptIdx, span<ScriptVariable>& argumentValues, ScriptVariable& returnValue) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::println("MiniScript::call(): invalid script index: " + to_string(scriptIdx));
		return false;
	}
	// push a new script state
	pushScriptState();
	// script state vector could get modified, so
	{
		auto& scriptState = getScriptState();
		// also put named arguments into state context variables
		auto argumentIdx = 0;
		for (const auto& argument: scripts[scriptIdx].arguments) {
			if (argumentIdx == argumentValues.size()) {
				break;
			}
			setVariable(argument.name, argumentValues[argumentIdx], nullptr, argument.reference);
			argumentIdx++;
		}
	}
	//
	resetScriptExecutationState(scriptIdx, STATEMACHINESTATE_NEXT_STATEMENT);
	// script state vector could get modified, so
	{
		auto& scriptState = getScriptState();
		// run this function dude
		scriptState.running = true;
	}
	// execute
	for (;true;) {
		execute();
		// run this function dude
		if (getScriptState().running == false) break;
	}
	// get return value
	{
		const auto& scriptState = getScriptState();
		// run this function dude
		returnValue = scriptState.returnValue;
	}
	// done, pop the function script state
	popScriptState();
	//
	return true;
}

const vector<MiniScript::ScriptMethod*> MiniScript::getMethods() {
	vector<ScriptMethod*> methods;
	for (const auto& [scriptMethodName, scriptMethod]: scriptMethods) {
		if (scriptMethod->isPrivate() == true) continue;
		methods.push_back(scriptMethod);
	}
	//
	struct {
		bool operator()(ScriptMethod* a, ScriptMethod* b) const {
			auto aPrefix = StringTools::substring(a->getMethodName(), 0, StringTools::lastIndexOf(a->getMethodName(), ".") + 1);
			auto aName = StringTools::substring(a->getMethodName(), StringTools::lastIndexOf(a->getMethodName(), ".") + 1);
			auto bPrefix = StringTools::substring(b->getMethodName(), 0, StringTools::lastIndexOf(b->getMethodName(), ".") + 1);
			auto bName = StringTools::substring(b->getMethodName(), StringTools::lastIndexOf(b->getMethodName(), ".") + 1);
			array<string, 6> prefixes {
				"is",
				"has",
				"get",
				"set",
				"unset",
				"compute"
			};
			array<string, 6> sortPrefixes {
				"0",
				"1",
				"2",
				"3",
				"4",
				"5"
			};
			int aPrefixIdx = 0;
			for (const auto& prefix: prefixes) {
				if ((aName != prefix || aPrefix.empty() == false) && StringTools::startsWith(aName, prefix) == true) {
					aName = StringTools::substring(aName, prefix.size());
					break;
				}
				aPrefixIdx++;
			}
			int bPrefixIdx = 0;
			for (const auto& prefix: prefixes) {
				if ((bName != prefix || bPrefix.empty() == false) && StringTools::startsWith(bName, prefix) == true) {
					bName = StringTools::substring(bName, prefix.size());
					break;
				}
				bPrefixIdx++;
			}
			if (aName == bName) {
				return aPrefix + (aPrefixIdx < 6?sortPrefixes[aPrefixIdx]:"") + aName < bPrefix + (bPrefixIdx < 6?sortPrefixes[bPrefixIdx]:"") + bName;
			} else {
				return aPrefix + aName < bPrefix + bName;
			}
		}
	} sortFunction;
	//
	sort(methods.begin(), methods.end(), sortFunction);
	//
	return methods;
}

const vector<MiniScript::ScriptMethod*> MiniScript::getOperatorMethods() {
	vector<ScriptMethod*> methods;
	for (const auto& [scriptOperatorId, scriptMethod]: scriptOperators) {
		methods.push_back(scriptMethod);
	}
	return methods;
}

const string MiniScript::getScriptInformation(int scriptIdx, bool includeStatements) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::println("MiniScript::getScriptInformation(): invalid script index: " + to_string(scriptIdx));
		return string();
	}
	const auto& script = scripts[scriptIdx];
	string result;
	string argumentsString;
	switch(script.scriptType) {
		case Script::SCRIPTTYPE_FUNCTION: {
			for (const auto& argument: script.arguments) {
				if (argumentsString.empty() == false) argumentsString+= ", ";
				if (argument.reference == true) argumentsString+= "=";
				argumentsString+= argument.name;
			}
			argumentsString = "(" + argumentsString + ")";
			result+= "function: "; break;
		}
		case Script::SCRIPTTYPE_ON: result+= "on: "; break;
		case Script::SCRIPTTYPE_ONENABLED: result+= "on-enabled: "; break;
	}
	if (script.condition.empty() == false)
		result+= script.condition + argumentsString + "; ";
	if (script.name.empty() == false) {
		result+= "name = '" + script.name + argumentsString + "';\n";
	} else {
		result+= "\n";
	}
	if (includeStatements == true) {
		for (const auto& scriptStatement: script.statements) {
			result+= "\t" + to_string(scriptStatement.statementIdx) + ": " + StringTools::replace(scriptStatement.executableStatement, "\n", "\n\t\t") + (scriptStatement.gotoStatementIdx != STATEMENTIDX_NONE?" (gotoStatement " + to_string(scriptStatement.gotoStatementIdx) + ")":"") + "\n";
		}
		result+= "\n";
	}
	//
	return result;
}

const string MiniScript::getInformation() {
	string result;
	result+= "Script: " + scriptPathName + "/" + scriptFileName + " (runs " + (native == true?"natively":"interpreted") + ")" + "\n\n";
	auto scriptIdx = 0;
	for (const auto& script: scripts) {
		result+= getScriptInformation(scriptIdx);
		scriptIdx++;
	}

	//
	result+="State Machine States:\n";
	{
		vector<string> states;
		for (const auto& [scriptStateMachineStateId, scriptStateMachineState]: scriptStateMachineStates) {
			string state;
			state = scriptStateMachineState->getName() + "(" + to_string(scriptStateMachineState->getId()) + ")";
			states.push_back(state);
		}
		sort(states.begin(), states.end());
		for (const auto& state: states) result+= state+ "\n";
	}
	result+= "\n";

	//
	if (native == false) {
		//
		result+= "Methods:\n";
		{
			vector<string> methods;
			for (const auto& [scriptMethodName, scriptMethod]: scriptMethods) {
				if (scriptMethod->isPrivate() == true) continue;
				string method;
				method+= scriptMethod->getMethodName();
				method+= "(";
				method+= scriptMethod->getArgumentsInformation();
				method+= "): ";
				method+= ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
				methods.push_back(method);
			}
			sort(methods.begin(), methods.end());
			for (const auto& method: methods) result+= method + "\n";
		}
		result+= "\n";

		//
		result+= "Operators:\n";
		{
			vector<string> operators;
			for (const auto& [scriptOperatorId, scriptMethod]: scriptOperators) {
				string operatorString;
				operatorString+= getOperatorAsString(scriptMethod->getOperator());
				operatorString+= " --> ";
				operatorString+= scriptMethod->getMethodName();
				operatorString+= "(";
				operatorString+= scriptMethod->getArgumentsInformation();
				operatorString+= "): ";
				operatorString+= ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
				operators.push_back(operatorString);
			}
			sort(operators.begin(), operators.end());
			for (const auto& method: operators) result+= method + "\n";
		}
		result+= "\n";
	} else {
		result+= "Methods:\n\trunning natively\n\n";
		result+= "Operators:\n\trunning natively\n\n";
	}

	//
	result+= "Variables:\n";
	{
		const auto& scriptState = getScriptState();
		vector<string> variables;
		for (const auto& [scriptVariableName, scriptVariableValue]: scriptState.variables) {
			string variable;
			variable+= scriptVariableName + " = " + scriptVariableValue->getAsString();
			variables.push_back(variable);
		}
		sort(variables.begin(), variables.end());
		for (const auto& variable: variables) result+= variable + "\n";
	}

	//
	return result;
}

void MiniScript::registerStateMachineStates() {
	// base
	if (native == false) {
		//
		class ScriptStateNextStatement: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateNextStatement(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATEMACHINESTATE_NEXT_STATEMENT";
			}
			virtual int getId() override {
				return STATEMACHINESTATE_NEXT_STATEMENT;
			}
			virtual void execute() override {
				if (miniScript->getScriptState().statementIdx == STATEMENTIDX_NONE) {
					miniScript->enabledNamedConditions.clear();
					miniScript->timeEnabledConditionsCheckLast = TIME_NONE;
					miniScript->setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
					return;
				}
				if (miniScript->native == false) miniScript->executeScriptLine();
			}
		};
		registerStateMachineState(new ScriptStateNextStatement(this));
	}
	{
		//
		class ScriptStateWait: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateWait(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATEMACHINESTATE_WAIT";
			}
			virtual int getId() override {
				return STATEMACHINESTATE_WAIT;
			}
			virtual void execute() override {
				auto now = Time::getCurrentMillis();
				if (now > miniScript->getScriptState().timeWaitStarted + miniScript->getScriptState().timeWaitTime) {
					miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				}
			}
		};
		registerStateMachineState(new ScriptStateWait(this));
	}
	{
		//
		class ScriptStateWaitForCondition: public ScriptStateMachineState {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptStateWaitForCondition(MiniScript* miniScript): ScriptStateMachineState(), miniScript(miniScript) {}
			virtual const string getName() override {
				return "STATEMACHINESTATE_WAIT_FOR_CONDITION";
			}
			virtual int getId() override {
				return STATEMACHINESTATE_WAIT_FOR_CONDITION;
			}
			virtual void execute() override {
				auto now = Time::getCurrentMillis();
				if (now < miniScript->getScriptState().timeWaitStarted + miniScript->getScriptState().timeWaitTime) {
					return;
				}
				auto scriptIdxToStart = miniScript->determineScriptIdxToStart();
				if (scriptIdxToStart == SCRIPTIDX_NONE) {
					miniScript->getScriptState().timeWaitStarted = now;
					miniScript->getScriptState().timeWaitTime = 100LL;
					return;
				}
				miniScript->resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
			}
		};
		registerStateMachineState(new ScriptStateWaitForCondition(this));
	}
}

void MiniScript::registerMethods() {
	// unregister old registered methods
	for (const auto& [scriptMethodId, scriptMethod]: scriptMethods) delete scriptMethod;
	scriptMethods.clear();
	// script intern base methods
	{
		//
		class ScriptMethodInternalScriptEvaluate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodInternalScriptEvaluate(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "internal.script.evaluate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 1) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (argumentValues.size() == 1) {
					returnValue = argumentValues[0];
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodInternalScriptEvaluate(this));
	}
	{
		//
		class ScriptMethodInternalEvaluateMemberAccess: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodInternalEvaluateMemberAccess(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = true },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "this", .optional = false, .reference = false, .nullable = true },
						{.type = ScriptVariableType::TYPE_STRING, .name = "member", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_PSEUDO_MIXED,
					true
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "internal.script.evaluateMemberAccess";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				// Current layout:
				//	0: variable name of object, 1: variable content of object
				//	2: object method to call
				//	3: variable name of argument 0; 4: variable content of argument 0
				//	5: variable name of argument 1; 6: variable content of argument 1
				//	..
				//
				string variable;
				string member;
				//
				if (argumentValues.size() < 3 ||
					miniScript->getStringValue(argumentValues, 2, member, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					// do we have a this variable name?
					{
						string thisVariableName;
						if (argumentValues[0].getType() != MiniScript::TYPE_NULL && argumentValues[0].getStringValue(thisVariableName) == true) {
							// yep, looks like that, we always use a reference here
							argumentValues[1] = miniScript->getVariable(thisVariableName, &statement, true);
						}
					}
					// check if map, if so fetch function assignment of member property
					auto functionIdx = MiniScript::SCRIPTIDX_NONE;
					if (argumentValues[1].getType() == TYPE_MAP) {
						string function;
						auto mapValue = argumentValues[1].getMapEntry(member);
						if (mapValue.getType() == MiniScript::TYPE_FUNCTION_ASSIGNMENT && mapValue.getStringValue(function) == true) {
							functionIdx = miniScript->getFunctionScriptIdx(function);
						}
					}
					//
					const auto& className = ScriptVariable::getClassName(argumentValues[1].getType());
					//
					if (className.empty() == false || functionIdx != MiniScript::SCRIPTIDX_NONE) {
						//
						ScriptMethod* method { nullptr };
						if (functionIdx == MiniScript::SCRIPTIDX_NONE) {
							#if defined(__MINISCRIPT_TRANSPILATION__)
								method = evaluateMemberAccessArrays[static_cast<int>(argumentValues[1].getType()) - static_cast<int>(MiniScript::TYPE_STRING)][EVALUATEMEMBERACCESS_MEMBER];
							#else
								method = miniScript->getMethod(className + "." + member);
							#endif
						}
						if (method != nullptr || functionIdx != MiniScript::SCRIPTIDX_NONE) {
							// create method call arguments
							vector<ScriptVariable> callArgumentValues(1 + (argumentValues.size() - 3) / 2);
							//	this
							callArgumentValues[0] = move(argumentValues[1]);
							//	additional method call arguments
							{
								auto callArgumentValueIdx = 1;
								for (auto argumentValueIdx = 3; argumentValueIdx < argumentValues.size(); argumentValueIdx+=2) {
									// do we have a this variable name?
									string argumentVariableName;
									if (argumentValues[argumentValueIdx].getType() != MiniScript::TYPE_NULL && argumentValues[argumentValueIdx].getStringValue(argumentVariableName) == true) {
										// yep, looks like that
										if (method != nullptr) {
											argumentValues[argumentValueIdx + 1] = miniScript->getVariable(argumentVariableName, &statement, callArgumentValueIdx >= method->getArgumentTypes().size()?false:method->getArgumentTypes()[callArgumentValueIdx].reference);
										} else
										if (functionIdx != MiniScript::SCRIPTIDX_NONE) {
											argumentValues[argumentValueIdx + 1] = miniScript->getVariable(argumentVariableName, &statement, callArgumentValueIdx >= miniScript->getScripts()[functionIdx].arguments.size()?false:miniScript->getScripts()[functionIdx].arguments[callArgumentValueIdx].reference);
										}
									}
									//
									callArgumentValues[callArgumentValueIdx] = move(argumentValues[argumentValueIdx + 1]);
									callArgumentValueIdx++;
								}
							}
							//
							span callArgumentValuesSpan(callArgumentValues);
							//
							if (method != nullptr) {
								method->executeMethod(callArgumentValuesSpan, returnValue, statement);
							} else
							if (functionIdx != MiniScript::SCRIPTIDX_NONE) {
								miniScript->call(functionIdx, callArgumentValuesSpan, returnValue);
							}
							// write back arguments from call arguments
							//	this
							argumentValues[1] = move(callArgumentValuesSpan[0]);
							//	additional arguments
							{
								auto callArgumentValueIdx = 1;
								for (auto argumentValueIdx = 3; argumentValueIdx < argumentValues.size(); argumentValueIdx+=2) {
									argumentValues[argumentValueIdx] = move(callArgumentValuesSpan[callArgumentValueIdx].getValueAsString());
									callArgumentValueIdx++;
								}
							}
						}
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()) + ": invalid variable type");
						miniScript->startErrorScript();
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
			bool isPrivate() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodInternalEvaluateMemberAccess(this));
	}
	// script base methods
	{
		//
		class ScriptMethodScriptEvaluate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEvaluate(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "statement", .optional = false, .reference = false, .nullable = false }
					},
					TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.evaluate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string statementString;
				if (miniScript->getStringValue(argumentValues, 0, statementString, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (miniScript->evaluate(statementString, returnValue) == false) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": '" + statementString + "': An error occurred");
					}
				}
			}
		};
		registerMethod(new ScriptMethodScriptEvaluate(this));
	}
	{
		//
		class ScriptMethodScriptCall: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptCall(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.call"; // METHOD_SCRIPTCALL;
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string function;
				if (miniScript->getStringValue(argumentValues, 0, function) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto scriptIdx = miniScript->getFunctionScriptIdx(function);
					if (scriptIdx == SCRIPTIDX_NONE) {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": function not found: " + function);
						miniScript->startErrorScript();
					} else {
						#if defined (__APPLE__)
							// MACOSX currently does not support initializing span using begin and end iterators,
							vector<ScriptVariable> callArgumentValues(argumentValues.size() - 1);
							for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues[i - 1] = move(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
							// move back arguments
							for (auto i = 1; i < argumentValues.size(); i++) argumentValues[i] = move(callArgumentValues[i - 1]);
						#else
							span callArgumentValuesSpan(argumentValues.begin() + 1, argumentValues.end());
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
						#endif
					}
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodScriptCall(this));
	}
	//
	{
		//
		class ScriptMethodReturn: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodReturn(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "return";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (miniScript->isFunctionRunning() == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": no function is being executed, return($value) has no effect");
					miniScript->startErrorScript();
				} else
				if (argumentValues.size() == 0) {
					miniScript->stopRunning();
				} else
				if (argumentValues.size() == 1) {
					auto& scriptState = miniScript->getScriptState();
					scriptState.returnValue = argumentValues[0];
					miniScript->stopRunning();
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		registerMethod(new ScriptMethodReturn(this));
	}
	{
		//
		class ScriptMethodScriptGetVariables: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptGetVariables(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_MAP), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getVariables";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setType(TYPE_MAP);
				for (const auto& [variableName, variableValue]: miniScript->getScriptState().variables) {
					returnValue.setMapEntry(variableName, *variableValue);
				}
			}
		};
		registerMethod(new ScriptMethodScriptGetVariables(this));
	}
	{
		//
		class ScriptMethodEnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEnd(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "end";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (miniScript->getScriptState().endTypeStack.empty() == true) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": end without block/forXXX/if");
					miniScript->startErrorScript();
				} else {
					auto endType = miniScript->getScriptState().endTypeStack.top();
					miniScript->getScriptState().endTypeStack.pop();
					switch(endType) {
						case ScriptState::ENDTYPE_BLOCK:
							if (miniScript->isFunctionRunning() == true && miniScript->scriptStateStack.size() == 2) {
								miniScript->stopRunning();
							}
							break;
						case ScriptState::ENDTYPE_FOR:
							// no op
							break;
						case ScriptState::ENDTYPE_IF:
							miniScript->getScriptState().conditionStack.pop();
							break;
					}
					if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		registerMethod(new ScriptMethodEnd(this));
	}
	{
		//
		class ScriptMethodForTime: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForTime(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forTime";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto now = Time::getCurrentMillis();
					auto timeWaitStarted = now;
					auto forTimeStartedIt = miniScript->getScriptState().forTimeStarted.find(statement.line);
					if (forTimeStartedIt == miniScript->getScriptState().forTimeStarted.end()) {
						miniScript->getScriptState().forTimeStarted[statement.line] = timeWaitStarted;
					} else {
						timeWaitStarted = forTimeStartedIt->second;
					}
					//
					if (Time::getCurrentMillis() > timeWaitStarted + time) {
						miniScript->getScriptState().forTimeStarted.erase(statement.line);
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
					}
				}
			}
		};
		registerMethod(new ScriptMethodForTime(this));
	}
	{
		//
		class ScriptMethodForCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodForCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "forCondition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto now = Time::getCurrentMillis();
					if (booleanValue == false) {
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					} else {
						miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_FOR);
					}
				}
			}
		};
		registerMethod(new ScriptMethodForCondition(this));
	}
	{
		//
		class ScriptMethodIfCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodIfCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "if";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					miniScript->getScriptState().endTypeStack.push(ScriptState::ENDTYPE_IF);
					//
					miniScript->getScriptState().conditionStack.push(booleanValue);
					if (booleanValue == false) {
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		registerMethod(new ScriptMethodIfCondition(this));
	}
	{
		//
		class ScriptMethodElseIfCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElseIfCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "elseif";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue;
				if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
					miniScript->startErrorScript();
				} else {
					//
					auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
					if (conditionStackElement == false) {
						miniScript->getScriptState().conditionStack.pop();
						miniScript->getScriptState().conditionStack.push(booleanValue);
					}
					if (conditionStackElement == true || booleanValue == false) {
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		registerMethod(new ScriptMethodElseIfCondition(this));
	}
	{
		//
		class ScriptMethodElse: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodElse(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "else";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (miniScript->getScriptState().conditionStack.empty() == true) {
					Console::println("ScriptMethodElse::executeMethod(): else without if");
					miniScript->startErrorScript();
				} else {
					auto conditionStackElement = miniScript->getScriptState().conditionStack.top();
					if (conditionStackElement == true) {
						miniScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
						miniScript->gotoStatementGoto(statement);
					}
				}
			}
		};
		registerMethod(new ScriptMethodElse(this));
	}
	{
		//
		class ScriptMethodScriptWaitForCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWaitForCondition(MiniScript* miniScript): miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.waitForCondition";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				// script bindings
				miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
				miniScript->getScriptState().timeWaitTime = 100LL;
				miniScript->setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
			}
		};
		registerMethod(new ScriptMethodScriptWaitForCondition(this));
	}
	{
		//
		class ScriptMethodScriptWait: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptWait(MiniScript* miniScript):
				ScriptMethod({
					{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false, .reference = false, .nullable = false }
				}),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.wait";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t time;
				if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
					miniScript->getScriptState().timeWaitStarted = Time::getCurrentMillis();
					miniScript->getScriptState().timeWaitTime = time;
					miniScript->setScriptStateState(STATEMACHINESTATE_WAIT);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
				}
			}
		};
		registerMethod(new ScriptMethodScriptWait(this));
	}
	{
		//
		class ScriptMethodScriptEmit: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEmit(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.emit";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string condition;
				if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
					miniScript->emit(condition);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodScriptEmit(this));
	}
	{
		//
		class ScriptMethodScriptEnableNamedCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptEnableNamedCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.enableNamedCondition"; // METHOD_ENABLENAMEDCONDITION;
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->enabledNamedConditions.erase(
						remove(
							miniScript->enabledNamedConditions.begin(),
							miniScript->enabledNamedConditions.end(),
							name
						),
						miniScript->enabledNamedConditions.end()
					);
					miniScript->enabledNamedConditions.push_back(name);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodScriptEnableNamedCondition(this));
	}
	{
		//
		class ScriptMethodScriptDisableNamedCondition: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptDisableNamedCondition(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.disableNamedCondition"; // METHOD_DISABLENAMEDCONDITION;
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string name;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
					miniScript->enabledNamedConditions.erase(
						remove(
							miniScript->enabledNamedConditions.begin(),
							miniScript->enabledNamedConditions.end(),
							name
						),
						miniScript->enabledNamedConditions.end()
					);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodScriptDisableNamedCondition(this));
	}
	{
		//
		class ScriptMethodScriptGetNamedConditions: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptGetNamedConditions(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_STRING),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.getNamedConditions";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string result;
				for (const auto& namedCondition: miniScript->enabledNamedConditions) {
					result+= result.empty() == false?",":namedCondition;
				}
				returnValue.setValue(result);
			}
		};
		registerMethod(new ScriptMethodScriptGetNamedConditions(this));
	}
	{
		//
		class ScriptMethodConsoleLog: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConsoleLog(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.log";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				for (const auto& argumentValue: argumentValues) {
					Console::print(argumentValue.getValueAsString());
				}
				Console::println();
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodConsoleLog(this));
	}
	{
		//
		class ScriptMethodConsoleDump: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodConsoleDump(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					}
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "console.dump";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 1) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					Console::println(argumentValues[0].getValueAsString(true));
				}
			}
		};
		registerMethod(new ScriptMethodConsoleDump(this));
	}
	{
		//
		class ScriptMethodScriptStop: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodScriptStop(MiniScript* miniScript): ScriptMethod(), miniScript(miniScript) {}
			const string getMethodName() override {
				return "script.stop";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				miniScript->stopScriptExecution();
				miniScript->stopRunning();
			}
		};
		registerMethod(new ScriptMethodScriptStop(this));
	}
	// equality
	{
		//
		class ScriptMethodEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodEquals(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "equals";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueAsString() != argumentValues[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_EQUALS;
			}
		};
		registerMethod(new ScriptMethodEquals(this));
	}
	{
		//
		class ScriptMethodNotEqual: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNotEqual(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "notEqual";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueAsString() == argumentValues[i].getValueAsString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_NOTEQUAL;
			}
		};
		registerMethod(new ScriptMethodNotEqual(this));
	}
	// int methods
	{
		//
		class ScriptMethodInt: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodInt(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "int", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "int";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t integerValue;
				if (MiniScript::getIntegerValue(argumentValues, 0, integerValue, false) == true) {
					returnValue.setValue(integerValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodInt(this));
	}
	// float methods
	{
		//
		class ScriptMethodFloat: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodFloat(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "float", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "float";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float floatValue;
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(floatValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodFloat(this));
	}
	//
	{
		//
		class ScriptMethodGreater: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreater(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greater";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA > stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA > floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_GREATER;
			}
		};
		registerMethod(new ScriptMethodGreater(this));
	}
	{
		//
		class ScriptMethodGreaterEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGreaterEquals(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "greaterEquals";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA >= stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA >= floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_GREATEREQUALS;
			}
		};
		registerMethod(new ScriptMethodGreaterEquals(this));
	}
	{
		//
		class ScriptMethodLesser: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesser(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesser";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA < stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA < floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_LESSER;
			}
		};
		registerMethod(new ScriptMethodLesser(this));
	}
	{
		//
		class ScriptMethodLesserEquals: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodLesserEquals(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "lesserEquals";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string stringValueA;
					string stringValueB;
					if (MiniScript::getStringValue(argumentValues, 0, stringValueA, false) == true &&
						MiniScript::getStringValue(argumentValues, 1, stringValueB, false) == true) {
						returnValue.setValue(stringValueA <= stringValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					float floatValueA;
					float floatValueB;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
						returnValue.setValue(floatValueA <= floatValueB);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_LESSEREQUALS;
			}
		};
		registerMethod(new ScriptMethodLesserEquals(this));
	}
	// vector2 methods
	{
		//
		class ScriptMethodVec2: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_VECTOR2
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true) {
					returnValue.setValue(Vector2(xValue, yValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2(this));
	}
	{
		//
		class ScriptMethodVec2ComputeLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2ComputeLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.computeLength";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2ComputeLength(this));
	}
	{
		//
		class ScriptMethodVec2ComputeLengthSquared: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2ComputeLengthSquared(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.computeLengthSquared";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2ComputeLengthSquared(this));
	}
	{
		//
		class ScriptMethodVec2ComputeDotProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2ComputeDotProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.computeDotProduct";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 a;
				Vector2 b;
				if (MiniScript::getVector2Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector2Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector2::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2ComputeDotProduct(this));
	}
	{
		//
		class ScriptMethodVec2Normalize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2Normalize(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR2),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.normalize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
					auto length = vec2.computeLength();
					returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector2(0.0f, 0.0f):vec2.normalize());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2Normalize(this));
	}
	{
		//
		class ScriptMethodVec2GetX: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2GetX(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.getX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2GetX(this));
	}
	{
		//
		class ScriptMethodVec2GetY: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec2GetY(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec2.getY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2, false) == true) {
					returnValue.setValue(vec2.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec2GetY(this));
	}
	// vector3 methods
	{
		//
		class ScriptMethodVec3: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3(this));
	}
	{
		//
		class ScriptMethodVec3ComputeLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeLength";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeLength(this));
	}
	{
		//
		class ScriptMethodVec3ComputeLengthSquared: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeLengthSquared(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeLengthSquared";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeLengthSquared(this));
	}
	{
		//
		class ScriptMethodVec3ComputeDotProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeDotProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeDotProduct";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeDotProduct(this));
	}
	{
		//
		class ScriptMethodVec3ComputeCrossProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeCrossProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeCrossProduct";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector3::computeCrossProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeCrossProduct(this));
	}
	{
		//
		class ScriptMethodVec3Normalize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3Normalize(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.normalize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					auto length = vec3.computeLength();
					returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector3(0.0f, 0.0f, 0.0f):vec3.normalize());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3Normalize(this));
	}
	{
		//
		class ScriptMethodVec3ComputeAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3ComputeAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "n", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.computeAngle";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 a;
				Vector3 b;
				Vector3 n;
				if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, b, false) == true &&
					MiniScript::getVector3Value(argumentValues, 2, n, false) == true) {
					returnValue.setValue(Vector3::computeAngle(a, b, n));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3ComputeAngle(this));
	}
	{
		//
		class ScriptMethodVec3GetX: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetX(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetX(this));
	}
	{
		//
		class ScriptMethodVec3GetY: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetY(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetY(this));
	}
	{
		//
		class ScriptMethodVec3GetZ: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec3GetZ(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec3.getZ";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
					returnValue.setValue(vec3.getZ());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec3GetZ(this));
	}
	// vector4 methods
	{
		//
		class ScriptMethodVec4: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "w", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_VECTOR4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				float wValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 3, wValue, false) == true) {
					returnValue.setValue(Vector4(xValue, yValue, zValue, wValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4(this));
	}
	{
		//
		class ScriptMethodVec4ComputeLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4ComputeLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.computeLength";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					returnValue.setValue(Float::isInfinite(length) == true || Float::isNaN(length) == true?0.0f:length);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4ComputeLength(this));
	}
	{
		//
		class ScriptMethodVec4ComputeLengthSquared: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4ComputeLengthSquared(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.computeLengthSquared";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					returnValue.setValue(vec4.computeLengthSquared());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4ComputeLengthSquared(this));
	}
	{
		//
		class ScriptMethodVec4ComputeDotProduct: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4ComputeDotProduct(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.computeDotProduct";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 a;
				Vector4 b;
				if (MiniScript::getVector4Value(argumentValues, 0, a, false) == true &&
					MiniScript::getVector4Value(argumentValues, 1, b, false) == true) {
					returnValue.setValue(Vector4::computeDotProduct(a, b));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4ComputeDotProduct(this));
	}
	{
		//
		class ScriptMethodVec4Normalize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4Normalize(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR4),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.normalize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					auto length = vec4.computeLength();
					returnValue.setValue(length < Math::EPSILON || Float::isInfinite(length) == true || Float::isNaN(length) == true?Vector4(0.0f, 0.0f, 0.0f, 0.0f):vec4.normalize());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4Normalize(this));
	}
	{
		//
		class ScriptMethodVec4GetX: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4GetX(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.getX";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getX());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4GetX(this));
	}
	{
		//
		class ScriptMethodVec4GetY: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4GetY(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.getY";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getY());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4GetY(this));
	}
	{
		//
		class ScriptMethodVec4GetZ: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4GetZ(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.getZ";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getZ());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4GetZ(this));
	}
	{
		//
		class ScriptMethodVec4GetW: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodVec4GetW(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "vec4.getW";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector4 vec4;
				if (MiniScript::getVector4Value(argumentValues, 0, vec4, false) == true) {
					returnValue.setValue(vec4.getW());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodVec4GetW(this));
	}
	// quaternion methods
	{
		//
		class ScriptMethodQuaternionIdentity: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionIdentity(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_QUATERNION),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.identity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Quaternion().identity());
			}
		};
		registerMethod(new ScriptMethodQuaternionIdentity(this));
	}
	{
		//
		class ScriptMethodQuaternionInvert: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionInvert(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_QUATERNION
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.invert";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
					returnValue.setValue(quaternion.invert());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodQuaternionInvert(this));
	}
	{
		//
		class ScriptMethodQuaternionRotate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionRotate(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_QUATERNION
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.rotate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Quaternion().rotate(axis, angle));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodQuaternionRotate(this));
	}
	{
		//
		class ScriptMethodQuaternionNormalize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionNormalize(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_QUATERNION
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.normalize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
					returnValue.setValue(quaternion.normalize());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodQuaternionNormalize(this));
	}
	{
		//
		class ScriptMethodQuaternionInvert: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionInvert(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.computeEulerAngles";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
					returnValue.setValue(quaternion.computeEulerAngles());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodQuaternionInvert(this));
	}
	{
		//
		class ScriptMethodQuaternionComputeMatrix: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionComputeMatrix(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.computeMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Quaternion quaternion;
				if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
					returnValue.setValue(quaternion.computeMatrix());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodQuaternionComputeMatrix(this));
	}
	// matrix3x3 methods
	{
		//
		class ScriptMethodMatrix3x3Identity: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3Identity(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_MATRIX3x3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.identity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Matrix3x3().identity());
			}
		};
		registerMethod(new ScriptMethodMatrix3x3Identity(this));
	}
	{
		//
		class ScriptMethodMatrix3x3Translate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3Translate(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR2, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX3x3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.translate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 translation;
				if (MiniScript::getVector2Value(argumentValues, 0, translation, false) == true) {
					returnValue.setValue(Matrix3x3().identity().setTranslation(translation));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix3x3Translate(this));
	}
	{
		//
		class ScriptMethodMatrix3x3Rotate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3Rotate(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX3x3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.rotate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix3x3().identity().setAxes(angle));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix3x3Rotate(this));
	}
	{
		//
		class ScriptMethodMatrix3x3RotateAroundTextureCenter: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3RotateAroundTextureCenter(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX3x3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.rotateAroundTextureCenter";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float angle;
				if (MiniScript::getFloatValue(argumentValues, 0, angle, false) == true) {
					returnValue.setValue(Matrix3x3::rotateAroundTextureCenter(angle));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix3x3RotateAroundTextureCenter(this));
	}
	{
		//
		class ScriptMethodMatrix3x3RotateAroundPoint: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3RotateAroundPoint(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR2, .name = "point", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX3x3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.rotateAroundPoint";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 point;
				float angle;
				if (MiniScript::getVector2Value(argumentValues, 0, point, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix3x3().rotateAroundPoint(point, angle));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix3x3RotateAroundPoint(this));
	}
	{
		//
		class ScriptMethodMatrix3x3Scale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3Scale(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_MATRIX3x3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.scale";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector2 vec2Value;
				float floatValue;
				if (MiniScript::getVector2Value(argumentValues, 0, vec2Value, false) == true) {
					returnValue.setValue(Matrix3x3().identity().scale(vec2Value));
				} else
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Matrix3x3().identity().scale(floatValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}

		};
		registerMethod(new ScriptMethodMatrix3x3Scale(this));
	}
	// matrix4x4 methods
	{
		//
		class ScriptMethodMatrix4x4Identity: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Identity(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_MATRIX4x4),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.identity";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Matrix4x4().identity());
			}
		};
		registerMethod(new ScriptMethodMatrix4x4Identity(this));
	}
	{
		//
		class ScriptMethodMatrix4x4Translate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Translate(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.translate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 translation;
				if (MiniScript::getVector3Value(argumentValues, 0, translation, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setTranslation(translation));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix4x4Translate(this));
	}
	{
		//
		class ScriptMethodMatrix4x4Rotate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Rotate(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.rotate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 axis;
				float angle;
				if (MiniScript::getVector3Value(argumentValues, 0, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, angle, false) == true) {
					returnValue.setValue(Matrix4x4().identity().setAxes(axis, angle));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix4x4Rotate(this));
	}
	{
		//
		class ScriptMethodMatrix4x4Scale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Scale(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_MATRIX4x4),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.scale";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Vector3 vec3Value;
				float floatValue;
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(vec3Value));
				} else
				if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
					returnValue.setValue(Matrix4x4().identity().scale(floatValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}

		};
		registerMethod(new ScriptMethodMatrix4x4Scale(this));
	}
	{
		//
		class ScriptMethodMatrix4x4Invert: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Invert(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "mat4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.invert";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Matrix4x4 mat4;
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
					returnValue.setValue(mat4.invert());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix4x4Invert(this));
	}
	{
		//
		class ScriptMethodMatrix4x4EulerAngles: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4EulerAngles(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "mat4", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.computeEulerAngles";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Matrix4x4 mat4;
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
					returnValue.setValue(mat4.computeEulerAngles());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodMatrix4x4EulerAngles(this));
	}
	// transform
	{
		//
		class ScriptMethodTransformAxisZ: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformAxisZ(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.AXIS_Z";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Vector3(0.0f, 0.0f, 1.0f));
			}
		};
		registerMethod(new ScriptMethodTransformAxisZ(this));
	}
	{
		//
		class ScriptMethodTransformAxisY: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformAxisY(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.AXIS_Y";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Vector3(0.0f, 1.0f, 0.0f));
			}
		};
		registerMethod(new ScriptMethodTransformAxisY(this));
	}
	{
		//
		class ScriptMethodTransformAxisX: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformAxisX(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_VECTOR3),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.AXIS_X";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Vector3(1.0f, 0.0f, 0.0f));
			}
		};
		registerMethod(new ScriptMethodTransformAxisX(this));
	}
	{
		//
		class ScriptMethodTransform: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransform(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = true, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "scale", .optional = true, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationZ", .optional = true, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationY", .optional = true, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationX", .optional = true, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_TRANSFORM),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 vec3Value;
				float floatValue;
				// translation
				if (argumentValues.size() >= 1) {
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
						transform.setTranslation(vec3Value);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				// scale
				if (argumentValues.size() >= 2) {
					if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
						transform.setScale(vec3Value);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				// rotations: we always use euler angles here
				transform.addRotation(Vector3(0.0f, 0.0f, 1.0f), 0.0f);
				transform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
				transform.addRotation(Vector3(1.0f, 0.0f, 0.0f), 0.0f);
				//
				for (auto i = 2; i < argumentValues.size() && i < 5; i++) {
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, true) == true) {
						transform.setRotationAngle(i - 2, floatValue);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				}
				transform.update();
				returnValue.setValue(transform);
			}
		};
		registerMethod(new ScriptMethodTransform(this));
	}
	{
		//
		class ScriptMethodTransformGetTranslation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetTranslation(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getTranslation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
					returnValue.setValue(transform.getTranslation());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetTranslation(this));
	}
	{
		//
		class ScriptMethodTransformSetTranslation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformSetTranslation(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.setTranslation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 translation;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, translation, false) == true) {
					transform.setTranslation(translation);
					transform.update();
					argumentValues[0].setValue(transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformSetTranslation(this));
	}
	{
		//
		class ScriptMethodTransformGetScale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetScale(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getScale";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
					returnValue.setValue(transform.getScale());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetScale(this));
	}
	{
		//
		class ScriptMethodTransformSetScale: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformSetScale(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "scale", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.setScale";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 scale;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, scale, false) == true) {
					transform.setScale(scale);
					transform.update();
					argumentValues[0].setValue(transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformSetScale(this));
	}
	{
		//
		class ScriptMethodTransformGetRotationAxis: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetRotationAxis(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getRotationAxis";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						returnValue.setValue(transform.getRotationAxis(idx));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetRotationAxis(this));
	}
	{
		//
		class ScriptMethodTransformGetRotationAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetRotationAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_FLOAT),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getRotationAngle";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
					if (idx < transform.getRotationCount()) {
						returnValue.setValue(transform.getRotationAngle(idx));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetRotationAngle(this));
	}
	{
		//
		class ScriptMethodTransformSetRotationAngle: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformSetRotationAngle(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.setRotationAngle";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t idx;
				Transform transform;
				float angle;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
					if (idx < transform.getRotationCount()) {
						transform.setRotationAngle(idx, angle);
						transform.update();
						argumentValues[0].setValue(transform);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": rotation index invalid: " + to_string(idx) + " / " + to_string(transform.getRotationCount()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformSetRotationAngle(this));
	}
	{
		//
		class ScriptMethodTransformRotate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformRotate(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.rotate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 vec3;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
					returnValue.setValue(transform.getRotationsQuaternion() * vec3);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformRotate(this));
	}
	{
		//
		class ScriptMethodTransformApplyRotation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformApplyRotation(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = true, .nullable = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.applyRotation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 axis;
				float angle;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, axis, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
					//
					transform.addRotation(axis, angle);
					transform.update();
					// get transform and make sure its a euler transform
					auto euler = transform.getTransformMatrix().computeEulerAngles();
					while (transform.getRotationCount() > 3) transform.removeRotation(transform.getRotationCount() - 1);
					while (transform.getRotationCount() < 3) transform.addRotation(Vector3(), 0.0f);
					transform.setRotationAxis(0, Vector3(0.0f, 0.0f, 1.0f));
					transform.setRotationAxis(1, Vector3(0.0f, 1.0f, 0.0f));
					transform.setRotationAxis(2, Vector3(1.0f, 0.0f, 0.0f));
					transform.setRotationAngle(0, euler.getZ());
					transform.setRotationAngle(1, euler.getY());
					transform.setRotationAngle(2, euler.getX());
					transform.update();
					argumentValues[0].setValue(transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformApplyRotation(this));
	}
	{
		//
		class ScriptMethodTransformInterpolateRotation: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformInterpolateRotation(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "currentAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "targetAngle", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "timePassedSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "degreesPerSeconds", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "interpolatedAngle", .optional = false, .reference = true, .nullable = false },
					},
					ScriptVariableType::TYPE_BOOLEAN),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.interpolateRotation";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				float currentAngle;
				float targetAngle;
				float timePassedSeconds;
				float degreesPerSeconds;
				float interpolatedAngle = 0.0f;
				if (argumentValues.size() == 5 &&
					MiniScript::getFloatValue(argumentValues, 0, currentAngle) == true &&
					MiniScript::getFloatValue(argumentValues, 1, targetAngle) == true &&
					MiniScript::getFloatValue(argumentValues, 2, timePassedSeconds) == true &&
					MiniScript::getFloatValue(argumentValues, 3, degreesPerSeconds) == true) {
					returnValue = Rotation::interpolate(currentAngle, targetAngle, timePassedSeconds, degreesPerSeconds, interpolatedAngle);
					argumentValues[4].setValue(interpolatedAngle);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformInterpolateRotation(this));
	}
	{
		//
		class ScriptMethodTransformGetTransformMatrix: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetTransformMatrix(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_MATRIX4x4),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getTransformMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
					returnValue.setValue(transform.getTransformMatrix());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetTransformMatrix(this));
	}
	{
		//
		class ScriptMethodTransformGetRotationsQuaternion: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformGetRotationsQuaternion(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_QUATERNION),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.getRotationsQuaternion";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true) {
					returnValue.setValue(transform.getRotationsQuaternion());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformGetRotationsQuaternion(this));
	}
	{
		//
		class ScriptMethodTransformFromMatrix: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformFromMatrix(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_MATRIX4x4, .name = "transformMatrix", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_TRANSFORM),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.fromMatrix";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Matrix4x4 transformMatrix;
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, transformMatrix, false) == true) {
					Transform transform;
					transform.fromMatrix(transformMatrix, RotationOrder::ZYX);
					returnValue.setValue(transform);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformFromMatrix(this));
	}
	// bool methods
	{
		//
		class ScriptMethodBool: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBool(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "bool";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool boolValue;
				if (MiniScript::getBooleanValue(argumentValues, 0, boolValue, false) == true) {
					returnValue.setValue(boolValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
		};
		registerMethod(new ScriptMethodBool(this));
	}
	{
		//
		class ScriptMethodNot: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodNot(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN), miniScript(miniScript) {}
			const string getMethodName() override {
				return "not";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				bool booleanValue = false;
				if (MiniScript::getBooleanValue(argumentValues, 0, booleanValue, false) == true) {
					returnValue.setValue(!booleanValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
					return;
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_NOT;
			}
		};
		registerMethod(new ScriptMethodNot(this));
	}
	{
		//
		class ScriptMethodAnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodAnd(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "and";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(true);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == false) {
							returnValue.setValue(false);
							break;
						}
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_AND;
			}
		};
		registerMethod(new ScriptMethodAnd(this));
	}
	{
		//
		class ScriptMethodOr: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodOr(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "or";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 2) {
					returnValue.setValue(false);
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(false);
					for (auto i = 0; i < argumentValues.size(); i++) {
						bool booleanValue;
						if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
							Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
							miniScript->startErrorScript();
						} else
						if (booleanValue == true) {
							returnValue.setValue(true);
							break;
						}
					}
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_OR;
			}
		};
		registerMethod(new ScriptMethodOr(this));
	}
	// string functions
	{
		//
		class ScriptMethodString: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodString(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodString(this));
	}
	{
		//
		class ScriptMethodStringLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.length";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(static_cast<int64_t>(stringValue.size()));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodStringLength(this));
	}
	{
		//
		class ScriptMethodStringCharAt: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringCharAt(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.charAt";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				int64_t index;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(index >= 0 && index < stringValue.size()?string(&stringValue[index], 1):string());
				}
			}
		};
		registerMethod(new ScriptMethodStringCharAt(this));
	}
	{
		//
		class ScriptMethodStringStartsWith: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringStartsWith(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "prefix", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.startsWith";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string prefix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, prefix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::startsWith(stringValue, prefix));
				}
			}
		};
		registerMethod(new ScriptMethodStringStartsWith(this));
	}
	{
		//
		class ScriptMethodStringEndsWith: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringEndsWith(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "suffix", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.endsWith";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string suffix;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, suffix, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::endsWith(stringValue, suffix));
				}
			}
		};
		registerMethod(new ScriptMethodStringEndsWith(this));
	}
	{
		//
		class ScriptMethodStringReplace: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringReplace(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.replace";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string what;
				string by;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 3, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::replace(stringValue, what, by, beginIndex));
				}
			}
		};
		registerMethod(new ScriptMethodStringReplace(this));
	}
	{
		//
		class ScriptMethodStringIndexOf: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIndexOf(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.indexOf";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::indexOf(stringValue, what, beginIndex)));
				}
			}
		};
		registerMethod(new ScriptMethodStringIndexOf(this));
	}
	{
		//
		class ScriptMethodStringFirstIndexOf: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringFirstIndexOf(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.firstIndexOf";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = 0;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::firstIndexOf(stringValue, what, beginIndex)));
				}
			}
		};
		registerMethod(new ScriptMethodStringFirstIndexOf(this));
	}
	{
		//
		class ScriptMethodStringLastIndexOf: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringLastIndexOf(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.lastIndexOf";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string what;
				int64_t beginIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, what, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(StringTools::lastIndexOf(stringValue, what, beginIndex)));
				}
			}
		};
		registerMethod(new ScriptMethodStringLastIndexOf(this));
	}
	{
		//
		class ScriptMethodStringSubString: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringSubString(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "endIndex", .optional = true, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.substring";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex;
				int64_t endIndex = -1;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, beginIndex, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, endIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					if (endIndex == -1) {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex));
					} else {
						returnValue.setValue(StringTools::substring(stringValue, beginIndex, endIndex));
					}
				}
			}
		};
		registerMethod(new ScriptMethodStringSubString(this));
	}
	{
		//
		class ScriptMethodStringEqualsIgnoreCase: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringEqualsIgnoreCase(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "other", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.equalsIgnoreCase";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string other;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, other, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::equalsIgnoreCase(stringValue, other));
				}
			}
		};
		registerMethod(new ScriptMethodStringEqualsIgnoreCase(this));
	}
	{
		//
		class ScriptMethodStringTrim: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringTrim(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.trim";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::trim(stringValue));
				}
			}
		};
		registerMethod(new ScriptMethodStringTrim(this));
	}
	{
		//
		class ScriptMethodStringRegexMatch: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringRegexMatch(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.regexMatch";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string pattern;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::regexMatch(stringValue, pattern));
				}
			}
		};
		registerMethod(new ScriptMethodStringRegexMatch(this));
	}
	{
		//
		class ScriptMethodStringRegexReplace: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringRegexReplace(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "pattern", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.regexReplace";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string pattern;
				string by;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, pattern, false) == false ||
					MiniScript::getStringValue(argumentValues, 2, by, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::regexReplace(stringValue, pattern, by));
				}
			}
		};
		registerMethod(new ScriptMethodStringRegexReplace(this));
	}
	{
		//
		class ScriptMethodStringTokenize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringTokenize(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "delimiters", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.tokenize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string delimiters;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, delimiters, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto tokenizedStringVector = StringTools::tokenize(stringValue, delimiters);
					//
					returnValue.setType(MiniScript::TYPE_ARRAY);
					for (const auto& tokenizedString: tokenizedStringVector) {
						returnValue.pushArrayEntry(tokenizedString);
					}
				}
			}
		};
		registerMethod(new ScriptMethodStringTokenize(this));
	}
	{
		//
		class ScriptMethodStringSpace: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringSpace(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "spaces", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.space";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t spaces = 1;
				if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					string spacesString;
					for (auto i = 0; i < spaces; i++) spacesString+= " ";
					returnValue.setValue(spacesString);
				}
			}
		};
		registerMethod(new ScriptMethodStringSpace(this));
	}
	{
		//
		class ScriptMethodStringConcatenate: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringConcatenate(MiniScript* miniScript): ScriptMethod({}, ScriptVariableType::TYPE_STRING), miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.concatenate";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string result;
				for (const auto& argumentValue: argumentValues) {
					result+= argumentValue.getValueAsString();
				}
				returnValue.setValue(result);
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodStringConcatenate(this));
	}
	{
		//
		class ScriptMethodToStringUpperCase: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToStringUpperCase(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.toUpperCase";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toUpperCase(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodToStringUpperCase(this));
	}
	{
		//
		class ScriptMethodToStringLowerCase: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodToStringLowerCase(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.toLowerCase";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(StringTools::toLowerCase(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodToStringLowerCase(this));
	}
	{
		//
		class ScriptMethodStringIsEmpty: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsEmpty(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isEmpty";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(stringValue.empty());
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodStringIsEmpty(this));
	}
	{
		//
		class ScriptMethodStringIsFloat: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsFloat(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isFloat";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Float::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodStringIsFloat(this));
	}
	{
		//
		class ScriptMethodStringIsInteger: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringIsInteger(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.isInteger";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
					returnValue.setValue(Integer::is(stringValue));
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodStringIsInteger(this));
	}
	{
		//
		class ScriptMethodStringPadLeft: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringPadLeft(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "toSize", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.padLeft";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::padLeft(stringValue, by, toSize));
				}
			}
		};
		registerMethod(new ScriptMethodStringPadLeft(this));
	}
	{
		//
		class ScriptMethodStringPadRight: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodStringPadRight(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "toSize", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.padRight";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				string by;
				int64_t toSize;
				if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, by, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, toSize, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::padRight(stringValue, by, toSize));
				}
			}
		};
		registerMethod(new ScriptMethodStringPadRight(this));
	}
	// array methods
	{
		//
		class ScriptMethodArray: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArray(MiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_ARRAY);
				for (const auto& argumentValue: argumentValues) {
					returnValue.pushArrayEntry(argumentValue);
				}
			}
		};
		registerMethod(new ScriptMethodArray(this));
	}
	{
		//
		class ScriptMethodArrayLength: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayLength(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.length";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(static_cast<int64_t>(argumentValues[0].getArraySize()));
				}
			}
		};
		registerMethod(new ScriptMethodArrayLength(this));
	}
	{
		//
		class ScriptMethodArrayPush: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayPush(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.push";
			}
			bool isVariadic() const override {
				return true;
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				if (argumentValues.size() < 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					for (auto i = 1; i < argumentValues.size(); i++) {
						argumentValues[0].pushArrayEntry(argumentValues[i]);
					}
				}
			}
		};
		registerMethod(new ScriptMethodArrayPush(this));
	}
	{
		//
		class ScriptMethodArrayGet: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayGet(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.get";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() <= 1 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = argumentValues[0].getArrayEntry(index);
				}
			}
		};
		registerMethod(new ScriptMethodArrayGet(this));
	}
	{
		//
		class ScriptMethodArraySet: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArraySet(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.set";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() <= 2 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].setArrayEntry(index, argumentValues[2]);
				}
			}
		};
		registerMethod(new ScriptMethodArraySet(this));
	}
	{
		//
		class ScriptMethodArrayRemove: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayRemove(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.remove";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t index;
				if ((argumentValues.size() < 2 || argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) ||
					MiniScript::getIntegerValue(argumentValues, 1, index, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeArrayEntry(index);
				}
			}
		};
		registerMethod(new ScriptMethodArrayRemove(this));
	}
	{
		//
		class ScriptMethodArrayRemoveOf: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayRemoveOf(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.removeOf";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto& array = argumentValues[0];
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							array.removeArrayEntry(i);
							i--;
						}
					}
				}
			}
		};
		registerMethod(new ScriptMethodArrayRemoveOf(this));
	}
	{
		//
		class ScriptMethodArrayIndexOf: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayIndexOf(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.indexOf";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string stringValue;
				int64_t beginIndex = 0;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, stringValue, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 2, beginIndex, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					const auto& array = argumentValues[0];
					returnValue.setValue(static_cast<int64_t>(-1));
					for (auto i = beginIndex; i < array.getArraySize(); i++) {
						auto arrayValue = array.getArrayEntry(i);
						if (arrayValue.getValueAsString() == stringValue) {
							returnValue.setValue(static_cast<int64_t>(i));
							break;
						}
					}
				}
			}
		};
		registerMethod(new ScriptMethodArrayIndexOf(this));
	}
	{
		//
		class ScriptMethodArraySort: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArraySort(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.sort";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string function;
				if (argumentValues.size() != 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY ||
					MiniScript::getStringValue(argumentValues, 1, function, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = argumentValues[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						class SortClass {
							private:
								MiniScript* miniScript;
								const string& function;
							public:
								SortClass(MiniScript* miniScript, const string& function): miniScript(miniScript), function(function) {
								}
								bool operator()(const MiniScript::ScriptVariable* a, const MiniScript::ScriptVariable* b) const {
									vector<MiniScript::ScriptVariable> sortArgumentValues { *a, *b };
									span sortArgumentValuesSpan(sortArgumentValues);
									MiniScript::ScriptVariable sortReturnValue;
									miniScript->call(function, sortArgumentValuesSpan, sortReturnValue);
									bool result = false;
									sortReturnValue.getBooleanValue(result, false);
									return result;
								}
						};
						sort(arrayPtr->begin(), arrayPtr->end(), SortClass(miniScript, function));
					}
				}
			}
		};
		registerMethod(new ScriptMethodArraySort(this));
	}
	{
		//
		class ScriptMethodArrayReverse: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodArrayReverse(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .reference = true, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "array.reverse";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_ARRAY) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					//
					auto arrayPtr = argumentValues[0].getArrayPointer();
					if (arrayPtr != nullptr) {
						reverse(arrayPtr->begin(), arrayPtr->end());
					}
				}
			}
		};
		registerMethod(new ScriptMethodArrayReverse(this));
	}
	// map
	{
		//
		class ScriptMethodMap: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMap(MiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_MAP
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_MAP);
			}
		};
		registerMethod(new ScriptMethodMap(this));
	}
	{
		//
		class ScriptMethodMapSet: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapSet(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.set";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() != 3 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].setMapEntry(key, argumentValues[2]);
				}
			}
		};
		registerMethod(new ScriptMethodMapSet(this));
	}
	{
		//
		class ScriptMethodMapHas: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapHas(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].hasMapEntry(key));
				}
			}
		};
		registerMethod(new ScriptMethodMapHas(this));
	}
	{
		//
		class ScriptMethodMapGet: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGet(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.get";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue = argumentValues[0].getMapEntry(key);
				}
			}
		};
		registerMethod(new ScriptMethodMapGet(this));
	}
	{
		//
		class ScriptMethodMapRemove: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapRemove(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.remove";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeMapEntry(key);
				}
			}
		};
		registerMethod(new ScriptMethodMapRemove(this));
	}
	{
		//
		class ScriptMethodMapGetKeys: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGetKeys(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.getKeys";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = argumentValues[0].getMapKeys();
					returnValue.setType(TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		registerMethod(new ScriptMethodMapGetKeys(this));
	}
	{
		//
		class ScriptMethodMapGetValues: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMapGetValues(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "map.getValues";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_MAP) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto values = argumentValues[0].getMapValues();
					returnValue.setType(TYPE_ARRAY);
					for (const auto value: values) {
						returnValue.pushArrayEntry(*value);
					}
				}
			}
		};
		registerMethod(new ScriptMethodMapGetValues(this));
	}
	// sets
	{
		//
		class ScriptMethodSet: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSet(MiniScript* miniScript):
				ScriptMethod(
					{},
					ScriptVariableType::TYPE_SET
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setType(MiniScript::TYPE_SET);
			}
		};
		registerMethod(new ScriptMethodSet(this));
	}
	{
		//
		class ScriptMethodSetInsert: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetInsert(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.insert";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() != 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].insertSetKey(key);
				}
			}
		};
		registerMethod(new ScriptMethodSetInsert(this));
	}
	{
		//
		class ScriptMethodSetHas: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetHas(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.has";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].hasSetKey(key));
				}
			}
		};
		registerMethod(new ScriptMethodSetHas(this));
	}
	{
		//
		class ScriptMethodSetRemove: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetRemove(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .reference = true, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.remove";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string key;
				if (argumentValues.size() < 2 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_SET ||
					MiniScript::getStringValue(argumentValues, 1, key, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					argumentValues[0].removeSetKey(key);
				}
			}
		};
		registerMethod(new ScriptMethodSetRemove(this));
	}
	{
		//
		class ScriptMethodSetGetKeys: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetGetKeys(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_ARRAY
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "set.getKeys";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1 ||
					argumentValues[0].getType() != ScriptVariableType::TYPE_SET) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto keys = argumentValues[0].getSetKeys();
					returnValue.setType(TYPE_ARRAY);
					for (const auto& key: keys) {
						returnValue.pushArrayEntry(key);
					}
				}
			}
		};
		registerMethod(new ScriptMethodSetGetKeys(this));
	}
	// get variable
	{
		//
		class ScriptMethodGetVariable: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetVariable(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariable";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}

		};
		registerMethod(new ScriptMethodGetVariable(this));
	}
	// get variable reference
	{
		//
		class ScriptMethodGetVariableReference: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodGetVariableReference(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "getVariableReference";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					returnValue = miniScript->getVariable(variable, &statement, true);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isPrivate() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodGetVariableReference(this));
	}
	// set variable
	{
		//
		class ScriptMethodSetVariable: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodSetVariable(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "setVariable";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (argumentValues.size() != 2 ||
					MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->setVariable(variable, argumentValues[1], &statement);
					returnValue = argumentValues[1];
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_SET;
			}
		};
		registerMethod(new ScriptMethodSetVariable(this));
	}
	// unset variable
	{
		//
		class ScriptMethodUnsetVariable: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodUnsetVariable(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_NULL
				),
				miniScript(miniScript) {
				//
			}
			const string getMethodName() override {
				return "unsetVariable";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string variable;
				if (argumentValues.size() != 1 ||
					MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					miniScript->unsetVariable(variable, &statement);
				}
			}
		};
		registerMethod(new ScriptMethodUnsetVariable(this));
	}
	// time
	{
		//
		class ScriptMethodTimeGetCurrentMillis: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimeGetCurrentMillis(MiniScript* miniScript):
				ScriptMethod({}, ScriptVariableType::TYPE_INTEGER),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getCurrentMillis";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				returnValue.setValue(Time::getCurrentMillis());
			}
		};
		registerMethod(new ScriptMethodTimeGetCurrentMillis(this));
	}
	{
		//
		class ScriptMethodTimeGetAsString: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTimeGetAsString(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "format", .optional = true, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "time.getAsString";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string format = "%Y-%m-%d %H:%M:%S";
				if (MiniScript::getStringValue(argumentValues, 0, format, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(Time::getAsString(format));
				}
			}
		};
		registerMethod(new ScriptMethodTimeGetAsString(this));
	}
	// xml
	{
		//
		class ScriptMethodXMLCreateTag: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodXMLCreateTag(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_MAP, .name = "attributes", .optional = true, .reference = false, .nullable = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "innerXML", .optional = true, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "xml.createTag";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				string name;
				string innerXML;
				if (MiniScript::getStringValue(argumentValues, 0, name, false) == false ||
					(argumentValues.size() >= 2 && argumentValues[1].getType() != ScriptVariableType::TYPE_MAP) ||
					MiniScript::getStringValue(argumentValues, 2, innerXML, true) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					auto mapPtr = argumentValues[1].getMapPointer();
					string xml;
					xml+= "<" + name;
					if (mapPtr != nullptr && mapPtr->empty() == false) {
						for(const auto& [mapEntryName, mapEntryValue]: *mapPtr) {
							xml+= " " + mapEntryName + "=\"" + GUIParser::escape(mapEntryValue->getValueAsString()) + "\"";
						}
					}
					if (innerXML.empty() == true) {
						xml+= "/>";
					} else {
						xml+= ">" + innerXML + "</" + name + ">";
					}
					//
					returnValue.setValue(xml);
				}
			}
		};
		registerMethod(new ScriptMethodXMLCreateTag(this));
	}
	// json
	{
		//
		class ScriptMethodJSONSerialize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodJSONSerialize(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_STRING
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.serialize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				//
				if (argumentValues.size() != 1) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(argumentValues[0].getValueAsString());
				}
			}
		};
		registerMethod(new ScriptMethodJSONSerialize(this));
	}
	{
		//
		class ScriptMethodJSONDeserialize: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodJSONDeserialize(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_STRING, .name = "json", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "json.deserialize";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string json;
				if (MiniScript::getStringValue(argumentValues, 0, json, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					json = StringTools::trim(json);
					if (StringTools::startsWith(json, "{") == true) {
						returnValue = MiniScript::initializeMapSet(json, miniScript, statement);
					} else
					if (StringTools::startsWith(json, "[") == true) {
						returnValue = MiniScript::initializeArray(json, miniScript, statement);
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": JSON string not valid");
					}
				}
			}
		};
		registerMethod(new ScriptMethodJSONDeserialize(this));
	}
	{
		//
		class ScriptMethodIncrement: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodIncrement(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixIncrement";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					++value;
					argumentValues[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_INCREMENT;
			}
		};
		registerMethod(new ScriptMethodIncrement(this));
	}
	{
		//
		class ScriptMethodDecrement: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodDecrement(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .reference = true, .nullable = false },
					},
					ScriptVariableType::TYPE_INTEGER
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "prefixDecrement";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					--value;
					argumentValues[0].setValue(value);
					returnValue.setValue(value);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_DECREMENT;
			}
		};
		registerMethod(new ScriptMethodDecrement(this));
	}
	//
	{
		//
		class ScriptMethodBitwiseNot: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseNot(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "value", .optional = false, .reference = false, .nullable = false },
					},
					ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseNot";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t value;
				if (MiniScript::getIntegerValue(argumentValues, 0, value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(~value);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_BITWISENOT;
			}
		};
		registerMethod(new ScriptMethodBitwiseNot(this));
	}
	//
	{
		class ScriptMethodBitwiseAnd: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseAnd(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseAnd";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA & valueB);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_BITWISEAND;
			}
		};
		registerMethod(new ScriptMethodBitwiseAnd(this));
	}
	//
	{
		class ScriptMethodBitwiseOr: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseOr(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseOr";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA | valueB);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_BITWISEOR;
			}
		};
		registerMethod(new ScriptMethodBitwiseOr(this));
	}
	//
	{
		class ScriptMethodBitwiseXor: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodBitwiseXor(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .reference = false, .nullable = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .reference = false, .nullable = false }
					},
					ScriptVariableType::TYPE_INTEGER),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "bitwiseXor";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				int64_t valueA;
				int64_t valueB;
				if (MiniScript::getIntegerValue(argumentValues, 0, valueA, false) == false ||
					MiniScript::getIntegerValue(argumentValues, 1, valueB, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(valueA ^ valueB);
				}
			}
			ScriptOperator getOperator() const override {
				return OPERATOR_BITWISEXOR;
			}
		};
		registerMethod(new ScriptMethodBitwiseXor(this));
	}

	// register math functions
	MiniScriptMath::registerMethods(this);

	// determine operators
	for (const auto& [scriptMethodName, scriptMethod]: scriptMethods) {
		auto methodOperator = scriptMethod->getOperator();
		if (methodOperator != OPERATOR_NONE) {
			auto methodOperatorString = getOperatorAsString(methodOperator);
			auto scriptOperatorIt = scriptOperators.find(static_cast<uint8_t>(methodOperator));
			if (scriptOperatorIt != scriptOperators.end()) {
				Console::println("MiniScript::registerMethods(): operator '" + methodOperatorString + "' already registered for method '" + scriptMethod->getMethodName() + "'");
				continue;
			}
			scriptOperators[static_cast<uint8_t>(methodOperator)] = scriptMethod;
		}
	}
}

void MiniScript::registerVariables() {
}

const MiniScript::ScriptVariable MiniScript::initializeArray(const string_view& initializerString, MiniScript* miniScript, const ScriptStatement& statement) {
	ScriptVariable variable;
	variable.setType(TYPE_ARRAY);
	//
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto quote = '\0';
	auto arrayValueStart = string::npos;
	auto arrayValueEnd = string::npos;
	auto quotedArrayValueStart = string::npos;
	auto quotedArrayValueEnd = string::npos;
	auto lc = '\0';
	auto i = 0;
	//
	auto pushToArray = [&]() -> void {
		// quoted value
		if (quotedArrayValueStart != string::npos) {
			quotedArrayValueStart++;
			auto arrayValueLength = quotedArrayValueEnd - quotedArrayValueStart;
			if (arrayValueLength > 0) {
				auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[quotedArrayValueStart], arrayValueLength));
				if (arrayValueStringView.empty() == false) {
					variable.pushArrayEntry(string(arrayValueStringView));
				}
			}
		} else
		// unquoted value
		if (arrayValueStart != string::npos) {
			arrayValueEnd = i - 1;
			auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
			if (arrayValueLength > 0) {
				auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
				if (arrayValueStringView.empty() == false) {
					ScriptVariable arrayValue;
					arrayValue.setImplicitTypedValueFromStringView(arrayValueStringView, miniScript, statement);
					variable.pushArrayEntry(arrayValue);
				}
			}
		}
		//
		quotedArrayValueStart = string::npos;
		quotedArrayValueEnd = string::npos;
		arrayValueStart = string::npos;
		arrayValueEnd = string::npos;
	};
	//
	for (; i < initializerString.size(); i++) {
		auto c = initializerString[i];
		// quotes
		if (squareBracketCount == 1 && curlyBracketCount == 0 && (c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
				quotedArrayValueStart = i;
			} else
			if (quote == c) {
				quote = '\0';
				quotedArrayValueEnd = i;
			}
		} else
		// no quote
		if (quote == '\0') {
			// , -> push to array
			if (squareBracketCount == 1 && curlyBracketCount == 0 && bracketCount == 0 && c == ',') {
				// push to array
				pushToArray();
			} else
			// possible function call
			if (c == '(') {
				bracketCount++;
			} else
			if (c == ')') {
				bracketCount--;
			} else
			// array initializer
			if (c == '[' && curlyBracketCount == 0 && bracketCount == 0) {
				// we have a inner array initializer, mark it
				if (squareBracketCount == 1) arrayValueStart = i;
				// increase square bracket count
				squareBracketCount++;
			} else
			// end of array initializer
			if (c == ']' && curlyBracketCount == 0 && bracketCount == 0) {
				squareBracketCount--;
				// done? push to array
				if (squareBracketCount == 0) {
					// push to array
					pushToArray();
				} else
				// otherwise push inner array initializer
				if (squareBracketCount == 1) {
					// parse and push
					if (arrayValueStart != string::npos) {
						arrayValueEnd = i;
						auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
						if (arrayValueLength > 0) {
							auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
							if (arrayValueStringView.empty() == false) {
								auto arrayValue = initializeArray(arrayValueStringView, miniScript, statement);
								variable.pushArrayEntry(arrayValue);
							}
						}
						//
						arrayValueStart = string::npos;
						arrayValueEnd = string::npos;
					}
				}
			} else
			// map/set initializer
			if (c == '{' && squareBracketCount == 1 && bracketCount == 0) {
				// we have a inner map/set initializer, mark it
				if (curlyBracketCount == 0) arrayValueStart = i;
				// increase curly bracket count
				curlyBracketCount++;
			} else
			// end of map/set initializer
			if (c == '}' && squareBracketCount == 1 && bracketCount == 0) {
				curlyBracketCount--;
				// otherwise push inner array initializer
				if (curlyBracketCount == 0) {
					// parse and push
					if (arrayValueStart != string::npos) {
						arrayValueEnd = i;
						auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
						if (arrayValueLength > 0) {
							auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
							if (arrayValueStringView.empty() == false) {
								auto arrayValue = initializeMapSet(arrayValueStringView, miniScript, statement);
								variable.pushArrayEntry(arrayValue);
							}
						}
						//
						arrayValueStart = string::npos;
						arrayValueEnd = string::npos;
					}
				}
			} else
			// set up argument start
			if (squareBracketCount == 1 && curlyBracketCount == 0 && bracketCount == 0 && arrayValueStart == string::npos && c != ' ' && c != '\t' && c != '\n') {
				arrayValueStart = i;
			}
		}
		//
		lc = c;
	}
	//
	auto initalizer = make_unique<MiniScript::ScriptVariable::Initializer>(string(initializerString), statement, nullptr);
	variable.initializer->copy(initalizer.get());
	//
	return variable;
}

const MiniScript::ScriptVariable MiniScript::initializeMapSet(const string_view& initializerString, MiniScript* miniScript, const ScriptStatement& statement) {
	ScriptVariable variable;
	variable.setType(TYPE_MAP);
	//
	auto bracketCount = 0;
	auto curlyBracketCount = 0;
	auto squareBracketCount = 0;
	auto quote = '\0';
	auto mapKeyStart = string::npos;
	auto mapKeyEnd = string::npos;
	auto mapValueStart = string::npos;
	auto mapValueEnd = string::npos;
	auto quotedMapKeyStart = string::npos;
	auto quotedMapKeyEnd = string::npos;
	auto quotedMapValueStart = string::npos;
	auto quotedMapValueEnd = string::npos;
	auto i = 0;
	enum ParseMode { PARSEMODE_KEY, PARSEMODE_VALUE };
	auto parseMode = PARSEMODE_KEY;
	auto hasValues = false;
	auto inlineFunctionSignatureStart = string::npos;

	//
	auto insertMapKeyValuePair = [&]() -> void {
		//
		string_view mapKey;
		// quoted map key
		if (quotedMapKeyStart != string::npos && quotedMapKeyEnd != string::npos) {
			quotedMapKeyStart++;
			auto mapKeyLength = quotedMapKeyEnd - quotedMapKeyStart;
			if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[quotedMapKeyStart], mapKeyLength));
		} else
		// unquoted map key
		if (mapKeyStart != string::npos && mapKeyEnd != string::npos) {
			//
			auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
			if (mapKeyLength > 0) {
				mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
				if (mapKey.empty() == true) mapKey = string_view();
			}
		}
		//
		quotedMapKeyStart = string::npos;
		quotedMapKeyEnd = string::npos;
		mapKeyStart = string::npos;
		mapKeyEnd = string::npos;
		// validate map key
		if (mapKey.empty() == true) {
			// no op
		} else
		if (viewIsKey(mapKey) == false) {
			Console::println(miniScript->getStatementInformation(statement) + ": a invalid key name, ignoring map entry: " + string(mapKey));
		} else {
			// quoted map value
			if (quotedMapValueStart != string::npos && quotedMapValueEnd != string::npos) {
				quotedMapValueStart++;
				auto mapValueLength = quotedMapValueEnd - quotedMapValueStart;
				if (mapValueLength > 0) {
					auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[quotedMapValueStart], mapValueLength));
					if (mapValueStringView.empty() == false) {
						//
						variable.setMapEntry(string(mapKey), string(mapValueStringView));
						//
						hasValues = true;
					}
				}
			} else
			// unquoted map value
			if (mapValueStart != string::npos && mapValueEnd != string::npos) {
				auto mapValueLength = mapValueEnd - mapValueStart + 1;
				if (mapValueLength > 0) {
					auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
					if (mapValueStringView.empty() == false) {
						ScriptVariable mapValue;
						mapValue.setImplicitTypedValueFromStringView(mapValueStringView, miniScript, statement);
						//
						variable.setMapEntry(string(mapKey), mapValue);
						//
						hasValues = true;
					}
				}
			} else {
				//
				variable.setMapEntry(string(mapKey), ScriptVariable());
			}
		}
		//
		quotedMapValueStart = string::npos;
		quotedMapValueEnd = string::npos;
		mapValueStart = string::npos;
		mapValueEnd = string::npos;
		inlineFunctionSignatureStart = string::npos;

		//
		parseMode = PARSEMODE_KEY;
	};
	//
	auto lc = '\0';
	for (; i < initializerString.size(); i++) {
		auto c = initializerString[i];
		// quotes
		if (curlyBracketCount == 1 && squareBracketCount == 0 && (c == '"' || c == '\'') && lc != '\\') {
			// we have a new quote here
			if (quote == '\0') {
				quote = c;
				// key?
				if (parseMode == PARSEMODE_KEY) {
					quotedMapKeyStart = i;
					mapKeyStart = string::npos;
				} else
				// value
				if (parseMode == PARSEMODE_VALUE) {
					quotedMapValueStart = i;
					mapValueStart = string::npos;
				}
			} else
			// finish the quote
			if (quote == c) {
				quote = '\0';
				// key?
				if (parseMode == PARSEMODE_KEY) {
					quotedMapKeyEnd = i;
				} else
				// value
				if (parseMode == PARSEMODE_VALUE) {
					quotedMapValueEnd = i;
				}
			}
		} else
		// no quote
		if (quote == '\0') {
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c == ':' && lc != '\\') {
				//
				if (quotedMapKeyStart != string::npos) {
					quotedMapKeyEnd = i - 1;
				} else
				if (mapKeyStart != string::npos) {
					mapKeyEnd = i - 1;
				}
				//
				parseMode = PARSEMODE_VALUE;
				//
			} else
			// , -> insert map
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c == ',') {
				if (mapValueStart != string::npos) {
					mapValueEnd = i - 1;
				} else
				if (mapKeyStart != string::npos && mapValueStart == string::npos && quotedMapValueStart == string::npos) {
					mapKeyEnd = i - 1;
				}
				// insert map key value pair
				insertMapKeyValuePair();
				// nada
			} else
			// possible function call
			if (c == '(') {
				//
				bracketCount++;
				//
				if (bracketCount == 1) inlineFunctionSignatureStart = i;
			} else
			if (c == ')') {
				bracketCount--;
				// function assignment
				if (inlineFunctionSignatureStart != string::npos && bracketCount == 0 && mapValueStart == string::npos) mapValueStart = inlineFunctionSignatureStart;
				//
				inlineFunctionSignatureStart = string::npos;
			} else
			// map/set initializer
			if (c == '{' && squareBracketCount == 0 && bracketCount == 0) {
				// increase square bracket count
				curlyBracketCount++;
				// we have a inner map/set initializer, mark it
				if (curlyBracketCount == 1) {
					mapKeyStart = i + 1;
				} else
				if (curlyBracketCount == 2) {
					if (mapValueStart == string::npos) mapValueStart = i;
				}
			} else
			// end of map/set initializer
			if (c == '}' && squareBracketCount == 0 && bracketCount == 0) {
				//
				curlyBracketCount--;
				// done? insert into map
				if (curlyBracketCount == 0) {
					//
					if (mapValueStart != string::npos) {
						mapValueEnd = i - 1;
					} else
					if (mapKeyStart != string::npos) {
						mapKeyEnd = i - 1;
					}
					// insert map key value pair
					insertMapKeyValuePair();
				} else
				// otherwise push inner array initializer
				if (curlyBracketCount == 1) {
					// parse and insert into map
					string_view mapKey;
					// quoted map key
					if (quotedMapKeyStart != string::npos) {
						quotedMapKeyStart++;
						auto mapKeyLength = quotedMapKeyEnd - quotedMapKeyStart;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[quotedMapKeyStart], mapKeyLength));
					} else
					// unquoted map key
					if (mapKeyStart != string::npos) {
						if (mapKeyEnd == string::npos) mapKeyEnd = i;
						auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
					}
					// validate map key
					if (mapKey.empty() == true || viewIsKey(mapKey) == false) {
						Console::println(miniScript->getStatementInformation(statement) + ": invalid key name, ignoring map entry: " + string(mapKey));
					} else {
						//
						quotedMapKeyStart = string::npos;
						quotedMapKeyEnd = string::npos;
						mapKeyStart = string::npos;
						mapKeyEnd = string::npos;
						inlineFunctionSignatureStart = string::npos;

						// map value
						if (mapValueStart != string::npos) {
							mapValueEnd = i;
							auto mapValueLength = mapValueEnd - mapValueStart + 1;
							if (mapValueLength > 0) {
								auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
								if (mapValueStringView.empty() == false) {
									//
									vector<string_view> arguments;
									string_view functionScriptCodeStringView;
									if (viewIsInlineFunction(mapValueStringView, arguments, functionScriptCodeStringView) == true) {
										string functionScriptCode;
										// function declaration
										auto functionName = string() + "map_inline_function_" + to_string(miniScript->inlineFunctionIdx++);
										functionScriptCode = "function: " + functionName + "(=$this";
										auto argumentIdx = 0;
										for (const auto& argument: arguments) {
											functionScriptCode+= ",";
											functionScriptCode+= argument;
											argumentIdx++;
										}
										functionScriptCode+= string() + ")" + "\n";
										// function definition
										auto scriptCode = string(functionScriptCodeStringView);
										auto lineIdx = MiniScript::LINE_FIRST;
										auto currentLineIdx = MiniScript::LINE_FIRST;
										for (auto i = 0; i < scriptCode.size(); i++) {
											//
											currentLineIdx = lineIdx;

											// try to get next statement code
											auto statementCode = miniScript->getNextStatement(scriptCode, i, lineIdx);
											//
											functionScriptCode+= miniScript->doStatementPreProcessing(statementCode, statement) + "\n";
										}
										//
										functionScriptCode+= "\n";
										functionScriptCode+= string() + "end" + "\n";
										// store it to be parsed later
										miniScript->deferredFunctionScriptCodes.push_back(functionScriptCode);
										//
										ScriptVariable mapValue;
										mapValue.setFunctionAssignment(functionName);
										variable.setMapEntry(string(mapKey), mapValue);
									} else {
										// map/set
										auto mapValue = initializeMapSet(mapValueStringView, miniScript, statement);
										variable.setMapEntry(string(mapKey), mapValue);
									}
								}
							}
							//
							mapValueStart = string::npos;
							mapValueEnd = string::npos;
						}
					}
					//
					parseMode = PARSEMODE_KEY;
				}
			} else
			// array initializer
			if (c == '[' && curlyBracketCount == 1 && bracketCount == 0) {
				// we have a inner array initializer, mark it
				if (squareBracketCount == 0) mapValueStart = i;
				// increase square bracket count
				squareBracketCount++;
			} else
			// end of array initializer
			if (c == ']' && curlyBracketCount == 1 && bracketCount == 0) {
				squareBracketCount--;
				// otherwise push inner array initializer
				if (squareBracketCount == 0) {
					// parse and insert into map
					string_view mapKey;

					// quoted map key
					if (quotedMapKeyStart != string::npos) {
						quotedMapKeyStart++;
						auto mapKeyLength = quotedMapKeyEnd - quotedMapKeyStart;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[quotedMapKeyStart], mapKeyLength));
					} else
					// unquoted map key
					if (mapKeyStart != string::npos) {
						auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
					}
					// validate map key
					if (mapKey.empty() == true || viewIsKey(mapKey) == false) {
						Console::println(miniScript->getStatementInformation(statement) + ": invalid key name, ignoring map entry: " + string(mapKey));
					} else {
						//
						quotedMapKeyStart = string::npos;
						quotedMapKeyEnd = string::npos;
						mapKeyStart = string::npos;
						mapKeyEnd = string::npos;
						inlineFunctionSignatureStart = string::npos;

						// map value
						if (mapValueStart != string::npos) {
							mapValueEnd = i;
							auto mapValueLength = mapValueEnd - mapValueStart + 1;
							if (mapValueLength > 0) {
								auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
								if (mapValueStringView.empty() == false) {
									auto mapValue = initializeArray(mapValueStringView, miniScript, statement);
									variable.setMapEntry(string(mapKey), mapValue);
								}
							}
							//
							mapValueStart = string::npos;
							mapValueEnd = string::npos;
						}
					}
					//
					parseMode = PARSEMODE_KEY;
				}
			} else
			// set up map key  start
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c != ' ' && c != '\t' && c != '\n') {
				if (parseMode == PARSEMODE_KEY && mapKeyStart == string::npos && quotedMapKeyStart == string::npos) {
					mapKeyStart = i;
				} else
				if (parseMode == PARSEMODE_VALUE && mapValueStart == string::npos && quotedMapValueStart == string::npos) {
					mapValueStart = i;
				}
			}
		}
		//
		lc = c;
	}
	// convert to set if no values given
	if (hasValues == false) {
		ScriptVariable setVariable;
		setVariable.setType(TYPE_SET);
		const auto& mapValueReference = variable.getMapValueReference();
		for (const auto& [mapVariableKey, mapVariableValue]: mapValueReference) {
			setVariable.insertSetKey(mapVariableKey);
		}
		variable = setVariable;
	}
	//
	auto initalizer = make_unique<MiniScript::ScriptVariable::Initializer>(string(initializerString), statement, nullptr);
	variable.initializer->copy(initalizer.get());
	//
	return variable;
}

void MiniScript::ScriptVariable::setFunctionCallStatement(const string& initializerStatement, MiniScript* miniScript, const ScriptStatement& statement) {
	setType(TYPE_FUNCTION_CALL);
	getStringValueReference() = initializerStatement;
	//
	ScriptStatement initializerScriptStatement(
		statement.line,
		statement.statementIdx,
		initializerStatement,
		initializerStatement,
		MiniScript::STATEMENTIDX_NONE
	);
	//
	string_view methodName;
	vector<string_view> arguments;
	string accessObjectMemberStatement;
	ScriptSyntaxTreeNode* evaluateSyntaxTree = new ScriptSyntaxTreeNode();
	if (miniScript->parseScriptStatement(initializerStatement, methodName, arguments, initializerScriptStatement, accessObjectMemberStatement) == false) {
		//
	} else
	if (miniScript->createScriptStatementSyntaxTree(methodName, arguments, initializerScriptStatement, *evaluateSyntaxTree) == false) {
		//
	} else {
		getInitializerReference() = new Initializer(initializerStatement, statement, evaluateSyntaxTree);
	}
}

inline MiniScript::ScriptVariable* MiniScript::getVariableIntern(const string& name, const string& callerMethod, ScriptVariable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const ScriptStatement* statement, bool expectVariable, bool global) {
	//
	if (isVariableAccess(name) == false) {
		if (statement != nullptr) {
			Console::println(getStatementInformation(*statement) + ": variable: '" + name + "': variable names must start with an $");
		} else {
			Console::println(scriptFileName + ": variable: '" + name + "': variable names must start with an $");
		}
		return nullptr;
	}
	// get root variable
	key.clear();
	// no array idx by default
	arrayIdx = ARRAYIDX_NONE;
	// determine left and right access operator position if there are any
	auto accessOperatorLeftIdx = string::npos;
	auto accessOperatorRightIdx = string::npos;
	if (getVariableAccessOperatorLeftRightIndices(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, statement) == false) {
		return nullptr;
	}
	// access operator, if we have any, evaluate the array index
	auto haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
	auto extractedVariableName = haveAccessOperator == true?StringTools::substring(name, 0, accessOperatorLeftIdx):string();
	if (haveAccessOperator == true &&
		evaluateAccess(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, statement) == false) {
		return nullptr;
	}
	// retrieve variable from function script state
	ScriptVariable* variablePtr = nullptr;
	if (global == false) {
		const auto& scriptState = getScriptState();
		auto scriptVariableIt = scriptState.variables.find(extractedVariableName.empty() == false?extractedVariableName:name);
		if (scriptVariableIt == scriptState.variables.end()) {
			if (isFunctionRunning() == false) {
				if (expectVariable == true) {
					if (statement != nullptr) {
						Console::println(getStatementInformation(*statement) + ": variable: '" + name + "' does not exist");
					} else {
						Console::println(scriptFileName + ": variable: '" + name + "' does not exist");
					}
				}
				return nullptr;
			}
		} else {
			variablePtr = scriptVariableIt->second;
		}
	}
	// if no success try to retrieve variable from root script state, but only when expecting variable aka reading variable
	if (global == true || (expectVariable == true && variablePtr == nullptr)) {
		const auto& scriptState = getRootScriptState();
		auto scriptVariableIt = scriptState.variables.find(extractedVariableName.empty() == false?extractedVariableName:name);
		if (scriptVariableIt == scriptState.variables.end()) {
			if (expectVariable == true) {
				if (statement != nullptr) {
					Console::println(getStatementInformation(*statement) + ": variable: '" + name + "' does not exist");
				} else {
					Console::println(scriptFileName + ": variable: '" + name + "' does not exist");
				}
			}
			return nullptr;
		} else {
			variablePtr = scriptVariableIt->second;
		}
	}
	//
	if (variablePtr == nullptr) return nullptr;
	// get pointer to children variable
	if (haveAccessOperator == false) {
		//
		return variablePtr;
	} else {
		// resolve first parsed access pattern and repeat until resolved
		while (haveAccessOperator == true) {
			// map key access
			if (key.empty() == false) {
				if (variablePtr->getType() == TYPE_MAP) {
					//
					auto& mapValueReference = variablePtr->getMapValueReference();
					// key
					auto mapIt = mapValueReference.find(key);
					if (mapIt != mapValueReference.end()) {
						//
						parentVariable = variablePtr;
						//
						variablePtr = mapIt->second;
					} else {
						if (expectVariable == true) {
							if (statement != nullptr) {
								Console::println(getStatementInformation(*statement) + ": variable: '" + name + "': key not found: '" + key + "'");
							} else {
								Console::println(scriptFileName + "': variable: '" + name + "': key not found: '" + key + "'");
							}
						}
						// we have our parent
						parentVariable = variablePtr;
						//
						return nullptr;
					}
				} else
				if (variablePtr->getType() == TYPE_SET) {
					//
					auto& setValueReference = variablePtr->getSetValueReference();
					// key
					auto setIt = setValueReference.find(key);
					if (setIt != setValueReference.end()) {
						//
						setAccessBool = SETACCESSBOOL_TRUE;
						//
						parentVariable = variablePtr;
					} else {
						//
						setAccessBool = SETACCESSBOOL_FALSE;
						// we have our parent
						parentVariable = variablePtr;
						//
						return nullptr;
					}
				} else {
					if (statement != nullptr) {
						Console::println(getStatementInformation(*statement) + ": variable: '" + name + "': map/set access operator, but variable is not of type map/set");
					} else {
						Console::println(scriptFileName + ": variable: '" + name + "': map/set access operator, but variable is not of type map/set");
					}
					return nullptr;
				}
			} else {
				if (variablePtr->getType() != TYPE_ARRAY) {
					if (statement != nullptr) {
						Console::println(getStatementInformation(*statement) + ": variable: '" + name + "': array access operator, but variable is not of type array");
					} else {
						Console::println(scriptFileName + ": variable: '" + name + "': array access operator, but variable is not of type array");
					}
					return nullptr;
				}
				auto& arrayValueReference = variablePtr->getArrayValueReference();
				// otherwise array
				if (arrayIdx == ARRAYIDX_ADD) {
					// we have our parent
					parentVariable = variablePtr;
					//
					return nullptr;
				} else
				if (arrayIdx >= 0 && arrayIdx < arrayValueReference.size()) {
					//
					parentVariable = variablePtr;
					//
					variablePtr = arrayValueReference[arrayIdx];
				} else {
					if (statement != nullptr) {
						Console::println(getStatementInformation(*statement) + ": variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " < " + to_string(arrayValueReference.size()));
					} else {
						Console::println(scriptFileName + ": variable: '" + name + "': index out of bounds: 0 <= " + to_string(arrayIdx) + " <= " + to_string(arrayValueReference.size()));
					}
					return nullptr;
				}
			}

			//
			auto accessOperatorStartIdx = accessOperatorRightIdx;
			accessOperatorLeftIdx = string::npos;
			accessOperatorRightIdx = string::npos;
			if (getVariableAccessOperatorLeftRightIndices(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, statement, accessOperatorStartIdx) == false) {
				// fail
				return nullptr;
			}

			// do we have a next array access next to previous one?
			haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
			if (haveAccessOperator == false) {
				return variablePtr;
			} else {
				// yep, evaluate it
				if (evaluateAccess(name, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, statement) == false) {
					return nullptr;
				}
			}
		}
		//
		return variablePtr;
	}
}

inline bool MiniScript::evaluateInternal(const string& statement, const string& executableStatement, ScriptVariable& returnValue, bool pushOwnScriptState) {
	ScriptStatement evaluateStatement(
		LINE_NONE,
		0,
		"internal.script.evaluate(" + statement + ")",
		"internal.script.evaluate(" + executableStatement + ")",
		STATEMENTIDX_NONE
	);
	auto scriptEvaluateStatement = "internal.script.evaluate(" + executableStatement + ")";
	//
	string_view methodName;
	vector<string_view> arguments;
	string accessObjectMemberStatement;
	ScriptSyntaxTreeNode evaluateSyntaxTree;
	if (parseScriptStatement(scriptEvaluateStatement, methodName, arguments, evaluateStatement, accessObjectMemberStatement) == false) {
		return false;
	} else
	if (createScriptStatementSyntaxTree(methodName, arguments, evaluateStatement, evaluateSyntaxTree) == false) {
		return false;
	} else {
		//
		if (pushOwnScriptState == true) {
			pushScriptState();
			resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NEXT_STATEMENT);
		}
		getScriptState().running = true;
		//
		returnValue = executeScriptStatement(
			evaluateSyntaxTree,
			evaluateStatement
		);
		//
		if (pushOwnScriptState == true) popScriptState();
		//
		return true;
	}
}

inline const MiniScript::ScriptVariable MiniScript::initializeVariable(const ScriptVariable& variable) {
	switch (variable.type) {
		case TYPE_ARRAY:
			{
				ScriptVariable arrayVariable;
				//
				arrayVariable.setType(TYPE_ARRAY);
				auto arrayPointer = variable.getArrayPointer();
				if (arrayPointer == nullptr) break;
				for (const auto arrayEntry: *arrayPointer) {
					arrayVariable.pushArrayEntry(initializeVariable(*arrayEntry));
				}
				//
				return arrayVariable;
			}
		case TYPE_MAP:
			{
				ScriptVariable mapVariable;
				//
				auto mapPointer = variable.getMapPointer();
				if (mapPointer == nullptr) break;
				for (const auto& [mapKey, mapValue]: *mapPointer) {
					mapVariable.setMapEntry(mapKey, initializeVariable(*mapValue));
				}
				//
				return mapVariable;
			}
		case TYPE_FUNCTION_CALL:
			{
				return executeScriptStatement(
					*variable.getInitializer()->getSyntaxTree(),
					variable.getInitializer()->getStatement()
				);
			}
		default: break;
	}
	//
	return variable;
}

inline bool MiniScript::viewIsKey(const string_view& candidate) {
	if (candidate.size() == 0) return false;
	if (candidate[0] == '$') return false;
	for (auto i = 0; i < candidate.size(); i++) {
		auto c = candidate[i];
		if (Character::isAlphaNumeric(c) == false && c != '_') return false;
	}
	return true;
}

inline bool MiniScript::getVariableAccessOperatorLeftRightIndices(const string& name, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const ScriptStatement* statement, int startIdx) {
	accessOperatorLeftIdx = string::npos;
	accessOperatorRightIdx = string::npos;
	auto haveKey = false;
	auto squareBracketsCount = 0;
	// improve me!
	if (startIdx > 0) {
		haveKey = name[startIdx - 1] == '.';
		if (haveKey == true) accessOperatorLeftIdx = startIdx - 1;
	}
	for (auto i = startIdx; i < name.length(); i++) {
		auto c = name[i];
		if (haveKey == true) {
			if (c == '.') {
				//
				accessOperatorRightIdx = i;
				//
				return true;
			} else
			if (c == '[') {
				//
				accessOperatorRightIdx = i;
				//
				return true;
			}
			if (c == ']') {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': unexpected char: ']'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: ']'");
				}
				return false;
			}
		} else
		if (c == '.' && squareBracketsCount == 0) {
			haveKey = true;
			accessOperatorLeftIdx = i;
		} else
		if (c == '[') {
			if (squareBracketsCount == 0) accessOperatorLeftIdx = i;
			squareBracketsCount++;
		} else
		if (c == ']') {
			squareBracketsCount--;
			if (squareBracketsCount == 0) {
				//
				accessOperatorRightIdx = i + 1;
				//
				return true;
			} else
			if (squareBracketsCount < 0) {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': unexpected char: ']'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': variable: '" + name + "': unexpected char: ']'");
				}
				return false;
			}
		}
	}
	//
	if (haveKey == true) accessOperatorRightIdx = name.size();
	//
	return true;
}

inline bool MiniScript::evaluateAccess(const string& name, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const ScriptStatement* statement) {
	key.clear();
	arrayIdx = ARRAYIDX_NONE;
	// check for dot access
	if (name.data()[arrayAccessOperatorLeftIdx] == '.') {
		key = string(StringTools::viewTrim(string_view(&name.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 1)));
		return true;
	}
	// evaluate array index
	auto arrayIdxExpressionStringView = StringTools::viewTrim(string_view(&name.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 2));
	if (arrayIdxExpressionStringView.empty() == false) {
		// integer first for performance
		if (Integer::viewIs(arrayIdxExpressionStringView) == true) {
			arrayIdx = Integer::viewParse(arrayIdxExpressionStringView);
		} else {
			// TODO: as evaluate statement we also might need the expression that had not yet a preprocessor run for error messages and such
			ScriptVariable statementReturnValue;
			auto evaluateStatement = string(arrayIdxExpressionStringView);
			if (evaluateInternal(evaluateStatement, evaluateStatement, statementReturnValue, false) == false || statementReturnValue.getIntegerValue(arrayIdx, false) == false) {
				if (statement != nullptr) {
					Console::println("MiniScript::" + callerMethod + "(): " + getStatementInformation(*statement) + ": variable: '" + name + "': failed to evaluate expression: '" + string(arrayIdxExpressionStringView) + "'");
				} else {
					Console::println("MiniScript::" + callerMethod + "(): '" + scriptFileName + "': variable: '" + name + "': failed to evaluate expression: '" + string(arrayIdxExpressionStringView) + "'");
				}
				//
				return false;
			}
		}
	} else {
		arrayIdx = ARRAYIDX_ADD;
	}
	//
	return true;
}
