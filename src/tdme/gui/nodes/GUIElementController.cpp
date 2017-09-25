// Generated from /tdme/src/tdme/gui/nodes/GUIElementController.java
#include <tdme/gui/nodes/GUIElementController.h>

#include <tdme/gui/GUI.h>
#include <tdme/gui/events/GUIActionListener_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::nodes::GUIElementController;
using tdme::gui::GUI;
using tdme::gui::events::GUIActionListener_Type;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
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

GUIElementController::GUIElementController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIElementController::GUIElementController(GUINode* node) 
	: GUIElementController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

wstring GUIElementController::CONDITION_DISABLED;

wstring GUIElementController::CONDITION_ENABLED;

void GUIElementController::ctor(GUINode* node)
{
	super::ctor(node);
	this->isActionPerforming = false;
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUIElementController::isDisabled()
{
	return disabled;
}

void GUIElementController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

void GUIElementController::initialize()
{
	setDisabled(disabled);
}

void GUIElementController::dispose()
{
}

void GUIElementController::postLayout()
{
}

void GUIElementController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			isActionPerforming = true;
			if ((java_cast< GUIElementNode* >(node))->isFocusable() == true) {
				node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
			}
		} else if (event->getType() == GUIMouseEvent_Type::MOUSE_DRAGGED) {
			isActionPerforming = true;
		} else if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			isActionPerforming = false;
			node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, java_cast< GUIElementNode* >(node));
		}
	} else {
		isActionPerforming = false;
	}
}

void GUIElementController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMED, java_cast< GUIElementNode* >(node));
				}
			}
			break;
		default: {
				break;
			}
		}

	}
}

void GUIElementController::tick()
{
	if (isActionPerforming == true) {
		if (disabled == true) {
			isActionPerforming = false;
			return;
		}
		node->getScreenNode()->delegateActionPerformed(GUIActionListener_Type::PERFORMING, java_cast< GUIElementNode* >(node));
	}
}

void GUIElementController::onFocusGained()
{
}

void GUIElementController::onFocusLost()
{
}

bool GUIElementController::hasValue()
{
	return false;
}

MutableString* GUIElementController::getValue()
{
	return nullptr;
}

void GUIElementController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIElementController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.nodes.GUIElementController", 35);
    return c;
}

void GUIElementController::clinit()
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

java::lang::Class* GUIElementController::getClass0()
{
	return class_();
}

