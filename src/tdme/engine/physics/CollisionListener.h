#pragma once

#include <tdme/engine/physics/fwd-tdme.h>

using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::RigidBody;

/** 
 * Rigid body collision listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::CollisionListener
{

	/** 
	 * On collision
	 * Note: 
	 * The collision response will only live while calling this method. 
	 * If you need it somewhere else you need to clone it
	 * @param rigid body 1
	 * @param rigid body 2
	 * @param collision response
	 */
	virtual void onCollision(RigidBody* rigidBody1, RigidBody* rigidBody2, CollisionResponse* collisionResponse) = 0;

	/** 
	 * On collision begin
	 * Note: 
	 * The collision response will only live while calling this method. 
	 * If you need it somewhere else you need to clone it
	 * @param rigid body 1
	 * @param rigid body 2
	 * @param collision response
	 */
	virtual void onCollisionBegin(RigidBody* rigidBody1, RigidBody* rigidBody2, CollisionResponse* collisionResponse) = 0;

	/** 
	 * On collision end
	 * @param rigid body 1
	 * @param rigid body 2
	 */
	virtual void onCollisionEnd(RigidBody* rigidBody1, RigidBody* rigidBody2) = 0;
};
