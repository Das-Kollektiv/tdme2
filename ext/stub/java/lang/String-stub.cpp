// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <algorithm>
#include <functional>
#include <string>

#include <Array.h>
#include <java/lang/String.h>
#include <tdme/utils/StringConverter.h>

using std::replace;
using std::string;
using std::transform;
using std::toupper;
using std::tolower;
using std::to_wstring;
using std::wstring;

using java::lang::String;

using tdme::utils::StringConverter;

template<typename ComponentType, typename ... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray<::java::io::Serializable, ::java::lang::ObjectArray> SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray<::java::lang::CharSequence, ObjectArray> CharSequenceArray;
typedef ::SubArray<::java::lang::Comparable, ObjectArray> ComparableArray;
typedef ::SubArray<::java::lang::String, ObjectArray,
		::java::io::SerializableArray, ComparableArray, CharSequenceArray> StringArray;
}  // namespace lang
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::lang::String::String(const ::default_init_tag&) :
		super(*static_cast<::default_init_tag*>(0)) {
	clinit();
}

java::lang::String::String() :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor();
}

java::lang::String::String(const wstring& arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(String* arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(char16_tArray* arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(int8_tArray* arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(StringBuffer* arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(StringBuilder* arg0) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0);
}

java::lang::String::String(int8_tArray* arg0, int32_t arg1) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1);
}

java::lang::String::String(int8_tArray* arg0, String* arg1) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1);
}

java::lang::String::String(int8_tArray* arg0, Charset* arg1) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1);
}

java::lang::String::String(char16_tArray* arg0, int32_t arg1, int32_t arg2) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2);
}

java::lang::String::String(int32_tArray* arg0, int32_t arg1, int32_t arg2) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2);
}

java::lang::String::String(int8_tArray* arg0, int32_t arg1, int32_t arg2) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2);
}

java::lang::String::String(int32_t arg0, int32_t arg1, char16_tArray* arg2) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2);
}

java::lang::String::String(int8_tArray* arg0, int32_t arg1, int32_t arg2,
		int32_t arg3) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2, arg3);
}

java::lang::String::String(int8_tArray* arg0, int32_t arg1, int32_t arg2,
		String* arg3) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2, arg3);
}

java::lang::String::String(int8_tArray* arg0, int32_t arg1, int32_t arg2,
		Charset* arg3) :
		String(*static_cast<::default_init_tag*>(0)) {
	ctor(arg0, arg1, arg2, arg3);
}

Comparator* java::lang::String::CASE_INSENSITIVE_ORDER;
ObjectStreamFieldArray* java::lang::String::serialPersistentFields;
constexpr int64_t java::lang::String::serialVersionUID;

void String::ctor() { /* stub */
}

void String::ctor(const wstring& arg0) { /* stub */
	cppwstring = arg0;
}

void String::ctor(String* arg0) { /* stub */
	cppwstring = arg0->cppwstring;
}

void String::ctor(char16_tArray* arg0) { /* stub */
	/* super::ctor(); */
	for (int i = 0; i < arg0->length; i++)
		cppwstring += (wchar_t) (arg0->get(i));
}

void String::ctor(int8_tArray* arg0) { /* stub */
	string cppstring;
	for (int i = 0; i < arg0->length; i++)
		cppstring += (wchar_t) (arg0->get(i));
	cppwstring = StringConverter::toWideString(cppstring);
}

void String::ctor(StringBuffer* arg0) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(StringBuffer* arg0)");
}

void String::ctor(StringBuilder* arg0) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(StringBuilder* arg0)");
}

void String::ctor(int8_tArray* arg0, int32_t arg1) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, int32_t arg1)");
}

void String::ctor(int8_tArray* arg0, String* arg1) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, String* arg1)");
}

void String::ctor(int8_tArray* arg0, Charset* arg1) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, Charset* arg1)");
}

void String::ctor(char16_tArray* arg0, int32_t arg1, int32_t arg2) { /* stub */
	for (int i = 0; i < arg2; i++) {
		cppwstring += arg0->get(arg1 + i);
	}
}

