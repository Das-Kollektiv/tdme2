#include <cstdlib>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Generator.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Console.h>

using std::exit;
using std::string;

using miniscript::miniscript::Generator;
using miniscript::miniscript::Version;
using miniscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::println(string("miniscriptnmakefile ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if ((argc != 3 && argc != 4) || (argc == 4 && string(argv[1]) != "--library")) {
		Console::println("Usage: miniscriptnmakefile [--library] source_pathname makefile_filename");
		return EXIT_FAILURE;
	}

	//
	auto library = argc == 4 && string(argv[1]) == "--library";
	auto srcPath = string(argv[1 + (library == true?1:0)]);
	auto makefileURI = string(argv[2 + (library == true?1:0)]);

	//
	Generator::generateNMakefile(srcPath, makefileURI, library);

	//
	return EXIT_SUCCESS;
}
