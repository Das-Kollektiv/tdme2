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
protected:
	Context* context { nullptr };
	Logic* logic { nullptr };

	// overridden methods
	void registerStateMachineStates() override;
	void registerMethods() override;
	void registerVariables() override;

public:

	/**
	 * Public constructor
	 * @param context context
	 * @param logic logic
	 */
	LogicMiniScript(Context* context, Logic* logic);

	/**
	 * Destructor
	 */
	virtual ~LogicMiniScript();

};
