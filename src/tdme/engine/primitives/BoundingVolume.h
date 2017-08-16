// Generated from /tdme/src/tdme/engine/primitives/BoundingVolume.java

#pragma once

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::math::Vector3;

/** 
 * Bounding Volume Interface
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::primitives::BoundingVolume
{

	/** 
	 * Set up this bounding volume from given bounding volume
	 * @param original
	 */
	virtual void fromBoundingVolume(BoundingVolume* original) = 0;

	/** 
	 * Create bounding volume from given original(of same type) with applied transformations
	 * @param original bounding volume
	 * @param transformations
	 */
	virtual void fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations) = 0;

	/** 
	 * Computes closest point on bounding volume for given point 
	 * @param point
	 * @param clostest point
	 */
	virtual void computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestsPoint) = 0;

	/** 
	 * Checks if point is in bounding volume
	 * @param point
	 * @return bool if point is in bounding volume
	 */
	virtual bool containsPoint(Vector3* point) = 0;

	/** 
	 * Check if this bounding volume collides with bounding volume 2
	 * @param bounding volume 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	virtual bool doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision) = 0;

	/** 
	 * @return center of bounding volume
	 */
	virtual Vector3* getCenter() = 0;

	/** 
	 * @return radius of bounding volume if regarded as sphere
	 */
	virtual float getSphereRadius() = 0;

	/** 
	 * Computes dimension on axis
	 * @param axis
	 * @return dimension on axis
	 */
	virtual float computeDimensionOnAxis(Vector3* axis) = 0;

	/** 
	 * Updates the bounding volume
	 */
	virtual void update() = 0;

	/** 
	 * Clones this bounding volume
	 * @return cloned bounding volume
	 */
	virtual BoundingVolume* clone() = 0;
};
