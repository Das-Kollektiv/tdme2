// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/nativewindow/fwd-tdme.h>
#include <java/lang/fwd-tdme.h>
#include <com/jogamp/nativewindow/VisualIDHolder.h>
#include <com/jogamp/common/type/WriteCloneable.h>
#include <java/lang/Comparable.h>

using com::jogamp::nativewindow::VisualIDHolder;
using com::jogamp::common::type::WriteCloneable;
using java::lang::Comparable;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;


struct com::jogamp::nativewindow::CapabilitiesImmutable
	: public virtual VisualIDHolder
	, public virtual WriteCloneable
	, public virtual Comparable
{

	/*virtual bool equals(Object* arg0); (already declared) */
	virtual int32_t getAlphaBits() = 0;
	virtual int32_t getBlueBits() = 0;
	virtual int32_t getGreenBits() = 0;
	virtual int32_t getRedBits() = 0;
	virtual int32_t getTransparentAlphaValue() = 0;
	virtual int32_t getTransparentBlueValue() = 0;
	virtual int32_t getTransparentGreenValue() = 0;
	virtual int32_t getTransparentRedValue() = 0;
	/*virtual int32_t hashCode(); (already declared) */
	virtual bool isBackgroundOpaque() = 0;
	virtual bool isBitmap() = 0;
	virtual bool isOnscreen() = 0;
	/*virtual String* toString(); (already declared) */
	virtual StringBuilder* toString(StringBuilder* arg0) = 0;

	// Generated
	static ::java::lang::Class *class_();
	virtual String* toString();
};
