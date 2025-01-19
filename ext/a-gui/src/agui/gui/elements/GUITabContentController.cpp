#include <agui/gui/elements/GUITabContentController.h>

#include <agui/agui.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUITabContentController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

GUITabContentController::GUITabContentController(GUINode* node)
	: GUINodeController(node)
{
	this->selected = false;
	CONDITION_SELECTED = node->getId() + "-selected";
	CONDITION_UNSELECTED = node->getId() + "-unselected";
}

bool GUITabContentController::isDisabled()
{
	return false;
}

void GUITabContentController::setDisabled(bool disabled)
{
}

bool GUITabContentController::isSelected()
{
	return selected;
}

void GUITabContentController::setSelected(bool selected)
{
	auto& nodeConditions = parentElementNode->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = selected;
	nodeConditions.add(this->selected == true ?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUITabContentController::initialize()
{
	auto _parentElementNode = this->node->getParentNode();
	while (dynamic_cast<GUIElementNode*>(_parentElementNode) == nullptr) _parentElementNode = _parentElementNode->getParentNode();
	parentElementNode = required_dynamic_cast<GUIElementNode*>(_parentElementNode);
}

void GUITabContentController::dispose()
{
}

void GUITabContentController::postLayout()
{
}

void GUITabContentController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
}

void GUITabContentController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUITabContentController::tick()
{
}

void GUITabContentController::onFocusGained()
{
}

void GUITabContentController::onFocusLost()
{
}

bool GUITabContentController::hasValue()
{
	return false;
}

const MutableString& GUITabContentController::getValue()
{
	return value;
}

void GUITabContentController::setValue(const MutableString& value)
{
}

void GUITabContentController::onSubTreeChange()
{
}
