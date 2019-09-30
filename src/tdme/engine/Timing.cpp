#include <tdme/engine/Timing.h>

#include <tdme/utils/Time.h>

using tdme::engine::Timing;
using tdme::utils::Time;

Timing::Timing() 
{
	frame = 0;
	startTime = Time::getCurrentMillis();
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
	currentFrameAtTime = Time::getCurrentMillis();
	currentFPS = 0;
	if (lastFrameAtTime != UNDEFINED) {
		currentFPS = 1000.0f / ((currentFrameAtTime - lastFrameAtTime));
	}
	frame++;
}

int64_t Timing::getFrame()
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
	auto seconds = (Time::getCurrentMillis() - startTime) / 1000LL;
	return frame / seconds;
}
