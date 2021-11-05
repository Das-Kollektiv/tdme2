#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>

using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;

GUIPositionEffect::GUIPositionEffect(): GUIEffect()
{
	effectState.type = EffectState::TYPE_POSITION;
}

void GUIPositionEffect::applyState(const EffectState& state) {
	if (state.type != EffectState::TYPE_RESET && state.type != EffectState::TYPE_POSITION) return;
	this->positionXStart = state.positionX;
	this->positionYStart = state.positionY;
}

void GUIPositionEffect::apply(GUIRenderer* guiRenderer)
{
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	effectState.positionX = positionXStart + ((positionXEnd - positionXStart) / timeTotal * (timeTotal - timeLeft));
	effectState.positionY = positionYStart + ((positionYEnd - positionYStart) / timeTotal * (timeTotal - timeLeft));
	guiRenderer->setGUIEffectOffsetX(-effectState.positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(-effectState.positionY / screenHeight * 2.0f);
}
