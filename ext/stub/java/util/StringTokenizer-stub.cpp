// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/StringTokenizer.h>

using java::util::StringTokenizer;
extern void unimplemented_(const char16_t* name);
java::util::StringTokenizer::StringTokenizer(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::StringTokenizer::StringTokenizer(String* arg0)
	: StringTokenizer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::StringTokenizer::StringTokenizer(String* arg0, String* arg1)
	: StringTokenizer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::StringTokenizer::StringTokenizer(String* arg0, String* arg1, bool arg2)
	: StringTokenizer(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}


void StringTokenizer::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringTokenizer::ctor(String* arg0)");
}

void StringTokenizer::ctor(String* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringTokenizer::ctor(String* arg0, String* arg1)");
}

void StringTokenizer::ctor(String* arg0, String* arg1, bool arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringTokenizer::ctor(String* arg0, String* arg1, bool arg2)");
}

int32_t StringTokenizer::countTokens()
{ /* stub */
	unimplemented_(u"int32_t StringTokenizer::countTokens()");
	return 0;
}

bool StringTokenizer::hasMoreElements()
{ /* stub */
	unimplemented_(u"bool StringTokenizer::hasMoreElements()");
	return 0;
}

bool StringTokenizer::hasMoreTokens()
{ /* stub */
	unimplemented_(u"bool StringTokenizer::hasMoreTokens()");
	return 0;
}

/* private: bool StringTokenizer::isDelimiter(int32_t arg0) */
Object* StringTokenizer::nextElement()
{ /* stub */
	unimplemented_(u"Object* StringTokenizer::nextElement()");
	return 0;
}

String* StringTokenizer::nextToken()
{ /* stub */
	unimplemented_(u"String* StringTokenizer::nextToken()");
	return 0;
}

String* StringTokenizer::nextToken(String* arg0)
{ /* stub */
	unimplemented_(u"String* StringTokenizer::nextToken(String* arg0)");
	return 0;
}

/* private: int32_t StringTokenizer::scanToken(int32_t arg0) */
/* private: void StringTokenizer::setMaxDelimCodePoint() */
/* private: int32_t StringTokenizer::skipDelimiters(int32_t arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* StringTokenizer::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.StringTokenizer", 25);
    return c;
}

java::lang::Class* StringTokenizer::getClass0()
{
	return class_();
}

