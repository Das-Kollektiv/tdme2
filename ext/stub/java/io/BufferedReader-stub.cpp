// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/BufferedReader.h>

using java::io::BufferedReader;
extern void unimplemented_(const char16_t* name);
java::io::BufferedReader::BufferedReader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::BufferedReader::BufferedReader(Reader* arg0)
	: BufferedReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::io::BufferedReader::BufferedReader(Reader* arg0, int32_t arg1)
	: BufferedReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

constexpr int32_t java::io::BufferedReader::INVALIDATED;
constexpr int32_t java::io::BufferedReader::UNMARKED;
int32_t java::io::BufferedReader::defaultCharBufferSize;
int32_t java::io::BufferedReader::defaultExpectedLineLength;

void BufferedReader::ctor(Reader* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void BufferedReader::ctor(Reader* arg0)");
}

void BufferedReader::ctor(Reader* arg0, int32_t arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void BufferedReader::ctor(Reader* arg0, int32_t arg1)");
}

void BufferedReader::close()
{ /* stub */
	unimplemented_(u"void BufferedReader::close()");
}

/* private: void BufferedReader::ensureOpen() */
/* private: void BufferedReader::fill() */
void BufferedReader::mark(int32_t arg0)
{ /* stub */
	unimplemented_(u"void BufferedReader::mark(int32_t arg0)");
}

bool BufferedReader::markSupported()
{ /* stub */
	unimplemented_(u"bool BufferedReader::markSupported()");
	return 0;
}

int32_t BufferedReader::read()
{ /* stub */
	unimplemented_(u"int32_t BufferedReader::read()");
	return 0;
}

int32_t BufferedReader::read(char16_tArray* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	unimplemented_(u"int32_t BufferedReader::read(char16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

/* private: int32_t BufferedReader::read1(char16_tArray* arg0, int32_t arg1, int32_t arg2) */
String* BufferedReader::readLine()
{ /* stub */
	unimplemented_(u"String* BufferedReader::readLine()");
	return 0;
}

String* BufferedReader::readLine(bool arg0)
{ /* stub */
	unimplemented_(u"String* BufferedReader::readLine(bool arg0)");
	return 0;
}

bool BufferedReader::ready()
{ /* stub */
	unimplemented_(u"bool BufferedReader::ready()");
	return 0;
}

void BufferedReader::reset()
{ /* stub */
	unimplemented_(u"void BufferedReader::reset()");
}

int64_t BufferedReader::skip(int64_t arg0)
{ /* stub */
	unimplemented_(u"int64_t BufferedReader::skip(int64_t arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* BufferedReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.BufferedReader", 22);
    return c;
}

int32_t BufferedReader::read(CharBuffer* arg0)
{
	return super::read(arg0);
}

int32_t BufferedReader::read(char16_tArray* arg0)
{
	return super::read(arg0);
}

java::lang::Class* BufferedReader::getClass0()
{
	return class_();
}

