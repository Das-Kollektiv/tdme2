#include <algorithm>
#include <cstdlib>
#include <memory>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/Documentation.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Properties.h>

#include <tdme/engine/logics/LogicMinitScript.h>
#include <tdme/gui/scripting/GUIMinitScript.h>
#include <tdme/minitscript/EngineMinitScript.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Integer.h>
#include <tdme/utilities/StringTools.h>

using std::find;
using std::make_unique;
using std::set;
using std::string;
using std::vector;

using minitscript::minitscript::Documentation;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Version;
using minitscript::utilities::Properties;

using tdme::engine::logics::LogicMinitScript;
using tdme::gui::scripting::GUIMinitScript;
using tdme::minitscript::EngineMinitScript;
using tdme::utilities::Console;
using tdme::utilities::Integer;
using tdme::utilities::StringTools;


int main(int argc, char** argv)
{
	//
	auto printInformation = []() -> void {
		Console::printLine(string("minitscriptdocumentation ") + Version::getVersion());
		Console::printLine(Version::getCopyright());
		Console::printLine();
		Console::printLine("Usage: minitscriptdocumentation [--heading=n] classes|functions|logic-functions|gui-functions|keys|keywords");
		Console::printLine();
	};
	//
	if (argc != 2 && argc != 3) {
		printInformation();
		return EXIT_SUCCESS;
	}

	//
	auto heading = 1;
	auto argIdx = 1;
	if (StringTools::startsWith(argv[argIdx], "--heading=") == true) {
		auto sectionVector = StringTools::tokenize(argv[1], "=");
		if (sectionVector.size() != 2) {
			printInformation();
			return EXIT_SUCCESS;
		} else {
			heading = Integer::parse(sectionVector[1]);
		}
		argIdx++;
	}
	//
	if (argIdx >= argc) {
		printInformation();
		return EXIT_SUCCESS;
	}
	//
	auto documentationType = string(argv[argIdx]);
	array<string, 6> documentationTypes = {
		"classes",
		"functions",
		"logic-functions",
		"gui-functions",
		"keys",
		"keywords"
	};
	if (find(documentationTypes.begin(), documentationTypes.end(), documentationType) == documentationTypes.end()) {
		printInformation();
		return EXIT_SUCCESS;
	}

	//
	EngineMinitScript::initialize();

	//
	auto context = make_unique<minitscript::minitscript::Context>();
	auto minitScript = make_unique<EngineMinitScript>();
	minitScript->setContext(context.get());
	minitScript->registerMethods();
	minitScript->registerVariables();

	//
	Properties descriptions;
	descriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	auto baseMinitScript = make_unique<EngineMinitScript>();
	baseMinitScript->registerMethods();

	//
	auto logicMinitScript = make_unique<LogicMinitScript>();
	logicMinitScript->registerMethods();

	//
	auto guiMinitScript = make_unique<GUIMinitScript>(nullptr);
	guiMinitScript->registerMethods();

	// base
	auto baseClassMethods = Documentation::getAllClassMethods(baseMinitScript.get());
	auto baseMethodCategories = Documentation::getMethodsCategories(baseMinitScript.get(), baseClassMethods);

	//
	auto allClassMethods = Documentation::getAllClassMethods(minitScript.get());
	//
	if (documentationType == "classes") {
		// classes
		auto classesDocumentation = Documentation::generateClassesDocumentation("Engine MinitScript classes", heading, baseMinitScript.get(), descriptions, "minitscript.basemethod.", baseClassMethods);
		Console::printLine(classesDocumentation);
	} else
	if (documentationType == "functions") {
		// base functions
		auto baseFunctionsDocumentation = Documentation::generateFunctionsDocumentation("Engine MinitScript base functions", heading, baseMinitScript.get(), descriptions, "minitscript.basemethod.", baseClassMethods);
		Console::printLine(baseFunctionsDocumentation);
	} else
	if (documentationType == "logic-functions") {
		// logic methods
		auto logicFunctionsCategories = Documentation::getMethodsCategories(logicMinitScript.get(), baseClassMethods);
		auto logicFunctionsDocumentation = Documentation::generateFunctionsDocumentation("Engine MinitScript logic functions", heading, logicMinitScript.get(), descriptions, "minitscript.logicmethod.", baseClassMethods, baseMinitScript.get());
		Console::printLine(logicFunctionsDocumentation);
	} else
	if (documentationType == "gui-functions") {
		// gui methods
		auto guiFunctionsCategories = Documentation::getMethodsCategories(guiMinitScript.get(), baseClassMethods);
		auto guiFunctionsDocumentation = Documentation::generateFunctionsDocumentation("Engine MinitScript GUI functions", heading, guiMinitScript.get(), descriptions, "minitscript.", baseClassMethods, baseMinitScript.get());
		Console::printLine(guiFunctionsDocumentation);
	} else
	if (documentationType == "keys") {
		Console::printLine("# properties methodname=human readable string");
		Console::printLine("# base methods");
		//
		auto baseMethodCategories = Documentation::getMethodsCategories(minitScript.get(), allClassMethods);
		for (const auto& baseMethodCategory: baseMethodCategories) {
			Console::printLine("minitscript.basemethod.group." + (baseMethodCategory.empty() == true?"uncategorized":baseMethodCategory) + "=");
		}
		//
		auto scriptMethods = minitScript->getMethods();
		for (auto scriptMethod: scriptMethods) {
			Console::printLine("minitscript.basemethod." + scriptMethod->getMethodName() + "=");
		}
	} else
	if (documentationType == "keywords") {
		set<string> allMethods;
		{
			//
			auto scriptMethods = minitScript->getMethods();
			for (auto scriptMethod: scriptMethods) {
				allMethods.insert(scriptMethod->getMethodName());
			}
		}
		//
		for (const auto& method: allMethods) {
			Console::print(method + " ");
		}
	}
	//
	return EXIT_SUCCESS;
}
