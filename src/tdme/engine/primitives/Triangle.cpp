#include <tdme/engine/primitives/Triangle.h>

#include <vector>

#include <tdme/math/Math.h>

#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::math::Math;

using tdme::engine::primitives::Triangle;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::math::MathTools;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Triangle::Triangle()
{
	this->vertices.resize(3);
	update();
}

Triangle::Triangle(Vector3* vertex0, Vector3* vertex1, Vector3* vertex2) 
{
	this->vertices.resize(3);
	this->vertices[0].set(vertex0);
	this->vertices[1].set(vertex1);
	this->vertices[2].set(vertex2);
	update();
}


vector<Vector3>* Triangle::getVertices()
{
	return &vertices;
}

void Triangle::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< Triangle* >(original) != nullptr == false) {
		return;
	}
	auto triangle = dynamic_cast< Triangle* >(original);
	for (auto i = 0; i < vertices.size(); i++)
		vertices[i].set(&triangle->vertices[i]);

	center.set(&triangle->center);
	sphereRadius = triangle->sphereRadius;
}

void Triangle::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< Triangle* >(original) != nullptr == false) {
		return;
	}
	auto triangle = dynamic_cast< Triangle* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	for (auto i = 0; i < 3; i++) {
		transformationsMatrix->multiply(&triangle->vertices[i], &vertices[i]);
	}
	update();
}

void Triangle::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	Vector3 edge0;
	Vector3 edge1;
	Vector3 v0Point;
	edge0.set(&vertices[1])->sub(&vertices[0]);
	edge1.set(&vertices[2])->sub(&vertices[0]);
	v0Point.set(&vertices[0])->sub(point);
	auto a = Vector3::computeDotProduct(&edge0, &edge0);
	auto b = Vector3::computeDotProduct(&edge0, &edge1);
	auto c = Vector3::computeDotProduct(&edge1, &edge1);
	auto d = Vector3::computeDotProduct(&edge0, &v0Point);
	auto e = Vector3::computeDotProduct(&edge1, &v0Point);
	auto det = a * c - b * b;
	auto s = b * e - c * d;
	auto t = b * d - a * e;
	if (s + t < det) {
		if (s < 0.0f) {
			if (t < 0.0f) {
				if (d < 0.0f) {
					s = MathTools::clamp(-d / a, 0.0f, 1.0f);
					t = 0.0f;
				} else {
					s = 0.0f;
					t = MathTools::clamp(-e / c, 0.0f, 1.0f);
				}
			} else {
				s = 0.0f;
				t = MathTools::clamp(-e / c, 0.0f, 1.0f);
			}
		} else if (t < 0.0f) {
			s = MathTools::clamp(-d / a, 0.0f, 1.0f);
			t = 0.0f;
		} else {
			auto invDet = 1.0f / det;
			s *= invDet;
			t *= invDet;
		}
	} else {
		if (s < 0.0f) {
			auto tmp0 = b + d;
			auto tmp1 = c + e;
			if (tmp1 > tmp0) {
				auto numer = tmp1 - tmp0;
				auto denom = a - 2 * b + c;
				s = MathTools::clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			} else {
				t = MathTools::clamp(-e / c, 0.0f, 1.0f);
				s = 0.0f;
			}
		} else if (t < 0.0f) {
			if (a + d > b + e) {
				auto numer = c + e - b - d;
				auto denom = a - 2 * b + c;
				s = MathTools::clamp(numer / denom, 0.0f, 1.0f);
				t = 1 - s;
			} else {
				s = MathTools::clamp(-e / c, 0.0f, 1.0f);
				t = 0.0f;
			}
		} else {
			auto numer = c + e - b - d;
			auto denom = a - 2 * b + c;
			s = MathTools::clamp(numer / denom, 0.0f, 1.0f);
			t = 1.0f - s;
		}
	}
	closestPoint->set(&vertices[0])->add(edge0.scale(s))->add(edge1.scale(t));
}

bool Triangle::containsPoint(Vector3* point)
{
	Vector3 closestPoint;
	computeClosestPointOnBoundingVolume(point, &closestPoint);
	return closestPoint.equals(point);
}

bool Triangle::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
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

Vector3* Triangle::getCenter()
{
	return &center;
}

float Triangle::getSphereRadius()
{
	return sphereRadius;
}

float Triangle::computeDimensionOnAxis(Vector3* axis)
{
	auto vertexOnAxis = Vector3::computeDotProduct(&vertices[0], axis);
	auto min = vertexOnAxis;
	auto max = vertexOnAxis;
	for (auto i = 1; i < vertices.size(); i++) {
		vertexOnAxis = Vector3::computeDotProduct(&vertices[i], axis);
		if (vertexOnAxis < min) min = vertexOnAxis;
		if (vertexOnAxis > max) max = vertexOnAxis;
	}
	return Math::abs(max - min);
}

void Triangle::update()
{
	Vector3 distanceVector;
	this->center.set(&vertices[0])->add(&vertices[1])->add(&vertices[2])->scale(1.0f / 3.0f);
	this->sphereRadius = 0.0f;
	for (auto i = 0; i < vertices.size(); i++) {
		auto _sphereRadius = distanceVector.set(&center)->sub(&vertices[i])->computeLength();
		if (_sphereRadius > sphereRadius) sphereRadius = _sphereRadius;
	}
}

BoundingVolume* Triangle::clone()
{
	return new Triangle(
		&vertices[0],
		&vertices[1],
		&vertices[2]
	);
}
