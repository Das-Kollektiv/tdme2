#include <tdme/utilities/EngineMiniScript.h>

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
#include <tdme/utilities/MiniScriptMatrix3x3.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptMatrix4x4.h>
#include <tdme/utilities/MiniScriptQuaternion.h>
#include <tdme/utilities/MiniScriptTransform.h>
#include <tdme/utilities/MiniScriptVector2.h>
#include <tdme/utilities/MiniScriptVector3.h>
#include <tdme/utilities/MiniScriptVector4.h>
#include <tdme/utilities/StringTools.h>

using tdme::utilities::EngineMiniScript;

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
using tdme::utilities::MiniScriptMatrix3x3;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptMatrix4x4;
using tdme::utilities::MiniScriptQuaternion;
using tdme::utilities::MiniScriptTransform;
using tdme::utilities::MiniScriptVector2;
using tdme::utilities::MiniScriptVector3;
using tdme::utilities::MiniScriptVector4;
using tdme::utilities::StringTools;

void EngineMiniScript::registerDataTypes() {
	//
	registerDataType(new MiniScriptTransform());
	registerDataType(new MiniScriptMatrix4x4());
	registerDataType(new MiniScriptMatrix3x3());
	registerDataType(new MiniScriptQuaternion());
	registerDataType(new MiniScriptVector2());
	registerDataType(new MiniScriptVector3());
	registerDataType(new MiniScriptVector4());
}

EngineMiniScript* EngineMiniScript::loadScript(const string& pathName, const string& fileName) {
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
	unique_ptr<EngineMiniScript> scriptInstance;
	if (logicMiniScript == true) {
		scriptInstance = make_unique<LogicMiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	} else
	if (guiMiniScript == true) {
		scriptInstance = make_unique<GUIMiniScript>(nullptr);
		scriptInstance->parseScript(pathName, fileName);
	} else {
		scriptInstance = make_unique<EngineMiniScript>();
		scriptInstance->parseScript(pathName, fileName);
	}
	//
	return scriptInstance.release();
}

EngineMiniScript::EngineMiniScript(): MiniScript() {
}
