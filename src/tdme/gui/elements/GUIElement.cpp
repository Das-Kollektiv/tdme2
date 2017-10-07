#include <tdme/gui/elements/GUIElement.h>

using tdme::gui::elements::GUIElement;

GUIElement::GUIElement(const ::default_init_tag&)
{
}

GUIElement::GUIElement()
	: GUIElement(*static_cast< ::default_init_tag* >(0))
{
}

