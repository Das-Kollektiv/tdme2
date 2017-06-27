// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/zip/InflaterInputStream.h>

using java::util::zip::InflaterInputStream;
extern void unimplemented_(const char16_t* name);
java::util::zip::InflaterInputStream::InflaterInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::zip::InflaterInputStream::InflaterInputStream(InputStream* arg0)
	: InflaterInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::zip::InflaterInputStream::InflaterInputStream(InputStream* arg0, Inflater* arg1)
	: InflaterInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::zip::InflaterInputStream::InflaterInputStream(InputStream* arg0, Inflater* arg1, int32_t arg2)
	: InflaterInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}


void InflaterInputStream::ctor(InputStream* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InflaterInputStream::ctor(InputStream* arg0)");
}

void InflaterInputStream::ctor(InputStream* arg0, Inflater* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InflaterInputStream::ctor(InputStream* arg0, Inflater* arg1)");
}

void InflaterInputStream::ctor(InputStream* arg0, Inflater* arg1, int32_t arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InflaterInputStream::ctor(InputStream* arg0, Inflater* arg1, int32_t arg2)");
}

int32_t InflaterInputStream::available()
{ /* stub */
	unimplemented_(u"int32_t InflaterInputStream::available()");
	return 0;
}

void InflaterInputStream::close()
{ /* stub */
	unimplemented_(u"void InflaterInputStream::close()");
}

/* private: void InflaterInputStream::ensureOpen() */
void InflaterInputStream::fill()
{ /* stub */
	unimplemented_(u"void InflaterInputStream::fill()");
}

void InflaterInputStream::mark(int32_t arg0)
{ /* stub */
	unimplemented_(u"void InflaterInputStream::mark(int32_t arg0)");
}

bool InflaterInputStream::markSupported()
{ /* stub */
	unimplemented_(u"bool InflaterInputStream::markSupported()");
	return 0;
}

int32_t InflaterInputStream::read()
{ /* stub */
	unimplemented_(u"int32_t InflaterInputStream::read()");
	return 0;
}

int32_t InflaterInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t InflaterInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

void InflaterInputStream::reset()
{ /* stub */
	unimplemented_(u"void InflaterInputStream::reset()");
}

int64_t InflaterInputStream::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t InflaterInputStream::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InflaterInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.zip.InflaterInputStream", 33);
    return c;
}

int32_t InflaterInputStream::read(int8_tArray* arg0)
{
	return super::read(arg0);
}

java::lang::Class* InflaterInputStream::getClass0()
{
	return class_();
}

