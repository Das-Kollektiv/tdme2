#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Transpile with './bin/tdme/tools/cli/miniscripttranspiler resources/tests/scripts/emit-test.tscript src/tdme/tests/MiniScriptEmitTest.cpp'
 */
class MiniScriptEmitTest: public MiniScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(MiniScriptEmitTest)

	/**
	 * Public constructor
	 */
	MiniScriptEmitTest();

	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/
	/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/

};
