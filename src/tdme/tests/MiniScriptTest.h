#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

class MiniScriptTest: public MiniScript {

public:
	/**
	 * Public constructor
	 */
	MiniScriptTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/

public:
	// overridden methods
	void emit(const string& condition) override;
	inline void startScript() override {
		if (native == false) {
			MiniScript::startScript();
			return;
		}
		for (auto& scriptVariableIt: scriptState.variables) delete scriptVariableIt.second;
		scriptState.variables.clear();
		scriptState.running = true;
		registerVariables();
		resetScriptExecutationState(0, STATE_NEXT_STATEMENT);
	}
	inline void execute() override {
		if (native == false) {
			MiniScript::execute();
			return;
		}
		if (scriptState.running == false) return;
		// execute while having statements to be processed
		if (scriptState.state.state == STATE_NEXT_STATEMENT) {
			if (scriptState.scriptIdx == 0) on_initialize(scriptState.statementIdx); else
			if (scriptState.scriptIdx == 1) on_nothing(scriptState.statementIdx); else
			if (scriptState.scriptIdx == 2) on_error(scriptState.statementIdx); else
			if (scriptState.scriptIdx == 3) on_emittest(scriptState.statementIdx); else
			if (scriptState.scriptIdx == 4) on_enabled_named_condition_1(scriptState.statementIdx);
		}
		if (scriptState.running == false) return;
		executeStateMachine();
	};

protected:
	// overridden methods
	void initializeNative() override;
	int determineScriptIdxToStart() override;
	int determineNamedScriptIdxToStart() override;

	/**
	 * Miniscript transpilation of: ON: initialize
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_initialize(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: ON: nothing
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_nothing(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: ON: error
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_error(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: ON: emittest
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_emittest(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: ON-ENABLED: equals(1,1) (named_condition_1)
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_enabled_named_condition_1(int miniScriptGotoStatementIdx);


	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
