#include <tdme/engine/physics/World.h>

#include <algorithm>
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
#include <tdme/utils/StringUtils.h>

using std::remove;
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
using tdme::utils::StringUtils;

World::World() 
{
	partition = new PhysicsPartitionOctTree();
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
	return rigidBody;
}

RigidBody* World::addStaticRigidBody(const string& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float friction)
{
	auto rigidBody = new RigidBody(this, id, enabled, typeId, obv, transformations, 0.0f, friction, 0.0f, RigidBody::computeInertiaMatrix(obv, 0.0f, 0.0f, 0.0f, 0.0f));
	rigidBodies.push_back(rigidBody);
	rigidBodiesById[id] = rigidBody;
	if (enabled == true) partition->addRigidBody(rigidBody);
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

void World::removeRigidBody(const string& id) {
	auto rididBodyByIdIt = rigidBodiesById.find(id);
	if (rididBodyByIdIt != rigidBodiesById.end()) {
		auto rigidBody = rididBodyByIdIt->second;
		if (rigidBody->enabled == true) partition->removeRigidBody(rigidBody);
		rigidBodies.erase(remove(rigidBodies.begin(), rigidBodies.end(), rigidBody), rigidBodies.end());
		rigidBodiesDynamic.erase(remove(rigidBodiesDynamic.begin(), rigidBodiesDynamic.end(), rigidBody), rigidBodiesDynamic.end());
		rigidBodiesById.erase(rididBodyByIdIt);
		delete rigidBody;
	}
}

void World::doCollisionTest(RigidBody* rigidBody1, RigidBody* rigidBody2, map<string, RigidBodyCollisionStruct>& rigidBodyTestedCollisions, map<string, RigidBodyCollisionStruct>& rigidBodyCollisionsCurrentFrame, Vector3& collisionMovement, CollisionResponse &collision, bool useAndInvertCollision) {
	// create rigidBody12 key
	string rigidBodyKey = rigidBody1->id + "," + rigidBody2->id;
	// check if collision has been tested already
	if (rigidBodyTestedCollisions.find(rigidBodyKey) != rigidBodyTestedCollisions.end()) return;
	// nope, add 12 key
	RigidBodyCollisionStruct rigidBodyCollisionStruct;
	rigidBodyCollisionStruct.rigidBody1Id = rigidBody1->id;
	rigidBodyCollisionStruct.rigidBody2Id = rigidBody2->id;
	rigidBodyTestedCollisions[rigidBodyKey] = rigidBodyCollisionStruct;
	// check if to use given collision and invert
	if (useAndInvertCollision == false) {
		// determine collision movement
		collisionMovement.set(rigidBody1->movement);
		if (collisionMovement.computeLength() < MathTools::EPSILON) {
			collisionMovement.set(rigidBody2->movement);
			collisionMovement.scale(-1.0f);
		}
	} else {
		collision.invertNormals();
	}
	// do collision test
	if (useAndInvertCollision == true || (rigidBody1->cbv->doesCollideWith(rigidBody2->cbv, collisionMovement, &collision) == true && collision.hasPenetration() == true)) {
		// check for hit point count
		if (collision.getHitPointsCount() == 0) return;

		// we have a collision, so register it
		rigidBodyCollisionsCurrentFrame[rigidBodyKey] = rigidBodyCollisionStruct;

		// fire collision events
		if (rigidBodyCollisionsLastFrame.find(rigidBodyKey) == rigidBodyCollisionsLastFrame.end()) {
			rigidBody1->fireOnCollisionBegin(rigidBody2, &collision);
		}
		rigidBody1->fireOnCollision(rigidBody2, &collision);
		// unset sleeping if both non static and colliding
		if (rigidBody1->isStatic_ == false && rigidBody2->isStatic_ == false) {
			rigidBody1->awake(true);
			rigidBody2->awake(true);
		}
		// add constraint entity
		constraintsSolver->allocateConstraintsEntity()->set(rigidBody1, rigidBody2, &collision);
	}
}

void World::update(float deltaTime)
{
	if (deltaTime < MathTools::EPSILON) return;

	// lazy initiate constraints solver
	if (constraintsSolver == nullptr) {
		constraintsSolver = new ConstraintsSolver(&rigidBodiesDynamic);
	}
	// apply gravity
	{
		Vector3 worldPosForce;
		Vector3 gravityForce;
		for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
			// update rigid body
			auto rigidBody = rigidBodiesDynamic.at(i);
			// skip on disabled, static
			if (rigidBody->enabled == false) {
				continue;
			}
			// unset sleeping if velocity change occured
			if (rigidBody->checkVelocityChange() == true) {
				rigidBody->awake(true);
			}
			// skip on sleeping
			if (rigidBody->isSleeping_ == true) {
				continue;
			}
			// add gravity
			rigidBody->addForce(
				worldPosForce.set(rigidBody->getPosition()).setY(10000.0f),
				gravityForce.set(0.0f, -rigidBody->getMass() * MathTools::g, 0.0f)
			);
		}
	}
	{
		// do the collision tests,
		// take every rigid body and its partitions into account
		auto collisionTests = 0;
		Vector3 collisionMovement;
		CollisionResponse collision;
		map<string, RigidBodyCollisionStruct> rigidBodyTestedCollisions;
		map<string, RigidBodyCollisionStruct> rigidBodyCollisionsCurrentFrame;
		for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
			auto rigidBody1 = rigidBodiesDynamic.at(i);
			if (rigidBody1->enabled == false) continue;
			auto nearObjects = 0;
			// get objects near to into account, can return a rigid body multiple times
			for (auto _i = partition->getObjectsNearTo(rigidBody1)->iterator(); _i->hasNext(); ) {
				RigidBody* rigidBody2 = _i->next();

				// skip on disabled
				if (rigidBody2->enabled == false)
					continue;

				// skip on same rigid body
				if (rigidBody1 == rigidBody2)
					continue;

				// skip if both are static
				if (rigidBody1->isStatic_ == true && rigidBody2->isStatic_ == true)
					continue;

				// skip on rigid body 1 static, 2 non static and sleeping
				if (rigidBody1->isStatic_ == true && rigidBody2->isStatic_ == false && rigidBody2->isSleeping_ == true) {
					continue;
				}

				// skip on rigid body 2 static, 1 non static and sleeping
				if (rigidBody2->isStatic_ == true && rigidBody1->isStatic_ == false && rigidBody1->isSleeping_ == true) {
					continue;
				}

				// check if rigid body 2 want to have collision with rigid body 1
				if (((rigidBody1->typeId & rigidBody2->collisionTypeIds) == rigidBody1->typeId) == false) {
					continue;
				}

				// check if rigid body 1 want to have collision with rigid body 2
				if (((rigidBody2->typeId & rigidBody1->collisionTypeIds) == rigidBody2->typeId) == false) {
					continue;
				}

				nearObjects++;
				collisionTests++;
				doCollisionTest(rigidBody1, rigidBody2, rigidBodyTestedCollisions, rigidBodyCollisionsCurrentFrame, collisionMovement, collision, false);
				doCollisionTest(rigidBody2, rigidBody1, rigidBodyTestedCollisions, rigidBodyCollisionsCurrentFrame, collisionMovement, collision, true);
			}
		}

		// fire on collision end
		//	check each collision last frame that disappeared in current frame
		for (auto it: rigidBodyCollisionsLastFrame) {
			RigidBodyCollisionStruct* rigidBodyCollisionStruct = &it.second;
			{
				string rigidBodyKey = rigidBodyCollisionStruct->rigidBody1Id + "," + rigidBodyCollisionStruct->rigidBody2Id;
				auto rigidBodyCollisionsCurrentFrameIt = rigidBodyCollisionsCurrentFrame.find(rigidBodyKey);
				if (rigidBodyCollisionsCurrentFrameIt != rigidBodyCollisionsCurrentFrame.end()) continue;
			}

			{
				string rigidBodyKey = rigidBodyCollisionStruct->rigidBody2Id + "," + rigidBodyCollisionStruct->rigidBody1Id;
				auto rigidBodyCollisionsCurrentFrameIt = rigidBodyCollisionsCurrentFrame.find(rigidBodyKey);
				if (rigidBodyCollisionsCurrentFrameIt != rigidBodyCollisionsCurrentFrame.end()) continue;
			}

			auto rigidBody1 = rigidBodiesById[rigidBodyCollisionStruct->rigidBody1Id];
			auto rigidBody2 = rigidBodiesById[rigidBodyCollisionStruct->rigidBody2Id];
			rigidBody1->fireOnCollisionEnd(rigidBody2);
		}
		// swap rigid body collisions current and last frame
		rigidBodyCollisionsLastFrame = rigidBodyCollisionsCurrentFrame;
		// do collision resolving
		constraintsSolver->compute(deltaTime);
		constraintsSolver->updateAllBodies(deltaTime);
		constraintsSolver->reset();
	}

	// update transformations for rigid body
	for (auto i = 0; i < rigidBodies.size(); i++) {
		auto rigidBody = rigidBodies.at(i);
		// skip if enabled
		if (rigidBody->enabled == false) {
			continue;
		}
		// skip if static or sleeping
		if (rigidBody->isStatic_ == true || rigidBody->isSleeping_ == true) {
			continue;
		}
		// set up transformations, keep care that only 1 rotation exists
		auto rotations = rigidBody->transformations->getRotations();
		while (rotations->size() > 1) {
			rotations->remove(rotations->size() - 1);
		}
		while (rotations->size() < 1) {
			rotations->add(new Rotation());
		}
		// set up orientation
		rotations->get(0)->fromQuaternion(rigidBody->orientation);
		rotations->get(0)->getAxis().getArray()[1] *= -1.0f;
		//	set up position
		auto transformations = rigidBody->transformations;
		transformations->getTranslation().set(rigidBody->position);
		// update
		transformations->update();
		// update bounding volume
		rigidBody->cbv->fromBoundingVolumeWithTransformations(rigidBody->obv, transformations);
		// update partition
		partition->updateRigidBody(rigidBody);
	}
}

