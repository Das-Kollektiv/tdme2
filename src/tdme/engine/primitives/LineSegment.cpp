// Generated from /tdme/src/tdme/engine/primitives/LineSegment.java
#include <tdme/engine/primitives/LineSegment.h>

#include <java/lang/ArrayStoreException.h>
#include <java/lang/Math.h>
#include <tdme/engine/primitives/BoundingBox.h>
#include <tdme/engine/primitives/OrientedBoundingBox.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using tdme::engine::primitives::LineSegment;
using java::lang::ArrayStoreException;
using java::lang::Math;
using tdme::engine::primitives::BoundingBox;
using tdme::engine::primitives::OrientedBoundingBox;
using tdme::math::MathTools;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

LineSegment::LineSegment(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

LineSegment::LineSegment()
	: LineSegment(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void LineSegment::ctor()
{
	super::ctor();
	init();
}

void LineSegment::init()
{
	d = new Vector3();
	d1 = new Vector3();
	d2 = new Vector3();
	r = new Vector3();
	c1 = new Vector3();
	c2 = new Vector3();
	n = new Vector3();
	t = new Vector3();
}

bool LineSegment::doesLineSegmentsCollide(Vector3* p1, Vector3* q1, Vector3* p2, Vector3* q2, Vector3* p)
{
	computeClosestPointsOnLineSegments(p1, q1, p2, q2, c1, c2);
	if (c1->sub(c2)->computeLength() < MathTools::EPSILON) {
		p->set(c2);
		return true;
	} else {
		return false;
	}
}

void LineSegment::computeClosestPointsOnLineSegments(Vector3* p1, Vector3* q1, Vector3* p2, Vector3* q2, Vector3* c1, Vector3* c2)
{
	float s;
	float t;
	d1->set(q1)->sub(p1);
	d2->set(q2)->sub(p2);
	r->set(p1)->sub(p2);
	auto a = Vector3::computeDotProduct(d1, d1);
	auto e = Vector3::computeDotProduct(d2, d2);
	auto f = Vector3::computeDotProduct(d2, r);
	if (a <= MathTools::EPSILON && e <= MathTools::EPSILON) {
		s = 0.0f;
		t = 0.0f;
		c1 = p1;
		c2 = p2;
		return;
	}
	if (a <= MathTools::EPSILON) {
		s = 0.0f;
		t = f / e;
		t = MathTools::clamp(t, 0.0f, 1.0f);
	} else {
		auto c = Vector3::computeDotProduct(d1, r);
		if (e <= MathTools::EPSILON) {
			t = 0.0f;
			s = MathTools::clamp(-c / a, 0.0f, 1.0f);
		} else {
			auto b = Vector3::computeDotProduct(d1, d2);
			auto denom = a * e - b * b;
			if (denom != 0.0f) {
				s = MathTools::clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			} else {
				s = 0.0f;
			}
			t = (b * s + f) / e;
			if (t < 0.0f) {
				t = 0.0f;
				s = MathTools::clamp(-c / a, 0.0f, 1.0f);
			} else if (t > 1.0f) {
				t = 1.0f;
				s = MathTools::clamp((b - c) / a, 0.0f, 1.0f);
			}
		}
	}
	c1->set(p1)->add(d1->scale(s));
	c2->set(p2)->add(d2->scale(t));
}

bool LineSegment::doesBoundingBoxCollideWithLineSegment(BoundingBox* boundingBox, Vector3* p, Vector3* q, Vector3* contactMin, Vector3* contactMax)
{
	auto tmin = 0.0f;
	auto tmax = 1.0f;
	auto minXYZ = boundingBox->min->getArray();
	auto maxXYZ = boundingBox->max->getArray();
	d->set(q)->sub(p);
	auto directionXYZ = d->getArray();
	auto pointXYZ = p->getArray();
	for (auto i = 0; i < 3; i++) {
		if (Math::abs((*directionXYZ)[i]) < MathTools::EPSILON && ((*pointXYZ)[i] <= (*minXYZ)[i] || (*pointXYZ)[i] >= (*maxXYZ)[i])) {
			return false;
		} else {
			auto odd = 1.0f / (*directionXYZ)[i];
			auto t1 = ((*minXYZ)[i] - (*pointXYZ)[i]) * odd;
			auto t2 = ((*maxXYZ)[i] - (*pointXYZ)[i]) * odd;
			if (t1 > t2) {
				auto tmp = t1;
				t1 = t2;
				t2 = tmp;
			}
			tmin = Math::max(tmin, t1);
			tmax = Math::min(tmax, t2);
			if (tmin > tmax)
				return false;

		}
	}
	if (tmin > 1.0)
		return false;

	contactMin->set(p)->add(d1->set(d)->scale(tmin));
	contactMax->set(p)->add(d2->set(d)->scale(tmax));
	return true;
}

bool LineSegment::doesOrientedBoundingBoxCollideWithLineSegment(OrientedBoundingBox* orientedBoundingBox, Vector3* p, Vector3* q, Vector3* contactMin, Vector3* contactMax)
{
	auto tmin = 0.0f;
	auto tmax = 1.0f;
	auto obbAxes = orientedBoundingBox->axes;
	auto obbCenter = orientedBoundingBox->center;
	auto obbHalfExtension = orientedBoundingBox->halfExtension;
	auto obbHalfExtensionXYZ = obbHalfExtension->getArray();
	d->set(q)->sub(p);
	for (auto i = 0; i < 3; i++) {
		auto directionLengthOnAxis = Vector3::computeDotProduct(d, (*obbAxes)[i]);
		auto obbExtensionLengthOnAxis = (*obbHalfExtensionXYZ)[i];
		auto obbCenterLengthOnAxis = Vector3::computeDotProduct(obbCenter, (*obbAxes)[i]);
		auto pointLengthOnAxis = Vector3::computeDotProduct(p, (*obbAxes)[i]);
		if (Math::abs(directionLengthOnAxis) < MathTools::EPSILON && (pointLengthOnAxis <= obbCenterLengthOnAxis - obbExtensionLengthOnAxis || pointLengthOnAxis >= obbCenterLengthOnAxis + obbExtensionLengthOnAxis)) {
			return false;
		} else {
			auto odd = 1.0f / directionLengthOnAxis;
			auto t1 = (obbCenterLengthOnAxis - obbExtensionLengthOnAxis - pointLengthOnAxis) * odd;
			auto t2 = (obbCenterLengthOnAxis + obbExtensionLengthOnAxis - pointLengthOnAxis) * odd;
			if (t1 > t2) {
				auto tmp = t1;
				t1 = t2;
				t2 = tmp;
			}
			tmin = Math::max(tmin, t1);
			tmax = Math::min(tmax, t2);
			if (tmin > tmax)
				return false;

		}
	}
	if (tmin > 1.0)
		return false;

	contactMin->set(p)->add(d1->set(d)->scale(tmin));
	contactMax->set(p)->add(d2->set(d)->scale(tmax));
	return true;
}

bool LineSegment::doesLineSegmentCollideWithTriangle(Vector3* p1, Vector3* p2, Vector3* p3, Vector3* r1, Vector3* r2, Vector3* contact)
{
	Vector3::computeCrossProduct(d1->set(p2)->sub(p1), d2->set(p3)->sub(p1), n)->normalize();
	auto dist1 = Vector3::computeDotProduct(d1->set(r1)->sub(p1), n);
	auto dist2 = Vector3::computeDotProduct(d2->set(r2)->sub(p1), n);
	if (dist1 * dist2 >= 0.0f) {
		return false;
	}
	if (Math::abs(dist1 - dist2) < MathTools::EPSILON) {
		return false;
	}
	contact->set(r2)->sub(r1)->scale(-dist1 / (dist2 - dist1));
	contact->add(r1);
	Vector3::computeCrossProduct(n, d1->set(p2)->sub(p1), t);
	if (Vector3::computeDotProduct(t, d2->set(contact)->sub(p1)) < 0.0f) {
		return false;
	}
	Vector3::computeCrossProduct(n, d1->set(p3)->sub(p2), t);
	if (Vector3::computeDotProduct(t, d2->set(contact)->sub(p2)) < 0.0f) {
		return false;
	}
	Vector3::computeCrossProduct(n, d1->set(p1)->sub(p3), t);
	if (Vector3::computeDotProduct(t, d2->set(contact)->sub(p1)) < 0.0f) {
		return false;
	}
	return true;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* LineSegment::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.primitives.LineSegment", 34);
    return c;
}

java::lang::Class* LineSegment::getClass0()
{
	return class_();
}

