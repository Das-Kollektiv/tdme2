// Generated from /tdme/src/tdme/engine/primitives/Sphere.java

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
	Vector3* getCenter() override;

	/** 
	 * @return float radius
	 */
	float getRadius();
	float getSphereRadius() override;

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
	Sphere* set(Vector3* center, float radius);
	void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint) override;
	bool containsPoint(Vector3* point) override;
	bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) override;
	float computeDimensionOnAxis(Vector3* axis) override;
	void update() override;
	BoundingVolume* clone() override;

	/**
	 * Public constructor
	 */
	Sphere();

	/**
	 * Public constructor
	 * @param center
	 * @param radius
	 */
	Sphere(Vector3* center, float radius);
};
