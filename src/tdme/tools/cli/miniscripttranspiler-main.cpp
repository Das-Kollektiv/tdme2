#include <algorithm>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
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
#include <tdme/utilities/MiniScriptTranspiler.h>
#include <tdme/utilities/StringTools.h>

using std::find;
using std::map;
using std::set;
using std::string;
using std::string_view;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
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
using tdme::utilities::MiniScriptTranspiler;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {
class MiniScriptTranspilerTool {
public:

static void processFile(const string& scriptFileName, const string& miniscriptTranspilationFileName, const vector<string>& miniScriptExtensionFileNames) {
	Console::println("Processing script: " + scriptFileName);


	//
	auto miniScript = unique_ptr<MiniScript>(MiniScript::loadScript(Tools::getPathName(scriptFileName), Tools::getFileName(scriptFileName)));
	if (miniScript == nullptr) {
		Console::println("No script instance: " + scriptFileName);
		return;
	}

	//
	unordered_map<string, vector<string>> methodCodeMap;
	auto allMethods = MiniScriptTranspiler::getAllMethodNames(miniScript.get());

	//
	vector<string> transpilationUnits;
	for (const auto& transpilationUnit: miniScript->getTranspilationUnits()) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: miniScriptExtensionFileNames) transpilationUnits.push_back(transpilationUnit);
	for (const auto& transpilationUnit: transpilationUnits) {
		vector<string> transpilationUnitCode;
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(transpilationUnit), Tools::getFileName(transpilationUnit), transpilationUnitCode);
		for (auto i = 0; i < transpilationUnitCode.size(); i++) {
			const auto& line = transpilationUnitCode[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "registerMethod") == true ||
				StringTools::startsWith(trimmedLine, "miniScript->registerMethod") == true) {
				auto bracketCount = 0;
				string className;
				if (StringTools::firstIndexOf(StringTools::substring(trimmedLine, 14), "new") == string::npos) {
					Console::println("src/tdme/utilities/MiniScript.cpp: registerMethod @ " + to_string(i) + ": '" + trimmedLine + "': unable to determine class name");
				} else {
					auto classNameStartIdx = trimmedLine.find("registerMethod") + 14 + 5;
					for (auto j = classNameStartIdx; j < trimmedLine.size(); j++) {
						auto c = trimmedLine[j];
						if (c == '(') break;
						if (c == ' ') continue;
						className+= c;
					}
					MiniScriptTranspiler::gatherMethodCode(transpilationUnitCode, className, i, methodCodeMap);
				}
			}
		}
	}

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
	MiniScriptTranspiler::generateMiniScriptEvaluateMemberAccessArrays(miniScript.get(), memberAccessEvaluationDeclarations, memberAccessEvaluationDefinitions);

	//
	string miniScriptClassName = Tools::removeFileExtension(Tools::getFileName(miniscriptTranspilationFileName));
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
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "ScriptStatement(" + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.line) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.statementIdx) + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.conditionStatement.statement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(script.conditionStatement.executableStatement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + to_string(script.conditionStatement.gotoStatementIdx) + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + ")," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + script.name + "\"," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.emitCondition == true?"true":"false") + "," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{" + "\n";
			auto statementIdx = MiniScript::STATEMENTIDX_FIRST;
			for (const auto& statement: script.statements) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "ScriptStatement(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.line) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.statementIdx) + "," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(statement.statement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + StringTools::replace(StringTools::replace(statement.executableStatement, "\\", "\\\\"), "\"", "\\\"") + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + to_string(statement.gotoStatementIdx) + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + ")" + (statementIdx < script.statements.size() - 1?",":"") + "\n";
				statementIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}," + "\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{},\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + (script.callable == true?"true":"false") + ",\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "{\n";
			auto argumentIdx = 0;
			for (const auto& argument: script.arguments) {
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "Script::ScriptArgument(" + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + "\"" + argument.name + "\"," + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" + "\t" + (argument.assignBack == true?"true":"false") + "\n";
				initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\t" ")" + (argumentIdx != script.arguments.size() - 1?",":"") + "\n";
				argumentIdx++;
			}
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "}\n";
			initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + ")" + (scriptIdx < scripts.size() - 1?",":"") + "\n";
			scriptIdx++;
		}
	}
	initializeNativeDefinition+= methodCodeIndent + "\t" + "}" + "\n";
	initializeNativeDefinition+= methodCodeIndent + ");" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "setNativeScriptFunctions(" + "\n";
	initializeNativeDefinition+= methodCodeIndent + "\t" + "{" + "\n";
	auto scriptFunctionIdx = 0;
	for (const auto& [functionName, functionIdx]: miniScript->scriptFunctions) {
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "{" + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + "\"" + functionName + "\"," + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "\t" + to_string(functionIdx) + "\n";
		initializeNativeDefinition+= methodCodeIndent + "\t" + "\t" + "}" + (scriptFunctionIdx != miniScript->scriptFunctions.size() - 1?",":"") + "\n";
		scriptFunctionIdx++;
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
			MiniScriptTranspiler::transpile(miniScript.get(), generatedSubCode, scriptIdx, methodCodeMap, allMethods);
			generatedDefinitions+= generatedSubCode;
			generatedDefinitions+= string() + "}" + "\n\n";

			//
			if (script.emitCondition == false) {
				if (script.scriptType == MiniScript::Script::SCRIPTTYPE_ONENABLED) {
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "// next statements belong to tested enabled named condition with name \"" + script.name + "\"" + "\n";
					generatedDetermineNamedScriptIdxToStartDefinition+= string() + "\t" + "\t" + "if (enabledNamedCondition == \"" + script.name + "\")" + "\n";
				}
				MiniScriptTranspiler::transpileScriptCondition(
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
			MiniScriptTranspiler::generateArrayMapSetInitializer(
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
			MiniScriptTranspiler::generateArrayAccessMethods(
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
				MiniScriptTranspiler::generateArrayMapSetInitializer(
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
				MiniScriptTranspiler::generateArrayAccessMethods(
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
		vector<string> miniScriptClass;
		vector<string> miniScriptClassNew;
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationFileName), Tools::getFileName(miniscriptTranspilationFileName), miniScriptClass);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClass.size(); i++) {
			const auto& line = miniScriptClass[i];
			auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/") {
				reject = true;
				miniScriptClassNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassNew.push_back(generatedDefinitions);
				miniScriptClassNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DEFINITIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationFileName),
				Tools::getFileName(miniscriptTranspilationFileName),
				miniScriptClassNew
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in file " + miniscriptTranspilationFileName + ". Dont forget to rebuild your sources.");
		}
	}

	//
	// inject C++ declaration code / header
	{
		vector<string> miniScriptClassHeader;
		vector<string> miniScriptClassHeaderNew;
		auto miniscriptTranspilationHeaderFileName = Tools::getPathName(miniscriptTranspilationFileName) + "/" + Tools::removeFileExtension(Tools::getFileName(miniscriptTranspilationFileName)) + ".h";
		FileSystem::getInstance()->getContentAsStringArray(Tools::getPathName(miniscriptTranspilationHeaderFileName), Tools::getFileName(miniscriptTranspilationHeaderFileName), miniScriptClassHeader);
		auto reject = false;
		auto injectedGeneratedCode = false;
		for (auto i = 0; i < miniScriptClassHeader.size(); i++) {
			const auto& line = miniScriptClassHeader[i];
			const auto trimmedLine = StringTools::trim(line);
			if (StringTools::startsWith(trimmedLine, "//") == true) {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
				continue;
			}
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/") {
				reject = true;
				miniScriptClassHeaderNew.push_back(line);
			} else
			if (trimmedLine == "/*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/") {
				reject = false;
				injectedGeneratedCode = true;
				miniScriptClassHeaderNew.push_back(generatedDeclarations);
				miniScriptClassHeaderNew.push_back(line);
			} else {
				if (reject == false) miniScriptClassHeaderNew.push_back(line);
			}
		}

		//
		if (injectedGeneratedCode == false) {
			Console::println(scriptFileName + ": Could not inject generated C++ code, are you missing the /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_START__*/ and /*__MINISCRIPT_TRANSPILEDMINISCRIPTCODE_DECLARATIONS_END__*/ markers in file " + miniscriptTranspilationFileName + "?");
		} else {
			//
			FileSystem::getInstance()->setContentFromStringArray(
				Tools::getPathName(miniscriptTranspilationHeaderFileName),
				Tools::getFileName(miniscriptTranspilationHeaderFileName),
				miniScriptClassHeaderNew
			);
			//
			Console::println(scriptFileName + ": Injected generated C++ code in header file " + miniscriptTranspilationHeaderFileName + ". Dont forget to rebuild your sources.");
		}
	}
}

};
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
		Console::println("Usage: miniscripttranspiler path_to_script_file path_to_cpp_miniscript_transpilation_file [path_to_cpp_miniscript_extension_file1] [path_to_cpp_miniscript_extension_fileN]");
		Application::exit(Application::EXITCODE_FAILURE);
	}

	vector<string> miniScriptExtensionFileNames;
	for (auto i = 3; i < argc; i++) miniScriptExtensionFileNames.push_back(argv[i]);

	//
	tdme::tools::cli::MiniScriptTranspilerTool::processFile(argv[1], argv[2], miniScriptExtensionFileNames);

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
