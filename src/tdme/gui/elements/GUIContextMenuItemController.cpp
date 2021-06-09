#include <tdme/gui/elements/GUIContextMenuItemController.h>

#include <string>

#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/elements/GUIMenuHeaderItemController.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
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

using tdme::gui::elements::GUIMenuHeaderItemController;
using tdme::gui::elements::GUIContextMenuItemController;
using tdme::gui::events::GUIKeyboardEvent;
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
