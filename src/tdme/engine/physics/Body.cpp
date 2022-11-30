#include <string>
#include <vector>

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/body/CollisionBody.h>
#include <reactphysics3d/collision/narrowphase/CollisionDispatch.h>
#include <reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/collision/CollisionCallback.h>
#include <reactphysics3d/constraint/ContactPoint.h>
#include <reactphysics3d/engine/PhysicsWorld.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/mathematics/Vector3.h>
#include <reactphysics3d/memory/MemoryAllocator.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/TerrainMesh.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Console;

Body::Body(World* world, const string& id, int type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes)
{
	this->world = world;
	this->id = id;
	this->inertiaTensor = inertiaTensor;
	this->type = type;
	this->restitution = restitution;
	this->friction = friction;
	this->mass = mass;
	this->collideTypeIds = ~0;
	this->collisionTypeId = collisionTypeId;
	//
	switch (type) {
		case TYPE_STATIC:
			this->rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::STATIC);
			this->rigidBody->setMass(mass);
			this->rigidBody->setIsAllowedToSleep(true);
			this->collisionBody = rigidBody;
			break;
		case TYPE_DYNAMIC:
			this->rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
			this->rigidBody->setMass(mass);
			this->rigidBody->setIsAllowedToSleep(true);
			this->collisionBody = rigidBody;
			break;
		case TYPE_KINEMATIC:
			this->rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
			this->rigidBody->setMass(mass);
			this->rigidBody->setIsAllowedToSleep(true);
			this->collisionBody = rigidBody;
			break;
		case TYPE_COLLISION:
			this->rigidBody = nullptr;
			this->collisionBody = this->world->world->createCollisionBody(reactphysics3d::Transform());
			break;
		default:
			Console::println("Body::Body(): unsupported type: " + to_string(type) + ": using collision body");
			this->rigidBody = nullptr;
			this->collisionBody = this->world->world->createCollisionBody(reactphysics3d::Transform());
			break;
	}
	collisionBody->setUserData(this);
	//
	for (auto boundingVolume: boundingVolumes) {
		this->boundingVolumes.push_back(boundingVolume->clone());
	}
	// finally create collision shapes
	for (auto boundingVolume: this->boundingVolumes) {
		boundingVolume->createCollisionShape(world);
	}
	setTransform(transform);
	setEnabled(enabled);
}

Body::~Body() {
	for (auto boundingVolume: boundingVolumes) {
		delete boundingVolume;
	}
}

const Vector3 Body::getNoRotationInertiaTensor() {
	return Vector3(0.0f, 0.0f, 0.0f);
}

bool Body::isCloned() {
	return cloned;
}

void Body::setCloned(bool cloned) {
	this->cloned = cloned;
}

const string& Body::getId()
{
	return id;
}

int32_t Body::getType() {
	return type;
}

uint16_t Body::getCollisionTypeId()
{
	return collisionTypeId;
}

void Body::setCollisionTypeId(uint16_t typeId)
{
	this->collisionTypeId = typeId;
	for (auto collider: colliders) {
		collider->setCollisionCategoryBits(typeId);
	}
}

uint16_t Body::getCollisionTypeIds()
{
	return collideTypeIds;
}

void Body::setCollisionTypeIds(uint16_t collisionTypeIds)
{
	this->collideTypeIds = collisionTypeIds;
	for (auto collider: colliders) {
		collider->setCollideWithMaskBits(collisionTypeIds);
	}
}

bool Body::isEnabled()
{
	return collisionBody->isActive();
}

void Body::setEnabled(bool enabled)
{
	collisionBody->setIsActive(enabled);
	if (enabled == true && rigidBody != nullptr) rigidBody->setIsSleeping(false);
}

bool Body::isSleeping()
{
	return rigidBody != nullptr?rigidBody->isSleeping():true;
}

void Body::setSleeping(bool sleeping) {
	if (rigidBody != nullptr) rigidBody->setIsSleeping(sleeping);
}

vector<BoundingVolume*>& Body::getBoundingVolumes() {
	return boundingVolumes;
}