void String::ctor(int32_tArray* arg0, int32_t arg1, int32_t arg2) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int32_tArray* arg0, int32_t arg1, int32_t arg2)");
}

void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2)");
}

void String::ctor(int32_t arg0, int32_t arg1, char16_tArray* arg2) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int32_t arg0, int32_t arg1, char16_tArray* arg2)");
}

void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3)");
}

void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, String* arg3) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, String* arg3)");
}

void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2,
		Charset* arg3) { /* stub */
	/* super::ctor(); */
	unimplemented_(u"void String::ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, Charset* arg3)");
}

char16_t String::charAt(int32_t arg0) { /* stub */
	return cppwstring[arg0];
}

/* private: void String::checkBounds(int8_tArray* arg0, int32_t arg1, int32_t arg2) */
int32_t String::codePointAt(int32_t arg0) { /* stub */
	unimplemented_(u"int32_t String::codePointAt(int32_t arg0)");
	return 0;
}

int32_t String::codePointBefore(int32_t arg0) { /* stub */
	unimplemented_(u"int32_t String::codePointBefore(int32_t arg0)");
	return 0;
}

int32_t String::codePointCount(int32_t arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::codePointCount(int32_t arg0, int32_t arg1)");
	return 0;
}

int32_t String::compareTo(String* arg0) { /* stub */
	unimplemented_(u"int32_t String::compareTo(String* arg0)");
	return 0;
}

int32_t String::compareTo(Object* o) {
	return compareTo(dynamic_cast<String*>(o));
}

int32_t String::compareToIgnoreCase(String* arg0) { /* stub */
	unimplemented_(u"int32_t String::compareToIgnoreCase(String* arg0)");
	return 0;
}

String* String::concat(String* arg0) { /* stub */
	unimplemented_(u"String* String::concat(String* arg0)");
	return 0;
}

bool String::contains(CharSequence* arg0) { /* stub */
	unimplemented_(u"bool String::contains(CharSequence* arg0)");
	return 0;
}

bool String::contentEquals(StringBuffer* arg0) { /* stub */
	unimplemented_(u"bool String::contentEquals(StringBuffer* arg0)");
	return 0;
}

bool String::contentEquals(CharSequence* arg0) { /* stub */
	unimplemented_(u"bool String::contentEquals(CharSequence* arg0)");
	return 0;
}

String* String::copyValueOf(char16_tArray* arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::copyValueOf(char16_tArray* arg0)");
	return 0;
}

