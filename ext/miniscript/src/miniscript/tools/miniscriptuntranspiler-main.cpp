#include <cstdlib>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/StringTools.h>

using std::exit;
using std::string;
using std::vector;

using miniscript::miniscript::Version;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTools;

namespace miniscript {
namespace tools {
class MiniscriptUntranspiler {
public:
static void processFile(const string& scriptFileName, const string& miniscriptTranspilationFileName) {
	Console::println("Processing script: " + scriptFileName);

	// de-inject C++ definition code
	{
		vector<string> miniScriptClass;
		vector<string> miniScriptClassNew;
		FileSystem::getContentAsStringArray(FileSystem::getPathName(miniscriptTranspilationFileName), FileSystem::getFileName(miniscriptTranspilationFileName), miniScriptClass);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClass.size(); i++) {
			const auto& line = miniScriptClass[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/") {
				reject = true;
				miniScriptClassNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not remove generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(miniscriptTranspilationFileName),
				FileSystem::getFileName(miniscriptTranspilationFileName),
				miniScriptClassNew
			);
			//
			Console::println(scriptFileName + ": Removed generated C++ code in file " + miniscriptTranspilationFileName + ". Dont forget to rebuild your sources.");
		}
	}

	//
	// inject C++ declaration code / header
	{
		vector<string> miniScriptClassHeader;
		vector<string> miniScriptClassHeaderNew;
		auto miniscriptTranspilationHeaderFileName = FileSystem::getPathName(miniscriptTranspilationFileName) + "/" + FileSystem::removeFileExtension(FileSystem::getFileName(miniscriptTranspilationFileName)) + ".h";
		FileSystem::getContentAsStringArray(FileSystem::getPathName(miniscriptTranspilationHeaderFileName), FileSystem::getFileName(miniscriptTranspilationHeaderFileName), miniScriptClassHeader);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClassHeader.size(); i++) {
			const auto& line = miniScriptClassHeader[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/") {
				reject = true;
				miniScriptClassHeaderNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassHeaderNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not remove generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(miniscriptTranspilationHeaderFileName),
				FileSystem::getFileName(miniscriptTranspilationHeaderFileName),
				miniScriptClassHeaderNew
			);
			//
			Console::println(scriptFileName + ": Removed generated C++ code in header file " + miniscriptTranspilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

};
}
}

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
	miniscript::tools::MiniscriptUntranspiler::processFile(argv[1], argv[2]);

	//
	exit(EXIT_SUCCESS);
}
