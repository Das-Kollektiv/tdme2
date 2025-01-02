#include <cstdlib>
#include <cstdio>
#include <iostream>
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

using std::cin;
using std::exit;
using std::make_unique;
using std::string;
using std::tmpnam;
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
	//
	auto printVersion = [&]() -> void {
		Console::printLine(string("minitscript ") + Version::getVersion());
		Console::printLine(Version::getCopyright());
	};
	//
	auto printUsage = [&]() -> void {
		Console::printLine("Usage: minitscript [--version] [--verbose] [path_to_script | < path_to_script] --arguments [script command line arguments...]");
	};
	//
	auto printInformation = [&]() -> void {
		printVersion();
		Console::printLine();
		printUsage();
		Console::printLine();
		Console::printLine("If you do not provide a path to the script or do not pipe a script into the standard input stream,");
		Console::printLine("you get a prompt to enter your script. You can finish inputting by hitting Ctrl-D on Unix or Ctrl-Z on Windows.");
	};

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
				Console::printLine("Invalid command line arguments!");
				Console::printLine();
				printUsage();
				return EXIT_FAILURE;
			} else {
				pathToScript = argument;
			}
		}
	}

	// version
	if (version == true) {
		printVersion();
		return EXIT_FAILURE;
	}

	//
	MinitScript::initialize();
	// run script
	unique_ptr<Context> context;
	unique_ptr<MinitScript> script;
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
					FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/cli", "statements.tscript"),
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
			Console::printLine("An error occurred: " + string(exception.what()));
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
		//
		script = make_unique<MinitScript>();
		script->setContext(context.get());
		script->parseScript(
			FileSystem::getPathName(pathToScript),
			FileSystem::getFileName(pathToScript)
		);
		//
		if (script != nullptr) {
			// verbose
			if (verbose == true) Console::printLine(script->getInformation());
			//
			if (script->isValid() == false) {
				Console::printLine(pathToScript + ": Script not valid. Exiting!");
				return EXIT_FAILURE;
			} else
			if (script->isModule() == true) {
				Console::printLine(pathToScript + ": Script is a module. You can not start a module. Exiting!");
				return EXIT_FAILURE;
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
		} else {
			return EXIT_FAILURE;
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
			Console::printLine("An error occurred: " + string(exception.what()));
		}
	}

	//
	return context->getExitCode();
}
