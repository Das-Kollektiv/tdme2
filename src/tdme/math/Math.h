// Generated from /tdme/src/tdme/math/MathTools.java

#pragma once

#include <cmath>
#include <cstdlib>

#include <fwd-tdme.h>
#include <tdme/math/fwd-tdme.h>

/** 
 * Math
 * @author Andreas Drewke
 * @version $Id$
 */
class tdme::math::Math final
{
public:
	static constexpr double E { 2.718281828459045 };
	static constexpr double PI { 3.141592653589793 };

	inline static int32_t abs(int32_t arg0) {
		return ::abs(arg0);
	}

	inline static float abs(float arg0) {
		return ::fabs(arg0);
	}

	inline static float acos(float arg0) {
		return ::acosf(arg0);
	}

	inline static float asin(float arg0) {
		return ::asin(arg0);
	}

	inline static float atan(float arg0) {
		return ::atanf(arg0);
	}

	inline static float atan2(float arg0, float arg1) {
		return ::atan2f(arg0, arg1);
	}

	inline static float ceil(float arg0) {
		return ::ceilf(arg0);
	}

	inline static float cos(float arg0) {
		return ::cosf(arg0);
	}

	inline static float floor(float arg0) {
		return std::floorf(arg0);
	}

	inline static int32_t max(int32_t arg0, int32_t arg1) {
		return arg0 > arg1?arg0:arg1;
	}

	inline static float max(float arg0, float arg1) {
		return arg0 > arg1?arg0:arg1;
	}

	inline static int32_t min(int32_t arg0, int32_t arg1) {
		return arg0 < arg1?arg0:arg1;
	}

	inline static float min(float arg0, float arg1) {
		return arg0 < arg1?arg0:arg1;
	}

	inline static double pow(double arg0, double arg1) {
		return std::pow(arg0, arg1);
	}

	inline static float random() {
		return (float)rand() / RAND_MAX;
	}

	inline static float sin(float arg0) {
		return ::sinf(arg0);
	}

	inline static float sqrt(float arg0) {
		return ::sqrtf(arg0);
	}

	inline static float tan(float arg0) {
		return ::tanf(arg0);
	}

};
