// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxMultipleOptionController.java
#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>

#include <java/lang/ClassCastException.h>
#include <java/lang/String.h>
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
using java::lang::ClassCastException;
using java::lang::String;
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

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    if (!t) throw new ::java::lang::ClassCastException();
    return t;
}

GUISelectBoxMultipleOptionController::GUISelectBoxMultipleOptionController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxMultipleOptionController::GUISelectBoxMultipleOptionController(GUINode* node) 
	: GUISelectBoxMultipleOptionController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

String* GUISelectBoxMultipleOptionController::CONDITION_SELECTED;

String* GUISelectBoxMultipleOptionController::CONDITION_UNSELECTED;

String* GUISelectBoxMultipleOptionController::CONDITION_FOCUSSED;

String* GUISelectBoxMultipleOptionController::CONDITION_UNFOCUSSED;

String* GUISelectBoxMultipleOptionController::CONDITION_DISABLED;

String* GUISelectBoxMultipleOptionController::CONDITION_ENABLED;

void GUISelectBoxMultipleOptionController::ctor(GUINode* node)
{
	super::ctor(node);
	this->selected = (java_cast< GUIElementNode* >(node))->isSelected();
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
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (java_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
	nodeConditions->remove(CONDITION_DISABLED);
	nodeConditions->remove(CONDITION_ENABLED);
	nodeConditions->add(disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUISelectBoxMultipleOptionController::unselect()
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto disabled = (java_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
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
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
	this->focussed = true;
	nodeConditions->add(this->focussed == true ? CONDITION_FOCUSSED : CONDITION_UNFOCUSSED);
}

void GUISelectBoxMultipleOptionController::unfocus()
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
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
	auto disabled = (java_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			(java_cast< GUISelectBoxMultipleController* >(selectBoxMultipleNode->getController()))->unfocus();
			toggle();
			focus();
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(selectBoxMultipleNode));
			node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(selectBoxMultipleNode));
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

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxMultipleOptionController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxMultipleOptionController", 54);
    return c;
}

void GUISelectBoxMultipleOptionController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_SELECTED = u"selected"_j;
	CONDITION_UNSELECTED = u"unselected"_j;
	CONDITION_FOCUSSED = u"focussed"_j;
	CONDITION_UNFOCUSSED = u"unfocussed"_j;
	CONDITION_DISABLED = u"disabled"_j;
	CONDITION_ENABLED = u"enabled"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUISelectBoxMultipleOptionController::getClass0()
{
	return class_();
}

