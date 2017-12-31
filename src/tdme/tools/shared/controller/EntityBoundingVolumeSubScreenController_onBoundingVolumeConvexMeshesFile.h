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
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile
	: public virtual Action
{
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_BoundingVolumeType;

public:
	void performAction() override;
	EntityBoundingVolumeSubScreenController_onBoundingVolumeConvexMeshesFile(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, LevelEditorEntity* entityFinal);

private:
	Model* createModel(const string& id, double* points, uint32_t* triangles, uint32_t pointCount, uint32_t triangleCount);

	EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController;
	LevelEditorEntity* entityFinal;
};
