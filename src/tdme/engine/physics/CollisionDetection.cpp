// Generated from /tdme/src/tdme/engine/physics/CollisionDetection.java
#include <tdme/engine/physics/CollisionDetection.h>

#include <java/io/Serializable.h>
#include <java/lang/Cloneable.h>
#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <java/lang/Object.h>
#include <java/lang/StackTraceElement.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/Thread.h>
#include <tdme/engine/physics/CollisionResponse_Entity.h>
#include <tdme/engine/physics/CollisionResponse.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/BoundingVolume.h>
#include <tdme/engine/primitives/Capsule.h>
#include <tdme/engine/primitives/ConvexMesh.h>
#include <tdme/engine/primitives/LineSegment.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/engine/primitives/Sphere.h>
#include <tdme/engine/primitives/Triangle.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/SeparatingAxisTheorem.h>
#include <tdme/math/TriangleTriangleIntersection_ReturnValue.h>
#include <tdme/math/TriangleTriangleIntersection.h>
#include <tdme/math/Vector3.h>
#include <tdme/utils/_Console.h>
#include <Array.h>
#include <SubArray.h>
#include <ObjectArray.h>

using tdme::engine::physics::CollisionDetection;
using java::io::Serializable;
using java::lang::Cloneable;
using java::lang::Float;
using java::lang::Math;
using java::lang::Object;
using java::lang::StackTraceElement;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::Thread;
using tdme::engine::physics::CollisionResponse_Entity;
using tdme::engine::physics::CollisionResponse;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::BoundingVolume;
using tdme::engine::primitives::Capsule;
using tdme::engine::primitives::ConvexMesh;
using tdme::engine::primitives::LineSegment;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::engine::primitives::Sphere;
using tdme::engine::primitives::Triangle;
using tdme::math::MathTools;
using tdme::math::SeparatingAxisTheorem;
using tdme::math::TriangleTriangleIntersection_ReturnValue;
using tdme::math::TriangleTriangleIntersection;
using tdme::math::Vector3;
using tdme::utils::_Console;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
typedef ::SubArray< ::java::lang::StackTraceElement, ObjectArray, ::java::io::SerializableArray > StackTraceElementArray;
}  // namespace lang
}  // namespace java

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

namespace  {
typedef ::SubArray< ::int32_tArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > int32_tArrayArray;
}  // namespace 

namespace tdme {
namespace engine {
namespace primitives {
typedef ::SubArray< ::tdme::engine::primitives::TriangleArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > TriangleArrayArray;
}  // namespace primitives
}  // namespace engine
}  // namespace tdme

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

extern void lock(::java::lang::Object *);
extern void unlock(::java::lang::Object *);

