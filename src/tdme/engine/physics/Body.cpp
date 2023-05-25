#include <string>
#include <vector>

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/collision/narrowphase/CollisionDispatch.h>
#include <reactphysics3d/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <reactphysics3d/collision/shapes/CollisionShape.h>
#include <reactphysics3d/collision/Collider.h>
#include <reactphysics3d/collision/CollisionCallback.h>
#include <reactphysics3d/constraint/ContactPoint.h>
#include <reactphysics3d/engine/PhysicsWorld.h>
#include <reactphysics3d/mathematics/Quaternion.h>
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
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Console;

Body::Body(World* world, const string& id, BodyType type, bool enabled, uint16_t collisionTypeId, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes)
{
	this->world = world;
	this->id = id;
	this->inertiaTensor = inertiaTensor;
	this->type = type;
	this->restitution = restitution;
	this->friction = friction;
	this->mass = mass;
	this->collisionTypeIds = ~0;
	this->collisionTypeId = collisionTypeId;
	//
	switch (type) {
		case BODYTYPE_STATIC:
		case BODYTYPE_COLLISION_STATIC:
			rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			rigidBody->setType(reactphysics3d::BodyType::STATIC);
			rigidBody->setMass(mass);
			rigidBody->setIsAllowedToSleep(true);
			rigidBody->enableGravity(false);
			rigidBody->setIsSleeping(true);
			break;
		case BODYTYPE_DYNAMIC:
		case BODYTYPE_COLLISION_DYNAMIC:
			rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
			rigidBody->setMass(mass);
			rigidBody->setIsAllowedToSleep(true);
			break;
		case BODYTYPE_KINEMATIC:
			rigidBody = this->world->world->createRigidBody(reactphysics3d::Transform());
			rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
			rigidBody->setMass(mass);
			rigidBody->setIsAllowedToSleep(true);
			break;
		default:
			Console::println("Body::Body(): unsupported type: " + to_string(type) + ": using collision body");
			break;
	}
	rigidBody->setUserData(this);
	//
	for (auto boundingVolume: boundingVolumes) {
		this->boundingVolumes.push_back(boundingVolume->clone());
	}
	// finally create collision shapes
	for (auto boundingVolume: this->boundingVolumes) {
		boundingVolume->createCollisionShape(world);
	}
	//
	setTransform(transform);
	setEnabled(enabled);
}

Body::~Body() {
	// remove colliders
	removeColliders(colliders, boundingVolumes);
	// destroy rigid body
	this->world->world->destroyRigidBody(rigidBody);
}

void Body::setCollisionTypeId(uint16_t typeId)
{
	this->collisionTypeId = typeId;
	for (auto collider: colliders) {
		collider->setCollisionCategoryBits(typeId);
	}
}

void Body::setCollisionTypeIds(uint16_t collisionTypeIds)
{
	this->collisionTypeIds = collisionTypeIds;
	for (auto collider: colliders) {
		collider->setCollideWithMaskBits(collisionTypeIds);
	}
}

void Body::resetColliders() {
	// we need the scale from our body transform to be passed as local transform when resetting colliders
	Transform localTransform;
	localTransform.setScale(transform.getScale());
	localTransform.update();
	// reset colliders, means remove and add them and create colliders with correct scale
	resetColliders(colliders, boundingVolumes, localTransform);
	// set up inverse inertia tensor local
	if (type == BODYTYPE_DYNAMIC) rigidBody->setLocalInertiaTensor(reactphysics3d::Vector3(inertiaTensor.getX(), inertiaTensor.getY(), inertiaTensor.getZ()));
}

void Body::removeColliders(vector<reactphysics3d::Collider*>& colliders, vector<BoundingVolume*>& boundingVolumes) {
	// remove colliders
	for (auto collider: colliders) {
		rigidBody->removeCollider(collider);
	}
	// delete bounding volumes
	for (auto boundingVolume: boundingVolumes) {
		delete boundingVolume;
	}
}

