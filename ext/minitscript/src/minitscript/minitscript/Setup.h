#pragma once

#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>

using std::string;
using std::vector;

/**
 * MinitScript setup methods
 * @author Andreas Drewke
 */
class minitscript::minitscript::Setup {
public:
	/**
	 * Setup function and stacket script indices
	 * @param minitScript MinitScript instance
	 * @param scriptIdx script index
	 * @param parseErrors parse errors
	 */
	static bool setupFunctionAndStackletScriptIndices(MinitScript* minitScript, int scriptIdx, vector<string>& parseErrors);

	/**
	 * Setup function and stacket script indices
	 * @param minitScript MinitScript instance
	 * @param syntaxTreeNode syntax tree node
	 * @param statement statement
	 * @param parseErrors parse errors
	 */
	static bool setupFunctionAndStackletScriptIndices(MinitScript* minitScript, MinitScript::SyntaxTreeNode& syntaxTreeNode, const MinitScript::Statement& statement, vector<string>& parseErrors);

	/**
	  * Setup function and stacket script indices
	  * @param minitScript MinitScript instance
	  * @param variable variable
	  * @param statement statement
	  * @param subLineIdx sub line index
	 * @param parseErrors parse errors
	  * @return success
	  */
	static bool setupFunctionAndStackletScriptIndices(MinitScript* minitScript, MinitScript::Variable& variable, const MinitScript::Statement& statement, int subLineIdx, vector<string>& parseErrors);

};
