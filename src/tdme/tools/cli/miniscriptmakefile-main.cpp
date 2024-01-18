#include <cstdlib>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Generator.h>

#include <tdme/engine/Version.h>
#include <tdme/utilities/Console.h>

using std::exit;
using std::string;

using miniscript::miniscript::Generator;

using tdme::engine::Version;
using tdme::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("miniscriptmakefile ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc != 4) {
		Console::printLine("Usage: miniscriptmakefile base_pathname source_pathname makefile_filename");
		return EXIT_FAILURE;
	}

	//
	auto basePath = string(argv[1]);
	auto srcPath = string(argv[2]);
	auto makefileURI = string(argv[3]);

	//
	Generator::generateMakefile(srcPath, makefileURI, true, basePath, { "tdme" });

	//
	return EXIT_SUCCESS;
}
