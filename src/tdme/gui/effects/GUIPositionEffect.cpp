// Generated from /tdme/src/tdme/gui/effects/GUIPositionEffect.java
#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::GUI;
using tdme::gui::renderer::GUIRenderer;

GUIPositionEffect::GUIPositionEffect(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIPositionEffect::GUIPositionEffect() 
	: GUIPositionEffect(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUIPositionEffect::init()
{
	positionXStart = 0.0f;
	positionXEnd = 0.0f;
	positionYStart = 0.0f;
	positionYEnd = 0.0f;
	positionX = 0.0f;
	positionY = 0.0f;
}

void GUIPositionEffect::ctor()
{
	super::ctor();
	init();
}

float GUIPositionEffect::getPositionXStart()
{
	return positionXStart;
}

void GUIPositionEffect::setPositionXStart(float positionXStart)
{
	this->positionXStart = positionXStart;
}

float GUIPositionEffect::getPositionXEnd()
{
	return positionXEnd;
}

void GUIPositionEffect::setPositionXEnd(float positionXEnd)
{
	this->positionXEnd = positionXEnd;
}

float GUIPositionEffect::getPositionYStart()
{
	return positionYStart;
}

void GUIPositionEffect::setPositionYStart(float positionYStart)
{
	this->positionYStart = positionYStart;
}

float GUIPositionEffect::getPositionYEnd()
{
	return positionYEnd;
}

void GUIPositionEffect::setPositionYEnd(float positionYEnd)
{
	this->positionYEnd = positionYEnd;
}

void GUIPositionEffect::apply(GUIRenderer* guiRenderer)
{
	if (active == false)
		return;

	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	positionX = positionXStart + ((positionXEnd - positionXStart) / timeTotal * (timeTotal - timeLeft));
	positionY = positionYStart + ((positionYEnd - positionYStart) / timeTotal * (timeTotal - timeLeft));
	guiRenderer->setGUIEffectOffsetX(-positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(-positionY / screenHeight * 2.0f);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIPositionEffect::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.effects.GUIPositionEffect", 34);
    return c;
}

java::lang::Class* GUIPositionEffect::getClass0()
{
	return class_();
}

