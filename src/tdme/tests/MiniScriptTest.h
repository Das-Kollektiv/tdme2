#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/test.tscript src/tdme/tests/MiniScriptTest.cpp'
 */
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
		auto& scriptState = getScriptState();
		for (auto& scriptVariableIt: scriptState.variables) delete scriptVariableIt.second;
		scriptState.variables.clear();
		getScriptState().running = true;
		registerVariables();
		resetScriptExecutationState(0, STATEMACHINESTATE_NEXT_STATEMENT);
	}
	inline void execute() override {
		if (native == false) {
			MiniScript::execute();
			return;
		}
		auto& scriptState = getScriptState();
		if (getScriptState().running == false) return;
		// execute while having statements to be processed
		if (getScriptState().state == STATEMACHINESTATE_NEXT_STATEMENT) {
			if (getScriptState().scriptIdx == 0) on_initialize(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 1) factorial(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 2) helloWorldFunction(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 3) on_nothing(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 4) on_error(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 5) on_emittest(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 6) on_enabled_named_condition_1(scriptState.statementIdx); else
				;
		}
		if (getScriptState().running == false) return;
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
	 * Miniscript transpilation of: FUNCTION: factorial
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void factorial(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: FUNCTION: helloWorldFunction
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void helloWorldFunction(int miniScriptGotoStatementIdx);

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
	 * Miniscript transpilation of: ON-ENABLED: true == true (named_condition_1)
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_enabled_named_condition_1(int miniScriptGotoStatementIdx);


	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
