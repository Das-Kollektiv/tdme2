#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>
#include <tdme/gui/effects/GUIEffect.h>

using tdme::gui::effects::GUIEffect;
using tdme::gui::renderer::GUIRenderer;

/** 
 * GUI position effect
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIPositionEffect
	: public GUIEffect
{

private:
	float positionXStart {  };
	float positionXEnd {  };
	float positionYStart {  };
	float positionYEnd {  };
	float positionX {  };
	float positionY {  };

public:

	/** 
	 * @return position X start
	 */
	inline virtual float getPositionXStart() const {
		return positionXStart;
	}

	/** 
	 * Set position X start
	 * @param position X start
	 */
	inline virtual void setPositionXStart(float positionXStart) {
		this->positionXStart = positionXStart;
	}

	/** 
	 * @return position X end
	 */
	inline virtual float getPositionXEnd() const {
		return positionXEnd;
	}

	/** 
	 * Set position X end
	 * @param position X end
	 */
	inline virtual void setPositionXEnd(float positionXEnd) {
		this->positionXEnd = positionXEnd;
	}

	/** 
	 * @return position Y start
	 */
	inline virtual float getPositionYStart() const {
		return positionYStart;
	}

	/** 
	 * Set position Y start
	 * @param position Y start
	 */
	inline virtual void setPositionYStart(float positionYStart) {
		this->positionYStart = positionYStart;
	}

	/** 
	 * @return get position Y end
	 */
	inline virtual float getPositionYEnd() const {
		return positionYEnd;
	}

	/** 
	 * Set position Y end
	 * @param position Y end
	 */
	inline virtual void setPositionYEnd(float positionYEnd) {
		this->positionYEnd = positionYEnd;
	}

	// override methods
	void apply(GUIRenderer* guiRenderer) override;

	// Public constructor
	GUIPositionEffect();

private:
	/**
	 * Init
	 */
	void init();
};
