// Generated from /tdme/src/tdme/engine/physics/ConstraintsSolver.java
#include <tdme/engine/physics/ConstraintsSolver.h>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/util/Iterator.h>
#include <tdme/engine/physics/CollisionResponse.h>
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
#include <tdme/utils/Key.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap_ValuesIterator.h>
#include <tdme/utils/_HashMap.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::physics::ConstraintsSolver;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::util::Iterator;
using tdme::engine::physics::CollisionResponse;
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
using tdme::utils::Key;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap_ValuesIterator;
using tdme::utils::_HashMap;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::CollisionResponse, ::java::lang::ObjectArray > CollisionResponseArray;
typedef ::SubArray< ::tdme::engine::physics::ConstraintsEntity, ::java::lang::ObjectArray > ConstraintsEntityArray;
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6, ::java::lang::ObjectArray > Matrix1x6Array;
typedef ::SubArray< ::tdme::engine::physics::Matrix6x6, ::java::lang::ObjectArray > Matrix6x6Array;
typedef ::SubArray< ::tdme::engine::physics::Vector6, ::java::lang::ObjectArray > Vector6Array;
}  // namespace physics
}  // namespace engine

namespace utils {
typedef ::SubArray< ::tdme::utils::Key, ::java::lang::ObjectArray > KeyArray;
}  // namespace utils
}  // namespace tdme

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

