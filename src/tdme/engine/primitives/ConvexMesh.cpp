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
}

ConvexMesh::ConvexMesh(const vector<Triangle>* triangles)
{
	this->triangles = *triangles;
	createVertices();
	update();
}

ConvexMesh::ConvexMesh(Object3DModel* model) 
{
	model->getFaceTriangles(&triangles);
	createVertices();
	update();
}

void ConvexMesh::createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes, float height)
{
	vector<Triangle> faceTriangles;
	model->getFaceTriangles(&faceTriangles);
	for (auto i = 0; i < faceTriangles.size(); i++) {
		vector<Triangle> convexMeshTriangles;

		// add triangle on top
		convexMeshTriangles.push_back(faceTriangles[i]);

		// add triangle on bottom
		convexMeshTriangles.push_back(faceTriangles[i]);
		(*convexMeshTriangles[1].getVertices())[0].addY(-height);
		(*convexMeshTriangles[1].getVertices())[1].addY(-height);
		(*convexMeshTriangles[1].getVertices())[2].addY(-height);

		// add triangle vertices
		Vector3 triangleVertex0Bottom;
		Vector3 triangleVertex1Bottom;
		Vector3 triangleVertex2Bottom;
		Vector3& triangleVertex0Top = (*faceTriangles[i].getVertices())[0];
		Vector3& triangleVertex1Top = (*faceTriangles[i].getVertices())[1];
		Vector3& triangleVertex2Top = (*faceTriangles[i].getVertices())[2];
		triangleVertex0Bottom.set(triangleVertex0Top).addY(-height);
		triangleVertex1Bottom.set(triangleVertex1Top).addY(-height);
		triangleVertex2Bottom.set(triangleVertex2Top).addY(-height);

		// add bottom top triangles
		//	vertices 0, 2
		convexMeshTriangles.push_back(Triangle(triangleVertex0Top, triangleVertex2Top, triangleVertex0Bottom));
		convexMeshTriangles.push_back(Triangle(triangleVertex0Bottom, triangleVertex2Top, triangleVertex2Bottom));
		//	vertices 0, 1
		convexMeshTriangles.push_back(Triangle(triangleVertex0Top, triangleVertex1Top, triangleVertex0Bottom));
		convexMeshTriangles.push_back(Triangle(triangleVertex0Bottom, triangleVertex1Top, triangleVertex1Bottom));
		//	vertices 1, 2
		convexMeshTriangles.push_back(Triangle(triangleVertex1Top, triangleVertex2Top, triangleVertex1Bottom));
		convexMeshTriangles.push_back(Triangle(triangleVertex1Bottom, triangleVertex2Top, triangleVertex2Bottom));

		// add to convex meshes
		convexMeshes->push_back(ConvexMesh(&convexMeshTriangles));
	}
}

void ConvexMesh::createVertices()
{
	for (auto i = 0; i < triangles.size(); i++) {
		auto triangleVertices = triangles[i].getVertices();
		for (auto j = 0; j < triangleVertices->size(); j++) {
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

vector<Triangle>* ConvexMesh::getTriangles()
{
	return &triangles;
}

void ConvexMesh::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		return;
	}
	auto mesh = dynamic_cast< ConvexMesh* >(original);
	if (mesh->triangles.size() != triangles.size()) {
		return;
	}
	for (auto i = 0; i < triangles.size(); i++) {
		triangles[i].fromBoundingVolume(&mesh->triangles[i]);
	}
	center.set(mesh->center);
	sphereRadius = mesh->sphereRadius;
	update();
}

void ConvexMesh::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		return;
	}
	auto mesh = dynamic_cast< ConvexMesh* >(original);
	if (mesh->triangles.size() != triangles.size()) {
		return;
	}
	for (auto i = 0; i < triangles.size(); i++) {
		auto meshTriangleVertices = mesh->triangles[i].getVertices();
		auto triangleVertices = triangles[i].getVertices();
		transformations->getTransformationsMatrix().multiply((*meshTriangleVertices)[0], (*triangleVertices)[0]);
		transformations->getTransformationsMatrix().multiply((*meshTriangleVertices)[1], (*triangleVertices)[1]);
		transformations->getTransformationsMatrix().multiply((*meshTriangleVertices)[2], (*triangleVertices)[2]);
		triangles[i].update();
	}
	update();
}

void ConvexMesh::computeClosestPointOnBoundingVolume(const Vector3& point, Vector3& closestsPoint) const
{
	if (containsPoint(point) == true) {
		closestsPoint.set(point);
		return;
	}
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
		auto triangle = triangles[i];
		auto triangleVertices = triangle.getVertices();
		triangleEdge1.set((*triangleVertices)[1]).sub((*triangleVertices)[0]).normalize();
		triangleEdge2.set((*triangleVertices)[2]).sub((*triangleVertices)[1]).normalize();
		triangleEdge3.set((*triangleVertices)[0]).sub((*triangleVertices)[2]).normalize();
		Vector3::computeCrossProduct(triangleEdge1, triangleEdge2, triangleNormal).normalize();
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
	for (auto i = 0; i < vertexReferences.size(); i++) {
		vertices[i].set((*triangles[vertexReferences[i][0]].getVertices())[vertexReferences[i][1]]);
	}
	center.set(0.0f, 0.0f, 0.0f);
	for (auto i = 0; i < triangles.size(); i++) {
		auto triangleVertices = triangles[i].getVertices();
		center.add((*triangleVertices)[0]);
		center.add((*triangleVertices)[1]);
		center.add((*triangleVertices)[2]);
	}
	center.scale(1.0f / (triangles.size() * 3.0f));
	this->sphereRadius = 0.0f;
	for (auto i = 0; i < triangles.size(); i++) {
		auto triangleVertices = triangles[i].getVertices();
		for (auto j = 0; j < 3; j++) {
			auto _sphereRadius = tmp.set(center).sub((*triangleVertices)[j]).computeLength();
			if (_sphereRadius > sphereRadius)
				sphereRadius = _sphereRadius;
		}
	}
}

BoundingVolume* ConvexMesh::clone() const
{
	return new ConvexMesh(&triangles);
}
