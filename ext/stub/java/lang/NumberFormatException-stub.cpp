// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/NumberFormatException.h>

using java::lang::NumberFormatException;
extern void unimplemented_(const char16_t* name);
java::lang::NumberFormatException::NumberFormatException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::NumberFormatException::NumberFormatException()
	: NumberFormatException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::NumberFormatException::NumberFormatException(String* arg0)
	: NumberFormatException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int64_t java::lang::NumberFormatException::serialVersionUID;

void NumberFormatException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void NumberFormatException::ctor()");
}

void NumberFormatException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void NumberFormatException::ctor(String* arg0)");
}

NumberFormatException* NumberFormatException::forInputString(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"NumberFormatException* NumberFormatException::forInputString(String* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* NumberFormatException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.NumberFormatException", 31);
    return c;
}

java::lang::Class* NumberFormatException::getClass0()
{
	return class_();
}

