#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::set;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	auto miniScript = new MiniScript();
	miniScript->registerMethods();

	// methods
	Console::println();
	Console::println("| Methods                                                                                          |");
	Console::println("|--------------------------------------------------------------------------------------------------|");
	auto scriptMethods = miniScript->getMethods();
	vector<string> methods;
	for (auto scriptMethod: scriptMethods) {
		string method;
		method+= "| ";
		method+= scriptMethod->getMethodName();
		method+= "(";
		auto argumentIdx = 0;
		if (scriptMethod->isVariadic() == true) {
			method+="...";
		} else {
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				if (argumentIdx > 0) method+= ", ";
				method+= argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
				if (argumentType.optional == true) {
					method+= "(OPTIONAL)";
				}
				argumentIdx++;
			}
		}
		method+= "): ";
		method+= scriptMethod->isMixedReturnValue() == true?"Mixed":MiniScript::ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType());
		while (method.size() < 99) method+= " ";
		method+= "|";
		methods.push_back(method);
	}
	sort(methods.begin(), methods.end());
	for (auto& method: methods) Console::println(method);

	// operators
	auto scriptOperatorMethods = miniScript->getOperatorMethods();
	vector<string> operators;
	for (auto method: scriptOperatorMethods) {
		string operatorString;
		operatorString = "| ";
		operatorString+= MiniScript::getOperatorAsString(method->getOperator());
		while (operatorString.size() < 5) operatorString+= " ";
		operatorString+= "| ";
		operatorString+= method->getMethodName();
		operatorString+= "(";
		auto argumentIdx = 0;
		if (method->isVariadic() == true) {
			operatorString+="...";
		} else {
			for (auto& argumentType: method->getArgumentTypes()) {
				if (argumentIdx > 0) operatorString+= ", ";
				operatorString+= argumentType.name + ": " + MiniScript::ScriptVariable::getTypeAsString(argumentType.type);
				if (argumentType.optional == true) {
					operatorString+= "(OPTIONAL)";
				}
				argumentIdx++;
			}
		}
		operatorString+= "): ";
		operatorString+= method->isMixedReturnValue() == true?"Mixed":MiniScript::ScriptVariable::getTypeAsString(method->getReturnValueType());
		while (operatorString.size() < 99) operatorString+= " ";
		operatorString+= "|";
		operators.push_back(operatorString);
	}
	sort(operators.begin(), operators.end());
	Console::println();
	Console::println("| Operators                                                                                        |");
	Console::println("|--------------------------------------------------------------------------------------------------|");
	for (auto& method: operators) Console::println(method);
}
