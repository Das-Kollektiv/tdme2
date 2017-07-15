// Generated from /tdme/src/tdme/gui/elements/GUISelectBoxMultipleController.java
#include <tdme/gui/elements/GUISelectBoxMultipleController.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUISelectBoxMultipleOptionController.h>
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
#include <tdme/utils/_ArrayList.h>

using tdme::gui::elements::GUISelectBoxMultipleController;
using java::lang::Object;
using java::lang::String;
using tdme::gui::GUI;
using tdme::gui::elements::GUISelectBoxMultipleOptionController;
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
using tdme::utils::_ArrayList;

template<typename T, typename U>
static T java_cast(U* u)
{
    if (!u) return static_cast<T>(nullptr);
    auto t = dynamic_cast<T>(u);
    return t;
}

GUISelectBoxMultipleController::GUISelectBoxMultipleController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUISelectBoxMultipleController::GUISelectBoxMultipleController(GUINode* node) 
	: GUISelectBoxMultipleController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUISelectBoxMultipleController::init()
{
	childControllerNodes = new _ArrayList();
	selectBoxMultipleOptionControllers = new _ArrayList();
	value = new MutableString();
	searchValue = new MutableString();
}

String* GUISelectBoxMultipleController::CONDITION_DISABLED;

String* GUISelectBoxMultipleController::CONDITION_ENABLED;

constexpr char16_t GUISelectBoxMultipleController::VALUE_DELIMITER;

void GUISelectBoxMultipleController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUISelectBoxMultipleController::isDisabled()
{
	return disabled;
}

void GUISelectBoxMultipleController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	selectCurrent();
}

void GUISelectBoxMultipleController::initialize()
{
	if (getFocussedOptionIdx() == -1) {
		auto value = getValue();
		setValue(value);
	}
}

void GUISelectBoxMultipleController::dispose()
{
}

void GUISelectBoxMultipleController::postLayout()
{
}

void GUISelectBoxMultipleController::unselect()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxMultipleOptionController* >(childController) != nullptr) {
			(java_cast< GUISelectBoxMultipleOptionController* >(childController))->unselect();
		}
	}
}

void GUISelectBoxMultipleController::unfocus()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxMultipleOptionController* >(childController) != nullptr) {
			(java_cast< GUISelectBoxMultipleOptionController* >(childController))->unfocus();
		}
	}
}

void GUISelectBoxMultipleController::determineSelectBoxMultipleOptionControllers()
{
	selectBoxMultipleOptionControllers->clear();
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUISelectBoxMultipleOptionController* >(childController) != nullptr) {
			selectBoxMultipleOptionControllers->add(java_cast< GUISelectBoxMultipleOptionController* >(childController));
		}
	}
}

int32_t GUISelectBoxMultipleController::getFocussedOptionIdx()
{
	auto selectBoxOptionControllerIdx = -1;
	for (auto i = 0; i < selectBoxMultipleOptionControllers->size(); i++) {
		auto selectBoxOptionController = java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(i));
		if (selectBoxOptionController->isFocussed() == true) {
			selectBoxOptionControllerIdx = i;
			break;
		}
	}
	return selectBoxOptionControllerIdx;
}

void GUISelectBoxMultipleController::selectCurrent()
{
	setValue(getValue());
}

void GUISelectBoxMultipleController::focusNext()
{
	determineSelectBoxMultipleOptionControllers();
	auto selectBoxMultipleOptionControllerIdx = getFocussedOptionIdx();
	unfocus();
	if (selectBoxMultipleOptionControllers->size() == 0)
		return;

	selectBoxMultipleOptionControllerIdx = (selectBoxMultipleOptionControllerIdx + 1) % selectBoxMultipleOptionControllers->size();
	if (selectBoxMultipleOptionControllerIdx < 0)
		selectBoxMultipleOptionControllerIdx += selectBoxMultipleOptionControllers->size();

	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->focus();
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeX(java_cast< GUIParentNode* >(node));
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeY(java_cast< GUIParentNode* >(node));
}

