// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <java/util/EventObject.h>

using java::util::EventObject;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;


struct default_init_tag;
class com::jogamp::newt::event::NEWTEvent
	: public EventObject
{

public:
	typedef EventObject super;

public: /* package */
	static constexpr bool DEBUG { false };

private:
	Object* attachment {  };

public:
	static Object* consumedTag;

private:
	int16_t eventType {  };
	int64_t when {  };

protected:
	void ctor(int16_t arg0, Object* arg1, int64_t arg2);

public:
	Object* getAttachment();
	int16_t getEventType();
	int64_t getWhen();
	bool isConsumed();
	void setAttachment(Object* arg0);
	void setConsumed(bool arg0);
	static String* toHexString(int16_t arg0);
	String* toString() override;
	virtual StringBuilder* toString(StringBuilder* arg0);

	// Generated

public: /* protected */
	NEWTEvent(int16_t arg0, Object* arg1, int64_t arg2);
protected:
	NEWTEvent(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
