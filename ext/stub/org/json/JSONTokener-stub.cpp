// Generated from /tdme/lib/json.jar
#include <org/json/JSONTokener.h>

using org::json::JSONTokener;
extern void unimplemented_(const char16_t* name);
org::json::JSONTokener::JSONTokener(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

org::json::JSONTokener::JSONTokener(Reader* reader)
	: JSONTokener(*static_cast< ::default_init_tag* >(0))
{
	ctor(reader);
}

org::json::JSONTokener::JSONTokener(InputStream* inputStream)
	: JSONTokener(*static_cast< ::default_init_tag* >(0))
{
	ctor(inputStream);
}

org::json::JSONTokener::JSONTokener(String* s)
	: JSONTokener(*static_cast< ::default_init_tag* >(0))
{
	ctor(s);
}


void JSONTokener::ctor(Reader* reader)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONTokener::ctor(Reader* reader)");
}

void JSONTokener::ctor(InputStream* inputStream)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONTokener::ctor(InputStream* inputStream)");
}

void JSONTokener::ctor(String* s)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONTokener::ctor(String* s)");
}

void JSONTokener::back()
{ /* stub */
	unimplemented_(u"void JSONTokener::back()");
}

int32_t JSONTokener::dehexchar(char16_t c)
{ /* stub */
	clinit();
	unimplemented_(u"int32_t JSONTokener::dehexchar(char16_t c)");
	return 0;
}

bool JSONTokener::end()
{ /* stub */
	unimplemented_(u"bool JSONTokener::end()");
	return 0;
}

bool JSONTokener::more()
{ /* stub */
	unimplemented_(u"bool JSONTokener::more()");
	return 0;
}

char16_t JSONTokener::next()
{ /* stub */
	unimplemented_(u"char16_t JSONTokener::next()");
	return 0;
}

char16_t JSONTokener::next(char16_t c)
{ /* stub */
	unimplemented_(u"char16_t JSONTokener::next(char16_t c)");
	return 0;
}

String* JSONTokener::next(int32_t n)
{ /* stub */
	unimplemented_(u"String* JSONTokener::next(int32_t n)");
	return 0;
}

char16_t JSONTokener::nextClean()
{ /* stub */
	unimplemented_(u"char16_t JSONTokener::nextClean()");
	return 0;
}

String* JSONTokener::nextString(char16_t quote)
{ /* stub */
	unimplemented_(u"String* JSONTokener::nextString(char16_t quote)");
	return 0;
}

String* JSONTokener::nextTo(char16_t arg0)
{ /* stub */
	unimplemented_(u"String* JSONTokener::nextTo(char16_t arg0)");
	return 0;
}

String* JSONTokener::nextTo(String* delimiters)
{ /* stub */
	unimplemented_(u"String* JSONTokener::nextTo(String* delimiters)");
	return 0;
}

Object* JSONTokener::nextValue()
{ /* stub */
	unimplemented_(u"Object* JSONTokener::nextValue()");
	return 0;
}

char16_t JSONTokener::skipTo(char16_t arg0)
{ /* stub */
	unimplemented_(u"char16_t JSONTokener::skipTo(char16_t arg0)");
	return 0;
}

JSONException* JSONTokener::syntaxError(String* message)
{ /* stub */
	unimplemented_(u"JSONException* JSONTokener::syntaxError(String* message)");
	return 0;
}

String* JSONTokener::toString()
{ /* stub */
	unimplemented_(u"String* JSONTokener::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* JSONTokener::class_()
{
    static ::java::lang::Class* c = ::class_(u"org.json.JSONTokener", 20);
    return c;
}

java::lang::Class* JSONTokener::getClass0()
{
	return class_();
}

