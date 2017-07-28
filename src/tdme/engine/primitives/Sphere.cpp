// Generated from /tdme/src/tdme/engine/primitives/Sphere.java
#include <tdme/engine/primitives/Sphere.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>

using tdme::engine::primitives::Sphere;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
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

Sphere::Sphere(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Sphere::Sphere() 
	: Sphere(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

Sphere::Sphere(Vector3* center, float radius) 
	: Sphere(*static_cast< ::default_init_tag* >(0))
{
	ctor(center,radius);
}

BoundingVolume* Sphere::createBoundingVolume(Vector3* center, float radius)
{
	clinit();
	return new Sphere(center, radius);
}

void Sphere::ctor()
{
	super::ctor();
	this->center = new Vector3();
	this->radius = 0.0f;
	this->axis = new Vector3();
}

void Sphere::ctor(Vector3* center, float radius)
{
	super::ctor();
	this->center = center;
	this->radius = radius;
	this->axis = new Vector3();
}

void Sphere::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Sphere::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto sphere = java_cast< Sphere* >(original);
	center->set(sphere->center);
	radius = sphere->radius;
}

void Sphere::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Sphere::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto sphere = java_cast< Sphere* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(sphere->center, center);
	axis->set(sphere->center)->addX(sphere->radius);
	transformationsMatrix->multiply(axis, axis);
	radius = axis->sub(center)->computeLength();
}

Vector3* Sphere::getCenter()
{
	return center;
}

float Sphere::getRadius()
{
	return radius;
}

float Sphere::getSphereRadius()
{
	return radius;
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

Sphere* Sphere::set(Vector3* center, float radius)
{
	this->center->set(center);
	this->radius = radius;
	this->update();
	return this;
}

void Sphere::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	axis->set(point)->sub(center);
	auto length = point->computeLength();
	if (length <= radius) {
		closestPoint->set(point);
	} else {
		closestPoint->set(axis)->normalize()->scale(radius);
		closestPoint->add(center);
	}
	return;
}

bool Sphere::containsPoint(Vector3* point)
{
	auto distance = point->clone()->sub(center)->computeLength();
	return distance <= radius;
}

bool Sphere::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
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
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Sphere::doesCollideWith(): unsupported bounding volume 2: "_j)->append(static_cast< Object* >(bv2))->toString()));
		return false;
	}
}

float Sphere::computeDimensionOnAxis(Vector3* axis)
{
	return radius * 2.0f;
}

void Sphere::update()
{
}

BoundingVolume* Sphere::clone()
{
	return new Sphere(center->clone(), radius);
}

String* Sphere::toString()
{
	return ::java::lang::StringBuilder().append(u"Sphere [center="_j)
		/*
		->append(static_cast< Object* >(center))
		*/
		->append(u", radius="_j)
		->append(radius)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Sphere::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.Sphere", 29);
    return c;
}

java::lang::Class* Sphere::getClass0()
{
	return class_();
}

