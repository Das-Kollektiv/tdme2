// Generated from /tdme/src/tdme/engine/Timing.java
#include <tdme/engine/Timing.h>

#include <java/lang/System.h>

using tdme::engine::Timing;
using java::lang::System;

Timing::Timing() 
{
	frame = 0;
	startTime = System::currentTimeMillis();
	lastFrameAtTime = UNDEFINED;
	currentFrameAtTime = UNDEFINED;
	currentFPS = 60.0f;
	lastFrameAtTime = Timing::UNDEFINED;
	currentFrameAtTime = Timing::UNDEFINED;
	currentFPS = Timing::UNDEFINED;
}

constexpr int64_t Timing::UNDEFINED;

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
