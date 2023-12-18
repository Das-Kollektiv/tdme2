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
	Console::println(string("miniscriptuntranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 3) {
		Console::println("Usage: miniscriptuntranspiler path_to_script_file path_to_cpp_miniscript_transpilation_file");
		exit(EXIT_FAILURE);
	}

	//
	Transpiler::untranspile(argv[1], argv[2]);

	//
	exit(EXIT_SUCCESS);
}
