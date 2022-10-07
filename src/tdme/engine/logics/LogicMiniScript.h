#pragma once

#include <string>
#include <unordered_map>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/MiniScript.h>

using std::string;
using std::unordered_map;

using tdme::engine::logics::Context;
using tdme::engine::logics::Logic;
using tdme::engine::physics::Body;
using tdme::engine::prototype::Prototype;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::os::threading::Mutex;
using tdme::utilities::MiniScript;

/**
 * Logic mini script
 */
class tdme::engine::logics::LogicMiniScript: public MiniScript {
	friend class MiniScriptLogic;

protected:
	Context* context { nullptr };
	Logic* logic { nullptr };

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
	array<bool, 3> mouseDown {{ false, false, false }};
	array<bool, 3> mouseUp {{ false, false, false }};
	array<bool, 3> mouseDragging {{ false, false, false }};
	bool mouseMoved = false;
	float mouseWheelX { 0.0f };
	float mouseWheelY { 0.0f };
	float mouseWheelZ { 0.0f };

	struct PrototypeCounter {
		int counter;
		Prototype* prototype { nullptr };
	};
	unordered_map<string, PrototypeCounter> prototypes;

	struct PrototypeToAdd {
		Prototype* prototype { nullptr };
		string id;
		Transform transform;
	};
	Mutex prototypesToAddMutex;
	unordered_map<string, PrototypeToAdd> enginePrototypesToAdd;
	unordered_map<string, PrototypeToAdd> physicsPrototypesToAdd;

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

	// overridden methods
	void registerStateMachineStates() override;
	void registerMethods() override;
	void registerVariables() override;

	/**
	 * Collect HID events
	 * @param mouseEvents mouse events
	 * @param keyEvents keyboard events
	 */
	void collectHIDEvents(vector<GUIMouseEvent>& mouseEvents, vector<GUIKeyboardEvent>& keyEvents);

};
