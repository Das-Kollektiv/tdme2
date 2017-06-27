// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/newt/event/fwd-tdme.h>
#include <com/jogamp/newt/event/NEWTEventListener.h>

using com::jogamp::newt::event::NEWTEventListener;
using com::jogamp::newt::event::MouseEvent;


struct com::jogamp::newt::event::MouseListener
	: public virtual NEWTEventListener
{

	virtual void mouseClicked(MouseEvent* arg0) = 0;
	virtual void mouseDragged(MouseEvent* arg0) = 0;
	virtual void mouseEntered(MouseEvent* arg0) = 0;
	virtual void mouseExited(MouseEvent* arg0) = 0;
	virtual void mouseMoved(MouseEvent* arg0) = 0;
	virtual void mousePressed(MouseEvent* arg0) = 0;
	virtual void mouseReleased(MouseEvent* arg0) = 0;
	virtual void mouseWheelMoved(MouseEvent* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
