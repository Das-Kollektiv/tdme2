// Generated from /tdme/src/tdme/engine/primitives/Sphere.java
#include <tdme/engine/primitives/Sphere.h>

#include <java/lang/String.h>

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

using tdme::engine::primitives::Sphere;
using java::lang::String;
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

Sphere::Sphere() 
{
	this->center.set(0.0f, 0.0f, 0.0f);
	this->radius = 0.0f;
}

Sphere::Sphere(Vector3* center, float radius) 
{
	this->center.set(center);
	this->radius = radius;
}

void Sphere::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		return;
	}
	auto sphere = dynamic_cast< Sphere* >(original);
	center.set(&sphere->center);
	radius = sphere->radius;
}

void Sphere::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		return;
	}
	Vector3 axis;
	auto sphere = dynamic_cast< Sphere* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(&sphere->center, &center);
	axis.set(&sphere->center)->addX(sphere->radius);
	transformationsMatrix->multiply(&axis, &axis);
	radius = axis.sub(&center)->computeLength();
}

Vector3* Sphere::getCenter()
{
	return &center;
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
	this->center.set(center);
	this->radius = radius;
	this->update();
	return this;
}

void Sphere::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	Vector3 axis;
	axis.set(point)->sub(&center);
	auto length = point->computeLength();
	if (length <= radius) {
		closestPoint->set(point);
	} else {
		closestPoint->set(&axis)->normalize()->scale(radius);
		closestPoint->add(&center);
	}
	return;
}

bool Sphere::containsPoint(Vector3* point)
{
	Vector3 axis;
	auto distance = axis.set(point)->sub(&center)->computeLength();
	return distance <= radius;
}

bool Sphere::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
{
	if (dynamic_cast< BoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< BoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< OrientedBoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< OrientedBoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< Sphere* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Sphere* >(bv2), movement, collision);
	} else if (dynamic_cast< Capsule* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Capsule* >(bv2), movement, collision);
	} else if (dynamic_cast< Triangle* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Triangle* >(bv2), movement, collision);
	} else if (dynamic_cast< ConvexMesh* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< ConvexMesh* >(bv2), movement, collision);
	} else {
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
	return new Sphere(&center, radius);
}

