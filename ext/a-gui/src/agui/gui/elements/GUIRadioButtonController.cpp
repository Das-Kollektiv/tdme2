#include <agui/gui/elements/GUIRadioButtonController.h>

#include <string>
#include <unordered_map>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/events/GUIKeyboardEvent.h>
#include <agui/gui/events/GUIMouseEvent.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/gui/nodes/GUIElementNode.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::unordered_map;
using std::vector;

using agui::gui::elements::GUIRadioButtonController;
using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUIElementNode;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;
using agui::utilities::MutableString;

string GUIRadioButtonController::CONDITION_SELECTED = "selected";
string GUIRadioButtonController::CONDITION_UNSELECTED = "unselected";
string GUIRadioButtonController::CONDITION_DISABLED = "disabled";
string GUIRadioButtonController::CONDITION_ENABLED = "enabled";

unordered_map<string, vector<string>> GUIRadioButtonController::radioButtonGroupNodesByName;

GUIRadioButtonController::GUIRadioButtonController(GUINode* node)
	: GUIElementController(node)
{
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
	this->disabled = required_dynamic_cast<GUIElementNode*>(node)->isDisabled();
	this->deselectable = required_dynamic_cast<GUIElementNode*>(node)->hasOption("deselectable");
	radioButtonGroupNodesByName[
		node->getScreenNode()->getId() +
		"_radiobuttongroup_" +
		required_dynamic_cast<GUIElementNode*>(node)->getName()
	].push_back(node->getId());
}

bool GUIRadioButtonController::isSelected()
{
	return selected;
}

void GUIRadioButtonController::select()
{
	auto radioButtonGroupNodesIt = radioButtonGroupNodesByName.find(
		this->node->getScreenNode()->getId() +
		"_radiobuttongroup_" +
		required_dynamic_cast<GUIElementNode*>(this->node)->getName()
	);
	//
	auto wasSelected = selected;
	// deselect radio buttons of same group, determined by element name
	if (radioButtonGroupNodesIt != radioButtonGroupNodesByName.end()) {
		for (auto i = 0; i < radioButtonGroupNodesIt->second.size(); i++) {
			auto radioButtonNode = required_dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(radioButtonGroupNodesIt->second[i]));
			auto& nodeConditions = radioButtonNode->getActiveConditions();
			auto nodeController = required_dynamic_cast<GUIRadioButtonController*>(radioButtonNode->getController());
			nodeConditions.remove(nodeController->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
			nodeController->selected = false;
			nodeConditions.add(nodeController->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
		}
	}
	//
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	selected = wasSelected == true?(deselectable == true?false:true):true;
	nodeConditions.add(selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

bool GUIRadioButtonController::isDisabled()
{
	return disabled;
}

void GUIRadioButtonController::setDisabled(bool disabled)
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUIRadioButtonController::initialize()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);

	//
	GUIElementController::initialize();
}

void GUIRadioButtonController::dispose()
{
	GUIElementController::dispose();
	radioButtonGroupNodesByName.erase(
		this->node->getScreenNode()->getId() +
		"_radiobuttongroup_" +
		this->node->getId()
	);
}

void GUIRadioButtonController::postLayout()
{
}

void GUIRadioButtonController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_RELEASED) {
			select();
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(node));
			node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
		}
	}
}

void GUIRadioButtonController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
	if (disabled == false) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent::KEYBOARDEVENT_KEY_PRESSED) {
					select();
					node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(node));
				}
			}
			break;
		default: {
				break;
			}
		}

	}
}

void GUIRadioButtonController::tick()
{
	GUIElementController::tick();
}

void GUIRadioButtonController::onFocusGained()
{
}

void GUIRadioButtonController::onFocusLost()
{
}

bool GUIRadioButtonController::hasValue()
{
	return true;
}

const MutableString& GUIRadioButtonController::getValue()
{
	value.reset();
	if (selected == true) {
		value.append(required_dynamic_cast<GUIElementNode*>(node)->getValue());
	}
	return value;
}

void GUIRadioButtonController::setValue(const MutableString& value)
{
	if (value.equals(required_dynamic_cast<GUIElementNode*>(node)->getValue()) == true) {
		select();
	}
}

