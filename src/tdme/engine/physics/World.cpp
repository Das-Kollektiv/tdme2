#include <tdme/engine/physics/World.h>

#include <map>
#include <string>

#include <tdme/math/Math.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/ConstraintsEntity.h>
#include <tdme/engine/physics/ConstraintsSolver.h>
#include <tdme/engine/physics/PhysicsPartition.h>
#include <tdme/engine/physics/PhysicsPartitionOctTree.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/VectorIteratorMultiple.h>
#include <tdme/utils/Pool.h>
#include <tdme/utils/Console.h>

using std::map;
using std::string;
using std::to_string;

using tdme::engine::physics::World;
using tdme::math::Math;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsEntity;
using tdme::engine::physics::ConstraintsSolver;
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::VectorIteratorMultiple;
using tdme::utils::Pool;
using tdme::utils::Console;

World::World() 
{
	partition = new PhysicsPartitionOctTree();
	updateRigidBodyIndices = true;
}

World::~World()
{
	reset();
	if (constraintsSolver != nullptr) delete constraintsSolver;
	if (partition != nullptr) delete partition;
}

void World::reset()
{
	for (auto rigidBody: rigidBodies) {
		delete rigidBody;
	}
	rigidBodies.clear();
	rigidBodiesDynamic.clear();
	rigidBodiesById.clear();
	partition->reset();
	updateRigidBodyIndices = true;
}

PhysicsPartition* World::getPartition()
{
	return partition;
}

void World::setPartition(PhysicsPartition* partition)
{
	if (this->partition != nullptr) delete this->partition;
	this->partition = partition;
}

RigidBody* World::addRigidBody(const string& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix)
{
	auto rigidBody = new RigidBody(this, id, enabled, typeId, obv, transformations, restitution, friction, mass, inertiaMatrix);
	rigidBodies.push_back(rigidBody);
	rigidBodiesDynamic.push_back(rigidBody);
	rigidBodiesById[id] = rigidBody;
	if (enabled == true) partition->addRigidBody(rigidBody);
	updateRigidBodyIndices = true;
	return rigidBody;
}

RigidBody* World::addStaticRigidBody(const string& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float friction)
{
	auto rigidBody = new RigidBody(this, id, enabled, typeId, obv, transformations, 0.0f, friction, 0.0f, RigidBody::computeInertiaMatrix(obv, 0.0f, 0.0f, 0.0f, 0.0f));
	rigidBodies.push_back(rigidBody);
	rigidBodiesById[id] = rigidBody;
	if (enabled == true) partition->addRigidBody(rigidBody);
	updateRigidBodyIndices = true;
	return rigidBody;
}

RigidBody* World::getRigidBody(const string& id)
{
	auto rididBodyByIdIt = rigidBodiesById.find(id);
	if (rididBodyByIdIt != rigidBodiesById.end()) {
		return rididBodyByIdIt->second;
	}
	return nullptr;
}

void World::doCollisionTest(RigidBody* rigidBody1, RigidBody* rigidBody2, map<string, RigidBodyCollisionStruct>& rigidBodyTestedCollisions, map<string, RigidBodyCollisionStruct>& rigidBodyCollisionsCurrentFrame, Vector3& collisionMovement, CollisionResponse &collision, bool useAndInvertCollision) {
	string rigidBodyKey = to_string(rigidBody1->idx) + "," + to_string(rigidBody2->idx);
	if (rigidBodyTestedCollisions.find(rigidBodyKey) != rigidBodyTestedCollisions.end()) return;
	RigidBodyCollisionStruct rigidBodyCollisionStruct;
	rigidBodyCollisionStruct.rigidBody1Idx = rigidBody1->idx;
	rigidBodyCollisionStruct.rigidBody2Idx = rigidBody2->idx;
	rigidBodyTestedCollisions[rigidBodyKey] = rigidBodyCollisionStruct;
	if (useAndInvertCollision == false) {
		collisionMovement.set(rigidBody1->movement);
		if (collisionMovement.computeLength() < MathTools::EPSILON) {
			collisionMovement.set(rigidBody2->movement);
			collisionMovement.scale(-1.0f);
		}
	} else {
		collision.invertNormals();
	}
	if (useAndInvertCollision == true || (rigidBody1->cbv->doesCollideWith(rigidBody2->cbv, collisionMovement, &collision) == true && collision.hasPenetration() == true)) {
		if (collision.getHitPointsCount() == 0) return;

		rigidBodyCollisionsCurrentFrame[rigidBodyKey] = rigidBodyCollisionStruct;
		if (rigidBodyCollisionsLastFrame.find(rigidBodyKey) == rigidBodyCollisionsLastFrame.end()) {
			rigidBody1->fireOnCollisionBegin(rigidBody2, &collision);
		}
		rigidBody1->fireOnCollision(rigidBody2, &collision);
		if (rigidBody1->isStatic_ == false && rigidBody2->isStatic_ == false) {
			rigidBody1->awake(true);
			rigidBody2->awake(true);
		}
		constraintsSolver->allocateConstraintsEntity()->set(rigidBody1, rigidBody2, &collision);
	}
}

