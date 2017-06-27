// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/event/NEWTEventListener.h>

using com::jogamp::newt::event::NEWTEventListener;
using com::jogamp::newt::event::WindowEvent;
using com::jogamp::newt::event::WindowUpdateEvent;


struct com::jogamp::newt::event::WindowListener
	: public virtual NEWTEventListener
{

	virtual void windowDestroyNotify(WindowEvent* arg0) = 0;
	virtual void windowDestroyed(WindowEvent* arg0) = 0;
	virtual void windowGainedFocus(WindowEvent* arg0) = 0;
	virtual void windowLostFocus(WindowEvent* arg0) = 0;
	virtual void windowMoved(WindowEvent* arg0) = 0;
	virtual void windowRepaint(WindowUpdateEvent* arg0) = 0;
	virtual void windowResized(WindowEvent* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
