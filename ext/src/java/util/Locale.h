// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <atomic>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/text/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/util/concurrent/fwd-tdme.h>
#include <sun/util/resources/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/lang/Cloneable.h>
#include <java/io/Serializable.h>

using java::lang::Object;
using java::lang::Cloneable;
using java::io::Serializable;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::String;
using java::text::MessageFormat;
using java::util::concurrent::ConcurrentHashMap;
using sun::util::resources::OpenListResourceBundle;
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

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::CloneableArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;
using java::util::LocaleArray;

struct default_init_tag;
class java::util::Locale final
	: public virtual Object
	, public Cloneable
	, public Serializable
{

public:
	typedef Object super;
	static Locale* CANADA;
	static Locale* CANADA_FRENCH;
	static Locale* CHINA;
	static Locale* CHINESE;

private:
	static constexpr int32_t DISPLAY_COUNTRY { 1 };
	static constexpr int32_t DISPLAY_LANGUAGE { 0 };
	static constexpr int32_t DISPLAY_VARIANT { 2 };

public:
	static Locale* ENGLISH;
	static Locale* FRANCE;
	static Locale* FRENCH;
	static Locale* GERMAN;
	static Locale* GERMANY;
	static Locale* ITALIAN;
	static Locale* ITALY;
	static Locale* JAPAN;
	static Locale* JAPANESE;
	static Locale* KOREA;
	static Locale* KOREAN;
	static Locale* PRC;
	static Locale* ROOT;
	static Locale* SIMPLIFIED_CHINESE;
	static Locale* TAIWAN;
	static Locale* TRADITIONAL_CHINESE;
	static Locale* UK;
	static Locale* US;

private:
	static ConcurrentHashMap* cache;
	String* country {  };
	static Locale* defaultLocale;
	std::atomic< int32_t > hashCodeValue {  };
	std::atomic< int32_t > hashcode {  };
	static std::atomic< StringArray* > isoCountries;
	static std::atomic< StringArray* > isoLanguages;
	String* language {  };

public: /* package */
	static constexpr int64_t serialVersionUID { 9149081749638150636LL };

private:
	String* variant {  };

protected:
	void ctor(String* arg0);
	void ctor(String* arg0, String* arg1);
	void ctor(String* arg0, String* arg1, String* arg2);
	/*void ctor(String* arg0, String* arg1, bool arg2); (private) */

public:
	Object* clone() override;
	/*static StringArray* composeList(MessageFormat* arg0, StringArray* arg1); (private) */
	/*String* convertOldISOCodes(String* arg0); (private) */
	/*static Locale* createSingleton(String* arg0, String* arg1, String* arg2); (private) */
	bool equals(Object* arg0) override;
	/*static String* formatList(StringArray* arg0, String* arg1, String* arg2); (private) */
	static LocaleArray* getAvailableLocales();
	String* getCountry();
	static Locale* getDefault();
	String* getDisplayCountry();
	String* getDisplayCountry(Locale* arg0);
	String* getDisplayLanguage();
	String* getDisplayLanguage(Locale* arg0);
	String* getDisplayName();
	String* getDisplayName(Locale* arg0);
	/*String* getDisplayString(String* arg0, Locale* arg1, int32_t arg2); (private) */
	String* getDisplayVariant();
	String* getDisplayVariant(Locale* arg0);
	/*StringArray* getDisplayVariantArray(OpenListResourceBundle* arg0, Locale* arg1); (private) */
	/*static StringArray* getISO2Table(String* arg0); (private) */
	/*static String* getISO3Code(String* arg0, String* arg1); (private) */
	String* getISO3Country();
	String* getISO3Language();
	static StringArray* getISOCountries();
	static StringArray* getISOLanguages();

public: /* package */
	static Locale* getInstance(String* arg0, String* arg1, String* arg2);

public:
	String* getLanguage();
	String* getVariant();
	int32_t hashCode() override;
	/*Object* readResolve(); (private) */
	static void setDefault(Locale* arg0);
	/*String* toLowerCase(String* arg0); (private) */
	String* toString() override;
	/*String* toUpperCase(String* arg0); (private) */

	// Generated
	Locale(String* arg0);
	Locale(String* arg0, String* arg1);
	Locale(String* arg0, String* arg1, String* arg2);
protected:
	Locale(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
