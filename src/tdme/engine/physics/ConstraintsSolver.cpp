#include <tdme/engine/physics/ConstraintsSolver.h>

#include <vector>

#include <tdme/math/Math.h>
#include <tdme/engine/physics/ConstraintsEntity.h>
#include <tdme/engine/physics/ContactCache_ContactCacheInfo.h>
#include <tdme/engine/physics/ContactCache.h>
#include <tdme/engine/physics/DynamicVector.h>
#include <tdme/engine/physics/Matrix1x6.h>
#include <tdme/engine/physics/Matrix6x6.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/engine/physics/Vector6.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::physics::ConstraintsSolver;
using tdme::math::Math;
using tdme::engine::physics::ConstraintsEntity;
using tdme::engine::physics::ContactCache_ContactCacheInfo;
using tdme::engine::physics::ContactCache;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::Matrix6x6;
using tdme::engine::physics::RigidBody;
using tdme::engine::physics::Vector6;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

ConstraintsSolver::ConstraintsSolver(vector<RigidBody*>* rigidBodies)
{
	constraintsEntityCount = 0;
	constraintsBodyIdxMap.resize(CONSTRAINTS_MAX);
	jacobianMatrices.resize(CONSTRAINTS_MAX);
	bVectors.resize(CONSTRAINTS_MAX);
	lambda.setSize(CONSTRAINTS_MAX);
	lambdaInit.setSize(CONSTRAINTS_MAX);
	errorValues.setSize(CONSTRAINTS_MAX);
	b.setSize(CONSTRAINTS_MAX);
	lowerBounds.setSize(CONSTRAINTS_MAX);
	upperBounds.setSize(CONSTRAINTS_MAX);
	lambda.setSize(CONSTRAINTS_MAX);
	lambdaInit.setSize(CONSTRAINTS_MAX);
	errorValues.setSize(CONSTRAINTS_MAX);
	b.setSize(CONSTRAINTS_MAX);
	lowerBounds.setSize(CONSTRAINTS_MAX);
	upperBounds.setSize(CONSTRAINTS_MAX);
	d.resize(CONSTRAINTS_MAX);
	constraintsEntities.resize(BODIES_MAX);
	invInertiaMatrices.resize(BODIES_MAX);
	velocityVectors.resize(BODIES_MAX);
	constrainedVelocityVectors.resize(BODIES_MAX);
	forcesVectors.resize(BODIES_MAX);
	a.resize(BODIES_MAX);
	this->rigidBodies = rigidBodies;
}

constexpr int32_t ConstraintsSolver::BODIES_MAX;

constexpr int32_t ConstraintsSolver::CONSTRAINTS_MAX;

void ConstraintsSolver::reset()
{
	constraintsEntityCount = 0;
	constraintsCount = 0;
	constrainedBodies.clear();
}

ConstraintsEntity* ConstraintsSolver::allocateConstraintsEntity()
{
	return &constraintsEntities[constraintsEntityCount++];
}

void ConstraintsSolver::initialize(float dt)
{
	constraintsCount = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto& constraintedBody = constraintsEntities[i];
		constrainedBodies[constraintedBody.rb1->id] = constraintedBody.rb1;
		constrainedBodies[constraintedBody.rb2->id] = constraintedBody.rb2;
		constraintsCount += constraintedBody.collision.getHitPointsCount() * 3;
	}
	auto currentConstraint = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto& constraintedBody = constraintsEntities[i];
		auto hitPointsCount = constraintedBody.collision.getHitPointsCount();
		for (auto j = 0; j < hitPointsCount * 3; j++) {
			constraintsBodyIdxMap[currentConstraint + j][0] = constraintedBody.rb1->idx;
			constraintsBodyIdxMap[currentConstraint + j][1] = constraintedBody.rb2->idx;
		}
		constraintedBody.computeJacobian(currentConstraint, &jacobianMatrices);
		constraintedBody.computeLowerBound(currentConstraint, &lowerBounds);
		constraintedBody.computeUpperBound(currentConstraint, &upperBounds);
		constraintedBody.computeBaumgarte(currentConstraint, &errorValues);
		auto contactCacheInfo = contactCache.get(constraintedBody.rb1, constraintedBody.rb2, &constraintedBody.collision);
		if (contactCacheInfo != nullptr) {
			for (auto j = 0; j < hitPointsCount * 3; j++) {
				lambdaInit.setValue(currentConstraint + j, contactCacheInfo->lamdas[j]);
			}
		} else {
			for (auto j = 0; j < hitPointsCount * 3; j++) {
				lambdaInit.setValue(currentConstraint + j, 0.0f);
			}
		}
		currentConstraint += hitPointsCount * 3;
	}
}

