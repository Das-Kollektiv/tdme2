// Generated from /tdme/src/tdme/gui/elements/GUIElement.java
#include <tdme/gui/elements/GUIElement.h>

using tdme::gui::elements::GUIElement;
GUIElement::GUIElement(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIElement::GUIElement()
	: GUIElement(*static_cast< ::default_init_tag* >(0))
{
	ctor();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIElement::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIElement", 28);
    return c;
}

java::lang::Class* GUIElement::getClass0()
{
	return class_();
}