void World::synch(Engine* engine)
{
	for (auto i = 0; i < rigidBodies.size(); i++) {
		// update rigid body
		auto rigidBody = rigidBodies.at(i);
		// skip on static objects
		if (rigidBody->isStatic_ == true)
			continue;
		// skip on sleeping objects
		if (rigidBody->isSleeping_ == true)
			continue;
		// synch with engine entity
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
	// height bounding box to determine partition bounding volumes
	heightBoundingBox.getMin().set(pointXYZ[0], -10000.0f, pointXYZ[2]);
	heightBoundingBox.getMax().set(pointXYZ[0], +10000.0f, pointXYZ[2]);
	heightBoundingBox.update();
	// determine height of point on x, z
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
				// compute closest point on height candidate
				cbv->computeClosestPointOnBoundingVolume(heightOnPointCandidate, heightOnPointA);
				// check new height, take only result into account which is near to candidate
				if (Math::abs(heightOnPointCandidate.getX() - heightOnPointA.getX()) < 0.1f &&
					Math::abs(heightOnPointCandidate.getZ() - heightOnPointA.getZ()) < 0.1f &&
					heightOnPointA.getY() >= height && heightOnPointA.getY() < pointXYZ[1] + Math::max(0.1f, stepUpMax)) {
					height = heightOnPointA.getY();
					heightRigidBody = rigidBody;
				}
			}
		}
	}
	// check if we have a ground
	if (heightRigidBody == nullptr) {
		// nope
		return nullptr;
	}
	// yep
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
	// center, center
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
	// left, top
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
	// left, bottom
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
	// right, top
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
	// right, bottom
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
	// set up result
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
		// clone obv
		auto obv = rigidBody->obv == nullptr ? static_cast< BoundingVolume* >(nullptr) : rigidBody->obv->clone();
		RigidBody* clonedRigidBody = nullptr;
		if (rigidBody->isStatic_ == true) {
			// clone static rigid body
			clonedRigidBody = clonedWorld->addStaticRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, rigidBody->transformations, obv, rigidBody->friction);
		} else {
			// update dynamic rigid body
			clonedRigidBody = clonedWorld->addRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, rigidBody->transformations, obv, rigidBody->restitution, rigidBody->friction, rigidBody->mass, rigidBody->inverseInertia.clone());
		}
		// synch additional properties
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
		// synch rigid bodies
		synch(clonedRigidBody, rigidBody);
		// set up rigid body in partition
		if (clonedRigidBody->enabled == true) {
			world->partition->updateRigidBody(clonedRigidBody);
		} else {
			world->partition->removeRigidBody(clonedRigidBody);
		}
	}
}
