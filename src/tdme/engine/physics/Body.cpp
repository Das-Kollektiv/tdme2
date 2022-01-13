#include <string>
#include <vector>

#include <ext/reactphysics3d/src/body/Body.h>
#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/collision/narrowphase/DefaultCollisionDispatch.h>
#include <ext/reactphysics3d/src/collision/narrowphase/NarrowPhaseAlgorithm.h>
#include <ext/reactphysics3d/src/collision/shapes/CollisionShape.h>
#include <ext/reactphysics3d/src/collision/CollisionCallback.h>
#include <ext/reactphysics3d/src/collision/NarrowPhaseInfo.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/constraint/ContactPoint.h>
#include <ext/reactphysics3d/src/engine/CollisionWorld.h>
#include <ext/reactphysics3d/src/engine/DynamicsWorld.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>
#include <ext/reactphysics3d/src/mathematics/Vector3.h>
#include <ext/reactphysics3d/src/memory/MemoryAllocator.h>

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
#include <tdme/engine/Transformations.h>
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
using tdme::engine::Transformations;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Console;

constexpr uint16_t Body::TYPEIDS_ALL;
constexpr uint16_t Body::TYPEID_STATIC;
constexpr uint16_t Body::TYPEID_DYNAMIC;

Body::Body(World* world, const string& id, BodyType bodyType, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*> boundingVolumes)
{
	this->world = world;
	this->id = id;
	this->inertiaTensor = inertiaTensor;
	this->bodyType = bodyType;
	this->mass = mass;
	this->collideTypeIds = ~0;
	this->collisionTypeId = collisionTypeId;
	switch (bodyType) {
		case BODYTYPE_STATIC:
			this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::STATIC);
			this->collisionBody = rigidBody;
			break;
		case BODYTYPE_DYNAMIC:
			this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::DYNAMIC);
			this->collisionBody = rigidBody;
			break;
		case BODYTYPE_KINEMATIC:
			this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
			this->rigidBody->setType(reactphysics3d::BodyType::KINEMATIC);
			this->collisionBody = rigidBody;
			break;
		case BODYTYPE_COLLISION:
			this->rigidBody = nullptr;
			this->collisionBody = this->world->world.createCollisionBody(reactphysics3d::Transform());
			break;
		default:
			Console::println("Body::Body(): unsupported type: " + to_string(bodyType) + ": using collision body");
			this->rigidBody = nullptr;
			this->collisionBody = this->world->world.createCollisionBody(reactphysics3d::Transform());
			break;
	}
	if (rigidBody != nullptr) {
		rigidBody->getMaterial().setFrictionCoefficient(friction);
		rigidBody->getMaterial().setBounciness(restitution);
		rigidBody->setMass(mass);
	}
	collisionBody->setUserData(this);
	for (auto boundingVolume: boundingVolumes) {
		this->boundingVolumes.push_back(dynamic_cast<TerrainMesh*>(boundingVolume) != nullptr?boundingVolume:boundingVolume->clone());
	}
	fromTransformations(transformations);
	setEnabled(enabled);
}

Body::~Body() {
	for (auto boundingVolume: boundingVolumes) {
		if (dynamic_cast<TerrainMesh*>(boundingVolume) != nullptr && cloned == true) continue;
		delete boundingVolume;
	}
}

void Body::setCollisionTypeId(uint16_t typeId)
{
	this->collisionTypeId = typeId;
	for (auto proxyShape: proxyShapes) {
		proxyShape->setCollisionCategoryBits(typeId);
	}
}

void Body::setCollisionTypeIds(uint16_t collisionTypeIds)
{
	this->collideTypeIds = collisionTypeIds;
	for (auto proxyShape: proxyShapes) {
		proxyShape->setCollideWithMaskBits(collisionTypeIds);
	}
}

