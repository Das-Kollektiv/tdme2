#include <tdme/gui/elements/GUIInputController.h>

#include <string>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIInputInternalNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>

using std::string;

using tdme::gui::elements::GUIInputController;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIInputInternalNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;

string GUIInputController::CONDITION_DISABLED = "disabled";
string GUIInputController::CONDITION_ENABLED = "enabled";

GUIInputController::GUIInputController(GUINode* node) 
	: GUIElementController(node)
{
	this->disabled = (dynamic_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUIInputController::isDisabled()
{
	return disabled;
}

void GUIInputController::setDisabled(bool disabled)
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIInputController::initialize()
{
	textInputNode = dynamic_cast< GUIInputInternalNode* >(node->getScreenNode()->getNodeById(node->getId() + "_text-input"));

	//
	GUIElementController::initialize();
}

void GUIInputController::dispose()
{
	GUIElementController::dispose();
}

void GUIInputController::postLayout()
{
}

void GUIInputController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(node));
		event->setProcessed(true);
	}
}

void GUIInputController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(node, event);
}

void GUIInputController::tick()
{
	GUIElementController::tick();
}

void GUIInputController::onFocusGained()
{
}

void GUIInputController::onFocusLost()
{
}

bool GUIInputController::hasValue()
{
	return true;
}

const MutableString& GUIInputController::getValue()
{
	return textInputNode->getText();
}

void GUIInputController::setValue(const MutableString& value)
{
	textInputNode->getText().set(value);
}
