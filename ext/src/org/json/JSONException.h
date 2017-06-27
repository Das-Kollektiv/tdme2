// Generated from /tdme/lib/json.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <java/lang/Exception.h>

using java::lang::Exception;
using java::lang::String;
using java::lang::Throwable;


struct default_init_tag;
class org::json::JSONException
	: public Exception
{

public:
	typedef Exception super;

private:
	Throwable* cause {  };
	static constexpr int64_t serialVersionUID { 0LL };

protected:
	void ctor(String* message);
	void ctor(Throwable* cause);

public:
	Throwable* getCause() override;

	// Generated
	JSONException(String* message);
	JSONException(Throwable* cause);
protected:
	JSONException(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
