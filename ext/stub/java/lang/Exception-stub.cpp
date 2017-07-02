// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/Exception.h>

using java::lang::Exception;
extern void unimplemented_(const char16_t* name);
java::lang::Exception::Exception(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::Exception::Exception()
	: Exception(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::Exception::Exception(String* arg0)
	: Exception(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Exception::Exception(Throwable* arg0)
	: Exception(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::Exception::Exception(String* arg0, Throwable* arg1)
	: Exception(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::Exception::serialVersionUID;

void Exception::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Exception::ctor()");
}

void Exception::ctor(String* arg0)
{ /* stub */
	super::ctor(arg0);
}

void Exception::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Exception::ctor(Throwable* arg0)");
}

void Exception::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Exception::ctor(String* arg0, Throwable* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Exception::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.Exception", 19);
    return c;
}

java::lang::Class* Exception::getClass0()
{
	return class_();
}

