#include <cstdlib>
#include <string>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/FileSystem.h>
#include <miniscript/utilities/StringTools.h>

using std::exit;
using std::string;
using std::to_string;
using std::vector;

using miniscript::miniscript::Version;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::FileSystem;
using miniscript::utilities::StringTools;

void scanDir(const string& folder, vector<string>& sourceFiles, vector<string>& mainSourceFiles) {
	class SourceFilesFilter : public virtual FileSystem::FileNameFilter {
		public:
			virtual ~SourceFilesFilter() {}

			bool accept(const string& pathName, const string& fileName) override {
				if (fileName == ".") return false;
				if (fileName == "..") return false;
				if (FileSystem::isPath(pathName + "/" + fileName) == true) return true;
				// skip on CPP files that gets #include ed
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".incl.cpp") == true) return false;
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".include.cpp") == true) return false;
				// CPP hit, yes
				if (StringTools::endsWith(StringTools::toLowerCase(fileName), ".cpp") == true) return true;
				return false;
			}
	};

	SourceFilesFilter sourceFilesFilter;
	vector<string> files;

	FileSystem::list(folder, files, &sourceFilesFilter);

	for (const auto& fileName: files) {
		if (StringTools::endsWith(fileName, "-main.cpp") == true) {
			mainSourceFiles.push_back(folder + "/" + fileName);
		} else
		if (StringTools::endsWith(fileName, ".cpp") == true) {
			sourceFiles.push_back(folder + "/" + fileName);
		} else {
			scanDir(folder + "/" + fileName, sourceFiles, mainSourceFiles);
		}
	}
}

int main(int argc, char** argv)
{
	Console::println(string("miniscriptmakefile ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc != 2) {
		Console::println("Usage: miniscriptmakefile path_to_source");
		exit(EXIT_FAILURE);
	}

	//
	auto pathToSource = string(argv[1]);

	//
	try {
		Console::println("Scanning source files");
		vector<string> sourceFiles;
		vector<string> mainSourceFiles;
		scanDir(pathToSource, sourceFiles, mainSourceFiles);

		string sourceFilesVariable = "\\\n";
		for (const auto& file: sourceFiles) sourceFilesVariable+= "\t" + file + "\\\n";
		sourceFilesVariable+= "\n";

		string mainSourceFilesVariable = "\\\n";
		for (const auto& file: mainSourceFiles) mainSourceFilesVariable+= "\t" + file + "\\\n";
		mainSourceFilesVariable+= "\n";

		Console::println("Generating Makefile");

		auto makefileSource = FileSystem::getContentAsString("./resources/templates/makefiles", "Makefile");
		makefileSource = StringTools::replace(makefileSource, "{$source-files}", sourceFilesVariable);
		makefileSource = StringTools::replace(makefileSource, "{$main-source-files}", mainSourceFilesVariable);
		FileSystem::setContentFromString(".", "Makefile", makefileSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}

	//
	exit(EXIT_SUCCESS);
}
