// Generated from /tdme/src/tdme/engine/primitives/ConvexMesh.java
#include <tdme/engine/primitives/ConvexMesh.h>

#include <vector>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
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
#include <tdme/utils/_Console.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;

using tdme::engine::primitives::ConvexMesh;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
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
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::BoundingVolume, ::java::lang::ObjectArray > BoundingVolumeArray;
typedef ::SubArray< ::tdme::engine::primitives::Triangle, ::java::lang::ObjectArray, BoundingVolumeArray > TriangleArray;
}  // namespace primitives
}  // namespace engine

namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

ConvexMesh::ConvexMesh(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

ConvexMesh::ConvexMesh(TriangleArray* triangles) 
	: ConvexMesh(*static_cast< ::default_init_tag* >(0))
{
	ctor(triangles);
}

ConvexMesh::ConvexMesh(Object3DModel* model) 
	: ConvexMesh(*static_cast< ::default_init_tag* >(0))
{
	ctor(model);
}

void ConvexMesh::createTerrainConvexMeshes(Object3DModel* model, vector<ConvexMesh>* convexMeshes)
{
	clinit();
	vector<Triangle> faceTriangles;
	model->getFaceTriangles(&faceTriangles);
	for (auto i = 0; i < faceTriangles.size(); i++) {
		auto convexMeshTriangles = new TriangleArray(2);
		convexMeshTriangles->set(0, faceTriangles[i].clone());
		convexMeshTriangles->set(1, faceTriangles[i].clone());
		(*(*convexMeshTriangles)[1]->getVertices())[0]->addY(-1.0f);
		(*(*convexMeshTriangles)[1]->getVertices())[1]->addY(-1.0f);
		(*(*convexMeshTriangles)[1]->getVertices())[2]->addY(-1.0f);
		convexMeshes->push_back(ConvexMesh(convexMeshTriangles));
	}
}

void ConvexMesh::ctor(TriangleArray* triangles)
{
	super::ctor();
	this->center = new Vector3();
	this->distanceVector = new Vector3();
	this->closestsPoint = new Vector3();
	this->triangles = triangles;
	this->triangleEdge1 = new Vector3();
	this->triangleEdge2 = new Vector3();
	this->triangleEdge3 = new Vector3();
	this->triangleNormal = new Vector3();
	update();
	createVertices();
}

void ConvexMesh::ctor(Object3DModel* model)
{
	super::ctor();
	center = new Vector3();
	distanceVector = new Vector3();
	closestsPoint = new Vector3();
	vector<Triangle> faceTriangles;
	model->getFaceTriangles(&faceTriangles);
	triangles = new TriangleArray(faceTriangles.size());
	int faceTriangleIdx = 0;
	for (auto& triangle: faceTriangles) {
		triangles->set(faceTriangleIdx++, triangle.clone());
	}
	triangleEdge1 = new Vector3();
	triangleEdge2 = new Vector3();
	triangleEdge3 = new Vector3();
	triangleNormal = new Vector3();
	update();
	createVertices();
}

void ConvexMesh::createVertices()
{
	for (auto i = 0; i < triangles->length; i++) {
		for (auto j = 0; j < (*triangles)[i]->vertices.size(); j++) {
			auto haveVertex = false;
			for (auto k = 0; k < vertices.size(); k++) {
				if (vertices.at(k)->equals((*triangles)[i]->vertices[j]) == true) {
					haveVertex = true;
				}
			}
			if (haveVertex == false)
				vertices.push_back((*triangles)[i]->vertices[j]);
		}
	}
}

TriangleArray* ConvexMesh::getTriangles()
{
	return triangles;
}

vector<Vector3*>* ConvexMesh::getVertices()
{
	return &vertices;
}

void ConvexMesh::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Mesh::fromBoundingVolume(): original is not of same type"_j));
		return;
	}
	auto mesh = java_cast< ConvexMesh* >(original);
	if (mesh->triangles->length != triangles->length) {
		_Console::println(static_cast< Object* >(u"Mesh::fromBoundingVolume(): triangles count mismatch"_j));
		return;
	}
	for (auto i = 0; i < triangles->length; i++) {
		(*triangles)[i]->fromBoundingVolume((*mesh->triangles)[i]);
	}
	center->set(mesh->center);
	sphereRadius = mesh->sphereRadius;
}

void ConvexMesh::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< ConvexMesh* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"Mesh::fromBoundingVolume(): original is not of same type"_j));
		return;
	}
	auto mesh = java_cast< ConvexMesh* >(original);
	if (mesh->triangles->length != triangles->length) {
		_Console::println(static_cast< Object* >(u"Mesh::fromBoundingVolume(): triangles count mismatch"_j));
		return;
	}
	for (auto i = 0; i < triangles->length; i++) {
		transformations->getTransformationsMatrix()->multiply((*mesh->triangles)[i]->vertices[0], (*triangles)[i]->vertices[0]);
		transformations->getTransformationsMatrix()->multiply((*mesh->triangles)[i]->vertices[1], (*triangles)[i]->vertices[1]);
		transformations->getTransformationsMatrix()->multiply((*mesh->triangles)[i]->vertices[2], (*triangles)[i]->vertices[2]);
		(*triangles)[i]->update();
	}
	update();
}

