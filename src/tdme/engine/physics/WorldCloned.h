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

#include <string>

#include <tdme/engine/physics/RigidBodyCloned.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/fwd-tdme.h>

using std::map;
using std::string;
using std::vector;

using tdme::engine::Transformations;
using tdme::engine::physics::RigidBodyCloned;
using tdme::engine::primitives::BoundingVolume;

/** 
 * Physics
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::WorldCloned: public World
{
	friend class World;
	friend class RigidBodyCloned;

protected:

	/**
	 * Synch into cloned rigid body from rigid body
	 * @param cloned rigid body
	 * @param rigid body
	 */
	void synch(RigidBody* clonedRigidBody, RigidBody* rigidBody);

	/**
	 * Protected constructor
	 */
	WorldCloned();

public:

	/**
	 * Create rigid body
	 * @param id
	 * @param enabled
	 * @param type id
	 * @param obv
	 * @param cbv
	 * @param transformations
	 * @param restitution
	 * @param friction
	 * @param mass in kg
	 * @param inertia matrix settings
	 */
	virtual RigidBody* createRigidBody(const string& id, bool enabled, int32_t typeId, BoundingVolume* obv, BoundingVolume* cbv, const Transformations& transformations, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inverseInertiaSettings);

	/**
	 * Add a rigid body
	 * @param rigid body
	 * @return rigid body
	 */
	virtual RigidBody* addRigidBody(RigidBody* rigidBody);

	/**
	 * Destructor
	 */
	virtual ~WorldCloned();

};
