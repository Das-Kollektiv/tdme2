#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxMultipleController.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUISelectBoxMultipleOptionController;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxMultipleController;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

wstring GUISelectBoxMultipleOptionController::CONDITION_SELECTED = L"selected";
wstring GUISelectBoxMultipleOptionController::CONDITION_UNSELECTED = L"unselected";
wstring GUISelectBoxMultipleOptionController::CONDITION_FOCUSSED = L"focussed";
wstring GUISelectBoxMultipleOptionController::CONDITION_UNFOCUSSED = L"unfocussed";
wstring GUISelectBoxMultipleOptionController::CONDITION_DISABLED = L"disabled";
wstring GUISelectBoxMultipleOptionController::CONDITION_ENABLED = L"enabled";

GUISelectBoxMultipleOptionController::GUISelectBoxMultipleOptionController(GUINode* node) 
	: GUINodeController(node)
{
	this->selected = (dynamic_cast< GUIElementNode* >(node))->isSelected();
	this->focussed = false;
}

bool GUISelectBoxMultipleOptionController::isDisabled()
{
	return false;
}

void GUISelectBoxMultipleOptionController::setDisabled(bool disabled)
{
}

bool GUISelectBoxMultipleOptionController::isSelected()
{
	return selected;
}

void GUISelectBoxMultipleOptionController::select()
{
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
	nodeConditions->remove(CONDITION_DISABLED);
	nodeConditions->remove(CONDITION_ENABLED);
	nodeConditions->add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxMultipleOptionController::unselect()
{
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
	nodeConditions->remove(CONDITION_DISABLED);
	nodeConditions->remove(CONDITION_ENABLED);
	nodeConditions->add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxMultipleOptionController::toggle()
{
	if (selected == true) {
		unselect();
	} else {
		select();
	}
}

bool GUISelectBoxMultipleOptionController::isFocussed()
{
	return focussed;
}

void GUISelectBoxMultipleOptionController::focus()
{
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
	this->focussed = true;
	nodeConditions->add(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
}

void GUISelectBoxMultipleOptionController::unfocus()
{
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
	this->focussed = false;
	nodeConditions->add(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
}

void GUISelectBoxMultipleOptionController::initialize()
{
	selectBoxMultipleNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()) != nullptr) {
			break;
		}
		selectBoxMultipleNode = selectBoxMultipleNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}
}

void GUISelectBoxMultipleOptionController::dispose()
{
}

void GUISelectBoxMultipleOptionController::postLayout()
{
	if (selected == true) {
		node->scrollToNodeX(selectBoxMultipleNode);
		node->scrollToNodeY(selectBoxMultipleNode);
	}
}

void GUISelectBoxMultipleOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto disabled = (dynamic_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			(dynamic_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->unfocus();
			toggle();
			focus();
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(selectBoxMultipleNode));
			node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(selectBoxMultipleNode));
			node->scrollToNodeX(selectBoxMultipleNode);
			node->scrollToNodeY(selectBoxMultipleNode);
		}
	}
}

void GUISelectBoxMultipleOptionController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUISelectBoxMultipleOptionController::tick()
{
}

void GUISelectBoxMultipleOptionController::onFocusGained()
{
}

void GUISelectBoxMultipleOptionController::onFocusLost()
{
}

bool GUISelectBoxMultipleOptionController::hasValue()
{
	return false;
}

MutableString* GUISelectBoxMultipleOptionController::getValue()
{
	return nullptr;
}

void GUISelectBoxMultipleOptionController::setValue(MutableString* value)
{
}