namespace
{
struct synchronized
{
    synchronized(::java::lang::Object *o) : o(o) { ::lock(o); }
    ~synchronized() { ::unlock(o); }
private:
    synchronized(const synchronized&); synchronized& operator=(const synchronized&);
    ::java::lang::Object *o;
};
}
CollisionDetection::CollisionDetection(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

CollisionDetection::CollisionDetection()
	: CollisionDetection(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void CollisionDetection::init()
{
	lineSegment = new LineSegment();
	closestPointOnCapsule1 = new Vector3();
	closestPointOnCapsule2 = new Vector3();
	closestPoint = new Vector3();
	axis = new Vector3();
	obbExtended = new OrientedBoundingBox();
	contactMin = new Vector3();
	contactMax = new Vector3();
	contactAvg = new Vector3();
	contactAvgCollisionNormal = new Vector3();
	contactAvgSubContactMin = new Vector3();
	contactOptimal = new Vector3();
	sphere1 = new Sphere();
	sphere2 = new Sphere();
	obbConverted1 = new OrientedBoundingBox();
	obbConverted2 = new OrientedBoundingBox();
	pointOnFaceNearest = new Vector3();
	pointOnFaceOpposite = new Vector3();
	triangle1Edge1 = new Vector3();
	triangle1Edge2 = new Vector3();
	triangle1Edge3 = new Vector3();
	triangle1Normal = new Vector3();
	triangle2Edge1 = new Vector3();
	triangle2Edge2 = new Vector3();
	triangle2Edge3 = new Vector3();
	triangle2Normal = new Vector3();
	closestPointsOnCapsuleSegment = (new Vector3Array({
		new Vector3(),
		new Vector3(),
		new Vector3(),
		new Vector3(),
		new Vector3()
	}));
	closestPointsOnTriangleSegments = (new Vector3Array({
		new Vector3(),
		new Vector3(),
		new Vector3(),
		new Vector3(),
		new Vector3()
	}));
	satAxis = new Vector3();
	satAxesCount = 0;
	haveSatAxisBestFit = false;
	satAxisBestFit = new Vector3();
	satAxisBestFitPenetration = 0.0f;
	separatingAxisTheorem = new SeparatingAxisTheorem();
	hitPoint = new Vector3();
	triangleTriangleIntersection = new TriangleTriangleIntersection();
	triangle1 = new Triangle(new Vector3(), new Vector3(), new Vector3());
	triangle2 = new Triangle(new Vector3(), new Vector3(), new Vector3());
	hitPointTriangle1 = new Vector3();
	hitPointTriangle2 = new Vector3();
	collision1 = new CollisionResponse();
}

constexpr bool CollisionDetection::VERBOSE;

constexpr int32_t CollisionDetection::SAT_AXES_TEST_MAX;

constexpr int32_t CollisionDetection::TRIANGLES_TEST_MAX;

CollisionDetection* CollisionDetection::instance = nullptr;

Object* CollisionDetection::synchronizeObject;

Vector3* CollisionDetection::zeroVector;

int32_tArray* CollisionDetection::lineSegmentsTriangleIndices;

constexpr bool CollisionDetection::CHECK_COLLISIONRESPONSE;

CollisionDetection* CollisionDetection::getInstance() {
	clinit();
	if (CollisionDetection::instance == nullptr) {
		CollisionDetection::instance = new CollisionDetection();
	}
	return CollisionDetection::instance;
}

void CollisionDetection::ctor()
{
	super::ctor();
	init();
	satPenetrations = new floatArray(SAT_AXES_TEST_MAX);
	satAxes = new Vector3Array(SAT_AXES_TEST_MAX);
	for (auto i = 0; i < satAxes->length; i++) 
				satAxes->set(i, new Vector3());

	satAxesCount = 0;
	testTriangleCount = 0;
	testTriangles = __newMultiArray< TriangleArrayArray >(TRIANGLES_TEST_MAX,2);
	for (auto i = 0; i < testTriangles->length; i++) 
				testTriangles->set(i, new TriangleArray(2));

}

void CollisionDetection::resetSATAxes()
{
	haveSatAxisBestFit = false;
	satAxesCount = 0;
}

void CollisionDetection::addSATAxis(Vector3* axis)
{
	if (separatingAxisTheorem->checkAxis(axis) == false)
		return;

	for (auto i = 0; i < satAxesCount; i++) {
		if ((*satAxes)[i]->equals(axis, 0.1f))
			return;

	}
	(*satAxes)[satAxesCount++]->set(axis);
}

void CollisionDetection::determineSatAxisBestFit()
{
	for (auto i = 0; i < satAxesCount; i++) {
		if (Float::isNaN((*satPenetrations)[i]) || Math::abs((*satPenetrations)[i]) < MathTools::EPSILON) {
			continue;
		}
		if (haveSatAxisBestFit == false || -(*satPenetrations)[i] > satAxisBestFitPenetration) {
			haveSatAxisBestFit = true;
			satAxisBestFit->set((*satAxes)[i]);
			satAxisBestFitPenetration = -(*satPenetrations)[i];
		}
	}
}

void CollisionDetection::resetTriangles()
{
	testTriangleCount = 0;
}

bool CollisionDetection::doCollideAABBvsAABBFast(BoundingBox* b1, BoundingBox* b2)
{
	clinit();
	auto b1MinXYZ = b1->getMin()->getArray();
	auto b1MaxXYZ = b1->getMax()->getArray();
	auto b2MinXYZ = b2->getMin()->getArray();
	auto b2MaxXYZ = b2->getMax()->getArray();
	if ((*b2MaxXYZ)[0] - (*b1MinXYZ)[0] < 0.0f)
		return false;

	if ((*b1MaxXYZ)[0] - (*b2MinXYZ)[0] < 0.0f)
		return false;

	if ((*b2MaxXYZ)[1] - (*b1MinXYZ)[1] < 0.0f)
		return false;

	if ((*b1MaxXYZ)[1] - (*b2MinXYZ)[1] < 0.0f)
		return false;

	if ((*b2MaxXYZ)[2] - (*b1MinXYZ)[2] < 0.0f)
		return false;

	if ((*b1MaxXYZ)[2] - (*b2MinXYZ)[2] < 0.0f)
		return false;

	return true;
}

bool CollisionDetection::doCollide(BoundingBox* b1, BoundingBox* b2, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(b1);
	obbConverted2->fromBoundingBox(b2);
	return doCollide(obbConverted1, obbConverted2, movement, collision);
}

bool CollisionDetection::doCollide(BoundingBox* aabb, Sphere* sphere, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obbConverted1, sphere, movement, collision);
}

bool CollisionDetection::doCollide(Sphere* sphere, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(sphere, obbConverted1, movement, collision);
}

bool CollisionDetection::doCollide(BoundingBox* aabb, Capsule* capsule, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obbConverted1, capsule, movement, collision);
}

bool CollisionDetection::doCollide(Capsule* capsule, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(capsule, obbConverted1, movement, collision);
}

