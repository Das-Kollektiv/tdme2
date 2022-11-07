#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {
class MiniscriptUntranspiler {
public:
static void processFile(const string& scriptFileName, const string& miniscriptTranspilationFileName) {
	Console::println("Processing script: " + scriptFileName);

	// de-inject C++ definition code
	{
		vector<string> miniScriptClass;
		vector<string> miniScriptClassNew;
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationFileName), Tools::getFileName(miniscriptTranspilationFileName), miniScriptClass);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClass.size(); i++) {
			auto& line = miniScriptClass[i];
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
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationFileName),
				Tools::getFileName(miniscriptTranspilationFileName),
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
		auto miniscriptTranspilationHeaderFileName = Tools::getPathName(miniscriptTranspilationFileName) + "/" + Tools::removeFileEnding(Tools::getFileName(miniscriptTranspilationFileName)) + ".h";
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationHeaderFileName), Tools::getFileName(miniscriptTranspilationHeaderFileName), miniScriptClassHeader);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClassHeader.size(); i++) {
			auto& line = miniScriptClassHeader[i];
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
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationHeaderFileName),
				Tools::getFileName(miniscriptTranspilationHeaderFileName),
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
}

int main(int argc, char** argv)
{
	Console::println(string("miniscriptuntranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 3) {
		Console::println("Usage: miniscriptuntranspiler path_to_script_file path_to_cpp_miniscript_transpilation_file");
		Application::exit(1);
	}

	//
	tdme::tools::cli::MiniscriptUntranspiler::processFile(argv[1], argv[2]);
}
