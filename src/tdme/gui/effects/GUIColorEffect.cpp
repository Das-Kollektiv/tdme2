#include <tdme/gui/effects/GUIColorEffect.h>

#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using tdme::gui::effects::GUIColorEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;

GUIColorEffect::GUIColorEffect(): GUIEffect()
{
	effectState.type = EffectState::TYPE_COLOR;
}

void GUIColorEffect::applyState(const EffectState& state) {
	if (state.type != EffectState::TYPE_RESET && state.type != EffectState::TYPE_COLOR) return;
	this->colorAddStart = state.colorAdd;
	this->colorMulStart = state.colorMul;
}

void GUIColorEffect::apply(GUIRenderer* guiRenderer)
{
	effectState.colorMul.set(
		colorMulStart.getRed() + ((colorMulEnd.getRed() - colorMulStart.getRed()) * (timeTotal - timeLeft) / timeTotal),
		colorMulStart.getGreen() + ((colorMulEnd.getGreen() - colorMulStart.getGreen()) * (timeTotal - timeLeft) / timeTotal),
		colorMulStart.getBlue() + ((colorMulEnd.getBlue() - colorMulStart.getBlue()) * (timeTotal - timeLeft) / timeTotal),
		colorMulStart.getAlpha() + ((colorMulEnd.getAlpha() - colorMulStart.getAlpha()) * (timeTotal - timeLeft) / timeTotal)
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
		colorAddStart.getRed() + ((colorAddEnd.getRed() - colorAddStart.getRed()) * (timeTotal - timeLeft) / timeTotal),
		colorAddStart.getGreen() + ((colorAddEnd.getGreen() - colorAddStart.getGreen()) * (timeTotal - timeLeft) / timeTotal),
		colorAddStart.getBlue() + ((colorAddEnd.getBlue() - colorAddStart.getBlue()) * (timeTotal - timeLeft) / timeTotal),
		colorAddStart.getAlpha() + ((colorAddEnd.getAlpha() - colorAddStart.getAlpha()) * (timeTotal - timeLeft) / timeTotal));
	guiRenderer->setGUIEffectColorAdd(
		GUIColor(
			effectColorAdd.getRed() + effectState.colorAdd.getRed(),
			effectColorAdd.getGreen() + effectState.colorAdd.getGreen(),
			effectColorAdd.getBlue() + effectState.colorAdd.getBlue(),
			effectColorAdd.getAlpha() + effectState.colorAdd.getAlpha()
		)
	);
}
