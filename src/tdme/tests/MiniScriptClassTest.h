#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/class-test.tscript src/tdme/tests/MiniScriptClassTest.cpp'
 */
class MiniScriptClassTest: public EngineMiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptClassTest)

	/**
	 * Public constructor
	 */
	MiniScriptClassTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
