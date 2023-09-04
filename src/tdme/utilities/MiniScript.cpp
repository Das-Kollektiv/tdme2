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

#include <ext/rapidjson/document.h>
#include <ext/rapidjson/stringbuffer.h>
#include <ext/rapidjson/writer.h>

using std::find;
using std::initializer_list;
using std::make_unique;
using std::map;
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

using rapidjson::Document;
using rapidjson::StringBuffer;
using rapidjson::Value;
using rapidjson::Writer;

string MiniScript::OPERATOR_CHARS = "!*/%+-<>&|=";
string MiniScript::METHOD_SCRIPTCALL = "script.call";
string MiniScript::METHOD_ENABLENAMEDCONDITION = "script.enableNamedCondition";
string MiniScript::METHOD_DISABLENAMEDCONDITION = "script.disableNamedCondition";

vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ALL = {};
vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ENGINE = { "initializeEngine", "updateEngine" };
vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_LOGIC = { "initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed" };
vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTIONS_ENGINELOGIC = {
	// engine
	"initializeEngine", "updateEngine",
	// logic
	"initializeLogic", "updateLogic", "onLogicAdded", "onLogicsProcessed"
};
vector<string> MiniScript::ScriptMethod::CONTEXTFUNCTION_GUI = {};

MiniScript* MiniScript::loadScript(const string& pathName, const string& fileName) {
	// we need to detect MiniScript variant
	vector<string> scriptAsStringArray;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptAsStringArray);
	} catch (Exception& exception) {
		Console::println("MiniScript::loadScript(): " + pathName + "/" + fileName + ": An error occurred: " + string(exception.what()));
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

bool MiniScript::parseScriptStatement(const string_view& statement, string_view& methodName, vector<string_view>& arguments) {
	if (VERBOSE == true) Console::println("MiniScript::parseScriptStatement(): '" + scriptFileName + "': '" + string(statement) + "'");
	auto bracketCount = 0;
	auto quote = false;
	auto methodStart = string::npos;
	auto methodEnd = string::npos;
	auto argumentStart = string::npos;
	auto argumentEnd = string::npos;
	auto quotedArgumentStart = string::npos;
	auto quotedArgumentEnd = string::npos;
	for (auto i = 0; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"') {
			if (bracketCount == 1) {
				if (quote == false) {
					quotedArgumentStart = i;
				} else {
					quotedArgumentEnd = i;
				}
			} else {
				if (quote == false) {
					if (argumentStart == string::npos) {
						argumentStart = i;
					}
				} else {
					argumentEnd = i;
				}
			}
			quote = quote == false?true:false;
		} else
		if (quote == true) {
			if (bracketCount == 1) {
				quotedArgumentEnd = i;
			} else {
				if (argumentStart == string::npos) {
					argumentStart = i;
				} else {
					argumentEnd = i;
				}
			}
		} else
		if (quote == false) {
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
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&statement[quotedArgumentStart], argumentLength)));
						quotedArgumentStart = string::npos;
						quotedArgumentEnd = string::npos;
					} else
					if (argumentStart != string::npos) {
						if (argumentEnd == string::npos) argumentEnd = i - 1;
						auto argumentLength = argumentEnd - argumentStart + 1;
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&statement[argumentStart], argumentLength)));
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
			if (c == ',') {
				if (bracketCount == 1) {
					if (quotedArgumentStart != string::npos) {
						if (quotedArgumentEnd == string::npos) quotedArgumentEnd = i - 1;
						auto argumentLength = quotedArgumentEnd - quotedArgumentStart + 1;
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&statement[quotedArgumentStart], argumentLength)));
						quotedArgumentStart = string::npos;
						quotedArgumentEnd = string::npos;
					} else
					if (argumentStart != string::npos) {
						if (argumentEnd == string::npos) argumentEnd = i - 1;
						auto argumentLength = argumentEnd - argumentStart + 1;
						if (argumentLength > 0) arguments.push_back(StringTools::viewTrim(string_view(&statement[argumentStart], argumentEnd - argumentStart + 1)));
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
	if (methodStart != string::npos && methodEnd != string::npos) {
		methodName = StringTools::viewTrim(string_view(&statement[methodStart], methodEnd - methodStart + 1));
	}
	if (VERBOSE == true) {
		Console::print("MiniScript::parseScriptStatement(): '" + scriptFileName + "': method: '" + string(methodName) + "', arguments: ");
		int variableIdx = 0;
		for (const auto& argument: arguments) {
			if (variableIdx > 0) Console::print(", ");
			Console::print("'" + string(argument) + "'");
			variableIdx++;
		}
		Console::println();
	}
	if (bracketCount != 0) {
		Console::println("MiniScript::parseScriptStatement(): '" + scriptFileName + "': '" + string(statement) + "': unbalanced bracket count: " + to_string(bracketCount) + " still open");
		//
		parseErrors.push_back(string(statement) + ": unbalanced bracket count: " + to_string(bracketCount) + " still open");
		//
		return false;
	}
	return true;
}

MiniScript::ScriptVariable MiniScript::executeScriptStatement(const ScriptSyntaxTreeNode& syntaxTree, const ScriptStatement& statement) {
	if (VERBOSE == true) Console::println("MiniScript::executeScriptStatement(): " + getStatementInformation(statement) + "': " + syntaxTree.value.getValueString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	// return on literal or empty syntaxTree
	if (syntaxTree.type != ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD && syntaxTree.type != ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION) {
		return syntaxTree.value;
	}
	//
	vector<ScriptVariable> argumentValues;
	ScriptVariable returnValue;
	// construct argument values
	for (const auto& argument: syntaxTree.arguments) {
		switch (argument.type) {
			case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
				{
					argumentValues.push_back(argument.value);
					break;
				}
			case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
				{
					argumentValues.push_back(executeScriptStatement(argument, statement));
					break;
				}
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
		Console::println("MiniScript::executeScriptStatement(): '" + getStatementInformation(statement) + ": " + syntaxTree.value.getValueString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	}
	// try first user functions
	if (syntaxTree.method == nullptr) {
		auto method = syntaxTree.value.getValueString();
		auto scriptFunctionsIt = scriptFunctions.find(method);
		if (scriptFunctionsIt != scriptFunctions.end()) {
			auto scriptIdx = scriptFunctionsIt->second;
			// call
			span argumentValuesSpan(argumentValues);
			call(scriptIdx, argumentValuesSpan, returnValue);
			// assign back arguments
			auto argumentIdx = 0;
			for (const auto& argument: scripts[scriptIdx].arguments) {
				//
				if (argumentIdx == argumentValues.size()) {
					break;
				}
				//
				if (argument.assignBack == true) {
					const auto& assignBackArgument = syntaxTree.arguments[argumentIdx];
					if (assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
						assignBackArgument.value.getValueString() == "getVariable" &&
						assignBackArgument.arguments.empty() == false) {
						//
						auto variableName = assignBackArgument.arguments[0].value.getValueString();
						if (StringTools::startsWith(variableName, "$") == true) {
							setVariable(variableName, argumentValues[argumentIdx], &statement);
						} else {
							Console::println(getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
						}
					} else {
						Console::println(
							getStatementInformation(statement) +
							": Can not assign back argument value @ " +
							to_string(argumentIdx) +
							" to variable '" +
							assignBackArgument.value.getValueString() +
							(
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
									?"(...)"
									:""
							) +
							"'"
						);
					}
				}
				argumentIdx++;
			}
			//
			return returnValue;
		} else {
			Console::println(getStatementInformation(statement) + ": unknown function '" + string(syntaxTree.value.getValueString()) + "'");
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
									argumentValues[argumentIdx].type == TYPE_VECTOR2;
							break;
						}
					case TYPE_VECTOR3:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_VECTOR3;
							break;
						}
					case TYPE_VECTOR4:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_VECTOR4;
							break;
						}
					case TYPE_QUATERNION:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_QUATERNION;
							break;
						}
					case TYPE_MATRIX3x3:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_MATRIX3x3;
							break;
						}
					case TYPE_MATRIX4x4:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_MATRIX4x4;
							break;
						}
					case TYPE_TRANSFORM:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_TRANSFORM;
							break;
						}
					case TYPE_ARRAY:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_ARRAY;
							break;
						}
					case TYPE_MAP:
						{
							argumentOk =
								argumentIdx < 0 || argumentIdx >= argumentValues.size()?
									argumentType.optional:
									argumentValues[argumentIdx].type == TYPE_MAP;
							break;
						}
					case TYPE_PSEUDO_NUMBER:
						{
							float floatValue;
							argumentOk = getFloatValue(argumentValues, argumentIdx, floatValue, argumentType.optional);
							break;
						}
				}
				if (argumentOk == false) {
					Console::println(
						getStatementInformation(statement) +
						": method '" + string(syntaxTree.value.getValueString()) + "'" +
						": argument value @ " + to_string(argumentIdx) + ": expected " + ScriptVariable::getTypeAsString(argumentType.type) + ", but got: " + (argumentIdx < argumentValues.size()?argumentValues[argumentIdx].getAsString():"nothing"));
				}
				argumentIdx++;
			}
			if (scriptMethod->isVariadic() == false && argumentValues.size() > scriptMethod->getArgumentTypes().size()) {
				Console::println(
					getStatementInformation(statement) +
					": method '" + string(syntaxTree.value.getValueString()) + "'" +
					": too many arguments: expected: " + to_string(scriptMethod->getArgumentTypes().size()) + ", got " + to_string(argumentValues.size()));
			}
		}
		// execute method
		span argumentValuesSpan(argumentValues);
		scriptMethod->executeMethod(argumentValuesSpan, returnValue, statement);
		// assign back arguments
		{
			auto argumentIdx = 0;
			for (const auto& argumentType: scriptMethod->getArgumentTypes()) {
				//
				if (argumentIdx == argumentValues.size()) {
					break;
				}
				//
				if (argumentType.assignBack == true) {
					const auto& assignBackArgument = syntaxTree.arguments[argumentIdx];
					if (assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
						assignBackArgument.value.getValueString() == "getVariable" &&
						assignBackArgument.arguments.empty() == false) {
						//
						auto variableName = assignBackArgument.arguments[0].value.getValueString();
						if (StringTools::startsWith(variableName, "$") == true) {
							setVariable(variableName, argumentValues[argumentIdx], &statement);
						} else {
							Console::println(getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
						}
					} else {
						Console::println(
							getStatementInformation(statement) +
							": Can not assign back argument value @ " +
							to_string(argumentIdx) +
							" to variable '" +
							assignBackArgument.value.getValueString() +
							(
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
									?"(...)"
									:""
							) +
							"'"
						);
					}

				}
				argumentIdx++;
			}
		}
		// check return type
		if (MiniScript::ScriptVariable::isExpectedType(returnValue.getType(), scriptMethod->getReturnValueType()) == false) {
			Console::println(
				getStatementInformation(statement) +
				": method '" + string(syntaxTree.value.getValueString()) + "'" +
				": return value: expected " + ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType()) + ", but got: " + ScriptVariable::getReturnTypeAsString(returnValue.getType()));
		}
		//
		return returnValue;
	}
	//
	return returnValue;
}

