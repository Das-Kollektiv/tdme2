// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/newt/event/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::newt::event::NEWTEvent;


struct com::jogamp::newt::event::NEWTEventConsumer
	: public virtual Object
{

	virtual bool consumeEvent(NEWTEvent* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
