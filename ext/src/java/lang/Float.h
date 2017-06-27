// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/Number.h>
#include <java/lang/Comparable.h>

using java::lang::Number;
using java::lang::Comparable;
using java::lang::Class;
using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class java::lang::Float final
	: public Number
	, public Comparable
{

public:
	typedef Number super;
	static constexpr int32_t MAX_EXPONENT { 127 };
	static constexpr float MAX_VALUE { 3.4028235E38f };
	static constexpr int32_t MIN_EXPONENT { -126 };
	static constexpr float MIN_NORMAL { 1.17549435E-38f };
	static constexpr float MIN_VALUE { 1.4E-45f };
	static constexpr float NEGATIVE_INFINITY { (-std::numeric_limits<float>::infinity()) };
	static constexpr float NaN { std::numeric_limits<float>::quiet_NaN() };
	static constexpr float POSITIVE_INFINITY { std::numeric_limits<float>::infinity() };
	static constexpr int32_t SIZE { 32 };
	static Class* TYPE;

private:
	static constexpr int64_t serialVersionUID { -2671257302660747028LL };
	float value {  };

protected:
	void ctor(float arg0);
	void ctor(double arg0);
	void ctor(String* arg0);

public:
	int8_t byteValue() override;
	static int32_t compare(float arg0, float arg1);
	int32_t compareTo(Float* arg0);
	double doubleValue() override;
	bool equals(Object* arg0) override;
	static int32_t floatToIntBits(float arg0);
	static int32_t floatToRawIntBits(float arg0);
	float floatValue() override;
	int32_t hashCode() override;
	static float intBitsToFloat(int32_t arg0);
	int32_t intValue() override;
	bool isInfinite();
	static bool isInfinite(float arg0);
	bool isNaN();
	static bool isNaN(float arg0);
	int64_t longValue() override;
	static float parseFloat(String* arg0);
	int16_t shortValue() override;
	static String* toHexString(float arg0);
	String* toString() override;
	static String* toString(float arg0);
	static Float* valueOf(String* arg0);
	static Float* valueOf(float arg0);

	// Generated
	Float(float arg0);
	Float(double arg0);
	Float(String* arg0);
protected:
	Float(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
};
