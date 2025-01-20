#include <tdme/engine/primitives/BoundingVolume.h>

#include <string>

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/collision/narrowphase/CollisionDispatch.h>
#include <reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/collision/CollisionCallback.h>
#include <reactphysics3d/constraint/ContactPoint.h>
#include <reactphysics3d/engine/OverlappingPairs.h>
#include <reactphysics3d/engine/PhysicsWorld.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/memory/MemoryAllocator.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;
using tdme::math::Vector3;

BoundingVolume::~BoundingVolume() {
}

void BoundingVolume::setTransform(const Transform& transform) {
	//
	setScale(transform.getScale());

	// set transform
	collisionShapeTransform.setPosition(
		reactphysics3d::Vector3(
			transform.getTranslation().getX(),
			transform.getTranslation().getY(),
			transform.getTranslation().getZ()
		)
	);
	collisionShapeTransform.setOrientation(
		reactphysics3d::Quaternion(
			transform.getRotationsQuaternion().getX(),
			transform.getRotationsQuaternion().getY(),
			transform.getRotationsQuaternion().getZ(),
			transform.getRotationsQuaternion().getW()
		)
	);
}

const Vector3& BoundingVolume::getScale() {
	return scale;
}

const Vector3& BoundingVolume::getCenter() const {
	return center;
}
