// Generated from /tdme/lib/json.jar
#include <org/json/JSONObject.h>

using org::json::JSONObject;
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

extern void unimplemented_(const char16_t* name);
org::json::JSONObject::JSONObject(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

org::json::JSONObject::JSONObject()
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

org::json::JSONObject::JSONObject(JSONTokener* x)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(x);
}

org::json::JSONObject::JSONObject(Map* arg0)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0);
}

org::json::JSONObject::JSONObject(Object* bean)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(bean);
}

org::json::JSONObject::JSONObject(String* source)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(source);
}

org::json::JSONObject::JSONObject(JSONObject* arg0, StringArray* arg1)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

org::json::JSONObject::JSONObject(Object* arg0, StringArray* arg1)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

org::json::JSONObject::JSONObject(String* arg0, Locale* arg1)
	: JSONObject(*static_cast< ::default_init_tag* >(0))
{
	ctor(arg0, arg1);
}

Object* org::json::JSONObject::NULL_;

void JSONObject::ctor()
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor()");
}

void JSONObject::ctor(JSONTokener* x)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(JSONTokener* x)");
}

void JSONObject::ctor(Map* arg0)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(Map* arg0)");
}

void JSONObject::ctor(Object* bean)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(Object* bean)");
}

void JSONObject::ctor(String* source)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(String* source)");
}

void JSONObject::ctor(JSONObject* arg0, StringArray* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(JSONObject* arg0, StringArray* arg1)");
}

void JSONObject::ctor(Object* arg0, StringArray* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(Object* arg0, StringArray* arg1)");
}

void JSONObject::ctor(String* arg0, Locale* arg1)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONObject::ctor(String* arg0, Locale* arg1)");
}

JSONObject* JSONObject::accumulate(String* key, Object* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::accumulate(String* key, Object* value)");
	return 0;
}

JSONObject* JSONObject::append(String* key, Object* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::append(String* key, Object* value)");
	return 0;
}

String* JSONObject::doubleToString(double d)
{ /* stub */
	clinit();
	unimplemented_(u"String* JSONObject::doubleToString(double d)");
	return 0;
}

Object* JSONObject::get(String* key)
{ /* stub */
	unimplemented_(u"Object* JSONObject::get(String* key)");
	return 0;
}

bool JSONObject::getBoolean(String* key)
{ /* stub */
	unimplemented_(u"bool JSONObject::getBoolean(String* key)");
	return 0;
}

double JSONObject::getDouble(String* arg0)
{ /* stub */
	unimplemented_(u"double JSONObject::getDouble(String* arg0)");
	return 0;
}

int32_t JSONObject::getInt(String* arg0)
{ /* stub */
	unimplemented_(u"int32_t JSONObject::getInt(String* arg0)");
	return 0;
}

JSONArray* JSONObject::getJSONArray(String* key)
{ /* stub */
	unimplemented_(u"JSONArray* JSONObject::getJSONArray(String* key)");
	return 0;
}

JSONObject* JSONObject::getJSONObject(String* key)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::getJSONObject(String* key)");
	return 0;
}

int64_t JSONObject::getLong(String* arg0)
{ /* stub */
	unimplemented_(u"int64_t JSONObject::getLong(String* arg0)");
	return 0;
}

StringArray* JSONObject::getNames(JSONObject* jo)
{ /* stub */
	clinit();
	unimplemented_(u"StringArray* JSONObject::getNames(JSONObject* jo)");
	return 0;
}

StringArray* JSONObject::getNames(Object* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"StringArray* JSONObject::getNames(Object* arg0)");
	return 0;
}

String* JSONObject::getString(String* key)
{ /* stub */
	unimplemented_(u"String* JSONObject::getString(String* key)");
	return 0;
}

bool JSONObject::has(String* key)
{ /* stub */
	unimplemented_(u"bool JSONObject::has(String* key)");
	return 0;
}

JSONObject* JSONObject::increment(String* key)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::increment(String* key)");
	return 0;
}

bool JSONObject::isNull(String* key)
{ /* stub */
	unimplemented_(u"bool JSONObject::isNull(String* key)");
	return 0;
}

Iterator* JSONObject::keys()
{ /* stub */
	unimplemented_(u"Iterator* JSONObject::keys()");
	return 0;
}

int32_t JSONObject::length()
{ /* stub */
	unimplemented_(u"int32_t JSONObject::length()");
	return 0;
}

JSONArray* JSONObject::names()
{ /* stub */
	unimplemented_(u"JSONArray* JSONObject::names()");
	return 0;
}

String* JSONObject::numberToString(Number* number)
{ /* stub */
	clinit();
	unimplemented_(u"String* JSONObject::numberToString(Number* number)");
	return 0;
}

Object* JSONObject::opt(String* key)
{ /* stub */
	unimplemented_(u"Object* JSONObject::opt(String* key)");
	return 0;
}

