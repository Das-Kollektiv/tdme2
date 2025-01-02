#include <minitscript/minitscript/Transpiler.h>

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/math/Math.h>
#include <minitscript/os/filesystem/FileSystem.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Character.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Exception.h>
#include <minitscript/utilities/Integer.h>
#include <minitscript/utilities/StringTools.h>
#include <minitscript/utilities/UTF8StringTools.h>

using minitscript::minitscript::Transpiler;

using std::find;
using std::remove;
using std::sort;
using std::string;
using std::string_view;
using std::to_string;
using std::unique;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using minitscript::math::Math;
using minitscript::os::filesystem::FileSystem;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Transpiler;
using minitscript::minitscript::Version;
using minitscript::utilities::Character;
using minitscript::utilities::Console;
using minitscript::utilities::Exception;
using minitscript::utilities::Integer;
using minitscript::utilities::StringTools;
using minitscript::utilities::UTF8StringTools;

void Transpiler::transpile(MinitScript* minitScript, const string& transpilationFileName, const vector<string>& minitScriptExtensionFileNames) {
	auto scriptFileName = minitScript->getScriptPathName() + "/" + minitScript->getScriptFileName();
	//
	Console::printLine(scriptFileName + ": Processing script");
	//
	auto replace = [](const vector<string> input, const string& startTag, const string& endTag, const string& replacement, vector<string>& output) -> bool {
		auto reject = false;
		auto replaceSuccess = false;
		for (auto i = 0; i < input.size(); i++) {
			const auto& line = input[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) output.push_back(line);
				continue;
			}
			if (trimmedLine == startTag) {
				reject = true;
				output.push_back(line);
			} else
			if (trimmedLine == endTag) {
				reject = false;
				replaceSuccess = true;
				output.push_back(replacement);
				output.push_back(line);
			} else {
				if (reject == false) output.push_back(line);
			}
		}
		//
		return replaceSuccess;
	};

	//
	unordered_map<string, vector<string>> methodCodeMap;
	auto allMethods = getAllClassesMethodNames(minitScript);

	//
	vector<string> transpilationUnitIncludes;
	vector<string> transpilationUnitUsings;

	//
	vector<string> transpilationUnits;
	for (const auto& transpilationUnit: minitScript->getTranspilationUnits()) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: minitScriptExtensionFileNames) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: transpilationUnits) {
		vector<string> transpilationUnitCode;
		FileSystem::getContentAsStringArray(FileSystem::getPathName(transpilationUnit), FileSystem::getFileName(transpilationUnit), transpilationUnitCode);
		for (auto i = 0; i < transpilationUnitCode.size(); i++) {
			const auto& line = transpilationUnitCode[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "#include ") == true) {
				transpilationUnitIncludes.push_back(trimmedLine);
			} else
			if (StringTools::startsWith(trimmedLine, "using ") == true) {
				transpilationUnitUsings.push_back(trimmedLine);
			}
			if (StringTools::startsWith(trimmedLine, "registerMethod") == true ||
				StringTools::startsWith(trimmedLine, "minitScript->registerMethod") == true) {
				auto bracketCount = 0;
				string className;
				if (StringTools::firstIndexOf(StringTools::substring(trimmedLine, 14), "new") == string::npos) {
					Console::printLine(transpilationUnit + ": registerMethod @ " + to_string(i) + ": '" + trimmedLine + "': unable to determine class name");
				} else {
					auto classNameStartIdx = trimmedLine.find("registerMethod") + 14 + 5;
					for (auto j = classNameStartIdx; j < trimmedLine.size(); j++) {
						auto c = trimmedLine[j];
						if (c == '(') break;
						if (c == ' ') continue;
						className+= c;
					}
					gatherMethodCode(transpilationUnitCode, className, i, methodCodeMap);
				}
			}
		}
	}
	//
	sort(transpilationUnitIncludes.begin(), transpilationUnitIncludes.end());
	transpilationUnitIncludes.erase(unique(transpilationUnitIncludes.begin(), transpilationUnitIncludes.end()), transpilationUnitIncludes.end());

	//
	sort(transpilationUnitUsings.begin(), transpilationUnitUsings.end());
	transpilationUnitUsings.erase(unique(transpilationUnitUsings.begin(), transpilationUnitUsings.end()), transpilationUnitUsings.end());

	//
	Console::printLine(minitScript->getInformation());

	//
	const auto& scripts = minitScript->getScripts();

	// determine variables
	unordered_set<string> globalVariables;
	vector<unordered_set<string>> localVariables(scripts.size());
	determineVariables(minitScript, globalVariables, localVariables);

	//
	string declarationIndent = "\t";
	string definitionIndent = "\t";
	string generatedExecuteCode;
	if (minitScript->isModule() == false) {
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			auto methodName = createMethodName(minitScript, scriptIdx);
			if (script._module.empty() == false) {
				const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(script._module, "[^0-9a-zA-Z]", "_");
				generatedExecuteCode+= declarationIndent + "\t\t" + "if (getScriptState().scriptIdx == " + to_string(scriptIdx) + ") " + moduleObjectName + "->export_" + methodName + "(scriptState.statementIdx); else\n";
			} else {
				generatedExecuteCode+= declarationIndent + "\t\t" + "if (getScriptState().scriptIdx == " + to_string(scriptIdx) + ") " + methodName + "(scriptState.statementIdx); else\n";
			}
			scriptIdx++;
		}
	}
	if (generatedExecuteCode.empty() == false) generatedExecuteCode+= declarationIndent + "\t\t\t" + ";\n";

	// determine "initialize" and "nothing" script indices
	auto initializeScriptIdx = -1;
	auto nothingScriptIdx = -1;
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true) {
				if (script.condition == "nothing") nothingScriptIdx = scriptIdx;
				if (script.condition == "initialize") initializeScriptIdx = scriptIdx;
			}
			//
			scriptIdx++;
		}
	}

	// member access evaluation
	vector<string> memberAccessEvaluationDeclarations;
	vector<string> memberAccessEvaluationDefinitions;
	generateEvaluateMemberAccessArrays(minitScript, memberAccessEvaluationDeclarations, memberAccessEvaluationDefinitions);

	// module classes
	vector<string> moduleClassesDeclarations;
	if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
		moduleClassesDeclarations.push_back(string() + "// module classes declarations");
		for (const auto& _module: minitScript->getModules()) {
			const auto includePathName = minitScript->getScriptPathName();
			const auto includeFileName = _module;
			const auto moduleClassName = string() + "_" + UTF8StringTools::regexReplace((includePathName.empty() == false?includePathName + "/":"") + includeFileName, "[^0-9a-zA-Z]", "_");
			const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(includeFileName, "[^0-9a-zA-Z]", "_");
			moduleClassesDeclarations.push_back("unique_ptr<" + moduleClassName + "> " + moduleObjectName + ";");
		}
		moduleClassesDeclarations.push_back(string());
	}

	//
	string minitScriptClassName = FileSystem::getFileName(transpilationFileName);
	string generatedDeclarations = "\n";
	generatedDeclarations+= declarationIndent + "/**" + "\n";
	generatedDeclarations+= declarationIndent + " * Public destructor" + "\n";
	generatedDeclarations+= declarationIndent + " */" + "\n";
	generatedDeclarations+= declarationIndent + "inline ~" + minitScriptClassName + "() {" + "\n";
	generatedDeclarations+= declarationIndent + "\t" + "if (native == true) {" + "\n";
	generatedDeclarations+= declarationIndent + "\t\t" + "unregisterVariables();" + "\n";
	generatedDeclarations+= declarationIndent + "\t\t" + "// function stacks" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (script._module.empty() == false ||
				script.type == MinitScript::Script::TYPE_STACKLET
				#if defined(MINITSCRIPT_EVENTS)
					||
					script.type == MinitScript::Script::TYPE_ON ||
					script.type == MinitScript::Script::TYPE_ONENABLED
				#endif
			) {
				scriptIdx++;
				continue;
			}
			//
			auto methodName = createMethodName(minitScript, scriptIdx);
			auto shortMethodName = createShortMethodName(minitScript, scriptIdx);
			generatedDeclarations+= declarationIndent + "\t\t" + "if (" + shortMethodName + "_Stack.empty() == false) _Console::printLine(\"~" + minitScriptClassName + "(): Warning: " + methodName + ": stack not empty, size = \" + to_string(" + shortMethodName + "_Stack.size()));" + "\n";
			scriptIdx++;
		}
	}
	generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";

	generatedDeclarations+= declarationIndent + "}" + "\n";
	generatedDeclarations+= "\n";
	generatedDeclarations+= declarationIndent + "// overridden methods" + "\n";
	//
	generatedDeclarations+= declarationIndent + "void registerMethods() override;" + "\n";
	//
	generatedDeclarations+= declarationIndent + "inline void registerVariables() override {" + "\n";
	if (minitScript->isModule() == false) {
		generatedDeclarations+= declarationIndent + "\t" + minitScript->getBaseClass() + "::registerVariables();" + "\n";
	}
	generatedDeclarations+= declarationIndent + "\t" + "if (native == true) {" + "\n";
	if (globalVariables.empty() == false) {
		generatedDeclarations+= declarationIndent + "\t\t" + "// global script variables" + "\n";
		for (const auto& variable: globalVariables) {
			generatedDeclarations+= declarationIndent + "\t\t" + "if (hasVariable(\"" + variable + "\") == false) setVariable(\"" + variable + "\", Variable())" + ";" + "\n";
			generatedDeclarations+= declarationIndent + "\t\t" + createGlobalVariableName(variable) + " = getVariable(\"" + variable + "\", nullptr, true);" + "\n";
		}
	}
	if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
		generatedDeclarations+= declarationIndent + "\t\t" + "// modules" + "\n";
		for (const auto& _module: minitScript->getModules()) {
			const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(_module, "[^0-9a-zA-Z]", "_");
			generatedDeclarations+= declarationIndent + "\t\t" + moduleObjectName + "->registerVariables();" + "\n";
		}
	}
	generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
	generatedDeclarations+= declarationIndent + "}" + "\n";
	//
	generatedDeclarations+= declarationIndent + "inline void unregisterVariables() override {" + "\n";
	generatedDeclarations+= declarationIndent + "\t" + "if (native == true) {" + "\n";
	if (globalVariables.empty() == false) {
		generatedDeclarations+= declarationIndent + "\t\t" + "// global script variables" + "\n";
		for (const auto& variable: globalVariables) {
			generatedDeclarations+= declarationIndent + "\t\t" + createGlobalVariableName(variable) + ".unset();" + "\n";
		}
	}
	if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
		generatedDeclarations+= declarationIndent + "\t\t" + "// modules" + "\n";
		for (const auto& _module: minitScript->getModules()) {
			const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(_module, "[^0-9a-zA-Z]", "_");
			generatedDeclarations+= declarationIndent + "\t\t" + moduleObjectName + "->unregisterVariables();" + "\n";
		}
	}
	generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
	generatedDeclarations+= declarationIndent + "}" + "\n";
	//
	generatedDeclarations+= declarationIndent + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
	generatedDeclarations+= declarationIndent + "\t" + "void emit(const string& condition) override;" + "\n";
	generatedDeclarations+= declarationIndent + "#endif" + "\n";
	//
	generatedDeclarations+= declarationIndent + "inline void initializeScript() override {" + "\n";
	if (minitScript->isModule() == true) {
		generatedDeclarations+= declarationIndent + "\t" + "_Console::printLine(\"" + minitScriptClassName + "::initializeScript(): This MinitScript instance is a module, so this method should not be called.\");" + "\n";
	} else {
		generatedDeclarations+= declarationIndent + "\t" + "if (native == false) {" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + minitScript->getBaseClass() + "::initializeScript();" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "return;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "registerVariables();" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "resetScriptExecutationState(" + to_string(initializeScriptIdx) + ", STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
	}
	generatedDeclarations+= declarationIndent + "}" + "\n";
	//
	generatedDeclarations+= declarationIndent + "inline void execute() override {" + "\n";
	if (minitScript->isModule() == true) {
		generatedDeclarations+= declarationIndent + "\t" + "rootScript->execute();" + "\n";
	} else {
		generatedDeclarations+= declarationIndent + "\t" + "if (native == false) {" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + minitScript->getBaseClass() + "::execute();" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "return;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "auto& scriptState = getScriptState();" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "if (scriptState.running == false) return;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "// execute while having statements to be processed" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "if (scriptState.state == STATEMACHINESTATE_NEXT_STATEMENT) {" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "// take goto statement index into account" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "if (scriptState.gotoStatementIdx != STATEMENTIDX_NONE) {" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "\t" + "scriptState.statementIdx = scriptState.gotoStatementIdx;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "\t" + "scriptState.gotoStatementIdx = STATEMENTIDX_NONE;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "}" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "\t" + "//" + "\n";
		generatedDeclarations+= generatedExecuteCode;
		generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "if (isFunctionRunning() == false && deferredEmit.empty() == false) {" + "\n";
		generatedDeclarations+= declarationIndent + "\t\t" + "auto condition = deferredEmit;" + "\n";
		generatedDeclarations+= declarationIndent + "\t\t" + "deferredEmit.clear();" + "\n";
		generatedDeclarations+= declarationIndent + "\t\t" + "emit(condition);" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "#endif" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "executeStateMachine();" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "// try garbage collection" + "\n";
		generatedDeclarations+= declarationIndent + "\t" + "tryGarbageCollection();" + "\n";
	}
	generatedDeclarations+= declarationIndent + "}" + "\n";
	generatedDeclarations+= "\n";

	// module only: generate module export inline class methods for functions and stacklets that are our own
	if (minitScript->isModule() == true) {
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (script._module.empty() == false ||
				(script.type != MinitScript::Script::TYPE_FUNCTION &&
				script.type != MinitScript::Script::TYPE_STACKLET)) {
				scriptIdx++;
				continue;
			}
			// method name
			auto methodName = createMethodName(minitScript, scriptIdx);
			auto shortMethodName = createShortMethodName(minitScript, scriptIdx);

			// declaration
			generatedDeclarations+= declarationIndent + "/**" + "\n";
			generatedDeclarations+= declarationIndent + " * Module export of MinitScript transpilation of: " + getScriptTypeReadableName(script.type) + ": " + script.condition + (script.name.empty() == false?" (" + script.name + ")":"") + "\n";
			generatedDeclarations+= declarationIndent + " * @param minitScriptGotoStatementIdx MinitScript goto statement index" + "\n";
			generatedDeclarations+= declarationIndent + " */" + "\n";
			generatedDeclarations+= declarationIndent + "inline void export_" + methodName + "(int minitScriptGotoStatementIdx) {" + "\n";
			generatedDeclarations+= declarationIndent + "\t" + methodName + "(minitScriptGotoStatementIdx);" + "\n";
			generatedDeclarations+= declarationIndent + "}" + "\n";
			generatedDeclarations+= "\n";

			//
			scriptIdx++;
		}
	}

	generatedDeclarations+= string() + "protected:" + "\n";
	for (const auto& moduleClassDeclaration: moduleClassesDeclarations) {
		generatedDeclarations+= declarationIndent + moduleClassDeclaration+ "\n";
	}
	for (const auto& memberAccessEvaluationDeclaration: memberAccessEvaluationDeclarations) {
		generatedDeclarations+= declarationIndent + memberAccessEvaluationDeclaration + "\n";
	}
	generatedDeclarations+= "\n";

	//
	generatedDeclarations+= declarationIndent + "// overridden methods" + "\n";
	generatedDeclarations+= declarationIndent + "void initializeNative() override;" + "\n";
	generatedDeclarations+= declarationIndent + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
	generatedDeclarations+= declarationIndent + "\t" + "int determineScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= declarationIndent + "\t" + "int determineNamedScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= declarationIndent + "#endif" + "\n";
	generatedDeclarations+= "\n";

	string registerMethodsDefinitions;
	registerMethodsDefinitions+= "void " + minitScriptClassName + "::registerMethods() {" + "\n";
	if (minitScript->isModule() == true) {
		registerMethodsDefinitions+= definitionIndent + "if (native == false) return;" + "\n";
		//
		for (const auto& memberAccessEvaluationDefinition: memberAccessEvaluationDefinitions) {
			registerMethodsDefinitions+= definitionIndent + memberAccessEvaluationDefinition + "\n";
		}
	} else {
		registerMethodsDefinitions+= definitionIndent + minitScript->getBaseClass() + "::registerMethods();" + "\n";
		registerMethodsDefinitions+= definitionIndent + "if (native == false) return;" + "\n";
		//
		for (const auto& memberAccessEvaluationDefinition: memberAccessEvaluationDefinitions) {
			registerMethodsDefinitions+= definitionIndent + memberAccessEvaluationDefinition + "\n";
		}
		//
		if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
			registerMethodsDefinitions+= definitionIndent + "// modules" + "\n";
			for (const auto& _module: minitScript->getModules()) {
				const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(_module, "[^0-9a-zA-Z]", "_");
				registerMethodsDefinitions+= definitionIndent + moduleObjectName + "->registerMethods();" + "\n";
			}
			registerMethodsDefinitions += "\n";
		}
	}
	registerMethodsDefinitions+= string() + "}" + "\n";

	//
	string emitDefinition;
	emitDefinition+= string() + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
	emitDefinition+= "void " + minitScriptClassName + "::emit(const string& condition) {" + "\n";
	if (minitScript->isModule() == true) {
		emitDefinition+= definitionIndent + "// this MinitScript instance is a module, so forward to root script" + "\n";
		emitDefinition+= definitionIndent + "rootScript->emit(condition);" + "\n";
	} else {
		emitDefinition+= definitionIndent + "if (native == false) {" + "\n";
		emitDefinition+= definitionIndent + "\t" + minitScript->getBaseClass() + "::emit(condition);" + "\n";
		emitDefinition+= definitionIndent + "\t" + "return;" + "\n";
		emitDefinition+= definitionIndent + "}" + "\n";
		emitDefinition+= definitionIndent + "if (isFunctionRunning() == true) {" + "\n";
		emitDefinition+= definitionIndent + "\t" + "deferredEmit = condition;" + "\n";
		emitDefinition+= definitionIndent + "\t" + "return;" + "\n";
		emitDefinition+= definitionIndent + "}" + "\n";
		emitDefinition+= definitionIndent + "emitted = true;" + "\n";
	}

	//
	string generatedDefinitions = "\n";
	string initializeNativeDefinition;
	initializeNativeDefinition+= "void " + minitScriptClassName + "::initializeNative() {" + "\n";
	initializeNativeDefinition+= definitionIndent + "this->scriptFileName = " + "\"" + escapeString(minitScript->getScriptFileName()) + "\"" + ";" + "\n";
	initializeNativeDefinition+= definitionIndent + "this->scriptPathName = " + "\"" + escapeString(minitScript->getScriptPathName()) + "\"" + ";" + "\n";
	initializeNativeDefinition+= definitionIndent + "this->_module = " + string(minitScript->isModule() == true?"true":"false") + ";" + "\n";
	initializeNativeDefinition+= definitionIndent + "this->modules =" + "\n";
	initializeNativeDefinition+= definitionIndent + "\t" + "{" + "\n";
	{
		auto moduleIdx = 0;
		for (const auto& _module: minitScript->getModules()) {
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" +  "\"" + escapeString(_module) + "\"" + (moduleIdx < minitScript->getModules().size() - 1?",":"") + "\n";
			moduleIdx++;
		}
	}
	initializeNativeDefinition+= declarationIndent + "\t" + "};" + "\n";
	initializeNativeDefinition+= definitionIndent + "native = true;" + "\n";
	initializeNativeDefinition+= definitionIndent + "nativeHash = \"" + minitScript->getNativeHash() + "\";" + "\n";
	initializeNativeDefinition+= definitionIndent + "nativeModuleHashes =" + "\n";
	initializeNativeDefinition+= definitionIndent + "\t" + "{" + "\n";
	{
		auto moduleIdx = 0;
		for (const auto& moduleHash: minitScript->getNativeModuleHashes()) {
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" +  "\"" + escapeString(moduleHash) + "\"" + (moduleIdx < minitScript->getModules().size() - 1?",":"") + "\n";
			moduleIdx++;
		}
	}
	initializeNativeDefinition+= declarationIndent + "\t" + "};" + "\n";
	initializeNativeDefinition+= definitionIndent + "nativeScripts =" + "\n";
	initializeNativeDefinition+= definitionIndent + "\t" + "{" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "Script(" + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\"" + escapeString(script._module) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + getScriptTypeEnumIdentifier(script.type) + "," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + to_string(script.line) + "," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\"" + escapeString(script.condition) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\"" + escapeString(script.executableCondition) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "Statement(" + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(script.conditionStatement.fileName) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.line) + "," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.statementIdx) + "," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(script.conditionStatement.statement) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(script.conditionStatement.executableStatement) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.gotoStatementIdx) + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + ")," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "{}," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\"" + escapeString(script.name) + "\"," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + (script.emitCondition == true?"true":"false") + "," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "{" + "\n";

			//
			if (script._module.empty() == false) {
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "// no statements here, they are stored in " + script._module + " module" + "\n";
			} else {
				//
				auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
				for (const auto& statement: script.statements) {
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "Statement(" + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(statement.fileName) + "\"," + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.line) + "," + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.statementIdx) + "," + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(statement.statement) + "\"," + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + escapeString(statement.executableStatement) + "\"," + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.gotoStatementIdx) + "\n";
					initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + ")" + (statementIdx < script.statements.size() - 1?",":"") + "\n";
					statementIdx++;
				}
			}
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "}," + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "{},\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + (script.callable == true?"true":"false") + ",\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "{\n";
			auto argumentIdx = 0;
			for (const auto& argument: script.arguments) {
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "Script::Argument(" + "\n";
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + argument.name + "\"," + "\n";
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + (argument.reference == true?"true":"false") + ",\n";
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" + "\t" + (argument.privateScope == true?"true":"false") + "\n";
				initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\t" ")" + (argumentIdx != script.arguments.size() - 1?",":"") + "\n";
				argumentIdx++;
			}
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "},\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + to_string(minitScript->isModule() == false?script.rootScriptIdx:MinitScript::SCRIPTIDX_NONE) + "\n";
			initializeNativeDefinition+= definitionIndent + "\t" + "\t" + ")" + (scriptIdx < scripts.size() - 1?",":"") + "\n";
			scriptIdx++;
		}
	}
	initializeNativeDefinition+= definitionIndent + "\t" + "};" + "\n";
	initializeNativeDefinition+= definitionIndent + "nativeFunctions =" + "\n";
	initializeNativeDefinition+= definitionIndent + "\t" + "{" + "\n";
	auto functionItIdx = 0;
	for (const auto& [functionName, functionScriptIdx]: minitScript->functions) {
		//
		if (scripts[functionScriptIdx]._module.empty() == false) {
			functionItIdx++;
			continue;
		}
		//
		initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "{" + "\n";
		initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + "\"" + functionName + "\"," + "\n";
		initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "\t" + to_string(functionScriptIdx) + "\n";
		initializeNativeDefinition+= definitionIndent + "\t" + "\t" + "}" + (functionItIdx != minitScript->functions.size() - 1?",":"") + "\n";
		functionItIdx++;
	}
	initializeNativeDefinition+= definitionIndent + "\t" + "};" + "\n";

	//
	if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
		initializeNativeDefinition+= definitionIndent + "// initialize modules" + "\n";
		for (const auto& _module: minitScript->getModules()) {
			const auto includePathName = minitScript->getScriptPathName();
			const auto includeFileName = _module;
			const auto moduleClassName = string() + "_" + UTF8StringTools::regexReplace((includePathName.empty() == false?includePathName + "/":"") + includeFileName, "[^0-9a-zA-Z]", "_");
			const auto moduleObjectName = string() + "_" + UTF8StringTools::regexReplace(_module, "[^0-9a-zA-Z]", "_");
			initializeNativeDefinition+= definitionIndent + moduleObjectName + " = make_unique<" + moduleClassName + ">();" + "\n";
			initializeNativeDefinition+= definitionIndent + moduleObjectName + "->initializeNativeModule(this);" + "\n";
		}
	}

	//
	if (minitScript->isModule() == true) {
		initializeNativeDefinition+= definitionIndent + "// modules do not have further initialization" + "\n";
		initializeNativeDefinition+= definitionIndent + "this->scripts = nativeScripts;" + "\n";
		initializeNativeDefinition+= definitionIndent + "this->functions = nativeFunctions;" + "\n";
	}

	//
	initializeNativeDefinition+= string() + "}" + "\n";

	//
	string generatedDetermineScriptIdxToStartDefinition = "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= "int " + minitScriptClassName + "::determineScriptIdxToStart() {" + "\n";
	if (minitScript->isModule() == true) {
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "_Console::printLine(\"" + minitScriptClassName + "::determineScriptIdxToStart(): This MinitScript instance is a module, so this method should not be called.\");" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "return SCRIPTIDX_NONE;" + "\n";
	} else {
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "#define MINITSCRIPT_METHOD_POPSTACK()" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "if (native == false) return MinitScript::determineScriptIdxToStart();" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "// MinitScript setup" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "auto minitScript = this;" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "//" + "\n";
	}
	string generatedDetermineNamedScriptIdxToStartDefinition = "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "#if defined(MINITSCRIPT_EVENTS)" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= "int " + minitScriptClassName + "::determineNamedScriptIdxToStart() {" + "\n";
	if (minitScript->isModule() == true) {
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "_Console::printLine(\"" + minitScriptClassName + "::determineNamedScriptIdxToStart(): This MinitScript instance is a module, so this method should not be called.\");" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "return SCRIPTIDX_NONE;" + "\n";
	} else {
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "#define MINITSCRIPT_METHOD_POPSTACK()" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "if (native == false) return MinitScript::determineNamedScriptIdxToStart();" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "auto minitScript = this;" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "for (const auto& enabledNamedCondition: enabledNamedConditions) {" + "\n";
	}
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (script._module.empty() == false) {
				scriptIdx++;
				continue;
			}
			// method name
			auto methodName = createMethodName(minitScript, scriptIdx);
			auto shortMethodName = createShortMethodName(minitScript, scriptIdx);

			// emit name
			string emitName =
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);

			// emit code
			#if defined(MINITSCRIPT_EVENTS)
				// events
				if (script.type == MinitScript::Script::TYPE_ON && StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true) {
					string emitDefinitionIndent = "\t";
					emitDefinition+= emitDefinitionIndent + "if (condition == \"" + emitName + "\") {" + "\n";
					emitDefinition+= emitDefinitionIndent + "\t" + "resetScriptExecutationState(" + to_string(scriptIdx) + ", STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
					emitDefinition+= emitDefinitionIndent + "} else" + "\n";
				}
			#endif

			// declaration
			generatedDeclarations+= declarationIndent + "/**" + "\n";
			generatedDeclarations+= declarationIndent + " * MinitScript transpilation of: " + getScriptTypeReadableName(script.type) + ": " + script.condition + (script.name.empty() == false?" (" + script.name + ")":"") + "\n";
			generatedDeclarations+= declarationIndent + " * @param minitScriptGotoStatementIdx MinitScript goto statement index" + "\n";
			generatedDeclarations+= declarationIndent + " */" + "\n";
			generatedDeclarations+= declarationIndent + "void " + methodName + "(int minitScriptGotoStatementIdx);" + "\n";
			generatedDeclarations+= "\n";

			// transpile definition
			generatedDefinitions+= "void " + minitScriptClassName + "::" + methodName + "(int minitScriptGotoStatementIdx) {" + "\n";
			string generatedSubCode;

			// local variables, which applies to stacklets and functions
			if (localVariables[scriptIdx].empty() == false) {
				generatedDefinitions+= definitionIndent + "// local script variables" + "\n";
				generatedDefinitions+= definitionIndent + "#define MINITSCRIPT_METHOD_POPSTACK() " + shortMethodName + "_Stack.pop();" + "\n";
				generatedDefinitions+= definitionIndent + "// STATEMENTIDX_FIRST means complete method call" + "\n";
				generatedDefinitions+= definitionIndent + "if (minitScriptGotoStatementIdx == STATEMENTIDX_FIRST) {" + "\n";
				generatedDefinitions+= definitionIndent + "\t" + "auto& _lv = " + shortMethodName + "_Stack.emplace();" + "\n";
				for (const auto& variable: localVariables[scriptIdx]) {
					generatedDefinitions+= definitionIndent + "\t" + "if (hasVariable(\"" + variable + "\") == false) setVariable(\"" + variable + "\", Variable())" + "; _lv." + createLocalVariableName(variable) + " = getVariable(\"" + variable + "\", nullptr, true);" + "\n";
				}
				generatedDefinitions+= definitionIndent + "}" + "\n";
				generatedDefinitions+= definitionIndent + "//" + "\n";
				generatedDefinitions+= definitionIndent + "auto& _lv = " + shortMethodName + "_Stack.top();" + "\n";
			} else {
				// we can still have a stacklet without local variables
				if (script.type == MinitScript::Script::TYPE_STACKLET) {
					auto scopeScriptIdx = minitScript->getStackletScopeScriptIdx(scriptIdx);
					if (scopeScriptIdx != MinitScript::SCRIPTIDX_NONE) {
						auto scopeShortMethodName = createShortMethodName(minitScript, minitScript->getStackletScopeScriptIdx(scriptIdx));
						generatedDefinitions+= definitionIndent + "// local script variables" + "\n";
						generatedDefinitions+= definitionIndent + "auto& _lv = " + scopeShortMethodName + "_Stack.top();" + "\n";
					}
				}
				#if defined(MINITSCRIPT_EVENTS)
					// events
					else
					// ok, reset emitted for conditions and enabled conditions
					if (script.type == MinitScript::Script::TYPE_ON ||
						script.type == MinitScript::Script::TYPE_ONENABLED) {
						generatedDefinitions+= definitionIndent + "// reset emitted" + "\n";
						generatedDefinitions+= definitionIndent + "emitted = false;" + "\n";
					}
				#endif
				// no local variables or condition/enabled condition
				generatedDefinitions+= definitionIndent + "// local script variables" + "\n";
				generatedDefinitions+= definitionIndent + "#define MINITSCRIPT_METHOD_POPSTACK()" + "\n";
			}

			// transpile array access operator and map/set initializer
			string arrayAccessMethodsDefinitions;
			string arrayMapSetInitializerDefinitions;

			//
			for (auto statementIdx = 0; statementIdx < script.statements.size(); statementIdx++) {
				string statementArrayMapSetInitializerDefinitions;
				//
				generateArrayMapSetInitializer(
					minitScript,
					statementArrayMapSetInitializerDefinitions,
					MinitScript::SCRIPTIDX_NONE,
					script.type == MinitScript::Script::TYPE_FUNCTION || script.type == MinitScript::Script::TYPE_STACKLET?
						scriptIdx:
						MinitScript::SCRIPTIDX_NONE,
					minitScriptClassName,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false,
					{},
					1
				);
				if (statementArrayMapSetInitializerDefinitions.empty() == false) statementArrayMapSetInitializerDefinitions+= "\n";
				arrayMapSetInitializerDefinitions+= statementArrayMapSetInitializerDefinitions;
				//
				generateArrayAccessMethods(
					minitScript,
					arrayAccessMethodsDefinitions,
					minitScriptClassName,
					MinitScript::SCRIPTIDX_NONE,
					script.type == MinitScript::Script::TYPE_FUNCTION || script.type == MinitScript::Script::TYPE_STACKLET?
						scriptIdx:
						MinitScript::SCRIPTIDX_NONE,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false,
					{},
					1
				);
			}

			//
			generatedDefinitions+= arrayMapSetInitializerDefinitions;
			generatedDefinitions+= arrayAccessMethodsDefinitions;

			//
			transpile(minitScript, minitScriptClassName, generatedSubCode, scriptIdx, methodCodeMap, allMethods);
			generatedDefinitions+= generatedSubCode;

			// local variables
			if (localVariables[scriptIdx].empty() == false) {
				generatedDefinitions+= definitionIndent + "//" + "\n";
				generatedDefinitions+= definitionIndent + "MINITSCRIPT_METHOD_POPSTACK();" + "\n";
			}
			generatedDefinitions+= definitionIndent + "#undef MINITSCRIPT_METHOD_POPSTACK" + "\n";

			//
			generatedDefinitions+= string() + "}" + "\n\n";

			//
			if (script.emitCondition == false) {
				#if defined(MINITSCRIPT_EVENTS)
					// events
					if (script.type == MinitScript::Script::TYPE_ONENABLED) {
						generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent;
						generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "\t" + "// next statements belong to tested enabled named condition with name \"" + script.name + "\"" + "\n";
						generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "\t" + "if (enabledNamedCondition == \"" + script.name + "\") {" + "\n";
					} else {
				#endif
					generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "{" + "\n";
				//
				#if defined(MINITSCRIPT_EVENTS)
					// events
					}
				#endif
				//
				string arrayMapSetInitializerDefinitions;
				string arrayAccessMethodsDefinitions;
				//
				generateArrayMapSetInitializer(
					minitScript,
					arrayMapSetInitializerDefinitions,
					MinitScript::SCRIPTIDX_NONE,
					MinitScript::SCRIPTIDX_NONE,
					minitScriptClassName,
					methodName,
					script.conditionSyntaxTree,
					script.conditionStatement,
					methodCodeMap,
					allMethods,
					true,
					{},
					#if defined(MINITSCRIPT_EVENTS)
						// events
						script.type == MinitScript::Script::TYPE_ONENABLED?3:2
					#else
						2
					#endif
				);
				if (arrayMapSetInitializerDefinitions.empty() == false) arrayMapSetInitializerDefinitions+= "\n";
				//
				generateArrayAccessMethods(
					minitScript,
					arrayAccessMethodsDefinitions,
					minitScriptClassName,
					MinitScript::SCRIPTIDX_NONE,
					MinitScript::SCRIPTIDX_NONE,
					methodName,
					script.conditionSyntaxTree,
					script.conditionStatement,
					methodCodeMap,
					allMethods,
					true,
					{},
					#if defined(MINITSCRIPT_EVENTS)
						// events
						script.type == MinitScript::Script::TYPE_ONENABLED?3:2
					#else
						2
					#endif
				);
				//
				#if defined(MINITSCRIPT_EVENTS)
					// events
					if (script.type == MinitScript::Script::TYPE_ON) {
						generatedDetermineScriptIdxToStartDefinition+= arrayMapSetInitializerDefinitions;
						generatedDetermineScriptIdxToStartDefinition+= arrayAccessMethodsDefinitions;
					} else {
						generatedDetermineNamedScriptIdxToStartDefinition+= arrayMapSetInitializerDefinitions;
						generatedDetermineNamedScriptIdxToStartDefinition+= arrayAccessMethodsDefinitions;
					}
					//
					transpileCondition(
						minitScript,
						script.type == MinitScript::Script::TYPE_ON?generatedDetermineScriptIdxToStartDefinition:generatedDetermineNamedScriptIdxToStartDefinition,
						scriptIdx,
						methodCodeMap,
						allMethods,
						"-1",
						"bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return " + to_string(scriptIdx) + ";",
						script.type == MinitScript::Script::TYPE_ONENABLED?1:0
					);
					//
					if (script.type == MinitScript::Script::TYPE_ONENABLED) {
						generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "\t" + "}" + "\n";
					} else {
						generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "}" + "\n";
					}
				#endif
			}

			//
			scriptIdx++;
		}
	}

	//
	if (minitScript->isModule() == false) {
		generatedDetermineScriptIdxToStartDefinition+= "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "//" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "return " + to_string(nothingScriptIdx) + ";" + "\n";
		generatedDetermineScriptIdxToStartDefinition+= definitionIndent + "#undef MINITSCRIPT_METHOD_POPSTACK" + "\n";
	}
	generatedDetermineScriptIdxToStartDefinition+= string() + "}" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "#endif" + "\n";
	//
	if (minitScript->isModule() == false) {
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "}" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "//" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "return SCRIPTIDX_NONE;" + "\n";
		generatedDetermineNamedScriptIdxToStartDefinition+= definitionIndent + "#undef MINITSCRIPT_METHOD_POPSTACK" + "\n";
	}
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "}" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "#endif" + "\n";

	//
	if (minitScript->isModule() == false) {
		string emitDefinitionIndent = "\t";
		emitDefinition+= emitDefinitionIndent + "{" + "\n";
		emitDefinition+= emitDefinitionIndent + "\t" + "_Console::printLine(\"" + minitScriptClassName + "::emit(): no condition with name: '\" + condition + \"'\");" + "\n";
		emitDefinition+= emitDefinitionIndent + "}" + "\n";
	}
	emitDefinition+= string() + "}" + "\n";
	emitDefinition+= string() + "#endif" + "\n";

	//
	if (globalVariables.empty() == false) {
		generatedDeclarations+= declarationIndent + "// global script variables" + "\n";
		for (const auto& variable: globalVariables) {
			generatedDeclarations+= declarationIndent + "Variable " + createGlobalVariableName(variable) + ";" + "\n";
		}
		generatedDeclarations+= "\n";
	}

	//
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			if (script._module.empty() == false ||
				#if defined(MINITSCRIPT_EVENTS)
					// events
					script.type == MinitScript::Script::TYPE_ON ||
					script.type == MinitScript::Script::TYPE_ONENABLED ||
				#endif
				script.type == MinitScript::Script::TYPE_STACKLET) {
				scriptIdx++;
				continue;
			}
			// method name
			auto shortMethodName = createShortMethodName(minitScript, scriptIdx);
			//
			generatedDeclarations+= declarationIndent + "// local script variables of: " + getScriptTypeReadableName(script.type) + ": " + script.condition + (script.name.empty() == false?" (" + script.name + ")":"") + "\n";
			generatedDeclarations+= declarationIndent + "struct LV_" + shortMethodName + " {" + "\n";
			for (const auto& variable: localVariables[scriptIdx]) {
				generatedDeclarations+= declarationIndent + "\t" + "Variable " + createLocalVariableName(variable) + ";" + "\n";
			}
			generatedDeclarations+= declarationIndent + "\t" + "// destructor, we unset the variable references here" + "\n";
			generatedDeclarations+= declarationIndent + "\t" + "~LV_" + shortMethodName + "() {" + "\n";
			for (const auto& variable: localVariables[scriptIdx]) {
				generatedDeclarations+= declarationIndent + "\t" + "\t" + createLocalVariableName(variable) + ".unset();" + "\n";
			}
			generatedDeclarations+= declarationIndent + "\t" + "}" + "\n";
			generatedDeclarations+= declarationIndent + "};" + "\n";
			generatedDeclarations+= declarationIndent + "stack<LV_" + shortMethodName + "> " + shortMethodName + "_Stack;" + "\n\n";
			//
			scriptIdx++;
		}
	}

	// sum up definitions
	generatedDefinitions =
		string("\n#define __MINITSCRIPT_TRANSPILATION__\n\n") +
		initializeNativeDefinition +
		registerMethodsDefinitions +
		generatedDetermineScriptIdxToStartDefinition +
		generatedDetermineNamedScriptIdxToStartDefinition + "\n" +
		emitDefinition +
		generatedDefinitions;

	// inject C++ definition code
	{
		//
		auto injectedGeneratedCode = true;
		//
		vector<string> minitScriptCPP;
		vector<string> generatedMinitScriptCPP;
		auto transpilationCPPFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".cpp";
		if (FileSystem::exists(transpilationCPPFileName) == false) {
			auto minitScriptCPPString = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/transpilation", "Transpilation.cpp");
			minitScriptCPPString = StringTools::replace(minitScriptCPPString, "{$script}", scriptFileName);
			minitScriptCPPString = StringTools::replace(minitScriptCPPString, "{$class-name}", minitScriptClassName);
			minitScriptCPPString = StringTools::replace(minitScriptCPPString, "{$base-class}", minitScript->getBaseClass());
			minitScriptCPPString = StringTools::replace(minitScriptCPPString, "{$base-class-header}", minitScript->getBaseClassHeader());
			minitScriptCPP = StringTools::tokenize(minitScriptCPPString, "\n", true);
		} else {
			FileSystem::getContentAsStringArray(FileSystem::getPathName(transpilationCPPFileName), FileSystem::getFileName(transpilationCPPFileName), minitScriptCPP);
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string includes;
			for (const auto& include: transpilationUnitIncludes) includes+= include + "\n";
			//
			if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
				includes+= "\n";
				includes+= string() + "// module includes" + "\n";
				for (const auto& _module: minitScript->getModules()) {
					const auto includePathName = minitScript->getScriptPathName();
					const auto includeFileName = _module;
					includes+= string() + "#include " + "\"" + "_" + UTF8StringTools::regexReplace((includePathName.empty() == false?includePathName + "/":"") + includeFileName, "[^0-9a-zA-Z]", "_") + ".h" + "\"" + "\n";
				}
			}
			//
			injectedGeneratedCode = replace(
				minitScriptCPP,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_END__*/",
				includes,
				generatedMinitScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				minitScriptCPP = generatedMinitScriptCPP;
				generatedMinitScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string usings;
			for (const auto& _using: transpilationUnitUsings) usings+= _using + "\n";
			//
			injectedGeneratedCode = replace(
				minitScriptCPP,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_END__*/",
				usings,
				generatedMinitScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				minitScriptCPP = generatedMinitScriptCPP;
				generatedMinitScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			injectedGeneratedCode = replace(
				minitScriptCPP,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_END__*/",
				generatedDefinitions,
				generatedMinitScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				minitScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(transpilationCPPFileName),
				FileSystem::getFileName(transpilationCPPFileName),
				generatedMinitScriptCPP
			);
			//
			Console::printLine(scriptFileName + ": Injected generated C++ code in file " + transpilationCPPFileName + ". Dont forget to rebuild your sources.");
		}
	}

	//
	// inject C++ declaration code / header
	{
		vector<string> minitScriptClassHeader;
		vector<string> generatedMinitScriptClassHeader;
		auto transpilationHeaderFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".h";
		if (FileSystem::exists(transpilationHeaderFileName) == false) {
			auto minitScriptHeaderString = FileSystem::getContentAsString(MINITSCRIPT_DATA + "/resources/minitscript/templates/transpilation", "Transpilation.h");
			minitScriptHeaderString = StringTools::replace(minitScriptHeaderString, "{$script}", scriptFileName);
			minitScriptHeaderString = StringTools::replace(minitScriptHeaderString, "{$class-name}", minitScriptClassName);
			minitScriptHeaderString = StringTools::replace(minitScriptHeaderString, "{$base-class}", minitScript->getBaseClass());
			minitScriptHeaderString = StringTools::replace(minitScriptHeaderString, "{$base-class-header}", minitScript->getBaseClassHeader());
			minitScriptClassHeader = StringTools::tokenize(minitScriptHeaderString, "\n", true);
		} else {
			FileSystem::getContentAsStringArray(FileSystem::getPathName(transpilationHeaderFileName), FileSystem::getFileName(transpilationHeaderFileName), minitScriptClassHeader);
		}
		//
		auto injectedGeneratedCode = replace(
			minitScriptClassHeader,
			"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_START__*/",
			"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_END__*/",
			generatedDeclarations,
			generatedMinitScriptClassHeader
		);
		//
		if (injectedGeneratedCode == false) {
			Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_END__*/ tags in file " + transpilationFileName + "?");
		} else {
			minitScriptClassHeader = generatedMinitScriptClassHeader;
			generatedMinitScriptClassHeader.clear();
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string includes;
			//
			if (minitScript->isModule() == false && minitScript->getModules().empty() == false) {
				includes+= "\n";
				includes+= string() + "// module includes" + "\n";
				for (const auto& _module: minitScript->getModules()) {
					const auto includePathName = minitScript->getScriptPathName();
					const auto includeFileName = _module;
					includes+= string() + "#include " + "\"" + "_" + UTF8StringTools::regexReplace((includePathName.empty() == false?includePathName + "/":"") + includeFileName, "[^0-9a-zA-Z]", "_") + ".h" + "\"" + "\n";
				}
			}
			//
			injectedGeneratedCode = replace(
				minitScriptClassHeader,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_END__*/",
				includes,
				generatedMinitScriptClassHeader
			);
			if (injectedGeneratedCode == false) {
				Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				minitScriptClassHeader = generatedMinitScriptClassHeader;
				generatedMinitScriptClassHeader.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string usings;
			//
			injectedGeneratedCode = replace(
				minitScriptClassHeader,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_END__*/",
				usings,
				generatedMinitScriptClassHeader
			);
			if (injectedGeneratedCode == false) {
				Console::printLine(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				minitScriptClassHeader = generatedMinitScriptClassHeader;
				generatedMinitScriptClassHeader.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(transpilationHeaderFileName),
				FileSystem::getFileName(transpilationHeaderFileName),
				minitScriptClassHeader
			);
			//
			Console::printLine(scriptFileName + ": Injected generated C++ code in header file " + transpilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

void Transpiler::untranspile(const string& scriptFileName, const string& transpilationFileName) {
	Console::printLine(scriptFileName + ": Processing script");
	//
	auto replace = [](const vector<string> input, const string& startTag, const string& endTag, const string& replacement, vector<string>& output) -> bool {
		auto reject = false;
		auto replaceSuccess = false;
		for (auto i = 0; i < input.size(); i++) {
			const auto& line = input[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) output.push_back(line);
				continue;
			}
			if (trimmedLine == startTag) {
				reject = true;
				output.push_back(line);
			} else
			if (trimmedLine == endTag) {
				reject = false;
				replaceSuccess = true;
				output.push_back(replacement);
				output.push_back(line);
			} else {
				if (reject == false) output.push_back(line);
			}
		}
		//
		return replaceSuccess;
	};
	// de-inject C++ definition code
	{
		vector<string> minitScriptClass;
		vector<string> minitScriptClassNew;
		auto transpilationCPPFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".cpp";
		FileSystem::getContentAsStringArray(FileSystem::getPathName(transpilationCPPFileName), FileSystem::getFileName(transpilationCPPFileName), minitScriptClass);
		//
		auto injectedGeneratedCode = false;
		{
			injectedGeneratedCode = replace(
				minitScriptClass,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_INCLUDES_END__*/",
				string(),
				minitScriptClassNew
			);
			minitScriptClass = minitScriptClassNew;
			minitScriptClassNew.clear();
		}
		if (injectedGeneratedCode == true) {
			injectedGeneratedCode = replace(
				minitScriptClass,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_USINGS_END__*/",
				string(),
				minitScriptClassNew
			);
			minitScriptClass = minitScriptClassNew;
			minitScriptClassNew.clear();
		}
		if (injectedGeneratedCode == true) {
			injectedGeneratedCode = replace(
				minitScriptClass,
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_START__*/",
				"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_END__*/",
				string(),
				minitScriptClassNew
			);
		}
		//
		if (injectedGeneratedCode == false) {
			Console::printLine(scriptFileName + ": Could not remove generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DEFINITIONS_END__*/ markers in file " + transpilationFileName + "?");
		} else {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(transpilationCPPFileName),
				FileSystem::getFileName(transpilationCPPFileName),
				minitScriptClassNew
			);
			//
			Console::printLine(scriptFileName + ": Removed generated C++ code in file " + transpilationCPPFileName + ". Dont forget to rebuild your sources.");
		}
	}
	//
	// inject C++ declaration code / header
	{
		vector<string> minitScriptClassHeader;
		vector<string> minitScriptClassHeaderNew;
		auto transpilationHeaderFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".h";
		FileSystem::getContentAsStringArray(FileSystem::getPathName(transpilationHeaderFileName), FileSystem::getFileName(transpilationHeaderFileName), minitScriptClassHeader);
		//
		auto injectedGeneratedCode = false;
		injectedGeneratedCode = replace(
			minitScriptClassHeader,
			"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_START__*/",
			"/*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_END__*/",
			string(),
			minitScriptClassHeaderNew
		);
		//
		if (injectedGeneratedCode == false) {
			Console::printLine(scriptFileName + ": Could not remove generated C++ code, are you missing the /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_START__*/ and /*__MINITSCRIPT_TRANSPILEDMINITSCRIPTCODE_DECLARATIONS_END__*/ markers in file " + transpilationFileName + "?");
		} else {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(transpilationHeaderFileName),
				FileSystem::getFileName(transpilationHeaderFileName),
				minitScriptClassHeaderNew
			);
			//
			Console::printLine(scriptFileName + ": Removed generated C++ code in header file " + transpilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

const unordered_set<string> Transpiler::getAllClassesMethodNames(MinitScript* minitScript) {
	unordered_set<string> allMethods;
	for (auto scriptMethod: minitScript->getMethods()) {
		string className;
		if (scriptMethod->getMethodName().rfind("::") != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind("::"));
		if (className.empty() == true) continue;
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.size() + 2,
				scriptMethod->getMethodName().size());
		// first argument name of method must equal the name of the class
		if (scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != StringTools::toLowerCase(className)) continue;
		// first argument of method must be of type of the class
		if (className != MinitScript::Variable::getTypeAsString(scriptMethod->getArgumentTypes()[0].type)) continue;		//
		allMethods.insert(method);
	}
	//
	return allMethods;
}

const vector<string> Transpiler::getAllClassesMethodNamesSorted(MinitScript* minitScript) {
	auto allMethods = getAllClassesMethodNames(minitScript);
	//
	vector<string> result;
	for (auto method: allMethods) result.push_back(method);
	sort(result.begin(), result.end());
	//
	return result;
}

const unordered_map<string, vector<string>> Transpiler::getClassesMethodNames(MinitScript* minitScript) {
	unordered_map<string, vector<string>> methodByClasses;
	for (auto scriptMethod: minitScript->getMethods()) {
		string className;
		if (scriptMethod->getMethodName().rfind("::") != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind("::"));
		if (className.empty() == true) continue;
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.size() + 2,
				scriptMethod->getMethodName().size());
		// first argument name of method must equal the name of the class
		if (scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != StringTools::toLowerCase(className)) continue;
		// first argument of method must be of type of the class
		if (className != MinitScript::Variable::getTypeAsString(scriptMethod->getArgumentTypes()[0].type)) continue;
		//
		methodByClasses[className].push_back(method);
	}
	//
	return methodByClasses;
}

void Transpiler::determineVariables(MinitScript* minitScript, unordered_set<string>& globalVariables, vector<unordered_set<string>>& localVariables) {
	// TODO:
	//	Problem: Variables can be set before read  or read before set
	//		we allow to read from GLOBAL variable also if local variable has not been found
	//		One fix would be to: Dont look variable up in parent context, but rather also need a $GLOBAL accessor
	//
	const auto& scripts = minitScript->getScripts();
	//
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			//
			determineVariables(MinitScript::SCRIPTIDX_NONE, script.conditionSyntaxTree, globalVariables, localVariables);
			//
			for (auto statementIdx = 0; statementIdx < script.statements.size(); statementIdx++) {
				determineVariables(
					script.type == MinitScript::Script::TYPE_FUNCTION || script.type == MinitScript::Script::TYPE_STACKLET?
						scriptIdx:
						MinitScript::SCRIPTIDX_NONE,
					script.syntaxTree[statementIdx],
					globalVariables,
					localVariables
				);
			}
			//
			scriptIdx++;
		}
	}
	// move stacklet variables into their scopes
	for (auto scriptIdx = 0; scriptIdx < localVariables.size(); scriptIdx++) {
		const auto& script = scripts[scriptIdx];
		if (script.type != MinitScript::Script::TYPE_STACKLET) continue;
		//
		auto stackletScopeScriptIdx = minitScript->getStackletScopeScriptIdx(scriptIdx);
		for (const auto& variable: localVariables[scriptIdx]) {
			if (stackletScopeScriptIdx == MinitScript::SCRIPTIDX_NONE) {
				globalVariables.insert(variable);
			} else {
				localVariables[stackletScopeScriptIdx].insert(variable);
			}
		}
		localVariables[scriptIdx].clear();
	}
}

void Transpiler::determineVariables(int scriptIdx, const MinitScript::SyntaxTreeNode& syntaxTreeNode, unordered_set<string>& globalVariables, vector<unordered_set<string>>& localVariables) {
	auto addVariable = [&](const string& variableStatement) -> void {
		//
		if (scriptIdx == MinitScript::SCRIPTIDX_NONE ||
			StringTools::startsWith(variableStatement, "$$.") == true ||
			StringTools::startsWith(variableStatement, "$GLOBAL.") == true) {
			//
			if (StringTools::startsWith(variableStatement, "$$.") == true) {
				const auto variableName = createVariableName("$" + StringTools::substring(variableStatement, string_view("$$.").size()));
				globalVariables.insert(variableName);
			} else
			if (StringTools::startsWith(variableStatement, "$GLOBAL.") == true) {
				const auto variableName = createVariableName("$" + StringTools::substring(variableStatement, string_view("$GLOBAL.").size()));
				globalVariables.insert(variableName);
			} else {
				const auto variableName = createVariableName(variableStatement);
				globalVariables.insert(variableName);
			}
		} else {
			const auto variableName = createVariableName(variableStatement);
			localVariables[scriptIdx].insert(variableName);
		}
	};
	//
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				for (const auto& argument: syntaxTreeNode.arguments) determineVariables(scriptIdx, argument, globalVariables, localVariables);
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				if ((syntaxTreeNode.value.getValueAsString() == "getMethodArgumentVariable" ||
					syntaxTreeNode.value.getValueAsString() == "getVariable" ||
					syntaxTreeNode.value.getValueAsString() == "getVariableReference" ||
					syntaxTreeNode.value.getValueAsString() == "setVariable" ||
					syntaxTreeNode.value.getValueAsString() == "setVariableReference" ||
					syntaxTreeNode.value.getValueAsString() == "setConstant" ||
					syntaxTreeNode.value.getValueAsString() == "unsetVariableReference") &&
					syntaxTreeNode.arguments.empty() == false &&
					syntaxTreeNode.arguments[0].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) {
					//
					addVariable(syntaxTreeNode.arguments[0].value.getValueAsString());
				} else
				if (syntaxTreeNode.value.getValueAsString() == "internal.script.evaluateMemberAccess") {
					if (syntaxTreeNode.arguments[0].value.getType() == MinitScript::TYPE_STRING) {
						addVariable(syntaxTreeNode.arguments[0].value.getValueAsString());
					}
					for (auto i = 3; i < syntaxTreeNode.arguments.size(); i+= 2) {
						if (syntaxTreeNode.arguments[i].value.getType() == MinitScript::TYPE_STRING) {
							addVariable(syntaxTreeNode.arguments[i].value.getValueAsString());
						}
					}
				}
				//
				for (const auto& argument: syntaxTreeNode.arguments) determineVariables(scriptIdx, argument, globalVariables, localVariables);
				//
				break;
			}
		default:
			break;
	}
}

void Transpiler::gatherMethodCode(
	const vector<string>& minitScriptExtensionsCode,
	const string& className,
	int registerLine,
	unordered_map<string, vector<string>>& methodCodeMap
) {
	// TODO: this is a bit ugly and can be improved a lot, lets see and get this to work first
	auto classDefinitionLine = -1;
	// get class definition start line
	for (auto i = registerLine; i >= 0; i--) {
		const auto& line = minitScriptExtensionsCode[i];
		auto trimmedLine = StringTools::trim(line);
		if (StringTools::regexMatch(trimmedLine, "class[\\ \\t]+" + className + "[\\ \\t]*:.*") == true) {
			classDefinitionLine = i;
			break;
		}
	}
	// nope
	if (classDefinitionLine == -1) {
		Console::printLine("Transpiler::gatherMethodCode(): did not found '" + className + "' definition");
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
	for (auto i = classDefinitionLine; finished == false && i < minitScriptExtensionsCode.size(); i++) {
		const auto& line = minitScriptExtensionsCode[i];
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
	for (const auto& codeLine: executeMethodCode) {
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
		Console::printLine("Transpiler::gatherMethodCode(): Not registering method with methodName: '" + methodName + "': method already registered");
		return;
	}

	//
	Console::printLine("Transpiler::gatherMethodCode(): registering method with methodName: '" + methodName + "'");

	//
	methodCodeMap[methodName] = executeMethodCode;
}

void Transpiler::generateVariableAccess(
	MinitScript* minitScript,
	string& generatedCode,
	int scriptConditionIdx,
	int scriptIdx,
	const string& variableName,
	const string& indent,
	bool getMethodArgumentVariable,
	bool getVariable,
	bool getVariableReference,
	bool setVariable,
	bool setVariableReference,
	bool setConstant,
	const string& returnValueStatement,
	const string& statementEnd,
	int getArgumentIdx,
	int setArgumentIdx
) {
	//
	auto haveFunction = false;
	auto haveScript = (scriptConditionIdx != MinitScript::SCRIPTIDX_NONE || scriptIdx != MinitScript::SCRIPTIDX_NONE);
	if (haveScript == true) {
		const auto& script = minitScript->getScripts()[scriptConditionIdx != MinitScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
		haveFunction =
			script.type == MinitScript::Script::TYPE_FUNCTION ||
			(script.type == MinitScript::Script::TYPE_STACKLET && minitScript->getStackletScopeScriptIdx(scriptIdx) != MinitScript::SCRIPTIDX_NONE);
	}
	//
	auto dollarDollarVariable = StringTools::startsWith(variableName, "$$.");
	auto dollarGlobalVariable = StringTools::startsWith(variableName, "$GLOBAL.");
	if (haveFunction == true ||
		dollarDollarVariable == true ||
		dollarGlobalVariable == true) {
		//
		if (dollarDollarVariable == true || dollarGlobalVariable == true) {
			auto globalVariableIdx = 0;
			string globalVariable;
			if (dollarDollarVariable == true) {
				globalVariable = "$" + StringTools::substring(variableName, string_view("$$.").size());
				globalVariableIdx = 3;
			}
			if (dollarGlobalVariable == true) {
				globalVariable = "$" + StringTools::substring(variableName, string_view("$GLOBAL.").size());
				globalVariableIdx = 8;
			}
			auto haveVariableStatement = variableHasStatement(globalVariable);
			if (getMethodArgumentVariable == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getMethodArgumentVariable(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), &subStatement)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createMethodArgumentVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
				}
			} else
			if (getVariable == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getVariable(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), &subStatement, false)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createNonReferenceVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
				}
			} else
			if (getVariableReference == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getVariable(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), &subStatement, true)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createReferenceVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
				}
			} else
			if (setVariable == true || setConstant == true) {
				if (haveVariableStatement == true) {
					if (setConstant == true) {
						generatedCode+= indent + "setConstant(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), arguments[" + to_string(setArgumentIdx) + "], &subStatement); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
					} else {
						generatedCode+= indent + "setVariable(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "], &subStatement); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
					}
				} else {
					generatedCode+= indent + "if (" + createGlobalVariableName(globalVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + globalVariable + ": assignment of constant is not allowed\"); else ";
					if (setConstant == true) {
						generatedCode+= "{ ";
						generatedCode+= createGlobalVariableName(globalVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "]); ";
						generatedCode+= "setConstant(" + createGlobalVariableName(globalVariable) + "); ";
						generatedCode+= "} ";
					} else {
						generatedCode+= createGlobalVariableName(globalVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "]); ";
					}
					generatedCode+= returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				}
			} else
			if (setVariableReference == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + "setVariable(&" + createGlobalVariableName(globalVariable) + ", \"$\" + StringTools::substring(arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), " + to_string(globalVariableIdx) + "), arguments[" + to_string(setArgumentIdx) + "], &subStatement, true); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				} else {
					generatedCode+= indent + "if (" + createGlobalVariableName(globalVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + globalVariable + ": assignment of constant is not allowed\"); else ";
					generatedCode+= createGlobalVariableName(globalVariable) + ".setReference(&arguments[" + to_string(setArgumentIdx) + "]); " + returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				}
			}
		} else {
			const auto& localVariable = variableName;
			auto haveVariableStatement = variableHasStatement(localVariable);
			if (getMethodArgumentVariable == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getMethodArgumentVariable(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createMethodArgumentVariable(&_lv." + createLocalVariableName(localVariable) + ")" + statementEnd;
				}
			} else
			if (getVariable == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getVariable(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement, false)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createNonReferenceVariable(&_lv." + createLocalVariableName(localVariable) + ")" + statementEnd;
				}
			} else
			if (getVariableReference == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + returnValueStatement + "getVariable(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement, true)" + statementEnd;
				} else {
					generatedCode+= indent + returnValueStatement + "Variable::createReferenceVariable(&_lv." + createLocalVariableName(localVariable) + ")" + statementEnd;
				}
			} else
			if (setVariable == true || setConstant == true) {
				if (haveVariableStatement == true) {
					if (setConstant == true) {
						generatedCode+= indent + "setConstant(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "], &subStatement); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
					} else {
						generatedCode+= indent + "setVariable(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "], &subStatement); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
					}
				} else {
					generatedCode+= indent + "if (_lv." + createLocalVariableName(localVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + localVariable + ": assignment of constant is not allowed\"); else ";
					if (setConstant == true) {
						generatedCode+= "{ ";
						generatedCode+= "_lv." + createLocalVariableName(localVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "]); ";
						generatedCode+= "setConstant(_lv." + createLocalVariableName(localVariable) + "); ";
						generatedCode+= "} ";
					} else {
						generatedCode+= "_lv." + createLocalVariableName(localVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "]); ";
					}
					generatedCode+= returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				}
			} else
			if (setVariableReference == true) {
				if (haveVariableStatement == true) {
					generatedCode+= indent + "setVariable(&_lv." + createLocalVariableName(localVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "], &subStatement, true); returnValue = arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				} else {
					generatedCode+= indent + "if (_lv." + createLocalVariableName(localVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + localVariable + ": assignment of constant is not allowed\"); else ";
					generatedCode+= "_lv." + createLocalVariableName(localVariable) + ".setReference(&arguments[" + to_string(setArgumentIdx) + "]); " + returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
				}
			}
		}
	} else {
		//
		const auto& globalVariable = variableName;
		auto haveVariableStatement = variableHasStatement(globalVariable);
		if (getMethodArgumentVariable == true) {
			if (haveVariableStatement == true) {
				generatedCode+= indent + returnValueStatement + "getMethodArgumentVariable(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement)" + statementEnd;
			} else {
				generatedCode+= indent + returnValueStatement + "Variable::createMethodArgumentVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
			}
		} else
		if (getVariable == true) {
			if (haveVariableStatement == true) {
				generatedCode+= indent + returnValueStatement + "getVariable(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement, false)" + statementEnd;
			} else {
				generatedCode+= indent + returnValueStatement + "Variable::createNonReferenceVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
			}
		} else
		if (getVariableReference == true) {
			if (haveVariableStatement == true) {
				generatedCode+= indent + returnValueStatement + "getVariable(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), &subStatement, true)" + statementEnd;
			} else {
				generatedCode+= indent + returnValueStatement + "Variable::createReferenceVariable(&" + createGlobalVariableName(globalVariable) + ")" + statementEnd;
			}
		} else
		if (setVariable == true || setConstant == true) {
			if (haveVariableStatement == true) {
				if (setConstant == true) {
					generatedCode+= indent + "setConstant(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "], &subStatement); " + returnValueStatement + "arguments[" + to_string(getArgumentIdx) + "]" + statementEnd;
				} else {
					generatedCode+= indent + "setVariable(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "], &subStatement); " + returnValueStatement + "arguments[" + to_string(getArgumentIdx) + "]" + statementEnd;
				}
			} else {
				generatedCode+= indent + "if (" + createGlobalVariableName(globalVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + globalVariable + ": assignment of constant is not allowed\"); else ";
				if (setConstant == true) {
					generatedCode+= "{ ";
					generatedCode+= createGlobalVariableName(globalVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "]); ";
					generatedCode+= "setConstant(" + createGlobalVariableName(globalVariable) + "); ";
					generatedCode+= "} ";
				} else {
					generatedCode+= createGlobalVariableName(globalVariable) + ".setValue(arguments[" + to_string(setArgumentIdx) + "].isConstant() == true?MinitScript::Variable::createNonConstVariable(&arguments[" + to_string(setArgumentIdx) + "]):arguments[" + to_string(setArgumentIdx) + "]); ";
				}
				generatedCode+= returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
			}
		} else
		if (setVariableReference == true) {
			if (haveVariableStatement == true) {
				generatedCode+= indent + "setVariable(&" + createGlobalVariableName(globalVariable) + ", arguments[" + to_string(getArgumentIdx) + "].getValueAsString(), arguments[" + to_string(setArgumentIdx) + "], &subStatement, true); " + returnValueStatement + "arguments[" + to_string(getArgumentIdx) + "]" + statementEnd;
			} else {
				generatedCode+= indent + "if (" + createGlobalVariableName(globalVariable) + ".isConstant() == true) _Console::printLine(getStatementInformation(statement) + \": Constant: " + globalVariable + ": assignment of constant is not allowed\"); else ";
				generatedCode+= createGlobalVariableName(globalVariable) + ".setReference(&arguments[" + to_string(setArgumentIdx) + "]); " + returnValueStatement + "arguments[" + to_string(setArgumentIdx) + "]" + statementEnd;
			}
		}
	}
}

