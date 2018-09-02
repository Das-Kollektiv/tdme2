#include <string>
#include <vector>

#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Exception.h>
#include <tdme/utils/FilenameFilter.h>
#include <tdme/utils/StringTokenizer.h>
#include <tdme/utils/StringUtils.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utils::Console;
using tdme::utils::Exception;
using tdme::utils::FilenameFilter;
using tdme::utils::StringTokenizer;
using tdme::utils::StringUtils;

void scanDir(const string& folder, vector<string>& totalFiles) {
	class ListFilter : public virtual FilenameFilter {
		public:
			virtual ~ListFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::getInstance()->isPath(pathName + "/" + fileName) == true) return true;
				if (StringUtils::endsWith(StringUtils::toLowerCase(fileName), ".h") == true) return true;
				return false;
			}
	};

	ListFilter listFilter;
	vector<string> files;

	FileSystem::getInstance()->list(folder, files, &listFilter);

	for (auto fileName: files) {
		if (StringUtils::endsWith(fileName, ".h") == true) {
			totalFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, totalFiles);
		}
	}
}

void processFile(const string& fileName) {
	vector<string> fileContent;
	FileSystem::getInstance()->getContentAsStringArray(".", fileName, fileContent);
	int methodCount = 0;
	int paramCount = 0;
	bool haveMethod = false;
	bool hadMethod = false;
	int docLineStartIdx = -1;
	int docLineEndIdx = -1;
	int lineIdx = 0;
	vector<string> doc;
	vector<string> newFileContent;
	string method = "";
	for (auto line: fileContent) {
		newFileContent.push_back(line);
		if (haveMethod == false) {
			if (line.find("/**") != string::npos) {
				docLineStartIdx = lineIdx;
				doc.push_back(line);
				haveMethod = true;
				methodCount++;
				paramCount = 0;
			}
		} else {
			doc.push_back(line);
			if (line.find("@param ") != string::npos) {
				paramCount++;
			}
			if (line.find("*/") != string::npos) {
				docLineEndIdx = lineIdx;
				if (paramCount == 0) methodCount--;
				haveMethod = false;
				hadMethod = true;
				lineIdx++;
				continue;
			}
		}
		if (hadMethod) {
			method+= line;
			if (line.find(";") != string::npos || line.find("{") != string::npos) {
				method = StringUtils::trim(method);
				// parse parameter names
				if (paramCount > 0) {
					// Console::println(fileName + ": " + method + ": " + to_string(paramCount) + " / " + to_string(docLineStartIdx) + " - " + to_string(docLineEndIdx));
					bool paramBegin = false;
					bool paramIgnore = false;
					int smallerCount = 0;
					int roundBracketCount = 0;
					string param;
					vector<string> params;
					for (auto i = 0; i < method.length() && method[i] != ';' && method[i] != '{' && roundBracketCount >= 0; i++) {
						if (paramBegin == false) {
							if (method[i] == '(') paramBegin = true;
						} else
						if (method[i] == '<') {
							smallerCount++;
						} else
						if (method[i] == '(') {
							roundBracketCount++;
						} else
						if (method[i] == '>') {
							smallerCount--;
						} else
						if (method[i] == ')') {
							roundBracketCount--;
						} else
						if (method[i] == '=') {
							paramIgnore = true;
						} else
						if (smallerCount == 0 && roundBracketCount == 0){
							if (method[i] == ',') {
								param = StringUtils::trim(param);
								params.push_back(param);
								param = "";
								paramIgnore = false;
							} else
							if (paramIgnore == false) {
								param+= method[i];
							}
						}
					}
					if (param.length() > 0) {
						param = StringUtils::trim(param);
						params.push_back(param);
						param = "";
					}
					auto i = 0;
					StringTokenizer t;
					vector<string> paramsFinal;
					for (auto param: params) {
						t.tokenize(param, " ");
						while (t.hasMoreTokens() == true) param = t.nextToken();
						if (param.length() == 0) continue;
						paramsFinal.push_back(param);
					}
					int paramIdx = 0;
					vector<string> newDoc;
					for (auto docLine: doc) {
						size_t docLineParamIdx = docLine.find("@param ");
						if (docLineParamIdx != string::npos) {
							if (paramIdx < paramsFinal.size()) {
								docLine.insert(docLineParamIdx + 7, paramsFinal[paramIdx++] + " ");
							} else {
								Console::println("Warning: Missing parameter " + to_string(paramIdx));
							}
						}
						newDoc.push_back(docLine);
					}
					if (paramIdx != paramsFinal.size()) {
						Console::print("Warning: Having extra parameter: ");
						// for (auto i = paramIdx; i < paramsFinal.size(); i++) Console::print(paramsFinal[i] + " ");
						// Console::println();
					}
					for (auto i = docLineStartIdx; i <= docLineEndIdx; i++) {
						newFileContent[i] = newDoc[i - docLineStartIdx];
					}
				}
				hadMethod = false;
				doc.clear();
				method = "";
			}
		}
		lineIdx++;
	}
	FileSystem::getInstance()->setContentFromStringArray(".", fileName, newFileContent);
}

int main(int argc, char** argv)
{
	Console::println(string("fixdoxygen 1.9.9"));
	Console::println(string("Programmed 2018 by Andreas Drewke, drewke.net."));
	Console::println();

	if (argc != 2) {
		Console::println("Usage: fixdoxyen path_to_headers");
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
