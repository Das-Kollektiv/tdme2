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
	Console::println(string("miniscriptnmakefile ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc != 4) {
		Console::println("Usage: miniscriptnmakefile base_pathname source_pathname makefile_filename");
		exit(EXIT_FAILURE);
	}

	//
	auto basePath = string(argv[1]);
	auto srcPath = string(argv[2]);
	auto makefileURI = string(argv[3]);

	//
	Generator::generateNMakefile(srcPath, makefileURI, true, basePath);

	//
	exit(EXIT_SUCCESS);
}