bool CollisionDetection::doCollide(Sphere* s1, Sphere* s2, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	axis->set(s2->getCenter())->sub(s1->getCenter());
	if (checkMovementFallback(axis, movement, collision) == true) {
		auto collisionEntity = collision->getEntityAt(0);
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(s1->getRadius())->add(s1->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(-s2->getRadius())->add(s2->getCenter()));
		return true;
	}
	auto distance = axis->computeLength();
	auto _distance = distance - (s1->getRadius() + s2->getRadius());
	if (_distance < 0.0f) {
		auto collisionEntity = collision->addResponse(_distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(s1->getRadius())->add(s1->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(-s2->getRadius())->add(s2->getCenter()));
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Capsule* c1, Capsule* c2, Vector3* movement, CollisionResponse* collision)
{
	if (doBroadTest(c1, c2) == false)
		return false;

	lineSegment->computeClosestPointsOnLineSegments(c1->getA(), c1->getB(), c2->getA(), c2->getB(), closestPointOnCapsule1, closestPointOnCapsule2);
	return doCollide(sphere1->set(closestPointOnCapsule1, c1->getRadius()), sphere2->set(closestPointOnCapsule2, c2->getRadius()), movement, collision);
}

bool CollisionDetection::doCollide(Capsule* c, Sphere* s, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(c, s) == false)
		return false;

	auto sphereCenter = s->getCenter();
	c->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(sphereCenter)->sub(closestPoint);
	if (checkMovementFallback(axis, movement, collision) == true) {
		auto collisionEntity = collision->getEntityAt(0);
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(-s->getRadius())->add(s->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(c->getRadius())->add(closestPoint));
		return true;
	}
	auto distance = axis->computeLength();
	auto _distance = distance - (c->getRadius() + s->getRadius());
	if (_distance < 0.0f) {
		auto collisionEntity = collision->addResponse(_distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(-s->getRadius())->add(s->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(c->getRadius())->add(closestPoint));
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Sphere* s, Capsule* c, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(s, c) == false)
		return false;

	auto sphereCenter = s->getCenter();
	c->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(closestPoint)->sub(sphereCenter);
	if (checkMovementFallback(axis, movement, collision) == true) {
		auto collisionEntity = collision->getEntityAt(0);
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(s->getRadius())->add(s->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(movement)->normalize()->scale(-c->getRadius())->add(closestPoint));
		return true;
	}
	auto distance = axis->computeLength();
	auto _distance = distance - (c->getRadius() + s->getRadius());
	if (_distance < 0.0f) {
		auto collisionEntity = collision->addResponse(_distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(s->getRadius())->add(s->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(-c->getRadius())->add(closestPoint));
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(obb1, obb2) == false)
		return false;

	auto axes1 = obb1->getAxes();
	auto axes2 = obb2->getAxes();
	auto obb1Vertices = obb1->getVertices();
	auto obb2Vertices = obb2->getVertices();
	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[0]->set((*axes1)[0]), satPenetrations, 0) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[1]->set((*axes1)[1]), satPenetrations, 1) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[2]->set((*axes1)[2]), satPenetrations, 2) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[3]->set((*axes2)[0]), satPenetrations, 3) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[4]->set((*axes2)[1]), satPenetrations, 4) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, (*satAxes)[5]->set((*axes2)[2]), satPenetrations, 5) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[0], (*axes2)[0], (*satAxes)[6]), satPenetrations, 6) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[0], (*axes2)[1], (*satAxes)[7]), satPenetrations, 7) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[0], (*axes2)[2], (*satAxes)[8]), satPenetrations, 8) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[1], (*axes2)[0], (*satAxes)[9]), satPenetrations, 9) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[1], (*axes2)[1], (*satAxes)[10]), satPenetrations, 10) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[1], (*axes2)[2], (*satAxes)[11]), satPenetrations, 11) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[2], (*axes2)[0], (*satAxes)[12]), satPenetrations, 12) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[2], (*axes2)[1], (*satAxes)[13]), satPenetrations, 13) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(obb1Vertices, obb2Vertices, Vector3::computeCrossProduct((*axes1)[2], (*axes2)[2], (*satAxes)[14]), satPenetrations, 14) == false)
		return false;

	auto selectedEntityIdx = -1;
	auto selectedEntityDistance = 0.0f;
	for (auto i = 0; i < 15; i++) {
		if (Float::isNaN((*satPenetrations)[i]))
			continue;

		if (selectedEntityIdx == -1 || -(*satPenetrations)[i] > selectedEntityDistance) {
			selectedEntityDistance = -(*satPenetrations)[i];
			selectedEntityIdx = i;
		}
	}
	auto entity = collision->addResponse(-(*satPenetrations)[selectedEntityIdx]);
	entity->getNormal()->set((*satAxes)[selectedEntityIdx]);
	computeHitPoints(obb1, obb2, entity);
	return collision->getEntityCount() > 0;
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obb, obbConverted1, movement, collision);
}

bool CollisionDetection::doCollide(BoundingBox* aabb, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obbConverted1, obb, movement, collision);
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb, Sphere* sphere, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(obb, sphere) == false)
		return false;

	auto sphereCenter = sphere->getCenter();
	obb->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(sphereCenter)->sub(closestPoint);
	float distance;
	if (axis->computeLength() < MathTools::EPSILON) {
		obb->computeNearestPointOnFaceBoundingVolume(closestPoint, pointOnFaceNearest);
		obb->computeOppositePointOnFaceBoundingVolume(closestPoint, pointOnFaceOpposite);
		obb->computeNearestPointOnFaceBoundingVolume(pointOnFaceNearest, closestPoint);
		axis->set(sphereCenter)->sub(pointOnFaceNearest);
		distance = -axis->computeLength() - sphere->getRadius();
		axis->set(pointOnFaceNearest)->sub(pointOnFaceOpposite);
	} else {
		distance = axis->computeLength() - sphere->getRadius();
	}
	if (distance < 0.0f) {
		auto collisionEntity = collision->addResponse(distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(closestPoint);
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(-sphere->getRadius())->add(sphereCenter));
		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Sphere* sphere, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(sphere, obb) == false)
		return false;

	auto sphereCenter = sphere->getCenter();
	obb->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(closestPoint)->sub(sphereCenter);
	float distance;
	if (axis->computeLength() < MathTools::EPSILON) {
		obb->computeNearestPointOnFaceBoundingVolume(closestPoint, pointOnFaceNearest);
		obb->computeOppositePointOnFaceBoundingVolume(closestPoint, pointOnFaceOpposite);
		obb->computeNearestPointOnFaceBoundingVolume(pointOnFaceNearest, closestPoint);
		axis->set(sphereCenter)->sub(pointOnFaceNearest);
		distance = axis->computeLength() - sphere->getRadius();
		axis->set(pointOnFaceOpposite)->sub(pointOnFaceNearest);
	} else {
		distance = axis->computeLength() - sphere->getRadius();
	}
	if (distance < 0.0f) {
		auto collisionEntity = collision->addResponse(distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(sphere->getRadius())->add(sphereCenter));
		collisionEntity->addHitPoint(closestPoint);
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb, Capsule* capsule, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(obb, capsule) == false)
		return false;

	auto r = capsule->getRadius();
	obbExtended->fromOrientedBoundingBox(obb);
	obbExtended->getHalfExtension()->add(r);
	obbExtended->update();
	if (lineSegment->doesOrientedBoundingBoxCollideWithLineSegment(obbExtended, capsule->getA(), capsule->getB(), contactMin, contactMax) == true) {
		axis->set(capsule->getB())->sub(capsule->getA())->normalize();
		contactAvg->set(contactMin)->add(contactMax)->scale(0.5f);
		obb->computeClosestPointOnBoundingVolume(contactAvg, closestPoint);
		if (contactAvg->equals(closestPoint) == true) {
			contactOptimal->set(contactAvg);
		} else {
			contactAvgCollisionNormal->set(contactAvg)->sub(closestPoint)->normalize();
			auto collisionNormalDotABNormalized = Vector3::computeDotProduct(contactAvgCollisionNormal, axis);
			contactAvgSubContactMin->set(contactAvg)->sub(contactMin);
			contactOptimal->set(contactAvg)->sub(contactAvgSubContactMin->scale(collisionNormalDotABNormalized));
		}
		doCollide(obb, sphere1->set(contactOptimal, r), movement, collision);
		if (collision->hasEntitySelected() == true)
			return true;

	}
	return false;
}

