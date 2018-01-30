#include <tdme/engine/primitives/TerrainConvexMesh.h>

#include <array>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>

using std::array;
using std::vector;

using tdme::engine::primitives::TerrainConvexMesh;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::utils::Console;

TerrainConvexMesh::TerrainConvexMesh(const TerrainConvexMesh& other) {
	this->height = other.height;
	this->triangle = other.triangle;
	this->triangleTransformed = other.triangleTransformed;
	this->positionTransformed = other.positionTransformed;
	this->createConvexMesh();
}

TerrainConvexMesh::TerrainConvexMesh()
{
	height = 0.75f;
	createConvexMesh();
}

TerrainConvexMesh::TerrainConvexMesh(const Triangle& triangle, float height)
{
	this->height = height;
	this->triangle = triangle;
	this->triangleTransformed = triangle;
	collisionShape = nullptr;
	createConvexMesh();
}

TerrainConvexMesh& TerrainConvexMesh::operator=(const TerrainConvexMesh& other) {
	this->height = other.height;
	this->triangle = other.triangle;
	this->triangleTransformed = other.triangleTransformed;
	this->positionTransformed = other.positionTransformed;
	this->createConvexMesh();
	return *this;
}

void TerrainConvexMesh::createTerrainConvexMeshes(Object3DModel* model, vector<TerrainConvexMesh>* convexMeshes, float height)
{
	// please note: no optimizations yet
	vector<Triangle> faceTriangles;
	model->getFaceTriangles(&faceTriangles);
	for (auto& triangle: faceTriangles) {
		convexMeshes->push_back(TerrainConvexMesh(triangle, height));
	}
}

const Vector3& TerrainConvexMesh::getPositionTransformed() const {
	return positionTransformed;
}

void TerrainConvexMesh::createConvexMesh() {
	// extend triangle to convex mesh
	int triangleIdx = 0;
	array<Triangle, 8> triangles;

	// set up top triangle
	triangles[0] = triangleTransformed;

	// add triangle vertices
	Vector3 triangleVertex0Bottom;
	Vector3 triangleVertex1Bottom;
	Vector3 triangleVertex2Bottom;
	Vector3 triangleVertex0Top = triangles[triangleIdx].getVertices()[0];
	Vector3 triangleVertex1Top = triangles[triangleIdx].getVertices()[1];
	Vector3 triangleVertex2Top = triangles[triangleIdx].getVertices()[2];
	triangleIdx++;

	triangleVertex0Bottom.set(triangleVertex0Top).addY(-height);
	triangleVertex1Bottom.set(triangleVertex1Top).addY(-height);
	triangleVertex2Bottom.set(triangleVertex2Top).addY(-height);

	// set up triangle on bottom
	triangles[triangleIdx].getVertices()[0].set(triangleVertex0Top).addY(-height);
	triangles[triangleIdx].getVertices()[1].set(triangleVertex1Top).addY(-height);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex2Top).addY(-height);
	triangleIdx++;

	// add bottom top triangles
	//	vertices 0, 2
	triangles[triangleIdx].getVertices()[0].set(triangleVertex0Top);
	triangles[triangleIdx].getVertices()[1].set(triangleVertex2Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex0Bottom);
	triangleIdx++;
	triangles[triangleIdx].getVertices()[1].set(triangleVertex0Bottom);
	triangles[triangleIdx].getVertices()[0].set(triangleVertex2Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex2Bottom);
	triangleIdx++;

	//	vertices 0, 1
	triangles[triangleIdx].getVertices()[1].set(triangleVertex0Top);
	triangles[triangleIdx].getVertices()[0].set(triangleVertex1Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex0Bottom);
	triangleIdx++;
	triangles[triangleIdx].getVertices()[1].set(triangleVertex0Bottom);
	triangles[triangleIdx].getVertices()[0].set(triangleVertex1Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex1Bottom);
	triangleIdx++;

	//	vertices 1, 2
	triangles[triangleIdx].getVertices()[1].set(triangleVertex1Top);
	triangles[triangleIdx].getVertices()[0].set(triangleVertex2Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex1Bottom);
	triangleIdx++;
	triangles[triangleIdx].getVertices()[1].set(triangleVertex1Bottom);
	triangles[triangleIdx].getVertices()[0].set(triangleVertex2Top);
	triangles[triangleIdx].getVertices()[2].set(triangleVertex2Bottom);
	triangleIdx++;

	// center
	Vector3 center;
	for (auto& triangle: triangles) {
		for (auto& vertex: triangle.getVertices()) {
			center.add(vertex);
		}
	}
	center.scale(1.0f / (triangles.size() * 3));
	positionTransformed.set(center);

	// create convex mesh shape
	vector<Vector3> vertices;
	vector<int> indices;
	int vertexIdx = 0;
	Vector3 vertexTransformed;
	for (auto& triangle: triangles) {
		for (auto& vertex: triangle.getVertices()) {
			vertexTransformed.set(vertex);
			vertexTransformed.sub(center);
			vertices.push_back(vertexTransformed);
			indices.push_back(vertexIdx++);
		}
	}

	//
	ConvexMeshBoundingVolume::createConvexMesh(vertices, indices);
}

void TerrainConvexMesh::applyTransformations(Transformations* transformations) {
	auto& transformationsMatrix = transformations->getTransformationsMatrix();
	triangleTransformed = triangle;
	for (auto& vertex: triangleTransformed.getVertices()) {
		transformationsMatrix.multiply(vertex, vertex);
	}
	createConvexMesh();
}

void TerrainConvexMesh::fromTransformations(Transformations* transformations) {
	collisionShapeTransform.setPosition(reactphysics3d::Vector3(positionTransformed.getX(), positionTransformed.getY(), positionTransformed.getZ()));
	computeBoundingBox();
}

BoundingVolume* TerrainConvexMesh::clone() const
{
	return new TerrainConvexMesh(triangle, height);
}