void ConstraintsSolver::fillMatrices()
{
	for (auto it: constrainedBodies) {
		RigidBody* rb = it.second;
		auto bodyIdx = rb->idx;
		auto& velocityVector = velocityVectors[bodyIdx];
		velocityVector.setValue(0, rb->linearVelocity);
		velocityVector.setValue(3, rb->angularVelocity);
		auto& constainedVelocityVector = constrainedVelocityVectors[bodyIdx];
		constainedVelocityVector.fill(0.0f);
		auto& forcesVector = forcesVectors[bodyIdx];
		forcesVector.setValue(0, rb->force);
		forcesVector.setValue(3, rb->torque);
		auto& invInertiaMatrix = invInertiaMatrices[bodyIdx];
		invInertiaMatrix.fill(0.0f);
		auto worldInverseInertiaArray = rb->worldInverseInertia.getArray();
		if (rb->isStatic_ == false) {
			invInertiaMatrix.setValue(0, 0, rb->inverseMass);
			invInertiaMatrix.setValue(1, 1, rb->inverseMass);
			invInertiaMatrix.setValue(2, 2, rb->inverseMass);
			invInertiaMatrix.setValue(3, 3, worldInverseInertiaArray[0 + 0]);
			invInertiaMatrix.setValue(3, 4, worldInverseInertiaArray[0 + 1]);
			invInertiaMatrix.setValue(3, 5, worldInverseInertiaArray[0 + 2]);
			invInertiaMatrix.setValue(4, 3, worldInverseInertiaArray[4 + 0]);
			invInertiaMatrix.setValue(4, 4, worldInverseInertiaArray[4 + 1]);
			invInertiaMatrix.setValue(4, 5, worldInverseInertiaArray[4 + 2]);
			invInertiaMatrix.setValue(5, 3, worldInverseInertiaArray[8 + 0]);
			invInertiaMatrix.setValue(5, 4, worldInverseInertiaArray[8 + 1]);
			invInertiaMatrix.setValue(5, 5, worldInverseInertiaArray[8 + 2]);
		}
	}
}

void ConstraintsSolver::computeVectorB(float dt)
{
	Matrix1x6 tmpMatrix1x6;
	auto oneOverDT = 1.0f / dt;
	errorValues.scale(oneOverDT, b);
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = constraintsBodyIdxMap[i][0];
		auto body2Idx = constraintsBodyIdxMap[i][1];
		auto t1 = jacobianMatrices[i][0].multiply(velocityVectors[body1Idx]) + jacobianMatrices[i][1].multiply(velocityVectors[body2Idx]) * oneOverDT;
		auto t2 = jacobianMatrices[i][0].multiply(invInertiaMatrices[body1Idx], tmpMatrix1x6).multiply(forcesVectors[body1Idx]) + jacobianMatrices[i][1].multiply(invInertiaMatrices[body2Idx], tmpMatrix1x6).multiply(forcesVectors[body2Idx]);
		auto result = b.getValue(i) + t1 + t2;
		b.setValue(i, result);
	}
}

void ConstraintsSolver::computeMatrixB()
{
	Vector6 tmpVector6;
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = constraintsBodyIdxMap[i][0];
		auto body2Idx = constraintsBodyIdxMap[i][1];
		invInertiaMatrices[body1Idx].multiply(jacobianMatrices[i][0].getTranspose(tmpVector6), bVectors[i][0]);
		invInertiaMatrices[body2Idx].multiply(jacobianMatrices[i][1].getTranspose(tmpVector6), bVectors[i][1]);
	}
}