bool CollisionDetection::doCollide(Capsule* capsule, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision)
{
	if (doCollide(obb, capsule, movement, collision) == true) {
		collision->invertNormals();
		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Triangle* triangle, Sphere* sphere, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	auto sphereCenter = sphere->getCenter();
	triangle->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(sphereCenter)->sub(closestPoint);
	if (checkMovementFallback(axis, movement, collision) == true) {
		return true;
	}
	auto distance = axis->computeLength() - sphere->getRadius();
	if (distance < 0.0f) {
		auto collisionEntity = collision->addResponse(distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(-sphere->getRadius())->add(sphere->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(closestPoint));
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Sphere* sphere, Triangle* triangle, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	auto sphereCenter = sphere->getCenter();
	triangle->computeClosestPointOnBoundingVolume(sphereCenter, closestPoint);
	axis->set(closestPoint)->sub(sphereCenter);
	if (checkMovementFallback(axis, movement, collision) == true) {
		return true;
	}
	auto distance = axis->computeLength() - sphere->getRadius();
	if (distance < 0.0f) {
		auto collisionEntity = collision->addResponse(distance);
		collisionEntity->getNormal()->set(axis)->normalize();
		collisionEntity->addHitPoint(hitPoint->set(axis)->normalize()->scale(sphere->getRadius())->add(sphere->getCenter()));
		collisionEntity->addHitPoint(hitPoint->set(closestPoint));
		if (CHECK_COLLISIONRESPONSE)
			checkCollision(collision);

		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Sphere* sphere, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh, sphere) == false)
		return false;

	for (auto triangle : *mesh->getTriangles()) {
		if (doCollide(sphere, triangle, movement, collision1) == true) {
			collision->mergeResponse(collision1);
		}
	}
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(ConvexMesh* mesh, Sphere* sphere, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh, sphere) == false)
		return false;

	for (auto triangle : *mesh->getTriangles()) {
		if (doCollide(triangle, sphere, movement, collision1) == true) {
			collision->mergeResponse(collision1);
		}
	}
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(Triangle* triangle, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(triangle, obbConverted1, movement, collision);
}

bool CollisionDetection::doCollide(BoundingBox* aabb, Triangle* triangle, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obbConverted1, triangle, movement, collision);
}

bool CollisionDetection::doCollide(Triangle* triangle, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(triangle, obb) == false)
		return false;

	auto obbVertices = obb->getVertices();
	auto obbAxes = obb->getAxes();
	auto triangleVertices = triangle->getVertices();
	triangle1Edge1->set((*triangleVertices)[1])->sub((*triangleVertices)[0])->normalize();
	triangle1Edge2->set((*triangleVertices)[2])->sub((*triangleVertices)[1])->normalize();
	triangle1Edge3->set((*triangleVertices)[0])->sub((*triangleVertices)[2])->normalize();
	triangle1Normal = Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2)->normalize();
	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, (*satAxes)[0]->set(triangle1Normal), satPenetrations, 0) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, (*satAxes)[1]->set((*obbAxes)[0]), satPenetrations, 1) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, (*satAxes)[2]->set((*obbAxes)[1]), satPenetrations, 2) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, (*satAxes)[3]->set((*obbAxes)[2]), satPenetrations, 3) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge1, (*satAxes)[4]), satPenetrations, 4) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge2, (*satAxes)[5]), satPenetrations, 5) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge3, (*satAxes)[6]), satPenetrations, 6) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge1, (*satAxes)[7]), satPenetrations, 7) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge2, (*satAxes)[8]), satPenetrations, 8) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge3, (*satAxes)[9]), satPenetrations, 9) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge1, (*satAxes)[10]), satPenetrations, 10) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge2, (*satAxes)[11]), satPenetrations, 11) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangleVertices, obbVertices, Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge3, (*satAxes)[12]), satPenetrations, 12) == false)
		return false;

	auto selectedEntityIdx = -1;
	auto selectedEntityDistance = 0.0f;
	for (auto i = 0; i < 13; i++) {
		if (Float::isNaN((*satPenetrations)[i]) || Math::abs((*satPenetrations)[i]) < MathTools::EPSILON) {
			continue;
		}
		if (selectedEntityIdx == -1 || -(*satPenetrations)[i] > selectedEntityDistance) {
			selectedEntityDistance = -(*satPenetrations)[i];
			selectedEntityIdx = i;
		}
	}
	auto entity = collision->addResponse(-(*satPenetrations)[selectedEntityIdx]);
	entity->getNormal()->set((*satAxes)[selectedEntityIdx]);
	computeHitPoints(triangle, obb, entity);
	return true;
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb, Triangle* triangle, Vector3* movement, CollisionResponse* collision)
{
	if (doCollide(triangle, obb, movement, collision) == true) {
		collision->invertNormals();
		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(ConvexMesh* mesh, BoundingBox* aabb, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(mesh, obbConverted1, movement, collision);
}

bool CollisionDetection::doCollide(BoundingBox* aabb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision)
{
	obbConverted1->fromBoundingBox(aabb);
	return doCollide(obbConverted1, mesh, movement, collision);
}

bool CollisionDetection::doCollide(ConvexMesh* mesh, OrientedBoundingBox* obb, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh, obb) == false)
		return false;

	auto obbVertices = obb->getVertices();
	auto obbAxes = obb->getAxes();
	auto meshVertices = mesh->getVertices();
	resetTriangles();
	for (auto triangle : *mesh->getTriangles()) {
		collision1->reset();
		if (doBroadTest(triangle, obb) == false)
			continue;

		auto triangleVertices = triangle->getVertices();
		triangle1Edge1->set((*triangleVertices)[1])->sub((*triangleVertices)[0])->normalize();
		triangle1Edge2->set((*triangleVertices)[2])->sub((*triangleVertices)[1])->normalize();
		triangle1Edge3->set((*triangleVertices)[0])->sub((*triangleVertices)[2])->normalize();
		Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2, triangle1Normal)->normalize();
		resetSATAxes();
		addSATAxis(satAxis->set(triangle1Normal));
		addSATAxis(satAxis->set((*obbAxes)[0]));
		addSATAxis(satAxis->set((*obbAxes)[1]));
		addSATAxis(satAxis->set((*obbAxes)[2]));
		addSATAxis(satAxis->set(triangle1Edge1));
		addSATAxis(satAxis->set(triangle1Edge2));
		addSATAxis(satAxis->set(triangle1Edge3));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge1, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge2, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[0], triangle1Edge3, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge1, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge2, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[1], triangle1Edge3, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge1, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge2, satAxis));
		addSATAxis(Vector3::computeCrossProduct((*obbAxes)[2], triangle1Edge3, satAxis));
		for (auto satAxisIdx = 0; satAxisIdx < satAxesCount; satAxisIdx++) {
			if (separatingAxisTheorem->doSpanIntersect(meshVertices, obbVertices, (*satAxes)[satAxisIdx], satPenetrations, satAxisIdx) == false) {
				resetSATAxes();
				resetTriangles();
				return false;
			}
		}
		determineSatAxisBestFit();
		(*testTriangles)[testTriangleCount++]->set(0, triangle);
	}
	if (haveSatAxisBestFit == true) {
		auto entity = collision->addResponse(satAxisBestFitPenetration);
		entity->getNormal()->set(satAxisBestFit);
		for (auto i = 0; i < testTriangleCount; i++) {
			computeHitPoints((*(*testTriangles)[i])[0], obb, entity);
		}
	}
	resetTriangles();
	resetSATAxes();
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(OrientedBoundingBox* obb, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision)
{
	if (doCollide(mesh, obb, movement, collision) == true) {
		collision->invertNormals();
		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Triangle* triangle1, Triangle* triangle2, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(triangle1, triangle2) == false)
		return false;

	auto triangle1Vertices = triangle1->getVertices();
	triangle1Edge1->set((*triangle1Vertices)[1])->sub((*triangle1Vertices)[0])->normalize();
	triangle1Edge2->set((*triangle1Vertices)[2])->sub((*triangle1Vertices)[1])->normalize();
	triangle1Edge3->set((*triangle1Vertices)[0])->sub((*triangle1Vertices)[2])->normalize();
	Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2, triangle1Normal)->normalize();
	auto triangle2Vertices = triangle2->getVertices();
	triangle2Edge1->set((*triangle2Vertices)[1])->sub((*triangle2Vertices)[0])->normalize();
	triangle2Edge2->set((*triangle2Vertices)[2])->sub((*triangle2Vertices)[1])->normalize();
	triangle2Edge3->set((*triangle2Vertices)[0])->sub((*triangle2Vertices)[2])->normalize();
	Vector3::computeCrossProduct(triangle2Edge1, triangle2Edge2, triangle2Normal)->normalize();
	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, (*satAxes)[0]->set(triangle1Normal), satPenetrations, 0) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, (*satAxes)[1]->set(triangle2Normal), satPenetrations, 1) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge1, (*satAxes)[2]), satPenetrations, 2) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge2, (*satAxes)[3]), satPenetrations, 3) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge3, (*satAxes)[4]), satPenetrations, 4) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge1, (*satAxes)[5]), satPenetrations, 5) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge2, (*satAxes)[6]), satPenetrations, 6) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge3, (*satAxes)[7]), satPenetrations, 7) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge1, (*satAxes)[8]), satPenetrations, 8) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge2, (*satAxes)[9]), satPenetrations, 9) == false)
		return false;

	if (separatingAxisTheorem->doSpanIntersect(triangle1Vertices, triangle2Vertices, Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge3, (*satAxes)[10]), satPenetrations, 10) == false)
		return false;

	auto selectedEntityIdx = -1;
	auto selectedEntityDistance = 0.0f;
	for (auto i = 0; i < 11; i++) {
		if (Float::isNaN((*satPenetrations)[i]) || Math::abs((*satPenetrations)[i]) < MathTools::EPSILON) {
			continue;
		}
		if (selectedEntityIdx == -1 || -(*satPenetrations)[i] > selectedEntityDistance) {
			selectedEntityDistance = -(*satPenetrations)[i];
			selectedEntityIdx = i;
		}
	}
	if (selectedEntityIdx == -1)
		return false;

	auto entity = collision->addResponse(-(*satPenetrations)[selectedEntityIdx]);
	entity->getNormal()->set((*satAxes)[selectedEntityIdx]);
	computeHitPoints(triangle1, triangle2, entity);
	return true;
}

