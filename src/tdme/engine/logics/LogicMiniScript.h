#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using std::string;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::utilities::MiniScript;

/**
 * Logic mini script
 */
class tdme::engine::logics::LogicMiniScript: public MiniScript {
	friend class MiniScriptLogic;

protected:
	Context* context { nullptr };
	Logic* logic { nullptr };

	// overridden methods
	void registerStateMachineStates() override;
	void registerMethods() override;
	void registerVariables() override;

	/**
	 * Set context
	 * @param context context
	 */
	inline void setContext(Context* context) {
		this->context = context;
	}

	/**
	 * Set logic
	 * @param logic logic
	 */
	inline void setLogic(Logic* logic) {
		this->logic = logic;
	}

public:

	/**
	 * Public constructor
	 */
	LogicMiniScript();

	/**
	 * Destructor
	 */
	virtual ~LogicMiniScript();

};
