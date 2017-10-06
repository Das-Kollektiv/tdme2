
#pragma once

#include <fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1
	: public virtual Action
{
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_BoundingVolumeType;

public:
	void performAction() override;

	// Generated
	EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshFile_1(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, int32_t idxFinal, LevelEditorEntity* entityFinal);

private:
	EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController;
	int32_t idxFinal;
	LevelEditorEntity* entityFinal;
};
