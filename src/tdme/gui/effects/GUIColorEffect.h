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

private:
	GUIColor colorAddStart { 0.0f, 0.0f, 0.0f, 0.0f };
	GUIColor colorAddEnd { 0.0f, 0.0f, 0.0f, 0.0f };
	GUIColor colorMulStart { 1.0f, 1.0f, 1.0f, 1.0f };
	GUIColor colorMulEnd { 1.0f, 1.0f, 1.0f, 1.0f };

public:
	/**
	 * Public constructor
	 */
	GUIColorEffect();

	/**
	 * @return color add
	 */
	inline virtual const GUIColor& getColorAdd() const {
		return colorAddEnd;
	}

	/**
	 * Set color add
	 * @param colorAdd color add
	 */
	inline virtual void setColorAdd(const GUIColor& colorAdd) {
		this->colorAddEnd = colorAdd;
	}

	/**
	 * @return color mul
	 */
	inline virtual const GUIColor& getColorMul() const {
		return colorMulEnd;
	}

	/**
	 * Set color mul
	 * @param colorMul color mul
	 */
	inline virtual void setColorMul(const GUIColor& colorMul) {
		this->colorMulEnd = colorMul;
	}

	// overridden methods
	void applyState(const EffectState& state) override;
	void apply(GUIRenderer* guiRenderer) override;

};
