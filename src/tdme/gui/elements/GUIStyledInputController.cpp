#include <tdme/gui/elements/GUIStyledInputController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUIStyledTextNode.h>
#include <tdme/gui/nodes/GUIStyledTextNodeController.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/Console.h>
#include <tdme/utilities/MutableString.h>

using tdme::gui::elements::GUIStyledInputController;

using std::string;

using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUIStyledTextNode;
using tdme::gui::nodes::GUIStyledTextNodeController;
using tdme::gui::GUI;
using tdme::utilities::Console;
using tdme::utilities::MutableString;

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
