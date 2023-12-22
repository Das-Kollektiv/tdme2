#include <miniscript/miniscript/Documentation.h>

#include <algorithm>
#include <map>
#include <string>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Documentation.h>
#include <miniscript/miniscript/MiniScript.h>
#include <miniscript/utilities/StringTools.h>

using std::map;
using std::pair;
using std::string;
using std::set;
using std::sort;
using std::to_string;
using std::unordered_set;
using std::vector;

using miniscript::miniscript::Documentation;

using miniscript::miniscript::MiniScript;
using miniscript::utilities::StringTools;

const set<string> Documentation::getAllClassMethods(MiniScript* miniScript) {
	set<string> allClassMethods;
	//
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
		const auto& className = MiniScript::Variable::getTypeAsString(static_cast<MiniScript::VariableType>(typeIdx));
		if (className.empty() == true) break;
		allClassMethods.insert(className);
	}
	//
	for (auto scriptMethod: miniScript->getMethods()) {
		string className;
		if (scriptMethod->getMethodName().rfind("::") != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind("::"));
		if (className.empty() == true && allClassMethods.find(scriptMethod->getMethodName()) == allClassMethods.end()) continue;
		//
		auto _class = false;
		for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
			const auto& classNameCandidate = MiniScript::Variable::getTypeAsString(static_cast<MiniScript::VariableType>(typeIdx));
			if (classNameCandidate.empty() == true) break;
			if (classNameCandidate == className) {
				_class = true;
				break;
			}
		}
		if (_class == false) continue;
		//
		auto method =
			StringTools::substring(
				scriptMethod->getMethodName(),
				className.empty() == true?0:className.size() + 2,
				scriptMethod->getMethodName().size());
		// no arguments or no "this" argument
		auto _static =
			scriptMethod->getArgumentTypes().empty() == true ||
			scriptMethod->getArgumentTypes()[0].name != StringTools::toLowerCase(className) ||
			MiniScript::Variable::getTypeAsString(scriptMethod->getArgumentTypes()[0].type) != className;
		//
		allClassMethods.insert(scriptMethod->getMethodName());
	}
	//
	return allClassMethods;
}

const set<string> Documentation::getMethodsCategories(MiniScript* miniScript, const set<string>& allClassMethods, MiniScript* excludeMiniScript) {
	set<string> categories;
	auto scriptMethods = miniScript->getMethods();
	for (auto scriptMethod: scriptMethods) {
		if (excludeMiniScript != nullptr && excludeMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
		if (allClassMethods.find(scriptMethod->getMethodName()) != allClassMethods.end()) continue;
		string result;
		string category;
		if (scriptMethod->getMethodName().rfind('.') != string::npos) category = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind('.'));
		categories.insert(category);
	}
	return categories;
}

