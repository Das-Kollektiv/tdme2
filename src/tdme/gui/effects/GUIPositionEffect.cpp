#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/tdme.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>

using tdme::gui::effects::GUIPositionEffect;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;

GUIPositionEffect::GUIPositionEffect(): GUIEffect()
{
	originalStartState.type = EffectState::TYPE_POSITION;
	originalEndState.type = EffectState::TYPE_POSITION;
	startState.type = EffectState::TYPE_POSITION;
	endState.type = EffectState::TYPE_POSITION;
	effectState.type = EffectState::TYPE_POSITION;
}

void GUIPositionEffect::applyState(const EffectState& state) {
	if (state.type != EffectState::TYPE_RESET && state.type != EffectState::TYPE_POSITION) return;
	startState.positionX = state.positionX;
	startState.positionY = state.positionY;
}

void GUIPositionEffect::apply(GUIRenderer* guiRenderer)
{
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	effectState.positionX = startState.positionX + ((endState.positionX - startState.positionX) * t);
	effectState.positionY = startState.positionY + ((endState.positionY - startState.positionY) * t);
	guiRenderer->setGUIEffectOffsetX(guiRenderer->getGUIEffectOffsetX() + -effectState.positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(guiRenderer->getGUIEffectOffsetY() + -effectState.positionY / screenHeight * 2.0f);
}
