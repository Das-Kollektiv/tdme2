// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using com::jogamp::nativewindow::WindowClosingProtocol_WindowClosingMode;


struct com::jogamp::nativewindow::WindowClosingProtocol
	: public virtual Object
{

	virtual WindowClosingProtocol_WindowClosingMode* getDefaultCloseOperation() = 0;
	virtual WindowClosingProtocol_WindowClosingMode* setDefaultCloseOperation(WindowClosingProtocol_WindowClosingMode* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