bool MiniScript::createScriptStatementSyntaxTree(const string_view& methodName, const vector<string_view>& arguments, const ScriptStatement& statement, ScriptSyntaxTreeNode& syntaxTree) {
	if (VERBOSE == true) Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": " + string(methodName) + "(" + getArgumentsAsString(arguments) + ")");
	// arguments
	for (const auto& argument: arguments) {
		// variable
		if (StringTools::viewStartsWith(argument, "$") == true) {
			//
			ScriptVariable value;
			value.setValue(string(argument));

			// look up getVariable method
			string methodName = "getVariable";
			ScriptMethod* method = nullptr;
			{
				auto scriptMethodsIt = scriptMethods.find(methodName);
				if (scriptMethodsIt != scriptMethods.end()) {
					method = scriptMethodsIt->second;
				} else {
					Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": unknown method '" + methodName + "'");
					//
					parseErrors.push_back(getStatementInformation(statement) + ": unknown method '" + methodName + "'");
					//
					return false;
				}
			}

			//
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
			argument.find('(') != string::npos &&
			argument.find(')') != string::npos) {
			// method call
			string_view subMethodName;
			vector<string_view> subArguments;
			if (parseScriptStatement(argument, subMethodName, subArguments) == true) {
				ScriptSyntaxTreeNode subSyntaxTree;
				if (createScriptStatementSyntaxTree(subMethodName, subArguments, statement, subSyntaxTree) == false) {
					Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": '" + string(argument) + "': failed to create syntax tree for statement");
					//
					return false;
				}
				syntaxTree.arguments.push_back(subSyntaxTree);
			} else {
				Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": '" + string(argument) + "': : failed to parse statement");
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
				value.setImplicitTypedValueFromStringView(argument);
				//
				syntaxTree.arguments.emplace_back(
					ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
					value,
					nullptr,
					initializer_list<ScriptSyntaxTreeNode>{}
				);
			}
		}
	}
	// try first user functions
	{
		auto functionString = string(methodName);
		auto scriptFunctionsIt = scriptFunctions.find(functionString);
		if (scriptFunctionsIt != scriptFunctions.end()) {
			syntaxTree.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION;
			syntaxTree.value = functionString;
			//
			return true;
		}
	}
	// try methods next
	{
		string methodString = string(methodName);
		auto scriptMethodsIt = scriptMethods.find(methodString);
		if (scriptMethodsIt != scriptMethods.end()) {
			syntaxTree.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
			syntaxTree.value = methodString;
			syntaxTree.method = scriptMethodsIt->second;
			//
			return true;
		} else {
			Console::println("MiniScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": unknown function/method '" + string(methodString) + "'");
			//
			parseErrors.push_back(getStatementInformation(statement) + ": unknown function/method '" + string(methodString) + "'");
			//
			return false;
		}
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
				validateCallable(syntaxTreeNode.value.getValueString());
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
				validateContextFunctions(syntaxTreeNode.value.getValueString(), functionStack	);
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
	/*
	 TODO:
	if (scriptState.scriptIdx == scriptIdxToStart) {
		Console::println("MiniScript::emit(): '" + scriptFileName + "': script already running: " + condition);
		return;
	}
	*/
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
	vector<string> scriptLines;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptLines);
	} catch (FileSystemException& fse)	{
		Console::println("MiniScript::loadScript(): " + pathName + "/" + fileName + ": an error occurred: " + fse.what());
		//
		scriptValid = true;
		//
		parseErrors.push_back("An error occurred: " + string(fse.what()));
		//
		return;
	}

	//
	{
		string scriptAsString;
		for (const auto& scriptLine: scriptLines) scriptAsString+= scriptLine + "\n";
		auto scriptHash = SHA256::encode(scriptAsString);
		if (native == true) {
			if (scriptHash == nativeHash) {
				scripts = nativeScripts;
				registerStateMachineStates();
				registerMethods();
				startScript();
				return;
			} else {
				Console::println("MiniScript::loadScript(): " + pathName + "/" + fileName + ": Script has changed. Script will be run in interpreted mode. Retranspile and recompile your script if you want to run it natively.");
				native = false;
			}
		}
		nativeHash = scriptHash;
	}

	//
	registerStateMachineStates();
	registerMethods();

	//
	auto haveScript = false;
	auto line = LINEIDX_FIRST;
	auto statementIdx = STATEMENTIDX_FIRST;
	enum GotoStatementType { GOTOSTATEMENTTYPE_FOR, GOTOSTATEMENTTYPE_IF, GOTOSTATEMENTTYPE_ELSE, GOTOSTATEMENTTYPE_ELSEIF };
	struct GotoStatementStruct {
		GotoStatementType type;
		int statementIdx;
	};
	stack<GotoStatementStruct> gotoStatementStack;
	for (auto scriptLine: scriptLines) {
		scriptLine = StringTools::trim(scriptLine);
		if (StringTools::startsWith(scriptLine, "#") == true || scriptLine.empty() == true) {
			line++;
			continue;
		}
		// script type
		auto callable = false;
		auto scriptType = Script::SCRIPTTYPE_NONE;
		if (StringTools::startsWith(scriptLine, "function:") == true) scriptType = Script::SCRIPTTYPE_FUNCTION; else
		if (StringTools::startsWith(scriptLine, "on:") == true) scriptType = Script::SCRIPTTYPE_ON; else
		if (StringTools::startsWith(scriptLine, "on-enabled:") == true) scriptType = Script::SCRIPTTYPE_ONENABLED; else
		if (StringTools::startsWith(scriptLine, "callable:") == true) {
			callable = true;
			scriptType = Script::SCRIPTTYPE_FUNCTION;
		}
		// no script yet
		if (haveScript == false) {
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
						StringTools::trim(StringTools::substring(scriptLine, string("callable:").size())):
						StringTools::trim(StringTools::substring(scriptLine, string("function:").size()));
				} else
				if (scriptType == Script::SCRIPTTYPE_ON)
					statement = StringTools::trim(StringTools::substring(scriptLine, string("on:").size())); else
				if (scriptType == Script::SCRIPTTYPE_ONENABLED)
					statement = StringTools::trim(StringTools::substring(scriptLine, string("on-enabled:").size()));
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
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + "': @" + to_string(line) + ": 'function:': unbalanced bracket count");
							//
							parseErrors.push_back(to_string(line) + ": 'function:': unbalanced bracket count");
							//
							scriptValid = false;
						} else
						if (rightBracketIdx == string::npos) {
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + "': @" + to_string(line) + ": 'function:': unbalanced bracket count");
							//
							parseErrors.push_back(to_string(line) + ": 'function:': unbalanced bracket count");
							//
							scriptValid = false;
						} else {
							auto argumentNamesString = StringTools::trim(StringTools::substring(statement, leftBracketIdx + 1, rightBracketIdx));
							auto argumentNamesTokenized = StringTools::tokenize(argumentNamesString, ",");
							statement = StringTools::substring(statement, 0, leftBracketIdx);
							for (const auto& argumentName: argumentNamesTokenized) {
								auto argumentNameTrimmed = StringTools::trim(argumentName);
								auto assignBack = false;
								if (StringTools::startsWith(argumentNameTrimmed, "=") == true) {
									assignBack = true;
									argumentNameTrimmed = StringTools::trim(StringTools::substring(argumentNameTrimmed, 1));
								}
								if (StringTools::regexMatch(argumentNameTrimmed, "\\$[a-zA-Z0-9]+") == true) {
									arguments.emplace_back(
										argumentNameTrimmed,
										assignBack
									);
								} else {
									Console::println("MiniScript::MiniScript(): '" + scriptFileName + "': @" + to_string(line) + ": 'function:': invalid argument name: '" + argumentNameTrimmed + "'");
									//
									parseErrors.push_back(to_string(line) + ": 'function:': invalid argument name: '" + argumentNameTrimmed + "'");
									//
									scriptValid = false;
								}
							}
						}

					}
				}
				auto conditionOrNameExecutable = doStatementPreProcessing(StringTools::trim(statement));
				auto conditionOrName = StringTools::trim(statement);
				auto emitCondition = StringTools::regexMatch(conditionOrName, "[a-zA-Z0-9]+");
				statementIdx = STATEMENTIDX_FIRST;
				// add to user functions
				if (scriptType == Script::SCRIPTTYPE_FUNCTION) {
					scriptFunctions[conditionOrName] = scripts.size();
				}

				// push to scripts
				scripts.emplace_back(
					scriptType,
					line,
					conditionOrName,
					conditionOrNameExecutable,
					ScriptStatement(line, statementIdx, conditionOrName, conditionOrNameExecutable, STATEMENTIDX_NONE),
					ScriptSyntaxTreeNode(),
					name,
					emitCondition,
					initializer_list<ScriptStatement>{},
					initializer_list<ScriptSyntaxTreeNode>{},
					callable,
					arguments
				);
			} else {
				Console::println("MiniScript::MiniScript(): '" + scriptFileName + "': @" + to_string(line) + ": expecting 'on:', 'on-enabled:', 'on-function:' script condition");
				//
				parseErrors.push_back(to_string(line) + ": expecting 'on:', 'on-enabled:', 'on-function:' script condition");
				//
				scriptValid = false;
			}
		} else {
			if (StringTools::startsWith(scriptLine, "on:") == true) {
				Console::println("MiniScript::loadScript(): '" + scriptFileName + "': @" + to_string(line) + ": unbalanced forXXX/if/elseif/else/end");
				//
				parseErrors.push_back(to_string(line) + ": unbalanced forXXX/if/elseif/else/end");
				//
				scriptValid = false;
			} else
			if (scriptLine == "end") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_FOR:
							{
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, gotoStatementStackElement.statementIdx);
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
							}
							break;
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSE:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
							}
							break;
					}
				} else{
					scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
					haveScript = false;
				}
			} else
			if (scriptLine == "else") {
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, scriptLine, STATEMENTIDX_NONE);
							}
							break;
						default:
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": else without if/elseif");
							//
							parseErrors.push_back(to_string(line) + ": else without if/elseif");
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
					Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": else without if");
					//
					parseErrors.push_back(to_string(line) + ": else without if");
					//
					scriptValid = false;
				}
			} else
			if (StringTools::regexMatch(scriptLine, "^elseif[\\s]*\\(.*\\)$") == true) {
				auto executableStatement = doStatementPreProcessing(scriptLine);
				if (gotoStatementStack.empty() == false) {
					auto gotoStatementStackElement = gotoStatementStack.top();
					gotoStatementStack.pop();
					switch(gotoStatementStackElement.type) {
						case GOTOSTATEMENTTYPE_IF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, executableStatement, STATEMENTIDX_NONE);
							}
							break;
						case GOTOSTATEMENTTYPE_ELSEIF:
							{
								scripts[scripts.size() - 1].statements[gotoStatementStackElement.statementIdx].gotoStatementIdx = scripts[scripts.size() - 1].statements.size();
								scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, executableStatement, STATEMENTIDX_NONE);
							}
							break;
						default:
							Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": elseif without if");
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
					Console::println("MiniScript::MiniScript(): '" + scriptFileName + ": @" + to_string(line) + ": elseif without if");
					//
					parseErrors.push_back(to_string(line) + ": elseif without if");
					//
					scriptValid = false;
				}
			} else {
				auto executableStatement = doStatementPreProcessing(scriptLine);
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
				scripts[scripts.size() - 1].statements.emplace_back(line, statementIdx, scriptLine, executableStatement, STATEMENTIDX_NONE);
			}
			statementIdx++;
		}
		line++;
	}

	// check for unbalanced forXXX/if/elseif/else/end
	if (scriptValid == true && gotoStatementStack.empty() == false) {
		Console::println("MiniScript::loadScript(): '" + scriptFileName + ": unbalanced forXXX/if/elseif/else/end");
		//
		parseErrors.push_back("Unbalanced forXXX/if/elseif/else/end");
		//
		scriptValid = false;
		//
		return;
	}

	// create syntax tree
	for (auto& script: scripts) {
		// create syntax tree of executable condition if we have any
		if (script.emitCondition == false && script.executableCondition.empty() == false) {
			string_view method;
			vector<string_view> arguments;
			if (parseScriptStatement(script.executableCondition, method, arguments) == false) {
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
			if (parseScriptStatement(statement.executableStatement, methodName, arguments) == false) {
				//
				scriptValid = false;
			} else
			if (createScriptStatementSyntaxTree(methodName, arguments, statement, syntaxTree) == false) {
				//
				scriptValid = false;
			}
		}
	}

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
		Console::println("MiniScript::loadScript(): '" + scriptFileName + ": script needs to define an error condition");
		//
		parseErrors.push_back("Script needs to define an error condition");
		//
		scriptValid = false;
		//
		return;

	}

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
	for (const auto& [scriptVariableName, scriptVariable]: scriptState.variables) delete scriptVariable;
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

