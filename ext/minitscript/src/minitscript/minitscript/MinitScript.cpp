#include <minitscript/minitscript/MinitScript.h>

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <span>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <minitscript/minitscript/MinitScript.h>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/ApplicationMethods.h>
#include <minitscript/minitscript/ArrayMethods.h>
#include <minitscript/minitscript/BaseMethods.h>
#include <minitscript/minitscript/ByteArrayMethods.h>
#include <minitscript/minitscript/CryptographyMethods.h>
#include <minitscript/minitscript/ConsoleMethods.h>
#include <minitscript/minitscript/ContextMethods.h>
#include <minitscript/minitscript/FileSystemMethods.h>
#include <minitscript/minitscript/HTTPDownloadClientClass.h>
#include <minitscript/minitscript/JSONMethods.h>
#include <minitscript/minitscript/MapMethods.h>
#include <minitscript/minitscript/MathMethods.h>
#include <minitscript/minitscript/NetworkMethods.h>
#include <minitscript/minitscript/ScriptMethods.h>
#include <minitscript/minitscript/Setup.h>
#include <minitscript/minitscript/SetMethods.h>
#include <minitscript/minitscript/StringMethods.h>
#include <minitscript/minitscript/TimeMethods.h>
#include <minitscript/minitscript/Validations.h>
#include <minitscript/minitscript/XMLMethods.h>

#include <minitscript/math/Math.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/os/threading/Thread.h>
#include <minitscript/utilities/Character.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Integer.h>
#include <minitscript/utilities/StringTools.h>
#include <minitscript/utilities/SHA256.h>
#include <minitscript/utilities/Time.h>

using std::find;
using std::ifstream;
using std::initializer_list;
using std::make_pair;
using std::make_unique;
using std::map;
using std::remove;
using std::reverse;
using std::smatch;
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

using minitscript::minitscript::MinitScript;

using minitscript::minitscript::ApplicationMethods;
using minitscript::minitscript::ArrayMethods;
using minitscript::minitscript::BaseMethods;
using minitscript::minitscript::ByteArrayMethods;
using minitscript::minitscript::CryptographyMethods;
using minitscript::minitscript::ConsoleMethods;
using minitscript::minitscript::ContextMethods;
using minitscript::minitscript::FileSystemMethods;
using minitscript::minitscript::HTTPDownloadClientClass;
using minitscript::minitscript::JSONMethods;
using minitscript::minitscript::MapMethods;
using minitscript::minitscript::MathMethods;
using minitscript::minitscript::NetworkMethods;
using minitscript::minitscript::ScriptMethods;
using minitscript::minitscript::Setup;
using minitscript::minitscript::SetMethods;
using minitscript::minitscript::StringMethods;
using minitscript::minitscript::TimeMethods;
using minitscript::minitscript::Validations;
using minitscript::minitscript::XMLMethods;

using minitscript::math::Math;
using minitscript::os::filesystem::FileSystem;
using minitscript::os::threading::Thread;
using minitscript::utilities::Character;
using minitscript::utilities::Console;
using minitscript::utilities::Integer;
using minitscript::utilities::StringTools;
using minitscript::utilities::SHA256;
using minitscript::utilities::Time;

const string MinitScript::OPERATOR_CHARS = "[].->+-!~/*%<>=&^|";

vector<MinitScript::DataType*> MinitScript::dataTypes;
MinitScript::ShutdownRAII MinitScript::shutdownRAII(MinitScript::dataTypes);

const string MinitScript::METHOD_SCRIPTCALL = "script.call";
const string MinitScript::METHOD_SCRIPTCALLSTACKLET = "script.callStacklet";
const string MinitScript::METHOD_SCRIPTCALLBYINDEX = "script.callByIndex";
const string MinitScript::METHOD_SCRIPTCALLSTACKLETBYINDEX = "script.callStackletByIndex";

const string MinitScript::METHOD_ENABLENAMEDCONDITION = "script.enableNamedCondition";
const string MinitScript::METHOD_DISABLENAMEDCONDITION = "script.disableNamedCondition";

const string MinitScript::Variable::TYPENAME_NONE = "";
const string MinitScript::Variable::TYPENAME_NULL = "Null";
const string MinitScript::Variable::TYPENAME_BOOLEAN = "Boolean";
const string MinitScript::Variable::TYPENAME_INTEGER = "Integer";
const string MinitScript::Variable::TYPENAME_FLOAT = "Float";
const string MinitScript::Variable::TYPENAME_FUNCTION = "Function";
const string MinitScript::Variable::TYPENAME_STACKLET = "Stacklet";
const string MinitScript::Variable::TYPENAME_NUMBER = "Number";
const string MinitScript::Variable::TYPENAME_MIXED = "Mixed";
const string MinitScript::Variable::TYPENAME_STRING = "String";
const string MinitScript::Variable::TYPENAME_BYTEARRAY = "ByteArray";
const string MinitScript::Variable::TYPENAME_ARRAY = "Array";
const string MinitScript::Variable::TYPENAME_MAP = "Map";
const string MinitScript::Variable::TYPENAME_SET = "Set";

const vector<string> MinitScript::Method::CONTEXTFUNCTIONS_ALL = {};

void MinitScript::initialize() {
	//
	Console::initialize();
	//
	registerDataType(new HTTPDownloadClientClass());
	//
	HTTPDownloadClientClass::initialize();
}

const string MinitScript::getBaseClassHeader() {
	return "minitscript/minitscript/MinitScript.h";
}

const string MinitScript::getBaseClass() {
	return "minitscript::minitscript::MinitScript";
}

const vector<string> MinitScript::getTranspilationUnits() {
	return {
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ApplicationMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ArrayMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/BaseMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ByteArrayMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ConsoleMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ContextMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/CryptographyMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/FileSystemMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/HTTPDownloadClientClass.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/JSONMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/MapMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/MathMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/NetworkMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/ScriptMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/SetMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/StringMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/TimeMethods.cpp",
		MINITSCRIPT_DATA + "/src/minitscript/minitscript/XMLMethods.cpp"
	};
}

MinitScript::MinitScript() {
	for (auto dataType: MinitScript::dataTypes) {
		if (dataType->isRequiringGarbageCollection() == false) continue;
		// create script context
		auto scriptContext = dataType->createScriptContext();
		scriptContext->setMinitScript(this);
		scriptContext->setIndex(garbageCollectionDataTypes.size());
		//
		garbageCollectionDataTypes.emplace_back(dataType,scriptContext);
		garbageCollectionScriptContextsByDataType[dataType->getType()] = scriptContext;
	}
}

MinitScript::~MinitScript() {
	for (const auto& [methodName, method]: this->methods) delete method;
	for (const auto& [stateMachineStateId, stateMachineState]: this->stateMachineStates) delete stateMachineState;
	//
	unregisterVariables();
	while (hasScriptState() == true) popScriptState();
	//
	garbageCollection();
	for (auto& garbageCollectionDataType: garbageCollectionDataTypes) garbageCollectionDataType.dataType->deleteScriptContext(garbageCollectionDataType.context);
}

void MinitScript::registerStateMachineState(StateMachineState* state) {
	auto stateMachineStateIt = stateMachineStates.find(state->getId());
	if (stateMachineStateIt != stateMachineStates.end()) {
		Console::printLine("MinitScript::registerStateMachineState(): " + scriptFileName + ": State with id + " + to_string(state->getId()) + ", name " + state->getName() + " already registered.");
		return;
	}
	stateMachineStates[state->getId()] = state;
}

void MinitScript::initializeNativeModule(MinitScript* parentScript) {
	//
	this->parentScript = parentScript;
	// determine root script, which is initially "this"
	auto rootScriptCandidate = rootScript;
	while (rootScriptCandidate != nullptr) {
		rootScript = rootScriptCandidate;
		rootScriptCandidate = rootScriptCandidate->parentScript;
	}
	// find root script indices
	// 	so iterate our module scripts
	for (auto i = 0; i < scripts.size(); i++) {
		auto& moduleScript = scripts[i];
        // only applies for functions and stacklets
		if ((moduleScript.type != Script::TYPE_FUNCTION &&
			moduleScript.type != Script::TYPE_STACKLET)) {
			continue;
		}
		// only applies for functions and stacklets
		// find module script in root native scripts
		for (auto j = 0; j < rootScript->nativeScripts.size(); j++) {
			auto& script = rootScript->nativeScripts[j];
			//
			if (moduleScript.condition == script.condition &&
				moduleScript.name == script.name) {
				//
				if (moduleScript._module.empty() == true) {
					script.moduleStatements = &(moduleScript.statements);
				}
				//
				moduleScript.rootScriptIdx = j;
			}
		}
	}
	// print out scripts that have no root script index
	for (auto i = 0; i < scripts.size(); i++) {
		auto& moduleScript = scripts[i];
		if (moduleScript.rootScriptIdx == SCRIPTIDX_NONE) {
			Console::printLine("MinitScript::initializeModule()): " + scriptFileName + ": " + moduleScript.condition + ": Not available in root script");
		}
	}
}

void MinitScript::initializeNative() {
}

void MinitScript::complain(const string& methodName, const SubStatement& subStatement) {
	auto argumentsInformation = getArgumentsInformation(methodName);
	if (argumentsInformation.empty() == true) argumentsInformation = "None";
	auto errorMessageDetails = getSubStatementInformation(subStatement) + ": " + methodName + "(...): Argument mismatch: expected arguments: " + argumentsInformation;
	//
	Console::printLine(errorMessageDetails);
	//
	errorMessage =
		"An method usage complain has occurred: " +
		errorMessageDetails;
	//
	errorSubStatement = subStatement;
}

void MinitScript::complain(const string& methodName, const SubStatement& subStatement, const string& message) {
	auto errorMessageDetails = getSubStatementInformation(subStatement) + ": " + methodName + "(...): " + message;
	//
	Console::printLine(errorMessageDetails);
	//
	errorMessage =
		"An method usage complain has occurred: " +
		errorMessageDetails;
	//
	errorSubStatement = subStatement;
}

void MinitScript::complainOperator(const string& methodName, const string& operatorString, const SubStatement& subStatement) {
	auto argumentsInformation = getArgumentsInformation(methodName);
	if (argumentsInformation.empty() == true) argumentsInformation = "None";
	auto errorMessageDetails = getSubStatementInformation(subStatement) + ": '" + operatorString + "': Argument mismatch: expected arguments: " + argumentsInformation;
	//
	Console::printLine(errorMessageDetails);
	//
	errorMessage =
		(isOperator(operatorString) == true?
			"An operator usage complain has occurred: ":
			"An method usage complain has occurred: "
		) +
		errorMessageDetails;
	//
	errorSubStatement = subStatement;
}

void MinitScript::complainOperator(const string& methodName, const string& operatorString, const SubStatement& subStatement, const string& message) {
	auto errorMessageDetails = getSubStatementInformation(subStatement) + ": '" + operatorString + "': " + message;
	//
	Console::printLine(errorMessageDetails);
	//
	errorMessage =
		(isOperator(operatorString) == true?
			"An operator usage complain has occurred: ":
			"An method usage complain has occurred: "
		) +
		errorMessageDetails;
	//
	errorSubStatement = subStatement;
}

void MinitScript::registerMethod(Method* method) {
	auto methodsIt = rootScript->methods.find(method->getMethodName());
	if (methodsIt != rootScript->methods.end()) {
		Console::printLine("MinitScript::registerMethod(): " + scriptFileName + ": Method with name " + method->getMethodName() + " already registered.");
		return;
	}
	rootScript->methods[method->getMethodName()] = method;
}

void MinitScript::registerDataType(DataType* dataType) {
	dataType->setType(static_cast<VariableType>(TYPE_PSEUDO_DATATYPES + MinitScript::dataTypes.size()));
	MinitScript::dataTypes.push_back(dataType);
}

void MinitScript::executeNextStatement() {
	// Note: modules do not execute in their own MinitScript instance
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
	//
	#if defined(MINITSCRIPT_EVENTS)
		// events
		if (scriptState.statementIdx == STATEMENTIDX_FIRST) emitted = false;
	#endif
	//
	executeStatement(syntaxTree, statement);
	//
	#if defined(MINITSCRIPT_EVENTS)
		// events
		if (emitted == true) return;
	#endif
	//
	scriptState.statementIdx++;
	if (scriptState.statementIdx >= script.statements.size()) {
		scriptState.scriptIdx = SCRIPTIDX_NONE;
		scriptState.statementIdx = STATEMENTIDX_NONE;
		setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
	}
}

