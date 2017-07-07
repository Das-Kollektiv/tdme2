// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <regex>
#include <string>
#include <vector>

#include <java/util/StringTokenizer.h>
#include <java/lang/String.h>

#include <tdme/utils/_Console.h>

using java::util::StringTokenizer;

using tdme::utils::_Console;

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
	ctor(arg0, new String(L" \t\n\r\f"));
}

void StringTokenizer::ctor(String* arg0, String* arg1)
{ /* stub */
	wstring input = arg0->getCPPWString();
	wstring delimiters = arg1->getCPPWString();
	wstring token;
	for (int i = 0; i < input.length(); i++) {
		// got a delimiter?
		if (delimiters.find(input[i]) != -1) {
			// yep, add token to elements if we have any
			if (token.length() > 0) {
				elements.push_back(token);
				token = L"";
			}
		} else {
			// no delimiter, add char to token
			token+= input[i];
		}
	}
	// do we have a token still? add it to elements
	if (token.length() > 0) {
		elements.push_back(token);
		token = L"";
	}
}

void StringTokenizer::ctor(String* arg0, String* arg1, bool arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void StringTokenizer::ctor(String* arg0, String* arg1, bool arg2)");
}

int32_t StringTokenizer::countTokens()
{ /* stub */
	return elements.size();
}

bool StringTokenizer::hasMoreElements()
{ /* stub */
	return idx != elements.size();;
}

bool StringTokenizer::hasMoreTokens()
{ /* stub */
	return idx != elements.size();;
}

/* private: bool StringTokenizer::isDelimiter(int32_t arg0) */
Object* StringTokenizer::nextElement()
{ /* stub */
	return new String(elements[idx++]);
}

String* StringTokenizer::nextToken()
{ /* stub */
	return new String(elements[idx++]);
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

