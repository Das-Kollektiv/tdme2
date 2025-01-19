#include <agui/gui/elements/GUIInputController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUIInputInternalController.h>
#include <agui/gui/nodes/GUIInputInternalNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using std::string;

using agui::gui::elements::GUIInputController;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUIInputInternalController;
using agui::gui::nodes::GUIInputInternalNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

string GUIInputController::CONDITION_DISABLED = "disabled";
string GUIInputController::CONDITION_ENABLED = "enabled";

GUIInputController::GUIInputController(GUINode* node)
	: GUIElementController(node)
{
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
}

void GUIInputController::onChange() {
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	if (inputNode->getText().getString().empty() == true) {
		if (nodeConditions.has("hint") == false) nodeConditions.add("hint");
	} else {
		if (nodeConditions.has("hint") == true) nodeConditions.remove("hint");
	}
}

bool GUIInputController::isDisabled()
{
	return disabled;
}

void GUIInputController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUIInputController::initialize()
{
	inputNode = required_dynamic_cast<GUIInputInternalNode*>(node->getScreenNode()->getNodeById(node->getId() + "_text-input"));

	//
	GUIElementController::initialize();

	//
	onChange();
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
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
		event->setProcessed(true);
	}
}

void GUIInputController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
}

void GUIInputController::tick()
{
	GUIElementController::tick();
}

void GUIInputController::onFocusGained()
{
	inputNode = required_dynamic_cast<GUIInputInternalNode*>(node->getScreenNode()->getNodeById(node->getId() + "_text-input"));
	inputNode->getController()->onFocusGained();
}

void GUIInputController::onFocusLost()
{
	inputNode = required_dynamic_cast<GUIInputInternalNode*>(node->getScreenNode()->getNodeById(node->getId() + "_text-input"));
	inputNode->getController()->onFocusLost();
}

bool GUIInputController::hasValue()
{
	return true;
}

const MutableString& GUIInputController::getValue()
{
	return inputNode->getText();
}

void GUIInputController::setValue(const MutableString& value)
{
	inputNode->getText().set(value);
	auto inputInternalController = required_dynamic_cast<GUIInputInternalController*>(inputNode->getController());
	inputInternalController->formatText();
	inputInternalController->onTextUpdate();
	onChange();
}

void GUIInputController::onSubTreeChange()
{
}
