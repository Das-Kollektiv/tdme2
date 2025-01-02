#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Validations.h>
#include <minitscript/utilities/Console.h>

using std::string;
using std::vector;

using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Validations;
using minitscript::utilities::Console;

bool Validations::validateStacklets(MinitScript* minitScript, int scriptIdx, vector<string>& parseErrors) {
	//
	const auto& scripts = minitScript->getScripts();
	const auto& script = scripts[scriptIdx];
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateStacklets(minitScript, script.type == MinitScript::Script::TYPE_FUNCTION?scriptIdx:MinitScript::SCRIPTIDX_NONE, syntaxTreeNode, statement, parseErrors) == false) {
			//
			return false;
		}
	}
	//
	return true;
}

bool Validations::validateStacklets(MinitScript* minitScript, const string& function, vector<string>& parseErrors, int scopeScriptIdx) {
	auto functionScriptIdx = minitScript->getFunctionScriptIdx(function);
	if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
		Console::printLine("MinitScript::validateStacklet(): function not found: " + function);
		return false;
	}
	//
	const auto& scripts = minitScript->getScripts();
	const auto& script = scripts[functionScriptIdx];
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateStacklets(minitScript, scopeScriptIdx == MinitScript::SCRIPTIDX_NONE?functionScriptIdx:scopeScriptIdx, syntaxTreeNode, statement, parseErrors) == false) {
			//
			return false;
		}
	}
	//
	return true;
}

bool Validations::validateStacklets(MinitScript* minitScript, int scopeScriptIdx, const MinitScript::SyntaxTreeNode& syntaxTreeNode, const MinitScript::Statement& statement, vector<string>& parseErrors) {
	const auto& scripts = minitScript->getScripts();
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				// TODO: improve me! This is actually litaral only, which can be also set as variable and be reused later
				//	basically we forbid here to create a stacklet assignment variable with wrong scope in a given scope
				if (syntaxTreeNode.value.getType() == MinitScript::TYPE_STACKLET_ASSIGNMENT) {
					// we only allow assignments of stacklets with a correct scope, means
					string stackletName;
					auto stackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
					if (syntaxTreeNode.value.getStackletValue(stackletName, stackletScriptIdx) == false ||
						(stackletScriptIdx = minitScript->getFunctionScriptIdx(stackletName)) == MinitScript::SCRIPTIDX_NONE) {
						//
						Console::printLine(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": " +
							syntaxTreeNode.value.getValueAsString() +
							": Stacklet not found"
						);
						//
						parseErrors.push_back(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": " +
							syntaxTreeNode.value.getValueAsString() +
							": Stacklet not found"
						);
						//
						return false;
					}
					//
					int stackletScopeScriptIdx = minitScript->getStackletScopeScriptIdx(stackletScriptIdx);
					if (stackletScopeScriptIdx != scopeScriptIdx) {
						// construct scope error
						string scopeErrorMessage;
						if (stackletScopeScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							scopeErrorMessage = "Stacklet requires root scope";
						} else {
							scopeErrorMessage = "Stacklet requires scope of " + scripts[stackletScopeScriptIdx].condition + "()";
						}
						scopeErrorMessage+= ", but has scope of ";
						if (scopeScriptIdx == MinitScript::SCRIPTIDX_NONE) {
							scopeErrorMessage+= "root scope";
						} else {
							scopeErrorMessage+= scripts[scopeScriptIdx].condition + "()";
						}
						//
						Console::printLine(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": " +
							syntaxTreeNode.value.getValueAsString() +
							": Stacklet scope invalid: " +
							scopeErrorMessage
						);
						//
						parseErrors.push_back(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": " +
							syntaxTreeNode.value.getValueAsString() +
							": Stacklet scope invalid" +
							scopeErrorMessage
						);
						//
						return false;
					}
					// check stacklet itself for stacklet litarals
					if (validateStacklets(minitScript, stackletName, parseErrors, scopeScriptIdx) == false) return false;
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateStacklets(minitScript, scopeScriptIdx, argument, statement, parseErrors) == false) return false;
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateStacklets(minitScript, scopeScriptIdx, argument, statement, parseErrors) == false) return false;
				}
				//
				if (minitScript->getFunctionScriptIdx(syntaxTreeNode.value.getValueAsString()) == scopeScriptIdx) {
					// recursion
				} else {
					validateStacklets(minitScript, syntaxTreeNode.value.getValueAsString(), parseErrors);
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
			{
				//
				string stackletName = syntaxTreeNode.value.getValueAsString();
				auto stackletScriptIdx = syntaxTreeNode.getScriptIdx();
				if (stackletName.empty() == true || stackletScriptIdx == MinitScript::SCRIPTIDX_NONE) {
					//
					Console::printLine(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": " +
						syntaxTreeNode.value.getValueAsString() +
						": Stacklet not found"
					);
					//
					parseErrors.push_back(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": " +
						syntaxTreeNode.value.getValueAsString() +
						": Stacklet not found"
					);
					//
					return false;
				}
				//
				int stackletScopeScriptIdx = minitScript->getStackletScopeScriptIdx(stackletScriptIdx);
				if (stackletScopeScriptIdx != scopeScriptIdx) {
					// construct scope error
					string scopeErrorMessage;
					if (stackletScopeScriptIdx == MinitScript::SCRIPTIDX_NONE) {
						scopeErrorMessage = "Stacklet requires root scope";
					} else {
						scopeErrorMessage = "Stacklet requires scope of " + scripts[stackletScopeScriptIdx].condition + "()";
					}
					scopeErrorMessage+= ", but has scope of ";
					if (scopeScriptIdx == MinitScript::SCRIPTIDX_NONE) {
						scopeErrorMessage+= "root scope";
					} else {
						scopeErrorMessage+= scripts[scopeScriptIdx].condition + "()";
					}
					//
					Console::printLine(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": " +
						syntaxTreeNode.value.getValueAsString() +
						": Stacklet scope invalid: " +
						scopeErrorMessage
					);
					//
					parseErrors.push_back(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": " +
						syntaxTreeNode.value.getValueAsString() +
						": Stacklet scope invalid" +
						scopeErrorMessage
					);
					//
					return false;
				}
				//
				validateStacklets(minitScript, syntaxTreeNode.value.getValueAsString(), parseErrors, scopeScriptIdx);
				//
				break;
			}
		default:
			break;
	}
	//
	return true;
}

