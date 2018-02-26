#include <tdme/engine/physics/RigidBody.h>

#include <string>
#include <vector>

#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
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
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;


RigidBody::RigidBody(World* world, const string& id, bool enabled, int32_t typeId, BoundingVolume* obv, const Transformations& transformations, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inverseInertiaSettings)
{
	this->world = world;
	this->idx = -1;
	this->id = id;
	this->rootId = id;
	this->enabled = enabled;
	this->typeId = typeId;
	this->collisionTypeIds = TYPEIDS_ALL;
	this->inverseInertiaSettings = inverseInertiaSettings;
	this->restitution = restitution;
	this->friction = friction;
	this->isSleeping_ = false;
	this->sleepingFrameCount = 0;
	setBoundingVolume(obv);
	setMass(mass);
	fromTransformations(transformations);
}

RigidBody::~RigidBody() {
	delete obv;
	delete cbv;
}

constexpr int32_t RigidBody::TYPEIDS_ALL;

constexpr float RigidBody::LINEARVELOCITY_SLEEPTOLERANCE;
constexpr float RigidBody::ANGULARVELOCITY_SLEEPTOLERANCE;

constexpr int32_t RigidBody::SLEEPING_FRAMES;

RigidBody::InertiaMatrixSettings RigidBody::getNoRotationInertiaMatrix()
{
	RigidBody::InertiaMatrixSettings inertiaMatrix;
	inertiaMatrix.noInertiaMatrix = true;
	inertiaMatrix.mass = 0.0f;
	inertiaMatrix.scaleX = 0.0f;
	inertiaMatrix.scaleY = 0.0f;
	inertiaMatrix.scaleZ = 0.0f;
	return inertiaMatrix;
}

RigidBody::InertiaMatrixSettings RigidBody::computeInertiaMatrix(BoundingVolume* bv, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis)
{
	RigidBody::InertiaMatrixSettings inertiaMatrix;
	inertiaMatrix.noInertiaMatrix = false;
	inertiaMatrix.mass = mass;
	inertiaMatrix.scaleX = scaleXAxis;
	inertiaMatrix.scaleY = scaleYAxis;
	inertiaMatrix.scaleZ = scaleZAxis;
	return inertiaMatrix;
}

