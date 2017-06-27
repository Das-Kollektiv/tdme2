// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;


struct default_init_tag;
class com::jogamp::newt::event::KeyEvent_NonPrintableRange
	: public virtual Object
{

public:
	typedef Object super;
	bool inclKeyChar {  };
	int16_t max {  };
	int16_t min {  };

	/*void ctor(int16_t arg0, int16_t arg1, bool arg2); (private) */

	// Generated
	KeyEvent_NonPrintableRange();
protected:
	KeyEvent_NonPrintableRange(const ::default_init_tag&);


public:
	static ::java::lang::Class *class_();

private:
	virtual ::java::lang::Class* getClass0();
};
