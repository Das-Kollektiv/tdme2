#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Setup.h>
#include <minitscript/utilities/Console.h>

using std::string;
using std::vector;

using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Setup;
using minitscript::utilities::Console;

bool Setup::setupFunctionAndStackletScriptIndices(MinitScript* minitScript, int scriptIdx, vector<string>& parseErrors) {
	//
	auto& scripts = minitScript->scripts;
	auto& script = scripts[scriptIdx];
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	//
	for (auto& syntaxTreeNode: script.syntaxTree) {
		auto& statement = script.statements[statementIdx++];
		//
		if (setupFunctionAndStackletScriptIndices(minitScript, syntaxTreeNode, statement, parseErrors) == false) {
			//
			return false;
		}
	}
	//
	return true;

}

bool Setup::setupFunctionAndStackletScriptIndices(MinitScript* minitScript, MinitScript::SyntaxTreeNode& syntaxTreeNode, const MinitScript::Statement& statement, vector<string>& parseErrors) {
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTreeNode.value.getType()) {
					case(MinitScript::TYPE_ARRAY):
					case(MinitScript::TYPE_MAP):
						{
							if (setupFunctionAndStackletScriptIndices(minitScript, syntaxTreeNode.value, statement, syntaxTreeNode.subLineIdx, parseErrors) == false) return false;
							//
							break;
						}
					case(MinitScript::TYPE_FUNCTION_ASSIGNMENT):
						{
							string function;
							auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
							if (syntaxTreeNode.value.getFunctionValue(function, functionScriptIdx) == false ||
								(functionScriptIdx = minitScript->getFunctionScriptIdx(function)) == MinitScript::SCRIPTIDX_NONE) {
								//
								Console::printLine(
									minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
									": Function not found: " +
									syntaxTreeNode.value.getValueAsString()
								);
								//
								parseErrors.push_back(
									minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
									": Function not found: " +
									syntaxTreeNode.value.getValueAsString()
								);
								//
								return false;
							}
							//
							syntaxTreeNode.value.setFunctionAssignment(function, functionScriptIdx);
							//
							break;
						}
					case(MinitScript::TYPE_STACKLET_ASSIGNMENT):
						{
							string stacklet;
							auto stackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
							if (syntaxTreeNode.value.getStackletValue(stacklet, stackletScriptIdx) == false ||
								(stackletScriptIdx = minitScript->getFunctionScriptIdx(stacklet)) == MinitScript::SCRIPTIDX_NONE) {
								//
								Console::printLine(
									minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
									": Stacklet not found" +
									syntaxTreeNode.value.getValueAsString()
								);
								//
								parseErrors.push_back(
									minitScript->getStatementInformation(statement, syntaxTreeNode.subLineIdx) +
									": Stacklet not found: " +
									syntaxTreeNode.value.getValueAsString()
								);
								//
								return false;
							}
							//
							syntaxTreeNode.value.setStackletAssignment(stacklet, stackletScriptIdx);
							//
							break;
						}
					default:
						break;
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (auto& argument: syntaxTreeNode.arguments) {
					if (setupFunctionAndStackletScriptIndices(minitScript, argument, statement, parseErrors) == false) return false;
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

bool Setup::setupFunctionAndStackletScriptIndices(MinitScript* minitScript, MinitScript::Variable& variable, const MinitScript::Statement& statement, int subLineIdx, vector<string>& parseErrors) {
	switch (variable.getType()) {
		case MinitScript::TYPE_ARRAY:
			{
				auto arrayPointer = variable.getArrayPointer();
				if (arrayPointer == nullptr) break;
				for (auto arrayEntry: *arrayPointer) {
					if (setupFunctionAndStackletScriptIndices(minitScript, *arrayEntry, statement, subLineIdx, parseErrors) == false) return false;
				}
				//
				break;
			}
		case MinitScript::TYPE_MAP:
			{
				//
				auto mapPointer = variable.getMapPointer();
				if (mapPointer == nullptr) break;
				for (auto& [mapKey, mapValue]: *mapPointer) {
					if (setupFunctionAndStackletScriptIndices(minitScript, *mapValue, statement, subLineIdx, parseErrors) == false) return false;
				}
				//
				break;
			}
		case MinitScript::TYPE_FUNCTION_ASSIGNMENT:
			{
				string function;
				auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
				if (variable.getFunctionValue(function, functionScriptIdx) == false ||
					(functionScriptIdx = minitScript->getFunctionScriptIdx(function)) == MinitScript::SCRIPTIDX_NONE) {
					//
					Console::printLine(
						minitScript->getStatementInformation(statement, subLineIdx) +
						": Function not found: " +
						variable.getValueAsString()
					);
					//
					parseErrors.push_back(
						minitScript->getStatementInformation(statement, subLineIdx) +
						": Function not found: " +
						variable.getValueAsString()
					);
					//
					return false;
				}
				//
				variable.setFunctionAssignment(function, functionScriptIdx);
				//
				break;
			}
		case MinitScript::TYPE_STACKLET_ASSIGNMENT:
			{
				string stacklet;
				auto stackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
				if (variable.getStackletValue(stacklet, stackletScriptIdx) == false ||
					(stackletScriptIdx = minitScript->getFunctionScriptIdx(stacklet)) == MinitScript::SCRIPTIDX_NONE) {
					//
					Console::printLine(
						minitScript->getStatementInformation(statement, subLineIdx) +
						": Stacklet not found" +
						variable.getValueAsString()
					);
					//
					parseErrors.push_back(
						minitScript->getStatementInformation(statement, subLineIdx) +
						": Stacklet not found: " +
						variable.getValueAsString()
					);
					//
					return false;
				}
				//
				variable.setStackletAssignment(stacklet, stackletScriptIdx);
				//
				break;
			}
		default: break;
	}
	//
	return true;
}
