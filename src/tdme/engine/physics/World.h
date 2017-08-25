// Generated from /tdme/src/tdme/engine/physics/World.java

#pragma once

#include <map>
#include <string>
#include <vector>

#include <fwd-tdme.h>
#include <tdme/engine/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/utils/fwd-tdme.h>

using std::map;
using std::wstring;
using std::vector;

using tdme::engine::Engine;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::ConstraintsSolver;
using tdme::engine::physics::PhysicsPartition;
using tdme::engine::physics::RigidBody;
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
public: /* protected */
	PhysicsPartition* partition {  };

private:
	struct RigidBodyCollisionStruct {
		int32_t rigidBody1Idx;
		int32_t rigidBody2Idx;
	};

	vector<RigidBody*> rigidBodies {  };
	vector<RigidBody*> rigidBodiesDynamic {  };
	map<wstring, RigidBody*> rigidBodiesById {  };
	ConstraintsSolver* constraintsSolver { nullptr };
	map<wstring, RigidBodyCollisionStruct> rigidBodyCollisionsLastFrame;
public:

	/** 
	 * Resets the physic world
	 */
	void reset();

	/** 
	 * @return partition algorithm
	 */
	PhysicsPartition* getPartition();

	/** 
	 * Set partition algorithm
	 * @param partition
	 */
	void setPartition(PhysicsPartition* partition);

	/** 
	 * Add a rigid body
	 * @param id
	 * @param enabled
	 * @param transformations
	 * @param obv
	 * @param restitution
	 * @param friction
	 * @param mass
	 * @param inertia matrix
	 * @return rigid body
	 */
	RigidBody* addRigidBody(const wstring& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float restitution, float friction, float mass, Matrix4x4* inertiaMatrix);

	/** 
	 * Add a static rigid body
	 * @param id
	 * @param enabled
	 * @param transformations
	 * @param obv
	 * @param friction
	 * @return rigid body
	 */
	RigidBody* addStaticRigidBody(const wstring& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float friction);

	/** 
	 * Returns rigid body identified by id 
	 * @param id
	 * @return ridig body
	 */
	RigidBody* getRigidBody(const wstring& id);

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

private:

	/** 
	 * Returns higher vector of
	 * @param a
	 * @param b
	 * @return higher vector
	 */
	static Vector3* higher(Vector3* a, Vector3* b);

public:

	/** 
	 * Determine height on x,y,u while respecting step up max
	 * @param type ids
	 * @param step up max
	 * @param point on which height should be calculated
	 * @param point where height has been determined
	 * @return rigid body from which height was determined or null
	 */
	RigidBody* determineHeight(int32_t typeIds, float stepUpMax, Vector3* point, Vector3* dest);

	/** 
	 * Determine height of bounding volume
	 * @param type ids
	 * @param step up max
	 * @param bounding volume
	 * @param point
	 * @param dest
	 * @return rigid body from which height was determined or null
	 */
	RigidBody* determineHeight(int32_t typeIds, float stepUpMax, BoundingVolume* boundingVolume, Vector3* point, Vector3* dest);

	/** 
	 * Check if world collides with given bounding volume
	 * @param type ids
	 * @param bounding volume
	 * @return collided rigid bodies
	 */
	const vector<RigidBody*> doesCollideWith(int32_t typeIds, BoundingVolume* boundingVolume);

	/** 
	 * Clone this world
	 */
	World* clone();

private:

	/** 
	 * Synch into cloned rigid body from rigid body
	 * @param cloned rigid body
	 * @param rigid body
	 */
	void synch(RigidBody* clonedRigidBody, RigidBody* rigidBody);

public:

	/** 
	 * Updates given world with this world
	 * Given world should be a clone of this world
	 * @param world
	 */
	void synch(World* world);

	/**
	 * Public constructor
	 */
	World();
};
