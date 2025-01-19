#include <agui/gui/effects/GUIColorEffect.h>

#include <agui/agui.h>
#include <agui/gui/effects/GUIEffectState.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/gui/GUI.h>
#include <agui/math/Math.h>

using agui::gui::effects::GUIColorEffect;
using agui::gui::effects::GUIEffectState;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode;
using agui::gui::renderer::GUIRenderer;
using agui::gui::GUI;
using agui::math::Math;

GUIColorEffect::GUIColorEffect(GUINode* guiNode): GUIEffect(EFFECTTYPE_COLOR, guiNode)
{
}

void GUIColorEffect::apply(GUI* gui)
{
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	auto effectState = node->getEffectState();
	effectState->colorMul.set(
		startState.colorMul.getRed() + ((endState.colorMul.getRed() - startState.colorMul.getRed()) * t),
		startState.colorMul.getGreen() + ((endState.colorMul.getGreen() - startState.colorMul.getGreen()) * t),
		startState.colorMul.getBlue() + ((endState.colorMul.getBlue() - startState.colorMul.getBlue()) * t),
		startState.colorMul.getAlpha() + ((endState.colorMul.getAlpha() - startState.colorMul.getAlpha()) * t)
	);
	auto guiRenderer = gui->getRenderer();
	const auto& effectColorMul = guiRenderer->getGUIEffectColorMul();
	const auto& effectColorAdd = guiRenderer->getGUIEffectColorAdd();
	guiRenderer->setGUIEffectColorMul(
		GUIColor(
			effectColorMul.getRed() * effectState->colorMul.getRed(),
			effectColorMul.getGreen() * effectState->colorMul.getGreen(),
			effectColorMul.getBlue() * effectState->colorMul.getBlue(),
			effectColorMul.getAlpha() * effectState->colorMul.getAlpha()
		)
	);
	effectState->colorAdd.set(
		startState.colorAdd.getRed() + ((endState.colorAdd.getRed() - startState.colorAdd.getRed()) * t),
		startState.colorAdd.getGreen() + ((endState.colorAdd.getGreen() - startState.colorAdd.getGreen()) * t),
		startState.colorAdd.getBlue() + ((endState.colorAdd.getBlue() - startState.colorAdd.getBlue()) * t),
		startState.colorAdd.getAlpha() + ((endState.colorAdd.getAlpha() - startState.colorAdd.getAlpha()) * t)
	);
	guiRenderer->setGUIEffectColorAdd(
		GUIColor(
			effectColorAdd.getRed() + effectState->colorAdd.getRed(),
			effectColorAdd.getGreen() + effectState->colorAdd.getGreen(),
			effectColorAdd.getBlue() + effectState->colorAdd.getBlue(),
			effectColorAdd.getAlpha() + effectState->colorAdd.getAlpha()
		)
	);
}
