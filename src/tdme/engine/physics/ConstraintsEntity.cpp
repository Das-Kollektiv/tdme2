// Generated from /tdme/src/tdme/engine/physics/ConstraintsEntity.java
#include <tdme/engine/physics/ConstraintsEntity.h>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/physics/DynamicVector.h>
#include <tdme/engine/physics/Matrix1x6.h>
#include <tdme/engine/physics/RigidBody.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::physics::ConstraintsEntity;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::physics::DynamicVector;
using tdme::engine::physics::Matrix1x6;
using tdme::engine::physics::RigidBody;
using tdme::math::MathTools;
using tdme::math::Vector3;

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
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6, ::java::lang::ObjectArray > Matrix1x6Array;
}  // namespace physics
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math

namespace engine {
namespace physics {
typedef ::SubArray< ::tdme::engine::physics::Matrix1x6Array, ::java::lang::CloneableArray, ::java::io::SerializableArray > Matrix1x6ArrayArray;
}  // namespace physics
}  // namespace engine
}  // namespace tdme

ConstraintsEntity::ConstraintsEntity(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ConstraintsEntity::ConstraintsEntity() 
	: ConstraintsEntity(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void ConstraintsEntity::init()
{
	tmpVector3 = new Vector3();
	r1 = new Vector3();
	r2 = new Vector3();
	r1CrossN = new Vector3();
	r2CrossN = new Vector3();
	r1CrossU1 = new Vector3();
	r2CrossU1 = new Vector3();
	r1CrossU2 = new Vector3();
	r2CrossU2 = new Vector3();
}

constexpr float ConstraintsEntity::HITPOINT_TOLERANCE;

void ConstraintsEntity::computeCrossProduct(Vector3* a, Vector3* b, Vector3* dest)
{
	clinit();
	auto aXYZ = a->getArray();
	auto bXYZ = b->getArray();
	dest->set((*aXYZ)[1] * (*bXYZ)[2] - (*aXYZ)[2] * (*bXYZ)[1], (*aXYZ)[2] * (*bXYZ)[0] - (*aXYZ)[0] * (*bXYZ)[2], (*aXYZ)[0] * (*bXYZ)[1] - (*aXYZ)[1] * (*bXYZ)[0]);
}

void ConstraintsEntity::ctor()
{
	super::ctor();
	init();
	this->frictionVectors = new Vector3Array(2);
	this->frictionVectors->set(0, new Vector3());
	this->frictionVectors->set(1, new Vector3());
}

void ConstraintsEntity::set(RigidBody* rb1, RigidBody* rb2, CollisionResponse* collision)
{
	this->rb1 = rb1;
	this->rb2 = rb2;
	this->collision = collision;
	muMg = ((rb1->friction + rb2->friction) / 2.0f) * ((rb1->mass + rb2->mass) / 2.0f) * MathTools::g;
	collision->getNormal()->scale(-1.0f);
	collision->getNormal()->computeOrthogonalVector((*this->frictionVectors)[0]);
	computeCrossProduct(collision->getNormal(), (*this->frictionVectors)[0], (*this->frictionVectors)[1]);
}

void ConstraintsEntity::computeJacobian(int32_t constraintIdx, Matrix1x6ArrayArray* jacobianMatrices)
{
	auto body1Position = rb1->getPosition();
	auto body2Position = rb2->getPosition();
	auto n = collision->getNormal();
	auto t1 = (*frictionVectors)[0];
	auto t2 = (*frictionVectors)[1];
	Matrix1x6* jacobianMatrix;
	auto currentConstraintIdx = constraintIdx;
	for (auto hitPointIdx = 0; hitPointIdx < collision->getHitPointsCount(); hitPointIdx++) {
		auto point = collision->getHitPointAt(hitPointIdx);
		r1->set(point)->sub(body1Position);
		r2->set(point)->sub(body2Position);
		computeCrossProduct(r1, n, r1CrossN);
		computeCrossProduct(r2, n, r2CrossN);
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[0];
		jacobianMatrix->setValue(0, tmpVector3->set(n)->scale(-1.0f));
		jacobianMatrix->setValue(3, tmpVector3->set(r1CrossN)->scale(-1.0f));
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[1];
		jacobianMatrix->setValue(0, n);
		jacobianMatrix->setValue(3, r2CrossN);
		currentConstraintIdx++;
		computeCrossProduct(r1, t1, r1CrossU1);
		computeCrossProduct(r2, t1, r2CrossU1);
		computeCrossProduct(r1, t2, r1CrossU2);
		computeCrossProduct(r2, t2, r2CrossU2);
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[0];
		jacobianMatrix->setValue(0, tmpVector3->set(t1)->scale(-1.0f));
		jacobianMatrix->setValue(3, tmpVector3->set(r1CrossU1)->scale(-1.0f));
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[1];
		jacobianMatrix->setValue(0, t1);
		jacobianMatrix->setValue(3, r2CrossU1);
		currentConstraintIdx++;
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[0];
		jacobianMatrix->setValue(0, tmpVector3->set(t2)->scale(-1.0f));
		jacobianMatrix->setValue(3, tmpVector3->set(r1CrossU2)->scale(-1.0f));
		jacobianMatrix = (*(*jacobianMatrices)[currentConstraintIdx])[1];
		jacobianMatrix->setValue(0, t2);
		jacobianMatrix->setValue(3, r2CrossU2);
		currentConstraintIdx++;
	}
}

void ConstraintsEntity::computeLowerBound(int32_t constraintIdx, DynamicVector* lowerBounds)
{
	auto currentConstraintIdx = constraintIdx;
	for (auto hitPointIdx = 0; hitPointIdx < collision->getHitPointsCount(); hitPointIdx++) {
		lowerBounds->setValue(currentConstraintIdx++, 0.0f);
		lowerBounds->setValue(currentConstraintIdx++, -muMg);
		lowerBounds->setValue(currentConstraintIdx++, -muMg);
	}
}

void ConstraintsEntity::computeUpperBound(int32_t constraintIdx, DynamicVector* upperBounds)
{
	auto currentConstraintIdx = constraintIdx;
	for (auto hitPointIdx = 0; hitPointIdx < collision->getHitPointsCount(); hitPointIdx++) {
		upperBounds->setValue(currentConstraintIdx++, Float::POSITIVE_INFINITY);
		upperBounds->setValue(currentConstraintIdx++, +muMg);
		upperBounds->setValue(currentConstraintIdx++, +muMg);
	}
}

void ConstraintsEntity::computeBaumgarte(int32_t constraintIdx, DynamicVector* errorValues)
{
	auto currentConstraintIdx = constraintIdx;
	auto restitutionCoeff = rb1->restitution + rb2->restitution;
	auto penetration = collision->getPenetration();
	auto errorValue = Math::abs(restitutionCoeff * (Vector3::computeDotProduct(collision->getNormal(), rb1->angularVelocity) - Vector3::computeDotProduct(collision->getNormal(), rb2->angularVelocity))) + (0.4f * penetration);
	for (auto hitPointIdx = 0; hitPointIdx < collision->getHitPointsCount(); hitPointIdx++) {
		errorValues->setValue(currentConstraintIdx++, errorValue);
		errorValues->setValue(currentConstraintIdx++, 0.0f);
		errorValues->setValue(currentConstraintIdx++, 0.0f);
	}
}

String* ConstraintsEntity::toString()
{
	return ::java::lang::StringBuilder().append(u"Constraints [rb1="_j)->append(static_cast< Object* >(rb1))
		->append(u", rb2="_j)
		->append(static_cast< Object* >(rb2))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ConstraintsEntity::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.ConstraintsEntity", 37);
    return c;
}

java::lang::Class* ConstraintsEntity::getClass0()
{
	return class_();
}

