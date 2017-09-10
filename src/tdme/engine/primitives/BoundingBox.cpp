#include <tdme/engine/primitives/BoundingBox.h>

#include <vector>

#include <java/lang/Math.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::vector;

using tdme::engine::primitives::BoundingBox;
using java::lang::Math;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;

array<int32_t, 3> BoundingBox::FACE0_INDICES = {{ 0, 4, 7 }};
array<int32_t, 3> BoundingBox::FACE1_INDICES = {{ 7, 3, 0 }};
array<int32_t, 3> BoundingBox::FACE2_INDICES = {{ 6, 5, 1 }};
array<int32_t, 3> BoundingBox::FACE3_INDICES = {{ 1, 2, 6 }};
array<int32_t, 3> BoundingBox::FACE4_INDICES = {{ 5, 4, 0 }};
array<int32_t, 3> BoundingBox::FACE5_INDICES = {{ 0, 1, 5 }};
array<int32_t, 3> BoundingBox::FACE6_INDICES = {{ 3, 7, 6 }};
array<int32_t, 3> BoundingBox::FACE7_INDICES = {{ 6, 2, 3 }};
array<int32_t, 3> BoundingBox::FACE8_INDICES = {{ 2, 1, 0 }};
array<int32_t, 3> BoundingBox::FACE9_INDICES = {{ 0, 3, 2 }};
array<int32_t, 3> BoundingBox::FACE10_INDICES = {{ 4, 5, 6 }};
array<int32_t, 3> BoundingBox::FACE11_INDICES = {{ 6, 7, 4 }};
array<array<int32_t,3>,12> BoundingBox::facesVerticesIndexes =
{{
	FACE0_INDICES, FACE1_INDICES, FACE2_INDICES, FACE3_INDICES,
	FACE4_INDICES, FACE5_INDICES, FACE6_INDICES, FACE7_INDICES,
	FACE8_INDICES, FACE9_INDICES, FACE10_INDICES, FACE11_INDICES
}};

BoundingBox::BoundingBox() 
{
	min.set(0.0f, 0.0f, 0.0f);
	max.set(0.0f, 0.0f, 0.0f);
	vertices.resize(8);
	update();
}

BoundingBox::BoundingBox(BoundingBox* boundingBox) 
{
	this->min.set(&boundingBox->min);
	this->max.set(&boundingBox->max);
	vertices.resize(8);
	update();
}

BoundingBox::BoundingBox(Vector3* min, Vector3* max)
{

	this->min.set(min);
	this->max.set(max);
	vertices.resize(8);
	update();
}

Vector3* BoundingBox::getMin()
{
	return &min;
}

Vector3* BoundingBox::getMax()
{
	return &max;
}

vector<Vector3>* BoundingBox::getVertices()
{
	return &vertices;
}

array<array<int32_t,3>,12>* BoundingBox::getFacesVerticesIndexes()
{
	return &facesVerticesIndexes;
}

void BoundingBox::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< BoundingBox* >(original) != nullptr == false) {
		return;
	}
	auto boundingBox = dynamic_cast< BoundingBox* >(original);
	min.set(&boundingBox->min);
	max.set(&boundingBox->max);
	center.set(&boundingBox->center);
	for (auto i = 0; i < vertices.size(); i++) {
		vertices[i].set(&boundingBox->vertices[i]);
	}
}

