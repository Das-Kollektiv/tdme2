// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/InputStream.h>

using java::io::InputStream;
extern void unimplemented_(const char16_t* name);
java::io::InputStream::InputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::InputStream::InputStream()
	: InputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

constexpr int32_t java::io::InputStream::MAX_SKIP_BUFFER_SIZE;

void InputStream::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputStream::ctor()");
}

int32_t InputStream::available()
{ /* stub */
	unimplemented_(u"int32_t InputStream::available()");
	return 0;
}

void InputStream::close()
{ /* stub */
	unimplemented_(u"void InputStream::close()");
}

void InputStream::mark(int32_t readlimit)
{ /* stub */
	unimplemented_(u"void InputStream::mark(int32_t readlimit)");
}

bool InputStream::markSupported()
{ /* stub */
	unimplemented_(u"bool InputStream::markSupported()");
	return 0;
}

int32_t InputStream::read(int8_tArray* b)
{ /* stub */
	unimplemented_(u"int32_t InputStream::read(int8_tArray* b)");
	return 0;
}

int32_t InputStream::read(int8_tArray* b, int32_t off, int32_t len)
{ /* stub */
	unimplemented_(u"int32_t InputStream::read(int8_tArray* b, int32_t off, int32_t len)");
	return 0;
}

void InputStream::reset()
{ /* stub */
	unimplemented_(u"void InputStream::reset()");
}

int64_t InputStream::skip(int64_t n)
{ /* stub */
	unimplemented_(u"int64_t InputStream::skip(int64_t n)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.InputStream", 19);
    return c;
}

java::lang::Class* InputStream::getClass0()
{
	return class_();
}

