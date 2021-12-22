#include <tdme/engine/Timing.h>

#include <array>

#include <tdme/tdme.h>
#include <tdme/utilities/Time.h>

using std::array;

using tdme::engine::Timing;
using tdme::utilities::Time;

Timing::Timing()
{
	frame = 0;
	startTime = Time::getCurrentMillis();
	lastFrameAtTime = UNDEFINED;
	currentFrameAtTime = UNDEFINED;
	avarageFPS = 60.0f;
	lastFrameAtTime = Timing::UNDEFINED;
	currentFrameAtTime = Timing::UNDEFINED;
	fps = Timing::UNDEFINED;
	avarageFPS = Timing::UNDEFINED;
	for (auto i = 0; i < avarageFPSSequence.size(); i++) avarageFPSSequence[i] = 60.0f;
}

constexpr int64_t Timing::UNDEFINED;

void Timing::updateTiming()
{
	lastFrameAtTime = currentFrameAtTime;
	currentFrameAtTime = Time::getCurrentMillis();
	fps = 0;
	if (lastFrameAtTime != UNDEFINED) {
		fps = 1000.0f / ((currentFrameAtTime - lastFrameAtTime));
	}
	fps++;

	// avarage fps
	avarageFPSIndex = (avarageFPSIndex + 1) % avarageFPSSequence.size();
	avarageFPSSequence[avarageFPSIndex] = fps;
	avarageFPS = 0.0f;
	for (auto i = 0; i < avarageFPSSequence.size(); i++) avarageFPS+= avarageFPSSequence[(avarageFPSIndex - i) % avarageFPSSequence.size()];
	avarageFPS/= avarageFPSSequence.size();

}
