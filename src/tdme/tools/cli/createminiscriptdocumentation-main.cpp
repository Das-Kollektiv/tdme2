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

static void generateMiniScriptDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, unordered_set<string>& categories, MiniScript* omitMiniScript = nullptr) {
	auto scriptMethods = miniScript->getMethods();
	map<string, vector<pair<string, string>>> methodByCategory;
	for (auto scriptMethod: scriptMethods) {
		if (omitMiniScript != nullptr && omitMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
		string result;
		string category;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) category = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		string description;
		description+= "| ";
		description+= descriptions.get(descriptionPrefix + scriptMethod->getMethodName(), "Not documented");
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
		methodByCategory[category].push_back(make_pair(scriptMethod->getMethodName(), result));
	}
	// collect categories
	for (auto& methodByCategoryIt: methodByCategory) {
		auto& category = methodByCategoryIt.first;
		categories.insert(category);
	}
	//
	map<string, vector<string>> methodByCategory2;
	for (auto& methodByCategoryIt: methodByCategory) {
		auto& category = methodByCategoryIt.first;
		if (category.empty() == true) continue;
		auto& methods = methodByCategoryIt.second;
		for (auto& method: methods) {
			auto& methodName = method.first;
			auto& methodMarkup = method.second;
			methodByCategory2[category].push_back(methodMarkup);
		}
	}
	{
		auto emptyCategoryMethodsIt = methodByCategory.find(string());
		if (emptyCategoryMethodsIt != methodByCategory.end()) {
			auto& methods = emptyCategoryMethodsIt->second;
			for (auto& method: methods) {
				auto& methodName = method.first;
				if (categories.contains(methodName) == true) {
					auto& methodMarkup = method.second;
					methodByCategory2[methodName].insert(methodByCategory2[methodName].begin(), methodMarkup);
				}
			}
		}
	}
	Console::println();
	Console::println("# " + to_string(mainHeadingIdx) + ". " + heading);
	auto categoryIdx = 1;
	for (auto& methodByCategoryIt: methodByCategory2) {
		auto& category = methodByCategoryIt.first;
		auto categoryName = descriptions.get(descriptionPrefix + "group." + (category.empty() == true?"uncategorized":category), "Not documented");
		Console::println();
		Console::println("## " + to_string(mainHeadingIdx) + "." + to_string(categoryIdx++) + " " + categoryName);
		Console::println();
		Console::println("| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of Methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |");
		Console::println("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
		auto& methodsMarkup = methodByCategoryIt.second;
		for (auto& methodMarkup: methodsMarkup) Console::print(methodMarkup);
	}
}

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	auto baseMiniScript = new MiniScript();
	baseMiniScript->registerMethods();

	//
	auto logicMiniScript = new LogicMiniScript();
	logicMiniScript->registerMethods();

	//
	auto guiMiniScript = new GUIMiniScript(nullptr);
	guiMiniScript->registerMethods();

	//
	unordered_set<string> baseMethodCategories;
	unordered_set<string> logicMethodCategories;
	unordered_set<string> guiMethodCategories;

	// base methods
	generateMiniScriptDocumentation("MiniScript Base Methods", 6, baseMiniScript, descriptions, "miniscript.basemethod.", baseMethodCategories);
	// logic methods
	generateMiniScriptDocumentation("MiniScript Logic Methods", 7, logicMiniScript, descriptions, "miniscript.logicmethod.", logicMethodCategories, baseMiniScript);
	// gui methods
	generateMiniScriptDocumentation("MiniScript GUI Methods", 8, guiMiniScript, descriptions, "miniscript.", guiMethodCategories, baseMiniScript);

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
	Console::println("# 9. Operators");
	Console::println();
	Console::println("| Op | Method                                                                                      |");
	Console::println("|----|---------------------------------------------------------------------------------------------|");
	for (auto& method: operators) Console::println(method);

	//
	Console::println();
	Console::println("# properties methodname=human readable string");
	//
	{
		Console::println("# base methods");
		//
		for (auto& baseMethodCategory: baseMethodCategories) {
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
		for (auto& logicMethodCategory: logicMethodCategories) {
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
		for (auto& guiMethodCategory: guiMethodCategories) {
			Console::println("miniscript.group." + (guiMethodCategory.empty() == true?"uncategorized":guiMethodCategory) + "=");
		}
		//
		auto scriptMethods = guiMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::println("miniscript." + scriptMethod->getMethodName() + "=");
		}
	}
}
