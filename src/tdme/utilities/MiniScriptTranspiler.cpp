#include <tdme/utilities/MiniScriptTranspiler.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix3x3.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector2.h>
#include <tdme/math/Vector3.h>
#include <tdme/math/Vector4.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::MiniScriptTranspiler;

using std::remove;
using std::sort;
using std::string;
using std::to_string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix3x3;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector2;
using tdme::math::Vector3;
using tdme::math::Vector4;
using tdme::utilities::Console;
using tdme::utilities::StringTools;

const unordered_set<string> MiniScriptTranspiler::getAllMethodNames(MiniScript* miniScript) {
	unordered_set<string> allMethods;
	for (auto scriptMethod: miniScript->getMethods()) {
		string className;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.empty() == true?0:className.size() + 1,
				scriptMethod->getMethodName().size());
		// first argument name of method must equal the name of the class
		if (scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != className) continue;
		// first argument of method must be of type of the class
		if (className != MiniScript::ScriptVariable::getClassName(scriptMethod->getArgumentTypes()[0].type) ||
			className != scriptMethod->getArgumentTypes()[0].name) continue;
		//
		allMethods.insert(method);
	}
	//
	return allMethods;
}

const vector<string> MiniScriptTranspiler::getAllMethodNamesSorted(MiniScript* miniScript) {
	auto allMethods = getAllMethodNames(miniScript);
	//
	vector<string> result;
	for (auto method: allMethods) result.push_back(method);
	sort(result.begin(), result.end());
	//
	return result;
}

const unordered_map<string, vector<string>> MiniScriptTranspiler::getAllClassesMethodNames(MiniScript* miniScript) {
	unordered_map<string, vector<string>> methodByClasses;
	for (auto scriptMethod: miniScript->getMethods()) {
		string className;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.empty() == true?0:className.size() + 1,
				scriptMethod->getMethodName().size());
		// first argument name of method must equal the name of the class
		if (scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != className) continue;
		// first argument of method must be of type of the class
		if (className != MiniScript::ScriptVariable::getClassName(scriptMethod->getArgumentTypes()[0].type) ||
			className != scriptMethod->getArgumentTypes()[0].name) continue;
		//
		methodByClasses[className].push_back(method);
	}
	//
	return methodByClasses;
}

