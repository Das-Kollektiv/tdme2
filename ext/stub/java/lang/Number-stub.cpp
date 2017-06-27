// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Number.h>

using java::lang::Number;
extern void unimplemented_(const char16_t* name);
java::lang::Number::Number(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Number::Number()
	: Number(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int64_t java::lang::Number::serialVersionUID;

void Number::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Number::ctor()");
}

int8_t Number::byteValue()
{ /* stub */
	unimplemented_(u"int8_t Number::byteValue()");
	return 0;
}

int16_t Number::shortValue()
{ /* stub */
	unimplemented_(u"int16_t Number::shortValue()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Number::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Number", 16);
    return c;
}

java::lang::Class* Number::getClass0()
{
	return class_();
}

