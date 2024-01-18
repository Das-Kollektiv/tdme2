#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Generator.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Console.h>

using std::exit;
using std::pair;
using std::string;
using std::to_string;
using std::vector;

using miniscript::miniscript::Generator;
using miniscript::miniscript::Version;
using miniscript::utilities::Console;

int main(int argc, char** argv)
{
	Console::printLine(string("miniscriptlibrary ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if ((argc - 2) / 2 == 0 || argc % 2 == 1) {
		Console::printLine("Usage: miniscriptlibrary script_filename1 script_class_name1 [script_filenameN script_class_nameN] library_filename");
		exit(EXIT_FAILURE);
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
