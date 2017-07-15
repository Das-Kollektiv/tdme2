// Generated from /tdme/src/tdme/gui/elements/GUICheckboxController.java
#include <tdme/gui/elements/GUICheckboxController.h>

#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::elements::GUICheckboxController;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUICheckboxController::GUICheckboxController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUICheckboxController::GUICheckboxController(GUINode* node) 
	: GUICheckboxController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

String* GUICheckboxController::CONDITION_CHECKED;

String* GUICheckboxController::CONDITION_UNCHECKED;

String* GUICheckboxController::CONDITION_DISABLED;

String* GUICheckboxController::CONDITION_ENABLED;

void GUICheckboxController::ctor(GUINode* node)
{
	super::ctor(node);
	this->checked = (java_cast< GUIElementNode* >(node))->isSelected();
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
	this->value = new MutableString();
}

bool GUICheckboxController::isChecked()
{
	return checked;
}

void GUICheckboxController::setChecked(bool checked)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->checked == true ? CONDITION_CHECKED : CONDITION_UNCHECKED);
	this->checked = checked;
	nodeConditions->add(this->checked == true ? CONDITION_CHECKED : CONDITION_UNCHECKED);
}

bool GUICheckboxController::isDisabled()
{
	return disabled;
}

void GUICheckboxController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUICheckboxController::initialize()
{
	setChecked(checked);
	setDisabled(disabled);
}

void GUICheckboxController::dispose()
{
}

void GUICheckboxController::postLayout()
{
}

void GUICheckboxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			setChecked(checked == true ? false : true);
			node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
		}
	}
}

void GUICheckboxController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					setChecked(checked == true ? false : true);
					node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
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

MutableString* GUICheckboxController::getValue()
{
	value->reset();
	if (checked == true) {
		value->append((java_cast< GUIElementNode* >(node))->getValue());
	}
	return value;
}

void GUICheckboxController::setValue(MutableString* value)
{
	setChecked(value->equals((java_cast< GUIElementNode* >(node))->getValue()));
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUICheckboxController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUICheckboxController", 39);
    return c;
}

void GUICheckboxController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_CHECKED = u"checked"_j;
	CONDITION_UNCHECKED = u"unchecked"_j;
	CONDITION_DISABLED = u"disabled"_j;
	CONDITION_ENABLED = u"enabled"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUICheckboxController::getClass0()
{
	return class_();
}