namespace tdme {
namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix1x6ArrayArray;
typedef ::SubArray< ::tdme::engine::physics::Vector6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Vector6ArrayArray;
}  // namespace physics
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ConstraintsSolver::ConstraintsSolver(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ConstraintsSolver::ConstraintsSolver(_ArrayList* rigidBodies) 
	: ConstraintsSolver(*static_cast< ::default_init_tag* >(0))
{
	ctor(rigidBodies);
}

void ConstraintsSolver::init()
{
	constraintsEntityCount = 0;
	collisionsCount = 0;
	constraintsCount = 0;
	keyCount = 0;
	rigidBodies = nullptr;
	constrainedBodies = new _HashMap();
	contactCache = new ContactCache();
	constraintsBodyIdxMap = new int32_tArrayArray(CONSTRAINTS_MAX);
	jacobianMatrices = new Matrix1x6ArrayArray(CONSTRAINTS_MAX);
	bVectors = new Vector6ArrayArray(CONSTRAINTS_MAX);
	lambda = new DynamicVector(CONSTRAINTS_MAX);
	lambdaInit = new DynamicVector(CONSTRAINTS_MAX);
	errorValues = new DynamicVector(CONSTRAINTS_MAX);
	b = new DynamicVector(CONSTRAINTS_MAX);
	lowerBounds = new DynamicVector(CONSTRAINTS_MAX);
	upperBounds = new DynamicVector(CONSTRAINTS_MAX);
	d = new floatArray(CONSTRAINTS_MAX);
	constraintsEntities = new ConstraintsEntityArray(BODIES_MAX);
	collisions = new CollisionResponseArray(BODIES_MAX);
	keys = new KeyArray(BODIES_MAX * 2);
	invInertiaMatrices = new Matrix6x6Array(BODIES_MAX);
	velocityVectors = new Vector6Array(BODIES_MAX);
	constrainedVelocityVectors = new Vector6Array(BODIES_MAX);
	forcesVectors = new Vector6Array(BODIES_MAX);
	a = new Vector6Array(BODIES_MAX);
	rigidBodiesVelocityChange = new _ArrayList();
	rigidBodiesCurrentChain = new _ArrayList();
	rigidBodiesChainsResult = new _ArrayList();
	tmpLamdaValues = new floatArray(CollisionResponse::HITPOINT_COUNT * 3);
	tmpMatrix1x6 = new Matrix1x6();
	tmpVector6 = new Vector6();
	newLinearVelocity = new Vector3();
	newAngularVelocity = new Vector3();
	force = new Vector3();
	torque = new Vector3();
}

constexpr int32_t ConstraintsSolver::BODIES_MAX;

constexpr int32_t ConstraintsSolver::CONSTRAINTS_MAX;

void ConstraintsSolver::ctor(_ArrayList* rigidBodies)
{
	super::ctor();
	init();
	this->rigidBodies = rigidBodies;
	for (auto i = 0; i < CONSTRAINTS_MAX; i++) {
		constraintsBodyIdxMap->set(i, new int32_tArray(2));
		jacobianMatrices->set(i, new Matrix1x6Array(2));
		(*jacobianMatrices)[i]->set(0, new Matrix1x6());
		(*jacobianMatrices)[i]->set(1, new Matrix1x6());
		bVectors->set(i, new Vector6Array(2));
		(*bVectors)[i]->set(0, new Vector6());
		(*bVectors)[i]->set(1, new Vector6());
	}
	for (auto i = 0; i < BODIES_MAX; i++) {
		invInertiaMatrices->set(i, new Matrix6x6());
		velocityVectors->set(i, new Vector6());
		constrainedVelocityVectors->set(i, new Vector6());
		forcesVectors->set(i, new Vector6());
		a->set(i, new Vector6());
		constraintsEntities->set(i, new ConstraintsEntity());
		collisions->set(i, new CollisionResponse());
	}
	for (auto i = 0; i < BODIES_MAX * 2; i++) {
		keys->set(i, new Key());
	}
	lambda->setSize(CONSTRAINTS_MAX);
	lambdaInit->setSize(CONSTRAINTS_MAX);
	errorValues->setSize(CONSTRAINTS_MAX);
	b->setSize(CONSTRAINTS_MAX);
	lowerBounds->setSize(CONSTRAINTS_MAX);
	upperBounds->setSize(CONSTRAINTS_MAX);
}

void ConstraintsSolver::reset()
{
	constraintsEntityCount = 0;
	collisionsCount = 0;
	constraintsCount = 0;
	keyCount = 0;
	constrainedBodies->clear();
}

ConstraintsEntity* ConstraintsSolver::allocateConstraintsEntity()
{
	return (*constraintsEntities)[constraintsEntityCount++];
}

CollisionResponse* ConstraintsSolver::allocateCollision()
{
	return (*collisions)[collisionsCount++];
}

Key* ConstraintsSolver::allocateKey()
{
	return (*keys)[keyCount++];
}

void ConstraintsSolver::releaseKey()
{
	keyCount--;
}

void ConstraintsSolver::initialize(float dt)
{
	constraintsCount = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto constraintedBody = (*constraintsEntities)[i];
		constrainedBodies->put(constraintedBody->rb1->id, constraintedBody->rb1);
		constrainedBodies->put(constraintedBody->rb2->id, constraintedBody->rb2);
		constraintsCount += constraintedBody->collision->getHitPointsCount() * 3;
	}
	auto currentConstraint = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto constraintedBody = (*constraintsEntities)[i];
		auto hitPointsCount = constraintedBody->collision->getHitPointsCount();
		for (auto j = 0; j < hitPointsCount * 3; j++) {
			(*(*constraintsBodyIdxMap)[currentConstraint + j])[0] = constraintedBody->rb1->idx;
			(*(*constraintsBodyIdxMap)[currentConstraint + j])[1] = constraintedBody->rb2->idx;
		}
		constraintedBody->computeJacobian(currentConstraint, jacobianMatrices);
		constraintedBody->computeLowerBound(currentConstraint, lowerBounds);
		constraintedBody->computeUpperBound(currentConstraint, upperBounds);
		constraintedBody->computeBaumgarte(currentConstraint, errorValues);
		auto contactCacheInfo = contactCache->get(constraintedBody->rb1, constraintedBody->rb2, constraintedBody->collision);
		if (contactCacheInfo != nullptr) {
			for (auto j = 0; j < hitPointsCount * 3; j++) {
				lambdaInit->setValue(currentConstraint + j, (*contactCacheInfo->lamdas)[j]);
			}
		} else {
			for (auto j = 0; j < hitPointsCount * 3; j++) {
				lambdaInit->setValue(currentConstraint + j, 0.0f);
			}
		}
		currentConstraint += hitPointsCount * 3;
	}
}