bool MinitScript::parseStatement(const string_view& executableStatement, string_view& methodName, vector<ParserArgument>& arguments, const Statement& statement) {
	if (VERBOSE == true) Console::printLine("MinitScript::parseStatement(): " + getStatementInformation(statement) + ": '" + string(executableStatement) + "'");
	int executableStatementStartIdx = 0;
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
	auto argumentSubLineIdx = -1;
	auto lc  = '\0';
	//
	auto subLineIdx = 0;
	//
	auto i = executableStatementStartIdx;
	//
	auto hasNextArgument = [&]() -> bool {
		//
		for (i++; i < executableStatement.size(); i++) {
			auto c = executableStatement[i];
			// do we have a non space character?
			if (Character::isSpace(c) == false) return c != ')';
		}
		//
		return false;
	};
	//
	auto createArgument = [&]() {
		//
		if (quotedArgumentStart != string::npos) {
			auto argumentLength = quotedArgumentEnd - quotedArgumentStart + 1;
			if (argumentLength > 0) arguments.emplace_back(StringTools::viewTrim(string_view(&executableStatement[quotedArgumentStart], argumentLength)), argumentSubLineIdx);
			quotedArgumentStart = string::npos;
			quotedArgumentEnd = string::npos;
			argumentSubLineIdx = -1;
		} else
		if (argumentStart != string::npos) {
			if (argumentEnd == string::npos) argumentEnd = i - 1;
			auto argumentLength = argumentEnd - argumentStart + 1;
			if (argumentLength > 0) arguments.emplace_back(StringTools::viewTrim(string_view(&executableStatement[argumentStart], argumentLength)), argumentSubLineIdx);
			argumentStart = string::npos;
			argumentEnd = string::npos;
			argumentSubLineIdx = -1;
		}
	};
	//
	methodStart = executableStatementStartIdx;
	//
	for (; i < executableStatement.size(); i++) {
		//
		auto c = executableStatement[i];
		// quotes
		if (squareBracketCount == 0 && curlyBracketCount == 0 && ((c == '"' || c == '\'') && lc != '\\')) {
			// new quote
			if (quote == '\0') {
				//
				if (bracketCount == 1) {
					argumentStart = string::npos;
					quotedArgumentStart = i;
					argumentSubLineIdx = subLineIdx;
				}
				//
				quote = c;
			} else
			// end of quote
			if (quote == c) {
				//
				if (bracketCount == 1) {
					quotedArgumentEnd = i;
				}
				//
				quote = '\0';
			}
		} else
		// we still have a quote, so do not process any other chars at other places
		if (quote != '\0') {
			// no op
		} else {
			// no quotes, handle \n
			if (c == '\n') {
				subLineIdx++;
			} else
			// (
			if (c == '(') {
				bracketCount++;
				// mark the method end
				if (bracketCount == 1) {
					//
					methodEnd = i - 1;
					// check if we have a next argument and mark it
					// if its a quoted argument, the non quoted argument will be unset later
					if (hasNextArgument() == true) {
						//
						argumentStart = i;
						argumentSubLineIdx = subLineIdx;
						//
						i--;
						continue;
					} else {
						i--;
					}
				}
			} else
			// )
			if (c == ')') {
				//
				bracketCount--;
				// end of statement, create argument
				if (bracketCount == 0) createArgument();
			} else
			// [
			if (c == '[' && curlyBracketCount == 0) {
				squareBracketCount++;
			} else
			// ]
			if (c == ']' && curlyBracketCount == 0) {
				squareBracketCount--;
			} else
			// {
			if (c == '{') {
				curlyBracketCount++;
			} else
			// }
			if (c == '}') {
				curlyBracketCount--;
			} else
			// ,
			if (squareBracketCount == 0 && curlyBracketCount == 0 && bracketCount == 1 && c == ',') {
				if (bracketCount == 1) {
					// create argument
					createArgument();
					// check if we have a next argument and mark it
					// if its a quoted argument, the non quoted argument will be unset later
					if (hasNextArgument() == true) {
						//
						argumentStart = i;
						argumentSubLineIdx = subLineIdx;
						//
						i--;
						continue;
					} else {
						i--;
					}
				}
			}
		}
		//
		lc = lc == '\\' && c == '\\'?'\0':c;
	}

	// extract method name
	if (methodStart != string::npos) {
		// we might have a statement without ()
		if (methodEnd == string::npos) methodEnd = i - 1;
		//
		methodName = StringTools::viewTrim(string_view(&executableStatement[methodStart], methodEnd - methodStart + 1));
	}

	//
	if (VERBOSE == true) {
		Console::printLine("MinitScript::parseStatement(): " + StringTools::replace(getStatementInformation(statement), "\n", "\\n"));
		Console::printLine(string("\t") + ": Method: '" + string(methodName) + "'");
		Console::printLine(string("\t") + ": Arguments");
		int variableIdx = 0;
		for (const auto& argument: arguments) {
			Console::printLine(string("\t\t") + "@" + to_string(argument.subLineIdx) + "'" + StringTools::replace(string(argument.argument), "\n", "\\n") + "'");
			variableIdx++;
		}
		Console::printLine();
	}

	// complain about bracket count
	if (bracketCount != 0) {
		// TODO: sub line index
		Console::printLine(getStatementInformation(statement) + ": " + string(executableStatement) + "': Unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(getStatementInformation(statement) + ": " + string(executableStatement) + ": Unbalanced bracket count: " + to_string(Math::abs(bracketCount)) + " " + (bracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}
	// complain about square bracket count
	if (squareBracketCount != 0) {
		// TODO: sub line index
		Console::printLine(getStatementInformation(statement) + ": " + string(executableStatement) + "': Unbalanced square bracket count: " + to_string(Math::abs(squareBracketCount)) + " " + (squareBracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(getStatementInformation(statement) + ": " + string(executableStatement) + ": Unbalanced square bracket count: " + to_string(Math::abs(squareBracketCount)) + " " + (squareBracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}
	// complain about curly bracket count
	if (curlyBracketCount != 0) {
		// TODO: sub line index
		Console::printLine(getStatementInformation(statement) + ": " + string(executableStatement) + "': Unbalanced curly bracket count: " + to_string(Math::abs(curlyBracketCount)) + " " + (curlyBracketCount < 0?"too much closed":"still open"));
		//
		parseErrors.push_back(getStatementInformation(statement) + ": " + string(executableStatement) + ": Unbalanced curly bracket count: " + to_string(Math::abs(curlyBracketCount)) + " " + (curlyBracketCount < 0?"too much closed":"still open"));
		//
		return false;
	}

	//
	return true;
}

MinitScript::Variable MinitScript::executeStatement(const SyntaxTreeNode& syntaxTree, const Statement& statement) {
	if (VERBOSE == true) Console::printLine("MinitScript::executeStatement(): " + getStatementInformation(statement) + "': " + syntaxTree.value.getValueAsString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	// return on literal or empty syntaxTree
	if (syntaxTree.type == SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) {
		return initializeVariable(syntaxTree.value);
	}
	//
	vector<Variable> arguments;
	Variable returnValue;
	// construct argument values
	arguments.reserve(syntaxTree.arguments.size());
	for (const auto& argument: syntaxTree.arguments) {
		switch (argument.type) {
			case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
				{
					arguments.push_back(initializeVariable(argument.value));
					break;
				}
			case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			case SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
				{
					arguments.push_back(executeStatement(argument, statement));
					break;
				}
			default:
				break;
		}
	}
	//
	if (VERBOSE == true) {
		Console::printLine("MinitScript::executeStatement(): '" + getStatementInformation(statement) + ": " + syntaxTree.value.getValueAsString() + "(" + getArgumentsAsString(syntaxTree.arguments) + ")");
	}
	// try first function
	if (syntaxTree.type == SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION) {
		// call
		span argumentsSpan(arguments);
		call(syntaxTree.getScriptIdx(), argumentsSpan, returnValue);
		//
		return returnValue;
	} else
	if (syntaxTree.type == SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET) {
		// call
		span argumentsSpan(arguments);
		callStacklet(syntaxTree.getScriptIdx(), argumentsSpan, returnValue);
		//
		return returnValue;
	} else
	if (syntaxTree.type == SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
		// try methods next
		auto method = syntaxTree.getMethod();
		// validate arguments
		if (VALIDATION == true) {
			auto argumentIdx = 0;
			for (const auto& argumentType: method->getArgumentTypes()) {
				auto argumentOk = true;
				// nullable and NULL argument
				if (argumentType.nullable == true &&
					argumentIdx >= 0 && argumentIdx < arguments.size() &&
					arguments[argumentIdx].getType() == TYPE_NULL) {
					argumentOk = true;
				} else {
					// otherwise check the argument
					switch(argumentType.type) {
						case TYPE_NULL:
							break;
						case TYPE_BOOLEAN:
							{
								bool booleanValue;
								argumentOk = getBooleanValue(arguments, argumentIdx, booleanValue, argumentType.optional);
							}
							break;
						case TYPE_INTEGER:
							{
								int64_t integerValue;
								argumentOk = getIntegerValue(arguments, argumentIdx, integerValue, argumentType.optional);
							}
							break;
						case TYPE_FLOAT:
							{
								float floatValue;
								argumentOk = getFloatValue(arguments, argumentIdx, floatValue, argumentType.optional);
							}
							break;
						case TYPE_PSEUDO_NUMBER:
							{
								float floatValue;
								argumentOk = getFloatValue(arguments, argumentIdx, floatValue, argumentType.optional);
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
								argumentOk = getStringValue(arguments, argumentIdx, stringValue, argumentType.optional);
							}
							break;
						case TYPE_BYTEARRAY:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= arguments.size()?
										argumentType.optional:
										arguments[argumentIdx].getType() == TYPE_BYTEARRAY;
								break;
							}
						case TYPE_ARRAY:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= arguments.size()?
										argumentType.optional:
										arguments[argumentIdx].getType() == TYPE_ARRAY;
								break;
							}
						case TYPE_MAP:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= arguments.size()?
										argumentType.optional:
										arguments[argumentIdx].getType() == TYPE_MAP;
								break;
							}
						case TYPE_SET:
							{
								argumentOk =
									argumentIdx < 0 || argumentIdx >= arguments.size()?
										argumentType.optional:
										arguments[argumentIdx].getType() == TYPE_SET;
								break;
							}
						default:
							{
								// custom data types
								argumentOk =
									argumentIdx < 0 || argumentIdx >= arguments.size()?
										argumentType.optional:
										arguments[argumentIdx].getType() == argumentType.type;
								break;
							}

					}
				}
				if (argumentOk == false) {
					Console::printLine(
						getStatementInformation(statement, syntaxTree.subLineIdx) +
						": Method '" + string(syntaxTree.value.getValueAsString()) + "'" +
						": argument value @ " + to_string(argumentIdx) + ": expected " + Variable::getTypeAsString(argumentType.type) + ", but got: " + (argumentIdx < arguments.size()?arguments[argumentIdx].getAsString():"nothing"));
				}
				argumentIdx++;
			}
			if (method->isVariadic() == false && arguments.size() > method->getArgumentTypes().size()) {
				Console::printLine(
					getStatementInformation(statement, syntaxTree.subLineIdx) +
					": Method '" + string(syntaxTree.value.getValueAsString()) + "'" +
					": too many arguments: expected: " + to_string(method->getArgumentTypes().size()) + ", got " + to_string(arguments.size()));
			}
		}
		// execute method
		span argumentsSpan(arguments);
		method->executeMethod(argumentsSpan, returnValue, SubStatement(statement, syntaxTree.subLineIdx));
		// check return type
		if (VALIDATION == true) {
			if (method->isReturnValueNullable() == true && returnValue.getType() == TYPE_NULL) {
				// no op, this is a valid return value
			} else
			if (MinitScript::Variable::isExpectedType(returnValue.getType(), method->getReturnValueType()) == false) {
				Console::printLine(
					getStatementInformation(statement, syntaxTree.subLineIdx) +
					": Method '" + string(syntaxTree.value.getValueAsString()) + "'" +
					": return value: expected " + Variable::getReturnTypeAsString(method->getReturnValueType(), method->isReturnValueNullable()) + ", but got: " + Variable::getReturnTypeAsString(returnValue.getType(), false));
			}
		}
		//
		return returnValue;
	}
	//
	return returnValue;
}

bool MinitScript::createStatementSyntaxTree(const string& scriptFileName, int scriptIdx, const string_view& methodName, const vector<ParserArgument>& arguments, const Statement& statement, SyntaxTreeNode& syntaxTree, int subLineIdx) {
	if (VERBOSE == true) {
		//
		auto getArgumentsAsString = [](const vector<ParserArgument>& arguments) -> const string {
			string argumentsString;
			for (const auto& argument: arguments) argumentsString+= (argumentsString.empty() == false?", ":"") + string("@") + to_string(argument.subLineIdx) + string("'") + string(argument.argument) + string("'");
			return argumentsString;
		};
		//
		Console::printLine("MinitScript::createScriptStatementSyntaxTree(): " + getStatementInformation(statement) + ": " + string(methodName) + "(" + getArgumentsAsString(arguments) + ")");
	}
	// method/function
	auto functionScriptIdx = SCRIPTIDX_NONE;
	Method* method = nullptr;
	// try first user functions
	{
		auto functionsIt = functions.find(string(methodName));
		if (functionsIt != functions.end()) {
			functionScriptIdx = functionsIt->second;
		}
	}
	// try methods next
	{
		auto methodsIt = methods.find(string(methodName));
		if (methodsIt != methods.end()) {
			method = methodsIt->second;
		}
	}

	// arguments
	vector<bool> argumentReferences(0);
	if (functionScriptIdx != SCRIPTIDX_NONE) {
		const auto& script = scripts[functionScriptIdx];
		if (script.type == Script::TYPE_STACKLET) {
			if (arguments.empty() == false) {
				Console::printLine(getStatementInformation(statement) + ": A stacklet must not be called with any arguments: " + string(methodName));
				//
				parseErrors.push_back(getStatementInformation(statement) + ": A stacklet must not be called with any arguments: " + string(methodName));
				//
				return false;
			}
		} else {
			argumentReferences.resize(script.arguments.size());
			auto argumentIdx = 0;
			for (const auto& argument: scripts[functionScriptIdx].arguments) {
				argumentReferences[argumentIdx++] = argument.reference;
			}
		}
	} else
	if (method != nullptr) {
		argumentReferences.resize(method->getArgumentTypes().size());
		auto argumentIdx = 0;
		for (const auto& argument: method->getArgumentTypes()) {
			argumentReferences[argumentIdx++] = argument.reference;
		}
	}
	auto argumentIdx = 0;
	for (const auto& argument: arguments) {
		// object member access
		int accessObjectMemberStartIdx;
		vector<string_view> lamdaFunctionStackletArguments;
		string_view lamdaFunctionStackletScriptCode;
		int lamdaFunctionStackletLineIdx = statement.line + subLineIdx + argument.subLineIdx;
		if (viewIsLamdaFunction(argument.argument, lamdaFunctionStackletArguments, lamdaFunctionStackletScriptCode, lamdaFunctionStackletLineIdx) == true) {
			Variable variable;
			createLamdaFunction(variable, lamdaFunctionStackletArguments, lamdaFunctionStackletScriptCode, lamdaFunctionStackletLineIdx, false, statement);
			SyntaxTreeNode subSyntaxTree(SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL, variable, nullptr, {}, subLineIdx + argument.subLineIdx);
			syntaxTree.arguments.push_back(subSyntaxTree);
		} else
		if (viewIsStacklet(argument.argument, lamdaFunctionStackletArguments, lamdaFunctionStackletScriptCode, lamdaFunctionStackletLineIdx) == true) {
			string scopeName;
			// empty scope means root scope
			if (scriptIdx != SCRIPTIDX_NONE) {
				// function are a valid scope for stacklets
				if (scripts[scriptIdx].type == Script::TYPE_FUNCTION) {
					scopeName = scripts[scriptIdx].condition;
				}
				// TODO: as well as stacklets
			}
			Variable variable;
			createStacklet(variable, scopeName, lamdaFunctionStackletArguments, lamdaFunctionStackletScriptCode, lamdaFunctionStackletLineIdx, statement);
			SyntaxTreeNode subSyntaxTree(SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL, variable, nullptr, {}, subLineIdx + argument.subLineIdx);
			syntaxTree.arguments.push_back(subSyntaxTree);
		} else
		// plain variable
		if (viewIsVariableAccess(argument.argument) == true) {
			//
			Variable value;
			value.setValue(deescape(argument.argument, statement));
			// look up getVariable method
			string methodName =
				method != nullptr && method->getMethodName() == "memberExecute" && argumentIdx >= 3?"getVariableReference":
					(argumentIdx >= argumentReferences.size() || argumentReferences[argumentIdx] == false?
							(method != nullptr?"getMethodArgumentVariable":"getVariable"):
							"getVariableReference");
			//
			Method* method = nullptr;
			{
				auto methodsIt = rootScript->methods.find(methodName);
				if (methodsIt != rootScript->methods.end()) {
					method = methodsIt->second;
				} else {
					Console::printLine(getStatementInformation(statement, subLineIdx + argument.subLineIdx) + ": Unknown method: " + methodName);
					//
					parseErrors.push_back(getStatementInformation(statement, subLineIdx + argument.subLineIdx) + ": Unknown method: " + methodName);
					//
					return false;
				}
			}
			//
			syntaxTree.arguments.emplace_back(
				SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD,
				MinitScript::Variable(deescape(methodName, statement)),
				method,
				initializer_list<SyntaxTreeNode>
					{
						{
							SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
							value,
							nullptr,
							{},
							subLineIdx + argument.subLineIdx
						}
					},
				subLineIdx + argument.subLineIdx
			);
		} else
		// method call
		if (argument.argument.empty() == false &&
			viewIsStringLiteral(argument.argument) == false &&
			viewIsInitializer(argument.argument) == false &&
			viewIsCall(argument.argument) == true) {
			// method call
			string_view subMethodName;
			vector<ParserArgument> subArguments;
			//
			if (parseStatement(argument.argument, subMethodName, subArguments, statement) == true) {
				SyntaxTreeNode subSyntaxTree;
				if (createStatementSyntaxTree(scriptFileName, scriptIdx, subMethodName, subArguments, statement, subSyntaxTree, subLineIdx + argument.subLineIdx) == false) {
					return false;
				}
				syntaxTree.arguments.push_back(subSyntaxTree);
			} else {
				//
				return false;
			}
		} else {
			// implicitely literal
			Variable value;
			value.setImplicitTypedValueFromStringView(scriptFileName, argument.argument, this, scriptIdx, statement);
			//
			syntaxTree.arguments.emplace_back(
				SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL,
				value,
				nullptr,
				initializer_list<SyntaxTreeNode>{},
				subLineIdx + argument.subLineIdx
			);
		}
		//
		argumentIdx++;
	}
	// try first user functions
	if (functionScriptIdx != SCRIPTIDX_NONE) {
		syntaxTree.type = scripts[functionScriptIdx].type == Script::TYPE_FUNCTION?SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET;
		syntaxTree.value.setValue(deescape(methodName, statement));
		syntaxTree.subLineIdx = subLineIdx;
		syntaxTree.setScriptIdx(functionScriptIdx);
		//
		return true;
	} else
	// try methods next
	if (method != nullptr) {
		syntaxTree.type = SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
		syntaxTree.value.setValue(deescape(methodName, statement));
		syntaxTree.subLineIdx = subLineIdx;
		syntaxTree.setMethod(method);
		//
		return true;
	} else {
		Console::printLine(getStatementInformation(statement, subLineIdx) + ": Unknown function/method: " + string(methodName) + "()");
		//
		parseErrors.push_back(getStatementInformation(statement, subLineIdx) + ": Unknown function/method: " + string(methodName) + "()");
		//
		return false;
	}
	//
	return false;
}

int MinitScript::getStackletScopeScriptIdx(int scriptIdx) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size() ||
		scripts[scriptIdx].type != MinitScript::Script::TYPE_STACKLET) {
		return MinitScript::SCRIPTIDX_NONE;
	}
	//
	const auto& stackletScript = scripts[scriptIdx];
	const auto& stackletScopeName = stackletScript.arguments.size() == 1?stackletScript.arguments[0].name:string();
	if (stackletScopeName.empty() == true) {
		return MinitScript::SCRIPTIDX_NONE;
	}
	//
	for (auto i = 0; i < scripts.size(); i++) {
		if (i == scriptIdx) continue;
		const auto& scriptCandidate = scripts[i];
		if (scriptCandidate.type != MinitScript::Script::TYPE_FUNCTION && scriptCandidate.type != MinitScript::Script::TYPE_STACKLET) continue;
		if (scriptCandidate.condition == stackletScopeName) {
			if (scriptCandidate.type == MinitScript::Script::TYPE_STACKLET) return getStackletScopeScriptIdx(i); else return i;
		}
	}
	//
	return MinitScript::SCRIPTIDX_NONE;
}

#if defined(MINITSCRIPT_EVENTS)
	// events
	void MinitScript::emit(const string& condition) {
		// defer emit if a function/stacklet is still running
		if (isFunctionRunning() == true) {
			deferredEmit = condition;
			return;
		}
		//
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
		//
		emitted = true;
	}
#endif

void MinitScript::executeStateMachine() {
	while (true == true) {
		{
			auto& scriptState = getScriptState();
			// determine state machine state if it did change
			{
				if (scriptState.lastStateMachineState == nullptr || scriptState.state != scriptState.lastState) {
					scriptState.lastState = scriptState.state;
					scriptState.lastStateMachineState = nullptr;
					auto stateMachineStateIt = stateMachineStates.find(scriptState.state);
					if (stateMachineStateIt != stateMachineStates.end()) {
						scriptState.lastStateMachineState = stateMachineStateIt->second;
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
		#if defined(MINITSCRIPT_EVENTS)
			// events
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
		#endif
	}
}

void MinitScript::execute() {
	const auto& scriptState = getScriptState();

	//
	if (scriptState.running == false || scriptState.state == STATEMACHINESTATE_NONE) return;

	// check named conditions
	#if defined(MINITSCRIPT_EVENTS)
		// events
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
	#endif

	// execute while having statements to be processed
	executeStateMachine();

	// try garbage collection
	tryGarbageCollection();
}

bool MinitScript::getNextStatement(const string& scriptFileName, const string& scriptCode, int& i, int& line, string& statement) {
	string statementCode;
	vector<string> statementCodeLines;
	statementCodeLines.emplace_back();
	auto quote = '\0';
	auto expectBracket = false;
	auto canExpectStacklet = false;
	auto inlineFunctionArguments = false;
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto hash = false;
	auto expectRightArgument = false;
	auto lc = '\0';
	auto llc = '\0';
	for (; i < scriptCode.size(); i++) {
		auto c = scriptCode[i];
		auto nc = i + 1 < scriptCode.size()?scriptCode[i + 1]:'\0';
		// this is some sort of hack, but it works, we need a more sophisticated parser later
		if (c != '-' && c != '>' &&
			c != ' ' && c != '\t' && c != '\n' && c != '\r') canExpectStacklet = c == ',' || c == '(';
		// handle quotes
		if (hash == true && c != '\n') {
			// no op
		} else
		if ((c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
			} else
			if (quote == c) {
				expectRightArgument = false;
				quote = '\0';
			}
			// add char to script line
			statementCodeLines.back() += c;
			//
			inlineFunctionArguments = false;
		} else
		if (quote != '\0') {
			// no op
			if (c == '\n') {
				Console::printLine(scriptFileName + ":" + to_string(line) + ": Newline within string literal is not allowed");
				parseErrors.push_back(scriptFileName + ":" + to_string(line) + ": Newline within string literal is not allowed");
				//
				return false;
			} else {
				statementCodeLines.back() += c;
			}
		} else
		// brackets
		if (c == '(') {
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			bracketCount++;
			expectBracket = false;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		if (c == ')') {
			//
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			bracketCount--;
			// add char to script line
			statementCodeLines.back() += c;
			//
			inlineFunctionArguments = true;
		} else
		// square brackets
		if (c == '[') {
			//
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			squareBracketCount++;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		if (c == ']') {
			//
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			squareBracketCount--;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		// curly brackets
		if (c == '{') {
			//
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			curlyBracketCount++;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		if (c == '}') {
			//
			inlineFunctionArguments = false;
			expectRightArgument = false;
			//
			curlyBracketCount--;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		// hash
		if (c == '#' && curlyBracketCount == 0 && squareBracketCount == 0) {
			// hash
			hash = true;
		} else
		// new line
		if (c == '\r') {
			// ignore
		} else
		// assigment operator
		if (// TODO: implement those prefix/postfix operators properly, for now they get ignored
			//(lc == '+' && c == '+') ||
			//(lc == '-' && c == '-') ||
			//(lc == '+' && c == '+') ||
			//(lc == '-' && c == '-') ||
			(isOperatorChar(lc) == false && c == '!' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '~' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '*' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '/' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '%' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '+' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '-' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '<' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '>' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '&' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '^' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '|' && isOperatorChar(nc) == false) ||
			(isOperatorChar(lc) == false && c == '=' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '<' && c == '=' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '>' && c == '=' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '=' && c == '=' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '!' && c == '=' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '&' && c == '&' && isOperatorChar(nc) == false) ||
			(isOperatorChar(llc) == false && lc == '|' && c == '|' && isOperatorChar(nc) == false)
		) {
			if (expectBracket == false && expectRightArgument == false && bracketCount == 0 && squareBracketCount == 0 && curlyBracketCount == 0) {
				expectRightArgument = true;
			}
			// add char to script line
			statementCodeLines.back() += c;
		} else
		if (lc == '-' && c == '>') {
			// we expect a bracket now for object->xyz() member method call, if we have a possible identifier
			if (inlineFunctionArguments == false && canExpectStacklet == false) expectBracket = true;
			//
			expectRightArgument = false;
			// add char to script line
			statementCodeLines.back() += c;
		} else
		if ((c == '\n' && ++line) || (hash == false && c == ';')) {
			// break here and process script line
			if (expectBracket == false && expectRightArgument == false && bracketCount == 0 && squareBracketCount == 0 && curlyBracketCount == 0) break;
			// unset hash after newline
			if (c == '\n') {
				//
				hash = false;
				//
				statementCodeLines.emplace_back();
			} else {
				statementCodeLines.back() += c;
				//
				inlineFunctionArguments = false;
			}
		} else {
			//
			if (Character::isSpace(c) == false && c != '-' && nc != '>') inlineFunctionArguments = false;
			// add char to script line
			statementCodeLines.back() += c;
			//
			if (Character::isSpace(c) == false) expectRightArgument = false;
		}
		//
		lc = lc == '\\' && c == '\\'?'\0':c;
		llc = lc;
	}

	//
	auto lineIdx = 0;
	for (const auto& line: statementCodeLines) {
		auto trimmedLine = StringTools::trim(line);
		statementCode+= trimmedLine;
		if (statementCode.empty() == false && lineIdx != statementCodeLines.size() - 1) statementCode+= "\n";
		lineIdx++;
	}

	// add last line index
	if (i == scriptCode.size() && scriptCode.back() != '\n') ++line;

	// done
	statement = statementCode;

	//
	return true;
}

bool MinitScript::parseScriptInternal(const string& scriptCode, const string& _module, int lineIdxOffset) {
	//
	auto _scriptFileName = _module.empty() == true?scriptFileName:_module;
	auto scriptCount = scripts.size();
	auto haveScript = false;
	auto lineIdx = LINE_FIRST;
	auto currentLineIdx = LINE_NONE;
	auto statementIdx = STATEMENTIDX_FIRST;
	struct Block {
		enum Type { TYPE_FOR, TYPE_FOREACH, TYPE_IF, TYPE_ELSE, TYPE_ELSEIF, TYPE_SWITCH, TYPE_CASE, TYPE_DEFAULT, TYPE_TRY, TYPE_CATCH };
		Block(Type type, int statementIdx): type(type), statementIdx(statementIdx) {}
		Type type;
		int statementIdx;
	};
	vector<Block> blockStack;
	//
	for (auto i = 0; i < scriptCode.size(); i++) {
		//
		currentLineIdx = lineIdx;

		// try to get next statement code
		string statementCode;
		if (getNextStatement(_scriptFileName, scriptCode, i, lineIdx, statementCode) == false) {
			//
			scriptValid = false;
			return false;
		}

		// add last line index
		if (i == scriptCode.size() && scriptCode.back() != '\n') ++lineIdx;
		//
		if (statementCode.empty() == true) continue;

		// no script yet
		if (haveScript == false) {
			// check if we have to read additional info from code
			if (statementCode == "use:" ||
				statementCode == "function:" ||
				statementCode == "stacklet:" ||
				statementCode == "callable:"
				#if defined(MINITSCRIPT_EVENTS)
					// events
					||
					statementCode == "on:" ||
					statementCode == "on-enabled:"
				#endif
					) {
				//
				i++;
				// we need the condition or name
				for (; i < scriptCode.size(); i++) {
					string nextStatementCode;
					if (getNextStatement(_scriptFileName, scriptCode, i, lineIdx, nextStatementCode) == false) {
						//
						scriptValid = false;
						return false;
					}
					//
					if (nextStatementCode.empty() == false) {
						statementCode+= " " + nextStatementCode;
						break;
					}
				}
			}
			// check if we need to parse ":= name"
			//	applies to on: and on-enabled only
			#if defined(MINITSCRIPT_EVENTS)
				// events
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
							string nextStatementCode;
							if (getNextStatement(_scriptFileName, scriptCode, i, lineIdx, nextStatementCode) == false) {
								//
								scriptValid = false;
								return false;
							}
							//
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
									lc = lc == '\\' && c == '\\'?'\0':c;
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
							string nextStatementCode;
							if (getNextStatement(_scriptFileName, scriptCode, i, lineIdx, nextStatementCode) == false) {
								//
								scriptValid = false;
								return false;
							}
							if (nextStatementCode.empty() == false) {
								statementCode+= " " + nextStatementCode;
								break;
							}
						}
					}
				}
			#endif
			//
			auto moduleUseStatement = false;
			if (statementCode == "module") {
				//
				moduleUseStatement = true;
				// only apply module for main script
				if (_module.empty() == true) this->_module = true;
			} else
			if (StringTools::startsWith(statementCode, "use:") == true) {
				//
				moduleUseStatement = true;

				// parse deferred function script codes,
				//	which are created by parsing map initializers and possible map inline functions
				do {
					auto deferredInlineScriptCodesCopy = deferredInlineScriptCodes;
					deferredInlineScriptCodes.clear();
					for (const auto& functionScriptCodePair: deferredInlineScriptCodesCopy) {
						parseScriptInternal(functionScriptCodePair.second, string(), functionScriptCodePair.first);
					}
				} while (deferredInlineScriptCodes.empty() == false);

				// push to modules
				auto moduleScriptFileName = StringTools::trim(StringTools::substring(statementCode, string("use:").size()));
				if (find(modules.begin(), modules.end(), moduleScriptFileName) != modules.end()) {
					// no op
				} else {
					//
					modules.push_back(moduleScriptFileName);

					// load module script code
					string moduleScriptCode;
					try {
						moduleScriptCode = FileSystem::getContentAsString(scriptPathName, moduleScriptFileName);
					} catch (FileSystem::FileSystemException& fse)	{
						Console::printLine(scriptPathName + "/" + moduleScriptFileName + ": An error occurred: " + fse.what());
						parseErrors.push_back(scriptPathName + "/" + moduleScriptFileName + ": An error occurred: " + fse.what());
						scriptValid = false;
						return false;
					}
					// hash
					nativeModuleHashes.push_back( SHA256::encode(moduleScriptCode));
					// and parse it
					if (parseScriptInternal(moduleScriptCode, moduleScriptFileName) == false) return false;
					// parse module deferred function script codes,
					//	which are created by parsing map initializers and possible map inline functions
					do {
						auto deferredInlineScriptCodesCopy = deferredInlineScriptCodes;
						deferredInlineScriptCodes.clear();
						for (const auto& functionScriptCodePair: deferredInlineScriptCodesCopy) {
							parseScriptInternal(functionScriptCodePair.second, moduleScriptFileName, functionScriptCodePair.first);
						}
					} while (deferredInlineScriptCodes.empty() == false);
				}
			}

			// script type
			auto callable = false;
			auto scriptType = Script::TYPE_NONE;
			if (StringTools::startsWith(statementCode, "function:") == true) scriptType = Script::TYPE_FUNCTION; else
			if (StringTools::startsWith(statementCode, "stacklet:") == true) scriptType = Script::TYPE_STACKLET; else
			#if defined(MINITSCRIPT_EVENTS)
				if (StringTools::startsWith(statementCode, "on:") == true) scriptType = Script::TYPE_ON; else
				if (StringTools::startsWith(statementCode, "on-enabled:") == true) scriptType = Script::TYPE_ONENABLED; else
			#endif
			if (StringTools::startsWith(statementCode, "callable:") == true) {
				callable = true;
				scriptType = Script::TYPE_FUNCTION;
			}
			//
			#if defined(MINITSCRIPT_EVENTS)
				// events
				if (_module.empty() == false &&
					(scriptType == Script::TYPE_ON ||
					scriptType == Script::TYPE_ONENABLED)) {
								Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": 'on:' and  'on-enabled:': Conditional execution functionality is not available in modules");
								parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": 'on:' and  'on-enabled:': Conditional execution functionality is not available in modules");
								scriptValid = false;
								return false;
				} else
			#endif
			if (moduleUseStatement == true) {
				// no op
			} else
			// no, but did we got a new script?
			if (scriptType != Script::TYPE_NONE) {
				// yes
				haveScript = true;
				// functions: argument names
				vector<Script::Argument> arguments;
				// determine statement
				string statement;
				if (scriptType == Script::TYPE_FUNCTION) {
					statement = callable == true?
						StringTools::trim(StringTools::substring(statementCode, string("callable:").size())):
						StringTools::trim(StringTools::substring(statementCode, string("function:").size()));
				} else
				if (scriptType == Script::TYPE_STACKLET) {
					statement = StringTools::trim(StringTools::substring(statementCode, string("stacklet:").size()));
				}
				#if defined(MINITSCRIPT_EVENTS)
					// events
					else
					if (scriptType == Script::TYPE_ON)
						statement = StringTools::trim(StringTools::substring(statementCode, string("on:").size())); else
					if (scriptType == Script::TYPE_ONENABLED)
						statement = StringTools::trim(StringTools::substring(statementCode, string("on-enabled:").size()));
				#endif
				// and name
				string name;
				auto scriptLineNameSeparatorIdx =
					scriptType == Script::TYPE_FUNCTION?
						statement.rfind("function:"):
						(scriptType == Script::TYPE_STACKLET?
							statement.rfind("stacklet:"):
							statement.rfind(":=")
						);
				if (scriptLineNameSeparatorIdx != string::npos) {
					name =
						StringTools::trim(
							StringTools::substring(
								statement,
								scriptLineNameSeparatorIdx +
									(scriptType == Script::TYPE_FUNCTION?string("function").size():(scriptType == Script::TYPE_STACKLET?string("stacklet").size():string(":=").size()))
							)
						);
					statement = StringTools::trim(StringTools::substring(statement, 0, scriptLineNameSeparatorIdx));
				}
				if (scriptType == Script::TYPE_FUNCTION ||
					scriptType == Script::TYPE_STACKLET) {
					auto leftBracketIdx = statement.find('(');
					auto rightBracketIdx = statement.find(')');
					if (leftBracketIdx != string::npos || leftBracketIdx != string::npos) {
						if (leftBracketIdx == string::npos) {
							Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Unbalanced bracket count");
							parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Unbalanced bracket count");
							scriptValid = false;
							return false;
						} else
						if (rightBracketIdx == string::npos) {
							Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Unbalanced bracket count");
							parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Unbalanced bracket count");
							scriptValid = false;
							return false;
						} else {
							auto argumentNamesString = StringTools::trim(StringTools::substring(statement, leftBracketIdx + 1, rightBracketIdx));
							auto argumentNamesTokenized = StringTools::tokenize(argumentNamesString, ",");
							statement = StringTools::substring(statement, 0, leftBracketIdx);
							for (const auto& argumentName: argumentNamesTokenized) {
								auto argumentNameTrimmed = StringTools::trim(argumentName);
								auto reference = false;
								auto privateScope = false;
								if (StringTools::startsWith(argumentNameTrimmed, "&&") == true) {
									reference = true;
									privateScope = true;
									argumentNameTrimmed = StringTools::trim(StringTools::substring(argumentNameTrimmed, 2));
								} else
								if (StringTools::startsWith(argumentNameTrimmed, "&") == true) {
									reference = true;
									argumentNameTrimmed = StringTools::trim(StringTools::substring(argumentNameTrimmed, 1));
								}
								if (scriptType == Script::TYPE_FUNCTION) {
									if (StringTools::regexMatch(argumentNameTrimmed, "\\$[a-zA-Z0-9_]+") == true) {
										arguments.emplace_back(
											argumentNameTrimmed,
											reference,
											privateScope
										);
									} else {
										Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Invalid argument name: '" + argumentNameTrimmed + "'");
										parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Invalid argument name: '" + argumentNameTrimmed + "'");
										scriptValid = false;
										return false;

									}
								} else
								if (scriptType == Script::TYPE_STACKLET) {
									if (StringTools::regexMatch(argumentNameTrimmed, "[a-zA-Z0-9_]+") == true) {
										arguments.emplace_back(
											argumentNameTrimmed,
											reference,
											false
										);
									} else {
										Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Invalid stacklet parent stacklet/function: '" + argumentNameTrimmed + "'");
										parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": " + (scriptType == Script::TYPE_FUNCTION?"function":"stacklet") + ": Invalid stacklet parent stacklet/function: '" + argumentNameTrimmed + "'");
										scriptValid = false;
										return false;
									}
								}
							}
						}

					}
				}
				auto trimmedStatement = StringTools::trim(statement);
				Statement evaluateStatement(
					_scriptFileName,
					currentLineIdx + lineIdxOffset,
					STATEMENTIDX_FIRST,
					"internal.script.evaluate(" + StringTools::replace(StringTools::replace(trimmedStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
					"internal.script.evaluate(" + StringTools::replace(StringTools::replace(trimmedStatement, "\\", "\\\\"), "\"", "\\\"") + ")",
					STATEMENTIDX_NONE
				);
				auto conditionOrNameExecutable = doStatementPreProcessing(trimmedStatement, evaluateStatement);
				auto conditionOrName = trimmedStatement;
				auto emitCondition = StringTools::regexMatch(conditionOrName, "[a-zA-Z0-9_]+");
				statementIdx = STATEMENTIDX_FIRST;
				// add to user functions
				if (scriptType == Script::TYPE_FUNCTION || scriptType == Script::TYPE_STACKLET) {
					functions[conditionOrName] = scripts.size();
				}

				// push to scripts
				scripts.emplace_back(
					_module,
					scriptType,
					currentLineIdx + lineIdxOffset,
					conditionOrName,
					conditionOrNameExecutable,
					Statement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx,
						conditionOrName,
						conditionOrNameExecutable,
						STATEMENTIDX_NONE
					),
					SyntaxTreeNode(),
					name,
					emitCondition,
					initializer_list<Statement>{},
					initializer_list<SyntaxTreeNode>{},
					callable,
					arguments,
					scripts.size()
				);
			} else {
				Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": expecting 'on:', 'on-enabled:', 'stacklet:', 'function:', 'callable:'");
				parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": expecting 'on:', 'on-enabled:', 'stacklet:', 'function:', 'callable:'");
				scriptValid = false;
				return false;
			}
		} else {
			if (StringTools::startsWith(statementCode, "function:") == true ||
				StringTools::startsWith(statementCode, "stacklet:") == true ||
				StringTools::startsWith(statementCode, "callable:") == true
				#if defined(MINITSCRIPT_EVENTS)
					// events
					||
					StringTools::startsWith(statementCode, "on:") == true ||
					StringTools::startsWith(statementCode, "on-enabled:") == true
				#endif
			) {
				Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Unbalanced if/elseif/else/switch/case/default/forCondition/forTime/end");
				parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Unbalanced if/elseif/else/switch/case/default/forCondition/forTime/end");
				scriptValid = false;
				return false;
			} else {
				//
				smatch matches;
				auto regexStatementCode = StringTools::replace(statementCode, "\n", " ");
				//
				if (statementCode == "end") {
					if (blockStack.empty() == false) {
						auto block = blockStack.back();
						blockStack.erase(blockStack.begin() + blockStack.size() - 1);
						switch(block.type) {
							case Block::TYPE_FOR:
							case Block::TYPE_FOREACH:
								{
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										block.statementIdx
									);
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
								}
								break;
							case Block::TYPE_IF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_ELSE:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_ELSEIF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_SWITCH:
								{
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_CASE:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size() + 1;
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_DEFAULT:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size() + 1;
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;
							case Block::TYPE_CATCH:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size() + 1;
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx,
										statementCode,
										statementCode,
										STATEMENTIDX_NONE
									);
								}
								break;

						}
					} else {
						// end of 'on:', 'on-enabled:', 'function' ... block
						scripts.back().statements.emplace_back(
							_scriptFileName,
							currentLineIdx + lineIdxOffset,
							statementIdx,
							statementCode,
							statementCode,
							STATEMENTIDX_NONE
						);
						haveScript = false;
					}
				} else
				if (statementCode == "else") {
					if (blockStack.empty() == false) {
						auto block = blockStack.back();
						blockStack.erase(blockStack.begin() + blockStack.size() - 1);
						switch(block.type) {
							case Block::TYPE_IF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									// we push "else" to statements later
								}
								break;
							case Block::TYPE_ELSEIF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									// we push "else" to statements later
								}
								break;
							default:
								Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": else without if/elseif");
								parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": else without if/elseif");
								scriptValid = false;
								return false;
						}
						blockStack.emplace_back(
							Block::TYPE_ELSE,
							statementIdx
						);
					} else {
						Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": else without if");
						parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": else without if");
						scriptValid = false;
						return false;
					}
				} else
				if (StringTools::regexMatch(regexStatementCode, "^elseif[\\s]*\\(.*\\)$") == true) {
					Statement elseIfStatement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						STATEMENTIDX_FIRST,
						StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
						StringTools::replace(StringTools::replace(statementCode, "\\", "\\\\"), "\"", "\\\""),
						STATEMENTIDX_NONE
					);
					auto executableStatement = doStatementPreProcessing(statementCode, elseIfStatement);
					if (blockStack.empty() == false) {
						auto block = blockStack.back();
						blockStack.erase(blockStack.begin() + blockStack.size() - 1);
						switch(block.type) {
							case Block::TYPE_IF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									// we push "if" to statements later
								}
								break;
							case Block::TYPE_ELSEIF:
								{
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									// we push "if" to statements later
								}
								break;
							default:
								Console::printLine(scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": elseif without if");
								parseErrors.push_back(scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": elseif without if");
								scriptValid = false;
								return false;
						}
						blockStack.emplace_back(
							Block::TYPE_ELSEIF,
							statementIdx
						);
					} else {
						Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": elseif without if");
						parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": elseif without if");
						scriptValid = false;
						return false;
					}
				} else
				if (StringTools::regexMatch(regexStatementCode, "^catch[\\s]*\\((.*)\\)$", &matches) == true) {
					auto exceptionVariable = matches[1].str();
					if (blockStack.empty() == false) {
						auto block = blockStack.back();
						blockStack.erase(blockStack.begin() + blockStack.size() - 1);
						switch(block.type) {
							case Block::TYPE_TRY:
								{
									//
									scripts.back().statements[block.statementIdx].gotoStatementIdx = scripts.back().statements.size();
									// create initialize statement and push it
									string initializeVariableStatement =
										"setVariable(\"" +
											StringTools::replace(StringTools::replace(exceptionVariable, "\\", "\\\\"), "\"", "\\\"") +
											"\", " +
											"null"
										")";
									scripts.back().statements.emplace_back(
										_scriptFileName,
										currentLineIdx + lineIdxOffset,
										statementIdx++,
										statementCode,
										initializeVariableStatement,
										STATEMENTIDX_NONE
									);
									// we push "catch" to statements later
								}
								break;
						}
						blockStack.emplace_back(
							Block::TYPE_CATCH,
							statementIdx
						);
					} else {
						Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": catch without try");
						parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": catch without try");
						scriptValid = false;
						return false;
					}
				} else
				if (StringTools::regexMatch(regexStatementCode, "^for[\\s]*\\(.*\\)$") == true) {
					Statement generatedStatement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						STATEMENTIDX_FIRST,
						statementCode,
						statementCode,
						STATEMENTIDX_NONE
					);
					// parse for statement
					string_view forMethodName;
					vector<ParserArgument> forArguments;
					string executableStatement = doStatementPreProcessing(statementCode, generatedStatement);
					// success?
					if (parseStatement(executableStatement, forMethodName, forArguments, generatedStatement) == true &&
						forArguments.size() == 3) {
						// create initialize statement
						string initializeStatement = string(forArguments[0].argument);
						scripts.back().statements.emplace_back(
							_scriptFileName,
							currentLineIdx + lineIdxOffset,
							statementIdx++,
							statementCode,
							initializeStatement,
							STATEMENTIDX_NONE
						);
						//
						blockStack.emplace_back(
							Block::TYPE_FOR,
							statementIdx
						);
						//
						statementCode = "forCondition(" + string(forArguments[1].argument) + ", -> { " + string(forArguments[2].argument) + " })";
					} else {
						Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Invalid for statement");
						parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Invalid for statement");
						scriptValid = false;
						return false;
					}
				} else
				// array/set forEach
				if (StringTools::regexMatch(regexStatementCode, "^forEach[\\s]*\\([\\s]*(&?\\$[a-zA-Z0-9_]+)[\\s]*in[\\s]*((\\$[a-zA-Z0-9_]+)|(\\[.*\\])|(\\{.*\\}))[\\s]*\\)$", &matches) == true) {
					Statement generatedStatement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						STATEMENTIDX_FIRST,
						statementCode,
						statementCode,
						STATEMENTIDX_NONE
					);
					//
					auto iterationDepth = 0;
					for (const auto& block: blockStack) {
						if (block.type == Block::TYPE_FOREACH) iterationDepth++;
					}
					//
					auto entryReference = false;
					auto entryVariable = matches[1].str();
					if (StringTools::startsWith(entryVariable, "&") == true) {
						entryReference = true;
						entryVariable = StringTools::substring(entryVariable, 1);
					}
					auto containerByInitializer = false;
					auto containerVariable = matches[2].str();
					string containerInitializer;
					if (StringTools::startsWith(containerVariable, "[") == true || StringTools::startsWith(containerVariable, "{") == true) {
						containerByInitializer = true;
						containerInitializer = containerVariable;
						containerVariable = string("$___cv_" + to_string(iterationDepth));
					}
					auto initializationStackletVariable = string("$___is_" + to_string(iterationDepth));
					auto containerVariableType = string("$___vt_" + to_string(iterationDepth));
					auto iterationVariable = string("$___it_" + to_string(iterationDepth));
					auto entryVariableBackup = string("$___evb_" + to_string(iterationDepth));
					auto containerArrayVariable = string("$___cav_" + to_string(iterationDepth));
					auto containerArrayVariableBackup = string("$___cavb_" + to_string(iterationDepth));
					string iterationUpdate =
						entryReference == true?
							"setVariableReference(\"" + entryVariable + "\", " + containerArrayVariable + "[" + iterationVariable + "])":
							entryVariable + " = " + containerArrayVariable + "[" + iterationVariable + "]";
					//
					string initialization =
						initializationStackletVariable + " = -> { " +
							"if (script.isNative() == true); " +
								"setVariableReference(\"" + containerArrayVariableBackup + "\", " + containerArrayVariable + "); " +
								"setVariableReference(\"" + entryVariableBackup + "\", " + entryVariable + "); " +
							"end; " +
							containerVariableType + " = getType(" + containerVariable + "); " +
							"if (" + containerVariableType + " == \"Array\"); " +
								"setVariableReference(\"" + containerArrayVariable + "\", " + containerVariable + "); " +
							"elseif (" + containerVariableType + " == \"Set\"); " +
								containerArrayVariable + " = Set::getKeys(" + containerVariable + "); " +
							"else; " +
								"throw(\"forEach() expects array or set as container, but got \" + String::toLowerCase(getType(" + containerVariable + "))); " +
							"end; " +
							iterationVariable + " = 0; " +
							"if (" + iterationVariable + " < Array::getSize(" + containerArrayVariable + ")); " +
								iterationUpdate + "; " +
							"end;" +
						"}";
					//
					if (containerByInitializer == true) {
						scripts.back().statements.emplace_back(
							_scriptFileName,
							currentLineIdx + lineIdxOffset,
							statementIdx++,
							statementCode,
							doStatementPreProcessing(containerVariable + " = " + containerInitializer, generatedStatement),
							STATEMENTIDX_NONE
						);
					}
					scripts.back().statements.emplace_back(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx++,
						statementCode,
						doStatementPreProcessing(initialization, generatedStatement),
						STATEMENTIDX_NONE
					);
					scripts.back().statements.emplace_back(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx++,
						statementCode,
						"internal.script.callStacklet(" + initializationStackletVariable + ")",
						STATEMENTIDX_NONE
					);
					blockStack.emplace_back(
						Block::TYPE_FOREACH,
						statementIdx
					);
					//
					statementCode =
						"forCondition(" + iterationVariable + " < Array::getSize(" + containerArrayVariable + "), " +
						"-> { " +
							iterationVariable + "++" + "; " +
							"if (" + iterationVariable + " < Array::getSize(" + containerArrayVariable + ")); " +
								iterationUpdate + "; " +
							"else; " +
								"if (script.isNative() == true); " +
									"setVariableReference(\"" + containerArrayVariable + "\", " + containerArrayVariableBackup + "); " +
									"setVariableReference(\"" + entryVariable + "\", " + entryVariableBackup + "); " +
								"else; " +
									"unsetVariableReference(\"" + containerArrayVariable + "\"); " +
									"unsetVariableReference(\"" + entryVariable + "\"); " +
								"end; " +
								"setVariable(\"" + containerArrayVariable + "\", $$.___ARRAY); " +
								"setVariable(\"" + entryVariable + "\", $$.___NULL); " +
								(containerByInitializer == true?"setVariable(\"" + containerVariable + "\", $$.___ARRAY); ":"") +
							"end; " +
						"})";
				} else
				// map forEach
				if (StringTools::regexMatch(regexStatementCode, "^forEach[\\s]*\\([\\s]*(\\$[a-zA-Z0-9_]+)[\\s]*,[\\s]*(&?\\$[a-zA-Z0-9_]+)[\\s]*in[\\s]*((\\$[a-zA-Z0-9_]+)|(\\[.*\\])|(\\{.*\\}))[\\s]*\\)$", &matches) == true) {
					Statement generatedStatement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						STATEMENTIDX_FIRST,
						statementCode,
						statementCode,
						STATEMENTIDX_NONE
					);
					//
					auto iterationDepth = 0;
					for (const auto& block: blockStack) {
						if (block.type == Block::TYPE_FOREACH) iterationDepth++;
					}
					//
					auto entryKeyVariable = matches[1].str();
					auto entryValueReference = false;
					auto entryValueVariable = matches[2].str();
					if (StringTools::startsWith(entryValueVariable, "&") == true) {
						entryValueReference = true;
						entryValueVariable = StringTools::substring(entryValueVariable, 1);
					}
					auto containerByInitializer = false;
					auto containerVariable = matches[3].str();
					string containerInitializer;
					if (StringTools::startsWith(containerVariable, "[") == true || StringTools::startsWith(containerVariable, "{") == true) {
						containerByInitializer = true;
						containerInitializer = containerVariable;
						containerVariable = string("$___cv_" + to_string(iterationDepth));
					}
					auto initializationStackletVariable = string("$___is_" + to_string(iterationDepth));
					auto containerVariableType = string("$___vt_" + to_string(iterationDepth));
					auto iterationVariable = string("$___it_" + to_string(iterationDepth));
					auto entryValueVariableBackup = string("$___evb_" + to_string(iterationDepth));
					auto containerArrayVariable = string("$___cav_" + to_string(iterationDepth));
					auto containerArrayVariableBackup = string("$___cavb_" + to_string(iterationDepth));
					string iterationUpdate =
						entryKeyVariable + " = " + containerArrayVariable + "[" + iterationVariable + "]; " +
						(entryValueReference == true?
							"setVariableReference(\"" + entryValueVariable + "\", Map::getReference(" + containerVariable + ", " + entryKeyVariable + "))":
							entryValueVariable + " = Map::get(" + containerVariable + ", " + entryKeyVariable + ")"
						);
					//
					string initialization =
						initializationStackletVariable + " = -> { " +
							"if (script.isNative() == true); " +
								"setVariableReference(\"" + containerArrayVariable + "\", " + containerArrayVariableBackup + "); " +
								"setVariableReference(\"" + entryValueVariable + "\", " + entryValueVariableBackup + "); " +
							"end; " +
							containerVariableType + " = getType(" + containerVariable + "); " +
							"if (" + containerVariableType + " == \"Map\"); " +
								containerArrayVariable + " = Map::getKeys(" + containerVariable + "); " +
							"else; " +
								"throw(\"forEach() expects map as container, but got \" + String::toLowerCase(getType(" + containerVariable + "))); " +
							"end; " +
							iterationVariable + " = 0; " +
							"if (" + iterationVariable + " < Array::getSize(" + containerArrayVariable + ")); " +
								iterationUpdate + "; " +
							"end; " +
						"}";
					//
					if (containerByInitializer == true) {
						scripts.back().statements.emplace_back(
							_scriptFileName,
							currentLineIdx + lineIdxOffset,
							statementIdx++,
							statementCode,
							doStatementPreProcessing(containerVariable + " = " + containerInitializer, generatedStatement),
							STATEMENTIDX_NONE
						);
					}
					scripts.back().statements.emplace_back(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx++,
						statementCode,
						doStatementPreProcessing(initialization, generatedStatement),
						STATEMENTIDX_NONE
					);
					scripts.back().statements.emplace_back(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx++,
						statementCode,
						"internal.script.callStacklet(" + initializationStackletVariable + ")",
						STATEMENTIDX_NONE
					);
					blockStack.emplace_back(
						Block::TYPE_FOREACH,
						statementIdx
					);
					//
					statementCode =
						"forCondition(" + iterationVariable + " < Array::getSize(" + containerArrayVariable + "), " +
						"-> { " +
							iterationVariable + "++" + "; " +
							"if (" + iterationVariable + " < Array::getSize(" + containerArrayVariable + ")); " +
								iterationUpdate + "; " +
							"else; " +
								"if (script.isNative() == true); " +
									"setVariableReference(\"" + containerArrayVariable + "\", " + containerArrayVariableBackup + "); " +
									"setVariableReference(\"" + entryValueVariable + "\", " + entryValueVariableBackup + "); " +
								"else; "
									"unsetVariableReference(\"" + containerArrayVariable + "\"); " +
									"unsetVariableReference(\"" + entryValueVariable + "\"); " +
								"end; " +
								"setVariable(\"" + containerArrayVariable + "\", $$.___ARRAY); " +
								"setVariable(\"" + entryKeyVariable + "\", $$.___NULL); "
								"setVariable(\"" + entryValueVariable + "\", $$.___NULL); " +
								(containerByInitializer == true?"setVariable(\"" + containerVariable + "\", $$.___ARRAY); ":"") +
							"end;"
						"})";
				} else
				if (StringTools::regexMatch(regexStatementCode, "^forEach[\\s]*\\(.*\\)$", &matches) == true) {
					Console::printLine(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Invalid forEach statement");
					parseErrors.push_back(_scriptFileName + ":" + to_string(currentLineIdx + lineIdxOffset) + ": Invalid forEach statement");
					scriptValid = false;
					return false;
				}
				// do we need to push to block stack?
				if (StringTools::regexMatch(regexStatementCode, "^forTime[\\s]*\\(.*\\)$") == true ||
					StringTools::regexMatch(regexStatementCode, "^forCondition[\\s]*\\(.*\\)$") == true) {
					blockStack.emplace_back(
						Block::TYPE_FOR,
						statementIdx
					);
				} else
				if (StringTools::regexMatch(regexStatementCode, "^if[\\s]*\\(.*\\)$") == true) {
					blockStack.emplace_back(
						Block::TYPE_IF,
						statementIdx
					);
				} else
				if (StringTools::regexMatch(regexStatementCode, "^switch[\\s]*\\(.*\\)$") == true) {
					blockStack.emplace_back(
						Block::TYPE_SWITCH,
						STATEMENTIDX_NONE
					);
				} else
				if (StringTools::regexMatch(regexStatementCode, "^case[\\s]*\\(.*\\)$") == true) {
					blockStack.emplace_back(
						Block::TYPE_CASE,
						statementIdx
					);
				} else
				if (StringTools::regexMatch(regexStatementCode, "^default[\\s]*$") == true) {
					blockStack.emplace_back(
						Block::TYPE_DEFAULT,
						statementIdx
					);
				} else
				if (StringTools::regexMatch(regexStatementCode, "^try[\\s]*$") == true) {
					blockStack.emplace_back(
						Block::TYPE_TRY,
						statementIdx
					);
				}
				// push to statements now, except "end", we already did push that
				if (statementCode != "end") {
					// add to statements
					Statement generatedStatement(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						STATEMENTIDX_FIRST,
						statementCode,
						statementCode,
						STATEMENTIDX_NONE
					);
					//
					scripts.back().statements.emplace_back(
						_scriptFileName,
						currentLineIdx + lineIdxOffset,
						statementIdx,
						statementCode,
						doStatementPreProcessing(statementCode, generatedStatement),
						STATEMENTIDX_NONE
					);
				}
			}
			//
			statementIdx++;
		}
	}

	// check for unbalanced if/elseif/else/switch/case/default/forCondition/forTime/end
	if (scriptValid == true && blockStack.empty() == false) {
		Console::printLine(_scriptFileName + ": Unbalanced if/elseif/else/switch/case/default/forCondition/forTime/end");
		parseErrors.push_back(_scriptFileName + ":" + "Unbalanced if/elseif/else/switch/case/default/forCondition/forTime/end");
		scriptValid = false;
		return false;
	}

	// create syntax tree
	for (auto scriptIdx = scriptCount; scriptIdx < scripts.size(); scriptIdx++) {
		auto& script = scripts[scriptIdx];
		// create syntax tree of executable condition if we have any
		if (script.emitCondition == false && script.executableCondition.empty() == false) {
			string_view method;
			vector<ParserArgument> arguments;
			if (parseStatement(script.executableCondition, method, arguments, script.conditionStatement) == false) {
				scriptValid = false;
				return false;
			} else
			if (createStatementSyntaxTree(_scriptFileName, SCRIPTIDX_NONE, method, arguments, script.conditionStatement, script.conditionSyntaxTree) == false) {
				scriptValid = false;
				return false;
			}
		}
		// create script syntax tree
		for (auto statementIdx = STATEMENTIDX_FIRST; statementIdx < script.statements.size(); statementIdx++) {
			const auto& statement = script.statements[statementIdx];
			script.syntaxTree.emplace_back();
			auto& syntaxTree = script.syntaxTree.back();
			string_view methodName;
			vector<ParserArgument> arguments;
			if (parseStatement(statement.executableStatement, methodName, arguments, statement) == false) {
				scriptValid = false;
				return false;
			} else
			if (createStatementSyntaxTree(_scriptFileName, scriptIdx, methodName, arguments, statement, syntaxTree) == false) {
				scriptValid = false;
				return false;
			}
		}
	}
	//
	return scriptValid;
}