bool CollisionDetection::doCollide(ConvexMesh* mesh1, ConvexMesh* mesh2, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh1, mesh2) == false)
		return false;

	auto mesh1Vertices = mesh1->getVertices();
	auto mesh2Vertices = mesh2->getVertices();
	resetTriangles();
	for (auto triangle1 : *mesh1->getTriangles()) 
				for (auto triangle2 : *mesh2->getTriangles()) {
			if (doBroadTest(triangle1, triangle2) == false)
				continue;

			auto triangle1Vertices = triangle1->getVertices();
			triangle1Edge1->set((*triangle1Vertices)[1])->sub((*triangle1Vertices)[0])->normalize();
			triangle1Edge2->set((*triangle1Vertices)[2])->sub((*triangle1Vertices)[1])->normalize();
			triangle1Edge3->set((*triangle1Vertices)[0])->sub((*triangle1Vertices)[2])->normalize();
			Vector3::computeCrossProduct(triangle1Edge1, triangle1Edge2, triangle1Normal)->normalize();
			auto triangle2Vertices = triangle2->getVertices();
			triangle2Edge1->set((*triangle2Vertices)[1])->sub((*triangle2Vertices)[0])->normalize();
			triangle2Edge2->set((*triangle2Vertices)[2])->sub((*triangle2Vertices)[1])->normalize();
			triangle2Edge3->set((*triangle2Vertices)[0])->sub((*triangle2Vertices)[2])->normalize();
			Vector3::computeCrossProduct(triangle2Edge1, triangle2Edge2, triangle2Normal)->normalize();
			resetSATAxes();
			addSATAxis(satAxis->set(triangle1Normal));
			addSATAxis(satAxis->set(triangle2Normal));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge1, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge2, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge1, triangle2Edge3, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge1, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge2, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge2, triangle2Edge3, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge1, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge2, satAxis));
			addSATAxis(Vector3::computeCrossProduct(triangle1Edge3, triangle2Edge3, satAxis));
			for (auto satAxisIdx = 0; satAxisIdx < satAxesCount; satAxisIdx++) {
				if (separatingAxisTheorem->doSpanIntersect(mesh1Vertices, mesh2Vertices, (*satAxes)[satAxisIdx], satPenetrations, satAxisIdx) == false) {
					resetSATAxes();
					resetTriangles();
					return false;
				}
			}
			determineSatAxisBestFit();
			(*testTriangles)[testTriangleCount]->set(0, triangle1);
			(*testTriangles)[testTriangleCount]->set(1, triangle2);
			testTriangleCount++;
		}

	if (haveSatAxisBestFit == true) {
		auto entity = collision->addResponse(satAxisBestFitPenetration);
		entity->getNormal()->set(satAxisBestFit);
		for (auto i = 0; i < testTriangleCount; i++) {
			computeHitPoints((*(*testTriangles)[i])[0], (*(*testTriangles)[i])[1], entity);
		}
	}
	resetSATAxes();
	resetTriangles();
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(Triangle* triangle, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(triangle, mesh) == false)
		return false;

	for (auto triangle2 : *mesh->getTriangles()) {
		if (doCollide(triangle, triangle2, movement, collision1) == true) {
			if (collision->hasEntitySelected() == false || collision1->getPenetration() > collision->getPenetration()) {
				collision->fromResponse(collision1);
			}
		}
	}
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(ConvexMesh* mesh, Triangle* triangle, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(triangle, mesh) == false)
		return false;

	for (auto triangle2 : *mesh->getTriangles()) {
		if (doCollide(triangle2, triangle, movement, collision1) == true) {
			if (collision->hasEntitySelected() == false || collision1->getPenetration() > collision->getPenetration()) {
				collision->fromResponse(collision1);
			}
		}
	}
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(Triangle* triangle, Capsule* capsule, Vector3* movement, CollisionResponse* collision)
{
	if (doBroadTest(triangle, capsule) == false)
		return false;

	auto triangleVertices = triangle->getVertices();
	lineSegment->computeClosestPointsOnLineSegments(capsule->getA(), capsule->getB(), (*triangleVertices)[1], (*triangleVertices)[0], (*closestPointsOnCapsuleSegment)[0], (*closestPointsOnTriangleSegments)[0]);
	lineSegment->computeClosestPointsOnLineSegments(capsule->getA(), capsule->getB(), (*triangleVertices)[2], (*triangleVertices)[1], (*closestPointsOnCapsuleSegment)[1], (*closestPointsOnTriangleSegments)[1]);
	lineSegment->computeClosestPointsOnLineSegments(capsule->getA(), capsule->getB(), (*triangleVertices)[0], (*triangleVertices)[2], (*closestPointsOnCapsuleSegment)[2], (*closestPointsOnTriangleSegments)[2]);
	(*closestPointsOnCapsuleSegment)[3]->set(capsule->getA());
	triangle->computeClosestPointOnBoundingVolume((*closestPointsOnCapsuleSegment)[3], (*closestPointsOnTriangleSegments)[3]);
	(*closestPointsOnCapsuleSegment)[4]->set(capsule->getB());
	triangle->computeClosestPointOnBoundingVolume((*closestPointsOnCapsuleSegment)[4], (*closestPointsOnTriangleSegments)[4]);
	auto bestFitLength = closestPoint->set((*closestPointsOnCapsuleSegment)[0])->sub((*closestPointsOnTriangleSegments)[0])->computeLengthSquared();
	auto bestFitTest = 0;
	for (auto i = 1; i < 5; i++) {
		auto testLength = closestPoint->set((*closestPointsOnCapsuleSegment)[i])->sub((*closestPointsOnTriangleSegments)[i])->computeLengthSquared();
		if (testLength < bestFitLength) {
			bestFitLength = testLength;
			bestFitTest = i;
		}
	}
	return doCollide(triangle, sphere1->set((*closestPointsOnCapsuleSegment)[bestFitTest], capsule->getRadius()), movement, collision);
}

