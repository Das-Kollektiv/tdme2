#pragma once

#include <map>
#include <string>

#include <ext/reactphysics3d/src/engine/DynamicsWorld.h>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::Body;
using tdme::engine::physics::WorldListener;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

/** 
 * Physics
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::World final
{
	friend class Body;

private:
	struct BodyCollisionStruct {
		string body1Id;
		string body2Id;
	};

	reactphysics3d::DynamicsWorld world;

	vector<Body*> bodies {  };
	vector<Body*> rigidBodiesDynamic {  };
	map<string, Body*> bodiesById {  };
	map<string, BodyCollisionStruct> bodyCollisionsLastFrame;
	vector<WorldListener*> worldListeners { };

	/**
	 * Synch into cloned body from body
	 * @param cloned body
	 * @param body
	 */
	void synch(Body* clonedBody, Body* body);

public:

	/** 
	 * Resets the physic world
	 */
	void reset();

	/** 
	 * Add a rigid body
	 * @param id
	 * @param enabled
	 * @param collision type id
	 * @param transformations
	 * @param restitution
	 * @param friction
	 * @param mass
	 * @param inertia matrix
	 * @param bounding volumes
	 * @return body
	 */
	Body* addRigidBody(const string& id, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, float restitution, float friction, float mass, const Vector3& inertiaTensor, vector<BoundingVolume*> boundingVolumes);

	/** 
	 * Add a collision body
	 * @param id
	 * @param enabled
	 * @param collision type id
	 * @param transformations
	 * @param bounding volumes
	 * @return body
	 */
	Body* addCollisionBody(const string& id, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, vector<BoundingVolume*> boundingVolumes);

	/**
	 * Add a static rigid body
	 * @param id
	 * @param enabled
	 * @param collision type id
	 * @param transformations
	 * @param friction
	 * @param bounding volumes
	 * @return body
	 */
	Body* addStaticRigidBody(const string& id, bool enabled, uint16_t collisionTypeId, const Transformations& transformations, float friction, vector<BoundingVolume*> boundingVolumes);

	/** 
	 * Returns body identified by id
	 * @param id
	 * @return ridig body
	 */
	Body* getBody(const string& id);

	/** 
	 * Removes body identified by id
	 * @param id
	 */
	void removeBody(const string& id);

	/**
	 * Update world
	 * @param delta time
	 */
	void update(float deltaTime);

	/** 
	 * Synch physics world with engine
	 * @param engine
	 */
	void synch(Engine* engine);

	/** 
	 * Determine height on x,y,u while respecting step up max
	 * @param collision type ids
	 * @param step up max
	 * @param point on which height should be calculated
	 * @param point where height has been determined
	 * @return body from which height was determined or null
	 */
	Body* determineHeight(uint16_t collisionTypeId, float stepUpMax, const Vector3& point, Vector3& dest);

	/**
	 * Check if world collides with given body
	 * @param collision type ids
	 * @param body
	 * @param bodies that collide with given body
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(uint16_t collisionTypeIds, Body* body, vector<Body*>& rigidBodies);

	/**
	 * Check if world collides with given bounding volumes and its transformations, which both form a collision for method runtime
	 * @param collision type ids
	 * @param transformations
	 * @param bounding volume
	 * @param bodies that collide with given body
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(uint16_t collisionTypeIds, const Transformations& transformations, vector<BoundingVolume*> boundingVolumes, vector<Body*>& rigidBodies);

	/**
	 * Check if body 1 collides with body 2
	 * @param body 1
	 * @param body 2
	 * @return if collision happpened or not
	 */
	bool doCollide(Body* body1, Body* body2);

	/** 
	 * Clone this world
	 * @param collision type ids to clone
	 */
	World* clone(uint16_t collisionTypeIds = ~0);

	/** 
	 * Updates given world with this world
	 * Given world should be a clone of this world
	 * @param world
	 */
	void synch(World* world);

	/**
	 * Add a world listener
	 * @param listener
	 */
	void addWorldListener(WorldListener* listener);

	/**
	 * Remove a world listener
	 * @param listener
	 */
	void removeWorldListener(WorldListener* listener);

	/**
	 * Public constructor
	 */
	World();

	/**
	 * Destructor
	 */
	~World();

};
