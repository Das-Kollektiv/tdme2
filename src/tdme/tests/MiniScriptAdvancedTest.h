#include <array>
#include <utility>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::array;
using std::move;

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/advanced-test.tscript src/tdme/tests/MiniScriptAdvancedTest.cpp'
 */
class MiniScriptAdvancedTest: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptAdvancedTest)

	/**
	 * Public constructor
	 */
	MiniScriptAdvancedTest();

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
		resetScriptExecutationState(2, STATEMACHINESTATE_NEXT_STATEMENT);
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
			if (getScriptState().scriptIdx == 0) sortFunctionDesc(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 1) sortFunctionAsc(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 2) on_initialize(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 3) on_nothing(scriptState.statementIdx); else
			if (getScriptState().scriptIdx == 4) on_error(scriptState.statementIdx); else
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
	 * Miniscript transpilation of: function: sortFunctionDesc
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void sortFunctionDesc(int miniScriptGotoStatementIdx);

	/**
	 * Miniscript transpilation of: function: sortFunctionAsc
	 * @param miniScriptGotoStatementIdx MiniScript goto statement index
	 */
	void sortFunctionAsc(int miniScriptGotoStatementIdx);

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

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 21, argument indices 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	inline ScriptVariable on_nothing_array_access_statement_s_21_0_0(const ScriptStatement& statement) {
		return ScriptVariable(static_cast<int64_t>(11ll));
	}

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 22, argument indices 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	inline ScriptVariable on_nothing_array_access_statement_s_22_0_0(const ScriptStatement& statement) {
		return ScriptVariable(static_cast<int64_t>(11ll));
	}

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 23, argument indices 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	inline ScriptVariable on_nothing_array_access_statement_s_23_0_0(const ScriptStatement& statement) {
		return ScriptVariable(static_cast<int64_t>(11ll));
	}

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 23, argument indices 0, array access statement index 1
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_23_0_1(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 34, argument indices 0, 1, 1, 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_34_0_1_1_0_0(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 40, argument indices 0, 1, 1, 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_40_0_1_1_0_0(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 41, argument indices 0, 1, 1, 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_41_0_1_1_0_0(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 99, argument indices 0, 0, 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_99_0_0_0_0(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array access statement for method 'on_nothing', statement index 99, argument indices 0, 1, 1, 4, 0, array access statement index 0
	 * @param statement statement
	 * @return array index
	 */
	ScriptVariable on_nothing_array_access_statement_s_99_0_1_1_4_0_0(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array/map/set initializer for method 'on_nothing', statement index 7, argument indices 1
	 * @param statement statement
	 * @return initialized variable
	 */
	ScriptVariable on_nothing_initializer_s_7_1(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array/map/set initializer for method 'on_nothing', statement index 61, argument indices 1
	 * @param statement statement
	 * @return initialized variable
	 */
	ScriptVariable on_nothing_initializer_s_61_1(const ScriptStatement& statement);

	/**
	 * Miniscript transpilation for a statement array/map/set initializer for method 'on_nothing', statement index 105, argument indices 1
	 * @param statement statement
	 * @return initialized variable
	 */
	ScriptVariable on_nothing_initializer_s_105_1(const ScriptStatement& statement);


	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
