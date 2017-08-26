// Generated from /tdme/src/tdme/engine/physics/ConstraintsEntity.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <java/lang/Object.h>

using std::array;
using std::vector;

using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::RigidBody;
using tdme::math::Vector3;

/** 
 * Physics constraints entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ConstraintsEntity final
{
private:
	static constexpr float HITPOINT_TOLERANCE { 0.3f };

public: /* protected */
	RigidBody* rb1 {  };
	RigidBody* rb2 {  };
	CollisionResponse collision;

private:
	array<Vector3, 2> frictionVectors { };
	float muMg {  };

public: /* protected */

	/** 
	 * Protected constructor
	 * @param rb1
	 * @param rb2
	 * @param collision
	 */
	void set(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision);

	/** 
	 * Compute jacobian
	 * @param constraint idx
	 * @param jacobian matrices
	 */
	void computeJacobian(int32_t constraintIdx, vector<array<Matrix1x6, 2>>* jacobianMatrices);

	/** 
	 * Compute lower bounds
	 * @param constraint idx
	 * @param lower bounds
	 */
	void computeLowerBound(int32_t constraintIdx, DynamicVector* lowerBounds);

	/** 
	 * Create upper bounds
	 * @param constraint idx
	 * @param upper bounds
	 */
	void computeUpperBound(int32_t constraintIdx, DynamicVector* upperBounds);

	/** 
	 * Compute baumgarte
	 * @param constraint idx
	 * @param error values
	 */
	void computeBaumgarte(int32_t constraintIdx, DynamicVector* errorValues);

public: /* protected */
	/**
	 * Protected constructor
	 */
	ConstraintsEntity();
};
