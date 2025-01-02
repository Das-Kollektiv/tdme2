#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Generator.h>

#include <tdme/engine/Version.h>
#include <tdme/utilities/Console.h>

using std::exit;
using std::pair;
using std::string;
using std::to_string;
using std::vector;

using minitscript::minitscript::Generator;

using tdme::engine::Version;
using tdme::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptlibrary ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if ((argc - 2) / 2 == 0 || argc % 2 == 1) {
		Console::printLine("Usage: minitscriptlibrary script_filename1 script_class_name1 [script_filenameN script_class_nameN] library_filename");
		return EXIT_FAILURE;
	}

	//
	auto libraryURI = string(argv[argc - 1]);
	vector<pair<string, string>> scriptClassPairs;
	for (auto i = 0; i < ((argc - 2) / 2); i++) {
		auto scriptURI = string(argv[1 + i * 2]);
		auto className = string(argv[1 + i * 2 + 1]);
		scriptClassPairs.emplace_back(scriptURI, className);
	}

	//
	Generator::generateLibrary(scriptClassPairs, libraryURI);

	//
	return EXIT_SUCCESS;
}
