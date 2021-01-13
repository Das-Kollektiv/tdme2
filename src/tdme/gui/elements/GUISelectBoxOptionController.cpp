#include <tdme/gui/elements/GUISelectBoxOptionController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/elements/GUISelectBoxParentOptionController.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::elements::GUISelectBoxParentOptionController;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

string GUISelectBoxOptionController::CONDITION_SELECTED = "selected";
string GUISelectBoxOptionController::CONDITION_UNSELECTED = "unselected";
string GUISelectBoxOptionController::CONDITION_FOCUSSED = "focussed";
string GUISelectBoxOptionController::CONDITION_UNFOCUSSED = "unfocussed";
string GUISelectBoxOptionController::CONDITION_DISABLED = "disabled";
string GUISelectBoxOptionController::CONDITION_ENABLED = "enabled";
string GUISelectBoxOptionController::CONDITION_CHILD = "child";

GUISelectBoxOptionController::GUISelectBoxOptionController(GUINode* node)
	: GUIElementController(node)
{
	this->initialPostLayout = true;
	this->selected = (dynamic_cast< GUIElementNode* >(node))->isSelected();
	this->focussed = false;
}

bool GUISelectBoxOptionController::isDisabled()
{
	return false;
}

void GUISelectBoxOptionController::setDisabled(bool disabled)
{
}

bool GUISelectBoxOptionController::isSelected()
{
	return selected;
}

void GUISelectBoxOptionController::select()
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast<GUISelectBoxController*>(selectBoxMultipleNode->getController()))->isDisabled();
	nodeConditions.remove(CONDITION_DISABLED);
	nodeConditions.remove(CONDITION_ENABLED);
	nodeConditions.add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxOptionController::unselect()
{
	auto& nodeConditions = (dynamic_cast<GUIElementNode*>(node))->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true ? CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast<GUISelectBoxController*>(selectBoxMultipleNode->getController()))->isDisabled();
	nodeConditions.remove(CONDITION_DISABLED);
	nodeConditions.remove(CONDITION_ENABLED);
	nodeConditions.add(disabled == true?CONDITION_DISABLED:CONDITION_ENABLED);
}

void GUISelectBoxOptionController::toggle()
{
	if (selected == true) {
		unselect();
	} else {
		select();
	}
}

bool GUISelectBoxOptionController::isFocussed()
{
	return focussed;
}

void GUISelectBoxOptionController::focus()
{
	auto& nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = true;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

void GUISelectBoxOptionController::unfocus()
{
	auto& nodeConditions = (dynamic_cast<GUIElementNode*>(node))->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = false;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

bool GUISelectBoxOptionController::isCollapsed() {
	auto _node = node->getParentNode();
	while(_node != nullptr && _node != selectBoxMultipleNode) {
		if (_node->isConditionsMet() == false) return true;
		_node = _node->getParentNode();
	}
	return false;
}

void GUISelectBoxOptionController::initialize()
{
	selectBoxMultipleNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUISelectBoxController*>(selectBoxMultipleNode->getController()) != nullptr) {
			break;
		}
		selectBoxMultipleNode = selectBoxMultipleNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}

	{
		auto childIdx = 0;
		GUIElementNode* _parentElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId()));
		while (_parentElementNode != nullptr) {
			if (dynamic_cast<GUISelectBoxParentOptionController*>(_parentElementNode->getController()) != nullptr) {
				childIdx++;
			} else {
				break;
			}
			_parentElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(_parentElementNode->getParentElementNodeId()));
		}
		if (childIdx > 0) {
			auto& nodeConditions = (dynamic_cast<GUIElementNode*>(node))->getActiveConditions();
			nodeConditions.add(CONDITION_CHILD);
		}
	}

	//
	GUIElementController::initialize();
}

void GUISelectBoxOptionController::dispose()
{
	GUIElementController::dispose();
}

void GUISelectBoxOptionController::postLayout()
{
	if (initialPostLayout != true) return;
	if (selected == true) {
		node->scrollToNodeX(selectBoxMultipleNode);
		node->scrollToNodeY(selectBoxMultipleNode);
	}
	initialPostLayout = false;
}

void GUISelectBoxOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = (dynamic_cast<GUISelectBoxController*>(selectBoxMultipleNode->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == MOUSE_BUTTON_LEFT) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			(dynamic_cast<GUISelectBoxController*>(selectBoxMultipleNode->getController()))->unfocus();
			toggle();
			focus();
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast<GUIElementNode*>(selectBoxMultipleNode));
			node->scrollToNodeX(selectBoxMultipleNode);
			node->scrollToNodeY(selectBoxMultipleNode);
			node->getScreenNode()->delegateValueChanged(dynamic_cast<GUIElementNode*>(selectBoxMultipleNode));
		}
	}
}

void GUISelectBoxOptionController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(node, event);
}

void GUISelectBoxOptionController::onFocusGained()
{
}

void GUISelectBoxOptionController::onFocusLost()
{
}

bool GUISelectBoxOptionController::hasValue()
{
	return false;
}

const MutableString& GUISelectBoxOptionController::getValue()
{
	return value;
}

void GUISelectBoxOptionController::setValue(const MutableString& value)
{
}
