// Generated from /tdme/lib/json.jar
#include <org/json/JSONObject_Null.h>

using org::json::JSONObject_Null;
extern void unimplemented_(const char16_t* name);
org::json::JSONObject_Null::JSONObject_Null(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}


/* private: void JSONObject_Null::ctor() */
Object* JSONObject_Null::clone()
{ /* stub */
	unimplemented_(u"Object* JSONObject_Null::clone()");
	return 0;
}

bool JSONObject_Null::equals(Object* object)
{ /* stub */
	unimplemented_(u"bool JSONObject_Null::equals(Object* object)");
	return 0;
}

String* JSONObject_Null::toString()
{ /* stub */
	unimplemented_(u"String* JSONObject_Null::toString()");
	return 0;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* JSONObject_Null::class_()
{
    static ::java::lang::Class* c = ::class_(u"org.json.JSONObject.Null", 24);
    return c;
}

java::lang::Class* JSONObject_Null::getClass0()
{
	return class_();
}

