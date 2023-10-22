#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/base-test.tscript src/tdme/tests/MiniScriptBaseTest.cpp'
 */
class MiniScriptBaseTest: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptBaseTest)

	/**
	 * Public constructor
	 */
	MiniScriptBaseTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/

public:
	// overridden methods
	void registerMethods() override;
	void emit(const string& condition) override;
	inline void startScript() override {
		if (native == false) {
			MiniScript::startScript();
			return;
		}
		auto& scriptState = getScriptState();
		for (const auto& [scriptVariableName, scriptVariable]: scriptState.variables) delete scriptVariable;
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
			if (getScriptState().scriptIdx == 1) on_nothing(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 2) on_error(scriptState.statementIdx); else
				;
		}
		if (getScriptState().running == false) return;
		executeStateMachine();
	}

protected:
	// evaluate member access constants
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_NONE { -1 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_APPLYROTATION { 0 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_CHARAT { 1 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_COMPUTEEULERANGLES { 2 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTH { 3 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_COMPUTELENGTHSQUARED { 4 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_COMPUTEMATRIX { 5 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_ENDSWITH { 6 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_EQUALSIGNORECASE { 7 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_FIRSTINDEXOF { 8 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GET { 9 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETKEYS { 10 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONANGLE { 11 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONAXIS { 12 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETROTATIONSQUATERNION { 13 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETSCALE { 14 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETTRANSFORMMATRIX { 15 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETTRANSLATION { 16 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETVALUES { 17 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETW { 18 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETX { 19 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETY { 20 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_GETZ { 21 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_HAS { 22 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_INDEXOF { 23 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_INSERT { 24 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_INVERT { 25 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_ISEMPTY { 26 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_ISFLOAT { 27 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_ISINTEGER { 28 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_LASTINDEXOF { 29 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_LENGTH { 30 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_NORMALIZE { 31 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_PADLEFT { 32 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_PADRIGHT { 33 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_PUSH { 34 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REGEXMATCH { 35 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REGEXREPLACE { 36 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REMOVE { 37 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REMOVEOF { 38 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REPLACE { 39 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_REVERSE { 40 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_ROTATE { 41 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SET { 42 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SETROTATIONANGLE { 43 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SETSCALE { 44 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SETTRANSLATION { 45 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SORT { 46 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_STARTSWITH { 47 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_SUBSTRING { 48 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_TOLOWERCASE { 49 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_TOUPPERCASE { 50 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_TOKENIZE { 51 };
	static constexpr int EVALUATEMEMBERACCESSARRAYIDX_TRIM { 52 };
	
	// evaluate member access arrays
	array<array<ScriptMethod*, 53>, 11> evaluateMemberAccessArrays {};
	// evaluate member access arrays

	// overridden methods
	void initializeNative() override;
	int determineScriptIdxToStart() override;
	int determineNamedScriptIdxToStart() override;

	/**
	 * Miniscript transpilation of: on: initialize
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_initialize(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: on: nothing
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_nothing(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: on: error
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void on_error(int miniScriptGotoStatementIdx);


	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
