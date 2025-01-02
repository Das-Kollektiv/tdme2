#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Generator.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Console.h>

using std::exit;
using std::pair;
using std::string;
using std::to_string;
using std::vector;

using minitscript::minitscript::Generator;
using minitscript::minitscript::Version;
using minitscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptlibrary ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	auto nativeOnly = argc >= 2?string(argv[1]) == "--native-only":false;

	//
	if ((argc - 2 - (nativeOnly == true?1:0)) / 2 == 0 || (argc - (nativeOnly == true?1:0)) % 2 == 1) {
		Console::printLine("Usage: minitscriptlibrary [--native-only] script_filename1 script_class_name1 [script_filenameN script_class_nameN] library_filename");
		exit(EXIT_FAILURE);
	}

	//
	auto libraryURI = string(argv[argc - 1]);
	vector<pair<string, string>> scriptClassPairs;
	for (auto i = 0; i < ((argc - 2 - (nativeOnly == true?1:0)) / 2); i++) {
		auto scriptURI = string(argv[1 + (nativeOnly == true?1:0) + i * 2]);
		auto className = string(argv[1 + (nativeOnly == true?1:0) + i * 2 + 1]);
		scriptClassPairs.emplace_back(scriptURI, className);
	}

	//
	Generator::generateLibrary(scriptClassPairs, libraryURI, nativeOnly);

	//
	return EXIT_SUCCESS;
}
