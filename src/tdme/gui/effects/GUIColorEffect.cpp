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
	effectState.type = EffectState::TYPE_COLOR;
}

void GUIColorEffect::applyState(const EffectState& state) {
	if (state.type != EffectState::TYPE_RESET && state.type != EffectState::TYPE_COLOR) return;
	this->colorAddStart = state.colorAdd;
	this->colorMulStart = state.colorMul;
}

void GUIColorEffect::apply(GUIRenderer* guiRenderer)
{
	auto t = Math::abs(timeTotal) < Math::EPSILON?1.0f:(timeTotal - timeLeft) / timeTotal;
	effectState.colorMul.set(
		colorMulStart.getRed() + ((colorMulEnd.getRed() - colorMulStart.getRed()) * t),
		colorMulStart.getGreen() + ((colorMulEnd.getGreen() - colorMulStart.getGreen()) * t),
		colorMulStart.getBlue() + ((colorMulEnd.getBlue() - colorMulStart.getBlue()) * t),
		colorMulStart.getAlpha() + ((colorMulEnd.getAlpha() - colorMulStart.getAlpha()) * t)
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
		colorAddStart.getRed() + ((colorAddEnd.getRed() - colorAddStart.getRed()) * t),
		colorAddStart.getGreen() + ((colorAddEnd.getGreen() - colorAddStart.getGreen()) * t),
		colorAddStart.getBlue() + ((colorAddEnd.getBlue() - colorAddStart.getBlue()) * t),
		colorAddStart.getAlpha() + ((colorAddEnd.getAlpha() - colorAddStart.getAlpha()) * t)
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
