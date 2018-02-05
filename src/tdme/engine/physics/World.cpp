#include <tdme/engine/physics/World.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_set>
#include <string>

#include <ext/reactphysics3d/src/collision/ProxyShape.h>
#include <ext/reactphysics3d/src/engine/CollisionWorld.h>
#include <ext/reactphysics3d/src/mathematics/Ray.h>
#include <ext/reactphysics3d/src/mathematics/Vector3.h>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Rotations.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/VectorIteratorMultiple.h>

using std::find;
using std::remove;
using std::map;
using std::string;
using std::to_string;
using std::unordered_set;

using tdme::engine::physics::World;
using tdme::math::Math;
using tdme::math::MathTools;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Rotation;
using tdme::engine::Rotations;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::ConvexMeshBoundingVolume;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::VectorIteratorMultiple;

World::World(): world(reactphysics3d::Vector3(0.0, -9.81, 0.0))
{
	rigidBodyRotationTransformation.getRotations()->add(new Rotation());
}

World::~World()
{
	reset();
}

void World::reset()
{
	// TODO
}

RigidBody* World::addRigidBody(const string& id, bool enabled, uint16_t typeId, Transformations* transformations, BoundingVolume* boundingVolume, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix)
{
	removeRigidBody(id);
	auto rigidBody = new RigidBody(this, id, RigidBody::TYPE_DYNAMIC, enabled, typeId, boundingVolume, transformations, restitution, friction, mass, inertiaMatrix);
	rigidBodies.push_back(rigidBody);
	rigidBodiesDynamic.push_back(rigidBody);
	rigidBodiesById[id] = rigidBody;
	return rigidBody;
}

RigidBody* World::addStaticRigidBody(const string& id, bool enabled, uint16_t typeId, Transformations* transformations, BoundingVolume* boundingVolume, float friction)
{
	removeRigidBody(id);
	auto rigidBody = new RigidBody(this, id, RigidBody::TYPE_STATIC, enabled, typeId, boundingVolume, transformations, 0.0f, friction, 1000000.0f, RigidBody::computeInertiaMatrix(boundingVolume, 0.0f, 0.0f, 0.0f, 0.0f));
	rigidBodies.push_back(rigidBody);
	rigidBodiesById[id] = rigidBody;
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
		world.destroyRigidBody(rigidBody->rigidBody);
		rigidBodies.erase(remove(rigidBodies.begin(), rigidBodies.end(), rigidBody), rigidBodies.end());
		rigidBodiesDynamic.erase(remove(rigidBodiesDynamic.begin(), rigidBodiesDynamic.end(), rigidBody), rigidBodiesDynamic.end());
		rigidBodiesById.erase(rididBodyByIdIt);
		delete rigidBody;
	}
}

