#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/
MiniScriptTest::MiniScriptTest(): MiniScript() {
	setNative(true);
}

int MiniScriptTest::determineScriptIdxToStart() {
	auto miniScript = this;

	//
	return 1;
}

int MiniScriptTest::determineNamedScriptIdxToStart() {
	auto miniScript = this;
	for (auto& enabledConditionName: scriptState.enabledConditionNames) {

		// next statements belong to tested enabled named condition with name "named_condition_1"
		if (enabledConditionName == "named_condition_1")
		// equals(1, 1)
		{
			// required method code arguments
			const MiniScript::ScriptStatement statement = {
				.line = 182,
				.statementIdx = 0,
				.statement = "<unavailable>",
				.gotoStatementIdx = -1
			};
			miniScript->scriptState.statementIdx = statement.statementIdx;
			ScriptVariable returnValue;
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(1));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
			bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return 4;
		}
	}

	//
	return -1;
}

void MiniScriptTest::emit(const string& condition) {
	if (condition == "initialize") {
		on_initialize(-1);
		return;
	}
	if (condition == "nothing") {
		on_nothing(-1);
		return;
	}
	if (condition == "error") {
		on_error(-1);
		return;
	}
	if (condition == "emittest") {
		on_emittest(-1);
		return;
	}
}