bool CollisionDetection::doCollide(Capsule* capsule, Triangle* triangle, Vector3* movement, CollisionResponse* collision)
{
	if (doCollide(triangle, capsule, movement, collision) == true) {
		collision->invertNormals();
		return true;
	} else {
		return false;
	}
}

bool CollisionDetection::doCollide(Capsule* capsule, ConvexMesh* mesh, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh, capsule) == false)
		return false;

	for (auto triangle : *mesh->getTriangles()) {
		if (doCollide(capsule, triangle, movement, collision1) == true) {
			if (collision->hasEntitySelected() == false || collision1->getPenetration() > collision->getPenetration()) {
				collision->fromResponse(collision1);
			}
		}
	}
	return collision->hasEntitySelected();
}

bool CollisionDetection::doCollide(ConvexMesh* mesh, Capsule* capsule, Vector3* movement, CollisionResponse* collision)
{
	collision->reset();
	if (doBroadTest(mesh, capsule) == false)
		return false;

	for (auto triangle : *mesh->getTriangles()) {
		if (doCollide(triangle, capsule, movement, collision1) == true) {
			if (collision->hasEntitySelected() == false || collision1->getPenetration() > collision->getPenetration()) {
				collision->fromResponse(collision1);
			}
		}
	}
	return collision->hasEntitySelected();
}

