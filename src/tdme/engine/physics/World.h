/*********************************************************************************
 * This source code is based on                                                  *
 * ReactPhysics3D physics library, http://www.reactphysics3d.com                 *
 * Copyright (c) 2010-2015 Daniel Chappuis                                       *
 *********************************************************************************
 *                                                                               *
 * This software is provided 'as-is', without any express or implied warranty.   *
 * In no event will the authors be held liable for any damages arising from the  *
 * use of this software.                                                         *
 *                                                                               *
 * Permission is granted to anyone to use this software for any purpose,         *
 * including commercial applications, and to alter it and redistribute it        *
 * freely, subject to the following restrictions:                                *
 *                                                                               *
 * 1. The origin of this software must not be misrepresented; you must not claim *
 *    that you wrote the original software. If you use this software in a        *
 *    product, an acknowledgment in the product documentation would be           *
 *    appreciated but is not required.                                           *
 *                                                                               *
 * 2. Altered source versions must be plainly marked as such, and must not be    *
 *    misrepresented as being the original software.                             *
 *                                                                               *
 * 3. This notice may not be removed or altered from any source distribution.    *
 *                                                                               *
 ********************************************************************************/

#pragma once

#include <map>
#include <string>
#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/fwd-tdme.h>
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
	friend class RigidBody;

private:
	PhysicsPartition* partition {  };

	struct RigidBodyCollisionStruct {
		string rigidBody1Id;
		string rigidBody2Id;
	};

	vector<RigidBody*> rigidBodies {  };
	vector<RigidBody*> rigidBodiesDynamic {  };
	map<string, RigidBody*> rigidBodiesById {  };
	ConstraintsSolver* constraintsSolver { nullptr };
	map<string, RigidBodyCollisionStruct> rigidBodyCollisionsLastFrame;

	/**
	 * Do collision test between rigid bodies
	 * @param rigid body 1
	 * @param rigid body 1
	 * @param rigid body tested collisions
	 * @param rigid body collisions current frame
	 * @param collision movement
	 * @param collision
	 * @param use and invert collision
	 */
	inline void doCollisionTest(RigidBody* rigidBody1, RigidBody* rigidBody2, map<string, RigidBodyCollisionStruct>& rigidBodyTestedCollisions, map<string, RigidBodyCollisionStruct>& rigidBodyCollisionsCurrentFrame, Vector3& collisionMovement, CollisionResponse &collision, bool useAndInvertCollision);
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
	RigidBody* addRigidBody(const string& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float restitution, float friction, float mass, const Matrix4x4& inertiaMatrix);

	/** 
	 * Add a static rigid body
	 * @param id
	 * @param enabled
	 * @param transformations
	 * @param obv
	 * @param friction
	 * @return rigid body
	 */
	RigidBody* addStaticRigidBody(const string& id, bool enabled, int32_t typeId, Transformations* transformations, BoundingVolume* obv, float friction);

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

private:

	/** 
	 * Returns higher vector of
	 * @param a
	 * @param b
	 * @return higher vector
	 */
	static const Vector3& higher(const Vector3& a, const Vector3& b);

public:

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
	 * Check if world collides with given bounding volume
	 * @param type ids
	 * @param bounding volume
	 * @param rigid bodies that collide with bounding volume
	 * @return if collision happpened or not
	 */
	bool doesCollideWith(int32_t typeIds, BoundingVolume* boundingVolume, vector<RigidBody*>& rigidBodies);

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

	/**
	 * Destructor
	 */
	~World();
};
