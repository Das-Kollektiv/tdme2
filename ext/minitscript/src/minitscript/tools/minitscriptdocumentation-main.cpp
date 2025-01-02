#include <algorithm>
#include <cstdlib>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <minitscript/minitscript.h>
#include <minitscript/minitscript/Context.h>
#include <minitscript/minitscript/Documentation.h>
#include <minitscript/minitscript/MinitScript.h>
#include <minitscript/minitscript/Version.h>
#include <minitscript/utilities/Console.h>
#include <minitscript/utilities/Integer.h>
#include <minitscript/utilities/Properties.h>
#include <minitscript/utilities/StringTools.h>

using std::exit;
using std::find;
using std::make_pair;
using std::make_unique;
using std::map;
using std::pair;
using std::set;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using minitscript::minitscript::Context;
using minitscript::minitscript::Documentation;
using minitscript::minitscript::MinitScript;
using minitscript::minitscript::Version;
using minitscript::utilities::Console;
using minitscript::utilities::Integer;
using minitscript::utilities::Properties;
using minitscript::utilities::StringTools;

int main(int argc, char** argv)
{
	//
	auto printInformation = []() -> void {
		Console::printLine(string("minitscriptdocumentation ") + Version::getVersion());
		Console::printLine(Version::getCopyright());
		Console::printLine();
		Console::printLine("Usage: minitscriptdocumentation [--heading=n] classes|functions|variables|operators|keys|keywords");
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
		"variables",
		"operators",
		"keys",
		"keywords"
	};
	if (find(documentationTypes.begin(), documentationTypes.end(), documentationType) == documentationTypes.end()) {
		printInformation();
		return EXIT_SUCCESS;
	}
	//
	Properties descriptions;
	descriptions.load(MINITSCRIPT_DATA + "/resources/minitscript/documentation", "method-descriptions.properties");
	//
	MinitScript::initialize();
	//
	auto context = make_unique<Context>();
	auto minitScript = make_unique<MinitScript>();
	minitScript->setContext(context.get());
	minitScript->registerMethods();
	minitScript->registerVariables();
	//
	auto allClassMethods = Documentation::getAllClassMethods(minitScript.get());
	//
	if (documentationType == "classes") {
		// classes
		auto classesDocumentation = Documentation::generateClassesDocumentation("Classes", heading, minitScript.get(), descriptions, "minitscript.basemethod.", allClassMethods);
		Console::printLine(classesDocumentation);
	} else
	if (documentationType == "functions") {
		// base methods
		auto methodsDocumentation = Documentation::generateFunctionsDocumentation("Functions", heading, minitScript.get(), descriptions, "minitscript.basemethod.", allClassMethods);
		Console::printLine(methodsDocumentation);
	} else
	if (documentationType == "variables") {
		// variables
		auto variablesDocumentation = Documentation::generateVariablesDocumentation("Constants", heading, minitScript.get());
		Console::printLine(variablesDocumentation);
	} else
	if (documentationType == "operators") {
		// operators
		auto operatorsDocumentation = Documentation::generateOperatorsDocumentation("Operators", heading, minitScript.get());
		Console::printLine(operatorsDocumentation);
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
