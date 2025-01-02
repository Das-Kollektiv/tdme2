#include <cstdlib>
#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Generator.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/StringTools.h>

using std::exit;
using std::string;
using std::to_string;
using std::vector;

using minitscript::minitscript::Generator;
using minitscript::minitscript::Version;
using minitscript::utilities::Console;
using minitscript::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptmain ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	auto printUsage = []() -> void {
		Console::printLine("Usage: minitscriptmain [--use-library] [--native-only] script_filename script_class_name main_filename");
	};

	//
	if (argc == 1) {
		printUsage();
		return EXIT_FAILURE;
	}

	//
	auto useLibrary = false;
	auto nativeOnly = false;
	auto i = 1;
	for (; i < argc; i++) {
		string argument = argv[i];
		if (StringTools::startsWith(argument, "--") == false) break;
		if (argument == "--use-library") {
			useLibrary = true;
		} else
		if (argument == "--native-only") {
			nativeOnly = true;
		}
	}
	auto scriptURI = i < argc?string(argv[i++]):string();
	auto className = i < argc?string(argv[i++]):string();
	auto mainURI = i < argc?string(argv[i++]):string();

	//
	if (i != argc) {
		printUsage();
		return EXIT_FAILURE;
	}

	//
	if (StringTools::endsWith(mainURI, "-main.cpp") == false) {
		Console::printLine("An error occurred: main_filename must end with '-main.cpp'");
		return EXIT_FAILURE;
	}

	// generate
	Generator::generateMain(scriptURI, className, mainURI, useLibrary, nativeOnly);

	//
	return EXIT_SUCCESS;
}
