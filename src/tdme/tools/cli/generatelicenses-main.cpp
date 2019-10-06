#include <string>
#include <vector>

#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

void scanDir(const string& folder, vector<string>& totalFiles) {
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

	FileSystem::getInstance()->list(folder, files, &listFilter);

	for (auto fileName: files) {
		if (fileName == "LICENSE") {
			totalFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, totalFiles);
		}
	}
}

void processFile(const string& fileName) {
	vector<string> lines;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, lines);
	Console::println(fileName);
	for (auto i = 0; i < fileName.size() + 2; i++) Console::print("-");
	Console::println();
	Console::println();
	for (auto& line: lines) {
		Console::println("\t" + line);
	}
	Console::println();
	Console::println();
}

int main(int argc, char** argv)
{
	Console::println(string("generate licenses 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();

	if (argc != 2) {
		Console::println("Usage: generatelicenses path");
		exit(0);
	}

	auto pathToHeaders = string(argv[1]);

	Console::println("Scanning files");
	vector<string> files;
	scanDir(pathToHeaders, files);

	Console::println("Processing files");
	for (auto fileName: files) {
		processFile(fileName);
	}
}
