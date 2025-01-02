#include <minitscript/minitscript/Generator.h>

#include <array>
#include <string>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/StringTools.h>

using minitscript::minitscript::Generator;

using minitscript::os::filesystem::FileSystem;
using minitscript::utilities::Console;
using minitscript::utilities::Exception;
using minitscript::utilities::StringTools;

using std::array;
using std::pair;
using std::string;
using std::vector;

void Generator::generateMain(
	const string& scriptURI,
	const string& className,
	const string& mainURI,
	bool useLibrary,
	bool nativeOnly
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
		Console::printLine("Generating main C++ file: " + mainURI);

		auto mainSource = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/transpilation", "script-main.cpp");
		mainSource = StringTools::replace(mainSource, "{$script}", scriptURI);
		mainSource = StringTools::replace(mainSource, "{$script-class}", className);
		mainSource = StringTools::replace(mainSource, "{$library}", library);
		mainSource = StringTools::replace(mainSource, "{$native-only}", nativeOnly == true?"true":"false");
		FileSystem::setContentFromString(FileSystem::getPathName(mainURI), FileSystem::getFileName(mainURI), mainSource);
	} catch (Exception& exception) {
		Console::printLine("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateLibrary(
	const vector<pair<string, string>>& scriptClassPairs,
	const string& libraryURI,
	bool nativeOnly
) {
	string libraryCode;
	libraryCode+= string() + "auto scriptURI = pathName + \"/\" + fileName;" + "\n";
	string libraryIncludes;
	for (const auto& scriptClassPair: scriptClassPairs) {
		const auto& scriptURI = scriptClassPair.first;
		const auto& className = scriptClassPair.second;
		libraryIncludes+= string() + "#include \"" + className + ".h\"" + "\n";
		libraryCode+= string() + "\t" + "if (scriptURI == \"" + scriptURI + "\") {" + "\n";
		libraryCode+= string() + "\t\t" + "script = make_unique<" + className + ">();" + "\n";
		libraryCode+= string() + "\t\t" + "if (script->isModule() == true) {" + "\n";
		libraryCode+= string() + "\t\t\t" + "script = nullptr;" + "\n";
		libraryCode+= string() + "\t\t\t" + "_Console::printLine(scriptURI + \": Unable to load a module script.\");" + "\n";
		libraryCode+= string() + "\t\t" + "}" + "\n";
		libraryCode+= string() + "\t" + "} else" + "\n";
	}

	//
	try {
		Console::printLine("Generating library C++ file");
		auto mainSource = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/transpilation", "NativeLibrary.cpp");
		mainSource = StringTools::replace(mainSource, "{$library-includes}", libraryIncludes);
		mainSource = StringTools::replace(mainSource, "{$library-code}", libraryCode);
		mainSource = StringTools::replace(mainSource, "{$native-only}", nativeOnly == true?"true":"false");
		FileSystem::setContentFromString(FileSystem::getPathName(libraryURI), FileSystem::getFileName(libraryURI), mainSource);
	} catch (Exception& exception) {
		Console::printLine("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath, const vector<string>& excludePaths) {
	//
	try {
		Console::printLine("Scanning source files");
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
		Console::printLine("Generating Makefile");

		//
		auto makefileSource = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/makefiles", library == true?"Library-Makefile":"Makefile");
		makefileSource = StringTools::replace(makefileSource, "{$MINITSCRIPT_DATA}", MINITSCRIPT_DATA);
		makefileSource = StringTools::replace(makefileSource, "{$source-path}", srcPath);
		makefileSource = StringTools::replace(makefileSource, "{$source-files}", sourceFilesVariable);
		if (library == false) makefileSource = StringTools::replace(makefileSource, "{$main-source-files}", mainSourceFilesVariable);
		FileSystem::setContentFromString(FileSystem::getPathName(makefileURI), FileSystem::getFileName(makefileURI), makefileSource);
	} catch (Exception& exception) {
		Console::printLine("An error occurred: " + string(exception.what()));
	}
}

void Generator::generateNMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath, const vector<string>& excludePaths) {
	//
	try {
		Console::printLine("Scanning source files");
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
			Console::printLine("Generating Makefile");
			//
			makefileSource = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/makefiles", "Library-Makefile.nmake");
			auto makefileMainSourceTemplate = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/makefiles", "Makefile.nmake.main");
			makefileSource = StringTools::replace(makefileSource, "{$MINITSCRIPT_DATA}", MINITSCRIPT_DATA);
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
			Console::printLine("Generating Makefile");
			//
			makefileSource = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/makefiles", "Makefile.nmake");
			auto makefileMainSourceTemplate = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/makefiles", "Makefile.nmake.main");
			makefileSource = StringTools::replace(makefileSource, "{$MINITSCRIPT_DATA}", MINITSCRIPT_DATA);
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
		Console::printLine("An error occurred: " + string(exception.what()));
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