String* String::copyValueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2) { /* stub */
	clinit();
	unimplemented_(u"String* String::copyValueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

bool String::endsWith(String* arg0) { /* stub */
	return cppwstring.size() >= arg0->cppwstring.size()
			&& cppwstring.compare(cppwstring.size() - arg0->cppwstring.size(),
					arg0->cppwstring.size(), arg0->cppwstring) == 0;
}

bool String::equals(Object* arg0) { /* stub */
	return arg0->toString()->cppwstring == cppwstring;
}

bool String::operator==(const String& b) const {
	return this->cppwstring == b.cppwstring;
}

bool String::operator<(const String& b) const {
	return this->cppwstring < b.cppwstring;
}

bool String::operator>(const String& b)  const{
	return this->cppwstring > b.cppwstring;
}

bool String::equalsIgnoreCase(String* arg0) { /* stub */
	wstring stringA = cppwstring;
	wstring stringB = arg0->cppwstring;
	transform(stringA.begin(), stringA.end(), stringA.begin(), toupper);
	transform(stringB.begin(), stringB.end(), stringB.begin(), toupper);
	return stringA == stringB;
}

String* String::format(String* arg0, ObjectArray* arg1) { /* stub */
	clinit();
	unimplemented_(u"String* String::format(String* arg0, ObjectArray* arg1)");
	return 0;
}

String* String::format(Locale* arg0, String* arg1, ObjectArray* arg2) { /* stub */
	clinit();
	unimplemented_(u"String* String::format(Locale* arg0, String* arg1, ObjectArray* arg2)");
	return 0;
}

int8_tArray* String::getBytes() { /* stub */
	unimplemented_(u"int8_tArray* String::getBytes()");
	return 0;
}

int8_tArray* String::getBytes(String* arg0) { /* stub */
	unimplemented_(u"int8_tArray* String::getBytes(String* arg0)");
	return 0;
}

int8_tArray* String::getBytes(Charset* arg0) { /* stub */
	unimplemented_(u"int8_tArray* String::getBytes(Charset* arg0)");
	return 0;
}

void String::getBytes(int32_t arg0, int32_t arg1, int8_tArray* arg2,
		int32_t arg3) { /* stub */
	unimplemented_(u"void String::getBytes(int32_t arg0, int32_t arg1, int8_tArray* arg2, int32_t arg3)");
}

void String::getChars(char16_tArray* arg0, int32_t arg1) { /* stub */
	unimplemented_(u"void String::getChars(char16_tArray* arg0, int32_t arg1)");
}

void String::getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2,
		int32_t arg3) { /* stub */
	unimplemented_(u"void String::getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2, int32_t arg3)");
}

int32_t String::hashCode() { /* stub */
	auto h = hash;
	if (h == 0 && cppwstring.length() > 0) {
		for (auto i = 0; i < cppwstring.length(); i++) {
			h = 31 * h + cppwstring[i];
		}
		hash = h;
	}
	return h;
}

int32_t String::indexOf(int32_t arg0) { /* stub */
	unimplemented_(u"int32_t String::indexOf(int32_t arg0)");
	return 0;
}

int32_t String::indexOf(String* arg0) { /* stub */
	return cppwstring.find(arg0->cppwstring);
}

int32_t String::indexOf(int32_t arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::indexOf(int32_t arg0, int32_t arg1)");
	return 0;
}

int32_t String::indexOf(String* arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::indexOf(String* arg0, int32_t arg1)");
	return 0;
}

int32_t String::indexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2,
		char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6) { /* stub */
	clinit();
	unimplemented_(u"int32_t String::indexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6)");
	return 0;
}

bool String::isEmpty() { /* stub */
	unimplemented_(u"bool String::isEmpty()");
	return 0;
}

int32_t String::lastIndexOf(int32_t arg0) { /* stub */
	return cppwstring.find_last_of(arg0);
}

int32_t String::lastIndexOf(String* arg0) { /* stub */
	return cppwstring.rfind(arg0->cppwstring);
}

int32_t String::lastIndexOf(int32_t arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::lastIndexOf(int32_t arg0, int32_t arg1)");
	return 0;
}

int32_t String::lastIndexOf(String* arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::lastIndexOf(String* arg0, int32_t arg1)");
	return 0;
}

int32_t String::lastIndexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2,
		char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6) { /* stub */
	clinit();
	unimplemented_(u"int32_t String::lastIndexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6)");
	return 0;
}

int32_t String::length() { /* stub */
	return cppwstring.length();
}

int32_t String::offsetByCodePoints(int32_t arg0, int32_t arg1) { /* stub */
	unimplemented_(u"int32_t String::offsetByCodePoints(int32_t arg0, int32_t arg1)");
	return 0;
}

bool String::regionMatches(int32_t arg0, String* arg1, int32_t arg2,
		int32_t arg3) { /* stub */
	unimplemented_(u"bool String::regionMatches(int32_t arg0, String* arg1, int32_t arg2, int32_t arg3)");
	return 0;
}

bool String::regionMatches(bool arg0, int32_t arg1, String* arg2, int32_t arg3,
		int32_t arg4) { /* stub */
	unimplemented_(u"bool String::regionMatches(bool arg0, int32_t arg1, String* arg2, int32_t arg3, int32_t arg4)");
	return 0;
}

String* String::replace(char16_t arg0, char16_t arg1) { /* stub */
	String* result = new String(cppwstring);
	std::replace(result->cppwstring.begin(), result->cppwstring.end(), arg0,
			arg1);
	return result;
}

