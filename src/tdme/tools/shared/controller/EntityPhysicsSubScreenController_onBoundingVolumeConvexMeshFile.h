#pragma once

#include <tdme/tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::events::Action;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile
	: public virtual Action
{
	friend class EntityPhysicsSubScreenController;
	friend class EntityPhysicsSubScreenController_BoundingVolumeType;

public:
	void performAction() override;

	// Generated
	EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshFile(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, int32_t idxFinal, LevelEditorEntity* entityFinal);

private:
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController;
	int32_t idxFinal;
	LevelEditorEntity* entityFinal;
};
