#include <tdme/engine/primitives/ConvexMesh.h>

#include <array>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::array;
using std::vector;

using tdme::engine::primitives::ConvexMesh;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::math::Vector3;
using tdme::utils::Console;

ConvexMesh::ConvexMesh()
{
}

ConvexMesh::ConvexMesh(Object3DModel* model)
{
	vector<Triangle> triangles;
	vector<int> indices;
	model->getFaceTriangles(&triangles);
	int vertexIdx = 0;
	for (auto& triangle: triangles) {
		for (auto& vertex: *triangle.getVertices()) {
			vertices.push_back(vertex);
			indices.push_back(vertexIdx++);
		}
	}

	// create convex mesh
	ConvexMeshBoundingVolume::createConvexMesh(vertices, indices);
}

ConvexMesh::ConvexMesh(const vector<Vector3>& vertices, const vector<int>& indices) {
	this->vertices = vertices;
	this->indices = indices;

	// create convex mesh
	ConvexMeshBoundingVolume::createConvexMesh(vertices, indices);
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(vertices, indices);
}

const vector<Vector3>& ConvexMesh::getVertices() {
	return vertices;
}
