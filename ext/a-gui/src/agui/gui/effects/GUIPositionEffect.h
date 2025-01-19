#pragma once

#include <agui/agui.h>
#include <agui/gui/effects/fwd-agui.h>
#include <agui/gui/effects/GUIEffect.h>
#include <agui/gui/effects/GUIEffectState.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/gui/fwd-agui.h>

// namespaces
namespace agui {
namespace gui {
namespace effects {
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::renderer::GUIRenderer;
	using ::agui::gui::GUI;
}
}
}

/**
 * GUI position effect
 * @author Andreas Drewke
 */
class agui::gui::effects::GUIPositionEffect final: public GUIEffect
{

public:
	/**
	 * Reset effect state regarding position effect
	 * @param effectState effect state
	 */
	inline static void resetEffectState(GUIEffectState* effectState) {
		effectState->positionX = 0.0f;
		effectState->positionY = 0.0f;
	}

	// forbid class copy
	FORBID_CLASS_COPY(GUIPositionEffect)

	/**
	 *  Public constructor
	 *  @param guiNode GUI node
	 */
	GUIPositionEffect(GUINode* guiNode);

	/**
	 * @return position X
	 */
	inline float getPositionX() const {
		return originalEndState.positionX;
	}

	/**
	 * Set position X
	 * @param positionX position X
	 */
	inline void setPositionX(float positionX) {
		originalEndState.positionX = positionX;
	}

	/**
	 * @return position Y
	 */
	inline float getPositionY() const {
		return originalEndState.positionY;
	}

	/**
	 * Set position Y
	 * @param positionX position Y
	 */
	inline void setPositionY(float positionY) {
		originalEndState.positionY = positionY;
	}

	/**
	 * @return start position X
	 */
	inline float getStartPositionX() const {
		return originalStartState.positionX;
	}

	/**
	 * Set start position X
	 * @param positionX start position X
	 */
	inline void setStartPositionX(float positionX) {
		originalStartState.positionX = positionX;
	}

	/**
	 * @return start position Y
	 */
	inline float getStartPositionY() const {
		return originalStartState.positionY;
	}

	/**
	 * Set start position Y
	 * @param positionX start position Y
	 */
	inline void setStartPositionY(float positionY) {
		originalStartState.positionY = positionY;
	}

	// overridden methods
	void apply(GUI* gui) override;

};
