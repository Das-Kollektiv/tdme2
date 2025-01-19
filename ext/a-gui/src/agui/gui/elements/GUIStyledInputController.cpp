#include <agui/gui/elements/GUIStyledInputController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeController.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/nodes/GUIStyledTextNode.h>
#include <agui/gui/nodes/GUIStyledTextNodeController.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/Console.h>
#include <agui/utilities/MutableString.h>

using agui::gui::elements::GUIStyledInputController;

using std::string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeController;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::nodes::GUIStyledTextNode;
using agui::gui::nodes::GUIStyledTextNodeController;
using agui::gui::GUI;
using agui::utilities::Console;
using agui::utilities::MutableString;

GUIStyledInputController::GUIStyledInputController(GUINode* node)
	: GUINodeController(node)
{
}

bool GUIStyledInputController::isDisabled()
{
	return false;
}

void GUIStyledInputController::setDisabled(bool disabled)
{
	// no op
}

void GUIStyledInputController::initialize()
{
	styledTextNodeController = required_dynamic_cast<GUIStyledTextNodeController*>(node->getScreenNode()->getInnerNodeById(node->getId())->getController());
}

void GUIStyledInputController::dispose()
{
}

void GUIStyledInputController::postLayout()
{
}

void GUIStyledInputController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if ((node == this->node || node == styledTextNodeController->getNode()) &&
		node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(this->node));
		}
	}
}

void GUIStyledInputController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	styledTextNodeController->handleKeyboardEvent(event);
}

void GUIStyledInputController::tick()
{
}

void GUIStyledInputController::onFocusGained()
{
	GUI::setDisableTabFocusControl(true);
	required_dynamic_cast<GUIStyledTextNode*>(styledTextNodeController->getNode())->setEditMode(true);
}

void GUIStyledInputController::onFocusLost()
{
	required_dynamic_cast<GUIStyledTextNode*>(styledTextNodeController->getNode())->setEditMode(false);
	GUI::setDisableTabFocusControl(false);
}

bool GUIStyledInputController::hasValue()
{
	return true;
}

const MutableString& GUIStyledInputController::getValue()
{
	return styledTextNodeController->getValue();
}

void GUIStyledInputController::setValue(const MutableString& value)
{
	styledTextNodeController->setValue(value);
}

void GUIStyledInputController::onSubTreeChange() {
}
