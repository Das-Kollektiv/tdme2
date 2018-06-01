#include <tdme/engine/primitives/TerrainMesh.h>

#include <vector>

#include <ext/reactphysics3d/src/collision/TriangleMesh.h>
#include <ext/reactphysics3d/src/collision/TriangleVertexArray.h>
#include <ext/reactphysics3d/src/collision/shapes/ConcaveMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/utils/Console.h>

using std::vector;

using tdme::engine::primitives::TerrainMesh;
using tdme::engine::Object3DModel;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::utils::Console;

TerrainMesh::TerrainMesh()
{
}

TerrainMesh::TerrainMesh(Object3DModel* model, const Transformations& transformations)
{
	// fetch vertices and indices
	vector<Triangle> triangles;
	model->getTriangles(triangles);
	Vector3 vertexTransformed;
	for (auto& triangle: triangles) {
		auto verticesIdx = vertices.size() / 3;
		transformations.getTransformationsMatrix().multiply(triangle.getVertices()[0], vertexTransformed);
		vertices.push_back(vertexTransformed[0]);
		vertices.push_back(vertexTransformed[1]);
		vertices.push_back(vertexTransformed[2]);
		transformations.getTransformationsMatrix().multiply(triangle.getVertices()[1], vertexTransformed);
		vertices.push_back(vertexTransformed[0]);
		vertices.push_back(vertexTransformed[1]);
		vertices.push_back(vertexTransformed[2]);
		transformations.getTransformationsMatrix().multiply(triangle.getVertices()[2], vertexTransformed);
		vertices.push_back(vertexTransformed[0]);
		vertices.push_back(vertexTransformed[1]);
		vertices.push_back(vertexTransformed[2]);
		indices.push_back(verticesIdx + 0);
		indices.push_back(verticesIdx + 1);
		indices.push_back(verticesIdx + 2);
	}
	vertices.shrink_to_fit();
	indices.shrink_to_fit();
	setScale(Vector3(1.0f, 1.0f, 1.0f));
}

TerrainMesh::~TerrainMesh() {
	if (collisionShape != nullptr) delete collisionShape;
	if (triangleMesh != nullptr) delete triangleMesh;
	if (triangleVertexArray != nullptr) delete triangleVertexArray;
}

void TerrainMesh::setScale(const Vector3& scale) {
	// store new scale
	this->scale.set(scale);

	// delete old collision shape
	if (collisionShape != nullptr) delete collisionShape;
	if (triangleMesh != nullptr) delete triangleMesh;
	if (triangleVertexArray != nullptr) delete triangleVertexArray;

	// RP3D triangle vertex array
	triangleVertexArray = new reactphysics3d::TriangleVertexArray(
		vertices.size() / 3,
		vertices.data(),
		3 * sizeof(float),
		vertices.size() / 3 / 3,
		indices.data(),
		3 * sizeof(int),
		reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE
	);

	// add the triangle vertex array to the triangle mesh
	triangleMesh = new reactphysics3d::TriangleMesh();
	triangleMesh->addSubpart(triangleVertexArray);

	// create the concave mesh shape
	collisionShape = new reactphysics3d::ConcaveMeshShape(triangleMesh);

	// compute bounding box
	computeBoundingBox();
}

TerrainMesh::BoundingVolume* TerrainMesh::clone() const {
	Console::println("TerrainMesh::clone(): Not supported!");
	return nullptr;
}
