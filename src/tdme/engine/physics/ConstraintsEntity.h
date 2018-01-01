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
#include <vector>

#include <tdme/tdme.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Math.h>
#include <tdme/engine/physics/fwd-tdme.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/DynamicVector.h>
#include <tdme/engine/physics/Matrix1x6.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/fwd-tdme.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Float.h>

using std::array;
using std::vector;

using tdme::engine::physics::ConstraintsEntity;
using tdme::math::Math;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::RigidBody;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::Float;

/** 
 * Physics constraints entity
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::engine::physics::ConstraintsEntity final
{
	friend class ConstraintsSolver;
	friend class World;

private:
	static constexpr float HITPOINT_TOLERANCE { 0.3f };

	RigidBody* rb1 {  };
	RigidBody* rb2 {  };
	CollisionResponse collision;

	array<Vector3, 2> frictionVectors { };
	float muMg {  };

	/** 
	 * Protected constructor
	 * @param rb1
	 * @param rb2
	 * @param collision
	 */
	inline void set(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision) {
		this->collision.fromResponse(collision);
		this->rb1 = rb1;
		this->rb2 = rb2;
		//	see http://en.wikipedia.org/wiki/Friction#Coefficient_of_friction
		muMg = ((rb1->friction + rb2->friction) / 2.0f) * ((rb1->mass + rb2->mass) / 2.0f) * MathTools::g;
		// our collision normal is the vector object a collides with object b
		this->collision.getNormal()->scale(-1.0f);
		// compute first friction vector
		this->collision.getNormal()->computeOrthogonalVector(this->frictionVectors[0]);
		// compute second friction vector
		Vector3::computeCrossProduct(*this->collision.getNormal(), this->frictionVectors[0], this->frictionVectors[1]);
	}

	/** 
	 * Compute jacobian
	 * @param constraint idx
	 * @param jacobian matrices
	 */
	inline void computeJacobian(int32_t constraintIdx, vector<array<Matrix1x6, 2>>* jacobianMatrices) {
		Vector3 r1;
		Vector3 r2;
		Vector3 r1CrossN;
		Vector3 r2CrossN;
		Vector3 r1CrossU1;
		Vector3 r2CrossU1;
		Vector3 r1CrossU2;
		Vector3 r2CrossU2;
		Vector3 tmpVector3;

		auto& body1Position = rb1->getPosition();
		auto& body2Position = rb2->getPosition();
		auto n = collision.getNormal();
		auto t1 = frictionVectors[0];
		auto t2 = frictionVectors[1];
		Matrix1x6* jacobianMatrix;
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			auto point = collision.getHitPointAt(hitPointIdx);
			r1.set(*point).sub(body1Position);
			r2.set(*point).sub(body2Position);
			Vector3::computeCrossProduct(r1, *n, r1CrossN);
			Vector3::computeCrossProduct(r2, *n, r2CrossN);
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(*n).scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(r1CrossN).scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, *n);
			jacobianMatrix->setValue(3, r2CrossN);
			currentConstraintIdx++;
			Vector3::computeCrossProduct(r1, t1, r1CrossU1);
			Vector3::computeCrossProduct(r2, t1, r2CrossU1);
			Vector3::computeCrossProduct(r1, t2, r1CrossU2);
			Vector3::computeCrossProduct(r2, t2, r2CrossU2);
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(t1).scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(r1CrossU1).scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, t1);
			jacobianMatrix->setValue(3, r2CrossU1);
			currentConstraintIdx++;
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(t2).scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(r1CrossU2).scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, t2);
			jacobianMatrix->setValue(3, r2CrossU2);
			currentConstraintIdx++;
		}
	}

	/** 
	 * Compute lower bounds
	 * @param constraint idx
	 * @param lower bounds
	 */
	inline void computeLowerBound(int32_t constraintIdx, DynamicVector* lowerBounds) {
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			lowerBounds->setValue(currentConstraintIdx++, 0.0f); // Lower bound for the contact constraint
			lowerBounds->setValue(currentConstraintIdx++, -muMg); // Lower bound for the first friction constraint
			lowerBounds->setValue(currentConstraintIdx++, -muMg); // Lower bound for the second friction constraint
		}
	}

	/** 
	 * Create upper bounds
	 * @param constraint idx
	 * @param upper bounds
	 */
	inline void computeUpperBound(int32_t constraintIdx, DynamicVector* upperBounds) {
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			upperBounds->setValue(currentConstraintIdx++, Float::POSITIVE_INFINITY); // Upper bound for the contact constraint
			upperBounds->setValue(currentConstraintIdx++, +muMg); // Upper bound for the first friction constraint
			upperBounds->setValue(currentConstraintIdx++, +muMg); // Upper bound for the second friction constraint
		}
	}

	/** 
	 * Compute baumgarte
	 * @param constraint idx
	 * @param error values
	 */
	inline void computeBaumgarte(int32_t constraintIdx, DynamicVector* errorValues) {
		auto currentConstraintIdx = constraintIdx;
		auto restitutionCoeff = rb1->restitution + rb2->restitution;
		auto penetration = collision.getPenetration();
		auto errorValue = Math::abs(restitutionCoeff * (Vector3::computeDotProduct(*collision.getNormal(), rb1->angularVelocity) - Vector3::computeDotProduct(*collision.getNormal(), rb2->angularVelocity))) + (0.4f * penetration);
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			errorValues->setValue(currentConstraintIdx++, errorValue); // Error value for contact constraint
			errorValues->setValue(currentConstraintIdx++, 0.0f); // Error value for friction constraint
			errorValues->setValue(currentConstraintIdx++, 0.0f); // Error value for friction constraint
		}
	}

public:
	/**
	 * Protected constructor
	 */
	inline ConstraintsEntity() {
	}

};
