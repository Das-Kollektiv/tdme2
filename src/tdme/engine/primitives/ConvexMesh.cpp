#include <tdme/engine/primitives/ConvexMesh.h>

#include <algorithm>
#include <array>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <reactphysics3d/collision/shapes/ConvexMeshShape.h>
#include <reactphysics3d/utils/Message.h>

#include <tdme/tdme.h>
#include <tdme/engine/fileio/models/WFObjWriter.h>

#include <tdme/engine/physics/World.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/engine/ObjectModel.h>
#include <tdme/engine/Transform.h>
#include <tdme/math/Math.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utilities/ByteBuffer.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/Exception.h>
#include <tdme/utilities/ExceptionBase.h>
#include <tdme/utilities/Float.h>
#include <tdme/utilities/FloatBuffer.h>
#include <tdme/utilities/IntBuffer.h>
#include <tdme/utilities/ModelTools.h>

using std::array;
using std::find;
using std::make_unique;
using std::map;
using std::reverse;
using std::sort;
using std::unique;
using std::unique_ptr;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using tdme::engine::fileio::models::WFObjWriter;

using tdme::engine::physics::World;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::Triangle;
using tdme::engine::ObjectModel;
using tdme::engine::Transform;
using tdme::math::Math;
using tdme::math::Vector3;
using tdme::utilities::ByteBuffer;
using tdme::utilities::Console;
using tdme::utilities::Exception;
using tdme::utilities::ExceptionBase;
using tdme::utilities::Float;
using tdme::utilities::FloatBuffer;
using tdme::utilities::IntBuffer;
using tdme::utilities::ModelTools;

ConvexMesh::ConvexMesh()
{
}

void ConvexMesh::createConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale) {
	// check if local translation is given
	// 	determine center/position transformed
	collisionShapeLocalTranslation.set(0.0f, 0.0f, 0.0f);
	for (auto vertexIdx: indices) {
		const auto& vertex = vertices[vertexIdx];
		collisionShapeLocalTranslation.add(vertex);
	}
	collisionShapeLocalTranslation.scale(1.0f / indices.size());

	// center
	center.set(collisionShapeLocalTranslation).scale(scale);

	// scale collision shape local translation
	collisionShapeLocalTranslation.scale(scale);

	// local transform
	collisionShapeLocalTransform.setPosition(reactphysics3d::Vector3(collisionShapeLocalTranslation.getX(), collisionShapeLocalTranslation.getY(), collisionShapeLocalTranslation.getZ()));

	// transform
	collisionShapeTransform = reactphysics3d::Transform();
}

