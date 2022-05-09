#pragma once

#include <vector>

#include <ext/reactphysics3d/src/collision/TriangleMesh.h>
#include <ext/reactphysics3d/src/collision/TriangleVertexArray.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/Transform.h>

using std::vector;

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
