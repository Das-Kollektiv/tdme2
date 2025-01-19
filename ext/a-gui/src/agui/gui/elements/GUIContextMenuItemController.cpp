#include <agui/gui/elements/GUIContextMenuItemController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUIContextMenuController.h>
#include <agui/gui/elements/GUIMenuHeaderItemController.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>
#include <agui/utilities/StringTools.h>

using std::string;

using agui::gui::elements::GUIContextMenuController;
using agui::gui::elements::GUIContextMenuItemController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;
using agui::utilities::StringTools;

string GUIContextMenuItemController::CONDITION_SELECTED = "selected";
string GUIContextMenuItemController::CONDITION_UNSELECTED = "unselected";

GUIContextMenuItemController::GUIContextMenuItemController(GUINode* node)
	: GUIElementController(node)
{
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
}

bool GUIContextMenuItemController::isSelected()
{
	return selected;
}

void GUIContextMenuItemController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIContextMenuItemController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUIContextMenuItemController::initialize()
{
	contextMenuNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUIContextMenuController*>(contextMenuNode->getController()) != nullptr) {
			break;
		}
		contextMenuNode = contextMenuNode->getParentControllerNode();
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

void GUIContextMenuItemController::postLayout()
{
}

void GUIContextMenuItemController::dispose()
{
	GUIElementController::dispose();
}

void GUIContextMenuItemController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (isDisabled() == false && node == this->node && node->isEventBelongingToNode(event)) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(contextMenuNode));
		}
	}
}

void GUIContextMenuItemController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
}

void GUIContextMenuItemController::tick()
{
	GUIElementController::tick();
}

void GUIContextMenuItemController::onFocusGained()
{
}

void GUIContextMenuItemController::onFocusLost()
{
}

bool GUIContextMenuItemController::hasValue()
{
	return false;
}

const MutableString& GUIContextMenuItemController::getValue()
{
	return value;
}

void GUIContextMenuItemController::setValue(const MutableString& value)
{
}