ConvexMesh::ConvexMesh(ObjectModel* model, const Vector3& scale)
{
	vector<Triangle> triangles;
	model->getTriangles(triangles);

	// determine coplanar faces of model
	unordered_map<int, vector<const Triangle*>> trianglesCoplanar;
	{
		auto triangle1Idx = 0;
		unordered_set<int> trianglesProcessed;
		//
		for (const auto& triangle1: triangles) {
			if (trianglesProcessed.find(triangle1Idx) != trianglesProcessed.end()) {
				triangle1Idx++;
				continue;
			}
			// if not processed add outer triangle
			trianglesCoplanar[triangle1Idx].push_back(&triangle1);
			trianglesProcessed.insert(triangle1Idx);
			//
			auto triangle2Added = 0;
			do {
				auto triangle2Idx = 0;
				triangle2Added = 0;
				for (const auto& triangle2: triangles) {
					// if alreaedy processed skip triangle2
					if (trianglesProcessed.find(triangle2Idx) != trianglesProcessed.end()) {
						triangle2Idx++;
						continue;
					}
					// adjacent?
					auto adjacent = areTrianglesAdjacent(triangle1, triangle2);
					if (adjacent == false) {
						for (auto triangle1CoplanarTriangle: trianglesCoplanar[triangle1Idx]) {
							if (areTrianglesAdjacent(*triangle1CoplanarTriangle, triangle2) == true) {
								adjacent = true;
								break;
							}
						}
					}
					// same plane?
					auto triangle2OnTriangle1Plane =
						isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[0]) &&
						isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[1]) &&
						isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[2]);
					if (adjacent == true && triangle2OnTriangle1Plane == true) {
						trianglesCoplanar[triangle1Idx].push_back(&triangle2);
						// mark as processed
						trianglesProcessed.insert(triangle2Idx);
						// mark as added
						triangle2Added++;
					}
					triangle2Idx++;
				}
			} while (triangle2Added > 0);
			//
			triangle1Idx++;
		}
	}

	// iterate triangles that are coplanar and build a polygon
	for (const auto& [trianglesCoplanarIdx, trianglesCoplanarVector]: trianglesCoplanar) {
		// collect polygon vertices
		vector<Vector3> polygonVertices;

		// determine polygon vertices
		for (auto triangle: trianglesCoplanarVector) {
			for (const auto& triangleVertex: triangle->getVertices()) {
				bool foundVertex = false;
				for (const auto& polygonVertex: polygonVertices) {
					if (polygonVertex.equals(triangleVertex, VERTEX_COMPARE_EPSILON) == true) {
						foundVertex = true;
						break;
					}
				}
				if (foundVertex == false) {
					polygonVertices.push_back(triangleVertex);
				}
			}
		}

		// remove vertices that live on the line 2 other 2 vertices span
		/*
		{
			vector<int> polygonVerticesToRemove;
			Vector3 c;
			for (auto i = 0; i < polygonVertices.size(); i++) {
				for (auto j = 0; j < polygonVertices.size(); j++) {
					if (i == j) continue;
					for (auto k = 0; k < polygonVertices.size(); k++) {
						if (i == k || j == k) continue;
						LineSegment::computeClosestPointOnLineSegment(
							polygonVertices[i],
							polygonVertices[j],
							polygonVertices[k],
							c
						);
						if (polygonVertices[k].equals(c, VERTEX_COMPARE_EPSILON) == true) polygonVerticesToRemove.push_back(k);
					}
				}
			}
			sort(polygonVerticesToRemove.begin(), polygonVerticesToRemove.end());
			polygonVerticesToRemove.erase(unique(polygonVerticesToRemove.begin(), polygonVerticesToRemove.end()), polygonVerticesToRemove.end());
			auto polygonVerticesToRemoved = 0;
			for (auto i: polygonVerticesToRemove) {
				polygonVertices.erase(polygonVertices.begin() + i - polygonVerticesToRemoved);
				polygonVerticesToRemoved++;
			}
		}
		*/

		// check if to skip as combined polygons could already have the current polygon
		if (polygonVertices.size() > 2) {
			auto skip = false;
			auto idx = 0;
			for (auto faceVertexCount: facesVerticesCount) {
				unordered_set<int> foundIndices;
				for (auto i = 0; i < faceVertexCount; i++) {
					auto foundVertex = false;
					for (const auto& polygonVertex: polygonVertices) {
						if (polygonVertex.equals(vertices[indices[idx]], VERTEX_COMPARE_EPSILON) == true) {
							foundIndices.insert(indices[idx]);
							break;
						}
					}
					idx++;
				}
				if (foundIndices.size() == polygonVertices.size()) {
					skip = true;
					break;
				}
			}
			if (skip == true) {
				continue;
			}
		}

		//
		if (polygonVertices.size() < 3) continue;

		// determine polygon center, a point outside of mesh viewing the polygon
		Vector3 polygonCenter;
		for (const auto& polygonVertex: polygonVertices) {
			polygonCenter.add(polygonVertex);
		}
		polygonCenter.scale(1.0f / polygonVertices.size());

		// plane normal
		Vector3 triangle1Edge1;
		Vector3 triangle1Edge2;
		triangle1Edge1.set(trianglesCoplanarVector[0]->getVertices()[1]).sub(trianglesCoplanarVector[0]->getVertices()[0]).normalize();
		triangle1Edge2.set(trianglesCoplanarVector[0]->getVertices()[2]).sub(trianglesCoplanarVector[0]->getVertices()[0]).normalize();
		auto polygonNormal = Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2).normalize();

		// determine polygon vertices order
		vector<int> polygonVerticesOrdered;
		// add first vertex
		polygonVerticesOrdered.push_back(0);

		// then check vertex order if it matches
		// if it matches we have the next vertex
		Vector3 distanceVector;
		// as long as we have vertices left
		while (polygonVerticesOrdered.size() != polygonVertices.size()) {
			// find next vertex with most little
			auto hitVertexAngle = 0.0f;
			auto hitVertexIdx = -1;
			for (int i = 0; i < polygonVertices.size(); i++) {
				// check if already add to ordered vertices list
				if (find(polygonVerticesOrdered.begin(), polygonVerticesOrdered.end(), i) != polygonVerticesOrdered.end()) continue;

				// otherwise check if angle is smaller
				auto angleCurrent = Vector3::computeAngle(
					polygonVertices[0].clone().sub(polygonCenter).normalize(),
					polygonVertices[i].clone().sub(polygonCenter).normalize(),
					polygonNormal
				);
				if (hitVertexIdx == -1 || angleCurrent < hitVertexAngle) {
					hitVertexAngle = angleCurrent;
					hitVertexIdx = i;
				}
			}
			// yep
			polygonVerticesOrdered.push_back(hitVertexIdx);
		}

		/*
		{
			// vertex order
			// 	see: https://stackoverflow.com/questions/14370636/sorting-a-list-of-3d-coplanar-points-to-be-clockwise-or-counterclockwise
			auto& polygonVertexOrderedFirst = polygonVertices[polygonVerticesOrdered[0]];
			auto& polygonVertexOrderedLast = polygonVertices[polygonVerticesOrdered[1]];
			Vector3 ac;
			Vector3 bc;
			ac.set(polygonVertexOrderedFirst).sub(polygonCenter);
			bc.set(polygonVertexOrderedLast).sub(polygonCenter);
			auto acbcCross = Vector3::computeCrossProduct(ac, bc);
			// counter clockwise???
			if ((Vector3::computeDotProduct(polygonNormal, acbcCross) > 0.0f) == false) {
				// yep, reverse
				reverse(begin(polygonVerticesOrdered), end(polygonVerticesOrdered));
			}
		}
		*/

		// add face
		facesVerticesCount.push_back(polygonVerticesOrdered.size());
		for (auto polygonVerticesOrderedIdx: polygonVerticesOrdered) {
			// polygon vertex
			auto& polygonVertex = polygonVertices[polygonVerticesOrderedIdx];

			// check if to insert vertex
			int vertexIdx = 0;
			for (const auto& vertexExisting: vertices) {
				if (vertexExisting.equals(polygonVertex, VERTEX_COMPARE_EPSILON) == true) {
					break;
				}
				vertexIdx++;
			}
			if (vertexIdx == vertices.size()) {
				vertices.push_back(polygonVertex);
			}

			// add index
			indices.push_back(vertexIdx);
		}
	}

	/*
	static int wfObjIdx = 0;

	WFObjWriter wfObjWriter;
	for (const auto& vertex: vertices) wfObjWriter.addVertex(vertex);
	auto faceVertexIdx = 0;
	for (auto& faceVertexCount: facesVerticesCount) {
		vector<int> faceVertexIndices;
		for (auto i = 0; i <  faceVertexCount; i++) {
			faceVertexIndices.push_back(indices[faceVertexIdx++]);
		}
		wfObjWriter.addFace(faceVertexIndices);
	}
	wfObjWriter.write(".", "wfobj." + to_string(wfObjIdx++) + ".obj");
	*/

	// create convex mesh
	setScale(scale);
}

