#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/tools/editor/misc/Tools.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/StringTools.h>

using std::set;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::tools::editor::misc::Tools;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::Integer;
using tdme::utilities::MiniScript;
using tdme::utilities::StringTools;

void gatherMethodCode(const vector<string>& miniScriptExtensionsCode, const string& className, int registerLine, unordered_map<string, vector<string>>& methodCodeMap) {
	// TODO: this is a bit ugly and can be improved a lot, lets see and get this to work first
	auto classDefinitionLine = -1;
	// get class definition start line
	for (auto i = registerLine; i >= 0; i--) {
		auto& line = miniScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		if (StringTools::regexMatch(trimmedLine, "class[\\ \\t]+" + className + "[\\ \\t]*:.*") == true) {
			classDefinitionLine = i;
			break;
		}
	}
	// nope
	if (classDefinitionLine == -1) {
		Console::println("gatherMethodCode(): did not found '" + className + "' definition");
		return;
	}
	//
	auto curlyBracketCount = 0;
	auto finished = false;
	auto haveExecuteMethodDeclaration = false;
	auto executeMethodCurlyBracketStart = -1;
	auto haveGetMethodNameDeclaration = false;
	auto getMethodNameCurlyBracketStart = -1;
	vector<string> executeMethodCode;
	string getMethodNameCode;
	for (auto i = classDefinitionLine; finished == false && i < miniScriptExtensionsCode.size(); i++) {
		auto& line = miniScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		// have getMethodName declaration, with following body
		if (StringTools::regexMatch(trimmedLine, "const[\\ \\t]+string[\\ \\t]+getMethodName()[\\ \\t]*\\(.*") == true) {
			haveGetMethodNameDeclaration = true;
		}
		// have executeMethod declaration, with following body
		if (StringTools::regexMatch(trimmedLine, "void[\\ \\t]+executeMethod[\\ \\t]*\\(.*") == true) {
			haveExecuteMethodDeclaration = true;
		}
		//
		for (auto j = 0; j < trimmedLine.size(); j++) {
			auto c = trimmedLine[j];
			if (c == '{') {
				curlyBracketCount++;
				// new code block,
				// 	if we have the declaration mark this curly bracket as executeMethod implementation start curly bracket
				if (haveExecuteMethodDeclaration == true) {
					executeMethodCurlyBracketStart = curlyBracketCount;
				}
				// 	if we have the declaration mark this curly bracket as getMethodName implementation start curly bracket
				if (haveGetMethodNameDeclaration == true) {
					getMethodNameCurlyBracketStart = curlyBracketCount;
				}
			} else
			if (c == '}') {
				// do we just leave our getMethodName implementation?
				if (getMethodNameCurlyBracketStart != -1 && curlyBracketCount == getMethodNameCurlyBracketStart) {
					// yup
					getMethodNameCurlyBracketStart = -1;
				}
				// do we just leave our executeMethod implementation?
				if (executeMethodCurlyBracketStart != -1 && curlyBracketCount == executeMethodCurlyBracketStart) {
					// yup
					executeMethodCurlyBracketStart = -1;
				}
				//
				curlyBracketCount--;
				// get out of here :D
				if (curlyBracketCount <= 0) {
					finished = true;
					break;
				}
			}
		}
		// is this getMethodName code?
		if (haveGetMethodNameDeclaration == false && getMethodNameCurlyBracketStart != -1 && curlyBracketCount >= getMethodNameCurlyBracketStart) {
			getMethodNameCode+= trimmedLine;
		}
		// is this executeMethod code?
		if (haveExecuteMethodDeclaration == false && executeMethodCurlyBracketStart != -1 && curlyBracketCount >= executeMethodCurlyBracketStart) {
			executeMethodCode.push_back(line);
		}
		// do we still process getMethodName declaration
		if (haveGetMethodNameDeclaration == true) {
			// ok unset
			haveGetMethodNameDeclaration = false;
		}
		// do we still process executeMethod declaration
		if (haveExecuteMethodDeclaration == true) {
			// ok unset
			haveExecuteMethodDeclaration = false;
		}
	}

	// determine method name
	string methodName;
	{
		auto haveMethodName = false;
		for (auto i = 0; i < getMethodNameCode.size(); i++) {
			auto c = getMethodNameCode[i];
			if (c == '"') {
				if (haveMethodName == false) haveMethodName = true; else
					break;
			} else
			if (haveMethodName == true) {
				methodName+= c;
			}
		}
	}

	// find min indent from method code and depth indent
	int minIndent = Integer::MAX_VALUE;
	for (auto& codeLine: executeMethodCode) {
		auto indent = 0;
		for (auto i = 0; i < codeLine.size(); i++) {
			auto c = codeLine[i];
			if (c == '\t') {
				indent++;
			} else {
				break;
			}
		}
		minIndent = Math::min(minIndent, indent);
	}

	// remove indent
	for (auto& codeLine: executeMethodCode) {
		codeLine = StringTools::substring(codeLine, minIndent);
	}

	//
	auto methodCodeMapIt = methodCodeMap.find(methodName);
	if (methodCodeMapIt != methodCodeMap.end()) {
		Console::println("gatherMethodCode(): Not registering method with methodName: '" + methodName + "': method already registered");
		return;
	}

	//
	Console::println("gatherMethodCode(): registering method with methodName: '" + methodName + "'");

	//
	methodCodeMap[methodName] = executeMethodCode;
}

