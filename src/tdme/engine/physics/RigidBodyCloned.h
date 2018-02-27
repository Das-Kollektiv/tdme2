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

#include <tdme/tdme.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/primitives/fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

using std::string;

using tdme::engine::Transformations;
using tdme::engine::physics::World;
using tdme::engine::physics::RigidBody;
using tdme::engine::primitives::BoundingVolume;

/** 
 * Rigid Body class for cloned rigid body which reuses original rigid body data as much as it can
 * ported from "game physics - a practical introduction/ben kenwright"
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::RigidBodyCloned: public RigidBody
{
public:

	/**
	 * Protected constructor
	 * @param partition
	 * @param id
	 * @param enabled
	 * @param type id
	 * @param original bounding volume
	 * @param computed bounding volume
	 * @param transformations
	 * @param restitution
	 * @param mass in kg
	 */
	RigidBodyCloned(World* world, const string& id, bool enabled, int32_t typeId, BoundingVolume* obv, BoundingVolume* cbv, const Transformations& transformations, float restitution, float friction, float mass, const RigidBody::InertiaMatrixSettings& inverseInertiaSettings);

	/** 
	 * Synchronizes this rigid body with transformations
	 * @param transformations
	 */
	virtual void fromTransformations(const Transformations& transformations);

	/**
	 * Dispose
	 */
	virtual void dispose() override;
};