void ConstraintsSolver::fillMatrices()
{
	for (auto _i = constrainedBodies->getValuesIterator()->iterator(); _i->hasNext(); ) {
		RigidBody* rb = java_cast< RigidBody* >(_i->next());
		{
			auto bodyIdx = rb->idx;
			auto velocityVector = (*velocityVectors)[bodyIdx];
			velocityVector->setValue(0, rb->linearVelocity);
			velocityVector->setValue(3, rb->angularVelocity);
			auto constainedVelocityVector = (*constrainedVelocityVectors)[bodyIdx];
			constainedVelocityVector->fill(0.0f);
			auto forcesVector = (*forcesVectors)[bodyIdx];
			forcesVector->setValue(0, rb->force);
			forcesVector->setValue(3, rb->torque);
			auto invInertiaMatrix = (*invInertiaMatrices)[bodyIdx];
			invInertiaMatrix->fill(0.0f);
			auto worldInverseInertiaArray = rb->worldInverseInertia->getArray();
			if (rb->isStatic_ == false) {
				invInertiaMatrix->setValue(0, 0, rb->inverseMass);
				invInertiaMatrix->setValue(1, 1, rb->inverseMass);
				invInertiaMatrix->setValue(2, 2, rb->inverseMass);
				invInertiaMatrix->setValue(3, 3, (*worldInverseInertiaArray)[0 + 0]);
				invInertiaMatrix->setValue(3, 4, (*worldInverseInertiaArray)[0 + 1]);
				invInertiaMatrix->setValue(3, 5, (*worldInverseInertiaArray)[0 + 2]);
				invInertiaMatrix->setValue(4, 3, (*worldInverseInertiaArray)[4 + 0]);
				invInertiaMatrix->setValue(4, 4, (*worldInverseInertiaArray)[4 + 1]);
				invInertiaMatrix->setValue(4, 5, (*worldInverseInertiaArray)[4 + 2]);
				invInertiaMatrix->setValue(5, 3, (*worldInverseInertiaArray)[8 + 0]);
				invInertiaMatrix->setValue(5, 4, (*worldInverseInertiaArray)[8 + 1]);
				invInertiaMatrix->setValue(5, 5, (*worldInverseInertiaArray)[8 + 2]);
			}
		}
	}
}

void ConstraintsSolver::computeVectorB(float dt)
{
	auto oneOverDT = 1.0f / dt;
	errorValues->scale(oneOverDT, b);
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = (*(*constraintsBodyIdxMap)[i])[0];
		auto body2Idx = (*(*constraintsBodyIdxMap)[i])[1];
		auto t1 = (*(*jacobianMatrices)[i])[0]->multiply((*velocityVectors)[body1Idx]) + (*(*jacobianMatrices)[i])[1]->multiply((*velocityVectors)[body2Idx]) * oneOverDT;
		auto t2 = (*(*jacobianMatrices)[i])[0]->multiply((*invInertiaMatrices)[body1Idx], tmpMatrix1x6)->multiply((*forcesVectors)[body1Idx]) + (*(*jacobianMatrices)[i])[1]->multiply((*invInertiaMatrices)[body2Idx], tmpMatrix1x6)->multiply((*forcesVectors)[body2Idx]);
		auto result = b->getValue(i) + t1 + t2;
		b->setValue(i, result);
	}
}

void ConstraintsSolver::computeMatrixB()
{
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = (*(*constraintsBodyIdxMap)[i])[0];
		auto body2Idx = (*(*constraintsBodyIdxMap)[i])[1];
		(*invInertiaMatrices)[body1Idx]->multiply((*(*jacobianMatrices)[i])[0]->getTranspose(tmpVector6), (*(*bVectors)[i])[0]);
		(*invInertiaMatrices)[body2Idx]->multiply((*(*jacobianMatrices)[i])[1]->getTranspose(tmpVector6), (*(*bVectors)[i])[1]);
	}
}

