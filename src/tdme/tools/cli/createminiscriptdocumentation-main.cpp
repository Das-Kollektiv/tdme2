#include <memory>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/Properties.h>
#include <tdme/utilities/StringTools.h>

using std::make_pair;
using std::make_unique;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::application::Application;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

namespace tdme {
namespace tools {
namespace cli {
class MiniscriptDocumentation {
public:
static void generateMiniScriptMethodsDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, unordered_set<string>& categories, const set<string>& allClassMethods, MiniScript* omitMiniScript = nullptr) {
	auto scriptMethods = miniScript->getMethods();
	map<string, vector<pair<string, string>>> methodMarkupByCategory;
	for (auto scriptMethod: scriptMethods) {
		if (omitMiniScript != nullptr && omitMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
		if (allClassMethods.find(scriptMethod->getMethodName()) != allClassMethods.end()) continue;
		string result;
		string category;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) category = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		string description;
		description+= "| ";
		description+= descriptions.get(descriptionPrefix + scriptMethod->getMethodName(), "Not documented");
		if (scriptMethod->getContextFunctions().empty() == false) {
			string contextFunctions;
			for (const auto& contextFunction: scriptMethod->getContextFunctions()) {
				if (contextFunctions.empty() == false) contextFunctions+= ", ";
				contextFunctions+= contextFunction + "()";
			}
			description+= " - <i>available in " + contextFunctions + "</i>";
		}
		while (description.size() < 99) description+= " ";
		description+= "|";
		result+= description + "\n";
		string method;
		method+= "| <sub>";
		method+= scriptMethod->getMethodName();
		method+= "(";
		method+= scriptMethod->getArgumentsInformation();
		method+= "): ";
		method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
		method+= "</sub>";
		while (method.size() < 99) method+= " ";
		method+= "|";
		method+= "\n";
		result+= method;
		methodMarkupByCategory[category].push_back(make_pair(scriptMethod->getMethodName(), result));
	}
	// collect categories
	for (const auto& [category, methodMarkup]: methodMarkupByCategory) {
		categories.insert(category);
	}
	//
	map<string, vector<string>> methodMarkupByCategory2;
	for (const auto& [category, methods]: methodMarkupByCategory) {
		if (category.empty() == true) continue;
		for (const auto& [methodName, methodMarkup]: methods) {
			methodMarkupByCategory2[category].push_back(methodMarkup);
		}
	}
	{
		auto emptyCategoryMethodsIt = methodMarkupByCategory.find(string());
		if (emptyCategoryMethodsIt != methodMarkupByCategory.end()) {
			const auto& methods = emptyCategoryMethodsIt->second;
			for (const auto& [methodName, methodMarkup]: methods) {
				if (categories.contains(methodName) == true) {
					methodMarkupByCategory2[methodName].insert(methodMarkupByCategory2[methodName].begin(), methodMarkup);
				} else {
					methodMarkupByCategory2[string()].push_back(methodMarkup);
				}
			}
		}
	}
	Console::println();
	Console::println("# " + to_string(mainHeadingIdx) + ". " + heading);
	auto categoryIdx = 1;
	for (const auto& [category, methodsMarkup]: methodMarkupByCategory2) {
		auto categoryName = descriptions.get(descriptionPrefix + "group." + (category.empty() == true?"uncategorized":category), "Not documented");
		Console::println();
		Console::println("## " + to_string(mainHeadingIdx) + "." + to_string(categoryIdx++) + " " + categoryName);
		Console::println();
		Console::println("| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |");
		Console::println("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
		for (const auto& methodMarkup: methodsMarkup) Console::print(methodMarkup);
	}
}

static void generateMiniScriptClassesDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, set<string>& allClassMethods) {
	auto scriptMethods = miniScript->getMethods();
	//
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); typeIdx <= static_cast<int>(MiniScript::TYPE_SET); typeIdx++) {
		const auto& className = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
		allClassMethods.insert(className);
	}
	//
	for (auto scriptMethod: scriptMethods) {
		string className;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		if (className.empty() == true && allClassMethods.find(scriptMethod->getMethodName()) == allClassMethods.end()) continue;
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.empty() == true?0:className.size() + 1,
				scriptMethod->getMethodName().size());
		// no arguments or no "this" argument
		auto _static =
			scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != className;
			MiniScript::ScriptVariable::getClassName(scriptMethod->getArgumentTypes()[0].type) != className;
		//
		allClassMethods.insert(scriptMethod->getMethodName());
	}
	//
	map<string, array<map<string, string>, 2>> methodMarkupByClassName;
	for (auto scriptMethod: scriptMethods) {
		//
		if (allClassMethods.find(scriptMethod->getMethodName()) == allClassMethods.end()) continue;
		//
		string result;
		string className;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		// constructors
		auto _static = false;
		if (className.empty() == true) {
			for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); typeIdx <= static_cast<int>(MiniScript::TYPE_SET); typeIdx++) {
				const auto& possibleClassName = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
				if (scriptMethod->getMethodName() == possibleClassName) {
					className = possibleClassName;
					_static = true;
					break;
				}
			}
		}
		//
		if (_static == false) {
			_static =
				scriptMethod->getArgumentTypes().empty() == true ||
				scriptMethod->getArgumentTypes()[0].name != className;
				MiniScript::ScriptVariable::getClassName(scriptMethod->getArgumentTypes()[0].type) != className;
		}
		//
		string description;
		description+= "| ";
		description+= descriptions.get(descriptionPrefix + scriptMethod->getMethodName(), "Not documented");
		while (description.size() < 99) description+= " ";
		description+= "|";
		result+= description + "\n";
		string method;
		method+= "| <sub>";
		if (_static == true) {
			method+= "<b>static</b> ";
		}
		method+= _static == true?scriptMethod->getMethodName():StringTools::substring(scriptMethod->getMethodName(), className.size() + 1, scriptMethod->getMethodName().size());
		method+= "(";
		method+= scriptMethod->getArgumentsInformation(_static == true?0:1);
		method+= "): ";
		method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
		method+= "</sub>";
		while (method.size() < 99) method+= " ";
		method+= "|";
		method+= "\n";
		result+= method;
		methodMarkupByClassName[className][_static == true?0:1][scriptMethod->getMethodName()] = result;
	}
	//
	auto classIdx = 1;
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); typeIdx <= static_cast<int>(MiniScript::TYPE_SET); typeIdx++) {
		const auto& className = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
		auto classNameDescription = descriptions.get("miniscript.baseclass." + (className.empty() == true?"No class":className), "Not documented");
		//
		Console::println();
		Console::println("## " + to_string(mainHeadingIdx) + "." + to_string(classIdx++) + " " + classNameDescription);
		Console::println();
		//
		for (auto staticIdx = 0; staticIdx < 2; staticIdx++) {
			//
			if (staticIdx == 0) {
				Console::println("| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |");
				Console::println("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
				Console::println("| &nbsp;                                    |");
				Console::println("| <sub>Static methods</sub                  |");
			} else {
				Console::println("| &nbsp;                                    |");
				Console::println("| <sub>Non static methods</sub              |");
			}
			//
			for (const auto& [method, methodMarkup]: methodMarkupByClassName[className][staticIdx]) {
				Console::print(methodMarkup);
			}
		}
	}
}

};
};
};
};

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	auto baseMiniScript = make_unique<MiniScript>();
	baseMiniScript->registerMethods();

	//
	auto logicMiniScript = make_unique<LogicMiniScript>();
	logicMiniScript->registerMethods();

	//
	auto guiMiniScript = make_unique<GUIMiniScript>(nullptr);
	guiMiniScript->registerMethods();

	//
	unordered_set<string> baseClassesCategories;
	unordered_set<string> baseMethodCategories;
	unordered_set<string> logicMethodCategories;
	unordered_set<string> guiMethodCategories;

	set<string> allClassMethods;
	// classes
	tdme::tools::cli::MiniscriptDocumentation::generateMiniScriptClassesDocumentation("MiniScript Classes", 6, baseMiniScript.get(), descriptions, "miniscript.basemethod.", allClassMethods);
	// base methods
	tdme::tools::cli::MiniscriptDocumentation::generateMiniScriptMethodsDocumentation("MiniScript Base Methods", 7, baseMiniScript.get(), descriptions, "miniscript.basemethod.", baseMethodCategories, allClassMethods);
	// logic methods
	tdme::tools::cli::MiniscriptDocumentation::generateMiniScriptMethodsDocumentation("MiniScript Logic Methods", 8, logicMiniScript.get(), descriptions, "miniscript.logicmethod.", logicMethodCategories, allClassMethods, baseMiniScript.get());
	// gui methods
	tdme::tools::cli::MiniscriptDocumentation::generateMiniScriptMethodsDocumentation("MiniScript GUI Methods", 9, guiMiniScript.get(), descriptions, "miniscript.", guiMethodCategories, allClassMethods, baseMiniScript.get());

	// operators
	auto scriptOperatorMethods = baseMiniScript->getOperatorMethods();
	vector<string> operators;
	for (auto scriptMethod: scriptOperatorMethods) {
		string operatorString;
		operatorString = "| ";
		operatorString+= StringTools::replace(MiniScript::getOperatorAsString(scriptMethod->getOperator()), "|", "\\|");
		while (operatorString.size() < 5) operatorString+= " ";
		operatorString+= "| ";
		operatorString+= scriptMethod->getMethodName();
		operatorString+= "(";
		operatorString+= scriptMethod->getArgumentsInformation();
		operatorString+= "): ";
		operatorString+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
		while (operatorString.size() < 99) operatorString+= " ";
		operatorString+= "|";
		operators.push_back(operatorString);
	}
	sort(operators.begin(), operators.end());
	Console::println();
	Console::println("# 10. Operators");
	Console::println();
	Console::println("| Op | Method                                                                                      |");
	Console::println("|----|---------------------------------------------------------------------------------------------|");
	for (const auto& method: operators) Console::println(method);

	//
	Console::println();
	Console::println("# properties methodname=human readable string");
	//
	{
		Console::println("# base methods");
		//
		for (const auto& baseMethodCategory: baseMethodCategories) {
			Console::println("miniscript.basemethod.group." + (baseMethodCategory.empty() == true?"uncategorized":baseMethodCategory) + "=");
		}
		//
		auto scriptMethods = baseMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::println("miniscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::println("# miniscript logic methods");
		//
		for (const auto& logicMethodCategory: logicMethodCategories) {
			Console::println("miniscript.logicmethod.group." + (logicMethodCategory.empty() == true?"uncategorized":logicMethodCategory) + "=");
		}
		//
		auto scriptMethods = logicMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::println("miniscript.logicmethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::println("# miniscript gui methods");
		//
		for (const auto& guiMethodCategory: guiMethodCategories) {
			Console::println("miniscript.group." + (guiMethodCategory.empty() == true?"uncategorized":guiMethodCategory) + "=");
		}
		//
		auto scriptMethods = guiMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::println("miniscript." + scriptMethod->getMethodName() + "=");
		}
	}

	//
	Console::println();
	Console::println("Keywords: ");
	set<string> allMethods;
	{
		//
		auto scriptMethods = baseMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			allMethods.insert(scriptMethod->getMethodName());
		}
	}
	{
		//
		auto scriptMethods = logicMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			allMethods.insert(scriptMethod->getMethodName());
		}
	}
	{
		//
		auto scriptMethods = guiMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			allMethods.insert(scriptMethod->getMethodName());
		}
	}
	//
	for (const auto& method: allMethods) {
		Console::print(method + " ");
	}
	Console::println();

	//
	Console::shutdown();
	return 0;
}
