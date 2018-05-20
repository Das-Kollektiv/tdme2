#include <tdme/engine/physics/RigidBody.h>

#include <string>
#include <vector>

#include <ext/reactphysics3d/src/body/Body.h>
#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/body/RigidBody.h>
#include <ext/reactphysics3d/src/collision/CollisionCallback.h>
#include <ext/reactphysics3d/src/collision/NarrowPhaseInfo.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/collision/narrowphase/DefaultCollisionDispatch.h>
#include <ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <ext/reactphysics3d/src/constraint/ContactPoint.h>
#include <ext/reactphysics3d/src/engine/CollisionWorld.h>
#include <ext/reactphysics3d/src/engine/DynamicsWorld.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>
#include <ext/reactphysics3d/src/mathematics/Vector3.h>
#include <ext/reactphysics3d/src/memory/MemoryAllocator.h>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/TerrainConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::RigidBody;
using tdme::engine::Rotation;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::TerrainConvexMesh;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;

constexpr uint16_t RigidBody::TYPEIDS_ALL;
constexpr uint16_t RigidBody::TYPEID_STATIC;
constexpr uint16_t RigidBody::TYPEID_DYNAMIC;

RigidBody::RigidBody(World* world, const string& id, int type, bool enabled, uint16_t typeId, BoundingVolume* boundingVolume, const Transformations& transformations, float restitution, float friction, float mass, const Matrix4x4& inverseInertiaMatrix)
{
	this->world = world;
	this->id = id;
	this->rootId = id;
	this->inverseInertiaMatrix.set(inverseInertiaMatrix);
	// terrain convex mesh
	if (dynamic_cast<TerrainConvexMesh*>(boundingVolume) != nullptr) {
		// transform terrain convex mesh with transformations
		this->boundingVolume = boundingVolume->clone();
		dynamic_cast<TerrainConvexMesh*>(this->boundingVolume)->applyTransformations(transformations);
		// determine position
		auto positionTransformed = dynamic_cast<TerrainConvexMesh*>(this->boundingVolume)->getPositionTransformed();
		this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
		rigidBody->setType(reactphysics3d::BodyType::STATIC);
		rigidBody->getMaterial().setFrictionCoefficient(friction);
		rigidBody->getMaterial().setBounciness(restitution);
		rigidBody->setMass(mass);
		this->proxyShape = rigidBody->addCollisionShape(this->boundingVolume->collisionShape, this->boundingVolume->collisionShapeLocalTransform, mass);
		this->proxyShape->setCollideWithMaskBits(~typeId);
		Transformations terrainTransformations;
		terrainTransformations.setTranslation(positionTransformed);
		fromTransformations(terrainTransformations);
	} else
	// everything other
	{
		this->boundingVolume = boundingVolume->clone();
		this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
		switch (type) {
			case TYPE_STATIC:
				rigidBody->setType(reactphysics3d::BodyType::STATIC);
				break;
			case TYPE_DYNAMIC:
				rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
				break;
			case TYPE_KINEMATIC:
				rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
				break;
		}
		auto& inverseInertiaMatrixArray = inverseInertiaMatrix.getArray();
		rigidBody->setInverseInertiaTensorLocal(
			reactphysics3d::Matrix3x3(
				inverseInertiaMatrixArray[0],
				inverseInertiaMatrixArray[1],
				inverseInertiaMatrixArray[2],
				inverseInertiaMatrixArray[4],
				inverseInertiaMatrixArray[5],
				inverseInertiaMatrixArray[6],
				inverseInertiaMatrixArray[8],
				inverseInertiaMatrixArray[9],
				inverseInertiaMatrixArray[10]
			)
		);
		rigidBody->getMaterial().setFrictionCoefficient(friction);
		rigidBody->getMaterial().setBounciness(restitution);
		rigidBody->setMass(mass);
		this->proxyShape = rigidBody->addCollisionShape(this->boundingVolume->collisionShape, this->boundingVolume->collisionShapeLocalTransform, mass);
		this->proxyShape->setCollideWithMaskBits(~0);
		fromTransformations(transformations);
	}
	this->rigidBody->setUserData(this);
	this->proxyShape->setCollisionCategoryBits(typeId);
	setEnabled(enabled);
}

RigidBody::~RigidBody() {
	delete boundingVolume;
}

