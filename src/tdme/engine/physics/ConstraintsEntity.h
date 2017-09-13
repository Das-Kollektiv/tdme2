// Generated from /tdme/src/tdme/engine/physics/ConstraintsEntity.java

#pragma once

#include <array>
#include <vector>

#include <fwd-tdme.h>
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
	void set(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision) {
		this->collision.fromResponse(collision);
		this->rb1 = rb1;
		this->rb2 = rb2;
		muMg = ((rb1->friction + rb2->friction) / 2.0f) * ((rb1->mass + rb2->mass) / 2.0f) * MathTools::g;
		this->collision.getNormal()->scale(-1.0f);
		this->collision.getNormal()->computeOrthogonalVector(&this->frictionVectors[0]);
		Vector3::computeCrossProduct(this->collision.getNormal(), &this->frictionVectors[0], &this->frictionVectors[1]);
	}

	/** 
	 * Compute jacobian
	 * @param constraint idx
	 * @param jacobian matrices
	 */
	void computeJacobian(int32_t constraintIdx, vector<array<Matrix1x6, 2>>* jacobianMatrices) {
		Vector3 r1;
		Vector3 r2;
		Vector3 r1CrossN;
		Vector3 r2CrossN;
		Vector3 r1CrossU1;
		Vector3 r2CrossU1;
		Vector3 r1CrossU2;
		Vector3 r2CrossU2;
		Vector3 tmpVector3;

		auto body1Position = rb1->getPosition();
		auto body2Position = rb2->getPosition();
		auto n = collision.getNormal();
		auto t1 = frictionVectors[0];
		auto t2 = frictionVectors[1];
		Matrix1x6* jacobianMatrix;
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			auto point = collision.getHitPointAt(hitPointIdx);
			r1.set(point)->sub(body1Position);
			r2.set(point)->sub(body2Position);
			Vector3::computeCrossProduct(&r1, n, &r1CrossN);
			Vector3::computeCrossProduct(&r2, n, &r2CrossN);
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(n)->scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(&r1CrossN)->scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, n);
			jacobianMatrix->setValue(3, &r2CrossN);
			currentConstraintIdx++;
			Vector3::computeCrossProduct(&r1, &t1, &r1CrossU1);
			Vector3::computeCrossProduct(&r2, &t1, &r2CrossU1);
			Vector3::computeCrossProduct(&r1, &t2, &r1CrossU2);
			Vector3::computeCrossProduct(&r2, &t2, &r2CrossU2);
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(&t1)->scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(&r1CrossU1)->scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, &t1);
			jacobianMatrix->setValue(3, &r2CrossU1);
			currentConstraintIdx++;
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][0];
			jacobianMatrix->setValue(0, tmpVector3.set(&t2)->scale(-1.0f));
			jacobianMatrix->setValue(3, tmpVector3.set(&r1CrossU2)->scale(-1.0f));
			jacobianMatrix = &(*jacobianMatrices)[currentConstraintIdx][1];
			jacobianMatrix->setValue(0, &t2);
			jacobianMatrix->setValue(3, &r2CrossU2);
			currentConstraintIdx++;
		}
	}

	/** 
	 * Compute lower bounds
	 * @param constraint idx
	 * @param lower bounds
	 */
	void computeLowerBound(int32_t constraintIdx, DynamicVector* lowerBounds) {
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			lowerBounds->setValue(currentConstraintIdx++, 0.0f);
			lowerBounds->setValue(currentConstraintIdx++, -muMg);
			lowerBounds->setValue(currentConstraintIdx++, -muMg);
		}
	}

	/** 
	 * Create upper bounds
	 * @param constraint idx
	 * @param upper bounds
	 */
	void computeUpperBound(int32_t constraintIdx, DynamicVector* upperBounds) {
		auto currentConstraintIdx = constraintIdx;
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			upperBounds->setValue(currentConstraintIdx++, Float::POSITIVE_INFINITY);
			upperBounds->setValue(currentConstraintIdx++, +muMg);
			upperBounds->setValue(currentConstraintIdx++, +muMg);
		}
	}

	/** 
	 * Compute baumgarte
	 * @param constraint idx
	 * @param error values
	 */
	void computeBaumgarte(int32_t constraintIdx, DynamicVector* errorValues) {
		auto currentConstraintIdx = constraintIdx;
		auto restitutionCoeff = rb1->restitution + rb2->restitution;
		auto penetration = collision.getPenetration();
		auto errorValue = Math::abs(restitutionCoeff * (Vector3::computeDotProduct(collision.getNormal(), &rb1->angularVelocity) - Vector3::computeDotProduct(collision.getNormal(), &rb2->angularVelocity))) + (0.4f * penetration);
		for (auto hitPointIdx = 0; hitPointIdx < collision.getHitPointsCount(); hitPointIdx++) {
			errorValues->setValue(currentConstraintIdx++, errorValue);
			errorValues->setValue(currentConstraintIdx++, 0.0f);
			errorValues->setValue(currentConstraintIdx++, 0.0f);
		}
	}

public: /* protected */
	/**
	 * Protected constructor
	 */
	ConstraintsEntity() {
	}
};
