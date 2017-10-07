#include <tdme/gui/elements/GUIScrollAreaController.h>

#include <tdme/gui/elements/GUIScrollAreaController_initialize_1.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUIScrollAreaController;
using tdme::gui::elements::GUIScrollAreaController_initialize_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

GUIScrollAreaController::GUIScrollAreaController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
}

GUIScrollAreaController::GUIScrollAreaController(GUINode* node) 
	: GUIScrollAreaController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIScrollAreaController::ctor(GUINode* node)
{
	super::ctor(node);
}

bool GUIScrollAreaController::isDisabled()
{
	return false;
}

void GUIScrollAreaController::setDisabled(bool disabled)
{
}

void GUIScrollAreaController::initialize()
{
	auto const contentNode = dynamic_cast< GUIParentNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_inner"));
	auto const upArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_vertical_layout_up"));
	auto const downArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_vertical_layout_down"));
	auto const leftArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_horizontal_layout_left"));
	auto const rightArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_scrollbar_horizontal_layout_right"));
	node->getScreenNode()->addActionListener(new GUIScrollAreaController_initialize_1(this, upArrowNode, contentNode, downArrowNode, leftArrowNode, rightArrowNode));
}

void GUIScrollAreaController::dispose()
{
}

void GUIScrollAreaController::postLayout()
{
}

void GUIScrollAreaController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUIScrollAreaController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIScrollAreaController::tick()
{
}

void GUIScrollAreaController::onFocusGained()
{
}

void GUIScrollAreaController::onFocusLost()
{
}

bool GUIScrollAreaController::hasValue()
{
	return false;
}

MutableString* GUIScrollAreaController::getValue()
{
	return nullptr;
}

void GUIScrollAreaController::setValue(MutableString* value)
{
}

