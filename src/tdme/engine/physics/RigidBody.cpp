// Generated from /tdme/src/tdme/engine/physics/RigidBody.java
#include <tdme/engine/physics/RigidBody.h>

#include <vector>

#include <java/lang/Math.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionListener.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>

using std::vector;

using tdme::engine::physics::RigidBody;
using java::lang::Math;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionListener;
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::_Console;


RigidBody::RigidBody(World* world, const wstring& id, bool enabled, int32_t typeId, BoundingVolume* obv, Transformations* transformations, float restitution, float friction, float mass, Matrix4x4* inverseInertia)
{
	this->world = world;
	this->idx = -1;
	this->id = id;
	this->enabled = enabled;
	this->typeId = typeId;
	this->collisionTypeIds = TYPEIDS_ALL;
	this->transformations = new Transformations();
	this->inverseInertia = inverseInertia;
	this->restitution = restitution;
	this->friction = friction;
	this->isSleeping_ = false;
	this->sleepingFrameCount = 0;
	setBoundingVolume(obv);
	setMass(mass);
	synch(transformations);
	computeWorldInverseInertiaMatrix();
}

constexpr int32_t RigidBody::TYPEIDS_ALL;

constexpr float RigidBody::VELOCITY_SLEEPTOLERANCE;

constexpr int32_t RigidBody::SLEEPING_FRAMES;

Matrix4x4* RigidBody::getNoRotationInertiaMatrix()
{
	return new Matrix4x4(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4x4* RigidBody::computeInertiaMatrix(BoundingVolume* bv, float mass, float scaleXAxis, float scaleYAxis, float scaleZAxis)
{
	auto width = bv->computeDimensionOnAxis(&OrientedBoundingBox::AABB_AXIS_X);
	auto height = bv->computeDimensionOnAxis(&OrientedBoundingBox::AABB_AXIS_Y);
	auto depth = bv->computeDimensionOnAxis(&OrientedBoundingBox::AABB_AXIS_Z);
	return
		(new Matrix4x4(
			scaleXAxis * 1.0f / 12.0f * mass * (height * height + depth * depth), 0.0f, 0.0f, 0.0f,
			0.0f, scaleYAxis * 1.0f / 12.0f * mass * (width * width + depth * depth), 0.0f, 0.0f,
			0.0f, 0.0f, scaleZAxis * 1.0f / 12.0f * mass * (width * width + height * height), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		))->invert();
}

void RigidBody::setIdx(int32_t idx)
{
	this->idx = idx;
}

int32_t RigidBody::getIdx()
{
	return idx;
}

const wstring& RigidBody::getId()
{
	return id;
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
	if (this->enabled == enabled)
		return;

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

Transformations* RigidBody::getTransformations()
{
	return transformations;
}

BoundingVolume* RigidBody::getBoudingVolume()
{
	return obv;
}

void RigidBody::setBoundingVolume(BoundingVolume* obv)
{
	this->obv = obv;
	this->cbv = this->obv == nullptr ? nullptr : obv->clone();
}

BoundingVolume* RigidBody::getBoundingVolumeTransformed()
{
	return cbv;
}

Vector3* RigidBody::getPosition()
{
	return &position;
}

Vector3* RigidBody::getMovement()
{
	return &movement;
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
	if (Math::abs(mass) < MathTools::EPSILON) {
		this->isStatic_ = true;
		this->inverseMass = 0.0f;
	} else {
		this->isStatic_ = false;
		this->inverseMass = 1.0f / mass;
	}
}

Vector3* RigidBody::getLinearVelocity()
{
	return &linearVelocity;
}

Vector3* RigidBody::getAngularVelocity()
{
	return &angularVelocity;
}

Vector3* RigidBody::getForce()
{
	return &force;
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
	orientation.computeMatrix(&orientationMatrix);
	worldInverseInertia.set(&orientationMatrix)->transpose()->multiply(&inverseInertia)->multiply(&orientationMatrix);
}

void RigidBody::synch(Transformations* transformations)
{
	this->transformations->fromTransformations(transformations);
	if (this->cbv != nullptr)
		this->cbv->fromBoundingVolumeWithTransformations(this->obv, this->transformations);

	this->position.set(this->transformations->getTranslation());
	this->orientation.identity();
	for (auto i = 0; i < this->transformations->getRotations()->size(); i++) {
		auto r = this->transformations->getRotations()->get(i);
		this->orientation.multiply(r->getQuaternion());
	}
	(*this->orientation.getArray())[1] *= -1.0f;
	this->orientation.normalize();
	this->awake(true);
}

void RigidBody::addForce(Vector3* forceOrigin, Vector3* force)
{
	if (isStatic_ == true)
		return;

	if (force->computeLength() < MathTools::EPSILON)
		return;

	awake(false);
	this->force.add(force);
	Vector3 distance;
	Vector3 tmp;
	distance.set(forceOrigin)->sub(&position);
	if (distance.computeLength() < MathTools::EPSILON) {
		_Console::println(
			wstring(L"RigidBody::addForce(): ") +
			id +
			wstring(L": Must not equals position")
		);
	}
	Vector3::computeCrossProduct(force, &distance, &tmp);
	this->torque.add(&tmp);
}

void RigidBody::update(float deltaTime)
{
	if (isSleeping_ == true)
		return;

	if (linearVelocity.computeLength() < VELOCITY_SLEEPTOLERANCE && angularVelocity.computeLength() < VELOCITY_SLEEPTOLERANCE) {
		sleepingFrameCount++;
		if (sleepingFrameCount >= SLEEPING_FRAMES) {
			sleep();
		}
	} else {
		awake(true);
	}
	if (isSleeping_ == true) {
		linearVelocity.set(0.0f, 0.0f, 0.0f);
		angularVelocity.set(0.0f, 0.0f, 0.0f);
		return;
	}
	Vector3 tmpVector3;
	Quaternion tmpQuaternion1;
	Quaternion tmpQuaternion2;
	movement.set(&position);
	position.add(tmpVector3.set(&linearVelocity)->scale(deltaTime));
	movement.sub(&position);
	movement.scale(-1.0f);
	auto angularVelocityXYZ = angularVelocity.getArray();
	tmpQuaternion2.set((*angularVelocityXYZ)[0], -(*angularVelocityXYZ)[1], (*angularVelocityXYZ)[2], 0.0f)->scale(0.5f * deltaTime);
	tmpQuaternion1.set(&orientation);
	tmpQuaternion1.multiply(&tmpQuaternion2);
	orientation.add(&tmpQuaternion1);
	orientation.normalize();
	force.set(0.0f, 0.0f, 0.0f);
	torque.set(0.0f, 0.0f, 0.0f);
	linearVelocityLast.set(&linearVelocity);
	angularVelocityLast.set(&angularVelocity);
	computeWorldInverseInertiaMatrix();
}

bool RigidBody::checkVelocityChange()
{
	Vector3 tmpVector3;

	if (tmpVector3.set(&linearVelocity)->sub(&linearVelocityLast)->computeLength() > VELOCITY_SLEEPTOLERANCE)
		return true;

	if (tmpVector3.set(&angularVelocity)->sub(&angularVelocityLast)->computeLength() > VELOCITY_SLEEPTOLERANCE)
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
