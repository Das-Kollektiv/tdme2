#include <cstdlib>
#include <memory>

// Windows MSC: required for OpenSSL to work when having OpenSSL embedded in a DLL which is used here
#if defined(_MSC_VER)
	#include <openssl/applink.c>
#endif

using std::make_unique;

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/NativeLibrary.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/os/network/Network.h>
#include <minitscript/utilities/Console.h>

#include "{$script-class}.h"

using minitscript::minitscript::Context;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::NativeLibrary;
using minitscript::os::filesystem::FileSystem;
using minitscript::os::network::Network;
using minitscript::utilities::Console;

int main(int argc, char *argv[]) {
	// Windows MSC: required for OpenSSL to work when having OpenSSL embedded in a DLL which is used here
	#if defined(_MSC_VER)
		OPENSSL_Applink();
	#endif
	// initialize network
	Network::initialize();
	// initialize MinitScript
	MinitScript::initialize();
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
	script->parseScript(FileSystem::getPathName(scriptFile), FileSystem::getFileName(scriptFile), {$native-only});
	// script valid?
	if (script->isValid() == false) {
		// nope, exit here
		Console::printLine("Script not valid. Exiting!");
		return EXIT_FAILURE;
	}
	// does it run in native mode?
	if (script->isNative() == false) {
		// nope, print out a warning
		Console::printLine("Warning: Script not executed natively: " + scriptFile);
	}
	// add script to context, push it to minitscript stack
	auto scriptPtr = script.get();
	scriptPtr->getContext()->addScript("application", script.release());
	scriptPtr->getContext()->push(scriptPtr);
	scriptPtr->startScript();
	while (scriptPtr->isRunning() == true) {
		scriptPtr->execute();
	}
	// done
	scriptPtr->getContext()->pop();
	//
	return scriptPtr->getContext()->getExitCode();
}
