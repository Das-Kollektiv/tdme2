#include <miniscript/miniscript/MiniScript.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
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

#include <miniscript/miniscript/MiniScript.h>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/miniscript/ArrayMethods.h>
#include <miniscript/miniscript/BaseMethods.h>
#include <miniscript/miniscript/ConsoleMethods.h>
#include <miniscript/miniscript/JSONMethods.h>
#include <miniscript/miniscript/MapMethods.h>
#include <miniscript/miniscript/MathMethods.h>
#include <miniscript/miniscript/ScriptMethods.h>
#include <miniscript/miniscript/SetMethods.h>
#include <miniscript/miniscript/StringMethods.h>
#include <miniscript/miniscript/TimeMethods.h>
#include <miniscript/miniscript/XMLMethods.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/FileSystem.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/StringTokenizer.h>
#include <miniscript/utilities/StringTools.h>
#include <miniscript/utilities/SHA256.h>
#include <miniscript/utilities/Time.h>

using std::find;
using std::ifstream;
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
using std::stringstream;
using std::to_string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using miniscript::miniscript::MiniScript;

using miniscript::math::Math;
using miniscript::miniscript::ArrayMethods;
using miniscript::miniscript::BaseMethods;
using miniscript::miniscript::ConsoleMethods;
using miniscript::miniscript::JSONMethods;
using miniscript::miniscript::MapMethods;
using miniscript::miniscript::MathMethods;
using miniscript::miniscript::ScriptMethods;
using miniscript::miniscript::SetMethods;
using miniscript::miniscript::StringMethods;
using miniscript::miniscript::TimeMethods;
using miniscript::miniscript::XMLMethods;
using miniscript::utilities::Character;
using miniscript::utilities::Console;
using miniscript::utilities::FileSystem;
using miniscript::utilities::Integer;
using miniscript::utilities::StringTokenizer;
using miniscript::utilities::StringTools;
using miniscript::utilities::SHA256;
using miniscript::utilities::Time;

const string MiniScript::OPERATOR_CHARS = "+-!~/%<>=&^|";
vector<MiniScript::ScriptDataType*> MiniScript::scriptDataTypes;
const string MiniScript::METHOD_SCRIPTCALL = "script.call";
const string MiniScript::METHOD_ENABLENAMEDCONDITION = "script.enableNamedCondition";
const string MiniScript::METHOD_DISABLENAMEDCONDITION = "script.disableNamedCondition";

const string MiniScript::ScriptVariable::CLASSNAME_NONE = "";
const string MiniScript::ScriptVariable::CLASSNAME_STRING = "string";
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


const string MiniScript::getBaseClass() {
	return "miniscript::miniscript::MiniScript";
}

const vector<string> MiniScript::getTranspilationUnits() {
	return {
		"src/miniscript/miniscript/MiniScript.cpp",
		"src/miniscript/miniscript/MathMethods.cpp"
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

void MiniScript::registerDataType(ScriptDataType* scriptDataType) {
	scriptDataType->setType(TYPE_PSEUDO_CUSTOM_DATATYPES + scriptDataTypes.size());
	scriptDataTypes.push_back(scriptDataType);
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
						case TYPE_PSEUDO_NUMBER:
							{
								float floatValue;
								argumentOk = getFloatValue(argumentValues, argumentIdx, floatValue, argumentType.optional);
								break;
							}
						case TYPE_PSEUDO_MIXED:
							{
								argumentOk = true;
								break;
							}
						case TYPE_STRING:
							{
								string stringValue;
								argumentOk = getStringValue(argumentValues, argumentIdx, stringValue, argumentType.optional);
							}
							break;
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
						default:
							{
								// custom data types
								argumentOk =
									argumentIdx < 0 || argumentIdx >= argumentValues.size()?
										argumentType.optional:
										argumentValues[argumentIdx].getType() == argumentType.type;
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
								if (StringTools::startsWith(argumentNameTrimmed, "&") == true) {
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
		scriptCode = FileSystem::getContentAsString(pathName, fileName);
	} catch (FileSystem::FileSystemException& fse)	{
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
				if (argument.reference == true) argumentsString+= "&";
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
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "statement", .optional = false, .reference = false, .nullable = false }
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
						{ .type = ScriptVariableType::TYPE_STRING, .name = "variable", .optional = false, .reference = false, .nullable = true },
						{ .type = ScriptVariableType::TYPE_PSEUDO_MIXED, .name = "this", .optional = false, .reference = false, .nullable = true },
						{ .type = ScriptVariableType::TYPE_STRING, .name = "member", .optional = false, .reference = false, .nullable = false }
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
					const auto& className = argumentValues[1].getClassName();
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

	// register math methods
	miniScriptMath = make_unique<MathMethods>(this);
	miniScriptMath->registerMethods();

	// register base methods
	BaseMethods::registerMethods(this);

	// register string methods
	StringMethods::registerMethods(this);

	// register array methods
	ArrayMethods::registerMethods(this);

	// register map methods
	MapMethods::registerMethods(this);

	// register set methods
	SetMethods::registerMethods(this);

	// register script methods
	ScriptMethods::registerMethods(this);

	// register script methods
	TimeMethods::registerMethods(this);

	// register JSON methods
	JSONMethods::registerMethods(this);

	// register XML methods
	XMLMethods::registerMethods(this);

	// register console methods
	ConsoleMethods::registerMethods(this);

	//
	for (const auto scriptDataType: scriptDataTypes) {
		if (scriptDataType->isMathDataType() == true) miniScriptMath->registerDataType(scriptDataType);
		scriptDataType->registerMethods(this);
	}

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
	for (const auto& [variableName, variable]: getRootScriptState().variables) delete variable;
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
										functionScriptCode = "function: " + functionName + "(&$this";
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