void ConvexMesh::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestsPoint)
{
	if (containsPoint(point) == true) {
		closestsPoint->set(point);
		return;
	}
	if (triangles->length == 0) {
		return;
	}
	(*triangles)[0]->computeClosestPointOnBoundingVolume(point, this->closestsPoint);
	auto distance = distanceVector->set(point)->sub(this->closestsPoint)->computeLength();
	closestsPoint->set(this->closestsPoint);
	for (auto i = 1; i < triangles->length; i++) {
		(*triangles)[i]->computeClosestPointOnBoundingVolume(point, this->closestsPoint);
		auto _distance = distanceVector->set(point)->sub(this->closestsPoint)->computeLength();
		if (_distance < distance) {
			distance = _distance;
			closestsPoint->set(this->closestsPoint);
		}
	}
}

bool ConvexMesh::containsPoint(Vector3* point)
{
	for (auto i = 0; i < triangles->length; i++) {
		auto triangle = (*triangles)[i];
		auto triangleVertices = triangle->getVertices();
		triangleEdge1->set((*triangleVertices)[1])->sub((*triangleVertices)[0])->normalize();
		triangleEdge2->set((*triangleVertices)[2])->sub((*triangleVertices)[1])->normalize();
		triangleEdge3->set((*triangleVertices)[0])->sub((*triangleVertices)[2])->normalize();
		Vector3::computeCrossProduct(triangleEdge1, triangleEdge2, triangleNormal)->normalize();
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

bool ConvexMesh::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
{
	if (dynamic_cast< BoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< BoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< OrientedBoundingBox* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< OrientedBoundingBox* >(bv2), movement, collision);
	} else if (dynamic_cast< Sphere* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Sphere* >(bv2), movement, collision);
	} else if (dynamic_cast< Capsule* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Capsule* >(bv2), movement, collision);
	} else if (dynamic_cast< Triangle* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< Triangle* >(bv2), movement, collision);
	} else if (dynamic_cast< ConvexMesh* >(bv2) != nullptr) {
		return CollisionDetection::getInstance()->doCollide(this, java_cast< ConvexMesh* >(bv2), movement, collision);
	} else {
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"Capsule::doesCollideWith(): unsupported bounding volume 2: "_j)->append(static_cast< Object* >(bv2))->toString()));
		return false;
	}
}

Vector3* ConvexMesh::getCenter()
{
	return center;
}

float ConvexMesh::getSphereRadius()
{
	return sphereRadius;
}

float ConvexMesh::computeDimensionOnAxis(Vector3* axis)
{
	auto dimensionOnAxis = 0.0f;
	for (auto i = 0; i < triangles->length; i++) {
		auto _dimensionOnAxis = (*triangles)[i]->computeDimensionOnAxis(axis);
		if (_dimensionOnAxis > dimensionOnAxis)
			dimensionOnAxis = _dimensionOnAxis;

	}
	return dimensionOnAxis;
}

void ConvexMesh::update()
{
	center->set(0.0f, 0.0f, 0.0f);
	for (auto i = 0; i < triangles->length; i++) {
		center->add((*triangles)[i]->vertices[0]);
		center->add((*triangles)[i]->vertices[1]);
		center->add((*triangles)[i]->vertices[2]);
	}
	center->scale(1.0f / (triangles->length * 3.0f));
	this->sphereRadius = 0.0f;
	for (auto i = 0; i < triangles->length; i++) 
	for (auto j = 0; j < 3; j++) {
		auto _sphereRadius = distanceVector->set(center)->sub((*triangles)[i]->vertices[j])->computeLength();
		if (_sphereRadius > sphereRadius)
			sphereRadius = _sphereRadius;
	}
}

BoundingVolume* ConvexMesh::clone()
{
	auto triangles = new TriangleArray(this->triangles->length);
	for (auto i = 0; i < this->triangles->length; i++) {
		triangles->set(i, java_cast< Triangle* >((*this->triangles)[i]->clone()));
	}
	return new ConvexMesh(triangles);
}

String* ConvexMesh::toString()
{
	return ::java::lang::StringBuilder().append(u"ConvexMesh [center="_j)
		/*
		->append(static_cast< Object* >(center))
		*/
		->append(u", sphereRadius="_j)
		->append(sphereRadius)
		->append(u", triangles="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(triangles)))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ConvexMesh::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.ConvexMesh", 33);
    return c;
}

java::lang::Class* ConvexMesh::getClass0()
{
	return class_();
}

