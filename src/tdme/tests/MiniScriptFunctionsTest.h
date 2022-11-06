#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/functions-test.tscript src/tdme/tests/MiniScriptFunctionsTest.cpp'
 */
class MiniScriptFunctionsTest: public MiniScript {
public:
	/**
	 * Public constructor
	 */
	MiniScriptFunctionsTest();

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
			if (getScriptState().scriptIdx == 3) assignTest(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 4) globalVariableTest(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 5) on_nothing(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 6) on_error(scriptState.statementIdx); else
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
	 * Miniscript transpilation of: FUNCTION: assignTest
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void assignTest(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: FUNCTION: globalVariableTest
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void globalVariableTest(int miniScriptGotoStatementIdx);

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


	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
