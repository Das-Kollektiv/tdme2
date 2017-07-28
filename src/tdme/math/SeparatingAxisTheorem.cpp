// Generated from /tdme/src/tdme/math/SeparatingAxisTheorem.java
#include <tdme/math/SeparatingAxisTheorem.h>

#include <vector>

#include <java/lang/Float.h>
#include <java/lang/Math.h>
#include <tdme/math/MathTools.h>
#include <tdme/math/Vector3.h>
#include <Array.h>
#include <ObjectArray.h>
#include <SubArray.h>

using std::vector;

using tdme::math::SeparatingAxisTheorem;
using java::lang::Float;
using java::lang::Math;
using tdme::math::MathTools;
using tdme::math::Vector3;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace tdme {
namespace math {
typedef ::SubArray< ::tdme::math::Vector3, ::java::lang::ObjectArray > Vector3Array;
}  // namespace math
}  // namespace tdme

SeparatingAxisTheorem::SeparatingAxisTheorem(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

SeparatingAxisTheorem::SeparatingAxisTheorem()
	: SeparatingAxisTheorem(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void SeparatingAxisTheorem::ctor()
{
	super::ctor();
	init();
}

void SeparatingAxisTheorem::init()
{
	minMax1 = new floatArray(2);
	minMax2 = new floatArray(2);
	axis = new Vector3();
}

bool SeparatingAxisTheorem::checkAxis(Vector3* axis)
{
	auto axisXYZ = axis->getArray();
	if (Float::isNaN((*axisXYZ)[0]) || Float::isNaN((*axisXYZ)[1]) || Float::isNaN((*axisXYZ)[2])) {
		return false;
	}
	if (Math::abs((*axisXYZ)[0]) < MathTools::EPSILON && Math::abs((*axisXYZ)[1]) < MathTools::EPSILON && Math::abs((*axisXYZ)[2]) < MathTools::EPSILON) {
		return false;
	}
	return true;
}

float SeparatingAxisTheorem::doCalculatePoint(Vector3* point, Vector3* axis)
{
	auto distance = Vector3::computeDotProduct(point, axis);
	return distance;
}

void SeparatingAxisTheorem::doCalculateInterval(vector<Vector3*>* vertices, Vector3* axis, floatArray* result)
{
	auto distance = Vector3::computeDotProduct((*vertices)[0], axis);
	auto min = distance;
	auto max = distance;
	for (auto i = 1; i < vertices->size(); i++) {
		distance = Vector3::computeDotProduct((*vertices)[i], axis);
		if (distance < min)
			min = distance;

		if (distance > max)
			max = distance;

	}
	(*result)[0] = min;
	(*result)[1] = max;
}

bool SeparatingAxisTheorem::checkPointInVerticesOnAxis(vector<Vector3*>* vertices, Vector3* point, Vector3* axis)
{
	if (checkAxis(axis) == false)
		return true;

	doCalculateInterval(vertices, axis, minMax1);
	auto pOnAxis = doCalculatePoint(point, axis);
	return pOnAxis >= (*minMax1)[0] && pOnAxis <= (*minMax1)[1];
}

bool SeparatingAxisTheorem::doSpanIntersect(vector<Vector3*>* vertices1, vector<Vector3*>* vertices2, Vector3* axisTest, floatArray* resultArray, int32_t resultOffset)
{
	axis->set(axisTest)->normalize();
	doCalculateInterval(vertices1, axis, minMax1);
	doCalculateInterval(vertices2, axis, minMax2);
	auto min1 = (*minMax1)[0];
	auto max1 = (*minMax1)[1];
	auto min2 = (*minMax2)[0];
	auto max2 = (*minMax2)[1];
	auto len1 = max1 - min1;
	auto len2 = max2 - min2;
	auto min = Math::min(min1, min2);
	auto max = Math::max(max1, max2);
	auto len = max - min;
	if (len > len1 + len2) {
		return false;
	}
	if (min2 < min1) {
		axisTest->scale(-1.0f);
	}
	(*resultArray)[resultOffset] = len1 + len2 - len;
	return true;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* SeparatingAxisTheorem::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.SeparatingAxisTheorem", 31);
    return c;
}

java::lang::Class* SeparatingAxisTheorem::getClass0()
{
	return class_();
}

