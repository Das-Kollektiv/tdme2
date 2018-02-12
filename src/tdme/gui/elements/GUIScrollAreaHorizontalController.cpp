#include <tdme/gui/elements/GUIScrollAreaHorizontalController.h>

#include <tdme/gui/elements/GUIScrollAreaHorizontalController_initialize_1.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUIScrollAreaHorizontalController;
using tdme::gui::elements::GUIScrollAreaHorizontalController_initialize_1;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

GUIScrollAreaHorizontalController::GUIScrollAreaHorizontalController(GUINode* node) 
	: GUINodeController(node)
{
}

bool GUIScrollAreaHorizontalController::isDisabled()
{
	return false;
}

void GUIScrollAreaHorizontalController::setDisabled(bool disabled)
{
}

void GUIScrollAreaHorizontalController::initialize()
{
	auto const contentNode = dynamic_cast< GUIParentNode* >(node->getScreenNode()->getNodeById(node->getId() + "_inner"));
	auto const leftArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_horizontal_layout_left"));
	auto const rightArrowNode = dynamic_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(node->getId() + "_scrollbar_horizontal_layout_right"));
	node->getScreenNode()->addActionListener(new GUIScrollAreaHorizontalController_initialize_1(this, leftArrowNode, contentNode, rightArrowNode));
}

void GUIScrollAreaHorizontalController::dispose()
{
}

void GUIScrollAreaHorizontalController::postLayout()
{
}

void GUIScrollAreaHorizontalController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUIScrollAreaHorizontalController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIScrollAreaHorizontalController::tick()
{
}

void GUIScrollAreaHorizontalController::onFocusGained()
{
}

void GUIScrollAreaHorizontalController::onFocusLost()
{
}

bool GUIScrollAreaHorizontalController::hasValue()
{
	return false;
}

const MutableString& GUIScrollAreaHorizontalController::getValue()
{
	return value;
}

void GUIScrollAreaHorizontalController::setValue(const MutableString& value)
{
}

