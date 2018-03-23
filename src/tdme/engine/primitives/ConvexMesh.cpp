#include <tdme/engine/primitives/ConvexMesh.h>

#include <array>
#include <vector>

#include <tdme/engine/Object3DModel.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/SeparatingAxisTheorem.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/Console.h>

using std::array;
using std::vector;

using tdme::engine::primitives::ConvexMesh;
using tdme::engine::Object3DModel;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Matrix4x4;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::Vector3;
using tdme::utils::Console;

ConvexMesh::ConvexMesh()
{
	createVertices();
	update();
	terrain = false;
	terrainHeight = 0.0f;
}

ConvexMesh::ConvexMesh(const vector<Triangle>* triangles, bool terrain, float terrainHeight)
{
	this->triangles = *triangles;
	this->terrain = terrain;
	this->terrainHeight = terrainHeight;
	createVertices();
	update();
}

ConvexMesh::ConvexMesh(Object3DModel* model, bool terrain, float terrainHeight)
{
	this->terrain = terrain;
	this->terrainHeight = terrainHeight;
	model->getFaceTriangles(&triangles);
	createVertices();
	update();
}

void ConvexMesh::createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes, float terrainHeight)
{
	// please note: no optimizations yet
	vector<Triangle> faceTriangles;
	model->getFaceTriangles(&faceTriangles);
	for (auto i = 0; i < faceTriangles.size(); i++) {
		vector<Triangle> convexMeshTriangles;

		// add triangle on top
		convexMeshTriangles.push_back(faceTriangles[i]);

		// add triangle on bottom
		convexMeshTriangles.push_back(faceTriangles[i]);

		// add bottom top triangles
		//	vertices 0, 2
		convexMeshTriangles.push_back(faceTriangles[i]);
		convexMeshTriangles.push_back(faceTriangles[i]);
		//	vertices 0, 1
		convexMeshTriangles.push_back(faceTriangles[i]);
		convexMeshTriangles.push_back(faceTriangles[i]);
		//	vertices 1, 2
		convexMeshTriangles.push_back(faceTriangles[i]);
		convexMeshTriangles.push_back(faceTriangles[i]);

		// add to convex meshes
		convexMeshes->push_back(ConvexMesh(&convexMeshTriangles, true, terrainHeight));
	}
}

void ConvexMesh::createVertices()
{
	vertexReferences.clear();
	vertices.clear();
	// iterate triangles
	for (auto i = 0; i < triangles.size(); i++) {
		auto triangleVertices = triangles[i].getVertices();
		// iterate triangle vertices
		for (auto j = 0; j < triangleVertices->size(); j++) {
			// check if we already have this vertex
			auto haveVertex = false;
			for (auto k = 0; k < vertices.size(); k++) {
				if (vertices.at(k).equals((*triangleVertices)[j]) == true) {
					haveVertex = true;
					break;
				}
			}
			if (haveVertex == false) {
				vertexReferences.push_back({{i, j}});
				vertices.push_back((*triangleVertices)[j]);
			}
		}
	}
}

bool ConvexMesh::isTerrain() {
	return terrain;
}

vector<Triangle>* ConvexMesh::getTriangles()
{
	return &triangles;
}

void ConvexMesh::fromBoundingVolume(BoundingVolume* original)
{
	// check for same type of original
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		return;
	}
	auto mesh = dynamic_cast< ConvexMesh* >(original);
	if (mesh->triangles.size() != triangles.size()) {
		return;
	}
	// set up triangles from original
	for (auto i = 0; i < (terrain == true?Math::min(1, triangles.size()):triangles.size()); i++) {
		triangles[i].fromBoundingVolume(&mesh->triangles[i]);
	}
	// center
	center.set(mesh->center);
	// bounding box
	boundingBox = mesh->boundingBox;
}

void ConvexMesh::fromBoundingVolumeWithTransformations(BoundingVolume* original, const Transformations& transformations)
{
	// check for same type of original
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		return;
	}
	auto mesh = dynamic_cast< ConvexMesh* >(original);
	if (mesh->triangles.size() != triangles.size()) {
		return;
	}
	// set up triangles from original
	for (auto i = 0; i < (terrain == true?Math::min(1, triangles.size()):triangles.size()); i++) {
		triangles[i].fromBoundingVolumeWithTransformations(&mesh->triangles[i], transformations);
	}
	// update
	update();
}

void ConvexMesh::computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestsPoint) const
{
	// check if convex mesh contains point
	if (containsPoint(point) == true) {
		// yep, return it
		closestsPoint.set(point);
		return;
	}
	// otherwise find closests point on triangles
	if (triangles.size() == 0) {
		return;
	}
	Vector3 closestPointOnTriangle;
	Vector3 distanceVector;
	triangles[0].computeClosestPointOnBoundingVolume(point, closestPointOnTriangle);
	auto distance = distanceVector.set(point).sub(closestPointOnTriangle).computeLength();
	closestsPoint.set(closestPointOnTriangle);
	for (auto i = 1; i < triangles.size(); i++) {
		triangles[i].computeClosestPointOnBoundingVolume(point, closestPointOnTriangle);
		auto _distance = distanceVector.set(point).sub(closestPointOnTriangle).computeLength();
		if (_distance < distance) {
			distance = _distance;
			closestsPoint.set(closestPointOnTriangle);
		}
	}
}

