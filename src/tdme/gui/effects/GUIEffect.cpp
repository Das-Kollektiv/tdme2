// Generated from /tdme/src/tdme/gui/effects/GUIEffect.java
#include <tdme/gui/effects/GUIEffect.h>

#include <tdme/engine/Engine.h>
#include <tdme/engine/Timing.h>
#include <tdme/gui/events/Action.h>

using tdme::gui::effects::GUIEffect;
using tdme::engine::Engine;
using tdme::engine::Timing;
using tdme::gui::events::Action;

GUIEffect::GUIEffect(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIEffect::GUIEffect() 
	: GUIEffect(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUIEffect::ctor()
{
	super::ctor();
	active = false;
	timeTotal = 0.0f;
	timeLeft = timeTotal;
	timePassed = 0.0f;
}

bool GUIEffect::isActive()
{
	return active;
}

float GUIEffect::getTimeTotal()
{
	return timeTotal;
}

void GUIEffect::setTimeTotal(float timeTotal)
{
	this->timeTotal = timeTotal;
}

Action* GUIEffect::getAction()
{
	return action;
}

void GUIEffect::setAction(Action* action)
{
	this->action = action;
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIEffect::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.effects.GUIEffect", 26);
    return c;
}

java::lang::Class* GUIEffect::getClass0()
{
	return class_();
}