void World::update(float deltaTime)
{
	if (deltaTime < MathTools::EPSILON) return;

	// update velocities
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		auto rigidBody = rigidBodiesDynamic.at(i);
		// skip if enabled
		if (rigidBody->enabled == false) {
			continue;
		}
		// skip if sleeping
		if (rigidBody->isSleeping() == true &&
			rigidBody->angularVelocity.computeLengthSquared() < MathTools::EPSILON &&
			rigidBody->linearVelocity.computeLengthSquared() < MathTools::EPSILON) {
			continue;
		}
		auto& rigidBodyAngularVelocity = rigidBody->angularVelocity;
		rigidBody->rigidBody->setAngularVelocity(
			reactphysics3d::Vector3(
				rigidBodyAngularVelocity.getX(),
				rigidBodyAngularVelocity.getY(),
				rigidBodyAngularVelocity.getZ()
			)
		);
		auto& rigidBodyLinearVelocity = rigidBody->linearVelocity;
		rigidBody->rigidBody->setLinearVelocity(
			reactphysics3d::Vector3(
				rigidBodyLinearVelocity.getX(),
				rigidBodyLinearVelocity.getY(),
				rigidBodyLinearVelocity.getZ()
			)
		);
	}

	// do the job
	world.update(deltaTime);

	// TODO: collision events
	{
		// do the collision tests,
		// take every rigid body and its partitions into account
		map<string, RigidBodyCollisionStruct> rigidBodyTestedCollisions;
		map<string, RigidBodyCollisionStruct> rigidBodyCollisionsCurrentFrame;

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
	}

	// update transformations for rigid body
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		auto rigidBody = rigidBodiesDynamic.at(i);
		// skip if enabled
		if (rigidBody->enabled == false) {
			continue;
		}
		// skip if static or sleeping
		if (rigidBody->isSleeping() == true) {
			continue;
		}
		// set up transformations, keep care that only 1 rotation exists
		auto rotations = rigidBody->transformations.getRotations();
		while (rotations->size() > 1) {
			rotations->remove(rotations->size() - 1);
		}
		while (rotations->size() < 1) {
			rotations->add(new Rotation());
		}
		// set up position, orientation
		auto transform = rigidBody->rigidBody->getTransform();
		auto& position = transform.getPosition();
		auto& orientation = transform.getOrientation();
		//	set up transformations
		auto& physicsTransformations = rigidBody->transformations;
		physicsTransformations.getRotations()->get(0)->fromQuaternion(Quaternion(orientation.x, orientation.y, orientation.z, orientation.w));
		physicsTransformations.getTranslation().set(position.x, position.y, position.z);
		physicsTransformations.update();
		// velocities
		auto angularVelocity = rigidBody->rigidBody->getAngularVelocity();
		auto linearVelocity = rigidBody->rigidBody->getLinearVelocity();
		rigidBody->getAngularVelocity().set(angularVelocity.x, angularVelocity.y, angularVelocity.z);
		rigidBody->getLinearVelocity().set(linearVelocity.x, linearVelocity.y, linearVelocity.z);
	}
}

void World::synch(Engine* engine)
{
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		// update rigid body
		auto rigidBody = rigidBodiesDynamic.at(i);

		// skip on sleeping objects
		if (rigidBody->isSleeping() == true) continue;

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

		// enable
		engineEntity->setEnabled(rigidBody->enabled);

		//apply inverse local transformation for engine update
		if (rigidBody->enabled == true) {
			engineEntity->fromTransformations(&rigidBody->transformations);
		}
	}
}

RigidBody* World::determineHeight(int32_t typeIds, float stepUpMax, const Vector3& point, Vector3& dest)
{
	class CustomCallbackClass : public reactphysics3d::RaycastCallback {
	public:
		CustomCallbackClass(float stepUpMax, const Vector3& point): stepUpMax(stepUpMax), point(point), height(-10000.0f), rigidBody(nullptr) {
		}
		virtual reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& info) {
			Vector3 hitPoint(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
			if (hitPoint.getY() >= height && hitPoint.getY() <= point.getY() + Math::max(0.1f, stepUpMax)) {
				height = hitPoint.getY();
				rigidBody = (RigidBody*)info.body->getUserData();
			}
			return reactphysics3d::decimal(1.0);
		};
		RigidBody* getRigidBody() {
			return rigidBody;
		}
		const float getHeight() {
			return height;
		}
	private:
		float stepUpMax;
		Vector3 point;
		float height;
		RigidBody* rigidBody;
	};
	reactphysics3d::Vector3 startPoint(point.getX(), +10000.0f, point.getZ());
	reactphysics3d::Vector3 endPoint(point.getX(), -10000.0f, point.getZ());
	reactphysics3d::Ray ray(startPoint, endPoint);
	CustomCallbackClass customCallbackObject(stepUpMax, point);
	world.raycast(ray, &customCallbackObject, typeIds);
	if (customCallbackObject.getRigidBody() != nullptr) {
		dest.set(point);
		dest.setY(customCallbackObject.getHeight());
		return customCallbackObject.getRigidBody();
	} else {
		return nullptr;
	}
}