void World::update(float deltaTime)
{
	if (updateRigidBodyIndices == true) {
		int rigidBodyIdx = 0;
		for (auto rigidBody: rigidBodies) {
			rigidBody->idx = rigidBodyIdx++;
		}
		updateRigidBodyIndices = false;
	}
	if (constraintsSolver == nullptr) {
		constraintsSolver = new ConstraintsSolver(&rigidBodies);
	}
	{
		Vector3 worldPosForce;
		Vector3 gravityForce;
		for (auto i = 0; i < rigidBodies.size(); i++) {
			auto rigidBody = rigidBodies.at(i);
			if (rigidBody->enabled == false) {
				continue;
			}
			if (rigidBody->isStatic_ == true) {
				continue;
			}
			if (rigidBody->checkVelocityChange() == true) {
				rigidBody->awake(true);
			}
			if (rigidBody->isSleeping_ == true) {
				continue;
			}
			rigidBody->addForce(
				worldPosForce.set(rigidBody->getPosition()).setY(10000.0f),
				gravityForce.set(0.0f, -rigidBody->getMass() * MathTools::g, 0.0f)
			);
		}
	}
	{
		auto collisionTests = 0;
		Vector3 collisionMovement;
		CollisionResponse collision;
		map<string, RigidBodyCollisionStruct> rigidBodyTestedCollisions;
		map<string, RigidBodyCollisionStruct> rigidBodyCollisionsCurrentFrame;
		for (auto i = 0; i < rigidBodies.size(); i++) {
			auto rigidBody1 = rigidBodies.at(i);
			if (rigidBody1->enabled == false) continue;
			if (rigidBody1->isStatic_ == true) continue;
			auto nearObjects = 0;
			for (auto _i = partition->getObjectsNearTo(rigidBody1->cbv)->iterator(); _i->hasNext(); ) {
				RigidBody* rigidBody2 = _i->next();

				if (rigidBody2->enabled == false)
					continue;

				if (rigidBody1 == rigidBody2)
					continue;

				if (rigidBody1->isStatic_ == true && rigidBody2->isStatic_ == true)
					continue;

				if (rigidBody1->isStatic_ == true && rigidBody2->isStatic_ == false && rigidBody2->isSleeping_ == true) {
					continue;
				}
				if (rigidBody2->isStatic_ == true && rigidBody1->isStatic_ == false && rigidBody1->isSleeping_ == true) {
					continue;
				}

				if (((rigidBody1->typeId & rigidBody2->collisionTypeIds) == rigidBody1->typeId) == false) {
					continue;
				}
				if (((rigidBody2->typeId & rigidBody1->collisionTypeIds) == rigidBody2->typeId) == false) {
					continue;
				}
				nearObjects++;
				collisionTests++;
				doCollisionTest(rigidBody1, rigidBody2, rigidBodyTestedCollisions, rigidBodyCollisionsCurrentFrame, collisionMovement, collision, false);
				doCollisionTest(rigidBody2, rigidBody1, rigidBodyTestedCollisions, rigidBodyCollisionsCurrentFrame, collisionMovement, collision, true);
			}
		}

		for (auto it: rigidBodyCollisionsLastFrame) {
			RigidBodyCollisionStruct* rigidBodyCollisionStruct = &it.second;
			{
				string rigidBodyKey = to_string(rigidBodyCollisionStruct->rigidBody1Idx) + "," + to_string(rigidBodyCollisionStruct->rigidBody2Idx);
				auto rigidBodyCollisionsCurrentFrameIt = rigidBodyCollisionsCurrentFrame.find(rigidBodyKey);
				if (rigidBodyCollisionsCurrentFrameIt != rigidBodyCollisionsCurrentFrame.end()) continue;
			}

			{
				string rigidBodyKey = to_string(rigidBodyCollisionStruct->rigidBody2Idx) + "," + to_string(rigidBodyCollisionStruct->rigidBody1Idx);
				auto rigidBodyCollisionsCurrentFrameIt = rigidBodyCollisionsCurrentFrame.find(rigidBodyKey);
				if (rigidBodyCollisionsCurrentFrameIt != rigidBodyCollisionsCurrentFrame.end()) continue;
			}

			auto rigidBody1 = rigidBodies.at(rigidBodyCollisionStruct->rigidBody1Idx);
			auto rigidBody2 = rigidBodies.at(rigidBodyCollisionStruct->rigidBody2Idx);
			rigidBody1->fireOnCollisionEnd(rigidBody2);
		}

		rigidBodyCollisionsLastFrame = rigidBodyCollisionsCurrentFrame;
		constraintsSolver->compute(deltaTime);
		constraintsSolver->updateAllBodies(deltaTime);
		constraintsSolver->reset();
	}

	for (auto i = 0; i < rigidBodies.size(); i++) {
		auto rigidBody = rigidBodies.at(i);
		if (rigidBody->enabled == false) {
			continue;
		}
		if (rigidBody->isStatic_ == true || rigidBody->isSleeping_ == true) {
			continue;
		}
		auto rotations = rigidBody->transformations->getRotations();
		while (rotations->size() > 1) {
			rotations->remove(rotations->size() - 1);
		}
		while (rotations->size() < 1) {
			rotations->add(new Rotation());
		}
		rotations->get(0)->fromQuaternion(rigidBody->orientation);
		rotations->get(0)->getAxis().getArray()[1] *= -1.0f;
		auto transformations = rigidBody->transformations;
		transformations->getTranslation().set(rigidBody->position);
		transformations->update();
		rigidBody->cbv->fromBoundingVolumeWithTransformations(rigidBody->obv, transformations);
		partition->updateRigidBody(rigidBody);
	}
}

