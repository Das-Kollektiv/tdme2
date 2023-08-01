#include <tdme/engine/primitives/BoundingBox.h>

#include <vector>

#include <tdme/tdme.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::Transform;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

const array<int32_t, 3> BoundingBox::FACE0_INDICES = {{ 0, 4, 7 }};
const array<int32_t, 3> BoundingBox::FACE1_INDICES = {{ 7, 3, 0 }};
const array<int32_t, 3> BoundingBox::FACE2_INDICES = {{ 6, 5, 1 }};
const array<int32_t, 3> BoundingBox::FACE3_INDICES = {{ 1, 2, 6 }};
const array<int32_t, 3> BoundingBox::FACE4_INDICES = {{ 5, 4, 0 }};
const array<int32_t, 3> BoundingBox::FACE5_INDICES = {{ 0, 1, 5 }};
const array<int32_t, 3> BoundingBox::FACE6_INDICES = {{ 3, 7, 6 }};
const array<int32_t, 3> BoundingBox::FACE7_INDICES = {{ 6, 2, 3 }};
const array<int32_t, 3> BoundingBox::FACE8_INDICES = {{ 2, 1, 0 }};
const array<int32_t, 3> BoundingBox::FACE9_INDICES = {{ 0, 3, 2 }};
const array<int32_t, 3> BoundingBox::FACE10_INDICES = {{ 4, 5, 6 }};
const array<int32_t, 3> BoundingBox::FACE11_INDICES = {{ 6, 7, 4 }};
const array<array<int32_t,3>,12> BoundingBox::facesVerticesIndexes =
{{
	FACE0_INDICES, FACE1_INDICES, FACE2_INDICES, FACE3_INDICES,
	FACE4_INDICES, FACE5_INDICES, FACE6_INDICES, FACE7_INDICES,
	FACE8_INDICES, FACE9_INDICES, FACE10_INDICES, FACE11_INDICES
}};

BoundingBox::BoundingBox()
{
	vertices.resize(8);
	update();
}

BoundingBox::BoundingBox(BoundingBox* boundingBox)
{
	vertices.resize(8);
	this->min.set(boundingBox->min);
	this->max.set(boundingBox->max);
	update();
}

BoundingBox::BoundingBox(OrientedBoundingBox* obb)
{
	vertices.resize(8);
	min = obb->getCenter();
	max = obb->getCenter();
	for (auto& vertex: obb->getVertices()) {
		extend(vertex);
	}
}

BoundingBox::BoundingBox(const Vector3& min, const Vector3& max)
{
	vertices.resize(8);
	this->min.set(min);
	this->max.set(max);
	update();
}

void BoundingBox::fromBoundingVolume(BoundingBox* boundingBox)
{
	min = boundingBox->min;
	max = boundingBox->max;
	vertices = boundingBox->vertices;
	center = boundingBox->center;
	dimensions = boundingBox->dimensions;
}

void BoundingBox::fromBoundingVolumeWithTransformMatrix(BoundingBox* boundingBox, const Matrix4x4& transformMatrix)
{
	// apply transform from original vertices to local vertices
	auto _vertices = boundingBox->getVertices();
	for (auto i = 0; i < vertices.size(); i++) {
		vertices[i] = transformMatrix.multiply(_vertices[i]);
	}
	// determine axis aligned bounding box constraints based on local vertices
	float minX = vertices[0][0], minY = vertices[0][1], minZ = vertices[0][2];
	float maxX = vertices[0][0], maxY = vertices[0][1], maxZ = vertices[0][2];
	for (auto vertexIndex = 1; vertexIndex < vertices.size(); vertexIndex++) {
		const auto& vertex = vertices[vertexIndex];
		if (vertex[0] < minX) minX = vertex[0];
		if (vertex[1] < minY) minY = vertex[1];
		if (vertex[2] < minZ) minZ = vertex[2];
		if (vertex[0] > maxX) maxX = vertex[0];
		if (vertex[1] > maxY) maxY = vertex[1];
		if (vertex[2] > maxZ) maxZ = vertex[2];
	}
	// set up new aabb
	min.set(minX, minY, minZ);
	max.set(maxX, maxY, maxZ);
	// compute new vertices based on aabb constraints
	update();
}

void BoundingBox::update() {
	// near, left, top
	vertices[0].set(min[0], min[1], min[2]);
	// near, right, top
	vertices[1].set(max[0], min[1], min[2]);
	// near, right, bottom
	vertices[2].set(max[0], max[1], min[2]);
	// near, left, bottom
	vertices[3].set(min[0], max[1], min[2]);
	// far, left, top
	vertices[4].set(min[0], min[1], max[2]);
	// far, right, top
	vertices[5].set(max[0], min[1], max[2]);
	// far, right, bottom
	vertices[6].set(max[0], max[1], max[2]);
	// far, left, bottom
	vertices[7].set(min[0], max[1], max[2]);
	center.set(min).add(max).scale(0.5f);
	dimensions.set(max).sub(min);
}


