#include <cstdlib>
#include <memory>

using std::make_unique;

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/NativeLibrary.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>

#include "{$script-class}.h"

using miniscript::miniscript::Context;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::NativeLibrary;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;

int main(int argc, char *argv[]) {
	// initialize MiniScript
	MiniScript::initialize();
	// create context and argument values
	auto context = make_unique<Context>();
	//
	{
		// create main argument values
		vector<string> argumentValues;
		for (auto i = 0; i < argc; i++) {
			argumentValues.push_back(string(argv[i]));
		}
		context->setArgumentValues(argumentValues);
	}
	// load script and set context
	auto script = make_unique<{$script-class}>();
	script->setContext(context.get());
	{$library}
	string scriptFile = "{$script}";
	script->parseScript(FileSystem::getPathName(scriptFile), FileSystem::getFileName(scriptFile));
	// script valid?
	if (script->isValid() == false) {
		// nope, exit here
		Console::println("Script not valid. Exiting!");
		return EXIT_FAILURE;
	}
	// does it run in native mode?
	if (script->isNative() == false) {
		// nope, print out a warning
		Console::println("Warning: Script not executed natively: " + scriptFile);
	}
	// add script to context, push it to miniscript stack
	auto scriptPtr = script.get();
	scriptPtr->getContext()->addScript("application", script.release());
	scriptPtr->getContext()->push(scriptPtr);
	while (scriptPtr->isRunning() == true) {
		scriptPtr->execute();
	}
	// done
	scriptPtr->getContext()->pop();
	//
	return EXIT_SUCCESS;
}
