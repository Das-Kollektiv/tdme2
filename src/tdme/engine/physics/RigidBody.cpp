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
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/TerrainMesh.h>
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
using tdme::engine::primitives::TerrainMesh;
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
	this->boundingVolume = dynamic_cast<TerrainMesh*>(boundingVolume) != nullptr?boundingVolume:boundingVolume->clone();
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
	this->proxyShape->setCollisionCategoryBits(typeId);
	this->rigidBody->setUserData(this);
	fromTransformations(transformations);
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
	// rigig body transform
	auto& transformationsMatrix = this->transformations.getTransformationsMatrix();
	reactphysics3d::Transform transform;
	// take from transformations matrix
	transform.setFromOpenGL(transformationsMatrix.getArray().data());
	/*
	// TODO: center of mass ~ pivot
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
	*/
	// set transform
	rigidBody->setTransform(transform);
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
