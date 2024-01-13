#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

// Windows MSC: required for OpenSSL to work when having OpenSSL embedded in a DLL which is used here
#if defined(_MSC_VER)
	#include <openssl/applink.c>
#endif

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/os/network/Network.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/StringTools.h>

using std::cin;
using std::exit;
using std::make_unique;
using std::string;
using std::tmpnam;
using std::unique_ptr;

using miniscript::miniscript::Context;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::Version;
using miniscript::os::filesystem::FileSystem;
using miniscript::os::network::Network;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTools;

static void printInformation() {
	Console::println(string("miniscript ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();
	Console::println("Usage: miniscript [--version] [--verbose] [path_to_script | < path_to_script] --arguments [script command line arguments...]");
	Console::println();
	Console::println("If you do not provide a path to the script or do not pipe a script into the standard input stream,");
	Console::println("you get a prompt to enter your script. You can finish inputting by hitting Ctrl-D on Unix or Ctrl-Z on Windows.");
}

int main(int argc, char** argv)
{
	//
	string pathToScript;
	auto verbose = false;
	auto version = false;
	for (auto i = 1; i < argc; i++) {
		string argument = argv[i];
		if (argument == "--help") {
			printInformation();
			return EXIT_SUCCESS;
		} else
		if (argument == "--version") {
			version = true;
		} else
		if (argument == "--verbose") {
			verbose = true;
		} else
		if (argument == "--arguments") {
			break;
		} else {
			if (pathToScript.empty() == false) {
				Console::println("Path to script already given");
				return EXIT_FAILURE;
			} else {
				pathToScript = argument;
			}
		}
	}

	// version
	if (version == true) {
		Console::println(string("miniscript ") + Version::getVersion());
		Console::println(Version::getCopyright());
		return EXIT_FAILURE;
	}

	//
	MiniScript::initialize();
	// run script
	unique_ptr<Context> context;
	unique_ptr<MiniScript> script;
	// if no file given, then read from input stream until Ctrl+D(Unix) or Ctrl+Z(Windows) was hit
	//	which is the standard behaviour of those kind of CLI apps
	//	we store the file as temporary one and reuse it for execution
	string tmpFile;
	if (pathToScript.empty() == true) {
		// read from standard input
		auto statementsOnly = true;
		string scriptCode;
		string line;
		while (cin.eof() == false && getline(cin, line)) {
			if (StringTools::startsWith(line, "on:") == true ||
				StringTools::startsWith(line, "on-enabled:") == true ||
				StringTools::startsWith(line, "function:") == true ||
				StringTools::startsWith(line, "callable:") == true) statementsOnly = false;
			scriptCode+= line + "\n";
		}
		pathToScript = tmpnam(nullptr);
		// create the script
		try {
			if (statementsOnly == true) {
				scriptCode = StringTools::replace(
					FileSystem::getContentAsString("resources/miniscript/templates/cli", "statements.tscript"),
					"{$statements}",
					scriptCode
				);
			}
			//
			FileSystem::setContentFromString(
				FileSystem::getPathName(pathToScript),
				FileSystem::getFileName(pathToScript),
				scriptCode
			);
			// we want to delete the script later
			tmpFile = pathToScript;
		} catch (Exception& exception) {
			pathToScript.clear();
			Console::println("An error occurred: " + string(exception.what()));
		}
	}
	// do we have a script to run?
	if (pathToScript.empty() == false) {
		// yes, go
		context = make_unique<Context>();
		//
		{
			// create main argument values
			vector<string> argumentValues;
			argumentValues.push_back(string(argv[0]));
			bool haveArguments = false;
			for (auto i = 0; i < argc; i++) {
				string argumentValue(argv[i]);
				if (haveArguments == false &&
					argumentValue == "--arguments") {
					haveArguments = true;
					continue;
				}
				//
				if (haveArguments == false) continue;
				//
				argumentValues.push_back(argumentValue);
			}
			//
			context->setArgumentValues(argumentValues);
		}

		script = make_unique<MiniScript>();
		script->setContext(context.get());
		script->parseScript(
			FileSystem::getPathName(pathToScript),
			FileSystem::getFileName(pathToScript)
		);
		if (script != nullptr) {
			// verbose
			if (verbose == true) Console::println(script->getInformation());
			//
			if (script->isValid() == false) {
				Console::println(pathToScript + ": Script not valid. Exiting!");
			} else {
				// TODO: we need a MiniScript startup routine
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
				while (scriptPtr->isRunning() == true) {
					scriptPtr->execute();
				}
				context->pop();
			}
		}
	} else
	if (version == false) {
		printInformation();
		return EXIT_SUCCESS;
	}

	// delete temporary file if we have created any
	if (tmpFile.empty() == false) {
		try {
			FileSystem::removeFile(
				FileSystem::getPathName(tmpFile),
				FileSystem::getFileName(tmpFile)
			);
		} catch (Exception& exception) {
			pathToScript.clear();
			Console::println("An error occurred: " + string(exception.what()));
		}
	}

	//
	return script == nullptr || script->isValid() == false?EXIT_FAILURE:EXIT_SUCCESS;
}
