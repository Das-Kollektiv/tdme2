#pragma once

#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>
#include <tdme/gui/nodes/fwd-tdme.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;

/**
 * GUI color effect
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIColorEffect final: public GUIEffect
{
public:
	/**
	 * Public constructor
	 */
	GUIColorEffect();

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
	void applyState(const EffectState& state) override;
	void apply(GUIRenderer* guiRenderer) override;

};