void CollisionDetection::computeHitPoints(OrientedBoundingBox* obb1, OrientedBoundingBox* obb2, CollisionResponse_Entity* collisionEntity)
{
	auto obb1Vertices = obb1->getVertices();
	auto obb1FacesVerticesIndexes = OrientedBoundingBox::getFacesVerticesIndexes();
	auto obb2Vertices = obb2->getVertices();
	auto obb2FacesVerticesIndexes = OrientedBoundingBox::getFacesVerticesIndexes();
	for (auto triangleObb1Idx = 0; triangleObb1Idx < obb1FacesVerticesIndexes->length; triangleObb1Idx++) 
				for (auto triangleObb2Idx = 0; triangleObb2Idx < obb2FacesVerticesIndexes->length; triangleObb2Idx++) {
			auto tritriReturn = triangleTriangleIntersection->computeTriangleTriangleIntersection((*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[0]], (*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[1]], (*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[2]], (*obb2Vertices)[(*(*obb2FacesVerticesIndexes)[triangleObb2Idx])[0]], (*obb2Vertices)[(*(*obb2FacesVerticesIndexes)[triangleObb2Idx])[1]], (*obb2Vertices)[(*(*obb2FacesVerticesIndexes)[triangleObb2Idx])[2]], hitPointTriangle1, hitPointTriangle2);
			{
				Vector3Array* _triangle1Vertices;
				Vector3Array* _triangle2Vertices;
				{
					auto v = tritriReturn;
					if ((v == TriangleTriangleIntersection_ReturnValue::NOINTERSECTION)) {
						goto end_switch0;;
					}
					if ((v == TriangleTriangleIntersection_ReturnValue::INTERSECTION)) {
						collisionEntity->addHitPoint(hitPointTriangle1);
						collisionEntity->addHitPoint(hitPointTriangle2);
						goto end_switch0;;
					}
					if ((v == TriangleTriangleIntersection_ReturnValue::COPLANAR_INTERSECTION)) {
						auto _triangle1Vertices = triangle1->getVertices();
						auto _triangle2Vertices = triangle2->getVertices();
						(*_triangle1Vertices)[0]->set((*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[0]]);
						(*_triangle1Vertices)[1]->set((*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[1]]);
						(*_triangle1Vertices)[2]->set((*obb1Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb1Idx])[2]]);
						triangle1->update();
						(*_triangle2Vertices)[0]->set((*obb2Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb2Idx])[0]]);
						(*_triangle2Vertices)[1]->set((*obb2Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb2Idx])[1]]);
						(*_triangle2Vertices)[2]->set((*obb2Vertices)[(*(*obb1FacesVerticesIndexes)[triangleObb2Idx])[2]]);
						triangle2->update();
						computeCoplanarTrianglesHitPoints(triangle1, triangle2, collisionEntity);
						goto end_switch0;;
					}
end_switch0:;
				}
			}

		}

}

void CollisionDetection::computeHitPoints(Triangle* triangle, OrientedBoundingBox* obb, CollisionResponse_Entity* collisionEntity)
{
	auto triangleVertices = triangle->getVertices();
	auto obbVertices = obb->getVertices();
	auto obbFacesVerticesIndexes = OrientedBoundingBox::getFacesVerticesIndexes();
	for (auto triangleObbIdx = 0; triangleObbIdx < obbFacesVerticesIndexes->length; triangleObbIdx++) {
		auto tritriReturn = triangleTriangleIntersection->computeTriangleTriangleIntersection((*triangleVertices)[0], (*triangleVertices)[1], (*triangleVertices)[2], (*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[0]], (*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[1]], (*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[2]], hitPointTriangle1, hitPointTriangle2);
		{
			Vector3Array* _triangle1Vertices;
			Vector3Array* _triangle2Vertices;
			{
				auto v = tritriReturn;
				if ((v == TriangleTriangleIntersection_ReturnValue::NOINTERSECTION)) {
					goto end_switch1;;
				}
				if ((v == TriangleTriangleIntersection_ReturnValue::INTERSECTION)) {
					collisionEntity->addHitPoint(hitPointTriangle1);
					collisionEntity->addHitPoint(hitPointTriangle2);
					goto end_switch1;;
				}
				if ((v == TriangleTriangleIntersection_ReturnValue::COPLANAR_INTERSECTION)) {
					auto _triangle1Vertices = triangle1->getVertices();
					auto _triangle2Vertices = triangle2->getVertices();
					(*_triangle1Vertices)[0]->set((*triangleVertices)[0]);
					(*_triangle1Vertices)[1]->set((*triangleVertices)[1]);
					(*_triangle1Vertices)[2]->set((*triangleVertices)[2]);
					triangle1->update();
					(*_triangle2Vertices)[0]->set((*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[0]]);
					(*_triangle2Vertices)[1]->set((*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[1]]);
					(*_triangle2Vertices)[2]->set((*obbVertices)[(*(*obbFacesVerticesIndexes)[triangleObbIdx])[2]]);
					triangle2->update();
					computeCoplanarTrianglesHitPoints(triangle1, triangle2, collisionEntity);
					goto end_switch1;;
				}
end_switch1:;
			}
		}

	}
}

