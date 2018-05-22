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

TerrainMesh::TerrainMesh(Object3DModel* model)
{
	// fetch vertices and indices
	vector<Triangle> triangles;
	model->getFaceTriangles(&triangles);
	for (auto& triangle: triangles) {
		auto verticesIdx = vertices.size() / 3;
		vertices.push_back(triangle.getVertices()[0][0]);
		vertices.push_back(triangle.getVertices()[0][1]);
		vertices.push_back(triangle.getVertices()[0][2]);
		vertices.push_back(triangle.getVertices()[1][0]);
		vertices.push_back(triangle.getVertices()[1][1]);
		vertices.push_back(triangle.getVertices()[1][2]);
		vertices.push_back(triangle.getVertices()[2][0]);
		vertices.push_back(triangle.getVertices()[2][1]);
		vertices.push_back(triangle.getVertices()[2][2]);
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

bool TerrainMesh::setScale(const Vector3& scale) {
	if (this->scale.equals(scale) == false) {
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
		collisionShape = new reactphysics3d::ConcaveMeshShape(triangleMesh, reactphysics3d::Vector3(scale.getX(), scale.getY(), scale.getZ()));

		// compute bounding box
		computeBoundingBox();

		//
		return true;
	}

	//
	return false;
}

TerrainMesh::BoundingVolume* TerrainMesh::clone() const {
	Console::println("TerrainMesh::clone(): Not supported!");
	return nullptr;
}
