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
	effectState.colorMul.set(colorMulStart.getRed() + ((colorMulEnd.getRed() - colorMulStart.getRed()) / timeTotal * (timeTotal - timeLeft)), colorMulStart.getGreen() + ((colorMulEnd.getGreen() - colorMulStart.getGreen()) / timeTotal * (timeTotal - timeLeft)), colorMulStart.getBlue() + ((colorMulEnd.getBlue() - colorMulStart.getBlue()) / timeTotal * (timeTotal - timeLeft)), colorMulStart.getAlpha() + ((colorMulEnd.getAlpha() - colorMulStart.getAlpha()) / timeTotal * (timeTotal - timeLeft)));
	guiRenderer->setGUIEffectColorMul(effectState.colorMul);
	effectState.colorAdd.set(colorAddStart.getRed() + ((colorAddEnd.getRed() - colorAddStart.getRed()) / timeTotal * (timeTotal - timeLeft)), colorAddStart.getGreen() + ((colorAddEnd.getGreen() - colorAddStart.getGreen()) / timeTotal * (timeTotal - timeLeft)), colorAddStart.getBlue() + ((colorAddEnd.getBlue() - colorAddStart.getBlue()) / timeTotal * (timeTotal - timeLeft)), colorAddStart.getAlpha() + ((colorAddEnd.getAlpha() - colorAddStart.getAlpha()) / timeTotal * (timeTotal - timeLeft)));
	guiRenderer->setGUIEffectColorAdd(effectState.colorAdd);
}
