// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/IllegalArgumentException.h>

using java::lang::IllegalArgumentException;
extern void unimplemented_(const char16_t* name);
java::lang::IllegalArgumentException::IllegalArgumentException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::IllegalArgumentException::IllegalArgumentException()
	: IllegalArgumentException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::IllegalArgumentException::IllegalArgumentException(String* arg0)
	: IllegalArgumentException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::IllegalArgumentException::IllegalArgumentException(Throwable* arg0)
	: IllegalArgumentException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::IllegalArgumentException::IllegalArgumentException(String* arg0, Throwable* arg1)
	: IllegalArgumentException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::IllegalArgumentException::serialVersionUID;

void IllegalArgumentException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IllegalArgumentException::ctor()");
}

void IllegalArgumentException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IllegalArgumentException::ctor(String* arg0)");
}

void IllegalArgumentException::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IllegalArgumentException::ctor(Throwable* arg0)");
}

void IllegalArgumentException::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IllegalArgumentException::ctor(String* arg0, Throwable* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* IllegalArgumentException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.IllegalArgumentException", 34);
    return c;
}

java::lang::Class* IllegalArgumentException::getClass0()
{
	return class_();
}

