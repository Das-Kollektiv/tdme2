// Generated from /tdme/src/tdme/gui/elements/GUIDropDownController.java
#include <tdme/gui/elements/GUIDropDownController.h>

#include <java/lang/Object.h>
#include <java/lang/String.h>
#include <java/lang/StringBuilder.h>
#include <tdme/gui/GUI.h>
#include <tdme/gui/elements/GUIDropDownOptionController.h>
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

using tdme::gui::elements::GUIDropDownController;
using java::lang::Object;
using java::lang::String;
using java::lang::StringBuilder;
using tdme::gui::GUI;
using tdme::gui::elements::GUIDropDownOptionController;
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

GUIDropDownController::GUIDropDownController(const ::default_init_tag&)
	: super(*static_cast< ::default_init_tag* >(0))
{
	clinit();
}

GUIDropDownController::GUIDropDownController(GUINode* node) 
	: GUIDropDownController(*static_cast< ::default_init_tag* >(0))
{
	ctor(node);
}

void GUIDropDownController::init()
{
	childControllerNodes = new _ArrayList();
	dropDownOptionControllers = new _ArrayList();
	isOpen_ = false;
	dropDownNode = nullptr;
	arrowNode = nullptr;
	textElementNode = nullptr;
	value = new MutableString();
}

String* GUIDropDownController::CONDITION_DISABLED;

String* GUIDropDownController::CONDITION_ENABLED;

String* GUIDropDownController::CONDITION_OPENED;

String* GUIDropDownController::CONDITION_CLOSED;

void GUIDropDownController::ctor(GUINode* node)
{
	super::ctor(node);
	init();
	this->disabled = (java_cast< GUIElementNode* >(node))->isDisabled();
}

bool GUIDropDownController::isDisabled()
{
	return disabled;
}

void GUIDropDownController::setDisabled(bool disabled)
{
	auto nodeConditions = (java_cast< GUIElementNode* >(node))->getActiveConditions();
	auto nodeConditionsTextElement = textElementNode->getActiveConditions();
	nodeConditions->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	nodeConditionsTextElement->remove(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	this->disabled = disabled;
	nodeConditions->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	nodeConditionsTextElement->add(this->disabled == true ? CONDITION_DISABLED : CONDITION_ENABLED);
	if (disabled == true && isOpen() == true) {
		toggleOpenState();
	}
}

void GUIDropDownController::initialize()
{
	dropDownNode = java_cast< GUIParentNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_layout_horizontal"_j)->toString()));
	arrowNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_arrow"_j)->toString()));
	textElementNode = java_cast< GUIElementNode* >(node->getScreenNode()->getNodeById(::java::lang::StringBuilder().append(node->getId())->append(u"_layout_horizontal_element"_j)->toString()));
	(java_cast< GUIElementNode* >(node))->getActiveConditions()->add(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
	arrowNode->getActiveConditions()->add(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
	setDisabled(disabled);
}

void GUIDropDownController::dispose()
{
}

void GUIDropDownController::postLayout()
{
}

bool GUIDropDownController::isOpen()
{
	return isOpen_;
}

void GUIDropDownController::unselect()
{
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUIDropDownOptionController* >(childController) != nullptr) {
			(java_cast< GUIDropDownOptionController* >(childController))->unselect();
		}
	}
}

void GUIDropDownController::toggleOpenState()
{
	(java_cast< GUIElementNode* >(node))->getActiveConditions()->remove(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
	arrowNode->getActiveConditions()->remove(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
	isOpen_ = isOpen_ == true ? false : true;
	(java_cast< GUIElementNode* >(node))->getActiveConditions()->add(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
	arrowNode->getActiveConditions()->add(isOpen_ == true ? CONDITION_OPENED : CONDITION_CLOSED);
}

void GUIDropDownController::determineDropDownOptionControllers()
{
	dropDownOptionControllers->clear();
	(java_cast< GUIParentNode* >(node))->getChildControllerNodes(childControllerNodes);
	for (auto i = 0; i < childControllerNodes->size(); i++) {
		auto childControllerNode = java_cast< GUINode* >(childControllerNodes->get(i));
		auto childController = childControllerNode->getController();
		if (dynamic_cast< GUIDropDownOptionController* >(childController) != nullptr) {
			dropDownOptionControllers->add(java_cast< GUIDropDownOptionController* >(childController));
		}
	}
}

int32_t GUIDropDownController::getSelectedOptionIdx()
{
	auto selectBoxOptionControllerIdx = -1;
	for (auto i = 0; i < dropDownOptionControllers->size(); i++) {
		auto selectBoxOptionController = java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(i));
		if (selectBoxOptionController->isSelected() == true) {
			selectBoxOptionControllerIdx = i;
			break;
		}
	}
	return selectBoxOptionControllerIdx;
}

void GUIDropDownController::selectNext()
{
	determineDropDownOptionControllers();
	auto selectBoxOptionControllerIdx = getSelectedOptionIdx();
	unselect();
	if (dropDownOptionControllers->size() == 0)
		return;

	selectBoxOptionControllerIdx = (selectBoxOptionControllerIdx + 1) % dropDownOptionControllers->size();
	if (selectBoxOptionControllerIdx < 0)
		selectBoxOptionControllerIdx += dropDownOptionControllers->size();

	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->select();
	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->getNode()->scrollToNodeX(dropDownNode);
	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->getNode()->scrollToNodeY(dropDownNode);
}

void GUIDropDownController::selectPrevious()
{
	determineDropDownOptionControllers();
	auto selectBoxOptionControllerIdx = getSelectedOptionIdx();
	unselect();
	if (dropDownOptionControllers->size() == 0)
		return;

	selectBoxOptionControllerIdx = (selectBoxOptionControllerIdx - 1) % dropDownOptionControllers->size();
	if (selectBoxOptionControllerIdx < 0)
		selectBoxOptionControllerIdx += dropDownOptionControllers->size();

	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->select();
	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->getNode()->scrollToNodeX(dropDownNode);
	java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(selectBoxOptionControllerIdx))->getNode()->scrollToNodeY(dropDownNode);
}

void GUIDropDownController::handleMouseEvent(GUINode* node, GUIMouseEvent* event)
{
	if (disabled == false && node == static_cast< GUINode* >(this->dropDownNode) && node->isEventBelongingToNode(event) && event->getButton() == 1) {
		event->setProcessed(true);
		if (event->getType() == GUIMouseEvent_Type::MOUSE_RELEASED) {
			toggleOpenState();
			node->getScreenNode()->getGUI()->setFoccussedNode(java_cast< GUIElementNode* >(this->node));
		}
	}
}

void GUIDropDownController::handleKeyboardEvent(GUINode* node, GUIKeyboardEvent* event)
{
	if (disabled == false && node == this->node) {
		switch (event->getKeyCode()) {
		case GUIKeyboardEvent::KEYCODE_UP: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					if (isOpen() == false) {
						toggleOpenState();
					} else {
						selectPrevious();
					}
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_DOWN: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					if (isOpen() == false) {
						toggleOpenState();
					} else {
						selectNext();
					}
				}
			}
			break;
		case GUIKeyboardEvent::KEYCODE_SPACE: {
				event->setProcessed(true);
				if (event->getType() == GUIKeyboardEvent_Type::KEY_PRESSED) {
					toggleOpenState();
				}
				if (isOpen_ == false) {
					node->getScreenNode()->delegateValueChanged(java_cast< GUIElementNode* >(node));
				}
			}
			break;
		}

	}
}

