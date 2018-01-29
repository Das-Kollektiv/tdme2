#include <tdme/engine/physics/RigidBody.h>

#include <string>
#include <vector>

#include <ext/reactphysics3d/src/body/Body.h>
#include <ext/reactphysics3d/src/body/CollisionBody.h>
#include <ext/reactphysics3d/src/body/RigidBody.h>
#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/mathematics/Transform.h>

#include <tdme/math/Math.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/ConcaveMesh.h>
#include <tdme/engine/primitives/HeightField.h>
#include <tdme/engine/primitives/TerrainConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::string;
using std::to_string;
using std::vector;

using tdme::engine::physics::RigidBody;
using tdme::math::Math;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConcaveMesh;
using tdme::engine::primitives::HeightField;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::TerrainConvexMesh;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;

constexpr uint16_t RigidBody::TYPEIDS_ALL;
constexpr uint16_t RigidBody::TYPEID_STATIC;
constexpr uint16_t RigidBody::TYPEID_DYNAMIC;

RigidBody::RigidBody(World* world, const string& id, int type, bool enabled, uint16_t typeId, BoundingVolume* boundingVolume, Transformations* transformations, float restitution, float friction, float mass, const Matrix4x4& inverseInertiaMatrix)
{
	this->world = world;
	this->id = id;
	this->rootId = id;
	this->typeId = typeId;
	this->inverseInertiaMatrix.set(inverseInertiaMatrix);
	// do not clone concave mesh or height fields
	// TODO: Note this is not working yet
	if (dynamic_cast<ConcaveMesh*>(boundingVolume) != nullptr ||
		dynamic_cast<HeightField*>(boundingVolume) != nullptr) {
		this->boundingVolume = boundingVolume;
		this->rigidBody = this->world->world.createCollisionBody(reactphysics3d::Transform());
		this->proxyShape = getCollisionBody()->addCollisionShape(this->boundingVolume->collisionShape, reactphysics3d::Transform());
		this->proxyShape->setCollideWithMaskBits(~typeId);
		getCollisionBody()->setType(reactphysics3d::BodyType::STATIC);
	} else
	if (dynamic_cast<TerrainConvexMesh*>(boundingVolume) != nullptr) {
		// transform terrain convex mesh with transformations
		this->boundingVolume = boundingVolume->clone();
		dynamic_cast<TerrainConvexMesh*>(this->boundingVolume)->applyTransformations(transformations);
		// determine position
		auto positionTransformed = dynamic_cast<TerrainConvexMesh*>(this->boundingVolume)->getPositionTransformed();
		this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
		getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
		getRigidBody()->getMaterial().setFrictionCoefficient(friction);
		getRigidBody()->getMaterial().setBounciness(restitution);
		getRigidBody()->setMass(mass);
		this->proxyShape = getRigidBody()->addCollisionShape(this->boundingVolume->collisionShape, this->boundingVolume->collisionShapeLocalTransform, mass);
		this->proxyShape->setCollideWithMaskBits(~typeId);
		Transformations terrainTransformations;
		terrainTransformations.getTranslation().set(positionTransformed.getX(), positionTransformed.getY(), positionTransformed.getZ());
		fromTransformations(&terrainTransformations);
	} else
	{
		this->boundingVolume = boundingVolume->clone();
		this->rigidBody = this->world->world.createRigidBody(reactphysics3d::Transform());
		switch (type) {
			case TYPE_STATIC:
				getRigidBody()->setType(reactphysics3d::BodyType::STATIC);
				break;
			case TYPE_DYNAMIC:
				getRigidBody()->setType(reactphysics3d::BodyType::DYNAMIC);
				break;
			case TYPE_KINEMATIC:
				getRigidBody()->setType(reactphysics3d::BodyType::KINEMATIC);
				break;
		}
		auto& inverseInertiaMatrixArray = inverseInertiaMatrix.getArray();
		getRigidBody()->setInverseInertiaTensorLocal(
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
		getRigidBody()->getMaterial().setFrictionCoefficient(friction);
		getRigidBody()->getMaterial().setBounciness(restitution);
		getRigidBody()->setMass(mass);
		this->proxyShape = getRigidBody()->addCollisionShape(this->boundingVolume->collisionShape, this->boundingVolume->collisionShapeLocalTransform, mass);
		this->proxyShape->setCollideWithMaskBits(~0);
		fromTransformations(transformations);
	}
	this->rigidBody->setUserData(this);
	this->proxyShape->setCollisionCategoryBits(typeId);
	setEnabled(enabled);
}

RigidBody::~RigidBody() {
	if (dynamic_cast<ConcaveMesh*>(boundingVolume) == nullptr &&
		dynamic_cast<HeightField*>(boundingVolume) == nullptr) {
		delete boundingVolume;
	}
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
	return typeId;
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
	return getRigidBody()->getType() == reactphysics3d::BodyType::STATIC;
}

bool RigidBody::isSleeping()
{
	return rigidBody->isSleeping();
}

BoundingVolume* RigidBody::getBoundingVolume()
{
	return boundingVolume;
}

Vector3& RigidBody::getPosition()
{
	return transformations.getTranslation();
}

float RigidBody::getFriction()
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return 0.0f;
	return rigidBody->getMaterial().getFrictionCoefficient();
}

void RigidBody::setFriction(float friction)
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return;
	rigidBody->getMaterial().setFrictionCoefficient(friction);
}

float RigidBody::getRestitution()
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return 0.0f;
	return rigidBody->getMaterial().getBounciness();
}

void RigidBody::setRestitution(float restitution)
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return;
	rigidBody->getMaterial().setBounciness(restitution);
}

float RigidBody::getMass()
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return 0.0f;
	return rigidBody->getMass();
}

void RigidBody::setMass(float mass)
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return;
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

Transformations* RigidBody::getTransformations() {
	return &transformations;
}

void RigidBody::fromTransformations(Transformations* transformations)
{
	if (dynamic_cast<ConcaveMesh*>(boundingVolume) != nullptr ||
		dynamic_cast<HeightField*>(boundingVolume) != nullptr) {
		Console::println("RigidBody::fromTransformations(): not supported with concave mesh, height field or terrain convex mesh");
		return;
	}
	// store engine transformations
	this->transformations.fromTransformations(transformations);
	// obv
	boundingVolume->collisionShape->setLocalScaling(
		reactphysics3d::Vector3(
			transformations->getScale().getX(),
			transformations->getScale().getY(),
			transformations->getScale().getZ()
		)
	);
	// rigig body transform
	auto& transformationsMatrix = this->transformations.getTransformationsMatrix();
	reactphysics3d::Transform transform;
	transform.setFromOpenGL(transformationsMatrix.getArray().data());
	auto rigidBody = getRigidBody();
	if (rigidBody != nullptr) rigidBody->setTransform(transform);
	auto collisionBody = getCollisionBody();
	if (collisionBody != nullptr) collisionBody->setTransform(transform);
}

void RigidBody::addForce(const Vector3& forceOrigin, const Vector3& force)
{
	auto rigidBody = getRigidBody();
	if (rigidBody == nullptr) return;
	rigidBody->applyForce(
		reactphysics3d::Vector3(force.getX(), force.getY(), force.getZ()),
		reactphysics3d::Vector3(forceOrigin.getX(), forceOrigin.getY(), forceOrigin.getZ())
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
