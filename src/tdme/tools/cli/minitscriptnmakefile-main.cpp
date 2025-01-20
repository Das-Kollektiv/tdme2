#include <cstdlib>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Generator.h>

#include <tdme/tdme.h>
#include <tdme/engine/Version.h>
#include <tdme/utilities/Console.h>

using std::exit;
using std::string;

using minitscript::minitscript::Generator;

using tdme::engine::Version;
using tdme::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptnmakefile ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc != 4) {
		Console::printLine("Usage: minitscriptnmakefile base_pathname source_pathname makefile_filename");
		return EXIT_FAILURE;
	}

	//
	auto basePath = string(argv[1]);
	auto srcPath = string(argv[2]);
	auto makefileURI = string(argv[3]);

	//
	Generator::generateNMakefile(srcPath, makefileURI, true, basePath, { "tdme" });

	//
	return EXIT_SUCCESS;
}
