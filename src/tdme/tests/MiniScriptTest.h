#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::MiniScript;

class MiniScriptTest: public MiniScript {

	// overriden methods
	void nothing(int miniScriptGotoStatementIdx) override;

};
