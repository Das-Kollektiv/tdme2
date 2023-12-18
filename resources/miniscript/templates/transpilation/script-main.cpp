#include <cstdlib>
#include <memory>

using std::make_unique;

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/Library.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>

#include "{$script-class}.h"

using miniscript::miniscript::Context;
using miniscript::miniscript::Library;
using miniscript::miniscript::MiniScript;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;

int main(int argc, char *argv[]) {
	auto context = make_unique<Context>();
	auto script = make_unique<{$script-class}>();
	script->setContext(context.get());
	{$library}
	string scriptFile = "{$script}";
	script->parseScript(FileSystem::getPathName(scriptFile), FileSystem::getFileName(scriptFile));
	if (script->isValid() == false) {
		Console::println("Script not valid. Exiting!");
		return EXIT_FAILURE;
	}
	if (script->isNative() == false) {
		Console::println("Warning: Script not executed natively: " + scriptFile);
	}
	while (script->isRunning() == true) {
		script->execute();
	}
	//
	return EXIT_SUCCESS;
}
