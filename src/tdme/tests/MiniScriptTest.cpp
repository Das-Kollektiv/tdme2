#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

void MiniScriptTest::nothing(int miniScriptGotoStatementIdx) {
	/*__MINISCRIPT_TRANSPILED_NOTHING_START__*/
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 0;
	if (miniScriptGotoStatementIdx != 0) Console::println("MiniScript::initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));
	statement_0:
	// console.log("------------")
	{
		const MiniScript::ScriptStatement statement = {
			.line = 3, 
			.statementIdx = 0, 
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		vector<ScriptVariable> argumentValues;
		vector<ScriptVariable>& argumentValuesD0 = argumentValues;
		argumentValues.push_back(MiniScript::ScriptVariable(string("------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
	}
	while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
	statement_1:
	// console.log("Initialize")
	{
		const MiniScript::ScriptStatement statement = {
			.line = 4, 
			.statementIdx = 1, 
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		vector<ScriptVariable> argumentValues;
		vector<ScriptVariable>& argumentValuesD0 = argumentValues;
		argumentValues.push_back(MiniScript::ScriptVariable(string("Initialize")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
	}
	while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
	statement_2:
	// console.log("------------")
	{
		const MiniScript::ScriptStatement statement = {
			.line = 5, 
			.statementIdx = 2, 
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		vector<ScriptVariable> argumentValues;
		vector<ScriptVariable>& argumentValuesD0 = argumentValues;
		argumentValues.push_back(MiniScript::ScriptVariable(string("------------")));
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
	}
	while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
	statement_3:
	// console.log()
	{
		const MiniScript::ScriptStatement statement = {
			.line = 6, 
			.statementIdx = 3, 
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		vector<ScriptVariable> argumentValues;
		vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					for (auto& argumentValue: argumentValues) {
						Console::print(argumentValue.getValueString());
					}
					Console::println();
	}
	while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();
	statement_4:
	// end()
	{
		const MiniScript::ScriptStatement statement = {
			.line = 7, 
			.statementIdx = 4, 
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		vector<ScriptVariable> argumentValues;
		vector<ScriptVariable>& argumentValuesD0 = argumentValues;
					if (miniScript->scriptState.endTypeStack.empty() == true) {
						if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
							Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
							miniScript->startErrorScript();
						}
					} else {
						auto endType = miniScript->scriptState.endTypeStack.top();
						miniScript->scriptState.endTypeStack.pop();
						switch(endType) {
							case ScriptState::ENDTYPE_FOR:
								// no op
								break;
							case ScriptState::ENDTYPE_IF:
								miniScript->scriptState.conditionStack.pop();
								break;
						}
						if (statement.gotoStatementIdx != STATE_NONE) {
							miniScript->setScriptState(STATE_NEXT_STATEMENT);
						}
					}
	}
	while (scriptState.state.state != STATE_NEXT_STATEMENT) miniScript->executeStateMachine();

	/*__MINISCRIPT_TRANSPILED_NOTHING_END__*/
}
