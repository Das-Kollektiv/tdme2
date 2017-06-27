// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/io/InputStreamReader.h>

using java::io::InputStreamReader;
extern void unimplemented_(const char16_t* name);
java::io::InputStreamReader::InputStreamReader(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::io::InputStreamReader::InputStreamReader(InputStream* in)
	: InputStreamReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(in);
}

java::io::InputStreamReader::InputStreamReader(InputStream* in, String* charsetName)
	: InputStreamReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(in, charsetName);
}

java::io::InputStreamReader::InputStreamReader(InputStream* in, Charset* cs)
	: InputStreamReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(in, cs);
}

java::io::InputStreamReader::InputStreamReader(InputStream* in, CharsetDecoder* dec)
	: InputStreamReader(*static_cast< ::default_init_tag* >(0))
{
	ctor(in, dec);
}


void InputStreamReader::ctor(InputStream* in)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputStreamReader::ctor(InputStream* in)");
}

void InputStreamReader::ctor(InputStream* in, String* charsetName)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputStreamReader::ctor(InputStream* in, String* charsetName)");
}

void InputStreamReader::ctor(InputStream* in, Charset* cs)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputStreamReader::ctor(InputStream* in, Charset* cs)");
}

void InputStreamReader::ctor(InputStream* in, CharsetDecoder* dec)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void InputStreamReader::ctor(InputStream* in, CharsetDecoder* dec)");
}

void InputStreamReader::close()
{ /* stub */
	unimplemented_(u"void InputStreamReader::close()");
}

String* InputStreamReader::getEncoding()
{ /* stub */
	unimplemented_(u"String* InputStreamReader::getEncoding()");
	return 0;
}

int32_t InputStreamReader::read()
{ /* stub */
	unimplemented_(u"int32_t InputStreamReader::read()");
	return 0;
}

int32_t InputStreamReader::read(char16_tArray* cbuf, int32_t offset, int32_t length)
{ /* stub */
	unimplemented_(u"int32_t InputStreamReader::read(char16_tArray* cbuf, int32_t offset, int32_t length)");
	return 0;
}

bool InputStreamReader::ready()
{ /* stub */
	unimplemented_(u"bool InputStreamReader::ready()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* InputStreamReader::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.io.InputStreamReader", 25);
    return c;
}

int32_t InputStreamReader::read(CharBuffer* target)
{
	return super::read(target);
}

int32_t InputStreamReader::read(char16_tArray* cbuf)
{
	return super::read(cbuf);
}

java::lang::Class* InputStreamReader::getClass0()
{
	return class_();
}

