#include <tdme/utilities/TDMEMiniScript.h>

#include <memory>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/gui/scripting/GUIMiniScript.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::TDMEMiniScript;

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using tdme::engine::logics::LogicMiniScript;
using tdme::gui::scripting::GUIMiniScript;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;
using tdme::utilities::StringTools;

TDMEMiniScript* TDMEMiniScript::loadScript(const string& pathName, const string& fileName) {
	// we need to detect MiniScript variant
	vector<string> scriptAsStringArray;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptAsStringArray);
	} catch (Exception& exception) {
		Console::println("MiniScript::loadScript(): An error occurred: " + string(exception.what()));
		return nullptr;
	}

	// detect MiniScript variant
	auto logicMiniScript = false;
	auto guiMiniScript = false;
	array<string, 2> logicMiniScriptFunctions {
		"updateEngine",
		"updateLogic"
	};
	array<string, 12> guiMiniScriptFunctions {
		"onAction",
		"onChange",
		"onMouseOver",
		"onContextMenuRequest",
		"onFocus",
		"onUnfocus",
		"onMove",
		"onMoveRelease",
		"onTooltipShowRequest",
		"onTooltipCloseRequest",
		"onDragRequest",
		"onTick"
	};
	for (const auto& scriptLine: scriptAsStringArray) {
		for (const auto& functionName: logicMiniScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				logicMiniScript = true;
				break;
			}
		}
		if (logicMiniScript == true) break;
		for (const auto& functionName: guiMiniScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				guiMiniScript = true;
				break;
			}
		}
		if (guiMiniScript == true) break;
	}

	// load specific MiniScript
	unique_ptr<TDMEMiniScript> scriptInstance;
	if (logicMiniScript == true) {
		scriptInstance = make_unique<LogicMiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	} else
	if (guiMiniScript == true) {
		scriptInstance = make_unique<GUIMiniScript>(nullptr);
		scriptInstance->parseScript(pathName, fileName);
	} else {
		scriptInstance = make_unique<TDMEMiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	}
	//
	return scriptInstance.release();
}

TDMEMiniScript::TDMEMiniScript(): MiniScript() {
}
