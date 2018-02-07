#pragma once

#include <ext/reactphysics3d/src/collision/shapes/AABB.h>
#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>

using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingBox;
using tdme::math::Vector3;

/** 
 * Bounding Volume Interface
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::primitives::BoundingVolume
{
	friend class tdme::engine::physics::RigidBody;
	friend class tdme::engine::physics::World;
	friend class BoundingBox;
	friend class Capsule;
	friend class ConvexMesh;
	friend class OrientedBoundingBox;
	friend class Sphere;
	friend class PrimitiveModel;

protected:
	Vector3 center {  };
	Vector3 collisionShapeLocalTranslation {  };
	reactphysics3d::CollisionShape* collisionShape {  };
	reactphysics3d::Transform collisionShapeLocalTransform {  };
	reactphysics3d::Transform collisionShapeTransform {  };
	reactphysics3d::AABB collisionShapeAABB {  };
	BoundingBox boundingBoxTransformed {  };
	Vector3 centerTransformed {  };

	/**
	 * Compute bounding box
	 */
	void computeBoundingBox();

public:

	/** 
	 * Transform bounding volume from given transformations
	 * @param transformations
	 */
	virtual void fromTransformations(Transformations* transformations);

	/** 
	 * Checks if point is in bounding volume
	 * @param point
	 * @return bool if point is in bounding volume
	 */
	virtual bool containsPoint(const Vector3& point);

	/** 
	 * Check if this bounding volume collides with bounding volume 2
	 * @deprecated this method is deprecated, please try to avoid it
	 * @param bounding volume 2
	 * @param movement
	 * @param collision
	 * @return collision
	 */
	bool doesCollideWith(BoundingVolume* bv2, CollisionResponse* collision);

	/**
	 * @return center
	 */
	const Vector3& getCenter() const;

	/**
	 * @return transformed center
	 */
	const Vector3& getCenterTransformed() const;

	/** 
	 * Get bounding box transformed
	 * @return bounding box
	 */
	const BoundingBox& getBoundingBoxTransformed() const;

	/** 
	 * Clones this bounding volume
	 * @return cloned bounding volume
	 */
	virtual BoundingVolume* clone() const = 0;

	/**
	 * Destructor
	 */
	virtual ~BoundingVolume();
};