bool MiniScript::getNextStatementOperator(const string& statement, MiniScript::ScriptStatementOperator& nextOperator) {
	//
	auto bracketCount = 0;
	auto quote = false;
	for (auto i = 0; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"') {
			quote = quote == false?true:false;
		} else
		if (quote == false) {
			if (c == '(') {
				bracketCount++;
			} else
			if (c == ')') {
				bracketCount--;
			} else {
				for (int j = OPERATOR_NONE + 1; j < OPERATOR_MAX; j++) {
					auto priorizedOperator = static_cast<ScriptOperator>(j);
					string operatorCandidate;
					auto operatorString = getOperatorAsString(priorizedOperator);
					if (operatorString.size() == 1) operatorCandidate+= statement[i];
					if (operatorString.size() == 2 && i + 1 < statement.size()) {
						operatorCandidate+= statement[i];
						operatorCandidate+= statement[i + 1];
					}
					if (operatorString == operatorCandidate && (nextOperator.idx == OPERATORIDX_NONE || priorizedOperator > nextOperator.scriptOperator)) {
						if (i > 0 && isOperatorChar(statement[i - 1]) == true) {
							continue;
						}
						if (operatorString.size() == 2 && i + 2 < statement.size() && isOperatorChar(statement[i + 2]) == true) {
							continue;
						} else
						if (operatorString.size() == 1 && i + 1 < statement.size() && isOperatorChar(statement[i + 1]) == true) {
							continue;
						}
						if (priorizedOperator == OPERATOR_SUBTRACTION) {
							string leftArgumentBrackets;
							auto leftArgumentLeft = 0;
							auto leftArgument = findLeftArgument(statement, i - 1, leftArgumentLeft, leftArgumentBrackets);
							if (leftArgument.length() == 0) continue;
						}
						nextOperator.idx = i;
						nextOperator.scriptOperator = priorizedOperator;
					}
				}
			}
		}
	}

	//
	if (bracketCount > 0) {
		Console::println("MiniScript::getNextStatementOperator(): '" + scriptFileName + "': '" + statement + "': unbalanced bracket count: " + to_string(bracketCount) + " still open");
		return false;
	}
	//
	return nextOperator.idx != OPERATORIDX_NONE;
}

const string MiniScript::trimArgument(const string& argument) {
	auto processedArgument = StringTools::trim(argument);
	if ((StringTools::startsWith(processedArgument, "(") == true && StringTools::endsWith(processedArgument, ")")) == true ||
		(StringTools::startsWith(processedArgument, "[") == true && StringTools::endsWith(processedArgument, "]")) == true) {
		processedArgument = StringTools::substring(processedArgument, 1, processedArgument.size() - 1);
	}
	return processedArgument;
}

const string MiniScript::findRightArgument(const string statement, int position, int& length, string& brackets) {
	//
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto quote = false;
	string argument;
	length = 0;
	for (auto i = position; i < statement.size(); i++) {
		auto c = statement[i];
		if (c == '"') {
			quote = quote == false?true:false;
			argument+= c;
		} else
		if (quote == false) {
			if (c == '(') {
				bracketCount++;
				argument+= c;
			} else
			if (c == '[') {
				squareBracketCount++;
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
				if (squareBracketCount < 0) {
					brackets = "[]";
					return trimArgument(argument);
				}
				argument+= c;
			} else
			if (c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				argument+= c;
			} else {
				argument+= c;
			}
		} else
		if (quote == true) {
			argument+= c;
		}
		length++;
	}
	return trimArgument(argument);
}

