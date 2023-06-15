#pragma once

#include <map>
#include <string>
#include <vector>

#include <reactphysics3d/constraint/Joint.h>
#include <reactphysics3d/engine/PhysicsCommon.h>
#include <reactphysics3d/engine/PhysicsWorld.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utilities/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::physics::Body;
using tdme::engine::physics::BodyHierarchy;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::WorldListener;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::Engine;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/**
 * Dynamic physics world class
 * @author Andreas Drewke
 */
class tdme::engine::physics::World final
{
	friend class Body;
	friend class tdme::engine::primitives::Capsule;
	friend class tdme::engine::primitives::ConvexMesh;
	friend class tdme::engine::primitives::HeightMap;
	friend class tdme::engine::primitives::OrientedBoundingBox;
	friend class tdme::engine::primitives::Sphere;
	friend class tdme::engine::primitives::TerrainMesh;

private:
	struct BodyCollisionStruct {
		string body1Id;
		string body2Id;
	};

	reactphysics3d::PhysicsCommon physicsCommon;
	reactphysics3d::PhysicsWorld* world { nullptr };

	vector<Body*> bodies;
	vector<Body*> rigidBodiesDynamic;
	map<string, Body*> bodiesById;
	map<string, reactphysics3d::Joint*> jointsById;
	map<string, BodyCollisionStruct> bodyCollisionsLastFrame;
	vector<WorldListener*> worldListeners;

	/**
	 * Synchronize cloned body from body
	 * @param clonedBody cloned body
	 * @param body body
	 */
	void synchronize(Body* clonedBody, Body* body);

public:
	/**
	 * Public constructor
	 * @param id id
	 */
	World(const string& id);

	/**
	 * Destructor
	 */
	~World();

	/**
	 * @return id
	 */
	const string& getId() {
		return world->getName();
	}

	/**
	 * Resets the physic world
	 */
	void reset();

	/**
	 * Add a rigid body
	 * @param id id
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param restitution restitution
	 * @param friction friction
	 * @param mass mass
	 * @param inertiaTensor inertia matrix
	 * @param boundingVolumes bounding volumes
	 * @return body
	 */
	Body* addRigidBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, float restitution, float friction, float mass, const Vector3& inertiaTensor, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false);

	/**
	 * Add a static collision body
	 * @param id id
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param boundingVolumes bounding volumes
	 * @return body
	 */
	Body* addStaticCollisionBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false);

	/**
	 * Add a dynamic collision body
	 * @param id id
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param boundingVolumes bounding volumes
	 * @return body
	 */
	Body* addDynamicCollisionBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false);

	/**
	 * Add a static rigid body
	 * @param id id
	 * @param collisionTypeId collision type id
	 * @param enabled enabled
	 * @param transform transform
	 * @param friction friction
	 * @param boundingVolumes bounding volumes
	 * @return body
	 */
	Body* addStaticRigidBody(const string& id, uint16_t collisionTypeId, bool enabled, const Transform& transform, float friction, const vector<BoundingVolume*>& boundingVolumes, bool hierarchy = false);

	/**
	 * Returns body identified by id
	 * @param id id
	 * @return body
	 */
	inline Body* getBody(const string& id) {
		auto bodyByIdIt = bodiesById.find(id);
		if (bodyByIdIt != bodiesById.end()) {
			return bodyByIdIt->second;
		}
		return nullptr;
	}

	/**
	 * Returns body hierarchy identified by id
	 * @param id id
	 * @return body hierarchy
	 */
	BodyHierarchy* getBodyHierarchy(const string& id);

	/**
	 * Removes body identified by id
	 * @param id id
	 */
	void removeBody(const string& id);

	/**
	 * Add fixed joint
	 * @param id id
	 * @param body1 body 1
	 * @param body2 body 2
	 */
	void addFixedJoint(const string& id, Body* body1, Body* body2);

	/**
	 * Remove joint
	 * @param id id
	 */
	void removeJoint(const string& id);

	/**
	 * Update world
	 * @param deltaTime delta time
	 */
	void update(float deltaTime);

	/**
	 * Synchronize physics world with engine
	 * @param engine engine
	 */
	void synchronize(Engine* engine);

	/**
	 * Determine height on x,y,u while respecting step up max
	 * @param collisionTypeId collision type ids
	 * @param stepUpMax step up max
	 * @param point point on which height should be calculated
	 * @param heightPoint point with determined height
	 * @param minHeight min height to determine height from
	 * @param maxHeight max height to start raytracing from
	 * @return body from which height was determined or null
	 */
	Body* determineHeight(uint16_t collisionTypeIds, float stepUpMax, const Vector3& point, Vector3& heightPoint, float minHeight = -10000.0f, float maxHeight = 10000.0f);

	/**
	 * Do a ray cast from given start to given end point, if there is any body with given collision type in between
	 * then the body is returned and a hit point is reported
	 * @param collisionTypeIds collision type ids
	 * @param start start
	 * @param end end
	 * @param hitPoint hit point
	 * @param actorId actor rigid body id, which will be exlcluded from ray tracing
	 * @return body
	 *
	 */
	Body* doRayCasting(uint16_t collisionTypeIds, const Vector3& start, const Vector3& end, Vector3& hitPoint, const string& actorId = string());

	/**
	 * Check if world collides with given body
	 * @param collisionTypeIds collision type ids
	 * @param body body
	 * @param collisionBodies bodies that collide with given body
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(uint16_t collisionTypeIds, Body* body, vector<Body*>& collisionBodies);

	/**
	 * Check if world collides with given bounding volumes and its transform, which both form a collision for method runtime
	 * @param collisionTypeIds collision type ids
	 * @param transform transform
	 * @param boundingVolumes bounding volume
	 * @param collisionBodies bodies that collide with given body
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(uint16_t collisionTypeIds, const Transform& transform, vector<BoundingVolume*> boundingVolumes, vector<Body*>& collisionBodies);

	/**
	 * Check if body 1 collides with body 2
	 * @param body1 body 1
	 * @param body2 body 2
	 * @return if collision happpened or not
	 */
	bool doCollide(Body* body1, Body* body2);

	/**
	 * Get collision response
	 * @param body1 body 1
	 * @param body2 body 2
	 * @param collision collision response
	 * @return if having hit points
	 */
	bool getCollisionResponse(Body* body1, Body* body2, CollisionResponse& collision);

	/**
	 * Clone this world
	 * @param id id
	 * @param collisionTypeIds collision type ids to clone
	 */
	World* clone(const string& id, uint16_t collisionTypeIds = ~0);

	/**
	 * Synchronize given world with this world
	 * Given world should be a clone of this world
	 * @param world world
	 */
	void synchronize(World* world);

	/**
	 * Add a world listener
	 * @param listener listener
	 */
	void addWorldListener(WorldListener* listener);

	/**
	 * Remove a world listener
	 * @param listener listener
	 */
	void removeWorldListener(WorldListener* listener);

};
