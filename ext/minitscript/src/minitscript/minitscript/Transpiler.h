#pragma once

#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/utilities/StringTools.h>

using std::array;
using std::find;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

/**
 * MinitScript transpiler
 * @author Andreas Drewke
 */
class minitscript::minitscript::Transpiler {
public:
	/**
	 * Transpile MinitScript script instance
	 * @param minitScript MinitScript script instance
	 * @param transpilationFileName transpilation file name
	 * @param minitScriptExtensionFileNames MinitScript extension file names
	 */
	static void transpile(MinitScript* minitScript, const string& transpilationFileName, const vector<string>& minitScriptExtensionFileNames);

	/**
	 * Untranspile
	 * @param scriptFileName script file name
	 * @param transpilationFileName transpilation file name
	 */
	static void untranspile(const string& scriptFileName, const string& transpilationFileName);

	/**
	 * Create source code for whole script
	 * @param minitScript MinitScript instance
	 * @return source code
	 */
	static const string createSourceCode(MinitScript* minitScript);

private:
	/**
	 * Get script type name
	 * @param type script type
	 * @return script type enum identifier
	 */
	inline static const string getScriptTypeReadableName(MinitScript::Script::Type type) {
		switch(type) {
			case MinitScript::Script::TYPE_NONE: return "none";
			case MinitScript::Script::TYPE_FUNCTION: return "function";
			case MinitScript::Script::TYPE_STACKLET: return "stacklet";
			//
			#if defined(MINITSCRIPT_EVENTS)
				// events
				case MinitScript::Script::TYPE_ON: return "on";
				case MinitScript::Script::TYPE_ONENABLED: return "on-enabled";
			#endif
		};
		//
		return string();
	}

	/**
	 * Get script type enum identifier
	 * @param type script type
	 * @return script type enum identifier
	 */
	inline static const string getScriptTypeEnumIdentifier(MinitScript::Script::Type type) {
		switch(type) {
			case MinitScript::Script::TYPE_NONE: return "Script::TYPE_NONE";
			case MinitScript::Script::TYPE_FUNCTION: return "Script::TYPE_FUNCTION";
			case MinitScript::Script::TYPE_STACKLET: return "Script::TYPE_STACKLET";
			//
			#if defined(MINITSCRIPT_EVENTS)
				// events
				case MinitScript::Script::TYPE_ON: return "Script::TYPE_ON";
				case MinitScript::Script::TYPE_ONENABLED: return "Script::TYPE_ONENABLED";
			#endif
		};
		//
		return string();
	}

