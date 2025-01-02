#include <cstdlib>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Transpiler.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Console.h>

using std::exit;
using std::string;

using minitscript::minitscript::Transpiler;
using minitscript::minitscript::Version;
using minitscript::utilities::Console;


int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptuntranspiler ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc < 3) {
		Console::printLine("Usage: minitscriptuntranspiler path_to_script_file path_to_cpp_minitscript_transpilation_file");
		return EXIT_FAILURE;
	}

	//
	Transpiler::untranspile(argv[1], argv[2]);

	//
	return EXIT_SUCCESS;
}
