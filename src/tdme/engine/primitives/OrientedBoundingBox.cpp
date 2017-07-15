// Generated from /tdme/src/tdme/engine/primitives/OrientedBoundingBox.java
#include <tdme/engine/primitives/OrientedBoundingBox.h>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/util/Arrays.h>
#include <tdme/engine/Transformations.h>
#include <tdme/engine/physics/CollisionDetection.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Matrix4x4.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::primitives::OrientedBoundingBox;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Math;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using java::util::Arrays;
using tdme::engine::Transformations;
using tdme::engine::physics::CollisionDetection;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::MathTools;
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
    return t;
}

OrientedBoundingBox::OrientedBoundingBox(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

OrientedBoundingBox::OrientedBoundingBox(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension) 
	: OrientedBoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor(center,axis0,axis1,axis2,halfExtension);
}

OrientedBoundingBox::OrientedBoundingBox(BoundingBox* bb) 
	: OrientedBoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor(bb);
}

OrientedBoundingBox::OrientedBoundingBox() 
	: OrientedBoundingBox(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void OrientedBoundingBox::init()
{
	axis = new Vector3();
	axisTransformed = new Vector3Array({
		new Vector3(),
		new Vector3(),
		new Vector3()
	});
	direction = new Vector3();
	scale = new Vector3();
}

Vector3* OrientedBoundingBox::AABB_AXIS_X;

Vector3* OrientedBoundingBox::AABB_AXIS_Y;

Vector3* OrientedBoundingBox::AABB_AXIS_Z;

int32_tArrayArray* OrientedBoundingBox::facesVerticesIndexes;

BoundingVolume* OrientedBoundingBox::createBoundingVolume(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	clinit();
	return new OrientedBoundingBox(center, axis0, axis1, axis2, halfExtension);
}

void OrientedBoundingBox::ctor(Vector3* center, Vector3* axis0, Vector3* axis1, Vector3* axis2, Vector3* halfExtension)
{
	super::ctor();
	init();
	this->center = center;
	this->axes = new Vector3Array(3);
	this->axes->set(0, axis0);
	this->axes->set(1, axis1);
	this->axes->set(2, axis2);
	this->halfExtension = halfExtension;
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	update();
}

void OrientedBoundingBox::ctor(BoundingBox* bb)
{
	super::ctor();
	init();
	this->halfExtension = (new Vector3())->set(bb->getMax())->sub(bb->getMin())->scale(0.5f);
	this->center = (new Vector3())->set(bb->getMin())->add(halfExtension);
	this->axes = new Vector3Array(3);
	this->axes->set(0, AABB_AXIS_X->clone());
	this->axes->set(1, AABB_AXIS_Y->clone());
	this->axes->set(2, AABB_AXIS_Z->clone());
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	update();
}

void OrientedBoundingBox::ctor()
{
	super::ctor();
	init();
	this->halfExtension = new Vector3(0.0f, 0.0f, 0.0f);
	this->center = new Vector3(0.0f, 0.0f, 0.0f);
	this->axes = new Vector3Array(3);
	this->axes->set(0, AABB_AXIS_X->clone());
	this->axes->set(1, AABB_AXIS_Y->clone());
	this->axes->set(2, AABB_AXIS_Z->clone());
	this->vertices = new Vector3Array(8);
	for (auto i = 0; i < vertices->length; i++) {
		vertices->set(i, new Vector3());
	}
	update();
}

Vector3* OrientedBoundingBox::getCenter()
{
	return center;
}

float OrientedBoundingBox::getSphereRadius()
{
	return sphereRadius;
}

Vector3Array* OrientedBoundingBox::getAxes()
{
	return axes;
}

Vector3* OrientedBoundingBox::getHalfExtension()
{
	return halfExtension;
}

void OrientedBoundingBox::fromBoundingBox(BoundingBox* bb)
{
	this->halfExtension->set(bb->getMax())->sub(bb->getMin())->scale(0.5f);
	this->center->set(bb->getMin())->add(halfExtension);
	(*this->axes)[0]->set(AABB_AXIS_X);
	(*this->axes)[1]->set(AABB_AXIS_Y);
	(*this->axes)[2]->set(AABB_AXIS_Z);
	update();
}

void OrientedBoundingBox::fromOrientedBoundingBox(OrientedBoundingBox* obb)
{
	this->halfExtension->set(obb->halfExtension);
	this->center->set(obb->center);
	(*this->axes)[0]->set((*obb->axes)[0]);
	(*this->axes)[1]->set((*obb->axes)[1]);
	(*this->axes)[2]->set((*obb->axes)[2]);
	update();
}

void OrientedBoundingBox::fromBoundingVolume(BoundingVolume* original)
{
	if (dynamic_cast< OrientedBoundingBox* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"OrientedBoundingBox::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto obb = java_cast< OrientedBoundingBox* >(original);
	center->set(obb->center);
	for (auto i = 0; i < axes->length; i++) 
				(*axes)[i]->set((*obb->axes)[i]);

	halfExtension->set(obb->halfExtension);
	for (auto i = 0; i < vertices->length; i++) 
				(*vertices)[i]->set((*obb->vertices)[i]);

}

void OrientedBoundingBox::fromBoundingVolumeWithTransformations(BoundingVolume* original, Transformations* transformations)
{
	if (dynamic_cast< OrientedBoundingBox* >(original) != nullptr == false) {
		_Console::println(static_cast< Object* >(u"OrientedBoundingBox::fromBoundingVolumeWithTransformations(): original is not of same type"_j));
		return;
	}
	auto obb = java_cast< OrientedBoundingBox* >(original);
	auto transformationsMatrix = transformations->getTransformationsMatrix();
	transformationsMatrix->multiply(obb->center, center);
	transformationsMatrix->multiplyNoTranslation((*obb->axes)[0], (*axisTransformed)[0]);
	transformationsMatrix->multiplyNoTranslation((*obb->axes)[1], (*axisTransformed)[1]);
	transformationsMatrix->multiplyNoTranslation((*obb->axes)[2], (*axisTransformed)[2]);
	(*axes)[0]->set((*axisTransformed)[0])->normalize();
	(*axes)[1]->set((*axisTransformed)[1])->normalize();
	(*axes)[2]->set((*axisTransformed)[2])->normalize();
	halfExtension->set(obb->halfExtension);
	halfExtension->scale(scale->set((*axisTransformed)[0]->computeLength(), (*axisTransformed)[1]->computeLength(), (*axisTransformed)[2]->computeLength()));
	update();
}

void OrientedBoundingBox::update()
{
	auto halfExtensionXYZ = halfExtension->getArray();
	(*vertices)[0]->set(center);
	(*vertices)[0]->add(axis->set((*axes)[0])->scale(-(*halfExtensionXYZ)[0]));
	(*vertices)[0]->add(axis->set((*axes)[1])->scale(-(*halfExtensionXYZ)[1]));
	(*vertices)[0]->add(axis->set((*axes)[2])->scale(-(*halfExtensionXYZ)[2]));
	(*vertices)[1]->set(center);
	(*vertices)[1]->add(axis->set((*axes)[0])->scale(+(*halfExtensionXYZ)[0]));
	(*vertices)[1]->add(axis->set((*axes)[1])->scale(-(*halfExtensionXYZ)[1]));
	(*vertices)[1]->add(axis->set((*axes)[2])->scale(-(*halfExtensionXYZ)[2]));
	(*vertices)[2]->set(center);
	(*vertices)[2]->add(axis->set((*axes)[0])->scale(+(*halfExtensionXYZ)[0]));
	(*vertices)[2]->add(axis->set((*axes)[1])->scale(+(*halfExtensionXYZ)[1]));
	(*vertices)[2]->add(axis->set((*axes)[2])->scale(-(*halfExtensionXYZ)[2]));
	(*vertices)[3]->set(center);
	(*vertices)[3]->add(axis->set((*axes)[0])->scale(-(*halfExtensionXYZ)[0]));
	(*vertices)[3]->add(axis->set((*axes)[1])->scale(+(*halfExtensionXYZ)[1]));
	(*vertices)[3]->add(axis->set((*axes)[2])->scale(-(*halfExtensionXYZ)[2]));
	(*vertices)[4]->set(center);
	(*vertices)[4]->add(axis->set((*axes)[0])->scale(-(*halfExtensionXYZ)[0]));
	(*vertices)[4]->add(axis->set((*axes)[1])->scale(-(*halfExtensionXYZ)[1]));
	(*vertices)[4]->add(axis->set((*axes)[2])->scale(+(*halfExtensionXYZ)[2]));
	(*vertices)[5]->set(center);
	(*vertices)[5]->add(axis->set((*axes)[0])->scale(+(*halfExtensionXYZ)[0]));
	(*vertices)[5]->add(axis->set((*axes)[1])->scale(-(*halfExtensionXYZ)[1]));
	(*vertices)[5]->add(axis->set((*axes)[2])->scale(+(*halfExtensionXYZ)[2]));
	(*vertices)[6]->set(center);
	(*vertices)[6]->add(axis->set((*axes)[0])->scale(+(*halfExtensionXYZ)[0]));
	(*vertices)[6]->add(axis->set((*axes)[1])->scale(+(*halfExtensionXYZ)[1]));
	(*vertices)[6]->add(axis->set((*axes)[2])->scale(+(*halfExtensionXYZ)[2]));
	(*vertices)[7]->set(center);
	(*vertices)[7]->add(axis->set((*axes)[0])->scale(-(*halfExtensionXYZ)[0]));
	(*vertices)[7]->add(axis->set((*axes)[1])->scale(+(*halfExtensionXYZ)[1]));
	(*vertices)[7]->add(axis->set((*axes)[2])->scale(+(*halfExtensionXYZ)[2]));
	sphereRadius = halfExtension->computeLength();
}

Vector3Array* OrientedBoundingBox::getVertices()
{
	return vertices;
}

int32_tArrayArray* OrientedBoundingBox::getFacesVerticesIndexes()
{
	clinit();
	return facesVerticesIndexes;
}

void OrientedBoundingBox::computeClosestPointOnBoundingVolume(Vector3* point, Vector3* closestPoint)
{
	direction->set(point)->sub(center);
	closestPoint->set(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > (*halfExtensionXYZ)[i])
			distance = (*halfExtensionXYZ)[i];

		if (distance < -(*halfExtensionXYZ)[i])
			distance = -(*halfExtensionXYZ)[i];

		closestPoint->add(axis->set((*axes)[i])->scale(distance));
	}
}

void OrientedBoundingBox::computeNearestPointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace)
{
	direction->set(pointInObb)->sub(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	auto axisMinPenetration = 10000.0f;
	auto axisIdxLeastPenetration = 0;
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > (*halfExtensionXYZ)[i])
			distance = (*halfExtensionXYZ)[i];

		if (distance < -(*halfExtensionXYZ)[i])
			distance = -(*halfExtensionXYZ)[i];

		float penetration;
		if (distance >= 0.0f) {
			penetration = (*halfExtensionXYZ)[i] - distance;
		} else {
			penetration = (*halfExtensionXYZ)[i] + distance;
		}
		if (penetration < axisMinPenetration) {
			axisMinPenetration = penetration;
			axisIdxLeastPenetration = i;
		}
	}
	computeNearestPointOnFaceBoundingVolumeAxis(axisIdxLeastPenetration, pointInObb, pointOnFace);
}

