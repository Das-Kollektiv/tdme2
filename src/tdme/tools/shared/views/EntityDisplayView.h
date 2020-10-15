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
	Engine* engine { nullptr };
	EntityDisplaySubScreenController* entityDisplaySubScreenController { nullptr };
	bool displayGroundPlate;
	bool displayShadowing;

public:
	/**
	 * @return display ground plate
	 */
	inline virtual bool isDisplayGroundPlate() {
		return this->displayGroundPlate;
	}

	/**
	 * Set up ground plate visibility
	 * @param groundPlate ground plate visible
	 */
	inline virtual void setDisplayGroundPlate(bool groundPlate) {
		this->displayGroundPlate = groundPlate;
	}

	/**
	 * @return display shadowing
	 */
	inline virtual bool isDisplayShadowing() {
		return displayShadowing;
	}

	/**
	 * Set up shadow rendering
	 * @param shadowing shadow rendering
	 */
	inline virtual void setDisplayShadowing(bool shadowing) {
		this->displayShadowing = shadowing;
	}

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

	/**
	 * Destructor
	 */
	virtual ~EntityDisplayView();

};