void ConstraintsSolver::computeVectorA()
{
	Vector6 tmpVector6;
	for (auto it: constrainedBodies) {
		RigidBody* rb = it.second;
		a[rb->idx].fill(0.0f);
	}
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = constraintsBodyIdxMap[i][0];
		auto body2Idx = constraintsBodyIdxMap[i][1];
		a[body1Idx].add(tmpVector6.set(bVectors[i][0]).scale(lambda.getValue(i)));
		a[body2Idx].add(tmpVector6.set(bVectors[i][1]).scale(lambda.getValue(i)));
	}
}

void ConstraintsSolver::PGLCP()
{
	Vector6 tmpVector6;
	for (auto i = 0; i < constraintsCount; i++) {
		lambda.setValue(i, lambdaInit.getValue(i));
	}
	computeVectorA();
	for (auto i = 0; i < constraintsCount; i++) {
		d[i] = jacobianMatrices[i][0].multiply(bVectors[i][0]) + jacobianMatrices[i][1].multiply(bVectors[i][1]);
	}
	for (auto iteration = 0; iteration < 20; iteration++) {
		for (auto i = 0; i < constraintsCount; i++) {
			auto body1Idx = constraintsBodyIdxMap[i][0];
			auto body2Idx = constraintsBodyIdxMap[i][1];
			auto xDelta = (b.getValue(i) - jacobianMatrices[i][0].multiply(a[body1Idx]) - jacobianMatrices[i][1].multiply(a[body2Idx])) / d[i];
			auto xTemp = lambda.getValue(i);
			auto min = Math::min(xTemp + xDelta, upperBounds.getValue(i));
			auto max = Math::max(lowerBounds.getValue(i), min);
			lambda.setValue(i, max);
			xDelta = lambda.getValue(i) - xTemp;
			a[body1Idx].add(tmpVector6.set(bVectors[i][0]).scale(xDelta));
			a[body2Idx].add(tmpVector6.set(bVectors[i][1]).scale(xDelta));
		}
	}
}

void ConstraintsSolver::computeVectorVelocityConstraints(float dt)
{
	Vector6 tmpVector6;
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = constraintsBodyIdxMap[i][0];
		auto body2Idx = constraintsBodyIdxMap[i][1];
		constrainedVelocityVectors[body1Idx].sub(tmpVector6.set(bVectors[i][0]).scale(lambda.getValue(i) * dt));
		constrainedVelocityVectors[body2Idx].sub(tmpVector6.set(bVectors[i][1]).scale(lambda.getValue(i) * dt));
	}
}

void ConstraintsSolver::updateContactCache()
{
	contactCache.clear();
	auto constraintsIdx = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto& constraintsEntity = constraintsEntities[i];
		auto hitPoints = constraintsEntity.collision.getHitPointsCount();
		vector<float> tmpLamdaValues;
		for (auto j = 0; j < hitPoints * 3; j++) {
			tmpLamdaValues.push_back(lambda.getValue(constraintsIdx + j));
		}
		contactCache.add(constraintsEntity.rb1, constraintsEntity.rb2, &constraintsEntity.collision, &tmpLamdaValues);
		constraintsIdx += hitPoints * 3;
	}
}

void ConstraintsSolver::checkChainSuccessor(RigidBody* rigidBodySrc, Vector3* normalLast, vector<RigidBody*>& rigidBodiesCurrentChain)
{
	rigidBodiesCurrentChain.push_back(rigidBodySrc);
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto& constraintEntity = constraintsEntities[i];
		RigidBody* rigidBodyCheck = nullptr;
		if (constraintEntity.rb1 == rigidBodySrc) {
			rigidBodyCheck = constraintEntity.rb2;
		} else if (constraintEntity.rb2 == rigidBodySrc) {
			rigidBodyCheck = constraintEntity.rb1;
		} else {
			continue;
		}
		if (rigidBodyCheck->isStatic_ == true) {
			continue;
		}
		if (rigidBodyCheck->enabled == false)
			continue;

		auto haveRigidBodyCheck = false;
		for (auto j = 0; j < rigidBodiesCurrentChain.size(); j++) {
			if (rigidBodiesCurrentChain.at(j) == rigidBodyCheck) {
				haveRigidBodyCheck = true;
				break;
			}
		}
		if (haveRigidBodyCheck == true) {
			continue;
		}
		auto normalCurrent = constraintEntity.collision.getNormal();
		if (normalLast != nullptr) {
			if (Math::abs(Vector3::computeDotProduct(*normalLast, *normalCurrent)) < 0.75f) {
				continue;
			}
		}
		checkChainSuccessor(rigidBodyCheck, normalCurrent, rigidBodiesCurrentChain);
	}
}

