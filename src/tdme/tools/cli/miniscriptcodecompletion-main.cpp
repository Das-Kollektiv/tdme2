#include <array>
#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/EngineMiniScript.h>
#include <tdme/utilities/Properties.h>

using std::array;
using std::make_unique;
using std::string;
using std::vector;

using tdme::application::Application;
using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::EngineMiniScript;
using tdme::utilities::Properties;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptcodecompletion ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	Properties methodDescriptions;
	methodDescriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	vector<string> keywords1;
	vector<string> keywords2;
	keywords2.push_back("callable:");
	keywords2.push_back("function:");
	keywords2.push_back("on:");
	keywords2.push_back("on-enabled:");


	//
	vector<string> lines;
	lines.push_back("<?xml version=\"1.0\"?>");
	lines.push_back("<code-completion>");

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
	array<EngineMiniScript*, 3> miniScriptFlavours = { baseMiniScript.get(), logicMiniScript.get(), guiMiniScript.get() };
	for (const auto miniScriptFlavour: miniScriptFlavours) {
		// methods
		auto scriptMethods = miniScriptFlavour->getMethods();
		vector<string> methods;
		for (const auto& scriptMethod: scriptMethods) {
			//
			if ((miniScriptFlavour != baseMiniScript.get() && baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) ||
				(miniScriptFlavour == guiMiniScript.get() && logicMiniScript->hasMethod(scriptMethod->getMethodName()) == true)
				) continue;
			//
			keywords1.push_back(scriptMethod->getMethodName());
			string description;
			if (description.empty() == true) description = methodDescriptions.get("miniscript.basemethod." + scriptMethod->getMethodName(), string());
			if (description.empty() == true) description = methodDescriptions.get("miniscript.logicmethod." + scriptMethod->getMethodName(), string());
			if (description.empty() == true) description = methodDescriptions.get("miniscript." + scriptMethod->getMethodName(), string());
			Console::println("Adding method: " + scriptMethod->getMethodName());
			lines.push_back("	<keyword name=\"" + scriptMethod->getMethodName() + "\" func=\"yes\">");
			lines.push_back("		<overload return-value=\"" + EngineMiniScript::Variable::getReturnTypeAsString(scriptMethod->getReturnValueType(), scriptMethod->isReturnValueNullable()) + "\" descr=\"" + GUIParser::escape(description) + "\">");
			for (const auto& argumentType: scriptMethod->getArgumentTypes()) {
				string argumentValueString;
				if (argumentType.optional == true) argumentValueString+= "[";
				argumentValueString+= EngineMiniScript::Variable::getTypeAsString(argumentType.type) + " ";
				argumentValueString+= string() + (argumentType.reference == true?"&":"") + "$" + argumentType.name;
				if (argumentType.optional == true) argumentValueString+= "]";
				lines.push_back("			<parameter name=\"" + argumentValueString + "\" />");
			}
			if (scriptMethod->isVariadic() == true) {
				lines.push_back("			<parameter name=\"...\" />");
			}
			lines.push_back("		</overload>");
			lines.push_back("	</keyword>");
		}
	}

	//
	lines.push_back("</code-completion>");
	for (const auto& line: lines) Console::println(line);
	Console::println();

	// syntax highlighting
	Console::println("Syntax highlighting: ");
	Console::print("Syntax highlighting: keywords1: ");
	for (const auto& keyword1: keywords1) Console::print(keyword1 + " ");
	Console::println();

	Console::print("Syntax highlighting: keywords2: ");
	for (const auto& keyword2: keywords2) Console::print(keyword2 + " ");
	Console::println();
	Console::println();

	// store
	Console::println("Saving to: resources/engine/code-completion/tscript.xml");
	FileSystem::getInstance()->setContentFromStringArray("resources/engine/code-completion", "tscript.xml", lines);

	//
	Application::exit(Application::EXITCODE_SUCCESS);
}
