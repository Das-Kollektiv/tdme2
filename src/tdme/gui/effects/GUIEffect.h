#pragma once

#include <tdme/tdme.h>
#include <tdme/gui/effects/fwd-tdme.h>
#include <tdme/gui/events/fwd-tdme.h>
#include <tdme/gui/renderer/fwd-tdme.h>

using tdme::gui::events::Action;
using tdme::gui::renderer::GUIRenderer;

/** 
 * GUI Effect base class
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::gui::effects::GUIEffect
{

protected:
	bool active {  };
	float timeTotal {  };
	float timeLeft {  };
	float timePassed {  };
	Action* action {  };

public:

	/** 
	 * @return active
	 */
	inline virtual bool isActive() const {
		return active;
	}

	/** 
	 * @return time total
	 */
	inline virtual float getTimeTotal() const {
		return timeTotal;
	}

	/** 
	 * Set time total
	 * @param timeTotal time total
	 */
	inline virtual void setTimeTotal(float timeTotal) {
		this->timeTotal = timeTotal;
	}

	/** 
	 * @return action to be performed on effect end
	 */
	inline virtual Action* getAction() const {
		return action;
	}

	/** 
	 * Set action to be performed on effect end
	 * @param action action
	 */
	inline virtual void setAction(Action* action) {
		this->action = action;
	}

	/** 
	 * Start this effect
	 */
	virtual void start();

	/** 
	 * Updates the effect to GUI renderer and updates time
	 * @param guiRenderer gui renderer
	 */
	virtual void update(GUIRenderer* guiRenderer);

	/** 
	 * Apply effect
	 * @param guiRenderer GUI renderer
	 */
	virtual void apply(GUIRenderer* guiRenderer) = 0;

	/**
	 * Public constructor
	 */
	GUIEffect();

	/**
	 * Destructor
	 */
	virtual ~GUIEffect();

};
