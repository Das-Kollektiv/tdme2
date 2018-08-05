#pragma once

#include <tdme/engine/physics/fwd-tdme.h>

using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::Body;

/** 
 * Rigid body collision listener
 * @author Andreas Drewke
 * @version $Id$
 */
struct tdme::engine::physics::CollisionListener
{

	/**
	 * Destructor
	 */
	virtual ~CollisionListener() {}

	/** 
	 * On collision
	 * Note: 
	 * 	The collision response will only live while calling this method.
	 * 	If you need it somewhere else you need to clone it
	 * @param body 1
	 * @param body 2
	 * @param collision response
	 */
	virtual void onCollision(Body* body1, Body* body2, CollisionResponse* collisionResponse) = 0;

	/** 
	 * On collision begin
	 * Note: 
	 * 	The collision response will only live while calling this method.
	 * 	If you need it somewhere else you need to clone it
	 * @param body 1
	 * @param body 2
	 * @param collision response
	 */
	virtual void onCollisionBegin(Body* body1, Body* body2, CollisionResponse* collisionResponse) = 0;

	/** 
	 * On collision end
	 * @param body 1
	 * @param body 2
	 */
	virtual void onCollisionEnd(Body* body1, Body* body2) = 0;
};