int32_t ConstraintsSolver::processRigidBodyChain(int32_t idx, const vector<RigidBody*>& rigidBodiesCurrentChain)
{
	auto rigidBodyAIdx = -1;
	for (auto j = idx; j < rigidBodiesCurrentChain.size(); j++) {
		auto rigidBody = rigidBodiesCurrentChain.at(j);
		auto isVelocityChangeRigidBody = false;
		for (auto k = 0; k < rigidBodiesVelocityChange.size(); k++) {
			auto rigidBodyVC = rigidBodiesVelocityChange.at(k);
			if (rigidBodyVC == rigidBody) {
				isVelocityChangeRigidBody = true;
				break;
			}
		}
		if (isVelocityChangeRigidBody == true) {
			rigidBodyAIdx = j;
			break;
		} else {
			continue;
		}
	}
	if (rigidBodyAIdx == -1)
		return -1;

	auto rigidBodyA = rigidBodiesCurrentChain.at(rigidBodyAIdx);
	auto rigidBodyASpeed = rigidBodyA->linearVelocity.computeLength();
	auto rigidBodyBIdx = -1;
	auto rigidBodyBSpeed = 0.0f;
	for (auto j = idx + 1; j < rigidBodiesCurrentChain.size(); j++) {
		auto rigidBody = rigidBodiesCurrentChain.at(j);
		auto isVelocityChangeRigidBody = false;
		for (auto k = 0; k < rigidBodiesVelocityChange.size(); k++) {
			auto rigidBodyVC = rigidBodiesVelocityChange.at(k);
			if (rigidBodyVC == rigidBody) {
				isVelocityChangeRigidBody = true;
				break;
			}
		}
		if (isVelocityChangeRigidBody == false)
			continue;

		auto ab = Vector3::computeDotProduct(rigidBodiesCurrentChain.at(rigidBodyAIdx)->linearVelocity, rigidBodiesCurrentChain.at(j)->linearVelocity);
		if (ab > 0.0f)
			continue;

		auto _speed = rigidBody->linearVelocity.computeLength();
		if (_speed > rigidBodyBSpeed) {
			rigidBodyBIdx = j;
			rigidBodyBSpeed = _speed;
		}
	}
	if (rigidBodyBIdx == -1) {
		return -1;
	}
	if (rigidBodyA->linearVelocity.computeLength() > MathTools::EPSILON) {
		auto y = rigidBodyA->linearVelocity.getY();
		rigidBodyA->linearVelocity.normalize();
		rigidBodyA->linearVelocity.scale(rigidBodyASpeed - rigidBodyBSpeed > 0.0f ? rigidBodyASpeed - rigidBodyBSpeed : 0.0f);
		rigidBodyA->linearVelocity.setY(y);
	}
	auto rigidBodyB = rigidBodiesCurrentChain.at(rigidBodyBIdx);
	if (rigidBodyB->linearVelocity.computeLength() > MathTools::EPSILON) {
		auto y = rigidBodyB->linearVelocity.getY();
		rigidBodyB->linearVelocity.normalize();
		rigidBodyB->linearVelocity.scale(rigidBodyBSpeed - rigidBodyASpeed > 0.0f ? rigidBodyBSpeed - rigidBodyASpeed : 0.0f);
		rigidBodyB->linearVelocity.setY(y);
	}
	for (auto rigidBodyIdx = rigidBodyAIdx + 1; rigidBodyIdx < rigidBodyBIdx; rigidBodyIdx++) {
		auto rigidBody = rigidBodiesCurrentChain.at(rigidBodyIdx);
		auto y = rigidBody->linearVelocity.getY();
		rigidBody->linearVelocity.scale(0.0f);
		rigidBody->linearVelocity.setY(y);
	}
	return rigidBodyBIdx + 1;
}

