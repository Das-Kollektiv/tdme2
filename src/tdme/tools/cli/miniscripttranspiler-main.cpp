#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/MiniScriptTranspiler.h>
#include <tdme/utilities/StringTools.h>

using std::find;
using std::map;
using std::set;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::MiniScriptTranspiler;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {
class MiniscriptTranspiler {
public:
static void gatherMethodCode(const vector<string>& miniScriptExtensionsCode, const string& className, int registerLine, unordered_map<string, vector<string>>& methodCodeMap) {
	// TODO: this is a bit ugly and can be improved a lot, lets see and get this to work first
	auto classDefinitionLine = -1;
	// get class definition start line
	for (auto i = registerLine; i >= 0; i--) {
		const auto& line = miniScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		if (StringTools::regexMatch(trimmedLine, "class[\\ \\t]+" + className + "[\\ \\t]*:.*") == true) {
			classDefinitionLine = i;
			break;
		}
	}
	// nope
	if (classDefinitionLine == -1) {
		Console::println("gatherMethodCode(): did not found '" + className + "' definition");
		return;
	}
	//
	auto curlyBracketCount = 0;
	auto finished = false;
	auto haveExecuteMethodDeclaration = false;
	auto executeMethodCurlyBracketStart = -1;
	auto haveGetMethodNameDeclaration = false;
	auto getMethodNameCurlyBracketStart = -1;
	vector<string> executeMethodCode;
	string getMethodNameCode;
	for (auto i = classDefinitionLine; finished == false && i < miniScriptExtensionsCode.size(); i++) {
		const auto& line = miniScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		// have getMethodName declaration, with following body
		if (StringTools::regexMatch(trimmedLine, "const[\\ \\t]+string[\\ \\t]+getMethodName()[\\ \\t]*\\(.*") == true) {
			haveGetMethodNameDeclaration = true;
		}
		// have executeMethod declaration, with following body
		if (StringTools::regexMatch(trimmedLine, "void[\\ \\t]+executeMethod[\\ \\t]*\\(.*") == true) {
			haveExecuteMethodDeclaration = true;
		}
		//
		for (auto j = 0; j < trimmedLine.size(); j++) {
			auto c = trimmedLine[j];
			if (c == '{') {
				curlyBracketCount++;
				// new code block,
				// 	if we have the declaration mark this curly bracket as executeMethod implementation start curly bracket
				if (haveExecuteMethodDeclaration == true) {
					executeMethodCurlyBracketStart = curlyBracketCount;
				}
				// 	if we have the declaration mark this curly bracket as getMethodName implementation start curly bracket
				if (haveGetMethodNameDeclaration == true) {
					getMethodNameCurlyBracketStart = curlyBracketCount;
				}
			} else
			if (c == '}') {
				// do we just leave our getMethodName implementation?
				if (getMethodNameCurlyBracketStart != -1 && curlyBracketCount == getMethodNameCurlyBracketStart) {
					// yup
					getMethodNameCurlyBracketStart = -1;
				}
				// do we just leave our executeMethod implementation?
				if (executeMethodCurlyBracketStart != -1 && curlyBracketCount == executeMethodCurlyBracketStart) {
					// yup
					executeMethodCurlyBracketStart = -1;
				}
				//
				curlyBracketCount--;
				// get out of here :D
				if (curlyBracketCount <= 0) {
					finished = true;
					break;
				}
			}
		}
		// is this getMethodName code?
		if (haveGetMethodNameDeclaration == false && getMethodNameCurlyBracketStart != -1 && curlyBracketCount >= getMethodNameCurlyBracketStart) {
			getMethodNameCode+= trimmedLine;
		}
		// is this executeMethod code?
		if (haveExecuteMethodDeclaration == false && executeMethodCurlyBracketStart != -1 && curlyBracketCount >= executeMethodCurlyBracketStart) {
			executeMethodCode.push_back(line);
		}
		// do we still process getMethodName declaration
		if (haveGetMethodNameDeclaration == true) {
			// ok unset
			haveGetMethodNameDeclaration = false;
		}
		// do we still process executeMethod declaration
		if (haveExecuteMethodDeclaration == true) {
			// ok unset
			haveExecuteMethodDeclaration = false;
		}
	}

	// determine method name
	string methodName;
	{
		auto haveMethodName = false;
		for (auto i = 0; i < getMethodNameCode.size(); i++) {
			auto c = getMethodNameCode[i];
			if (c == '"') {
				if (haveMethodName == false) haveMethodName = true; else
					break;
			} else
			if (haveMethodName == true) {
				methodName+= c;
			}
		}
	}

	// find min indent from method code and depth indent
	int minIndent = Integer::MAX_VALUE;
	for (const auto& codeLine: executeMethodCode) {
		auto indent = 0;
		for (auto i = 0; i < codeLine.size(); i++) {
			auto c = codeLine[i];
			if (c == '\t') {
				indent++;
			} else {
				break;
			}
		}
		minIndent = Math::min(minIndent, indent);
	}

	// remove indent
	for (auto& codeLine: executeMethodCode) {
		codeLine = StringTools::substring(codeLine, minIndent);
	}

	//
	auto methodCodeMapIt = methodCodeMap.find(methodName);
	if (methodCodeMapIt != methodCodeMap.end()) {
		Console::println("gatherMethodCode(): Not registering method with methodName: '" + methodName + "': method already registered");
		return;
	}

	//
	Console::println("gatherMethodCode(): registering method with methodName: '" + methodName + "'");

	//
	methodCodeMap[methodName] = executeMethodCode;
}

static void createArrayAccessMethods(MiniScript* miniScript, string& generatedDeclarations, string& generatedDefinitions, const string& miniScriptClassName, const string& methodName, const MiniScript::ScriptSyntaxTreeNode& syntaxTree, const MiniScript::ScriptStatement& statement, const unordered_map<string, vector<string>>& methodCodeMap, const unordered_set<string>& allMethods, bool condition, const vector<int>& argumentIndices = {}, int depth = 0) {
	string headerIndent = "\t";

	//
	switch (syntaxTree.type) {
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				if (syntaxTree.value.getValueAsString() == "getVariable" ||
					syntaxTree.value.getValueAsString() == "setVariable") {
					//
					for (auto argumentIdx = 0; argumentIdx < syntaxTree.arguments.size(); argumentIdx++) {
						auto argumentString = StringTools::replace(StringTools::replace(syntaxTree.arguments[argumentIdx].value.getValueAsString(), "\\", "\\\\"), "\"", "\\\"");
						//
						auto nextArgumentIndices = argumentIndices;
						nextArgumentIndices.push_back(argumentIdx);
						// ignore array and map initializers
						if (StringTools::startsWith(argumentString, "[") == true ||
							StringTools::startsWith(argumentString, "{") == true) continue;
						//
						auto arrayAccessStatementIdx = 0;
						auto arrayAccessStatementLeftIdx = -1;
						auto arrayAccessStatementRightIdx = -1;
						auto quote = '\0';
						auto bracketCount = 0;
						for (auto i = 0; i < argumentString.size(); i++) {
							auto c = argumentString[i];
							// handle quotes
							if (quote != '\0') {
								// unset quote if closed
								// also we can ignore content of quote blocks
								if (c == quote) {
									quote = '\0';
								}
							} else
							if (c == '"' || c == '\'') {
								quote = c;
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
									// check if literal
									MiniScript::ScriptVariable arrayAccessStatementAsScriptVariable;
									//
									arrayAccessStatementAsScriptVariable.setImplicitTypedValue(arrayAccessStatementString, miniScript, statement);
									switch (arrayAccessStatementAsScriptVariable.getType()) {
										case MiniScript::TYPE_BOOLEAN:
											{
												bool booleanValue;
												if (arrayAccessStatementAsScriptVariable.getBooleanValue(booleanValue) == true) {
													generatedDeclarations+= headerIndent + "/**\n";
													generatedDeclarations+= headerIndent + " * Miniscript transpilation for a " + (condition == true?"condition":"statement") + " array access statement for method '" + methodName + "', statement index " + to_string(statement.statementIdx) + ", argument indices " + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDeclarations+= headerIndent + " * @param statement statement" + "\n";
													generatedDeclarations+= headerIndent + " * @return array index" + "\n";
													generatedDeclarations+= headerIndent + " */" + "\n";
													generatedDeclarations+= headerIndent + "inline ScriptVariable " + methodName + "_array_access_statement_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + "(const ScriptStatement& statement) {" + "\n";
													generatedDeclarations+= headerIndent + "	return ScriptVariable(" + (booleanValue == true?"true":"false") + ");" + "\n";
													generatedDeclarations+= headerIndent + "}" + "\n\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										case MiniScript::TYPE_INTEGER:
											{
												int64_t integerValue;
												if (arrayAccessStatementAsScriptVariable.getIntegerValue(integerValue) == true) {
													generatedDeclarations+= headerIndent + "/**\n";
													generatedDeclarations+= headerIndent + " * Miniscript transpilation for a " + (condition == true?"condition":"statement") + " array access statement for method '" + methodName + "', statement index " + to_string(statement.statementIdx) + ", argument indices " + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDeclarations+= headerIndent + " * @param statement statement" + "\n";
													generatedDeclarations+= headerIndent + " * @return array index" + "\n";
													generatedDeclarations+= headerIndent + " */" + "\n";
													generatedDeclarations+= headerIndent + "inline ScriptVariable " + methodName + "_array_access_statement_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + "(const ScriptStatement& statement) {" + "\n";
													generatedDeclarations+= headerIndent + "	return ScriptVariable(static_cast<int64_t>(" + to_string(integerValue) + "ll));" + "\n";
													generatedDeclarations+= headerIndent + "}" + "\n\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										case MiniScript::TYPE_FLOAT:
											{
												float floatValue;
												if (arrayAccessStatementAsScriptVariable.getFloatValue(floatValue) == true) {
													generatedDeclarations+= headerIndent + "/**\n";
													generatedDeclarations+= headerIndent + " * Miniscript transpilation for a " + (condition == true?"condition":"statement") + " array access statement for method '" + methodName + "', statement index " + to_string(statement.statementIdx) + ", argument indices " + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDeclarations+= headerIndent + " * @param statement statement" + "\n";
													generatedDeclarations+= headerIndent + " * @return array index" + "\n";
													generatedDeclarations+= headerIndent + " */" + "\n";
													generatedDeclarations+= headerIndent + "inline ScriptVariable " + methodName + "_array_access_statement_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + "(const ScriptStatement& statement) {" + "\n";
													generatedDeclarations+= headerIndent + "	return ScriptVariable(static_cast<int64_t>(" + to_string(static_cast<int64_t>(floatValue)) + "ll));" + "\n";
													generatedDeclarations+= headerIndent + "}" + "\n\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										default:
											break;
									}
									// variable?
									if (StringTools::startsWith(arrayAccessStatementString, "$") == true) arrayAccessStatementString = "getVariable(\"" + arrayAccessStatementString + "\")";
									// parse array access statment at current index
									string_view arrayAccessMethodName;
									vector<string_view> arrayAccessArguments;
									string accessObjectMemberStatement;
									// create a pseudo statement (information)
									MiniScript::ScriptStatement arrayAccessStatement(
										statement.line,
										statement.statementIdx,
										arrayAccessStatementString,
										arrayAccessStatementString,
										MiniScript::STATEMENTIDX_NONE
									);
									// parse script statement
									if (miniScript->parseScriptStatement(string_view(arrayAccessStatementString), arrayAccessMethodName, arrayAccessArguments, arrayAccessStatement, accessObjectMemberStatement) == false) {
										break;
									}
									// create syntax tree for this array access
									MiniScript::ScriptSyntaxTreeNode arrayAccessSyntaxTree;
									if (miniScript->createScriptStatementSyntaxTree(arrayAccessMethodName, arrayAccessArguments, arrayAccessStatement, arrayAccessSyntaxTree) == false) {
										break;
									}

									//
									string transpiledCode;
									auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
									auto scriptStateChanged = false;
									auto scriptStopped = false;
									vector<string >enabledNamedConditions;
									MiniScriptTranspiler::transpileScriptStatement(
										miniScript,
										transpiledCode,
										arrayAccessSyntaxTree,
										arrayAccessStatement,
										MiniScript::SCRIPTIDX_NONE,
										MiniScript::SCRIPTIDX_NONE,
										statementIdx,
										methodCodeMap,
										allMethods,
										scriptStateChanged,
										scriptStopped,
										enabledNamedConditions,
										0,
										{},
										"ScriptVariable()",
										"return returnValue;"
									);
									generatedDeclarations+= headerIndent + "/**\n";
									generatedDeclarations+= headerIndent + " * Miniscript transpilation for a " + (condition == true?"condition":"statement") + " array access statement for method '" + methodName + "', statement index " + to_string(statement.statementIdx) + ", argument indices " + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
									generatedDeclarations+= headerIndent + " * @param statement statement" + "\n";
									generatedDeclarations+= headerIndent + " * @return array index" + "\n";
									generatedDeclarations+= headerIndent + " */" + "\n";
									generatedDeclarations+= headerIndent + "ScriptVariable " + methodName + "_array_access_statement_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + "(const ScriptStatement& statement);" + "\n\n";
									generatedDefinitions+= string() + "inline MiniScript::ScriptVariable " + miniScriptClassName + "::" + methodName + "_array_access_statement_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + "(const ScriptStatement& statement) {" + "\n";
									generatedDefinitions+= string() + "	// Miniscript setup" + "\n";
									generatedDefinitions+= string() + "	auto miniScript = this;" + "\n";
									generatedDefinitions+= string() + "	//" + "\n";;
									generatedDefinitions+= transpiledCode;
									generatedDefinitions+= string() + "}" + "\n\n";
									//
									arrayAccessStatementIdx++;
								}
							}
						}
					}
				}
				//
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					createArrayAccessMethods(
						miniScript,
						generatedDeclarations,
						generatedDefinitions,
						miniScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth + 1
					);
					//
					argumentIdx++;
				}
			}
			break;
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto argumentIdx = 1;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					createArrayAccessMethods(
						miniScript,
						generatedDeclarations,
						generatedDefinitions,
						miniScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth + 1
					);
					//
					argumentIdx++;
				}
				//
				break;
			}
		default:
			break;
	}
}

static void generateMiniScriptEvaluateMemberAccessArrays(MiniScript* miniScript, vector<string>& declarations, vector<string>& definitions) {
	auto scriptMethods = miniScript->getMethods();
	auto allMethods = MiniScriptTranspiler::getAllMethodNamesSorted(miniScript);
	auto methodsByClasses = MiniScriptTranspiler::getAllClassesMethodNames(miniScript);
	declarations.push_back("// evaluate member access constants");
	declarations.push_back("static constexpr int EVALUATEMEMBERACCESSARRAYIDX_NONE { -1 };");
	auto methodIdx = 0;
	for (const auto& method: allMethods) {
		declarations.push_back("static constexpr int EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(method) + " { " + to_string(methodIdx) + " };");
		methodIdx++;
	}
	declarations.push_back("");
	declarations.push_back("// evaluate member access arrays");
	declarations.push_back(
		"array<array<ScriptMethod*, " +
		to_string(methodIdx) +
		">, " +
		to_string((static_cast<int>(MiniScript::TYPE_SET) - static_cast<int>(MiniScript::TYPE_STRING)) + 1) +
		"> evaluateMemberAccessArrays {};"
	);
	declarations.push_back("// evaluate member access arrays");
	definitions.push_back("evaluateMemberAccessArrays = {};");
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); typeIdx <= static_cast<int>(MiniScript::TYPE_SET); typeIdx++) {
		const auto& className = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
		const auto& methods = methodsByClasses[className];
		auto methodIdx = 0;
		for (const auto& method: allMethods) {
			//
			if (std::find(methods.begin(), methods.end(), method) == methods.end()) {
				methodIdx++;
				continue;
			}
			//
			definitions.push_back("evaluateMemberAccessArrays[" + to_string(typeIdx - static_cast<int>(MiniScript::TYPE_STRING)) + "][" + "EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(method) + "] = getMethod(\"" + className + "." + method + "\");");
			methodIdx++;
		}
	}
}

static void createArrayMapSetVariable(MiniScript* miniScript, const MiniScript::ScriptVariable& variable, const unordered_map<string, vector<string>>& methodCodeMap, const unordered_set<string>& allMethods, const string& methodName, bool condition, const string& miniScriptClassName, string& generatedDeclarations, string& generatedDefinitions, int depth = 0, int initializerDepth = 0, const string& postStatement = string()) {
	string headerIndent = "\t";
	auto indent = StringTools::indent(string(), "\t", initializerDepth + 1);
	switch (variable.getType()) {
		case MiniScript::TYPE_NULL:
			{
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_BOOLEAN:
			{
				bool value;
				variable.getBooleanValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + "(" + (value == true?"true":"false") + ");" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_INTEGER:
			{
				int64_t value;
				variable.getIntegerValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + "(static_cast<int64_t>(" + to_string(value) + "ll));" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_FLOAT:
			{
				float value;
				variable.getFloatValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + "(" + to_string(value) + "f);" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_STRING:
			{
				string value;
				variable.getStringValue(value);
				value = StringTools::replace(StringTools::replace(value, "\\", "\\\\"), "\"", "\\\"");
				//
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + "(string(\"" + value + "\"));" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_ARRAY:
			{
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_ARRAY);" + "\n";
				const auto arrayValue = variable.getArrayPointer();
				for (const auto& arrayEntry: *arrayValue) {
					createArrayMapSetVariable(
						miniScript,
						arrayEntry,
						methodCodeMap,
						allMethods,
						methodName,
						condition,
						miniScriptClassName,
						generatedDeclarations,
						generatedDefinitions,
						depth,
						initializerDepth + 1,
						"variableD" + to_string(initializerDepth) + ".pushArrayValue(variableD" + to_string(initializerDepth + 1) + ");"
					);
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_MAP:
			{
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_MAP);" + "\n";
				const auto mapValue = variable.getMapPointer();
				for (const auto& [mapEntryName, mapEntryValue]: *mapValue) {
					auto mapEntryNameEscaped = StringTools::replace(StringTools::replace(mapEntryName, "\\", "\\\\"), "\"", "\\\"");
					createArrayMapSetVariable(
						miniScript,
						mapEntryValue,
						methodCodeMap,
						allMethods,
						methodName,
						condition,
						miniScriptClassName,
						generatedDeclarations,
						generatedDefinitions,
						depth,
						initializerDepth + 1,
						"variableD" + to_string(initializerDepth) + ".setMapValue(\"" + mapEntryNameEscaped + "\", variableD" + to_string(initializerDepth + 1) + ");"
					);
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_SET:
			{
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_SET);" + "\n";
				const auto setValue = variable.getSetPointer();
				for (const auto& key: *setValue) {
					generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".insertSetKey(\"" + key + "\");" + "\n";
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MiniScript::TYPE_FUNCTION_CALL:
			{
				//
				const auto& statement = variable.getInitializer()->getStatement();
				string transpiledCode;
				auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
				auto scriptStateChanged = false;
				auto scriptStopped = false;
				vector<string>enabledNamedConditions;
				MiniScriptTranspiler::transpileScriptStatement(
					miniScript,
					transpiledCode,
					*variable.getInitializer()->getSyntaxTree(),
					statement,
					MiniScript::SCRIPTIDX_NONE,
					MiniScript::SCRIPTIDX_NONE,
					statementIdx,
					methodCodeMap,
					allMethods,
					scriptStateChanged,
					scriptStopped,
					enabledNamedConditions,
					0,
					{},
					"ScriptVariable()",
					"const auto& variableD" + to_string(initializerDepth) + " = returnValue; " + postStatement + "\n", 1
				);
				generatedDefinitions+= transpiledCode;
			}
			break;
		case MiniScript::TYPE_FUNCTION_ASSIGNMENT:
			{
				string value;
				variable.getStringValue(value);
				value = StringTools::replace(StringTools::replace(value, "\\", "\\\\"), "\"", "\\\"");
				//
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "ScriptVariable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setFunctionAssignment(\"" + value + "\");" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		default: break;
	}
}

static void createArrayMapSetInitializer(MiniScript* miniScript, string& generatedDeclarations, string& generatedDefinitions, const string& miniScriptClassName, const string& methodName, const MiniScript::ScriptSyntaxTreeNode& syntaxTree, const MiniScript::ScriptStatement& statement, const unordered_map<string, vector<string>>& methodCodeMap, const unordered_set<string>& allMethods, bool condition, const vector<int>& argumentIndices = {}, int depth = 0) {
	string headerIndent = "\t";

	//
	switch (syntaxTree.type) {
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTree.value.getType()) {
					case MiniScript::TYPE_ARRAY:
					case MiniScript::TYPE_MAP:
					case MiniScript::TYPE_SET:
						{
							generatedDeclarations+= headerIndent + "/**\n";
							generatedDeclarations+= headerIndent + " * Miniscript transpilation for a " + (condition == true?"condition":"statement") + " array/map/set initializer for method '" + methodName + "', statement index " + to_string(statement.statementIdx) + ", argument indices " + MiniScript::getArgumentIndicesAsString(argumentIndices, ", ")  + "\n";
							generatedDeclarations+= headerIndent + " * @param statement statement" + "\n";
							generatedDeclarations+= headerIndent + " * @return initialized variable" + "\n";
							generatedDeclarations+= headerIndent + " */" + "\n";
							generatedDeclarations+= headerIndent + "ScriptVariable " + methodName + "_initializer_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(argumentIndices, "_") + "(const ScriptStatement& statement);" + "\n\n";
							//
							string generatedInitializerDeclarations;
							string generatedInitializerDefinitions;
							//
							createArrayMapSetVariable(
								miniScript,
								syntaxTree.value,
								methodCodeMap,
								allMethods,
								methodName,
								condition,
								miniScriptClassName,
								generatedInitializerDeclarations,
								generatedInitializerDefinitions,
								depth,
								0,
								"return variableD0;"
							);
							//
							generatedDefinitions+= "\n";
							generatedDefinitions+= string() + "inline MiniScript::ScriptVariable " + miniScriptClassName + "::" + methodName + "_initializer_" + (condition == true?"c":"s") + "_" + to_string(statement.statementIdx) + "_" + MiniScript::getArgumentIndicesAsString(argumentIndices, "_") + "(const ScriptStatement& statement) {" + "\n";
							generatedDefinitions+= string() + "	// Miniscript setup" + "\n";
							generatedDefinitions+= string() + "	auto miniScript = this;" + "\n";
							generatedDefinitions+= string() + "	//" + "\n";;
							generatedDefinitions+= generatedInitializerDefinitions;
							generatedDefinitions+= string() + "}" + "\n";
							//
							break;
						}
					default: break;
				}
				//
				break;
			}
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					createArrayMapSetInitializer(
						miniScript,
						generatedDeclarations,
						generatedDefinitions,
						miniScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth + 1
					);
					//
					argumentIdx++;
				}
				break;
			}
		case MiniScript::ScriptSyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto argumentIdx = 1; // TODO: check me!
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					createArrayMapSetInitializer(
						miniScript,
						generatedDeclarations,
						generatedDefinitions,
						miniScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth + 1
					);
					//
					argumentIdx++;
				}
				//
				break;
			}
		default:
			break;
	}
}

static void processFile(const string& scriptFileName, const string& miniscriptTranspilationFileName, const vector<string>& miniScriptExtensionFileNames) {
	Console::println("Processing script: " + scriptFileName);


	//
	auto miniScript = unique_ptr<MiniScript>(MiniScript::loadScript(Tools::getPathName(scriptFileName), Tools::getFileName(scriptFileName)));
	if (miniScript == nullptr) {
		Console::println("No script instance: " + scriptFileName);
		return;
	}

	//
	unordered_map<string, vector<string>> methodCodeMap;
	auto allMethods = MiniScriptTranspiler::getAllMethodNames(miniScript.get());

	//
	vector<string> transpilationUnits;
	for (const auto& transpilationUnit: miniScript->getTranspilationUnits()) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: miniScriptExtensionFileNames) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: transpilationUnits) {
		vector<string> transpilationUnitCode;
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(transpilationUnit), Tools::getFileName(transpilationUnit), transpilationUnitCode);
		for (auto i = 0; i < transpilationUnitCode.size(); i++) {
			const auto& line = transpilationUnitCode[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "registerMethod") == true ||
				StringTools::startsWith(trimmedLine, "miniScript->registerMethod") == true) {
				auto bracketCount = 0;
				string className;
				if (StringTools::firstIndexOf(StringTools::substring(trimmedLine, 14), "new") == string::npos) {
					Console::println("src/tdme/utilities/MiniScript.cpp: registerMethod @ " + to_string(i) + ": '" + trimmedLine + "': unable to determine class name");
				} else {
					auto classNameStartIdx = trimmedLine.find("registerMethod") + 14 + 5;
					for (auto j = classNameStartIdx; j < trimmedLine.size(); j++) {
						auto c = trimmedLine[j];
						if (c == '(') break;
						if (c == ' ') continue;
						className+= c;
					}
					gatherMethodCode(transpilationUnitCode, className, i, methodCodeMap);
				}
			}
		}
	}

	Console::println(miniScript->getInformation());

	//
	string headerIndent = "\t";
	string methodCodeIndent = "\t";
	const auto& scripts = miniScript->getScripts();
	string generatedExecuteCode;
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
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
			generatedExecuteCode+= headerIndent + "\t\t" + "if (getScriptState().scriptIdx == " + to_string(scriptIdx) + ") " + methodName + "(scriptState.statementIdx); else\n";
			scriptIdx++;
		}
	}
	if (generatedExecuteCode.empty() == false) generatedExecuteCode+= headerIndent + "\t\t\t" + ";\n";

	// determine "initialize" and "nothing" script indices
	auto initializeScriptIdx = -1;
	auto nothingScriptIdx = -1;
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (StringTools::regexMatch(script.condition, "[a-zA-Z0-9]+") == true) {
				if (script.condition == "nothing") nothingScriptIdx = scriptIdx;
				if (script.condition == "initialize") initializeScriptIdx = scriptIdx;
			}
			//
			scriptIdx++;
		}
	}

	// member access evaluation
	vector<string> memberAccessEvaluationDeclarations;
	vector<string> memberAccessEvaluationDefinitions;
	generateMiniScriptEvaluateMemberAccessArrays(miniScript.get(), memberAccessEvaluationDeclarations, memberAccessEvaluationDefinitions);

	//
	string miniScriptClassName = Tools::removeFileExtension(Tools::getFileName(miniscriptTranspilationFileName));
	string generatedDeclarations = "\n";
	generatedDeclarations+= string() + "public:" + "\n";
	generatedDeclarations+= headerIndent + "// overridden methods" + "\n";
	generatedDeclarations+= headerIndent + "void registerMethods() override;" + "\n";
	generatedDeclarations+= headerIndent + "void emit(const string& condition) override;" + "\n";
	generatedDeclarations+= headerIndent + "inline void startScript() override {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (native == false) {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "MiniScript::startScript();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "auto& scriptState = getScriptState();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "for (const auto& [scriptVariableName, scriptVariable]: scriptState.variables) delete scriptVariable;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "scriptState.variables.clear();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "getScriptState().running = true;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "registerVariables();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "resetScriptExecutationState(" + to_string(initializeScriptIdx) + ", STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
	generatedDeclarations+= headerIndent + "}" + "\n";
	generatedDeclarations+= headerIndent + "inline void execute() override {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (native == false) {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "MiniScript::execute();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "auto& scriptState = getScriptState();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "// execute while having statements to be processed" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().state == STATEMACHINESTATE_NEXT_STATEMENT) {" + "\n";
	generatedDeclarations+= generatedExecuteCode;
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "executeStateMachine();" + "\n";
	generatedDeclarations+= headerIndent + "}" + "\n";
	generatedDeclarations+= "\n";
	generatedDeclarations+= string() + "protected:" + "\n";

	//
	for (const auto& memberAccessEvaluationDeclaration: memberAccessEvaluationDeclarations) {
		generatedDeclarations+= headerIndent + memberAccessEvaluationDeclaration + "\n";
	}
	generatedDeclarations+= "\n";

	//
	generatedDeclarations+= headerIndent + "// overridden methods" + "\n";
	generatedDeclarations+= headerIndent + "void initializeNative() override;" + "\n";
	generatedDeclarations+= headerIndent + "int determineScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= headerIndent + "int determineNamedScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= "\n";

	string registerMethodsDefinitions;
	registerMethodsDefinitions+= "void " + miniScriptClassName + "::registerMethods() {" + "\n";
	registerMethodsDefinitions+= methodCodeIndent+ "MiniScript::registerMethods();" + "\n";
	registerMethodsDefinitions+= methodCodeIndent + "if (native == false) return;" + "\n";
	//
	for (const auto& memberAccessEvaluationDefintion: memberAccessEvaluationDefinitions) {
		registerMethodsDefinitions+= methodCodeIndent + memberAccessEvaluationDefintion + "\n";
	}
	registerMethodsDefinitions+= string() + "}" + "\n";

	//
	string emitDefinition;
	emitDefinition+= "void " + miniScriptClassName + "::emit(const string& condition) {" + "\n";
	emitDefinition+= methodCodeIndent + "if (native == false) {" + "\n";
	emitDefinition+= methodCodeIndent + "\t" + "MiniScript::emit(condition);" + "\n";
	emitDefinition+= methodCodeIndent + "\t" + "return;" + "\n";
	emitDefinition+= methodCodeIndent + "}" + "\n";
	string generatedDefinitions = "\n";
	string initializeNativeDefinition;
	initializeNativeDefinition+= "void " + miniScriptClassName + "::initializeNative() {" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNative(true);" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeHash(\"" + miniScript->getNativeHash() + "\");" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeScripts(" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "\t" + "{" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "Script(" + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?"Script::SCRIPTTYPE_FUNCTION":(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"Script::SCRIPTTYPE_ON":"Script::SCRIPTTYPE_ONENABLED")) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + to_string(script.line) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.condition, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.executableCondition, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "ScriptStatement(" + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.line) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.statementIdx) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.conditionStatement.statement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.conditionStatement.executableStatement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.gotoStatementIdx) + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + ")," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + script.name + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.emitCondition == true?"true":"false") + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{" + "\n";
			auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
			for (const auto& statement: script.statements) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "ScriptStatement(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.line) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.statementIdx) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(statement.statement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(statement.executableStatement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.gotoStatementIdx) + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + ")" + (statementIdx < script.statements.size() - 1?",":"") + "\n";
				statementIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{},\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.callable == true?"true":"false") + ",\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{\n";
			auto argumentIdx = 0;
			for (const auto& argument: script.arguments) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "Script::ScriptArgument(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + argument.name + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + (argument.assignBack == true?"true":"false") + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" ")" + (argumentIdx != script.arguments.size() - 1?",":"") + "\n";
				argumentIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + ")" + (scriptIdx < scripts.size() - 1?",":"") + "\n";
			scriptIdx++;
		}
	}
	initializeNativeDefinition+= methodCodeIndent + "\t" + "}" + "\n";
	initializeNativeDefinition+= methodCodeIndent + ");" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeScriptFunctions(" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "\t" + "{" + "\n";
	auto scriptFunctionIdx = 0;
	for (const auto& [functionName, functionIdx]: miniScript->scriptFunctions) {
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "{" + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + functionName + "\"," + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + to_string(functionIdx) + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "}" + (scriptFunctionIdx != miniScript->scriptFunctions.size() - 1?",":"") + "\n";
		scriptFunctionIdx++;
	}
	initializeNativeDefinition+= methodCodeIndent + "\t" + "}" + "\n";
	initializeNativeDefinition+= methodCodeIndent + ");" + "\n";
	initializeNativeDefinition+= string() + "}" + "\n";

	//
	string generatedDetermineScriptIdxToStartDefinition = "\n";
	generatedDetermineScriptIdxToStartDefinition+= "int " + miniScriptClassName + "::determineScriptIdxToStart() {" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "\t" + "if (native == false) return MiniScript::determineScriptIdxToStart();" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "\t" + "auto miniScript = this;" + "\n";
	string generatedDetermineNamedScriptIdxToStartDefinition = "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= "int " + miniScriptClassName + "::determineNamedScriptIdxToStart() {" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "if (native == false) return MiniScript::determineNamedScriptIdxToStart();" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "auto miniScript = this;" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "for (const auto& enabledNamedCondition: enabledNamedConditions) {" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
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

			string emitName =
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);

			// emit code
			if (script.scriptType == MiniScript::Script::SCRIPTTYPE_ON && StringTools::regexMatch(script.condition, "[a-zA-Z0-9]+") == true) {
				string emitDefinitionIndent = "\t";
				emitDefinition+= emitDefinitionIndent + "if (condition == \"" + emitName + "\") {" + "\n";
				emitDefinition+= emitDefinitionIndent + "\t" + methodName + "(STATEMENTIDX_FIRST);" + "\n";
				emitDefinition+= emitDefinitionIndent + "} else" + "\n";
			}

			// declaration
			generatedDeclarations+= headerIndent + "/**" + "\n";
			generatedDeclarations+= headerIndent + " * Miniscript transpilation of: " + (script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?"function":(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on":"on-enabled")) + ": " + script.condition + (script.name.empty() == false?" (" + script.name + ")":"") + "\n";
			generatedDeclarations+= headerIndent + " * @param miniScriptGotoStatementIdx MiniScript goto statement index" + "\n";
			generatedDeclarations+= headerIndent + " */" + "\n";
			generatedDeclarations+= headerIndent + "void " + methodName + "(int miniScriptGotoStatementIdx);" + "\n";
			generatedDeclarations+= "\n";

			// transpile definition
			generatedDefinitions+= "void " + miniScriptClassName + "::" + methodName + "(int miniScriptGotoStatementIdx) {" + "\n";
			string generatedSubCode;
			MiniScriptTranspiler::transpile(miniScript.get(), generatedSubCode, scriptIdx, methodCodeMap, allMethods);
			generatedDefinitions+= generatedSubCode;
			generatedDefinitions+= string() + "}" + "\n\n";

			//
			if (script.emitCondition == false) {
				if (script.scriptType == MiniScript::Script::SCRIPTTYPE_ONENABLED) {
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "// next statements belong to tested enabled named condition with name \"" + script.name + "\"" + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "if (enabledNamedCondition == \"" + script.name + "\")" + "\n";
				}
				MiniScriptTranspiler::transpileScriptCondition(
					miniScript.get(),
					script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?generatedDetermineScriptIdxToStartDefinition:generatedDetermineNamedScriptIdxToStartDefinition,
					scriptIdx,
					methodCodeMap,
					allMethods,
					"-1",
					"bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return " + to_string(scriptIdx) + ";",
					script.scriptType == MiniScript::Script::SCRIPTTYPE_ONENABLED?1:0
				);
			}

			//
			scriptIdx++;
		}
	}

	//
	generatedDetermineScriptIdxToStartDefinition+= "\n";
	generatedDetermineScriptIdxToStartDefinition+= methodCodeIndent + "//" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= methodCodeIndent + "return " + to_string(nothingScriptIdx) + ";" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "}" + "\n";
	//
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "}" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "//" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "return SCRIPTIDX_NONE;" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "}" + "\n";

	//
	{
		string emitDefinitionIndent = "\t";
		emitDefinition+= emitDefinitionIndent + "{" + "\n";
		emitDefinition+= emitDefinitionIndent + "\t" + "Console::println(\"" + miniScriptClassName + "::emit(): no condition with name: '\" + condition + \"'\");" + "\n";
		emitDefinition+= emitDefinitionIndent + "}" + "\n";
		emitDefinition+= string() + "}" + "\n";
	}

	// transpile array access operator
	string arrayAccessMethodsDeclarations;
	string arrayAccessMethodsDefinitions;
	//
	string arrayMapSetInitializerDeclarations;
	string arrayMapSetInitializerDefinitions;

	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
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
			createArrayMapSetInitializer(
				miniScript.get(),
				arrayMapSetInitializerDeclarations,
				arrayMapSetInitializerDefinitions,
				miniScriptClassName,
				methodName,
				script.conditionSyntaxTree,
				script.conditionStatement,
				methodCodeMap,
				allMethods,
				true
			);
			createArrayAccessMethods(
				miniScript.get(),
				arrayAccessMethodsDeclarations,
				arrayAccessMethodsDefinitions,
				miniScriptClassName,
				methodName,
				script.conditionSyntaxTree,
				script.conditionStatement,
				methodCodeMap,
				allMethods,
				true
			);
			for (auto statementIdx = 0; statementIdx < script.statements.size(); statementIdx++) {
				createArrayMapSetInitializer(
					miniScript.get(),
					arrayMapSetInitializerDeclarations,
					arrayMapSetInitializerDefinitions,
					miniScriptClassName,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false
				);
				createArrayAccessMethods(
					miniScript.get(),
					arrayAccessMethodsDeclarations,
					arrayAccessMethodsDefinitions,
					miniScriptClassName,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false
				);
			}
			scriptIdx++;
		}
	}

	// inject array access method declarations into declarations
	generatedDeclarations+= arrayAccessMethodsDeclarations;
	// inject array/map/set initializer declarations into declarations
	generatedDeclarations+= arrayMapSetInitializerDeclarations;

	// sum up definitions
	generatedDefinitions =
		string("\n#define __MINISCRIPT_TRANSPILATION__\n\n") +
		initializeNativeDefinition +
		registerMethodsDefinitions +
		generatedDetermineScriptIdxToStartDefinition +
		generatedDetermineNamedScriptIdxToStartDefinition + "\n" +
		emitDefinition +
		generatedDefinitions +
		arrayAccessMethodsDefinitions +
		arrayMapSetInitializerDefinitions;

	// inject C++ definition code
	{
		vector<string> miniScriptClass;
		vector<string> miniScriptClassNew;
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationFileName), Tools::getFileName(miniscriptTranspilationFileName), miniScriptClass);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClass.size(); i++) {
			const auto& line = miniScriptClass[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/") {
				reject = true;
				miniScriptClassNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassNew.push_back(generatedDefinitions);
				miniScriptClassNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationFileName),
				Tools::getFileName(miniscriptTranspilationFileName),
				miniScriptClassNew
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in file " + miniscriptTranspilationFileName + ". Dont forget to rebuild your sources.");
		}
	}

	//
	// inject C++ declaration code / header
	{
		vector<string> miniScriptClassHeader;
		vector<string> miniScriptClassHeaderNew;
		auto miniscriptTranspilationHeaderFileName = Tools::getPathName(miniscriptTranspilationFileName) + "/" + Tools::removeFileExtension(Tools::getFileName(miniscriptTranspilationFileName)) + ".h";
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationHeaderFileName), Tools::getFileName(miniscriptTranspilationHeaderFileName), miniScriptClassHeader);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClassHeader.size(); i++) {
			const auto& line = miniScriptClassHeader[i];
			const auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/") {
				reject = true;
				miniScriptClassHeaderNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassHeaderNew.push_back(generatedDeclarations);
				miniScriptClassHeaderNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationHeaderFileName),
				Tools::getFileName(miniscriptTranspilationHeaderFileName),
				miniScriptClassHeaderNew
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in header file " + miniscriptTranspilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

};
};
};
};

int main(int argc, char** argv)
{
	Console::println(string("miniscripttranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 3) {
		Console::println("Usage: miniscripttranspiler path_to_script_file path_to_cpp_miniscript_transpilation_file [path_to_cpp_miniscript_extension_file1] [path_to_cpp_miniscript_extension_fileN]");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	vector<string> miniScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) miniScriptExtensionFileNames.push_back(argv[i]);

	//
	tdme::tools::cli::MiniscriptTranspiler::processFile(argv[1], argv[2], miniScriptExtensionFileNames);

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
