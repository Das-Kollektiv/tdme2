#pragma once

#include <reactphysics3d/collision/shapes/AABB.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/mathematics/Transform.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/fwd-tdme.h>

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::Transform;
using tdme::math::Vector3;

/**
 * Bounding volume interface
 * @author Andreas Drewke
 */
class tdme::engine::primitives::BoundingVolume
{
	friend class Capsule;
	friend class ConvexMesh;
	friend class OrientedBoundingBox;
	friend class Sphere;
	friend class tdme::engine::physics::Body;
	friend class tdme::engine::physics::BodyHierarchy;
	friend class tdme::engine::physics::World;
	friend class tdme::utilities::Primitives;

protected:
	World* world { nullptr };
	Vector3 scale;
	Vector3 center;
	Vector3 collisionShapeLocalTranslation;
	reactphysics3d::CollisionShape* collisionShape { nullptr };
	reactphysics3d::Transform collisionShapeLocalTransform;
	reactphysics3d::Transform collisionShapeTransform;

	/**
	 * Destroy collision shape
	 */
	virtual void destroyCollisionShape() = 0;

	/**
	 * Create collision shap
	 */
	virtual void createCollisionShape(World* world) = 0;

	/**
	 * @return is attached to world
	 */
	inline bool isAttachedToWorld() {
		return world != nullptr;
	}

public:
	/**
	 * Destructor
	 */
	virtual ~BoundingVolume();

	/**
	 * Transform bounding volume from given transform
	 * @param transform transform
	 */
	virtual void setTransform(const Transform& transform);

	/**
	 * Get local scale
	 * @return scale
	 */
	const Vector3& getScale();

	/**
	 * Set local scale
	 * @return if collision shape had been recreated
	 */
	virtual void setScale(const Vector3& scale) = 0;

	/**
	 * @return center
	 */
	const Vector3& getCenter() const;

	/**
	 * Clones this bounding volume
	 * @return cloned bounding volume
	 */
	virtual BoundingVolume* clone() const = 0;

};
