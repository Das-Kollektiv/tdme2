#include <tdme/gui/effects/GUIEffect.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/utilities/Action.h>

using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::gui::effects::GUIEffect;
using tdme::utilities::Action;

GUIEffect::GUIEffect()
{
}

GUIEffect::~GUIEffect() {
	if (action != nullptr) delete action;
}

void GUIEffect::start()
{
	startState = effectState;
	endState = originalEndState;
	timeLeft = timeTotal;
	timePassed = 0.0f;
	timeLast = -1LL;
	repeatLeft = repeat;
	yoyoLeft = yoyo == true?1:0;
	active = true;
}

void GUIEffect::stop()
{
	active = false;
	effectState = originalStartState;
}

bool GUIEffect::update(GUIRenderer* guiRenderer)
{
	if (active == false) return false;
	// TODO: Maybe do not use timing from main engine
	timePassed = timeLast == -1LL?0.0f:static_cast<float>(Engine::getInstance()->getTiming()->getCurrentFrameAtTime() - timeLast) / 1000.0f;
	timeLeft -= timePassed;
	timeLast = Engine::getInstance()->getTiming()->getCurrentFrameAtTime();
	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
		if (yoyoLeft > 0) {
			timeLeft = timeTotal;
			timePassed = 0.0f;
			yoyoLeft--;
			endState = originalStartState;
			startState = originalEndState;
		} else
		if (repeat == -1 || repeatLeft > 0) {
			timeLeft = timeTotal;
			timePassed = 0.0f;
			if (repeat != -1) repeatLeft--;
			yoyoLeft = yoyo == true?1:0;
			startState = originalStartState;
			endState = originalEndState;
		} else
		if (persistant == false) {
			active = false;
			return true;
		}
	}
	return false;
}

