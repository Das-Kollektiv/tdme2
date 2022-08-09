#pragma once

#include <string>

#include <tdme/tdme.h>

#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/logics/Logic.h>
#include <tdme/engine/logics/LogicMiniScript.h>

using std::string;

using tdme::engine::logics::LogicMiniScript;

using tdme::engine::logics::Logic;

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
	}

	/**
	 * Update engine
	 */
	void updateEngine() override;

	/**
	 * Update logic
	 */
	void updateLogic() override;

	/**
	 * On logic added
	 */
	void onLogicAdded() override;

	/**
	 * On logics processed
	 */
	void onLogicsProcessed() override;

private:
	LogicMiniScript* miniScript { nullptr };
};