bool MiniScriptTranspiler::transpileScriptStatement(MiniScript* miniScript, string& generatedCode, const MiniScript::ScriptSyntaxTreeNode& syntaxTree, const MiniScript::ScriptStatement& statement, int scriptConditionIdx, int scriptIdx, int& statementIdx, const unordered_map<string, vector<string>>& methodCodeMap, bool& scriptStateChanged, bool& scriptStopped, vector<string>& enabledNamedConditions, int depth, const vector<int>& argumentIndices, const string& returnValue, const string& injectCode, int additionalIndent) {
	//
	statementIdx++;
	auto currentStatementIdx = statementIdx;

	// indenting
	string minIndentString = "\t";
	string depthIndentString;
	for (auto i = 0; i < depth + additionalIndent; i++) depthIndentString+= "\t";

	//
	struct ArrayAccessStatement {
		ArrayAccessStatement(
			int argumentIdx,
			int statementIdx,
			int leftIdx,
			int rightIdx,
			string statementMethod
		):
			argumentIdx(argumentIdx),
			statementIdx(statementIdx),
			leftIdx(leftIdx),
			rightIdx(rightIdx),
			statementMethod(statementMethod)
		{}
		int argumentIdx;
		int statementIdx;
		int leftIdx;
		int rightIdx;
		string statementMethod;
	};

	//
	vector<ArrayAccessStatement> arrayAccessStatements;

	//
	switch (syntaxTree.type) {
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				// check script user functions
				auto scriptFunctionsIdx = miniScript->getFunctionScriptIdx(syntaxTree.value.getValueAsString());
				if (scriptFunctionsIdx != MiniScript::SCRIPTIDX_NONE) {
					// have a wrapping script.call call
					MiniScript::ScriptSyntaxTreeNode callSyntaxTreeNode;
					callSyntaxTreeNode.type = MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
					callSyntaxTreeNode.value = MiniScript::METHOD_SCRIPTCALL;
					// construct argument for name of function
					MiniScript::ScriptSyntaxTreeNode callArgumentSyntaxTreeNode;
					callArgumentSyntaxTreeNode.type = MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
					callArgumentSyntaxTreeNode.value = syntaxTree.value;
					// add argumnet for name of function
					callSyntaxTreeNode.arguments.push_back(callArgumentSyntaxTreeNode);
					// add original parameter to call syntaxTree
					for (const auto& argument: syntaxTree.arguments) {
						callSyntaxTreeNode.arguments.push_back(argument);
					}
					// asign script.call method
					auto method = miniScript->getMethod(callSyntaxTreeNode.value.getValueAsString());
					if (method == nullptr) {
						Console::println("MiniScriptTranspiler::transpileScriptStatement(): method code not found: '" + callSyntaxTreeNode.value.getValueAsString() + "'");
						return false;
					}
					callSyntaxTreeNode.method = method;
					return transpileScriptStatement(miniScript, generatedCode, callSyntaxTreeNode, statement, scriptConditionIdx, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, depth, argumentIndices, returnValue, injectCode, additionalIndent);
				} else {
					Console::println("MiniScriptTranspiler::transpileScriptStatement(): function not found: '" + syntaxTree.value.getValueAsString() + "'");
					return false;
				}
				//
				break;
			}
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			//
			if ((scriptConditionIdx != MiniScript::SCRIPTIDX_NONE ||
				scriptIdx != MiniScript::SCRIPTIDX_NONE) &&
				(syntaxTree.value.getValueAsString() == "getVariable" ||
				syntaxTree.value.getValueAsString() == "setVariable")) {
				//
				for (auto argumentIdx = 0; argumentIdx < syntaxTree.arguments.size(); argumentIdx++) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					auto argumentString = StringTools::replace(StringTools::replace(syntaxTree.arguments[argumentIdx].value.getValueAsString(), "\\", "\\\\"), "\"", "\\\"");
					auto arrayAccessStatementIdx = 0;
					auto arrayAccessStatementLeftIdx = -1;
					auto arrayAccessStatementRightIdx = -1;
					auto quote = '\0';
					auto bracketCount = 0;
					auto lc = '\0';
					for (auto i = 0; i < argumentString.size(); i++) {
						auto c = argumentString[i];
						// handle quotes
						if ((c == '"' || c == '\'') && lc != '\\') {
							if (quote == '\0') {
								quote = c;
							} else
							if (quote == c) {
								quote = '\0';
							}
						} else
						if (c == '[') {
							if (bracketCount == 0) arrayAccessStatementLeftIdx = i;
							bracketCount++;
						} else
						if (c == ']') {
							bracketCount--;
							if (bracketCount == 0) {
								arrayAccessStatementRightIdx = i;
								//
								auto arrayAccessStatementString = StringTools::substring(argumentString, arrayAccessStatementLeftIdx + 1, arrayAccessStatementRightIdx);
								// array append operator []
								if (arrayAccessStatementString.empty() == true) {
									//
									arrayAccessStatementIdx++;
									//
									continue;
								}
								//
								const auto& script = miniScript->getScripts()[scriptConditionIdx != MiniScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
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
								auto arrayAccessStatementMethod = methodName + "_array_access_statement_" + (scriptConditionIdx != MiniScript::SCRIPTIDX_NONE?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx);
								//
								generatedCode+= minIndentString + depthIndentString + "// we will use " + arrayAccessStatementMethod + "() to determine array access index"+ "\n";
								//
								arrayAccessStatements.emplace_back(
									argumentIdx,
									arrayAccessStatementIdx,
									arrayAccessStatementLeftIdx,
									arrayAccessStatementRightIdx,
									arrayAccessStatementMethod
								);
								//
								arrayAccessStatementIdx++;
							}
						}
						//
						lc = c;
					}
				}
			}
			//
			break;
		default:
			Console::println("MiniScriptTranspiler::transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": function or method call expected, but got literal or 'none' syntaxTree");
			return false;

	}

	//
	auto method = syntaxTree.value.getValueAsString();

	// find method code in method code map
	auto methodCodeMapIt = methodCodeMap.find(method);
	if (methodCodeMapIt == methodCodeMap.end()) {
		Console::println("MiniScriptTranspiler::transpileScriptStatement(): method code not found: '" + method + "'");
		return false;
	}
	const auto& methodCode = methodCodeMapIt->second;

	// script method
	auto scriptMethod = miniScript->getMethod(string(method));
	if (scriptMethod == nullptr) {
		Console::println("MiniScriptTranspiler::transpileScriptStatement(): method not found: '" + method + "'");
		return false;
	}

	// comment about current statement
	generatedCode+= minIndentString + depthIndentString;
	generatedCode+= "// " + (depth > 0?"depth = " + to_string(depth):"") + (argumentIndices.empty() == false?" / argument index = " + to_string(argumentIndices.back()):"");
	generatedCode+= depth > 0 || argumentIndices.empty() == false?": ":"";
	generatedCode+= syntaxTree.value.getValueAsString() + "(" + miniScript->getArgumentsAsString(syntaxTree.arguments) + ")";
	generatedCode+= "\n";

	// argument values header
	generatedCode+= minIndentString + depthIndentString + "{" + "\n";

	// argument indices
	auto parentArgumentIdx = argumentIndices.size() >= 2?argumentIndices[argumentIndices.size() - 2]:MiniScript::ARGUMENTIDX_NONE;
	auto argumentIdx = argumentIndices.empty() == false?argumentIndices.back():MiniScript::ARGUMENTIDX_NONE;

	// statement
	if (depth == 0) {
		generatedCode+= minIndentString + depthIndentString + "\t" + "// statement setup" + "\n";
		if (scriptConditionIdx != MiniScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const ScriptStatement& statement = scripts[" + to_string(scriptConditionIdx) + "].conditionStatement;" + "\n";
		} else
		if (scriptIdx != MiniScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const ScriptStatement& statement = scripts[" + to_string(scriptIdx) + "].statements[" + to_string(statement.statementIdx) + "];" + "\n";
		}
		generatedCode+= minIndentString + depthIndentString + "\t" + "getScriptState().statementIdx = statement.statementIdx;" + "\n";
	}

	// construct argument values
	{
		vector<string> argumentValuesCode;
		if (depth > 0) {
			argumentValuesCode.push_back("ScriptVariable& returnValue = argumentValuesD" + to_string(depth - 1) + (parentArgumentIdx != MiniScript::ARGUMENTIDX_NONE?"AIDX" + to_string(parentArgumentIdx):"") + "[" + to_string(argumentIdx) + "];");
		} else {
			argumentValuesCode.push_back("ScriptVariable returnValue;");
		}
		argumentValuesCode.push_back("array<ScriptVariable, " + to_string(syntaxTree.arguments.size()) + "> argumentValues {");

		// construct argument values
		if (syntaxTree.arguments.empty() == false) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "// required method code arguments" + "\n";
			auto argumentIdx = 0;
			for (const auto& argument: syntaxTree.arguments) {
				//
				auto nextArgumentIndices = argumentIndices;
				nextArgumentIndices.push_back(argumentIdx);
				//
				auto lastArgument = argumentIdx == syntaxTree.arguments.size() - 1;
				switch (argument.type) {
					case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
						{
							switch (argument.value.getType())  {
								case MiniScript::TYPE_NULL:
									argumentValuesCode.push_back(string() + "\t" + "ScriptVariable()" + (lastArgument == false?",":""));
									break;
								case MiniScript::TYPE_BOOLEAN:
									{
										bool value;
										argument.value.getBooleanValue(value);
										argumentValuesCode.push_back(string() + "\t" + "ScriptVariable(" + (value == true?"true":"false") + ")" + (lastArgument == false?",":""));
									}
									break;
								case MiniScript::TYPE_INTEGER:
									{
										int64_t value;
										argument.value.getIntegerValue(value);
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(static_cast<int64_t>(" + to_string(value) + "ll))" + (lastArgument == false?",":""));
									}
									break;
								case MiniScript::TYPE_FLOAT:
									{
										float value;
										argument.value.getFloatValue(value);
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(" + to_string(value) + "f)" + (lastArgument == false?",":""));
									}
									break;
								case MiniScript::TYPE_STRING:
									{
										string value;
										argument.value.getStringValue(value);
										value = StringTools::replace(StringTools::replace(value, "\\", "\\\\"), "\"", "\\\"");
										// take array access statements into account
										auto arrayAccessStatementOffset = 0;
										for (auto& arrayAccessStatement: arrayAccessStatements) {
											if (arrayAccessStatement.argumentIdx != argumentIdx) continue;
											string arrayAccessStatementMethodCall = "\" + " + arrayAccessStatement.statementMethod + "(statement).getValueAsString() + \"";
											value =
												StringTools::substring(value, 0, arrayAccessStatement.leftIdx + 1 + arrayAccessStatementOffset) +
												arrayAccessStatementMethodCall +
												StringTools::substring(value, arrayAccessStatement.rightIdx + arrayAccessStatementOffset, value.size());
											arrayAccessStatementOffset-= (arrayAccessStatement.rightIdx - (arrayAccessStatement.leftIdx + 1)) - arrayAccessStatementMethodCall.size();
										}
										//
										argumentValuesCode.push_back(string() + "\t" +  + "ScriptVariable(string(\"" + value + "\"))" + (lastArgument == false?",":""));
									}
									break;
								case MiniScript::TYPE_ARRAY:
								case MiniScript::TYPE_MAP:
								case MiniScript::TYPE_SET:
									{
										const auto& script = miniScript->getScripts()[scriptConditionIdx != MiniScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
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
										auto initializerMethod = methodName + "_initializer_" + (scriptConditionIdx != MiniScript::SCRIPTIDX_NONE?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + miniScript->getArgumentIndicesAsString(nextArgumentIndices, "_");
										argumentValuesCode.push_back(string() + "\t" + initializerMethod + "(statement)" + (lastArgument == false?",":""));
									}
									break;
								default:
									{
										Console::println("MiniScriptTranspiler::transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": '" + argument.value.getAsString() + "': unknown argument type: " + argument.value.getTypeAsString());
										break;
									}
							}
							break;
						}
					case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
						{
							argumentValuesCode.push_back(string() + "\t" + "ScriptVariable()" + (lastArgument == false?",":"") + " // argumentValues[" + to_string(argumentIdx) + "] --> returnValue of " + argument.value.getValueAsString() + "(" + miniScript->getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
						{
							argumentValuesCode.push_back(string() + "\t" + "ScriptVariable()" + (lastArgument == false?",":"") + " // argumentValues[" + to_string(argumentIdx) + "] --> returnValue of " + argument.value.getValueAsString() + "(" + miniScript->getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					default:
						break;
				}
				//
				argumentIdx++;
			}
		}
		// end of arguments initialization
		argumentValuesCode.push_back("};");

		//
		argumentValuesCode.push_back("array<ScriptVariable, " + to_string(syntaxTree.arguments.size()) + ">& argumentValuesD" + to_string(depth) + (argumentIdx != MiniScript::ARGUMENTIDX_NONE?"AIDX" + to_string(argumentIdx):"") + " = argumentValues;");

		// argument values header
		for (const auto& codeLine: argumentValuesCode) {
			generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + "\n";
		}
	}

	// enabled named conditions
	if (method == MiniScript::METHOD_ENABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::println("MiniScriptTranspiler::transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": " + MiniScript::METHOD_ENABLENAMEDCONDITION + "(): expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueAsString();
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
	if (method == MiniScript::METHOD_DISABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::println("MiniScriptTranspiler::transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": " + MiniScript::METHOD_DISABLENAMEDCONDITION + "(): expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueAsString();
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
		auto argumentIdx = 0;
		for (const auto& argument: syntaxTree.arguments) {
			switch (argument.type) {
				case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
				case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
					{
						//
						auto nextArgumentIndices = argumentIndices;
						nextArgumentIndices.push_back(argumentIdx);

						//
						if (transpileScriptStatement(miniScript, generatedCode, argument, statement, scriptConditionIdx, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, depth + 1, nextArgumentIndices, returnValue) == false) {
							Console::println("MiniScriptTranspiler::transpileScriptStatement(): transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": '" + syntaxTree.value.getValueAsString() + "(" + miniScript->getArgumentsAsString(syntaxTree.arguments) + ")" + "': transpile error");
						}
					}
					//
					break;
				default:
					//
					break;
			}
			argumentIdx++;
		}
	}

	// assign back arguments code for functions
	vector<string> assignBackCodeLines;
	if (method == MiniScript::METHOD_SCRIPTCALL && syntaxTree.arguments.empty() == false) {
		// check script user functions
		auto scriptIdx = miniScript->getFunctionScriptIdx(syntaxTree.arguments[0].value.getValueAsString());
		if (scriptIdx != MiniScript::SCRIPTIDX_NONE) {
			// assign back arguments starting from argument index 1 as 0 is function name
			auto argumentIdx = 1;
			for (const auto& argument: miniScript->getScripts()[scriptIdx].arguments) {
				//
				if (argumentIdx == syntaxTree.arguments.size()) {
					break;
				}
				//
				if (argument.assignBack == true) {
					const auto& assignBackArgument = syntaxTree.arguments[argumentIdx];
					if (assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
						assignBackArgument.value.getValueAsString() == "getVariable" &&
						assignBackArgument.arguments.empty() == false) {
						//
						auto variableName = assignBackArgument.arguments[0].value.getValueAsString();
						if (miniScript->isVariableAccess(variableName) == true) {
							assignBackCodeLines.push_back("setVariable(\"" + variableName + "\", argumentValues[" + to_string(argumentIdx) + "], &statement);");
						} else {
							Console::println("MiniScriptTranspiler::executeScriptStatement(): " + miniScript->getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
						}
					} else {
						Console::println(
							"MiniScriptTranspiler::executeScriptStatement(): " +
							miniScript->getStatementInformation(statement) +
							": Can not assign back argument value @ " +
							to_string(argumentIdx) +
							" to variable '" +
							assignBackArgument.value.getValueAsString() +
							(
								assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
								assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
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
			Console::println("MiniScriptTranspiler::transpileScriptStatement(): function not found: '" + syntaxTree.value.getValueAsString() + "'");
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
				if (assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&
					assignBackArgument.value.getValueAsString() == "getVariable" &&
					assignBackArgument.arguments.empty() == false) {
					//
					auto variableName = assignBackArgument.arguments[0].value.getValueAsString();
					if (miniScript->isVariableAccess(variableName) == true) {
						assignBackCodeLines.push_back("setVariable(\"" + variableName + "\", argumentValues[" + to_string(argumentIdx) + "], &statement);");
					} else {
						Console::println("MiniScriptTranspiler::transpileScriptStatement(): " + miniScript->getStatementInformation(statement) + ": Can not assign back argument value @ " + to_string(argumentIdx) + " to variable '" + variableName + "'");
					}
				} else {
					Console::println(
						"MiniScriptTranspiler::transpileScriptStatement(): " +
						miniScript->getStatementInformation(statement) +
						": Can not assign back argument value @ " +
						to_string(argumentIdx) +
						" to variable '" +
						assignBackArgument.value.getValueAsString() +
						(
							assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD ||
							assignBackArgument.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION
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

	// special case: inject EVALUATEMEMBERACCESS_MEMBER for "internal.script.evaluateMemberAccess"
	if (scriptMethod != nullptr && scriptMethod->getMethodName() == "internal.script.evaluateMemberAccess") {
		generatedCode+= minIndentString + depthIndentString + "\t" + "const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(syntaxTree.arguments[2].value.getValueAsString()) + ";\n";
	}

	// generate code
	generatedCode+= minIndentString + depthIndentString + "\t" + "// method code: " + string(method) + "\n";
	for (auto codeLine: methodCode) {
		codeLine = StringTools::replace(codeLine, "getMethodName()", "string(\"" + string(method) + "\")");
		// replace returns with gotos
		if (StringTools::regexMatch(codeLine, "[\\ \\t]*return[\\ \\t]*;.*") == true) {
			Console::println("MiniScriptTranspiler::transpileScriptStatement(): method '" + string(method) + "': return statement not supported!");
			return false;
		} else
		if (StringTools::regexMatch(codeLine, "[\\ \\t]*miniScript[\\ \\t]*->gotoStatementGoto[\\ \\t]*\\([\\ \\t]*statement[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true) {
			if (statement.gotoStatementIdx != MiniScript::STATEMENTIDX_NONE) {
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

bool MiniScriptTranspiler::transpile(MiniScript* miniScript, string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap) {
	if (scriptIdx < 0 || scriptIdx >= miniScript->getScripts().size()) {
		Console::println("MiniScriptTranspiler::transpile(): invalid script index");
		return false;
	}

	//
	const auto& script = miniScript->getScripts()[scriptIdx];

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

	Console::println("MiniScriptTranspiler::transpile(): transpiling code for " + scriptType + " = '" + script.condition + "', with name '" + script.name + "'");

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
	auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
	vector<string> enabledNamedConditions;
	auto scriptStateChanged = false;
	for (auto scriptStatementIdx = MiniScript::STATEMENTIDX_FIRST; scriptStatementIdx < script.statements.size(); scriptStatementIdx++) {
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
		transpileScriptStatement(miniScript, generatedCode, syntaxTree, statement, MiniScript::SCRIPTIDX_NONE, scriptIdx, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions);
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
	generatedCodeHeader+= methodIndent + "if (miniScriptGotoStatementIdx != STATEMENTIDX_NONE && miniScriptGotoStatementIdx != STATEMENTIDX_FIRST) Console::println(\"MiniScriptTranspiler::" + methodName + "(): Can not go to statement \" + to_string(miniScriptGotoStatementIdx));" + "\n";
	//
	generatedCode = generatedCodeHeader + generatedCode;
	return true;
}

bool MiniScriptTranspiler::transpileScriptCondition(MiniScript* miniScript, string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const string& returnValue, const string& injectCode, int depth) {
	if (scriptIdx < 0 || scriptIdx >= miniScript->getScripts().size()) {
		Console::println("MiniScriptTranspiler::transpileScriptCondition(): invalid script index");
		return false;
	}

	//
	const auto& script = miniScript->getScripts()[scriptIdx];

	//
	Console::println("MiniScriptTranspiler::transpile(): transpiling code condition for condition = '" + script.condition + "', with name '" + script.name + "'");

	//
	auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
	auto scriptStateChanged = false;
	auto scriptStopped = false;
	vector<string >enabledNamedConditions;
	transpileScriptStatement(miniScript, generatedCode, script.conditionSyntaxTree, script.conditionStatement, scriptIdx, MiniScript::SCRIPTIDX_NONE, statementIdx, methodCodeMap, scriptStateChanged, scriptStopped, enabledNamedConditions, 0, {}, returnValue, injectCode, depth + 1);

	//
	generatedCode+= "\t\n";

	//
	return true;
}

const string MiniScriptTranspiler::createSourceCode(const MiniScript::ScriptSyntaxTreeNode& syntaxTreeNode) {
	//
	string result;
	switch (syntaxTreeNode.type) {
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTreeNode.value.getType()) {
					case MiniScript::TYPE_NULL:
						{
							result+= (result.empty() == false?", ":"") + string("<VOID>");
							break;
						}
					case MiniScript::TYPE_BOOLEAN:
					case MiniScript::TYPE_INTEGER:
					case MiniScript::TYPE_FLOAT:
						{
							result+= (result.empty() == false?", ":"") + syntaxTreeNode.value.getValueAsString();
							break;
						}
					case MiniScript::TYPE_STRING:
						{
							result+= (result.empty() == false?", ":"") + string("\"") + syntaxTreeNode.value.getValueAsString() + string("\"");
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
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto endElse = syntaxTreeNode.value.getValueAsString() == "end" || syntaxTreeNode.value.getValueAsString() == "else";
				result+= syntaxTreeNode.value.getValueAsString();
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

const string MiniScriptTranspiler::createSourceCode(MiniScript::Script::ScriptType scriptType, const string& condition, const vector<MiniScript::Script::ScriptArgument>& arguments, const string& name, const MiniScript::ScriptSyntaxTreeNode& conditionSyntaxTree, const vector<MiniScript::ScriptSyntaxTreeNode>& syntaxTree) {
	//
	string result;
	//
	switch(scriptType) {
		case MiniScript::Script::SCRIPTTYPE_FUNCTION: {
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
		case MiniScript::Script::SCRIPTTYPE_ON:
			{
				result+= "on: ";
				if (condition.empty() == false) {
					result+= condition;
				}
				break;
			}
		case MiniScript::Script::SCRIPTTYPE_ONENABLED:
			{
				result+= "on-enabled: "; break;
				if (condition.empty() == false) {
					result+= condition;
				}
			}
	}
	if (conditionSyntaxTree.type != MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE)
		result+= createSourceCode(conditionSyntaxTree);
	if (name.empty() == false) {
		result+= " := " + name + "\n";
	} else {
		result+= "\n";
	}
	//
	auto indent = 1;
	for (const auto& syntaxTreeNode: syntaxTree) {
		if (syntaxTreeNode.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueAsString() == "if") indent+= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "elseif") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "else") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "end") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "forTime") indent+= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "forCondition") indent+= 0;
		}
		for (auto i = 0; i < indent; i++) result+= "\t";
		result+= createSourceCode(syntaxTreeNode) + "\n";
		if (syntaxTreeNode.type == MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueAsString() == "if") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "elseif") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "else") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "end") indent-= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "forTime") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "forCondition") indent+= 1;
		}
	}
	return result;
}

const string MiniScriptTranspiler::createSourceCode(MiniScript* miniScript) {
	string result;
	// create source code
	for (const auto& script: miniScript->getScripts()) {
		result+= createSourceCode(script.scriptType, script.emitCondition == true?script.condition:string(), script.arguments, script.name, script.conditionSyntaxTree, script.syntaxTree);
	}
	//
	return result;
}