void MinitScript::parseScript(const string& pathName, const string& fileName, bool nativeOnly) {
	//
	scriptValid = true;
	scriptPathName = pathName;
	scriptFileName = fileName;

	//
	for (const auto& [methodName, method]: methods) delete method;
	for (const auto& [stateMachineStateId, stateMachineState]: stateMachineStates) delete stateMachineState;
	methods.clear();
	stateMachineStates.clear();

	//
	unregisterVariables();
	while (hasScriptState() == true) popScriptState();

	// push root script state and reset execution
	pushScriptState();
	resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_WAIT_FOR_CONDITION);

	//
	string scriptCode;
	if (native == false || nativeOnly == false) {
		try {
			scriptCode = FileSystem::getContentAsString(scriptPathName, scriptFileName);
		} catch (FileSystem::FileSystemException& fse)	{
			Console::printLine(scriptPathName + "/" + scriptFileName + ": An error occurred: " + fse.what());
			parseErrors.push_back(scriptPathName + "/" + scriptFileName + ": An error occurred: " + fse.what());
			scriptValid = true;
			return;
		}
	}

	//
	{
		auto scriptHash = SHA256::encode(scriptCode);
		if (native == true) {
			// check modules hashes also
			string nativeModuleHashesConcatenated;
			for (const auto& moduleHash: nativeModuleHashes) nativeModuleHashesConcatenated+= moduleHash;
			string moduleHashesConcatenated;
			//
			if (nativeOnly == false) {
				for (const auto& moduleScriptFileName: modules) {
					// load module script code
					string moduleScriptCode;
					try {
						moduleScriptCode = FileSystem::getContentAsString(scriptPathName, moduleScriptFileName);
					} catch (FileSystem::FileSystemException& fse)	{
						Console::printLine(scriptPathName + "/" + moduleScriptFileName + ": An error occurred: " + fse.what());
						parseErrors.push_back(scriptPathName + "/" + moduleScriptFileName + ": An error occurred: " + fse.what());
					}
					// hash
					moduleHashesConcatenated+= SHA256::encode(moduleScriptCode);
				}
			}
			//
			if (nativeOnly == true ||
				(scriptHash == nativeHash && moduleHashesConcatenated == nativeModuleHashesConcatenated)) {
				scripts = nativeScripts;
				functions = nativeFunctions;
				registerStateMachineStates();
				registerMethods();
				initializeScript();
				return;
			} else {
				Console::printLine(scriptPathName + "/" + scriptFileName + ": Scripts have changed. Scripts will be run in interpreted mode. Retranspile and recompile your scripts if you want to run it natively.");
				// unset some native related variables
				native = false;
				_module = false;
				modules = {};
			}
		}
		nativeHash = scriptHash;
	}

	//
	registerStateMachineStates();
	registerMethods();

	//
	if (parseScriptInternal(scriptCode) == false) return;

	// parse deferred function script codes,
	//	which are created by parsing map initializers and possible map inline functions
	do {
		auto deferredInlineScriptCodesCopy = deferredInlineScriptCodes;
		deferredInlineScriptCodes.clear();
		for (const auto& functionScriptCodePair: deferredInlineScriptCodesCopy) {
			parseScriptInternal(functionScriptCodePair.second, string(), functionScriptCodePair.first);
		}
	} while (deferredInlineScriptCodes.empty() == false);

	// set up stacklet and function indices
	for (auto scriptIdx = 0; scriptIdx < scripts.size(); scriptIdx++) {
		//
		if (Setup::setupFunctionAndStackletScriptIndices(this, scriptIdx, parseErrors) == false) {
			scriptValid = false;
			return;
		}
	}

	// validations
	if (scriptValid == true) {
		for (auto scriptIdx = 0; scriptIdx < scripts.size(); scriptIdx++) {
			const auto& script = scripts[scriptIdx];
			//
			if (script.type == MinitScript::Script::TYPE_STACKLET) {
				// valid: root scope
				if (script.arguments.empty()) continue;
				// invalid: more than 1 argument
				if (script.arguments.size() != 1) {
					Console::printLine(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: only none(for root scope) or one argument is allowed, which defines a function/stacklet as stacklet scope");
					parseErrors.push_back(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: only none(for root scope) or one argument is allowed, which defines a function/stacklet as stacklet scope");
					scriptValid = false;
					return;
				}
				//
				auto stackletScopeScriptIdx = getFunctionScriptIdx(script.arguments[0].name);
				// invalid: scope function/stacklet not found
				if (stackletScopeScriptIdx == SCRIPTIDX_NONE) {
					Console::printLine(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: scope function/stacklet not found: " + script.arguments[0].name);
					parseErrors.push_back(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: scope function/stacklet not found: " + script.arguments[0].name);
					scriptValid = false;
					return;
				} else
				// invalid: stacklet can not have itself as scope stacklet
				if (stackletScopeScriptIdx == scriptIdx) {
					Console::printLine(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: scope function/stacklet can not be the stacklet itself");
					parseErrors.push_back(scriptFileName + ": Stacklet: " + script.condition + ": invalid arguments: scope function/stacklet can not be the stacklet itself");
					scriptValid = false;
					return;
				}
			}
			//
			if (script.type == MinitScript::Script::TYPE_FUNCTION
				#if defined(MINITSCRIPT_EVENTS)
					||
					script.type == MinitScript::Script::TYPE_ON ||
					script.type == MinitScript::Script::TYPE_ONENABLED
				#endif
				) {
				//
				if (Validations::validateStacklets(this, scriptIdx, parseErrors) == false) {
					scriptValid = false;
					return;
				}
			}
			//
			if (script.type == MinitScript::Script::TYPE_FUNCTION) {
				//
				if (script.callable == true) {
					//
					if (Validations::validateCallable(this, script.condition, parseErrors) == false) {
						scriptValid = false;
						return;
					}
				} else {
					//
					vector<string> functionStack;
					//
					if (Validations::validateContextFunctions(this, script.condition, functionStack, parseErrors) == false) {
						scriptValid = false;
						return;
					}
				}
			}
		}
	}

	//
	initializeScript();
}

void MinitScript::initializeScript() {
	if (VERBOSE == true) Console::printLine("MinitScript::initializeScript(): '" + scriptFileName + ": Starting script.");
	if (scriptValid == false) {
		Console::printLine(scriptFileName + ": Script not valid: not starting");
		return;
	}
	//
	registerVariables();
}

void MinitScript::startScript() {
	if (VERBOSE == true) Console::printLine("MinitScript::startScript(): '" + scriptFileName + ": Starting script.");
	if (scriptValid == false) {
		Console::printLine(scriptFileName + ": Script not valid: not starting");
		return;
	}
	if (hasFunction("main") == true) {
		vector<Variable> callArguments(0);
		span callArgumentsSpan(callArguments);
		Variable returnValue;
		call("main", callArgumentsSpan, returnValue);
	}
	// events
	#if defined(MINITSCRIPT_EVENTS)
		//
		else
		if (hasCondition("initialize") == true) {
			emit("initialize");
		}
	#endif
}

#if defined(MINITSCRIPT_EVENTS)
	// events
	int MinitScript::determineScriptIdxToStart() {
		if (VERBOSE == true) Console::printLine("MinitScript::determineScriptIdxToStart()");
		auto nothingScriptIdx = SCRIPTIDX_NONE;
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			if (script.type != Script::TYPE_ON) {
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
				Variable returnValue;
				if (evaluateInternal(script.condition, script.executableCondition, returnValue) == true) {
					auto returnValueBoolValue = false;
					if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
						Console::printLine("MinitScript::determineScriptIdxToStart(): " + script.condition + ": Expecting boolean return value, but got: " + returnValue.getAsString());
						conditionMet = false;
					} else
					if (returnValueBoolValue == false) {
						conditionMet = false;
					}
				} else {
					Console::printLine("MinitScript::determineScriptIdxToStart(): " + scriptFileName + ":" + to_string(script.line) + ": " + script.condition + ": Parse error");
				}
				if (conditionMet == false) {
					if (VERBOSE == true) {
						Console::print("MinitScript::determineScriptIdxToStart(): " + script.condition + ": FAILED");
					}
				} else {
					if (VERBOSE == true) {
						Console::print("MinitScript::determineScriptIdxToStart(): " + script.condition + ": OK");
					}
					return scriptIdx;
				}
			}
			scriptIdx++;
		}
		return nothingScriptIdx;
	}

	int MinitScript::determineNamedScriptIdxToStart() {
		if (VERBOSE == true) Console::printLine("MinitScript::determineNamedScriptIdxToStart()");
		// TODO: we could have a hash map here to speed up enabledConditionName -> script lookup
		const auto& scriptState = getScriptState();
		for (const auto& enabledConditionName: enabledNamedConditions) {
			auto scriptIdx = 0;
			for (const auto& script: scripts) {
				if (script.type != Script::TYPE_ONENABLED ||
					script.name != enabledConditionName) {
					// no op
				} else {
					auto conditionMet = true;
					Variable returnValue;
					if (evaluateInternal(script.condition, script.executableCondition, returnValue) == true) {
						auto returnValueBoolValue = false;
						if (returnValue.getBooleanValue(returnValueBoolValue, false) == false) {
							Console::printLine("MinitScript::determineNamedScriptIdxToStart(): " + script.condition + ": Expecting boolean return value, but got: " + returnValue.getAsString());
							conditionMet = false;
						} else
						if (returnValueBoolValue == false) {
							conditionMet = false;
						}
					} else {
						Console::printLine("MinitScript::determineNamedScriptIdxToStart(): " + scriptFileName + ":" + to_string(script.line) + ": " + script.condition + ": Parse error");
					}
					if (conditionMet == false) {
						if (VERBOSE == true) {
							Console::print("MinitScript::determineNamedScriptIdxToStart(): " + script.condition + ": FAILED");
						}
					} else {
						if (VERBOSE == true) {
							Console::print("MinitScript::determineNamedScriptIdxToStart(): " + script.condition + ": OK");
						}
						return scriptIdx;
					}
				}
				scriptIdx++;
			}
		}
		return SCRIPTIDX_NONE;
	}
#endif

const string MinitScript::doStatementPreProcessing(const string& processedStatement, const Statement& statement, bool setVariableStatement, bool memberAccessPropertyStatement) {
	auto preprocessedStatement = processedStatement;
	//
	struct StatementOperator {
		int idx { OPERATORIDX_NONE };
		int idx2 { OPERATORIDX_NONE };
		Operator operator_ { OPERATOR_NONE };
	};
	//
	auto trimArgument = [](const string& argument, bool removeBrackets = true) -> const string {
		auto leftNewLineCount = 0;
		for (auto i = 0; i < argument.size(); i++) {
			auto c = argument[i];
			if (c == '\n') {
				leftNewLineCount++;
			} else
			if (Character::isSpace(c) == false) {
				break;
			}
		}
		auto rightNewLineCount = 0;
		for (int i = argument.size() - 1; i >= 0; i--) {
			auto c = argument[i];
			if (c == '\n') {
				rightNewLineCount++;
			} else
			if (Character::isSpace(c) == false) {
				break;
			}
		}
		auto processedArgument = StringTools::trim(argument);
		if (removeBrackets == true &&
			StringTools::startsWith(processedArgument, "(") == true && StringTools::endsWith(processedArgument, ")") == true) {
			processedArgument = StringTools::substring(processedArgument, 1, processedArgument.size() - 1);
		}
		return processedArgument.empty() == true?string():StringTools::generate("\n", leftNewLineCount) + processedArgument + StringTools::generate("\n", rightNewLineCount);
	};
	//
	auto findLeftArgument = [&](const string& statement, int position, int& length, string& brackets, bool removeBrackets = true) -> const string {
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
			auto lc = i > 0?statement[i - 1]:'\0';
			if (lc == '\\' && c == '\\') lc = '\0';
			//
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
						return trimArgument(argument, removeBrackets);
					}
					argument = c + argument;
				} else
				if (c == '[') {
					squareBracketCount--;
					if (squareBracketCount < 0) {
						brackets = "[]";
						return trimArgument(argument, removeBrackets);
					}
					argument = c + argument;
				} else
				if (c == '{') {
					curlyBracketCount--;
					if (curlyBracketCount < 0) {
						brackets = "{}";
						return trimArgument(argument, removeBrackets);
					}
					argument = c + argument;
				} else
				if (squareBracketCount == 0 && curlyBracketCount == 0 && c == ',') {
					if (bracketCount == 0) return trimArgument(argument, removeBrackets);
					argument = c + argument;
				} else {
					argument = c + argument;
				}
			} else
			if (quote != '\0') {
				argument = c + argument;
			}
			length++;
		}
		return trimArgument(argument, removeBrackets);
	};
	//
	auto findRightArgument = [&](const string& statement, int position, int& length, string& brackets, bool removeBrackets = true) -> const string {
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
						return trimArgument(argument, removeBrackets);
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
							return trimArgument(argument, removeBrackets);
						}
					}
					argument+= c;
				} else
				if (c == '}') {
					curlyBracketCount--;
					if (curlyBracketCount < 0) {
						brackets = "{}";
						return trimArgument(argument, removeBrackets);
					}
					argument+= c;
				} else
				if (squareBracketCount == 0 && curlyBracketCount == 0 && c == ',') {
					if (bracketCount == 0) return trimArgument(argument, removeBrackets);
					//
					if (argument.empty() == true && (c == ' ' || c == '\t')) {
						// no op
					} else {
						argument+= c;
					}
				} else {
					//
					if (argument.empty() == true && (c == ' ' || c == '\t')) {
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
			lc = lc == '\\' && c == '\\'?'\0':c;
		}
		//
		return trimArgument(argument, removeBrackets);
	};
	//
	auto viewIsLamdaFunctionWithoutArgumentsHead = [](const string_view& candidate, int& i) -> bool {
		//
		i = 0;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		//
		if (candidate[i] != '{') return false;
		//
		return true;
	};
	auto viewIsLamdaFunctionHead = [&](const string_view& candidate, int& i) -> bool {
	//
		if (viewIsLamdaFunctionWithoutArgumentsHead(candidate, i) == true) return true;
		//
		i = 0;
		//
		if (candidate.empty() == true) return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		// (
		if (candidate[i++] != '(') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		//
		auto argumentStartIdx = string::npos;
		auto argumentEndIdx = string::npos;
		//
		for (; i < candidate.size(); i++) {
			auto c = candidate[i];
			if (c == '&') {
				if (argumentStartIdx == string::npos) {
					argumentStartIdx = i;
				} else {
					return false;
				}
			} else
			if (c == '$') {
				if (argumentStartIdx == string::npos) {
					argumentStartIdx = i;
				} else
				if (argumentStartIdx == i - 1 && candidate[argumentStartIdx] == '&') {
					// no op
				} else {
					return false;
				}
			} else
			if (c == ',' || c == ')') {
				if (argumentEndIdx == string::npos) {
					if (argumentStartIdx != string::npos) {
						argumentEndIdx = i;
					}
					//
					argumentStartIdx = string::npos;
					argumentEndIdx = string::npos;
				} else {
					return false;
				}
				if (c == ')') {
					i++;
					break;
				}
			} else
			if (argumentStartIdx != string::npos && Character::isAlphaNumeric(candidate[i]) == false && c != '_') {
				return false;
			}
		}
		//
		if (i >= candidate.size()) return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		// -
		if (candidate[i++] != '-') return false;
		//
		if (i >= candidate.size()) return false;
		// >
		if (candidate[i++] != '>') return false;
		// spaces
		for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
		if (i >= candidate.size()) return false;
		//
		if (candidate[i] != '{') return false;
		//
		return true;
	};
	//
	auto viewIsAssignment = [&](const string_view& candidate) -> int {
		//
		auto squareBracketCount = 0;
		auto curlyBracketCount = 0;
		auto bracketCount = 0;
		auto quote = '\0';
		auto lc = '\0';
		for (auto i = 0; i < candidate.size(); i++) {
			auto c = candidate[i];
			auto nc = i + 1 < candidate.size()?candidate[i + 1]:'\0';
			if ((c == '"' || c == '\'') && lc != '\\') {
				if (quote == '\0') {
					quote = c;
				} else
				if (quote == c) {
					quote = '\0';
				}
			} else
			if (quote == '\0') {
				auto iIncrement = 0;
				if (c == '-' &&
					nc == '>' &&
					viewIsLamdaFunctionWithoutArgumentsHead(string_view(&candidate[i], candidate.size() - i), iIncrement) == true) {
					//
					i+= iIncrement - 1;
					continue;
				}
				if (c == '(') {
					// read ahead if inline/lambda function
					string_view lamdaFunctionCandidate(&candidate[i], candidate.size() - i);
					auto iIncrement = 0;
					if (viewIsLamdaFunctionHead(lamdaFunctionCandidate, iIncrement) == true) {
						i+= iIncrement - 1;
					} else {
						bracketCount++;
					}
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
				if (c == '[') {
					squareBracketCount++;
				} else
				if (c == ']') {
					squareBracketCount--;
				}
				//
				if (c == '=' &&
					lc != '=' &&
					nc != '=' &&
					bracketCount == 0 &&
					curlyBracketCount == 0 &&
					squareBracketCount == 0) {
					//
					return i;
				}
			}
			//
			lc = lc == '\\' && c == '\\'?'\0':c;
		}
		//
		return -1;
	};
	//
	auto getNextStatementOperator = [&](const string& processedStatement, StatementOperator& nextOperator, const Statement& statement) {
		auto curlyBracketCount = 0;
		auto bracketCount = 0;
		auto quote = '\0';
		auto lc = '\0';
		for (auto i = 0; i < processedStatement.size(); i++) {
			auto c = processedStatement[i];
			auto nc = i + 1 < processedStatement.size()?processedStatement[i + 1]:'\0';
			if ((c == '"' || c == '\'') && lc != '\\') {
				if (quote == '\0') {
					quote = c;
				} else
				if (quote == c) {
					quote = '\0';
				}
			} else
			if (quote == '\0') {
				auto iIncrement = 0;
				if (c == '-' &&
					nc == '>' &&
					viewIsLamdaFunctionWithoutArgumentsHead(string_view(&processedStatement[i], processedStatement.size() - i), iIncrement) == true) {
					//
					i+= iIncrement - 1;
					continue;
				}
				if (c == '(') {
					// read ahead if inline/lambda function
					string_view lamdaFunctionCandidate(&processedStatement[i], processedStatement.size() - i);
					auto iIncrement = 0;
					if (viewIsLamdaFunctionHead(lamdaFunctionCandidate, iIncrement) == true) {
						i+= iIncrement - 1;
					} else {
						bracketCount++;
					}
				} else
				if (c == ')') {
					bracketCount--;
				} else
				if (c == '{') {
					curlyBracketCount++;
				} else
				if (c == '}') {
					curlyBracketCount--;
				}
				if (curlyBracketCount == 0 &&
					isOperatorChar(processedStatement[i]) == true) {
					//
					for (int j = OPERATOR_NONE + 1; j < OPERATOR_MAX; j++) {
						//
						string operatorCandidate;
						operatorCandidate+= processedStatement[i];
						if (i + 1 < processedStatement.size() && isOperatorChar(processedStatement[i + 1]) == true) operatorCandidate+= processedStatement[i + 1];
						//
						auto priorizedOperator = static_cast<Operator>(j);
						auto operatorString = getOperatorAsString(priorizedOperator);
						if (priorizedOperator == OPERATOR_SUBSCRIPT) operatorString = StringTools::substring(operatorString, 0, 1);
						// valid?
						if (operatorCandidate.empty() == true ||
							(isOperator(operatorCandidate) == false && operatorCandidate != "[")) {
							continue;
						}
						//
						if (operatorString == operatorCandidate && (nextOperator.idx == OPERATORIDX_NONE || priorizedOperator > nextOperator.operator_)) {
							auto idx2 = -1;
							auto isMemberAccessOrAssignmentOperator = [](const string& candidate) { return candidate == "->"; };
							auto isSubscriptOperator = [](const string& candidate) { return candidate == "["; };
							if (operatorString.size() == 1 &&
								i > 0 &&
								isOperatorChar(processedStatement[i - 1]) == true &&
								(isMemberAccessOrAssignmentOperator(processedStatement[i - 1] + operatorString) == true ||
								isOperator(processedStatement[i - 1] + operatorString) == true)) {
								continue;
							}
							if (operatorString.size() == 1 &&
								i + 1 < processedStatement.size() &&
								isOperatorChar(processedStatement[i + 1]) == true &&
								(isMemberAccessOrAssignmentOperator(operatorString + processedStatement[i + 1]) == true ||
								isOperator(operatorString + processedStatement[i + 1]) == true)) {
								continue;
							}
							if (operatorString.size() == 2 &&
								i + 2 < processedStatement.size() &&
								isOperatorChar(processedStatement[i + 2]) == true) {
								continue;
							} else
							if (priorizedOperator == OPERATOR_SUBTRACTION) {
								string leftArgumentBrackets;
								auto leftArgumentLeft = 0;
								auto leftArgument = findLeftArgument(processedStatement, i - 1, leftArgumentLeft, leftArgumentBrackets);
								if (leftArgument.length() == 0) continue;
							} else
							if (priorizedOperator == OPERATOR_SUBSCRIPT) {
								// ignore on set/= operator
								auto assignmentIdx = viewIsAssignment(preprocessedStatement);
								if (assignmentIdx != -1 && i < assignmentIdx) continue;
								// find left argument
								string leftArgumentBrackets;
								int leftArgumentLength = 0;
								auto leftArgument = findLeftArgument(preprocessedStatement, i - 1, leftArgumentLength, leftArgumentBrackets);
								//
								if (leftArgument.length() == 0) continue;
								// find idx2
								auto _squareBracketCount = 0;
								auto _curlyBracketCount = 0;
								auto _bracketCount = 0;
								auto _quote = '\0';
								auto _lc = '\0';
								for (auto k = i; k < preprocessedStatement.size(); k++) {
									auto _c = preprocessedStatement[k];
									auto _nc = k + 1 < preprocessedStatement.size()?preprocessedStatement[k + 1]:'\0';
									if ((_c == '"' || _c == '\'') && _lc != '\\') {
										if (_quote == '\0') {
											_quote = _c;
										} else
										if (_quote == _c) {
											_quote = '\0';
										}
									} else
									if (_quote == '\0') {
										//
										auto kIncrement = 0;
										if (_c == '-' &&
											_nc == '>' &&
											viewIsLamdaFunctionWithoutArgumentsHead(string_view(&preprocessedStatement[k], preprocessedStatement.size() - k), kIncrement) == true) {
											//
											k+= kIncrement;
											continue;
										}
										if (_c == '(') {
											// read ahead if inline/lambda function
											string_view lamdaFunctionCandidate(&preprocessedStatement[k], preprocessedStatement.size() - k);
											auto kIncrement = 0;
											if (viewIsLamdaFunctionHead(lamdaFunctionCandidate, kIncrement) == true) {
												k+= kIncrement;
												continue;
											} else {
												_bracketCount++;
											}
										} else
										if (_c == ')') {
											_bracketCount--;
										} else
										if (_c == '{') {
											_curlyBracketCount++;
										} else
										if (_c == '}') {
											_curlyBracketCount--;
										} else
										if (_c == '[') {
											_squareBracketCount++;
										} else
										if (_c == ']') {
											_squareBracketCount--;
										}
										//
										if (_bracketCount == 0 &&
											_curlyBracketCount == 0 &&
											_squareBracketCount == 0) {
											//
											idx2 = k;
											// done here
											break;
										}
									}
									//
									_lc = _lc == '\\' && _c == '\\'?'\0':_c;
								}
								// disable sub script except for use with execute
								if (setVariableStatement == true) {
									auto viewIsMemberExecute = [](const string_view& candidate) -> bool {
										if (candidate.size() == 0) return false;
										//
										auto i = 0;
										// spaces
										for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
										if (i >= candidate.size()) return false;
										// -
										if (candidate[i++] != '-') return false;
										//
										if (i >= candidate.size()) return false;
										// >
										if (candidate[i++] != '>') return false;
										//
										return true;
									};
									//
									if (viewIsMemberExecute(string_view(&preprocessedStatement[idx2 + 1], preprocessedStatement.size() - (idx2 + 1))) == false) {
										continue;
									}
								}
							} else
							if (priorizedOperator == OPERATOR_MEMBERACCESS_PROPERTY) {
								if (setVariableStatement == true) {
									auto viewIsMemberProperty = [](const string_view& candidate) -> bool {
										if (candidate.size() == 0) return false;
										//
										auto i = 0;
										// spaces
										for (; i < candidate.size() && Character::isSpace(candidate[i]) == true; i++);
										if (i >= candidate.size()) return false;
										// -
										if (candidate[i++] != '.') return false;
										//
										if (i >= candidate.size()) return false;
										// >
										// ...
										//
										return true;
									};
									//
									if (viewIsMemberProperty(string_view(&preprocessedStatement[idx2 + 1], preprocessedStatement.size())) == false) {
										continue;
									}
								}
								// ignore on set/= operator
								auto assignmentIdx = viewIsAssignment(preprocessedStatement);
								if (assignmentIdx != -1 && i < assignmentIdx) {
									continue;
								}
								// find left argument
								string leftArgumentBrackets;
								int leftArgumentLength = 0;
								auto leftArgument = findLeftArgument(preprocessedStatement, i - 1, leftArgumentLength, leftArgumentBrackets);
								//
								// needs to be a variable or function/method call or a map/set initializer
								if (leftArgument.length() == 0 ||
									(leftArgument[0] != '$' &&
									leftArgument[leftArgument.size() - 1] != ')' &&
									leftArgument[0] != '{' &&
									leftArgument[leftArgument.size() - 1] != '}' &&
									leftArgument[0] != '[' &&
									leftArgument[leftArgument.size() - 1] != ']' &&
									memberAccessPropertyStatement == false)) {
									continue;
								}
								// no $$, $GLOBAL
								if (leftArgument == "$$" ||
									leftArgument == "$GLOBAL") {
									continue;
								}
							} else
							if (priorizedOperator == OPERATOR_MEMBERACCESS_EXECUTE) {
								// find left argument
								string leftArgumentBrackets;
								int leftArgumentLength = 0;
								auto leftArgument = findLeftArgument(preprocessedStatement, i - 1, leftArgumentLength, leftArgumentBrackets, false);
								// check for inline function/lambda
								//	which happens if no left argument or we have argument definition
								if (leftArgument.empty() == true ||
									(leftArgument[0] == '(' &&
									leftArgument[leftArgument.size() - 1] == ')')) {
									//
									continue;
								}
							}
							//
							nextOperator.idx = i;
							nextOperator.idx2 = idx2;
							nextOperator.operator_ = priorizedOperator;
						}
					}
				}
			}
			lc = lc == '\\' && c == '\\'?'\0':c;
		}
		//
		if (bracketCount > 0) {
			//
			return false;
		}
		//
		return nextOperator.idx != OPERATORIDX_NONE;
	};
	//
	auto encodeOperatorString = [](const string& operatorString) -> int64_t {
		int64_t result = 0ll;
		if (operatorString.size() >= 1) result+= static_cast<int64_t>(operatorString[0]);
		if (operatorString.size() >= 2) result+= static_cast<int64_t>(operatorString[1]) << 8;
		return result;
	};
	//
	StatementOperator nextOperator;
	while (getNextStatementOperator(preprocessedStatement, nextOperator, statement) == true) {
		//
		Method* method { nullptr };
		Method* prefixOperatorMethod { nullptr };
		Method* postfixOperatorMethod { nullptr };
		//
		{
			// resolve method
			method = getOperatorMethod(nextOperator.operator_);
			if (method == nullptr) {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": No operator method found");
				scriptValid = false;
				return preprocessedStatement;
			}
			// default for methods with 1 argument is post fix operator method
			postfixOperatorMethod = method;
			//
			// special case prefix or postfix operator methods, that have 1 argument only
			if (method->getOperator() == OPERATOR_POSTFIX_INCREMENT ||
				method->getOperator() == OPERATOR_PREFIX_INCREMENT) {
				prefixOperatorMethod = getOperatorMethod(OPERATOR_POSTFIX_INCREMENT);
				postfixOperatorMethod = getOperatorMethod(OPERATOR_PREFIX_INCREMENT);
			}
			//
			if (method->getOperator() == OPERATOR_POSTFIX_DECREMENT ||
				method->getOperator() == OPERATOR_PREFIX_DECREMENT) {
				prefixOperatorMethod = getOperatorMethod(OPERATOR_POSTFIX_DECREMENT);
				postfixOperatorMethod = getOperatorMethod(OPERATOR_PREFIX_DECREMENT);
			}
			//
			if (method->getOperator() == OPERATOR_POSTFIX_INCREMENT ||
				method->getOperator() == OPERATOR_PREFIX_INCREMENT ||
				method->getOperator() == OPERATOR_POSTFIX_DECREMENT ||
				method->getOperator() == OPERATOR_PREFIX_DECREMENT) {
				//
				if (prefixOperatorMethod == nullptr) {
					Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": No prefix operator method found");
					scriptValid = false;
					return preprocessedStatement;
				}
				//
				if (postfixOperatorMethod == nullptr) {
					Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": No postfix operator method found");
					scriptValid = false;
					return preprocessedStatement;
				}
			}
		}
		//
		if (nextOperator.operator_ == OPERATOR_SUBSCRIPT) {
			// find the single argument right
			auto operatorString = getOperatorAsString(nextOperator.operator_);
			// find left argument
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperator.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find index
			auto index = doStatementPreProcessing(StringTools::substring(preprocessedStatement, nextOperator.idx + 1, nextOperator.idx2), statement);
			//
			auto leftArgumentNewLines = 0;
			for (auto i = 0; i < leftArgument.size(); i++) {
				auto c = leftArgument[i];
				if (c == '\n') leftArgumentNewLines++; else break;
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperator.idx - leftArgumentLength) +
				StringTools::generate("\n", leftArgumentNewLines) +
				method->getMethodName() + "(" + StringTools::substring(leftArgument, leftArgumentNewLines) + ", " + index + ", " + to_string(encodeOperatorString(operatorString)) + ")" +
				StringTools::substring(preprocessedStatement, nextOperator.idx2 + 1, preprocessedStatement.size()
			);
		} else
		if (nextOperator.operator_ == OPERATOR_MEMBERACCESS_PROPERTY) {
			//
			auto operatorString = getOperatorAsString(nextOperator.operator_);
			// find left argument
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperator.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find right argument
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperator.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			//
			if (leftArgument.empty() == true || rightArgument.empty() == true) {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": Requires left and right argument");
				scriptValid = false;
				return preprocessedStatement;
			}
			//
			// resolve multiple properties
			vector<string> properties;
			string property;
			string outerLeftStatement;
			string outerRightStatement;
			for (auto i = 0; i < rightArgument.size(); i++) {
				auto c = rightArgument[i];
				if (c == '.') {
					properties.push_back(property);
					property.clear();
				} else {
					property+= c;
				}
			}
			if (property.empty() == false) {
				properties.push_back(property);
				property.clear();
			}
			for (int i = 1; i < properties.size() ; i++) {
				const auto& property = properties[i];
				outerLeftStatement+= method->getMethodName() + "(";
				outerRightStatement+= ", " + property + ", " + to_string(encodeOperatorString(operatorString)) + ")";
			}
			rightArgument = properties[0];
			//
			auto leftArgumentNewLines = 0;
			for (auto i = 0; i < leftArgument.size(); i++) {
				auto c = leftArgument[i];
				if (c == '\n') leftArgumentNewLines++; else break;
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperator.idx - leftArgumentLength) +
				StringTools::generate("\n", leftArgumentNewLines) +
				outerLeftStatement +
				method->getMethodName() + "(" + StringTools::substring(leftArgument, leftArgumentNewLines) + ", " + rightArgument + ", " + to_string(encodeOperatorString(operatorString)) + ")" +
				outerRightStatement +
				StringTools::substring(preprocessedStatement, nextOperator.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size()
			);
			//
		} else
		if (nextOperator.operator_ == OPERATOR_MEMBERACCESS_EXECUTE) {
			//
			auto operatorString = getOperatorAsString(nextOperator.operator_);
			// find left argument
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperator.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find right argument
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperator.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			// object member access
			string_view subMethodName;
			vector<ParserArgument> subArguments;
			//
			if (parseStatement(rightArgument, subMethodName, subArguments, statement) == false) {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": Could not parse statement: " + rightArgument);
				scriptValid = false;
				return preprocessedStatement;
			}
			//
			string arguments;
			// TODO: not required really, would require string operations on validation
			// arguments+= "\"" + string(subMethodName) + "\"";
			arguments+= string(subMethodName);
			arguments+= ", " + to_string(encodeOperatorString(operatorString));
			for (const auto& argument: subArguments) {
				arguments+= ", " + string(argument.argument);
			}
			//
			if (leftArgument.empty() == true || rightArgument.empty() == true) {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": Requires left and right argument");
				scriptValid = false;
				return preprocessedStatement;
			}
			//
			auto leftArgumentNewLines = 0;
			for (auto i = 0; i < leftArgument.size(); i++) {
				auto c = leftArgument[i];
				if (c == '\n') leftArgumentNewLines++; else break;
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperator.idx - leftArgumentLength) +
				StringTools::generate("\n", leftArgumentNewLines) +
				method->getMethodName() + "(" + StringTools::substring(leftArgument, leftArgumentNewLines) + ", " + arguments + ")" +
				StringTools::substring(preprocessedStatement, nextOperator.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size()
			);
			//
		} else
		if (method->isVariadic() == false &&
			method->getArgumentTypes().size() == 2) {
			// find the single argument right
			auto operatorString = getOperatorAsString(nextOperator.operator_);
			// find left argument
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperator.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find argument right
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperator.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			//
			if (leftArgument.empty() == false) {
				//
				auto leftArgumentNewLines = 0;
				for (auto i = 0; i < leftArgument.size(); i++) {
					auto c = leftArgument[i];
					if (c == '\n') leftArgumentNewLines++; else break;
				}
				// substitute with method call
				preprocessedStatement =
					StringTools::substring(preprocessedStatement, 0, nextOperator.idx - leftArgumentLength) +
					StringTools::generate("\n", leftArgumentNewLines) +
					prefixOperatorMethod->getMethodName() + "(" + StringTools::substring(leftArgument, leftArgumentNewLines) + ", " + to_string(encodeOperatorString(operatorString)) + ")" +
					StringTools::substring(preprocessedStatement, nextOperator.idx + operatorString.size(), preprocessedStatement.size()
				);
			} else
			if (rightArgument.empty() == false) {
				// substitute with method call
				preprocessedStatement =
					StringTools::substring(preprocessedStatement, 0, nextOperator.idx) +
					postfixOperatorMethod->getMethodName() + "(" + rightArgument + ", " + to_string(encodeOperatorString(operatorString)) + ")" +
					StringTools::substring(preprocessedStatement, nextOperator.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size());
			} else {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": Requires left or right argument");
				scriptValid = false;
				return preprocessedStatement;
			}
		} else
		if (method->isVariadic() == true ||
			method->getArgumentTypes().size() == 3) {
			//
			auto operatorString = getOperatorAsString(nextOperator.operator_);
			// find left argument
			string leftArgumentBrackets;
			int leftArgumentLength = 0;
			auto leftArgument = findLeftArgument(preprocessedStatement, nextOperator.idx - 1, leftArgumentLength, leftArgumentBrackets);
			// find right argument
			string rightArgumentBrackets;
			int rightArgumentLength = 0;
			auto rightArgument = findRightArgument(preprocessedStatement, nextOperator.idx + operatorString.size(), rightArgumentLength, rightArgumentBrackets);
			//
			if (leftArgument.empty() == true || rightArgument.empty() == true) {
				Console::printLine(getStatementInformation(statement, getStatementSubLineIdx(preprocessedStatement, nextOperator.idx)) + ": " + method->getMethodName() + ": Requires left and right argument");
				scriptValid = false;
				return preprocessedStatement;
			}
			//
			if (nextOperator.operator_ == OPERATOR_SET) {
				leftArgument = "\"" + StringTools::replace(doStatementPreProcessing(leftArgument, statement, true), "\"", "\\\"") + "\"";
			}
			//
			auto leftArgumentNewLines = 0;
			for (auto i = 0; i < leftArgument.size(); i++) {
				auto c = leftArgument[i];
				if (c == '\n') leftArgumentNewLines++; else break;
			}
			// substitute with method call
			preprocessedStatement =
				StringTools::substring(preprocessedStatement, 0, nextOperator.idx - leftArgumentLength) +
				StringTools::generate("\n", leftArgumentNewLines) +
				method->getMethodName() + "(" + StringTools::substring(leftArgument, leftArgumentNewLines) + ", " + rightArgument + ", " + to_string(encodeOperatorString(operatorString)) + ")" +
				StringTools::substring(preprocessedStatement, nextOperator.idx + operatorString.size() + rightArgumentLength, preprocessedStatement.size()
			);
			//
		}
		//
		nextOperator = StatementOperator();
	}
	//
	return preprocessedStatement;
}

