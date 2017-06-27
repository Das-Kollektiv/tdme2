// Generated from /tdme/src/tdme/gui/elements/GUIButtonController.java
#include <tdme/gui/elements/GUIButtonController.h>

using tdme::gui::elements::GUIButtonController;
GUIButtonController::GUIButtonController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIButtonController::GUIButtonController(GUINode* node) 
	: GUIButtonController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIButtonController::ctor(GUINode* node)
{
	super::ctor(node);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIButtonController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIButtonController", 37);
    return c;
}

java::lang::Class* GUIButtonController::getClass0()
{
	return class_();
}