void Body::resetColliders() {
	// remove colliders
	for (auto collider: colliders) {
		if (rigidBody != nullptr) {
			rigidBody->removeCollider(collider);
		} else {
			collisionBody->removeCollider(collider);
		}
	}
	colliders.clear();

	// set up scale
	for (auto boundingVolume: boundingVolumes) {
		// scale bounding volume and recreate it if nessessary
		if (boundingVolume->getScale().equals(transform.getScale()) == false) {
			boundingVolume->destroyCollisionShape();
			boundingVolume->setScale(transform.getScale());
			boundingVolume->createCollisionShape(world);
		}
	}

	// determine total volume
	float volumeTotal = 0.0f;
	for (auto boundingVolume: boundingVolumes) {
		// skip if not attached
		if (boundingVolume->isAttachedToWorld() == false) continue;
		//
		volumeTotal+=
			boundingVolume->boundingBoxTransformed.getDimensions().getX() *
			boundingVolume->boundingBoxTransformed.getDimensions().getY() *
			boundingVolume->boundingBoxTransformed.getDimensions().getZ();
	}
	// add bounding volumes with mass
	for (auto boundingVolume: boundingVolumes) {
		// skip if not attached
		if (boundingVolume->isAttachedToWorld() == false) continue;
		//
		float volumeBoundingVolume =
			boundingVolume->boundingBoxTransformed.getDimensions().getX() *
			boundingVolume->boundingBoxTransformed.getDimensions().getY() *
			boundingVolume->boundingBoxTransformed.getDimensions().getZ();

		reactphysics3d::Collider* collider = nullptr;
		if (rigidBody != nullptr) {
			//
			collider = rigidBody->addCollider(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform);
			collider->getMaterial().setBounciness(restitution);
			collider->getMaterial().setFrictionCoefficient(friction);
			collider->getMaterial().setMassDensity(volumeBoundingVolume / volumeTotal);
		} else {
			collider = collisionBody->addCollider(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform);
		}

		//
		collider->setCollideWithMaskBits(collideTypeIds);
		collider->setCollisionCategoryBits(collisionTypeId);

		//
		colliders.push_back(collider);
	}

	// set up inverse inertia tensor local
	if (rigidBody != nullptr) {
		// 	this method is only used when setting TDME2 transform, so no need to transform back
		reactphysics3d::Transform transform;
		collisionBody->setTransform(transform);
		// set inverse inertia tensor local
		rigidBody->setLocalInertiaTensor(reactphysics3d::Vector3(inertiaTensor.getX(), inertiaTensor.getY(), inertiaTensor.getZ()));
	};
}

