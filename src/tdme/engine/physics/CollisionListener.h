// Generated from /tdme/src/tdme/engine/physics/CollisionListener.java

#pragma once

#include <tdme/engine/physics/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::RigidBody;



/** 
 * Rigid body collision listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::CollisionListener
	: public virtual Object
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

	// Generated
	static ::java::lang::Class *class_();
};
