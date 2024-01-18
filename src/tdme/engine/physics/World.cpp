#include <tdme/engine/physics/World.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>

#include <reactphysics3d/utils/DefaultLogger.h>

#include <reactphysics3d/collision/shapes/AABB.h>
#include <reactphysics3d/collision/ContactManifold.h>
#include <reactphysics3d/collision/OverlapCallback.h>
#include <reactphysics3d/collision/RaycastInfo.h>
#include <reactphysics3d/constraint/ContactPoint.h>
#include <reactphysics3d/constraint/FixedJoint.h>
#include <reactphysics3d/constraint/Joint.h>
#include <reactphysics3d/engine/PhysicsWorld.h>
#include <reactphysics3d/engine/EventListener.h>
#include <reactphysics3d/mathematics/Ray.h>
#include <reactphysics3d/mathematics/Vector3.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/Body.h>
#include <tdme/engine/physics/BodyHierarchy.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/engine/physics/WorldListener.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Engine.h>
#include <tdme/engine/Entity.h>
#include <tdme/engine/Rotation.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Quaternion.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/StringTools.h>
#include <tdme/utilities/Time.h>

using std::find;
using std::make_unique;
using std::map;
using std::remove;
using std::string;
using std::to_string;
using std::unordered_set;

using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::engine::physics::World;
using tdme::engine::physics::WorldListener;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::Engine;
using tdme::engine::Entity;
using tdme::engine::Rotation;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Matrix4x4;
using tdme::math::Quaternion;
using tdme::math::Vector3;
using tdme::utilities::Console;
using tdme::utilities::StringTools;
using tdme::utilities::Time;

World::World(const string& id)
{
	//
    reactphysics3d::PhysicsWorld::WorldSettings worldSettings;
    worldSettings.worldName = id;

	//
	world = physicsCommon.createPhysicsWorld(worldSettings);
}

World::~World()
{
	//
	worldListeners.clear();
	reset();
	physicsCommon.destroyPhysicsWorld(world);
}

void World::reset()
{
	// joints
	{
		vector<string> jointIds;
		for (const auto& [jointId, joint]: jointsById) jointIds.push_back(jointId);
		for (const auto& jointId: jointIds) removeJoint(jointId);
	}
	// bodies
	{
		auto _bodies = bodies;
		for (auto body: _bodies) removeBody(body->getId());
		bodyCollisionsLastFrame.clear();
	}
}

Body* World::addRigidBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy)
{
	removeBody(id);
	//
	auto body =
		hierarchy == true?
			new BodyHierarchy(this, id, Body::BODYTYPE_DYNAMIC, collisionTypeId, enabled, transform, restitution, friction, mass, inertiaTensor):
			new Body(this, id, Body::BODYTYPE_DYNAMIC, collisionTypeId, enabled, transform, restitution, friction, mass, inertiaTensor, boundingVolumes);
	//
	if (hierarchy == true) {
		static_cast<BodyHierarchy*>(body)->addBody(id, Transform(), boundingVolumes);
		static_cast<BodyHierarchy*>(body)->update();
	}
	//
	bodies.push_back(body);
	rigidBodiesDynamic.push_back(body);
	bodiesById[id] = body;
	//
	for (auto listener: worldListeners) {
		listener->onAddedBody(id, Body::BODYTYPE_DYNAMIC, collisionTypeId, enabled, transform, restitution, friction, mass, inertiaTensor, boundingVolumes);
	}
	//
	return body;
}