RigidBody* World::determineHeight(int32_t typeIds, float stepUpMax, BoundingVolume* boundingVolume, const Vector3& point, Vector3& dest)
{
	auto determinedHeight = -10000.0f;
	Vector3 heightPoint;
	Vector3 heightPointDest;
	auto width = boundingVolume->getBoundingBoxTransformed().getDimensions().getX();
	auto height = boundingVolume->getBoundingBoxTransformed().getDimensions().getY();
	auto depth = boundingVolume->getBoundingBoxTransformed().getDimensions().getZ();
	float heightPointDestY;
	RigidBody* heightRigidBody = nullptr;
	RigidBody* rigidBody = nullptr;
	// center, center
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
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
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
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
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
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
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
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
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
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
	vector<RigidBody*> rigidBodyCandidates;
	auto determinedHeight = -10000.0f;
	CollisionResponse response;
	Vector3 movement(0.0f, 0.0f, 0.0f);
	Vector3 heightPoint;
	Vector3 heightPointDest;
	auto width = boundingVolume->getBoundingBoxTransformed().getDimensions().getX();
	auto height = boundingVolume->getBoundingBoxTransformed().getDimensions().getY();
	auto depth = boundingVolume->getBoundingBoxTransformed().getDimensions().getZ();
	float heightPointDestY;
	RigidBody* heightRigidBody = nullptr;
	RigidBody* rigidBody = nullptr;
	// center, center
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
	heightPoint.addY(-height / 2.0f);
	rigidBody = determineHeight(typeIds, height, heightPoint, heightPointDest);
	if (rigidBody != nullptr) rigidBodyCandidates.push_back(rigidBody);
	// left, top
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
	heightPoint.addX(-width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(-depth / 2.0f);
	rigidBody = determineHeight(typeIds, height, heightPoint, heightPointDest);
	if (rigidBody != nullptr) rigidBodyCandidates.push_back(rigidBody);
	// left, bottom
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
	heightPoint.addX(-width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(+depth / 2.0f);
	rigidBody = determineHeight(typeIds, height, heightPoint, heightPointDest);
	if (rigidBody != nullptr) rigidBodyCandidates.push_back(rigidBody);
	// right, top
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
	heightPoint.addX(+width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(-depth / 2.0f);
	rigidBody = determineHeight(typeIds, height, heightPoint, heightPointDest);
	if (rigidBody != nullptr) rigidBodyCandidates.push_back(rigidBody);
	// right, bottom
	heightPoint.set(boundingVolume->getBoundingBoxTransformed().getCenter());
	heightPoint.addX(+width / 2.0f);
	heightPoint.addY(-height / 2.0f);
	heightPoint.addZ(+depth / 2.0f);
	rigidBody = determineHeight(typeIds, height, heightPoint, heightPointDest);
	if (rigidBody != nullptr) rigidBodyCandidates.push_back(rigidBody);
	// check if they collide
	for (auto rigidBody: rigidBodyCandidates) {
		if (rigidBody->doesCollideWith(boundingVolume, &response) == true) {
			if (find(rigidBodies.begin(), rigidBodies.end(), rigidBody) == rigidBodies.end()) {
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
		RigidBody* clonedRigidBody = nullptr;
		if (rigidBody->isStatic() == true) {
			// clone static rigid body
			clonedRigidBody = clonedWorld->addStaticRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, &rigidBody->transformations, rigidBody->boundingVolume, rigidBody->getFriction());
		} else {
			// update dynamic rigid body
			clonedRigidBody = clonedWorld->addRigidBody(rigidBody->id, rigidBody->enabled, rigidBody->typeId, &rigidBody->transformations, rigidBody->boundingVolume, rigidBody->getRestitution(), rigidBody->getFriction(), rigidBody->getMass(), rigidBody->inverseInertiaMatrix);
		}
		// synch additional properties
		synch(clonedRigidBody, clonedRigidBody);
	}
	return clonedWorld;
}

void World::synch(RigidBody* clonedRigidBody, RigidBody* rigidBody)
{
	Console::println("World::synch()");
	clonedRigidBody->setCollisionTypeIds(rigidBody->getCollisionTypeIds());
	clonedRigidBody->setEnabled(rigidBody->isEnabled());
	clonedRigidBody->setMass(rigidBody->getMass());
	clonedRigidBody->setMass(rigidBody->getMass());
	clonedRigidBody->getAngularVelocity().set(rigidBody->angularVelocity);
	clonedRigidBody->getLinearVelocity().set(rigidBody->linearVelocity);
	clonedRigidBody->fromTransformations(&rigidBody->transformations);
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
	}
}
