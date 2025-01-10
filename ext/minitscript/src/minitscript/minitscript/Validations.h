#pragma once

#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>

using std::string;
using std::vector;

/**
 * MinitScript validations methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::Validations {
public:
	/**
	 * Validate stacklets
	 * @param minitScript MinitScript instance
	 * @param scriptIdx script index
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateStacklets(
		MinitScript* minitScript,
		int scriptIdx,
		vector<string>& parseErrors
	);

	/**
	 * Validate stacklets
	 * @param minitScript MinitScript instance
	 * @param function function
	 * @param parseErrors parse errors
	 * @param scopeScriptIdx scope script index or MinitScript::SCRIPTIDX_NONE for the function itself
	 * @return success
	 */
	static bool validateStacklets(
		MinitScript* minitScript,
		const string& function,
		vector<string>& parseErrors,
		int scopeScriptIdx = MinitScript::SCRIPTIDX_NONE
	);

	/**
	 * Validate stacklets
	 * @param minitScript MinitScript instance
	 * @param scopeScriptIdx scope script index
	 * @param syntaxTreeNode syntax tree node
	 * @param statement statement
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateStacklets(
		MinitScript* minitScript,
		int scopeScriptIdx,
		const MinitScript::SyntaxTreeNode& syntaxTreeNode,
		const MinitScript::Statement& statement,
		vector<string>& parseErrors
	);

	/**
	 * Validate callabe
	 * @param minitScript MinitScript instance
	 * @param function function
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateCallable(
		MinitScript* minitScript,
		const string& function,
		vector<string>& parseErrors
	);

	/**
	 * Validate callable
	 * @param minitScript MinitScript instance
	 * @param syntaxTreeNode syntax tree node
	 * @param statement statement
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateCallable(
		MinitScript* minitScript,
		const MinitScript::SyntaxTreeNode& syntaxTreeNode,
		const MinitScript::Statement& statement,
		vector<string>& parseErrors
	);

	/**
	 * Validate context functions
	 * @param minitScript MinitScript instance
	 * @param function function
	 * @param functionStack function stack
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateContextFunctions(
		MinitScript* minitScript,
		const string& function,
		vector<string>& functionStack,
		vector<string>& parseErrors
	);

	/**
	 * Validate context functions
	 * @param minitScript MinitScript instance
	 * @param syntaxTreeNode syntax tree node
	 * @param functionStack function stack
	 * @param statement statement
	 * @param parseErrors parse errors
	 * @return success
	 */
	static bool validateContextFunctions(
		MinitScript* minitScript,
		const MinitScript::SyntaxTreeNode& syntaxTreeNode,
		vector<string>& functionStack,
		const MinitScript::Statement& statement,
		vector<string>& parseErrors
	);
};
