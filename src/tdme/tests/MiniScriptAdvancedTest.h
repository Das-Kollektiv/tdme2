#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/advanced-test.tscript src/tdme/tests/MiniScriptAdvancedTest.cpp'
 */
class MiniScriptAdvancedTest: public MiniScript {
public:
	// forbid class copy
	CLASS_FORBID_COPY(MiniScriptAdvancedTest)

	/**
	 * Public constructor
	 */
	MiniScriptAdvancedTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
