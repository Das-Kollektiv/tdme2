// Generated from /tdme/src/tdme/engine/Timing.java
#include <tdme/engine/Timing.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <java/lang/System.h>

using tdme::engine::Timing;
using java::lang::String;
using java::lang::StringBuilder;
using java::lang::System;

Timing::Timing(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

Timing::Timing() 
	: Timing(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void Timing::init()
{
	lastFrameAtTime = Timing::UNDEFINED;
	currentFrameAtTime = Timing::UNDEFINED;
	currentFPS = Timing::UNDEFINED;
}

constexpr int64_t Timing::UNDEFINED;

void Timing::ctor()
{
	super::ctor();
	init();
	frame = 0;
	startTime = System::currentTimeMillis();
	lastFrameAtTime = UNDEFINED;
	currentFrameAtTime = UNDEFINED;
	currentFPS = 60.0f;
}

void Timing::updateTiming()
{
	lastFrameAtTime = currentFrameAtTime;
	currentFrameAtTime = System::currentTimeMillis();
	currentFPS = 0;
	if (lastFrameAtTime != UNDEFINED) {
		currentFPS = 1000.0f / ((currentFrameAtTime - lastFrameAtTime));
	}
	frame++;
}

int32_t Timing::getFrame()
{
	return frame;
}

int64_t Timing::getStartTime()
{
	return startTime;
}

int64_t Timing::getLastFrameAtTime()
{
	return lastFrameAtTime;
}

int64_t Timing::getCurrentFrameAtTime()
{
	return currentFrameAtTime;
}

int64_t Timing::getDeltaTime()
{
	if (currentFrameAtTime == UNDEFINED || lastFrameAtTime == UNDEFINED) {
		return 0LL;
	}
	return currentFrameAtTime - lastFrameAtTime;
}

float Timing::getCurrentFPS()
{
	return currentFPS;
}

float Timing::getAverageFPS()
{
	auto seconds = (System::currentTimeMillis() - startTime) / 1000LL;
	return frame / seconds;
}

String* Timing::toString()
{
	return ::java::lang::StringBuilder().append(u"Timing [frame="_j)->append(frame)
		->append(u", startTime="_j)
		->append(startTime)
		->append(u", lastFrameAtTime="_j)
		->append(lastFrameAtTime)
		->append(u", currentFrameAtTime="_j)
		->append(currentFrameAtTime)
		->append(u", currentFPS="_j)
		->append(currentFPS)
		->append(u"]"_j)->toString();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* Timing::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.engine.Timing", 18);
    return c;
}

java::lang::Class* Timing::getClass0()
{
	return class_();
}

