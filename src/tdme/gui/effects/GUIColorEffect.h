#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>
#include <tdme/gui/effects/GUIEffectState.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::effects::GUIEffectState;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUINode;
using tdme::gui::renderer::GUIRenderer;

/**
 * GUI color effect
 * @author Andreas Drewke
 */
class tdme::gui::effects::GUIColorEffect final: public GUIEffect
{
public:
	/**
	 * Reset effect state regarding color effect
	 * @param effectState effect state
	 */
	inline static void resetEffectState(GUIEffectState* effectState) {
		effectState->colorAdd.set(0.0f, 0.0f, 0.0f, 0.0f);
		effectState->colorMul.set(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// forbid class copy
	FORBID_CLASS_COPY(GUIColorEffect)

	/**
	 * Public constructor
	 * @param guiNode GUI node
	 */
	GUIColorEffect(GUINode* guiNode);

	/**
	 * @return color add
	 */
	inline const GUIColor& getColorAdd() const {
		return originalEndState.colorAdd;
	}

	/**
	 * Set color add
	 * @param colorAdd color add
	 */
	inline void setColorAdd(const GUIColor& colorAdd) {
		originalEndState.colorAdd = colorAdd;
	}

	/**
	 * @return color mul
	 */
	inline const GUIColor& getColorMul() const {
		return originalEndState.colorMul;
	}

	/**
	 * Set color mul
	 * @param colorMul color mul
	 */
	inline void setColorMul(const GUIColor& colorMul) {
		originalEndState.colorMul = colorMul;
	}

	/**
	 * @return start color add
	 */
	inline const GUIColor& getStartColorAdd() const {
		return originalStartState.colorAdd;
	}

	/**
	 * Set start color add
	 * @param colorAdd start color add
	 */
	inline void setStartColorAdd(const GUIColor& colorAdd) {
		originalStartState.colorAdd = colorAdd;
	}

	/**
	 * @return start color mul
	 */
	inline const GUIColor& getStartColorMul() const {
		return originalStartState.colorMul;
	}

	/**
	 * Set start color mul
	 * @param colorMul start color mul
	 */
	inline void setStartColorMul(const GUIColor& colorMul) {
		originalStartState.colorMul = colorMul;
	}

	// overridden methods
	void apply(GUIRenderer* guiRenderer) override;

};