void Transpiler::generateArrayAccessMethods(
	MinitScript* minitScript,
	string& generatedDefinitions,
	const string& minitScriptClassName,
	int scriptConditionIdx,
	int scriptIdx,
	const string& methodName,
	const MinitScript::SyntaxTreeNode& syntaxTree,
	const MinitScript::Statement& statement,
	const unordered_map<string, vector<string>>& methodCodeMap,
	const unordered_set<string>& allMethods,
	bool condition,
	const vector<int>& argumentIndices,
	int depth
	) {
	//
	switch (syntaxTree.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				if (syntaxTree.value.getValueAsString() == "getMethodArgumentVariable" ||
					syntaxTree.value.getValueAsString() == "getVariable" ||
					syntaxTree.value.getValueAsString() == "getVariableReference" ||
					syntaxTree.value.getValueAsString() == "setVariable" ||
					syntaxTree.value.getValueAsString() == "setVariableReference" ||
					syntaxTree.value.getValueAsString() == "setConstant") {
					//
					auto lamdaIndent = StringTools::indent(string(), "\t", depth);
					//
					for (auto argumentIdx = 0; argumentIdx < syntaxTree.arguments.size(); argumentIdx++) {
						auto argumentString = escapeString(syntaxTree.arguments[argumentIdx].value.getValueAsString());
						//
						auto nextArgumentIndices = argumentIndices;
						nextArgumentIndices.push_back(argumentIdx);
						// ignore array and map initializers
						if (StringTools::startsWith(argumentString, "[") == true ||
							StringTools::startsWith(argumentString, "{") == true) continue;
						//
						auto arrayAccessStatementIdx = 0;
						auto arrayAccessStatementLeftIdx = -1;
						auto arrayAccessStatementRightIdx = -1;
						auto quote = '\0';
						auto bracketCount = 0;
						for (auto i = 0; i < argumentString.size(); i++) {
							auto c = argumentString[i];
							// handle quotes
							if (quote != '\0') {
								// unset quote if closed
								// also we can ignore content of quote blocks
								if (c == quote) {
									quote = '\0';
								}
							} else
							if (c == '"' || c == '\'') {
								quote = c;
							} else
							if (c == '[') {
								if (bracketCount == 0) arrayAccessStatementLeftIdx = i;
								bracketCount++;
							} else
							if (c == ']') {
								bracketCount--;
								if (bracketCount == 0) {
									arrayAccessStatementRightIdx = i;
									//
									auto arrayAccessStatementString = StringTools::substring(argumentString, arrayAccessStatementLeftIdx + 1, arrayAccessStatementRightIdx);
									// array append operator []
									if (arrayAccessStatementString.empty() == true) {
										//
										arrayAccessStatementIdx++;
										//
										continue;
									}
									// check if literal
									MinitScript::Variable arrayAccessStatementAsScriptVariable;
									//
									arrayAccessStatementAsScriptVariable.setImplicitTypedValue(
										minitScript->getScriptFileName(),
										arrayAccessStatementString,
										minitScript,
										scriptIdx,
										statement
									);
									switch (arrayAccessStatementAsScriptVariable.getType()) {
										case MinitScript::TYPE_BOOLEAN:
											{
												bool booleanValue;
												if (arrayAccessStatementAsScriptVariable.getBooleanValue(booleanValue) == true) {
													generatedDefinitions+= lamdaIndent + "// MinitScript transpilation for a " + (condition == true?"condition":"statement") + " array access statement, statement index " + to_string(statement.statementIdx) + ", argument indices " + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDefinitions+= lamdaIndent + "auto array_access_statement_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + " = [&](const SubStatement& subStatement) -> Variable {" + "\n";
													generatedDefinitions+= lamdaIndent + "	return Variable(" + (booleanValue == true?"true":"false") + ");" + "\n";
													generatedDefinitions+= lamdaIndent + "};" + "\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										case MinitScript::TYPE_INTEGER:
											{
												int64_t integerValue;
												if (arrayAccessStatementAsScriptVariable.getIntegerValue(integerValue) == true) {
													generatedDefinitions+= lamdaIndent + "// MinitScript transpilation for a " + (condition == true?"condition":"statement") + " array access statement, statement index " + to_string(statement.statementIdx) + ", argument indices " + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDefinitions+= lamdaIndent + "auto array_access_statement_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + " = [&](const SubStatement& subStatement) -> Variable {" + "\n";
													generatedDefinitions+= lamdaIndent + "	return Variable(static_cast<int64_t>(" + to_string(integerValue) + "ll));" + "\n";
													generatedDefinitions+= lamdaIndent + "};" + "\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										case MinitScript::TYPE_FLOAT:
											{
												float floatValue;
												if (arrayAccessStatementAsScriptVariable.getFloatValue(floatValue) == true) {
													generatedDefinitions+= lamdaIndent + "// MinitScript transpilation for a " + (condition == true?"condition":"statement") + " array access statement, statement index " + to_string(statement.statementIdx) + ", argument indices " + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
													generatedDefinitions+= lamdaIndent + "auto array_access_statement_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + " = [&](const SubStatement& subStatement) -> Variable {" + "\n";
													generatedDefinitions+= lamdaIndent + "	return Variable(static_cast<int64_t>(" + to_string(static_cast<int64_t>(floatValue)) + "ll));" + "\n";
													generatedDefinitions+= lamdaIndent + "};" + "\n";
												}
												// literals
												arrayAccessStatementIdx++;
												//
												continue;
											}
										default:
											break;
									}
									// variable?
									if (StringTools::startsWith(arrayAccessStatementString, "$") == true) arrayAccessStatementString = "getVariable(\"" + arrayAccessStatementString + "\")";
									// parse array access statment at current index
									string_view arrayAccessMethodName;
									vector<MinitScript::ParserArgument> arrayAccessArguments;
									// create a pseudo statement (information)
									MinitScript::Statement arrayAccessStatement(
										minitScript->getScriptFileName(),
										statement.line,
										statement.statementIdx,
										arrayAccessStatementString,
										arrayAccessStatementString,
										MinitScript::STATEMENTIDX_NONE
									);
									// parse script statement
									if (minitScript->parseStatement(string_view(arrayAccessStatementString), arrayAccessMethodName, arrayAccessArguments, arrayAccessStatement) == false) {
										break;
									}
									// create syntax tree for this array access
									MinitScript::SyntaxTreeNode arrayAccessSyntaxTree;
									if (minitScript->createStatementSyntaxTree(
										minitScript->getScriptFileName(),
										scriptIdx,
										arrayAccessMethodName,
										arrayAccessArguments,
										arrayAccessStatement,
										arrayAccessSyntaxTree) == false) {
										//
										break;
									}

									//
									string transpiledCode;
									auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
									auto scriptStateChanged = false;
									auto scriptStopped = false;
									vector<string >enabledNamedConditions;
									transpileStatement(
										minitScript,
										transpiledCode,
										arrayAccessSyntaxTree,
										arrayAccessStatement,
										scriptConditionIdx,
										scriptIdx,
										statementIdx,
										methodCodeMap,
										allMethods,
										scriptStateChanged,
										scriptStopped,
										enabledNamedConditions,
										0,
										{},
										"Variable()",
										"return returnValue;",
										1
									);
									generatedDefinitions+= lamdaIndent + "// MinitScript transpilation for array access statement, statement index " + to_string(statement.statementIdx) + ", argument indices " + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, ", ") + ", array access statement index " + to_string(arrayAccessStatementIdx) + "\n";
									generatedDefinitions+= lamdaIndent + "auto array_access_statement_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx) + " = [&](const SubStatement& subStatement) -> Variable {" + "\n";
									generatedDefinitions+= lamdaIndent + "\t" + "// MinitScript setup" + "\n";
									generatedDefinitions+= lamdaIndent + "\t" + "auto minitScript = this;" + "\n";
									generatedDefinitions+= transpiledCode;
									generatedDefinitions+= lamdaIndent + "};" + "\n";
									//
									arrayAccessStatementIdx++;
								}
							}
						}
					}
				}
				//
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					generateArrayAccessMethods(
						minitScript,
						generatedDefinitions,
						minitScriptClassName,
						scriptConditionIdx,
						scriptIdx,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth
					);
					//
					argumentIdx++;
				}
			}
			break;
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto argumentIdx = 1;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					generateArrayAccessMethods(
						minitScript,
						generatedDefinitions,
						minitScriptClassName,
						scriptConditionIdx,
						scriptIdx,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth
					);
					//
					argumentIdx++;
				}
				//
				break;
			}
		default:
			break;
	}
}

void Transpiler::generateEvaluateMemberAccessArrays(
	MinitScript* minitScript,
	vector<string>& generatedDeclarations,
	vector<string>& generatedDefinitions
) {
	//
	auto scriptMethods = minitScript->getMethods();
	auto allMethods = getAllClassesMethodNamesSorted(minitScript);
	auto methodsByClasses = getClassesMethodNames(minitScript);
	generatedDeclarations.push_back("// evaluate member access constants");
	generatedDeclarations.push_back("static constexpr int EVALUATEMEMBERACCESSARRAYIDX_NONE { -1 };");
	auto methodIdx = 0;
	for (const auto& method: allMethods) {
		generatedDeclarations.push_back("static constexpr int EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(method) + " { " + to_string(methodIdx) + " };");
		methodIdx++;
	}
	generatedDeclarations.push_back("");
	generatedDeclarations.push_back("// evaluate member access arrays");
	generatedDeclarations.push_back(
		"array<array<Method*, " +
		to_string(methodIdx) +
		">, " +
		to_string((static_cast<int>(MinitScript::TYPE_PSEUDO_DATATYPES + MinitScript::getDataTypes().size()) - static_cast<int>(MinitScript::TYPE_STRING))) +
		"> evaluateMemberAccessArrays {};"
	);
	generatedDefinitions.push_back("evaluateMemberAccessArrays = {};");
	for (auto typeIdx = static_cast<int>(MinitScript::TYPE_STRING); typeIdx < static_cast<int>(MinitScript::TYPE_PSEUDO_DATATYPES + MinitScript::getDataTypes().size()); typeIdx++) {
		const auto& className = MinitScript::Variable::getTypeAsString(static_cast<MinitScript::VariableType>(typeIdx));
		const auto& methods = methodsByClasses[className];
		auto methodIdx = 0;
		for (const auto& method: allMethods) {
			//
			if (std::find(methods.begin(), methods.end(), method) == methods.end()) {
				methodIdx++;
				continue;
			}
			//
			generatedDefinitions.push_back("evaluateMemberAccessArrays[" + to_string(typeIdx - static_cast<int>(MinitScript::TYPE_STRING)) + "][" + "EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(method) + "] = getMethod(\"" + className + "::" + method + "\");");
			methodIdx++;
		}
	}
}

void Transpiler::generateArrayMapSetVariable(
	MinitScript* minitScript,
	int scriptConditionIdx,
	int scriptIdx,
	const MinitScript::Variable& variable,
	const unordered_map<string, vector<string>>& methodCodeMap,
	const unordered_set<string>& allMethods,
	const string& methodName,
	bool condition,
	const string& minitScriptClassName,
	string& generatedDefinitions,
	int depth,
	int initializerDepth,
	const string& postStatement
) {
	//
	string headerIndent = "\t";
	auto indent = StringTools::indent(string(), "\t", initializerDepth + depth);
	switch (variable.getType()) {
		case MinitScript::TYPE_NULL:
			{
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_BOOLEAN:
			{
				bool value;
				variable.getBooleanValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + "(" + (value == true?"true":"false") + ");" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_INTEGER:
			{
				int64_t value;
				variable.getIntegerValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + "(static_cast<int64_t>(" + to_string(value) + "ll));" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_FLOAT:
			{
				float value;
				variable.getFloatValue(value);
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + "(" + to_string(value) + "f);" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_FUNCTION_CALL:
			{
				//
				const auto& statement = variable.getInitializer()->getStatement();
				string transpiledCode;
				auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
				auto scriptStateChanged = false;
				auto scriptStopped = false;
				vector<string>enabledNamedConditions;
				transpileStatement(
					minitScript,
					transpiledCode,
					*variable.getInitializer()->getSyntaxTree(),
					statement,
					scriptConditionIdx,
					scriptIdx,
					statementIdx,
					methodCodeMap,
					allMethods,
					scriptStateChanged,
					scriptStopped,
					enabledNamedConditions,
					0,
					{},
					"Variable()",
					"const auto& variableD" + to_string(initializerDepth) + " = returnValue; " + postStatement + "\n", 1
				);
				generatedDefinitions+= transpiledCode;
			}
			break;
		case MinitScript::TYPE_FUNCTION_ASSIGNMENT:
			{
				string function;
				auto functionScriptIdx = MinitScript::SCRIPTIDX_NONE;
				variable.getFunctionValue(function, functionScriptIdx);
				function = escapeString(function);
				//
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setFunctionAssignment(\"" + function + "\", " + to_string(functionScriptIdx) + ");" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_STACKLET_ASSIGNMENT:
			{
				string stacket;
				auto stackletScriptIdx = MinitScript::SCRIPTIDX_NONE;
				variable.getStackletValue(stacket, stackletScriptIdx);
				stacket = escapeString(stacket);
				//
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setStackletAssignment(\"" + stacket + "\", " + to_string(stackletScriptIdx) + ");" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_STRING:
			{
				string value;
				variable.getStringValue(value);
				value = escapeString(value);
				//
				generatedDefinitions+= indent + "{" + "\n";
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + "(string(\"" + value + "\"));" + "\n";
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}" + "\n";
			}
			break;
		case MinitScript::TYPE_ARRAY:
			{
				if (initializerDepth == 0) {
					generatedDefinitions+= string() + "{" + "\n";
					generatedDefinitions+= indent + "\t" + "// MinitScript setup" + "\n";
					generatedDefinitions+= indent + "\t" + "auto minitScript = this;" + "\n";
					generatedDefinitions+= indent + "\t" + "//" + "\n";
				} else {
					generatedDefinitions+= indent + "{" + "\n";
				}
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_ARRAY);" + "\n";
				const auto arrayValue = variable.getArrayPointer();
				for (const auto arrayEntry: *arrayValue) {
					generateArrayMapSetVariable(
						minitScript,
						scriptConditionIdx,
						scriptIdx,
						*arrayEntry,
						methodCodeMap,
						allMethods,
						methodName,
						condition,
						minitScriptClassName,
						generatedDefinitions,
						depth,
						initializerDepth + 1,
						"variableD" + to_string(initializerDepth) + ".pushArrayEntry(variableD" + to_string(initializerDepth + 1) + ");"
					);
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}";
				generatedDefinitions+= initializerDepth == 0?";":"\n";
			}
			break;
		case MinitScript::TYPE_MAP:
			{
				if (initializerDepth == 0) {
					generatedDefinitions+= string() + "{" + "\n";
					generatedDefinitions+= indent + "\t" + "// MinitScript setup" + "\n";
					generatedDefinitions+= indent + "\t" + "auto minitScript = this;" + "\n";
					generatedDefinitions+= indent + "\t" + "//" + "\n";
				} else {
					generatedDefinitions+= indent + "{" + "\n";
				}
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_MAP);" + "\n";
				const auto mapValue = variable.getMapPointer();
				for (const auto& [mapEntryName, mapEntryValue]: *mapValue) {
					auto mapEntryNameEscaped = escapeString(mapEntryName);
					generateArrayMapSetVariable(
						minitScript,
						scriptConditionIdx,
						scriptIdx,
						*mapEntryValue,
						methodCodeMap,
						allMethods,
						methodName,
						condition,
						minitScriptClassName,
						generatedDefinitions,
						depth,
						initializerDepth + 1,
						"variableD" + to_string(initializerDepth) + ".setMapEntry(\"" + mapEntryNameEscaped + "\", variableD" + to_string(initializerDepth + 1) + ", " + (mapEntryValue->isPrivate() == true?"true":"false") + ");"
					);
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}";
				generatedDefinitions+= initializerDepth == 0?";":"\n";
			}
			break;
		case MinitScript::TYPE_SET:
			{
				if (initializerDepth == 0) {
					generatedDefinitions+= string() + "{" + "\n";
					generatedDefinitions+= indent + "\t" + "// MinitScript setup" + "\n";
					generatedDefinitions+= indent + "\t" + "auto minitScript = this;" + "\n";
					generatedDefinitions+= indent + "\t" + "//" + "\n";
				} else {
					generatedDefinitions+= indent + "{" + "\n";
				}
				generatedDefinitions+= indent + "\t" + "Variable variableD" + to_string(initializerDepth) + ";" + "\n";
				generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".setType(TYPE_SET);" + "\n";
				const auto setValue = variable.getSetPointer();
				for (const auto& key: *setValue) {
					generatedDefinitions+= indent + "\t" + "variableD" + to_string(initializerDepth) + ".insertSetKey(\"" + key + "\");" + "\n";
				}
				generatedDefinitions+= indent + "\t" + postStatement + "\n";
				generatedDefinitions+= indent + "}";
				generatedDefinitions+= initializerDepth == 0?";":"\n";
			}
			break;
		default: break;
	}
}

void Transpiler::generateArrayMapSetInitializer(
	MinitScript* minitScript,
	string& generatedDefinitions,
	int scriptConditionIdx,
	int scriptIdx,
	const string& minitScriptClassName,
	const string& methodName,
	const MinitScript::SyntaxTreeNode& syntaxTree,
	const MinitScript::Statement& statement,
	const unordered_map<string, vector<string>>& methodCodeMap,
	const unordered_set<string>& allMethods,
	bool condition,
	const vector<int>& argumentIndices,
	int depth
	) {
	//
	auto indent = StringTools::indent(string(), "\t", depth);
	//
	switch (syntaxTree.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTree.value.getType()) {
					case MinitScript::TYPE_ARRAY:
					case MinitScript::TYPE_MAP:
					case MinitScript::TYPE_SET:
						{
							//
							string generatedInitializerDefinitions;
							//
							generateArrayMapSetVariable(
								minitScript,
								scriptConditionIdx,
								scriptIdx,
								syntaxTree.value,
								methodCodeMap,
								allMethods,
								methodName,
								condition,
								minitScriptClassName,
								generatedInitializerDefinitions,
								depth,
								0,
								"return variableD0;"
							);
							//
							generatedDefinitions+= indent + "// MinitScript transpilation for array/map/set initializer, statement index " + to_string(statement.statementIdx) + ", argument indices " + MinitScript::getArgumentIndicesAsString(argumentIndices, ", ") + "\n";
							generatedDefinitions+= indent + "auto initializer_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(argumentIndices, "_") + " = [&](const SubStatement& subStatement) -> Variable ";
							generatedDefinitions+= generatedInitializerDefinitions;
							//
							break;
						}
					default: break;
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			{
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					generateArrayMapSetInitializer(
						minitScript,
						generatedDefinitions,
						scriptConditionIdx,
						scriptIdx,
						minitScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth
					);
					//
					argumentIdx++;
				}
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
			{
				auto argumentIdx = 1; // TODO: check me!
				for (const auto& argument: syntaxTree.arguments) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					generateArrayMapSetInitializer(
						minitScript,
						generatedDefinitions,
						scriptConditionIdx,
						scriptIdx,
						minitScriptClassName,
						methodName,
						argument,
						statement,
						methodCodeMap,
						allMethods,
						condition,
						nextArgumentIndices,
						depth
					);
					//
					argumentIdx++;
				}
				//
				break;
			}
		default:
			break;
	}
}

bool Transpiler::transpileStatement(
	MinitScript* minitScript,
	string& generatedCode,
	const MinitScript::SyntaxTreeNode& syntaxTree,
	const MinitScript::Statement& statement,
	int scriptConditionIdx,
	int scriptIdx,
	int& statementIdx,
	const unordered_map<string, vector<string>>& methodCodeMap,
	const unordered_set<string>& allMethods,
	bool& scriptStateChanged,
	bool& scriptStopped,
	vector<string>& enabledNamedConditions,
	int depth,
	const vector<int>& argumentIndices,
	const string& returnValue,
	const string& injectCode,
	int additionalIndent) {
	//
	statementIdx++;
	auto currentStatementIdx = statementIdx;

	// indenting
	string minIndentString = "\t";
	string depthIndentString;
	for (auto i = 0; i < depth + additionalIndent; i++) depthIndentString+= "\t";

	//
	struct ArrayAccessStatement {
		ArrayAccessStatement(
			int argumentIdx,
			int statementIdx,
			int leftIdx,
			int rightIdx,
			string statementMethod
		):
			argumentIdx(argumentIdx),
			statementIdx(statementIdx),
			leftIdx(leftIdx),
			rightIdx(rightIdx),
			statementMethod(statementMethod)
		{}
		int argumentIdx;
		int statementIdx;
		int leftIdx;
		int rightIdx;
		string statementMethod;
	};

	//
	vector<ArrayAccessStatement> arrayAccessStatements;

	//
	switch (syntaxTree.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
			{
				// check script user functions
				auto functionStackletScriptIdx = syntaxTree.getScriptIdx();
				if (functionStackletScriptIdx != MinitScript::SCRIPTIDX_NONE) {
					// have a wrapping script.call/script.callStacklet call
					MinitScript::SyntaxTreeNode callSyntaxTreeNode;
					callSyntaxTreeNode.type = MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD;
					callSyntaxTreeNode.value =
						syntaxTree.type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION?
							MinitScript::METHOD_SCRIPTCALLBYINDEX:
							MinitScript::METHOD_SCRIPTCALLSTACKLETBYINDEX;
					// construct argument for name of function/stacklet
					MinitScript::SyntaxTreeNode callArgumentSyntaxTreeNode;
					callArgumentSyntaxTreeNode.type = MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL;
					callArgumentSyntaxTreeNode.value = MinitScript::Variable(functionStackletScriptIdx);
					// add argumnet for name of function/stacklet
					callSyntaxTreeNode.arguments.push_back(callArgumentSyntaxTreeNode);
					// stacklets have no arguments when calling them, functions do have them
					if (syntaxTree.type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION) {
						// add original parameter to call syntaxTree
						for (const auto& argument: syntaxTree.arguments) {
							callSyntaxTreeNode.arguments.push_back(argument);
						}
					}
					// assign script.call/script.callStacklet method
					auto method = minitScript->getMethod(callSyntaxTreeNode.value.getValueAsString());
					if (method == nullptr) {
						Console::printLine("Transpiler::transpileStatement(): method code not found: '" + callSyntaxTreeNode.value.getValueAsString() + "'");
						return false;
					}
					callSyntaxTreeNode.setMethod(method);
					return transpileStatement(
						minitScript,
						generatedCode,
						callSyntaxTreeNode,
						statement,
						scriptConditionIdx,
						scriptIdx,
						statementIdx,
						methodCodeMap,
						allMethods,
						scriptStateChanged,
						scriptStopped,
						enabledNamedConditions,
						depth,
						argumentIndices,
						returnValue,
						injectCode,
						additionalIndent
					);
				} else {
					Console::printLine("Transpiler::transpileStatement(): Function/stacklet not found: '" + syntaxTree.value.getValueAsString() + "'");
					return false;
				}
				//
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
			//
			if ((scriptConditionIdx != MinitScript::SCRIPTIDX_NONE ||
				scriptIdx != MinitScript::SCRIPTIDX_NONE) &&
				(syntaxTree.value.getValueAsString() == "getMethodArgumentVariable" ||
				syntaxTree.value.getValueAsString() == "getVariable" ||
				syntaxTree.value.getValueAsString() == "getVariableReference" ||
				syntaxTree.value.getValueAsString() == "setVariable" ||
				syntaxTree.value.getValueAsString() == "setVariableReference" ||
				syntaxTree.value.getValueAsString() == "setConstant")) {
				//
				for (auto argumentIdx = 0; argumentIdx < syntaxTree.arguments.size(); argumentIdx++) {
					//
					auto nextArgumentIndices = argumentIndices;
					nextArgumentIndices.push_back(argumentIdx);
					//
					auto argumentString = escapeString(syntaxTree.arguments[argumentIdx].value.getValueAsString());
					auto arrayAccessStatementIdx = 0;
					auto arrayAccessStatementLeftIdx = -1;
					auto arrayAccessStatementRightIdx = -1;
					auto quote = '\0';
					auto bracketCount = 0;
					auto lc = '\0';
					for (auto i = 0; i < argumentString.size(); i++) {
						auto c = argumentString[i];
						// handle quotes
						if ((c == '"' || c == '\'') && lc != '\\') {
							if (quote == '\0') {
								quote = c;
							} else
							if (quote == c) {
								quote = '\0';
							}
						} else
						if (c == '[') {
							if (bracketCount == 0) arrayAccessStatementLeftIdx = i;
							bracketCount++;
						} else
						if (c == ']') {
							bracketCount--;
							if (bracketCount == 0) {
								arrayAccessStatementRightIdx = i;
								//
								auto arrayAccessStatementString = StringTools::substring(argumentString, arrayAccessStatementLeftIdx + 1, arrayAccessStatementRightIdx);
								// array append operator []
								if (arrayAccessStatementString.empty() == true) {
									//
									arrayAccessStatementIdx++;
									//
									continue;
								}
								//
								const auto& script = minitScript->getScripts()[scriptConditionIdx != MinitScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
								//
								auto arrayAccessStatementMethod = string() + "array_access_statement_" + to_string(statement.statementIdx) + "_" + MinitScript::getArgumentIndicesAsString(nextArgumentIndices, "_") + "_" + to_string(arrayAccessStatementIdx);
								//
								generatedCode+= minIndentString + depthIndentString + "// we will use " + arrayAccessStatementMethod + "() to determine array access index"+ "\n";
								//
								arrayAccessStatements.emplace_back(
									argumentIdx,
									arrayAccessStatementIdx,
									arrayAccessStatementLeftIdx,
									arrayAccessStatementRightIdx,
									arrayAccessStatementMethod
								);
								//
								arrayAccessStatementIdx++;
							}
						}
						//
						lc = c;
					}
				}
			}
			//
			break;
		default:
			Console::printLine("Transpiler::transpileStatement(): " + minitScript->getStatementInformation(statement) + ": Function or method call expected, but got literal or 'none' syntaxTree");
			return false;

	}

	//
	auto method = syntaxTree.value.getValueAsString();

	// find method code in method code map
	auto methodCodeMapIt = methodCodeMap.find(method);
	if (methodCodeMapIt == methodCodeMap.end()) {
		Console::printLine("Transpiler::transpileStatement(): method code not found: '" + method + "'");
		return false;
	}
	const auto& methodCode = methodCodeMapIt->second;

	// script method
	auto scriptMethod = minitScript->getMethod(string(method));
	if (scriptMethod == nullptr) {
		Console::printLine("Transpiler::transpileStatement(): method not found: '" + method + "'");
		return false;
	}

	// comment about current statement
	generatedCode+= minIndentString + depthIndentString;
	generatedCode+= "// " + (depth > 0?"depth = " + to_string(depth):"") + (argumentIndices.empty() == false?" / argument index = " + to_string(argumentIndices.back()):"");
	generatedCode+= depth > 0 || argumentIndices.empty() == false?": ":"";
	generatedCode+= escapeString(syntaxTree.value.getValueAsString()) + "(" + minitScript->getArgumentsAsString(syntaxTree.arguments) + ")";
	generatedCode+= "\n";

	// argument values header
	generatedCode+= minIndentString + depthIndentString + "{" + "\n";

	// argument indices
	auto parentArgumentIdx = argumentIndices.size() >= 2?argumentIndices[argumentIndices.size() - 2]:MinitScript::ARGUMENTIDX_NONE;
	auto argumentIdx = argumentIndices.empty() == false?argumentIndices.back():MinitScript::ARGUMENTIDX_NONE;

	// statement
	if (depth == 0) {
		generatedCode+= minIndentString + depthIndentString + "\t" + "// statement setup" + "\n";
		if (scriptConditionIdx != MinitScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto& statement = scripts[" + to_string(scriptConditionIdx) + "].conditionStatement;" + "\n";
			generatedCode+= minIndentString + depthIndentString + "\t" + "const SubStatement subStatement(statement, " + to_string(syntaxTree.subLineIdx) + ");" + "\n";
		} else
		if (scriptIdx != MinitScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto& statement = scripts[" + to_string(scriptIdx) + "].statements[" + to_string(statement.statementIdx) + "];" + "\n";
			generatedCode+= minIndentString + depthIndentString + "\t" + "const SubStatement subStatement(statement, " + to_string(syntaxTree.subLineIdx) + ");" + "\n";
		}
		generatedCode+= minIndentString + depthIndentString + "\t" + "getScriptState().statementIdx = subStatement.statement->statementIdx;" + "\n";
		generatedCode+= minIndentString + depthIndentString + "\t" + "//" + "\n";
	} else {
		generatedCode+= minIndentString + depthIndentString + "\t" + "// sub statement setup" + "\n";
		if (scriptConditionIdx != MinitScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const SubStatement subStatement(statement, " + to_string(syntaxTree.subLineIdx) + ");" + "\n";
		} else
		if (scriptIdx != MinitScript::SCRIPTIDX_NONE) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const SubStatement subStatement(statement, " + to_string(syntaxTree.subLineIdx) + ");" + "\n";
		}
	}

	// construct argument values
	string indent = "\t";
	{
		vector<string> argumentsCode;
		if (depth > 0) {
			argumentsCode.push_back("auto& returnValue = argumentsD" + to_string(depth - 1) + (parentArgumentIdx != MinitScript::ARGUMENTIDX_NONE?"AIDX" + to_string(parentArgumentIdx):"") + "[" + to_string(argumentIdx) + "];");
		} else {
			argumentsCode.push_back("Variable returnValue;");
		}
		argumentsCode.push_back("array<Variable, " + to_string(syntaxTree.arguments.size()) + "> arguments {");

		// construct argument values
		if (syntaxTree.arguments.empty() == false) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "// required method code arguments" + "\n";
			auto argumentIdx = 0;
			for (const auto& argument: syntaxTree.arguments) {
				//
				auto nextArgumentIndices = argumentIndices;
				nextArgumentIndices.push_back(argumentIdx);
				//
				auto lastArgument = argumentIdx == syntaxTree.arguments.size() - 1;
				switch (argument.type) {
					case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
						{
							switch (argument.value.getType())  {
								case MinitScript::TYPE_NULL:
									argumentsCode.push_back(indent + "Variable()" + (lastArgument == false?",":""));
									break;
								case MinitScript::TYPE_BOOLEAN:
									{
										bool value;
										argument.value.getBooleanValue(value);
										argumentsCode.push_back(indent + "Variable(" + (value == true?"true":"false") + ")" + (lastArgument == false?",":""));
									}
									break;
								case MinitScript::TYPE_INTEGER:
									{
										int64_t value;
										argument.value.getIntegerValue(value);
										argumentsCode.push_back(indent +  + "Variable(static_cast<int64_t>(" + to_string(value) + "ll))" + (lastArgument == false?",":""));
									}
									break;
								case MinitScript::TYPE_FLOAT:
									{
										float value;
										argument.value.getFloatValue(value);
										argumentsCode.push_back(indent +  + "Variable(" + to_string(value) + "f)" + (lastArgument == false?",":""));
									}
									break;
								case MinitScript::TYPE_STRING:
								case MinitScript::TYPE_FUNCTION_ASSIGNMENT:
								case MinitScript::TYPE_STACKLET_ASSIGNMENT:
									{
										string value;
										auto scriptIdx = MinitScript::SCRIPTIDX_NONE;
										// get it, while its hot
										if (argument.value.getType() == MinitScript::TYPE_FUNCTION_ASSIGNMENT) {
											argument.value.getFunctionValue(value, scriptIdx);
										} else
										if (argument.value.getType() == MinitScript::TYPE_STACKLET_ASSIGNMENT) {
											argument.value.getStackletValue(value, scriptIdx);
										} else {
											argument.value.getStringValue(value);
										}
										value = escapeString(value);
										// take array access statements into account
										auto arrayAccessStatementOffset = 0;
										for (auto& arrayAccessStatement: arrayAccessStatements) {
											if (arrayAccessStatement.argumentIdx != argumentIdx) continue;
											string arrayAccessStatementMethodCall = "\" + " + arrayAccessStatement.statementMethod + "(subStatement).getValueAsString() + \"";
											value =
												StringTools::substring(value, 0, arrayAccessStatement.leftIdx + 1 + arrayAccessStatementOffset) +
												arrayAccessStatementMethodCall +
												StringTools::substring(value, arrayAccessStatement.rightIdx + arrayAccessStatementOffset, value.size());
											arrayAccessStatementOffset-= (arrayAccessStatement.rightIdx - (arrayAccessStatement.leftIdx + 1)) - arrayAccessStatementMethodCall.size();
										}
										//
										argumentsCode.push_back(indent + "Variable(static_cast<VariableType>(" + to_string(argument.value.getType()) + "), string(\"" + value + "\"), " + to_string(scriptIdx) + ")" + (lastArgument == false?",":""));
									}
									//
									break;
								case MinitScript::TYPE_ARRAY:
								case MinitScript::TYPE_MAP:
								case MinitScript::TYPE_SET:
									{
										const auto& script = minitScript->getScripts()[scriptConditionIdx != MinitScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
										auto methodName = createMethodName(minitScript, scriptIdx);										//
										auto initializerMethod = string() + "initializer_" + to_string(statement.statementIdx) + "_" + minitScript->getArgumentIndicesAsString(nextArgumentIndices, "_");
										argumentsCode.push_back(indent + initializerMethod + "(subStatement)" + (lastArgument == false?",":""));
									}
									break;
								default:
									{
										Console::printLine("Transpiler::transpileStatement(): " + minitScript->getStatementInformation(statement) + ": '" + argument.value.getAsString() + "': Unknown argument type: " + argument.value.getTypeAsString());
										break;
									}
							}
							break;
						}
					case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
					case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
						{
							argumentsCode.push_back(indent + "Variable()" + (lastArgument == false?",":"") + " // arguments[" + to_string(argumentIdx) + "] --> returnValue of " + escapeString(argument.value.getValueAsString()) + "(" + minitScript->getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
						{
							argumentsCode.push_back(indent + "Variable()" + (lastArgument == false?",":"") + " // arguments[" + to_string(argumentIdx) + "] --> returnValue of " + escapeString(argument.value.getValueAsString()) + "(" + minitScript->getArgumentsAsString(argument.arguments) + ")");
							break;
						}
					default:
						break;
				}
				//
				argumentIdx++;
			}
		}
		// end of arguments initialization
		argumentsCode.push_back("};");

		//
		argumentsCode.push_back("array<Variable, " + to_string(syntaxTree.arguments.size()) + ">& argumentsD" + to_string(depth) + (argumentIdx != MinitScript::ARGUMENTIDX_NONE?"AIDX" + to_string(argumentIdx):"") + " = arguments;");

		// argument values header
		for (const auto& codeLine: argumentsCode) {
			generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + "\n";
		}
	}

	// enabled named conditions
	if (method == MinitScript::METHOD_ENABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::printLine("Transpiler::transpileStatement(): " + minitScript->getStatementInformation(statement) + ": " + MinitScript::METHOD_ENABLENAMEDCONDITION + "(): Expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueAsString();
			enabledNamedConditions.erase(
				remove(
					enabledNamedConditions.begin(),
					enabledNamedConditions.end(),
					name
				),
				enabledNamedConditions.end()
			);
			enabledNamedConditions.push_back(name);
		}
	} else
	if (method == MinitScript::METHOD_DISABLENAMEDCONDITION && syntaxTree.arguments.empty() == false) {
		if (syntaxTree.arguments.size() != 1) {
			Console::printLine("Transpiler::transpileStatement(): " + minitScript->getStatementInformation(statement) + ": " + MinitScript::METHOD_DISABLENAMEDCONDITION + "(): Expected string argument @ 0");
		} else {
			string name = syntaxTree.arguments[0].value.getValueAsString();
			enabledNamedConditions.erase(
				remove(
					enabledNamedConditions.begin(),
					enabledNamedConditions.end(),
					name
				),
				enabledNamedConditions.end()
			);
		}
	}

	// transpile method/function call argument
	{
		auto argumentIdx = 0;
		for (const auto& argument: syntaxTree.arguments) {
			switch (argument.type) {
				case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
				case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
				case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
					{
						//
						auto nextArgumentIndices = argumentIndices;
						nextArgumentIndices.push_back(argumentIdx);

						//
						if (transpileStatement(
							minitScript,
							generatedCode,
							argument,
							statement,
							scriptConditionIdx,
							scriptIdx,
							statementIdx,
							methodCodeMap,
							allMethods,
							scriptStateChanged,
							scriptStopped,
							enabledNamedConditions,
							depth + 1,
							nextArgumentIndices,
							returnValue,
							string(),
							additionalIndent
						) == false) {
							Console::printLine("Transpiler::transpileStatement(): transpileStatement(): " + minitScript->getStatementInformation(statement) + ": '" + syntaxTree.value.getValueAsString() + "(" + minitScript->getArgumentsAsString(syntaxTree.arguments) + ")" + "': transpile error");
						}
					}
					//
					break;
				default:
					//
					break;
			}
			argumentIdx++;
		}
	}

    // special case: inject EVALUATEMEMBERACCESS_MEMBER
	if (scriptMethod != nullptr && scriptMethod->getMethodName() == "memberExecute") {
		if (allMethods.contains(syntaxTree.arguments[1].value.getValueAsString()) == true) {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(syntaxTree.arguments[1].value.getValueAsString()) + ";\n";
		} else {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_NONE;" + "\n";
		}
	}

	/*
	// special case: inject EVALUATEMEMBERACCESS_MEMBER for "internal.script.evaluateMemberAccess"
	if (scriptMethod != nullptr && scriptMethod->getMethodName() == "internal.script.evaluateMemberAccess") {
		//
		auto callArgumentIdx = 0;
		//
		if (syntaxTree.arguments[0].value.getType() != MinitScript::TYPE_NULL) {
			generateVariableAccess(
				minitScript,
				generatedCode,
				scriptConditionIdx,
				scriptIdx,
				syntaxTree.arguments[0].value.getValueAsString(),
				minIndentString + depthIndentString + "\t",
				false,
				false,
				true,
				false,
				false,
				false,
				"auto EVALUATEMEMBERACCESS_ARGUMENT" + to_string(callArgumentIdx) + " = "
			);
		} else {
			generatedCode+= minIndentString + depthIndentString + "\t" + "auto EVALUATEMEMBERACCESS_ARGUMENT" + to_string(callArgumentIdx) + " = Variable();" + "\n";
		}
		//
		callArgumentIdx++;
		//
		vector<string> argumentVariables;
		for (auto argumentIdx = 3; argumentIdx < syntaxTree.arguments.size(); argumentIdx+=2) {
			// do we have a this variable name?
			argumentVariables.push_back(string());
			//
			if (syntaxTree.arguments[argumentIdx].value.getType() != MinitScript::TYPE_NULL) {
				//
				generateVariableAccess(
					minitScript,
					argumentVariables[argumentVariables.size() - 1],
					scriptConditionIdx,
					scriptIdx,
					syntaxTree.arguments[argumentIdx].value.getValueAsString(),
					minIndentString + depthIndentString + "\t\t",
					false,
					false,
					true,
					false,
					false,
					false,
					string(),
					",\n",
					argumentIdx,
					-1
				);
			} else {
				//
				argumentVariables[argumentVariables.size() - 1] = minIndentString + depthIndentString + "\t\t" + "Variable()," + "\n";
			}
			//
			callArgumentIdx++;
		}
		generatedCode+= minIndentString + depthIndentString + "\t" + "array<Variable, " + to_string(argumentVariables.size()) + "> EVALUATEMEMBERACCESS_ARGUMENTS" + " {" + "\n";
		for (const auto& argumentVariable: argumentVariables) generatedCode+= argumentVariable;
		generatedCode+= minIndentString + depthIndentString + "\t" + "};" + "\n";
		//
		if (allMethods.contains(syntaxTree.arguments[2].value.getValueAsString()) == true) {

			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_" + StringTools::toUpperCase(syntaxTree.arguments[2].value.getValueAsString()) + ";\n";
		} else {
			generatedCode+= minIndentString + depthIndentString + "\t" + "const auto EVALUATEMEMBERACCESS_MEMBER = EVALUATEMEMBERACCESSARRAYIDX_NONE;" + "\n";
		}
	}
	*/

	// do we have a variable look up or setting a variable?
	// 	transfer to use local method and global class variables
	if (syntaxTree.type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD &&

		(syntaxTree.value.getValueAsString() == "getMethodArgumentVariable" ||
		syntaxTree.value.getValueAsString() == "getVariable" ||
		syntaxTree.value.getValueAsString() == "getVariableReference" ||
		syntaxTree.value.getValueAsString() == "setVariable" ||
		syntaxTree.value.getValueAsString() == "setVariableReference" ||
		syntaxTree.value.getValueAsString() == "setConstant" ||
		syntaxTree.value.getValueAsString() == "unsetVariableReference") &&
		syntaxTree.arguments.empty() == false &&
		syntaxTree.arguments[0].type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL) {
		// generate variable access
		generateVariableAccess(
			minitScript,
			generatedCode,
			scriptConditionIdx,
			scriptIdx,
			syntaxTree.arguments[0].value.getValueAsString(),
			minIndentString + depthIndentString + "\t",
			syntaxTree.value.getValueAsString() == "getMethodArgumentVariable",
			syntaxTree.value.getValueAsString() == "getVariable",
			syntaxTree.value.getValueAsString() == "getVariableReference",
			syntaxTree.value.getValueAsString() == "setVariable",
			syntaxTree.value.getValueAsString() == "setVariableReference",
			syntaxTree.value.getValueAsString() == "setConstant"
		);
	} else {
		const auto& script = minitScript->getScripts()[scriptConditionIdx != MinitScript::SCRIPTIDX_NONE?scriptConditionIdx:scriptIdx];
		// generate code
		generatedCode+= minIndentString + depthIndentString + "\t" + "// method code: " + string(method) + "\n";
		for (auto codeLine: methodCode) {
			codeLine = StringTools::replace(codeLine, "getMethodName()", "string(\"" + string(method) + "\")");
			// replace returns with gotos
			if (StringTools::regexMatch(codeLine, "[\\ \\t]*return[\\ \\t]*;.*") == true) {
				Console::printLine("Transpiler::transpileStatement(): method '" + string(method) + "': return statement not supported!");
				return false;
			} else
			if (StringTools::regexMatch(codeLine, "[\\ \\t]*minitScript[\\ \\t]*->gotoStatementGoto[\\ \\t]*\\([\\ \\t]*\\*subStatement\\.statement[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true) {
				if (statement.gotoStatementIdx != MinitScript::STATEMENTIDX_NONE) {
					 // find indent
					int indent = 0;
					for (auto i = 0; i < codeLine.size(); i++) {
						auto c = codeLine[i];
						if (c == '\t') {
							indent++;
						} else {
							break;
						}
					}
					string indentString;
					for (auto i = 0; i < indent; i++) indentString+= "\t";
					//
					generatedCode+= minIndentString + indentString + depthIndentString + "\t" + "goto minitscript_statement_" + to_string(statement.gotoStatementIdx) + ";\n";
				} else {
					// for now we exit the C++ method after setting the gotoStatement and reenter the C++ method
					generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + " return;" + "\n";
				}
			} else
			if (StringTools::regexMatch(codeLine, "[\\ \\t]*minitScript[\\ \\t]*->gotoStatement[\\ \\t]*\\(.*\\)[\\ \\t]*;[\\ \\t]*") == true) {
				// TODO: those are the break and continue statements, we might improve this later
				//	we support break and continue with several levels, so this is not easy to be solved by iterating the statements, lets see later
				//	for now we exit the C++ method after setting the gotoStatement and reenter the C++ method
				generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + " return;" + "\n";
			} else
			if (StringTools::regexMatch(codeLine, "[\\ \\t]*MINITSCRIPT_METHODUSAGE_COMPLAIN[\\ \\t]*\\([\\ \\t]*(.*)\\)[\\ \\t]*;[\\ \\t]*") == true ||
				StringTools::regexMatch(codeLine, "[\\ \\t]*MINITSCRIPT_METHODUSAGE_COMPLAINM[\\ \\t]*\\([\\ \\t]*(.*)[\\ \\t]*,[\\ \\t]*(.*)[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true ||
				StringTools::regexMatch(codeLine, "[\\ \\t]*minitScript[\\ \\t]*->emit[\\ \\t]*\\([\\ \\t]*[a-zA-Z0-9]*[\\ \\t]*\\)[\\ \\t]*;[\\ \\t]*") == true) {
				 // find indent
				int indent = 0;
				for (auto i = 0; i < codeLine.size(); i++) {
					auto c = codeLine[i];
					if (c == '\t') {
						indent++;
					} else {
						break;
					}
				}
				string indentString;
				for (auto i = 0; i < indent; i++) indentString+= "\t";
				codeLine = StringTools::trim(codeLine);
				//
				generatedCode+=
					minIndentString +
					depthIndentString +
					indentString +
						"\t{ " + codeLine +
							(
								#if defined(MINITSCRIPT_EVENTS)
									script.type == MinitScript::Script::TYPE_ON || script.type == MinitScript::Script::TYPE_ONENABLED
								#else
									false
								#endif
								?
							" MINITSCRIPT_METHOD_POPSTACK(); return" +
								(
									returnValue.empty() == false?" " + returnValue:""
								) +
								";":""
							) +
						" }\n";
			} else {
				if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*minitScript[\\ \\t]*->[\\ \\t]*setScriptStateState[\\ \\t]*\\([\\ \\t]*.+[\\ \\t]*\\);.*") == true) {
					scriptStateChanged = true;
				}
				if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*minitScript[\\ \\t]*->[\\ \\t]*stopScriptExecutation[\\ \\t]*\\([\\ \\t]*\\);.*") == true) {
					scriptStopped = true;
				} else
				if (StringTools::regexMatch(codeLine, ".*[\\ \\t]*minitScript[\\ \\t]*->[\\ \\t]*stopRunning[\\ \\t]*\\([\\ \\t]*\\);.*") == true) {
					scriptStopped = true;
				}
				generatedCode+= minIndentString + depthIndentString + "\t" + codeLine + "\n";
			}
		}
	}

	// inject code if we have any to inject
	if (injectCode.empty() == false) {
		generatedCode+= minIndentString + depthIndentString + "\t" + injectCode + "\n";
	}

	//
	generatedCode+= minIndentString + depthIndentString + "}" + "\n";

	//
	return true;
}

bool Transpiler::transpile(MinitScript* minitScript, const string& className, string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const unordered_set<string>& allMethods) {
	if (scriptIdx < 0 || scriptIdx >= minitScript->getScripts().size()) {
		Console::printLine("Transpiler::transpile(): invalid script index");
		return false;
	}

	//
	const auto& script = minitScript->getScripts()[scriptIdx];

	//
	Console::printLine("Transpiler::transpile(): transpiling code for " + getScriptTypeReadableName(script.type) + " = '" + script.condition + "', with name '" + script.name + "'");

	//
	string methodIndent = "\t";
	string generatedCodeHeader;

	//
	generatedCodeHeader+= methodIndent + "// script setup" + "\n";
	generatedCodeHeader+= methodIndent + "auto minitScript = this;" + "\n";

	// method name
	auto methodName = createMethodName(minitScript, scriptIdx);

	//
	unordered_set<int> gotoStatementIdxSet;
	for (const auto& statement: script.statements) {
		if (statement.gotoStatementIdx != MinitScript::STATEMENTIDX_NONE) {
			gotoStatementIdxSet.insert(statement.statementIdx);
			gotoStatementIdxSet.insert(statement.gotoStatementIdx);
		}
	}
	gotoStatementIdxSet.insert(script.statements.size() - 1);

	//
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	vector<string> enabledNamedConditions;
	auto scriptStateChanged = false;
	for (auto scriptStatementIdx = MinitScript::STATEMENTIDX_FIRST; scriptStatementIdx < script.statements.size(); scriptStatementIdx++) {
		const auto& statement = script.statements[scriptStatementIdx];
		const auto& syntaxTree = script.syntaxTree[scriptStatementIdx];
		//
		if (scriptStateChanged == true || gotoStatementIdxSet.find(statement.statementIdx) != gotoStatementIdxSet.end()) {
			generatedCodeHeader+= methodIndent + "if (minitScriptGotoStatementIdx == " + to_string(statement.statementIdx)  + ") goto minitscript_statement_" + to_string(statement.statementIdx) + "; else" + "\n";
		}

		// enabled named conditions
		if (enabledNamedConditions.empty() == false) {
			generatedCode+= "\n";
			generatedCode+= methodIndent + "// enabled named conditions" + "\n";
			generatedCode+= methodIndent + "{" + "\n";
			generatedCode+= methodIndent + "\t" + "auto scriptIdxToStart = determineNamedScriptIdxToStart();" + "\n";
			generatedCode+= methodIndent + "\t" + "if (scriptIdxToStart != SCRIPTIDX_NONE && scriptIdxToStart != getScriptState().scriptIdx) {" + "\n";
			generatedCode+= methodIndent + "\t\t" + "resetScriptExecutationState(scriptIdxToStart, STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
			generatedCode+= methodIndent + "\t\t" + "timeEnabledConditionsCheckLast = _Time::getCurrentMillis();" + "\n";
			generatedCode+= methodIndent + "\t\t" + "return;" + "\n";
			generatedCode+= methodIndent + "\t" + "}" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}

		// statement_xyz goto label
		generatedCode+= methodIndent + "// statement: " + to_string(statement.statementIdx) + "\n";
		if (scriptStateChanged == true || gotoStatementIdxSet.find(statement.statementIdx) != gotoStatementIdxSet.end()) {
			generatedCode+= methodIndent + "minitscript_statement_" + to_string(statement.statementIdx) + ":" + "\n";
		}
		scriptStateChanged = false;
		auto scriptStopped = false;
		transpileStatement(
			minitScript,
			generatedCode,
			syntaxTree,
			statement,
			MinitScript::SCRIPTIDX_NONE,
			scriptIdx,
			statementIdx,
			methodCodeMap,
			allMethods,
			scriptStateChanged,
			scriptStopped,
			enabledNamedConditions
		);
		if (scriptStopped == true) {
			generatedCode+= methodIndent + "if (getScriptState().running == false) {" + "\n";
			generatedCode+= methodIndent + "\t" + "MINITSCRIPT_METHOD_POPSTACK();" + "\n";
			generatedCode+= methodIndent + "\t" + "return;" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}
		if (scriptStateChanged == true) {
			generatedCode+= methodIndent + "if (getScriptState().state != STATEMACHINESTATE_NEXT_STATEMENT) {" + "\n";
			generatedCode+= methodIndent + "\t" + "getScriptState().statementIdx++;" + "\n";
			generatedCode+= methodIndent + "\t" + "return;" + "\n";
			generatedCode+= methodIndent + "}" + "\n";
		}
	}
	generatedCode+= methodIndent + "getScriptState().scriptIdx = SCRIPTIDX_NONE;" + "\n";
	generatedCode+= methodIndent + "getScriptState().statementIdx = STATEMENTIDX_NONE;" + "\n";
	generatedCode+= methodIndent + "setScriptStateState(STATEMACHINESTATE_WAIT_FOR_CONDITION);" + "\n";

	//
	generatedCodeHeader+= methodIndent + "if (minitScriptGotoStatementIdx != STATEMENTIDX_NONE && minitScriptGotoStatementIdx != STATEMENTIDX_FIRST) _Console::printLine(\"" + className + "::" + methodName + "(): Can not go to statement \" + to_string(minitScriptGotoStatementIdx));" + "\n";
	//
	generatedCode = generatedCodeHeader + generatedCode;
	return true;
}

bool Transpiler::transpileCondition(MinitScript* minitScript, string& generatedCode, int scriptIdx, const unordered_map<string, vector<string>>& methodCodeMap, const unordered_set<string>& allMethods, const string& returnValue, const string& injectCode, int depth) {
	if (scriptIdx < 0 || scriptIdx >= minitScript->getScripts().size()) {
		Console::printLine("Transpiler::transpileScriptCondition(): invalid script index");
		return false;
	}

	//
	const auto& script = minitScript->getScripts()[scriptIdx];

	//
	Console::printLine("Transpiler::transpileScriptCondition(): transpiling code condition for condition = '" + script.condition + "', with name '" + script.name + "'");

	//
	auto statementIdx = MinitScript::STATEMENTIDX_FIRST;
	auto scriptStateChanged = false;
	auto scriptStopped = false;
	vector<string >enabledNamedConditions;
	transpileStatement(
		minitScript,
		generatedCode,
		script.conditionSyntaxTree,
		script.conditionStatement,
		scriptIdx,
		MinitScript::SCRIPTIDX_NONE,
		statementIdx,
		methodCodeMap,
		allMethods,
		scriptStateChanged,
		scriptStopped,
		enabledNamedConditions,
		0,
		{},
		returnValue,
		injectCode,
		depth + 1
	);

	//
	generatedCode+= "\t\n";

	//
	return true;
}

const string Transpiler::createSourceCode(const MinitScript::SyntaxTreeNode& syntaxTreeNode) {
	//
	string result;
	switch (syntaxTreeNode.type) {
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_LITERAL:
			{
				switch(syntaxTreeNode.value.getType()) {
					case MinitScript::TYPE_NULL:
						{
							result+= (result.empty() == false?", ":"") + string("<VOID>");
							break;
						}
					case MinitScript::TYPE_BOOLEAN:
					case MinitScript::TYPE_INTEGER:
					case MinitScript::TYPE_FLOAT:
						{
							result+= (result.empty() == false?", ":"") + syntaxTreeNode.value.getValueAsString();
							break;
						}
					case MinitScript::TYPE_STRING:
						{
							result+= (result.empty() == false?", ":"") + string("\"") + syntaxTreeNode.value.getValueAsString() + string("\"");
							break;
						}
					default:
						{
							result+= (result.empty() == false?", ":"") + string("<COMPLEX DATATYPE>");
							break;
						}
				}
				break;
			}
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_FUNCTION:
		case MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_STACKLET:
			{
				auto endElse = syntaxTreeNode.value.getValueAsString() == "end" || syntaxTreeNode.value.getValueAsString() == "else";
				result+= syntaxTreeNode.value.getValueAsString();
				if (endElse == false) result+= string("(");
				auto argumentIdx = 0;
				for (const auto& argument: syntaxTreeNode.arguments) {
					if (argumentIdx > 0) result+= ", ";
					result+= createSourceCode(argument);
					argumentIdx++;
				}
				if (endElse == false) result+= string(")");
				break;
			}
		default:
			break;
	}
	return result;
}

const string Transpiler::createSourceCode(MinitScript::Script::Type scriptType, const string& condition, const vector<MinitScript::Script::Argument>& functionArguments, const string& name, const MinitScript::SyntaxTreeNode& conditionSyntaxTree, const vector<MinitScript::SyntaxTreeNode>& syntaxTree) {
	//
	string result;
	//
	switch(scriptType) {
		case MinitScript::Script::TYPE_FUNCTION: {
			result+= "function: ";
			if (condition.empty() == false) {
				result+= condition;
			}
			auto argumentIdx = 0;
			result+= "(";
			for (const auto& argument: functionArguments) {
				if (argumentIdx > 0) result+= ", ";
				if (argument.reference == true) result+= "&";
				if (argument.privateScope == true) result+= "&";
				result+= argument.name;
				argumentIdx++;
			}
			result+= ")";
			break;
		}
		#if defined(MINITSCRIPT_EVENTS)
			// events
			case MinitScript::Script::TYPE_ON:
				{
					result+= "on: ";
					if (condition.empty() == false) {
						result+= condition;
					}
					break;
				}
			case MinitScript::Script::TYPE_ONENABLED:
				{
					result+= "on-enabled: ";
					if (condition.empty() == false) {
						result+= condition;
					}
					break;
				}
		#endif
		default: break;
	}
	if (conditionSyntaxTree.type != MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_NONE)
		result+= createSourceCode(conditionSyntaxTree);
	if (name.empty() == false) {
		result+= " := " + name + "\n";
	} else {
		result+= "\n";
	}
	//
	auto indent = 1;
	for (const auto& syntaxTreeNode: syntaxTree) {
		if (syntaxTreeNode.type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueAsString() == "if") indent+= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "elseif") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "else") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "end") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "forTime") indent-= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "forCondition") indent-= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "switch") indent-= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "case") indent-= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "default") indent-= 1;
		}
		for (auto i = 0; i < indent; i++) result+= "\t";
		result+= createSourceCode(syntaxTreeNode) + "\n";
		if (syntaxTreeNode.type == MinitScript::SyntaxTreeNode::SCRIPTSYNTAXTREENODE_EXECUTE_METHOD) {
			if (syntaxTreeNode.value.getValueAsString() == "if") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "elseif") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "else") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "end") indent+= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "forTime") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "forCondition") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "switch") indent+= 0; else
			if (syntaxTreeNode.value.getValueAsString() == "case") indent+= 1; else
			if (syntaxTreeNode.value.getValueAsString() == "default") indent+= 1;
		}
	}
	return result;
}

const string Transpiler::createSourceCode(MinitScript* minitScript) {
	string result;
	// create source code
	for (const auto& script: minitScript->getScripts()) {
		result+= createSourceCode(script.type, script.emitCondition == true?script.condition:string(), script.arguments, script.name, script.conditionSyntaxTree, script.syntaxTree);
		result+= "\n";
	}
	//
	return result;
}
