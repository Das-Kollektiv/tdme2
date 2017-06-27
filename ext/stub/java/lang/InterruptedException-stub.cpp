// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/InterruptedException.h>

using java::lang::InterruptedException;
extern void unimplemented_(const char16_t* name);
java::lang::InterruptedException::InterruptedException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::InterruptedException::InterruptedException()
	: InterruptedException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::InterruptedException::InterruptedException(String* arg0)
	: InterruptedException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void InterruptedException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InterruptedException::ctor()");
}

void InterruptedException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InterruptedException::ctor(String* arg0)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InterruptedException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.InterruptedException", 30);
    return c;
}

java::lang::Class* InterruptedException::getClass0()
{
	return class_();
}