void ConstraintsSolver::computeVectorA()
{
	for (auto _i = constrainedBodies->getValuesIterator()->iterator(); _i->hasNext(); ) {
		RigidBody* rb = java_cast< RigidBody* >(_i->next());
		{
			(*a)[rb->idx]->fill(0.0f);
		}
	}
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = (*(*constraintsBodyIdxMap)[i])[0];
		auto body2Idx = (*(*constraintsBodyIdxMap)[i])[1];
		(*a)[body1Idx]->add(tmpVector6->set((*(*bVectors)[i])[0])->scale(lambda->getValue(i)));
		(*a)[body2Idx]->add(tmpVector6->set((*(*bVectors)[i])[1])->scale(lambda->getValue(i)));
	}
}

void ConstraintsSolver::PGLCP()
{
	for (auto i = 0; i < constraintsCount; i++) {
		lambda->setValue(i, lambdaInit->getValue(i));
	}
	computeVectorA();
	for (auto i = 0; i < constraintsCount; i++) {
		(*d)[i] = (*(*jacobianMatrices)[i])[0]->multiply((*(*bVectors)[i])[0]) + (*(*jacobianMatrices)[i])[1]->multiply((*(*bVectors)[i])[1]);
	}
	for (auto iteration = 0; iteration < 20; iteration++) {
		for (auto i = 0; i < constraintsCount; i++) {
			auto body1Idx = (*(*constraintsBodyIdxMap)[i])[0];
			auto body2Idx = (*(*constraintsBodyIdxMap)[i])[1];
			auto xDelta = (b->getValue(i) - (*(*jacobianMatrices)[i])[0]->multiply((*a)[body1Idx]) - (*(*jacobianMatrices)[i])[1]->multiply((*a)[body2Idx])) / (*d)[i];
			auto xTemp = lambda->getValue(i);
			auto min = Math::min(xTemp + xDelta, upperBounds->getValue(i));
			auto max = Math::max(lowerBounds->getValue(i), min);
			lambda->setValue(i, max);
			xDelta = lambda->getValue(i) - xTemp;
			(*a)[body1Idx]->add(tmpVector6->set((*(*bVectors)[i])[0])->scale(xDelta));
			(*a)[body2Idx]->add(tmpVector6->set((*(*bVectors)[i])[1])->scale(xDelta));
		}
	}
}

void ConstraintsSolver::computeVectorVelocityConstraints(float dt)
{
	for (auto i = 0; i < constraintsCount; i++) {
		auto body1Idx = (*(*constraintsBodyIdxMap)[i])[0];
		auto body2Idx = (*(*constraintsBodyIdxMap)[i])[1];
		(*constrainedVelocityVectors)[body1Idx]->sub(tmpVector6->set((*(*bVectors)[i])[0])->scale(lambda->getValue(i) * dt));
		(*constrainedVelocityVectors)[body2Idx]->sub(tmpVector6->set((*(*bVectors)[i])[1])->scale(lambda->getValue(i) * dt));
	}
}

void ConstraintsSolver::updateContactCache()
{
	contactCache->clear();
	auto constraintsIdx = 0;
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto constraintsEntity = (*constraintsEntities)[i];
		auto hitPoints = constraintsEntity->collision->getHitPointsCount();
		for (auto j = 0; j < hitPoints * 3; j++) {
			(*tmpLamdaValues)[j] = lambda->getValue(constraintsIdx + j);
		}
		contactCache->add(constraintsEntity->rb1, constraintsEntity->rb2, constraintsEntity->collision, tmpLamdaValues);
		constraintsIdx += hitPoints * 3;
	}
}