const string Documentation::generateClassesDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, const set<string>& allClassMethods) {
	auto scriptMethods = miniScript->getMethods();
	//
	map<string, array<map<string, string>, 2>> methodMarkupByClassName;
	for (auto scriptMethod: scriptMethods) {
		//
		if (allClassMethods.find(scriptMethod->getMethodName()) == allClassMethods.end()) continue;
		//
		string result;
		string className;
		if (scriptMethod->getMethodName().rfind("::") != string::npos) className = StringTools::substring(scriptMethod->getMethodName(), 0, scriptMethod->getMethodName().rfind("::"));
		// constructors
		auto _static = false;
		if (className.empty() == true) {
			for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
				const auto& classNameCandidate = MiniScript::Variable::getTypeAsString(static_cast<MiniScript::VariableType>(typeIdx));
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
				scriptMethod->getArgumentTypes()[0].name != StringTools::toLowerCase(className) ||
				MiniScript::Variable::getTypeAsString(scriptMethod->getArgumentTypes()[0].type) != className;
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
		method+= _static == true?scriptMethod->getMethodName():StringTools::substring(scriptMethod->getMethodName(), className.size() + 2, scriptMethod->getMethodName().size());
		method+= "(";
		method+= scriptMethod->getArgumentsInformation(_static == true?0:1);
		method+= "): ";
		method+= MiniScript::Variable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
		method+= "</sub>";
		while (method.size() < 99) method+= " ";
		method+= "|";
		method+= "\n";
		result+= method;
		methodMarkupByClassName[className][_static == true?0:1][scriptMethod->getMethodName()] = result;
	}
	//
	string result;
	auto classIdx = 1;
	for (auto typeIdx = static_cast<int>(MiniScript::TYPE_STRING); ; typeIdx++) {
		const auto& className = MiniScript::Variable::getTypeAsString(static_cast<MiniScript::VariableType>(typeIdx));
		if (className.empty() == true) break;
		auto classNameDescription = descriptions.get("miniscript.baseclass." + (className.empty() == true?"No class":className), "Not documented");
		//
		result+= "\n";
		result+= "## " + to_string(mainHeadingIdx) + "." + to_string(classIdx++) + ". " + classNameDescription + "\n";
		result+= "\n";
		//
		for (auto staticIdx = 0; staticIdx < 2; staticIdx++) {
			//
			if (methodMarkupByClassName[className][staticIdx].empty() == true) continue;
			//
			if (staticIdx == 0) {
				result+= string() + "| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |" + "\n";
				result+= string() + "|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" + "\n";
				result+= string() + "| &nbsp;                                    |" + "\n";
				result+= string() + "| <b>STATIC METHODS</b>                     |" + "\n";
			} else {
				result+= string() + "| &nbsp;                                    |" + "\n";
				result+= string() + "| <b>NON STATIC METHODS</b>                 |" + "\n";
			}
			//
			for (const auto& [method, methodMarkup]: methodMarkupByClassName[className][staticIdx]) {
				result+= methodMarkup;
			}
		}
	}
	//
	return result;
}

const string Documentation::generateMethodsDocumentation(const string& heading, int mainHeadingIdx, MiniScript* miniScript, Properties& descriptions, const string& descriptionPrefix, const set<string>& allClassMethods, MiniScript* excludeMiniScript) {
	auto scriptMethods = miniScript->getMethods();
	map<string, vector<pair<string, string>>> methodMarkupByCategory;
	for (auto scriptMethod: scriptMethods) {
		if (excludeMiniScript != nullptr && excludeMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
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
		method+= MiniScript::Variable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
		method+= "</sub>";
		while (method.size() < 99) method+= " ";
		method+= "|";
		method+= "\n";
		result+= method;
		methodMarkupByCategory[category].push_back(make_pair(scriptMethod->getMethodName(), result));
	}
	// collect categories
	unordered_set<string> categories;
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
	//
	string result;
	result+= "# " + to_string(mainHeadingIdx) + ". " + heading;
	auto categoryIdx = 1;
	for (const auto& [category, methodsMarkup]: methodMarkupByCategory2) {
		auto categoryName = descriptions.get(descriptionPrefix + "group." + (category.empty() == true?"uncategorized":category), "Not documented");
		result+= "\n";
		result+= "## " + to_string(mainHeadingIdx) + "." + to_string(categoryIdx++) + ". " + categoryName + "\n";
		result+= "\n";
		result+= string() + "| &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Table of methods &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; |" + "\n";
		result+= string() + "|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|" + "\n";
		for (const auto& methodMarkup: methodsMarkup) result+= methodMarkup;
	}
	return result;
}

const string Documentation::generateOperatorsDocumentation(
	const string& heading,
	int mainHeadingIdx,
	MiniScript* miniScript
) {
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
		operatorString+= MiniScript::Variable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable());
		while (operatorString.size() < 99) operatorString+= " ";
		operatorString+= "|";
		operators.push_back(operatorString);
	}
	sort(operators.begin(), operators.end());
	//
	string result;
	result+= string() + "\n";
	result+= string() + "# 10. Operators" + "\n";
	result+= string() + "\n";
	result+= string() + "| Op | Method                                                                                      |" + "\n";
	result+= string() + "|----|---------------------------------------------------------------------------------------------|" + "\n";
	for (const auto& method: operators) result+= string() + method + "\n";
	return result;
}
