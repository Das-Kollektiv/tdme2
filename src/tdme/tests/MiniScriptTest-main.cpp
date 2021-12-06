#include <tdme/utilities/MiniScript.h>

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using tdme::utilities::MiniScript;

using tdme::utilities::Console;

int main(int argc, char *argv[]) {
	Console::println("MiniScript");
	MiniScript* script = new MiniScript();
	script->loadScript("resources/tests/scripts", "test.tscript");
	Console::println(script->getInformation());
	while (script->isRunning() == true) {
		script->execute();
	}
	delete script;
	return 0;
}

