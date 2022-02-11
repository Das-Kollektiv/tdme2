#include "MiniScriptTest.h"

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::Console;

int main(int argc, char *argv[]) {
	Console::println("MiniScriptNativeTest");
	auto script = new MiniScriptTest();
	script->loadScript("resources/tests/scripts", "test.tscript");
	Console::println(script->getInformation());
	while (script->isRunning() == true) {
		script->executeNative();
	}
	delete script;
	return 0;
}

