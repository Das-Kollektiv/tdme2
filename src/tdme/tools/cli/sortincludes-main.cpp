#include <algorithm>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/math/Math.h>
#include <tdme/os/filesystem/FileNameFilter.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Character.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTokenizer.h>
#include <tdme/utilities/StringTools.h>

using std::sort;
using std::string;
using std::to_string;
using std::unique;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::math::Math;
using tdme::os::filesystem::FileNameFilter;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Character;
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
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".h") == true) return true;
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".cpp") == true) return true;
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(path, files, &listFilter);

	for (const auto& fileName: files) {
		if (StringTools::endsWith(fileName, ".h") == true ||
			StringTools::endsWith(fileName, ".cpp") == true) {
			totalFiles.push_back(path + "/" + fileName);
		} else {
			scanPath(path + "/" + fileName, totalFiles);
		}
	}
}

static int compare_includes(const string& lhs, const string& rhs) {
	auto charCount = Math::min((int32_t)lhs.size(), (int32_t)rhs.size());
	for (auto i = 0; i < charCount; i++) {
		if (lhs[i] == rhs[i]) {
			// no op
		} else {
			auto charLHS = lhs[i];
			auto charLCLHS = Character::toLowerCase(lhs[i]);
			auto charLHSLowerCase = charLHS == charLCLHS;
			auto charRHS = rhs[i];
			auto charLCRHS = Character::toLowerCase(rhs[i]);
			auto charRHSLowerCase = charRHS == charLCRHS;
			if (charLHSLowerCase == true && charRHSLowerCase == false) {
				return true;
			} else
			if (charLHSLowerCase == false && charRHSLowerCase == true) {
				return false;
			} else {
				return lhs < rhs;
			}
		}
	}
	return lhs.size() < rhs.size();
}

void parseHpp(const string& fileName) {
	Console::printLine("Processing file: " + fileName);
	vector<string> fileContent;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, fileContent);
	vector<string> newFileContent;
	// collect and sort includes
	{
		auto startLineIdx = -1;
		auto endLineIdx = -1;
		auto lineIdx = 0;
		for (const auto& line: fileContent) {
			if (StringTools::startsWith(line, "#include <tdme/tdme.h>") == true) continue;
			if (StringTools::startsWith(line, "#include <agui/agui.h>") == true) continue;
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
				sort(newFileContent.begin() + startLineIdx, newFileContent.begin() + endLineIdx + 1, compare_includes);
				startLineIdx = -1;
				endLineIdx = -1;
			}
			lineIdx++;
		}
	}
	// sort usings
	fileContent = newFileContent;
	newFileContent.clear();
	{
		auto startLineIdx = -1;
		auto endLineIdx = -1;
		auto lineIdx = 0;
		for (const auto& line: fileContent) {
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
				sort(newFileContent.begin() + startLineIdx, newFileContent.begin() + endLineIdx + 1, compare_includes);
				startLineIdx = -1;
				endLineIdx = -1;
			}
			lineIdx++;
		}
	}
	// inject #include <tdme/tdme.h> and #include <agui/agui.h>
	fileContent = newFileContent;
	newFileContent.clear();
	{
		auto hadTDMEInclude = false;
		auto hadAGUIInclude = false;
		auto lineIdx = 0;
		for (auto line: fileContent) {
			if (lineIdx > 0) {
				if (hadTDMEInclude == false && StringTools::startsWith(line, "#include <tdme/") == true) {
					newFileContent.push_back("#include <tdme/tdme.h>");
					hadTDMEInclude = true;
				} else
				if (hadAGUIInclude == false && StringTools::startsWith(line, "#include <agui/") == true) {
					newFileContent.push_back("#include <agui/agui.h>");
					hadAGUIInclude = true;
				}
			}
			newFileContent.push_back(line);
			lineIdx++;
		}
	}
	// remove double lines
	fileContent = newFileContent;
	newFileContent.clear();
	{
		string lastLine;
		for (const auto& line: fileContent) {
			if ((StringTools::startsWith(line, "using ") == true || StringTools::startsWith(line, "#include ")) && line == lastLine) {
				lastLine = line;
				continue;
			}
			newFileContent.push_back(line);
			lastLine = line;
		}
	}
	// inject newlines after tdme and agui stuff
	string lastLine;
	for (auto i = 0; i < newFileContent.size(); i++) {
		auto line = newFileContent[i];
		if (StringTools::startsWith(line, "#include <tdme/") == true && StringTools::startsWith(lastLine, "#include <agui/") == true) {
			newFileContent.insert(newFileContent.begin() + i, string());
		}
		if (StringTools::startsWith(line, "using tdme::") == true && StringTools::startsWith(lastLine, "using agui::") == true) {
			newFileContent.insert(newFileContent.begin() + i, string());
		}
		lastLine = line;
	}
	FileSystem::getInstance()->setContentFromStringArray(".", fileName, newFileContent);
}

int main(int argc, char** argv)
{
	Console::printLine(string("sortincludes ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	//
	if (argc != 2) {
		Console::printLine("Usage: sortincludes path_to_source");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	//
	auto pathToSource = string(argv[1]);

	//
	Console::printLine("Scanning files");
	vector<string> files;
	scanPath(pathToSource, files);

	//
	Console::printLine("Processing files");
	for (const auto& fileName: files) {
		parseHpp(fileName);
	}

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
