#pragma once

#include <fwd-tdme.h>
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
	virtual float getPositionXStart();

	/** 
	 * Set position X start
	 * @param position X start
	 */
	virtual void setPositionXStart(float positionXStart);

	/** 
	 * @return position X end
	 */
	virtual float getPositionXEnd();

	/** 
	 * Set position X end
	 * @param position X end
	 */
	virtual void setPositionXEnd(float positionXEnd);

	/** 
	 * @return position Y start
	 */
	virtual float getPositionYStart();

	/** 
	 * Set position Y start
	 * @param position Y start
	 */
	virtual void setPositionYStart(float positionYStart);

	/** 
	 * @return get position Y end
	 */
	virtual float getPositionYEnd();

	/** 
	 * Set position Y end
	 * @param position Y end
	 */
	virtual void setPositionYEnd(float positionYEnd);
	void apply(GUIRenderer* guiRenderer) override;

	GUIPositionEffect();

private:
	void init();
};