const string MiniScript::findLeftArgument(const string statement, int position, int& length, string& brackets) {
	//
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto quote = false;
	string argument;
	length = 0;
	for (int i = position; i >= 0; i--) {
		auto c = statement[i];
		if (c == '"') {
			quote = quote == false?true:false;
			argument = c + argument;
		} else
		if (quote == false) {
			if (c == ')') {
				bracketCount++;
				argument = c + argument;
			} else
			if (c == ']') {
				squareBracketCount++;
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
			if (c == '[') {
				squareBracketCount--;
				if (squareBracketCount < 0) {
					brackets = "[]";
					return trimArgument(argument);
				}
				argument = c + argument;
			} else
			if (c == ',') {
				if (bracketCount == 0) return trimArgument(argument);
				argument = c + argument;
			} else {
				argument = c + argument;
			}
		} else
		if (quote == true) {
			argument = c + argument;
		}
		length++;
	}
	return trimArgument(argument);
}

const string MiniScript::doStatementPreProcessing(const string& statement) {
	// TODO: support [ ]
	auto preprocessedStatement = statement;
	ScriptStatementOperator nextOperators;
	while (getNextStatementOperator(preprocessedStatement, nextOperators) == true) {
		auto methodIt = scriptOperators.find(nextOperators.scriptOperator);
		if (methodIt == scriptOperators.end()) {
			Console::println("MiniScript::doStatementPreProcessing(): operator found in: '" + preprocessedStatement + "'@" + to_string(nextOperators.idx) + ": no method found");
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
				Console::println("MiniScript::doStatementPreProcessing(): operator found in: '" + preprocessedStatement + "'@" + to_string(nextOperators.idx) + ": unbalanced bracket usage");
				// TODO: error handling
				return preprocessedStatement;
			}
			//
			if (nextOperators.scriptOperator == OPERATOR_SET) {
				leftArgument = "\"" + doStatementPreProcessing(leftArgument) + "\"";
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperators.idx - leftArgumentLength) +
				method->getMethodName() + "(" + leftArgument + ", " + rightArgument + ")" +
				StringTools::substring(preprocessedStatement, nextOperators.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
		}
		nextOperators = ScriptStatementOperator();
	}
	return preprocessedStatement;
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
		// function arguments
		ScriptVariable functionArguments;
		functionArguments.setType(MiniScript::TYPE_ARRAY);
		// push arguments in function context
		for (const auto& argumentValue: argumentValues) {
			functionArguments.pushArrayValue(argumentValue);
		}
		// have $arguments
		setVariable("$arguments", functionArguments);
		// also put named arguments into state context variables
		auto argumentIdx = 0;
		for (const auto& argument: scripts[scriptIdx].arguments) {
			if (argumentIdx == argumentValues.size()) {
				break;
			}
			setVariable(argument.name, ScriptVariable(argumentValues[argumentIdx]));
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
	// also put named arguments from state context variables back into argumentValues
	{
		auto argumentIdx = 0;
		for (const auto& argument: scripts[scriptIdx].arguments) {
			if (argumentIdx == argumentValues.size()) {
				break;
			}
			if (argument.assignBack == true) {
				argumentValues[argumentIdx] = getVariable(argument.name);
			}
			argumentIdx++;
		}
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
	std::sort(methods.begin(), methods.end(), sortFunction);
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
				if (argument.assignBack == true) argumentsString+= "=";
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
			result+= "\t" + to_string(scriptStatement.statementIdx) + ": " + scriptStatement.statement + (scriptStatement.gotoStatementIdx != STATEMENTIDX_NONE?" (gotoStatement " + to_string(scriptStatement.gotoStatementIdx) + ")":"") + "\n";
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
				method+= ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
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
				operatorString+= ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "statement", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "statement", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false }
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
							// so we need to make a copy of argumentValues beginning from second element
							vector<ScriptVariable> callArgumentValues;
							for (auto i = 1; i < argumentValues.size(); i++) callArgumentValues.push_back(argumentValues[i]);
							// call
							span callArgumentValuesSpan(callArgumentValues);
							miniScript->call(scriptIdx, callArgumentValuesSpan, returnValue);
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = true, .assignBack = false }
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
					returnValue.setMapValue(variableName, *variableValue);
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "condition", .optional = false, .assignBack = false }
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
					{.type = ScriptVariableType::TYPE_INTEGER, .name = "time", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "condition", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .assignBack = false }
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
					Console::print(argumentValue.getValueString());
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
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
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
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "int", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "float", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR2, .name = "vec2", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "b", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "n", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "x", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "y", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "z", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "w", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_VECTOR4, .name = "vec4", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .assignBack = false },
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
		class ScriptMethodQuaternionMultiply: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionMultiply(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "quaternion.multiply";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Quaternion quaternion;
				Quaternion quaternionValue;
				Vector3 vec3Value;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::getQuaternionValue(argumentValues, 0, quaternion, false) == true) {
					if (MiniScript::getQuaternionValue(argumentValues, 1, quaternionValue, false) == true) {
						returnValue.setValue(quaternion.multiply(quaternionValue));
					} else
					if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
						returnValue.setValue(quaternion.multiply(vec3Value));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodQuaternionMultiply(this));
	}
	{ 		//
		class ScriptMethodQuaternionInvert: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodQuaternionInvert(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_QUATERNION, .name = "quaternion", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_VECTOR2, .name = "translation", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_VECTOR2, .name = "point", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
	{
		//
		class ScriptMethodMatrix3x3Multiply: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix3x3Multiply(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MATRIX3x3, .name = "mat3", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat3.multiply";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Matrix3x3 mat3;
				Matrix3x3 mat3Value;
				Vector2 vec2Value;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::getMatrix3x3Value(argumentValues, 0, mat3, false) == true) {
					if (MiniScript::getMatrix3x3Value(argumentValues, 1, mat3Value, false) == true) {
						returnValue.setValue(mat3.multiply(mat3Value));
					} else
					if (MiniScript::getVector2Value(argumentValues, 1, vec2Value, false) == true) {
						returnValue.setValue(mat3.multiply(vec2Value));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodMatrix3x3Multiply(this));
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
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "mat4", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "mat4", .optional = false, .assignBack = false },
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
	{
		//
		class ScriptMethodMatrix4x4Multiply: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodMatrix4x4Multiply(MiniScript* miniScript):
				ScriptMethod(
					{
						{ .type = ScriptVariableType::TYPE_MATRIX4x4, .name = "mat4", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_PSEUDO_MIXED
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "mat4.multiply";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Matrix4x4 mat4;
				Matrix4x4 mat4Value;
				Vector3 vec3Value;
				Vector4 vec4Value;
				if (argumentValues.size() != 2) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else
				if (MiniScript::getMatrix4x4Value(argumentValues, 0, mat4, false) == true) {
					if (MiniScript::getMatrix4x4Value(argumentValues, 1, mat4Value, false) == true) {
						returnValue.setValue(mat4.multiply(mat4Value));
					} else
					if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, false) == true) {
						returnValue.setValue(mat4.multiply(vec3Value));
					} else
					if (MiniScript::getVector4Value(argumentValues, 1, vec4Value, false) == true) {
						returnValue.setValue(mat4.multiply(vec4Value));
					} else {
						Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
						miniScript->startErrorScript();
					}
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
			bool isVariadic() const override {
				return true;
			}
		};
		registerMethod(new ScriptMethodMatrix4x4Multiply(this));
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
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_VECTOR3, .name = "scale", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationZ", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationY", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "rotationX", .optional = true, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = true },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "translation", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = true },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "scale", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = true },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "idx", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
		class ScriptMethodTransformMultiply: public ScriptMethod {
		private:
			MiniScript* miniScript { nullptr };
		public:
			ScriptMethodTransformMultiply(MiniScript* miniScript):
				ScriptMethod(
					{
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_VECTOR3),
					miniScript(miniScript) {}
			const string getMethodName() override {
				return "transform.multiply";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				Transform transform;
				Vector3 vec3;
				if (MiniScript::getTransformValue(argumentValues, 0, transform, false) == true &&
					MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
					returnValue.setValue(transform.getTransformMatrix() * vec3);
				} else {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				}
			}
		};
		registerMethod(new ScriptMethodTransformMultiply(this));
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "vec3", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = true },
						{.type = ScriptVariableType::TYPE_VECTOR3, .name = "axis", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_FLOAT, .name = "angle", .optional = false, .assignBack = false },
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
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "currentAngle", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "targetAngle", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "timePassedSeconds", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "degreesPerSeconds", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_FLOAT, .name = "interpolatedAngle", .optional = false, .assignBack = true },
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
					argumentValues[4] = interpolatedAngle;
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_TRANSFORM, .name = "transform", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_MATRIX4x4, .name = "transformMatrix", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_BOOLEAN, .name = "bool", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "a", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_BOOLEAN, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "prefix", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "suffix", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "what", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "endIndex", .optional = true, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string1", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "string2", .optional = false, .assignBack = false },
					},
					ScriptVariableType::TYPE_BOOLEAN
				),
				miniScript(miniScript) {}
			const string getMethodName() override {
				return "string.equalsIgnoreCase";
			}
			void executeMethod(span<ScriptVariable>& argumentValues, ScriptVariable& returnValue, const ScriptStatement& statement) override {
				string string1Value;
				string string2Value;
				if (MiniScript::getStringValue(argumentValues, 0, string1Value, false) == false ||
					MiniScript::getStringValue(argumentValues, 1, string2Value, false) == false) {
					Console::println(getMethodName() + "(): " + miniScript->getStatementInformation(statement) + ": argument mismatch: expected arguments: " + miniScript->getArgumentInformation(getMethodName()));
					miniScript->startErrorScript();
				} else {
					returnValue.setValue(StringTools::equalsIgnoreCase(string1Value, string2Value));
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "pattern", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "pattern", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "delimiters", .optional = false, .assignBack = false },
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
						returnValue.pushArrayValue(tokenizedString);
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "spaces", .optional = true, .assignBack = false }
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
					result+= argumentValue.getValueString();
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "string", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "src", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "toSize", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_STRING, .name = "src", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_STRING, .name = "by", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "toSize", .optional = false, .assignBack = false }
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
					returnValue.pushArrayValue(argumentValue);
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
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true }
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
						argumentValues[0].pushArrayValue(argumentValues[i]);
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .assignBack = false }
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
					returnValue = argumentValues[0].getArrayValue(index);
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .assignBack = false }
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
					argumentValues[0].setArrayValue(index, argumentValues[2]);
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "index", .optional = false, .assignBack = false }
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
					argumentValues[0].removeArrayValue(index);
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false },
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
						auto arrayValue = array.getArrayValue(i);
						if (arrayValue.getValueString() == stringValue) {
							array.removeArrayValue(i);
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
						{ .type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "value", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "beginIndex", .optional = true, .assignBack = false },
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
						auto arrayValue = array.getArrayValue(i);
						if (arrayValue.getValueString() == stringValue) {
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
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true },
						{.type = ScriptVariableType::TYPE_STRING, .name = "function", .optional = false, .assignBack = false },
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
					class SortClass {
						private:
							MiniScript* miniScript;
							const string& function;
						public:
							SortClass(MiniScript* miniScript, const string& function): miniScript(miniScript), function(function) {
							}
							bool operator()(const MiniScript::ScriptVariable& a, const MiniScript::ScriptVariable& b) const {
								vector<MiniScript::ScriptVariable> sortArgumentValues { a, b };
								span sortArgumentValuesSpan(sortArgumentValues);
								MiniScript::ScriptVariable sortReturnValue;
								miniScript->call(function, sortArgumentValuesSpan, sortReturnValue);
								bool result = false;
								sortReturnValue.getBooleanValue(result, false);
								return result;
							}
					};
					//
					auto arrayPtr = argumentValues[0].getArrayPointer();
					if (arrayPtr != nullptr) {
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
						{.type = ScriptVariableType::TYPE_ARRAY, .name = "array", .optional = false, .assignBack = true }
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .assignBack = false }
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
					argumentValues[0].setMapValue(key, argumentValues[2]);
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
					returnValue.setValue(argumentValues[0].hasMapValue(key));
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
					returnValue = argumentValues[0].getMapValue(key);
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
					argumentValues[0].removeMapValue(key);
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = false },
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
						returnValue.pushArrayValue(key);
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
						{ .type = ScriptVariableType::TYPE_MAP, .name = "map", .optional = false, .assignBack = false },
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
					for (const auto& value: values) {
						returnValue.pushArrayValue(value);
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
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .assignBack = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "key", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_SET, .name = "set", .optional = false, .assignBack = false },
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
						returnValue.pushArrayValue(key);
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "format", .optional = true, .assignBack = false }
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "name", .optional = false, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_MAP, .name = "attributes", .optional = true, .assignBack = false },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "innerXML", .optional = true, .assignBack = false },
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
							xml+= " " + mapEntryName + "=\"" + GUIParser::escape(mapEntryValue.getValueString()) + "\"";
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
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "value", .optional = false, .assignBack = false },
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
					returnValue.setValue(MiniScript::serializeAsJson(argumentValues[0]));
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "json", .optional = false, .assignBack = false },
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
					returnValue = MiniScript::deserializeJson(json);
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
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .assignBack = true },
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
					argumentValues[0] = value;
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
						{ .type = ScriptVariableType::TYPE_INTEGER, .name = "variable", .optional = false, .assignBack = true },
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
					argumentValues[0] = value;
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "value", .optional = false, .assignBack = false },
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .assignBack = false }
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
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "a", .optional = false, .assignBack = false },
						{.type = ScriptVariableType::TYPE_INTEGER, .name = "b", .optional = false, .assignBack = false }
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

