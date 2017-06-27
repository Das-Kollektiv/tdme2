// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/ClassNotFoundException.h>

using java::lang::ClassNotFoundException;
extern void unimplemented_(const char16_t* name);
java::lang::ClassNotFoundException::ClassNotFoundException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::ClassNotFoundException::ClassNotFoundException()
	: ClassNotFoundException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::ClassNotFoundException::ClassNotFoundException(String* arg0)
	: ClassNotFoundException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::ClassNotFoundException::ClassNotFoundException(String* arg0, Throwable* arg1)
	: ClassNotFoundException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::ClassNotFoundException::serialVersionUID;

void ClassNotFoundException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassNotFoundException::ctor()");
}

void ClassNotFoundException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassNotFoundException::ctor(String* arg0)");
}

void ClassNotFoundException::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ClassNotFoundException::ctor(String* arg0, Throwable* arg1)");
}

Throwable* ClassNotFoundException::getCause()
{ /* stub */
	unimplemented_(u"Throwable* ClassNotFoundException::getCause()");
	return 0;
}

Throwable* ClassNotFoundException::getException()
{ /* stub */
	unimplemented_(u"Throwable* ClassNotFoundException::getException()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ClassNotFoundException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.ClassNotFoundException", 32);
    return c;
}

java::lang::Class* ClassNotFoundException::getClass0()
{
	return class_();
}

