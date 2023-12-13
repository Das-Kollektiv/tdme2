#include <algorithm>
#include <cstdlib>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/math/Math.h>
#include <miniscript/os/filesystem/FileSystem.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/Transpiler.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Character.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Exception.h>
#include <miniscript/utilities/Integer.h>
#include <miniscript/utilities/StringTools.h>

using std::exit;
using std::find;
using std::make_unique;
using std::map;
using std::set;
using std::string;
using std::string_view;
using std::unique;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using miniscript::math::Math;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::Transpiler;
using miniscript::miniscript::Version;
using miniscript::os::filesystem::FileSystem;
using miniscript::utilities::Character;
using miniscript::utilities::Console;
using miniscript::utilities::Exception;
using miniscript::utilities::Integer;
using miniscript::utilities::StringTools;

namespace miniscript {
namespace tools {
class TranspilerTool {
public:

static int compare_includes(const string& lhs, const string& rhs) {
	if (StringTools::startsWith(lhs, "#include <tdme/tdme.h>") == true) return true; else
	if (StringTools::startsWith(rhs, "#include <tdme/tdme.h>") == true) return false;
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

static bool replace(const vector<string> input, const string& startTag, const string& endTag, const string& replacement, vector<string>& output) {
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
}

static void processFile(const string& scriptFileName, const string& transpilationFileName, const vector<string>& miniScriptExtensionFileNames) {
	Console::println("Processing script: " + scriptFileName);


	//
	auto miniScript = make_unique<MiniScript>();
	miniScript->parseScript(
		FileSystem::getPathName(scriptFileName),
		FileSystem::getFileName(scriptFileName)
	);
	if (miniScript == nullptr) {
		Console::println("No script instance: " + scriptFileName);
		return;
	}

	//
	unordered_map<string, vector<string>> methodCodeMap;
	auto allMethods = Transpiler::getAllClassesMethodNames(miniScript.get());

	//
	vector<string> transpilationUnitIncludes;
	vector<string> transpilationUnitUsings;

	//
	vector<string> transpilationUnits;
	for (const auto& transpilationUnit: miniScript->getTranspilationUnits()) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: miniScriptExtensionFileNames) transpilationUnits.push_back(transpilationUnit);
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
				StringTools::startsWith(trimmedLine, "miniScript->registerMethod") == true) {
				auto bracketCount = 0;
				string className;
				if (StringTools::firstIndexOf(StringTools::substring(trimmedLine, 14), "new") == string::npos) {
					Console::println("src/miniscript/utilities/MiniScript.cpp: registerMethod @ " + to_string(i) + ": '" + trimmedLine + "': unable to determine class name");
				} else {
					auto classNameStartIdx = trimmedLine.find("registerMethod") + 14 + 5;
					for (auto j = classNameStartIdx; j < trimmedLine.size(); j++) {
						auto c = trimmedLine[j];
						if (c == '(') break;
						if (c == ' ') continue;
						className+= c;
					}
					Transpiler::gatherMethodCode(transpilationUnitCode, className, i, methodCodeMap);
				}
			}
		}
	}

	//
	sort(transpilationUnitIncludes.begin(), transpilationUnitIncludes.end(), compare_includes);
	transpilationUnitIncludes.erase(unique(transpilationUnitIncludes.begin(), transpilationUnitIncludes.end()), transpilationUnitIncludes.end());

	//
	sort(transpilationUnitUsings.begin(), transpilationUnitUsings.end(), compare_includes);
	transpilationUnitUsings.erase(unique(transpilationUnitUsings.begin(), transpilationUnitUsings.end()), transpilationUnitUsings.end());

	//
	Console::println(miniScript->getInformation());

