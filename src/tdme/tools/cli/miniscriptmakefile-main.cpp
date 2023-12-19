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
	Console::println(string("miniscriptmakefile ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if ((argc != 3 && argc != 4) || (argc == 4 && string(argv[1]) != "--library")) {
		Console::println("Usage: miniscriptmakefile [--library] source_pathname makefile_filename");
		exit(EXIT_FAILURE);
	}

	//
	auto library = argc == 4 && string(argv[1]) == "--library";
	auto srcPath = string(argv[1 + (library == true?1:0)]);
	auto makefileURI = string(argv[2 + (library == true?1:0)]);

	//
	Generator::generateMakefile(srcPath, makefileURI, library);

	//
	exit(EXIT_SUCCESS);
}