bool Validations::validateCallable(MinitScript* minitScript, const string& function, vector<string>& parseErrors) {
	auto functionScriptIdx = minitScript->getFunctionScriptIdx(function);
	if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
		Console::printLine("MinitScript::validateCallable(): function not found: " + function);
		return false;
	}
	//
	const auto& scripts = minitScript->getScripts();
	const auto& script = scripts[functionScriptIdx];
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateCallable(minitScript, syntaxTreeNode, statement, parseErrors) == false) {
			//
			return false;
		}
	}
	//
	return true;
}

bool Validations::validateCallable(MinitScript* minitScript, const MinitScript::SyntaxTreeNode& syntaxTreeNode, const MinitScript::Statement& statement, vector<string>& parseErrors) {
	//
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				const auto& contextFunctions = syntaxTreeNode.getMethod()->getContextFunctions();
				if (contextFunctions.empty() == false) {
					//
					Console::printLine(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": Method " +
						syntaxTreeNode.getMethod()->getMethodName() + "() can not be called within a callable function"
					);
					//
					parseErrors.push_back(
						minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
						": Method " +
						syntaxTreeNode.getMethod()->getMethodName() + "() can not be called within a callable function"
					);
					//
					return false;
				}
			}
			break;
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateCallable(minitScript, argument, statement, parseErrors) == false) return false;
				}
				//
				validateCallable(minitScript, syntaxTreeNode.value.getValueAsString(), parseErrors);
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
			{
				validateCallable(minitScript, syntaxTreeNode.value.getValueAsString(), parseErrors);
				//
				break;
			}
		default:
			break;
	}
	//
	return true;
}

bool Validations::validateContextFunctions(MinitScript* minitScript, const string& function, vector<string>& functionStack, vector<string>& parseErrors) {
	auto functionScriptIdx = minitScript->getFunctionScriptIdx(function);
	if (functionScriptIdx == MinitScript::SCRIPTIDX_NONE) {
		Console::printLine("MinitScript::validateContextFunctions(): Function not found: " + function);
		return false;
	}
	//
	const auto& scripts = minitScript->getScripts();
	const auto& script = scripts[functionScriptIdx];
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	//
	functionStack.push_back(script.condition);
	//
	for (const auto& syntaxTreeNode: script.syntaxTree) {
		const auto& statement = script.statements[statementIdx++];
		//
		if (validateContextFunctions(minitScript, syntaxTreeNode, functionStack, statement, parseErrors) == false) {
			//
			return false;
		}
	}
	//
	functionStack.erase(functionStack.begin() + functionStack.size() - 1);
	//
	return true;
}

bool Validations::validateContextFunctions(MinitScript* minitScript, const MinitScript::SyntaxTreeNode& syntaxTreeNode, vector<string>& functionStack, const MinitScript::Statement& statement, vector<string>& parseErrors) {
	//
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				const auto& contextFunctions = syntaxTreeNode.getMethod()->getContextFunctions();
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
						Console::printLine(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": Method " +
							syntaxTreeNode.getMethod()->getMethodName() + "() can only be called within the following functions: " +
							contextFunctionsString +
							", but was called from " +
							functionStackFunction + "()"
						);
						//
						parseErrors.push_back(
							minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
							": Method " +
							syntaxTreeNode.getMethod()->getMethodName() + "() can only be called within the following functions: " +
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
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
			{
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (validateContextFunctions(minitScript, argument, functionStack, statement, parseErrors) == false) return false;
				}
				//
				if (functionStack.back() != syntaxTreeNode.value.getValueAsString()) {
					validateContextFunctions(minitScript, syntaxTreeNode.value.getValueAsString(), functionStack, parseErrors);
				}
				//
				break;
			}
		default:
			break;
	}
	//
	return true;
}
