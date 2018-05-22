#pragma once

#include <vector>

#include <ext/reactphysics3d/src/collision/TriangleMesh.h>
#include <ext/reactphysics3d/src/collision/TriangleVertexArray.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>

using std::vector;

using tdme::engine::primitives::TerrainMesh;
using tdme::engine::primitives::Triangle;
using tdme::engine::Object3DModel;

/** 
 * Terrain mesh collision object
 * @author Andreas Drewke
 * @version $Id$
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
	 * @param model
	 * @param scale
	 */
	TerrainMesh(Object3DModel* model, const Vector3& scale = Vector3(1.0f, 1.0f, 1.0f));

	/**
	 * Destructor
	 */
	~TerrainMesh();

	// overrides
	bool setScale(const Vector3& scale) override;
	BoundingVolume* clone() const override;
};
