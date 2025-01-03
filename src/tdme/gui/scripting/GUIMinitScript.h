#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/gui/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/scripting/fwd-tdme.h>
#include <tdme/minitscript/EngineMinitScript.h>

using std::array;
using std::string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIScreenNode;
using tdme::minitscript::EngineMinitScript;

/**
 * GUI mini script
 */
class tdme::gui::scripting::GUIMinitScript: public EngineMinitScript {
public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIMinitScript)

	/**
	 * Public constructor
	 * @param screenNode screen node
	 */
	GUIMinitScript(GUIScreenNode* screenNode);

	/**
	 * Destructor
	 */
	virtual ~GUIMinitScript();

	// overridden methods
	const string getBaseClassHeader();
	const string getBaseClass();
	const vector<string> getTranspilationUnits();
	void registerStateMachineStates() override;
	void registerMethods() override;

	/**
	 * @return release next screen node
	 */
	inline GUIScreenNode* releaseNextScreenNode() {
		return nextScreenNode.release();
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
	STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTION_GUI;

	GUIScreenNode* screenNode { nullptr };
	unique_ptr<GUIScreenNode> nextScreenNode;
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
