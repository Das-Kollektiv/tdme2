
#pragma once

#include <tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>
#include <tdme/gui/events/GUIInputEventHandler.h>

using tdme::gui::events::GUIInputEventHandler;
using tdme::engine::Engine;
using tdme::engine::Transformations;

/** 
 * Camera Rotation View
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::CameraRotationInputHandler
	: public virtual GUIInputEventHandler
{
private:
	Engine* engine {  };
	bool mouseDragging {  };
	bool keyLeft {  };
	bool keyRight {  };
	bool keyUp {  };
	bool keyDown {  };
	bool keyPeriod {  };
	bool keyComma {  };
	bool keyPlus {  };
	bool keyMinus {  };
	bool keyR {  };
	int32_t mouseLastX {  };
	int32_t mouseLastY {  };
	float maxAxisDimension {  };
	Transformations* lookFromRotations {  };
	float scale {  };
	bool resetRequested {  };

public:

	/** 
	 * @return max dimension on one of x,y,z axis
	 */
	virtual float getMaxAxisDimension();

	/** 
	 * Set max dimension on one of x,y,z axis
	 * @param max axis dimension
	 */
	virtual void setMaxAxisDimension(float maxAxisDimension);

	/** 
	 * @return look from rotation
	 */
	virtual Transformations* getLookFromRotations();

	/** 
	 * @return scale
	 */
	virtual float getScale();

	/** 
	 * Set scale
	 * @param scale
	 */
	virtual void setScale(float scale);

	/** 
	 * Reset
	 */
	virtual void reset();
	void handleInputEvents() override;

	/**
	 * Public constructor
	 */
	CameraRotationInputHandler(Engine* engine);

	/**
	 * Destructor
	 */
	~CameraRotationInputHandler();
};
