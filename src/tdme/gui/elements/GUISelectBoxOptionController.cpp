#include <tdme/gui/elements/GUISelectBoxOptionController.h>

#include <string>

#include <tdme/tdme.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/elements/GUISelectBoxParentOptionController.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementController.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/GUI.h>

using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::elements::GUISelectBoxParentOptionController;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::GUI;

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
	this->selected = required_dynamic_cast<GUIElementNode*>(node)->isSelected();
	this->focussed = false;
}

void GUISelectBoxOptionController::setDisabled(bool disabled)
{
	unselect();
	GUIElementController::setDisabled(disabled);
}

void GUISelectBoxOptionController::select()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions.add(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = required_dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController())->isDisabled();
	nodeConditions.remove(CONDITION_DISABLED);
	nodeConditions.remove(CONDITION_ENABLED);
	nodeConditions.add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxOptionController::unselect()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->selected == true?CONDITION_SELECTED:CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions.add(this->selected == true ? CONDITION_SELECTED:CONDITION_UNSELECTED);
	auto disabled = required_dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController())->isDisabled();
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

void GUISelectBoxOptionController::focus()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = true;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

void GUISelectBoxOptionController::unfocus()
{
	auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
	nodeConditions.remove(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
	this->focussed = false;
	nodeConditions.add(this->focussed == true?CONDITION_FOCUSSED:CONDITION_UNFOCUSSED);
}

bool GUISelectBoxOptionController::isHierarchyExpanded() {
	if (dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId().empty() == false) {
		GUIElementNode* _parentElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId()));
		while (_parentElementNode != nullptr) {
			auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(_parentElementNode->getController());
			if (selectBoxParentOptionController != nullptr) {
				if (selectBoxParentOptionController->isExpanded() == false) return false;
			} else {
				break;
			}
			_parentElementNode =
				_parentElementNode->getParentElementNodeId().empty() == false?
					dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(_parentElementNode->getParentElementNodeId())):
					nullptr;
		}
	}
	return true;
}

void GUISelectBoxOptionController::expandHierarchy() {
	if (dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId().empty() == false) {
		GUIElementNode* _parentElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId()));
		while (_parentElementNode != nullptr) {
			auto selectBoxParentOptionController = dynamic_cast<GUISelectBoxParentOptionController*>(_parentElementNode->getController());
			if (selectBoxParentOptionController != nullptr) {
				if (selectBoxParentOptionController->isExpanded() == false) selectBoxParentOptionController->toggleExpandState();
			} else {
				break;
			}
			_parentElementNode =
				_parentElementNode->getParentElementNodeId().empty() == false?
					dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(_parentElementNode->getParentElementNodeId())):
					nullptr;
		}
	}
}

void GUISelectBoxOptionController::initialize()
{
	selectBoxNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController()) != nullptr) {
			break;
		}
		selectBoxNode = selectBoxNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}

	{
		auto childIdx = 0;
		if (dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId().empty() == false) {
			GUIElementNode* _parentElementNode = dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(dynamic_cast<GUIElementNode*>(node)->getParentElementNodeId()));
			while (_parentElementNode != nullptr) {
				if (dynamic_cast<GUISelectBoxParentOptionController*>(_parentElementNode->getController()) != nullptr) {
					childIdx++;
				} else {
					break;
				}
				_parentElementNode =
					_parentElementNode->getParentElementNodeId().empty() == false?
						dynamic_cast<GUIElementNode*>(node->getScreenNode()->getNodeById(_parentElementNode->getParentElementNodeId())):
						nullptr;
			}
			if (childIdx > 0) {
				auto& nodeConditions = required_dynamic_cast<GUIElementNode*>(node)->getActiveConditions();
				nodeConditions.add(CONDITION_CHILD);
			}
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
		node->scrollToNodeX(selectBoxNode);
		node->scrollToNodeY(selectBoxNode);
	}
	initialPostLayout = false;
}

void GUISelectBoxOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	GUIElementController::handleMouseEvent(node, event);
	auto disabled = required_dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController())->isDisabled();
	auto multipleSelection = required_dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController())->isMultipleSelection();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event)) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent::MOUSEEVENT_PRESSED) {
			auto selectBoxController = required_dynamic_cast<GUISelectBoxController*>(selectBoxNode->getController());
			auto optionElementNode = required_dynamic_cast<GUIElementNode*>(node);
			selectBoxController->unfocus();
			if (multipleSelection == true && selectBoxController->isKeyControlDown() == true) {
				selectBoxController->toggle(optionElementNode);
				selectBoxController->focus(optionElementNode);
			} else {
				selectBoxController->unselect();
				selectBoxController->select(optionElementNode);
				selectBoxController->focus(optionElementNode);
			}
			node->getScreenNode()->getGUI()->setFoccussedNode(required_dynamic_cast<GUIElementNode*>(selectBoxNode));
			node->scrollToNodeX(selectBoxNode);
			node->scrollToNodeY(selectBoxNode);
			node->getScreenNode()->forwardChange(required_dynamic_cast<GUIElementNode*>(selectBoxNode));
			if (event->getButton() == MOUSE_BUTTON_RIGHT) {
				node->getScreenNode()->forwardContextMenuRequest(required_dynamic_cast<GUIElementNode*>(selectBoxNode), event->getXUnscaled(), event->getYUnscaled());
			}
		}
	}
}

void GUISelectBoxOptionController::handleKeyboardEvent(GUIKeyboardEvent* event)
{
	GUIElementController::handleKeyboardEvent(event);
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
