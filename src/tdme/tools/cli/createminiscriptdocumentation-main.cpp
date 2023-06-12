#include <set>
#include <string>
#include <unordered_map>
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

using std::set;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::application::Application;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::Properties;
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	Properties methodDescriptions;
	methodDescriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	auto baseMiniScript = new MiniScript();
	baseMiniScript->registerMethods();

	//
	auto logicMiniScript = new LogicMiniScript();
	logicMiniScript->registerMethods();

	//
	auto guiMiniScript = new GUIMiniScript(nullptr);
	guiMiniScript->registerMethods();

	// base methods
	{
		Console::println();
		Console::println("| Methods                                                                                          |");
		Console::println("|--------------------------------------------------------------------------------------------------|");
		auto scriptMethods = baseMiniScript->getMethods();
		vector<string> methods;
		for (auto scriptMethod: scriptMethods) {
			string description;
			description+= "| <sub>";
			description+= methodDescriptions.get("miniscript.basemethod." + scriptMethod->getMethodName(), "Not documented");
			description+= "</sub>";
			while (description.size() < 99) description+= " ";
			description+= "|";
			methods.push_back(description);
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			method+= scriptMethod->getArgumentsInformation();
			method+= "): ";
			method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
			while (method.size() < 99) method+= " ";
			method+= "|";
			methods.push_back(method);
		}
		for (auto& method: methods) Console::println(method);
	}

	// methods
	{
		Console::println();
		Console::println("| MiniScript logic methods                                                                         |");
		Console::println("|--------------------------------------------------------------------------------------------------|");
		auto scriptMethods = logicMiniScript->getMethods();
		vector<string> methods;
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			string description;
			description+= "| <sub>";
			description+= methodDescriptions.get("miniscript.logicmethod." + scriptMethod->getMethodName(), "Not documented");
			description+= "</sub>";
			while (description.size() < 99) description+= " ";
			description+= "|";
			methods.push_back(description);
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			method+= scriptMethod->getArgumentsInformation();
			method+= "): ";
			method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
			while (method.size() < 99) method+= " ";
			method+= "|";
			methods.push_back(method);
		}
		for (auto& method: methods) Console::println(method);
	}

	// methods
	{
		Console::println();
		Console::println("| MiniScript GUI methods                                                                           |");
		Console::println("|--------------------------------------------------------------------------------------------------|");
		auto scriptMethods = guiMiniScript->getMethods();
		vector<string> methods;
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			string description;
			description+= "| <sub>";
			description+= methodDescriptions.get("miniscript." + scriptMethod->getMethodName(), "Not documented");
			description+= "</sub>";
			while (description.size() < 99) description+= " ";
			description+= "|";
			methods.push_back(description);
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			method+= scriptMethod->getArgumentsInformation();
			method+= "): ";
			method+= MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType());
			while (method.size() < 99) method+= " ";
			method+= "|";
			methods.push_back(method);
		}
		for (auto& method: methods) Console::println(method);
	}

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
	Console::println("| Op | Method                                                                                      |");
	Console::println("|----|---------------------------------------------------------------------------------------------|");
	for (auto& method: operators) Console::println(method);
	//
	Console::println();
	Console::println("# properties methodname=human readable string");
	//
	{
		Console::println("# base methods");
		auto scriptMethods = baseMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::println("miniscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::println("# miniscript logic methods");
		auto scriptMethods = logicMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::println("miniscript.logicmethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::println("# miniscript gui methods");
		auto scriptMethods = guiMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::println("miniscript." + scriptMethod->getMethodName() + "=");
		}
	}
}
