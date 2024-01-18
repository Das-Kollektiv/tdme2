#include <cstdlib>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Transpiler.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Console.h>

using std::exit;
using std::string;

using miniscript::miniscript::Transpiler;
using miniscript::miniscript::Version;
using miniscript::utilities::Console;


int main(int argc, char** argv)
{
	Console::printLine(string("miniscriptuntranspiler ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc < 3) {
		Console::printLine("Usage: miniscriptuntranspiler path_to_script_file path_to_cpp_miniscript_transpilation_file");
		return EXIT_FAILURE;
	}

	//
	Transpiler::untranspile(argv[1], argv[2]);

	//
	return EXIT_SUCCESS;
}
