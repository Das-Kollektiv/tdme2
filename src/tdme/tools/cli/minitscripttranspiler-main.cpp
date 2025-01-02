#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Transpiler.h>

#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/minitscript/EngineMinitScript.h>

using std::exit;
using std::string;
using std::unique_ptr;
using std::vector;

using minitscript::minitscript::Transpiler;

using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::minitscript::EngineMinitScript;

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

	vector<string> miniScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) miniScriptExtensionFileNames.push_back(argv[i]);

	//
	EngineMinitScript::initialize();

	//
	auto scriptFileName = string(argv[1]);
	auto miniScript = unique_ptr<EngineMinitScript>(
		EngineMinitScript::loadScript(
			FileSystem::getInstance()->getPathName(scriptFileName),
			FileSystem::getInstance()->getFileName(scriptFileName)
		)
	);
	if (miniScript->isValid() == false) {
		Console::printLine(scriptFileName + ": Script not valid. Exiting!");
	} else {
		//
		Transpiler::transpile(miniScript.get(), argv[2], miniScriptExtensionFileNames);
	}

	//
	return EXIT_SUCCESS;
}