bool MiniScript::transpileScriptStatement(string& generatedCode, const ScriptSyntaxTreeNode& syntaxTree, const ScriptStatement& statement, int scriptConditionIdx, int scriptIdx, int& statementIdx, const unordered_map<string, vector<string>>& methodCodeMap, bool& scriptStateChanged, bool& scriptStopped, vector<string>& enabledNamedConditions, int depth, int argumentIdx, int parentArgumentIdx, const string& returnValue, const string& injectCode, int additionalIndent) {
	//
	statementIdx++;
	auto currentStatementIdx = statementIdx;

	//
	switch (syntaxTree.type) {
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				// check script user functions
				auto scriptFunctionsIt = scriptFunctions.find(syntaxTree.value.getValueString());
				if (scriptFunctionsIt != scriptFunctions.end()) {
					// have a wrapping script.call call
					ScriptSyntaxTreeNode callSyntaxTreeNode;
					callSyntaxTreeNode.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
					callSyntaxTreeNode.value = METHOD_SCRIPTCALL;
					// construct argument for name of function
					ScriptSyntaxTreeNode callArgumentSyntaxTreeNode;
					callArgumentSyntaxTreeNode.type = ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
					callArgumentSyntaxTreeNode.value = syntaxTree.value;
					// add argumnet for name of function
					callSyntaxTreeNode.arguments.push_back(callArgumentSyntaxTreeNode);
					// add original parameter to call syntaxTree
					for (const auto& argument: syntaxTree.arguments) {
						callSyntaxTreeNode.arguments.push_back(argument);
					}
					// asign script.call method
					auto methodIt = scriptMethods.find(callSyntaxTreeNode.value.getValueString());
					if (methodIt == scriptMethods.end()) {
						Console::println("MiniScript::transpileScriptStatement(): method code not found: '" + callSyntaxTreeNode.value.getValueString() + "'");
						return false;
					}
					callSyntaxTreeNode.method = methodIt->second;
					return transpileScriptStatement(generatedCode, callSyntaxTreeNode, statement, scriptConditionIdx, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, depth, argumentIdx, parentArgumentIdx, returnValue, injectCode, additionalIndent);
				} else {
					Console::println("MiniScript::transpileScriptStatement(): function not found: '" + syntaxTree.value.getValueString() + "'");
					return false;
				}
				//
				break;
			}
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			break;
		default:
			Console::println("MiniScript::transpileScriptStatement(): " + getStatementInformation(statement) + ": function or method call expected, but got literal or 'none' syntaxTree");
			return false;

	}

	//
	auto method = syntaxTree.value.getValueString();

	// find method code in method code map
	auto methodCodeMapIt = methodCodeMap.find(method);
	if (methodCodeMapIt == methodCodeMap.end()) {
		Console::println("MiniScript::transpileScriptStatement(): method code not found: '" + method + "'");
		return false;
	}
	const auto& methodCode = methodCodeMapIt->second;

	// script method
	auto scriptMethodIt = scriptMethods.find(string(method));
	if (scriptMethodIt == scriptMethods.end()) {
		Console::println("MiniScript::transpileScriptStatement(): method not found: '" + method + "'");
		return false;
	}
	auto scriptMethod = scriptMethodIt->second;

	// indenting
	string minIndentString = "\t";
	string depthIndentString;
	for (auto i = 0; i < depth + additionalIndent; i++) depthIndentString+= "\t";

	// comment about current statement
	generatedCode+= minIndentString + depthIndentString;
	generatedCode+= "// " + (depth > 0?"depth = " + to_string(depth):"") + (depth > 0 && argumentIdx != ARGUMENTIDX_NONE?" / ":"") + (argumentIdx != ARGUMENTIDX_NONE?"argument index = " + to_string(argumentIdx):"") + (depth > 0 || argumentIdx != ARGUMENTIDX_NONE?": ":"");
	generatedCode+= syntaxTree.value.getValueString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")";
	generatedCode+= "\n";

	// argument values header
	generatedCode+= minIndentString + depthIndentString + "{" + "\n";

	// construct argument values
	{
		vector<string> argumentValuesCode;
		if (depth > 0) {
			argumentValuesCode.push_back("ScriptVariable& returnValue = argumentValuesD" + to_string(depth - 1) + (parentArgumentIdx != ARGUMENTIDX_NONE?"AIDX" + to_string(parentArgumentIdx):"") + "[" + to_string(argumentIdx) + "];");
		} else {
			argumentValuesCode.push_back("ScriptVariable returnValue;");
		}
		argumentValuesCode.push_back("array<ScriptVariable, " + to_string(syntaxTree.arguments.size()) + "> argumentValues {");

		// construct argument values
		if (syntaxTree.arguments.empty() == false) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "// required method code arguments" + "\n";
			auto subArgumentIdx = 0;
			for (const auto& argument: syntaxTree.arguments) {
				auto lastArgument = subArgumentIdx == syntaxTree.arguments.size() - 1;
				switch (argument.type) {
					case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
						{
							switch (argument.value.getType())  {
								case TYPE_NULL:
									break;
								case TYPE_BOOLEAN:
									{
										bool value;
										argument.value.getBooleanValue(value);
										argumentValuesCode.push_back(string() + "\t" + "ScriptVariable(" + (value == true?"true":"false") + ")" + (lastArgument == false?",":""));
									}
									break;
								case TYPE_INTEGER:
									{
										int64_t value;
										argument.value.getIntegerValue(value);
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(static_cast<int64_t>(" + to_string(value) + "ll))" + (lastArgument == false?",":""));
									}
									break;
								case TYPE_FLOAT:
									{
										float value;
										argument.value.getFloatValue(value);
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(" + to_string(value) + "f)" + (lastArgument == false?",":""));
									}
									break;
								case TYPE_STRING:
									{
										string value;
										argument.value.getStringValue(value);
										value = StringTools::replace(StringTools::replace(value, "\\", "\\\\"), "\"", "\\\"");
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(string(\"" + value + "\"))" + (lastArgument == false?",":""));
									}
									break;
								default:
									{
										Console::println("MiniScript::transpileScriptStatement(): " + getStatementInformation(statement) + ": '" + argument.value.getAsString() + "': unknown argument type: " + argument.value.getTypeAsString());
										break;
									}
							}
							break;
						}
					case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
						{
							argumentValuesCode.push_back(string() + "\t" + "ScriptVariable()" + (lastArgument == false?",":"") + " // argumentValues[" + to_string(subArgumentIdx) + "] --> returnValue of " + argument.value.getValueString() + "(" + getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
						{
							argumentValuesCode.push_back(string() + "\t" + "ScriptVariable()" + (lastArgument == false?",":"") + " // argumentValues[" + to_string(subArgumentIdx) + "] --> returnValue of " + argument.value.getValueString() + "(" + getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					default:
						break;
				}
				//
				subArgumentIdx++;
			}
		}
		// end of arguments initialization
		argumentValuesCode.push_back("};");

		//
		argumentValuesCode.push_back("array<ScriptVariable, " + to_string(syntaxTree.arguments.size()) + ">& argumentValuesD" + to_string(depth) + (argumentIdx != ARGUMENTIDX_NONE?"AIDX" + to_string(argumentIdx):"") + " = argumentValues;");

		// argument values header
		for (const auto& codeLine: argumentValuesCode) {
			generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + "\n";
		}
	}

	// statement
	if (depth == 0) {
		generatedCode+= minIndentString + depthIndentString + "\t" + "// statement setup" + "\n";
		if (scriptConditionIdx != SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const ScriptStatement& statement = scripts[" + to_string(scriptConditionIdx) + "].conditionStatement;" + "\n";
		} else {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const ScriptStatement& statement = scripts[" + to_string(scriptIdx) + "].statements[" + to_string(statement.statementIdx) + "];" + "\n";
		}
		generatedCode+= minIndentString + depthIndentString + "\t" + "getScriptState().statementIdx = statement.statementIdx;" + "\n";
	}

	// enabled named conditions
	if (method == METHOD_ENABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::println("MiniScript::transpileScriptStatement(): " + getStatementInformation(statement) + ": " + METHOD_ENABLENAMEDCONDITION + "(): expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueString();
			enabledNamedConditions.erase(
				remove(
					enabledNamedConditions.begin(),
					enabledNamedConditions.end(),
					name
				),
				enabledNamedConditions.end()
			);
			enabledNamedConditions.push_back(name);
		}
	} else
	if (method == METHOD_DISABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::println("MiniScript::transpileScriptStatement(): " + getStatementInformation(statement) + ": " + METHOD_DISABLENAMEDCONDITION + "(): expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueString();
			enabledNamedConditions.erase(
				remove(
					enabledNamedConditions.begin(),
					enabledNamedConditions.end(),
					name
				),
				enabledNamedConditions.end()
			);
		}
	}

	// transpile method/function call argument
	{
		auto subArgumentIdx = 0;
		for (const auto& argument: syntaxTree.arguments) {
			switch (argument.type) {
				case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
				case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
					if (transpileScriptStatement(generatedCode, argument, statement, scriptConditionIdx, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, depth + 1, subArgumentIdx, argumentIdx, returnValue) == false) {
 						Console::println("MiniScript::transpileScriptStatement(): transpileScriptStatement(): " + getStatementInformation(statement) + ": '" + syntaxTree.value.getValueString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")" + "': transpile error");
					}
					break;
				default:
					break;
			}
			subArgumentIdx++;
		}
	}

	// assign back arguments code for functions
	vector<string> assignBackCodeLines;
	if (method == METHOD_SCRIPTCALL && syntaxTree.arguments.empty() == false) {
		// check script user functions
		auto scriptFunctionsIt = scriptFunctions.find(syntaxTree.arguments[0].value.getValueString());
		if (scriptFunctionsIt != scriptFunctions.end()) {
			//
			auto scriptIdx = scriptFunctionsIt->second;
			// assign back arguments starting from argument index 1 as 0 is function name
			auto argumentIdx = 1;
			for (const auto& argument: scripts[scriptIdx].arguments) {
				//
				if (argumentIdx == syntaxTree.arguments.size()) {
					break;
				}
				//
				if (argument.assignBack == true) {
					const auto& assignBackArgument = syntaxTree.arguments[argumentIdx];
					if (assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
						assignBackArgument.value.getValueString() == "getVariable" &&
						assignBackArgument.arguments.empty() == false) {
						//
						auto variableName = assignBackArgument.arguments[0].value.getValueString();
						if (StringTools::startsWith(variableName, "$") == true) {
							assignBackCodeLines.push_back("setVariable(\"" + variableName + "\", argumentValues[" + to_string(argumentIdx) + "], &statement);");
						} else {
							Console::println("MiniScript::executeScriptStatement(): " + getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
						}
					} else {
						Console::println(
							"MiniScript::executeScriptStatement(): " +
							getStatementInformation(statement) +
							": Can not assign back argument value @ " +
							to_string(argumentIdx) +
							" to variable '" +
							assignBackArgument.value.getValueString() +
							(
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
								assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
									?"(...)"
									:""
							) +
							"'"
						);
					}
				}
				argumentIdx++;
			}
		} else {
			Console::println("MiniScript::transpileScriptStatement(): function not found: '" + syntaxTree.value.getValueString() + "'");
			return false;
		}
	} else {
		// for methods
		auto argumentIdx = 0;
		for (const auto& argumentType: scriptMethod->getArgumentTypes()) {
			//
			if (argumentIdx == syntaxTree.arguments.size()) {
				break;
			}
			//
			if (argumentType.assignBack == true) {
				const auto& assignBackArgument = syntaxTree.arguments[argumentIdx];
				if (assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
					assignBackArgument.value.getValueString() == "getVariable" &&
					assignBackArgument.arguments.empty() == false) {
					//
					auto variableName = assignBackArgument.arguments[0].value.getValueString();
					if (StringTools::startsWith(variableName, "$") == true) {
						assignBackCodeLines.push_back("setVariable(\"" + variableName + "\", argumentValues[" + to_string(argumentIdx) + "], &statement);");
					} else {
						Console::println("MiniScript::transpileScriptStatement(): " + getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
					}
				} else {
					Console::println(
						"MiniScript::transpileScriptStatement(): " +
						getStatementInformation(statement) +
						": Can not assign back argument value @ " +
						to_string(argumentIdx) +
						" to variable '" +
						assignBackArgument.value.getValueString() +
						(
							assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
							assignBackArgument.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
								?"(...)"
								:""
						) +
						"'"
					);
				}
			}
			argumentIdx++;
		}
	}

	//
	if (assignBackCodeLines.empty() == false) {
		assignBackCodeLines.insert(assignBackCodeLines.begin(), string() + "// assign back");
		assignBackCodeLines.insert(assignBackCodeLines.end(), string() + "//");
	}

	// generate code
	generatedCode+= minIndentString + depthIndentString + "\t" + "// method code: " + string(method) + "\n";
	for (auto codeLine: methodCode) {
		codeLine = StringTools::replace(codeLine, "getMethodName()", "string(\"" + string(method) + "\")");
		// replace returns with gotos
		if (StringTools::regexMatch(codeLine, "[\\ \\t]*return[\\ \\t]*;.*") == true) {
			Console::println("MiniScript::transpileScriptStatement(): method '" + string(method) + "': return statement not supported!");
			return false;
		} else
		if (StringTools::regexMatch(codeLine, "[\\ \\t]*miniScript[\\ \\t]*->gotoStatementGoto[\\ \\t]*\\([\\ \\t]*statement[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true) {
			if (statement.gotoStatementIdx != STATEMENTIDX_NONE) {
				 // find indent
				int indent = 0;
				for (auto i = 0; i < codeLine.size(); i++) {
					auto c = codeLine[i];
					if (c == '\t') {
						indent++;
					} else {
						break;
					}
				}
				string indentString;
				for (auto i = 0; i < indent; i++) indentString+= "\t";
				generatedCode+= minIndentString + indentString + depthIndentString + "\t" + "goto miniscript_statement_" + to_string(statement.gotoStatementIdx) + ";\n";
			}
		} else
		if (StringTools::regexMatch(codeLine, "[\\ \\t]*miniScript[\\ \\t]*->startErrorScript[\\ \\t]*\\([\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true ||
			StringTools::regexMatch(codeLine, "[\\ \\t]*miniScript[\\ \\t]*->emit[\\ \\t]*\\([\\ \\t]*[a-zA-Z0-9]*[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true) {
			for (const auto& assignBackCodeLine: assignBackCodeLines) {
				generatedCode+= minIndentString + depthIndentString + "\t";
				for (auto i = 0; i < codeLine.size(); i++) {
					if (codeLine[i] == ' ' || codeLine[i] == '\t') {
						generatedCode+= codeLine[i];
					} else {
						break;
					}
				}
				generatedCode+= assignBackCodeLine + "\n";
			}
			generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + " return" + (returnValue.empty() == false?" " + returnValue:"") + ";\n";
		} else {
			if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*miniScript[\\ \\t]*->[\\ \\t]*setScriptStateState[\\ \\t]*\\([\\ \\t]*.+[\\ \\t]*\\);.*") == true) {
				scriptStateChanged = true;
			}
			if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*miniScript[\\ \\t]*->[\\ \\t]*stopScriptExecutation[\\ \\t]*\\([\\ \\t]*\\);.*") == true) {
				scriptStopped = true;
			} else
			if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*miniScript[\\ \\t]*->[\\ \\t]*stopRunning[\\ \\t]*\\([\\ \\t]*\\);.*") == true) {
				scriptStopped = true;
			}
			generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + "\n";
		}
	}

	// inject code if we have any to inject
	if (injectCode.empty() == false) {
		generatedCode+= minIndentString + depthIndentString + "\t" + injectCode + "\n";
	}

	// assign back code
	for (const auto& assignBackCodeLine: assignBackCodeLines) {
		generatedCode+= minIndentString + depthIndentString + "\t" + assignBackCodeLine + "\n";
	}
	//
	generatedCode+= minIndentString + depthIndentString + "}" + "\n";

	//
	return true;
}

bool MiniScript::transpile(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::println("MiniScript::transpile(): invalid script index");
		return false;
	}

	//
	const auto& script = scripts[scriptIdx];

	//
	string scriptType =
		(script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?
			"function":
			(
				script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?
					"condition":
					"named condition"
			)
		);

	Console::println("MiniScript::transpile(): transpiling code for " + scriptType + " = '" + script.condition + "', with name '" + script.name + "'");

	//
	string methodIndent = "\t";
	string generatedCodeHeader;

	// TODO: move me into a method
	generatedCodeHeader+= methodIndent + "// STATEMENTIDX_FIRST means complete method call" + "\n";
	generatedCodeHeader+= methodIndent + "if (miniScriptGotoStatementIdx == STATEMENTIDX_FIRST) {" + "\n";
	generatedCodeHeader+= methodIndent + "\t" + "resetScriptExecutationState(" + to_string(scriptIdx) + ", STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
	generatedCodeHeader+= methodIndent + "}" + "\n";
	// TODO: end
	generatedCodeHeader+= methodIndent + "// script setup" + "\n";
	generatedCodeHeader+= methodIndent + "auto miniScript = this;" + "\n";
	generatedCodeHeader+= methodIndent + "getScriptState().scriptIdx = " + to_string(scriptIdx) + ";" + "\n";

	// method name
	string methodName =
		(script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?
			"":
			(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on_":"on_enabled_")
		) +
		(script.name.empty() == false?script.name:(
			StringTools::regexMatch(script.condition, "[a-zA-Z0-9]+") == true?
				script.condition:
				to_string(scriptIdx)
			)
		);

	//
	unordered_set<int> gotoStatementIdxSet;
	for (const auto& scriptStatement: script.statements) gotoStatementIdxSet.insert(scriptStatement.gotoStatementIdx);

	//
	auto statementIdx = STATEMENTIDX_FIRST;
	vector<string> enabledNamedConditions;
	auto scriptStateChanged = false;
	for (auto scriptStatementIdx = STATEMENTIDX_FIRST; scriptStatementIdx < script.statements.size(); scriptStatementIdx++) {
		const auto& statement = script.statements[scriptStatementIdx];
		const auto& syntaxTree = script.syntaxTree[scriptStatementIdx];
		//
		if (scriptStateChanged == true) {
			generatedCodeHeader+= methodIndent + "if (miniScriptGotoStatementIdx == " + to_string(statement.statementIdx)  + ") goto miniscript_statement_" + to_string(statement.statementIdx) + "; else" + "\n";
		}

		// enabled named conditions
		if (enabledNamedConditions.empty() == false) {
			generatedCode+= "\n";
			generatedCode+= methodIndent + "// enabled named conditions" + "\n";
			generatedCode+= methodIndent + "{" + "\n";
			generatedCode+= methodIndent + "\t" + "auto scriptIdxToStart = determineNamedScriptIdxToStart();" + "\n";
			generatedCode+= methodIndent + "\t" + "if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != getScriptState().scriptIdx) {" + "\n";
			generatedCode+= methodIndent + "\t" + "resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
			generatedCode+= methodIndent + "\t" + "timeEnabledConditionsCheckLast = Time::getCurrentMillis();" + "\n";
			generatedCode+= methodIndent + "\t" + "return;" + "\n";
			generatedCode+= methodIndent + "\t" + "}" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}

		// statement_xyz goto label
		generatedCode+= methodIndent + "// statement: " + to_string(statement.statementIdx) + "\n";
		if (scriptStateChanged == true || gotoStatementIdxSet.find(statement.statementIdx) != gotoStatementIdxSet.end()) {
			generatedCode+= methodIndent + "miniscript_statement_" + to_string(statement.statementIdx) + ":" + "\n";
		}
		scriptStateChanged = false;
		auto scriptStopped = false;
		transpileScriptStatement(generatedCode, syntaxTree, statement, SCRIPTIDX_NONE, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions);
		if (scriptStopped == true) {
			generatedCode+= methodIndent + "if (getScriptState().running == false) {" + "\n";
			generatedCode+= methodIndent + "\t" + "return;" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}
		if (scriptStateChanged == true) {
			generatedCode+= methodIndent + "if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {" + "\n";
			generatedCode+= methodIndent + "\t" + "getScriptState().statementIdx++;" + "\n";
			generatedCode+= methodIndent + "\t" + "return;" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}
	}
	generatedCode+= methodIndent + "getScriptState().scriptIdx = SCRIPTIDX_NONE;" + "\n";
	generatedCode+= methodIndent + "getScriptState().statementIdx = STATEMENTIDX_NONE;" + "\n";
	generatedCode+= methodIndent + "setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);" + "\n";

	//
	generatedCodeHeader+= methodIndent + "if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println(\"MiniScript::" + methodName + "(): Can not go to statement \" + to_string(miniScriptGotoStatementIdx));" + "\n";
	//
	generatedCode = generatedCodeHeader + generatedCode;
	return true;
}

bool MiniScript::transpileScriptCondition(string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const string& returnValue, const string& injectCode, int depth) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::println("MiniScript::transpile(): invalid script index");
		return false;
	}

	//
	const auto& script = scripts[scriptIdx];

	//
	Console::println("MiniScript::transpile(): transpiling code condition for condition = '" + scripts[scriptIdx].condition + "', with name '" + scripts[scriptIdx].name + "'");

	//
	auto statementIdx = STATEMENTIDX_FIRST;
	auto scriptStateChanged = false;
	auto scriptStopped = false;
	vector<string >enabledNamedConditions;
	transpileScriptStatement(generatedCode, script.conditionSyntaxTree, script.conditionStatement, scriptIdx, SCRIPTIDX_NONE, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, 0, ARGUMENTIDX_NONE, ARGUMENTIDX_NONE, returnValue, injectCode, depth + 1);

	//
	generatedCode+= "\t\n";

	//
	return true;
}

const string MiniScript::createSourceCode(const ScriptSyntaxTreeNode& syntaxTreeNode) {
	//
	string result;
	switch (syntaxTreeNode.type) {
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTreeNode.value.getType()) {
					case TYPE_NULL:
						{
							result+= (result.empty() == false?", ":"") + string("<VOID>");
							break;
						}
					case TYPE_BOOLEAN:
					case TYPE_INTEGER:
					case TYPE_FLOAT:
						{
							result+= (result.empty() == false?", ":"") + syntaxTreeNode.value.getValueString();
							break;
						}
					case TYPE_STRING:
						{
							result+= (result.empty() == false?", ":"") + string("\"") + syntaxTreeNode.value.getValueString() + string("\"");
							break;
						}
					default:
						{
							result+= (result.empty() == false?", ":"") + string("<COMPLEX DATATYPE>");
							break;
						}
				}
				break;
			}
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto endElse = syntaxTreeNode.value.getValueString() == "end" || syntaxTreeNode.value.getValueString() == "else";
				result+= syntaxTreeNode.value.getValueString();
				if (endElse == false) result+= string("(");
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (argumentIdx > 0) result+= ", ";
					result+= createSourceCode(argument);
					argumentIdx++;
				}
				if (endElse == false) result+= string(")");
				break;
			}
		default:
			break;
	}
	return result;
}

