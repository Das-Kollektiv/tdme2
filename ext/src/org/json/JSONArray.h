// Generated from /tdme/lib/json.jar

#pragma once

#include <fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::Writer;
using java::lang::String;
using java::util::ArrayList;
using java::util::Collection;
using java::util::Map;
using org::json::JSONObject;
using org::json::JSONTokener;


struct default_init_tag;
class org::json::JSONArray
	: public virtual Object
{

public:
	typedef Object super;

private:
	ArrayList* myArrayList {  };

protected:
	void ctor();
	void ctor(JSONTokener* x);
	void ctor(String* source);
	void ctor(Collection* arg0);
	void ctor(Object* arg0);

public:
	virtual Object* get(int32_t index);
	virtual bool getBoolean(int32_t index);
	virtual double getDouble(int32_t arg0);
	virtual int32_t getInt(int32_t arg0);
	virtual JSONArray* getJSONArray(int32_t index);
	virtual JSONObject* getJSONObject(int32_t index);
	virtual int64_t getLong(int32_t arg0);
	virtual String* getString(int32_t index);
	virtual bool isNull(int32_t index);
	virtual String* join(String* arg0);
	virtual int32_t length();
	virtual Object* opt(int32_t index);
	virtual bool optBoolean(int32_t index);
	virtual bool optBoolean(int32_t arg0, bool arg1);
	virtual double optDouble(int32_t index);
	virtual double optDouble(int32_t arg0, double arg1);
	virtual int32_t optInt(int32_t index);
	virtual int32_t optInt(int32_t arg0, int32_t arg1);
	virtual JSONArray* optJSONArray(int32_t index);
	virtual JSONObject* optJSONObject(int32_t index);
	virtual int64_t optLong(int32_t index);
	virtual int64_t optLong(int32_t arg0, int64_t arg1);
	virtual String* optString(int32_t index);
	virtual String* optString(int32_t index, String* defaultValue);
	virtual JSONArray* put(bool value);
	virtual JSONArray* put(Collection* value);
	virtual JSONArray* put(double value);
	virtual JSONArray* put(int32_t value);
	virtual JSONArray* put(int64_t value);
	virtual JSONArray* put(Map* value);
	virtual JSONArray* put(Object* value);
	virtual JSONArray* put(int32_t index, bool value);
	virtual JSONArray* put(int32_t index, Collection* value);
	virtual JSONArray* put(int32_t index, double value);
	virtual JSONArray* put(int32_t index, int32_t value);
	virtual JSONArray* put(int32_t index, int64_t value);
	virtual JSONArray* put(int32_t index, Map* value);
	virtual JSONArray* put(int32_t index, Object* value);
	virtual Object* remove(int32_t index);
	virtual JSONObject* toJSONObject(JSONArray* arg0);
	String* toString() override;
	virtual String* toString(int32_t indentFactor);

public: /* package */
	virtual String* toString(int32_t arg0, int32_t arg1);

public:
	virtual Writer* write(Writer* arg0);

	// Generated
	JSONArray();
	JSONArray(JSONTokener* x);
	JSONArray(String* source);
	JSONArray(Collection* arg0);
	JSONArray(Object* arg0);
protected:
	JSONArray(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
