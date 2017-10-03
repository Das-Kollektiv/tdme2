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

#include <array>
#include <map>
#include <vector>
#include <string>

#include <fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/ConstraintsEntity.h>
#include <tdme/engine/physics/ContactCache.h>
#include <tdme/engine/physics/DynamicVector.h>
#include <tdme/engine/physics/Matrix1x6.h>
#include <tdme/engine/physics/Matrix6x6.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/fwd-tdme.h>

using std::array;
using std::map;
using std::vector;
using std::wstring;

using tdme::engine::physics::ConstraintsEntity;
using tdme::engine::physics::ContactCache;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::Vector6;
using tdme::math::Vector3;

/** 
 * Constraints solver
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ConstraintsSolver final
{
public: /* protected */
	static constexpr int32_t BODIES_MAX { 1024 };
	static constexpr int32_t CONSTRAINTS_MAX { 1024 * 3 };

private:
	int32_t constraintsEntityCount {  };
	int32_t constraintsCount {  };
	vector<RigidBody*>* rigidBodies {  };
	map<wstring, RigidBody*> constrainedBodies {  };
	ContactCache contactCache {  };
	vector<array<int32_t, 2>> constraintsBodyIdxMap {  };
	vector<array<Matrix1x6, 2>> jacobianMatrices {  };
	vector<array<Vector6, 2>> bVectors {  };
	DynamicVector lambda {  };
	DynamicVector lambdaInit {  };
	DynamicVector errorValues {  };
	DynamicVector b {  };
	DynamicVector lowerBounds {  };
	DynamicVector upperBounds {  };
	vector<float> d {  };
	vector<ConstraintsEntity> constraintsEntities {  };
	vector<Matrix6x6> invInertiaMatrices {  };
	vector<Vector6> velocityVectors {  };
	vector<Vector6> constrainedVelocityVectors {  };
	vector<Vector6> forcesVectors {  };
	vector<Vector6> a {  };
	vector<RigidBody*> rigidBodiesVelocityChange {  };
	vector<RigidBody*> rigidBodiesCurrentChain {  };
	vector<RigidBody*> rigidBodiesChainsResult {  };
	vector<float> tmpLamdaValues {  };

public: /* protected */

	/** 
	 * Reset
	 */
	void reset();

	/** 
	 * @return constraints entity
	 */
	ConstraintsEntity* allocateConstraintsEntity();

private:

	/** 
	 * Init method
	 * @param delta time
	 * @param constraints
	 * @param rigid bodies
	 */
	void initialize(float dt);

	/** 
	 * Fill matrices
	 */
	void fillMatrices();

	/** 
	 * Compute vector b
	 * @param delta time
	 */
	void computeVectorB(float dt);

	/** 
	 * Computes matrix b
	 */
	void computeMatrixB();

	/** 
	 * Compute vector a
	 * @param a
	 */
	void computeVectorA();

	/** 
	 * PGLCP
	 */
	void PGLCP();

	/** 
	 * Compute vector velocity constraints
	 */
	void computeVectorVelocityConstraints(float dt);

	/** 
	 * Update contact cache
	 */
	void updateContactCache();

	/** 
	 * Finds rigid body successors in a direction for given rigid body src 
	 * @param rigid body src
	 * @param normal last
	 * @param rigid bodies current chain
	 * @param rigid bodies current chain result
	 * @param calls
	 */
	void checkChainSuccessor(RigidBody* rigidBodySrc, Vector3* normalLast, vector<RigidBody*>& rigidBodiesCurrentChain);

public: /* protected */

	/** 
	 * Process rigid body chain
	 * @param idx
	 * @param rigid bodies current chain
	 * @return new idx to process
	 */
	int32_t processRigidBodyChain(int32_t idx, const vector<RigidBody*>& rigidBodiesCurrentChain);

	/** 
	 * Check if we have any user velocity rigids
	 * which have opposite velocity and do collide directly or via other objects
	 */
	void checkVelocityConstraint();

	/** 
	 * Compute 
	 * @param delta time
	 * @param constraints
	 * @param rigid bodies
	 */
	void compute(float dt);

private:

	/** 
	 * Set constrained linear and angular velocity for given body into dest vector
	 * @param body
	 * @param dest
	 */
	void getConstrainedVelocity(RigidBody* body, Vector3& linearVelocity, Vector3& angularVelocity);

public: /* protected */

	/** 
	 * Updates all bodies 
	 * @param delta time
	 */
	void updateAllBodies(float deltaTime);

	/**
	 * Protected constructor
	 * @param rigid bodies
	 */
	ConstraintsSolver(vector<RigidBody*>* rigidBodies);
};
