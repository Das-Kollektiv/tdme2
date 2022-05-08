#include <tdme/engine/primitives/BoundingVolume.h>

#include <string>

#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/collision/narrowphase/DefaultCollisionDispatch.h>
#include <ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/collision/CollisionCallback.h>
#include <ext/reactphysics3d/src/collision/NarrowPhaseInfo.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/constraint/ContactPoint.h>
#include <ext/reactphysics3d/src/engine/CollisionWorld.h>
#include <ext/reactphysics3d/src/engine/OverlappingPair.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>
#include <ext/reactphysics3d/src/memory/MemoryAllocator.h>

#include <tdme/tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Vector3.h>

using std::to_string;

using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Transform;
using tdme::math::Vector3;

BoundingVolume::~BoundingVolume() {
	if (collisionShape != nullptr) delete collisionShape;
}

void BoundingVolume::computeBoundingBox() {
	collisionShape->computeAABB(collisionShapeAABB, collisionShapeTransform * collisionShapeLocalTransform);
	boundingBoxTransformed = BoundingBox(
		Vector3(collisionShapeAABB.getMin().x, collisionShapeAABB.getMin().y, collisionShapeAABB.getMin().z),
		Vector3(collisionShapeAABB.getMax().x, collisionShapeAABB.getMax().y, collisionShapeAABB.getMax().z)
	);
	centerTransformed = boundingBoxTransformed.getCenter();
}

void BoundingVolume::fromTransform(const Transform& transform) {
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

	// compute bounding box
	computeBoundingBox();
}

const Vector3& BoundingVolume::getScale() {
	return scale;
}

const Vector3& BoundingVolume::getCenter() const {
	return center;
}

const Vector3& BoundingVolume::getCenterTransformed() const {
	return centerTransformed;
}

BoundingBox& BoundingVolume::getBoundingBoxTransformed() {
	return boundingBoxTransformed;
}
