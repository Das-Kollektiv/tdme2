// Generated from /tdme/src/tdme/engine/primitives/Triangle.java

#pragma once

#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using std::vector;

using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Triangle primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Triangle final
	: public BoundingVolume
{
public:

	/** 
	 * @return triangle vertices
	 */
	vector<Vector3>* getVertices();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	Vector3* getCenter() override;
	float getSphereRadius() override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;

	/**
	 * Public constructor
	 * @param vertex 0
	 * @param vertex 1
	 * @param vertex 2
	 */
	Triangle(Vector3* vertex0, Vector3* vertex1, Vector3* vertex2);

private:
	vector<Vector3> vertices {  };
	Vector3 center {  };
	Vector3 distanceVector {  };
	float sphereRadius {  };
};
