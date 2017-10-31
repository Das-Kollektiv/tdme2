
#pragma once

#include <tdme/tdme.h>
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
 * Sphere
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::Sphere final
	: public BoundingVolume
{
private:
	Vector3 center {  };
	float radius {  };

public:
	void fromBoundingVolume(BoundingVolume* original) override;
	void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) override;

	inline Vector3& getCenter() override {
		return center;
	}

	/** 
	 * @return float radius
	 */
	float getRadius() const;

	inline float getSphereRadius() const override {
		return radius;
	}

	/** 
	 * Set up radius
	 * @param radius
	 */
	void setRadius(float radius);

	/** 
	 * Set up sphere
	 * @param center
	 * @param radius
	 * @return this sphere
	 */
	Sphere* set(const Vector3& center, float radius);
	void computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const override;
	bool containsPoint(const Vector3& point) const override;
	bool doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(const Vector3& axis) const override;
	void update() override;
	BoundingVolume* clone() const override;

	/**
	 * Public constructor
	 */
	Sphere();

	/**
	 * Public constructor
	 * @param center
	 * @param radius
	 */
	Sphere(const Vector3& center, float radius);
};
