#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>

using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;

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
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	effectState.positionX = positionXStart + ((positionXEnd - positionXStart) * t);
	effectState.positionY = positionYStart + ((positionYEnd - positionYStart) * t);
	guiRenderer->setGUIEffectOffsetX(guiRenderer->getGUIEffectOffsetX() + -effectState.positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(guiRenderer->getGUIEffectOffsetY() + -effectState.positionY / screenHeight * 2.0f);
}
