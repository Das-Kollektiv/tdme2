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
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
