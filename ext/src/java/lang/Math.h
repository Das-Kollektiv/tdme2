// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::util::Random;


struct default_init_tag;
class java::lang::Math final
	: public Object
{

public:
	typedef Object super;
	static constexpr double E { 2.718281828459045 };
	static constexpr double PI { 3.141592653589793 };

private:
	static int64_t negativeZeroDoubleBits;
	static int64_t negativeZeroFloatBits;
	static Random* randomNumberGenerator;

	/*void ctor(); (private) */

public:
	static double IEEEremainder(double arg0, double arg1);
	static int32_t abs(int32_t arg0);
	static int64_t abs(int64_t arg0);
	static float abs(float arg0);
	static double abs(double arg0);
	static double acos(double arg0);
	static double asin(double arg0);
	static double atan(double arg0);
	static double atan2(double arg0, double arg1);
	static double cbrt(double arg0);
	static double ceil(double arg0);
	static double copySign(double arg0, double arg1);
	static float copySign(float arg0, float arg1);
	static double cos(double arg0);
	static double cosh(double arg0);
	static double exp(double arg0);
	static double expm1(double arg0);
	static double floor(double arg0);
	static int32_t getExponent(float arg0);
	static int32_t getExponent(double arg0);
	static double hypot(double arg0, double arg1);
	/*static void initRNG(); (private) */
	static double log(double arg0);
	static double log10(double arg0);
	static double log1p(double arg0);
	static int32_t max(int32_t arg0, int32_t arg1);
	static int64_t max(int64_t arg0, int64_t arg1);
	static float max(float arg0, float arg1);
	static double max(double arg0, double arg1);
	static int32_t min(int32_t arg0, int32_t arg1);
	static int64_t min(int64_t arg0, int64_t arg1);
	static float min(float arg0, float arg1);
	static double min(double arg0, double arg1);
	static double nextAfter(double arg0, double arg1);
	static float nextAfter(float arg0, double arg1);
	static double nextUp(double arg0);
	static float nextUp(float arg0);
	static double pow(double arg0, double arg1);
	static double random();
	static double rint(double arg0);
	static int32_t round(float arg0);
	static int64_t round(double arg0);
	static double scalb(double arg0, int32_t arg1);
	static float scalb(float arg0, int32_t arg1);
	static double signum(double arg0);
	static float signum(float arg0);
	static double sin(double arg0);
	static double sinh(double arg0);
	static double sqrt(double arg0);
	static double tan(double arg0);
	static double tanh(double arg0);
	static double toDegrees(double arg0);
	static double toRadians(double arg0);
	static double ulp(double arg0);
	static float ulp(float arg0);

	// Generated
	Math();
protected:
	Math(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
