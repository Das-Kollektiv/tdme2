// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/ByteArrayInputStream.h>

using java::io::ByteArrayInputStream;
extern void unimplemented_(const char16_t* name);
java::io::ByteArrayInputStream::ByteArrayInputStream(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::ByteArrayInputStream::ByteArrayInputStream(int8_tArray* arg0)
	: ByteArrayInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::ByteArrayInputStream::ByteArrayInputStream(int8_tArray* arg0, int32_t arg1, int32_t arg2)
	: ByteArrayInputStream(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}


void ByteArrayInputStream::ctor(int8_tArray* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ByteArrayInputStream::ctor(int8_tArray* arg0)");
}

void ByteArrayInputStream::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void ByteArrayInputStream::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

int32_t ByteArrayInputStream::available()
{ /* stub */
	unimplemented_(u"int32_t ByteArrayInputStream::available()");
	return 0;
}

void ByteArrayInputStream::close()
{ /* stub */
	unimplemented_(u"void ByteArrayInputStream::close()");
}

void ByteArrayInputStream::mark(int32_t arg0)
{ /* stub */
	unimplemented_(u"void ByteArrayInputStream::mark(int32_t arg0)");
}

bool ByteArrayInputStream::markSupported()
{ /* stub */
	unimplemented_(u"bool ByteArrayInputStream::markSupported()");
	return 0;
}

int32_t ByteArrayInputStream::read()
{ /* stub */
	unimplemented_(u"int32_t ByteArrayInputStream::read()");
	return 0;
}

int32_t ByteArrayInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t ByteArrayInputStream::read(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

void ByteArrayInputStream::reset()
{ /* stub */
	unimplemented_(u"void ByteArrayInputStream::reset()");
}

int64_t ByteArrayInputStream::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t ByteArrayInputStream::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* ByteArrayInputStream::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.ByteArrayInputStream", 28);
    return c;
}

int32_t ByteArrayInputStream::read(int8_tArray* arg0)
{
	return super::read(arg0);
}

java::lang::Class* ByteArrayInputStream::getClass0()
{
	return class_();
}

