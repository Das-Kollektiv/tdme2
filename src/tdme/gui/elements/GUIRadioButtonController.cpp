// Generated from /tdme/src/tdme/gui/elements/GUIRadioButtonController.java
#include <tdme/gui/elements/GUIRadioButtonController.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>
#include <tdme/utils/_ArrayList.h>
#include <tdme/utils/_HashMap.h>

using tdme::gui::elements::GUIRadioButtonController;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUI;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;
using tdme::utils::_ArrayList;
using tdme::utils::_HashMap;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIRadioButtonController::GUIRadioButtonController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIRadioButtonController::GUIRadioButtonController(GUINode* node) 
	: GUIRadioButtonController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIRadioButtonController::init()
{
	value = new MutableString();
}

String* GUIRadioButtonController::CONDITION_SELECTED;

String* GUIRadioButtonController::CONDITION_UNSELECTED;

String* GUIRadioButtonController::CONDITION_DISABLED;

String* GUIRadioButtonController::CONDITION_ENABLED;

_HashMap* GUIRadioButtonController::radioButtonGroupNodesByName;

void GUIRadioButtonController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->selected = (java_cast< GUIElementNode* >(node))->isSelected();
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
	auto radioButtonGroupNodes = java_cast< _ArrayList* >(radioButtonGroupNodesByName->get(::java::lang::StringBuilder().append(this->node->getScreenNode()->getId())->append(u"_radiobuttongroup_"_j)
		->append((java_cast< GUIElementNode* >(this->node))->getName())->toString()));
	if (radioButtonGroupNodes == nullptr) {
		radioButtonGroupNodes = new _ArrayList();
		radioButtonGroupNodesByName->put(::java::lang::StringBuilder().append(node->getScreenNode()->getId())->append(u"_radiobuttongroup_"_j)
			->append((java_cast< GUIElementNode* >(node))->getName())->toString(), radioButtonGroupNodes);
	}
	radioButtonGroupNodes->add(java_cast< GUIElementNode* >(node));
}

bool GUIRadioButtonController::isSelected()
{
	return selected;
}

void GUIRadioButtonController::select()
{
	auto radioButtonGroupNodes = java_cast< _ArrayList* >(radioButtonGroupNodesByName->get(::java::lang::StringBuilder().append(this->node->getScreenNode()->getId())->append(u"_radiobuttongroup_"_j)
		->append((java_cast< GUIElementNode* >(this->node))->getName())->toString()));
	if (radioButtonGroupNodes != nullptr) {
		for (auto i = 0; i < radioButtonGroupNodes->size(); i++) {
			auto radioButtonNode = java_cast< GUIElementNode* >(radioButtonGroupNodes->get(i));
			auto nodeConditions = radioButtonNode->getActiveConditions();
			auto nodeController = java_cast< GUIRadioButtonController* >(radioButtonNode->getController());
			nodeConditions->remove(nodeController->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
			nodeController->selected = false;
			nodeConditions->add(nodeController->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
		}
	}
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = true;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
}

bool GUIRadioButtonController::isDisabled()
{
	return disabled;
}

void GUIRadioButtonController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIRadioButtonController::initialize()
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	setDisabled(disabled);
}

void GUIRadioButtonController::dispose()
{
	radioButtonGroupNodesByName->remove(::java::lang::StringBuilder().append(this->node->getScreenNode()->getId())->append(u"_radiobuttongroup_"_j)
		->append((java_cast< GUIElementNode* >(this->node))->getName())->toString());
}

void GUIRadioButtonController::postLayout()
{
}

void GUIRadioButtonController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			select();
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
			node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
		}
	}
}

void GUIRadioButtonController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					select();
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

void GUIRadioButtonController::tick()
{
}

void GUIRadioButtonController::onFocusGained()
{
}

void GUIRadioButtonController::onFocusLost()
{
}

bool GUIRadioButtonController::hasValue()
{
	return true;
}

MutableString* GUIRadioButtonController::getValue()
{
	value->reset();
	if (selected == true) {
		value->append((java_cast< GUIElementNode* >(node))->getValue());
	}
	return value;
}

void GUIRadioButtonController::setValue(MutableString* value)
{
	if (value->equals((java_cast< GUIElementNode* >(node))->getValue()) == true) {
		select();
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIRadioButtonController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIRadioButtonController", 42);
    return c;
}

void GUIRadioButtonController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_SELECTED = u"selected"_j;
	CONDITION_UNSELECTED = u"unselected"_j;
	CONDITION_DISABLED = u"disabled"_j;
	CONDITION_ENABLED = u"enabled"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
	static bool in_cl_init = false;
	struct clinit_ {
		clinit_() {
			in_cl_init = true;
		radioButtonGroupNodesByName = new _HashMap();
		}
	};

	if (!in_cl_init) {
		static clinit_ clinit_instance;
	}
}

java::lang::Class* GUIRadioButtonController::getClass0()
{
	return class_();
}

