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
public:
	static constexpr int DISPLAY_BOUNDINGVOLUMEIDX_ALL { -1 };
private:
	Engine* engine { nullptr };
	EntityDisplaySubScreenController* entityDisplaySubScreenController { nullptr };
	bool displayGroundPlate;
	bool displayShadowing;
	bool displayBoundingVolume;
	int displayBoundingVolumeIdx;

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
	 * @return display bounding volume
	 */
	inline virtual bool isDisplayBoundingVolume() {
		return displayBoundingVolume;
	}

	/** 
	 * Set up bounding volume visibility
	 * @param displayBoundingVolume bounding volume
	 */
	inline virtual void setDisplayBoundingVolume(bool displayBoundingVolume) {
		this->displayBoundingVolume = displayBoundingVolume;
	}

	/**
	 * @return bounding volume index to display or DISPLAY_BOUNDINGVOLUMEIDX_ALL
	 */
	inline int getDisplayBoundingVolumeIdx() const {
		return displayBoundingVolumeIdx;
	}

	/**
	 * Set display bounding volume idx
	 * @param displayBoundingVolumeIdx display bounding volume index or DISPLAY_BOUNDINGVOLUMEIDX_ALL
	 */
	inline void setDisplayBoundingVolumeIdx(int displayBoundingVolumeIdx) {
		this->displayBoundingVolumeIdx = displayBoundingVolumeIdx;
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
