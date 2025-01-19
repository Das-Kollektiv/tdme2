#include <agui/gui/elements/GUISelectorHOptionController.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/GUISelectorHController.h>
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

using agui::gui::elements::GUISelectorHOptionController;

using agui::gui::elements::GUISelectorHController;
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

string GUISelectorHOptionController::CONDITION_SELECTED = "selected";
string GUISelectorHOptionController::CONDITION_UNSELECTED = "unselected";

GUISelectorHOptionController::GUISelectorHOptionController(GUINode* node)
	: GUIElementController(node)
{
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
	this->hidden = false;
}

void GUISelectorHOptionController::setDisabled(bool disabled)
{
	GUIElementController::setDisabled(disabled);
	unselect();
}

void GUISelectorHOptionController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUISelectorHOptionController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
}

void GUISelectorHOptionController::initialize()
{
	//
	selectorHNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUISelectorHController*>(selectorHNode->getController()) != nullptr) {
			break;
		}
		selectorHNode = selectorHNode->getParentControllerNode();
	}
	if (selected == true) {
		required_dynamic_cast<GUISelectorHController*>(selectorHNode->getController())->select(required_dynamic_cast<GUIElementNode*>(this->node));
	} else {
		unselect();
	}

	//
	GUIElementController::initialize();
}

void GUISelectorHOptionController::postLayout()
{
}

void GUISelectorHOptionController::dispose()
{
	GUIElementController::dispose();
}

void GUISelectorHOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
}

void GUISelectorHOptionController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
}

void GUISelectorHOptionController::tick()
{
	GUIElementController::tick();
}

void GUISelectorHOptionController::onFocusGained()
{
}

void GUISelectorHOptionController::onFocusLost()
{
}

bool GUISelectorHOptionController::hasValue()
{
	return false;
}

const MutableString& GUISelectorHOptionController::getValue()
{
	return value;
}

void GUISelectorHOptionController::setValue(const MutableString& value)
{
}
