// Generated from /tdme/lib/json.jar
#include <org/json/JSONException.h>

using org::json::JSONException;
extern void unimplemented_(const char16_t* name);
org::json::JSONException::JSONException(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

org::json::JSONException::JSONException(String* message)
	: JSONException(*static_cast< ::default_init_tag* >(0))
{
	ctor(message);
}

org::json::JSONException::JSONException(Throwable* cause)
	: JSONException(*static_cast< ::default_init_tag* >(0))
{
	ctor(cause);
}

constexpr int64_t org::json::JSONException::serialVersionUID;

void JSONException::ctor(String* message)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONException::ctor(String* message)");
}

void JSONException::ctor(Throwable* cause)
{ /* stub */
	/* super::ctor(); */
	unimplemented_(u"void JSONException::ctor(Throwable* cause)");
}

Throwable* JSONException::getCause()
{ /* stub */
return cause ; /* getter */
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* JSONException::class_()
{
    static ::java::lang::Class* c = ::class_(u"org.json.JSONException", 22);
    return c;
}

java::lang::Class* JSONException::getClass0()
{
	return class_();
}