void World::synch(Engine* engine)
{
	for (auto i = 0; i < rigidBodies.size(); i++) {
		auto rigidBody = rigidBodies.at(i);
		if (rigidBody->isStatic_ == true)
			continue;

		if (rigidBody->isSleeping_ == true)
			continue;

		auto engineEntity = engine->getEntity(rigidBody->id);
		if (engineEntity == nullptr) {
			Console::println(
				string("World::entity '") +
				rigidBody->id +
				string("' not found")
			);
			continue;
		}
		engineEntity->setEnabled(rigidBody->enabled);
		if (rigidBody->enabled == true) {
			engineEntity->fromTransformations(rigidBody->transformations);
		}
	}
}

const Vector3& World::higher(const Vector3& a, const Vector3& b)
{
	return a.getY() > b.getY() ? a : b;
}

RigidBody* World::determineHeight(int32_t typeIds, float stepUpMax, const Vector3& point, Vector3& dest)
{
	dest.set(point);
	auto& pointXYZ = point.getArray();
	BoundingBox heightBoundingBox;
	Vector3 heightOnPointCandidate;
	Vector3 heightOnPointA;
	Vector3 heightOnPointB;
	heightBoundingBox.getMin().set(pointXYZ[0], -10000.0f, pointXYZ[2]);
	heightBoundingBox.getMax().set(pointXYZ[0], +10000.0f, pointXYZ[2]);
	heightBoundingBox.update();
	heightOnPointCandidate.set(pointXYZ[0], 10000.0f, pointXYZ[2]);
	auto height = -10000.0f;
	RigidBody* heightRigidBody = nullptr;
	for (auto _i = partition->getObjectsNearTo(static_cast< BoundingVolume* >(&heightBoundingBox))->iterator(); _i->hasNext(); ) {
		RigidBody* rigidBody = _i->next();
		{
			if (((rigidBody->typeId & typeIds) == rigidBody->typeId) == false)
				continue;

			auto cbv = rigidBody->cbv;
			if (dynamic_cast< BoundingBox* >(cbv) != nullptr) {
				if (LineSegment::doesBoundingBoxCollideWithLineSegment(dynamic_cast< BoundingBox* >(cbv), heightBoundingBox.getMin(), heightBoundingBox.getMax(), heightOnPointA, heightOnPointB) == true) {
					auto heightOnPoint = higher(heightOnPointA, heightOnPointB);
					if (heightOnPoint.getY() >= height && heightOnPoint.getY() < pointXYZ[1] + Math::max(0.1f, stepUpMax)) {
						height = heightOnPoint.getY();
						heightRigidBody = rigidBody;
					}
				}
			} else
			if (dynamic_cast< OrientedBoundingBox* >(cbv) != nullptr) {
				if (LineSegment::doesOrientedBoundingBoxCollideWithLineSegment(dynamic_cast< OrientedBoundingBox* >(cbv), heightBoundingBox.getMin(), heightBoundingBox.getMax(), heightOnPointA, heightOnPointB) == true) {
					auto heightOnPoint = higher(heightOnPointA, heightOnPointB);
					if (heightOnPoint.getY() >= height && heightOnPoint.getY() < pointXYZ[1] + Math::max(0.1f, stepUpMax)) {
						height = heightOnPoint.getY();
						heightRigidBody = rigidBody;
					}
				}
			} else {
				cbv->computeClosestPointOnBoundingVolume(heightOnPointCandidate, heightOnPointA);
				if (Math::abs(heightOnPointCandidate.getX() - heightOnPointA.getX()) < 0.1f &&
					Math::abs(heightOnPointCandidate.getZ() - heightOnPointA.getZ()) < 0.1f &&
					heightOnPointA.getY() >= height && heightOnPointA.getY() < pointXYZ[1] + Math::max(0.1f, stepUpMax)) {
					height = heightOnPointA.getY();
					heightRigidBody = rigidBody;
				}
			}
		}
	}
	if (heightRigidBody == nullptr) {
		return nullptr;
	}
	dest.setY(height);
	return heightRigidBody;
}