void MinitScript::dumpScriptState(ScriptState& scriptState, const string& message) {
	Console::printLine("MinitScript::dumpScriptState(): " + (message.empty() == false?message + ": ":"") + to_string(rootScript->scriptStateStack.size()) + " on stack");
	Console::printLine(string("\t") + "idx: " + to_string(scriptState.idx));
	Console::printLine(string("\t") + "state: " + to_string(scriptState.state));
	Console::printLine(string("\t") + "lastState: " + to_string(scriptState.lastState));
	Console::printLine(string("\t") + "running: " + (scriptState.running == true?"true":"false"));
	Console::printLine(string("\t") + "scriptIdx: " + to_string(scriptState.scriptIdx));
	Console::printLine(string("\t") + "statementIdx: " + to_string(scriptState.statementIdx));
	Console::printLine(string("\t") + "gotoStatementIdx: " + to_string(scriptState.gotoStatementIdx));
	Console::printLine(string("\t") + "variable count: " + to_string(scriptState.variables.size()));
	Console::printLine(string("\t") + "block stack count: " + to_string(scriptState.blockStack.size()));
	array<string, 9> blockStackTypes {
		"TYPE_NONE",
		"TYPE_GLOBAL",
		"TYPE_STACKLET",
		"TYPE_FUNCTION",
		"TYPE_FOR",
		"TYPE_FORTIME",
		"TYPE_IF",
		"TYPE_SWITCH",
		"TYPE_CASE"
	};
	for (const auto& block: scriptState.blockStack) {
		Console::printLine(string("\t\t") + blockStackTypes[block.type]);
	}
	Console::printLine(string("\t") + "returnValue: " + scriptState.returnValue.getValueAsString());
}

