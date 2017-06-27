// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/lang/UnsupportedOperationException.h>

using java::lang::UnsupportedOperationException;
extern void unimplemented_(const char16_t* name);
java::lang::UnsupportedOperationException::UnsupportedOperationException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::lang::UnsupportedOperationException::UnsupportedOperationException()
	: UnsupportedOperationException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::lang::UnsupportedOperationException::UnsupportedOperationException(String* arg0)
	: UnsupportedOperationException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::UnsupportedOperationException::UnsupportedOperationException(Throwable* arg0)
	: UnsupportedOperationException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::lang::UnsupportedOperationException::UnsupportedOperationException(String* arg0, Throwable* arg1)
	: UnsupportedOperationException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::lang::UnsupportedOperationException::serialVersionUID;

void UnsupportedOperationException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void UnsupportedOperationException::ctor()");
}

void UnsupportedOperationException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void UnsupportedOperationException::ctor(String* arg0)");
}

void UnsupportedOperationException::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void UnsupportedOperationException::ctor(Throwable* arg0)");
}

void UnsupportedOperationException::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void UnsupportedOperationException::ctor(String* arg0, Throwable* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* UnsupportedOperationException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.lang.UnsupportedOperationException", 39);
    return c;
}

java::lang::Class* UnsupportedOperationException::getClass0()
{
	return class_();
}

