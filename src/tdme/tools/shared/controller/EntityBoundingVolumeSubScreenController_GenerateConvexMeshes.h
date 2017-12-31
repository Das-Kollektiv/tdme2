#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::model::Model;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityBoundingVolumeSubScreenController_GenerateConvexMeshes
{
	friend class EntityBoundingVolumeSubScreenController;
	friend class EntityBoundingVolumeSubScreenController_BoundingVolumeType;

public:
	static void removeConvexMeshes(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, LevelEditorEntity* entityFinal);
	static void generateConvexMeshes(EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController, LevelEditorEntity* entityFinal);

private:
	static Model* createModel(const string& id, double* points, uint32_t* triangles, uint32_t pointCount, uint32_t triangleCount);

	EntityBoundingVolumeSubScreenController* entityBoundingVolumeSubScreenController;
	LevelEditorEntity* entityFinal;
};
