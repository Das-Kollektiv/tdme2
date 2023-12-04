#include <cstdlib>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Context.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/miniscript/Version.h>
#include <miniscript/utilities/Console.h>
#include <miniscript/utilities/Properties.h>
#include <miniscript/utilities/StringTools.h>

using std::exit;
using std::make_pair;
using std::make_unique;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using miniscript::miniscript::Context;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::Version;
using miniscript::utilities::Console;
using miniscript::utilities::Properties;
using miniscript::utilities::StringTools;

namespace miniscript {
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
		method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
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
		Console::println("## " + to_string(mainHeadingIdx) + "." + to_string(categoryIdx++) + ". " + categoryName);
		Console::println();
		Console::println("| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |");
		Console::println("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
		for (const auto& methodMarkup: methodsMarkup) Console::print(methodMarkup);
	}
}

static void generateMiniScriptClassesDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, set<string>& allClassMethods) {
	auto scriptMethods = miniScript->getMethods();
	//
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
		const auto& className = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
		if (className.empty() == true) break;
		allClassMethods.insert(className);
	}
	//
	for (auto scriptMethod: scriptMethods) {
		string className;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		if (className.empty() == true && allClassMethods.find(scriptMethod->getMethodName()) == allClassMethods.end()) continue;
		//
		auto _class = false;
		for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
			const auto& classNameCandidate = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
			if (classNameCandidate.empty() == true) break;
			if (classNameCandidate == className) {
				_class = true;
				break;
			}
		}
		if (_class == false) continue;
		//
		string method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.empty() == true?0:className.size() + 1,
				scriptMethod->getMethodName().size());
		// no arguments or no "this" argument
		auto _static =
			scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != className ||
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
			for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
				const auto& classNameCandidate = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
				if (classNameCandidate.empty() == true) break;
				if (scriptMethod->getMethodName() == classNameCandidate) {
					className = classNameCandidate;
					_static = true;
					break;
				}
			}
		}
		//
		if (_static == false) {
			_static =
				scriptMethod->getArgumentTypes().empty() == true ||
				scriptMethod->getArgumentTypes()[0].name != className ||
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
		method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
		method+= "</sub>";
		while (method.size() < 99) method+= " ";
		method+= "|";
		method+= "\n";
		result+= method;
		methodMarkupByClassName[className][_static == true?0:1][scriptMethod->getMethodName()] = result;
	}
	//
	auto classIdx = 1;
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
		const auto& className = MiniScript::ScriptVariable::getClassName(static_cast<MiniScript::ScriptVariableType>(typeIdx));
		if (className.empty() == true) break;
		auto classNameDescription = descriptions.get("miniscript.baseclass." + (className.empty() == true?"No class":className), "Not documented");
		//
		Console::println();
		Console::println("## " + to_string(mainHeadingIdx) + "." + to_string(classIdx++) + ". " + classNameDescription);
		Console::println();
		//
		for (auto staticIdx = 0; staticIdx < 2; staticIdx++) {
			//
			if (methodMarkupByClassName[className][staticIdx].empty() == true) continue;
			//
			if (staticIdx == 0) {
				Console::println("| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |");
				Console::println("|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|");
				Console::println("| &nbsp;                                    |");
				Console::println("| <b>STATIC METHODS</b>                     |");
			} else {
				Console::println("| &nbsp;                                    |");
				Console::println("| <b>NON STATIC METHODS</b>                 |");
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
	Console::println(string("miniscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	Properties descriptions;
	descriptions.load("resources/documentation", "method-descriptions.properties");

	//
	// MiniScript::registerDataTypes();

	//
	auto context = make_unique<Context>();
	auto miniScript = make_unique<MiniScript>();
	miniScript->setContext(context.get());
	miniScript->registerMethods();

	//
	unordered_set<string> baseMethodCategories;
	set<string> allClassMethods;

	// classes
	miniscript::tools::cli::MiniscriptDocumentation::generateMiniScriptClassesDocumentation("MiniScript Classes", 6, miniScript.get(), descriptions, "miniscript.basemethod.", allClassMethods);
	// base methods
	miniscript::tools::cli::MiniscriptDocumentation::generateMiniScriptMethodsDocumentation("MiniScript Methods", 7, miniScript.get(), descriptions, "miniscript.basemethod.", baseMethodCategories, allClassMethods);

	// operators
	auto scriptOperatorMethods = miniScript->getOperatorMethods();
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
		operatorString+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
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
		auto scriptMethods = miniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::println("miniscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	}

	//
	Console::println();
	Console::println("Keywords: ");
	set<string> allMethods;
	{
		//
		auto scriptMethods = miniScript->getMethods();
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
	exit(EXIT_SUCCESS);
}
