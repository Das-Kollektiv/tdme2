// Generated from /tdme/src/tdme/gui/elements/GUIDropDownOptionController.java
#include <tdme/gui/elements/GUIDropDownOptionController.h>

#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/elements/GUIDropDownController.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/gui/nodes/GUITextNode.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::elements::GUIDropDownOptionController;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::elements::GUIDropDownController;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::gui::nodes::GUITextNode;
using tdme::utils::MutableString;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIDropDownOptionController::GUIDropDownOptionController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIDropDownOptionController::GUIDropDownOptionController(GUINode* node) 
	: GUIDropDownOptionController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

String* GUIDropDownOptionController::CONDITION_SELECTED;

String* GUIDropDownOptionController::CONDITION_UNSELECTED;

void GUIDropDownOptionController::ctor(GUINode* node)
{
	super::ctor(node);
	this->selected = (java_cast< GUIElementNode* >(node))->isSelected();
}

bool GUIDropDownOptionController::isSelected()
{
	return selected;
}

bool GUIDropDownOptionController::isDisabled()
{
	return false;
}

void GUIDropDownOptionController::setDisabled(bool disabled)
{
}

void GUIDropDownOptionController::select()
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	auto dropDownOptionTextNode = java_cast< GUITextNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_unselected"_j)->toString()));
	auto dropDownTextNodeEnabled = java_cast< GUITextNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(dropDownNode->getId())->append(u"_text_enabled"_j)->toString()));
	dropDownTextNodeEnabled->getText()->reset();
	dropDownTextNodeEnabled->getText()->append(dropDownOptionTextNode->getText());
	auto dropDownTextNodeDisabled = java_cast< GUITextNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(dropDownNode->getId())->append(u"_text_disabled"_j)->toString()));
	dropDownTextNodeDisabled->getText()->reset();
	dropDownTextNodeDisabled->getText()->append(dropDownOptionTextNode->getText());
}

void GUIDropDownOptionController::unselect()
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = false;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
}

void GUIDropDownOptionController::initialize()
{
	dropDownNode = node->getParentControllerNode();
	while (true == true) {
		if (dynamic_cast< GUIDropDownController* >(dropDownNode->getController()) != nullptr) {
			break;
		}
		dropDownNode = dropDownNode->getParentControllerNode();
	}
	if (selected == true) {
		select();
	} else {
		unselect();
	}
}

void GUIDropDownOptionController::postLayout()
{
	if (selected == true) {
		node->scrollToNodeX(dropDownNode);
		node->scrollToNodeY(dropDownNode);
	}
}

void GUIDropDownOptionController::dispose()
{
}

void GUIDropDownOptionController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			(java_cast< GUIDropDownController* >(dropDownNode->getController()))->unselect();
			select();
			(java_cast< GUIDropDownController* >(dropDownNode->getController()))->toggleOpenState();
			node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(dropDownNode));
			node->scrollToNodeX(dropDownNode);
			node->scrollToNodeY(dropDownNode);
		}
	}
}

void GUIDropDownOptionController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIDropDownOptionController::tick()
{
}

void GUIDropDownOptionController::onFocusGained()
{
}

void GUIDropDownOptionController::onFocusLost()
{
}

bool GUIDropDownOptionController::hasValue()
{
	return false;
}

MutableString* GUIDropDownOptionController::getValue()
{
	return nullptr;
}

void GUIDropDownOptionController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIDropDownOptionController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIDropDownOptionController", 45);
    return c;
}

void GUIDropDownOptionController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_SELECTED = u"selected"_j;
	CONDITION_UNSELECTED = u"unselected"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIDropDownOptionController::getClass0()
{
	return class_();
}

