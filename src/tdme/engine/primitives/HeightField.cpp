#include <tdme/engine/primitives/HeightField.h>

#include <string>

#include <ext/reactphysics3d/src/collision/shapes/HeightFieldShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Float.h>

using std::to_string;

using tdme::engine::primitives::HeightField;

using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::Float;

HeightField::HeightField(Object3DModel* model, Transformations* transformations)
{
	float terrainHeight = 1.0f;

	// get triangles
	vector<Triangle> triangles;
	model->getFaceTriangles(&triangles);
	// apply transformations if we have one
	if (transformations != nullptr) {
		auto& transformationsMatrix = transformations->getTransformationsMatrix();
		for (auto& triangle: triangles) {
			for (auto& vertex: triangle.getVertices()) {
				transformationsMatrix.multiply(vertex, vertex);
			}
		}
	}

	// center
	Vector3 center;
	for (auto& triangle: triangles) {
		for (auto& vertex: triangle.getVertices()) center.add(vertex);
	}
	center.scale(1.0f / (triangles.size() * 3));

	Vector3 bbMin = center;
	Vector3 bbMax = center;
	for (auto& triangle: triangles) {
		for (auto& vertex: triangle.getVertices()) {
			if (vertex.getX() < bbMin.getX()) bbMin.setX(vertex.getX());
			if (vertex.getY() < bbMin.getY()) bbMin.setY(vertex.getY());
			if (vertex.getZ() < bbMin.getZ()) bbMin.setZ(vertex.getZ());
			if (vertex.getX() > bbMax.getX()) bbMax.setX(vertex.getX());
			if (vertex.getY() > bbMax.getY()) bbMax.setY(vertex.getY());
			if (vertex.getZ() > bbMax.getZ()) bbMax.setZ(vertex.getZ());
		}
	}

	float minX = static_cast< int32_t >(bbMin.getX());
	float maxX = static_cast< int32_t >(bbMax.getX());
	float minZ = static_cast< int32_t >(bbMin.getZ());
	float maxZ = static_cast< int32_t >(bbMax.getZ());
	Vector3 distance;
	Vector3 point;
	Vector3 closestPoint;
	float closestPointCandidateDistance;
	Vector3 closestPointCandidate;
	float height;
	float minHeight = bbMax.getY();
	float maxHeight = bbMin.getY();
	int dimensionX = (int)(maxX + 1) - (int)minX;
	int dimensionZ = (int)(maxZ + 1) - (int)minZ;
	heightMap = new float[dimensionZ * dimensionX];
	for (float x = minX; x <= maxX; x+= 1.0f)
	for (float z = minZ; z <= maxZ; z+= 1.0f) {
		float closestPointDistance = 10000.0f;
		point.set(x, bbMax.getY(), z);
		for (auto& triangle: triangles) {
			triangle.computeClosestPointOnBoundingVolume(point, closestPointCandidate);
			closestPointCandidateDistance = distance.set(point).sub(closestPointCandidate).computeLength();
			if (closestPointCandidateDistance < closestPointDistance) {
				closestPointDistance = closestPointCandidateDistance;
				closestPoint.set(closestPointCandidate);
			}
		}
		float height = closestPoint.getY();
		if (height < minHeight) minHeight = height;
		if (height > maxHeight) maxHeight = height;
		heightMap[((int)(z - minZ) * dimensionX) + (int)(x - minX)] = height;
	}

	// we are done
	collisionShape = new reactphysics3d::HeightFieldShape(
		dimensionX, dimensionZ, minHeight, maxHeight, heightMap, reactphysics3d::HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE
	);
	// compute bounding box
	computeBoundingBox();
}

HeightField::~HeightField()
{
	delete collisionShape;
	delete heightMap;
}

void HeightField::fromTransformations(Transformations* transformations) {
	Console::println("HeightField::fromTransformations(): This is not supported");
}

BoundingVolume* HeightField::clone() const
{
	return nullptr;
}

