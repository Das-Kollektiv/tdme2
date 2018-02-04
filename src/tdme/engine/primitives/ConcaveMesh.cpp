#include <tdme/engine/primitives/ConcaveMesh.h>

#include <string>

#include <ext/reactphysics3d/src/collision/TriangleVertexArray.h>
#include <ext/reactphysics3d/src/collision/TriangleMesh.h>
#include <ext/reactphysics3d/src/collision/shapes/ConcaveMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>

using tdme::engine::primitives::ConcaveMesh;

using std::to_string;

using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;

ConcaveMesh::ConcaveMesh(Object3DModel* model, Transformations* transformations)
{
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

	// determine vertices and indices
	vector<Vector3> vertices;
	vector<int> indices;
	for (auto& triangle: triangles) {
		for (auto& triangleVertex: triangle.getVertices()) {
			// check if to insert vertex
			int vertexIdx = 0;
			for (auto& vertexExisting: vertices) {
				if (vertexExisting.equals(triangleVertex) == true) {
					break;
				}
				vertexIdx++;
			}
			if (vertexIdx == vertices.size()) {
				vertices.push_back(triangleVertex);
			}

			// add index
			indices.push_back(vertexIdx);
		}
	}

	// generate vertices and indices buffers
	verticesByteBuffer = ByteBuffer::allocate(vertices.size() * 3 * sizeof(float));
	indicesByteBuffer = ByteBuffer::allocate(triangles.size() * 3 * sizeof(int));
	auto verticesBuffer = verticesByteBuffer->asFloatBuffer();
	auto indicesBuffer = indicesByteBuffer->asIntBuffer();
	for (auto& vertex: vertices) verticesBuffer.put(vertex.getArray());
	for (auto& index: indices) indicesBuffer.put(index);

	// triangle vertex array
	triangleVertexArray = new reactphysics3d::TriangleVertexArray(
		vertices.size(),
		verticesByteBuffer->getBuffer(),
		3 * sizeof(float),
		triangles.size(),
		indicesByteBuffer->getBuffer(),
		sizeof(int),
		reactphysics3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		reactphysics3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE
	);
	// add to triangle mesh
	triangleMesh.addSubpart(triangleVertexArray);
	// we are done
	collisionShape = new reactphysics3d::ConcaveMeshShape(&triangleMesh);
	// compute bounding box
	computeBoundingBox();
}

ConcaveMesh::~ConcaveMesh()
{
	delete collisionShape;
	delete triangleVertexArray;
	delete verticesByteBuffer;
	delete indicesByteBuffer;
}

void ConcaveMesh::fromTransformations(Transformations* transformations) {
	Console::println("ConcaveMesh::fromTransformations(): This is not supported, rather create concave mesh with transformations");
}

BoundingVolume* ConcaveMesh::clone() const
{
	return nullptr;
}

