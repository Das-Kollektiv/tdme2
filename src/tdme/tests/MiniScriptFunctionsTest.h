#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/functions-test.tscript src/tdme/tests/MiniScriptFunctionsTest.cpp'
 */
class MiniScriptFunctionsTest: public EngineMiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptFunctionsTest)

	/**
	 * Public constructor
	 */
	MiniScriptFunctionsTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
