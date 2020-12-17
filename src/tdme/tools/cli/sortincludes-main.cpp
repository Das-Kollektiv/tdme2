#include <algorithm>
#include <string>
#include <vector>

#include <tdme/application/Application.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::sort;
using std::string;
using std::to_string;
using std::vector;

using tdme::application::Application;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::StringTokenizer;
using tdme::utilities::StringTools;

void scanDir(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FileNameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".h") == true) return true;
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".cpp") == true) return true;
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(folder, files, &listFilter);

	for (auto fileName: files) {
		if (StringTools::endsWith(fileName, ".h") == true ||
			StringTools::endsWith(fileName, ".cpp") == true) {
			totalFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, totalFiles);
		}
	}
}

void processFile(const string& fileName) {
	Console::println("Processing file: " + fileName);
	vector<string> fileContent;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, fileContent);
	vector<string> newFileContent;
	string method = "";
	{
		auto startLineIdx = -1;
		auto endLineIdx = -1;
		auto lineIdx = 0;
		for (auto line: fileContent) {
			StringTools::replace(line, "\n", "");
			StringTools::replace(line, "\r", "");
			newFileContent.push_back(line);
			if (StringTools::startsWith(line, "#include ") == true) {
				if (startLineIdx == -1) {
					startLineIdx = lineIdx;
					endLineIdx = lineIdx;
				} else {
					endLineIdx = lineIdx;
				}
			} else
			if (startLineIdx != -1 && endLineIdx != -1) {
				sort(newFileContent.begin() + startLineIdx, newFileContent.begin() + endLineIdx);
				startLineIdx = -1;
				endLineIdx = -1;
			}
			lineIdx++;
		}
	}
	fileContent = newFileContent;
	newFileContent.clear();
	{
		auto startLineIdx = -1;
		auto endLineIdx = -1;
		auto lineIdx = 0;
		for (auto line: fileContent) {
			StringTools::replace(line, "\n", "");
			StringTools::replace(line, "\r", "");
			newFileContent.push_back(line);
			if (StringTools::startsWith(line, "using ") == true) {
				if (startLineIdx == -1) {
					startLineIdx = lineIdx;
					endLineIdx = lineIdx;
				} else {
					endLineIdx = lineIdx;
				}
			} else
			if (startLineIdx != -1 && endLineIdx != -1) {
				sort(newFileContent.begin() + startLineIdx, newFileContent.begin() + endLineIdx);
				startLineIdx = -1;
				endLineIdx = -1;
			}
			lineIdx++;
		}
	}
	FileSystem::getInstance()->setContentFromStringArray(".", fileName, newFileContent);
}

int main(int argc, char** argv)
{
	Console::println(string("sortincludes 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();

	if (argc != 2) {
		Console::println("Usage: sortincludes path_to_source");
		Application::exit(1);
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
