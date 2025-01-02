#include <memory>
#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Transpiler.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/utilities/Console.h>

using std::exit;
using std::make_unique;
using std::string;
using std::vector;

using minitscript::minitscript::Context;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Transpiler;
using minitscript::minitscript::Version;
using minitscript::os::filesystem::FileSystem;
using minitscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscripttranspiler ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc < 3) {
		Console::printLine("Usage: minitscripttranspiler script_filename transpilation_filename [minitscript_extension_file1] [minitscript_extension_fileN]");
		return EXIT_FAILURE;
	}

	vector<string> minitScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) minitScriptExtensionFileNames.push_back(argv[i]);

	//
	MinitScript::initialize();

	//
	auto scriptFileName = string(argv[1]);
	auto context = make_unique<Context>();
	auto minitScript = make_unique<MinitScript>();
	minitScript->setContext(context.get());
	minitScript->parseScript(
		FileSystem::getPathName(scriptFileName),
		FileSystem::getFileName(scriptFileName)
	);
	if (minitScript->isValid() == false) {
		Console::printLine(scriptFileName + ": Script not valid. Exiting!");
	} else {
		//
		Transpiler::transpile(minitScript.get(), argv[2], minitScriptExtensionFileNames);
	}

	//
	return EXIT_SUCCESS;
}
