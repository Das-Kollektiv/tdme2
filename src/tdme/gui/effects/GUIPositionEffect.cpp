#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::GUI;
using tdme::gui::renderer::GUIRenderer;

GUIPositionEffect::GUIPositionEffect() 
{
	init();
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

