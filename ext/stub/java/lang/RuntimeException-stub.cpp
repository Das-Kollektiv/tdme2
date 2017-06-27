// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/RuntimeException.h>

using java::lang::RuntimeException;
extern void unimplemented_(const char16_t* name);
java::lang::RuntimeException::RuntimeException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::RuntimeException::RuntimeException()
	: RuntimeException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::RuntimeException::RuntimeException(String* arg0)
	: RuntimeException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::RuntimeException::RuntimeException(Throwable* arg0)
	: RuntimeException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::RuntimeException::RuntimeException(String* arg0, Throwable* arg1)
	: RuntimeException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::RuntimeException::serialVersionUID;

void RuntimeException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void RuntimeException::ctor()");
}

void RuntimeException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void RuntimeException::ctor(String* arg0)");
}

void RuntimeException::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void RuntimeException::ctor(Throwable* arg0)");
}

void RuntimeException::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void RuntimeException::ctor(String* arg0, Throwable* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* RuntimeException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.RuntimeException", 26);
    return c;
}

java::lang::Class* RuntimeException::getClass0()
{
	return class_();
}

