#include <cstdlib>
#include <memory>
#include <set>
#include <string>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Documentation.h>
#include <minitscript/utilities/Properties.h>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/scripting/GUIMinitScript.h>
#include <tdme/utilities/Console.h>
#include <tdme/minitscript/EngineMinitScript.h>

using std::make_unique;
using std::set;
using std::string;

using minitscript::minitscript::Documentation;
using minitscript::utilities::Properties;

using tdme::engine::logics::LogicMinitScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMinitScript;
using tdme::utilities::Console;
using tdme::minitscript::EngineMinitScript;

int main(int argc, char** argv)
{
	Console::printLine(string("minitscriptdocumentation ") + Version::getVersion());
	Console::printLine(Version::getCopyright());
	Console::printLine();

	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	EngineMinitScript::initialize();

	//
	auto baseMinitScript = make_unique<EngineMinitScript>();
	baseMinitScript->registerMethods();

	//
	auto logicMinitScript = make_unique<LogicMinitScript>();
	logicMinitScript->registerMethods();

	//
	auto guiMinitScript = make_unique<GUIMinitScript>(nullptr);
	guiMinitScript->registerMethods();

	//
	auto baseClassMethods = Documentation::getAllClassMethods(baseMinitScript.get());
	auto baseMethodCategories = Documentation::getMethodsCategories(baseMinitScript.get(), baseClassMethods);
	// classes
	auto classesDocumentation = Documentation::generateClassesDocumentation("EngineMinitScript Classes", 6, baseMinitScript.get(), descriptions, "minitscript.basemethod.", baseClassMethods);
	// base methods
	auto baseMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMinitScript Base Methods", 7, baseMinitScript.get(), descriptions, "minitscript.basemethod.", baseClassMethods);
	// logic methods
	auto logicMethodCategories = Documentation::getMethodsCategories(logicMinitScript.get(), baseClassMethods);
	auto logicMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMinitScript Logic Methods", 8, logicMinitScript.get(), descriptions, "minitscript.logicmethod.", baseClassMethods, baseMinitScript.get());
	// gui methods
	auto guiMethodCategories = Documentation::getMethodsCategories(guiMinitScript.get(), baseClassMethods);
	auto guiMethodsDocumentation = Documentation::generateMethodsDocumentation("EngineMinitScript GUI Methods", 9, guiMinitScript.get(), descriptions, "minitscript.", baseClassMethods, baseMinitScript.get());
	// base methods
	auto operatorsDocumentation = Documentation::generateOperatorsDocumentation("MinitScript Operators", 10, baseMinitScript.get());

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
			Console::printLine("minitscript.basemethod.group." + (baseMethodCategory.empty() == true?"uncategorized":baseMethodCategory) + "=");
		}
		//
		auto scriptMethods = baseMinitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::printLine("minitscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::printLine("# minitscript logic methods");
		//
		for (const auto& logicMethodCategory: logicMethodCategories) {
			Console::printLine("minitscript.logicmethod.group." + (logicMethodCategory.empty() == true?"uncategorized":logicMethodCategory) + "=");
		}
		//
		auto scriptMethods = logicMinitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMinitScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::printLine("minitscript.logicmethod." + scriptMethod->getMethodName() + "=");
		}
	}
	{
		Console::printLine("# minitscript gui methods");
		//
		for (const auto& guiMethodCategory: guiMethodCategories) {
			Console::printLine("minitscript.group." + (guiMethodCategory.empty() == true?"uncategorized":guiMethodCategory) + "=");
		}
		//
		auto scriptMethods = guiMinitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			if (baseMinitScript->hasMethod(scriptMethod->getMethodName()) == true) continue;
			Console::printLine("minitscript." + scriptMethod->getMethodName() + "=");
		}
	}

	//
	Console::printLine();
	Console::printLine("Keywords: ");
	set<string> allMethods;
	{
		//
		auto scriptMethods = baseMinitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			allMethods.insert(scriptMethod->getMethodName());
		}
	}
	{
		//
		auto scriptMethods = logicMinitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			allMethods.insert(scriptMethod->getMethodName());
		}
	}
	{
		//
		auto scriptMethods = guiMinitScript->getMethods();
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
