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
using tdme::engine::physics::RigidBody;
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
	friend class RigidBody;

private:
	struct RigidBodyCollisionStruct {
		string rigidBody1Id;
		string rigidBody2Id;
	};

	reactphysics3d::DynamicsWorld world;

	vector<RigidBody*> rigidBodies {  };
	vector<RigidBody*> rigidBodiesDynamic {  };
	map<string, RigidBody*> rigidBodiesById {  };
	map<string, RigidBodyCollisionStruct> rigidBodyCollisionsLastFrame;
	vector<WorldListener*> worldListeners { };

	/**
	 * Synch into cloned rigid body from rigid body
	 * @param cloned rigid body
	 * @param rigid body
	 */
	void synch(RigidBody* clonedRigidBody, RigidBody* rigidBody);

public:

	/** 
	 * Resets the physic world
	 */
	void reset();

	/** 
	 * Add a rigid body
	 * @param id
	 * @param enabled
	 * @param type id
	 * @param transformations
	 * @param bounding volume
	 * @param restitution
	 * @param friction
	 * @param mass
	 * @param inertia matrix
	 * @return rigid body
	 */
	RigidBody* addRigidBody(const string& id, bool enabled, uint16_t typeId, const Transformations& transformations, BoundingVolume* boundingVolume, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix);

	/** 
	 * Add a static rigid body
	 * @param id
	 * @param enabled
	 * @param type id
	 * @param transformations
	 * @param bounding volume
	 * @param friction
	 * @return rigid body
	 */
	RigidBody* addStaticRigidBody(const string& id, bool enabled, uint16_t typeId, const Transformations& transformations, BoundingVolume* boundingVolume, float friction);

	/** 
	 * Returns rigid body identified by id 
	 * @param id
	 * @return ridig body
	 */
	RigidBody* getRigidBody(const string& id);

	/** 
	 * Removes rigid body identified by id
	 * @param id
	 */
	void removeRigidBody(const string& id);

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
	 * @param type ids
	 * @param step up max
	 * @param point on which height should be calculated
	 * @param point where height has been determined
	 * @return rigid body from which height was determined or null
	 */
	RigidBody* determineHeight(int32_t typeIds, float stepUpMax, const Vector3& point, Vector3& dest);

	/** 
	 * Determine height of bounding volume
	 * @param type ids
	 * @param step up max
	 * @param bounding volume
	 * @param point
	 * @param dest
	 * @return rigid body from which height was determined or null
	 */
	RigidBody* determineHeight(int32_t typeIds, float stepUpMax, BoundingVolume* boundingVolume, const Vector3& point, Vector3& dest);

	/** 
	 * Check if world collides with given bounding box
	 * @param type ids
	 * @param bounding volume
	 * @param rigid bodies that collide with bounding volume
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(int32_t typeIds, BoundingBox* boundingBox, vector<RigidBody*>& rigidBodies);

	/**
	 * Check if world collides with given bounding volume
	 * @param type ids
	 * @param bounding volume
	 * @param rigid bodies that collide with bounding volume
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(int32_t typeIds, BoundingVolume* boundingVolume, vector<RigidBody*>& rigidBodies);

	/** 
	 * Clone this world
	 * @param collision type ids to clone
	 */
	World* clone(uint16_t collisionTypeIds);

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
