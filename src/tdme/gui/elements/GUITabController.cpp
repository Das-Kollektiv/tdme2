// Generated from /tdme/src/tdme/gui/elements/GUITabController.java
#include <tdme/gui/elements/GUITabController.h>

#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/elements/GUITabsHeaderController.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIColor.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode_Border.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>

using tdme::gui::elements::GUITabController;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::elements::GUITabsController;
using tdme::gui::elements::GUITabsHeaderController;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIColor;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode_Border;
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
    return t;
}

GUITabController::GUITabController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabController::GUITabController(GUINode* node) 
	: GUITabController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

wstring GUITabController::CONDITION_DISABLED;

wstring GUITabController::CONDITION_ENABLED;

wstring GUITabController::CONDITION_SELECTED;

wstring GUITabController::CONDITION_UNSELECTED;

void GUITabController::ctor(GUINode* node)
{
	super::ctor(node);
	this->tabsNode = nullptr;
	this->tabsHeaderNode = nullptr;
	this->selected = false;
	this->unfocussedNodeBorderLeftColor = nullptr;
	this->unfocussedNodeBorderRightColor = nullptr;
	this->unfocussedNodeBorderTopColor = nullptr;
	this->unfocussedNodeBorderBottomColor = nullptr;
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUITabController::isDisabled()
{
	return disabled;
}

void GUITabController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
}

bool GUITabController::isSelected()
{
	return selected;
}

void GUITabController::setSelected(bool selected)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(this->node))->getActiveConditions();
	nodeConditions->remove(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	this->selected = selected;
	nodeConditions->add(this->selected == true ? CONDITION_SELECTED : CONDITION_UNSELECTED);
	if ((java_cast< GUITabsHeaderController* >(tabsHeaderNode->getController()))->hasFocus() == true) {
		if (selected == true) {
			auto focussedBorderColor = node->getScreenNode()->getGUI()->getFoccussedBorderColor();
			auto border = node->getBorder();
			border->topColor = focussedBorderColor;
			border->leftColor = focussedBorderColor;
			border->bottomColor = focussedBorderColor;
			border->rightColor = focussedBorderColor;
		} else {
			auto border = node->getBorder();
			border->topColor = unfocussedNodeBorderTopColor;
			border->leftColor = unfocussedNodeBorderLeftColor;
			border->bottomColor = unfocussedNodeBorderBottomColor;
			border->rightColor = unfocussedNodeBorderRightColor;
		}
	} else {
		auto border = node->getBorder();
		border->topColor = unfocussedNodeBorderTopColor;
		border->leftColor = unfocussedNodeBorderLeftColor;
		border->bottomColor = unfocussedNodeBorderBottomColor;
		border->rightColor = unfocussedNodeBorderRightColor;
	}
}

void GUITabController::initialize()
{
	tabsNode = (java_cast< GUIParentNode* >(node))->getParentControllerNode()->getParentControllerNode();
	tabsHeaderNode = (java_cast< GUIParentNode* >(node))->getParentControllerNode();
	auto border = node->getBorder();
	unfocussedNodeBorderTopColor = border->topColor;
	unfocussedNodeBorderLeftColor = border->leftColor;
	unfocussedNodeBorderBottomColor = border->bottomColor;
	unfocussedNodeBorderRightColor = border->rightColor;
	setSelected(selected);
	setDisabled(disabled);
}

void GUITabController::dispose()
{
}

void GUITabController::postLayout()
{
}

void GUITabController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			auto guiTabsController = java_cast< GUITabsController* >(tabsNode->getController());
			guiTabsController->unselect();
			setSelected(selected == true ? false : true);
			guiTabsController->setTabContentSelected(node->getId());
		}
	}
}

void GUITabController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
}

void GUITabController::tick()
{
}

void GUITabController::onFocusGained()
{
}

void GUITabController::onFocusLost()
{
}

bool GUITabController::hasValue()
{
	return false;
}

MutableString* GUITabController::getValue()
{
	return nullptr;
}

void GUITabController::setValue(MutableString* value)
{
}

void GUITabController::selectTab()
{
	auto guiTabsController = java_cast< GUITabsController* >(tabsNode->getController());
	guiTabsController->unselect();
	setSelected(true);
	guiTabsController->setTabContentSelected(node->getId());
	node->getScreenNode()->getGUI()->invalidateFocussedNode();
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabController", 34);
    return c;
}

void GUITabController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_DISABLED = L"disabled";
	CONDITION_ENABLED = L"enabled";
	CONDITION_SELECTED = L"selected";
	CONDITION_UNSELECTED = L"unselected";
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUITabController::getClass0()
{
	return class_();
}

