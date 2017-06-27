// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/IOException.h>

using java::io::IOException;
extern void unimplemented_(const char16_t* name);
java::io::IOException::IOException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::IOException::IOException()
	: IOException(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::io::IOException::IOException(String* arg0)
	: IOException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::IOException::IOException(Throwable* arg0)
	: IOException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::IOException::IOException(String* arg0, Throwable* arg1)
	: IOException(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int64_t java::io::IOException::serialVersionUID;

void IOException::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IOException::ctor()");
}

void IOException::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IOException::ctor(String* arg0)");
}

void IOException::ctor(Throwable* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IOException::ctor(Throwable* arg0)");
}

void IOException::ctor(String* arg0, Throwable* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void IOException::ctor(String* arg0, Throwable* arg1)");
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* IOException::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.IOException", 19);
    return c;
}

java::lang::Class* IOException::getClass0()
{
	return class_();
}