void GUISelectBoxMultipleController::focusPrevious()
{
	determineSelectBoxMultipleOptionControllers();
	auto selectBoxMultipleOptionControllerIdx = getFocussedOptionIdx();
	unfocus();
	if (selectBoxMultipleOptionControllers->size() == 0)
		return;

	selectBoxMultipleOptionControllerIdx = (selectBoxMultipleOptionControllerIdx - 1) % selectBoxMultipleOptionControllers->size();
	if (selectBoxMultipleOptionControllerIdx < 0)
		selectBoxMultipleOptionControllerIdx += selectBoxMultipleOptionControllers->size();

	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->focus();
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeX(java_cast< GUIParentNode* >(node));
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeY(java_cast< GUIParentNode* >(node));
}

void GUISelectBoxMultipleController::toggle()
{
	determineSelectBoxMultipleOptionControllers();
	auto selectBoxMultipleOptionControllerIdx = getFocussedOptionIdx();
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->toggle();
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeX(java_cast< GUIParentNode* >(node));
	java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(selectBoxMultipleOptionControllerIdx))->getNode()->scrollToNodeY(java_cast< GUIParentNode* >(node));
}

void GUISelectBoxMultipleController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	auto disabled = (java_cast< GUISelectBoxMultipleController* >(this->node->getController()))->isDisabled();
	if (disabled == false && node == this->node && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_PRESSED) {
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(node));
		}
	}
}

void GUISelectBoxMultipleController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					focusPrevious();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					focusNext();
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					toggle();
				}
			}
			break;
		}

	}
}

void GUISelectBoxMultipleController::tick()
{
}

void GUISelectBoxMultipleController::onFocusGained()
{
}

void GUISelectBoxMultipleController::onFocusLost()
{
}

bool GUISelectBoxMultipleController::hasValue()
{
	return true;
}

MutableString* GUISelectBoxMultipleController::getValue()
{
	value->reset();
	determineSelectBoxMultipleOptionControllers();
	for (auto i = 0; i < selectBoxMultipleOptionControllers->size(); i++) {
		auto selectBoxOptionController = java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(i));
		if (selectBoxOptionController->isSelected() == true) {
			value->append((java_cast< GUIElementNode* >(selectBoxOptionController->getNode()))->getValue());
			value->append(VALUE_DELIMITER);
		}
	}
	if (value->length() > 0) {
		value->insert(0, VALUE_DELIMITER);
	}
	return value;
}

void GUISelectBoxMultipleController::setValue(MutableString* value)
{
	determineSelectBoxMultipleOptionControllers();
	unselect();
	unfocus();
	GUIElementNode* selectBoxOptionNodeLast = nullptr;
	for (auto i = 0; i < selectBoxMultipleOptionControllers->size(); i++) {
		auto selectBoxOptionController = java_cast< GUISelectBoxMultipleOptionController* >(selectBoxMultipleOptionControllers->get(i));
		auto selectBoxOptionNode = java_cast< GUIElementNode* >(selectBoxOptionController->getNode());
		searchValue->reset();
		searchValue->append(VALUE_DELIMITER);
		searchValue->append(selectBoxOptionNode->getValue());
		searchValue->append(VALUE_DELIMITER);
		if (value->indexOf(searchValue) != -1) {
			selectBoxOptionController->select();
			selectBoxOptionNode->scrollToNodeX(java_cast< GUIParentNode* >(node));
			selectBoxOptionNode->scrollToNodeY(java_cast< GUIParentNode* >(node));
			selectBoxOptionNodeLast = selectBoxOptionNode;
		}
	}
	if (selectBoxOptionNodeLast != nullptr) {
		(java_cast< GUISelectBoxMultipleOptionController* >(selectBoxOptionNodeLast->getController()))->focus();
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUISelectBoxMultipleController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUISelectBoxMultipleController", 48);
    return c;
}

void GUISelectBoxMultipleController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_DISABLED = u"disabled"_j;
	CONDITION_ENABLED = u"enabled"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUISelectBoxMultipleController::getClass0()
{
	return class_();
}

