#include <cstdlib>
#include <memory>
#include <set>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Documentation.h>
#include <miniscript/utilities/Properties.h>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/utilities/Console.h>
#include <tdme/miniscript/EngineMiniScript.h>

using std::make_unique;
using std::set;
using std::string;

using miniscript::miniscript::Documentation;
using miniscript::utilities::Properties;

using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::Console;
using tdme::miniscript::EngineMiniScript;

int main(int argc, char** argv)
{
	Console::printLine(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	EngineMiniScript::initialize();

	//
	auto baseMiniScript = make_unique<EngineMiniScript>();
	baseMiniScript->registerMethods();

	//
	auto logicMiniScript = make_unique<LogicMiniScript>();
	logicMiniScript->registerMethods();

	//
	auto guiMiniScript = make_unique<GUIMiniScript>(nullptr);
	guiMiniScript->registerMethods();

	//
	auto baseClassMethods = Documentation::getAllClassMethods(baseMiniScript.get());
	auto baseMethodCategories = Documentation::getMethodsCategories(baseMiniScript.get(), baseClassMethods);
	// classes
	auto classesDocumentation = Documentation::generateClassesDocumentation("EngineMiniScript Classes", 6, baseMiniScript.get(), descriptions, "miniscript.basemethod.", baseClassMethods);
	// base methods
	auto baseMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMiniScript Base Methods", 7, baseMiniScript.get(), descriptions, "miniscript.basemethod.", baseClassMethods);
	// logic methods
	auto logicMethodCategories = Documentation::getMethodsCategories(logicMiniScript.get(), baseClassMethods);
	auto logicMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMiniScript Logic Methods", 8, logicMiniScript.get(), descriptions, "miniscript.logicmethod.", baseClassMethods, baseMiniScript.get());
	// gui methods
	auto guiMethodCategories = Documentation::getMethodsCategories(guiMiniScript.get(), baseClassMethods);
	auto guiMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMiniScript GUI Methods", 9, guiMiniScript.get(), descriptions, "miniscript.", baseClassMethods, baseMiniScript.get());
	// base methods
	auto operatorsDocumentation = Documentation::generateOperatorsDocumentation("MiniScript Operators", 10, baseMiniScript.get());

	//
	Console::printLine("Classes");
	Console::printLine("---------");
	Console::printLine(classesDocumentation);
	//
	Console::printLine("Base methods");
	Console::printLine("---------");
	Console::printLine(baseMethodsDocumentation);
	//
	Console::printLine("Logic methods");
	Console::printLine("---------");
	Console::printLine(logicMethodsDocumentation);
	//
	Console::printLine("GUI methods");
	Console::printLine("---------");
	Console::printLine(guiMethodsDocumentation);
	//
	Console::printLine("Operators");
	Console::printLine("---------");
	Console::printLine(operatorsDocumentation);
	// properties
	Console::printLine();
	Console::printLine("# properties methodname=human readable string");
	//
	{
		Console::printLine("# base methods");
		//
		for (const auto& baseMethodCategory: baseMethodCategories) {
			Console::printLine("miniscript.basemethod.group." + (baseMethodCategory.empty() == true?"uncategorized":baseMethodCategory) + "=");
		}
		//
		auto scriptMethods = baseMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::printLine("miniscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::printLine("# miniscript logic methods");
		//
		for (const auto& logicMethodCategory: logicMethodCategories) {
			Console::printLine("miniscript.logicmethod.group." + (logicMethodCategory.empty() == true?"uncategorized":logicMethodCategory) + "=");
		}
		//
		auto scriptMethods = logicMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::printLine("miniscript.logicmethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::printLine("# miniscript gui methods");
		//
		for (const auto& guiMethodCategory: guiMethodCategories) {
			Console::printLine("miniscript.group." + (guiMethodCategory.empty() == true?"uncategorized":guiMethodCategory) + "=");
		}
		//
		auto scriptMethods = guiMiniScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::printLine("miniscript." + scriptMethod->getMethodName() + "=");
		}
	}

	//
	Console::printLine();
	Console::printLine("Keywords: ");
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
	Console::printLine();

	//
	return EXIT_SUCCESS;
}
