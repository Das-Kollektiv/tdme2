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
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

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
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			auto optionalArgumentCount = 0;
			auto argumentIdx = 0;
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				if (argumentType.optional == true) {
					method+= "[";
					optionalArgumentCount++;
				}
				if (argumentIdx > 0) method+= ", ";
				if (argumentType.assignBack == true) method+= "=";
				method+= "$" + argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
				argumentIdx++;
			}
			if (scriptMethod->isVariadic() == true) {
				if (argumentIdx > 0) method+= ", ";
				method+="...";
			}
			for (auto i = 0; i < optionalArgumentCount; i++) method+= "]";
			method+= "): ";
			method+= MiniScript::ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType());
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
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			auto argumentIdx = 0;
			auto optionalArgumentCount = 0;
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				if (argumentType.optional == true) {
					method+= "[";
					optionalArgumentCount++;
				}
				if (argumentIdx > 0) method+= ", ";
				if (argumentType.assignBack == true) method+= "=";
				method+= "$" + argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
				argumentIdx++;
			}
			if (scriptMethod->isVariadic() == true) {
				if (argumentIdx > 0) method+= ", ";
				method+="...";
			}
			for (auto i = 0; i < optionalArgumentCount; i++) method+= "]";
			method+= "): ";
			method+= MiniScript::ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType());
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
			string method;
			method+= "| ";
			method+= scriptMethod->getMethodName();
			method+= "(";
			auto argumentIdx = 0;
			auto optionalArgumentCount = 0;
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				if (argumentType.optional == true) {
					method+= "[";
					optionalArgumentCount++;
				}
				if (argumentIdx > 0) method+= ", ";
				if (argumentType.assignBack == true) method+= "=";
				method+= "$" + argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
				argumentIdx++;
			}
			if (scriptMethod->isVariadic() == true) {
				if (argumentIdx > 0) method+= ", ";
				method+="...";
			}
			for (auto i = 0; i < optionalArgumentCount; i++) method+= "]";
			method+= "): ";
			method+= MiniScript::ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType());
			while (method.size() < 99) method+= " ";
			method+= "|";
			methods.push_back(method);
		}
		for (auto& method: methods) Console::println(method);
	}

	// operators
	auto scriptOperatorMethods = baseMiniScript->getOperatorMethods();
	vector<string> operators;
	for (auto method: scriptOperatorMethods) {
		string operatorString;
		operatorString = "| ";
		operatorString+= StringTools::replace(MiniScript::getOperatorAsString(method->getOperator()), "|", "\\|");
		while (operatorString.size() < 5) operatorString+= " ";
		operatorString+= "| ";
		operatorString+= method->getMethodName();
		operatorString+= "(";
		auto optionalArgumentCount = 0;
		auto argumentIdx = 0;
		for (auto& argumentType: method->getArgumentTypes()) {
			if (argumentType.optional == true) {
				operatorString+= "[";
				optionalArgumentCount++;
			}
			if (argumentIdx > 0) operatorString+= ", ";
			if (argumentType.assignBack == true) operatorString+= "=";
			operatorString+= "$" + argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
			argumentIdx++;
		}
		if (method->isVariadic() == true) {
			if (argumentIdx > 0) operatorString+= ", ";
			operatorString+="...";
		}
		for (auto i = 0; i < optionalArgumentCount; i++) operatorString+= "]";
		operatorString+= "): ";
		operatorString+= MiniScript::ScriptVariable::getTypeAsString(method->getReturnValueType());
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
			Console::println("miniscript.gui." + scriptMethod->getMethodName() + "=");
		}
	}
}
