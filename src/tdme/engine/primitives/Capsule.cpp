#include <tdme/engine/primitives/Capsule.h>

#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using tdme::engine::primitives::Capsule;

using std::vector;

using tdme::math::Math;
using tdme::math::MathTools;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

Capsule::Capsule(const Vector3& a, const Vector3& b, float radius)
{
	this->a.set(a);
	this->b.set(b);
	this->radius = radius;
	createConvexMesh();
}

void Capsule::createConvexMesh() {
	vector<Vector3> vertices;
	vector<int> indices;
	int segmentsX = 5;
	int segmentsY = 5;
	Quaternion rotationQuaternion;
	rotationQuaternion.identity();
	Vector3 yAxis(0.0f, -1.0f, 0.0f);
	Vector3 abNormalized = a.clone().sub(b).normalize();
	auto& abNormalizedVectorXYZ = abNormalized.getArray();
	Vector3 rotationAxis;
	if (Math::abs(abNormalizedVectorXYZ[0]) < MathTools::EPSILON && Math::abs(abNormalizedVectorXYZ[2]) < MathTools::EPSILON) {
		rotationAxis.set(abNormalizedVectorXYZ[1], 0.0f, 0.0f);
	} else {
		Vector3::computeCrossProduct(yAxis, abNormalized, rotationAxis).normalize();
	}
	auto angle = Vector3::computeAngle(yAxis, abNormalized, yAxis);
	rotationQuaternion.rotate(angle, rotationAxis);
	for (auto ySegment = 0; ySegment < segmentsY / 2; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = Vector3();
		rotationQuaternion.multiply(
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))
			),
			vertex
		);
		vertex.scale(radius);
		vertex.add(b);
		vertices.push_back(vertex);
	}
	for (auto ySegment = segmentsY / 2; ySegment < segmentsY + 1; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = Vector3();
		rotationQuaternion.multiply(
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX)))
			),
			vertex
		);
		vertex.scale(radius);
		vertex.add(a);
		vertices.push_back(vertex);
	}
	int vi0, vi1, vi2;
	for (auto y = 0; y < segmentsY + 1; y++) {
		for (auto x = 0; x < segmentsX; x++) {
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			indices.push_back(vi0);
			indices.push_back(vi1);
			indices.push_back(vi2);
			vi0 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 0) % (segmentsX));
			vi1 = ((y + 0) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			vi2 = ((y + 1) % (segmentsY + 1)) * segmentsX + ((x + 1) % (segmentsX));
			indices.push_back(vi0);
			indices.push_back(vi1);
			indices.push_back(vi2);
		}
	}

	// create convex mesh
	ConvexMeshBoundingVolume::createConvexMesh(vertices, indices, true, a.clone().add(b).scale(0.5f));
}

float Capsule::getRadius() const
{
	return radius;
}

const Vector3& Capsule::getA() const
{
	return a;
}

const Vector3& Capsule::getB() const
{
	return b;
}

BoundingVolume* Capsule::clone() const
{
	return new Capsule(a, b, radius);
}
