#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::string;
using std::to_string;
using std::unordered_map;
using std::vector;

using tdme::utilities::MiniScript;

/**
 * MiniScript transpiler tool set
 * @author Andreas Drewke
 */
class tdme::utilities::MiniScriptTranspiler {
public:

	/**
	 * Get all method names
	 * @param miniScript MiniScript instance
	 * @return all method names
	 */
	static const unordered_set<string> getAllMethodNames(MiniScript* miniScript);

	/**
	 * Get all method names sorted
	 * @param miniScript MiniScript instance
	 * @return all method names sorted
	 */
	static const vector<string> getAllMethodNamesSorted(MiniScript* miniScript);

	/**
	 * Get all method names by class name
	 * @param miniScript MiniScript instance
	 * @return all method names
	 */
	static const unordered_map<string, vector<string>> getAllClassesMethodNames(MiniScript* miniScript);

	/**
	 * Gather method code
	 * @param miniScriptExtensionsCode MiniScript extensions code
	 * @param className class name
	 * @param register line register line
	 * @param methodCodeMap method code map
	 */
	static void gatherMethodCode(
		const vector<string>& miniScriptExtensionsCode,
		const string& className,
		int registerLine,
		unordered_map<string, vector<string>>& methodCodeMap
	);

	/**
	 * Generate array access methods
	 * @param miniScript MiniScript instance
	 * @param generatedDeclarations generated declarations
	 * @param generatedDefinitions generated definitions
	 * @param miniScriptClassName MiniScript class name
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
		MiniScript* miniScript,
		string& generatedDeclarations,
		string& generatedDefinitions,
		const string& miniScriptClassName,
		const string& methodName,
		const MiniScript::ScriptSyntaxTreeNode& syntaxTree,
		const MiniScript::ScriptStatement& statement,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		bool condition,
		const vector<int>& argumentIndices = {},
		int depth = 0
	);

	/**
	 * Generate MiniScript evaluate member access arrays
	 * @param miniScript MiniScript instance
	 * @param generatedDeclarations generated declarations
	 * @param generatedDefinitions generated definitions
	 */
	static void generateMiniScriptEvaluateMemberAccessArrays(
		MiniScript* miniScript,
		vector<string>& generatedDeclarations,
		vector<string>& generatedDefinitions
	);

	/**
	 * Generate array/map/set variable
	 * @param miniScript MiniScript instance
	 * @param variable variable
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param methodName method name
	 * @param condition condition
	 * @param miniScriptClassName MiniScript class name
	 * @param generatedDeclarations generated declarations
	 * @param generatedDefinitions generated definitions
	 * @param depth depth
	 * @param initializerDepth initializer depth
	 * @param postStatement post statement
	 */
	static void generateArrayMapSetVariable(
		MiniScript* miniScript,
		const MiniScript::ScriptVariable& variable,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		const string& methodName,
		bool condition,
		const string& miniScriptClassName,
		string& generatedDeclarations,
		string& generatedDefinitions,
		int depth = 0,
		int initializerDepth = 0,
		const string& postStatement = string()
	);

	/**
	 * Generate array/map/set variable
	 * @param miniScript MiniScript instance
	 * @param generatedDeclarations generated declarations
	 * @param generatedDefinitions generated definitions
	 * @param miniScriptClassName MiniScript class name
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
		MiniScript* miniScript,
		string& generatedDeclarations,
		string& generatedDefinitions,
		const string& miniScriptClassName,
		const string& methodName,
		const MiniScript::ScriptSyntaxTreeNode& syntaxTree,
		const MiniScript::ScriptStatement& statement,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods,
		bool condition,
		const vector<int>& argumentIndices = {},
		int depth = 0
	);

	/**
	 * Transpile script statement
	 * @param miniScript MiniScript instance
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
	static bool transpileScriptStatement(
		MiniScript* miniScript,
		string& generatedCode,
		const MiniScript::ScriptSyntaxTreeNode& syntaxTree,
		const MiniScript::ScriptStatement& statement,
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
	 * @param miniScript MiniScript instance
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @return success
	 */
	static bool transpile(
		MiniScript* miniScript,
		string& generatedCode,
		int scriptIdx,
		const unordered_map<string, vector<string>>& methodCodeMap,
		const unordered_set<string>& allMethods
	);

	/**
	 * Transpile a script condition
	 * @param miniScript MiniScript instance
	 * @param generatedCode generated code
	 * @param scriptIdx script index
	 * @param methodCodeMap method code map
	 * @param allMethods all methods
	 * @param returnValue return value
	 * @param injectCode inject code
	 * @return success
	 */
	static bool transpileScriptCondition(
		MiniScript* miniScript,
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
	static const string createSourceCode(const MiniScript::ScriptSyntaxTreeNode& syntaxTreeNode);

	/**
	 * Create source code for given syntax tree
	 * @param scriptType script type
	 * @param condition condition
	 * @param arguments function arguments
	 * @param name name of named conditions
	 * @param conditionSyntaxTree condition syntax tree
	 * @param syntaxTree syntax tree
	 */
	static const string createSourceCode(
		MiniScript::Script::ScriptType scriptType,
		const string& condition,
		const vector<MiniScript::Script::ScriptArgument>& arguments,
		const string& name,
		const MiniScript::ScriptSyntaxTreeNode& conditionSyntaxTree,
		const vector<MiniScript::ScriptSyntaxTreeNode>& syntaxTree
	);

	/**
	 * Create source code for whole script
	 * @param miniScript MiniScript instance
	 * @return source code
	 */
	static const string createSourceCode(MiniScript* miniScript);

};