BoundingBox Body::computeBoundingBoxTransformed() {
	auto aabb = rigidBody->getAABB();
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

float Body::getFriction()
{
	return friction;
}

void Body::setFriction(float friction)
{
	//
	this->friction = friction;
	for(auto collider: colliders) collider->getMaterial().setFrictionCoefficient(friction);
}

float Body::getRestitution()
{
	return restitution;
}

void Body::setRestitution(float restitution)
{
	//
	this->restitution = restitution;
	for(auto collider: colliders) collider->getMaterial().setBounciness(restitution);
}

float Body::getMass()
{
	return mass;
}

void Body::setMass(float mass)
{
	this->mass = mass;
	if (rigidBody == nullptr) {
		Console::println("Body::setMass(): no rigid body attached");
		return;
	}
	rigidBody->setMass(mass);
}

const Vector3 Body::getLinearVelocity()
{
	if (rigidBody == nullptr) {
		Console::println("Body::getLinearVelocity(): no rigid body attached");
		return Vector3();
	}
	return Vector3(
		rigidBody->getLinearVelocity().x,
		rigidBody->getLinearVelocity().y,
		rigidBody->getLinearVelocity().z
	);
}

void Body::setLinearVelocity(const Vector3& linearVelocity) {
	if (rigidBody == nullptr) {
		Console::println("Body::setLinearVelocity(): no rigid body attached");
		return;
	}
	rigidBody->setLinearVelocity(reactphysics3d::Vector3(linearVelocity.getX(), linearVelocity.getY(), linearVelocity.getZ()));
}

const Vector3 Body::getAngularVelocity()
{
	if (rigidBody == nullptr) {
		Console::println("Body::getAngularVelocity(): no rigid body attached");
		return Vector3();
	}
	return Vector3(
		rigidBody->getAngularVelocity().x,
		rigidBody->getAngularVelocity().y,
		rigidBody->getAngularVelocity().z
	);
}

void Body::setAngularVelocity(const Vector3& angularVelocity) {
	if (rigidBody == nullptr) {
		Console::println("Body::setAngularVelocity(): no rigid body attached");
		return;
	}
	rigidBody->setAngularVelocity(reactphysics3d::Vector3(angularVelocity.getX(), angularVelocity.getY(), angularVelocity.getZ()));
}

float Body::getLinearDamping()
{
	if (rigidBody == nullptr) {
		Console::println("Body::getLinearDamping(): no rigid body attached");
		return 0.0f;
	}
	return rigidBody->getLinearDamping();
}

void Body::setLinearDamping(float linearDamping)
{
	if (rigidBody == nullptr) {
		Console::println("Body::setLinearDamping(): no rigid body attached");
		return;
	}
	rigidBody->setLinearDamping(linearDamping);
}

float Body::getAngularDamping()
{
	if (rigidBody == nullptr) {
		Console::println("Body::getAngularDamping(): no rigid body attached");
		return 0.0f;
	}
	return rigidBody->getAngularDamping();
}

void Body::setAngularDamping(float angularDamping)
{
	if (rigidBody == nullptr) {
		Console::println("Body::setAngularDamping(): no rigid body attached");
		return;
	}
	rigidBody->setAngularDamping(angularDamping);
}

const Transform& Body::getTransform() {
	return transform;
}

void Body::setTransform(const Transform& transform)
{
	// store engine transform
	this->transform.setTransform(transform);

	// reset proxy shapes if bounding volumes do not match proxy shapes or if scaling has changed
	if (colliders.size() != boundingVolumes.size() || transformScale.equals(transform.getScale()) == false) {
		resetColliders();
		transformScale.set(transform.getScale());
	}

	/*
	// TODO: center of mass ~ pivot
	// set center of mass which is basically center of bv for now
	body->setCenterOfMassLocal(boundingVolume->collisionShapeLocalTransform.getPosition());
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
	collisionBody->setTransform(
		reactphysics3d::Transform(
			reactphysics3d::Vector3(
				this->transform.getTranslation().getX(),
				this->transform.getTranslation().getY(),
				this->transform.getTranslation().getZ()
			),
			reactphysics3d::Quaternion(
				this->transform.getRotationsQuaternion().getX(),
				this->transform.getRotationsQuaternion().getY(),
				this->transform.getRotationsQuaternion().getZ(),
				this->transform.getRotationsQuaternion().getW()
			)
		)
	);
}

void Body::addForce(const Vector3& forceOrigin, const Vector3& force)
{
	if (rigidBody == nullptr) {
		Console::println("Body::addForce(): no rigid body attached");
		return;
	}
	rigidBody->applyWorldForceAtWorldPosition(
		reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ()),
		reactphysics3d::Vector3(forceOrigin.getX(), forceOrigin.getY(), forceOrigin.getZ())
	);
}

void Body::addForce(const Vector3& force)
{
	if (rigidBody == nullptr) {
		Console::println("Body::addForce(): no rigid body attached");
		return;
	}
	rigidBody->applyWorldForceAtCenterOfMass(
		reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ())
	);
}

void Body::addTorque(const Vector3& torque)
{
	if (rigidBody == nullptr) {
		Console::println("Body::addTorque(): no rigid body attached");
		return;
	}
	rigidBody->applyWorldTorque(
		reactphysics3d::Vector3(torque.getX(), torque.getY(), torque.getZ())
	);
}

void Body::addCollisionListener(CollisionListener* listener)
{
	collisionListener.push_back(listener);
}

void Body::removeCollisionListener(CollisionListener* listener)
{
	collisionListener.erase(remove(collisionListener.begin(), collisionListener.end(), listener), collisionListener.end());
}

void Body::fireOnCollision(Body* other, CollisionResponse& collisionResponse)
{
	for (auto listener: collisionListener) {
		listener->onCollision(this, other, collisionResponse);
	}
}

void Body::fireOnCollisionBegin(Body* other, CollisionResponse& collisionResponse)
{
	for (auto listener: collisionListener) {
		listener->onCollisionBegin(this, other, collisionResponse);
	}
}

void Body::fireOnCollisionEnd(Body* other)
{
	for (auto listener: collisionListener) {
		listener->onCollisionEnd(this, other);
	}
}
