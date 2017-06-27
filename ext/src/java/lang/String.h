// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <stddef.h>
#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/nio/charset/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <java/lang/Object.h>
#include <java/io/Serializable.h>
#include <java/lang/Comparable.h>
#include <java/lang/CharSequence.h>

using java::lang::Object;
using java::io::Serializable;
using java::lang::Comparable;
using java::lang::CharSequence;
using java::io::ObjectStreamField;
using java::lang::StringBuffer;
using java::lang::StringBuilder;
using java::nio::charset::Charset;
using java::util::Comparator;
using java::util::Locale;
using java::lang::String;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::ObjectStreamField, ::java::lang::ObjectArray, ::java::lang::ComparableArray > ObjectStreamFieldArray;
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::ObjectStreamFieldArray;
using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;
class java::lang::String final
	: public virtual Object
	, public Serializable
	, public Comparable
	, public CharSequence
{

public:
	typedef Object super;
	static Comparator* CASE_INSENSITIVE_ORDER;

private:
	int32_t count {  };
	int32_t hash {  };
	int32_t offset {  };
	static ObjectStreamFieldArray* serialPersistentFields;
	static constexpr int64_t serialVersionUID { -6849794470754667710LL };
	char16_tArray* value {  };

protected:
	void ctor();
	void ctor(String* arg0);
	void ctor(char16_tArray* arg0);
	void ctor(int8_tArray* arg0);
	void ctor(StringBuffer* arg0);
	void ctor(StringBuilder* arg0);
	void ctor(int8_tArray* arg0, int32_t arg1);
	void ctor(int8_tArray* arg0, String* arg1);
	void ctor(int8_tArray* arg0, Charset* arg1);
	void ctor(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	void ctor(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	void ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2);
	void ctor(int32_t arg0, int32_t arg1, char16_tArray* arg2);
	void ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	void ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, String* arg3);
	void ctor(int8_tArray* arg0, int32_t arg1, int32_t arg2, Charset* arg3);

public:
	char16_t charAt(int32_t arg0) override;
	/*static void checkBounds(int8_tArray* arg0, int32_t arg1, int32_t arg2); (private) */
	int32_t codePointAt(int32_t arg0);
	int32_t codePointBefore(int32_t arg0);
	int32_t codePointCount(int32_t arg0, int32_t arg1);
	int32_t compareTo(String* arg0);
	int32_t compareToIgnoreCase(String* arg0);
	String* concat(String* arg0);
	bool contains(CharSequence* arg0);
	bool contentEquals(StringBuffer* arg0);
	bool contentEquals(CharSequence* arg0);
	static String* copyValueOf(char16_tArray* arg0);
	static String* copyValueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	bool endsWith(String* arg0);
	bool equals(Object* arg0) override;
	bool equalsIgnoreCase(String* arg0);
	static String* format(String* arg0, ObjectArray* arg1);
	static String* format(Locale* arg0, String* arg1, ObjectArray* arg2);
	int8_tArray* getBytes();
	int8_tArray* getBytes(String* arg0);
	int8_tArray* getBytes(Charset* arg0);
	void getBytes(int32_t arg0, int32_t arg1, int8_tArray* arg2, int32_t arg3);

public: /* package */
	void getChars(char16_tArray* arg0, int32_t arg1);

public:
	void getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2, int32_t arg3);
	int32_t hashCode() override;
	int32_t indexOf(int32_t arg0);
	int32_t indexOf(String* arg0);
	int32_t indexOf(int32_t arg0, int32_t arg1);
	int32_t indexOf(String* arg0, int32_t arg1);

public: /* package */
	static int32_t indexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6);

public:
	String* intern();
	bool isEmpty();
	int32_t lastIndexOf(int32_t arg0);
	int32_t lastIndexOf(String* arg0);
	int32_t lastIndexOf(int32_t arg0, int32_t arg1);
	int32_t lastIndexOf(String* arg0, int32_t arg1);

public: /* package */
	static int32_t lastIndexOf(char16_tArray* arg0, int32_t arg1, int32_t arg2, char16_tArray* arg3, int32_t arg4, int32_t arg5, int32_t arg6);

public:
	int32_t length() override;
	bool matches(String* arg0);
	int32_t offsetByCodePoints(int32_t arg0, int32_t arg1);
	bool regionMatches(int32_t arg0, String* arg1, int32_t arg2, int32_t arg3);
	bool regionMatches(bool arg0, int32_t arg1, String* arg2, int32_t arg3, int32_t arg4);
	String* replace(char16_t arg0, char16_t arg1);
	String* replace(CharSequence* arg0, CharSequence* arg1);
	String* replaceAll(String* arg0, String* arg1);
	String* replaceFirst(String* arg0, String* arg1);
	StringArray* split(String* arg0);
	StringArray* split(String* arg0, int32_t arg1);
	bool startsWith(String* arg0);
	bool startsWith(String* arg0, int32_t arg1);
	CharSequence* subSequence(int32_t arg0, int32_t arg1) override;
	String* substring(int32_t arg0);
	String* substring(int32_t arg0, int32_t arg1);
	char16_tArray* toCharArray();
	String* toLowerCase();
	String* toLowerCase(Locale* arg0);
	String* toString() override;
	String* toUpperCase();
	String* toUpperCase(Locale* arg0);
	String* trim();
	static String* valueOf(Object* arg0);
	static String* valueOf(char16_tArray* arg0);
	static String* valueOf(bool arg0);
	static String* valueOf(char16_t arg0);
	static String* valueOf(int32_t arg0);
	static String* valueOf(int64_t arg0);
	static String* valueOf(float arg0);
	static String* valueOf(double arg0);
	static String* valueOf(char16_tArray* arg0, int32_t arg1, int32_t arg2);

	// Generated
	String();
	String(String* arg0);
	String(char16_tArray* arg0);
	String(int8_tArray* arg0);
	String(StringBuffer* arg0);
	String(StringBuilder* arg0);
	String(int8_tArray* arg0, int32_t arg1);
	String(int8_tArray* arg0, String* arg1);
	String(int8_tArray* arg0, Charset* arg1);
	String(char16_tArray* arg0, int32_t arg1, int32_t arg2);
	String(int32_tArray* arg0, int32_t arg1, int32_t arg2);
	String(int8_tArray* arg0, int32_t arg1, int32_t arg2);

public: /* package */
	String(int32_t arg0, int32_t arg1, char16_tArray* arg2);

public:
	String(int8_tArray* arg0, int32_t arg1, int32_t arg2, int32_t arg3);
	String(int8_tArray* arg0, int32_t arg1, int32_t arg2, String* arg3);
	String(int8_tArray* arg0, int32_t arg1, int32_t arg2, Charset* arg3);
protected:
	String(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();
	virtual int32_t compareTo(Object* o) override;

private:
	virtual ::java::lang::Class* getClass0();
	friend String *operator"" _j(const char16_t *s, size_t n);
};
namespace java { namespace lang { String* operator "" _j(const char16_t* p, size_t n); } }
using java::lang::operator "" _j;

