#include <agui/gui/elements/GUIMenuItemController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUIDropDownController.h>
#include <agui/gui/elements/GUIMenuHeaderItemController.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUITextNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/StringTools.h>

using std::string;

using agui::gui::elements::GUIMenuHeaderItemController;
using agui::gui::elements::GUIMenuItemController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUITextNode;
using agui::gui::GUI;
using agui::utilities::MutableString;
using agui::utilities::StringTools;

string GUIMenuItemController::CONDITION_SELECTED = "selected";
string GUIMenuItemController::CONDITION_UNSELECTED = "unselected";

GUIMenuItemController::GUIMenuItemController(GUINode* node)
	: GUIElementController(node)
{
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
}

bool GUIMenuItemController::isSelected()
{
	return selected;
}

void GUIMenuItemController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIMenuItemController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIMenuItemController::initialize()
{
	//
	menuHeaderItemNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUIMenuHeaderItemController*>(menuHeaderItemNode->getController()) != nullptr) {
			break;
		}
		menuHeaderItemNode = menuHeaderItemNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}
	setDisabled(isDisabled());

	//
	GUIElementController::initialize();
}

void GUIMenuItemController::postLayout()
{
}

void GUIMenuItemController::dispose()
{
	GUIElementController::dispose();
}

void GUIMenuItemController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (node == this->node &&
		node->isEventBelongingToNode(event) &&
		event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED &&
		event->getButton() == MOUSE_BUTTON_LEFT) {
		auto menuHeaderItemController = required_dynamic_cast<GUIMenuHeaderItemController*>(menuHeaderItemNode->getController());
		menuHeaderItemController->toggleOpenState();
		menuHeaderItemController->unselect();
		menuHeaderItemController->unselectSelection();
		event->setProcessed(true);
	}
}

void GUIMenuItemController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	if (isDisabled() == false && event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
		switch (event->getKeyCode()) {
			case GUIKeyboardEvent::KEYCODE_SPACE: {
				auto menuHeaderItemController = required_dynamic_cast<GUIMenuHeaderItemController*>(menuHeaderItemNode->getController());
				menuHeaderItemController->toggleOpenState();
				menuHeaderItemController->unselect();
				menuHeaderItemController->unselectSelection();
				event->setProcessed(true);
			}
		}
	}
}

void GUIMenuItemController::tick()
{
	GUIElementController::tick();
}

void GUIMenuItemController::onFocusGained()
{
}

void GUIMenuItemController::onFocusLost()
{
}

bool GUIMenuItemController::hasValue()
{
	return false;
}

const MutableString& GUIMenuItemController::getValue()
{
	return value;
}

void GUIMenuItemController::setValue(const MutableString& value)
{
}
