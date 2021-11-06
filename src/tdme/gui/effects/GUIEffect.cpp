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
	active = false;
	timeTotal = 0.0f;
	timeLeft = timeTotal;
	timePassed = 0.0f;
	timeLast = -1LL;
}

GUIEffect::~GUIEffect() {
	if (action != nullptr) delete action;
}

void GUIEffect::start()
{
	active = true;
	timeLeft = timeTotal;
	timePassed = 0.0f;
	timeLast = -1LL;
}

void GUIEffect::stop()
{
	active = false;
	timeLeft = timeTotal;
	timePassed = 0.0f;
	timeLast = -1LL;
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
		if (persistant == false) {
			active = false;
			return true;
		}
	}
	return false;
}

