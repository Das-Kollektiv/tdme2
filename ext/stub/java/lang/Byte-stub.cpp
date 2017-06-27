// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Byte.h>

using java::lang::Byte;
extern void unimplemented_(const char16_t* name);
java::lang::Byte::Byte(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Byte::Byte(int8_t arg0)
	: Byte(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Byte::Byte(String* arg0)
	: Byte(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int8_t java::lang::Byte::MAX_VALUE;
constexpr int8_t java::lang::Byte::MIN_VALUE;
constexpr int32_t java::lang::Byte::SIZE;
Class* java::lang::Byte::TYPE;
constexpr int64_t java::lang::Byte::serialVersionUID;

void Byte::ctor(int8_t arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Byte::ctor(int8_t arg0)");
}

void Byte::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Byte::ctor(String* arg0)");
}

int8_t Byte::byteValue()
{ /* stub */
	unimplemented_(u"int8_t Byte::byteValue()");
	return 0;
}

int32_t Byte::compareTo(Byte* arg0)
{ /* stub */
	unimplemented_(u"int32_t Byte::compareTo(Byte* arg0)");
	return 0;
}

int32_t Byte::compareTo(Object* o)
{ 
	return compareTo(dynamic_cast< Byte* >(o));
}

Byte* Byte::decode(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Byte* Byte::decode(String* arg0)");
	return 0;
}

double Byte::doubleValue()
{ /* stub */
	unimplemented_(u"double Byte::doubleValue()");
	return 0;
}

bool Byte::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Byte::equals(Object* arg0)");
	return 0;
}

float Byte::floatValue()
{ /* stub */
	unimplemented_(u"float Byte::floatValue()");
	return 0;
}

int32_t Byte::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Byte::hashCode()");
	return 0;
}

int32_t Byte::intValue()
{ /* stub */
	unimplemented_(u"int32_t Byte::intValue()");
	return 0;
}

int64_t Byte::longValue()
{ /* stub */
	unimplemented_(u"int64_t Byte::longValue()");
	return 0;
}

int8_t Byte::parseByte(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"int8_t Byte::parseByte(String* arg0)");
	return 0;
}

int8_t Byte::parseByte(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"int8_t Byte::parseByte(String* arg0, int32_t arg1)");
	return 0;
}

int16_t Byte::shortValue()
{ /* stub */
	unimplemented_(u"int16_t Byte::shortValue()");
	return 0;
}

String* Byte::toString()
{ /* stub */
	unimplemented_(u"String* Byte::toString()");
	return 0;
}

String* Byte::toString(int8_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* Byte::toString(int8_t arg0)");
	return 0;
}

Byte* Byte::valueOf(int8_t arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Byte* Byte::valueOf(int8_t arg0)");
	return 0;
}

Byte* Byte::valueOf(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Byte* Byte::valueOf(String* arg0)");
	return 0;
}

Byte* Byte::valueOf(String* arg0, int32_t arg1)
{ /* stub */
	clinit();
	unimplemented_(u"Byte* Byte::valueOf(String* arg0, int32_t arg1)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Byte::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Byte", 14);
    return c;
}

java::lang::Class* Byte::getClass0()
{
	return class_();
}

