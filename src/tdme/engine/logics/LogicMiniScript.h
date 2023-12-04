#pragma once

#include <array>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/logics/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/os/threading/Mutex.h>
#include <tdme/utilities/EngineMiniScript.h>

using std::array;
using std::string;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::logics::Context;
using tdme::engine::logics::MiniScriptLogic;
using tdme::engine::physics::Body;
using tdme::engine::prototype::Prototype;
using tdme::engine::Transform;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::os::threading::Mutex;
using tdme::utilities::EngineMiniScript;

/**
 * Logic mini script
 */
class tdme::engine::logics::LogicMiniScript: public EngineMiniScript {
	friend class MiniScriptLogic;

protected:
	STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ENGINE;
	STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_LOGIC;
	STATIC_DLL_IMPEXT static const vector<string> CONTEXTFUNCTIONS_ENGINELOGIC;

	Context* context { nullptr };
	MiniScriptLogic* logic { nullptr };

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

	struct PrototypeCounter {
		int counter;
		unique_ptr<Prototype> prototype;
	};
	unordered_map<string, PrototypeCounter> prototypes;

	struct PrototypeToAdd {
		enum Type {
			TYPE_SPAWN,
			TYPE_ATTACH,
		};
		PrototypeToAdd(
			Type type,
			Prototype* prototype,
			const string& id,
			const string& attachNodeId,
			const Transform& transform,
			const string& hierarchyId,
			const string& hierarchyParentId
		):
			type(type),
			prototype(prototype),
			id(id),
			attachNodeId(attachNodeId),
			transform(transform),
			hierarchyId(hierarchyId),
			hierarchyParentId(hierarchyParentId)
		{}
		Type type;
		Prototype* prototype { nullptr };
		string id;
		string attachNodeId;
		Transform transform;
		string hierarchyId;
		string hierarchyParentId;
	};
	Mutex prototypesToAddMutex;
	vector<PrototypeToAdd> enginePrototypesToAdd;
	vector<PrototypeToAdd> physicsPrototypesToAdd;

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
	inline void setLogic(MiniScriptLogic* logic) {
		this->logic = logic;
	}

	/**
	 * Get entity by given entity id and given child entity id, the latter expects a entity hierarchy to resolve given child entity
	 * @param entityId entity id
	 * @param childEntityId child entity id
	 */
	Entity* getEntity(const string& entityId, const string& childEntityId);

public:
	// forbid class copy
	FORBID_CLASS_COPY(LogicMiniScript)

	/**
	 * Public constructor
	 */
	LogicMiniScript();

	/**
	 * Destructor
	 */
	virtual ~LogicMiniScript();

	// overridden methods
	const string getBaseClass();
	const vector<string> getTranspilationUnits();
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
