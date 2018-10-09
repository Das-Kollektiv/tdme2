#include <tdme/gui/effects/GUIEffect.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::effects::GUIEffect;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::gui::events::Action;

GUIEffect::GUIEffect() 
{
	active = false;
	timeTotal = 0.0f;
	timeLeft = timeTotal;
	timePassed = 0.0f;
}

GUIEffect::~GUIEffect() {
	if (action != nullptr) delete action;
}

void GUIEffect::start()
{
	active = true;
	timeLeft = timeTotal;
	timePassed = 0.0f;
}

void GUIEffect::update(GUIRenderer* guiRenderer)
{
	if (active == false)
		return;

	// TODO: Do not use timing from main engine
	timePassed = static_cast< float >((Engine::getInstance()->getTiming()->getDeltaTime())) / 1000.0f;
	timeLeft -= timePassed;
	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
		active = false;
		if (action != nullptr) {
			action->performAction();
		}
	}
}

