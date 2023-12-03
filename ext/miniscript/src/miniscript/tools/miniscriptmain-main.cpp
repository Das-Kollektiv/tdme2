#include <cstdlib>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/StringTools.h>

using std::exit;
using std::string;
using std::to_string;
using std::vector;

using miniscript::miniscript::Version;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("miniscriptmain ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc != 4) {
		Console::println("Usage: miniscriptmain script_filename script_class_name main_filename");
		exit(EXIT_FAILURE);
	}

	//
	auto pathToScript = string(argv[1]);
	auto scriptClassName = string(argv[2]);
	auto pathToMain = string(argv[3]);

	//
	if (StringTools::endsWith(pathToMain, "-main.cpp") == false) {
		Console::println("Error: main_filename must end with '-main.cpp'");
		exit(EXIT_FAILURE);
	}

	//
	try {
		Console::println("Generating main C++ file: " + pathToMain);

		auto mainSource = FileSystem::getContentAsString("./resources/templates/transpilation", "script-main.cpp");
		mainSource = StringTools::replace(mainSource, "{$script}", pathToScript);
		mainSource = StringTools::replace(mainSource, "{$script-class}", scriptClassName);
		FileSystem::setContentFromString(FileSystem::getPathName(pathToMain), FileSystem::getFileName(pathToMain), mainSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

	//
	exit(EXIT_SUCCESS);
}
