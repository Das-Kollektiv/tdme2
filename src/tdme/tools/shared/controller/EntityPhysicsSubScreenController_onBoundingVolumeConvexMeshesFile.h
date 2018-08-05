#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>
#include <tdme/gui/events/Action.h>

using std::string;

using tdme::engine::model::Model;
using tdme::gui::events::Action;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile
	: public virtual Action
{
	friend class EntityPhysicsSubScreenController;
	friend class EntityPhysicsSubScreenController_BoundingVolumeType;

public:
	void performAction() override;
	EntityPhysicsSubScreenController_onBoundingVolumeConvexMeshesFile(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, LevelEditorEntity* entityFinal);

private:
	EntityPhysicsSubScreenController* entityPhysicsSubScreenController;
	LevelEditorEntity* entityFinal;
};
