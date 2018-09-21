
#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/tools/shared/views/fwd-tdme.h>

using std::vector;
using std::string;


using tdme::engine::Engine;
using tdme::tools::shared::controller::EntityDisplaySubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

/** 
 * Entity display view
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::tools::shared::views::EntityDisplayView
{
private:
	Engine* engine {  };
	EntityDisplaySubScreenController* entityDisplaySubScreenController {  };
	bool displayGroundPlate {  };
	bool displayShadowing {  };
	bool displayBoundingVolume {  };

public:
	/** 
	 * @return display ground plate
	 */
	virtual bool isDisplayGroundPlate();

	/** 
	 * Set up ground plate visibility
	 * @param groundPlate ground plate visible
	 */
	virtual void setDisplayGroundPlate(bool groundPlate);

	/** 
	 * @return display shadowing
	 */
	virtual bool isDisplayShadowing();

	/** 
	 * Set up shadow rendering
	 * @param shadowing shadow rendering
	 */
	virtual void setDisplayShadowing(bool shadowing);

	/** 
	 * @return display bounding volume
	 */
	virtual bool isDisplayBoundingVolume();

	/** 
	 * Set up bounding volume visibility
	 * @param displayBoundingVolume bounding volume
	 */
	virtual void setDisplayBoundingVolume(bool displayBoundingVolume);

	/** 
	 * Display
	 * @param entity entity
	 */
	virtual void display(LevelEditorEntity* entity);

	/**
	 * Public constructor
	 * @param entityDisplaySubScreenController entity display sub screen controller
	 */
	EntityDisplayView(EntityDisplaySubScreenController* entityDisplaySubScreenController);
};
