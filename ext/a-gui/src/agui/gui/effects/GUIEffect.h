#pragma once

#include <memory>

#include <agui/agui.h>
#include <agui/gui/effects/fwd-agui.h>
#include <agui/gui/effects/GUIEffectState.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/utilities/Action.h>

using std::unique_ptr;

// namespaces
namespace agui {
namespace gui {
namespace effects {
	using ::agui::gui::nodes::GUIColor;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::renderer::GUIRenderer;
	using ::agui::gui::GUI;
	using ::agui::utilities::Action;
}
}
}

/**
 * GUI effect base class
 * @author Andreas Drewke
 */
class agui::gui::effects::GUIEffect
{
public:
	enum EffectType { EFFECTTYPE_NONE, EFFECTTYPE_COLOR, EFFECTTYPE_POSITION };
	static constexpr int REPEAT_UNLIMITED { -1 };

protected:
	EffectType type { EFFECTTYPE_NONE };
	bool active { false };
	int64_t timeLast { -1LL };
	float timeTotal { 0.0 };
	float timeLeft { 0.0 };
	float timePassed { 0.0 };
	int repeat { 0 };
	int repeatLeft { 0 };
	bool yoyo { false };
	int yoyoLeft { 0 };
	bool persistant { false };
	unique_ptr<Action> action;
	GUINode* node { nullptr };
	GUIEffectState originalStartState;
	GUIEffectState originalEndState;
	GUIEffectState startState;
	GUIEffectState endState;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIEffect)

	/**
	 * Public constructor
	 * @param type type
	 * @param GUINode GUI node
	 */
	GUIEffect(EffectType type, GUINode* guiNode);

	/**
	 * Destructor
	 */
	virtual ~GUIEffect();

	/**
	 * @return type
	 */
	inline EffectType getType() const {
		return type;
	}

	/**
	 * @return active
	 */
	inline bool isActive() const {
		return active;
	}

	/**
	 * @return time total
	 */
	inline float getTimeTotal() const {
		return timeTotal;
	}

	/**
	 * Set time total
	 * @param timeTotal time total
	 */
	inline void setTimeTotal(float timeTotal) {
		this->timeTotal = timeTotal;
	}

	/**
	 * @return repeat count or -1 for unlimited repeating
	 */
	inline int getRepeat() const {
		return repeat;
	}

	/**
	 * Set repeat count or -1 for unlimited repeating
	 * @param repeat repeat
	 */
	inline void setRepeat(int repeat) {
		this->repeat = repeat;
	}

	/**
	 * @return yoyo
	 */
	inline float isYoyo() const {
		return yoyo;
	}

	/**
	 * Set yoyo
	 * @param yoyo yoyo
	 */
	inline void setYoyo(bool yoyo) {
		this->yoyo = yoyo;
	}

	/**
	 * @return if this effect is persistant, means if duration is reached this effect will still remain until removal
	 */
	inline float isPersistant() const {
		return persistant;
	}

	/**
	 * Set persistant, means if duration is reached this effect will still remain until removal
	 * @param persistant persistant
	 */
	inline void setPersistant(bool persistant) {
		this->persistant = persistant;
	}

	/**
	 * @return action to be performed on effect end
	 */
	inline Action* getAction() const {
		return action.get();
	}

	/**
	 * Set action to be performed on effect end
	 * @param action action
	 */
	inline void setAction(Action* action) {
		this->action = unique_ptr<Action>(action);
	}

	/**
	 * Start this effect
	 */
	virtual void start();

	/**
	 * Stop this effect
	 */
	virtual void stop();

	/**
	 * Updates the effect to GUI renderer and updates time
	 * @param gui GUI instance
	 * @return if action should be called
	 */
	virtual bool update(GUI* gui);

	/**
	 * Apply effect
	 * @param gui GUI instance
	 */
	virtual void apply(GUI* gui) = 0;

};