bool MinitScript::call(int scriptIdx, span<Variable>& arguments, Variable& returnValue, bool pushScriptState) {
	//
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::printLine("MinitScript::call(): Invalid script index: " + to_string(scriptIdx));
		return false;
	}
	auto& script = scripts[scriptIdx];
	//
	if (script.type != Script::TYPE_FUNCTION &&
		script.type != Script::TYPE_STACKLET) {
		Console::printLine("MinitScript::call(): " + (script.name.empty() == false?script.name:script.condition) + ": Script is not a function/callable/stacklet.");
		return false;
	}
	// copy script state
	ScriptState currentScriptState = getScriptState();
	//
	if (pushScriptState == true) {
		if (script.type == Script::TYPE_STACKLET) {
			Console::printLine("MinitScript::call(): " + script.condition + ": Stacklets can not be called with a stack.");
			return false;
		}
		this->pushScriptState();
		// script state vector could get modified, so
		auto& scriptState = getScriptState();
		// also put named arguments into state context variables
		auto argumentIdx = 0;
		for (const auto& argument: script.arguments) {
			if (argumentIdx == arguments.size()) {
				break;
			}
			// private scope
			if (argument.privateScope == true) {
				arguments[argumentIdx].setPrivateScope();
			} else {
				arguments[argumentIdx].unsetPrivateScope();
			}
			//
			setVariable(argument.name, arguments[argumentIdx], nullptr, argument.reference);
			argumentIdx++;
		}
		//
		resetScriptExecutationState(script.rootScriptIdx, STATEMACHINESTATE_NEXT_STATEMENT);
	} else {
		//
		if (script.type != Script::TYPE_STACKLET) {
			Console::printLine("MinitScript::call(): " + script.condition + ": Function/Callable can not be called with no stack.");
			return false;
		}
		//
		resetStackletScriptExecutationState(script.rootScriptIdx, STATEMACHINESTATE_NEXT_STATEMENT);
	}
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
		returnValue.setValue(scriptState.returnValue);
	}
	// done, pop the function script state
	if (pushScriptState == true) {
		popScriptState();
	} else {
		auto& scriptState = getScriptState();
		scriptState.state = currentScriptState.state;
		scriptState.lastState = currentScriptState.lastState;
		scriptState.lastStateMachineState = currentScriptState.lastStateMachineState;
		scriptState.running = currentScriptState.running;
		scriptState.scriptIdx = currentScriptState.scriptIdx;
		scriptState.statementIdx = currentScriptState.statementIdx;
		scriptState.gotoStatementIdx = currentScriptState.gotoStatementIdx;
		scriptState.returnValue = currentScriptState.returnValue;
	}
	// try garbage collection
	tryGarbageCollection();
	// handle unhandled exception
	if (hasException() == true) {
		// global scope?
		if (getScriptStateStackSize() > 1) {
			// function scope: rethrow
			if (_throw(rootScript->exceptionThrowArgument) == true) {
				unsetException();
			} else {
				// goto "end" of current script
				const auto& scriptState = getScriptState();
				const auto& script = rootScript->scripts[scriptState.scriptIdx];
				const auto& statements = script.getStatements();
				gotoStatement(statements[statements.size() - 1]);
			}
		} else {
			//
			if (hasException() == true) {
				//
				auto minitScript = this;
				const auto& subStatement = exceptionSubStatement;
				MINITSCRIPT_METHODUSAGE_COMPLAINM("throw", "Unhandled exception!");
				//
				unsetException();
			}
		}
	}
	// if function calls are worked off, we can do the deferred emit
	#if defined(MINITSCRIPT_EVENTS)
		// events
		if (isFunctionRunning() == false && deferredEmit.empty() == false) {
			auto condition = deferredEmit;
			deferredEmit.clear();
			emit(condition);
		}
	#endif
	//
	return true;
}

