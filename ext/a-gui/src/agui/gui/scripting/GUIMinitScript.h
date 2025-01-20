#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include <minitscript/minitscript/MinitScript.h>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/scripting/fwd-agui.h>

using std::array;
using std::string;
using std::unique_ptr;
using std::unordered_set;
using std::vector;

// namespaces
namespace agui {
namespace gui {
namespace scripting {
	using ::minitscript::minitscript::MinitScript;

	using ::agui::gui::GUI;
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIScreenNode;
}
}
}

/**
 * GUI mini script
 */
class agui::gui::scripting::GUIMinitScript: public MinitScript {
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
	 * @returns release next screen node
	 */
	inline GUIScreenNode* releaseNextScreenNode() {
		return nextScreenNode.release();
	}

	/**
	 * @returns if screen has been popped
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
	AGUI_STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTION_GUI;

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
