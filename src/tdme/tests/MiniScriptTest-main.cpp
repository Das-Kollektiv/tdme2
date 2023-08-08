#include <memory>

#include "MiniScriptAdvancedTest.h"
#include "MiniScriptBaseTest.h"
#include "MiniScriptEmitTest.h"
#include "MiniScriptFunctionsTest.h"

using std::make_unique;

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>

using tdme::utilities::Console;

int main(int argc, char *argv[]) {
	Console::println("MiniScriptTest");
	// base test
	{
		auto script = make_unique<MiniScriptBaseTest>();
		script->loadScript("resources/tests/scripts", "base-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		// Console::println(script->getInformation());
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// advanced test
	{
		auto script = make_unique<MiniScriptAdvancedTest>();
		script->loadScript("resources/tests/scripts", "advanced-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		// Console::println(script->getInformation());
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// emit test
	{
		auto script = make_unique<MiniScriptEmitTest>();
		script->loadScript("resources/tests/scripts", "emit-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		// Console::println(script->getInformation());
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// emit test
	{
		auto script = make_unique<MiniScriptFunctionsTest>();
		script->loadScript("resources/tests/scripts", "functions-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		// Console::println(script->getInformation());
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// done
	return 0;
}

