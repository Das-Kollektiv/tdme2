#include <tdme/engine/primitives/ConvexMesh.h>

#include <algorithm>
#include <array>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>

#include <ext/reactphysics3d/src/collision/shapes/ConvexMeshShape.h>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/model/ModelHelper.h>
#include <tdme/engine/model/ModelHelper_VertexOrder.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/Float.h>

using std::array;
using std::find;
using std::reverse;
using std::map;
using std::string;
using std::to_string;
using std::unordered_set;
using std::vector;

using tdme::engine::primitives::ConvexMesh;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::model::ModelHelper;
using tdme::engine::model::ModelHelper_VertexOrder;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::math::Math;
using tdme::math::MathTools;
using tdme::math::Vector3;
using tdme::utils::Console;
using tdme::utils::Float;

ConvexMesh::ConvexMesh()
{
}

bool ConvexMesh::isVertexOnTrianglePlane(Triangle& triangle, const Vector3& vertex) {
	// see: http://www.ambrsoft.com/TrigoCalc/Plan3D/PointsCoplanar.htm
	Vector3 v1;
	Vector3 v2;
	Vector3 v3;
	Vector3 v2v3Cross;
	v1.set(triangle.getVertices()[1]).sub(triangle.getVertices()[0]);
	v2.set(triangle.getVertices()[2]).sub(triangle.getVertices()[0]);
	v3.set(vertex).sub(triangle.getVertices()[0]);
	auto v1Dotv2v3Cross = Vector3::computeDotProduct(v1, Vector3::computeCrossProduct(v2, v3, v2v3Cross));
	// What is best threshold here?
	return Math::abs(v1Dotv2v3Cross) < MathTools::EPSILON;
}

ConvexMesh::ConvexMesh(Object3DModel* model)
{
	vector<Triangle> triangles;
	model->getFaceTriangles(&triangles);

	// determine coplanar faces of model
	map<int, vector<Triangle*>> trianglesCoplanar;
	{
		auto triangle1Idx = 0;
		unordered_set<int> trianglesProcessed;
		for (auto& triangle1: triangles) {
			if (trianglesProcessed.find(triangle1Idx) != trianglesProcessed.end()) {
				triangle1Idx++;
				continue;
			}
			trianglesCoplanar[triangle1Idx].push_back(&triangle1);
			trianglesProcessed.insert(triangle1Idx);
			auto triangle2Idx = 0;
			for (auto& triangle2: triangles) {
				if (trianglesProcessed.find(triangle2Idx) != trianglesProcessed.end()) {
					triangle2Idx++;
					continue;
				}
				auto triangle2OnTriangle1Plane =
					isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[0]) &&
					isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[1]) &&
					isVertexOnTrianglePlane(triangle1, triangle2.getVertices()[2]);
				if (triangle2OnTriangle1Plane == true) {
					trianglesCoplanar[triangle1Idx].push_back(&triangle2);
					trianglesProcessed.insert(triangle2Idx);
				}
				triangle2Idx++;
			}
			triangle1Idx++;
		}
	}

	// iterate triangles that are coplanar and build a polygon
	for (auto trianglesCoplanarIt: trianglesCoplanar) {
		// collect polygon vertices
		vector<Vector3> polygonVertices;
		auto trianglesCoplanarId = trianglesCoplanarIt.first;
		auto& trianglesCoplanarVector = trianglesCoplanarIt.second;
		for (auto triangle: trianglesCoplanarVector) {
			for (auto& triangleVertex: triangle->getVertices()) {
				bool foundVertex = false;
				for (auto& polygonVertex: polygonVertices) {
					if (polygonVertex.equals(triangleVertex) == true) {
						foundVertex = true;
						break;
					}
				}
				if (foundVertex == false) {
					polygonVertices.push_back(triangleVertex);
				}
			}
		}

		// determine polygon vertices order
		vector<int> polygonVerticesOrdered;
		// add vertices of first triangles which should always be in clockwise order
		polygonVerticesOrdered.push_back(0);
		polygonVerticesOrdered.push_back(1);
		polygonVerticesOrdered.push_back(2);

		// then check vertex order if it matches
		// if it matches we have the next vertex
		Vector3 distanceVector;
		// as long as we have vertices left
		while (polygonVerticesOrdered.size() != polygonVertices.size()) {
			auto& polygonVerticesOrderedLast = polygonVertices[polygonVerticesOrdered[polygonVerticesOrdered.size() - 1]];
			// iterate polygon vertices to find next match to last vertex
			bool hitFound = false;
			vector<int> hitVerticesNoMatch;
			while (hitFound == false) {
				// find next closest vertex
				float hitVertexMinDistance;
				float hitVertexIdx = -1;
				for (int i = 0; i < polygonVertices.size(); i++) {
					// check if already add to ordered vertices list
					if (find(polygonVerticesOrdered.begin(), polygonVerticesOrdered.end(), i) != polygonVerticesOrdered.end()) continue;
					// check if its a no match
					if (find(hitVerticesNoMatch.begin(), hitVerticesNoMatch.end(), i) != hitVerticesNoMatch.end()) continue;

					// otherwise check if its closer than previous hit
					auto distanceCurrent = distanceVector.set(polygonVertices[i]).sub(polygonVerticesOrderedLast).computeLength();
					if (hitVertexIdx == -1 || distanceCurrent < hitVertexMinDistance) {
						hitVertexMinDistance = distanceCurrent;
						hitVertexIdx = i;
					}
				}
				// exit if no hit was found, should never happen
				if (hitVertexIdx == -1) return;

				// collect current ordered vertices
				vector<Vector3> vertexOrderVertices;
				for (auto polygonVerticesOrderedIdx: polygonVerticesOrdered) {
					vertexOrderVertices.push_back(polygonVertices[polygonVerticesOrderedIdx]);
				}
				// and add current next hit
				vertexOrderVertices.push_back(polygonVertices[hitVertexIdx]);

				// determine order
				auto vertexOrder = ModelHelper::determineVertexOrder(vertexOrderVertices);

				// if we have clockwise order everything is ok and we found a hit
				if (vertexOrder == ModelHelper_VertexOrder::CLOCKWISE) {
					hitFound = true;
					polygonVerticesOrdered.push_back(hitVertexIdx);
				} else {
					// otherwise add to list of no matches
					hitVerticesNoMatch.push_back(hitVertexIdx);
				}
			}
		}

		// reverse if we want counter clockwise order
		// reverse(std::begin(polygonVerticesOrdered), std::end(polygonVerticesOrdered));
		for (auto polygonVerticesOrderedIdx: polygonVerticesOrdered) {
			// polygon vertex
			auto& polygonVertex = polygonVertices[polygonVerticesOrderedIdx];

			// check if to insert vertex
			int vertexIdx = 0;
			for (auto& vertexExisting: vertices) {
				if (vertexExisting.equals(polygonVertex) == true) {
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

	// create convex mesh
	createConvexMesh(vertices, facesVerticesCount, indices);
}

ConvexMesh::ConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices) {
	this->vertices = vertices;
	this->facesVerticesCount = facesVerticesCount;
	this->indices = indices;

	// create convex mesh
	createConvexMesh(vertices, facesVerticesCount, indices);
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(vertices, facesVerticesCount, indices);
}

const vector<Vector3>& ConvexMesh::getVertices() {
	return vertices;
}
