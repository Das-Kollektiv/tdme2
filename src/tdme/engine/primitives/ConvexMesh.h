// Generated from /tdme/src/tdme/engine/primitives/ConvexMesh.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingVolume.h>

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
	vector<Vector3*> vertexReferences {  };
	Vector3 center {  };
	float sphereRadius {  };

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
	 */
	static void createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes);

	/** 
	 * @return triangles
	 */
	vector<Triangle>* getTriangles();

	/** 
	 * @return mesh vertices
	 */
	vector<Vector3>* getVertices();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestsPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;

	/**
	 * Public constructor
	 * @param triangles
	 */
	ConvexMesh(vector<Triangle>* triangles);

	/**
	 * Public constructor
	 * @param model
	 */
	ConvexMesh(Object3DModel* model);
};
