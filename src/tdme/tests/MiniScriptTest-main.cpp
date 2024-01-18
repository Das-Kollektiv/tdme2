#include <memory>

using std::make_unique;

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/miniscript/EngineMiniScript.h>

using tdme::utilities::Console;
using tdme::miniscript::EngineMiniScript;

int main(int argc, char *argv[]) {
	Console::printLine("MiniScriptTest");
	//
	EngineMiniScript::initialize();
	// base test
	{
		auto script = make_unique<EngineMiniScript>();
		script->parseScript("resources/tests/scripts", "base-test.tscript");
		Console::printLine("---------------------------------------------------------");
		Console::printLine("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::printLine("---------------------------------------------------------");
		// Console::printLine(script->getInformation());
		if (script->isValid() == false) {
			Console::printLine("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::printLine();
		Console::printLine();
		Console::printLine();
	}
	// class test
	{
		auto script = make_unique<EngineMiniScript>();
		script->parseScript("resources/tests/scripts", "class-test.tscript");
		Console::printLine("---------------------------------------------------------");
		Console::printLine("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::printLine("---------------------------------------------------------");
		// Console::printLine(script->getInformation());
		if (script->isValid() == false) {
			Console::printLine("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::printLine();
		Console::printLine();
		Console::printLine();
	}
	// advanced test
	{
		auto script = make_unique<EngineMiniScript>();
		script->parseScript("resources/tests/scripts", "advanced-test.tscript");
		Console::printLine("---------------------------------------------------------");
		Console::printLine("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::printLine("---------------------------------------------------------");
		// Console::printLine(script->getInformation());
		if (script->isValid() == false) {
			Console::printLine("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::printLine();
		Console::printLine();
		Console::printLine();
	}
	// emit test
	{
		auto script = make_unique<EngineMiniScript>();
		script->parseScript("resources/tests/scripts", "emit-test.tscript");
		Console::printLine("---------------------------------------------------------");
		Console::printLine("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::printLine("---------------------------------------------------------");
		// Console::printLine(script->getInformation());
		if (script->isValid() == false) {
			Console::printLine("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::printLine();
		Console::printLine();
		Console::printLine();
	}
	// function test
	{
		auto script = make_unique<EngineMiniScript>();
		script->parseScript("resources/tests/scripts", "functions-test.tscript");
		Console::printLine("---------------------------------------------------------");
		Console::printLine("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::printLine("---------------------------------------------------------");
		// Console::printLine(script->getInformation());
		if (script->isValid() == false) {
			Console::printLine("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::printLine();
		Console::printLine();
		Console::printLine();
	}
	//
	Console::shutdown();
	return 0;
}
