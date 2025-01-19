#include <tdme/minitscript/EngineMinitScript.h>

#include <memory>
#include <string>
#include <vector>

#include <minitscript/minitscript/MinitScript.h>

#include <tdme/tdme.h>
#include <tdme/engine/logics/LogicMinitScript.h>
#include <agui/gui/scripting/GUIMinitScript.h>
#include <tdme/os/filesystem/FileSystem.h>
#include <tdme/os/filesystem/FileSystemInterface.h>
#include <tdme/utilities/Console.h>
#include <tdme/minitscript/MinitScriptMatrix3x3.h>
#include <tdme/minitscript/MinitScriptMatrix4x4.h>
#include <tdme/minitscript/MinitScriptMatrix4x4.h>
#include <tdme/minitscript/MinitScriptQuaternion.h>
#include <tdme/minitscript/MinitScriptTransform.h>
#include <tdme/minitscript/MinitScriptVector2.h>
#include <tdme/minitscript/MinitScriptVector3.h>
#include <tdme/minitscript/MinitScriptVector4.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/StringTools.h>

using tdme::minitscript::EngineMinitScript;

using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

using minitscript::minitscript::MinitScript;

using tdme::engine::logics::LogicMinitScript;
using agui::gui::scripting::GUIMinitScript;
using tdme::os::filesystem::FileSystem;
using tdme::os::filesystem::FileSystemInterface;
using tdme::utilities::Console;
using tdme::minitscript::MinitScriptMatrix3x3;
using tdme::minitscript::MinitScriptMatrix4x4;
using tdme::minitscript::MinitScriptMatrix4x4;
using tdme::minitscript::MinitScriptQuaternion;
using tdme::minitscript::MinitScriptTransform;
using tdme::minitscript::MinitScriptVector2;
using tdme::minitscript::MinitScriptVector3;
using tdme::minitscript::MinitScriptVector4;
using tdme::utilities::Exception;
using tdme::utilities::StringTools;

void EngineMinitScript::initialize() {
	MinitScript::initialize();
	//
	registerDataType(new MinitScriptTransform());
	registerDataType(new MinitScriptMatrix4x4());
	registerDataType(new MinitScriptMatrix3x3());
	registerDataType(new MinitScriptQuaternion());
	registerDataType(new MinitScriptVector2());
	registerDataType(new MinitScriptVector3());
	registerDataType(new MinitScriptVector4());
	//
	MinitScriptTransform::initialize();
	MinitScriptMatrix4x4::initialize();
	MinitScriptMatrix3x3::initialize();
	MinitScriptQuaternion::initialize();
	MinitScriptVector2::initialize();
	MinitScriptVector3::initialize();
	MinitScriptVector4::initialize();
}

MinitScript* EngineMinitScript::loadScript(const string& pathName, const string& fileName) {
	// we need to detect MinitScript variant
	vector<string> scriptAsStringArray;
	try {
		FileSystem::getInstance()->getContentAsStringArray(pathName, fileName, scriptAsStringArray);
	} catch (Exception& exception) {
		Console::printLine("MinitScript::loadScript(): An error occurred: " + string(exception.what()));
		return nullptr;
	}

	// detect MinitScript variant
	auto logicMinitScript = false;
	auto guiMinitScript = false;
	array<string, 2> logicMinitScriptFunctions {
		"updateEngine",
		"updateLogic"
	};
	array<string, 12> guiMinitScriptFunctions {
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
		for (const auto& functionName: logicMinitScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				logicMinitScript = true;
				break;
			}
		}
		if (logicMinitScript == true) break;
		for (const auto& functionName: guiMinitScriptFunctions) {
			if (StringTools::regexMatch(scriptLine, "^[\\s]*function:[\\s]*" + functionName + "[\\s]*\\(.*\\).*$") == true) {
				guiMinitScript = true;
				break;
			}
		}
		if (guiMinitScript == true) break;
	}

	// load specific MinitScript
	unique_ptr<MinitScript> scriptInstance;
	if (logicMinitScript == true) {
		scriptInstance = make_unique<LogicMinitScript>();
		scriptInstance->parseScript(pathName, fileName);
	} else
	if (guiMinitScript == true) {
		scriptInstance = make_unique<GUIMinitScript>(nullptr);
		scriptInstance->parseScript(pathName, fileName);
	} else {
		scriptInstance = make_unique<EngineMinitScript>();
		scriptInstance->parseScript(pathName, fileName);
	}
	//
	return scriptInstance.release();
}

EngineMinitScript::EngineMinitScript(): MinitScript() {
}

const string EngineMinitScript::getBaseClass() {
	return "tdme::minitscript::EngineMinitScript";
}

const vector<string> EngineMinitScript::getTranspilationUnits() {
	return {
		"ext/minitscript/src/minitscript/minitscript/ApplicationMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/ArrayMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/BaseMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/ByteArrayMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/ConsoleMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/ContextMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/CryptographyMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/FileSystemMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/JSONMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/MapMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/MathMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/MinitScript.cpp",
		"ext/minitscript/src/minitscript/minitscript/NetworkMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/ScriptMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/SetMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/StringMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/TimeMethods.cpp",
		"ext/minitscript/src/minitscript/minitscript/XMLMethods.cpp",
		"src/tdme/minitscript/EngineMinitScript.cpp",
		"src/tdme/minitscript/MinitScriptMatrix3x3.cpp",
		"src/tdme/minitscript/MinitScriptMatrix4x4.cpp",
		"src/tdme/minitscript/MinitScriptQuaternion.cpp",
		"src/tdme/minitscript/MinitScriptTransform.cpp",
		"src/tdme/minitscript/MinitScriptVector2.cpp",
		"src/tdme/minitscript/MinitScriptVector3.cpp",
		"src/tdme/minitscript/MinitScriptVector4.cpp"
	};
}

