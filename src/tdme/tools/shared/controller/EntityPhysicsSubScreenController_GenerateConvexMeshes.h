#pragma once

#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/model/fwd-tdme.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/tools/shared/controller/fwd-tdme.h>
#include <tdme/engine/prototype/fwd-tdme.h>

using std::string;
using std::vector;

using tdme::engine::model::Model;
using tdme::engine::primitives::Triangle;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController_BoundingVolumeType;
using tdme::tools::shared::controller::EntityPhysicsSubScreenController;
using tdme::engine::prototype::Prototype;

class tdme::tools::shared::controller::EntityPhysicsSubScreenController_GenerateConvexMeshes
{
	friend class EntityPhysicsSubScreenController;
	friend class EntityPhysicsSubScreenController_BoundingVolumeType;

public:
	/**
	 * Remove convex meshes
	 * @param entityPhysicsSubScreenController entity physics sub screen controller
	 * @param entityFinal entity final
	 */
	static void removeConvexMeshes(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, Prototype* entityFinal);

	/**
	 * Generateconvex meshes
	 * @param entityPhysicsSubScreenController entity physics sub screen controller
	 * @param entityFinal entity final
	 */
	static void generateConvexMeshes(EntityPhysicsSubScreenController* entityPhysicsSubScreenController, Prototype* entityFinal);

private:

	/**
	 * Create model
	 * @param id id
	 * @param points points
	 * @param triangles triangles
	 * @param pointCount point count
	 * @param triangleCount triangle count
	 */
	static Model* createModel(const string& id, double* points, unsigned int* triangles, unsigned int pointCount, unsigned int triangleCount);

	/**
	 * Create model
	 * @param id id
	 * @param triangles triangles
	 */
	static Model* createModel(const string& id, vector<Triangle>& triangles);

	EntityPhysicsSubScreenController* entityPhysicsSubScreenController;
	Prototype* entityFinal;
};
