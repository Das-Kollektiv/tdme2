// Generated from /tdme/src/tdme/gui/elements/GUITabsHeaderController.java
#include <tdme/gui/elements/GUITabsHeaderController.h>

#include <java/lang/Object.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUITabController.h>
#include <tdme/gui/elements/GUITabsController.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/_ArrayList.h>

using tdme::gui::elements::GUITabsHeaderController;
using java::lang::Object;
using tdme::gui::GUI;
using tdme::gui::elements::GUITabController;
using tdme::gui::elements::GUITabsController;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUITabsHeaderController::GUITabsHeaderController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUITabsHeaderController::GUITabsHeaderController(GUINode* node) 
	: GUITabsHeaderController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUITabsHeaderController::ctor(GUINode* node)
{
	super::ctor(node);
	this->childControllerNodes = new _ArrayList();
	this->tabControllers = new _ArrayList();
	this->hasFocus_ = false;
}

bool GUITabsHeaderController::isDisabled()
{
	return false;
}

void GUITabsHeaderController::setDisabled(bool disabled)
{
}

void GUITabsHeaderController::initialize()
{
	tabsNode = (java_cast< GUIParentNode* >(node))->getParentControllerNode();
}

void GUITabsHeaderController::dispose()
{
}

void GUITabsHeaderController::postLayout()
{
}

bool GUITabsHeaderController::hasFocus()
{
	return hasFocus_;
}

void GUITabsHeaderController::unselect()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabController* >(childController) != nullptr) {
			auto guiTabController = java_cast< GUITabController* >(childController);
			if (static_cast< GUINode* >(guiTabController->getNode()->getParentControllerNode()) != node)
				continue;

			guiTabController->setSelected(false);
		}
	}
}

void GUITabsHeaderController::determineTabControllers()
{
	tabControllers->clear();
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUITabController* >(childController) != nullptr) {
			auto guiTabController = java_cast< GUITabController* >(childController);
			if (static_cast< GUINode* >(guiTabController->getNode()->getParentControllerNode()) != node)
				continue;

			if (guiTabController->isDisabled() == true)
				continue;

			tabControllers->add(guiTabController);
		}
	}
}

int32_t GUITabsHeaderController::getSelectedTabIdx()
{
	auto tabControllerIdx = -1;
	for (auto i = 0; i < tabControllers->size(); i++) {
		auto tabController = java_cast< GUITabController* >(tabControllers->get(i));
		if (tabController->isSelected() == true) {
			tabControllerIdx = i;
			break;
		}
	}
	return tabControllerIdx;
}

void GUITabsHeaderController::selectNext()
{
	determineTabControllers();
	auto tabControllerIdx = getSelectedTabIdx();
	unselect();
	tabControllerIdx = (tabControllerIdx + 1) % tabControllers->size();
	if (tabControllerIdx < 0)
		tabControllerIdx += tabControllers->size();

	java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->setSelected(true);
	auto guiTabsController = java_cast< GUITabsController* >(tabsNode->getController());
	guiTabsController->setTabContentSelected(java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->getNode()->getId());
}

void GUITabsHeaderController::selectPrevious()
{
	determineTabControllers();
	auto tabControllerIdx = getSelectedTabIdx();
	unselect();
	tabControllerIdx = (tabControllerIdx - 1) % tabControllers->size();
	if (tabControllerIdx < 0)
		tabControllerIdx += tabControllers->size();

	java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->setSelected(true);
	auto guiTabsController = java_cast< GUITabsController* >(tabsNode->getController());
	guiTabsController->setTabContentSelected(java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->getNode()->getId());
}

void GUITabsHeaderController::selectCurrent()
{
	determineTabControllers();
	auto tabControllerIdx = getSelectedTabIdx();
	unselect();
	java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->setSelected(true);
	auto guiTabsController = java_cast< GUITabsController* >(tabsNode->getController());
	guiTabsController->setTabContentSelected(java_cast< GUITabController* >(tabControllers->get(tabControllerIdx))->getNode()->getId());
}

void GUITabsHeaderController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
		}
	}
}

void GUITabsHeaderController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_LEFT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					selectPrevious();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_RIGHT: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					selectNext();
				}
			}
			break;
		}

	}
}

void GUITabsHeaderController::tick()
{
}

void GUITabsHeaderController::onFocusGained()
{
	hasFocus_ = true;
	selectCurrent();
}

void GUITabsHeaderController::onFocusLost()
{
	hasFocus_ = false;
	selectCurrent();
}

bool GUITabsHeaderController::hasValue()
{
	return false;
}

MutableString* GUITabsHeaderController::getValue()
{
	return nullptr;
}

void GUITabsHeaderController::setValue(MutableString* value)
{
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUITabsHeaderController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUITabsHeaderController", 41);
    return c;
}

java::lang::Class* GUITabsHeaderController::getClass0()
{
	return class_();
}

