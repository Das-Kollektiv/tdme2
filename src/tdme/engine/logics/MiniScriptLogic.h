#pragma once

#include <string>
#include <span>

#include <tdme/tdme.h>

#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MiniScript.h>

using std::span;
using std::string;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Logic;
using tdme::utilities::Console;
using tdme::utilities::MiniScript;

/**
 * Mini script logic
 * @author Andreas Drewke
 */
class tdme::engine::logics::MiniScriptLogic: public Logic {
public:

	/**
	 * Public constructor
	 * @param context context
	 * @param id id
	 * @param handlingHIDInput handling hid input
	 * @param miniScript logic mini script
	 */
	inline MiniScriptLogic(Context* context, const string& id, bool handlingHIDInput, LogicMiniScript* miniScript): Logic(context, id, handlingHIDInput), miniScript(miniScript) {
		miniScript->setContext(context);
		miniScript->setLogic(this);
	}

	// overridden methods
	inline void handleHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents) {
		miniScript->collectHIDEvents(mouseEvents, keyEvents);
	}

	inline void updateEngine() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateEngine", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateEngine()(): Failed to call updateEngine() function");
		}
	}

	inline void updateLogic() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("updateLogic", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::updateLogic()(): Failed to call updateLogic() function");
		}
	}

	inline void onLogicAdded() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicAdded", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicAdded()(): Failed to call onLogicAdded() function");
		}
	}

	inline void onLogicsProcessed() override {
		vector<MiniScript::ScriptVariable> argumentValues(0);
		MiniScript::ScriptVariable returnValue;
		span argumentValuesSpan(argumentValues);
		if (miniScript->call("onLogicsProcessed", argumentValuesSpan, returnValue) == false) {
			Console::println("MiniScriptLogic::onLogicsProcessed()(): Failed to call onLogicsProcessed() function");
		}
	}

private:
	LogicMiniScript* miniScript { nullptr };
};
