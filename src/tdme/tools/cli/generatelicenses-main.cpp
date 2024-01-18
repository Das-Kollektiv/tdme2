#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

void scanPath(const string& path, vector<string>& totalFiles) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				if (fileName == "LICENSE") return true;
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(path, files, &listFilter);

	for (const auto& fileName: files) {
		if (fileName == "LICENSE") {
			totalFiles.push_back(path + "/" + fileName);
		} else {
			scanPath(path + "/" + fileName, totalFiles);
		}
	}
}

void processFile(const string& indent, const string& fileName) {
	auto _fileName = StringTools::startsWith(fileName, "./") == true?StringTools::substring(fileName, 2, fileName.size()):fileName;
	vector<string> lines;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, lines);
	Console::printLine(indent + _fileName);
	Console::print(indent);
	for (auto i = 0; i < _fileName.size() + 2; i++) Console::print("-");
	Console::printLine();
	Console::printLine();
	for (const auto& line: lines) {
		if (StringTools::trim(line).size() == 0) {
			Console::printLine();
		} else {
			Console::printLine(indent + "\t" + line);
		}
	}
	Console::printLine();
	Console::printLine();
}

int main(int argc, char** argv)
{
	Console::printLine(string("generatelicenses ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	auto pathToHeaders = "."; // we do search in pwd
	auto indent = argc > 1?string(argv[1]):string();

	if (argc > 2 || (argc == 2 && indent.empty() == false && indent != "--indent")) {
		Console::printLine("Usage: generatelicenses [--indent]");
		Application::exit(1);
	}

	if (indent == "--indent") indent = "\t";

	Console::printLine("Scanning files");
	vector<string> files;
	scanPath(pathToHeaders, files);

	Console::printLine("Processing files");
	Console::printLine("------------------");
	Console::printLine();
	for (const auto& fileName: files) {
		if (fileName == "./LICENSE") continue; // ignore own project license
		processFile(indent, fileName);
	}

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
