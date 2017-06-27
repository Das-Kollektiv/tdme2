// Generated from /tdme/src/tdme/engine/primitives/BoundingBox.java
#include <tdme/engine/primitives/BoundingBox.h>

#include <java/io/Serializable.h>
#include <java/lang/ArrayStoreException.h>
#include <java/lang/ClassCastException.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::primitives::BoundingBox;
using java::io::Serializable;
using java::lang::ArrayStoreException;
using java::lang::ClassCastException;
using java::lang::Cloneable;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::Matrix4x4;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
}  // namespace lang
}  // namespace java

namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

BoundingBox::BoundingBox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

BoundingBox::BoundingBox() 
	: BoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

BoundingBox::BoundingBox(BoundingBox* boundingBox) 
	: BoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor(boundingBox);
}

BoundingBox::BoundingBox(Vector3* min, Vector3* max) 
	: BoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor(min,max);
}

int32_tArrayArray* BoundingBox::facesVerticesIndexes;

BoundingVolume* BoundingBox::createBoundingVolume(Vector3* min, Vector3* max)
{
	clinit();
	return new BoundingBox(min, max);
}

void BoundingBox::ctor()
{
	super::ctor();
	min = new Vector3();
	max = new Vector3();
	center = new Vector3();
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	halfExtension = new Vector3();
	update();
}

void BoundingBox::ctor(BoundingBox* boundingBox)
{
	super::ctor();
	this->min = boundingBox->min->clone();
	this->max = boundingBox->max->clone();
	this->center = new Vector3();
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	halfExtension = new Vector3();
	update();
}

void BoundingBox::ctor(Vector3* min, Vector3* max)
{
	super::ctor();
	this->min = min;
	this->max = max;
	this->center = new Vector3();
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	halfExtension = new Vector3();
	update();
}

Vector3* BoundingBox::getMin()
{
	return min;
}

Vector3* BoundingBox::getMax()
{
	return max;
}

Vector3Array* BoundingBox::getVertices()
{
	return vertices;
}

int32_tArrayArray* BoundingBox::getFacesVerticesIndexes()
{
	clinit();
	return facesVerticesIndexes;
}

void BoundingBox::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< BoundingBox* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"BoundingBox::fromBoundingVolume: original is not of same type"_j));
		return;
	}
	auto boundingBox = java_cast< BoundingBox* >(original);
	min->set(boundingBox->min);
	max->set(boundingBox->max);
	center->set(boundingBox->center);
	for (auto i = 0; i < vertices->length; i++) 
				(*vertices)[i]->set((*boundingBox->vertices)[i]);

}

void BoundingBox::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< BoundingBox* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"BoundingBox::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto boundingBox = java_cast< BoundingBox* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	auto _vertices = boundingBox->getVertices();
	for (auto i = 0; i < vertices->length; i++) {
		transformationsMatrix->multiply((*_vertices)[i], (*vertices)[i]);
	}
	auto vertexXYZ = (*vertices)[0]->getArray();
	float minX = (*vertexXYZ)[0], minY = (*vertexXYZ)[1], minZ = (*vertexXYZ)[2];
	float maxX = (*vertexXYZ)[0], maxY = (*vertexXYZ)[1], maxZ = (*vertexXYZ)[2];
	for (auto vertexIndex = 1; vertexIndex < vertices->length; vertexIndex++) {
		auto vertex = (*vertices)[vertexIndex];
		vertexXYZ = vertex->getArray();
		if ((*vertexXYZ)[0] < minX)
			minX = (*vertexXYZ)[0];

		if ((*vertexXYZ)[1] < minY)
			minY = (*vertexXYZ)[1];

		if ((*vertexXYZ)[2] < minZ)
			minZ = (*vertexXYZ)[2];

		if ((*vertexXYZ)[0] > maxX)
			maxX = (*vertexXYZ)[0];

		if ((*vertexXYZ)[1] > maxY)
			maxY = (*vertexXYZ)[1];

		if ((*vertexXYZ)[2] > maxZ)
			maxZ = (*vertexXYZ)[2];

	}
	min->set(minX, minY, minZ);
	max->set(maxX, maxY, maxZ);
	update();
}