	/**
	 * Create method name
	 * @param scriptIdx script index
	 * @return method name
	 */
	inline static const string createMethodName(MinitScript* minitScript, int scriptIdx) {
		if (scriptIdx < 0 || scriptIdx >= minitScript->getScripts().size()) return string();
		const auto& script = minitScript->getScripts()[scriptIdx];
		//
		string methodType;
		switch(script.type) {
			case MinitScript::Script::TYPE_NONE: break;
			case MinitScript::Script::TYPE_FUNCTION: methodType = "function"; break;
			case MinitScript::Script::TYPE_STACKLET: methodType = "stacklet"; break;
			//
			#if defined(MINITSCRIPT_EVENTS)
				// events
				case MinitScript::Script::TYPE_ON: methodType = "on"; break;
				case MinitScript::Script::TYPE_ONENABLED: methodType = "on_enabled"; break;
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
	}

	/**
	 * Create short method name
	 * @param scriptIdx script index
	 * @return short method name
	 */
	inline static const string createShortMethodName(MinitScript* minitScript, int scriptIdx) {
		if (scriptIdx < 0 || scriptIdx >= minitScript->getScripts().size()) return string();
		const auto& script = minitScript->getScripts()[scriptIdx];
		return
			(script.name.empty() == false?script.name:(
				StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
					script.condition:
					to_string(scriptIdx)
				)
			);
	}

	/**
	 * Escape string variable
	 * @param str string
	 * @return escaped string
	 */
	inline static const string escapeString(const string& str) {
		//
		auto result = str;
		const array<char, 11> escapeSequences = {'0', 'a', 'b', 'f', 'n', 'r', 't', 'v', 'U', '"'};
		for (const auto c: escapeSequences) {
			result = StringTools::replace(result, string("\\") + c, string("\\\\") + c);
		}
		//
		result = StringTools::replace(result, "\0", "\\0");
		result = StringTools::replace(result, "\a", "\\a");
		result = StringTools::replace(result, "\b", "\\b");
		result = StringTools::replace(result, "\f", "\\f");
		result = StringTools::replace(result, "\n", "\\n");
		result = StringTools::replace(result, "\r", "\\r");
		result = StringTools::replace(result, "\t", "\\t");
		result = StringTools::replace(result, "\v", "\\v");
		result = StringTools::replace(result, "\"", "\\\"");
		//
		string result2;
		auto lc = '\0';
		auto llc = '\0';
		for (auto i = 0; i < result.size(); i++) {
			//
			auto c = result[i];
			auto nc = i < result.size() - 1?result[i + 1]:'\0';
			if (c == '\\' && lc != '\\' && nc != '\\' && find(escapeSequences.begin(), escapeSequences.end(), nc) == escapeSequences.end()) {
				result2+= "\\\\";
			} else {
				result2+= c;
			}
			//
			auto lc = c;
			auto llc = lc;
		}
		//
		return result2;
	}

	/**
	 * Check if variable has access statement
	 * @param variableStatement variable statement
	 * @return variable has statement
	 */
	inline static bool variableHasStatement(const string& variableStatement) {
		auto doubleDotIdx = StringTools::indexOf(variableStatement, "::");
		if (doubleDotIdx == string::npos) doubleDotIdx = 0;
		auto dotIdx = StringTools::indexOf(variableStatement, ".", doubleDotIdx);
		if (dotIdx != string::npos) return true;
		auto squareBracketIdx = StringTools::indexOf(variableStatement, "[", doubleDotIdx);
		if (squareBracketIdx != string::npos) return true;
		return false;
	}

	/**
	 * Create variable name
	 * @param variableStatement variable statement
	 * @return variable name
	 */
	inline static const string createVariableName(const string& variableStatement) {
		auto doubleDotIdx = StringTools::indexOf(variableStatement, "::");
		if (doubleDotIdx == string::npos) doubleDotIdx = 0;
		auto dotIdx = StringTools::indexOf(variableStatement, ".", doubleDotIdx);
		if (dotIdx == string::npos) dotIdx = variableStatement.size();
		auto squareBracketIdx = StringTools::indexOf(variableStatement, "[", doubleDotIdx);
		if (squareBracketIdx == string::npos) squareBracketIdx = variableStatement.size();
		auto cppVariableName = StringTools::substring(variableStatement, 0, dotIdx < squareBracketIdx?dotIdx:squareBracketIdx);
		return cppVariableName;
	}

	/**
	 * Create global variable name
	 * @param variableStatement variable statement
	 * @return global CPP variable name
	 */
	inline static const string createGlobalVariableName(const string& variableStatement) {
		auto doubleDotIdx = StringTools::indexOf(variableStatement, "::");
		if (doubleDotIdx == string::npos) doubleDotIdx = 0;
		auto dotIdx = StringTools::indexOf(variableStatement, ".", doubleDotIdx);
		if (dotIdx == string::npos) dotIdx = variableStatement.size();
		auto squareBracketIdx = StringTools::indexOf(variableStatement, "[", doubleDotIdx);
		if (squareBracketIdx == string::npos) squareBracketIdx = variableStatement.size();
		auto cppVariableName = "_" + StringTools::substring(variableStatement, 1, dotIdx < squareBracketIdx?dotIdx:squareBracketIdx);
		cppVariableName = StringTools::replace(cppVariableName, "$", "_");
		cppVariableName = StringTools::replace(cppVariableName, ":", "_");
		cppVariableName = StringTools::replace(cppVariableName, ".", "_");
		return cppVariableName;
	}

	/**
	 * Create local variable name
	 * @param variableStatement variable statement
	 * @return local CPP variable name
	 */
	inline static const string createLocalVariableName(const string& variableStatement) {
		auto doubleDotIdx = StringTools::indexOf(variableStatement, "::");
		if (doubleDotIdx == string::npos) doubleDotIdx = 0;
		auto dotIdx = StringTools::indexOf(variableStatement, ".", doubleDotIdx);
		if (dotIdx == string::npos) dotIdx = variableStatement.size();
		auto squareBracketIdx = StringTools::indexOf(variableStatement, "[", doubleDotIdx);
		if (squareBracketIdx == string::npos) squareBracketIdx = variableStatement.size();
		auto cppVariableName = "_" + StringTools::substring(variableStatement, 1, dotIdx < squareBracketIdx?dotIdx:squareBracketIdx);
		cppVariableName = StringTools::replace(cppVariableName, "$", "_");
		cppVariableName = StringTools::replace(cppVariableName, ":", "_");
		cppVariableName = StringTools::replace(cppVariableName, ".", "_");
		return cppVariableName;
	}

	/**
	 * Get all classes method names
	 * @param minitScript MinitScript instance
	 * @return all classes method names
	 */
	static const unordered_set<string> getAllClassesMethodNames(MinitScript* minitScript);

	/**
	 * Get all classes method names sorted
	 * @param minitScript MinitScript instance
	 * @return all classes method names sorted
	 */
	static const vector<string> getAllClassesMethodNamesSorted(MinitScript* minitScript);

	/**
	 * Get method names per classes
	 * @param minitScript MinitScript instance
	 * @return method names per classes
	 */
	static const unordered_map<string, vector<string>> getClassesMethodNames(MinitScript* minitScript);

	/**
	 * Determine variables
	 * @param minitScript MinitScript script instance
	 * @param globalVariables global variables
	 * @param localVariables local variables per script index
	 */
	static void determineVariables(MinitScript* minitScript, unordered_set<string>& globalVariables, vector<unordered_set<string>>& localVariables);

	/**
	 * Determine variables within syntax tree
	 * @param scriptIdx script index
	 * @param syntaxTreeNode syntax tree node
	 * @param globalVariables global variables
	 * @param localVariables local variables per script index
	 */
	static void determineVariables(int scriptIdx, const MinitScript::SyntaxTreeNode& syntaxTreeNode, unordered_set<string>& globalVariables, vector<unordered_set<string>>& localVariables);

	/**
	 * Gather method code
	 * @param minitScriptExtensionsCode MinitScript extensions code
	 * @param className class name
	 * @param register line register line
	 * @param methodCodeMap method code map
	 */
	static void gatherMethodCode(
		const vector<string>& minitScriptExtensionsCode,
		const string& className,
		int registerLine,
		unordered_map<string, vector<string>>& methodCodeMap
	);

	/**
	 * Generate variable access
	 * @param minitScript MinitScript instance
	 * @param generatedCode generated code
	 * @param scriptConditionIdx script condition index
	 * @param scriptIdx script index
	 * @param variableName variable name
	 * @param accessName access name
	 * @param indent indent
	 * @param getMethodArgumentVariable get method argument variable
	 * @param getVariable issue get variable access
	 * @param getVariableReference issue get variable reference access
	 * @param setVariable set variable
	 * @param setVariableReference set variable reference
	 * @param setConstant set constant
	 * @param returnValue return value
	 * @param statementEnd statement end
	 * @param getArgumentIdx get argument index
	 * @param setArgumentIdx set argument index
	 */
	static void generateVariableAccess(
		MinitScript* minitScript,
		string& generatedCode,
		int scriptConditionIdx,
		int scriptIdx,
		const string& variableName,
		const string& indent,
		bool getMethodArgumentVariable,
		bool getVariable,
		bool getVariableReference,
		bool setVariable,
		bool setVariableReference,
		bool setConstant,
		const string& returnValueStatement = "returnValue = ",
		const string& statementEnd = ";\n",
		int getArgumentIdx = 0,
		int setArgumentIdx = 1
	);

	/**
	 * Generate array access methods
	 * @param minitScript MinitScript instance
	 * @param generatedDefinitions generated definitions
	 * @param minitScriptClassName MinitScript class name
	 * @param scriptConditionIdx script condition index
	 * @param scriptIdx script index
	 * @param methodName method name
	 * @param syntaxTree syntax tree
	 * @param statement statement
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param condition condition
	 * @param argumentIndices argument indices stack
	 * @param depth depth
	 */
	static void generateArrayAccessMethods(
		MinitScript* minitScript,
		string& generatedDefinitions,
		const string& minitScriptClassName,
		int scriptConditionIdx,
		int scriptIdx,
		const string& methodName,
		const MinitScript::SyntaxTreeNode& syntaxTree,
		const MinitScript::Statement& statement,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		bool condition,
		const vector<int>& argumentIndices = {},
		int depth = 0
	);

	/**
	 * Generate evaluate member access arrays
	 * @param minitScript MinitScript instance
	 * @param generatedDeclarations generated declarations
	 * @param generatedDefinitions generated definitions
	 */
	static void generateEvaluateMemberAccessArrays(
		MinitScript* minitScript,
		vector<string>& generatedDeclarations,
		vector<string>& generatedDefinitions
	);

	/**
	 * Generate array/map/set variable
	 * @param minitScript MinitScript instance
	 * @param scriptConditionIdx script condition index
	 * @param scriptIdx script index
	 * @param variable variable
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param methodName method name
	 * @param condition condition
	 * @param minitScriptClassName MinitScript class name
	 * @param generatedDefinitions generated definitions
	 * @param depth depth
	 * @param initializerDepth initializer depth
	 * @param postStatement post statement
	 */
	static void generateArrayMapSetVariable(
		MinitScript* minitScript,
		int scriptConditionIdx,
		int scriptIdx,
		const MinitScript::Variable& variable,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		const string& methodName,
		bool condition,
		const string& minitScriptClassName,
		string& generatedDefinitions,
		int depth = 0,
		int initializerDepth = 0,
		const string& postStatement = string()
	);

	/**
	 * Generate array/map/set variable
	 * @param minitScript MinitScript instance
	 * @param generatedDefinitions generated definitions
	 * @param scriptConditionIdx script condition index
	 * @param scriptIdx script index
	 * @param minitScriptClassName MinitScript class name
	 * @param methodName method name
	 * @param syntaxTree syntax tree
	 * @param statement statement
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param condition condition
	 * @param argumentIndices argument indices
	 * @param depth depth
	 */
	static void generateArrayMapSetInitializer(
		MinitScript* minitScript,
		string& generatedDefinitions,
		int scriptConditionIdx,
		int scriptIdx,
		const string& minitScriptClassName,
		const string& methodName,
		const MinitScript::SyntaxTreeNode& syntaxTree,
		const MinitScript::Statement& statement,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		bool condition,
		const vector<int>& argumentIndices = {},
		int depth = 0
	);

	/**
	 * Transpile statement
	 * @param minitScript MinitScript instance
	 * @param generatedCode generated code
	 * @param syntaxTree syntax tree
	 * @param statement script statement
	 * @param scriptConditionIdx script condition index
	 * @param scriptIdx script index
	 * @param statementIdx statement index
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param scriptStateChanged script could have state changed
	 * @param scriptStopped script could have been stopped
	 * @param enabledNamedConditions enabled named conditions
	 * @param depth depth
	 * @param argumentIndices argument indices
	 * @param returnValue return value
	 * @param injectCode code to additionally inject
	 * @param additionalIndent additional indent
	 */
	static bool transpileStatement(
		MinitScript* minitScript,
		string& generatedCode,
		const MinitScript::SyntaxTreeNode& syntaxTree,
		const MinitScript::Statement& statement,
		int scriptConditionIdx,
		int scriptIdx,
		int& statementIdx,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		bool& scriptStateChanged,
		bool& scriptStopped,
		vector<string>& enabledNamedConditions,
		int depth = 0,
		const vector<int>& argumentIndices = {},
		const string& returnValue = string(),
		const string& injectCode = string(),
		int additionalIndent = 0
	);

	/**
	 * Transpile a script statement
	 * @param minitScript MinitScript instance
	 * @param className MinitScript class name
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @return success
	 */
	static bool transpile(
		MinitScript* minitScript,
		const string& className,
		string& generatedCode,
		int scriptIdx,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods
	);

	/**
	 * Transpile a condition
	 * @param minitScript MinitScript instance
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param returnValue return value
	 * @param injectCode inject code
	 * @return success
	 */
	static bool transpileCondition(
		MinitScript* minitScript,
		string& generatedCode,
		int scriptIdx,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		const string& returnValue,
		const string& injectCode,
		int depth = 0
	);

	/**
	 * Create source code for given syntax tree node
	 * @param syntaxTreeNode syntax tree node
	 */
	static const string createSourceCode(const MinitScript::SyntaxTreeNode& syntaxTreeNode);

	/**
	 * Create source code for given syntax tree
	 * @param scriptType script type
	 * @param condition condition
	 * @param functionArguments function arguments
	 * @param name name of named conditions
	 * @param conditionSyntaxTree condition syntax tree
	 * @param syntaxTree syntax tree
	 */
	static const string createSourceCode(
		MinitScript::Script::Type scriptType,
		const string& condition,
		const vector<MinitScript::Script::Argument>& functionArguments,
		const string& name,
		const MinitScript::SyntaxTreeNode& conditionSyntaxTree,
		const vector<MinitScript::SyntaxTreeNode>& syntaxTree
	);

};