const vector<MinitScript::Method*> MinitScript::getMethods() {
	vector<Method*> methods;
	for (const auto& [methodName, method]: rootScript->methods) {
		if (method->isPrivate() == true) continue;
		methods.push_back(method);
	}
	//
	struct {
		bool operator()(Method* a, Method* b) const {
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

const vector<MinitScript::Method*> MinitScript::getOperatorMethods() {
	vector<Method*> methods;
	for (const auto& [operatorId, method]: operators) {
		methods.push_back(method);
	}
	return methods;
}

const string MinitScript::getScriptInformation(int scriptIdx, bool includeStatements) {
	if (scriptIdx < 0 || scriptIdx >= scripts.size()) {
		Console::printLine("MinitScript::getScriptInformation(): invalid script index: " + to_string(scriptIdx));
		return string();
	}
	const auto& script = scripts[scriptIdx];
	string result;
	string argumentsString;
	switch(script.type) {
		case Script::TYPE_FUNCTION:
		case Script::TYPE_STACKLET: {
			for (const auto& argument: script.arguments) {
				if (argumentsString.empty() == false) argumentsString+= ", ";
				if (argument.reference == true) argumentsString+= "&";
				if (argument.privateScope == true) argumentsString+= "&";
				argumentsString+= argument.name;
			}
			argumentsString = "(" + argumentsString + ")";
			if (script.type == Script::TYPE_FUNCTION) result+= "function: "; else result+= "stacklet: ";
			break;
		}
		//
		#if defined(MINITSCRIPT_EVENTS)
			// events
			case Script::TYPE_ON: result+= "on: "; break;
			case Script::TYPE_ONENABLED: result+= "on-enabled: "; break;
		#endif
		//
		default: break;
	}
	if (script.condition.empty() == false)
		result+= script.condition + argumentsString + (script._module.empty() == true?string():string(" [module: " + script._module + "]")) + "; ";
	if (script.name.empty() == false) {
		result+= "name = '" + script.name + argumentsString + "';\n";
	} else {
		result+= "\n";
	}
	if (includeStatements == true) {
		auto indent = 1;
		auto formatStatement = [&](const string& statement) {
			string result;
			auto statementMethodEndIdx = StringTools::indexOf(statement, "(");
			if (statementMethodEndIdx == string::npos) statementMethodEndIdx = statement.size();
			auto statementMethod = StringTools::trim(StringTools::substring(statement, 0, statementMethodEndIdx));
			if (statementMethod == "elseif") indent-= 1; else
			if (statementMethod == "else") indent-= 1; else
			if (statementMethod == "case") indent-= 1; else
			if (statementMethod == "default") indent-= 1; else
			if (statementMethod == "catch") indent-= 1; else
			if (statementMethod == "end") indent-= 1;
			for (auto i = 0; i < indent; i++) result+= "  ";
			result+= statement;
			if (statementMethod == "if") indent+= 1; else
			if (statementMethod == "elseif") indent+= 1; else
			if (statementMethod == "else") indent+= 1; else
			if (statementMethod == "forTime") indent+= 1; else
			if (statementMethod == "forCondition") indent+= 1; else
			if (statementMethod == "switch") indent+= 1; else
			if (statementMethod == "case") indent+= 1; else
			if (statementMethod == "default") indent+= 1; else
			if (statementMethod == "try") indent+= 1; else
			if (statementMethod == "catch") indent+= 1;
			return result;
		};
		result+=
			string() +
			"\t" + "        " + ": start" + "\n";
		for (const auto& statement: script.getStatements()) {
			string newLineIndent; for (auto i = 0; i < indent + 2; i++) newLineIndent+= "  ";
			result+=
				string() +
				"\t" +
				"[" +
				StringTools::padLeft(to_string(statement.line), "0", 4) +
				"|" +
				StringTools::padLeft(to_string(statement.statementIdx), "0", 4) +
				"] " +
				StringTools::replace(formatStatement(statement.executableStatement), "\n", "\n\t    :" + newLineIndent)
				+
				(statement.gotoStatementIdx != STATEMENTIDX_NONE?" [gotoStatement " + to_string(statement.gotoStatementIdx) + "]":"")
				+ "\n";
		}
		result+= "\n";
	}
	//
	return result;
}

const string MinitScript::getInformation() {
	string result;
	result+= "Script: " + scriptPathName + "/" + scriptFileName + " (runs " + (native == true?"natively":"interpreted") + ")" + "\n\n";
	result+= "\n";

	//
	result+="State Machine States:\n";
	{
		vector<string> states;
		for (const auto& [stateMachineStateId, stateMachineState]: stateMachineStates) {
			string state;
			state = stateMachineState->getName() + "(" + to_string(stateMachineState->getId()) + ")";
			states.push_back(state);
		}
		sort(states.begin(), states.end());
		for (const auto& state: states) result+= state+ "\n";
	}
	result+= "\n";

	//
	result+= "Methods:\n";
	{
		vector<string> methods;
		for (const auto& [methodName, method]: rootScript->methods) {
			if (method->isPrivate() == true) continue;
			string methodDescription;
			methodDescription+= method->getMethodName();
			methodDescription+= "(";
			methodDescription+= method->getArgumentsInformation();
			methodDescription+= "): ";
			methodDescription+= Variable::getReturnTypeAsString(method->getReturnValueType(), method->isReturnValueNullable());
			methods.push_back(methodDescription);
		}
		sort(methods.begin(), methods.end());
		for (const auto& method: methods) result+= method + "\n";
	}
	result+= "\n";

	//
	result+= "Operators:\n";
	{
		vector<string> operators;
		for (const auto& [operatorId, method]: rootScript->operators) {
			string operatorString;
			operatorString+= getOperatorAsString(method->getOperator());
			operatorString+= " --> ";
			operatorString+= method->getMethodName();
			operatorString+= "(";
			operatorString+= method->getArgumentsInformation();
			operatorString+= "): ";
			operatorString+= Variable::getReturnTypeAsString(method->getReturnValueType(), method->isReturnValueNullable());
			operators.push_back(operatorString);
		}
		sort(operators.begin(), operators.end());
		for (const auto& method: operators) result+= method + "\n";
	}
	result+= "\n";

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
	result+= "\n";

	//
	if (modules.empty() == false) {
		result+= "Modules:\n";
		{
			vector<string> modules = this->modules;
			sort(modules.begin(), modules.end());
			for (const auto& _module: modules) result+= _module + "\n";
		}
		result+= "\n";
	}

	//
	result+= string(_module == false?"Script":"Module") + ":\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			result+= getScriptInformation(scriptIdx);
			scriptIdx++;
		}
	}

	//
	return result;
}

void MinitScript::registerStateMachineStates() {
	// base
	if (native == false) {
		//
		class ScriptStateNextStatement: public StateMachineState {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptStateNextStatement(MinitScript* minitScript): StateMachineState(), minitScript(minitScript) {}
			virtual const string getName() override {
				return "STATEMACHINESTATE_NEXT_STATEMENT";
			}
			virtual int getId() override {
				return STATEMACHINESTATE_NEXT_STATEMENT;
			}
			virtual void execute() override {
				if (minitScript->getScriptState().statementIdx == STATEMENTIDX_NONE) {
					//
					#if defined(MINITSCRIPT_EVENTS)
						// events
						minitScript->enabledNamedConditions.clear();
						minitScript->timeEnabledConditionsCheckLast = TIME_NONE;
						minitScript->setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);
					#endif
					//
					return;
				}
				if (minitScript->native == false) minitScript->executeNextStatement();
			}
		};
		registerStateMachineState(new ScriptStateNextStatement(this));
	}
	{
		//
		class ScriptStateWait: public StateMachineState {
		private:
			MinitScript* minitScript { nullptr };
		public:
			ScriptStateWait(MinitScript* minitScript): StateMachineState(), minitScript(minitScript) {}
			virtual const string getName() override {
				return "STATEMACHINESTATE_WAIT";
			}
			virtual int getId() override {
				return STATEMACHINESTATE_WAIT;
			}
			virtual void execute() override {
				auto now = Time::getCurrentMillis();
				if (now > minitScript->getScriptState().timeWaitStarted + minitScript->getScriptState().timeWaitTime) {
					minitScript->setScriptStateState(STATEMACHINESTATE_NEXT_STATEMENT);
				} else {
					#if !defined(MINITSCRIPT_NO_SLEEP)
						Thread::sleep(10);
					#endif
				}
			}
		};
		registerStateMachineState(new ScriptStateWait(this));
	}
	#if defined(MINITSCRIPT_EVENTS)
		{
			//
			class ScriptStateWaitForCondition: public StateMachineState {
			private:
				MinitScript* minitScript { nullptr };
			public:
				ScriptStateWaitForCondition(MinitScript* minitScript): StateMachineState(), minitScript(minitScript) {}
				virtual const string getName() override {
					return "STATEMACHINESTATE_WAIT_FOR_CONDITION";
				}
				virtual int getId() override {
					return STATEMACHINESTATE_WAIT_FOR_CONDITION;
				}
				virtual void execute() override {
					auto now = Time::getCurrentMillis();
					if (now < minitScript->getScriptState().timeWaitStarted + minitScript->getScriptState().timeWaitTime) {
						return;
					}
					// events
					auto scriptIdxToStart = minitScript->determineScriptIdxToStart();
					if (scriptIdxToStart == SCRIPTIDX_NONE) {
						minitScript->getScriptState().timeWaitStarted = now;
						minitScript->getScriptState().timeWaitTime = 100LL;
						return;
					}
					minitScript->resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);
				}
			};
			registerStateMachineState(new ScriptStateWaitForCondition(this));
		}
	#endif
}

void MinitScript::registerMethods() {
	// unregister old registered methods
	for (const auto& [scriptMethodId, scriptMethod]: methods) delete scriptMethod;
	methods.clear();

	// register math methods
	minitScriptMath = make_unique<MathMethods>(this);
	minitScriptMath->registerMethods();

	// base script methods
	// 	register base methods
	BaseMethods::registerMethods(this);

	// 	register string methods
	StringMethods::registerMethods(this);

	// 	register byte array methods
	ByteArrayMethods::registerMethods(this);

	// 	register array methods
	ArrayMethods::registerMethods(this);

	// 	register map methods
	MapMethods::registerMethods(this);

	// 	register set methods
	SetMethods::registerMethods(this);

	// 	register script methods
	ScriptMethods::registerMethods(this);

	// additional script methods
	// register application methods
	ApplicationMethods::registerMethods(this);

	// register console methods
	ConsoleMethods::registerMethods(this);

	// register context methods
	ContextMethods::registerMethods(this);

	// register cryptography methods
	CryptographyMethods::registerMethods(this);

	// register file system methods
	FileSystemMethods::registerMethods(this);

	// register JSON methods
	JSONMethods::registerMethods(this);

	// register network methods
	NetworkMethods::registerMethods(this);

	// register time methods
	TimeMethods::registerMethods(this);

	// register XML methods
	XMLMethods::registerMethods(this);

	//
	for (const auto dataType: MinitScript::dataTypes) {
		if (dataType->isMathDataType() == true) minitScriptMath->registerDataType(dataType);
		dataType->registerMethods(this);
	}

	// determine operators
	for (const auto& [scriptMethodName, scriptMethod]: rootScript->methods) {
		auto methodOperator = scriptMethod->getOperator();
		if (methodOperator != OPERATOR_NONE) {
			auto methodOperatorString = getOperatorAsString(methodOperator);
			auto scriptOperatorIt = operators.find(static_cast<uint8_t>(methodOperator));
			if (scriptOperatorIt != operators.end()) {
				Console::printLine("MinitScript::registerMethods(): Operator '" + methodOperatorString + "' already registered for method " + scriptMethod->getMethodName() + "");
				continue;
			}
			operators[static_cast<uint8_t>(methodOperator)] = scriptMethod;
		}
	}
}

