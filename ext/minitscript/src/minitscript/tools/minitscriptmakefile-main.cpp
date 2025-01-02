#include <cstdlib>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Generator.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Console.h>

using std::exit;
using std::string;

using minitscript::minitscript::Generator;
using minitscript::minitscript::Version;
using minitscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptmakefile ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if ((argc != 3 && argc != 4) || (argc == 4 && string(argv[1]) != "--library")) {
		Console::printLine("Usage: minitscriptmakefile [--library] source_pathname makefile_filename");
		return EXIT_FAILURE;
	}

	//
	auto library = argc == 4 && string(argv[1]) == "--library";
	auto srcPath = string(argv[1 + (library == true?1:0)]);
	auto makefileURI = string(argv[2 + (library == true?1:0)]);

	//
	Generator::generateMakefile(srcPath, makefileURI, library);

	//
	return EXIT_SUCCESS;
}
