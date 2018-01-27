#include <tdme/engine/primitives/Sphere.h>

#include <string>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/math/Vector3.h>

using std::to_string;
using std::vector;

using tdme::engine::primitives::Sphere;
using tdme::math::Vector3;

Sphere::Sphere() 
{
	createConvexMesh();
}

Sphere::Sphere(const Vector3& center, float radius)
{
	this->center.set(center);
	this->radius = radius;
	createConvexMesh();
}

void Sphere::createConvexMesh() {
	vector<Vector3> vertices;
	vector<int> indices;
	int segmentsX = 5;
	int segmentsY = 5;
	for (auto ySegment = 0; ySegment < segmentsY + 1; ySegment++)
	for (auto xSegment = 0; xSegment < segmentsX; xSegment++) {
		auto vertex = (
			Vector3(
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::cos(Math::PI * 2 * xSegment / segmentsX))),
				((Math::cos(Math::PI * ySegment / segmentsY))),
				((Math::sin(Math::PI * ySegment / segmentsY) * Math::sin(Math::PI * 2 * xSegment / segmentsX))))
			).scale(radius).add(center);
		vertices.push_back(vertex);
	}
	int32_t vi0, vi1, vi2;
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
	ConvexMeshBoundingVolume::createConvexMesh(vertices, indices, true, center);
}

const Vector3& Sphere::getCenter() const {
	return center;
}

float Sphere::getRadius() const
{
	return radius;
}

BoundingVolume* Sphere::clone() const
{
	return new Sphere(center, radius);
}