void ConstraintsSolver::checkVelocityConstraint()
{
	for (auto i = 0; i < rigidBodies->size(); i++) {
		auto rigidBodyVelocityChange = rigidBodies->at(i);
		if (rigidBodyVelocityChange->enabled == false)
			continue;

		if (rigidBodyVelocityChange->checkVelocityChange() == true) {
			rigidBodiesVelocityChange.push_back(rigidBodyVelocityChange);
		}
	}
	for (auto i = 0; i < rigidBodiesVelocityChange.size(); i++) {
		auto rigidBodySrc = rigidBodiesVelocityChange.at(i);
		auto rigidBodyProcessed = false;
		for (auto j = 0; j < rigidBodiesChainsResult.size(); j++) {
			if (rigidBodiesChainsResult.at(j) == rigidBodySrc) {
				rigidBodyProcessed = true;
				break;
			}
		}
		if (rigidBodyProcessed == true)
			continue;

		checkChainSuccessor(rigidBodySrc, nullptr, rigidBodiesCurrentChain);
		for (auto j = 0; j < rigidBodiesCurrentChain.size(); j++) {
			auto rigidBody = rigidBodiesCurrentChain.at(j);
			rigidBodiesChainsResult.push_back(rigidBody);
		}
		if (rigidBodiesCurrentChain.size() < 2) {
			rigidBodiesCurrentChain.clear();
			continue;
		}
		auto idx = 0;
		while (true == true) {
			idx = processRigidBodyChain(idx, rigidBodiesCurrentChain);
			if (idx == -1 || idx >= rigidBodiesCurrentChain.size())
				break;

		}
		rigidBodiesCurrentChain.clear();
	}
	rigidBodiesChainsResult.clear();
	rigidBodiesVelocityChange.clear();
}

void ConstraintsSolver::compute(float dt)
{
	if (constraintsEntityCount == 0)
		return;

	checkVelocityConstraint();
	initialize(dt);
	fillMatrices();
	computeVectorB(dt);
	computeMatrixB();
	PGLCP();
	computeVectorVelocityConstraints(dt);
	updateContactCache();
}

void ConstraintsSolver::getConstrainedVelocity(RigidBody* body, Vector3& linearVelocity, Vector3& angularVelocity)
{
	auto vector6Array = constrainedVelocityVectors[body->idx].data;
	linearVelocity.set(vector6Array[0], vector6Array[1], vector6Array[2]);
	angularVelocity.set(vector6Array[3], vector6Array[4], vector6Array[5]);
}

void ConstraintsSolver::updateAllBodies(float deltaTime)
{
	Vector3 newLinearVelocity;
	Vector3 newAngularVelocity;
	Vector3 force;
	Vector3 torque;
	for (auto i = 0; i < rigidBodies->size(); i++) {
		auto body = rigidBodies->at(i);
		if (body->isStatic_ == true || body->isSleeping_ == true || body->enabled == false) {
			continue;
		}
		newLinearVelocity.set(0.0f, 0.0f, 0.0f);
		newAngularVelocity.set(0.0f, 0.0f, 0.0f);

		if (constrainedBodies.find(body->id) != constrainedBodies.end()) {
			getConstrainedVelocity(body, newLinearVelocity, newAngularVelocity);
		}
		force.set(body->force).scale(body->inverseMass * deltaTime);
		body->worldInverseInertia.multiply(body->torque, torque).scale(deltaTime);
		newLinearVelocity.add(force);
		newAngularVelocity.add(torque);
		newLinearVelocity.add(body->linearVelocity);
		newAngularVelocity.add(body->angularVelocity);
		body->linearVelocity.set(newLinearVelocity);
		body->angularVelocity.set(newAngularVelocity);
		body->update(deltaTime);
	}
}
