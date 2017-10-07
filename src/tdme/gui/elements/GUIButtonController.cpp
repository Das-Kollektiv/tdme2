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