void OrientedBoundingBox::computeNearestPointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace)
{
	direction->set(pointInObb)->sub(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	pointOnFace->set(center);
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > (*halfExtensionXYZ)[i])
			distance = (*halfExtensionXYZ)[i];

		if (distance < -(*halfExtensionXYZ)[i])
			distance = -(*halfExtensionXYZ)[i];

		if (i == axisIdx) {
			if (distance >= 0.0f) {
				pointOnFace->add(axis->set((*axes)[i])->scale(+(*halfExtensionXYZ)[i]));
			} else {
				pointOnFace->add(axis->set((*axes)[i])->scale(-(*halfExtensionXYZ)[i]));
			}
		} else {
			pointOnFace->add(axis->set((*axes)[i])->scale(distance));
		}
	}
}

void OrientedBoundingBox::computeOppositePointOnFaceBoundingVolume(Vector3* pointInObb, Vector3* pointOnFace)
{
	direction->set(pointInObb)->sub(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	auto axisMinPenetration = 10000.0f;
	auto axisIdxLeastPenetration = 0;
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > (*halfExtensionXYZ)[i])
			distance = (*halfExtensionXYZ)[i];

		if (distance < -(*halfExtensionXYZ)[i])
			distance = -(*halfExtensionXYZ)[i];

		float penetration;
		if (distance >= 0.0f) {
			penetration = (*halfExtensionXYZ)[i] - distance;
		} else {
			penetration = (*halfExtensionXYZ)[i] + distance;
		}
		if (penetration < axisMinPenetration) {
			axisMinPenetration = penetration;
			axisIdxLeastPenetration = i;
		}
	}
	computeOppositePointOnFaceBoundingVolumeAxis(axisIdxLeastPenetration, pointInObb, pointOnFace);
}