Matrix4x4 RigidBody::getNoRotationInertiaMatrix()
{
	return Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 RigidBody::computeInertiaMatrix(BoundingVolume* bv, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis)
{
	auto width = bv->getBoundingBoxTransformed().getDimensions().getX();
	auto height = bv->getBoundingBoxTransformed().getDimensions().getY();
	auto depth = bv->getBoundingBoxTransformed().getDimensions().getZ();
	return
		(Matrix4x4(
			scaleXAxis * 1.0f / 12.0f * mass * (height * height + depth * depth), 0.0f, 0.0f, 0.0f,
			0.0f, scaleYAxis * 1.0f / 12.0f * mass * (width * width + depth * depth), 0.0f, 0.0f,
			0.0f, 0.0f, scaleZAxis * 1.0f / 12.0f * mass * (width * width + height * height), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		)).invert();
}

const string& RigidBody::getId()
{
	return id;
}

const string& RigidBody::getRootId()
{
	return rootId;
}

void RigidBody::setRootId(const string& rootId) {
	this->rootId = rootId;
}

uint16_t RigidBody::getTypeId()
{
	return this->proxyShape->getCollisionCategoryBits();
}

void RigidBody::setTypeId(uint16_t typeId)
{
	this->proxyShape->setCollisionCategoryBits(typeId);
}

uint16_t RigidBody::getCollisionTypeIds()
{
	return this->proxyShape->getCollideWithMaskBits();
}

void RigidBody::setCollisionTypeIds(uint16_t collisionTypeIds)
{
	this->proxyShape->setCollideWithMaskBits(collisionTypeIds);
}

bool RigidBody::isEnabled()
{
	return enabled;
}

void RigidBody::setEnabled(bool enabled)
{
	// return if enable state has not changed
	if (this->enabled == enabled)
		return;

	//
	if (enabled == true) {
		rigidBody->setIsActive(true);
	} else {
		rigidBody->setIsActive(false);
	}

	//
	this->enabled = enabled;
}

bool RigidBody::isStatic()
{
	return rigidBody->getType() == reactphysics3d::BodyType::STATIC;
}

bool RigidBody::isSleeping()
{
	return rigidBody->isSleeping();
}

BoundingVolume* RigidBody::getBoundingVolume()
{
	return boundingVolume;
}

BoundingBox RigidBody::computeBoundingBoxTransformed() {
	auto aabb = proxyShape->getWorldAABB();
	return BoundingBox(
		Vector3(
			aabb.getMin().x,
			aabb.getMin().y,
			aabb.getMin().z
		),
		Vector3(
			aabb.getMax().x,
			aabb.getMax().y,
			aabb.getMax().z
		)
	);
}

const Vector3& RigidBody::getPosition() const
{
	return transformations.getTranslation();
}

float RigidBody::getFriction()
{
	return rigidBody->getMaterial().getFrictionCoefficient();
}

void RigidBody::setFriction(float friction)
{
	rigidBody->getMaterial().setFrictionCoefficient(friction);
}

float RigidBody::getRestitution()
{
	return rigidBody->getMaterial().getBounciness();
}

void RigidBody::setRestitution(float restitution)
{
	rigidBody->getMaterial().setBounciness(restitution);
}

float RigidBody::getMass()
{
	return rigidBody->getMass();
}

void RigidBody::setMass(float mass)
{
	rigidBody->getMass();
}

Vector3& RigidBody::getLinearVelocity()
{
	return linearVelocity;
}

Vector3& RigidBody::getAngularVelocity()
{
	return angularVelocity;
}

const Transformations& RigidBody::getTransformations() {
	return transformations;
}

void RigidBody::fromTransformations(const Transformations& transformations)
{
	// store engine transformations
	this->transformations.fromTransformations(transformations);
	// terrain convex mesh
	if (dynamic_cast<TerrainConvexMesh*>(boundingVolume) != nullptr) {
		auto& transformationsMatrix = this->transformations.getTransformationsMatrix();
		reactphysics3d::Transform transform;
		transform.setFromOpenGL(transformationsMatrix.getArray().data());
		rigidBody->setTransform(transform);
	} else {
		// everything else
		// "scale vector transformed" which takes transformations scale and orientation into account
		auto scaleVectorTransformed =
			boundingVolume->collisionShapeLocalTransform.getOrientation() *
			reactphysics3d::Vector3(
				transformations.getScale().getX(),
				transformations.getScale().getY(),
				transformations.getScale().getZ()
			);
		// set bv local translation
		boundingVolume->collisionShapeLocalTransform.setPosition(
			reactphysics3d::Vector3(
				boundingVolume->collisionShapeLocalTranslation.getX(),
				boundingVolume->collisionShapeLocalTranslation.getY(),
				boundingVolume->collisionShapeLocalTranslation.getZ()
			) * scaleVectorTransformed
		);
		// set local to body transform, proxy shape scaling
		proxyShape->setLocalToBodyTransform(boundingVolume->collisionShapeLocalTransform);
		proxyShape->setLocalScaling(scaleVectorTransformed);
		// rigig body transform
		auto& transformationsMatrix = this->transformations.getTransformationsMatrix();
		reactphysics3d::Transform transform;
		// take from transformations matrix
		transform.setFromOpenGL(transformationsMatrix.getArray().data());
		// set center of mass which is basically center of bv for now
		rigidBody->setCenterOfMassLocal(boundingVolume->collisionShapeLocalTransform.getPosition());
		// find final position, not sure yet if its working 100%, but still works with some tests
		auto centerOfMassWorld = transform * boundingVolume->collisionShapeLocalTransform.getPosition();
		transform.setPosition(
			transform.getPosition() +
			transform.getPosition() -
			centerOfMassWorld +
			(
				reactphysics3d::Vector3(
					boundingVolume->collisionShapeLocalTranslation.getX(),
					boundingVolume->collisionShapeLocalTranslation.getY(),
					boundingVolume->collisionShapeLocalTranslation.getZ()
				) * scaleVectorTransformed
			)
		);
		// set transform
		rigidBody->setTransform(transform);
	}
}

void RigidBody::addForce(const Vector3& forceOrigin, const Vector3& force)
{
	rigidBody->applyForce(
		reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ()),
		reactphysics3d::Vector3(forceOrigin.getX(), forceOrigin.getY(), forceOrigin.getZ())
	);
}