const string MiniScript::createSourceCode(Script::ScriptType scriptType, const string& condition, const vector<Script::ScriptArgument>& arguments, const string& name, const ScriptSyntaxTreeNode& conditionSyntaxTree, const vector<ScriptSyntaxTreeNode>& syntaxTree) {
	//
	string result;
	//
	switch(scriptType) {
		case Script::SCRIPTTYPE_FUNCTION: {
			result+= "function: ";
			if (condition.empty() == false) {
				result+= condition;
			}
			auto argumentIdx = 0;
			result+= "(";
			for (const auto& argument: arguments) {
				if (argumentIdx > 0) result+= ", ";
				if (argument.assignBack == true) result+= "=";
				result+= argument.name;
				argumentIdx++;
			}
			result+= ")";
			break;
		}
		case Script::SCRIPTTYPE_ON:
			{
				result+= "on: ";
				if (condition.empty() == false) {
					result+= condition;
				}
				break;
			}
		case Script::SCRIPTTYPE_ONENABLED:
			{
				result+= "on-enabled: "; break;
				if (condition.empty() == false) {
					result+= condition;
				}
			}
	}
	if (conditionSyntaxTree.type != ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE)
		result+= createSourceCode(conditionSyntaxTree);
	if (name.empty() == false) {
		result+= " := " + name + "\n";
	} else {
		result+= "\n";
	}
	//
	auto indent = 1;
	for (const auto& syntaxTreeNode: syntaxTree) {
		if (syntaxTreeNode.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueString() == "if") indent+= 0; else
			if (syntaxTreeNode.value.getValueString() == "elseif") indent-= 1; else
			if (syntaxTreeNode.value.getValueString() == "else") indent-= 1; else
			if (syntaxTreeNode.value.getValueString() == "end") indent-= 1; else
			if (syntaxTreeNode.value.getValueString() == "forTime") indent+= 0; else
			if (syntaxTreeNode.value.getValueString() == "forCondition") indent+= 0;
		}
		for (auto i = 0; i < indent; i++) result+= "\t";
		result+= createSourceCode(syntaxTreeNode) + "\n";
		if (syntaxTreeNode.type == ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueString() == "if") indent+= 1; else
			if (syntaxTreeNode.value.getValueString() == "elseif") indent+= 1; else
			if (syntaxTreeNode.value.getValueString() == "else") indent+= 1; else
			if (syntaxTreeNode.value.getValueString() == "end") indent-= 0; else
			if (syntaxTreeNode.value.getValueString() == "forTime") indent+= 1; else
			if (syntaxTreeNode.value.getValueString() == "forCondition") indent+= 1;
		}
	}
	return result;
}

