#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/scripting/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using tdme::gui::GUI;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utilities::MiniScript;

/**
 * GUI mini script
 */
class tdme::gui::scripting::GUIMiniScript: public MiniScript {
public:

	/**
	 * Public constructor
	 * @param screenNode screen node
	 */
	GUIMiniScript(GUIScreenNode* screenNode);

	/**
	 * Destructor
	 */
	virtual ~GUIMiniScript();

	// overridden methods
	void registerStateMachineStates() override;
	void registerMethods() override;
	void registerVariables() override;

	/**
	 * @return next screen node
	 */
	inline GUIScreenNode* getNextScreenNode() {
		return nextScreenNode;
	}

	/**
	 * @return if screen has been popped
	 */
	inline bool isPopped() {
		return popped;
	}

private:
	GUIScreenNode* screenNode { nullptr };
	GUIScreenNode* nextScreenNode { nullptr };
	bool popped { false };

};
