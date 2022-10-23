#include <tdme/engine/primitives/TerrainMesh.h>

#include <vector>

#include <reactphysics3d/collision/shapes/ConcaveMeshShape.h>
#include <reactphysics3d/collision/TriangleMesh.h>
#include <reactphysics3d/collision/TriangleVertexArray.h>

#include <tdme/tdme.h>
#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/utilities/Console.h>

using std::to_string;
using std::vector;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::TerrainMesh;
using tdme::engine::primitives::Triangle;
using tdme::engine::ObjectModel;
using tdme::utilities::Console;

TerrainMesh::TerrainMesh()
{
}

TerrainMesh::TerrainMesh(ObjectModel* model, const Transform& transform)
{
	// fetch vertices and indices
	vector<Triangle> triangles;
	vector<Vector3> indexedVertices;
	model->getTriangles(triangles);
	Vector3 vertexTransformed;
	for (auto& triangle: triangles) {
		for (const auto& vertex: triangle.getVertices()) {
			vertexTransformed = transform.getTransformMatrix().multiply(vertex);
			auto i = 0;
			for (; i < indexedVertices.size(); i++) {
				if (indexedVertices[i].equals(vertexTransformed) == true) break;
			}
			if (i == indexedVertices.size()) {
				indexedVertices.push_back(vertexTransformed);
				vertices.push_back(vertexTransformed[0]);
				vertices.push_back(vertexTransformed[1]);
				vertices.push_back(vertexTransformed[2]);
			}
			indices.push_back(i);
		}
	}
	vertices.shrink_to_fit();
	indices.shrink_to_fit();
	setScale(Vector3(1.0f, 1.0f, 1.0f));
}

TerrainMesh::~TerrainMesh() {
	destroyCollisionShape();
}

void TerrainMesh::setScale(const Vector3& scale) {
	//
	if (scale.equals(Vector3(1.0f, 1.0f, 1.0f)) == false) {
		Console::println("TerrainMesh::setScale(): != 1.0f: Not supported!");
	}
	// store new scale
	this->scale.set(scale);
}

void TerrainMesh::setTransform(const Transform& transform) {
	Console::println("TerrainMesh::setTransform(): Not supported!");
}

void TerrainMesh::destroyCollisionShape() {
	if (collisionShape == nullptr) return;
	this->world->physicsCommon.destroyConcaveMeshShape(static_cast<reactphysics3d::ConcaveMeshShape*>(collisionShape));
	this->world->physicsCommon.destroyTriangleMesh(triangleMesh);
	delete triangleVertexArray;
	collisionShape = nullptr;
	triangleMesh = nullptr;
	triangleVertexArray = nullptr;
}

void TerrainMesh::createCollisionShape(World* world) {
	if (this->world != nullptr && this->world != world) {
		Console::println("TerrainMesh::createCollisionShape(): already attached to a world.");
	}
	this->world = world;

	// RP3D triangle vertex array
	triangleVertexArray = new reactphysics3d::TriangleVertexArray(
		vertices.size() / 3,
		vertices.data(),
		3 * sizeof(float),
		indices.size() / 3,
		indices.data(),
		3 * sizeof(int),
		reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE
	);

	// add the triangle vertex array to the triangle mesh
	triangleMesh = world->physicsCommon.createTriangleMesh();
	triangleMesh->addSubpart(triangleVertexArray);

	// create the concave mesh shape
	collisionShape = world->physicsCommon.createConcaveMeshShape(triangleMesh);

	// compute bounding box
	computeBoundingBox();
}

TerrainMesh::BoundingVolume* TerrainMesh::clone() const {
	auto terrainMesh = new TerrainMesh();
	terrainMesh->vertices = vertices;
	terrainMesh->indices = indices;
	return terrainMesh;
}
