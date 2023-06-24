#include <array>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/engine/Version.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/gui/GUIParser.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/Properties.h>

using std::array;
using std::string;
using std::vector;

using tdme::engine::logics::LogicMiniScript;
using tdme::engine::Version;
using tdme::gui::scripting::GUIMiniScript;
using tdme::gui::GUIParser;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::Properties;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptcodecompletion ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	Properties methodDescriptions;
	methodDescriptions.load("resources/engine/code-completion", "tscript-methods.properties");

	//
	vector<string> keywords1;
	vector<string> keywords2;
	keywords2.push_back("function:");
	keywords2.push_back("on:");
	keywords2.push_back("on-enabled:");


	//
	vector<string> lines;
	lines.push_back("<?xml version=\"1.0\"?>");
	lines.push_back("<code-completion>");

	//
	auto baseMiniScript = new MiniScript();
	baseMiniScript->registerMethods();

	auto logicMiniScript = new LogicMiniScript();
	logicMiniScript->registerMethods();

	auto guiMiniScript = new GUIMiniScript(nullptr);
	guiMiniScript->registerMethods();

	//
	array<MiniScript*, 3> miniScriptFlavours = { baseMiniScript, logicMiniScript, guiMiniScript };
	for (auto miniScriptFlavour: miniScriptFlavours) {
		// methods
		auto scriptMethods = miniScriptFlavour->getMethods();
		vector<string> methods;
		for (auto scriptMethod: scriptMethods) {
			//
			if ((miniScriptFlavour != baseMiniScript && baseMiniScript->hasMethod(scriptMethod->getMethodName()) == true) ||
				(miniScriptFlavour == guiMiniScript && logicMiniScript->hasMethod(scriptMethod->getMethodName()) == true)
				) continue;
			//
			keywords1.push_back(scriptMethod->getMethodName());
			string description;
			if (description.empty() == true) description = methodDescriptions.get("miniscript.basemethod." + scriptMethod->getMethodName(), string());
			if (description.empty() == true) description = methodDescriptions.get("miniscript.logicmethod." + scriptMethod->getMethodName(), string());
			if (description.empty() == true) description = methodDescriptions.get("miniscript." + scriptMethod->getMethodName(), string());
			Console::println("Adding method: " + scriptMethod->getMethodName());
			lines.push_back("	<keyword name=\"" + scriptMethod->getMethodName() + "\" func=\"yes\">");
			lines.push_back("		<overload return-value=\"" + MiniScript::ScriptVariable::getReturnTypeAsString(scriptMethod->getReturnValueType()) + "\" descr=\"" + GUIParser::escape(description) + "\">");
			for (auto& argumentType: scriptMethod->getArgumentTypes()) {
				string argumentValueString;
				if (argumentType.optional == true) argumentValueString+= "[";
				argumentValueString+= MiniScript::ScriptVariable::getTypeAsString(argumentType.type) + " ";
				argumentValueString+= string() + (argumentType.assignBack == true?"=":"") + "$" + argumentType.name;
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
	for (auto& line: lines) Console::println(line);
	Console::println();

	// syntax highlighting
	Console::println("Syntax highlighting: ");
	Console::print("Syntax highlighting: keywords1: ");
	for (auto& keyword1: keywords1) Console::print(keyword1 + " ");
	Console::println();

	Console::print("Syntax highlighting: keywords2: ");
	for (auto& keyword2: keywords2) Console::print(keyword2 + " ");
	Console::println();
	Console::println();

	// store
	Console::println("Saving to: resources/engine/code-completion/tscript.xml");
	FileSystem::getInstance()->setContentFromStringArray("resources/engine/code-completion", "tscript.xml", lines);
}
