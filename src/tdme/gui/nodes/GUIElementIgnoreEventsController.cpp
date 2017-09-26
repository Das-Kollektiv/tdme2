// Generated from /tdme/src/tdme/gui/nodes/GUIElementIgnoreEventsController.java
#include <tdme/gui/nodes/GUIElementIgnoreEventsController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::nodes::GUIElementIgnoreEventsController;
using tdme::gui::GUI;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUIScreenNode;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUIElementIgnoreEventsController::GUIElementIgnoreEventsController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIElementIgnoreEventsController::GUIElementIgnoreEventsController(GUINode* node) 
	: GUIElementIgnoreEventsController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

wstring GUIElementIgnoreEventsController::CONDITION_DISABLED;

wstring GUIElementIgnoreEventsController::CONDITION_ENABLED;

void GUIElementIgnoreEventsController::ctor(GUINode* node)
{
	super::ctor(node);
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUIElementIgnoreEventsController::isDisabled()
{
	return disabled;
}

void GUIElementIgnoreEventsController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIElementIgnoreEventsController::initialize()
{
	setDisabled(disabled);
}

void GUIElementIgnoreEventsController::dispose()
{
}

void GUIElementIgnoreEventsController::postLayout()
{
}

void GUIElementIgnoreEventsController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			if ((java_cast< GUIElementNode* >(node))->isFocusable() == true) {
				node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
			}
		}
	}
}

void GUIElementIgnoreEventsController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUIElementIgnoreEventsController::tick()
{
}

void GUIElementIgnoreEventsController::onFocusGained()
{
}

void GUIElementIgnoreEventsController::onFocusLost()
{
}

bool GUIElementIgnoreEventsController::hasValue()
{
	return false;
}

MutableString* GUIElementIgnoreEventsController::getValue()
{
	return nullptr;
}

void GUIElementIgnoreEventsController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIElementIgnoreEventsController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIElementIgnoreEventsController", 47);
    return c;
}

void GUIElementIgnoreEventsController::clinit()
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

java::lang::Class* GUIElementIgnoreEventsController::getClass0()
{
	return class_();
}

