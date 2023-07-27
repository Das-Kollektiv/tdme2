#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/scripting/fwd-tdme.h>
#include <tdme/utilities/MiniScript.h>

using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utilities::MiniScript;

/**
 * GUI mini script
 */
class tdme::gui::scripting::GUIMiniScript: public MiniScript {
public:
	// forbid class copy
	CLASS_FORBID_COPY(GUIMiniScript)

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

	/**
	 * Collect HID events
	 * @param mouseEvents mouse events
	 * @param keyEvents keyboard events
	 */
	void collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents);

private:
	GUIScreenNode* screenNode { nullptr };
	GUIScreenNode* nextScreenNode { nullptr };
	bool popped { false };

	// keys
	unordered_set<int32_t> keyboardChars;
	unordered_set<int32_t> keyboardKeys;
	string keyboardTypedChars;
	bool keyboardMetaDown { false };
	bool keyboardControlDown { false };
	bool keyboardAltDown { false };
	bool keyboardShiftDown { false };

	// mouse
	int mouseX { -1 };
	int mouseY { -1 };
	int mouseXUnscaled { -1 };
	int mouseYUnscaled { -1 };
	array<bool, 8> mouseDown {{ false, false, false, false, false, false, false, false }};
	array<bool, 8> mouseUp {{ false, false, false, false, false, false, false, false }};
	array<bool, 8> mouseDragging {{ false, false, false, false, false, false, false, false }};
	bool mouseMoved = false;
	float mouseWheelX { 0.0f };
	float mouseWheelY { 0.0f };
	float mouseWheelZ { 0.0f };

};