bool JSONObject::optBoolean(String* key)
{ /* stub */
	unimplemented_(u"bool JSONObject::optBoolean(String* key)");
	return 0;
}

bool JSONObject::optBoolean(String* arg0, bool arg1)
{ /* stub */
	unimplemented_(u"bool JSONObject::optBoolean(String* arg0, bool arg1)");
	return 0;
}

double JSONObject::optDouble(String* key)
{ /* stub */
	unimplemented_(u"double JSONObject::optDouble(String* key)");
	return 0;
}

double JSONObject::optDouble(String* arg0, double arg1)
{ /* stub */
	unimplemented_(u"double JSONObject::optDouble(String* arg0, double arg1)");
	return 0;
}

int32_t JSONObject::optInt(String* key)
{ /* stub */
	unimplemented_(u"int32_t JSONObject::optInt(String* key)");
	return 0;
}

int32_t JSONObject::optInt(String* arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"int32_t JSONObject::optInt(String* arg0, int32_t arg1)");
	return 0;
}

JSONArray* JSONObject::optJSONArray(String* key)
{ /* stub */
	unimplemented_(u"JSONArray* JSONObject::optJSONArray(String* key)");
	return 0;
}

JSONObject* JSONObject::optJSONObject(String* key)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::optJSONObject(String* key)");
	return 0;
}

int64_t JSONObject::optLong(String* key)
{ /* stub */
	unimplemented_(u"int64_t JSONObject::optLong(String* key)");
	return 0;
}

int64_t JSONObject::optLong(String* arg0, int64_t arg1)
{ /* stub */
	unimplemented_(u"int64_t JSONObject::optLong(String* arg0, int64_t arg1)");
	return 0;
}

String* JSONObject::optString(String* key)
{ /* stub */
	unimplemented_(u"String* JSONObject::optString(String* key)");
	return 0;
}

String* JSONObject::optString(String* key, String* defaultValue)
{ /* stub */
	unimplemented_(u"String* JSONObject::optString(String* key, String* defaultValue)");
	return 0;
}

/* private: void JSONObject::populateMap(Object* arg0) */
JSONObject* JSONObject::put(String* key, bool value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, bool value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, Collection* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, Collection* value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, double value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, double value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, int32_t value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, int32_t value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, int64_t value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, int64_t value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, Map* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, Map* value)");
	return 0;
}

JSONObject* JSONObject::put(String* key, Object* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::put(String* key, Object* value)");
	return 0;
}

JSONObject* JSONObject::putOnce(String* key, Object* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::putOnce(String* key, Object* value)");
	return 0;
}

JSONObject* JSONObject::putOpt(String* key, Object* value)
{ /* stub */
	unimplemented_(u"JSONObject* JSONObject::putOpt(String* key, Object* value)");
	return 0;
}

String* JSONObject::quote(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* JSONObject::quote(String* arg0)");
	return 0;
}

Object* JSONObject::remove(String* key)
{ /* stub */
	unimplemented_(u"Object* JSONObject::remove(String* key)");
	return 0;
}

Object* JSONObject::stringToValue(String* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Object* JSONObject::stringToValue(String* arg0)");
	return 0;
}

void JSONObject::testValidity(Object* o)
{ /* stub */
	clinit();
	unimplemented_(u"void JSONObject::testValidity(Object* o)");
}

JSONArray* JSONObject::toJSONArray(JSONArray* arg0)
{ /* stub */
	unimplemented_(u"JSONArray* JSONObject::toJSONArray(JSONArray* arg0)");
	return 0;
}

String* JSONObject::toString()
{ /* stub */
	unimplemented_(u"String* JSONObject::toString()");
	return 0;
}

String* JSONObject::toString(int32_t indentFactor)
{ /* stub */
	unimplemented_(u"String* JSONObject::toString(int32_t indentFactor)");
	return 0;
}

String* JSONObject::toString(int32_t arg0, int32_t arg1)
{ /* stub */
	unimplemented_(u"String* JSONObject::toString(int32_t arg0, int32_t arg1)");
	return 0;
}

String* JSONObject::valueToString(Object* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"String* JSONObject::valueToString(Object* arg0)");
	return 0;
}

String* JSONObject::valueToString(Object* arg0, int32_t arg1, int32_t arg2)
{ /* stub */
	clinit();
	unimplemented_(u"String* JSONObject::valueToString(Object* arg0, int32_t arg1, int32_t arg2)");
	return 0;
}

Object* JSONObject::wrap(Object* arg0)
{ /* stub */
	clinit();
	unimplemented_(u"Object* JSONObject::wrap(Object* arg0)");
	return 0;
}

Writer* JSONObject::write(Writer* arg0)
{ /* stub */
	unimplemented_(u"Writer* JSONObject::write(Writer* arg0)");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* JSONObject::class_()
{
    static ::java::lang::Class* c = ::class_(u"org.json.JSONObject", 19);
    return c;
}

java::lang::Class* JSONObject::getClass0()
{
	return class_();
}

