#include <tdme/gui/effects/GUIColorEffect.h>

#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/GUIRenderer.h>
#include <tdme/math/Math.h>

using tdme::gui::effects::GUIColorEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;
using tdme::math::Math;

GUIColorEffect::GUIColorEffect(): GUIEffect()
{
	originalStartState.type = EffectState::TYPE_COLOR;
	originalEndState.type = EffectState::TYPE_COLOR;
	startState.type = EffectState::TYPE_COLOR;
	endState.type = EffectState::TYPE_COLOR;
	effectState.type = EffectState::TYPE_COLOR;
}

void GUIColorEffect::applyState(const EffectState& state) {
	if (state.type != EffectState::TYPE_RESET && state.type != EffectState::TYPE_COLOR) return;
	startState.colorAdd = state.colorAdd;
	startState.colorMul = state.colorMul;
}

void GUIColorEffect::apply(GUIRenderer* guiRenderer)
{
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	effectState.colorMul.set(
		startState.colorMul.getRed() + ((endState.colorMul.getRed() - startState.colorMul.getRed()) * t),
		startState.colorMul.getGreen() + ((endState.colorMul.getGreen() - startState.colorMul.getGreen()) * t),
		startState.colorMul.getBlue() + ((endState.colorMul.getBlue() - startState.colorMul.getBlue()) * t),
		startState.colorMul.getAlpha() + ((endState.colorMul.getAlpha() - startState.colorMul.getAlpha()) * t)
	);
	auto& effectColorMul = guiRenderer->getGUIEffectColorMul();
	auto& effectColorAdd = guiRenderer->getGUIEffectColorAdd();
	guiRenderer->setGUIEffectColorMul(
		GUIColor(
			effectColorMul.getRed() * effectState.colorMul.getRed(),
			effectColorMul.getGreen() * effectState.colorMul.getGreen(),
			effectColorMul.getBlue() * effectState.colorMul.getBlue(),
			effectColorMul.getAlpha() * effectState.colorMul.getAlpha()
		)
	);
	effectState.colorAdd.set(
		startState.colorAdd.getRed() + ((endState.colorAdd.getRed() - startState.colorAdd.getRed()) * t),
		startState.colorAdd.getGreen() + ((endState.colorAdd.getGreen() - startState.colorAdd.getGreen()) * t),
		startState.colorAdd.getBlue() + ((endState.colorAdd.getBlue() - startState.colorAdd.getBlue()) * t),
		startState.colorAdd.getAlpha() + ((endState.colorAdd.getAlpha() - startState.colorAdd.getAlpha()) * t)
	);
	guiRenderer->setGUIEffectColorAdd(
		GUIColor(
			effectColorAdd.getRed() + effectState.colorAdd.getRed(),
			effectColorAdd.getGreen() + effectState.colorAdd.getGreen(),
			effectColorAdd.getBlue() + effectState.colorAdd.getBlue(),
			effectColorAdd.getAlpha() + effectState.colorAdd.getAlpha()
		)
	);
}
