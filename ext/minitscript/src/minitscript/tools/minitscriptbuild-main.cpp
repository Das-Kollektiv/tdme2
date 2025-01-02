#include <cstdlib>
#include <memory>
#include <string>

// Windows MSC: required for OpenSSL to work when having OpenSSL embedded in a DLL which is used here
#if defined(_MSC_VER)
	#include <openssl/applink.c>
#endif

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/os/network/Network.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/StringTools.h>

using std::exit;
using std::make_unique;
using std::string;
using std::unique_ptr;

using minitscript::minitscript::Context;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Version;
using minitscript::os::filesystem::FileSystem;
using minitscript::os::network::Network;
using minitscript::utilities::Console;
using minitscript::utilities::Exception;
using minitscript::utilities::StringTools;

int main(int argc, char** argv)
{
	// TODO: --application, --library, --native-only
	//
	auto printInformation = [&]() -> void {
		Console::printLine(string("minitscriptbuild ") + Version::getVersion());
		Console::printLine(Version::getCopyright());
		Console::printLine();
		Console::printLine("Usage: minitscriptbuild [--help] [--application|--library] [--native-only] main-script.tscript [additional-script1.tscript] [additional-script2.tscript] [additional-scriptN.tscript]");
	};

	// no arguments, no build :DDD
	if (argc == 1) {
		printInformation();
		return EXIT_SUCCESS;
	}

	//
	vector<string> scriptURIs;

	//
	for (auto i = 1; i < argc; i++) {
		string argument = argv[i];
		if (argument == "--help") {
			printInformation();
			return EXIT_SUCCESS;
		}
	}

	//
	MinitScript::initialize();
	// run script
	auto context = make_unique<Context>();
	auto script = make_unique<MinitScript>();
	//
	{
		// create main argument values
		vector<string> argumentValues;
		argumentValues.push_back(argv[0]);
		for (auto i = 1; i < argc; i++) {
			string argumentValue(argv[i]);
			//
			if (argumentValue == "--help") continue;
			if (argumentValue == "--application") {
				argumentValues.push_back(argumentValue);
				continue;
			}
			if (argumentValue == "--library") {
				argumentValues.push_back(argumentValue);
				continue;
			}
			if (argumentValue == "--native-only") {
				argumentValues.push_back(argumentValue);
				continue;
			}
			/* we like / more than */
			argumentValue = StringTools::replace(argumentValue, "\\", "/");
			// we do not want to have .. or . in path names
			argumentValue = FileSystem::getCanonicalURI(FileSystem::getPathName(argumentValue), FileSystem::getFileName(argumentValue));
			//
			if (FileSystem::exists(argumentValue) == false) {
				Console::printLine("Script URI invalid: File not found: " + argumentValue);
				return EXIT_FAILURE;
			}
			//
			argumentValues.push_back(argumentValue);
		}
		//
		context->setArgumentValues(argumentValues);
	}
	auto pathToScript = MINITSCRIPT_DATA + "/resources/minitscript/scripts/build.tscript";
	script = make_unique<MinitScript>();
	script->setContext(context.get());
	script->parseScript(
		FileSystem::getPathName(pathToScript),
		FileSystem::getFileName(pathToScript)
	);
	//
	if (script->isValid() == false) {
		Console::printLine(pathToScript + ": Build script not valid. Exiting!");
		return EXIT_SUCCESS;
	} else {
		// TODO: we need a MinitScript startup routine
		Network::initialize();
		// Windows MSC: required for OpenSSL to work when having OpenSSL embedded in a DLL which is used here
		#if defined(_MSC_VER)
			OPENSSL_Applink();
		#endif
		// add script to context
		auto scriptPtr = script.get();
		context->push(scriptPtr);
		context->addScript("application", script.release());
		//
		scriptPtr->startScript();
		while (scriptPtr->isRunning() == true) {
			scriptPtr->execute();
		}
		context->pop();
	}

	//
	return context->getExitCode();
}