void GUIDropDownController::tick()
{
}

void GUIDropDownController::onFocusGained()
{
}

void GUIDropDownController::onFocusLost()
{
}

bool GUIDropDownController::hasValue()
{
	return true;
}

MutableString* GUIDropDownController::getValue()
{
	value->reset();
	determineDropDownOptionControllers();
	for (auto i = 0; i < dropDownOptionControllers->size(); i++) {
		auto dropDownOptionController = java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(i));
		if (dropDownOptionController->isSelected() == true) {
			value->append((java_cast< GUIElementNode* >(dropDownOptionController->getNode()))->getValue());
		}
	}
	return value;
}

void GUIDropDownController::setValue(MutableString* value)
{
	determineDropDownOptionControllers();
	unselect();
	for (auto i = 0; i < dropDownOptionControllers->size(); i++) {
		auto dropDownOptionController = java_cast< GUIDropDownOptionController* >(dropDownOptionControllers->get(i));
		auto dropDownOptionNode = (java_cast< GUIElementNode* >(dropDownOptionController->getNode()));
		if (value->equals(dropDownOptionNode->getValue())) {
			dropDownOptionController->select();
			dropDownOptionNode->scrollToNodeX(dropDownNode);
			dropDownOptionNode->scrollToNodeY(dropDownNode);
			break;
		}
	}
}

extern java::lang::Class* class_(const char16_t* c, int n);

java::lang::Class* GUIDropDownController::class_()
{
    static ::java::lang::Class* c = ::class_(u"tdme.gui.elements.GUIDropDownController", 39);
    return c;
}

void GUIDropDownController::clinit()
{
struct string_init_ {
	string_init_() {
	CONDITION_DISABLED = u"disabled"_j;
	CONDITION_ENABLED = u"enabled"_j;
	CONDITION_OPENED = u"opened"_j;
	CONDITION_CLOSED = u"closed"_j;
	}
};

	static string_init_ string_init_instance;

	super::clinit();
}

java::lang::Class* GUIDropDownController::getClass0()
{
	return class_();
}