void processFile(const string& scriptFileName, const string& miniscriptExtensionsFileName) {
	Console::println("Processing script: " + scriptFileName);

	//
	unordered_map<string, vector<string>> methodCodeMap;

	//
	vector<string> miniScriptExtensionsCode;
	FileSystem::getInstance()->getContentAsStringArray("src/tdme/utilities", "MiniScript.cpp", miniScriptExtensionsCode);
	for (auto i = 0; i < miniScriptExtensionsCode.size(); i++) {
		auto& line = miniScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		if (StringTools::startsWith(trimmedLine, "registerMethod") == true) {
			auto bracketCount = 0;
			string className;
			auto classNameStartIdx = StringTools::firstIndexOf(StringTools::substring(trimmedLine, 14), "new");
			if (classNameStartIdx == string::npos) {
				Console::println("src/tdme/utilities/MiniScript.cpp: registerMethod @ " + to_string(i) + ": '" + trimmedLine + "': unable to determine class name");
			} else {
				classNameStartIdx+= 14 + 3;
				for (auto j = classNameStartIdx; j < trimmedLine.size(); j++) {
					auto c = trimmedLine[j];
					if (c == '(') break;
					if (c == ' ') continue;
					className+= c;
				}
				gatherMethodCode(miniScriptExtensionsCode, className, i, methodCodeMap);
			}
		}
	}

	//
	MiniScript* script = new MiniScript();
	script->loadScript(Tools::getPathName(scriptFileName), Tools::getFileName(scriptFileName));

	Console::println(script->getInformation());

	//
	string generatedCode;
	script->transpile(generatedCode, "nothing", methodCodeMap);

	//
	vector<string> miniScriptClass;
	vector<string> miniScriptClassNew;
	FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptExtensionsFileName), Tools::getFileName(miniscriptExtensionsFileName), miniScriptClass);
	auto reject = false;
	auto injectedGeneratedCode = false;
	for (auto i = 0; i < miniScriptClass.size(); i++) {
		auto& line = miniScriptClass[i];
		auto trimmedLine = StringTools::trim(line);
		if (StringTools::startsWith(trimmedLine, "//") == true) {
			if (reject == false) miniScriptClassNew.push_back(line);
			continue;
		}
		if (trimmedLine == "/*__MINISCRIPT_TRANSPILED_NOTHING_START__*/") {
			reject = true;
			miniScriptClassNew.push_back(line);
		} else
		if (trimmedLine == "/*__MINISCRIPT_TRANSPILED_NOTHING_END__*/") {
			reject = false;
			injectedGeneratedCode = true;
			miniScriptClassNew.push_back(generatedCode);
			miniScriptClassNew.push_back(line);
		} else {
			if (reject == false) miniScriptClassNew.push_back(line);
		}
	}

	//
	if (injectedGeneratedCode == false) {
		Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILED_NOTHING_START__*/ and /*__MINISCRIPT_TRANSPILED_NOTHING_END__*/ markers in file " + miniscriptExtensionsFileName + "?");
	} else {
		//
		FileSystem::getInstance()->setContentFromStringArray(
			Tools::getPathName(miniscriptExtensionsFileName),
			Tools::getFileName(miniscriptExtensionsFileName),
			miniScriptClassNew
		);
		//
		Console::println(scriptFileName + ": Injected generated C++ code in file " + miniscriptExtensionsFileName + ". Dont forget to rebuild your sources.");
	}
}

int main(int argc, char** argv)
{
	Console::println(string("miniscripttranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc != 3) {
		Console::println("Usage: miniscripttranspiler path_to_script_file path_to_cpp_miniscript_extensions");
		Application::exit(1);
	}

	//
	processFile(argv[1], argv[2]);
}
