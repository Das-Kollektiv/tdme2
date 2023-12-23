#include <memory>
#include <set>
#include <string>

#include <miniscript/miniscript.h>
#include <miniscript/miniscript/Documentation.h>
#include <miniscript/utilities/Properties.h>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
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

using tdme::application::Application;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::utilities::Console;
using tdme::miniscript::EngineMiniScript;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptdocumentation ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	EngineMiniScript::registerDataTypes();

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
	Console::println("Classes");
	Console::println("---------");
	Console::println(classesDocumentation);
	//
	Console::println("Base methods");
	Console::println("---------");
	Console::println(baseMethodsDocumentation);
	//
	Console::println("Logic methods");
	Console::println("---------");
	Console::println(logicMethodsDocumentation);
	//
	Console::println("GUI methods");
	Console::println("---------");
	Console::println(guiMethodsDocumentation);
	//
	Console::println("Operators");
	Console::println("---------");
	Console::println(operatorsDocumentation);
	// properties
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
	Application::exit(Application::EXITCODE_SUCCESS);
}