void ConstraintsSolver::checkChainSuccessor(RigidBody* rigidBodySrc, Vector3* normalLast, _ArrayList* rigidBodiesCurrentChain)
{
	rigidBodiesCurrentChain->add(rigidBodySrc);
	for (auto i = 0; i < constraintsEntityCount; i++) {
		auto constraintEntity = (*constraintsEntities)[i];
		RigidBody* rigidBodyCheck = nullptr;
		if (constraintEntity->rb1 == rigidBodySrc) {
			rigidBodyCheck = constraintEntity->rb2;
		} else if (constraintEntity->rb2 == rigidBodySrc) {
			rigidBodyCheck = constraintEntity->rb1;
		} else {
			continue;
		}
		if (rigidBodyCheck->isStatic_ == true) {
			continue;
		}
		if (rigidBodyCheck->enabled == false)
			continue;

		auto haveRigidBodyCheck = false;
		for (auto j = 0; j < rigidBodiesCurrentChain->size(); j++) {
			if (java_cast< RigidBody* >(rigidBodiesCurrentChain->get(j)) == rigidBodyCheck) {
				haveRigidBodyCheck = true;
				break;
			}
		}
		if (haveRigidBodyCheck == true) {
			continue;
		}
		auto normalCurrent = constraintEntity->collision->getNormal();
		if (normalLast != nullptr) {
			if (Math::abs(Vector3::computeDotProduct(normalLast, normalCurrent)) < 0.75f) {
				continue;
			}
		}
		checkChainSuccessor(rigidBodyCheck, normalCurrent, rigidBodiesCurrentChain);
	}
}

int32_t ConstraintsSolver::processRigidBodyChain(int32_t idx, _ArrayList* rigidBodiesCurrentChain)
{
	auto rigidBodyAIdx = -1;
	for (auto j = idx; j < rigidBodiesCurrentChain->size(); j++) {
		auto rigidBody = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(j));
		auto isVelocityChangeRigidBody = false;
		for (auto k = 0; k < rigidBodiesVelocityChange->size(); k++) {
			auto rigidBodyVC = java_cast< RigidBody* >(rigidBodiesVelocityChange->get(k));
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

	auto rigidBodyA = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(rigidBodyAIdx));
	auto rigidBodyASpeed = rigidBodyA->linearVelocity->computeLength();
	auto rigidBodyBIdx = -1;
	auto rigidBodyBSpeed = 0.0f;
	for (auto j = idx + 1; j < rigidBodiesCurrentChain->size(); j++) {
		auto rigidBody = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(j));
		auto isVelocityChangeRigidBody = false;
		for (auto k = 0; k < rigidBodiesVelocityChange->size(); k++) {
			auto rigidBodyVC = java_cast< RigidBody* >(rigidBodiesVelocityChange->get(k));
			if (rigidBodyVC == rigidBody) {
				isVelocityChangeRigidBody = true;
				break;
			}
		}
		if (isVelocityChangeRigidBody == false)
			continue;

		auto ab = Vector3::computeDotProduct(java_cast< RigidBody* >(rigidBodiesCurrentChain->get(rigidBodyAIdx))->linearVelocity, java_cast< RigidBody* >(rigidBodiesCurrentChain->get(j))->linearVelocity);
		if (ab > 0.0f)
			continue;

		auto _speed = rigidBody->linearVelocity->computeLength();
		if (_speed > rigidBodyBSpeed) {
			rigidBodyBIdx = j;
			rigidBodyBSpeed = _speed;
		}
	}
	if (rigidBodyBIdx == -1) {
		return -1;
	}
	if (rigidBodyA->linearVelocity->computeLength() > MathTools::EPSILON) {
		auto y = rigidBodyA->linearVelocity->getY();
		rigidBodyA->linearVelocity->normalize();
		rigidBodyA->linearVelocity->scale(rigidBodyASpeed - rigidBodyBSpeed > 0.0f ? rigidBodyASpeed - rigidBodyBSpeed : 0.0f);
		rigidBodyA->linearVelocity->setY(y);
	}
	auto rigidBodyB = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(rigidBodyBIdx));
	if (rigidBodyB->linearVelocity->computeLength() > MathTools::EPSILON) {
		auto y = rigidBodyB->linearVelocity->getY();
		rigidBodyB->linearVelocity->normalize();
		rigidBodyB->linearVelocity->scale(rigidBodyBSpeed - rigidBodyASpeed > 0.0f ? rigidBodyBSpeed - rigidBodyASpeed : 0.0f);
		rigidBodyB->linearVelocity->setY(y);
	}
	for (auto rigidBodyIdx = rigidBodyAIdx + 1; rigidBodyIdx < rigidBodyBIdx; rigidBodyIdx++) {
		auto rigidBody = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(rigidBodyIdx));
		auto y = rigidBody->linearVelocity->getY();
		rigidBody->linearVelocity->scale(0.0f);
		rigidBody->linearVelocity->setY(y);
	}
	return rigidBodyBIdx + 1;
}

