
#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/engine/primitives/BoundingVolume.h>

using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Capsule primitive
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Capsule final
	: public BoundingVolume
{
public:
	/** 
	 * @return radius
	 */
	float getRadius() const;

	/** 
	 * Set up radius
	 * @param radius
	 */
	void setRadius(float radius);

	/** 
	 * @return line segment point a
	 */
	Vector3& getA();

	/** 
	 * @return line segment point b
	 */
	Vector3& getB();
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;
	void update() override;

	inline Vector3& getCenter() override {
		return center;
	}

	inline float getSphereRadius() const override {
		return sphereRadius;
	}

	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const override;
	bool containsPoint(const Vector3& point) const override;
	bool doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(const Vector3& axis) const override;
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 * @param a
	 * @param b
	 * @param radius
	 */
	Capsule(const Vector3& a, const Vector3& b, float radius);

private:
	Vector3 a {  };
	Vector3 b {  };
	float radius {  };
	Vector3 center {  };
	float sphereRadius {  };

};
