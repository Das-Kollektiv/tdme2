#pragma once

#include <string>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;

using tdme::engine::model::Model;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::tools::shared::model::LevelEditorEntity;

class tdme::tools::shared::controller::EntityPhysicsSubScreenController_GenerateConvexMeshes
{
	friend class EntityPhysicsSubScreenController;
	friend class EntityPhysicsSubScreenController_BoundingVolumeType;

public:
	static void removeConvexMeshes(EntityPhysicsSubScreenController* EntityPhysicsSubScreenController, LevelEditorEntity* entityFinal);
	static void generateConvexMeshes(EntityPhysicsSubScreenController* EntityPhysicsSubScreenController, LevelEditorEntity* entityFinal);

private:
	static Model* createModel(const string& id, double* points, uint32_t* triangles, uint32_t pointCount, uint32_t triangleCount);

	EntityPhysicsSubScreenController* entityPhysicsSubScreenController;
	LevelEditorEntity* entityFinal;
};
