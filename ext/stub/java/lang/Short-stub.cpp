// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Short.h>

using java::lang::Short;
extern void unimplemented_(const char16_t* name);
java::lang::Short::Short(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Short::Short(int16_t arg0)
	: Short(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Short::Short(String* arg0)
	: Short(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int16_t java::lang::Short::MAX_VALUE;
constexpr int16_t java::lang::Short::MIN_VALUE;
constexpr int32_t java::lang::Short::SIZE;
Class* java::lang::Short::TYPE;
constexpr int64_t java::lang::Short::serialVersionUID;

void Short::ctor(int16_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Short::ctor(int16_t arg0)");
}

void Short::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Short::ctor(String* arg0)");
}

int8_t Short::byteValue()
{ /* stub */
	unimplemented_(u"int8_t Short::byteValue()");
	return 0;
}

int32_t Short::compareTo(Short* arg0)
{ /* stub */
	unimplemented_(u"int32_t Short::compareTo(Short* arg0)");
	return 0;
}

int32_t Short::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< Short* >(o));
}

Short* Short::decode(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Short* Short::decode(String* arg0)");
	return 0;
}

double Short::doubleValue()
{ /* stub */
	unimplemented_(u"double Short::doubleValue()");
	return 0;
}

bool Short::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Short::equals(Object* arg0)");
	return 0;
}

float Short::floatValue()
{ /* stub */
	unimplemented_(u"float Short::floatValue()");
	return 0;
}

int32_t Short::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Short::hashCode()");
	return 0;
}

int32_t Short::intValue()
{ /* stub */
	unimplemented_(u"int32_t Short::intValue()");
	return 0;
}

int64_t Short::longValue()
{ /* stub */
	unimplemented_(u"int64_t Short::longValue()");
	return 0;
}

int16_t Short::parseShort(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int16_t Short::parseShort(String* arg0)");
	return 0;
}

int16_t Short::parseShort(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int16_t Short::parseShort(String* arg0, int32_t arg1)");
	return 0;
}

int16_t Short::reverseBytes(int16_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int16_t Short::reverseBytes(int16_t arg0)");
	return 0;
}

int16_t Short::shortValue()
{ /* stub */
	unimplemented_(u"int16_t Short::shortValue()");
	return 0;
}

String* Short::toString()
{ /* stub */
	unimplemented_(u"String* Short::toString()");
	return 0;
}

String* Short::toString(int16_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Short::toString(int16_t arg0)");
	return 0;
}

Short* Short::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Short* Short::valueOf(String* arg0)");
	return 0;
}

Short* Short::valueOf(int16_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Short* Short::valueOf(int16_t arg0)");
	return 0;
}

Short* Short::valueOf(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Short* Short::valueOf(String* arg0, int32_t arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Short::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Short", 15);
    return c;
}

java::lang::Class* Short::getClass0()
{
	return class_();
}

