#include <tdme/engine/primitives/BoundingVolume.h>

#include <string>

#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/collision/narrowphase/DefaultCollisionDispatch.h>
#include <ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <ext/reactphysics3d/src/constraint/ContactPoint.h>
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
	collisionShape->computeAABB(collisionShapeAABB, collisionShapeTransform);
	boundingBoxTransformed = BoundingBox(
		Vector3(collisionShapeAABB.getMin().x, collisionShapeAABB.getMin().y, collisionShapeAABB.getMin().z),
		Vector3(collisionShapeAABB.getMax().x, collisionShapeAABB.getMax().y, collisionShapeAABB.getMax().z)
	);
	centerTransformed = boundingBoxTransformed.getCenter();
}

void BoundingVolume::applyLocalTransformations(Transformations* transformations, Transformations* finalTransformations) {
	// apply bounding volume local transformations to final transformations
	// copy transformations
	finalTransformations->fromTransformations(transformations);
	// apply local transformations
	finalTransformations->getTranslation().sub(collisionShapeLocalTranslation);
	// TODO: pivot
	finalTransformations->getPivot().set(collisionShapeLocalTranslation.clone().scale(+1.0f));
	// update
	finalTransformations->update();
}

void BoundingVolume::applyInverseLocalTransformations(Transformations* transformations, Transformations* finalTransformations) {
	// apply bounding volume inverse local transformations to final transformations
	// copy
	finalTransformations->fromTransformations(transformations);
	// apply inverse local transformations
	finalTransformations->getTranslation().add(collisionShapeLocalTranslation);
	// TODO: pivotPhy
	//finalTransformations->getPivot().set(collisionShapeLocalTranslation.clone().scale(-1.0f));
	finalTransformations->getPivot().set(0.0f, 0.0f, 0.0f);
	// TODO: handle rotations
	finalTransformations->update();
}

void BoundingVolume::fromTransformations(Transformations* transformations) {
	Transformations finalTransformations;
	applyInverseLocalTransformations(transformations, &finalTransformations);
	auto& transformationsMatrix = finalTransformations.getTransformationsMatrix();
	collisionShape->setLocalScaling(reactphysics3d::Vector3(transformations->getScale().getX(), transformations->getScale().getY(), transformations->getScale().getZ()));
	collisionShapeTransform.setFromOpenGL(transformationsMatrix.getArray().data());
	computeBoundingBox();
}

bool BoundingVolume::containsPoint(const Vector3& point) {
	// TODO: Implement me!
	return false;
}

bool BoundingVolume::doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision)
{
	/*
	// callback
	class CustomNarrowPhaseCallback: public reactphysics3d::NarrowPhaseCallback {
	    public:
			CustomNarrowPhaseCallback(
				reactphysics3d::CollisionShape* collisionShape1,
				reactphysics3d::Transform* collisionShapeTransform1,
				reactphysics3d::CollisionShape* collisionShape2,
				reactphysics3d::Transform* collisionShapeTransform2,
				CollisionResponse* collision):
					collisionShape1(collisionShape1),
					collisionShapeTransform1(collisionShapeTransform1),
					collisionShape2(collisionShape2),
					collisionShapeTransform2(collisionShapeTransform2),
					collision(collision) {
			}
			void notifyContact(reactphysics3d::OverlappingPair* overlappingPair, const reactphysics3d::ContactPointInfo& contactInfo) override {
				auto entity = collision->addResponse(-contactInfo.penetrationDepth);
				entity->getNormal().set(contactInfo.normal.x, contactInfo.normal.y, contactInfo.normal.z);
				auto worldPoint1 = *collisionShapeTransform1 * (contactInfo.localPoint1 * collisionShape1->getScaling());
				auto worldPoint2 = *collisionShapeTransform2 * (contactInfo.localPoint2 * collisionShape2->getScaling());
				entity->addHitPoint(Vector3(worldPoint1.x, worldPoint1.y, worldPoint1.z));
				entity->addHitPoint(Vector3(worldPoint2.x, worldPoint2.y, worldPoint2.z));
			}
	    private:
			reactphysics3d::CollisionShape* collisionShape1;
			reactphysics3d::Transform* collisionShapeTransform1;
			reactphysics3d::CollisionShape* collisionShape2;
			reactphysics3d::Transform* collisionShapeTransform2;
			CollisionResponse* collision;
	};
	*/

	//
	collision->reset();

	/*
	// do broad test
	if (collisionShapeAABB.testCollision(bv2->collisionShapeAABB) == false) return false;

	// TODO: update for reactphysics3d-develop
	auto collisionShape1 = collisionShape;
	auto& collisionShapeTransform1 = collisionShapeTransform;
	auto collisionShape2 = bv2->collisionShape;
	auto& collisionShapeTransform2 = bv2->collisionShapeTransform;
	CustomNarrowPhaseCallback customNarrowPhaseCallback(collisionShape1, &collisionShapeTransform1, collisionShape2, &collisionShapeTransform2, collision);
	reactphysics3d::MemoryAllocator memoryAllocator;
	reactphysics3d::DefaultCollisionDispatch collisionDispatch;
	collisionDispatch.init(nullptr, &memoryAllocator);
	auto narrowPhaseAlgorithm = collisionDispatch.selectAlgorithm(collisionShape1->getType(), collisionShape2->getType());
    int nbMaxManifolds = reactphysics3d::CollisionShape::computeNbMaxContactManifolds(collisionShape1->getType(), collisionShape2->getType());
	reactphysics3d::OverlappingPair overlappingPair(nullptr, nullptr, nbMaxManifolds, memoryAllocator);
	void* cachedCollisionData1 = nullptr;
	void* cachedCollisionData2 = nullptr;
	reactphysics3d::CollisionShapeInfo shape1Info(nullptr, collisionShape1, collisionShapeTransform1, &overlappingPair, &cachedCollisionData1);
	reactphysics3d::CollisionShapeInfo shape2Info(nullptr, collisionShape2, collisionShapeTransform2, &overlappingPair, &cachedCollisionData2);
	narrowPhaseAlgorithm->setCurrentOverlappingPair(&overlappingPair);
	narrowPhaseAlgorithm->testCollision(shape1Info, shape2Info, &customNarrowPhaseCallback);
	*/
	return collision->hasEntitySelected();
}

const Vector3 BoundingVolume::getCenterTransformed() const {
	return centerTransformed;
}

const BoundingBox& BoundingVolume::getBoundingBoxTransformed() const {
	return boundingBoxTransformed;
}
