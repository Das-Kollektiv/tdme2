#include <tdme/engine/primitives/Sphere.h>

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
	this->convexMeshCenter.set(center);
	this->convexMeshRadius = radius;
	createConvexMesh();
}

Sphere::Sphere(const Vector3& center, float radius)
{
	this->center.set(center);
	this->radius = radius;
	this->convexMeshCenter.set(center);
	this->convexMeshRadius = radius;
	createConvexMesh();
}

void Sphere::createConvexMesh() {
	int segmentsX = 5;
	int segmentsY = 5;
	vector<Triangle> triangles;
	vector<Vector3> vertices;
	vertices.resize((segmentsY + 1) * segmentsX);
	for (auto ySegment = 0; ySegment <= segmentsY; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = (
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX))))
			).scale(radius).add(center);
		vertices[ySegment * segmentsX + xSegment] = vertex;
	}
	int ti, vi0, vi1, vi2;
	for (auto y = 0; y <= segmentsY; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			triangles.push_back(Triangle(vertices[vi0], vertices[vi1], vertices[vi2]));
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			triangles.push_back(Triangle(vertices[vi0], vertices[vi1], vertices[vi2]));
		}
	}
	convexMesh = ConvexMesh(&triangles);
}

void Sphere::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		return;
	}
	auto sphere = dynamic_cast< Sphere* >(original);
	center.set(sphere->center);
	radius = sphere->radius;
	convexMesh = sphere->convexMesh;
	convexMeshCenter.set(sphere->center);
	convexMeshRadius = sphere->radius;
}

void Sphere::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< Sphere* >(original) != nullptr == false) {
		return;
	}
	Vector3 axis;
	auto sphere = dynamic_cast< Sphere* >(original);
	auto& transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix.multiply(sphere->center, center);
	axis.set(sphere->center).addX(sphere->radius);
	transformationsMatrix.multiply(axis, axis);
	radius = axis.sub(center).computeLength();
	convexMeshCenter.set(center);
	convexMeshRadius = radius;
	convexMesh.fromBoundingVolumeWithTransformations(&sphere->convexMesh, transformations);
}

float Sphere::getRadius() const
{
	return radius;
}

void Sphere::setRadius(float radius)
{
	this->radius = radius;
}

Sphere* Sphere::set(const Vector3& center, float radius)
{
	this->center.set(center);
	this->radius = radius;
	this->update();
	return this;
}

void Sphere::computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestPoint) const
{
	Vector3 axis;
	axis.set(point).sub(center);
	auto length = point.computeLength();
	if (length <= radius) {
		closestPoint.set(point);
	} else {
		closestPoint.set(axis).normalize().scale(radius);
		closestPoint.add(center);
	}
	return;
}

bool Sphere::containsPoint(const Vector3& point) const
{
	Vector3 axis;
	auto distance = axis.set(point).sub(center).computeLength();
	return distance <= radius;
}

bool Sphere::doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision)
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

float Sphere::computeDimensionOnAxis(const Vector3& axis) const
{
	return radius * 2.0f;
}

void Sphere::update()
{
	if (convexMeshCenter.equals(center) == false ||
		Math::abs(convexMeshRadius - radius) > MathTools::EPSILON) {
		convexMeshCenter.set(center);
		convexMeshRadius = radius;
		createConvexMesh();
	}
}

BoundingVolume* Sphere::clone() const
{
	return new Sphere(center, radius);
}