RigidBody* World::determineHeight(int32_t typeIds, float stepUpMax, BoundingVolume* boundingVolume, const Vector3& point, Vector3& dest)
{
	auto determinedHeight = -10000.0f;
	Vector3 sideVector(1.0f, 0.0f, 0.0f);
	Vector3 upVector(0.0f, 1.0f, 0.0f);
	Vector3 forwardVector(0.0f, 0.0f, 1.0f);
	Vector3 heightPoint;
	Vector3 heightPointDest;
	auto width = boundingVolume->computeDimensionOnAxis(sideVector);
	auto height = boundingVolume->computeDimensionOnAxis(upVector);
	auto depth = boundingVolume->computeDimensionOnAxis(forwardVector);
	float heightPointDestY;
	RigidBody* heightRigidBody = nullptr;
	RigidBody* rigidBody = nullptr;
	heightPoint.set(boundingVolume->getCenter());
	heightPoint.addY(-height / 2.0f);
	rigidBody = determineHeight(typeIds, stepUpMax, heightPoint, heightPointDest);
	if (rigidBody != nullptr) {
		heightPointDestY = heightPointDest.getY();
		if (heightPointDestY > determinedHeight) {
			heightRigidBody = rigidBody;
			determinedHeight = heightPointDestY;
		}
	}
	heightPoint.set(boundingVolume->getCenter());
	heightPoint.addX(-width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(-depth / 2.0f);
	rigidBody = determineHeight(typeIds, stepUpMax, heightPoint, heightPointDest);
	if (rigidBody != nullptr) {
		heightPointDestY = heightPointDest.getY();
		if (heightPointDestY > determinedHeight) {
			heightRigidBody = rigidBody;
			determinedHeight = heightPointDestY;
		}
	}
	heightPoint.set(boundingVolume->getCenter());
	heightPoint.addX(-width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(+depth / 2.0f);
	rigidBody = determineHeight(typeIds, stepUpMax, heightPoint, heightPointDest);
	if (rigidBody != nullptr) {
		heightPointDestY = heightPointDest.getY();
		if (heightPointDestY > determinedHeight) {
			heightRigidBody = rigidBody;
			determinedHeight = heightPointDestY;
		}
	}
	heightPoint.set(boundingVolume->getCenter());
	heightPoint.addX(+width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(-depth / 2.0f);
	rigidBody = determineHeight(typeIds, stepUpMax, heightPoint, heightPointDest);
	if (rigidBody != nullptr) {
		heightPointDestY = heightPointDest.getY();
		if (heightPointDestY > determinedHeight) {
			heightRigidBody = rigidBody;
			determinedHeight = heightPointDestY;
		}
	}
	heightPoint.set(boundingVolume->getCenter());
	heightPoint.addX(+width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(+depth / 2.0f);
	rigidBody = determineHeight(typeIds, stepUpMax, heightPoint, heightPointDest);
	if (rigidBody != nullptr) {
		heightPointDestY = heightPointDest.getY();
		if (heightPointDestY > determinedHeight) {
			heightRigidBody = rigidBody;
			determinedHeight = heightPointDestY;
		}
	}
	if (heightRigidBody == nullptr) {
		return nullptr;
	} else {
		dest.set(point);
		dest.setY(determinedHeight);
		return heightRigidBody;
	}
}

bool World::doesCollideWith(int32_t typeIds, BoundingVolume* boundingVolume, vector<RigidBody*>& rigidBodies)
{
	Vector3 nullMovement;
	CollisionResponse collision;
	rigidBodies.clear();
	for (auto _i = partition->getObjectsNearTo(boundingVolume)->iterator(); _i->hasNext(); ) {
		RigidBody* rigidBody = _i->next();
		{
			if (((rigidBody->typeId & typeIds) == rigidBody->typeId) == false)
				continue;

			if (rigidBody->cbv->doesCollideWith(boundingVolume, nullMovement, &collision) == true && collision.hasPenetration() == true) {
				rigidBodies.push_back(rigidBody);
			}
		}
	}
	return rigidBodies.size() > 0;
}

World* World::clone()
{
	auto clonedWorld = new World();
	for (auto i = 0; i < rigidBodies.size(); i++) {
		auto rigidBody = rigidBodies.at(i);
		auto obv = rigidBody->obv == nullptr ? static_cast< BoundingVolume* >(nullptr) : rigidBody->obv->clone();
		RigidBody* clonedRigidBody = nullptr;
		if (rigidBody->isStatic_ == true) {
			clonedRigidBody = clonedWorld->addStaticRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, rigidBody->transformations, obv, rigidBody->friction);
		} else {
			clonedRigidBody = clonedWorld->addRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, rigidBody->transformations, obv, rigidBody->restitution, rigidBody->friction, rigidBody->mass, rigidBody->inverseInertia.clone());
		}
		synch(clonedRigidBody, clonedRigidBody);
	}
	return clonedWorld;
}

void World::synch(RigidBody* clonedRigidBody, RigidBody* rigidBody)
{
	clonedRigidBody->enabled = rigidBody->enabled;
	clonedRigidBody->isSleeping_ = rigidBody->isSleeping_;
	clonedRigidBody->collisionTypeIds = rigidBody->collisionTypeIds;
	clonedRigidBody->cbv->fromBoundingVolume(rigidBody->cbv);
	clonedRigidBody->isStatic_ = rigidBody->isStatic_;
	clonedRigidBody->mass = rigidBody->mass;
	clonedRigidBody->inverseMass = rigidBody->inverseMass;
	clonedRigidBody->force.set(rigidBody->force);
	clonedRigidBody->torque.set(rigidBody->torque);
	clonedRigidBody->orientation.set(rigidBody->orientation);
	clonedRigidBody->angularVelocity.set(rigidBody->angularVelocity);
	clonedRigidBody->linearVelocity.set(rigidBody->linearVelocity);
	clonedRigidBody->angularVelocityLast.set(rigidBody->angularVelocityLast);
	clonedRigidBody->movement.set(rigidBody->movement);
	clonedRigidBody->position.set(rigidBody->position);
	clonedRigidBody->worldInverseInertia.set(rigidBody->worldInverseInertia);
	clonedRigidBody->transformations->fromTransformations(rigidBody->transformations);
}

void World::synch(World* world)
{
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		auto rigidBody = rigidBodiesDynamic.at(i);
		auto clonedRigidBody = world->getRigidBody(rigidBody->id);
		if (clonedRigidBody == nullptr) {
			Console::println(
				string("Cloned world::entity '") +
				rigidBody->id +
				string("' not found")
			);
			continue;
		}
		synch(clonedRigidBody, rigidBody);
		if (clonedRigidBody->enabled == true) {
			world->partition->updateRigidBody(clonedRigidBody);
		} else {
			world->partition->removeRigidBody(clonedRigidBody);
		}
	}
}