ConvexMesh::ConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale) {
	this->vertices = vertices;
	this->facesVerticesCount = facesVerticesCount;
	this->indices = indices;
	setScale(scale);
}

ConvexMesh::~ConvexMesh() {
	destroyCollisionShape();
}

void ConvexMesh::setScale(const Vector3& scale) {
	// store new scale
	this->scale.set(scale);
	// recreate convex mesh
	createConvexMesh(vertices, facesVerticesCount, indices, scale);
	//
	// generate vertices and indices buffers
	verticesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(vertices.size() * 3 * sizeof(float)));
	indicesByteBuffer = unique_ptr<ByteBuffer>(ByteBuffer::allocate(indices.size() * sizeof(int)));
	auto verticesBuffer = verticesByteBuffer->asFloatBuffer();
	auto indicesBuffer = indicesByteBuffer->asIntBuffer();
	Vector3 vertexTransformed;
	for (const auto& vertex: vertices) {
		vertexTransformed.set(vertex);
		vertexTransformed.sub(center);
		vertexTransformed.scale(scale);
		verticesBuffer.put(vertexTransformed.getArray());
	}
	for (auto index: indices) {
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
}

void ConvexMesh::destroyCollisionShape() {
	if (collisionShape == nullptr) return;
	this->world->physicsCommon.destroyConvexMeshShape(static_cast<reactphysics3d::ConvexMeshShape*>(collisionShape));
	this->world->physicsCommon.destroyConvexMesh(convexMesh);
	polygonVertexArray = nullptr;
	verticesByteBuffer = nullptr;
	indicesByteBuffer = nullptr;
	collisionShape = nullptr;
	convexMesh = nullptr;
	world = nullptr;
}