const string MiniScript::createSourceCode() {
	string result;
	// create source code
	for (const auto& script: scripts) {
		result+= createSourceCode(script.scriptType, script.emitCondition == true?script.condition:string(), script.arguments, script.name, script.conditionSyntaxTree, script.syntaxTree);
	}
	//
	return result;
}

void MiniScript::serializeMapAsJson(Document& jParent, const ScriptVariable& variable) {
	const auto& value = variable.getMapValueReference();
	for (const auto& [subName, subVariable]: value) {
		//
		switch(subVariable.getType()) {
			case TYPE_NULL:
				jParent.AddMember(Value(subName, jParent.GetAllocator()), Value(), jParent.GetAllocator());
				break;
			case TYPE_BOOLEAN:
				{
					const auto& value = subVariable.getBooleanValueReference();
					jParent.AddMember(Value(subName, jParent.GetAllocator()), Value(value), jParent.GetAllocator());
				}
				break;
			case TYPE_INTEGER:
				{
					const auto& value = subVariable.getIntegerValueReference();
					jParent.AddMember(Value(subName, jParent.GetAllocator()), Value(value), jParent.GetAllocator());
				}
				break;
			case TYPE_FLOAT:
				{
					const auto& value = subVariable.getFloatValueReference();
					jParent.AddMember(Value(subName, jParent.GetAllocator()), Value(value), jParent.GetAllocator());
				}
				break;
			case TYPE_STRING:
				{
					const auto& value = subVariable.getStringValueReference();
					jParent.AddMember(Value(subName, jParent.GetAllocator()), Value(value, jParent.GetAllocator()), jParent.GetAllocator());
				}
				break;
			case TYPE_VECTOR2:
				{
					const auto& value = subVariable.getVector2ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_VECTOR3:
				{
					const auto& value = subVariable.getVector3ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_VECTOR4:
				{
					const auto& value = subVariable.getVector4ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_QUATERNION:
				{
					const auto& value = subVariable.getQuaternionValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_MATRIX3x3:
				{
					const auto& value = subVariable.getMatrix3x3ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_MATRIX4x4:
				{
					const auto& value = subVariable.getMatrix4x4ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_TRANSFORM:
				{
					const auto& value = subVariable.getTransformValueReference();
					const auto& transformMatrix = value.getTransformMatrix();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: transformMatrix.getArray()) {
						jSubArray.PushBack(Value(v), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
			case TYPE_ARRAY:
				{
					Value jSubParent;
					jSubParent.SetArray();
					serializeArrayAsJson(jParent, jSubParent, subVariable);
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubParent, jParent.GetAllocator());
				}
				break;
			case TYPE_MAP:
				{
					Document jSubParent;
					jSubParent.SetObject();
					serializeMapAsJson(jSubParent, subVariable);
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubParent, jParent.GetAllocator());
				}
				break;
			case TYPE_SET:
				{
					const auto& value = subVariable.getSetValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value) {
						jSubArray.PushBack(Value(v, jParent.GetAllocator()), jParent.GetAllocator());
					}
					jParent.AddMember(Value(subName, jParent.GetAllocator()), jSubArray, jParent.GetAllocator());
				}
				break;
		}
	}
}

void MiniScript::serializeArrayAsJson(Document& jDocument, Value& jParent, const ScriptVariable& variable) {
	const auto& value = variable.getArrayValueReference();
	for (const auto& subVariable: value) {
		//
		switch(subVariable.getType()) {
			case TYPE_NULL:
				jParent.PushBack(Value(), jDocument.GetAllocator());
				break;
			case TYPE_BOOLEAN:
				{
					const auto& value = subVariable.getBooleanValueReference();
					jParent.PushBack(Value(value), jDocument.GetAllocator());
				}
				break;
			case TYPE_INTEGER:
				{
					const auto& value = subVariable.getIntegerValueReference();
					jParent.PushBack(Value(value), jDocument.GetAllocator());
				}
				break;
			case TYPE_FLOAT:
				{
					const auto& value = subVariable.getFloatValueReference();
					jParent.PushBack(Value(value), jDocument.GetAllocator());
				}
				break;
			case TYPE_STRING:
				{
					const auto& value = subVariable.getStringValueReference();
					jParent.PushBack(Value(value, jDocument.GetAllocator()), jDocument.GetAllocator());
				}
				break;
			case TYPE_VECTOR2:
				{
					const auto& value = subVariable.getVector2ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_VECTOR3:
				{
					const auto& value = subVariable.getVector3ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_VECTOR4:
				{
					const auto& value = subVariable.getVector4ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_QUATERNION:
				{
					const auto& value = subVariable.getQuaternionValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_MATRIX3x3:
				{
					const auto& value = subVariable.getMatrix3x3ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_MATRIX4x4:
				{
					const auto& value = subVariable.getMatrix4x4ValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_TRANSFORM:
				{
					const auto& value = subVariable.getTransformValueReference();
					auto transformMatrix = value.getTransformMatrix();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: transformMatrix.getArray()) {
						jSubArray.PushBack(Value(v), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
			case TYPE_ARRAY:
				{
					Value jSubParent;
					jSubParent.SetArray();
					serializeArrayAsJson(jDocument, jSubParent, subVariable);
					jParent.PushBack(jSubParent, jDocument.GetAllocator());
				}
				break;
			case TYPE_MAP:
				{
					Document jSubParent;
					jSubParent.SetObject();
					serializeMapAsJson(jSubParent, subVariable);
					jParent.PushBack(jSubParent, jDocument.GetAllocator());
				}
				break;
			case TYPE_SET:
				{
					const auto& value = subVariable.getSetValueReference();
					Value jSubArray;
					jSubArray.SetArray();
					for (auto v: value) {
						jSubArray.PushBack(Value(v, jDocument.GetAllocator()), jDocument.GetAllocator());
					}
					jParent.PushBack(jSubArray, jDocument.GetAllocator());
				}
				break;
		}
	}
}

const string MiniScript::serializeAsJson(const ScriptVariable& variable) {
	//
	switch(variable.getType()) {
		case TYPE_NULL:
		case TYPE_BOOLEAN:
		case TYPE_INTEGER:
		case TYPE_FLOAT:
		case TYPE_STRING:
		case TYPE_VECTOR2:
		case TYPE_VECTOR3:
		case TYPE_VECTOR4:
		case TYPE_QUATERNION:
		case TYPE_MATRIX3x3:
		case TYPE_MATRIX4x4:
		case TYPE_TRANSFORM:
			Console::println("MiniScript::serializeAsJson(): unsupported root variable type: " + variable.getTypeAsString() + ", the root variable type must be map, set or array");
			break;
		case TYPE_SET:
			{
				Document jRoot;
				jRoot.SetArray();
				const auto& value = variable.getSetValueReference();
				for (auto v: value) {
					jRoot.PushBack(Value(v, jRoot.GetAllocator()), jRoot.GetAllocator());
				}
				StringBuffer stringBuffer;
				Writer<StringBuffer> writer(stringBuffer);
				jRoot.Accept(writer);
				return stringBuffer.GetString();
			}
			break;
		case TYPE_ARRAY:
			{
				Document jRoot;
				jRoot.SetArray();
				serializeArrayAsJson(jRoot, jRoot, variable);
				StringBuffer stringBuffer;
				Writer<StringBuffer> writer(stringBuffer);
				jRoot.Accept(writer);
				return stringBuffer.GetString();
			}
			break;
		case TYPE_MAP:
			{
				Document jRoot;
				jRoot.SetObject();
				serializeMapAsJson(jRoot, variable);
				StringBuffer stringBuffer;
				Writer<StringBuffer> writer(stringBuffer);
				jRoot.Accept(writer);
				return stringBuffer.GetString();
			}
			break;
	}
	//
	return string();
}

const MiniScript::ScriptVariable MiniScript::deserializeMapJson(const Value& jObjectValue) {
	//
	ScriptVariable result;
	result.setType(MiniScript::TYPE_MAP);
	//
	auto jObject = jObjectValue.GetObject();
	//
	for (auto& jObjectIt: jObject) {
		const auto name = string(jObjectIt.name.GetString());
		const auto& value = jObjectIt.value;
		//
		if (value.IsNull() == true) {
			result.setMapValue(name, ScriptVariable());
		} else
		if (value.IsBool() == true) {
			result.setMapValue(name, ScriptVariable(value.GetBool()));
		} else
		if (value.IsInt64() == true) {
			result.setMapValue(name, ScriptVariable(value.GetInt64()));
		} else
		if (value.IsFloat() == true) {
			result.setMapValue(name, ScriptVariable(value.GetFloat()));
		} else
		if (value.IsString() == true) {
			result.setMapValue(name, ScriptVariable(string(value.GetString())));
		} else
		if (value.IsArray() == true) {
			result.setMapValue(name, deserializeArrayJson(value));
		} else
		if (value.IsObject() == true) {
			result.setMapValue(name, deserializeMapJson(value));
		} else {
			Console::println("MiniScript::deserializeMapJson(): unknown JSON data type for: " + name);
		}
	}
	//
	return result;
}

const MiniScript::ScriptVariable MiniScript::deserializeArrayJson(const Value& jArrayValue) {
	//
	ScriptVariable result;
	result.setType(MiniScript::TYPE_ARRAY);
	//
	auto jArray = jArrayValue.GetArray();
	for (auto i = 0; i < jArray.Size(); i++) {
		const auto& value = jArray[i];
		//
		if (value.IsNull() == true) {
			result.pushArrayValue(ScriptVariable());
		} else
		if (value.IsBool() == true) {
			result.pushArrayValue(ScriptVariable(value.GetBool()));
		} else
		if (value.IsInt64() == true) {
			result.pushArrayValue(ScriptVariable(value.GetInt64()));
		} else
		if (value.IsFloat() == true) {
			result.pushArrayValue(ScriptVariable(value.GetFloat()));
		} else
		if (value.IsString() == true) {
			result.pushArrayValue(ScriptVariable(string(value.GetString())));
		} else
		if (value.IsArray() == true) {
			result.pushArrayValue(deserializeArrayJson(value));
		} else
		if (value.IsObject() == true) {
			result.pushArrayValue(deserializeMapJson(value));
		} else {
			Console::println("MiniScript::deserializeArrayJson(): unknown JSON data type in JSON array @ " + to_string(i));
		}
	}
	//
	return result;
}

const MiniScript::ScriptVariable MiniScript::deserializeJson(const string& json) {
	//
	Document jRoot;
	jRoot.Parse(json.c_str());
	if (jRoot.IsArray() == true) {
		return deserializeArrayJson(jRoot);
	} else
	if (jRoot.IsObject() == true) {
		return deserializeMapJson(jRoot);
	} else {
		Console::println("MiniScript::deserializeJson(): unknown JSON root data type: root data type must be array or object");
		return ScriptVariable();
	}
}

