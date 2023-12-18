#include <memory>
#include <string>
#include <vector>

#include <ext/miniscript/src/miniscript/miniscript/Transpiler.h>

#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>

using std::exit;
using std::string;
using std::unique_ptr;
using std::vector;

using miniscript::miniscript::Transpiler;

using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;

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
	EngineMiniScript::registerDataTypes();

	//
	auto scriptFileName = string(argv[1]);
	auto miniScript = unique_ptr<EngineMiniScript>(
		EngineMiniScript::loadScript(
			FileSystem::getInstance()->getPathName(scriptFileName),
			FileSystem::getInstance()->getFileName(scriptFileName)
		)
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
