#pragma once

#include <array>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::array;
using std::vector;

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
	float sphereRadius {  };
	bool terrain {  };
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
	 * @param height
	 */
	static void createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes, float height = 0.75f);

	/**
	 * @return is terrain
	 */
	bool isTerrain();

	/** 
	 * @return triangles
	 */
	vector<Triangle>* getTriangles();

	/** 
	 * @return mesh vertices
	 */
	inline const vector<Vector3>* getVertices() const {
		return &vertices;
	}

	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestsPoint) const override;
	bool containsPoint(const Vector3& point) const override;
	bool doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision) override;

	inline Vector3& getCenter() override {
		return center;
	}

	float getSphereRadius() const override {
		return sphereRadius;
	}

	float computeDimensionOnAxis(const Vector3& axis) const override;
	void update() override;
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 */
	ConvexMesh();

	/**
	 * Public constructor
	 * @param triangles
	 * @param is terrain
	 */
	ConvexMesh(const vector<Triangle>* triangles, bool terrain = false);

	/**
	 * Public constructor
	 * @param model
	 * @param is terrain
	 */
	ConvexMesh(Object3DModel* model, bool terrain = false);
};