void MinitScript::registerVariables() {
	//
	unregisterVariables();
	while (getScriptStateStackSize() > 1) popScriptState();
	if (hasScriptState() == false) pushScriptState();

	//
	minitScriptMath->registerConstants();

	// base script constants
	// 	register base constants
	BaseMethods::registerConstants(this);

	// 	register string constants
	StringMethods::registerConstants(this);

	// 	register byte array constants
	ByteArrayMethods::registerConstants(this);

	// 	register array constants
	ArrayMethods::registerConstants(this);

	// 	register map constants
	MapMethods::registerConstants(this);

	// 	register set constants
	SetMethods::registerConstants(this);

	// 	register script constants
	ScriptMethods::registerConstants(this);

	// additional script constants
	// register application constants
	ApplicationMethods::registerConstants(this);

	// register console constants
	ConsoleMethods::registerConstants(this);

	// register context constants
	ContextMethods::registerConstants(this);

	// register cryptography constants
	CryptographyMethods::registerConstants(this);

	// register file system constants
	FileSystemMethods::registerConstants(this);

	// register JSON constants
	JSONMethods::registerConstants(this);

	// register network constants
	NetworkMethods::registerConstants(this);

	// register time constants
	TimeMethods::registerConstants(this);

	// register XML constants
	XMLMethods::registerConstants(this);

	//
	for (const auto dataType: MinitScript::dataTypes) dataType->registerConstants(this);
}

void MinitScript::unregisterVariables() {
	// no op for ast interpretation
}

void MinitScript::createLamdaFunction(Variable& variable, const vector<string_view>& arguments, const string_view& functionScriptCode, int lineIdx, bool populateThis, const Statement& statement, const string& nameHint) {
	// function declaration
	auto functionName = string() + "lamda_function_" + (nameHint.empty() == true?"":StringTools::toLowerCase(nameHint) + "_") + to_string(inlineFunctionIdx++);
	auto inlineFunctionScriptCode = "function: " + functionName + "(";
	if (populateThis == true) inlineFunctionScriptCode+= "&&$this";
	auto argumentIdx = 0;
	for (const auto& argument: arguments) {
		if (argumentIdx > 0 || populateThis == true) inlineFunctionScriptCode+= ",";
		inlineFunctionScriptCode+= argument;
		argumentIdx++;
	}
	inlineFunctionScriptCode+= string() + ")" + "\n";
	// function definition
	inlineFunctionScriptCode+= string(functionScriptCode);
	inlineFunctionScriptCode+= "\n";
	inlineFunctionScriptCode+= string() + "end" + "\n";
	// store it to be parsed later
	//	we can reduce line index by function head
	//	our line counting does not start at 1 here, but at zero
	deferredInlineScriptCodes.push_back(make_pair(lineIdx - 2, inlineFunctionScriptCode));
	//
	variable.setFunctionAssignment(functionName);
}

void MinitScript::createStacklet(Variable& variable, const string& scopeName, const vector<string_view>& arguments, const string_view& stackletScriptCode, int lineIdx, const Statement& statement) {
	// stacklet declaration
	auto stackletName = string() + "stacklet_" + to_string(inlineStackletIdx++);
	auto inlineStackletScriptCode = "stacklet: " + stackletName + "(" + scopeName + ")" + "\n";
	// stacklet definition
	inlineStackletScriptCode+= string(stackletScriptCode);
	inlineStackletScriptCode+= "\n";
	inlineStackletScriptCode+= string() + "end" + "\n";
	// store it to be parsed later
	//	we can reduce line index by function head
	//	our line counting does not start at 1 here, but at zero
	deferredInlineScriptCodes.push_back(make_pair(lineIdx - 2, inlineStackletScriptCode));
	//
	variable.setStackletAssignment(stackletName);
}

const MinitScript::Variable MinitScript::initializeArray(const string& scriptFileName, const string_view& initializerString, MinitScript* minitScript, int scriptIdx, const Statement& statement) {
	Variable variable;
	variable.setType(TYPE_ARRAY);
	//
	auto lineIdx = statement.line;
	auto bracketCount = 0;
	auto squareBracketCount = 0;
	auto curlyBracketCount = 0;
	auto quote = '\0';
	auto arrayValueStart = string::npos;
	auto arrayValueEnd = string::npos;
	auto inlineFunctionSignatureStartCandidate = string::npos;
	auto inlineFunctionLineIdxCandidate = LINE_NONE;
	auto inlineFunctionLineIdx = LINE_NONE;
	//
	auto lc = '\0';
	auto i = 0;
	//
	auto pushToArray = [&]() -> void {
		// array value
		if (arrayValueStart != string::npos) {
			arrayValueEnd = i - 1;
			auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
			if (arrayValueLength > 0) {
				auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
				if (arrayValueStringView.empty() == false) {
					Variable arrayValue;
					arrayValue.setImplicitTypedValueFromStringView(scriptFileName, arrayValueStringView, minitScript, scriptIdx, statement);
					variable.pushArrayEntry(arrayValue);
				}
			}
		}
		//
		arrayValueStart = string::npos;
		arrayValueEnd = string::npos;
		//
		inlineFunctionSignatureStartCandidate = string::npos;
		inlineFunctionLineIdxCandidate = LINE_NONE;
		inlineFunctionLineIdx = LINE_NONE;
	};
	//
	for (; i < initializerString.size(); i++) {
		auto c = initializerString[i];
		// newline/line index
		if (c == '\n') {
			lineIdx++;
			// check for comment line
			auto comment = false;
			for (auto j = i + 1; j < initializerString.size(); j++) {
				auto _c = initializerString[j];
				// space after newline
				if (Character::isSpace(_c) == true) {
					// no op
				} else
				// comment start
				if (_c == '#') {
					comment = true;
					// iterate until next new line
					for (j++; j < initializerString.size(); j++) {
						if (initializerString[j] == '\n') break;
					}
					//
					i = j - 1;
					break;
				} else {
					// non hash as first character after new line
					break;
				}
			}
			//
			if (comment == true) continue;
		}
		// quotes
		if (squareBracketCount == 1 && curlyBracketCount == 0 && (c == '"' || c == '\'') && lc != '\\') {
			if (quote == '\0') {
				quote = c;
				if (arrayValueStart == string::npos) arrayValueStart = i;
			} else
			if (quote == c) {
				quote = '\0';
				if (arrayValueEnd == string::npos) arrayValueEnd = i;
			}
		} else
		// no quote
		if (quote == '\0') {
			// , -> push to array
			if (squareBracketCount == 1 && curlyBracketCount == 0 && bracketCount == 0 && c == ',') {
				pushToArray();
			} else
			// possible function call
			if (c == '(') {
				//
				bracketCount++;
				//
				if (bracketCount == 1) {
					inlineFunctionSignatureStartCandidate = i;
					inlineFunctionLineIdxCandidate = lineIdx;
				}
			} else
			if (c == ')') {
				bracketCount--;
				// function assignment
				if (inlineFunctionSignatureStartCandidate != string::npos && bracketCount == 0 && arrayValueStart == string::npos) {
					arrayValueStart = inlineFunctionSignatureStartCandidate;
					inlineFunctionLineIdx = inlineFunctionLineIdxCandidate;
				}
				//
				inlineFunctionSignatureStartCandidate = string::npos;
				inlineFunctionLineIdxCandidate = LINE_NONE;
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
					inlineFunctionSignatureStartCandidate = string::npos;
					inlineFunctionLineIdxCandidate = LINE_NONE;
					//
					if (arrayValueStart != string::npos) {
						arrayValueEnd = i;
						auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
						if (arrayValueLength > 0) {
							auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
							if (arrayValueStringView.empty() == false) {
								auto arrayValue = initializeArray(scriptFileName, arrayValueStringView, minitScript, scriptIdx, statement);
								variable.pushArrayEntry(arrayValue);
							}
						}
						//
						arrayValueStart = string::npos;
						arrayValueEnd = string::npos;
					}
					//
					inlineFunctionLineIdx = LINE_NONE;
				}
			} else
			// map/set initializer
			if (c == '{' && squareBracketCount == 1 && bracketCount == 0) {
				// we have a inner map/set initializer, mark it
				if (curlyBracketCount == 0) {
					if (arrayValueStart == string::npos) arrayValueStart = i;
				}
				// increase curly bracket count
				curlyBracketCount++;
			} else
			// end of map/set initializer or inline lamda function
			if (c == '}' && squareBracketCount == 1 && bracketCount == 0) {
				curlyBracketCount--;
				// otherwise push inner array initializer
				if (curlyBracketCount == 0) {
					// parse and push
					inlineFunctionSignatureStartCandidate = string::npos;
					inlineFunctionLineIdxCandidate = LINE_NONE;
					//
					if (arrayValueStart != string::npos) {
						arrayValueEnd = i;
						auto arrayValueLength = arrayValueEnd - arrayValueStart + 1;
						if (arrayValueLength > 0) {
							auto arrayValueStringView = StringTools::viewTrim(string_view(&initializerString[arrayValueStart], arrayValueLength));
							if (arrayValueStringView.empty() == false) {
								vector<string_view> lamdaFunctionArguments;
								string_view lamdaFunctionScriptCode;
								int lamdaFunctionLineIdx = inlineFunctionLineIdx;
								if (viewIsLamdaFunction(arrayValueStringView, lamdaFunctionArguments, lamdaFunctionScriptCode, lamdaFunctionLineIdx) == true) {
									Variable arrayValue;
									minitScript->createLamdaFunction(arrayValue, lamdaFunctionArguments, lamdaFunctionScriptCode, lamdaFunctionLineIdx, false, statement);
									variable.pushArrayEntry(arrayValue);
								} else {
									auto arrayValue = initializeMapSet(scriptFileName, arrayValueStringView, minitScript, scriptIdx, statement);
									variable.pushArrayEntry(arrayValue);
								}
							}
						}
						//
						arrayValueStart = string::npos;
						arrayValueEnd = string::npos;
					}
					//
					inlineFunctionLineIdx = LINE_NONE;
				}
			} else
			// set up argument start
			if (squareBracketCount == 1 && curlyBracketCount == 0 && bracketCount == 0 && arrayValueStart == string::npos && c != ' ' && c != '\t' && c != '\n') {
				arrayValueStart = i;
			}
		}
		//
		lc = lc == '\\' && c == '\\'?'\0':c;
	}
	//
	auto initalizer = make_unique<MinitScript::Variable::Initializer>(string(initializerString), statement, nullptr);
	variable.initializerReferenceUnion.initializer->copy(initalizer.get());
	//
	return variable;
}

const MinitScript::Variable MinitScript::initializeMapSet(const string& scriptFileName, const string_view& initializerString, MinitScript* minitScript, int scriptIdx, const Statement& statement) {
	//
	Variable variable;
	variable.setType(TYPE_MAP);
	//
	auto subLineIdx = 0;
	auto bracketCount = 0;
	auto curlyBracketCount = 0;
	auto squareBracketCount = 0;
	auto quote = '\0';
	auto mapKeyStart = string::npos;
	auto mapKeyEnd = string::npos;
	auto mapValueStart = string::npos;
	auto mapValueEnd = string::npos;
	enum ParseMode { PARSEMODE_KEY, PARSEMODE_VALUE };
	auto parseMode = PARSEMODE_KEY;
	auto inlineFunctionSignatureStartCandidate = string::npos;
	auto inlineFunctionLineIdxCandidate = LINE_NONE;
	auto inlineFunctionLineIdx = LINE_NONE;
	auto mapKeyLineIdx = LINE_NONE;
	auto hasValues = false;
	//
	auto i = 0;

	//
	auto insertMapKeyValuePair = [&]() -> void {
		//
		string_view mapKey;
		auto dequotedMapKey = false;
		// map key
		if (mapKeyStart != string::npos && mapKeyEnd != string::npos) {
			//
			auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
			if (mapKeyLength > 0) {
				mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
				if (viewIsStringLiteral(mapKey) == true) {
					mapKey = dequote(mapKey);
					dequotedMapKey = true;
				}
				if (mapKey.empty() == true) mapKey = string_view();
			}
		}
		//
		mapKeyStart = string::npos;
		mapKeyEnd = string::npos;
		// validate map key
		if (mapKey.empty() == true) {
			// no op
		} else
		if (viewIsKey(mapKey) == false) {
			Console::printLine(minitScript->getStatementInformation(statement, mapKeyLineIdx) + ": Invalid key name, ignoring map entry: " + string(mapKey));
		} else {
			auto _private = dequotedMapKey == true?false:viewIsKeyPrivate(mapKey);
			if (_private == true) mapKey = viewGetPrivateKey(mapKey);
			// map value
			if (mapValueStart != string::npos && mapValueEnd != string::npos) {
				auto mapValueLength = mapValueEnd - mapValueStart + 1;
				//
				if (mapValueLength > 0) {
					auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
					if (mapValueStringView.empty() == false) {
						//
						Variable mapValue;
						mapValue.setImplicitTypedValueFromStringView(scriptFileName, mapValueStringView, minitScript, scriptIdx, statement);
						//
						variable.setMapEntry(string(mapKey), mapValue, _private);
						//
						hasValues = true;
					}
				}
			} else {
				//
				variable.setMapEntry(string(mapKey), Variable(), _private);
			}
		}
		//
		mapKeyLineIdx = LINE_NONE;
		//
		mapValueStart = string::npos;
		mapValueEnd = string::npos;
		//
		inlineFunctionSignatureStartCandidate = string::npos;
		inlineFunctionLineIdxCandidate = LINE_NONE;
		inlineFunctionLineIdx = LINE_NONE;
		//
		parseMode = PARSEMODE_KEY;
	};
	//
	auto lc = '\0';
	for (; i < initializerString.size(); i++) {
		//
		auto c = initializerString[i];
		auto nc = i < initializerString.size() - 1?initializerString[i + 1]:'\0';
		// newline/line index
		if (c == '\n') {
			//
			subLineIdx++;
			// check for comment line
			auto comment = false;
			for (auto j = i + 1; j < initializerString.size(); j++) {
				auto _c = initializerString[j];
				// space after newline
				if (Character::isSpace(_c) == true) {
					// no op
				} else
				// comment start
				if (_c == '#') {
					comment = true;
					// iterate until next new line
					for (j++; j < initializerString.size(); j++) {
						if (initializerString[j] == '\n') break;
					}
					//
					i = j - 1;
					break;
				} else {
					// non hash as first character after new line
					break;
				}
			}
			//
			if (comment == true) continue;
		}
		// quotes
		if (curlyBracketCount == 1 && squareBracketCount == 0 && (c == '"' || c == '\'') && lc != '\\') {
			// we have a new quote here
			if (quote == '\0') {
				quote = c;
				// key?
				if (parseMode == PARSEMODE_KEY) {
					if (mapKeyStart == string::npos) {
						mapKeyStart = i;
						mapKeyLineIdx = subLineIdx;
					}
				} else
				// value
				if (parseMode == PARSEMODE_VALUE) {
					if (mapValueStart == string::npos) mapValueStart = i;
				}
			} else
			// finish the quote
			if (quote == c) {
				quote = '\0';
			}
		} else
		// no quote
		if (quote == '\0') {
			// : -> map key separator
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c == ':' && nc != ':' && lc != ':' && lc != '\\') {
				//
				if (mapKeyStart != string::npos) {
					mapKeyEnd = i - 1;
				}
				//
				parseMode = PARSEMODE_VALUE;
				//
			} else
			// , -> insert map
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c == ',') {
				// TODO: use parse mode here
				if (mapValueStart != string::npos) {
					mapValueEnd = i - 1;
				} else
				if (mapKeyStart != string::npos && mapValueStart == string::npos) {
					mapKeyEnd = i - 1;
				}
				// insert map key value pair
				insertMapKeyValuePair();
				// nada
			} else
			// possible function call or inline function as value
			if (c == '(') {
				//
				bracketCount++;
				//
				if (bracketCount == 1) {
					inlineFunctionSignatureStartCandidate = i;
					inlineFunctionLineIdxCandidate = statement.line + subLineIdx;
				}
			} else
			if (c == ')') {
				bracketCount--;
				// function assignment
				if (inlineFunctionSignatureStartCandidate != string::npos && bracketCount == 0 && mapValueStart == string::npos) {
					mapValueStart = inlineFunctionSignatureStartCandidate;
					inlineFunctionLineIdx = inlineFunctionLineIdxCandidate;
				}
				//
				inlineFunctionSignatureStartCandidate = string::npos;
				inlineFunctionLineIdxCandidate = LINE_NONE;
			} else
			// map/set initializer
			if (c == '{' && squareBracketCount == 0 && bracketCount == 0) {
				// TODO: unexpected character if beeing in key parse mode
				// increase square bracket count
				curlyBracketCount++;
				// we have a inner map/set initializer, mark it
				if (curlyBracketCount == 2) {
					if (mapValueStart == string::npos) mapValueStart = i;
				}
			} else
			// end of map/set initializer or inline lamda function
			if (c == '}' && squareBracketCount == 0 && bracketCount == 0) {
				// TODO: unexpected character if beeing in key parse mode
				curlyBracketCount--;
				// done? insert into map
				if (curlyBracketCount == 0) {
					// TODO: use parse mode here
					// first guess, we have a value to finish
					if (mapValueStart != string::npos) {
						mapValueEnd = i - 1;
					} else
					// or a key if parsing a set
					if (mapKeyStart != string::npos) {
						mapKeyEnd = i - 1;
					}
					// insert map key value pair
					insertMapKeyValuePair();
				} else
				// otherwise push inner map initializer
				if (curlyBracketCount == 1) {
					// parse and insert into map
					string_view mapKey;
					auto dequotedMapKey = false;
					// map key
					if (mapKeyStart != string::npos) {
						if (mapKeyEnd == string::npos) mapKeyEnd = i;
						auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
						if (viewIsStringLiteral(mapKey) == true) {
							mapKey = dequote(mapKey);
							dequotedMapKey = true;
						}
					}
					//
					mapKeyStart = string::npos;
					mapKeyEnd = string::npos;
					// validate map key
					if (mapKey.empty() == true || viewIsKey(mapKey) == false) {
						Console::printLine(minitScript->getStatementInformation(statement, mapKeyLineIdx) + ": Invalid key name, ignoring map entry: " + string(mapKey));
					} else {
						auto _private = dequotedMapKey == true?false:viewIsKeyPrivate(mapKey);
						if (_private == true) mapKey = viewGetPrivateKey(mapKey);
						//
						inlineFunctionSignatureStartCandidate = string::npos;
						inlineFunctionLineIdxCandidate = LINE_NONE;
						// map value
						if (mapValueStart != string::npos) {
							mapValueEnd = i;
							auto mapValueLength = mapValueEnd - mapValueStart + 1;
							if (mapValueLength > 0) {
								auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
								if (mapValueStringView.empty() == false) {
									vector<string_view> lamdaFunctionArguments;
									string_view lamdaFunctionScriptCode;
									int lamdaFunctionLineIdx = inlineFunctionLineIdx;
									if (viewIsLamdaFunction(mapValueStringView, lamdaFunctionArguments, lamdaFunctionScriptCode, lamdaFunctionLineIdx) == true) {
										Variable mapValue;
										minitScript->createLamdaFunction(mapValue, lamdaFunctionArguments, lamdaFunctionScriptCode, lamdaFunctionLineIdx, true, statement, string(mapKey));
										variable.setMapEntry(string(mapKey), mapValue, _private);
										//
										hasValues = true;
									} else {
										// map/set
										auto mapValue = initializeMapSet(scriptFileName, mapValueStringView, minitScript, scriptIdx, statement);
										variable.setMapEntry(string(mapKey), mapValue, _private);
										//
										hasValues = true;
									}

								}
							}
							//
							mapValueStart = string::npos;
							mapValueEnd = string::npos;
						}
						//
						inlineFunctionLineIdx = LINE_NONE;
					}
					//
					parseMode = PARSEMODE_KEY;
					mapKeyLineIdx = LINE_NONE;
				}
			} else
			// array initializer
			if (c == '[' && curlyBracketCount == 1 && bracketCount == 0) {
				// we have a inner array initializer, mark it
				if (squareBracketCount == 0) {
					if (mapValueStart == string::npos) mapValueStart = i;
				}
				// increase square bracket count
				squareBracketCount++;
			} else
			// end of array initializer
			if (c == ']' && squareBracketCount == 1 && curlyBracketCount == 1 && bracketCount == 0) {
				squareBracketCount--;
				// otherwise push inner array initializer
				if (squareBracketCount == 0 && mapValueStart != string::npos && initializerString[mapValueStart] == '[') {
					// parse and insert into map
					string_view mapKey;
					auto dequotedMapKey = false;
					// map key
					if (mapKeyStart != string::npos) {
						auto mapKeyLength = mapKeyEnd - mapKeyStart + 1;
						if (mapKeyLength > 0) mapKey = StringTools::viewTrim(string_view(&initializerString[mapKeyStart], mapKeyLength));
						if (viewIsStringLiteral(mapKey) == true) {
							mapKey = dequote(mapKey);
							dequotedMapKey = true;
						}
					}
					//
					mapKeyStart = string::npos;
					mapKeyEnd = string::npos;
					// validate map key
					if (mapKey.empty() == true || viewIsKey(mapKey) == false) {
						Console::printLine(minitScript->getStatementInformation(statement, mapKeyLineIdx) + ": Invalid key name, ignoring map entry: " + string(mapKey));
					} else {
						auto _private = dequotedMapKey == true?false:viewIsKeyPrivate(mapKey);
						if (_private == true) mapKey = viewGetPrivateKey(mapKey);
						//
						inlineFunctionSignatureStartCandidate = string::npos;
						inlineFunctionLineIdxCandidate = LINE_NONE;
						// array value
						if (mapValueStart != string::npos) {
							mapValueEnd = i;
							auto mapValueLength = mapValueEnd - mapValueStart + 1;
							if (mapValueLength > 0) {
								auto mapValueStringView = StringTools::viewTrim(string_view(&initializerString[mapValueStart], mapValueLength));
								if (mapValueStringView.empty() == false) {
									auto mapValue = initializeArray(scriptFileName, mapValueStringView, minitScript, scriptIdx, statement);
									variable.setMapEntry(string(mapKey), mapValue, _private);
									//
									hasValues = true;
								}
							}
							//
							mapValueStart = string::npos;
							mapValueEnd = string::npos;
						}
						//
						inlineFunctionLineIdx = LINE_NONE;
					}
					//
					parseMode = PARSEMODE_KEY;
					mapKeyLineIdx = LINE_NONE;
				}
			} else
			// set up map key  start
			if (curlyBracketCount == 1 && squareBracketCount == 0 && bracketCount == 0 && c != ' ' && c != '\t' && c != '\n') {
				if (parseMode == PARSEMODE_KEY && mapKeyStart == string::npos) {
					mapKeyStart = i;
					mapKeyLineIdx = subLineIdx;
				} else
				if (parseMode == PARSEMODE_VALUE && mapValueStart == string::npos) {
					mapValueStart = i;
				}
			}
		}
		//
		lc = lc == '\\' && c == '\\'?'\0':c;
	}
	// convert to set if no values given
	if (hasValues == false && variable.getMapSize() > 0) {
		Variable setVariable;
		setVariable.setType(TYPE_SET);
		const auto& mapValueReference = variable.getMapValueReference();
		for (const auto& [mapVariableKey, mapVariableValue]: mapValueReference) {
			setVariable.insertSetKey(mapVariableKey);
		}
		variable = setVariable;
	}
	//
	auto initalizer = make_unique<MinitScript::Variable::Initializer>(string(initializerString), statement, nullptr);
	variable.initializerReferenceUnion.initializer->copy(initalizer.get());
	//
	return variable;
}

