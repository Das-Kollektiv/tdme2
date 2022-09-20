#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/application/Application.h>
#include <tdme/engine/Version.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/StringTools.h>

using std::set;
using std::string;
using std::unordered_map;
using std::vector;

using tdme::application::Application;
using tdme::engine::Version;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::StringTools;

int main(int argc, char** argv)
{
	Console::println(string("createminiscriptcodecompletion ") + Version::getVersion());
	Console::println(Version::getCopyright());
	Console::println();

	//
	auto miniScript = new MiniScript();
	miniScript->registerMethods();

	vector<string> lines;
	lines.push_back("<?xml version=\"1.0\"?>");
	lines.push_back("<code-completion>");

	// methods
	auto scriptMethods = miniScript->getMethods();
	vector<string> methods;
	for (auto scriptMethod: scriptMethods) {
		Console::println("Adding method: " + scriptMethod->getMethodName());
		lines.push_back("	<keyword name=\"" + scriptMethod->getMethodName() + "\" func=\"yes\">");
		lines.push_back("		<overload return-value=\"" + MiniScript::ScriptVariable::getTypeAsString(scriptMethod->getReturnValueType()) + "\" descr=\"\">");
		for (auto& argumentType: scriptMethod->getArgumentTypes()) {
			string argumentValueString;
			if (argumentType.optional == true) argumentValueString+= "[";
			argumentValueString+= MiniScript::ScriptVariable::getTypeAsString(argumentType.type) + " ";
			argumentValueString+= string() + (argumentType.assignBack == true?"=":"") + "$" + argumentType.name;
			if (argumentType.optional == true) argumentValueString+= "]";
			lines.push_back("			<parameter name=\"" + argumentValueString + "\"/>");
		}
		if (scriptMethod->isVariadic() == true) {
			lines.push_back("			<parameter name=\"...\"/>");
		}
		lines.push_back("		</overload>");
		lines.push_back("	</keyword");
	}
	lines.push_back("</code-completion>");
	for (auto& line: lines) Console::println(line);
	Console::println();

	// store
	Console::println("Saving to: resources/engine/code-completion/tscript.xml");
	FileSystem::getInstance()->setContentFromStringArray("resources/engine/code-completion", "tscript.xml", lines);
}
