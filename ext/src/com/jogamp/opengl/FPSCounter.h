// Generated from /tdme/lib/jogl-all.jar

#pragma once

#include <fwd-tdme.h>
#include <com/jogamp/opengl/fwd-tdme.h>
#include <java/io/fwd-tdme.h>
#include <java/lang/Object.h>

using java::lang::Object;
using java::io::PrintStream;


struct com::jogamp::opengl::FPSCounter
	: public virtual Object
{
	static constexpr int32_t DEFAULT_FRAMES_PER_INTERVAL { 300 };

	virtual int64_t getFPSStartTime() = 0;
	virtual float getLastFPS() = 0;
	virtual int64_t getLastFPSPeriod() = 0;
	virtual int64_t getLastFPSUpdateTime() = 0;
	virtual float getTotalFPS() = 0;
	virtual int64_t getTotalFPSDuration() = 0;
	virtual int32_t getTotalFPSFrames() = 0;
	virtual int32_t getUpdateFPSFrames() = 0;
	virtual void resetFPSCounter() = 0;
	virtual void setUpdateFPSFrames(int32_t arg0, PrintStream* arg1) = 0;

	// Generated
	static ::java::lang::Class *class_();
};
