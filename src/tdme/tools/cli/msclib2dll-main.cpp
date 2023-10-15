#include <set>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::set;
using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;


void parseHpp(const string& fileName) {
	Console::println("Processing file: " + fileName);
	vector<string> fileContent;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, fileContent);
	StringTokenizer lineStringTokenizer;
	auto symbolsMode = false;
	set<string> symbols;
	for (auto i = 0; i < fileContent.size(); i++) {
		auto line = fileContent[i];
		line = StringTools::trim(line);
		if (symbolsMode == false) {
			if (StringTools::endsWith(line, " public symbols") == true) {
				symbolsMode = true;
				i++;
			}
		} else {
			if (line.empty() == true) {
				symbolsMode = false;
			} else {
				lineStringTokenizer.tokenize(line, " ");
				if (lineStringTokenizer.hasMoreTokens() == true) lineStringTokenizer.nextToken();
				if (lineStringTokenizer.hasMoreTokens() == true) symbols.insert(lineStringTokenizer.nextToken());
			}
		}
	}
	vector<string> newFileContent;
	newFileContent.push_back("EXPORTS");
	for (const auto& symbol: symbols) newFileContent.push_back("\t" + symbol);
	FileSystem::getInstance()->setContentFromStringArray(".", fileName + ".def", newFileContent);
}

int main(int argc, char** argv)
{
	Console::println(string("msclib2dll ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	if (argc != 2) {
		Console::println("Usage: msclib2dll path_to_file");
		Console::println("Note: path_to_file can be obtained from dumpbin /LINKERMEMBER xyz.lib");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	parseHpp(argv[1]);

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
