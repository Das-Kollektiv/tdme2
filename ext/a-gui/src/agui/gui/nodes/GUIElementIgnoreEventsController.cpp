#include <agui/gui/nodes/GUIElementIgnoreEventsController.h>

#include <agui/agui.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementIgnoreEventsController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

GUIElementIgnoreEventsController::GUIElementIgnoreEventsController(GUINode* node)
	: GUINodeController(node)
{
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
}

string GUIElementIgnoreEventsController::CONDITION_DISABLED= "disabled";
string GUIElementIgnoreEventsController::CONDITION_ENABLED = "enabled";

bool GUIElementIgnoreEventsController::isDisabled()
{
	return disabled;
}

void GUIElementIgnoreEventsController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUIElementIgnoreEventsController::initialize()
{
	setDisabled(disabled);
}

void GUIElementIgnoreEventsController::dispose()
{
}

void GUIElementIgnoreEventsController::postLayout()
{
}

void GUIElementIgnoreEventsController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			if (required_dynamic_cast<GUIElementNode*>(node)->isFocusable() == true) {
				node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
			}
		}
	}
}

void GUIElementIgnoreEventsController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIElementIgnoreEventsController::tick()
{
}

void GUIElementIgnoreEventsController::onFocusGained()
{
}

void GUIElementIgnoreEventsController::onFocusLost()
{
}

bool GUIElementIgnoreEventsController::hasValue()
{
	return false;
}

const MutableString& GUIElementIgnoreEventsController::getValue()
{
	return value;
}

void GUIElementIgnoreEventsController::setValue(const MutableString& value)
{
}

void GUIElementIgnoreEventsController::onSubTreeChange()
{
}

