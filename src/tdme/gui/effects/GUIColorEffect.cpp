// Generated from /tdme/src/tdme/gui/effects/GUIColorEffect.java
#include <tdme/gui/effects/GUIColorEffect.h>

#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/renderer/GUIRenderer.h>

using tdme::gui::effects::GUIColorEffect;
using tdme::gui::nodes::GUIColor;
using tdme::gui::renderer::GUIRenderer;

GUIColorEffect::GUIColorEffect(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIColorEffect::GUIColorEffect() 
	: GUIColorEffect(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

void GUIColorEffect::init()
{
	colorAddStart = new GUIColor();
	colorAddEnd = new GUIColor();
	colorMulStart = new GUIColor();
	colorMulEnd = new GUIColor();
	colorAdd = new GUIColor();
	colorMul = new GUIColor();
}

void GUIColorEffect::ctor()
{
	super::ctor();
	init();
}

GUIColor* GUIColorEffect::getColorAddStart()
{
	return colorAddStart;
}

GUIColor* GUIColorEffect::getColorAddEnd()
{
	return colorAddEnd;
}

GUIColor* GUIColorEffect::getColorMulStart()
{
	return colorMulStart;
}

GUIColor* GUIColorEffect::getColorMulEnd()
{
	return colorMulEnd;
}

void GUIColorEffect::update(GUIRenderer* guiRenderer)
{
	super::update(guiRenderer);
}

void GUIColorEffect::apply(GUIRenderer* guiRenderer)
{
	if (active == false)
		return;

	colorMul->set(colorMulStart->getRed() + ((colorMulEnd->getRed() - colorMulStart->getRed()) / timeTotal * (timeTotal - timeLeft)), colorMulStart->getGreen() + ((colorMulEnd->getGreen() - colorMulStart->getGreen()) / timeTotal * (timeTotal - timeLeft)), colorMulStart->getBlue() + ((colorMulEnd->getBlue() - colorMulStart->getBlue()) / timeTotal * (timeTotal - timeLeft)), colorMulStart->getAlpha() + ((colorMulEnd->getAlpha() - colorMulStart->getAlpha()) / timeTotal * (timeTotal - timeLeft)));
	guiRenderer->setGUIEffectColorMul(colorMul);
	colorAdd->set(colorAddStart->getRed() + ((colorAddEnd->getRed() - colorAddStart->getRed()) / timeTotal * (timeTotal - timeLeft)), colorAddStart->getGreen() + ((colorAddEnd->getGreen() - colorAddStart->getGreen()) / timeTotal * (timeTotal - timeLeft)), colorAddStart->getBlue() + ((colorAddEnd->getBlue() - colorAddStart->getBlue()) / timeTotal * (timeTotal - timeLeft)), colorAddStart->getAlpha() + ((colorAddEnd->getAlpha() - colorAddStart->getAlpha()) / timeTotal * (timeTotal - timeLeft)));
	guiRenderer->setGUIEffectColorAdd(colorAdd);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIColorEffect::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.effects.GUIColorEffect", 31);
    return c;
}

java::lang::Class* GUIColorEffect::getClass0()
{
	return class_();
}

