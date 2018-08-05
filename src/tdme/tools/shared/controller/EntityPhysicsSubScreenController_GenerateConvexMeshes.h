#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/tools/shared/model/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::Triangle;
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
	static Model* createModel(const string& id, vector<Triangle>& triangles);

	EntityPhysicsSubScreenController* entityPhysicsSubScreenController;
	LevelEditorEntity* entityFinal;
};
