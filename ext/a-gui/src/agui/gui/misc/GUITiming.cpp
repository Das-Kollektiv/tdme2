#include <agui/gui/misc/GUITiming.h>

#include <array>

#include <agui/agui.h>
#include <agui/utilities/Time.h>

using std::array;

using agui::gui::misc::GUITiming;
using agui::utilities::Time;

GUITiming::GUITiming()
{
	frame = 0;
	startTime = Time::getCurrentMillis();
	lastFrameAtTime = UNDEFINED;
	currentFrameAtTime = UNDEFINED;
	avarageFPS = 60.0f;
	lastFrameAtTime = GUITiming::UNDEFINED;
	currentFrameAtTime = GUITiming::UNDEFINED;
	fps = GUITiming::UNDEFINED;
	avarageFPS = GUITiming::UNDEFINED;
	for (auto i = 0; i < avarageFPSSequence.size(); i++) avarageFPSSequence[i] = 60.0f;
}

constexpr int64_t GUITiming::UNDEFINED;

void GUITiming::update()
{
	frame++;
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
