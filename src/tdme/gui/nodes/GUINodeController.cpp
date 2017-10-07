#include <tdme/gui/nodes/GUINodeController.h>

#include <tdme/gui/nodes/GUINode.h>

using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUINode;

GUINodeController::GUINodeController(const ::default_init_tag&)
{
}

GUINodeController::GUINodeController(GUINode* node) 
	: GUINodeController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUINodeController::ctor(GUINode* node)
{
	this->node = node;
}

GUINode* GUINodeController::getNode()
{
	return node;
}

