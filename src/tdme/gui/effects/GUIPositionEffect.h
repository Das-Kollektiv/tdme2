#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::renderer::GUIRenderer;

/**
 * GUI position effect
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIPositionEffect final: public GUIEffect
{

private:
	float positionXStart{ 0.0f };
	float positionYStart { 0.0f };
	float positionXEnd { 0.0f };
	float positionYEnd { 0.0f };

public:
	/**
	 *  Public constructor
	 */
	GUIPositionEffect();

	/**
	 * @return position X
	 */
	inline virtual float getPositionX() const {
		return positionXEnd;
	}

	/**
	 * Set position X
	 * @param positionX position X
	 */
	inline virtual void setPositionX(float positionX) {
		this->positionXEnd = positionX;
	}

	/**
	 * @return position Y
	 */
	inline virtual float getPositionY() const {
		return positionYEnd;
	}

	/**
	 * Set position Y
	 * @param positionX position Y
	 */
	inline virtual void setPositionY(float positionY) {
		this->positionYEnd = positionY;
	}

	// override methods
	void applyState(const EffectState& state) override;
	void apply(GUIRenderer* guiRenderer) override;

};
