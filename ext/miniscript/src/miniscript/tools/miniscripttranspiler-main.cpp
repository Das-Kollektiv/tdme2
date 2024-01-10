#include <memory>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/Transpiler.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>

using std::exit;
using std::make_unique;
using std::string;
using std::vector;

using miniscript::miniscript::Context;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::Transpiler;
using miniscript::miniscript::Version;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::println(string("miniscripttranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 3) {
		Console::println("Usage: miniscripttranspiler script_filename transpilation_filename [miniscript_extension_file1] [miniscript_extension_fileN]");
		exit(EXIT_FAILURE);
	}

	vector<string> miniScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) miniScriptExtensionFileNames.push_back(argv[i]);

	//
	MiniScript::initialize();

	//
	auto scriptFileName = string(argv[1]);
	auto context = make_unique<Context>();
	auto miniScript = make_unique<MiniScript>();
	miniScript->setContext(context.get());
	miniScript->parseScript(
		FileSystem::getPathName(scriptFileName),
		FileSystem::getFileName(scriptFileName)
	);
	if (miniScript->isValid() == false) {
		Console::println(scriptFileName + ": Script not valid. Exiting!");
	} else {
		//
		Transpiler::transpile(miniScript.get(), argv[2], miniScriptExtensionFileNames);
	}

	//
	exit(EXIT_SUCCESS);
}
