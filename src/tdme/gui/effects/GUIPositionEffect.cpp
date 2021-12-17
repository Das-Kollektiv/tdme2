#include <tdme/gui/effects/GUIPositionEffect.h>

#include <tdme/tdme.h>
#include <tdme/gui/effects/GUIEffectState.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/gui/GUI.h>
#include <tdme/math/Math.h>

using tdme::gui::effects::GUIPositionEffect;

using tdme::gui::effects::GUIEffectState;
using tdme::gui::nodes::GUINode;
using tdme::gui::renderer::GUIRenderer;
using tdme::gui::GUI;
using tdme::math::Math;

GUIPositionEffect::GUIPositionEffect(GUINode* guiNode): GUIEffect(EFFECTTYPE_POSITION, guiNode)
{
}

void GUIPositionEffect::apply(GUIRenderer* guiRenderer)
{
	float screenWidth = guiRenderer->getGUI()->getWidth();
	float screenHeight = guiRenderer->getGUI()->getHeight();
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	auto effectState = node->getEffectState();
	effectState->positionX = startState.positionX + ((endState.positionX - startState.positionX) * t);
	effectState->positionY = startState.positionY + ((endState.positionY - startState.positionY) * t);
	guiRenderer->setGUIEffectOffsetX(guiRenderer->getGUIEffectOffsetX() + -effectState->positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(guiRenderer->getGUIEffectOffsetY() + -effectState->positionY / screenHeight * 2.0f);
}