Matrix4x4 RigidBody::_getNoRotationInertiaMatrix()
{
	return Matrix4x4(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4 RigidBody::_computeInertiaMatrix(BoundingVolume* bv, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis)
{
	auto width = bv->computeDimensionOnAxis(OrientedBoundingBox::AABB_AXIS_X) * scaleXAxis;
	auto height = bv->computeDimensionOnAxis(OrientedBoundingBox::AABB_AXIS_Y) * scaleYAxis;
	auto depth = bv->computeDimensionOnAxis(OrientedBoundingBox::AABB_AXIS_Z) * scaleZAxis;
	return
		(Matrix4x4(
			1.0f / 12.0f * mass * (height * height + depth * depth), 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f / 12.0f * mass * (width * width + depth * depth), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f / 12.0f * mass * (width * width + height * height), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		)).invert();
}

void RigidBody::setIdx(int32_t idx)
{
	this->idx = idx;
}

int32_t RigidBody::getIdx()
{
	return idx;
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

int32_t RigidBody::getTypeId()
{
	return typeId;
}

int32_t RigidBody::getCollisionTypeIds()
{
	return collisionTypeIds;
}

void RigidBody::setCollisionTypeIds(int32_t collisionTypeIds)
{
	this->collisionTypeIds = collisionTypeIds;
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
		world->partition->addRigidBody(this);
	} else {
		world->partition->removeRigidBody(this);
	}
	this->enabled = enabled;
}

bool RigidBody::isStatic()
{
	return isStatic_;
}

bool RigidBody::isSleeping()
{
	return isSleeping_;
}

const Transformations& RigidBody::getTransformations()
{
	return transformations;
}

BoundingVolume* RigidBody::getBoudingVolume()
{
	return obv;
}

void RigidBody::setBoundingVolume(BoundingVolume* obv)
{
	if (this->obv == nullptr) delete this->obv;
	this->obv = obv->clone();
	if (this->cbv == nullptr) delete this->cbv;
	this->cbv = obv->clone();
}

BoundingVolume* RigidBody::getBoundingVolumeTransformed()
{
	return cbv;
}

Vector3& RigidBody::getPosition()
{
	return position;
}

Vector3& RigidBody::getMovement()
{
	return movement;
}

float RigidBody::getFriction()
{
	return friction;
}

void RigidBody::setFriction(float friction)
{
	this->friction = friction;
}

float RigidBody::getRestitution()
{
	return restitution;
}

void RigidBody::setRestitution(float restitution)
{
	this->restitution = restitution;
}

float RigidBody::getMass()
{
	return mass;
}

void RigidBody::setMass(float mass)
{
	this->mass = mass;
	if (Math::abs(mass) < Math::EPSILON) {
		this->isStatic_ = true;
		this->inverseMass = 0.0f;
	} else {
		this->isStatic_ = false;
		this->inverseMass = 1.0f / mass;
	}
}

Vector3& RigidBody::getLinearVelocity()
{
	return linearVelocity;
}

Vector3& RigidBody::getAngularVelocity()
{
	return angularVelocity;
}

Vector3& RigidBody::getForce()
{
	return force;
}

void RigidBody::awake(bool resetFrameCount)
{
	isSleeping_ = false;
	if (resetFrameCount) sleepingFrameCount = 0;
}

void RigidBody::sleep()
{
	isSleeping_ = true;
	sleepingFrameCount = 0;
}

void RigidBody::computeWorldInverseInertiaMatrix()
{
	Matrix4x4 inverseInertiaMatrix;
	if (inverseInertiaSettings.noInertiaMatrix == true) {
		inverseInertiaMatrix = _getNoRotationInertiaMatrix();
	} else {
		inverseInertiaMatrix = _computeInertiaMatrix(
			this->obv,
			inverseInertiaSettings.mass,
			inverseInertiaSettings.scaleX * this->transformations.getScale().getX(),
			inverseInertiaSettings.scaleY * this->transformations.getScale().getY(),
			inverseInertiaSettings.scaleZ * this->transformations.getScale().getZ()
		);
	}
	orientation.computeMatrix(orientationMatrix);
	worldInverseInertia.set(orientationMatrix).transpose().multiply(inverseInertiaMatrix).multiply(orientationMatrix);
}

void RigidBody::fromTransformations(const Transformations& transformations)
{
	this->transformations.fromTransformations(transformations);
	this->cbv->fromBoundingVolumeWithTransformations(this->obv, this->transformations);
	this->transformations.getTransformationsMatrix().multiply(Vector3(0.0f, 0.0f, 0.0f), this->position);
	this->orientation.set(this->transformations.getRotationsQuaternion());
	this->orientation.getArray()[1] *= -1.0f;
	this->orientation.normalize();
	this->computeWorldInverseInertiaMatrix();
	this->awake(true);
}

void RigidBody::addForce(const Vector3& forceOrigin, const Vector3& force)
{
	// skip on static objects
	if (isStatic_ == true)
		return;

	// check if we have any force to apply
	if (force.computeLength() < Math::EPSILON)
		return;

	// unset sleeping
	awake(false);

	// linear
	this->force.add(force);

	// angular
	Vector3 distance;
	Vector3 tmp;
	distance.set(forceOrigin).sub(position);
	if (distance.computeLength() < Math::EPSILON) {
		Console::println(
			string("RigidBody::addForce(): ") +
			id +
			string(": Must not equals position")
		);
	}
	Vector3::computeCrossProduct(force, distance, tmp);
	this->torque.add(tmp);
}

void RigidBody::update(float deltaTime)
{
	if (isSleeping_ == true)
		return;

	// check if to put object into sleep
	if (linearVelocity.computeLength() < LINEARVELOCITY_SLEEPTOLERANCE && angularVelocity.computeLength() < ANGULARVELOCITY_SLEEPTOLERANCE) {
		sleepingFrameCount++;
		if (sleepingFrameCount >= SLEEPING_FRAMES) {
			sleep();
		}
	} else {
		awake(true);
	}
	// unset velocity if sleeping
	if (isSleeping_ == true) {
		linearVelocity.set(0.0f, 0.0f, 0.0f);
		angularVelocity.set(0.0f, 0.0f, 0.0f);
		return;
	}
	// linear
	Vector3 tmpVector3;
	Quaternion tmpQuaternion1;
	Quaternion tmpQuaternion2;
	movement.set(position);
	position.add(tmpVector3.set(linearVelocity).scale(deltaTime));
	movement.sub(position);
	movement.scale(-1.0f);
	// angular
	auto& angularVelocityXYZ = angularVelocity.getArray();
	tmpQuaternion2.set(angularVelocityXYZ[0], -angularVelocityXYZ[1], angularVelocityXYZ[2], 0.0f).scale(0.5f * deltaTime);
	tmpQuaternion1.set(orientation);
	tmpQuaternion1.multiply(tmpQuaternion2);
	orientation.add(tmpQuaternion1);
	orientation.normalize();
	//
	force.set(0.0f, 0.0f, 0.0f);
	torque.set(0.0f, 0.0f, 0.0f);
	// store last velocities
	linearVelocityLast.set(linearVelocity);
	angularVelocityLast.set(angularVelocity);
	computeWorldInverseInertiaMatrix();
}

bool RigidBody::checkVelocityChange()
{
	Vector3 tmpVector3;

	if (tmpVector3.set(linearVelocity).sub(linearVelocityLast).computeLength() > LINEARVELOCITY_SLEEPTOLERANCE)
		return true;

	if (tmpVector3.set(angularVelocity).sub(angularVelocityLast).computeLength() > ANGULARVELOCITY_SLEEPTOLERANCE)
		return true;

	return false;
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