void ConvexMesh::createCollisionShape(World* world) {
	if (this->world != nullptr && this->world != world) {
		Console::printLine("ConvexMesh::createCollisionShape(): already attached to a world.");
	}
	this->world = world;

	//
	try {
		//
		polygonVertexArray = make_unique<reactphysics3d::PolygonVertexArray>(
			static_cast<uint32_t>(vertices.size()),
			verticesByteBuffer->getBuffer(),
			3 * sizeof(float),
			indicesByteBuffer->getBuffer(),
			sizeof(int),
			static_cast<uint32_t>(faces.size()),
			faces.data(),
			reactphysics3d::PolygonVertexArray::VertexDataType::VERTEX_FLOAT_TYPE,
			reactphysics3d::PolygonVertexArray::IndexDataType::INDEX_INTEGER_TYPE
		);
		vector<reactphysics3d::Message> messages;
		convexMesh = world->physicsCommon.createConvexMesh(*polygonVertexArray.get(), messages);
		// dump messages
		for (const auto& message: messages) {
			auto getMessageTypeText = [](const reactphysics3d::Message& message) -> const string {
				switch (message.type) {
					case reactphysics3d::Message::Type::Error:
						return "ERROR";
					case reactphysics3d::Message::Type::Warning:
						return "WARNING";
					case reactphysics3d::Message::Type::Information:
						return "INFORMATION";
				}
			};
			Console::printLine("ConvexMesh::createCollisionShape(): " + getMessageTypeText(message) + ": " + message.text);
		}
		//
		if (convexMesh == nullptr) {
			throw ExceptionBase("Invalid polyhedron mesh");
		}
		// create convex mesh shape
		collisionShape = world->physicsCommon.createConvexMeshShape(convexMesh);
	} catch (Exception& exception) {
		Console::printLine("ConvexMesh::createCollisionShape(): an error occurred: " + string(exception.what()));
		if (collisionShape != nullptr) {
			this->world->physicsCommon.destroyConvexMeshShape(static_cast<reactphysics3d::ConvexMeshShape*>(collisionShape));
			collisionShape = nullptr;
		}
		if (convexMesh != nullptr) {
			this->world->physicsCommon.destroyConvexMesh(convexMesh);
			convexMesh = nullptr;
		}
		polygonVertexArray = nullptr;
		this->world = nullptr;
	}
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(vertices, facesVerticesCount, indices, scale);
}

const vector<Vector3>& ConvexMesh::getVertices() {
	return vertices;
}
