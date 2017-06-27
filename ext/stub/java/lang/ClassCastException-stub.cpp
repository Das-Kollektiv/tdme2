// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/ClassCastException.h>

using java::lang::ClassCastException;
extern void unimplemented_(const char16_t* name);
java::lang::ClassCastException::ClassCastException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::ClassCastException::ClassCastException()
	: ClassCastException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::ClassCastException::ClassCastException(String* arg0)
	: ClassCastException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void ClassCastException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassCastException::ctor()");
}

void ClassCastException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassCastException::ctor(String* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ClassCastException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.ClassCastException", 28);
    return c;
}

java::lang::Class* ClassCastException::getClass0()
{
	return class_();
}

