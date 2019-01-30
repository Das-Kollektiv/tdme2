#include <tdme/gui/elements/GUICheckboxController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/Console.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::elements::GUICheckboxController;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIElementController;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::Console;
using tdme::utils::MutableString;

string GUICheckboxController::CONDITION_CHECKED = "checked";
string GUICheckboxController::CONDITION_UNCHECKED = "unchecked";
string GUICheckboxController::CONDITION_DISABLED = "disabled";
string GUICheckboxController::CONDITION_ENABLED = "enabled";

GUICheckboxController::GUICheckboxController(GUINode* node)
	: GUIElementController(node)
{
	this->checked = (dynamic_cast< GUIElementNode* >(node))->isSelected();
	this->disabled = (dynamic_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUICheckboxController::isChecked()
{
	return checked;
}

void GUICheckboxController::setChecked(bool checked)
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->checked == true ? CONDITION_CHECKED : CONDITION_UNCHECKED);
	this->checked = checked;
	nodeConditions.add(this->checked == true ? CONDITION_CHECKED : CONDITION_UNCHECKED);
}

bool GUICheckboxController::isDisabled()
{
	return disabled;
}

void GUICheckboxController::setDisabled(bool disabled)
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions.add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUICheckboxController::initialize()
{
	//
	setChecked(checked);

	//
	GUIElementController::initialize();
}

void GUICheckboxController::dispose()
{
	GUIElementController::dispose();
}

void GUICheckboxController::postLayout()
{
}

void GUICheckboxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSEEVENT_RELEASED) {
			setChecked(checked == true ? false : true);
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(node));
			node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(node));
		}
	}
}

void GUICheckboxController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(node, event);
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEYBOARDEVENT_KEY_PRESSED) {
					setChecked(checked == true ? false : true);
					node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(node));
				}
			}
			break;
		default: {
				break;
			}
		}

	}
}

void GUICheckboxController::tick()
{
	GUIElementController::tick();
}

void GUICheckboxController::onFocusGained()
{
}

void GUICheckboxController::onFocusLost()
{
}

bool GUICheckboxController::hasValue()
{
	return true;
}

const MutableString& GUICheckboxController::getValue()
{
	value.reset();
	if (checked == true) {
		value.append((dynamic_cast< GUIElementNode* >(node))->getValue());
	}
	return value;
}

void GUICheckboxController::setValue(const MutableString& value)
{
	setChecked(value.equals((dynamic_cast< GUIElementNode* >(node))->getValue()));
}
