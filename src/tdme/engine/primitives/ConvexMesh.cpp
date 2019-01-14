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
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Math.h>
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
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Triangle;
using tdme::math::Math;
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
	return Math::abs(v1Dotv2v3Cross) < Math::EPSILON;
}

ConvexMesh::ConvexMesh(Object3DModel* model, const Vector3& scale)
{
	vector<Triangle> triangles;
	model->getTriangles(triangles);

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

		// determine polygon vertices
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

		// determine polygon center, a point outside of mesh viewing the polygon
		Vector3 polygonCenter;
		for (auto& polygonVertex: polygonVertices) {
			polygonCenter.add(polygonVertex);
		}
		polygonCenter.scale(1.0f / polygonVertices.size());

		// determine polygon vertices order
		vector<int> polygonVerticesOrdered;
		// add first vertex
		polygonVerticesOrdered.push_back(0);

		// plane normal
		Vector3 triangle1Edge1;
		Vector3 triangle1Edge2;
		Vector3 polygonNormal;
		triangle1Edge1.set(polygonVertices[1]).sub(polygonVertices[0]);
		triangle1Edge2.set(polygonVertices[2]).sub(polygonVertices[0]);
		Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2, polygonNormal).normalize();
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

		{
			// vertex order
			// 	see: https://stackoverflow.com/questions/14370636/sorting-a-list-of-3d-coplanar-points-to-be-clockwise-or-counterclockwise
			auto& polygonVertexOrderedFirst = polygonVertices[polygonVerticesOrdered[0]];
			auto& polygonVertexOrderedLast = polygonVertices[polygonVerticesOrdered[1]];
			Vector3 ac;
			Vector3 bc;
			Vector3 acbcCross;
			ac.set(polygonVertexOrderedFirst).sub(polygonCenter);
			bc.set(polygonVertexOrderedLast).sub(polygonCenter);
			Vector3::computeCrossProduct(ac, bc, acbcCross);
			// counter clockwise???
			if ((Vector3::computeDotProduct(polygonNormal, acbcCross) > 0.0f) == false) {
				// yep, reverse
				reverse(begin(polygonVerticesOrdered), end(polygonVerticesOrdered));
			}
		}

		// add face
		facesVerticesCount.push_back(polygonVerticesOrdered.size());
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
	setScale(scale);
}

ConvexMesh::ConvexMesh(const vector<Vector3>& vertices, const vector<int>& facesVerticesCount, const vector<int>& indices, const Vector3& scale) {
	this->vertices = vertices;
	this->facesVerticesCount = facesVerticesCount;
	this->indices = indices;
	setScale(scale);
}

void ConvexMesh::setScale(const Vector3& scale) {
	// store new scale
	this->scale.set(scale);
	// recreate convex mesh
	createConvexMesh(vertices, facesVerticesCount, indices, scale);
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(vertices, facesVerticesCount, indices, scale);
}

const vector<Vector3>& ConvexMesh::getVertices() {
	return vertices;
}