void RigidBody::addForce(const Vector3& force)
{
	rigidBody->applyForceToCenterOfMass(
		reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ())
	);
}

void RigidBody::addTorque(const Vector3& torque)
{
	rigidBody->applyForceToCenterOfMass(
		reactphysics3d::Vector3(torque.getX(), torque.getY(), torque.getZ())
	);
}

bool RigidBody::doesCollideWith(BoundingVolume* boundingVolume, CollisionResponse* collision) {
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
	auto rigidBodyAABB = rigidBody->getProxyShapesList()->getWorldAABB();
	if (rigidBodyAABB.testCollision(boundingVolume->collisionShapeAABB) == false) return false;

	// do narrow test
	auto collisionShape1 = getBoundingVolume()->collisionShape;
	auto collisionShape2 = boundingVolume->collisionShape;
	auto& collisionShapeTransform2 = boundingVolume->collisionShapeTransform;
	reactphysics3d::MemoryManager memoryManager;
	reactphysics3d::DefaultCollisionDispatch collisionDispatch;
	reactphysics3d::CollisionWorld world;
	reactphysics3d::CollisionBody body2(collisionShapeTransform2, world, rigidBody->getID() + 1);
	auto proxyShape1 = rigidBody->getProxyShapesList();
	reactphysics3d::ProxyShape proxyShape2(&body2, collisionShape2, boundingVolume->collisionShapeLocalTransform, 0.0, memoryManager);
	reactphysics3d::OverlappingPair pair(proxyShape1, &proxyShape2, memoryManager.getPoolAllocator(), memoryManager.getSingleFrameAllocator());
    auto narrowPhaseInfo = new (
		memoryManager.allocate(
			reactphysics3d::MemoryManager::AllocationType::Pool,
			sizeof(reactphysics3d::NarrowPhaseInfo)
		)
	) reactphysics3d::NarrowPhaseInfo(
		&pair,
		collisionShape1,
		collisionShape2,
		proxyShape1->getLocalToWorldTransform(),
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

bool RigidBody::doesCollideWith(RigidBody* rigidBody, CollisionResponse* collision) {
	// callback
	class CustomCollisionCallback: public reactphysics3d::CollisionCallback {
	    public:
			CustomCollisionCallback(CollisionResponse* collision): collision(collision)  {
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

	// do the test
	CustomCollisionCallback customCollisionCallback(collision);
	world->world.testCollision(this->rigidBody, rigidBody->rigidBody, &customCollisionCallback);

	// done
	return collision->hasEntitySelected();
}

void RigidBody::addCollisionListener(CollisionListener* listener)
{
	collisionListener.push_back(listener);
}

void RigidBody::removeCollisionListener(CollisionListener* listener)
{
	collisionListener.erase(remove(collisionListener.begin(), collisionListener.end(), listener), collisionListener.end());
}

void RigidBody::fireOnCollision(RigidBody* other, CollisionResponse* collisionResponse)
{
	for (auto listener: collisionListener) {
		listener->onCollision(this, other, collisionResponse);
	}
}

void RigidBody::fireOnCollisionBegin(RigidBody* other, CollisionResponse* collisionResponse)
{
	for (auto listener: collisionListener) {
		listener->onCollisionBegin(this, other, collisionResponse);
	}
}

void RigidBody::fireOnCollisionEnd(RigidBody* other)
{
	for (auto listener: collisionListener) {
		listener->onCollisionEnd(this, other);
	}
}