void ConstraintsSolver::checkVelocityConstraint()
{
	for (auto i = 0; i < rigidBodies->size(); i++) {
		auto rigidBodyVelocityChange = java_cast< RigidBody* >(rigidBodies->get(i));
		if (rigidBodyVelocityChange->enabled == false)
			continue;

		if (rigidBodyVelocityChange->checkVelocityChange() == true) {
			rigidBodiesVelocityChange->add(rigidBodyVelocityChange);
		}
	}
	for (auto i = 0; i < rigidBodiesVelocityChange->size(); i++) {
		auto rigidBodySrc = java_cast< RigidBody* >(rigidBodiesVelocityChange->get(i));
		auto rigidBodyProcessed = false;
		for (auto j = 0; j < rigidBodiesChainsResult->size(); j++) {
			if (java_cast< RigidBody* >(rigidBodiesChainsResult->get(j)) == rigidBodySrc) {
				rigidBodyProcessed = true;
				break;
			}
		}
		if (rigidBodyProcessed == true)
			continue;

		checkChainSuccessor(rigidBodySrc, nullptr, rigidBodiesCurrentChain);
		for (auto j = 0; j < rigidBodiesCurrentChain->size(); j++) {
			auto rigidBody = java_cast< RigidBody* >(rigidBodiesCurrentChain->get(j));
			rigidBodiesChainsResult->add(rigidBody);
		}
		if (rigidBodiesCurrentChain->size() < 2) {
			rigidBodiesCurrentChain->clear();
			continue;
		}
		auto idx = 0;
		while (true == true) {
			idx = processRigidBodyChain(idx, rigidBodiesCurrentChain);
			if (idx == -1 || idx >= rigidBodiesCurrentChain->size())
				break;

		}
		rigidBodiesCurrentChain->clear();
	}
	rigidBodiesChainsResult->clear();
	rigidBodiesVelocityChange->clear();
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

void ConstraintsSolver::getConstrainedVelocity(RigidBody* body, Vector3* linearVelocity, Vector3* angularVelocity)
{
	auto vector6 = (*constrainedVelocityVectors)[body->idx];
	auto vector6Array = vector6->data;
	linearVelocity->set((*vector6Array)[0], (*vector6Array)[1], (*vector6Array)[2]);
	angularVelocity->set((*vector6Array)[3], (*vector6Array)[4], (*vector6Array)[5]);
}

void ConstraintsSolver::updateAllBodies(float deltaTime)
{
	for (auto i = 0; i < rigidBodies->size(); i++) {
		auto body = java_cast< RigidBody* >(rigidBodies->get(i));
		if (body->isStatic_ == true || body->isSleeping_ == true || body->enabled == false) {
			continue;
		}
		newLinearVelocity->set(0.0f, 0.0f, 0.0f);
		newAngularVelocity->set(0.0f, 0.0f, 0.0f);
		if (java_cast< RigidBody* >(constrainedBodies->get(body->id)) != nullptr) {
			getConstrainedVelocity(body, newLinearVelocity, newAngularVelocity);
		}
		force->set(body->force)->scale(body->inverseMass * deltaTime);
		body->worldInverseInertia->multiply(body->torque, torque)->scale(deltaTime);
		newLinearVelocity->add(force);
		newAngularVelocity->add(torque);
		newLinearVelocity->add(body->linearVelocity);
		newAngularVelocity->add(body->angularVelocity);
		body->linearVelocity->set(newLinearVelocity);
		body->angularVelocity->set(newAngularVelocity);
		body->update(deltaTime);
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ConstraintsSolver::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.ConstraintsSolver", 37);
    return c;
}

java::lang::Class* ConstraintsSolver::getClass0()
{
	return class_();
}

