#pragma once

#include <tdme/tdme.h>

#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>

using std::string;
using std::vector;

using tdme::engine::logics::Logic;
using tdme::engine::logics::LogicMiniScript;

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
	MiniScriptLogic(Context* context, const string& id, bool handlingHIDInput, LogicMiniScript* miniScript): Logic(context, id, handlingHIDInput), miniScript(miniScript) {
	}

	/**
	 * Update engine
	 */
	inline void updateEngine() override {
		miniScript->pushScriptState();
		miniScript->emit("updateEngine");
		miniScript->popScriptState();
	}

	/**
	 * Update logic
	 */
	inline void updateLogic() override {
		miniScript->emit("updateLogic");
	}

	/**
	 * On logic added
	 */
	inline void onLogicAdded() {
		miniScript->pushScriptState();
		miniScript->emit("logicAdded");
		miniScript->popScriptState();
	}

	/**
	 * On logics processed
	 */
	virtual void onLogicsProcessed() {
		miniScript->pushScriptState();
		miniScript->emit("logicsProcessed");
		miniScript->popScriptState();
	}

private:
	LogicMiniScript* miniScript { nullptr };
};
