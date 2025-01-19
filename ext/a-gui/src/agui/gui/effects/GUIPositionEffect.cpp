#include <agui/gui/effects/GUIPositionEffect.h>

#include <agui/agui.h>
#include <agui/gui/effects/GUIEffectState.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>

using agui::gui::effects::GUIPositionEffect;

using agui::gui::effects::GUIEffectState;
using agui::gui::nodes::GUINode;
using agui::gui::renderer::GUIRenderer;
using agui::gui::GUI;
using agui::math::Math;

GUIPositionEffect::GUIPositionEffect(GUINode* guiNode): GUIEffect(EFFECTTYPE_POSITION, guiNode)
{
}

void GUIPositionEffect::apply(GUI* gui)
{
	float screenWidth = gui->getWidth();
	float screenHeight = gui->getHeight();
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	auto effectState = node->getEffectState();
	effectState->positionX = startState.positionX + ((endState.positionX - startState.positionX) * t);
	effectState->positionY = startState.positionY + ((endState.positionY - startState.positionY) * t);
	auto guiRenderer = gui->getRenderer();
	guiRenderer->setGUIEffectOffsetX(guiRenderer->getGUIEffectOffsetX() + -effectState->positionX / screenWidth * 2.0f);
	guiRenderer->setGUIEffectOffsetY(guiRenderer->getGUIEffectOffsetY() + -effectState->positionY / screenHeight * 2.0f);
}
