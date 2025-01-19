#include <agui/gui/elements/GUITabController.h>

#include <agui/agui.h>
#include <agui/gui/elements/GUITabsController.h>
#include <agui/gui/elements/GUITabsHeaderController.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUITabsController;
using agui::gui::elements::GUITabsHeaderController;
using agui::gui::elements::GUITabController;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

string GUITabController::CONDITION_DISABLED = "disabled";
string GUITabController::CONDITION_ENABLED = "enabled";
string GUITabController::CONDITION_SELECTED = "selected";
string GUITabController::CONDITION_UNSELECTED = "unselected";

GUITabController::GUITabController(GUINode* node)
	: GUIElementController(node)
{
	this->tabsNode = nullptr;
	this->tabsHeaderNode = nullptr;
	this->selected = false;
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
}

bool GUITabController::isDisabled()
{
	return disabled;
}

void GUITabController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

bool GUITabController::isSelected()
{
	return selected;
}

void GUITabController::setSelected(bool selected)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(this->node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = selected;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	if (required_dynamic_cast<GUITabsHeaderController*>(tabsHeaderNode->getController())->hasFocus() == true) {
		if (selected == true) {
			auto focussedBorderColor = node->getScreenNode()->getFoccussedBorderColor();
			auto border = node->getBorder();
			border.topColor = focussedBorderColor;
			border.leftColor = focussedBorderColor;
			border.bottomColor = focussedBorderColor;
			border.rightColor = focussedBorderColor;
		} else {
			auto border = node->getBorder();
			border.topColor = unfocussedNodeBorderTopColor;
			border.leftColor = unfocussedNodeBorderLeftColor;
			border.bottomColor = unfocussedNodeBorderBottomColor;
			border.rightColor = unfocussedNodeBorderRightColor;
		}
	} else {
		auto border = node->getBorder();
		border.topColor = unfocussedNodeBorderTopColor;
		border.leftColor = unfocussedNodeBorderLeftColor;
		border.bottomColor = unfocussedNodeBorderBottomColor;
		border.rightColor = unfocussedNodeBorderRightColor;
	}
}

void GUITabController::initialize()
{
	tabsNode = required_dynamic_cast<GUIParentNode*>(node)->getParentControllerNode()->getParentControllerNode();
	tabsHeaderNode = required_dynamic_cast<GUIParentNode*>(node)->getParentControllerNode();
	auto border = node->getBorder();
	unfocussedNodeBorderTopColor = border.topColor;
	unfocussedNodeBorderLeftColor = border.leftColor;
	unfocussedNodeBorderBottomColor = border.bottomColor;
	unfocussedNodeBorderRightColor = border.rightColor;
	setSelected(selected);

	//
	GUIElementController::initialize();
}

void GUITabController::dispose()
{
	GUIElementController::dispose();
}

void GUITabController::postLayout()
{
}

void GUITabController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			auto guiTabsController = required_dynamic_cast<GUITabsController*>(tabsNode->getController());
			guiTabsController->unselect();
			guiTabsController->select(required_dynamic_cast<GUIElementNode*>(this->node));
			guiTabsController->setTabContentSelected(node->getId());
		}
	}
}

void GUITabController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
}

void GUITabController::tick()
{
	GUIElementController::tick();
}

void GUITabController::onFocusGained()
{
}

void GUITabController::onFocusLost()
{
}

bool GUITabController::hasValue()
{
	return false;
}

const MutableString& GUITabController::getValue()
{
	return value;
}

void GUITabController::setValue(const MutableString& value)
{
}