void MiniScriptTest::on_initialize(int miniScriptGotoStatementIdx) {
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(0, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 0;
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_initialize(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 0
	miniscript_statement_0:
	// console.log("------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 3,
			.statementIdx = 0,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 1
	miniscript_statement_1:
	// console.log("Initialize")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 4,
			.statementIdx = 1,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Initialize"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 2
	miniscript_statement_2:
	// console.log("------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 5,
			.statementIdx = 2,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 3
	miniscript_statement_3:
	// console.log()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 6,
			.statementIdx = 3,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 4
	miniscript_statement_4:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 7,
			.statementIdx = 4,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_nothing(int miniScriptGotoStatementIdx) {
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(1, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 1;
	if (miniScriptGotoStatementIdx == 103) goto miniscript_statement_103; else
	if (miniScriptGotoStatementIdx == 105) goto miniscript_statement_105; else
	if (miniScriptGotoStatementIdx == 107) goto miniscript_statement_107; else
	if (miniScriptGotoStatementIdx == 112) goto miniscript_statement_112; else
	if (miniScriptGotoStatementIdx == 114) goto miniscript_statement_114; else
	if (miniScriptGotoStatementIdx == 116) goto miniscript_statement_116; else
	if (miniScriptGotoStatementIdx == 122) goto miniscript_statement_122; else
	if (miniScriptGotoStatementIdx == 124) goto miniscript_statement_124; else
	if (miniScriptGotoStatementIdx == 126) goto miniscript_statement_126; else
	if (miniScriptGotoStatementIdx == 128) goto miniscript_statement_128; else
	if (miniScriptGotoStatementIdx == 130) goto miniscript_statement_130; else
	if (miniScriptGotoStatementIdx == 132) goto miniscript_statement_132; else
	if (miniScriptGotoStatementIdx == 134) goto miniscript_statement_134; else
	if (miniScriptGotoStatementIdx == 136) goto miniscript_statement_136; else
	if (miniScriptGotoStatementIdx == 140) goto miniscript_statement_140; else
	if (miniScriptGotoStatementIdx == 142) goto miniscript_statement_142; else
	if (miniScriptGotoStatementIdx == 151) goto miniscript_statement_151; else
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_nothing(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 0
	miniscript_statement_0:
	// console.log("---------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 11,
			.statementIdx = 0,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 1
	miniscript_statement_1:
	// console.log("Nothing")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 12,
			.statementIdx = 1,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Nothing"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 2
	miniscript_statement_2:
	// console.log("----------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 13,
			.statementIdx = 2,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 3
	miniscript_statement_3:
	// console.log()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 14,
			.statementIdx = 3,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 4
	miniscript_statement_4:
	// console.log("-----------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 15,
			.statementIdx = 4,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 5
	miniscript_statement_5:
	// console.log("Check bool operations")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 16,
			.statementIdx = 5,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check bool operations"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 6
	miniscript_statement_6:
	// console.log("-----------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 17,
			.statementIdx = 6,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 7
	miniscript_statement_7:
	// console.log("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): ", and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 18,
			.statementIdx = 7,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("MiniScript will do the job: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true): "));
		// argumentValues[1] --> returnValue of and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
		// depth = 1 / argument index = 1: and(or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will)), true)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
			argumentValues[1].setValue(true);
			// depth = 2 / argument index = 0: or(equals(MiniScript will do the job, MiniScript will not do the job), equals(it will, it will))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of equals(MiniScript will do the job, MiniScript will not do the job)
				// argumentValues[1] --> returnValue of equals(it will, it will)
				// depth = 3 / argument index = 0: equals(MiniScript will do the job, MiniScript will not do the job)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("MiniScript will do the job"));
					argumentValues[1].setValue(string("MiniScript will not do the job"));
					// method code: equals
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
				// depth = 3 / argument index = 1: equals(it will, it will)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("it will"));
					argumentValues[1].setValue(string("it will"));
					// method code: equals
					returnValue.setValue(true);
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
							returnValue.setValue(false);
							break;
						}
					}
				}
				// method code: or
				returnValue.setValue(false);
				for (auto i = 0; i < argumentValues.size(); i++) {
					bool booleanValue;
					if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
						Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
						miniScript->startErrorScript(); return;
					} else
					if (booleanValue == true) {
						returnValue.setValue(true);
						break;
					}
				}
			}
			// method code: and
			returnValue.setValue(true);
			for (auto i = 0; i < argumentValues.size(); i++) {
				bool booleanValue;
				if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
					Console::println("ScriptMethodAnd::executeMethod(): " + string("and") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
					miniScript->startErrorScript(); return;
				} else
				if (booleanValue == false) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 8
	miniscript_statement_8:
	// console.log("-----------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 19,
			.statementIdx = 8,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 9
	miniscript_statement_9:
	// console.log("Check int computation")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 20,
			.statementIdx = 9,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check int computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 10
	miniscript_statement_10:
	// console.log("-----------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 21,
			.statementIdx = 10,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 11
	miniscript_statement_11:
	// console.log("sub(add(1, 2, 3), 1)): ", sub(add(1, 2, 3), 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 22,
			.statementIdx = 11,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(1, 2, 3), 1)): "));
		// argumentValues[1] --> returnValue of sub(add(1, 2, 3), 1)
		// depth = 1 / argument index = 1: sub(add(1, 2, 3), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1, 2, 3)
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: add(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 12
	miniscript_statement_12:
	// console.log("div(20, 2): ", div(20, 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 23,
			.statementIdx = 12,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(20, 2): "));
		// argumentValues[1] --> returnValue of div(20, 2)
		// depth = 1 / argument index = 1: div(20, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 13
	miniscript_statement_13:
	// console.log("mul(11, 10): ", mul(11, 10))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 24,
			.statementIdx = 13,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(11, 10): "));
		// argumentValues[1] --> returnValue of mul(11, 10)
		// depth = 1 / argument index = 1: mul(11, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(11));
			argumentValues[1].setValue(static_cast<int64_t>(10));
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 14
	miniscript_statement_14:
	// console.log("greater(2, 1): ", greater(2, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 25,
			.statementIdx = 14,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("greater(2, 1): "));
		// argumentValues[1] --> returnValue of greater(2, 1)
		// depth = 1 / argument index = 1: greater(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 15
	miniscript_statement_15:
	// console.log("lesser(2, 1): ", lesser(2, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 26,
			.statementIdx = 15,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("lesser(2, 1): "));
		// argumentValues[1] --> returnValue of lesser(2, 1)
		// depth = 1 / argument index = 1: lesser(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 16
	miniscript_statement_16:
	// console.log("---------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 27,
			.statementIdx = 16,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 17
	miniscript_statement_17:
	// console.log("Check int computation (Operators)")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 28,
			.statementIdx = 17,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check int computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 18
	miniscript_statement_18:
	// console.log("---------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 29,
			.statementIdx = 18,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 19
	miniscript_statement_19:
	// console.log("1 + 2 + 3 - 1: ", sub(add(1,add(2, 3)), 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 30,
			.statementIdx = 19,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("1 + 2 + 3 - 1: "));
		// argumentValues[1] --> returnValue of sub(add(1,add(2, 3)), 1)
		// depth = 1 / argument index = 1: sub(add(1,add(2, 3)), 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1,add(2, 3))
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: add(1, add(2, 3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				// argumentValues[1] --> returnValue of add(2, 3)
				// depth = 3 / argument index = 1: add(2, 3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(static_cast<int64_t>(2));
					argumentValues[1].setValue(static_cast<int64_t>(3));
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						Vector3 result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result+= vec3Value;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						float result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= floatValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else {
						int64_t result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result+= intValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 20
	miniscript_statement_20:
	// console.log("20 / 2: ", div(20, 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 31,
			.statementIdx = 20,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("20 / 2: "));
		// argumentValues[1] --> returnValue of div(20, 2)
		// depth = 1 / argument index = 1: div(20, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 21
	miniscript_statement_21:
	// console.log("11 * 10: ", mul(11, 10))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 32,
			.statementIdx = 21,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("11 * 10: "));
		// argumentValues[1] --> returnValue of mul(11, 10)
		// depth = 1 / argument index = 1: mul(11, 10)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(11));
			argumentValues[1].setValue(static_cast<int64_t>(10));
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 22
	miniscript_statement_22:
	// console.log("2 > 1: ", greater(2, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 33,
			.statementIdx = 22,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2 > 1: "));
		// argumentValues[1] --> returnValue of greater(2, 1)
		// depth = 1 / argument index = 1: greater(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 23
	miniscript_statement_23:
	// console.log("2 < 1: ", lesser(2, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 34,
			.statementIdx = 23,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2 < 1: "));
		// argumentValues[1] --> returnValue of lesser(2, 1)
		// depth = 1 / argument index = 1: lesser(2, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 24
	miniscript_statement_24:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 35,
			.statementIdx = 24,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 25
	miniscript_statement_25:
	// console.log("Check float computation")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 36,
			.statementIdx = 25,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check float computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 26
	miniscript_statement_26:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 37,
			.statementIdx = 26,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 27
	miniscript_statement_27:
	// console.log("sub(add(1.1, 2.2, 3.3), 1.2)): ", sub(add(1.1, 2.2, 3.3), 1.2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 38,
			.statementIdx = 27,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(1.1, 2.2, 3.3), 1.2)): "));
		// argumentValues[1] --> returnValue of sub(add(1.1, 2.2, 3.3), 1.2)
		// depth = 1 / argument index = 1: sub(add(1.1, 2.2, 3.3), 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1.1, 2.2, 3.3)
			argumentValues[1].setValue(1.200000f);
			// depth = 2 / argument index = 0: add(1.1, 2.2, 3.3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				argumentValues[2].setValue(3.300000f);
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 28
	miniscript_statement_28:
	// console.log("div(20, 1.5): ", div(20, 1.5))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 39,
			.statementIdx = 28,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(20, 1.5): "));
		// argumentValues[1] --> returnValue of div(20, 1.5)
		// depth = 1 / argument index = 1: div(20, 1.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(1.500000f);
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 29
	miniscript_statement_29:
	// console.log("mul(11.5, 10.5): ", mul(11.5, 10.5))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 40,
			.statementIdx = 29,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(11.5, 10.5): "));
		// argumentValues[1] --> returnValue of mul(11.5, 10.5)
		// depth = 1 / argument index = 1: mul(11.5, 10.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(11.500000f);
			argumentValues[1].setValue(10.500000f);
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 30
	miniscript_statement_30:
	// console.log("greater(2.2, 1.3): ", greater(2.2, 1.3))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 41,
			.statementIdx = 30,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("greater(2.2, 1.3): "));
		// argumentValues[1] --> returnValue of greater(2.2, 1.3)
		// depth = 1 / argument index = 1: greater(2.2, 1.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.200000f);
			argumentValues[1].setValue(1.300000f);
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 31
	miniscript_statement_31:
	// console.log("lesser(2.5, 1.2): ", lesser(2.5, 1.2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 42,
			.statementIdx = 31,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("lesser(2.5, 1.2): "));
		// argumentValues[1] --> returnValue of lesser(2.5, 1.2)
		// depth = 1 / argument index = 1: lesser(2.5, 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.500000f);
			argumentValues[1].setValue(1.200000f);
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 32
	miniscript_statement_32:
	// console.log("-----------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 43,
			.statementIdx = 32,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 33
	miniscript_statement_33:
	// console.log("Check float computation (Operators)")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 44,
			.statementIdx = 33,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check float computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 34
	miniscript_statement_34:
	// console.log("-----------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 45,
			.statementIdx = 34,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 35
	miniscript_statement_35:
	// console.log("(1.1 + 2.2 + 3.3) - 1.2: ", sub(add(1.1,add(2.2, 3.3)), 1.2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 46,
			.statementIdx = 35,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("(1.1 + 2.2 + 3.3) - 1.2: "));
		// argumentValues[1] --> returnValue of sub(add(1.1,add(2.2, 3.3)), 1.2)
		// depth = 1 / argument index = 1: sub(add(1.1,add(2.2, 3.3)), 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(1.1,add(2.2, 3.3))
			argumentValues[1].setValue(1.200000f);
			// depth = 2 / argument index = 0: add(1.1, add(2.2, 3.3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				// argumentValues[1] --> returnValue of add(2.2, 3.3)
				// depth = 3 / argument index = 1: add(2.2, 3.3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(2.200000f);
					argumentValues[1].setValue(3.300000f);
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						Vector3 result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result+= vec3Value;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						float result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= floatValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else {
						int64_t result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result+= intValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 36
	miniscript_statement_36:
	// console.log("20 / 1.5: ", div(20, 1.5))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 47,
			.statementIdx = 36,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("20 / 1.5: "));
		// argumentValues[1] --> returnValue of div(20, 1.5)
		// depth = 1 / argument index = 1: div(20, 1.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(20));
			argumentValues[1].setValue(1.500000f);
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 37
	miniscript_statement_37:
	// console.log("11.5 * 10.5: ", mul(11.5, 10.5))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 48,
			.statementIdx = 37,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("11.5 * 10.5: "));
		// argumentValues[1] --> returnValue of mul(11.5, 10.5)
		// depth = 1 / argument index = 1: mul(11.5, 10.5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(11.500000f);
			argumentValues[1].setValue(10.500000f);
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 38
	miniscript_statement_38:
	// console.log("2.2 > 1.3: ", greater(2.2, 1.3))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 49,
			.statementIdx = 38,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2.2 > 1.3: "));
		// argumentValues[1] --> returnValue of greater(2.2, 1.3)
		// depth = 1 / argument index = 1: greater(2.2, 1.3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.200000f);
			argumentValues[1].setValue(1.300000f);
			// method code: greater
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA > floatValueB);
			} else {
				Console::println("ScriptMethodFGreater::executeMethod(): " + string("greater") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 39
	miniscript_statement_39:
	// console.log("2.5 < 1.2: ", lesser(2.5, 1.2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 50,
			.statementIdx = 39,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("2.5 < 1.2: "));
		// argumentValues[1] --> returnValue of lesser(2.5, 1.2)
		// depth = 1 / argument index = 1: lesser(2.5, 1.2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(2.500000f);
			argumentValues[1].setValue(1.200000f);
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 40
	miniscript_statement_40:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 51,
			.statementIdx = 40,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 41
	miniscript_statement_41:
	// console.log("Check vector3 computation")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 52,
			.statementIdx = 41,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector3 computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 42
	miniscript_statement_42:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 53,
			.statementIdx = 42,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 43
	miniscript_statement_43:
	// console.log("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): ", sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 54,
			.statementIdx = 43,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))): "));
		// argumentValues[1] --> returnValue of sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
		// depth = 1 / argument index = 1: sub(add(vec3(1.1, 2.2, 3.3)), vec3(1.2, 1.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of add(vec3(1.1, 2.2, 3.3))
			// argumentValues[1] --> returnValue of vec3(1.2, 1.0, 1.0)
			// depth = 2 / argument index = 0: add(vec3(1.1, 2.2, 3.3))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of vec3(1.1, 2.2, 3.3)
				// depth = 3 / argument index = 0: vec3(1.1, 2.2, 3.3)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 3> argumentValues;
					array<ScriptVariable, 3>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(1.100000f);
					argumentValues[1].setValue(2.200000f);
					argumentValues[2].setValue(3.300000f);
					// method code: vec3
					Vector3 result;
					float xValue;
					float yValue;
					float zValue;
					if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
						MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
						returnValue.setValue(Vector3(xValue, yValue, zValue));
					} else {
						Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// depth = 2 / argument index = 1: vec3(1.2, 1.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.200000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(1.000000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 44
	miniscript_statement_44:
	// console.log("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 55,
			.statementIdx = 44,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 45
	miniscript_statement_45:
	// console.log("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 56,
			.statementIdx = 45,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 46
	miniscript_statement_46:
	// console.log("div(vec3(20, 10, 5), 2): ", div(vec3(20, 10, 5), 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 57,
			.statementIdx = 46,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("div(vec3(20, 10, 5), 2): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 47
	miniscript_statement_47:
	// console.log("mul(vec3(20, 10, 5), 2): ", mul(vec3(20, 10, 5), 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 58,
			.statementIdx = 47,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("mul(vec3(20, 10, 5), 2): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 48
	miniscript_statement_48:
	// console.log("vec3.computeLength(vec3(20, 10, 5)): ", vec3.computeLength(vec3(20, 10, 5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 59,
			.statementIdx = 48,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeLength(vec3(20, 10, 5)): "));
		// argumentValues[1] --> returnValue of vec3.computeLength(vec3(20, 10, 5))
		// depth = 1 / argument index = 1: vec3.computeLength(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLength
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLength());
			} else {
				Console::println("ScriptMethodVec3ComputeLength::executeMethod(): " + string("vec3.computeLength") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 49
	miniscript_statement_49:
	// console.log("vec3.computeLengthSquared(vec3(20, 10, 5)): ", vec3.computeLengthSquared(vec3(20, 10, 5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 60,
			.statementIdx = 49,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeLengthSquared(vec3(20, 10, 5)): "));
		// argumentValues[1] --> returnValue of vec3.computeLengthSquared(vec3(20, 10, 5))
		// depth = 1 / argument index = 1: vec3.computeLengthSquared(vec3(20, 10, 5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeLengthSquared
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.computeLengthSquared());
			} else {
				Console::println("ScriptMethodVec3ComputeLengthSquared::executeMethod(): " + string("vec3.computeLengthSquared") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 50
	miniscript_statement_50:
	// console.log("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): ", vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 61,
			.statementIdx = 50,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1)): "));
		// argumentValues[1] --> returnValue of vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		// depth = 1 / argument index = 1: vec3.computeDotProduct(vec3(0, 0, 1), vec3(0, 0, -1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0, 0, 1)
			// argumentValues[1] --> returnValue of vec3(0, 0, -1)
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, -1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(-1));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeDotProduct
			Vector3 a;
			Vector3 b;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector3::computeDotProduct(a, b));
			} else {
				Console::println("ScriptMethodVec3ComputeDotProduct::executeMethod(): " + string("vec3.computeDotProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 51
	miniscript_statement_51:
	// console.log("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 62,
			.statementIdx = 51,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0)): "));
		// argumentValues[1] --> returnValue of vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: vec3.computeCrossProduct(vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 0, 0)
			// argumentValues[1] --> returnValue of vec3(0, 1, 0)
			// depth = 2 / argument index = 0: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeCrossProduct
			Vector3 a;
			Vector3 b;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true) {
				returnValue.setValue(Vector3::computeCrossProduct(a, b));
			} else {
				Console::println("ScriptMethodVec3ComputeCrossProduct::executeMethod(): " + string("vec3.computeCrossProduct") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 52
	miniscript_statement_52:
	// console.log("vec3.normalize(vec3(1, 2, 3)): ", vec3.normalize(vec3(1, 2, 3)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 63,
			.statementIdx = 52,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.normalize(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.normalize(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.normalize(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.normalize
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.normalize());
			} else {
				Console::println("ScriptMethodVec3Normalize::executeMethod(): " + string("vec3.normalize") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 53
	miniscript_statement_53:
	// console.log("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): ", vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 64,
			.statementIdx = 53,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0)): "));
		// argumentValues[1] --> returnValue of vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: vec3.computeAngle(vec3(0, 0, 1), vec3(1, 0, 0), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(0, 0, 1)
			// argumentValues[1] --> returnValue of vec3(1, 0, 0)
			// argumentValues[2] --> returnValue of vec3(0, 1, 0)
			// depth = 2 / argument index = 0: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 2: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX2 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.computeAngle
			Vector3 a;
			Vector3 b;
			Vector3 n;
			if (MiniScript::getVector3Value(argumentValues, 0, a, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, b, false) == true &&
				MiniScript::getVector3Value(argumentValues, 2, n, false) == true) {
				returnValue.setValue(Vector3::computeAngle(a, b, n));
			} else {
				Console::println("ScriptMethodVec3ComputeAngle::executeMethod(): " + string("vec3.computeAngle") + "(): parameter type mismatch @ argument 0: vector3 expected, @ argument 1: vector3 expected @ argument 2: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 54
	miniscript_statement_54:
	// console.log("vec3.getX(vec3(1, 2, 3)): ", vec3.getX(vec3(1, 2, 3)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 65,
			.statementIdx = 54,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getX(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getX(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getX(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getX
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getX());
			} else {
				Console::println("ScriptMethodVec3GetX::executeMethod(): " + string("vec3.getX") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 55
	miniscript_statement_55:
	// console.log("vec3.getY(vec3(1, 2, 3)): ", vec3.getY(vec3(1, 2, 3)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 66,
			.statementIdx = 55,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getY(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getY(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getY(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getY
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getY());
			} else {
				Console::println("ScriptMethodVec3GetY::executeMethod(): " + string("vec3.getY") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 56
	miniscript_statement_56:
	// console.log("vec3.getZ(vec3(1, 2, 3)): ", vec3.getZ(vec3(1, 2, 3)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 67,
			.statementIdx = 56,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3.getZ(vec3(1, 2, 3)): "));
		// argumentValues[1] --> returnValue of vec3.getZ(vec3(1, 2, 3))
		// depth = 1 / argument index = 1: vec3.getZ(vec3(1, 2, 3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1, 2, 3)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: vec3.getZ
			Vector3 vec3;
			if (MiniScript::getVector3Value(argumentValues, 0, vec3, false) == true) {
				returnValue.setValue(vec3.getZ());
			} else {
				Console::println("ScriptMethodVec3GetZ::executeMethod(): " + string("vec3.getZ") + "(): parameter type mismatch @ argument 0: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 57
	miniscript_statement_57:
	// console.log("-------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 68,
			.statementIdx = 57,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 58
	miniscript_statement_58:
	// console.log("Check vector3 computation (Operators)")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 69,
			.statementIdx = 58,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check vector3 computation (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 59
	miniscript_statement_59:
	// console.log("-------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 70,
			.statementIdx = 59,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 60
	miniscript_statement_60:
	// console.log("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): ", sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 71,
			.statementIdx = 60,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(1.1, 2.2, 3.3) - vec3(1.2, 1.0, 1.0): "));
		// argumentValues[1] --> returnValue of sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
		// depth = 1 / argument index = 1: sub(vec3(1.1, 2.2, 3.3), vec3(1.2, 1.0, 1.0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1.1, 2.2, 3.3)
			// argumentValues[1] --> returnValue of vec3(1.2, 1.0, 1.0)
			// depth = 2 / argument index = 0: vec3(1.1, 2.2, 3.3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(1.100000f);
				argumentValues[1].setValue(2.200000f);
				argumentValues[2].setValue(3.300000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.2, 1.0, 1.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.200000f);
				argumentValues[1].setValue(1.000000f);
				argumentValues[2].setValue(1.000000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: sub
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result-= vec3Value;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							break;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				bool valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result-= floatValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				bool valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result-= intValue;
						} else {
							Console::println("ScriptMethodSub::executeMethod(): " + string("sub") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 61
	miniscript_statement_61:
	// console.log("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): ", div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 72,
			.statementIdx = 61,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) / vec3(1.5, 2.5, 3.5): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 62
	miniscript_statement_62:
	// console.log("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): ", mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 73,
			.statementIdx = 62,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) * vec3(1.5, 2.5, 3.5)): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), vec3(1.5, 2.5, 3.5))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			// argumentValues[1] --> returnValue of vec3(1.5, 2.5, 3.5)
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(1.5, 2.5, 3.5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(1.500000f);
				argumentValues[1].setValue(2.500000f);
				argumentValues[2].setValue(3.500000f);
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 63
	miniscript_statement_63:
	// console.log("vec3(20, 10, 5) / 2): ", div(vec3(20, 10, 5), 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 74,
			.statementIdx = 63,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) / 2): "));
		// argumentValues[1] --> returnValue of div(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: div(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: div
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result/= vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result/= floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result/= intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 64
	miniscript_statement_64:
	// console.log("vec3(20, 10, 5) * 2): ", mul(vec3(20, 10, 5), 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 75,
			.statementIdx = 64,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("vec3(20, 10, 5) * 2): "));
		// argumentValues[1] --> returnValue of mul(vec3(20, 10, 5), 2)
		// depth = 1 / argument index = 1: mul(vec3(20, 10, 5), 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(20, 10, 5)
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: vec3(20, 10, 5)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(20));
				argumentValues[1].setValue(static_cast<int64_t>(10));
				argumentValues[2].setValue(static_cast<int64_t>(5));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: mul
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				auto valid = true;
				Vector3 result;
				if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
					Vector3 vec3Value;
					if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
						result = vec3Value;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				} else {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = Vector3(floatValue, floatValue, floatValue);
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result*= vec3Value;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								break;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
					}
					returnValue.setValue(result);
				}
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				auto valid = true;
				float result = 0.0f;
				{
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
						result = floatValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result*= floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			} else {
				auto valid = true;
				int64_t result = 0LL;
				{
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
						result = intValue;
					} else {
						Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
						miniScript->startErrorScript(); return;
						valid = false;
					}
				}
				if (valid == true) {
					for (auto i = 1; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result*= intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
							break;
						}
					}
					returnValue.setValue(result);
				}
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 65
	miniscript_statement_65:
	// console.log("-----------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 76,
			.statementIdx = 65,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 66
	miniscript_statement_66:
	// console.log("Check transformations computation")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 77,
			.statementIdx = 66,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check transformations computation"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 67
	miniscript_statement_67:
	// console.log("-----------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 78,
			.statementIdx = 67,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 68
	miniscript_statement_68:
	// setVariable("$transformations", transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 79,
			.statementIdx = 68,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transformations"));
		// argumentValues[1] --> returnValue of transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
		// depth = 1 / argument index = 1: transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of vec3(1,2,3)
			// argumentValues[1] --> returnValue of vec3(2, 3, 4)
			// argumentValues[2] --> returnValue of vec3(0, 1, 0)
			// depth = 2 / argument index = 0: vec3(1, 2, 3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(1));
				argumentValues[1].setValue(static_cast<int64_t>(2));
				argumentValues[2].setValue(static_cast<int64_t>(3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(2, 3, 4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(2));
				argumentValues[1].setValue(static_cast<int64_t>(3));
				argumentValues[2].setValue(static_cast<int64_t>(4));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 2: vec3(0, 1, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[2];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX2 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(1));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations
			Transformations transformations;
			Vector3 vec3Value;
			if (argumentValues.size() >= 1) {
				if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, true) == true) {
					transformations.setTranslation(vec3Value);
				} else {
					Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument 0: vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			if (argumentValues.size() >= 2) {
				if (MiniScript::getVector3Value(argumentValues, 1, vec3Value, true) == true) {
					transformations.setScale(vec3Value);
				} else {
					Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument 1: vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			for (auto i = 2; i < argumentValues.size(); i++) {
				if (MiniScript::getVector3Value(argumentValues, i, vec3Value, true) == true) {
					transformations.addRotation(vec3Value, 0.0f);
				} else {
					Console::println("ScriptMethodTransformations::executeMethod(): " + string("transformations") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
					miniScript->startErrorScript(); return;
				}
			}
			transformations.update();
			returnValue.setValue(transformations);
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 69
	miniscript_statement_69:
	// setVariable("$transformations", transformations.setRotationAngle($transformations, 0, 90))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 80,
			.statementIdx = 69,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$transformations"));
		// argumentValues[1] --> returnValue of transformations.setRotationAngle($transformations, 0, 90)
		// depth = 1 / argument index = 1: transformations.setRotationAngle($transformations, 0, 90)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			argumentValues[2].setValue(static_cast<int64_t>(90));
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.setRotationAngle
			int64_t idx;
			Transformations transformations;
			float angle;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
				if (idx < transformations.getRotationCount()) {
					transformations.setRotationAngle(idx, angle);
					transformations.update();
					returnValue.setValue(transformations);
				} else {
					Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected, @ argument 2: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 70
	miniscript_statement_70:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): ", $transformations)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 81,
			.statementIdx = 70,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)): "));
		// argumentValues[1] --> returnValue of getVariable("$transformations")
		// depth = 1 / argument index = 1: getVariable("$transformations")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$transformations"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 71
	miniscript_statement_71:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): ", transformations.getTranslation($transformations))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 82,
			.statementIdx = 71,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getTranslation(): "));
		// argumentValues[1] --> returnValue of transformations.getTranslation($transformations)
		// depth = 1 / argument index = 1: transformations.getTranslation($transformations)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.getTranslation
			Transformations transformations;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
				returnValue.setValue(transformations.getTranslation());
			} else {
				Console::println("ScriptMethodTransformationsGetTranslation::executeMethod(): " + string("transformations.getTranslation") + "(): parameter type mismatch @ argument 0: transformations expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 72
	miniscript_statement_72:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): ", transformations.setTranslation($transformations, vec3(-1,-2,-3)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 83,
			.statementIdx = 72,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setTranslation(vec3(-1,-2,-3)): "));
		// argumentValues[1] --> returnValue of transformations.setTranslation($transformations, vec3(-1,-2,-3))
		// depth = 1 / argument index = 1: transformations.setTranslation($transformations, vec3(-1,-2,-3))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// argumentValues[1] --> returnValue of vec3(-1,-2,-3)
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(-1, -2, -3)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(-1));
				argumentValues[1].setValue(static_cast<int64_t>(-2));
				argumentValues[2].setValue(static_cast<int64_t>(-3));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.setTranslation
			Transformations transformations;
			Vector3 translation;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, translation, false) == true) {
				transformations.setTranslation(translation);
				transformations.update();
				returnValue.setValue(transformations);
			} else {
				Console::println("ScriptMethodTransformationsSetTranslation::executeMethod(): " + string("transformations.setTranslation") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 73
	miniscript_statement_73:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): ", transformations.getScale($transformations))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 84,
			.statementIdx = 73,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getScale(): "));
		// argumentValues[1] --> returnValue of transformations.getScale($transformations)
		// depth = 1 / argument index = 1: transformations.getScale($transformations)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.getScale
			Transformations transformations;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true) {
				returnValue.setValue(transformations.getScale());
			} else {
				Console::println("ScriptMethodTransformationsGetScale::executeMethod(): " + string("transformations.getScale") + "(): parameter type mismatch @ argument 0: transformations expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 74
	miniscript_statement_74:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): ", transformations.setScale($transformations, vec3(-2,-3,-4)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 85,
			.statementIdx = 74,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setScale(): "));
		// argumentValues[1] --> returnValue of transformations.setScale($transformations, vec3(-2,-3,-4))
		// depth = 1 / argument index = 1: transformations.setScale($transformations, vec3(-2,-3,-4))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// argumentValues[1] --> returnValue of vec3(-2,-3,-4)
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(-2, -3, -4)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(-2));
				argumentValues[1].setValue(static_cast<int64_t>(-3));
				argumentValues[2].setValue(static_cast<int64_t>(-4));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.setScale
			Transformations transformations;
			Vector3 scale;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, scale, false) == true) {
				transformations.setScale(scale);
				transformations.update();
				returnValue.setValue(transformations);
			} else {
				Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.setScale") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 75
	miniscript_statement_75:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): ", transformations.getRotationAxis($transformations, 0))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 86,
			.statementIdx = 75,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAxis(): "));
		// argumentValues[1] --> returnValue of transformations.getRotationAxis($transformations, 0)
		// depth = 1 / argument index = 1: transformations.getRotationAxis($transformations, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.getRotationAxis
			int64_t idx;
			Transformations transformations;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
				if (idx < transformations.getRotationCount()) {
					returnValue.setValue(transformations.getRotationAxis(idx));
				} else {
					Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + string("transformations.getRotationAxis") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformationsGetRotationAxis::executeMethod(): " + string("transformations.getRotationAxis") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 76
	miniscript_statement_76:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): ", transformations.getRotationAngle($transformations, 0))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 87,
			.statementIdx = 76,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).getRotationAngle(): "));
		// argumentValues[1] --> returnValue of transformations.getRotationAngle($transformations, 0)
		// depth = 1 / argument index = 1: transformations.getRotationAngle($transformations, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.getRotationAngle
			int64_t idx;
			Transformations transformations;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true) {
				if (idx < transformations.getRotationCount()) {
					returnValue.setValue(transformations.getRotationAngle(idx));
				} else {
					Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + string("transformations.getRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformationsGetRotationAngle::executeMethod(): " + string("transformations.getRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 77
	miniscript_statement_77:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): ", transformations.setRotationAngle($transformations, 0, 90))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 88,
			.statementIdx = 77,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).setRotationAngle(): "));
		// argumentValues[1] --> returnValue of transformations.setRotationAngle($transformations, 0, 90)
		// depth = 1 / argument index = 1: transformations.setRotationAngle($transformations, 0, 90)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			argumentValues[2].setValue(static_cast<int64_t>(90));
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.setRotationAngle
			int64_t idx;
			Transformations transformations;
			float angle;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getIntegerValue(argumentValues, 1, idx, false) == true &&
				MiniScript::getFloatValue(argumentValues, 2, angle, false) == true) {
				if (idx < transformations.getRotationCount()) {
					transformations.setRotationAngle(idx, angle);
					transformations.update();
					returnValue.setValue(transformations);
				} else {
					Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): rotation index invalid: " + to_string(idx) + " / " + to_string(transformations.getRotationCount()));
					miniScript->startErrorScript(); return;
				}
			} else {
				Console::println("ScriptMethodTransformationsSetRotationAngle::executeMethod(): " + string("transformations.setRotationAngle") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: integer expected, @ argument 2: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 78
	miniscript_statement_78:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): ", transformations.multiply($transformations, vec3(0,0,0)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 89,
			.statementIdx = 78,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).multiply(vec3(0,0,0)): "));
		// argumentValues[1] --> returnValue of transformations.multiply($transformations, vec3(0,0,0))
		// depth = 1 / argument index = 1: transformations.multiply($transformations, vec3(0,0,0))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// argumentValues[1] --> returnValue of vec3(0,0,0)
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, 0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(0));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.multiply
			Transformations transformations;
			Vector3 vec3;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
				returnValue.setValue(transformations.getTransformationsMatrix() * vec3);
			} else {
				Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.multiply") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 79
	miniscript_statement_79:
	// console.log("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): ", transformations.rotate($transformations, vec3(0,0,1)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 90,
			.statementIdx = 79,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("transformations(vec3(1,2,3), vec3(2, 3, 4), vec3(0, 1, 0)).rotate(vec3(0,0,1)): "));
		// argumentValues[1] --> returnValue of transformations.rotate($transformations, vec3(0,0,1))
		// depth = 1 / argument index = 1: transformations.rotate($transformations, vec3(0,0,1))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$transformations")
			// argumentValues[1] --> returnValue of vec3(0,0,1)
			// depth = 2 / argument index = 0: getVariable("$transformations")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$transformations"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// depth = 2 / argument index = 1: vec3(0, 0, 1)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 3> argumentValues;
				array<ScriptVariable, 3>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(static_cast<int64_t>(0));
				argumentValues[1].setValue(static_cast<int64_t>(0));
				argumentValues[2].setValue(static_cast<int64_t>(1));
				// method code: vec3
				Vector3 result;
				float xValue;
				float yValue;
				float zValue;
				if (MiniScript::getFloatValue(argumentValues, 0, xValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 1, yValue, false) == true &&
					MiniScript::getFloatValue(argumentValues, 2, zValue, false) == true) {
					returnValue.setValue(Vector3(xValue, yValue, zValue));
				} else {
					Console::println("ScriptMethodVec3::executeMethod(): " + string("vec3") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected, @ argument 2: float expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: transformations.rotate
			Transformations transformations;
			Vector3 vec3;
			if (MiniScript::getTransformationsValue(argumentValues, 0, transformations, false) == true &&
				MiniScript::getVector3Value(argumentValues, 1, vec3, false) == true) {
				returnValue.setValue(transformations.getRotationsQuaternion() * vec3);
			} else {
				Console::println("ScriptMethodTransformationsSetScale::executeMethod(): " + string("transformations.rotate") + "(): parameter type mismatch @ argument 0: transformations expected, @ argument 1: vector3 expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 80
	miniscript_statement_80:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 91,
			.statementIdx = 80,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 81
	miniscript_statement_81:
	// console.log("Check string functions")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 92,
			.statementIdx = 81,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check string functions"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 82
	miniscript_statement_82:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 93,
			.statementIdx = 82,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 83
	miniscript_statement_83:
	// console.log(space(0), "1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 94,
			.statementIdx = 83,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(0)
		argumentValues[1].setValue(string("1"));
		// depth = 1 / argument index = 0: space(0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(0));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 84
	miniscript_statement_84:
	// console.log(space(2), "1.1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 95,
			.statementIdx = 84,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(2)
		argumentValues[1].setValue(string("1.1"));
		// depth = 1 / argument index = 0: space(2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 85
	miniscript_statement_85:
	// console.log(space(2), "1.2")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 96,
			.statementIdx = 85,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of space(2)
		argumentValues[1].setValue(string("1.2"));
		// depth = 1 / argument index = 0: space(2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(static_cast<int64_t>(2));
			// method code: space
			int64_t spaces = 1;
			if (MiniScript::getIntegerValue(argumentValues, 0, spaces, true) == false) {
				Console::println("ScriptMethodSpace::executeMethod(): " + string("space") + "(): parameter type mismatch @ argument 0: integer expected");
				miniScript->startErrorScript(); return;
			} else {
				string spacesString;
				for (auto i = 0; i < spaces; i++) spacesString+= " ";
				returnValue.setValue(spacesString);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 86
	miniscript_statement_86:
	// console.log(toUpperCase("xxxyyyzzz"))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 97,
			.statementIdx = 86,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of toUpperCase("xxxyyyzzz")
		// depth = 1 / argument index = 0: toUpperCase("xxxyyyzzz")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("xxxyyyzzz"));
			// method code: toUpperCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toUpperCase(stringValue));
			} else {
				Console::println("ScriptMethodToUpperCase::executeMethod(): " + string("toUpperCase") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 87
	miniscript_statement_87:
	// console.log(toLowerCase("XXXYYYZZZ"))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 98,
			.statementIdx = 87,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of toLowerCase("XXXYYYZZZ")
		// depth = 1 / argument index = 0: toLowerCase("XXXYYYZZZ")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("XXXYYYZZZ"));
			// method code: toLowerCase
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(StringTools::toLowerCase(stringValue));
			} else {
				Console::println("ScriptMethodToLowerCase::executeMethod(): " + string("toLowerCase") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 88
	miniscript_statement_88:
	// console.log(concatenate("abc", "def", "ghi"))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 99,
			.statementIdx = 88,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of concatenate("abc", "def", "ghi")
		// depth = 1 / argument index = 0: concatenate("abc", "def", "ghi")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 3> argumentValues;
			array<ScriptVariable, 3>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("abc"));
			argumentValues[1].setValue(string("def"));
			argumentValues[2].setValue(string("ghi"));
			// method code: concatenate
			string result;
			for (auto& argumentValue: argumentValues) {
				result+= argumentValue.getValueString();
			}
			returnValue.setValue(result);
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 89
	miniscript_statement_89:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 100,
			.statementIdx = 89,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 90
	miniscript_statement_90:
	// console.log("Check string functions (Operators)")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 101,
			.statementIdx = 90,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Check string functions (Operators)"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 91
	miniscript_statement_91:
	// console.log(add("abc",add("def", "ghi")))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 102,
			.statementIdx = 91,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("abc",add("def", "ghi"))
		// depth = 1 / argument index = 0: add("abc", add("def", "ghi"))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("abc"));
			// argumentValues[1] --> returnValue of add("def", "ghi")
			// depth = 2 / argument index = 1: add("def", "ghi")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				argumentValues[0].setValue(string("def"));
				argumentValues[1].setValue(string("ghi"));
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 92
	miniscript_statement_92:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 103,
			.statementIdx = 92,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 93
	miniscript_statement_93:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 104,
			.statementIdx = 93,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 94
	miniscript_statement_94:
	// console.log("Variable")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 105,
			.statementIdx = 94,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Variable"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 95
	miniscript_statement_95:
	// console.log("------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 106,
			.statementIdx = 95,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 96
	miniscript_statement_96:
	// setVariable("$variable", string("1234"))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 107,
			.statementIdx = 96,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$variable"));
		// argumentValues[1] --> returnValue of string("1234")
		// depth = 1 / argument index = 1: string("1234")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("1234"));
			// method code: string
			string stringValue;
			if (MiniScript::getStringValue(argumentValues, 0, stringValue, false) == true) {
				returnValue.setValue(stringValue);
			} else {
				Console::println("ScriptMethodString::executeMethod(): " + string("string") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 97
	miniscript_statement_97:
	// console.log(getVariable("$variable"))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 108,
			.statementIdx = 97,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$variable")
		// depth = 1 / argument index = 0: getVariable("$variable")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$variable"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 98
	miniscript_statement_98:
	// console.log("--------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 109,
			.statementIdx = 98,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 99
	miniscript_statement_99:
	// console.log("Lets check forTime")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 110,
			.statementIdx = 99,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forTime"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 100
	miniscript_statement_100:
	// console.log("--------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 111,
			.statementIdx = 100,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 101
	miniscript_statement_101:
	// setVariable("$i", 1)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 112,
			.statementIdx = 101,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 102
	miniscript_statement_102:
	// forTime(2000)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 113,
			.statementIdx = 102,
			.statement = "<unavailable>",
			.gotoStatementIdx = 107
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
		// method code: forTime
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == false) {
			Console::println("ScriptMethodForTime::executeMethod(): " + string("forTime") + "(): parameter type mismatch @ argument 0: integer expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			auto timeWaitStarted = now;
			auto forTimeStartedIt = miniScript->scriptState.forTimeStarted.find(statement.line);
			if (forTimeStartedIt == miniScript->scriptState.forTimeStarted.end()) {
				miniScript->scriptState.forTimeStarted[statement.line] = timeWaitStarted;
			} else {
				timeWaitStarted = forTimeStartedIt->second;
			}
			//
			if (Time::getCurrentMillis() > timeWaitStarted + time) {
				miniScript->scriptState.forTimeStarted.erase(statement.line);
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_107;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 103
	miniscript_statement_103:
	// console.log($i, ": Hello World")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 114,
			.statementIdx = 103,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(": Hello World"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$i"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 104
	miniscript_statement_104:
	// script.wait(500)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 115,
			.statementIdx = 104,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
			miniScript->scriptState.timeWaitTime = time;
			miniScript->setScriptState(STATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 105
	miniscript_statement_105:
	// setVariable("$i", add($i, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 116,
			.statementIdx = 105,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		// argumentValues[1] --> returnValue of add($i, 1)
		// depth = 1 / argument index = 1: add($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 106
	miniscript_statement_106:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 117,
			.statementIdx = 106,
			.statement = "<unavailable>",
			.gotoStatementIdx = 102
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_102;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 107
	miniscript_statement_107:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 118,
			.statementIdx = 107,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 108
	miniscript_statement_108:
	// console.log("Lets check forCondition")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 119,
			.statementIdx = 108,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forCondition"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 109
	miniscript_statement_109:
	// console.log("-------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 120,
			.statementIdx = 109,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 110
	miniscript_statement_110:
	// setVariable("$i", 1)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 121,
			.statementIdx = 110,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 111
	miniscript_statement_111:
	// forCondition(notequal($i, 6))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 122,
			.statementIdx = 111,
			.statement = "<unavailable>",
			.gotoStatementIdx = 116
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of notequal($i, 6)
		// depth = 1 / argument index = 0: notequal($i, 6)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(6));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: notequal
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() == argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_116;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 112
	miniscript_statement_112:
	// console.log($i, ": Hello World")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 123,
			.statementIdx = 112,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(": Hello World"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$i"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 113
	miniscript_statement_113:
	// script.wait(500)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 124,
			.statementIdx = 113,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(500));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
			miniScript->scriptState.timeWaitTime = time;
			miniScript->setScriptState(STATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 114
	miniscript_statement_114:
	// setVariable("$i", add($i, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 125,
			.statementIdx = 114,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		// argumentValues[1] --> returnValue of add($i, 1)
		// depth = 1 / argument index = 1: add($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 115
	miniscript_statement_115:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 126,
			.statementIdx = 115,
			.statement = "<unavailable>",
			.gotoStatementIdx = 111
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_111;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 116
	miniscript_statement_116:
	// console.log("i -> ", $i)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 127,
			.statementIdx = 116,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> "));
		// argumentValues[1] --> returnValue of getVariable("$i")
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$i"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 117
	miniscript_statement_117:
	// console.log("---------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 128,
			.statementIdx = 117,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 118
	miniscript_statement_118:
	// console.log("Lets check forCondition with if/elseif/else")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 129,
			.statementIdx = 118,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Lets check forCondition with if/elseif/else"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 119
	miniscript_statement_119:
	// console.log("---------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 130,
			.statementIdx = 119,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 120
	miniscript_statement_120:
	// setVariable("$i", 1)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 131,
			.statementIdx = 120,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 121
	miniscript_statement_121:
	// forCondition(lesser($i, 5))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 132,
			.statementIdx = 121,
			.statement = "<unavailable>",
			.gotoStatementIdx = 136
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of lesser($i, 5)
		// depth = 1 / argument index = 0: lesser($i, 5)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(5));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: lesser
			float floatValueA;
			float floatValueB;
			if (MiniScript::getFloatValue(argumentValues, 0, floatValueA, false) == true &&
				MiniScript::getFloatValue(argumentValues, 1, floatValueB, false) == true) {
				returnValue.setValue(floatValueA < floatValueB);
			} else {
				Console::println("ScriptMethodFLesser::executeMethod(): " + string("lesser") + "(): parameter type mismatch @ argument 0: float expected, @ argument 1: float expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: forCondition
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodForCondition::executeMethod(): " + string("forCondition") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto now = Time::getCurrentMillis();
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_136;
			} else {
				miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_FOR);
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 122
	miniscript_statement_122:
	// console.log($i, ":")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 133,
			.statementIdx = 122,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of getVariable("$i")
		argumentValues[1].setValue(string(":"));
		// depth = 1 / argument index = 0: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("$i"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 123
	miniscript_statement_123:
	// if(equals($i, 0))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 134,
			.statementIdx = 123,
			.statement = "<unavailable>",
			.gotoStatementIdx = 125
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 0)
		// depth = 1 / argument index = 0: equals($i, 0)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(0));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_125;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 124
	miniscript_statement_124:
	// console.log("i -> 0")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 135,
			.statementIdx = 124,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 0"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 125
	miniscript_statement_125:
	// elseif(equals($i, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 136,
			.statementIdx = 125,
			.statement = "<unavailable>",
			.gotoStatementIdx = 127
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 1)
		// depth = 1 / argument index = 0: equals($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_127;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 126
	miniscript_statement_126:
	// console.log("i -> 1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 137,
			.statementIdx = 126,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 1"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 127
	miniscript_statement_127:
	// elseif(equals($i, 2))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 138,
			.statementIdx = 127,
			.statement = "<unavailable>",
			.gotoStatementIdx = 129
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 2)
		// depth = 1 / argument index = 0: equals($i, 2)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(2));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_129;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 128
	miniscript_statement_128:
	// console.log("i -> 2")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 139,
			.statementIdx = 128,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 2"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 129
	miniscript_statement_129:
	// elseif(equals($i, 3))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 140,
			.statementIdx = 129,
			.statement = "<unavailable>",
			.gotoStatementIdx = 131
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of equals($i, 3)
		// depth = 1 / argument index = 0: equals($i, 3)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(3));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: equals
			returnValue.setValue(true);
			for (auto i = 1; i < argumentValues.size(); i++) {
				if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
					returnValue.setValue(false);
					break;
				}
			}
		}
		// method code: elseif
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): " + string("elseif") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElseIfCondition::executeMethod(): elseif without if");
			miniScript->startErrorScript(); return;
		} else {
			//
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == false) {
				miniScript->scriptState.conditionStack.pop();
				miniScript->scriptState.conditionStack.push(booleanValue);
			}
			if (conditionStackElement == true || booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_131;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 130
	miniscript_statement_130:
	// console.log("i -> 3")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 141,
			.statementIdx = 130,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("i -> 3"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 131
	miniscript_statement_131:
	// else()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 142,
			.statementIdx = 131,
			.statement = "<unavailable>",
			.gotoStatementIdx = 133
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: else
		if (miniScript->scriptState.conditionStack.empty() == true) {
			Console::println("ScriptMethodElse::executeMethod(): else without if");
			miniScript->startErrorScript(); return;
		} else {
			auto conditionStackElement = miniScript->scriptState.conditionStack.top();
			if (conditionStackElement == true) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_133;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 132
	miniscript_statement_132:
	// console.log("else: ", $i)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 143,
			.statementIdx = 132,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("else: "));
		// argumentValues[1] --> returnValue of getVariable("$i")
		// depth = 1 / argument index = 1: getVariable("$i")
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 1> argumentValues;
			array<ScriptVariable, 1>& argumentValuesD1AIDX1 = argumentValues;
			argumentValues[0].setValue(string("$i"));
			// method code: getVariable
			string variable;
			if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
				auto variableIt = miniScript->scriptState.variables.find(variable);
				if (variableIt == miniScript->scriptState.variables.end()) {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
				} else {
					returnValue = variableIt->second;
				}
			} else {
				Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
				miniScript->startErrorScript(); return;
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 133
	miniscript_statement_133:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 144,
			.statementIdx = 133,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 134
	miniscript_statement_134:
	// setVariable("$i", add($i, 1))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 145,
			.statementIdx = 134,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		// argumentValues[1] --> returnValue of add($i, 1)
		// depth = 1 / argument index = 1: add($i, 1)
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of getVariable("$i")
			argumentValues[1].setValue(static_cast<int64_t>(1));
			// depth = 2 / argument index = 0: getVariable("$i")
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 1> argumentValues;
				array<ScriptVariable, 1>& argumentValuesD2AIDX0 = argumentValues;
				argumentValues[0].setValue(string("$i"));
				// method code: getVariable
				string variable;
				if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
					auto variableIt = miniScript->scriptState.variables.find(variable);
					if (variableIt == miniScript->scriptState.variables.end()) {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
					} else {
						returnValue = variableIt->second;
					}
				} else {
					Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
					miniScript->startErrorScript(); return;
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 135
	miniscript_statement_135:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 146,
			.statementIdx = 135,
			.statement = "<unavailable>",
			.gotoStatementIdx = 121
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
				goto miniscript_statement_121;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 136
	miniscript_statement_136:
	// setVariable("$i", 1)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 147,
			.statementIdx = 136,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$i"));
		argumentValues[1].setValue(static_cast<int64_t>(1));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 137
	miniscript_statement_137:
	// setVariable("$j", 2)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 148,
			.statementIdx = 137,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$j"));
		argumentValues[1].setValue(static_cast<int64_t>(2));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 138
	miniscript_statement_138:
	// setVariable("$k", 3)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 149,
			.statementIdx = 138,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 2> argumentValues;
		array<ScriptVariable, 2>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("$k"));
		argumentValues[1].setValue(static_cast<int64_t>(3));
		// method code: setVariable
		string variable;
		if (argumentValues.size() != 2 ||
			MiniScript::getStringValue(argumentValues, 0, variable, false) == false) {
			Console::println("ScriptMethodSetVariable::executeMethod(): " + string("setVariable") + "(): parameter type mismatch @ argument 0: string expected, @ argument 1: mixed expected");
			miniScript->startErrorScript(); return;
		} else {
			miniScript->setVariable(variable, argumentValues[1]);
			returnValue = argumentValues[1];
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 139
	miniscript_statement_139:
	// if(or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k)))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 150,
			.statementIdx = 139,
			.statement = "<unavailable>",
			.gotoStatementIdx = 141
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of or(equals(getVariable("$i"), $j),equals(getVariable("$i"), $k))
		// depth = 1 / argument index = 0: or(equals(getVariable("$i"), $j), equals(getVariable("$i"), $k))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			// argumentValues[0] --> returnValue of equals(getVariable("$i"), $j)
			// argumentValues[1] --> returnValue of equals(getVariable("$i"), $k)
			// depth = 2 / argument index = 0: equals(getVariable("$i"), $j)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of getVariable("$j")
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$i"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						auto variableIt = miniScript->scriptState.variables.find(variable);
						if (variableIt == miniScript->scriptState.variables.end()) {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
						} else {
							returnValue = variableIt->second;
						}
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: getVariable("$j")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$j"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						auto variableIt = miniScript->scriptState.variables.find(variable);
						if (variableIt == miniScript->scriptState.variables.end()) {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
						} else {
							returnValue = variableIt->second;
						}
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: equals
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
			// depth = 2 / argument index = 1: equals(getVariable("$i"), $k)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of getVariable("$k")
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$i"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						auto variableIt = miniScript->scriptState.variables.find(variable);
						if (variableIt == miniScript->scriptState.variables.end()) {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
						} else {
							returnValue = variableIt->second;
						}
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: getVariable("$k")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("$k"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						auto variableIt = miniScript->scriptState.variables.find(variable);
						if (variableIt == miniScript->scriptState.variables.end()) {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
						} else {
							returnValue = variableIt->second;
						}
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// method code: equals
				returnValue.setValue(true);
				for (auto i = 1; i < argumentValues.size(); i++) {
					if (argumentValues[0].getValueString() != argumentValues[i].getValueString()) {
						returnValue.setValue(false);
						break;
					}
				}
			}
			// method code: or
			returnValue.setValue(false);
			for (auto i = 0; i < argumentValues.size(); i++) {
				bool booleanValue;
				if (MiniScript::getBooleanValue(argumentValues, i, booleanValue, false) == false) {
					Console::println("ScriptMethodOr::executeMethod(): " + string("or") + "(): parameter type mismatch @ argument " + to_string(i) + ": boolean expected");
					miniScript->startErrorScript(); return;
				} else
				if (booleanValue == true) {
					returnValue.setValue(true);
					break;
				}
			}
		}
		// method code: if
		bool booleanValue;
		if (miniScript->getBooleanValue(argumentValues, 0, booleanValue, false) == false) {
			Console::println("ScriptMethodIfCondition::executeMethod(): " + string("if") + "(): parameter type mismatch @ argument 0: boolean expected");
			miniScript->startErrorScript(); return;
		} else {
			//
			miniScript->scriptState.endTypeStack.push(ScriptState::ENDTYPE_IF);
			//
			miniScript->scriptState.conditionStack.push(booleanValue);
			if (booleanValue == false) {
				miniScript->setScriptState(STATE_NEXT_STATEMENT);
				goto miniscript_statement_141;
			}
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 140
	miniscript_statement_140:
	// console.log("This should not happen, but look ok in preprocessor processed output")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 151,
			.statementIdx = 140,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("This should not happen, but look ok in preprocessor processed output"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 141
	miniscript_statement_141:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 152,
			.statementIdx = 141,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 142
	miniscript_statement_142:
	// console.log("-------------------------------------------------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 153,
			.statementIdx = 142,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 143
	miniscript_statement_143:
	// console.log(add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")")))))
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 154,
			.statementIdx = 143,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		// argumentValues[0] --> returnValue of add("Test: string concatenation with brackets in string literals: ",add($i,add("(",add($j, ")"))))
		// depth = 1 / argument index = 0: add("Test: string concatenation with brackets in string literals: ", add($i,add("(",add($j, ")"))))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[0];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX0 = argumentValues;
			argumentValues[0].setValue(string("Test: string concatenation with brackets in string literals: "));
			// argumentValues[1] --> returnValue of add($i,add("(",add($j, ")")))
			// depth = 2 / argument index = 1: add($i, add("(",add($j, ")")))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX0[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of getVariable("$i")
				// argumentValues[1] --> returnValue of add("(",add($j, ")"))
				// depth = 3 / argument index = 0: getVariable("$i")
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 1> argumentValues;
					array<ScriptVariable, 1>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(string("$i"));
					// method code: getVariable
					string variable;
					if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
						auto variableIt = miniScript->scriptState.variables.find(variable);
						if (variableIt == miniScript->scriptState.variables.end()) {
							Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
						} else {
							returnValue = variableIt->second;
						}
					} else {
						Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
						miniScript->startErrorScript(); return;
					}
				}
				// depth = 3 / argument index = 1: add("(", add($j, ")"))
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(string("("));
					// argumentValues[1] --> returnValue of add($j, ")")
					// depth = 4 / argument index = 1: add($j, ")")
					{
						// required method code arguments
						ScriptVariable& returnValue = argumentValuesD3AIDX1[1];
						array<ScriptVariable, 2> argumentValues;
						array<ScriptVariable, 2>& argumentValuesD4AIDX1 = argumentValues;
						// argumentValues[0] --> returnValue of getVariable("$j")
						argumentValues[1].setValue(string(")"));
						// depth = 5 / argument index = 0: getVariable("$j")
						{
							// required method code arguments
							ScriptVariable& returnValue = argumentValuesD4AIDX1[0];
							array<ScriptVariable, 1> argumentValues;
							array<ScriptVariable, 1>& argumentValuesD5AIDX0 = argumentValues;
							argumentValues[0].setValue(string("$j"));
							// method code: getVariable
							string variable;
							if (MiniScript::getStringValue(argumentValues, 0, variable, false) == true) {
								auto variableIt = miniScript->scriptState.variables.find(variable);
								if (variableIt == miniScript->scriptState.variables.end()) {
									Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): variable not found: '" + variable + "'");
								} else {
									returnValue = variableIt->second;
								}
							} else {
								Console::println("ScriptMethodGetVariable::executeMethod(): " + string("getVariable") + "(): parameter type mismatch @ argument 0: string expected");
								miniScript->startErrorScript(); return;
							}
						}
						// method code: add
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
							string result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								string stringValue;
								if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
									result+= stringValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
									miniScript->startErrorScript(); return;
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
							Vector3 result;
							for (auto i = 0; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result+= vec3Value;
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript(); return;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result+= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript(); return;
									}
								}
							}
							returnValue.setValue(result);
						} else
						if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
							float result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= floatValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
							returnValue.setValue(result);
						} else {
							int64_t result = 0.0f;
							for (auto i = 0; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result+= intValue;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript(); return;
								}
							}
							returnValue.setValue(result);
						}
					}
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						Vector3 result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result+= vec3Value;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						float result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= floatValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else {
						int64_t result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result+= intValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: add
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
					string result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						string stringValue;
						if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
							result+= stringValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					Vector3 result;
					for (auto i = 0; i < argumentValues.size(); i++) {
						if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
								result+= vec3Value;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
								miniScript->startErrorScript(); return;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
					}
					returnValue.setValue(result);
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					float result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= floatValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				} else {
					int64_t result = 0.0f;
					for (auto i = 0; i < argumentValues.size(); i++) {
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
							result+= intValue;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
							miniScript->startErrorScript(); return;
						}
					}
					returnValue.setValue(result);
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 144
	miniscript_statement_144:
	// console.log("-------------------------------------------------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 155,
			.statementIdx = 144,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-------------------------------------------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 145
	miniscript_statement_145:
	// console.log("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): ", add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5))), " = 17")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 156,
			.statementIdx = 145,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 3> argumentValues;
		array<ScriptVariable, 3>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("(4.0 + 2.0) / 2.0 + (20.0 / 10.0 * (2.0 + 5)): "));
		// argumentValues[1] --> returnValue of add(div(add(4.0, 2.0), 2.0),mul(div(20.0, 10.0), add(2.0, 5)))
		argumentValues[2].setValue(string(" = 17"));
		// depth = 1 / argument index = 1: add(div(add(4.0, 2.0), 2.0), mul(div(20.0, 10.0), add(2.0, 5)))
		{
			// required method code arguments
			ScriptVariable& returnValue = argumentValuesD0[1];
			array<ScriptVariable, 2> argumentValues;
			array<ScriptVariable, 2>& argumentValuesD1AIDX1 = argumentValues;
			// argumentValues[0] --> returnValue of div(add(4.0, 2.0), 2.0)
			// argumentValues[1] --> returnValue of mul(div(20.0, 10.0), add(2.0, 5))
			// depth = 2 / argument index = 0: div(add(4.0, 2.0), 2.0)
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[0];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX0 = argumentValues;
				// argumentValues[0] --> returnValue of add(4.0, 2.0)
				argumentValues[1].setValue(2.000000f);
				// depth = 3 / argument index = 0: add(4.0, 2.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX0[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(4.000000f);
					argumentValues[1].setValue(2.000000f);
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						Vector3 result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result+= vec3Value;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						float result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= floatValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else {
						int64_t result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result+= intValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: div
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					auto valid = true;
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result/= vec3Value;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
									break;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result/= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
									break;
								}
							}
						}
						returnValue.setValue(result);
					}
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					auto valid = true;
					float result = 0.0f;
					{
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = floatValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result/= floatValue;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
						returnValue.setValue(result);
					}
				} else {
					auto valid = true;
					int64_t result = 0LL;
					{
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
							result = intValue;
						} else {
							Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result/= intValue;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
						returnValue.setValue(result);
					}
				}
			}
			// depth = 2 / argument index = 1: mul(div(20.0, 10.0), add(2.0, 5))
			{
				// required method code arguments
				ScriptVariable& returnValue = argumentValuesD1AIDX1[1];
				array<ScriptVariable, 2> argumentValues;
				array<ScriptVariable, 2>& argumentValuesD2AIDX1 = argumentValues;
				// argumentValues[0] --> returnValue of div(20.0, 10.0)
				// argumentValues[1] --> returnValue of add(2.0, 5)
				// depth = 3 / argument index = 0: div(20.0, 10.0)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[0];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX0 = argumentValues;
					argumentValues[0].setValue(20.000000f);
					argumentValues[1].setValue(10.000000f);
					// method code: div
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						auto valid = true;
						Vector3 result;
						if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
							Vector3 vec3Value;
							if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
								result = vec3Value;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
								miniScript->startErrorScript(); return;
								valid = false;
							}
						} else {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
								result = Vector3(floatValue, floatValue, floatValue);
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
								miniScript->startErrorScript(); return;
								valid = false;
							}
						}
						if (valid == true) {
							for (auto i = 1; i < argumentValues.size(); i++) {
								if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
									Vector3 vec3Value;
									if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
										result/= vec3Value;
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
										miniScript->startErrorScript(); return;
										break;
									}
								} else {
									float floatValue;
									if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
										result/= Vector3(floatValue, floatValue, floatValue);
									} else {
										Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
										miniScript->startErrorScript(); return;
										break;
									}
								}
							}
							returnValue.setValue(result);
						}
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						auto valid = true;
						float result = 0.0f;
						{
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
								result = floatValue;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
								miniScript->startErrorScript(); return;
								valid = false;
							}
						}
						if (valid == true) {
							for (auto i = 1; i < argumentValues.size(); i++) {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result/= floatValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
									break;
								}
							}
							returnValue.setValue(result);
						}
					} else {
						auto valid = true;
						int64_t result = 0LL;
						{
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
								result = intValue;
							} else {
								Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
								miniScript->startErrorScript(); return;
								valid = false;
							}
						}
						if (valid == true) {
							for (auto i = 1; i < argumentValues.size(); i++) {
								int64_t intValue;
								if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
									result/= intValue;
								} else {
									Console::println("ScriptMethodDiv::executeMethod(): " + string("div") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
									miniScript->startErrorScript(); return;
									break;
								}
							}
							returnValue.setValue(result);
						}
					}
				}
				// depth = 3 / argument index = 1: add(2.0, 5)
				{
					// required method code arguments
					ScriptVariable& returnValue = argumentValuesD2AIDX1[1];
					array<ScriptVariable, 2> argumentValues;
					array<ScriptVariable, 2>& argumentValuesD3AIDX1 = argumentValues;
					argumentValues[0].setValue(2.000000f);
					argumentValues[1].setValue(static_cast<int64_t>(5));
					// method code: add
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
						string result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							string stringValue;
							if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
								result+= stringValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
						Vector3 result;
						for (auto i = 0; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result+= vec3Value;
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result+= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
								}
							}
						}
						returnValue.setValue(result);
					} else
					if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
						float result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result+= floatValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					} else {
						int64_t result = 0.0f;
						for (auto i = 0; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result+= intValue;
							} else {
								Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
							}
						}
						returnValue.setValue(result);
					}
				}
				// method code: mul
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
					auto valid = true;
					Vector3 result;
					if (argumentValues[0].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, 0, vec3Value, false) == true) {
							result = vec3Value;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": vector3 expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
								Vector3 vec3Value;
								if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
									result*= vec3Value;
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
									miniScript->startErrorScript(); return;
									break;
								}
							} else {
								float floatValue;
								if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
									result*= Vector3(floatValue, floatValue, floatValue);
								} else {
									Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
									miniScript->startErrorScript(); return;
									break;
								}
							}
						}
						returnValue.setValue(result);
					}
				} else
				if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
					auto valid = true;
					float result = 0.0f;
					{
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, 0, floatValue, false) == true) {
							result = floatValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": float expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							float floatValue;
							if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
								result*= floatValue;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
						returnValue.setValue(result);
					}
				} else {
					auto valid = true;
					int64_t result = 0LL;
					{
						int64_t intValue;
						if (MiniScript::getIntegerValue(argumentValues, 0, intValue, false) == true) {
							result = intValue;
						} else {
							Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(0) + ": integer expected");
							miniScript->startErrorScript(); return;
							valid = false;
						}
					}
					if (valid == true) {
						for (auto i = 1; i < argumentValues.size(); i++) {
							int64_t intValue;
							if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
								result*= intValue;
							} else {
								Console::println("ScriptMethodMul::executeMethod(): " + string("mul") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
								miniScript->startErrorScript(); return;
								break;
							}
						}
						returnValue.setValue(result);
					}
				}
			}
			// method code: add
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_STRING) == true) {
				string result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					string stringValue;
					if (MiniScript::getStringValue(argumentValues, i, stringValue, false) == true) {
						result+= stringValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": string expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_VECTOR3) == true) {
				Vector3 result;
				for (auto i = 0; i < argumentValues.size(); i++) {
					if (argumentValues[i].getType() == MiniScript::TYPE_VECTOR3) {
						Vector3 vec3Value;
						if (MiniScript::getVector3Value(argumentValues, i, vec3Value, false) == true) {
							result+= vec3Value;
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": vector3 expected");
							miniScript->startErrorScript(); return;
						}
					} else {
						float floatValue;
						if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
							result+= Vector3(floatValue, floatValue, floatValue);
						} else {
							Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
							miniScript->startErrorScript(); return;
						}
					}
				}
				returnValue.setValue(result);
			} else
			if (MiniScript::hasType(argumentValues, MiniScript::TYPE_FLOAT) == true) {
				float result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					float floatValue;
					if (MiniScript::getFloatValue(argumentValues, i, floatValue, false) == true) {
						result+= floatValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": float expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			} else {
				int64_t result = 0.0f;
				for (auto i = 0; i < argumentValues.size(); i++) {
					int64_t intValue;
					if (MiniScript::getIntegerValue(argumentValues, i, intValue, false) == true) {
						result+= intValue;
					} else {
						Console::println("ScriptMethodAdd::executeMethod(): " + string("add") + "(): parameter type mismatch @ argument " + to_string(i) + ": integer expected");
						miniScript->startErrorScript(); return;
					}
				}
				returnValue.setValue(result);
			}
		}
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 146
	miniscript_statement_146:
	// console.log("--------------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 157,
			.statementIdx = 146,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 147
	miniscript_statement_147:
	// console.log("Test if enabled naming condition will be emitted")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 158,
			.statementIdx = 147,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Test if enabled naming condition will be emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 148
	miniscript_statement_148:
	// console.log("--------------------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 159,
			.statementIdx = 148,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("--------------------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 149
	miniscript_statement_149:
	// script.enableNamedCondition("named_condition_1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 160,
			.statementIdx = 149,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.enableNamedCondition
		string name;
		if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
			miniScript->scriptState.enabledConditionNames.erase(
				remove(
					miniScript->scriptState.enabledConditionNames.begin(),
					miniScript->scriptState.enabledConditionNames.end(),
					name
				),
				miniScript->scriptState.enabledConditionNames.end()
			);
			miniScript->scriptState.enabledConditionNames.push_back(name);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.enableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 150
	miniscript_statement_150:
	// script.wait(2000)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 161,
			.statementIdx = 150,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(2000));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
			miniScript->scriptState.timeWaitTime = time;
			miniScript->setScriptState(STATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 151
	miniscript_statement_151:
	// script.disableNamedCondition("named_condition_1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 162,
			.statementIdx = 151,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.disableNamedCondition
		string name;
		if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
			miniScript->scriptState.enabledConditionNames.erase(
				remove(
					miniScript->scriptState.enabledConditionNames.begin(),
					miniScript->scriptState.enabledConditionNames.end(),
					name
				),
				miniScript->scriptState.enabledConditionNames.end()
			);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 152
	miniscript_statement_152:
	// console.log("---------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 163,
			.statementIdx = 152,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 153
	miniscript_statement_153:
	// console.log("Naming condition has not been emitted")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 164,
			.statementIdx = 153,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Naming condition has not been emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 154
	miniscript_statement_154:
	// console.log("---------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 165,
			.statementIdx = 154,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 155
	miniscript_statement_155:
	// script.stop()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 166,
			.statementIdx = 155,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->scriptState.running = false;
		miniScript->scriptState.variables.clear();
		miniScript->scriptState.timeEnabledConditionsCheckLast = -1LL;
		miniScript->resetScriptExecutationState(-1, STATE_NONE);
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 156
	miniscript_statement_156:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 167,
			.statementIdx = 156,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_error(int miniScriptGotoStatementIdx) {
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(2, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 2;
	if (miniScriptGotoStatementIdx == 2) goto miniscript_statement_2; else
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_error(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 0
	miniscript_statement_0:
	// console.log("An error occurred")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 170,
			.statementIdx = 0,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("An error occurred"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 1
	miniscript_statement_1:
	// script.wait(1000)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 171,
			.statementIdx = 1,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(static_cast<int64_t>(1000));
		// method code: script.wait
		int64_t time;
		if (miniScript->getIntegerValue(argumentValues, 0, time) == true) {
			miniScript->scriptState.timeWaitStarted = Time::getCurrentMillis();
			miniScript->scriptState.timeWaitTime = time;
			miniScript->setScriptState(STATE_WAIT);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.wait") + "(): parameter type mismatch @ argument 0: integer expected");
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 2
	miniscript_statement_2:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 172,
			.statementIdx = 2,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_emittest(int miniScriptGotoStatementIdx) {
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(3, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 3;
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_emittest(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 0
	miniscript_statement_0:
	// console.log("---------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 175,
			.statementIdx = 0,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 1
	miniscript_statement_1:
	// console.log("SCRIPT JUST EMITTED A CONDITION")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 176,
			.statementIdx = 1,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("SCRIPT JUST EMITTED A CONDITION"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 2
	miniscript_statement_2:
	// console.log("---------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 177,
			.statementIdx = 2,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("---------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 3
	miniscript_statement_3:
	// console.log()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 178,
			.statementIdx = 3,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 4
	miniscript_statement_4:
	// script.stop()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 179,
			.statementIdx = 4,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: script.stop
		//
		miniScript->scriptState.running = false;
		miniScript->scriptState.variables.clear();
		miniScript->scriptState.timeEnabledConditionsCheckLast = -1LL;
		miniScript->resetScriptExecutationState(-1, STATE_NONE);
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 5
	miniscript_statement_5:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 180,
			.statementIdx = 5,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}

void MiniScriptTest::on_enabled_named_condition_1(int miniScriptGotoStatementIdx) {
	if (miniScriptGotoStatementIdx == -1) {
		resetScriptExecutationState(4, STATE_NEXT_STATEMENT);
	}
	auto miniScript = this;
	miniScript->scriptState.scriptIdx = 4;
	if (miniScriptGotoStatementIdx != -1 && miniScriptGotoStatementIdx != 0) Console::println("MiniScript::on_enabled_named_condition_1(): Can not go to statement " + to_string(miniScriptGotoStatementIdx));

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 0
	miniscript_statement_0:
	// script.disableNamedCondition("named_condition_1")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 183,
			.statementIdx = 0,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1"));
		// method code: script.disableNamedCondition
		string name;
		if (MiniScript::getStringValue(argumentValues, 0, name, false) == true) {
			miniScript->scriptState.enabledConditionNames.erase(
				remove(
					miniScript->scriptState.enabledConditionNames.begin(),
					miniScript->scriptState.enabledConditionNames.end(),
					name
				),
				miniScript->scriptState.enabledConditionNames.end()
			);
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.disableNamedCondition") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 1
	miniscript_statement_1:
	// console.log("------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 184,
			.statementIdx = 1,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 2
	miniscript_statement_2:
	// console.log("named_condition_1 has been emitted")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 185,
			.statementIdx = 2,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("named_condition_1 has been emitted"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 3
	miniscript_statement_3:
	// console.log("------------------------------------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 186,
			.statementIdx = 3,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("------------------------------------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 4
	miniscript_statement_4:
	// console.log()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 187,
			.statementIdx = 4,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 5
	miniscript_statement_5:
	// console.log("-----------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 188,
			.statementIdx = 5,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 6
	miniscript_statement_6:
	// console.log("Test emit")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 189,
			.statementIdx = 6,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("Test emit"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 7
	miniscript_statement_7:
	// console.log("-----------")
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 190,
			.statementIdx = 7,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("-----------"));
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 8
	miniscript_statement_8:
	// console.log()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 191,
			.statementIdx = 8,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: console.log
		for (auto& argumentValue: argumentValues) {
			Console::print(argumentValue.getValueString());
		}
		Console::println();
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 9
	miniscript_statement_9:
	// script.emit(emittest)
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 192,
			.statementIdx = 9,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 1> argumentValues;
		array<ScriptVariable, 1>& argumentValuesD0 = argumentValues;
		argumentValues[0].setValue(string("emittest"));
		// method code: script.emit
		string condition;
		if (MiniScript::getStringValue(argumentValues, 0, condition, false) == true) {
			miniScript->emit(condition); return;
		} else {
			Console::println("ScriptMethodScriptWait::executeMethod(): " + string("script.emit") + "(): parameter type mismatch @ argument 0: string expected");
			miniScript->startErrorScript(); return;
		}
	}
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}

	// enabled named conditions
	if (scriptState.enabledConditionNames.empty() == false) {
		auto scriptIdxToStart = determineNamedScriptIdxToStart();
		if (scriptIdxToStart != -1 && scriptIdxToStart != scriptState.scriptIdx) {
			resetScriptExecutationState(scriptIdxToStart, STATE_NEXT_STATEMENT);
			scriptState.timeEnabledConditionsCheckLast = Time::getCurrentMillis();
			return;
		}
	}

	// Statement: 10
	miniscript_statement_10:
	// end()
	{
		// required method code arguments
		const MiniScript::ScriptStatement statement = {
			.line = 193,
			.statementIdx = 10,
			.statement = "<unavailable>",
			.gotoStatementIdx = -1
		};
		miniScript->scriptState.statementIdx = statement.statementIdx;
		ScriptVariable returnValue;
		array<ScriptVariable, 0> argumentValues;
		array<ScriptVariable, 0>& argumentValuesD0 = argumentValues;
		// method code: end
		if (miniScript->scriptState.endTypeStack.empty() == true) {
			if (miniScript->scriptState.statementIdx < miniScript->scripts[miniScript->scriptState.scriptIdx].statements.size() - 1) {
				Console::println("ScriptMethodEnd::executeMethod(): end without forXXX/if");
				miniScript->startErrorScript(); return;
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
	if (scriptState.state.state != STATE_NEXT_STATEMENT) {
		miniScript->scriptState.statementIdx++;
		return;
	}
	scriptState.scriptIdx = -1;
	scriptState.statementIdx = -1;
	setScriptState(STATE_WAIT_FOR_CONDITION);
}


/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/
