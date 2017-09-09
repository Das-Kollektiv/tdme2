// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxController.java
#include <tdme/gui/elements/GUISelectBoxController.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxOptionController.h>
#include <tdme/gui/events/GUIKeyboardEvent_Type.h>
#include <tdme/gui/events/GUIKeyboardEvent.h>
#include <tdme/gui/events/GUIMouseEvent_Type.h>
#include <tdme/gui/events/GUIMouseEvent.h>
#include <tdme/gui/nodes/GUIElementNode.h>
#include <tdme/gui/nodes/GUINode.h>
#include <tdme/gui/nodes/GUINodeConditions.h>
#include <tdme/gui/nodes/GUINodeController.h>
#include <tdme/gui/nodes/GUIParentNode.h>
#include <tdme/gui/nodes/GUIScreenNode.h>
#include <tdme/utils/MutableString.h>

using tdme::gui::elements::GUISelectBoxController;
using java::lang::Object;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxOptionController;
using tdme::gui::events::GUIKeyboardEvent_Type;
using tdme::gui::events::GUIKeyboardEvent;
using tdme::gui::events::GUIMouseEvent_Type;
using tdme::gui::events::GUIMouseEvent;
using tdme::gui::nodes::GUIElementNode;
using tdme::gui::nodes::GUINode;
using tdme::gui::nodes::GUINodeConditions;
using tdme::gui::nodes::GUINodeController;
using tdme::gui::nodes::GUIParentNode;
using tdme::gui::nodes::GUIScreenNode;
using tdme::utils::MutableString;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUISelectBoxController::GUISelectBoxController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxController::GUISelectBoxController(GUINode* node) 
	: GUISelectBoxController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUISelectBoxController::init()
{
	value = new MutableString();
}

wstring GUISelectBoxController::CONDITION_DISABLED;

wstring GUISelectBoxController::CONDITION_ENABLED;

void GUISelectBoxController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUISelectBoxController::isDisabled()
{
	return disabled;
}

void GUISelectBoxController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	selectCurrent();
}

void GUISelectBoxController::initialize()
{
}

void GUISelectBoxController::dispose()
{
}

void GUISelectBoxController::postLayout()
{
}

void GUISelectBoxController::unselect()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes.at(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxOptionController* >(childController) != nullptr) {
			(java_cast< GUISelectBoxOptionController* >(childController))->unselect();
		}
	}
}

void GUISelectBoxController::determineSelectBoxOptionControllers()
{
	selectBoxOptionControllers.clear();
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(&childControllerNodes);
	for (auto i = 0; i < childControllerNodes.size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes.at(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxOptionController* >(childController) != nullptr) {
			selectBoxOptionControllers.push_back(java_cast< GUISelectBoxOptionController* >(childController));
		}
	}
}

int32_t GUISelectBoxController::getSelectedOptionIdx()
{
	auto selectBoxOptionControllerIdx = -1;
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers.at(i);
		if (selectBoxOptionController->isSelected() == true) {
			selectBoxOptionControllerIdx = i;
			break;
		}
	}
	return selectBoxOptionControllerIdx;
}

void GUISelectBoxController::selectCurrent()
{
	setValue(getValue());
}

void GUISelectBoxController::selectNext()
{
	determineSelectBoxOptionControllers();
	auto selectBoxOptionControllerIdx = getSelectedOptionIdx();
	unselect();
	if (selectBoxOptionControllers.size() == 0)
		return;

	selectBoxOptionControllerIdx = (selectBoxOptionControllerIdx + 1) % selectBoxOptionControllers.size();
	if (selectBoxOptionControllerIdx < 0)
		selectBoxOptionControllerIdx += selectBoxOptionControllers.size();

	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->select();
	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->getNode()->scrollToNodeX(java_cast< GUIParentNode* >(node));
	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->getNode()->scrollToNodeY(java_cast< GUIParentNode* >(node));
}

void GUISelectBoxController::selectPrevious()
{
	determineSelectBoxOptionControllers();
	auto selectBoxOptionControllerIdx = getSelectedOptionIdx();
	unselect();
	if (selectBoxOptionControllers.size() == 0)
		return;

	selectBoxOptionControllerIdx = (selectBoxOptionControllerIdx - 1) % selectBoxOptionControllers.size();
	if (selectBoxOptionControllerIdx < 0)
		selectBoxOptionControllerIdx += selectBoxOptionControllers.size();

	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->select();
	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->getNode()->scrollToNodeX(java_cast< GUIParentNode* >(node));
	java_cast< GUISelectBoxOptionController* >(selectBoxOptionControllers.at(selectBoxOptionControllerIdx))->getNode()->scrollToNodeY(java_cast< GUIParentNode* >(node));
}

void GUISelectBoxController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto disabled = (java_cast< GUISelectBoxController* >(this->node->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
		}
	}
}

void GUISelectBoxController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					selectPrevious();
					node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					selectNext();
					node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
				}
			}
			break;
		}

	}
}

void GUISelectBoxController::tick()
{
}

void GUISelectBoxController::onFocusGained()
{
}

void GUISelectBoxController::onFocusLost()
{
}

bool GUISelectBoxController::hasValue()
{
	return true;
}

MutableString* GUISelectBoxController::getValue()
{
	value->reset();
	determineSelectBoxOptionControllers();
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers.at(i);
		if (selectBoxOptionController->isSelected() == true) {
			value->append((java_cast< GUIElementNode* >(selectBoxOptionController->getNode()))->getValue());
		}
	}
	return value;
}

void GUISelectBoxController::setValue(MutableString* value)
{
	determineSelectBoxOptionControllers();
	unselect();
	for (auto i = 0; i < selectBoxOptionControllers.size(); i++) {
		auto selectBoxOptionController = selectBoxOptionControllers.at(i);
		auto selectBoxOptionNode = java_cast< GUIElementNode* >(selectBoxOptionController->getNode());
		if (value->equals(selectBoxOptionNode->getValue()) == true) {
			selectBoxOptionController->select();
			selectBoxOptionNode->scrollToNodeX(java_cast< GUIParentNode* >(node));
			selectBoxOptionNode->scrollToNodeY(java_cast< GUIParentNode* >(node));
			break;
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxController", 40);
    return c;
}

void GUISelectBoxController::clinit()
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

java::lang::Class* GUISelectBoxController::getClass0()
{
	return class_();
}