void CollisionDetection::computeHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity)
{
	auto triangle1Vertices = triangle1->getVertices();
	auto triangle2Vertices = triangle2->getVertices();
	auto tritriReturn = triangleTriangleIntersection->computeTriangleTriangleIntersection((*triangle1Vertices)[0], (*triangle1Vertices)[1], (*triangle1Vertices)[2], (*triangle2Vertices)[0], (*triangle2Vertices)[1], (*triangle2Vertices)[2], hitPointTriangle1, hitPointTriangle2);
	{
		Vector3Array* _triangle1Vertices;
		Vector3Array* _triangle2Vertices;
		{
			auto v = tritriReturn;
			if ((v == TriangleTriangleIntersection_ReturnValue::NOINTERSECTION)) {
				goto end_switch2;;
			}
			if ((v == TriangleTriangleIntersection_ReturnValue::INTERSECTION)) {
				collisionEntity->addHitPoint(hitPointTriangle1);
				collisionEntity->addHitPoint(hitPointTriangle2);
				goto end_switch2;;
			}
			if ((v == TriangleTriangleIntersection_ReturnValue::COPLANAR_INTERSECTION)) {
				auto _triangle1Vertices = triangle1->getVertices();
				auto _triangle2Vertices = triangle2->getVertices();
				(*_triangle1Vertices)[0]->set((*triangle1Vertices)[0]);
				(*_triangle1Vertices)[1]->set((*triangle1Vertices)[1]);
				(*_triangle1Vertices)[2]->set((*triangle1Vertices)[2]);
				triangle1->update();
				(*_triangle2Vertices)[0]->set((*triangle2Vertices)[0]);
				(*_triangle2Vertices)[1]->set((*triangle2Vertices)[1]);
				(*_triangle2Vertices)[2]->set((*triangle2Vertices)[2]);
				triangle2->update();
				computeCoplanarTrianglesHitPoints(triangle1, triangle2, collisionEntity);
				goto end_switch2;;
			}
end_switch2:;
		}
	}

}

void CollisionDetection::computeCoplanarTrianglesHitPoints(Triangle* triangle1, Triangle* triangle2, CollisionResponse_Entity* collisionEntity)
{
	auto triangle1Vertices = triangle1->getVertices();
	auto triangle2Vertices = triangle2->getVertices();
	auto lineSegmentsIntersections = 0;
	for (auto i = 0; i < lineSegmentsTriangleIndices->length; i += 2) 
				for (auto j = 0; j < lineSegmentsTriangleIndices->length; j += 2) {
			if (lineSegment->doesLineSegmentsCollide((*triangle1Vertices)[(*lineSegmentsTriangleIndices)[i + 0]], (*triangle1Vertices)[(*lineSegmentsTriangleIndices)[i + 1]], (*triangle2Vertices)[(*lineSegmentsTriangleIndices)[j + 0]], (*triangle2Vertices)[(*lineSegmentsTriangleIndices)[j + 1]], hitPoint) == true) {
				lineSegmentsIntersections++;
				collisionEntity->addHitPoint(hitPoint);
			}
		}

	if (lineSegmentsIntersections == 0) {
		for (auto i = 0; i < triangle1Vertices->length; i++) {
			if (triangle2->containsPoint((*triangle1Vertices)[i]) == true) {
				collisionEntity->addHitPoint((*triangle1Vertices)[i]);
			}
		}
		for (auto i = 0; i < triangle2Vertices->length; i++) {
			if (triangle1->containsPoint((*triangle2Vertices)[i]) == true) {
				collisionEntity->addHitPoint((*triangle2Vertices)[i]);
			}
		}
	}
}

bool CollisionDetection::doBroadTest(BoundingVolume* bv1, BoundingVolume* bv2)
{
	return axis->set(bv1->getCenter())->sub(bv2->getCenter())->computeLengthSquared() <= (bv1->getSphereRadius() + bv2->getSphereRadius()) * (bv1->getSphereRadius() + bv2->getSphereRadius());
}

bool CollisionDetection::checkMovementFallback(Vector3* normalCandidate, Vector3* movement, CollisionResponse* collision)
{
	clinit();
	if (movement == nullptr) {
		if (VERBOSE) {
			_Console::println(static_cast< Object* >(u"checkMovementFallback::fallback::movement = null"_j));
			auto stackTraceElement = Thread::currentThread()->getStackTrace();
			for (auto i = 2; i < 10 && i < stackTraceElement->length; i++) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append((*stackTraceElement)[i]->getClassName())->append(u":"_j)
					->append((*stackTraceElement)[i]->getLineNumber())->toString()));
			}
		}
		return false;
	}
	if (normalCandidate->equals(zeroVector) == true) {
		if (VERBOSE) {
			_Console::println(static_cast< Object* >(u"checkMovementFallback::fallback"_j));
			auto stackTraceElement = Thread::currentThread()->getStackTrace();
			for (auto i = 2; i < 10 && i < stackTraceElement->length; i++) {
				_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append((*stackTraceElement)[i]->getClassName())->append(u":"_j)
					->append((*stackTraceElement)[i]->getLineNumber())->toString()));
			}
		}
		collision->reset();
		collision->addResponse(-movement->computeLength())->getNormal()->set(movement)->scale(-1.0f)->normalize();
		return true;
	}
	return false;
}

void CollisionDetection::checkCollision(CollisionResponse* collision)
{
	clinit();
	auto normalXYZ = collision->getNormal()->getArray();
	if (Float::isNaN((*normalXYZ)[0]) == true || Float::isNaN((*normalXYZ)[1]) == true || Float::isNaN((*normalXYZ)[2]) == true) {
		_Console::println(static_cast< Object* >(u"CollisionDetection::checkCollision(): BROKEN NORMAL @ "_j));
		auto stackTraceElement = Thread::currentThread()->getStackTrace();
		for (auto i = 2; i < 10 && i < stackTraceElement->length; i++) {
			_Console::println(static_cast< Object* >(::java::lang::StringBuilder().append((*stackTraceElement)[i]->getClassName())->append(u":"_j)
				->append((*stackTraceElement)[i]->getLineNumber())->toString()));
		}
		_Console::println();
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* CollisionDetection::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.physics.CollisionDetection", 38);
    return c;
}

void CollisionDetection::clinit()
{
	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		instance = nullptr;
		synchronizeObject = new Object();
		zeroVector = new Vector3();
		lineSegmentsTriangleIndices = (new int32_tArray({
			0,
			1,
			1,
			2,
			2,
			0
		}));
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* CollisionDetection::getClass0()
{
	return class_();
}