void Body::resetProxyShapes() {
	// remove proxy shapes
	for (auto proxyShape: proxyShapes) {
		if (rigidBody != nullptr) {
			rigidBody->removeCollisionShape(proxyShape);
		} else {
			collisionBody->removeCollisionShape(proxyShape);
		}
	}
	proxyShapes.clear();

	// set up scale
	for (auto boundingVolume: boundingVolumes) {
		// scale bounding volume and recreate it if nessessary
		if (boundingVolume->getScale().equals(transformations.getScale()) == false) {
			boundingVolume->setScale(transformations.getScale());
		}
	}

	// reset proxy shapes with mass
	if (mass > Math::EPSILON) {
		// determine total volume
		float volumeTotal = 0.0f;
		for (auto boundingVolume: boundingVolumes) {
			volumeTotal+=
				boundingVolume->boundingBoxTransformed.getDimensions().getX() *
				boundingVolume->boundingBoxTransformed.getDimensions().getY() *
				boundingVolume->boundingBoxTransformed.getDimensions().getZ();
		}
		// add bounding volumes with mass
		for (auto boundingVolume: boundingVolumes) {
			reactphysics3d::ProxyShape* proxyShape = nullptr;
			float volumeBoundingVolume =
				boundingVolume->boundingBoxTransformed.getDimensions().getX() *
				boundingVolume->boundingBoxTransformed.getDimensions().getY() *
				boundingVolume->boundingBoxTransformed.getDimensions().getZ();
			if (rigidBody != nullptr) {
				proxyShape = rigidBody->addCollisionShape(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform, mass / volumeTotal * volumeBoundingVolume);
			} else {
				proxyShape = collisionBody->addCollisionShape(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform);
			}
			proxyShapes.push_back(proxyShape);
		}
	} else {
		// add bounding volumes without mass
		for (auto boundingVolume: boundingVolumes) {
			reactphysics3d::ProxyShape* proxyShape = nullptr;
			if (rigidBody != nullptr) {
				proxyShape = rigidBody->addCollisionShape(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform, 0.0f);
			} else {
				proxyShape = collisionBody->addCollisionShape(boundingVolume->collisionShape, boundingVolume->collisionShapeLocalTransform);
			}
			proxyShapes.push_back(proxyShape);
		}
	}

	// set up collisioin type ids and type id
	for (auto proxyShape: proxyShapes) {
		proxyShape->setCollideWithMaskBits(collideTypeIds);
		proxyShape->setCollisionCategoryBits(collisionTypeId);
	}

	// set up inverse inertia tensor local
	if (rigidBody != nullptr) {
		// set inverse inertia tensor local
		// 	TODO: transform with identity transform, this is a bit sub optimal but currently required to get rigid body dimensions
		// 	this method is only used when setting TDME2 transform, so no need to transform back
		reactphysics3d::Transform transform;
		collisionBody->setTransform(transform);

		auto boundingBoxTransformed = computeBoundingBoxTransformed();
		auto& inverseInertiaMatrixArray = computeInverseInertiaMatrix(&boundingBoxTransformed, mass, inertiaTensor.getX(), inertiaTensor.getY(), inertiaTensor.getZ()).getArray();
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

void Body::fromTransformations(const Transformations& transformations)
{
	// store engine transformations
	this->transformations.fromTransformations(transformations);

	// reset proxy shapes if bounding volumes do not match proxy shapes or if scaling has changed
	if (proxyShapes.size() != boundingVolumes.size() || transformationsScale.equals(transformations.getScale()) == false) {
		resetProxyShapes();
		transformationsScale.set(transformations.getScale());
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
				this->transformations.getTranslation().getX(),
				this->transformations.getTranslation().getY(),
				this->transformations.getTranslation().getZ()
			),
			reactphysics3d::Quaternion(
				this->transformations.getRotationsQuaternion().getX(),
				this->transformations.getRotationsQuaternion().getY(),
				this->transformations.getRotationsQuaternion().getZ(),
				this->transformations.getRotationsQuaternion().getW()
			)
		)
	);
}

void Body::addCollisionListener(CollisionListener* listener)
{
	removeCollisionListener(listener);
	collisionListener.push_back(listener);
}

void Body::removeCollisionListener(CollisionListener* listener)
{
	collisionListener.erase(remove(collisionListener.begin(), collisionListener.end(), listener), collisionListener.end());
}
