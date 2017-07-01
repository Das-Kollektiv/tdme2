// Generated from /Library/Java/JavaVirtualMachines/1.6.0.jdk/Contents/Classes/classes.jar

#pragma once

#include <string>

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/lang/AbstractStringBuilder.h>
#include <java/io/Serializable.h>
#include <java/lang/CharSequence.h>

using std::wstring;

using java::lang::AbstractStringBuilder;
using java::io::Serializable;
using java::lang::CharSequence;
using java::io::ObjectInputStream;
using java::io::ObjectOutputStream;
using java::io::ObjectStreamField;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::String;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace lang {
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
}  // namespace lang

namespace io {
typedef ::SubArray< ::java::io::ObjectStreamField, ::java::lang::ObjectArray, ::java::lang::ComparableArray > ObjectStreamFieldArray;
}  // namespace io
}  // namespace java

using java::io::ObjectStreamFieldArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;

struct default_init_tag;
class java::lang::StringBuffer final
	: public AbstractStringBuilder
	, public Serializable
	, public virtual CharSequence
{

public:
	typedef AbstractStringBuilder super;

private:
	static ObjectStreamFieldArray* serialPersistentFields;

public: /* package */
	static constexpr int64_t serialVersionUID { 3388685877147921107LL };

protected:
	void ctor();
	void ctor(int32_t arg0);
	void ctor(String* arg0);
	void ctor(CharSequence* arg0);

public:
	StringBuffer* append(Object* arg0) override;
	StringBuffer* append(String* arg0) override;
	StringBuffer* append(StringBuffer* arg0) override;
	StringBuffer* append(CharSequence* arg0) override;
	StringBuffer* append(char16_tArray* arg0) override;
	StringBuffer* append(bool arg0) override;
	StringBuffer* append(char16_t arg0) override;
	StringBuffer* append(int32_t arg0) override;
	StringBuffer* append(int64_t arg0) override;
	StringBuffer* append(float arg0) override;
	StringBuffer* append(double arg0) override;
	StringBuffer* append(CharSequence* arg0, int32_t arg1, int32_t arg2) override;
	StringBuffer* append(char16_tArray* arg0, int32_t arg1, int32_t arg2) override;
	StringBuffer* appendCodePoint(int32_t arg0) override;
	int32_t capacity() override;
	char16_t charAt(int32_t arg0) override;
	int32_t codePointAt(int32_t arg0) override;
	int32_t codePointBefore(int32_t arg0) override;
	int32_t codePointCount(int32_t arg0, int32_t arg1) override;
	StringBuffer* delete_(int32_t arg0, int32_t arg1) override;
	StringBuffer* deleteCharAt(int32_t arg0) override;
	void ensureCapacity(int32_t arg0) override;
	void getChars(int32_t arg0, int32_t arg1, char16_tArray* arg2, int32_t arg3) override;
	int32_t indexOf(String* arg0) override;
	int32_t indexOf(String* arg0, int32_t arg1) override;
	StringBuffer* insert(int32_t arg0, Object* arg1) override;
	StringBuffer* insert(int32_t arg0, String* arg1) override;
	StringBuffer* insert(int32_t arg0, char16_tArray* arg1) override;
	StringBuffer* insert(int32_t arg0, CharSequence* arg1) override;
	StringBuffer* insert(int32_t arg0, bool arg1) override;
	StringBuffer* insert(int32_t arg0, char16_t arg1) override;
	StringBuffer* insert(int32_t arg0, int32_t arg1) override;
	StringBuffer* insert(int32_t arg0, int64_t arg1) override;
	StringBuffer* insert(int32_t arg0, float arg1) override;
	StringBuffer* insert(int32_t arg0, double arg1) override;
	StringBuffer* insert(int32_t arg0, char16_tArray* arg1, int32_t arg2, int32_t arg3) override;
	StringBuffer* insert(int32_t arg0, CharSequence* arg1, int32_t arg2, int32_t arg3) override;
	int32_t lastIndexOf(String* arg0) override;
	int32_t lastIndexOf(String* arg0, int32_t arg1) override;
	int32_t length() override;
	int32_t offsetByCodePoints(int32_t arg0, int32_t arg1) override;
	/*void readObject(ObjectInputStream* arg0); (private) */
	StringBuffer* replace(int32_t arg0, int32_t arg1, String* arg2) override;
	StringBuffer* reverse() override;
	void setCharAt(int32_t arg0, char16_t arg1) override;
	void setLength(int32_t arg0) override;
	CharSequence* subSequence(int32_t arg0, int32_t arg1) override;
	String* substring(int32_t arg0) override;
	String* substring(int32_t arg0, int32_t arg1) override;
	String* toString() override;
	void trimToSize() override;
	/*void writeObject(ObjectOutputStream* arg0); (private) */

	// Generated
	StringBuffer();
	StringBuffer(int32_t arg0);
	StringBuffer(String* arg0);
	StringBuffer(CharSequence* arg0);
protected:
	StringBuffer(const ::default_init_tag&);

private:
	wstring cppwstring;

public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
