#include <memory>

#include "MiniScriptAdvancedTest.h"
#include "MiniScriptBaseTest.h"
#include "MiniScriptClassTest.h"
#include "MiniScriptEmitTest.h"
#include "MiniScriptFunctionsTest.h"

using std::make_unique;

#include <tdme/tdme.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>

using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;

int main(int argc, char *argv[]) {
	Console::println("MiniScriptTest");
	//
	EngineMiniScript::registerDataTypes();
	// base test
	{
		auto script = make_unique<MiniScriptBaseTest>();
		script->parseScript("resources/tests/scripts", "base-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		// Console::println(script->getInformation());
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// class test
	{
		auto script = make_unique<MiniScriptClassTest>();
		script->parseScript("resources/tests/scripts", "class-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		// Console::println(script->getInformation());
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
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
		script->parseScript("resources/tests/scripts", "advanced-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		// Console::println(script->getInformation());
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
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
		script->parseScript("resources/tests/scripts", "emit-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		// Console::println(script->getInformation());
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	// function test
	{
		auto script = make_unique<MiniScriptFunctionsTest>();
		script->parseScript("resources/tests/scripts", "functions-test.tscript");
		Console::println("---------------------------------------------------------");
		Console::println("Loaded test script: " + script->getScriptFileName() + ": runs " + (script->isNative() == true?"natively":"interpreted"));
		Console::println("---------------------------------------------------------");
		// Console::println(script->getInformation());
		if (script->isValid() == false) {
			Console::println("Script not valid. Exiting");
			return 1;
		}
		while (script->isRunning() == true) {
			script->execute();
		}
		//
		Console::println();
		Console::println();
		Console::println();
	}
	//
	Console::shutdown();
	return 0;
}
