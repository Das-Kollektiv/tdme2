// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar
#include <java/util/Locale.h>

using java::util::Locale;
template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Cloneable, ObjectArray > CloneableArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang

namespace util {
typedef ::SubArray< ::java::util::Locale, ::java::lang::ObjectArray, ::java::lang::CloneableArray, ::java::io::SerializableArray > LocaleArray;
}  // namespace util
}  // namespace java

extern void unimplemented_(const char16_t* name);
java::util::Locale::Locale(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

java::util::Locale::Locale(String* arg0)
	: Locale(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

java::util::Locale::Locale(String* arg0, String* arg1)
	: Locale(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

java::util::Locale::Locale(String* arg0, String* arg1, String* arg2)
	: Locale(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1, arg2);
}

Locale* java::util::Locale::CANADA;
Locale* java::util::Locale::CANADA_FRENCH;
Locale* java::util::Locale::CHINA;
Locale* java::util::Locale::CHINESE;
constexpr int32_t java::util::Locale::DISPLAY_COUNTRY;
constexpr int32_t java::util::Locale::DISPLAY_LANGUAGE;
constexpr int32_t java::util::Locale::DISPLAY_VARIANT;
Locale* java::util::Locale::ENGLISH;
Locale* java::util::Locale::FRANCE;
Locale* java::util::Locale::FRENCH;
Locale* java::util::Locale::GERMAN;
Locale* java::util::Locale::GERMANY;
Locale* java::util::Locale::ITALIAN;
Locale* java::util::Locale::ITALY;
Locale* java::util::Locale::JAPAN;
Locale* java::util::Locale::JAPANESE;
Locale* java::util::Locale::KOREA;
Locale* java::util::Locale::KOREAN;
Locale* java::util::Locale::PRC;
Locale* java::util::Locale::ROOT;
Locale* java::util::Locale::SIMPLIFIED_CHINESE;
Locale* java::util::Locale::TAIWAN;
Locale* java::util::Locale::TRADITIONAL_CHINESE;
Locale* java::util::Locale::UK;
Locale* java::util::Locale::US;
ConcurrentHashMap* java::util::Locale::cache;
Locale* java::util::Locale::defaultLocale;
std::atomic< StringArray* > java::util::Locale::isoCountries;
std::atomic< StringArray* > java::util::Locale::isoLanguages;
constexpr int64_t java::util::Locale::serialVersionUID;

void Locale::ctor(String* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Locale::ctor(String* arg0)");
}

void Locale::ctor(String* arg0, String* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Locale::ctor(String* arg0, String* arg1)");
}

void Locale::ctor(String* arg0, String* arg1, String* arg2)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void Locale::ctor(String* arg0, String* arg1, String* arg2)");
}

/* private: void Locale::ctor(String* arg0, String* arg1, bool arg2) */
Object* Locale::clone()
{ /* stub */
	unimplemented_(u"Object* Locale::clone()");
	return 0;
}

/* private: StringArray* Locale::composeList(MessageFormat* arg0, StringArray* arg1) */
/* private: String* Locale::convertOldISOCodes(String* arg0) */
/* private: Locale* Locale::createSingleton(String* arg0, String* arg1, String* arg2) */
bool Locale::equals(Object* arg0)
{ /* stub */
	unimplemented_(u"bool Locale::equals(Object* arg0)");
	return 0;
}

/* private: String* Locale::formatList(StringArray* arg0, String* arg1, String* arg2) */
LocaleArray* Locale::getAvailableLocales()
{ /* stub */
	clinit();
	unimplemented_(u"LocaleArray* Locale::getAvailableLocales()");
	return 0;
}

String* Locale::getCountry()
{ /* stub */
return country ; /* getter */
}

Locale* Locale::getDefault()
{ /* stub */
	clinit();
	unimplemented_(u"Locale* Locale::getDefault()");
	return 0;
}

String* Locale::getDisplayCountry()
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayCountry()");
	return 0;
}

String* Locale::getDisplayCountry(Locale* arg0)
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayCountry(Locale* arg0)");
	return 0;
}

String* Locale::getDisplayLanguage()
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayLanguage()");
	return 0;
}

String* Locale::getDisplayLanguage(Locale* arg0)
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayLanguage(Locale* arg0)");
	return 0;
}

String* Locale::getDisplayName()
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayName()");
	return 0;
}

String* Locale::getDisplayName(Locale* arg0)
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayName(Locale* arg0)");
	return 0;
}

/* private: String* Locale::getDisplayString(String* arg0, Locale* arg1, int32_t arg2) */
String* Locale::getDisplayVariant()
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayVariant()");
	return 0;
}

String* Locale::getDisplayVariant(Locale* arg0)
{ /* stub */
	unimplemented_(u"String* Locale::getDisplayVariant(Locale* arg0)");
	return 0;
}

/* private: StringArray* Locale::getDisplayVariantArray(OpenListResourceBundle* arg0, Locale* arg1) */
/* private: StringArray* Locale::getISO2Table(String* arg0) */
/* private: String* Locale::getISO3Code(String* arg0, String* arg1) */
String* Locale::getISO3Country()
{ /* stub */
	unimplemented_(u"String* Locale::getISO3Country()");
	return 0;
}

String* Locale::getISO3Language()
{ /* stub */
	unimplemented_(u"String* Locale::getISO3Language()");
	return 0;
}

StringArray* Locale::getISOCountries()
{ /* stub */
	clinit();
	unimplemented_(u"StringArray* Locale::getISOCountries()");
	return 0;
}

StringArray* Locale::getISOLanguages()
{ /* stub */
	clinit();
	unimplemented_(u"StringArray* Locale::getISOLanguages()");
	return 0;
}

Locale* Locale::getInstance(String* arg0, String* arg1, String* arg2)
{ /* stub */
	clinit();
	unimplemented_(u"Locale* Locale::getInstance(String* arg0, String* arg1, String* arg2)");
	return 0;
}

String* Locale::getLanguage()
{ /* stub */
return language ; /* getter */
}

String* Locale::getVariant()
{ /* stub */
return variant ; /* getter */
}

int32_t Locale::hashCode()
{ /* stub */
	unimplemented_(u"int32_t Locale::hashCode()");
	return 0;
}

/* private: Object* Locale::readResolve() */
void Locale::setDefault(Locale* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"void Locale::setDefault(Locale* arg0)");
}

/* private: String* Locale::toLowerCase(String* arg0) */
String* Locale::toString()
{ /* stub */
	unimplemented_(u"String* Locale::toString()");
	return 0;
}

/* private: String* Locale::toUpperCase(String* arg0) */
extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Locale::class_()
{
    static ::java::lang::Class* c = ::class_(u"java.util.Locale", 16);
    return c;
}

java::lang::Class* Locale::getClass0()
{
	return class_();
}

