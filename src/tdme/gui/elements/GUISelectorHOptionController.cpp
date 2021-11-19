#include <tdme/gui/elements/GUISelectorHOptionController.h>

#include <string>

#include <tdme/gui/elements/GUISelectorHController.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/gui/GUI.h>
#include <tdme/utilities/MutableString.h>
#include <tdme/utilities/StringTools.h>

using std::string;

using tdme::gui::elements::GUISelectorHOptionController;

using tdme::gui::elements::GUISelectorHController;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::gui::GUI;
using tdme::utilities::MutableString;
using tdme::utilities::StringTools;

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
