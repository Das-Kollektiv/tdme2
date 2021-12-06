#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;
using tdme::utilities::Action;

/**
 * GUI effect base class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIEffect
{
public:
	static constexpr int REPEAT_UNLIMITED { -1 };

	struct EffectState {
		enum Type { TYPE_RESET, TYPE_COLOR, TYPE_POSITION };
		Type type { TYPE_RESET };
		float positionX { 0.0f };
		float positionY { 0.0f };
		GUIColor colorAdd { 0.0f, 0.0f, 0.0f, 0.0f };
		GUIColor colorMul { 1.0f, 1.0f, 1.0f, 1.0f };
	};

protected:
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
	Action* action { nullptr };
	EffectState originalStartState;
	EffectState originalEndState;
	EffectState startState;
	EffectState endState;
	EffectState effectState;

public:
	/**
	 * Public constructor
	 */
	GUIEffect();

	/**
	 * Destructor
	 */
	virtual ~GUIEffect();

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
		return action;
	}

	/**
	 * Set action to be performed on effect end
	 * @param action action
	 */
	inline void setAction(Action* action) {
		this->action = action;
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
	 * @param guiRenderer gui renderer
	 * @return if action should be called
	 */
	virtual bool update(GUIRenderer* guiRenderer);

	/**
	 * @return effect state
	 */
	inline const EffectState& getState() {
		return effectState;
	}

	/**
	 * Apply state
	 * @param state state
	 */
	virtual void applyState(const EffectState& state) = 0;

	/**
	 * Apply effect
	 * @param guiRenderer GUI renderer
	 */
	virtual void apply(GUIRenderer* guiRenderer) = 0;

};
