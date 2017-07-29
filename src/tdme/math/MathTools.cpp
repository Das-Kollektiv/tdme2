// Generated from /tdme/src/tdme/math/MathTools.java
#include <tdme/math/MathTools.h>

#include <java/lang/Math.h>

using tdme::math::MathTools;
using java::lang::Math;

constexpr float MathTools::EPSILON;

constexpr float MathTools::DEG2RAD;

constexpr float MathTools::g;

float MathTools::clamp(float value, float min, float max)
{
	if (value < min)
		return min;

	if (value > max)
		return max;

	return value;
}

float MathTools::sign(float value)
{
	return value / Math::abs(value);
}

float MathTools::square(float value)
{
	return value * value;
}
