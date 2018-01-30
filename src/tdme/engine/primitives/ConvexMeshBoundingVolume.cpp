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


using tdme::engine::Transformations;
using tdme::math::Vector3;
using tdme::utils::ByteBuffer;
using tdme::utils::Console;
using tdme::utils::FloatBuffer;
using tdme::utils::IntBuffer;

void ConvexMeshBoundingVolume::createConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, bool haveLocalTranslation, const Vector3& localTranslation) {
	// delete old collision shape if we have any
	if (collisionShape != nullptr) delete collisionShape;
	if (polyhedronMesh != nullptr) delete polyhedronMesh;
	if (polygonVertexArray != nullptr) delete polygonVertexArray;
	if (verticesByteBuffer != nullptr) delete verticesByteBuffer;
	if (indicesByteBuffer != nullptr) delete indicesByteBuffer;

	Vector3 collisionShapeLocalTranslation;
	// check if local translation is given
	if (haveLocalTranslation == true) {
		collisionShapeLocalTranslation.set(localTranslation);
	} else {
		// determine center/position transformed
		collisionShapeLocalTranslation.set(0.0f, 0.0f, 0.0f);
		for (auto vertexIdx: indices) {
			auto& vertex = vertices[vertexIdx];
			collisionShapeLocalTranslation.add(vertex);
		}
		collisionShapeLocalTranslation.scale(1.0f / indices.size());
	}

	// local transformations
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));

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
	faces.clear();
	int indexIdx = 0;
	for (auto faceVerticesCount: facesVerticesCount) {
		reactphysics3d::PolygonVertexArray::PolygonFace face;
		face.nbVertices = faceVerticesCount;
		face.indexBase = indexIdx;
		faces.push_back(face);
		indexIdx+= faceVerticesCount;
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
