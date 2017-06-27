// Generated from /tdme/src/tdme/gui/nodes/GUINodeController.java
#include <tdme/gui/nodes/GUINodeController.h>

#include <tdme/gui/nodes/GUINode.h>

using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUINode;

GUINodeController::GUINodeController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUINodeController::GUINodeController(GUINode* node) 
	: GUINodeController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUINodeController::ctor(GUINode* node)
{
	super::ctor();
	this->node = node;
}

GUINode* GUINodeController::getNode()
{
	return node;
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUINodeController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUINodeController", 32);
    return c;
}

java::lang::Class* GUINodeController::getClass0()
{
	return class_();
}

