#pragma once

#include <string>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/fwd-minitscript.h>

using std::pair;
using std::string;
using std::vector;

/**
 * MinitScript generator
 * @author Andreas Drewke
 */
class minitscript::minitscript::Generator {
public:

	/**
	 * Generate main CPP file
	 * @param scriptURI script URI
	 * @param className script class name
	 * @param mainURI main C++ file URI
	 * @param useLibrary use library
	 * @param nativeOnly native only
	 */
	static void generateMain(
		const string& scriptURI,
		const string& className,
		const string& mainURI,
		bool useLibrary,
		bool nativeOnly
	);

	/**
	 * Generate library CPP file
	 * @param scriptClassPairs script class pairs
	 * @param libraryURI library URI
	 * @param nativeOnly native only
	 */
	static void generateLibrary(
		const vector<pair<string, string>>& scriptClassPairs,
		const string& libraryURI,
		bool nativeOnly
	);

	/**
	 * Generate Makefile
	 * @param srcPath source path
	 * @param makefileURI makefile URI
	 * @param library library
	 * @param basePath base path
	 * @param excludePaths exclude paths
	 */
	static void generateMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath = string(), const vector<string>& excludePaths = {});

	/**
	 * Generate NMakefile
	 * @param srcPath source path
	 * @param makefileURI makefile URI
	 * @param library library
	 * @param basePath base path
	 * @param excludePaths exclude paths
	 */
	static void generateNMakefile(const string& srcPath, const string& makefileURI, bool library, const string& basePath = string(), const vector<string>& excludePaths = {});

private:

	/**
	 * Scan path
	 * @param path path
	 * @param sourceFiles source files
	 * @param mainSourceFiles main source files
	 */
	static void scanPath(const string& path, vector<string>& sourceFiles, vector<string>& mainSourceFiles);

};