void MinitScript::Variable::setFunctionCallStatement(const string& scriptFileName, const string& initializerStatement, MinitScript* minitScript, int scriptIdx, const Statement& statement) {
	setType(TYPE_FUNCTION_CALL);
	getStringValueReference().setValue(initializerStatement);
	//
	Statement initializerScriptStatement(
		scriptFileName,
		statement.line,
		statement.statementIdx,
		initializerStatement,
		initializerStatement,
		MinitScript::STATEMENTIDX_NONE
	);
	//
	string_view methodName;
	vector<ParserArgument> arguments;
	SyntaxTreeNode* evaluateSyntaxTree = new SyntaxTreeNode();
	//
	if (minitScript->parseStatement(initializerStatement, methodName, arguments, initializerScriptStatement) == false) {
		//
	} else
	if (minitScript->createStatementSyntaxTree(scriptFileName, scriptIdx, methodName, arguments, initializerScriptStatement, *evaluateSyntaxTree) == false) {
		//
	} else {
		getInitializerReference() = new Initializer(initializerStatement, statement, evaluateSyntaxTree);
	}
}

MinitScript::Variable* MinitScript::evaluateVariableAccessIntern(MinitScript::Variable* variablePtr, const string& variableStatement, const string& callerMethod, Variable*& parentVariable, int64_t& arrayIdx, string& key, int& setAccessBool, const SubStatement* subStatement, bool expectVariable) {
	// get root variable
	key.clear();
	// no array idx by default
	arrayIdx = ARRAYIDX_NONE;
	// determine left and right access operator position if there are any
	auto accessOperatorLeftIdx = string::npos;
	auto accessOperatorRightIdx = string::npos;
	if (getVariableAccessOperatorLeftRightIndices(variableStatement, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, subStatement) == false) {
		return nullptr;
	}
	// access operator, if we have any, evaluate the array index
	auto haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
	if (haveAccessOperator == true &&
		evaluateAccess(variableStatement, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, subStatement) == false) {
		return nullptr;
	}
	//
	// get pointer to children variable
	if (haveAccessOperator == false) {
		//
		return variablePtr;
	} else {
		// resolve first parsed access pattern and repeat until resolved
		while (haveAccessOperator == true) {
			//
			bool privateParentScope = variablePtr->isPrivateScope();
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
						//
						if (variablePtr->isPrivate() == true && privateParentScope == false) {
							//
							Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Private variable: " + variableStatement + ": access not allowed from outside of object");
							//
							parentVariable = nullptr;
							return nullptr;
						}
					} else {
						if (expectVariable == true) {
							Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": key not found: '" + key + "'");
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
					Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": map/set access operator, but variable is not of type map/set");
					return nullptr;
				}
			} else
			if (variablePtr->getType() == TYPE_ARRAY) {
				// otherwise array
				if (arrayIdx == ARRAYIDX_ADD) {
					// we have our parent
					parentVariable = variablePtr;
					//
					return nullptr;
				} else
				if (arrayIdx >= ARRAYIDX_FIRST && arrayIdx < variablePtr->getArrayValueReference().size()) {
					//
					parentVariable = variablePtr;
					//
					variablePtr = variablePtr->getArrayValueReference()[arrayIdx];
				} else {
					Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": index out of bounds: 0 <= " + to_string(arrayIdx) + " < " + to_string(variablePtr->getArrayValueReference().size()));
					return nullptr;
				}
			} else {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": access operator, expected array, but got: " + variablePtr->getValueAsString());
				return nullptr;
			}

			//
			auto accessOperatorStartIdx = accessOperatorRightIdx;
			accessOperatorLeftIdx = string::npos;
			accessOperatorRightIdx = string::npos;
			if (getVariableAccessOperatorLeftRightIndices(variableStatement, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, subStatement, accessOperatorStartIdx) == false) {
				// fail
				return nullptr;
			}

			// do we have a next array access next to previous one?
			haveAccessOperator = accessOperatorLeftIdx != string::npos && accessOperatorRightIdx != string::npos;
			if (haveAccessOperator == false) {
				return variablePtr;
			} else {
				// yep, evaluate it
				if (evaluateAccess(variableStatement, callerMethod, accessOperatorLeftIdx, accessOperatorRightIdx, arrayIdx, key, subStatement) == false) {
					return nullptr;
				}
			}

			//
			if (parentVariable != nullptr && parentVariable->isPrivateScope() == true) privateParentScope = true;
		}
		//
		return variablePtr;
	}
}

inline void MinitScript::setVariableInternal(const string& variableStatement, Variable* parentVariable, Variable* variablePtr, int64_t arrayIdx, const string& key, const Variable& variable, const SubStatement* subStatement, bool createReference) {
	// common case
	if (variablePtr != nullptr) {
		if (variablePtr->isConstant() == false) {
			if (createReference == true) {
				variablePtr->setReference(&variable);
			} else {
				variablePtr->setValue(variable);
			}
		} else {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Constant: " + variableStatement + ": assignment of constant is not allowed");
		}
		return;
	} else
	// array add operator
	if (key.empty() == false) {
		if (parentVariable == nullptr) {
			// no op, we complain somewhere else, lol
		} else
		// all checks passed, push to map
		if (parentVariable->getType() == MinitScript::TYPE_MAP) {
			// check if our parent is not a const variable
			if (parentVariable->isConstant() == false) {
				parentVariable->setMapEntry(
					key,
					createReference == true?
						(variable.isReference() == true?variable:Variable::createReferenceVariable(&variable)):
						(variable.isReference() == false?variable:Variable::createNonReferenceVariable(&variable))
				);
			} else {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Constant: " + variableStatement + ": assignment of constant is not allowed");
			}
		} else
		if (parentVariable->getType() == MinitScript::TYPE_SET) {
			// check if our parent is not a const variable
			if (parentVariable->isConstant() == false) {
				bool booleanValue;
				if (variable.getBooleanValue(booleanValue, false) == true) {
					if (booleanValue == true) {
						parentVariable->insertSetKey(key);
					} else {
						parentVariable->removeSetKey(key);
					}
				} else {
					Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": set access operator: expected boolean variable to remove/insert key in set, but got " + variable.getTypeAsString());
				}
			} else {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Constant: " + variableStatement + ": assignment of constant is not allowed");
			}
		} else {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": map/set access operator: expected map/set, but got " + parentVariable->getTypeAsString() + ": '" + key + "'");
		}
		//
		return;
	} else
	if (arrayIdx == ARRAYIDX_ADD) {
		if (parentVariable == nullptr) {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": [] array push operator without array");
		} else
		if (parentVariable->getType() == MinitScript::TYPE_ARRAY) {
			// check if our parent is not a const variable
			if (parentVariable->isConstant() == false) {
				// all checks passed, push variable to array
				parentVariable->pushArrayEntry(
					createReference == true?
						(variable.isReference() == true?variable:Variable::createReferenceVariable(&variable)):
						(variable.isReference() == false?variable:Variable::createNonReferenceVariable(&variable))
				);
			} else {
				Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Constant: " + variableStatement + ": assignment of constant is not allowed");
			}
		} else {
			Console::printLine((subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": [] array push operator: expected array, but got " + parentVariable->getTypeAsString());
		}
		//
		return;
	}
}

inline bool MinitScript::evaluateInternal(const string& statement, const string& executableStatement, Variable& returnValue, bool pushScriptState) {
	Statement evaluateStatement(
		"evaluate",
		LINE_NONE,
		0,
		"internal.script.evaluate(" + statement + ")",
		"internal.script.evaluate(" + executableStatement + ")",
		STATEMENTIDX_NONE
	);
	auto scriptEvaluateStatement = "internal.script.evaluate(" + executableStatement + ")";
	//
	string_view methodName;
	vector<ParserArgument> arguments;
	SyntaxTreeNode evaluateSyntaxTree;
	if (parseStatement(scriptEvaluateStatement, methodName, arguments, evaluateStatement) == false) {
		return false;
	} else
	if (createStatementSyntaxTree("evaluate", SCRIPTIDX_NONE, methodName, arguments, evaluateStatement, evaluateSyntaxTree) == false) {
		return false;
	} else {
		//
		if (pushScriptState == true) {
			this->pushScriptState();
			resetScriptExecutationState(SCRIPTIDX_NONE, STATEMACHINESTATE_NEXT_STATEMENT);
		}
		getScriptState().running = true;
		//
		returnValue.setValue(
			executeStatement(
				evaluateSyntaxTree,
				evaluateStatement
			)
		);
		//
		if (pushScriptState == true) popScriptState();
		//
		return true;
	}
}

inline const MinitScript::Variable MinitScript::initializeVariable(const Variable& variable) {
	switch (variable.getType()) {
		case TYPE_ARRAY:
			{
				Variable arrayVariable;
				arrayVariable.setType(TYPE_ARRAY);
				//
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
				Variable mapVariable;
				mapVariable.setType(TYPE_MAP);
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
				return executeStatement(
					*variable.getInitializer()->getSyntaxTree(),
					variable.getInitializer()->getStatement()
				);
			}
		default: break;
	}
	//
	return variable;
}

inline bool MinitScript::viewIsKey(const string_view& candidate) {
	if (candidate.empty() == true) return false;
	auto i = 0;
	if (candidate[i] == '-') i++;
	for (; i < candidate.size(); i++) {
		auto c = candidate[i];
		if (Character::isAlphaNumeric(c) == false && c != '_') return false;
	}
	return true;
}

inline bool MinitScript::viewIsKeyPrivate(const string_view& candidate) {
	if (candidate.empty() == true) return false;
	if (candidate[0] == '-') return true;
	return false;
}

inline const string_view MinitScript::viewGetPrivateKey(const string_view& candidate) {
	return string_view(&candidate.data()[1], candidate.size() - 1);
}

inline bool MinitScript::getVariableAccessOperatorLeftRightIndices(const string& variableStatement, const string& callerMethod, string::size_type& accessOperatorLeftIdx, string::size_type& accessOperatorRightIdx, const SubStatement* subStatement, int startIdx) {
	accessOperatorLeftIdx = string::npos;
	accessOperatorRightIdx = string::npos;
	auto haveKey = false;
	auto squareBracketsCount = 0;
	// improve me!
	if (startIdx > 0) {
		haveKey = variableStatement[startIdx - 1] == '.';
		if (haveKey == true) accessOperatorLeftIdx = startIdx - 1;
	} else
	if (startIdx == 0) {
		//
		auto lc = '\0';
		for (auto i = 0; i < variableStatement.length(); i++) {
			auto c = variableStatement[i];
			if (lc == ':' && c == ':') {
				startIdx = i + 1;
				break;
			}
			//
			lc = c;
		}
	}
	for (auto i = startIdx; i < variableStatement.length(); i++) {
		auto c = variableStatement[i];
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
				Console::printLine("MinitScript::" + callerMethod + "(): " + (subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": unexpected char: ']'");
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
				Console::printLine("MinitScript::" + callerMethod + "(): " + (subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": unexpected char: ']'");
				return false;
			}
		}
	}
	//
	if (haveKey == true) accessOperatorRightIdx = variableStatement.size();
	//
	return true;
}

inline bool MinitScript::evaluateAccess(const string& variableStatement, const string& callerMethod, string::size_type& arrayAccessOperatorLeftIdx, string::size_type& arrayAccessOperatorRightIdx, int64_t& arrayIdx, string& key, const SubStatement* subStatement) {
	key.clear();
	arrayIdx = ARRAYIDX_NONE;
	// check for dot access
	if (variableStatement.data()[arrayAccessOperatorLeftIdx] == '.') {
		key = string(StringTools::viewTrim(string_view(&variableStatement.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 1)));
		return true;
	}
	// evaluate array index
	auto arrayIdxExpressionStringView = StringTools::viewTrim(string_view(&variableStatement.data()[arrayAccessOperatorLeftIdx + 1], arrayAccessOperatorRightIdx - arrayAccessOperatorLeftIdx - 2));
	if (arrayIdxExpressionStringView.empty() == false) {
		// integer first for performance
		if (Integer::viewIs(arrayIdxExpressionStringView) == true) {
			arrayIdx = Integer::viewParse(arrayIdxExpressionStringView);
		} else {
			// TODO: as evaluate statement we also might need the expression that had not yet a preprocessor run for error messages and such
			Variable statementReturnValue;
			auto evaluateStatement = string(arrayIdxExpressionStringView);
			if (evaluateInternal(evaluateStatement, evaluateStatement, statementReturnValue, false) == false || statementReturnValue.getIntegerValue(arrayIdx, false) == false) {
				Console::printLine("MinitScript::" + callerMethod + "(): " + (subStatement != nullptr?getSubStatementInformation(*subStatement):scriptFileName) + ": Variable: " + variableStatement + ": failed to evaluate expression: '" + string(arrayIdxExpressionStringView) + "'");
				return false;
			}
		}
	} else {
		arrayIdx = ARRAYIDX_ADD;
	}
	//
	return true;
}

void MinitScript::setConstantInternal(Variable& variable) {
	variable.setConstant();
	switch (variable.getType()) {
		case TYPE_ARRAY:
			{
				auto arrayPointer = variable.getArrayPointer();
				if (arrayPointer == nullptr) break;
				for (const auto arrayEntry: *arrayPointer) {
					setConstant(*arrayEntry);
				}
				//
				break;
			}
		case TYPE_MAP:
			{
				auto mapPointer = variable.getMapPointer();
				if (mapPointer == nullptr) break;
				for (const auto& [mapKey, mapValue]: *mapPointer) {
					setConstant(*mapValue);
				}
				//
				break;
			}
		default:
			break;
	}
}

void MinitScript::unsetConstantInternal(Variable& variable) {
	if (variable.isReference() == true) {
		Console::printLine("MinitScript::unsetConstantInternal(): Can not unset constant if reference variable is given.");
		return;
	}
	variable.unsetConstant();
	switch (variable.getType()) {
		case TYPE_ARRAY:
			{
				auto arrayPointer = variable.getArrayPointer();
				if (arrayPointer == nullptr) break;
				for (const auto arrayEntry: *arrayPointer) {
					unsetConstant(*arrayEntry);
				}
				//
				break;
			}
		case TYPE_MAP:
			{
				auto mapPointer = variable.getMapPointer();
				if (mapPointer == nullptr) break;
				for (const auto& [mapKey, mapValue]: *mapPointer) {
					unsetConstant(*mapValue);
				}
				//
				break;
			}
		default:
			break;
	}
}

void MinitScript::garbageCollection() {
	auto garbageCollectionDataTypesIndicesCopy = garbageCollectionDataTypesIndices;
	for (auto index: garbageCollectionDataTypesIndicesCopy) {
		auto& garbageCollectionDataType = garbageCollectionDataTypes[index];
		garbageCollectionDataType.dataType->garbageCollection(garbageCollectionDataType.context);
	}
}

const string MinitScript::stackTrace(const span<Variable>& arguments, const SubStatement& subStatement) {
	//
	auto createMethodName = [](MinitScript* rootScript, int scriptIdx) -> const string {
		if (scriptIdx < 0 || scriptIdx >= rootScript->getScripts().size()) return string();
		const auto& script = rootScript->getScripts()[scriptIdx];
		//
		string methodType;
		switch(script.type) {
			case MinitScript::Script::TYPE_NONE: break;
			case MinitScript::Script::TYPE_FUNCTION: methodType = "function: "; break;
			case MinitScript::Script::TYPE_STACKLET: methodType = "stacklet: "; break;
			//
			#if defined(MINITSCRIPT_EVENTS)
				// events
				case MinitScript::Script::TYPE_ON: methodType = "on: "; break;
				case MinitScript::Script::TYPE_ONENABLED: methodType = "on_enabled: "; break;
			#endif
		};
		//
		return
			methodType + "_" +
			(script.name.empty() == false?script.name:(
				StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
					script.condition:
					to_string(scriptIdx)
				)
			);
	};

	//
	string result;
	result+=
		string() +
		"Stack trace:" +
		"\n";
	//
	auto j = 0;
	for (int i = rootScript->scriptStateStack.size() - 1; i >= 0; --i) {
		auto scriptState = rootScript->scriptStateStack[i].get();
		if (scriptState->scriptIdx == SCRIPTIDX_NONE) continue;
		const auto& script = rootScript->scripts[scriptState->scriptIdx];
		const auto& statements = script.getStatements();
		const auto& statement = statements[scriptState->statementIdx];
		auto methodName = createMethodName(this->rootScript, scriptState->scriptIdx);
		auto scriptMethod = rootScript->getMethod(methodName);
		// arguments for script methods
		string arguments = scriptMethod != nullptr?scriptMethod->getArgumentsInformation():string();
		// arguments for functions and stacklets
		if (script.type == MinitScript::Script::TYPE_FUNCTION || script.type == MinitScript::Script::TYPE_STACKLET) {
			for (const auto& argument: script.arguments) {
				auto variableIt = scriptState->variables.find(argument.name);
				auto variable = variableIt == scriptState->variables.end()?MinitScript::Variable():variableIt->second;
				if (arguments.empty() == false) arguments+= ", ";
				arguments+= argument.name;
			}
		}
		//
		result+=
			string() +
			"[" + to_string(j) + "]: " +
			statement.fileName +
			":" +
			to_string(statement.line) +
			": " +
			methodName +
			"(" + arguments + "): " +
			statement.statement +
			(i > 0?"\n":"");
		//
		++j;
	}
	//
	return result;
}

bool MinitScript::_throw(const MinitScript::Variable& throwArgument) {
	auto& scriptState = getScriptState();
	auto& blockStack = scriptState.blockStack;
	auto& block = blockStack.back();
	//
	auto tryBlockIdx = -1;
	for (int i = blockStack.size() - 1; i >= 0; i--) {
		if (blockStack[i].type == MinitScript::ScriptState::Block::TYPE_TRY) {
			tryBlockIdx = i;
			break;
		}
	}
	if (tryBlockIdx == -1) {
		//
		blockStack.erase(blockStack.begin() + 1, blockStack.end());
		//
		return false;
	} else {
		auto catchStatement = blockStack[tryBlockIdx].catchStatement;
		//
		blockStack.erase(blockStack.begin() + tryBlockIdx + 1, blockStack.end());
		//
		blockStack.emplace_back(
			MinitScript::ScriptState::Block::TYPE_CATCH,
			false,
			nullptr,
			nullptr,
			nullptr,
			throwArgument
		);
		//
		gotoStatement(*catchStatement);
		//
		return true;
	}
}
