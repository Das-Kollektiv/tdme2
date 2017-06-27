// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/FilterInputStream.h>

using java::io::FilterInputStream;
extern void unimplemented_(const char16_t* name);
java::io::FilterInputStream::FilterInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::FilterInputStream::FilterInputStream(InputStream* arg0)
	: FilterInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}


void FilterInputStream::ctor(InputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void FilterInputStream::ctor(InputStream* arg0)");
}

int32_t FilterInputStream::available()
{ /* stub */
	unimplemented_(u"int32_t FilterInputStream::available()");
	return 0;
}

void FilterInputStream::close()
{ /* stub */
	unimplemented_(u"void FilterInputStream::close()");
}

void FilterInputStream::mark(int32_t arg0)
{ /* stub */
	unimplemented_(u"void FilterInputStream::mark(int32_t arg0)");
}

bool FilterInputStream::markSupported()
{ /* stub */
	unimplemented_(u"bool FilterInputStream::markSupported()");
	return 0;
}

int32_t FilterInputStream::read()
{ /* stub */
	unimplemented_(u"int32_t FilterInputStream::read()");
	return 0;
}

int32_t FilterInputStream::read(int8_tArray* arg0)
{ /* stub */
	unimplemented_(u"int32_t FilterInputStream::read(int8_tArray* arg0)");
	return 0;
}

int32_t FilterInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t FilterInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

void FilterInputStream::reset()
{ /* stub */
	unimplemented_(u"void FilterInputStream::reset()");
}

int64_t FilterInputStream::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t FilterInputStream::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* FilterInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.FilterInputStream", 25);
    return c;
}

java::lang::Class* FilterInputStream::getClass0()
{
	return class_();
}

