// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <cmath>
#include <string>

#include <java/lang/Float.h>
#include <java/lang/String.h>

using java::lang::Float;
extern void unimplemented_(const char16_t* name);
java::lang::Float::Float(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Float::Float(float arg0)
	: Float(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Float::Float(double arg0)
	: Float(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Float::Float(String* arg0)
	: Float(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int32_t java::lang::Float::MAX_EXPONENT;
constexpr float java::lang::Float::MAX_VALUE;
constexpr int32_t java::lang::Float::MIN_EXPONENT;
constexpr float java::lang::Float::MIN_NORMAL;
constexpr float java::lang::Float::MIN_VALUE;
constexpr float java::lang::Float::NEGATIVE_INFINITY;
constexpr float java::lang::Float::NaN;
constexpr float java::lang::Float::POSITIVE_INFINITY;
constexpr int32_t java::lang::Float::SIZE;
Class* java::lang::Float::TYPE;
constexpr int64_t java::lang::Float::serialVersionUID;

void Float::ctor(float arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Float::ctor(float arg0)");
}

void Float::ctor(double arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Float::ctor(double arg0)");
}

void Float::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Float::ctor(String* arg0)");
}

int8_t Float::byteValue()
{ /* stub */
	unimplemented_(u"int8_t Float::byteValue()");
	return 0;
}

int32_t Float::compare(float arg0, float arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Float::compare(float arg0, float arg1)");
	return 0;
}

int32_t Float::compareTo(Float* arg0)
{ /* stub */
	unimplemented_(u"int32_t Float::compareTo(Float* arg0)");
	return 0;
}

int32_t Float::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< Float* >(o));
}

double Float::doubleValue()
{ /* stub */
	unimplemented_(u"double Float::doubleValue()");
	return 0;
}

bool Float::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Float::equals(Object* arg0)");
	return 0;
}

int32_t Float::floatToIntBits(float arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t Float::floatToIntBits(float arg0)");
	return 0;
}

float Float::floatValue()
{ /* stub */
	unimplemented_(u"float Float::floatValue()");
	return 0;
}

int32_t Float::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Float::hashCode()");
	return 0;
}

int32_t Float::intValue()
{ /* stub */
	unimplemented_(u"int32_t Float::intValue()");
	return 0;
}

bool Float::isInfinite()
{ /* stub */
	unimplemented_(u"bool Float::isInfinite()");
	return 0;
}

bool Float::isInfinite(float arg0)
{ /* stub */
	clinit();
	unimplemented_(u"bool Float::isInfinite(float arg0)");
	return 0;
}

bool Float::isNaN()
{ /* stub */
	unimplemented_(u"bool Float::isNaN()");
	return 0;
}

bool Float::isNaN(float arg0)
{ /* stub */
	clinit();
	return isnan(arg0) != 0;
}

int64_t Float::longValue()
{ /* stub */
	unimplemented_(u"int64_t Float::longValue()");
	return 0;
}

float Float::parseFloat(String* arg0)
{ /* stub */
	return stof(arg0->getCPPWString());
}

int16_t Float::shortValue()
{ /* stub */
	unimplemented_(u"int16_t Float::shortValue()");
	return 0;
}

String* Float::toHexString(float arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Float::toHexString(float arg0)");
	return 0;
}

String* Float::toString()
{ /* stub */
	unimplemented_(u"String* Float::toString()");
	return 0;
}

String* Float::toString(float arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Float::toString(float arg0)");
	return 0;
}

Float* Float::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Float* Float::valueOf(String* arg0)");
	return 0;
}

Float* Float::valueOf(float arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Float* Float::valueOf(float arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Float::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Float", 15);
    return c;
}

java::lang::Class* Float::getClass0()
{
	return class_();
}