void Body::resetColliders(vector<reactphysics3d::Collider*>& colliders, vector<BoundingVolume*>& boundingVolumes, const Transform& transform) {
	// remove colliders
	for (auto collider: colliders) rigidBody->removeCollider(collider);
	colliders.clear();

	// set up scale
	{
		auto i = 0;
		for (auto boundingVolume: boundingVolumes) {
			Console::println(
				"bv[" + to_string(i) + "]: scale: " +
				to_string(boundingVolume->getScale().getX()) + ", " +
				to_string(boundingVolume->getScale().getY()) + ", " +
				to_string(boundingVolume->getScale().getZ())
			);
			// scale bounding volume and recreate it if nessessary
			if (boundingVolume->getScale().equals(transform.getScale()) == false) {
				boundingVolume->destroyCollisionShape();
				boundingVolume->setScale(transform.getScale());
				boundingVolume->createCollisionShape(world);
			}
			//
			i++;
		}
	}

	// transform: local transform

	// determine total volume
	/*
	float volumeTotal = 0.0f;
	for (auto boundingVolume: boundingVolumes) {
		// skip if not attached
		if (boundingVolume->isAttachedToWorld() == false) continue;
		//
		volumeTotal+=
			boundingVolume->worldBoundingBox.getDimensions().getX() *
			boundingVolume->worldBoundingBox.getDimensions().getY() *
			boundingVolume->worldBoundingBox.getDimensions().getZ();
	}
	*/

	// add bounding volumes with mass
	for (auto boundingVolume: boundingVolumes) {
		// skip if not attached
		if (boundingVolume->isAttachedToWorld() == false) continue;
		//
		/*
		float volumeBoundingVolume =
			boundingVolume->worldBoundingBox.getDimensions().getX() *
			boundingVolume->worldBoundingBox.getDimensions().getY() *
			boundingVolume->worldBoundingBox.getDimensions().getZ();
		*/
		//

		// RP3D collision shape local transform -> TDME2 collision shape local transform
		Transform collisionShapeLocalTransform;
		collisionShapeLocalTransform.setTranslation(
			Vector3(
				boundingVolume->collisionShapeLocalTransform.getPosition().x,
				boundingVolume->collisionShapeLocalTransform.getPosition().y,
				boundingVolume->collisionShapeLocalTransform.getPosition().z
			)
		);
		//
		auto collisionShapeLocalTransformRotation = Rotation::fromQuaternion(
			Quaternion(
				boundingVolume->collisionShapeLocalTransform.getOrientation().x,
				boundingVolume->collisionShapeLocalTransform.getOrientation().y,
				boundingVolume->collisionShapeLocalTransform.getOrientation().z,
				boundingVolume->collisionShapeLocalTransform.getOrientation().w
			)
		);
		//
		collisionShapeLocalTransform.addRotation(collisionShapeLocalTransformRotation.getAxis(), collisionShapeLocalTransformRotation.getAngle());
		collisionShapeLocalTransform.update();

		Console::println(
			"collisionShapeLocalTransform: translation: " +
			to_string(collisionShapeLocalTransform.getTranslation().getX()) + ", " +
			to_string(collisionShapeLocalTransform.getTranslation().getY()) + ", " +
			to_string(collisionShapeLocalTransform.getTranslation().getZ()));
		Console::println(
			"collisionShapeLocalTransform: scale: " +
			to_string(collisionShapeLocalTransform.getScale().getX()) + ", " +
			to_string(collisionShapeLocalTransform.getScale().getY()) + ", " +
			to_string(collisionShapeLocalTransform.getScale().getZ())
		);
		for (auto i = 0; i < collisionShapeLocalTransform.getRotationCount(); i++) {
			Console::println(
				"\tRotation: " + to_string(i) + ": " +
				to_string(collisionShapeLocalTransform.getRotationAxis(i).getX()) + ", " +
				to_string(collisionShapeLocalTransform.getRotationAxis(i).getY()) + ", " +
				to_string(collisionShapeLocalTransform.getRotationAxis(i).getZ()) + "; " +
				to_string(collisionShapeLocalTransform.getRotationAngle(i))
			);
		}

		Console::println(
			"transform: translation: " +
			to_string(transform.getTranslation().getX()) + ", " +
			to_string(transform.getTranslation().getY()) + ", " +
			to_string(transform.getTranslation().getZ())
		);
		Console::println(
			"transform: scale: " +
			to_string(transform.getScale().getX()) + ", " +
			to_string(transform.getScale().getY()) + ", " +
			to_string(transform.getScale().getZ())
		);
		for (auto i = 0; i < transform.getRotationCount(); i++) {
			Console::println(
				"\tRotation: " + to_string(i) + ": " +
				to_string(transform.getRotationAxis(i).getX()) + ", " +
				to_string(transform.getRotationAxis(i).getY()) + ", " +
				to_string(transform.getRotationAxis(i).getZ()) + "; " +
				to_string(transform.getRotationAngle(i))
			);
		}

		//
		auto _transform = transform;
		_transform.setScale(Vector3(1.0f, 1.0f, 1.0f));
		_transform.update();
		auto transformXCollisionShapeLocalTransform = _transform * collisionShapeLocalTransform;

		Console::println(
			"transform: translation: " +
			to_string(transformXCollisionShapeLocalTransform.getTranslation().getX()) + ", " +
			to_string(transformXCollisionShapeLocalTransform.getTranslation().getY()) + ", " +
			to_string(transformXCollisionShapeLocalTransform.getTranslation().getZ())
		);
		Console::println(
			"transform: scale: " +
			to_string(transformXCollisionShapeLocalTransform.getScale().getX()) + ", " +
			to_string(transformXCollisionShapeLocalTransform.getScale().getY()) + ", " +
			to_string(transformXCollisionShapeLocalTransform.getScale().getZ())
		);
		for (auto i = 0; i < transformXCollisionShapeLocalTransform.getRotationCount(); i++) {
			Console::println(
				"\tRotation: " + to_string(i) + ": " +
				to_string(transformXCollisionShapeLocalTransform.getRotationAxis(i).getX()) + ", " +
				to_string(transformXCollisionShapeLocalTransform.getRotationAxis(i).getY()) + ", " +
				to_string(transformXCollisionShapeLocalTransform.getRotationAxis(i).getZ()) + "; " +
				to_string(transformXCollisionShapeLocalTransform.getRotationAngle(i))
			);
		}
		Console::println();

		/*
			this = parent
			t = collisionShapeLocalTransform

		translation+= rotationsQuaternion * (t.translation * scale);
		scale*= t.scale;
		rotationsQuaternion*= t.rotationsQuaternion;
		*/

		reactphysics3d::Transform collisionShapeTransform(
			reactphysics3d::Vector3(transformXCollisionShapeLocalTransform.getTranslation().getX(), transformXCollisionShapeLocalTransform.getTranslation().getY(), transformXCollisionShapeLocalTransform.getTranslation().getZ()),
			reactphysics3d::Quaternion(transformXCollisionShapeLocalTransform.getRotationsQuaternion().getX(), transformXCollisionShapeLocalTransform.getRotationsQuaternion().getY(), transformXCollisionShapeLocalTransform.getRotationsQuaternion().getZ(), transformXCollisionShapeLocalTransform.getRotationsQuaternion().getW())
		);

		//
		auto collider = rigidBody->addCollider(boundingVolume->collisionShape, collisionShapeTransform);
		collider->getMaterial().setBounciness(restitution);
		collider->getMaterial().setFrictionCoefficient(friction);
		if (type == BODYTYPE_COLLISION_STATIC || type == BODYTYPE_COLLISION_DYNAMIC) collider->setIsTrigger(true);
		// collider->getMaterial().setMassDensity(volumeBoundingVolume / volumeTotal);

		//
		collider->setCollideWithMaskBits(collisionTypeIds);
		collider->setCollisionCategoryBits(collisionTypeId);

		//
		colliders.push_back(collider);
	}
}

void Body::setFriction(float friction)
{
	//
	this->friction = friction;
	for(auto collider: colliders) collider->getMaterial().setFrictionCoefficient(friction);
}

void Body::setRestitution(float restitution)
{
	//
	this->restitution = restitution;
	for(auto collider: colliders) collider->getMaterial().setBounciness(restitution);
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