bool ConvexMesh::containsPoint(const Vector3& point) const
{
	Vector3 triangleEdge1;
	Vector3 triangleEdge2;
	Vector3 triangleEdge3;
	Vector3 triangleNormal;
	for (auto i = 0; i < triangles.size(); i++) {
		// determine axes to test
		auto triangle = triangles[i];
		auto triangleVertices = triangle.getVertices();
		triangleEdge1.set((*triangleVertices)[1]).sub((*triangleVertices)[0]).normalize();
		triangleEdge2.set((*triangleVertices)[2]).sub((*triangleVertices)[1]).normalize();
		triangleEdge3.set((*triangleVertices)[0]).sub((*triangleVertices)[2]).normalize();
		Vector3::computeCrossProduct(triangleEdge1, triangleEdge2, triangleNormal).normalize();
		// check if projected point is between min and max of projected vertices
		if (SeparatingAxisTheorem::checkPointInVerticesOnAxis(&vertices, point, triangleEdge1) == false)
			return false;
		if (SeparatingAxisTheorem::checkPointInVerticesOnAxis(&vertices, point, triangleEdge2) == false)
			return false;
		if (SeparatingAxisTheorem::checkPointInVerticesOnAxis(&vertices, point, triangleEdge3) == false)
			return false;
		if (SeparatingAxisTheorem::checkPointInVerticesOnAxis(&vertices, point, triangleNormal) == false)
			return false;
	}
	return true;
}

bool ConvexMesh::doesCollideWith(BoundingVolume* bv2, const Vector3& movement, CollisionResponse* collision)
{
	if (dynamic_cast< BoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< BoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< OrientedBoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< OrientedBoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< Sphere* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Sphere* >(bv2), movement, collision);
	} else if (dynamic_cast< Capsule* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Capsule* >(bv2), movement, collision);
	} else if (dynamic_cast< Triangle* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< Triangle* >(bv2), movement, collision);
	} else if (dynamic_cast< ConvexMesh* >(bv2) != nullptr) {
		return CollisionDetection::doCollide(this, dynamic_cast< ConvexMesh* >(bv2), movement, collision);
	} else {
		return false;
	}
}

float ConvexMesh::computeDimensionOnAxis(const Vector3& axis) const
{
	auto dimensionOnAxis = 0.0f;
	for (auto i = 0; i < triangles.size(); i++) {
		auto _dimensionOnAxis = triangles[i].computeDimensionOnAxis(axis);
		if (_dimensionOnAxis > dimensionOnAxis)
			dimensionOnAxis = _dimensionOnAxis;

	}
	return dimensionOnAxis;
}

void ConvexMesh::update()
{
	Vector3 tmp;
	// update terrain mesh if it is one
	if (terrain == true) {
		int triangleIdx = 1;

		// add triangle vertices
		Vector3 triangleVertex0Bottom;
		Vector3 triangleVertex1Bottom;
		Vector3 triangleVertex2Bottom;
		Vector3& triangleVertex0Top = (*triangles[0].getVertices())[0];
		Vector3& triangleVertex1Top = (*triangles[0].getVertices())[1];
		Vector3& triangleVertex2Top = (*triangles[0].getVertices())[2];
		triangleVertex0Bottom.set(triangleVertex0Top).addY(-terrainHeight);
		triangleVertex1Bottom.set(triangleVertex1Top).addY(-terrainHeight);
		triangleVertex2Bottom.set(triangleVertex2Top).addY(-terrainHeight);

		// set up triangle on bottom
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex0Top).addY(-terrainHeight);
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex1Top).addY(-terrainHeight);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex2Top).addY(-terrainHeight);
		triangles[triangleIdx++].update();

		// add bottom top triangles
		//	vertices 0, 2
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex0Top);
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex2Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex0Bottom);
		triangles[triangleIdx++].update();
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex0Bottom);
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex2Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex2Bottom);
		triangles[triangleIdx++].update();

		//	vertices 0, 1
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex0Top);
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex1Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex0Bottom);
		triangles[triangleIdx++].update();
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex0Bottom);
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex1Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex1Bottom);
		triangles[triangleIdx++].update();

		//	vertices 1, 2
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex1Top);
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex2Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex1Bottom);
		triangles[triangleIdx++].update();
		(*triangles[triangleIdx].getVertices())[1].set(triangleVertex1Bottom);
		(*triangles[triangleIdx].getVertices())[0].set(triangleVertex2Top);
		(*triangles[triangleIdx].getVertices())[2].set(triangleVertex2Bottom);
		triangles[triangleIdx++].update();

		//
		createVertices();
	}
	// update vertices
	for (auto i = 0; i < vertexReferences.size(); i++) {
		vertices[i].set((*triangles[vertexReferences[i][0]].getVertices())[vertexReferences[i][1]]);
	}
	// center
	center.set(0.0f, 0.0f, 0.0f);
	for (auto i = 0; i < triangles.size(); i++) {
		center.add(triangles[i].getCenter());
	}
	center.scale(1.0f / triangles.size());
	// bounding box
	boundingBox.getMin().set(center);
	boundingBox.getMax().set(center);
	for (auto& vertex: vertices) {
		for (int i = 0; i < 3; i++) {
			if (vertex[i] < boundingBox.getMin()[i]) boundingBox.getMin()[i] = vertex[i]; else
			if (vertex[i] > boundingBox.getMax()[i]) boundingBox.getMax()[i] = vertex[i];
		}
	}
	boundingBox.update();
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(&triangles, terrain, terrainHeight);
}