void BoundingBox::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< BoundingBox* >(original) != nullptr == false) {
		return;
	}
	auto boundingBox = dynamic_cast< BoundingBox* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	auto _vertices = boundingBox->getVertices();
	for (auto i = 0; i < vertices.size(); i++) {
		transformationsMatrix->multiply(&(*_vertices)[i], &vertices[i]);
	}
	auto vertexXYZ = vertices[0].getArray();
	float minX = (*vertexXYZ)[0], minY = (*vertexXYZ)[1], minZ = (*vertexXYZ)[2];
	float maxX = (*vertexXYZ)[0], maxY = (*vertexXYZ)[1], maxZ = (*vertexXYZ)[2];
	for (auto vertexIndex = 1; vertexIndex < vertices.size(); vertexIndex++) {
		auto& vertex = vertices[vertexIndex];
		vertexXYZ = vertex.getArray();
		if ((*vertexXYZ)[0] < minX) minX = (*vertexXYZ)[0];
		if ((*vertexXYZ)[1] < minY) minY = (*vertexXYZ)[1];
		if ((*vertexXYZ)[2] < minZ) minZ = (*vertexXYZ)[2];
		if ((*vertexXYZ)[0] > maxX) maxX = (*vertexXYZ)[0];
		if ((*vertexXYZ)[1] > maxY) maxY = (*vertexXYZ)[1];
		if ((*vertexXYZ)[2] > maxZ) maxZ = (*vertexXYZ)[2];

	}
	min.set(minX, minY, minZ);
	max.set(maxX, maxY, maxZ);
	update();
}

void BoundingBox::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	auto pointXYZ = point->getArray();
	auto minXYZ = min.getArray();
	auto maxXYZ = max.getArray();
	auto closestX = (*pointXYZ)[0] < (*minXYZ)[0] ? (*minXYZ)[0] : (*pointXYZ)[0] > (*maxXYZ)[0] ? (*maxXYZ)[0] : (*pointXYZ)[0];
	auto closestY = (*pointXYZ)[1] < (*minXYZ)[1] ? (*minXYZ)[1] : (*pointXYZ)[1] > (*maxXYZ)[1] ? (*maxXYZ)[1] : (*pointXYZ)[1];
	auto closestZ = (*pointXYZ)[2] < (*minXYZ)[2] ? (*minXYZ)[2] : (*pointXYZ)[2] > (*maxXYZ)[2] ? (*maxXYZ)[2] : (*pointXYZ)[2];
	closestPoint->set(closestX, closestY, closestZ);
}

bool BoundingBox::containsPoint(Vector3* point)
{
	auto pointXYZ = point->getArray();
	auto minXYZ = min.getArray();
	auto maxXYZ = max.getArray();
	for (auto i = 0; i < 3; i++) {
		if ((*pointXYZ)[i] < (*minXYZ)[i]) return false;
		if ((*pointXYZ)[i] > (*maxXYZ)[i]) return false;
	}
	return true;
}

bool BoundingBox::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
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

Vector3* BoundingBox::getCenter()
{
	return &center;
}

float BoundingBox::getSphereRadius()
{
	return sphereRadius;
}

float BoundingBox::computeDimensionOnAxis(Vector3* axis)
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

void BoundingBox::update()
{
	auto minXYZ = min.getArray();
	auto maxXYZ = max.getArray();
	vertices[0].set((*minXYZ)[0], (*minXYZ)[1], (*minXYZ)[2]);
	vertices[1].set((*maxXYZ)[0], (*minXYZ)[1], (*minXYZ)[2]);
	vertices[2].set((*maxXYZ)[0], (*maxXYZ)[1], (*minXYZ)[2]);
	vertices[3].set((*minXYZ)[0], (*maxXYZ)[1], (*minXYZ)[2]);
	vertices[4].set((*minXYZ)[0], (*minXYZ)[1], (*maxXYZ)[2]);
	vertices[5].set((*maxXYZ)[0], (*minXYZ)[1], (*maxXYZ)[2]);
	vertices[6].set((*maxXYZ)[0], (*maxXYZ)[1], (*maxXYZ)[2]);
	vertices[7].set((*minXYZ)[0], (*maxXYZ)[1], (*maxXYZ)[2]);
	center.set(&min)->add(&max)->scale(0.5f);
	Vector3 halfExtension;
	halfExtension.set(&max)->sub(&min)->scale(0.5f);
	sphereRadius = halfExtension.computeLength();
}

BoundingVolume* BoundingBox::clone()
{
	return new BoundingBox(&min, &max);
}


