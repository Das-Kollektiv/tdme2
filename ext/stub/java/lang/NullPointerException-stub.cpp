// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/NullPointerException.h>

using java::lang::NullPointerException;
extern void unimplemented_(const char16_t* name);
java::lang::NullPointerException::NullPointerException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::NullPointerException::NullPointerException()
	: NullPointerException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::NullPointerException::NullPointerException(String* arg0)
	: NullPointerException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void NullPointerException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void NullPointerException::ctor()");
}

void NullPointerException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void NullPointerException::ctor(String* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* NullPointerException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.NullPointerException", 30);
    return c;
}

java::lang::Class* NullPointerException::getClass0()
{
	return class_();
}