void BoundingBox::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	auto pointXYZ = point->getArray();
	auto minXYZ = min->getArray();
	auto maxXYZ = max->getArray();
	auto closestX = (*pointXYZ)[0] < (*minXYZ)[0] ? (*minXYZ)[0] : (*pointXYZ)[0] > (*maxXYZ)[0] ? (*maxXYZ)[0] : (*pointXYZ)[0];
	auto closestY = (*pointXYZ)[1] < (*minXYZ)[1] ? (*minXYZ)[1] : (*pointXYZ)[1] > (*maxXYZ)[1] ? (*maxXYZ)[1] : (*pointXYZ)[1];
	auto closestZ = (*pointXYZ)[2] < (*minXYZ)[2] ? (*minXYZ)[2] : (*pointXYZ)[2] > (*maxXYZ)[2] ? (*maxXYZ)[2] : (*pointXYZ)[2];
	closestPoint->set(closestX, closestY, closestZ);
}

bool BoundingBox::containsPoint(Vector3* point)
{
	auto pointXYZ = point->getArray();
	auto minXYZ = min->getArray();
	auto maxXYZ = max->getArray();
	for (auto i = 0; i < 3; i++) {
		if ((*pointXYZ)[i] < (*minXYZ)[i])
			return false;

		if ((*pointXYZ)[i] > (*maxXYZ)[i])
			return false;

	}
	return true;
}

bool BoundingBox::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
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
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"BoundingBox::doesCollideWith(): unsupported bounding volume 2: "_j)->append(static_cast< Object* >(bv2))->toString()));
		return false;
	}
}

Vector3* BoundingBox::getCenter()
{
	return center;
}

float BoundingBox::getSphereRadius()
{
	return sphereRadius;
}

float BoundingBox::computeDimensionOnAxis(Vector3* axis)
{
	auto vertexOnAxis = Vector3::computeDotProduct((*vertices)[0], axis);
	auto min = vertexOnAxis;
	auto max = vertexOnAxis;
	for (auto i = 1; i < vertices->length; i++) {
		vertexOnAxis = Vector3::computeDotProduct((*vertices)[i], axis);
		if (vertexOnAxis < min)
			min = vertexOnAxis;

		if (vertexOnAxis > max)
			max = vertexOnAxis;

	}
	return Math::abs(max - min);
}

void BoundingBox::update()
{
	auto minXYZ = min->getArray();
	auto maxXYZ = max->getArray();
	(*vertices)[0]->set((*minXYZ)[0], (*minXYZ)[1], (*minXYZ)[2]);
	(*vertices)[1]->set((*maxXYZ)[0], (*minXYZ)[1], (*minXYZ)[2]);
	(*vertices)[2]->set((*maxXYZ)[0], (*maxXYZ)[1], (*minXYZ)[2]);
	(*vertices)[3]->set((*minXYZ)[0], (*maxXYZ)[1], (*minXYZ)[2]);
	(*vertices)[4]->set((*minXYZ)[0], (*minXYZ)[1], (*maxXYZ)[2]);
	(*vertices)[5]->set((*maxXYZ)[0], (*minXYZ)[1], (*maxXYZ)[2]);
	(*vertices)[6]->set((*maxXYZ)[0], (*maxXYZ)[1], (*maxXYZ)[2]);
	(*vertices)[7]->set((*minXYZ)[0], (*maxXYZ)[1], (*maxXYZ)[2]);
	center->set(min)->add(max)->scale(0.5f);
	halfExtension->set(max)->sub(min)->scale(0.5f);
	sphereRadius = halfExtension->computeLength();
}

BoundingVolume* BoundingBox::clone()
{
	return new BoundingBox(min->clone(), max->clone());
}

String* BoundingBox::toString()
{
	return ::java::lang::StringBuilder().append(u"BoundingBox [min="_j)->append(static_cast< Object* >(min))
		->append(u", max="_j)
		->append(static_cast< Object* >(max))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* BoundingBox::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.BoundingBox", 34);
    return c;
}

void BoundingBox::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		facesVerticesIndexes = (new int32_tArrayArray({
			(new int32_tArray({
			0,
			4,
			7
		})),
			(new int32_tArray({
			7,
			3,
			0
		})),
			(new int32_tArray({
			6,
			5,
			1
		})),
			(new int32_tArray({
			1,
			2,
			6
		})),
			(new int32_tArray({
			5,
			4,
			0
		})),
			(new int32_tArray({
			0,
			1,
			5
		})),
			(new int32_tArray({
			3,
			7,
			6
		})),
			(new int32_tArray({
			6,
			2,
			3
		})),
			(new int32_tArray({
			2,
			1,
			0
		})),
			(new int32_tArray({
			0,
			3,
			2
		})),
			(new int32_tArray({
			4,
			5,
			6
		})),
			(new int32_tArray({
			6,
			7,
			4
		}))
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* BoundingBox::getClass0()
{
	return class_();
}

