#include <tdme/gui/elements/GUISelectBoxOptionController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxController.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxController;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;

GUISelectBoxOptionController::GUISelectBoxOptionController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxOptionController::GUISelectBoxOptionController(GUINode* node) 
	: GUISelectBoxOptionController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

wstring GUISelectBoxOptionController::CONDITION_SELECTED;

wstring GUISelectBoxOptionController::CONDITION_UNSELECTED;

wstring GUISelectBoxOptionController::CONDITION_DISABLED;

wstring GUISelectBoxOptionController::CONDITION_ENABLED;

void GUISelectBoxOptionController::ctor(GUINode* node)
{
	super::ctor(node);
	this->selected = (dynamic_cast< GUIElementNode* >(node))->isSelected();
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
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast< GUISelectBoxController* >(selectBoxNode->getController()))->isDisabled();
	nodeConditions->remove(CONDITION_DISABLED);
	nodeConditions->remove(CONDITION_ENABLED);
	nodeConditions->add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxOptionController::unselect()
{
	auto nodeConditions = (dynamic_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (dynamic_cast< GUISelectBoxController* >(selectBoxNode->getController()))->isDisabled();
	nodeConditions->remove(CONDITION_DISABLED);
	nodeConditions->remove(CONDITION_ENABLED);
	nodeConditions->add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxOptionController::initialize()
{
	selectBoxNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast< GUISelectBoxController* >(selectBoxNode->getController()) != nullptr) {
			break;
		}
		selectBoxNode = selectBoxNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}
}

void GUISelectBoxOptionController::dispose()
{
}

void GUISelectBoxOptionController::postLayout()
{
	if (selected == true) {
		node->scrollToNodeX(selectBoxNode);
		node->scrollToNodeY(selectBoxNode);
	}
}

void GUISelectBoxOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto disabled = (dynamic_cast< GUISelectBoxController* >(selectBoxNode->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			(dynamic_cast< GUISelectBoxController* >(selectBoxNode->getController()))->unselect();
			select();
			node->getScreenNode()->getGUI()->setFoccussedNode(dynamic_cast< GUIElementNode* >(selectBoxNode));
			node->getScreenNode()->delegateValueChanged(dynamic_cast< GUIElementNode* >(selectBoxNode));
			node->scrollToNodeX(selectBoxNode);
			node->scrollToNodeY(selectBoxNode);
		}
	}
}

void GUISelectBoxOptionController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUISelectBoxOptionController::tick()
{
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

MutableString* GUISelectBoxOptionController::getValue()
{
	return nullptr;
}

void GUISelectBoxOptionController::setValue(MutableString* value)
{
}

void GUISelectBoxOptionController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_SELECTED = L"selected";
	CONDITION_UNSELECTED = L"unselected";
	CONDITION_DISABLED = L"disabled";
	CONDITION_ENABLED = L"enabled";
	}
};

	static string_init_ string_init_instance;
}

