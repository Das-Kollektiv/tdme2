#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::array;
using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::Triangle;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::Vector3;

/** 
 * Convex mesh collision object
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::ConvexMesh final
	: public BoundingVolume
{
private:
	vector<Triangle> triangles {  };
	vector<Vector3> vertices {  };
	vector<array<int32_t, 2>> vertexReferences {  };
	Vector3 center {  };
	BoundingBox boundingBox;
	bool terrain {  };
	float terrainHeight {  };
private:

	/** 
	 * Create vertices
	 */
	void createVertices();

public:

	/**
	 * Create terrain convex meshes
	 * @param model
	 * @param convex meshes
	 * @param terrain height
	 */
	static void createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes, float terrainHeight = 0.75f);

	/**
	 * @return is terrain
	 */
	inline bool isTerrain() {
		return terrain;
	}

	/** 
	 * @return triangles
	 */
	inline vector<Triangle>* getTriangles() {
		return &triangles;
	}

	/** 
	 * @return mesh vertices
	 */
	inline const vector<Vector3>* getVertices() const {
		return &vertices;
	}

	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, const Transformations& transformations) override;
	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestsPoint) const override;
	bool containsPoint(const Vector3& point) const override;
	bool doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision) override;

	inline Vector3& getCenter() override {
		return center;
	}

	inline virtual BoundingBox* getBoundingBox() override {
		return &boundingBox;
	}

	float computeDimensionOnAxis(const Vector3& axis) const override;
	void update() override;
	BoundingVolume* clone() const override;

	inline const Vector3& getTerrainNormal() {
		return triangles[0].getNormal();
	}

	/**
	 * Public constructor
	 */
	ConvexMesh();

	/**
	 * Public constructor
	 * @param triangles
	 * @param is terrain
	 * @param terrain height
	 */
	ConvexMesh(const vector<Triangle>* triangles, bool terrain = false, float terrainHeight = 0.0f);

	/**
	 * Public constructor
	 * @param model
	 * @param is terrain
	 * @param terrain height
	 */
	ConvexMesh(Object3DModel* model, bool terrain = false, float terrainHeight = 0.0f);
};
