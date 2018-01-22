#include <tdme/engine/primitives/ConvexMeshBoundingVolume.h>

#include <string>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>
#include <ext/reactphysics3d/src/collision/PolyhedronMesh.h>
#include <ext/reactphysics3d/src/collision/PolygonVertexArray.h>

#include <tdme/engine/Transformations.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/ByteBuffer.h>
#include <tdme/utils/FloatBuffer.h>
#include <tdme/utils/IntBuffer.h>

using tdme::engine::primitives::ConvexMeshBoundingVolume;

using std::string;
using std::to_string;

using tdme::engine::Transformations;
using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;

void ConvexMeshBoundingVolume::createConvexMesh(const vector<Vector3>& vertices, const vector<int>& indices, bool haveLocalTranslation, const Vector3& localTranslation) {
	// delete old collision shape if we have any
	if (collisionShape != nullptr) delete collisionShape;
	if (polyhedronMesh != nullptr) delete polyhedronMesh;
	if (polygonVertexArray != nullptr) delete polygonVertexArray;
	if (verticesByteBuffer != nullptr) delete verticesByteBuffer;
	if (indicesByteBuffer != nullptr) delete indicesByteBuffer;

	// check if local translation is given
	if (haveLocalTranslation == true) {
		collisionShapeLocalTranslation.set(localTranslation);
	} else {
		// determine center/position transformed
		collisionShapeLocalTranslation.set(0.0f, 0.0f, 0.0f);
		for (auto& vertex: vertices) {
			collisionShapeLocalTranslation.add(vertex);
		}
		collisionShapeLocalTranslation.scale(1.0f / vertices.size());
	}

	// generate vertices and indices buffers
	verticesByteBuffer = ByteBuffer::allocate(vertices.size() * 3 * sizeof(float));
	indicesByteBuffer = ByteBuffer::allocate(indices.size() * sizeof(int));
	auto verticesBuffer = verticesByteBuffer->asFloatBuffer();
	auto indicesBuffer = indicesByteBuffer->asIntBuffer();
	Vector3 vertexTransformed;
	for (auto& vertex: vertices) {
		vertexTransformed.set(vertex);
		vertexTransformed.sub(collisionShapeLocalTranslation);
		verticesBuffer.put(vertexTransformed.getArray());
	}
	for (auto& index: indices) {
		indicesBuffer.put(index);
	}
	for (auto i = 0; i < indices.size() / 3; i++) {
		reactphysics3d::PolygonVertexArray::PolygonFace face;
		face.indexBase = i * 3;
		face.nbVertices = 3;
		faces.push_back(face);
	}
	auto polygonVertexArray = new reactphysics3d::PolygonVertexArray(
		vertices.size(),
		verticesByteBuffer->getBuffer(),
		3 * sizeof(float),
		indicesByteBuffer->getBuffer(),
		sizeof(int),
		faces.size(),
		faces.data(),
		reactphysics3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
		reactphysics3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE
	);
	auto polyhedronMesh = new reactphysics3d::PolyhedronMesh(polygonVertexArray);
	// create convex mesh shape
	auto convexMeshShape = new reactphysics3d::ConvexMeshShape(polyhedronMesh);
	// set up new collision shape
	collisionShape = convexMeshShape;
	// transform
	collisionShapeTransform = reactphysics3d::Transform();
	// compute bounding box
	computeBoundingBox();
}

ConvexMeshBoundingVolume::~ConvexMeshBoundingVolume() {
	if (collisionShape != nullptr) delete collisionShape;
	if (polyhedronMesh != nullptr) delete polyhedronMesh;
	if (polygonVertexArray != nullptr) delete polygonVertexArray;
	if (verticesByteBuffer != nullptr) delete verticesByteBuffer;
	if (indicesByteBuffer != nullptr) delete indicesByteBuffer;
}
