// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <regex>
#include <string>

#include <java/lang/String.h>

using std::regex_match;
using std::wstring;
using std::wregex;
using std::regex_replace;

using java::lang::String;

bool String::matches(String* arg0) { /* stub */
	return regex_match(cppwstring, wregex(arg0->getCPPWString()));
}

String* String::replaceAll(String* arg0, String* arg1) { /* stub */
	return new String(regex_replace(cppwstring, wregex(arg0->cppwstring), arg1->cppwstring));
}
