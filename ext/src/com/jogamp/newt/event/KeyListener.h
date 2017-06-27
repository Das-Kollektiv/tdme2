// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/event/NEWTEventListener.h>

using com::jogamp::newt::event::NEWTEventListener;
using com::jogamp::newt::event::KeyEvent;


struct com::jogamp::newt::event::KeyListener
	: public virtual NEWTEventListener
{

	virtual void keyPressed(KeyEvent* arg0) = 0;
	virtual void keyReleased(KeyEvent* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
