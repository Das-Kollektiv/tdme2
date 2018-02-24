
#pragma once

#include <vector>

#include <tdme/tdme.h>
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
	inline vector<Vector3>* getVertices() {
		return &vertices;
	}

	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, const Transformations& transformations) override;
	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const override;
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
	Triangle();

	/**
	 * Public constructor
	 * @param vertex 0
	 * @param vertex 1
	 * @param vertex 2
	 */
	Triangle(const Vector3& vertex0, const Vector3& vertex1, const Vector3& vertex2);

private:
	vector<Vector3> vertices {  };
	Vector3 center {  };
	Vector3 distanceVector {  };
	float sphereRadius {  };
};
