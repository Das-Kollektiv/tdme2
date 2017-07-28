// Generated from /tdme/src/tdme/engine/primitives/Capsule.java
#include <tdme/engine/primitives/Capsule.h>

#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::primitives::Capsule;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

Capsule::Capsule(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Capsule::Capsule(Vector3* a, Vector3* b, float radius) 
	: Capsule(*static_cast< ::default_init_tag* >(0))
{
	ctor(a,b,radius);
}

BoundingVolume* Capsule::createBoundingVolume(Vector3* a, Vector3* b, float radius)
{
	clinit();
	return new Capsule(a, b, radius);
}

void Capsule::ctor(Vector3* a, Vector3* b, float radius)
{
	super::ctor();
	this->a = a;
	this->b = b;
	this->radius = radius;
	this->side = new Vector3();
	this->baSub = new Vector3();
	this->paSub = new Vector3();
	this->center = new Vector3();
	this->cpCvsP = new Vector3();
	update();
}

float Capsule::getRadius()
{
	return radius;
}

void Capsule::setRadius(float radius)
{
	this->radius = radius;
}

Vector3* Capsule::getA()
{
	return a;
}

Vector3* Capsule::getB()
{
	return b;
}

void Capsule::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< Capsule* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Capsule::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto capsule = java_cast< Capsule* >(original);
	a->set(capsule->a);
	b->set(capsule->b);
	center->set(capsule->center);
	radius = capsule->radius;
}

void Capsule::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< Capsule* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Capsule::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto capsule = java_cast< Capsule* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(capsule->a, a);
	transformationsMatrix->multiply(capsule->b, b);
	side->set(capsule->a)->addX(capsule->radius);
	transformationsMatrix->multiply(side, side);
	radius = side->sub(a)->computeLength();
	update();
}

void Capsule::update()
{
	baSub->set(b)->sub(a);
	auto baSubLength = baSub->computeLength();
	center->set(a)->add(baSub->normalize()->scale(baSubLength * 0.5f));
	sphereRadius = baSubLength / 2.0f + radius;
}

Vector3* Capsule::getCenter()
{
	return center;
}

float Capsule::getSphereRadius()
{
	return sphereRadius;
}

void Capsule::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	baSub->set(b)->sub(a);
	auto baSubLength = baSub->computeLength();
	if (baSubLength > 0.0f) {
		baSub->normalize();
		auto t = 0.0f;
		t = Vector3::computeDotProduct(paSub->set(point)->sub(a), baSub) / baSubLength;
		if (t < 0.0f)
			t = 0.0f;

		if (t > 1.0f)
			t = 1.0f;

		closestPoint->set(a)->add(baSub->scale(t * baSubLength));
	} else {
		closestPoint->set(a);
	}
}

bool Capsule::containsPoint(Vector3* point)
{
	computeClosestPointOnBoundingVolume(point, cpCvsP);
	auto distance = cpCvsP->sub(point)->computeLength();
	return distance <= radius;
}

bool Capsule::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
{
	if (dynamic_cast< BoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< BoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< OrientedBoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< OrientedBoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< Sphere* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Sphere* >(bv2), movement, collision);
	} else if (dynamic_cast< Capsule* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Capsule* >(bv2), movement, collision);
	} else if (dynamic_cast< Triangle* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Triangle* >(bv2), movement, collision);
	} else if (dynamic_cast< ConvexMesh* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< ConvexMesh* >(bv2), movement, collision);
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Capsule::doesCollideWith(): unsupported bounding volume 2: "_j)->append(static_cast< Object* >(bv2))->toString()));
		return false;
	}
}

float Capsule::computeDimensionOnAxis(Vector3* axis)
{
	return Math::abs(Vector3::computeDotProduct(baSub->set(b)->sub(a), axis)) + (radius * 2.0f);
}

BoundingVolume* Capsule::clone()
{
	return new Capsule(a->clone(), b->clone(), radius);
}

String* Capsule::toString()
{
	return ::java::lang::StringBuilder().append(u"Capsule [a="_j)
		/*
		->append(static_cast< Object* >(a))
		->append(u", b="_j)
		->append(static_cast< Object* >(b))
		*/
		->append(u", radius="_j)
		->append(radius)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Capsule::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.Capsule", 30);
    return c;
}

java::lang::Class* Capsule::getClass0()
{
	return class_();
}

