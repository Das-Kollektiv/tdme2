// Generated from /tdme/src/tdme/gui/elements/GUIInputController.java
#include <tdme/gui/elements/GUIInputController.h>

#include <string>

#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUIInputInternalNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>

using std::wstring;

using tdme::gui::elements::GUIInputController;
using java::lang::StringBuilder;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUIInputInternalNode;
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

GUIInputController::GUIInputController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIInputController::GUIInputController(GUINode* node) 
	: GUIInputController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

wstring GUIInputController::CONDITION_DISABLED;

wstring GUIInputController::CONDITION_ENABLED;

void GUIInputController::ctor(GUINode* node)
{
	super::ctor(node);
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUIInputController::isDisabled()
{
	return disabled;
}

void GUIInputController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIInputController::initialize()
{
	textInputNode = java_cast< GUIInputInternalNode* >(node->getScreenNode()->getNodeById(node->getId() + L"_text-input"));
	setDisabled(disabled);
}

void GUIInputController::dispose()
{
}

void GUIInputController::postLayout()
{
}

void GUIInputController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
		event->setProcessed(true);
	}
}

void GUIInputController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIInputController::tick()
{
}

void GUIInputController::onFocusGained()
{
}

void GUIInputController::onFocusLost()
{
}

bool GUIInputController::hasValue()
{
	return true;
}

MutableString* GUIInputController::getValue()
{
	return textInputNode->getText();
}

void GUIInputController::setValue(MutableString* value)
{
	textInputNode->getText()->set(value);
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIInputController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIInputController", 36);
    return c;
}

void GUIInputController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_DISABLED = L"disabled";
	CONDITION_ENABLED = L"enabled";
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIInputController::getClass0()
{
	return class_();
}

