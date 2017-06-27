// Generated from /tdme/lib/json.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Serializable;
using java::io::Writer;
using java::lang::CharSequence;
using java::lang::Comparable;
using java::lang::Number;
using java::lang::String;
using java::util::Collection;
using java::util::Iterator;
using java::util::Locale;
using java::util::Map;
using org::json::JSONArray;
using org::json::JSONTokener;

template<typename ComponentType, typename... Bases> struct SubArray;
namespace java {
namespace io {
typedef ::SubArray< ::java::io::Serializable, ::java::lang::ObjectArray > SerializableArray;
}  // namespace io

namespace lang {
typedef ::SubArray< ::java::lang::CharSequence, ObjectArray > CharSequenceArray;
typedef ::SubArray< ::java::lang::Comparable, ObjectArray > ComparableArray;
typedef ::SubArray< ::java::lang::String, ObjectArray, ::java::io::SerializableArray, ComparableArray, CharSequenceArray > StringArray;
}  // namespace lang
}  // namespace java

using java::io::SerializableArray;
using java::lang::CharSequenceArray;
using java::lang::ComparableArray;
using java::lang::ObjectArray;
using java::lang::StringArray;

struct default_init_tag;
class org::json::JSONObject
	: public virtual Object
{

public:
	typedef Object super;
	static Object* NULL_;

private:
	Map* map {  };

protected:
	void ctor();
	void ctor(JSONTokener* x);
	void ctor(Map* arg0);
	void ctor(Object* bean);
	void ctor(String* source);
	void ctor(JSONObject* arg0, StringArray* arg1);
	void ctor(Object* arg0, StringArray* arg1);
	void ctor(String* arg0, Locale* arg1);

public:
	virtual JSONObject* accumulate(String* key, Object* value);
	virtual JSONObject* append(String* key, Object* value);
	static String* doubleToString(double d);
	virtual Object* get(String* key);
	virtual bool getBoolean(String* key);
	virtual double getDouble(String* arg0);
	virtual int32_t getInt(String* arg0);
	virtual JSONArray* getJSONArray(String* key);
	virtual JSONObject* getJSONObject(String* key);
	virtual int64_t getLong(String* arg0);
	static StringArray* getNames(JSONObject* jo);
	static StringArray* getNames(Object* arg0);
	virtual String* getString(String* key);
	virtual bool has(String* key);
	virtual JSONObject* increment(String* key);
	virtual bool isNull(String* key);
	virtual Iterator* keys();
	virtual int32_t length();
	virtual JSONArray* names();
	static String* numberToString(Number* number);
	virtual Object* opt(String* key);
	virtual bool optBoolean(String* key);
	virtual bool optBoolean(String* arg0, bool arg1);
	virtual double optDouble(String* key);
	virtual double optDouble(String* arg0, double arg1);
	virtual int32_t optInt(String* key);
	virtual int32_t optInt(String* arg0, int32_t arg1);
	virtual JSONArray* optJSONArray(String* key);
	virtual JSONObject* optJSONObject(String* key);
	virtual int64_t optLong(String* key);
	virtual int64_t optLong(String* arg0, int64_t arg1);
	virtual String* optString(String* key);
	virtual String* optString(String* key, String* defaultValue);
	/*void populateMap(Object* arg0); (private) */
	virtual JSONObject* put(String* key, bool value);
	virtual JSONObject* put(String* key, Collection* value);
	virtual JSONObject* put(String* key, double value);
	virtual JSONObject* put(String* key, int32_t value);
	virtual JSONObject* put(String* key, int64_t value);
	virtual JSONObject* put(String* key, Map* value);
	virtual JSONObject* put(String* key, Object* value);
	virtual JSONObject* putOnce(String* key, Object* value);
	virtual JSONObject* putOpt(String* key, Object* value);
	static String* quote(String* arg0);
	virtual Object* remove(String* key);
	static Object* stringToValue(String* arg0);
	static void testValidity(Object* o);
	virtual JSONArray* toJSONArray(JSONArray* arg0);
	String* toString() override;
	virtual String* toString(int32_t indentFactor);

public: /* package */
	virtual String* toString(int32_t arg0, int32_t arg1);

public:
	static String* valueToString(Object* arg0);

public: /* package */
	static String* valueToString(Object* arg0, int32_t arg1, int32_t arg2);

public:
	static Object* wrap(Object* arg0);
	virtual Writer* write(Writer* arg0);

	// Generated
	JSONObject();
	JSONObject(JSONTokener* x);
	JSONObject(Map* arg0);
	JSONObject(Object* bean);
	JSONObject(String* source);
	JSONObject(JSONObject* arg0, StringArray* arg1);
	JSONObject(Object* arg0, StringArray* arg1);
	JSONObject(String* arg0, Locale* arg1);
protected:
	JSONObject(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
