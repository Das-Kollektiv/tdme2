#include <agui/gui/elements/GUIGridItemController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUIGridController.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUIGridController;
using agui::gui::elements::GUIGridItemController;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

string GUIGridItemController::CONDITION_SELECTED = "selected";
string GUIGridItemController::CONDITION_UNSELECTED = "unselected";
string GUIGridItemController::CONDITION_FOCUSSED = "focussed";
string GUIGridItemController::CONDITION_UNFOCUSSED = "unfocussed";
string GUIGridItemController::CONDITION_DISABLED = "disabled";
string GUIGridItemController::CONDITION_ENABLED = "enabled";

GUIGridItemController::GUIGridItemController(GUINode* node)
	: GUIElementController(node)
{
	this->initialPostLayout = true;
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
	this->focussed = false;
}

void GUIGridItemController::setDisabled(bool disabled)
{
	unselect();
	GUIElementController::setDisabled(disabled);
}

void GUIGridItemController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = required_dynamic_cast<GUIGridController*>(gridNode->getController())->isDisabled();
	nodeConditions.remove(CONDITION_DISABLED);
	nodeConditions.remove(CONDITION_ENABLED);
	nodeConditions.add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIGridItemController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true ? CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = required_dynamic_cast<GUIGridController*>(gridNode->getController())->isDisabled();
	nodeConditions.remove(CONDITION_DISABLED);
	nodeConditions.remove(CONDITION_ENABLED);
	nodeConditions.add(disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUIGridItemController::toggle()
{
	if (selected == true) {
		unselect();
	} else {
		select();
	}
}

void GUIGridItemController::focus()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = true;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

void GUIGridItemController::unfocus()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = false;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

void GUIGridItemController::initialize()
{
	gridNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUIGridController*>(gridNode->getController()) != nullptr) {
			break;
		}
		gridNode = gridNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}

	//
	GUIElementController::initialize();
}

void GUIGridItemController::dispose()
{
	GUIElementController::dispose();
}

void GUIGridItemController::postLayout()
{
	if (initialPostLayout != true) return;
	if (selected == true) {
		node->scrollToNodeX(gridNode);
		node->scrollToNodeY(gridNode);
	}
	initialPostLayout = false;
}

void GUIGridItemController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = required_dynamic_cast<GUIGridController*>(gridNode->getController())->isDisabled();
	auto multipleSelection = required_dynamic_cast<GUIGridController*>(gridNode->getController())->isMultipleSelection();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event)) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			auto gridController = required_dynamic_cast<GUIGridController*>(gridNode->getController());
			auto gridItemElementNode = required_dynamic_cast<GUIElementNode*>(node);
			gridController->unfocus();
			if (multipleSelection == true && gridController->isKeyControlDown() == true) {
				gridController->toggle(gridItemElementNode);
				gridController->focus(gridItemElementNode);
			} else {
				gridController->unselect();
				gridController->select(gridItemElementNode);
				gridController->focus(gridItemElementNode);
			}
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(gridNode));
			node->scrollToNodeX(gridNode);
			node->scrollToNodeY(gridNode);
			node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(gridNode));
			if (event->getButton() == MOUSE_BUTTON_RIGHT) {
				node->getScreenNode()->forwardContextMenuRequest(required_dynamic_cast<GUIElementNode*>(gridNode), event->getXUnscaled(), event->getYUnscaled());
			}
		}
	}
}

void GUIGridItemController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
}

void GUIGridItemController::onFocusGained()
{
}

void GUIGridItemController::onFocusLost()
{
}

bool GUIGridItemController::hasValue()
{
	return false;
}

const MutableString& GUIGridItemController::getValue()
{
	return value;
}

void GUIGridItemController::setValue(const MutableString& value)
{
}