String* String::replace(CharSequence* arg0, CharSequence* arg1) { /* stub */
	wstring source;
	wstring replacement;
	for (int i = 0; i < arg0->length(); i++) {
		source += arg0->charAt(i);
	}
	for (int i = 0; i < arg1->length(); i++) {
		replacement += arg1->charAt(i);
	}

	wstring string = cppwstring;
	if (source.empty())
		return new String(string);
	size_t start_pos = 0;
	while ((start_pos = string.find(source, start_pos)) != std::string::npos) {
		string.replace(start_pos, source.length(), replacement);
		start_pos += replacement.length();
	}

	return new String(string);
}

String* String::replaceFirst(String* arg0, String* arg1) { /* stub */
	unimplemented_(u"String* String::replaceFirst(String* arg0, String* arg1)");
	return 0;
}

StringArray* String::split(String* arg0) { /* stub */
	unimplemented_(u"StringArray* String::split(String* arg0)");
	return 0;
}

StringArray* String::split(String* arg0, int32_t arg1) { /* stub */
	unimplemented_(u"StringArray* String::split(String* arg0, int32_t arg1)");
	return 0;
}

bool String::startsWith(String* arg0) { /* stub */
	return cppwstring.find(arg0->cppwstring) == 0;
}

bool String::startsWith(String* arg0, int32_t arg1) { /* stub */
	unimplemented_(u"bool String::startsWith(String* arg0, int32_t arg1)");
	return 0;
}

CharSequence* String::subSequence(int32_t arg0, int32_t arg1) { /* stub */
	unimplemented_(u"CharSequence* String::subSequence(int32_t arg0, int32_t arg1)");
	return 0;
}

String* String::substring(int32_t arg0) { /* stub */
	return new String(cppwstring.substr(arg0));
}

String* String::substring(int32_t arg0, int32_t arg1) { /* stub */
	return new String(cppwstring.substr(arg0, arg1 - arg0));
}

char16_tArray* String::toCharArray() { /* stub */
	unimplemented_(u"char16_tArray* String::toCharArray()");
	return 0;
}

String* String::toLowerCase() { /* stub */
	wstring string = cppwstring;
	transform(string.begin(), string.end(), string.begin(), tolower);
	return new String(string);
}

String* String::toLowerCase(Locale* arg0) { /* stub */
	unimplemented_(u"String* String::toLowerCase(Locale* arg0)");
	return 0;
}

String* String::toString() { /* stub */
	return this;
}

String* String::toUpperCase() { /* stub */
	wstring string = cppwstring;
	transform(string.begin(), string.end(), string.begin(), toupper);
	return new String(string);
}

String* String::toUpperCase(Locale* arg0) { /* stub */
	unimplemented_(u"String* String::toUpperCase(Locale* arg0)");
	return 0;
}

String* String::trim() { /* stub */
	wstring string = cppwstring;
	string.erase(string.begin(),
			std::find_if(string.begin(), string.end(),
					std::not1(std::ptr_fun<int, int>(std::isspace))));
	string.erase(
			std::find_if(string.rbegin(), string.rend(),
					std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
			string.end());
	return new String(string);
}

String* String::valueOf(Object* arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(Object* arg0)");
	return 0;
}

String* String::valueOf(char16_tArray* arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(char16_tArray* arg0)");
	return 0;
}

String* String::valueOf(bool arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(bool arg0)");
	return 0;
}

String* String::valueOf(char16_t arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(char16_t arg0)");
	return 0;
}

String* String::valueOf(int32_t arg0) { /* stub */
	clinit();
	return new String(to_wstring(arg0));
}

String* String::valueOf(int64_t arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(int64_t arg0)");
	return 0;
}

String* String::valueOf(float arg0) { /* stub */
	clinit();
	return new String(to_wstring(arg0));
}

String* String::valueOf(double arg0) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(double arg0)");
	return 0;
}

String* String::valueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2) { /* stub */
	clinit();
	unimplemented_(u"String* String::valueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

wstring& String::getCPPWString() {
	return cppwstring;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* String::class_() {
	static ::java::lang::Class* c = ::class_(u"java.lang.String", 16);
	return c;
}

java::lang::Class* String::getClass0() {
	return class_();
}