void OrientedBoundingBox::computeOppositePointOnFaceBoundingVolumeAxis(int32_t axisIdx, Vector3* pointInObb, Vector3* pointOnFace)
{
	direction->set(pointInObb)->sub(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	pointOnFace->set(center);
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > (*halfExtensionXYZ)[i])
			distance = (*halfExtensionXYZ)[i];

		if (distance < -(*halfExtensionXYZ)[i])
			distance = -(*halfExtensionXYZ)[i];

		if (i == axisIdx) {
			if (distance >= 0.0f) {
				pointOnFace->add(axis->set((*axes)[i])->scale(-(*halfExtensionXYZ)[i]));
			} else {
				pointOnFace->add(axis->set((*axes)[i])->scale(+(*halfExtensionXYZ)[i]));
			}
		} else {
			pointOnFace->add(axis->set((*axes)[i])->scale(distance));
		}
	}
}

bool OrientedBoundingBox::containsPoint(Vector3* point)
{
	direction->set(point)->sub(center);
	auto halfExtensionXYZ = halfExtension->getArray();
	for (auto i = 0; i < axes->length; i++) {
		auto distance = Vector3::computeDotProduct(direction, (*axes)[i]);
		if (distance > 0.0f)
			distance += -MathTools::EPSILON;

		if (distance < 0.0f)
			distance += +MathTools::EPSILON;

		if (distance > (*halfExtensionXYZ)[i])
			return false;

		if (distance < -(*halfExtensionXYZ)[i])
			return false;

	}
	return true;
}