	//
	string headerIndent = "\t";
	string methodCodeIndent = "\t";
	const auto& scripts = miniScript->getScripts();
	string generatedExecuteCode;
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			// method name
			string methodName =
				(script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?
					"":
					(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on_":"on_enabled_")
				) +
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);
			//
			generatedExecuteCode+= headerIndent + "\t\t" + "if (getScriptState().scriptIdx == " + to_string(scriptIdx) + ") " + methodName + "(scriptState.statementIdx); else\n";
			scriptIdx++;
		}
	}
	if (generatedExecuteCode.empty() == false) generatedExecuteCode+= headerIndent + "\t\t\t" + ";\n";

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
	Transpiler::generateMiniScriptEvaluateMemberAccessArrays(miniScript.get(), memberAccessEvaluationDeclarations, memberAccessEvaluationDefinitions);

	//
	string miniScriptClassName = FileSystem::getFileName(transpilationFileName);
	string generatedDeclarations = "\n";
	generatedDeclarations+= string() + "public:" + "\n";
	generatedDeclarations+= headerIndent + "// overridden methods" + "\n";
	generatedDeclarations+= headerIndent + "void registerMethods() override;" + "\n";
	generatedDeclarations+= headerIndent + "void emit(const string& condition) override;" + "\n";
	generatedDeclarations+= headerIndent + "inline void startScript() override {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (native == false) {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "MiniScript::startScript();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "auto& scriptState = getScriptState();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "for (const auto& [scriptVariableName, scriptVariable]: scriptState.variables) delete scriptVariable;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "scriptState.variables.clear();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "getScriptState().running = true;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "registerVariables();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "resetScriptExecutationState(" + to_string(initializeScriptIdx) + ", STATEMACHINESTATE_NEXT_STATEMENT);" + "\n";
	generatedDeclarations+= headerIndent + "}" + "\n";
	generatedDeclarations+= headerIndent + "inline void execute() override {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (native == false) {" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "MiniScript::execute();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "\t" + "return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "auto& scriptState = getScriptState();" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "// execute while having statements to be processed" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().state == STATEMACHINESTATE_NEXT_STATEMENT) {" + "\n";
	generatedDeclarations+= generatedExecuteCode;
	generatedDeclarations+= headerIndent + "\t" + "}" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "if (getScriptState().running == false) return;" + "\n";
	generatedDeclarations+= headerIndent + "\t" + "executeStateMachine();" + "\n";
	generatedDeclarations+= headerIndent + "}" + "\n";
	generatedDeclarations+= "\n";
	generatedDeclarations+= string() + "protected:" + "\n";

	//
	for (const auto& memberAccessEvaluationDeclaration: memberAccessEvaluationDeclarations) {
		generatedDeclarations+= headerIndent + memberAccessEvaluationDeclaration + "\n";
	}
	generatedDeclarations+= "\n";

	//
	generatedDeclarations+= headerIndent + "// overridden methods" + "\n";
	generatedDeclarations+= headerIndent + "void initializeNative() override;" + "\n";
	generatedDeclarations+= headerIndent + "int determineScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= headerIndent + "int determineNamedScriptIdxToStart() override;" + "\n";
	generatedDeclarations+= "\n";

	string registerMethodsDefinitions;
	registerMethodsDefinitions+= "void " + miniScriptClassName + "::registerMethods() {" + "\n";
	registerMethodsDefinitions+= methodCodeIndent+ "MiniScript::registerMethods();" + "\n";
	registerMethodsDefinitions+= methodCodeIndent + "if (native == false) return;" + "\n";
	//
	for (const auto& memberAccessEvaluationDefintion: memberAccessEvaluationDefinitions) {
		registerMethodsDefinitions+= methodCodeIndent + memberAccessEvaluationDefintion + "\n";
	}
	registerMethodsDefinitions+= string() + "}" + "\n";

	//
	string emitDefinition;
	emitDefinition+= "void " + miniScriptClassName + "::emit(const string& condition) {" + "\n";
	emitDefinition+= methodCodeIndent + "if (native == false) {" + "\n";
	emitDefinition+= methodCodeIndent + "\t" + "MiniScript::emit(condition);" + "\n";
	emitDefinition+= methodCodeIndent + "\t" + "return;" + "\n";
	emitDefinition+= methodCodeIndent + "}" + "\n";
	string generatedDefinitions = "\n";
	string initializeNativeDefinition;
	initializeNativeDefinition+= "void " + miniScriptClassName + "::initializeNative() {" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNative(true);" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeHash(\"" + miniScript->getNativeHash() + "\");" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeScripts(" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "\t" + "{" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "Script(" + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?"Script::SCRIPTTYPE_FUNCTION":(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"Script::SCRIPTTYPE_ON":"Script::SCRIPTTYPE_ONENABLED")) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + to_string(script.line) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.condition, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.executableCondition, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "Statement(" + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.line) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.statementIdx) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(StringTools::replace(script.conditionStatement.statement, "\\", "\\\\"), "\"", "\\\""), "\n", "\\n") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(StringTools::replace(script.conditionStatement.executableStatement, "\\", "\\\\"), "\"", "\\\""), "\n", "\\n") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.gotoStatementIdx) + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + ")," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + script.name + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.emitCondition == true?"true":"false") + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{" + "\n";
			auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
			for (const auto& statement: script.statements) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "Statement(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.line) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.statementIdx) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(StringTools::replace(statement.statement, "\\", "\\\\"), "\n", "\\n"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(StringTools::replace(statement.executableStatement, "\\", "\\\\"), "\n", "\\n"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.gotoStatementIdx) + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + ")" + (statementIdx < script.statements.size() - 1?",":"") + "\n";
				statementIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{},\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.callableFunction == true?"true":"false") + ",\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{\n";
			auto argumentIdx = 0;
			for (const auto& argument: script.functionArguments) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "Script::ScriptArgument(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + argument.name + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + (argument.reference == true?"true":"false") + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" ")" + (argumentIdx != script.functionArguments.size() - 1?",":"") + "\n";
				argumentIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + ")" + (scriptIdx < scripts.size() - 1?",":"") + "\n";
			scriptIdx++;
		}
	}
	initializeNativeDefinition+= methodCodeIndent + "\t" + "}" + "\n";
	initializeNativeDefinition+= methodCodeIndent + ");" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeFunctions(" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "\t" + "{" + "\n";
	auto functionItIdx = 0;
	for (const auto& [functionName, functionIdx]: miniScript->functions) {
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "{" + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + functionName + "\"," + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + to_string(functionIdx) + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "}" + (functionItIdx != miniScript->functions.size() - 1?",":"") + "\n";
		functionItIdx++;
	}
	initializeNativeDefinition+= methodCodeIndent + "\t" + "}" + "\n";
	initializeNativeDefinition+= methodCodeIndent + ");" + "\n";
	initializeNativeDefinition+= string() + "}" + "\n";

	//
	string generatedDetermineScriptIdxToStartDefinition = "\n";
	generatedDetermineScriptIdxToStartDefinition+= "int " + miniScriptClassName + "::determineScriptIdxToStart() {" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "\t" + "if (native == false) return MiniScript::determineScriptIdxToStart();" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "\t" + "auto miniScript = this;" + "\n";
	string generatedDetermineNamedScriptIdxToStartDefinition = "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= "int " + miniScriptClassName + "::determineNamedScriptIdxToStart() {" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "if (native == false) return MiniScript::determineNamedScriptIdxToStart();" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "auto miniScript = this;" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "for (const auto& enabledNamedCondition: enabledNamedConditions) {" + "\n";
	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			// method name
			string methodName =
				(script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?
					"":
					(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on_":"on_enabled_")
				) +
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);

			string emitName =
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);

			// emit code
			if (script.scriptType == MiniScript::Script::SCRIPTTYPE_ON && StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true) {
				string emitDefinitionIndent = "\t";
				emitDefinition+= emitDefinitionIndent + "if (condition == \"" + emitName + "\") {" + "\n";
				emitDefinition+= emitDefinitionIndent + "\t" + methodName + "(STATEMENTIDX_FIRST);" + "\n";
				emitDefinition+= emitDefinitionIndent + "} else" + "\n";
			}

			// declaration
			generatedDeclarations+= headerIndent + "/**" + "\n";
			generatedDeclarations+= headerIndent + " * Miniscript transpilation of: " + (script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?"function":(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on":"on-enabled")) + ": " + script.condition + (script.name.empty() == false?" (" + script.name + ")":"") + "\n";
			generatedDeclarations+= headerIndent + " * @param miniScriptGotoStatementIdx MiniScript goto statement index" + "\n";
			generatedDeclarations+= headerIndent + " */" + "\n";
			generatedDeclarations+= headerIndent + "void " + methodName + "(int miniScriptGotoStatementIdx);" + "\n";
			generatedDeclarations+= "\n";

			// transpile definition
			generatedDefinitions+= "void " + miniScriptClassName + "::" + methodName + "(int miniScriptGotoStatementIdx) {" + "\n";
			string generatedSubCode;
			Transpiler::transpile(miniScript.get(), generatedSubCode, scriptIdx, methodCodeMap, allMethods);
			generatedDefinitions+= generatedSubCode;
			generatedDefinitions+= string() + "}" + "\n\n";

			//
			if (script.emitCondition == false) {
				if (script.scriptType == MiniScript::Script::SCRIPTTYPE_ONENABLED) {
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "// next statements belong to tested enabled named condition with name \"" + script.name + "\"" + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "if (enabledNamedCondition == \"" + script.name + "\")" + "\n";
				}
				Transpiler::transpileScriptCondition(
					miniScript.get(),
					script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?generatedDetermineScriptIdxToStartDefinition:generatedDetermineNamedScriptIdxToStartDefinition,
					scriptIdx,
					methodCodeMap,
					allMethods,
					"-1",
					"bool returnValueBool; returnValue.getBooleanValue(returnValueBool); if (returnValueBool == true) return " + to_string(scriptIdx) + ";",
					script.scriptType == MiniScript::Script::SCRIPTTYPE_ONENABLED?1:0
				);
			}

			//
			scriptIdx++;
		}
	}

	//
	generatedDetermineScriptIdxToStartDefinition+= "\n";
	generatedDetermineScriptIdxToStartDefinition+= methodCodeIndent + "//" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= methodCodeIndent + "return " + to_string(nothingScriptIdx) + ";" + "\n";
	generatedDetermineScriptIdxToStartDefinition+= string() + "}" + "\n";
	//
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "}" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "//" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= methodCodeIndent + "return SCRIPTIDX_NONE;" + "\n";
	generatedDetermineNamedScriptIdxToStartDefinition+= string() + "}" + "\n";

	//
	{
		string emitDefinitionIndent = "\t";
		emitDefinition+= emitDefinitionIndent + "{" + "\n";
		emitDefinition+= emitDefinitionIndent + "\t" + "Console::println(\"" + miniScriptClassName + "::emit(): no condition with name: '\" + condition + \"'\");" + "\n";
		emitDefinition+= emitDefinitionIndent + "}" + "\n";
		emitDefinition+= string() + "}" + "\n";
	}

	// transpile array access operator
	string arrayAccessMethodsDeclarations;
	string arrayAccessMethodsDefinitions;
	//
	string arrayMapSetInitializerDeclarations;
	string arrayMapSetInitializerDefinitions;

	{
		auto scriptIdx = 0;
		for (const auto& script: scripts) {
			// method name
			string methodName =
				(script.scriptType == MiniScript::Script::SCRIPTTYPE_FUNCTION?
					"":
					(script.scriptType == MiniScript::Script::SCRIPTTYPE_ON?"on_":"on_enabled_")
				) +
				(script.name.empty() == false?script.name:(
					StringTools::regexMatch(script.condition, "[a-zA-Z0-9_]+") == true?
						script.condition:
						to_string(scriptIdx)
					)
				);
			Transpiler::generateArrayMapSetInitializer(
				miniScript.get(),
				arrayMapSetInitializerDeclarations,
				arrayMapSetInitializerDefinitions,
				miniScriptClassName,
				methodName,
				script.conditionSyntaxTree,
				script.conditionStatement,
				methodCodeMap,
				allMethods,
				true
			);
			Transpiler::generateArrayAccessMethods(
				miniScript.get(),
				arrayAccessMethodsDeclarations,
				arrayAccessMethodsDefinitions,
				miniScriptClassName,
				methodName,
				script.conditionSyntaxTree,
				script.conditionStatement,
				methodCodeMap,
				allMethods,
				true
			);
			for (auto statementIdx = 0; statementIdx < script.statements.size(); statementIdx++) {
				Transpiler::generateArrayMapSetInitializer(
					miniScript.get(),
					arrayMapSetInitializerDeclarations,
					arrayMapSetInitializerDefinitions,
					miniScriptClassName,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false
				);
				Transpiler::generateArrayAccessMethods(
					miniScript.get(),
					arrayAccessMethodsDeclarations,
					arrayAccessMethodsDefinitions,
					miniScriptClassName,
					methodName,
					script.syntaxTree[statementIdx],
					script.statements[statementIdx],
					methodCodeMap,
					allMethods,
					false
				);
			}
			scriptIdx++;
		}
	}

	// inject array access method declarations into declarations
	generatedDeclarations+= arrayAccessMethodsDeclarations;
	// inject array/map/set initializer declarations into declarations
	generatedDeclarations+= arrayMapSetInitializerDeclarations;

	// sum up definitions
	generatedDefinitions =
		string("\n#define __MINISCRIPT_TRANSPILATION__\n\n") +
		initializeNativeDefinition +
		registerMethodsDefinitions +
		generatedDetermineScriptIdxToStartDefinition +
		generatedDetermineNamedScriptIdxToStartDefinition + "\n" +
		emitDefinition +
		generatedDefinitions +
		arrayAccessMethodsDefinitions +
		arrayMapSetInitializerDefinitions;

	// inject C++ definition code
	{
		//
		auto injectedGeneratedCode = true;
		//
		vector<string> miniScriptCPP;
		vector<string> generatedMiniScriptCPP;
		auto miniscriptTranspilationCPPFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".cpp";
		if (FileSystem::exists(miniscriptTranspilationCPPFileName) == false) {
			auto miniScriptCPPString = FileSystem::getContentAsString("./resources/templates/transpilation", "Transpilation.cpp");
			miniScriptCPPString = StringTools::replace(miniScriptCPPString, "{$script}", scriptFileName);
			miniScriptCPPString = StringTools::replace(miniScriptCPPString, "{$class-name}", miniScriptClassName);
			miniScriptCPPString = StringTools::replace(miniScriptCPPString, "{$base-class}", miniScript->getBaseClass());
			miniScriptCPP = StringTools::tokenize(miniScriptCPPString, "\n", true);
		} else {
			FileSystem::getContentAsStringArray(FileSystem::getPathName(miniscriptTranspilationCPPFileName), FileSystem::getFileName(miniscriptTranspilationCPPFileName), miniScriptCPP);
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string includes;
			for (const auto& include: transpilationUnitIncludes) includes+= include + "\n";
			//
			injectedGeneratedCode = replace(
				miniScriptCPP,
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_INCLUDES_START__*/",
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_INCLUDES_END__*/",
				includes,
				generatedMiniScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_INCLUDES_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_INCLUDES_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				miniScriptCPP = generatedMiniScriptCPP;
				generatedMiniScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			//
			string usings;
			for (const auto& _using: transpilationUnitUsings) usings+= _using + "\n";
			//
			injectedGeneratedCode = replace(
				miniScriptCPP,
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_USINGS_START__*/",
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_USINGS_END__*/",
				usings,
				generatedMiniScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_USINGS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_USINGS_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				miniScriptCPP = generatedMiniScriptCPP;
				generatedMiniScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			injectedGeneratedCode = replace(
				miniScriptCPP,
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/",
				"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/",
				generatedDefinitions,
				generatedMiniScriptCPP
			);
			if (injectedGeneratedCode == false) {
				Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/ tags in file " + transpilationFileName + "?");
			} else {
				miniScriptCPP.clear();
			}
		}
		//
		if (injectedGeneratedCode == true) {
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(miniscriptTranspilationCPPFileName),
				FileSystem::getFileName(miniscriptTranspilationCPPFileName),
				generatedMiniScriptCPP
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in file " + miniscriptTranspilationCPPFileName + ". Dont forget to rebuild your sources.");
		}
	}

	//
	// inject C++ declaration code / header
	{
		vector<string> miniScriptClassHeader;
		vector<string> generatedMiniScriptClassHeader;
		auto miniscriptTranspilationHeaderFileName = FileSystem::getPathName(transpilationFileName) + "/" + FileSystem::getFileName(transpilationFileName) + ".h";
		if (FileSystem::exists(miniscriptTranspilationHeaderFileName) == false) {
			auto miniScriptHeaderString = FileSystem::getContentAsString("./resources/templates/transpilation", "Transpilation.h");
			miniScriptHeaderString = StringTools::replace(miniScriptHeaderString, "{$script}", scriptFileName);
			miniScriptHeaderString = StringTools::replace(miniScriptHeaderString, "{$class-name}", miniScriptClassName);
			miniScriptHeaderString = StringTools::replace(miniScriptHeaderString, "{$base-class}", miniScript->getBaseClass());
			miniScriptClassHeader = StringTools::tokenize(miniScriptHeaderString, "\n", true);
		} else {
			FileSystem::getContentAsStringArray(FileSystem::getPathName(miniscriptTranspilationHeaderFileName), FileSystem::getFileName(miniscriptTranspilationHeaderFileName), miniScriptClassHeader);
		}
		//
		auto injectedGeneratedCode = replace(
			miniScriptClassHeader,
			"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/",
			"/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/",
			generatedDeclarations,
			generatedMiniScriptClassHeader
		);
		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/ tags in file " + transpilationFileName + "?");
		} else {
			//
			FileSystem::setContentFromStringArray(
				FileSystem::getPathName(miniscriptTranspilationHeaderFileName),
				FileSystem::getFileName(miniscriptTranspilationHeaderFileName),
				generatedMiniScriptClassHeader
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in header file " + miniscriptTranspilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

};
};
};

int main(int argc, char** argv)
{
	Console::println(string("miniscripttranspiler ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	if (argc < 3) {
		Console::println("Usage: miniscripttranspiler script_filename transpilation_filename [miniscript_extension_file1] [miniscript_extension_fileN]");
		exit(EXIT_FAILURE);
	}

	vector<string> miniScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) miniScriptExtensionFileNames.push_back(argv[i]);

	//
	// MiniScript::registerDataTypes();

	//
	miniscript::tools::TranspilerTool::processFile(argv[1], argv[2], miniScriptExtensionFileNames);

	//
	exit(EXIT_SUCCESS);
}
