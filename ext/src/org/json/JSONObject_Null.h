// Generated from /tdme/lib/json.jar

#pragma once

#include <fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <org/json/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::lang::String;


struct default_init_tag;
class org::json::JSONObject_Null final
	: public Object
{

public:
	typedef Object super;

	/*void ctor(); (private) */

public: /* protected */
	Object* clone() override;

public:
	bool equals(Object* object) override;
	String* toString() override;

	// Generated
	JSONObject_Null();
protected:
	JSONObject_Null(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
