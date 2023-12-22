#include <miniscript/miniscript/Generator.h>

#include <array>
#include <string>
#include <utility>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/StringTools.h>

using miniscript::miniscript::Generator;

using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::StringTools;

using std::array;
using std::pair;
using std::string;
using std::vector;

void Generator::generateMain(
	const string& scriptURI,
	const string& className,
	const string& mainURI,
	bool useLibrary
) {
	string library;
	if (useLibrary == true) {
		library =
			string() +
			"auto library = make_unique<NativeLibrary>(context.get());" + "\n" +
			"\t" + "script->setLibrary(library.get());";
	}
	//
	try {
		Console::println("Generating main C++ file: " + mainURI);

		auto mainSource = FileSystem::getContentAsString("./resources/miniscript/templates/transpilation", "script-main.cpp");
		mainSource = StringTools::replace(mainSource, "{$script}", scriptURI);
		mainSource = StringTools::replace(mainSource, "{$script-class}", className);
		mainSource = StringTools::replace(mainSource, "{$library}", library);
		FileSystem::setContentFromString(FileSystem::getPathName(mainURI), FileSystem::getFileName(mainURI), mainSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateLibrary(
	const vector<pair<string, string>>& scriptClassPairs,
	const string& libraryURI
) {
	string libraryCode;
	libraryCode+= string() + "auto scriptURI = pathName + \"/\" + fileName;" + "\n";
	string libraryIncludes;
	for (const auto& scriptClassPair: scriptClassPairs) {
		auto scriptURI = scriptClassPair.first;
		auto className = scriptClassPair.second;
		libraryIncludes+= string() + "#include \"" + className + ".h\"" + "\n";
		libraryCode+= string() + "\t" + "if (scriptURI == \"" + scriptURI + "\") {" + "\n";
		libraryCode+= string() + "\t\t" + "script = make_unique<" + className + ">();" + "\n";
		libraryCode+= string() + "\t" + "} else" + "\n";
	}

	//
	try {
		Console::println("Generating library C++ file");
		auto mainSource = FileSystem::getContentAsString("./resources/miniscript/templates/transpilation", "NativeLibrary.cpp");
		mainSource = StringTools::replace(mainSource, "{$library-includes}", libraryIncludes);
		mainSource = StringTools::replace(mainSource, "{$library-code}", libraryCode);
		FileSystem::setContentFromString(FileSystem::getPathName(libraryURI), FileSystem::getFileName(libraryURI), mainSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath, const vector<string>& excludePaths) {
	//
	try {
		Console::println("Scanning source files");
		vector<string> sourceFiles;
		vector<string> mainSourceFiles;
		scanPath((basePath.empty() == true?"":basePath + "/") + srcPath, sourceFiles, mainSourceFiles);

		// cut off base path
		if (basePath.empty() == false) {
			for (auto& sourceFile: sourceFiles) sourceFile = StringTools::substring(sourceFile, basePath.size() + 1);
			for (auto& mainSourceFile: mainSourceFiles) mainSourceFile = StringTools::substring(mainSourceFile, basePath.size() + 1);
		}

		// exclude paths
		if (excludePaths.empty() == false) {
			array<vector<string>*, 2> sourceFileSets = { &sourceFiles, &mainSourceFiles };
			for (auto i = 0; i < sourceFileSets.size(); i++) {
				for (auto j = 0; j < sourceFileSets[i]->size(); j++) {
					for (const auto& excludePath: excludePaths) {
						if (StringTools::startsWith((*sourceFileSets[i])[j], srcPath + "/" + excludePath + "/") == true) {
							sourceFileSets[i]->erase(sourceFileSets[i]->begin() + j);
							j--;
							break;
						}
					}
				}
			}
		}

		//
		string sourceFilesVariable = "\\\n";
		for (const auto& file: sourceFiles) sourceFilesVariable+= "\t" + file + " \\\n";
		sourceFilesVariable+= "\n";

		//
		string mainSourceFilesVariable = "\\\n";
		for (const auto& file: mainSourceFiles) mainSourceFilesVariable+= "\t" + file + " \\\n";
		mainSourceFilesVariable+= "\n";

		//
		Console::println("Generating Makefile");

		//
		auto makefileSource = FileSystem::getContentAsString("./resources/miniscript/templates/makefiles", library == true?"Library-Makefile":"Makefile");
		makefileSource = StringTools::replace(makefileSource, "{$source-path}", srcPath);
		makefileSource = StringTools::replace(makefileSource, "{$source-files}", sourceFilesVariable);
		if (library == false) makefileSource = StringTools::replace(makefileSource, "{$main-source-files}", mainSourceFilesVariable);
		FileSystem::setContentFromString(FileSystem::getPathName(makefileURI), FileSystem::getFileName(makefileURI), makefileSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateNMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath, const vector<string>& excludePaths) {
	//
	try {
		Console::println("Scanning source files");
		vector<string> sourceFiles;
		vector<string> mainSourceFiles;
		scanPath((basePath.empty() == true?"":basePath + "/") + srcPath, sourceFiles, mainSourceFiles);

		// cut off base path
		if (basePath.empty() == false) {
			for (auto& sourceFile: sourceFiles) sourceFile = StringTools::substring(sourceFile, basePath.size() + 1);
			for (auto& mainSourceFile: mainSourceFiles) mainSourceFile = StringTools::substring(mainSourceFile, basePath.size() + 1);
		}

		// exclude paths
		if (excludePaths.empty() == false) {
			array<vector<string>*, 2> sourceFileSets = { &sourceFiles, &mainSourceFiles };
			for (auto i = 0; i < sourceFileSets.size(); i++) {
				for (auto j = 0; j < sourceFileSets[i]->size(); j++) {
					for (const auto& excludePath: excludePaths) {
						if (StringTools::startsWith((*sourceFileSets[i])[j], srcPath + "/" + excludePath + "/") == true) {
							sourceFileSets[i]->erase(sourceFileSets[i]->begin() + j);
							j--;
							break;
						}
					}
				}
			}
		}

		//
		string sourceFilesVariable = "\\\n";
		for (const auto& file: sourceFiles) sourceFilesVariable+= "\t" + file + " \\\n";
		sourceFilesVariable+= "\n";

		//
		string makefileSource;

		//
		if (library == true) {
			Console::println("Generating Makefile");
			//
			makefileSource = FileSystem::getContentAsString("./resources/miniscript/templates/makefiles", "Library-Makefile.nmake");
			auto makefileMainSourceTemplate = FileSystem::getContentAsString("./resources/miniscript/templates/makefiles", "Makefile.nmake.main");
			makefileSource = StringTools::replace(makefileSource, "{$source-files}", sourceFilesVariable);
			makefileSource+= "\n";
		} else {
			//
			string mainTargets;
			for (const auto& file: mainSourceFiles) {
				if (mainTargets.empty() == false) mainTargets+= " ";
				mainTargets+= StringTools::substring(file, file.rfind('/') + 1, file.find("-main.cpp"));
			}
			//
			Console::println("Generating Makefile");
			//
			makefileSource = FileSystem::getContentAsString("./resources/miniscript/templates/makefiles", "Makefile.nmake");
			auto makefileMainSourceTemplate = FileSystem::getContentAsString("./resources/miniscript/templates/makefiles", "Makefile.nmake.main");
			makefileSource = StringTools::replace(makefileSource, "{$source-files}", sourceFilesVariable);
			makefileSource = StringTools::replace(makefileSource, "{$main-targets}", mainTargets);
			makefileSource+= "\n";

			//
			for (const auto& file: mainSourceFiles) {
				auto makefileMainSource = makefileMainSourceTemplate;
				auto mainTarget = StringTools::substring(file, file.rfind('/') + 1, file.find("-main.cpp"));
				auto mainTargetSource = file;
				auto mainTargetExecutable = mainTarget + ".exe";
				makefileMainSource = StringTools::replace(makefileMainSource, "{$main-target}", mainTarget);
				makefileMainSource = StringTools::replace(makefileMainSource, "{$main-target-source}", mainTargetSource);
				makefileMainSource = StringTools::replace(makefileMainSource, "{$main-target-executable}", mainTargetExecutable);
				makefileSource+= makefileMainSource + "\n";
			}
		}
		//
		FileSystem::setContentFromString(FileSystem::getPathName(makefileURI), FileSystem::getFileName(makefileURI), makefileSource);
	} catch (Exception& exception) {
		Console::println("An error occurred: " + string(exception.what()));
	}
}

void Generator::scanPath(const string& path, vector<string>& sourceFiles, vector<string>& mainSourceFiles) {
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
	//
	SourceFilesFilter sourceFilesFilter;
	vector<string> files;
	//
	FileSystem::list(path, files, &sourceFilesFilter);
	//
	for (const auto& fileName: files) {
		if (StringTools::endsWith(fileName, "-main.cpp") == true) {
			mainSourceFiles.push_back(path + "/" + fileName);
		} else
		if (StringTools::endsWith(fileName, ".cpp") == true) {
			sourceFiles.push_back(path + "/" + fileName);
		} else {
			scanPath(path + "/" + fileName, sourceFiles, mainSourceFiles);
		}
	}
}
