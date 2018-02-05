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

float TerrainConvexMesh::getHeight() {
	return height;
}

Triangle* TerrainConvexMesh::getTriangleTransformed() {
	return &triangleTransformed;
}

const Vector3& TerrainConvexMesh::getPositionTransformed() const {
	return positionTransformed;
}

void TerrainConvexMesh::createConvexMesh() {
	// extend triangle to convex mesh
	array<Triangle, 2> triangles;

	// set up top triangle
	triangles[0] = triangleTransformed;

	// set up bottom triangle
	triangles[1] = triangleTransformed;
	triangles[1].getVertices()[0].addY(-height);
	triangles[1].getVertices()[1].addY(-height);
	triangles[1].getVertices()[2].addY(-height);

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
	vector<int> facesVerticesCount;
	vector<int> indices;
	int vertexIdx = 0;

	// vertices
	vertices.push_back(triangles[0].getVertices()[2]);
	vertices.push_back(triangles[0].getVertices()[1]);
	vertices.push_back(triangles[0].getVertices()[0]);
	vertices.push_back(triangles[1].getVertices()[2]);
	vertices.push_back(triangles[1].getVertices()[1]);
	vertices.push_back(triangles[1].getVertices()[0]);

	// push top vertex
	facesVerticesCount.push_back(3);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(0);

	// sides
	// correct
	facesVerticesCount.push_back(4);
	indices.push_back(0 * 3 + 0);
	indices.push_back(0 * 3 + 1);
	indices.push_back(1 * 3 + 1);
	indices.push_back(1 * 3 + 0);
	// correct
	facesVerticesCount.push_back(4);
	indices.push_back(0 * 3 + 1);
	indices.push_back(0 * 3 + 2);
	indices.push_back(1 * 3 + 2);
	indices.push_back(1 * 3 + 1);
	// xxx
	facesVerticesCount.push_back(4);
	indices.push_back(0 * 3 + 2);
	indices.push_back(0 * 3 + 0);
	indices.push_back(1 * 3 + 0);
	indices.push_back(1 * 3 + 2);

	// push bottom vertex
	facesVerticesCount.push_back(3);
	indices.push_back(3);
	indices.push_back(4);
	indices.push_back(5);

	//
	ConvexMeshBoundingVolume::createConvexMesh(vertices, facesVerticesCount, indices, true, center);

	// compute bounding box
	computeBoundingBox();
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
