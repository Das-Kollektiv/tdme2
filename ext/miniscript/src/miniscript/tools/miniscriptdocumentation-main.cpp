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
#include <miniscript/miniscript/Documentation.h>
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
using miniscript::miniscript::Documentation;
using miniscript::miniscript::MiniScript;
using miniscript::miniscript::Version;
using miniscript::utilities::Console;
using miniscript::utilities::Properties;
using miniscript::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("miniscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	Properties descriptions;
	descriptions.load("resources/miniscript/documentation", "method-descriptions.properties");

	//
	// MiniScript::registerDataTypes();

	//
	auto context = make_unique<Context>();
	auto miniScript = make_unique<MiniScript>();
	miniScript->setContext(context.get());
	miniScript->registerMethods();
	miniScript->registerVariables();

	//
	auto allClassMethods = Documentation::getAllClassMethods(miniScript.get());
	//
	auto baseMethodCategories = Documentation::getMethodsCategories(miniScript.get(), allClassMethods);
	// classes
	auto classesDocumentation = Documentation::generateClassesDocumentation("Classes", 6, miniScript.get(), descriptions, "miniscript.basemethod.", allClassMethods);
	// base methods
	auto methodsDocumentation = Documentation::generateMethodsDocumentation("Methods", 7, miniScript.get(), descriptions, "miniscript.basemethod.", allClassMethods);
	// variables
	auto variablesDocumentation = Documentation::generateVariablesDocumentation("Constants", 8, miniScript.get());
	// operators
	auto operatorsDocumentation = Documentation::generateOperatorsDocumentation("Operators", 9, miniScript.get());

	//
	Console::println("Classes");
	Console::println("---------");
	Console::println(classesDocumentation);

	//
	Console::println("Methods");
	Console::println("---------");
	Console::println(methodsDocumentation);

	//
	Console::println("Variables");
	Console::println("-----------");
	Console::println(variablesDocumentation);

	//
	Console::println("Operators");
	Console::println("-----------");
	Console::println(operatorsDocumentation);

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