bool OrientedBoundingBox::doesCollideWith(BoundingVolume* bv2, Vector3* movement, CollisionResponse* collision)
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
		_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append(u"OrientedBoundingBox::doesCollideWith(): unsupported bounding volume 2: "_j)->append(static_cast< Object* >(bv2))->toString()));
		return false;
	}
}

float OrientedBoundingBox::computeDimensionOnAxis(Vector3* axis)
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

BoundingVolume* OrientedBoundingBox::clone()
{
	return new OrientedBoundingBox(center->clone(), (*axes)[0]->clone(), (*axes)[1]->clone(), (*axes)[2]->clone(), halfExtension->clone());
}

String* OrientedBoundingBox::toString()
{
	return ::java::lang::StringBuilder().append(u"OrientedBoundingBox [center="_j)->append(static_cast< Object* >(center))
		->append(u", axes="_j)
		->append(Arrays::toString(static_cast< ObjectArray* >(axes)))
		->append(u", halfExtension="_j)
		->append(static_cast< Object* >(halfExtension))
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* OrientedBoundingBox::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.OrientedBoundingBox", 42);
    return c;
}

void OrientedBoundingBox::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		AABB_AXIS_X = new Vector3(1.0f, 0.0f, 0.0f);
		AABB_AXIS_Y = new Vector3(0.0f, 1.0f, 0.0f);
		AABB_AXIS_Z = new Vector3(0.0f, 0.0f, 1.0f);
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

java::lang::Class* OrientedBoundingBox::getClass0()
{
	return class_();
}