Body* World::addStaticCollisionBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy) {
	removeBody(id);
	//
	auto body =
		hierarchy == true?
			new BodyHierarchy(this, id, Body::BODYTYPE_COLLISION_STATIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor()):
			new Body(this, id, Body::BODYTYPE_COLLISION_STATIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	//
	if (hierarchy == true) {
		static_cast<BodyHierarchy*>(body)->addBody(id, Transform(), boundingVolumes);
		static_cast<BodyHierarchy*>(body)->update();
	}
	//
	bodies.push_back(body);
	bodiesById[id] = body;
	//
	for (auto listener: worldListeners) {
		listener->onAddedBody(id, Body::BODYTYPE_COLLISION_STATIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	}
	//
	return body;
}

Body* World::addDynamicCollisionBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy) {
	removeBody(id);
	//
	auto body =
		hierarchy == true?
			new BodyHierarchy(this, id, Body::BODYTYPE_COLLISION_DYNAMIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor()):
			new Body(this, id, Body::BODYTYPE_COLLISION_DYNAMIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	//
	if (hierarchy == true) {
		static_cast<BodyHierarchy*>(body)->addBody(id, Transform(), boundingVolumes);
		static_cast<BodyHierarchy*>(body)->update();
	}
	//
	bodies.push_back(body);
	bodiesById[id] = body;
	//
	for (auto listener: worldListeners) {
		listener->onAddedBody(id, Body::BODYTYPE_COLLISION_DYNAMIC, collisionTypeId, enabled, transform, 0.0f, 0.0f, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	}
	//
	return body;
}

Body* World::addStaticRigidBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, float friction, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy)
{
	removeBody(id);
	//
	auto body =
		hierarchy == true?
			new BodyHierarchy(this, id, Body::BODYTYPE_STATIC, collisionTypeId, enabled, transform, 0.0f, friction, 0.0f, Body::getNoRotationInertiaTensor()):
			new Body(this, id, Body::BODYTYPE_STATIC, collisionTypeId, enabled, transform, 0.0f, friction, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	//
	if (hierarchy == true) {
		static_cast<BodyHierarchy*>(body)->addBody(id, Transform(), boundingVolumes);
		static_cast<BodyHierarchy*>(body)->update();
	}
	//
	bodies.push_back(body);
	bodiesById[id] = body;
	//
	for (auto listener: worldListeners) {
		listener->onAddedBody(id, Body::BODYTYPE_STATIC, collisionTypeId, enabled, transform, 0.0f, friction, 0.0f, Body::getNoRotationInertiaTensor(), boundingVolumes);
	}
	//
	return body;
}

BodyHierarchy* World::getBodyHierarchy(const string& id) {
	auto body = getBody(id);
	if (body == nullptr) return nullptr;
	return dynamic_cast<BodyHierarchy*>(body);
}

void World::removeBody(const string& id) {
	auto bodyByIdIt = bodiesById.find(id);
	if (bodyByIdIt != bodiesById.end()) {
		auto body = bodyByIdIt->second;
		bodies.erase(remove(bodies.begin(), bodies.end(), body), bodies.end());
		rigidBodiesDynamic.erase(remove(rigidBodiesDynamic.begin(), rigidBodiesDynamic.end(), body), rigidBodiesDynamic.end());
		bodiesById.erase(bodyByIdIt);
		for (auto listener: worldListeners) {
			listener->onRemovedBody(id, body->getType(), body->getCollisionTypeId());
		}
		//
		delete body;
	}
}

void World::addFixedJoint(const string& id, Body* body1, Body* body2) {
	removeJoint(id);
	if (body1->rigidBody == nullptr) {
		Console::printLine("World::createFixedJoint(): body1: no rigid body attached");
		return;
	} else
	if (body2->rigidBody == nullptr) {
		Console::printLine("World::createFixedJoint(): body2: no rigid body attached");
		return;
	}
	Vector3 anchorPoint = body1->getTransform().getTranslation().clone().add(body2->getTransform().getTranslation()).scale(0.5f);
	reactphysics3d::FixedJointInfo jointInfo(body1->rigidBody, body2->rigidBody, reactphysics3d::Vector3(anchorPoint.getX(), anchorPoint.getY(), anchorPoint.getZ()));
	jointInfo.isCollisionEnabled = false;
	jointsById[id] = dynamic_cast<reactphysics3d::FixedJoint*>(world->createJoint(jointInfo));
}

void World::removeJoint(const string& id) {
	auto jointByIdIt = jointsById.find(id);
	if (jointByIdIt != jointsById.end()) {
		auto joint = jointByIdIt->second;
		world->destroyJoint(joint);
		jointsById.erase(jointByIdIt);
	}
}

void World::update(float deltaTime)
{
	if (deltaTime < Math::EPSILON) return;

	// do the job
	world->update(deltaTime);

	/*
	// TODO: collision events
	// collision events
	{
		// fire on collision begin, on collision
		map<string, BodyCollisionStruct> bodyCollisionsCurrentFrame;
		CollisionResponse collision;
		auto manifolds = world->getContactsList();
		for (auto manifold: manifolds) {
			auto body1 = static_cast<Body*>(manifold->getBody1()->getUserData());
			auto body2 = static_cast<Body*>(manifold->getBody2()->getUserData());
			BodyCollisionStruct bodyCollisionStruct;
			bodyCollisionStruct.body1Id = body1->getId();
			bodyCollisionStruct.body2Id = body2->getId();
			string bodyKey = bodyCollisionStruct.body1Id + "," + bodyCollisionStruct.body2Id;
			string bodyKeyInverted = bodyCollisionStruct.body2Id + "," + bodyCollisionStruct.body1Id;
			bodyCollisionsCurrentFrame[bodyKey] = bodyCollisionStruct;
			for (int i=0; i<manifold->getNbContactPoints(); i++) {
				auto contactPoint = manifold->getContactPoints();
				while (contactPoint != nullptr) {
					// construct collision
					auto entity = collision.addResponse(-contactPoint->getPenetrationDepth());
					auto normal = contactPoint->getNormal();
					entity->setNormal(Vector3(normal.x, normal.y, normal.z));
					auto shape1 = manifold->getShape1();
					auto shape2 = manifold->getShape2();
					auto shapeLocalToWorldTransform1 = shape1->getLocalToWorldTransform();
					auto shapeLocalToWorldTransform2 = shape2->getLocalToWorldTransform();
					auto& localPoint1 = contactPoint->getLocalPointOnShape1();
					auto& localPoint2 = contactPoint->getLocalPointOnShape2();
					auto worldPoint1 = shapeLocalToWorldTransform1 * localPoint1;
					auto worldPoint2 = shapeLocalToWorldTransform2 * localPoint2;
					entity->addHitPoint(Vector3(worldPoint1.x, worldPoint1.y, worldPoint1.z));
					entity->addHitPoint(Vector3(worldPoint2.x, worldPoint2.y, worldPoint2.z));
					contactPoint = contactPoint->getNext();
					// fire events
					if (bodyCollisionsLastFrame.find(bodyKey) == bodyCollisionsLastFrame.end() &&
						bodyCollisionsLastFrame.find(bodyKeyInverted) == bodyCollisionsLastFrame.end()) {
						// fire on collision begin
						body1->fireOnCollisionBegin(body2, collision);
					}
					// fire on collision
					body1->fireOnCollision(body2, collision);
					// reset collision
					collision.reset();
				}
			}
		}

		// fire on collision end
		//	check each collision last frame that disappeared in current frame
		for (auto it: bodyCollisionsLastFrame) {
			BodyCollisionStruct* bodyCollisionStruct = &it.second;
			{
				string bodyKey = bodyCollisionStruct->body1Id + "," + bodyCollisionStruct->body2Id;
				auto bodyCollisionsCurrentFrameIt = bodyCollisionsCurrentFrame.find(bodyKey);
				if (bodyCollisionsCurrentFrameIt != bodyCollisionsCurrentFrame.end()) continue;
			}
			{
				string bodyKey = bodyCollisionStruct->body2Id + "," + bodyCollisionStruct->body1Id;
				auto bodyCollisionsCurrentFrameIt = bodyCollisionsCurrentFrame.find(bodyKey);
				if (bodyCollisionsCurrentFrameIt != bodyCollisionsCurrentFrame.end()) continue;
			}
			auto body1It = bodiesById.find(bodyCollisionStruct->body1Id);
			auto body1 = body1It == bodiesById.end()?nullptr:body1It->second;
			auto body2It = bodiesById.find(bodyCollisionStruct->body2Id);
			auto body2 = body2It == bodiesById.end()?nullptr:body2It->second;
			if (body1 == nullptr || body2 == nullptr) continue;
			body1->fireOnCollisionEnd(body2);
		}
		// swap rigid body collisions current and last frame
		bodyCollisionsLastFrame = bodyCollisionsCurrentFrame;
	}
	*/

	// update transform for rigid body
	for (auto body: rigidBodiesDynamic) {
		// skip if disabled
		if (body->isEnabled() == false) {
			continue;
		}
		// skip if static or sleeping
		if (body->isSleeping() == true) {
			continue;
		}

		// rp3d transform
		const auto& transform = body->rigidBody->getTransform();
		const auto& transformPosition = transform.getPosition();
		const auto& transformOrientation = transform.getOrientation();

		// tdme2 transform
		auto& physicsTransform = body->transform;

		// rotations
		// keep care that only 1 rotation exists
		while (physicsTransform.getRotationCount() > 1) {
			physicsTransform.removeRotation(physicsTransform.getRotationCount() - 1);
		}
		if (physicsTransform.getRotationCount() < 1) {
			physicsTransform.addRotation(Vector3(0.0f, 1.0f, 0.0f), 0.0f);
		}

		// rotations
		physicsTransform.getRotation(0).fromRotation(
			Rotation::fromQuaternion(
				Quaternion(
					transformOrientation.x,
					transformOrientation.y,
					transformOrientation.z,
					transformOrientation.w
				)
			)
		);
		// scale
		physicsTransform.setScale(body->transformScale);
		// translation
		physicsTransform.setTranslation(Vector3(transformPosition.x, transformPosition.y, transformPosition.z));
		// done
		physicsTransform.update();
	}
}

void World::synchronize(Engine* engine)
{
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		// update rigid body
		auto body = rigidBodiesDynamic[i];

		// skip on sleeping objects
		if (body->isSleeping() == true) continue;

		// synch with engine entity
		auto entity = engine->getEntity(body->getId());
		if (entity == nullptr) {
			Console::printLine("World::entity '" + body->getId() + "' not found");
			continue;
		}

		// enable
		entity->setEnabled(body->isEnabled());

		// apply transform to engine entity
		if (body->isEnabled() == true) entity->setTransform(body->transform);
	}
}

Body* World::determineHeight(uint16_t collisionTypeIds, float stepUpMax, const Vector3& point, Vector3& heightPoint, float minHeight, float maxHeight)
{
	// TODO: we seem to have a bug here
	//
	class CustomCallbackClass : public reactphysics3d::RaycastCallback {
	public:
		CustomCallbackClass(float stepUpMax, const Vector3& point, float height = 10000.0f): stepUpMax(stepUpMax), point(point), height(height), body(nullptr) {
		}
		virtual reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& info) {
			Vector3 hitPoint(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
			auto _body = static_cast<Body*>(info.body->getUserData());
			if (hitPoint.getY() < height && hitPoint.getY() <= point.getY() + stepUpMax) {
				height = hitPoint.getY();
				body = static_cast<Body*>(info.body->getUserData());
			}
			return reactphysics3d::decimal(info.hitFraction);
		};
		Body* getBody() {
			return body;
		}
		float getHeight() {
			return height;
		}
	private:
		float stepUpMax;
		Vector3 point;
		float height;
		Body* body;
	};
	reactphysics3d::Vector3 startPoint(point.getX(), maxHeight, point.getZ());
	reactphysics3d::Vector3 endPoint(point.getX(), minHeight, point.getZ());
	reactphysics3d::Ray ray(startPoint, endPoint);
	CustomCallbackClass customCallbackObject(stepUpMax, point, maxHeight);
	world->raycast(ray, &customCallbackObject, collisionTypeIds);
	if (customCallbackObject.getBody() != nullptr) {
		heightPoint.set(point);
		heightPoint.setY(customCallbackObject.getHeight());
		//
		return customCallbackObject.getBody();
	} else {
		return nullptr;
	}
}

Body* World::doRayCasting(uint16_t collisionTypeIds, const Vector3& start, const Vector3& end, Vector3& hitPoint, const string& actorId)
{
	class CustomCallbackClass : public reactphysics3d::RaycastCallback {
	public:
		CustomCallbackClass(const string& actorId): actorId(actorId), body(nullptr) {
		}
		virtual reactphysics3d::decimal notifyRaycastHit(const reactphysics3d::RaycastInfo& info) {
			auto _body = static_cast<Body*>(info.body->getUserData());
			if (actorId.size() == 0 || _body->getId() != actorId) {
				body = _body;
				hitPoint.set(info.worldPoint.x, info.worldPoint.y, info.worldPoint.z);
				return reactphysics3d::decimal(info.hitFraction);
			} else {
				return reactphysics3d::decimal(1.0);
			}
		};
		Body* getBody() {
			return body;
		}
		const Vector3& getHitPoint() {
			return hitPoint;
		}
	private:
		string actorId;
		Vector3 hitPoint;
		Body* body;
	};
	reactphysics3d::Vector3 startPoint(start.getX(), start.getY(), start.getZ());
	reactphysics3d::Vector3 endPoint(end.getX(), end.getY(), end.getZ());
	reactphysics3d::Ray ray(startPoint, endPoint);
	CustomCallbackClass customCallbackObject(actorId);
	world->raycast(ray, &customCallbackObject, collisionTypeIds);
	if (customCallbackObject.getBody() != nullptr) {
		hitPoint.set(customCallbackObject.getHitPoint());
		return customCallbackObject.getBody();
	} else {
		return nullptr;
	}
}

bool World::doesCollideWith(uint16_t collisionTypeIds, Body* body, vector<Body*>& collisionBodies) {
	// callback
	class CustomOverlapCallback: public reactphysics3d::OverlapCallback {
	    public:
			CustomOverlapCallback(int collisionTypeIds, Body* body, vector<Body*>& collisionBodies): collisionTypeIds(collisionTypeIds), body(body), collisionBodies(collisionBodies) {
			}

			void onOverlap(CallbackData &callbackData) {
				for (auto i = 0; i < callbackData.getNbOverlappingPairs(); i++) {
					auto overlappingPair = callbackData.getOverlappingPair(i);
					auto body1 = static_cast<Body*>(overlappingPair.getBody1()->getUserData());
					auto body2 = static_cast<Body*>(overlappingPair.getBody2()->getUserData());
					if (body != body1 && ((body1->getCollisionTypeId() & collisionTypeIds) != 0)) collisionBodies.push_back(body1);
					if (body != body2 && ((body2->getCollisionTypeId() & collisionTypeIds) != 0)) collisionBodies.push_back(body2);
				}
			}
	    private:
			int collisionTypeIds;
			Body* body;
			vector<Body*>& collisionBodies;
	};

	// do the test
	CustomOverlapCallback customOverlapCallback(collisionTypeIds, body, collisionBodies);
	world->testOverlap(body->rigidBody, customOverlapCallback);

	// done
	return collisionBodies.size() > 0;
}

bool World::doesCollideWith(uint16_t collisionTypeIds, const Transform& transform, vector<BoundingVolume*> boundingVolumes, vector<Body*>& collisionBodies) {
	auto collisionBody = addStaticCollisionBody("tdme.world->doescollidewith", 32768, true, transform, boundingVolumes);
	doesCollideWith(collisionTypeIds, collisionBody, collisionBodies);
	removeBody("tdme.world->doescollidewith");
	return collisionBodies.size() > 0;
}

bool World::doCollide(Body* body1, Body* body2) {
	return world->testOverlap(body1->rigidBody, body2->rigidBody);
}

bool World::getCollisionResponse(Body* body1, Body* body2, CollisionResponse& collision) {
	// callback
	class CustomCollisionCallback: public reactphysics3d::CollisionCallback {
	    public:
			CustomCollisionCallback(CollisionResponse& collision): collision(collision) {
			}

			void onContact(const CallbackData &callbackData) {
				for (auto i = 0; i < callbackData.getNbContactPairs(); i++) {
					auto contactPair = callbackData.getContactPair(i);
					auto body1 = contactPair.getBody1();
					auto body2 = contactPair.getBody2();
					auto collider1 = contactPair.getCollider1();
					auto collider2 = contactPair.getCollider2();
					for (auto j = 0; j < contactPair.getNbContactPoints(); j++) {
						auto contactPoint = contactPair.getContactPoint(j);
						// construct collision
						auto entity = collision.addResponse(-contactPoint.getPenetrationDepth());
						auto normal = contactPoint.getWorldNormal();
						entity->setNormal(Vector3(normal.x, normal.y, normal.z));
						auto collider1LocalToWorldTransform1 = collider1->getLocalToWorldTransform();
						auto collider2LocalToWorldTransform2 = collider2->getLocalToWorldTransform();
						const auto& localPoint1 = contactPoint.getLocalPointOnCollider1();
						const auto& localPoint2 = contactPoint.getLocalPointOnCollider2();
						auto worldPoint1 = collider1LocalToWorldTransform1 * localPoint1;
						auto worldPoint2 = collider2LocalToWorldTransform2 * localPoint2;
						entity->addHitPoint(Vector3(worldPoint1.x, worldPoint1.y, worldPoint1.z));
						entity->addHitPoint(Vector3(worldPoint2.x, worldPoint2.y, worldPoint2.z));
					}
				}
			}

	    private:
			CollisionResponse& collision;
	};
	// do the test
	CustomCollisionCallback customCollisionCallback(collision);
	world->testCollision(body1->rigidBody, body2->rigidBody, customCollisionCallback);
	return collision.getEntityCount() > 0;
}

World* World::clone(const string& id, uint16_t collisionTypeIds)
{
	//
	auto clonedWorld = new World(id);
	for (auto body: bodies) {
		// clone obv
		Body* clonedBody = nullptr;
		auto bodyType = body->getType();

		// test type
		if ((body->getCollisionTypeId() & collisionTypeIds) == 0) continue;

		// clone rigid body
		switch (bodyType) {
			case Body::BODYTYPE_STATIC:
				clonedBody = clonedWorld->addStaticRigidBody(body->id, body->getCollisionTypeId(), body->isEnabled(), body->transform, body->getFriction(), body->boundingVolumes);
				break;
			case Body::BODYTYPE_DYNAMIC:
				clonedBody = clonedWorld->addRigidBody(body->id, body->getCollisionTypeId(), body->isEnabled(), body->transform, body->getRestitution(), body->getFriction(), body->getMass(), body->inertiaTensor, body->boundingVolumes);
				break;
			case Body::BODYTYPE_COLLISION_STATIC:
				clonedBody = clonedWorld->addStaticCollisionBody(body->id, body->getCollisionTypeId(), body->isEnabled(), body->transform, body->boundingVolumes);
				break;
			case Body::BODYTYPE_COLLISION_DYNAMIC:
				clonedBody = clonedWorld->addDynamicCollisionBody(body->id, body->getCollisionTypeId(), body->isEnabled(), body->transform, body->boundingVolumes);
				break;
			default:
				Console::printLine("World::clone(): Unsupported type: " + to_string(bodyType));
				continue;
		}

		// synch additional properties
		synchronize(clonedBody, body);
	}

	//
	return clonedWorld;
}

void World::synchronize(Body* clonedBody, Body* body)
{
	clonedBody->setCollisionTypeIds(body->getCollisionTypeIds());
	clonedBody->setEnabled(body->isEnabled());
	clonedBody->setMass(body->getMass());
	clonedBody->setTransform(body->transform);
	if (clonedBody->getType() == Body::BODYTYPE_DYNAMIC) {
		clonedBody->setLinearVelocity(body->getLinearVelocity());
		clonedBody->setAngularVelocity(body->getAngularVelocity());
	}
}

void World::synchronize(World* world)
{
	for (auto i = 0; i < rigidBodiesDynamic.size(); i++) {
		auto body = rigidBodiesDynamic.at(i);
		auto clonedBody = world->getBody(body->id);
		if (clonedBody == nullptr) {
			Console::printLine("Cloned world::entity '" + body->id + "' not found");
			continue;
		}
		// synch rigid bodies
		synchronize(clonedBody, body);
	}
}

void World::addWorldListener(WorldListener* listener)
{
	worldListeners.push_back(listener);
}

void World::removeWorldListener(WorldListener* listener)
{
	worldListeners.erase(remove(worldListeners.begin(), worldListeners.end(), listener), worldListeners.end());
}
