#include <tdme/engine/primitives/BoundingVolume.h>

#include <string>

#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/collision/CollisionCallback.h>
#include <ext/reactphysics3d/src/collision/NarrowPhaseInfo.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/collision/narrowphase/DefaultCollisionDispatch.h>
#include <ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <ext/reactphysics3d/src/constraint/ContactPoint.h>
#include <ext/reactphysics3d/src/engine/CollisionWorld.h>
#include <ext/reactphysics3d/src/engine/OverlappingPair.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>
#include <ext/reactphysics3d/src/memory/MemoryAllocator.h>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::to_string;

using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Vector3;
using tdme::utils::Console;

BoundingVolume::~BoundingVolume() {
}

void BoundingVolume::computeBoundingBox() {
	collisionShape->computeAABB(collisionShapeAABB, collisionShapeTransform * collisionShapeLocalTransform);
	boundingBoxTransformed = BoundingBox(
		Vector3(collisionShapeAABB.getMin().x, collisionShapeAABB.getMin().y, collisionShapeAABB.getMin().z),
		Vector3(collisionShapeAABB.getMax().x, collisionShapeAABB.getMax().y, collisionShapeAABB.getMax().z)
	);
	centerTransformed = boundingBoxTransformed.getCenter();
}

void BoundingVolume::fromTransformations(Transformations* transformations) {
	auto& transformationsMatrix = transformations->getTransformationsMatrix();
	collisionShape->setLocalScaling(reactphysics3d::Vector3(transformations->getScale().getX(), transformations->getScale().getY(), transformations->getScale().getZ()));
	collisionShapeTransform.setFromOpenGL(transformationsMatrix.getArray().data());
	computeBoundingBox();
}

bool BoundingVolume::containsPoint(const Vector3& point) {
	// TODO: Implement me!
	return false;
}

bool BoundingVolume::doesCollideWith(BoundingVolume* bv2, CollisionResponse* collision)
{
	// callback
	class CustomCollisionCallbackInfo: public reactphysics3d::CollisionCallback::CollisionCallbackInfo {
	    public:
			CustomCollisionCallbackInfo(reactphysics3d::OverlappingPair* pair, reactphysics3d::MemoryManager& memoryManager, CollisionResponse* collision):
				reactphysics3d::CollisionCallback::CollisionCallbackInfo(pair, memoryManager),
				collision(collision) {
			}

			void notifyContact(const CollisionCallbackInfo& collisionCallbackInfo) {
				auto contactManifoldElement = collisionCallbackInfo.contactManifoldElements;
				while (contactManifoldElement != nullptr) {
					auto entity = collision->addResponse(-contactManifoldElement->getContactManifold()->getContactPoints()->getPenetrationDepth());
					auto normal = contactManifoldElement->getContactManifold()->getContactPoints()->getNormal();
					entity->getNormal().set(normal.x, normal.y, normal.z);
					auto shape1 = contactManifoldElement->getContactManifold()->getShape1();
					auto shape2 = contactManifoldElement->getContactManifold()->getShape2();
					auto& shapeLocalToWorldTransform1 = shape1->getLocalToWorldTransform();
					auto& shapeLocalToWorldTransform2 = shape2->getLocalToWorldTransform();
					auto& localPoint1 = contactManifoldElement->getContactManifold()->getContactPoints()->getLocalPointOnShape1();
					auto& localPoint2 = contactManifoldElement->getContactManifold()->getContactPoints()->getLocalPointOnShape2();
					auto worldPoint1 = shapeLocalToWorldTransform1 * (localPoint1 * shape1->getLocalScaling());
					auto worldPoint2 = shapeLocalToWorldTransform2 * (localPoint2 * shape2->getLocalScaling());
					entity->addHitPoint(Vector3(worldPoint1.x, worldPoint1.y, worldPoint1.z));
					entity->addHitPoint(Vector3(worldPoint2.x, worldPoint2.y, worldPoint2.z));
					contactManifoldElement = contactManifoldElement->getNext();
				}
			}
	    private:
			CollisionResponse* collision;
	};

	//
	collision->reset();

	// do broad test
	if (collisionShapeAABB.testCollision(bv2->collisionShapeAABB) == false) return false;

	// do narrow test
	auto collisionShape1 = collisionShape;
	auto& collisionShapeTransform1 = collisionShapeTransform;
	auto collisionShape2 = bv2->collisionShape;
	auto& collisionShapeTransform2 = bv2->collisionShapeTransform;
	reactphysics3d::MemoryManager memoryManager;
	reactphysics3d::DefaultCollisionDispatch collisionDispatch;
	reactphysics3d::CollisionWorld world;
	reactphysics3d::CollisionBody body1(collisionShapeTransform1, world, 0);
	reactphysics3d::CollisionBody body2(collisionShapeTransform2, world, 1);
	reactphysics3d::ProxyShape proxyShape1(&body1, collisionShape1, collisionShapeLocalTransform, 0.0, memoryManager);
	reactphysics3d::ProxyShape proxyShape2(&body2, collisionShape2, bv2->collisionShapeLocalTransform, 0.0, memoryManager);
	reactphysics3d::OverlappingPair pair(&proxyShape1, &proxyShape2, memoryManager.getPoolAllocator(), memoryManager.getSingleFrameAllocator());
    auto narrowPhaseInfo = new (
		memoryManager.allocate(
			reactphysics3d::MemoryManager::AllocationType::Pool,
			sizeof(reactphysics3d::NarrowPhaseInfo)
		)
	) reactphysics3d::NarrowPhaseInfo(
		&pair,
		collisionShape1,
		collisionShape2,
		proxyShape1.getLocalToWorldTransform(),
		proxyShape2.getLocalToWorldTransform(),
		memoryManager.getPoolAllocator()
	);
    while (narrowPhaseInfo != nullptr) {
		auto narrowPhaseAlgorithm = collisionDispatch.selectAlgorithm(
			Math::min(static_cast<int>(collisionShape1->getType()), static_cast<int>(collisionShape2->getType())),
			Math::max(static_cast<int>(collisionShape1->getType()), static_cast<int>(collisionShape2->getType()))
		);
		if (narrowPhaseAlgorithm != nullptr) {
			if (narrowPhaseAlgorithm->testCollision(narrowPhaseInfo, true, memoryManager.getPoolAllocator())) {
				narrowPhaseInfo->addContactPointsAsPotentialContactManifold();
			}
		}
        auto currentNarrowPhaseInfo = narrowPhaseInfo;
        narrowPhaseInfo = narrowPhaseInfo->next;
        currentNarrowPhaseInfo->~NarrowPhaseInfo();
        memoryManager.release(reactphysics3d::MemoryManager::AllocationType::Pool, currentNarrowPhaseInfo, sizeof(reactphysics3d::NarrowPhaseInfo));
    }
    pair.reducePotentialContactManifolds();
    pair.addContactPointsFromPotentialContactPoints();
    pair.clearObsoleteManifoldsAndContactPoints();
    pair.reduceContactManifolds();
    pair.clearPotentialContactManifolds();
	if (pair.hasContacts()) {
		CustomCollisionCallbackInfo customCollisionCallbackInfo(&pair, memoryManager, collision);
        reactphysics3d::CollisionCallback::CollisionCallbackInfo collisionInfo(&pair, memoryManager);
        customCollisionCallbackInfo.notifyContact(collisionInfo);
	}

	// done
	return collision->hasEntitySelected();
}

const Vector3 BoundingVolume::getCenterTransformed() const {
	return centerTransformed;
}

const BoundingBox& BoundingVolume::getBoundingBoxTransformed() const {
	return boundingBoxTransformed;
}
