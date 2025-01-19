#pragma once

#include <memory>

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffectState.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/Action.h>

using std::unique_ptr;

using tdme::gui::effects::GUIEffectState;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::gui::renderer::GUIRenderer;
using tdme::utilities::Action;

/**
 * GUI effect base class
 * @author Andreas Drewke
 */
class tdme::gui::effects::GUIEffect
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
	 * Updates the effect to GUI rendererBackend and updates time
	 * @param guiRenderer GUI renderer
	 * @return if action should be called
	 */
	virtual bool update(GUIRenderer* guiRenderer);

	/**
	 * Apply effect
	 * @param guiRenderer GUI rendererBackend
	 * @param guiNode GUI node
	 */
	virtual void apply(GUIRenderer* guiRenderer) = 0;

};
