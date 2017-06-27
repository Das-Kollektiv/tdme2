// Generated from /tdme/src/tdme/math/MathTools.java
#include <tdme/math/MathTools.h>

#include <java/lang/Math.h>

using tdme::math::MathTools;
using java::lang::Math;

MathTools::MathTools(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

MathTools::MathTools()
	: MathTools(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr float MathTools::EPSILON;

constexpr float MathTools::DEG2RAD;

constexpr float MathTools::g;

float MathTools::clamp(float value, float min, float max)
{
	clinit();
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

float MathTools::sign(float value)
{
	clinit();
	return value / Math::abs(value);
}

float MathTools::square(float value)
{
	clinit();
	return value * value;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* MathTools::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.math.MathTools", 19);
    return c;
}

java::lang::Class* MathTools::getClass0()
{
	return class_();
}

