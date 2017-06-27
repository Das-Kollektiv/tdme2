// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/Reader.h>

using java::io::Reader;
extern void unimplemented_(const char16_t* name);
java::io::Reader::Reader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::Reader::Reader()
	: Reader(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

java::io::Reader::Reader(Object* arg0)
	: Reader(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

constexpr int32_t java::io::Reader::maxSkipBufferSize;

void Reader::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Reader::ctor()");
}

void Reader::ctor(Object* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Reader::ctor(Object* arg0)");
}

void Reader::mark(int32_t arg0)
{ /* stub */
	unimplemented_(u"void Reader::mark(int32_t arg0)");
}

bool Reader::markSupported()
{ /* stub */
	unimplemented_(u"bool Reader::markSupported()");
	return 0;
}

int32_t Reader::read()
{ /* stub */
	unimplemented_(u"int32_t Reader::read()");
	return 0;
}

int32_t Reader::read(CharBuffer* arg0)
{ /* stub */
	unimplemented_(u"int32_t Reader::read(CharBuffer* arg0)");
	return 0;
}

int32_t Reader::read(char16_tArray* arg0)
{ /* stub */
	unimplemented_(u"int32_t Reader::read(char16_tArray* arg0)");
	return 0;
}

bool Reader::ready()
{ /* stub */
	unimplemented_(u"bool Reader::ready()");
	return 0;
}

void Reader::reset()
{ /* stub */
	unimplemented_(u"void Reader::reset()");
}

int64_t Reader::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t Reader::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Reader::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.Reader", 14);
    return c;
}

java::lang::Class* Reader::getClass0()
{
	return class_();
}

