#pragma once

#include <vector>

#include <reactphysics3d/collision/TriangleMesh.h>
#include <reactphysics3d/collision/TriangleVertexArray.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/Transform.h>

using std::vector;

using tdme::engine::physics::World;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::primitives::Triangle;
using tdme::engine::ObjectModel;
using tdme::engine::Transform;

/**
 * Terrain mesh physics primitive
 * @author Andreas Drewke
 */
class tdme::engine::primitives::TerrainMesh final
	: public BoundingVolume
{
private:
	vector<float> vertices;
	vector<int32_t> indices;
	reactphysics3d::TriangleVertexArray* triangleVertexArray { nullptr };
	reactphysics3d::TriangleMesh* triangleMesh { nullptr };

	// overriden methods
	void createCollisionShape(World* world) override;

public:
	/**
	 * Public constructor
	 */
	TerrainMesh();

	/**
	 * Public constructor
	 * @param model model
	 * @param transform transform
	 */
	TerrainMesh(ObjectModel* model, const Transform& transform = Transform());

	/**
	 * Destructor
	 */
	~TerrainMesh();

	// overrides
	void setScale(const Vector3& scale) override;
	void setTransform(const Transform& transform) override;
	BoundingVolume* clone() const override;
};
